#!/usr/bin/env python3
"""Preserve four-byte data layout for the two explicitly opted-in TUs.

Use the existing cross-platform LLVM resolver, not a host-specific executable
in build.ninja. Only layout metadata changes; payloads and relocations do not.
"""
from __future__ import annotations

import subprocess
import sys

from postprocess_extab_user import find_llvm_objcopy


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit("usage: postprocess_data_alignment.py <object>")
    subprocess.run(
        [find_llvm_objcopy(), "--remove-section", ".comment",
         "--set-section-alignment", ".data=4", sys.argv[1]],
        check=True,
    )


if __name__ == "__main__":
    main()
