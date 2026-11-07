#!/usr/bin/env python3
"""Trim trailing .sdata2 bytes that no symbol covers any more.

postprocess_sdata2.py turns an anonymous literal (e.g. `0.0f`) into an
undefined reference to the target's shared-pool lbl_*, but the literal's
bytes stay in our .sdata2. When those bytes are at the end of the section
and no symbol or relocation points at them, cut the section size back to the
end of the last defined symbol so the link does not shift the pool.
"""
from __future__ import annotations

import struct
import sys


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit("usage: postprocess_sdata2_trim.py <object>")
    path = sys.argv[1]
    d = bytearray(open(path, "rb").read())
    shoff = struct.unpack_from(">I", d, 0x20)[0]
    shentsize, shnum, shstrndx = struct.unpack_from(">HHH", d, 0x2E)
    secs = [list(struct.unpack_from(">10I", d, shoff + i * shentsize)) for i in range(shnum)]
    strbase = secs[shstrndx][4]

    def name(off: int) -> str:
        return d[strbase + off:d.index(b"\0", strbase + off)].decode()

    names = [name(s[0]) for s in secs]
    if ".sdata2" not in names:
        return
    idx = names.index(".sdata2")
    size = secs[idx][5]
    end = 0
    for s in secs:
        if s[1] == 2:  # SHT_SYMTAB
            for i in range(s[5] // 16):
                _, value, ssize, _, _, shndx = struct.unpack_from(">IIIBBH", d, s[4] + i * 16)
                if shndx == idx:
                    end = max(end, value + ssize)
        if s[1] == 4 and s[7] == idx:  # SHT_RELA applying to .sdata2
            for i in range(s[5] // 12):
                r_off = struct.unpack_from(">I", d, s[4] + i * 12)[0]
                end = max(end, r_off + 4)
    end = (end + 3) & ~3
    if end == 0 or end >= size:
        return
    struct.pack_into(">I", d, shoff + idx * shentsize + 0x14, end)
    open(path, "wb").write(d)
    print(f"  {path}: .sdata2 0x{size:X} -> 0x{end:X} (trimmed)")


if __name__ == "__main__":
    main()
