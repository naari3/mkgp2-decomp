#!/usr/bin/env python3
"""Pin an object's .data alignment to four bytes without dropping .comment.

postprocess_data_alignment.py removes .comment, which also drops MWLD's
per-symbol weak flags, so TUs that carry weak inline copies (dtors shared
with other TUs) fail to link with "multiply-defined". This variant keeps
.comment and only rewrites the alignment of the .data section symbol in it,
plus the ELF sh_addralign of .data. Payloads and relocations do not change.
"""
from __future__ import annotations

import struct
import sys

COMMENT_HEADER = 0x2C
COMMENT_ENTRY = 8


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit("usage: postprocess_data_align4_keep_comment.py <object>")
    path = sys.argv[1]
    d = bytearray(open(path, "rb").read())
    shoff = struct.unpack_from(">I", d, 0x20)[0]
    shnum = struct.unpack_from(">H", d, 0x30)[0]
    shstrndx = struct.unpack_from(">H", d, 0x32)[0]
    secs = [struct.unpack_from(">10I", d, shoff + i * 40) for i in range(shnum)]
    strbase = secs[shstrndx][4]

    def name(off: int) -> str:
        return d[strbase + off:d.index(b"\0", strbase + off)].decode()

    names = [name(s[0]) for s in secs]
    data_idx = names.index(".data")
    comment = secs[names.index(".comment")]
    symtab = next(s for s in secs if s[1] == 2)

    # sh_addralign is the 9th word of the section header.
    struct.pack_into(">I", d, shoff + data_idx * 40 + 32, 4)

    for k in range(symtab[5] // 16):
        off = symtab[4] + k * 16
        info = d[off + 12]
        shndx = struct.unpack_from(">H", d, off + 14)[0]
        if info & 0xF == 3 and shndx == data_idx:  # STT_SECTION
            entry = comment[4] + COMMENT_HEADER + k * COMMENT_ENTRY
            struct.pack_into(">I", d, entry, 4)

    open(path, "wb").write(bytes(d))


if __name__ == "__main__":
    main()
