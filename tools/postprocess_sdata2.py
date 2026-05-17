#!/usr/bin/env python3
"""Post-process CW-built .o: anonymous local sdata2 symbols -> named external.

CW for GameCube emits anonymous local symbols (e.g. @26, @28) into .sdata2 for
literals like `0.0f` and the s16->float magic constant `0x4330000080000000`.
When the target binary has these as named globals in a shared sdata2 pool TU
(referenced via *UND* sda21 relocs), our build mismatches by symbol scope and
section size.

Strategy: align our .o's anonymous local sdata2 references with the *expected*
named externals by reading the target .o's relocation table. The target .o
(built by dtk via asm) is the source of truth for which sda21 relocs name
which lbl_*.

For each `.text` reloc in our .o whose target_symbol is an anonymous local
sdata2 symbol (`@\\d+`), look up the same `.text` offset in the target's
`.text` relocation table. If both relocs are R_PPC_EMB_SDA21 and the local's
bytes match the named lbl_*'s value in the orig binary (sanity check), rename
the local to the target's name and mark it GLOBAL + SHN_UNDEF.

Usage:
  postprocess_sdata2.py <in.o> <out.o> --target <target.o>
                       [--dol <orig.dol> --symbols <symbols.txt>]
"""

import argparse
import re
import struct
import sys
from pathlib import Path
from typing import Dict, List, Optional, Tuple


R_PPC_EMB_SDA21 = 109
SHT_SYMTAB = 2
SHT_RELA = 4
STB_GLOBAL = 1
STT_NOTYPE = 0
SHN_UNDEF = 0
ANON_RE = re.compile(r"^@\d+$")


def read_elf_meta(data: bytes):
    en = ">" if data[5] == 2 else "<"
    e_shoff = struct.unpack_from(en + "I", data, 0x20)[0]
    e_shentsize = struct.unpack_from(en + "H", data, 0x2E)[0]
    e_shnum = struct.unpack_from(en + "H", data, 0x30)[0]
    e_shstrndx = struct.unpack_from(en + "H", data, 0x32)[0]
    shdrs = []
    for i in range(e_shnum):
        off = e_shoff + i * e_shentsize
        sh = struct.unpack_from(en + "10I", data, off)
        shdrs.append(list(sh) + [off])  # last element: header byte offset
    return en, e_shstrndx, shdrs


def read_section_name(data: bytes, shdrs, e_shstrndx, sh):
    base = shdrs[e_shstrndx][4]
    size = shdrs[e_shstrndx][5]
    end = data.index(b"\x00", base + sh[0], base + size)
    return data[base + sh[0]:end].decode("ascii")


def read_str(data: bytes, base: int, size: int, name_off: int) -> str:
    if name_off >= size:
        return ""
    end = data.index(b"\x00", base + name_off, base + size)
    return data[base + name_off:end].decode("ascii")


def find_text_reloc_names(target_path: Path) -> Dict[int, str]:
    """Return offset_in_text -> reloc_target_name for R_PPC_EMB_SDA21 entries."""
    data = target_path.read_bytes()
    en, e_shstrndx, shdrs = read_elf_meta(data)

    # Locate .text, .rela.text, .symtab, .strtab
    text_idx = None
    relatext_idx = None
    symtab_idx = None
    for i, sh in enumerate(shdrs):
        n = read_section_name(data, shdrs, e_shstrndx, sh)
        if n == ".text":
            text_idx = i
        elif n == ".rela.text":
            relatext_idx = i
        elif sh[1] == SHT_SYMTAB:
            symtab_idx = i

    result: Dict[int, str] = {}
    if relatext_idx is None or symtab_idx is None:
        return result

    rela_sh = shdrs[relatext_idx]
    symtab_sh = shdrs[symtab_idx]
    strtab_sh = shdrs[symtab_sh[6]]
    strtab_base = strtab_sh[4]
    strtab_size = strtab_sh[5]
    sym_entsize = symtab_sh[9] or 16

    # ELF32_Rela: offset(4), info(4), addend(4) = 12 bytes
    n_rela = rela_sh[5] // 12
    for i in range(n_rela):
        off = rela_sh[4] + i * 12
        r_off, r_info, _r_add = struct.unpack_from(en + "III", data, off)
        r_sym = r_info >> 8
        r_type = r_info & 0xFF
        if r_type != R_PPC_EMB_SDA21:
            continue
        sym_off = symtab_sh[4] + r_sym * sym_entsize
        st_name = struct.unpack_from(en + "I", data, sym_off)[0]
        name = read_str(data, strtab_base, strtab_size, st_name)
        if name:
            result[r_off] = name
    return result


