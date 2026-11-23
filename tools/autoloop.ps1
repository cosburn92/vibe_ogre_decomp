# tools/autoloop.ps1 - one function per fresh Claude session, so context never builds up.
# Usage:  powershell -File tools/autoloop.ps1 [-Runs 20] [-Model opus]
# Stop early: create a file named STOP in the repo root.
param(
    [int]$Runs = 20,
    [string]$Model = "opus"
)

$ErrorActionPreference = "Stop"
$repo = Split-Path -Parent $PSScriptRoot
Set-Location $repo
$logDir = Join-Path $repo "build/autoloop"
New-Item -ItemType Directory -Force $logDir | Out-Null

$prompt = @'
You are running unattended in a loop: one function per session, then exit.

1. Pick the next function worth doing. Prefer functions OB64-Decomp lacks
   (see the upstream-exports memory). Don't pick anything a recent commit
   (git log -20) already covers.
2. Decompile it using the usual workflow (decomp-workflow memory): make,
   funcdiff.py, romdiff.sh, sizecheck.sh.
3. If the build still matches baserom, commit just that change. Use the usual
   message style, "<segment>: <what it does> <func> matches|rewritten",
   with the Co-Authored-By trailer.
4. If anything goes wrong (build mismatch you can't fix, a destructive choice,
   a dead end), do NOT commit. Restore the working tree with
   git checkout -- . and git clean -fd src (re-run the splat split if the
   yaml had changed, since asm/ is untracked), then write one paragraph
   explaining the problem to build/autoloop/PROBLEM.txt and stop.

Keep reads small: pipe big asm/diff output through head or grep.
Do exactly one function, then stop.
'@

for ($i = 1; $i -le $Runs; $i++) {
    if (Test-Path "STOP") { Write-Host "STOP file found, exiting."; break }
    if (Test-Path "build/autoloop/PROBLEM.txt") {
        Write-Host "PROBLEM.txt exists, see it before rerunning."; break
    }

    $before = git rev-parse HEAD
    $stamp  = Get-Date -Format "yyyyMMdd-HHmmss"
    Write-Host "[$i/$Runs] $stamp starting..."

    claude -p $prompt --model $Model --permission-mode acceptEdits |
        Tee-Object -FilePath "$logDir/$stamp.log"

    if ($LASTEXITCODE -ne 0) { Write-Host "claude exited $LASTEXITCODE, stopping."; break }

    $after = git rev-parse HEAD
    $dirty = git status --porcelain
    if ($after -eq $before) { Write-Host "No commit this run, stopping."; break }
    if ($dirty) { Write-Host "Working tree left dirty, stopping."; break }

    Write-Host "  -> $(git log -1 --format=%s)"
}
