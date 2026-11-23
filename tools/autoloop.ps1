# tools/autoloop.ps1 - a few functions per fresh Claude session, so context stays small.
# Usage:  powershell -File tools/autoloop.ps1 [-Runs 10] [-Min 3] [-Max 5] [-Model opus]
#   -Runs  sessions to run
#   -Min   functions each session does before it may stop
#   -Max   functions each session does at most; between Min and Max it decides
# Stop early: create a file named STOP in the repo root.
param(
    [int]$Runs = 10,
    [int]$Min = 3,
    [int]$Max = 5,
    [string]$Model = "opus"
)

$ErrorActionPreference = "Stop"
if ($Min -lt 1 -or $Max -lt $Min) { throw "need 1 <= Min <= Max (got Min=$Min, Max=$Max)" }
$repo = Split-Path -Parent $PSScriptRoot
Set-Location $repo
$logDir = Join-Path $repo "build/autoloop"
New-Item -ItemType Directory -Force $logDir | Out-Null

$prompt = @'
You are running unattended in a loop. This session does between MIN and MAX
functions, one commit per function, then exits.

For each function:
1. Pick the next function worth doing. First look at git log -1: if a sibling
   or near-copy of the function just committed is still INCLUDE_ASM in the
   same file, take it. Otherwise prefer functions OB64-Decomp lacks (see the
   upstream-exports memory), smallest game functions first. Skip anything a
   recent commit (git log -20) already covers.
2. Decompile it using the usual workflow (decomp-workflow memory).
3. When it matches, commit just that change: "<segment>: <what it does>
   <func> matches", with the Co-Authored-By trailer. If after a fair effort it
   is the same size or a few instructions off, keep the C under
   #ifdef NON_MATCHING (note what differs) with INCLUDE_ASM in #else, check the
   build still matches baserom, and commit it as "... rewritten, <how close>".
4. If anything goes wrong (build mismatch you can't fix, a destructive choice,
   a dead end), do NOT commit it. Restore the working tree with
   git checkout -- . and git clean -fd src, write one paragraph explaining the
   problem to build/autoloop/PROBLEM.txt and stop the session.

When to stop:
- Before MIN commits, keep going (unless step 4 applies).
- Between MIN and MAX, decide after each commit. Continue when the next
  function is a cheap win: a sibling of what you just did, or small and in a
  file whose types you already know. Stop when the next one would be a fresh
  start in an unfamiliar file, when the last one was a long grind, or when
  this session's context has grown long.
- Never go past MAX.
- Never stop with uncommitted changes.
End with one line: "DONE <n> functions: <reason for stopping here>".

Run every shell command with the Bash tool (not PowerShell), and use exactly
these forms, which are pre-approved; anything else will be refused:
  build:    wsl bash -lc "cd /mnt/c/Users/Connor/dev/ogredecomp && make 2>&1 | tail -3"
  diff:     wsl bash -lc "cd /mnt/c/Users/Connor/dev/ogredecomp && sh tools/objcmp.sh SEG FUNC ROM SIZE"
  sizes:    wsl bash -lc "cd /mnt/c/Users/Connor/dev/ogredecomp && sh tools/sizecheck.sh SEG"
  git:      git status / log / diff / add / commit / checkout -- . / clean -fd src
Keep reads small: pipe big asm/diff output through head or grep.
'@
$prompt = $prompt.Replace("MIN", "$Min").Replace("MAX", "$Max")

$total = 0
for ($i = 1; $i -le $Runs; $i++) {
    if (Test-Path "STOP") { Write-Host "STOP file found, exiting."; break }
    if (Test-Path "build/autoloop/PROBLEM.txt") {
        Write-Host "PROBLEM.txt exists, see it before rerunning."; break
    }

    $before = git rev-parse HEAD
    $stamp  = Get-Date -Format "yyyyMMdd-HHmmss"
    Write-Host "[$i/$Runs] $stamp starting ($Min-$Max functions)..."

    # prompt goes in on stdin: PowerShell 5.1 mangles embedded quotes in native arguments
    $prompt | claude -p --model $Model --permission-mode acceptEdits |
        Tee-Object -FilePath "$logDir/$stamp.log"

    if ($LASTEXITCODE -ne 0) { Write-Host "claude exited $LASTEXITCODE, stopping."; break }

    $n = [int](git rev-list --count "$before..HEAD")
    $total += $n
    git log --format="  -> %s" "$before..HEAD" | Write-Host
    Write-Host "  $n commits this run, $total total"

    if (git status --porcelain) { Write-Host "Working tree left dirty, stopping."; break }
    if ($n -eq 0) { Write-Host "No commit this run, stopping."; break }
    if ($n -gt $Max) { Write-Host "  (note: went past Max=$Max)" }
}