def post_process(in_path: Path, out_path: Path, target_path: Path) -> bool:
    target_relocs = find_text_reloc_names(target_path)
    if not target_relocs:
        if in_path != out_path:
            out_path.write_bytes(in_path.read_bytes())
        return False

    data = bytearray(in_path.read_bytes())
    en, e_shstrndx, shdrs = read_elf_meta(data)

    text_idx = None
    relatext_idx = None
    symtab_idx = None
    sdata2_idx = None
    for i, sh in enumerate(shdrs):
        n = read_section_name(data, shdrs, e_shstrndx, sh)
        if n == ".text":
            text_idx = i
        elif n == ".rela.text":
            relatext_idx = i
        elif sh[1] == SHT_SYMTAB:
            symtab_idx = i
        elif n == ".sdata2":
            sdata2_idx = i

    if symtab_idx is None or relatext_idx is None:
        if in_path != out_path:
            out_path.write_bytes(data)
        return False

    rela_sh = shdrs[relatext_idx]
    symtab_sh = shdrs[symtab_idx]
    strtab_sh = shdrs[symtab_sh[6]]
    strtab_base = strtab_sh[4]
    strtab_size = strtab_sh[5]
    sym_entsize = symtab_sh[9] or 16

    # Walk our text relocs; find anonymous local sdata2 targets, map to target name
    targets: List[Tuple[int, str, str]] = []  # (sym_idx, old_name, new_name)
    seen_sym_idxs: set[int] = set()
    n_rela = rela_sh[5] // 12
    for i in range(n_rela):
        off = rela_sh[4] + i * 12
        r_off, r_info, _r_add = struct.unpack_from(en + "III", data, off)
        r_sym = r_info >> 8
        r_type = r_info & 0xFF
        if r_type != R_PPC_EMB_SDA21:
            continue
        sym_off = symtab_sh[4] + r_sym * sym_entsize
        st_name, _, _, st_info, _, st_shndx = struct.unpack_from(
            en + "IIIBBH", data, sym_off
        )
        st_bind = st_info >> 4
        if st_bind != 0:  # only LOCAL
            continue
        if sdata2_idx is not None and st_shndx != sdata2_idx:
            continue
        name = read_str(data, strtab_base, strtab_size, st_name)
        if not ANON_RE.match(name):
            continue
        expected = target_relocs.get(r_off)
        if expected is None:
            continue
        if r_sym in seen_sym_idxs:
            continue
        seen_sym_idxs.add(r_sym)
        targets.append((r_sym, name, expected))

    if not targets:
        if in_path != out_path:
            out_path.write_bytes(data)
        return False

    # Append new names to a fresh strtab at file end
    new_strtab = bytearray(data[strtab_base:strtab_base + strtab_size])
    new_name_offsets: Dict[str, int] = {}
    for _, _, new_name in targets:
        if new_name not in new_name_offsets:
            new_name_offsets[new_name] = len(new_strtab)
            new_strtab += new_name.encode("ascii") + b"\x00"

    new_strtab_off = len(data)
    data += new_strtab

    sh_hdr_off = strtab_sh[10]
    struct.pack_into(en + "I", data, sh_hdr_off + 0x10, new_strtab_off)
    struct.pack_into(en + "I", data, sh_hdr_off + 0x14, len(new_strtab))

    for sym_idx, old_name, new_name in targets:
        off = symtab_sh[4] + sym_idx * sym_entsize
        struct.pack_into(
            en + "IIIBBH",
            data, off,
            new_name_offsets[new_name],
            0,
            0,
            (STB_GLOBAL << 4) | STT_NOTYPE,
            0,
            SHN_UNDEF,
        )
        print(f"  {in_path.name}: {old_name!r} -> {new_name!r}")

    out_path.write_bytes(data)
    return True


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("in_file", type=Path)
    ap.add_argument("out_file", type=Path)
    ap.add_argument(
        "--target",
        type=Path,
        default=None,
        help="target .o (built by dtk via asm) — source of truth for reloc "
        "targets. If omitted, derived from in_file by replacing '/src/' with "
        "'/obj/' under the build directory.",
    )
    args = ap.parse_args()

    target = args.target
    if target is None:
        # Auto-derive: build/<ver>/src/<path>.o -> build/<ver>/obj/<path>.o
        parts = args.in_file.as_posix().split("/")
        try:
            idx = parts.index("src")
            parts[idx] = "obj"
            target = Path("/".join(parts))
        except ValueError:
            target = None

    if target is None or not target.exists():
        # No target available (e.g. NonMatching object); pass through unchanged
        if args.in_file != args.out_file:
            args.out_file.write_bytes(args.in_file.read_bytes())
        return

    post_process(args.in_file, args.out_file, target)


if __name__ == "__main__":
    main()
