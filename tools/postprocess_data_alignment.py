#!/usr/bin/env python3
"""Preserve four-byte data layout for the two explicitly opted-in TUs.

Use the existing cross-platform LLVM resolver, not a host-specific executable
in build.ninja. Only layout metadata changes; payloads and relocations do not.
"""
from __future__ import annotations

import struct
import subprocess
import sys

from postprocess_extab_user import find_llvm_objcopy


def unreferenced_sections(path: str, names: tuple[str, ...]) -> list[str]:
    """Return those of `names` that no symbol or relocation refers to.

    postprocess_sdata2.py turns literal refs into UNDEF externals but leaves
    the literal bytes behind. Without .comment MWLD links that orphan
    section instead of stripping it, shifting every later small-data symbol.
    """
    data = open(path, "rb").read()
    shoff, = struct.unpack_from(">I", data, 0x20)
    shentsize, shnum, shstrndx = struct.unpack_from(">HHH", data, 0x2E)
    shdrs = [struct.unpack_from(">10I", data, shoff + i * shentsize) for i in range(shnum)]
    strbase = shdrs[shstrndx][4]

    def secname(sh):
        end = data.index(b"\0", strbase + sh[0])
        return data[strbase + sh[0]:end].decode()

    wanted = {i: secname(sh) for i, sh in enumerate(shdrs) if secname(sh) in names}
    used = set()
    for sh in shdrs:
        if sh[1] != 2:  # SHT_SYMTAB
            continue
        syms = [struct.unpack_from(">IIIBBH", data, sh[4] + j * 16) for j in range(sh[5] // 16)]
        section_syms = {}
        for j, (_, _, _, info, _, shndx) in enumerate(syms):
            if shndx in wanted:
                if info & 0xF == 3:  # STT_SECTION
                    section_syms[j] = shndx
                else:
                    used.add(shndx)
        for rsh in shdrs:
            if rsh[1] != 4:  # SHT_RELA
                continue
            for k in range(rsh[5] // 12):
                r_info, = struct.unpack_from(">I", data, rsh[4] + k * 12 + 4)
                if (r_info >> 8) in section_syms:
                    used.add(section_syms[r_info >> 8])
    return [n for i, n in wanted.items() if i not in used]


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit("usage: postprocess_data_alignment.py <object>")
    extra = []
    for name in unreferenced_sections(sys.argv[1], (".sdata2",)):
        extra += ["--remove-section", name]
    subprocess.run(
        [find_llvm_objcopy(), *extra, "--remove-section", ".comment",
         "--set-section-alignment", ".data=4", sys.argv[1]],
        check=True,
    )


if __name__ == "__main__":
    main()
