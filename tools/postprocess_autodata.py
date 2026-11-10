#!/usr/bin/env python3
"""Post-compile step for the data-only TUs of tools/autodata.py.

Removes .comment (MWLD takes symbol alignment from it, which overrides the ELF
section alignment, and dead-strips unreferenced objects) and, for the units listed
in src/game/autodata/align4.txt, pins the data sections to 4-byte alignment because
the original data starts on a 4-byte boundary there. Payloads and relocations do not
change.
"""
import os
import subprocess
import sys

from postprocess_extab_user import find_llvm_objcopy

SECS = (".rodata", ".data", ".sdata", ".sdata2")


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit("usage: postprocess_autodata.py <object>")
    obj = sys.argv[1]
    root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    stem = "game/autodata/" + os.path.splitext(os.path.basename(obj))[0]
    lst = os.path.join(root, "src", "game", "autodata", "align4.txt")
    names = set()
    if os.path.exists(lst):
        names = {l.strip() for l in open(lst) if l.strip() and not l.startswith("#")}
    cmd = [find_llvm_objcopy(), "--remove-section", ".comment"]
    if stem in names:
        for s in SECS:
            cmd += ["--set-section-alignment", s + "=4"]
    subprocess.run(cmd + [obj], check=True)


if __name__ == "__main__":
    main()
