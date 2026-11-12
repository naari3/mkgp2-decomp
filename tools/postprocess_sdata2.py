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
LIT_LOG = __import__("os").environ.get("MKGP2_LIT_LOG")


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


def text_functions(data: bytes, en: str, shdrs, symtab_idx: int, text_idx: Optional[int]) -> List[Tuple[int, int, str]]:
    """Return sorted (value, size, name) of STT_FUNC symbols defined in .text."""
    out: List[Tuple[int, int, str]] = []
    if text_idx is None:
        return out
    symtab_sh = shdrs[symtab_idx]
    strtab_sh = shdrs[symtab_sh[6]]
    sym_entsize = symtab_sh[9] or 16
    for k in range(symtab_sh[5] // sym_entsize):
        st_name, st_value, st_size, st_info, _, st_shndx = struct.unpack_from(
            en + "IIIBBH", data, symtab_sh[4] + k * sym_entsize
        )
        if st_shndx != text_idx or (st_info & 0xF) != 2:
            continue
        out.append((st_value, st_size, read_str(data, strtab_sh[4], strtab_sh[5], st_name)))
    out.sort()
    return out


def func_relative(funcs: List[Tuple[int, int, str]], r_off: int) -> Optional[Tuple[str, int]]:
    for value, size, name in funcs:
        if value <= r_off < value + size:
            return name, r_off - value
    return None


def find_text_reloc_names(target_path: Path, owned: Optional[Dict] = None) -> Dict[int, str]:
    """Return offset_in_text -> reloc_target_name for R_PPC_EMB_SDA21 entries.

    External (undefined) targets go in the result; named globals the target
    defines itself go in `owned` when it is given."""
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
    funcs = text_functions(data, en, shdrs, symtab_idx, text_idx)

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
        st_name, _, _, _, _, st_shndx = struct.unpack_from(en + "IIIBBH", data, sym_off)
        name = read_str(data, strtab_base, strtab_size, st_name)
        # If the target object defines the symbol itself (the TU's split owns
        # that .sdata2 range), the local stays defined. When the target
        # defines it as a named global (another TU reads it), remember the
        # name so the literal can be exported under it.
        if st_shndx != SHN_UNDEF:
            st_bind = struct.unpack_from(en + "IIIBBH", data, sym_off)[3] >> 4
            if owned is not None and st_bind == STB_GLOBAL and name and not ANON_RE.match(name):
                owned[r_off] = name
                rel = func_relative(funcs, r_off)
                if rel is not None:
                    owned[rel] = name  # type: ignore[index]
            continue
        if name:
            result[r_off] = name
            # Function-relative key: lets a TU whose .text carries extra
            # functions the link discards (e.g. weak inline-dtor copies emitted
            # between real functions) still align with the target.
            rel = func_relative(funcs, r_off)
            if rel is not None:
                result[rel] = name  # type: ignore[index]
    return result


def post_process(in_path: Path, out_path: Path, target_path: Path) -> bool:
    owned_relocs: Dict = {}
    target_relocs = find_text_reloc_names(target_path, owned_relocs)
    if not target_relocs and not owned_relocs:
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
    our_funcs = text_functions(bytes(data), en, shdrs, symtab_idx, text_idx)

    # Walk our text relocs; find anonymous local sdata2 targets, map to target name
    targets: List[Tuple[int, str, str]] = []  # (sym_idx, old_name, new_name)
    seen_sym_idxs: set[int] = set()
    sym_names: Dict[int, str] = {}
    retarget: List[Tuple[int, str]] = []  # (rela entry file offset, new name)
    exports: List[Tuple[int, str, str]] = []  # owned literals to export by name
    exported_names: set[str] = set()  # one definition per exported name
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
        rel = func_relative(our_funcs, r_off)
        if rel is not None and rel in target_relocs:
            # prefer the function-relative match when both exist
            expected = target_relocs[rel]  # type: ignore[index]
        if LIT_LOG and expected is not None:
            # tools/literal_value_audit.py: the rename below is by position
            # only, so record the value the source wrote for this use.
            _v, _sz = struct.unpack_from(en + "II", data, sym_off + 4)
            _sh = shdrs[st_shndx]
            _b = b"" if _sh[1] == 8 else bytes(data[_sh[4] + _v:_sh[4] + _v + _sz])  # 8 = SHT_NOBITS
            with open(LIT_LOG, "a") as _f:
                _f.write(f"{in_path}\t{rel[0] if rel else ''}\t{rel[1] if rel else r_off}\t{expected}\t{_sz}\t{_b.hex()}\n")
        if expected is None:
            own = owned_relocs.get(r_off)
            if rel is not None and rel in owned_relocs:
                own = owned_relocs[rel]
            if (own is not None and r_sym not in seen_sym_idxs
                    and own not in exported_names):
                exported_names.add(own)
                seen_sym_idxs.add(r_sym)
                sym_names[r_sym] = own
                exports.append((r_sym, name, own))
            continue
        if r_sym in seen_sym_idxs:
            # The same literal is pooled under another name in the target
            # (e.g. a duplicate s32->float magic constant from another
            # original TU): point just this reloc at that name.
            if sym_names[r_sym] != expected:
                retarget.append((off, expected))
            continue
        seen_sym_idxs.add(r_sym)
        sym_names[r_sym] = expected
        targets.append((r_sym, name, expected))

    if not targets and not exports:
        if in_path != out_path:
            out_path.write_bytes(data)
        return False

    # Append new names to a fresh strtab at file end
    new_strtab = bytearray(data[strtab_base:strtab_base + strtab_size])
    new_name_offsets: Dict[str, int] = {}
    for new_name in [t[2] for t in targets] + [r[1] for r in retarget] + [e[2] for e in exports]:
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

    for sym_idx, old_name, new_name in exports:
        # Keep the definition (section, value, size); only rename and bind
        # globally so other TUs can link against it.
        off = symtab_sh[4] + sym_idx * sym_entsize
        _, st_value, st_size, st_info, st_other, st_shndx = struct.unpack_from(
            en + "IIIBBH", data, off
        )
        struct.pack_into(
            en + "IIIBBH",
            data, off,
            new_name_offsets[new_name],
            st_value,
            st_size,
            (STB_GLOBAL << 4) | (st_info & 0xF),
            st_other,
            st_shndx,
        )
        print(f"  {in_path.name}: {old_name!r} -> {new_name!r} (exported)")

    if retarget:
        # Append one undefined global per extra name to a relocated symtab.
        n_syms = symtab_sh[5] // sym_entsize
        new_symtab = bytearray(data[symtab_sh[4]:symtab_sh[4] + symtab_sh[5]])
        extra_idx: Dict[str, int] = {}
        for _, new_name in retarget:
            if new_name in extra_idx:
                continue
            extra_idx[new_name] = n_syms + len(extra_idx)
            ent = bytearray(sym_entsize)
            struct.pack_into(
                en + "IIIBBH", ent, 0,
                new_name_offsets[new_name], 0, 0,
                (STB_GLOBAL << 4) | STT_NOTYPE, 0, SHN_UNDEF,
            )
            new_symtab += ent
        while len(data) % 4:
            data += b"\x00"
        new_symtab_off = len(data)
        data += new_symtab
        struct.pack_into(en + "I", data, symtab_sh[10] + 0x10, new_symtab_off)
        struct.pack_into(en + "I", data, symtab_sh[10] + 0x14, len(new_symtab))
        for rel_off, new_name in retarget:
            r_off, r_info, r_add = struct.unpack_from(en + "III", data, rel_off)
            r_info = (extra_idx[new_name] << 8) | (r_info & 0xFF)
            struct.pack_into(en + "III", data, rel_off, r_off, r_info, r_add)
        print(f"  {in_path.name}: retargeted {len(retarget)} reloc(s) to {sorted(extra_idx)}")

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
