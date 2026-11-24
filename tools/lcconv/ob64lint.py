"""Interface check for an OB64-Decomp export, run before pushing.

OB64's final verification compares every C declaration and call with the C definition
it links to, across all of their source files, and rejects anything not already in
their reviewed baseline. So an export must add no new findings: neither in our new
files, nor in their existing files that call a function we now define in C (PR #3
needed fixes in 15 of their files for that reason).

This runs tools/ilint.py on the export checkout and on the base branch it will merge
into, and prints the findings only the export has.

usage: ob64lint.py OB64-CHECKOUT [BASE-REF]     (BASE-REF defaults to origin/main)
Exit status 1 when the export adds an error or a gap. Gaps (struct types, f()
declarations) aren't rejections by themselves, but each new one is something their
maintainers must review, so we fix them when the right type is known.
"""
import io
import os
import subprocess
import sys
import tarfile
import tempfile

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
import ilint


def findings_in(tree):
    """ilint findings for an OB64 source tree, with paths relative to the tree."""
    cwd = os.getcwd()
    os.chdir(tree)
    try:
        return ilint.check(ilint.source_files(['src']), ['-Iinclude'])
    finally:
        os.chdir(cwd)


def identity(finding):
    # Line numbers move when files are edited, so a finding is matched by what it says.
    path = finding['at'].rsplit(':', 1)[0].replace('\\', '/')
    return (finding['symbol'], finding['cls'], path, finding['got'], finding['want'])


def main():
    if len(sys.argv) not in (2, 3):
        sys.exit(__doc__)
    checkout = os.path.abspath(sys.argv[1])
    base = sys.argv[2] if len(sys.argv) == 3 else 'origin/main'

    with tempfile.TemporaryDirectory() as base_tree:
        archive = subprocess.run(['git', '-C', checkout, 'archive', base, 'src', 'include'],
                                 capture_output=True, check=True).stdout
        with tarfile.open(fileobj=io.BytesIO(archive)) as tar:
            tar.extractall(base_tree, filter='data')
        before = {identity(f) for f in findings_in(base_tree)}
    after = findings_in(checkout)
    new = [f for f in after if identity(f) not in before]

    for f in new:
        print('%-5s %-12s %s  %s\n      has  %s\n      def  %s  (%s)' % (
            f['severity'], f['cls'], f['symbol'], f['at'], f['got'], f['want'], f['ref']))
    blocking = [f for f in new if f['severity'] in ('error', 'gap')]
    print('\nexport vs %s: %d new errors, %d new gaps, %d new nodef' % (
        base, sum(f['severity'] == 'error' for f in new), sum(f['severity'] == 'gap' for f in new),
        sum(f['severity'] == 'nodef' for f in new)))
    sys.exit(1 if blocking else 0)


if __name__ == '__main__':
    main()
