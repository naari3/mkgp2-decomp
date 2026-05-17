#!/usr/bin/env python3
"""Import named symbols from ~/dolphin-emu/dolphin/mkgp2docs/*.md
into config/GNLJ82/symbols.txt.

Each md file holds reverse-engineering notes with symbol/address pairs in
two recurring shapes:

    Markdown table row:        | 0xADDR | Name | description |
    Markdown rename table:     | 0xADDR | FUN_xxx | NewName |
    Inline mention:            ... `Name` (0xADDR) ...
    Inline @ mention:          ... `Name @ 0xADDR` ...

The scanner extracts (addr, name) candidates from both shapes, dedups
intra-source (one name -> one address, and one address -> one name),
then applies the same placeholder-only rename + cross-source collision
guard as tools/import_symbols_from_ghidra.py.

Run from the mkgp2-decomp project root.
"""
from __future__ import annotations

import re
import sys
from pathlib import Path

DOCS_DIR = Path("../../dolphin-emu/dolphin/mkgp2docs").resolve()
SYM_PATH = Path("config/GNLJ82/symbols.txt")

GHIDRA_DEFAULT_PREFIXES = (
    "fun_", "sub_", "lab_", "dat_", "ptr_",
    "switchd_", "switchdatad_", "cased_",
    "off_", "byte_", "word_", "dword_", "qword_",
    "thunk_fun_", "thunk_sub_",
)
PLACEHOLDER_PREFIXES = ("fn_", "lbl_", "data_")

# Common words that look like C identifiers but are not symbol names;
# they appear in prose, table headers, and type/size columns.
RESERVED = {
    "int", "uint", "u8", "u16", "u32", "u64", "s8", "s16", "s32", "s64",
    "f32", "f64", "float", "double", "char", "byte", "short", "long",
    "void", "ptr", "bool", "size", "type", "enum", "struct", "union",
    "ushort", "uint8", "uint16", "uint32", "string", "wchar", "auto",
    "register", "extern", "static", "const", "volatile", "signed", "unsigned",
    "NULL", "null", "TRUE", "FALSE", "True", "False", "true", "false", "nullptr",
    "Index", "Address", "Name", "Description", "Offset", "Size", "Type",
    "Value", "Field", "Default", "Color", "Note", "Notes", "Count",
    "frame", "stack", "heap", "code",
    "yes", "no", "none", "None", "Yes", "No",
}

ADDR_RE_TXT = r"0x8[0-9a-fA-F]{7}"
SYM_RE_TXT = r"[A-Za-z_][A-Za-z0-9_]{2,}"

# Inline: Name(0xADDR) or Name @ 0xADDR, both optionally backtick-wrapped.
INLINE_RE = re.compile(
    rf"`?({SYM_RE_TXT})`?\s*[\(@]\s*`?({ADDR_RE_TXT})`?"
)
ADDR_ONLY = re.compile(rf"^`?({ADDR_RE_TXT})`?$")
SYM_ONLY = re.compile(rf"^`?({SYM_RE_TXT})`?$")

SYM_LINE = re.compile(
    r"^(?P<name>\S+)\s*=\s*(?P<section>[.\w]+):(?P<addr>0x[0-9a-fA-F]+);(?P<rest>.*)$"
)
TABLE_HEADER_SEP = re.compile(
    r"^\s*\|?\s*:?-{3,}:?\s*(\|\s*:?-{3,}:?\s*)+\|?\s*$"
)


def is_ghidra_default(name: str) -> bool:
    nl = name.lower()
    return any(nl.startswith(p) for p in GHIDRA_DEFAULT_PREFIXES)


def is_placeholder(name: str) -> bool:
    nl = name.lower()
    return any(nl.startswith(p) for p in PLACEHOLDER_PREFIXES)


def is_reserved(name: str) -> bool:
    return name in RESERVED


def is_valid_name(nm: str) -> bool:
    return not (is_ghidra_default(nm) or is_placeholder(nm) or is_reserved(nm))


def extract_candidates(path: Path) -> list[tuple[str, int, str]]:
    """Return [(name, addr_int, source_descr)] from one md file."""
    out: list[tuple[str, int, str]] = []
    text = path.read_text(encoding="utf-8")

    # 1) Inline mentions across the whole file.
    for m in INLINE_RE.finditer(text):
        nm = m.group(1)
        if not is_valid_name(nm):
            continue
        addr = int(m.group(2), 16)
        out.append((nm, addr, f"{path.name}:inline"))

    # 2) Markdown table rows. Find the cell that is *only* an address,
    # then look right (then left) for the first cell that is *only* an
    # acceptable C identifier.
    for lineno, line in enumerate(text.splitlines(), 1):
        if "|" not in line:
            continue
        if TABLE_HEADER_SEP.match(line):
            continue
        cells = [c.strip() for c in line.split("|")]
        if cells and cells[0] == "":
            cells = cells[1:]
        if cells and cells[-1] == "":
            cells = cells[:-1]
        if len(cells) < 2:
            continue
        addr_idx = -1
        addr_int = -1
        for i, c in enumerate(cells):
            mm = ADDR_ONLY.match(c)
            if mm:
                addr_idx = i
                addr_int = int(mm.group(1), 16)
                break
        if addr_idx < 0:
            continue
        ordering = list(range(addr_idx + 1, len(cells))) + list(
            range(addr_idx - 1, -1, -1)
        )
        for j in ordering:
            cand = cells[j]
            nm_m = SYM_ONLY.match(cand)
            if not nm_m:
                continue
            nm = nm_m.group(1)
            if not is_valid_name(nm):
                continue
            out.append((nm, addr_int, f"{path.name}:L{lineno}"))
            break
    return out


def main() -> int:
    if not DOCS_DIR.exists():
        sys.exit(f"mkgp2docs not found: {DOCS_DIR}")
    if not SYM_PATH.exists():
        sys.exit(f"symbols.txt not found: {SYM_PATH}")

    md_files = sorted(DOCS_DIR.glob("*.md"))
    print(f"scanning {len(md_files)} md files under {DOCS_DIR}")

    name_map: dict[int, str] = {}
    name_first_addr: dict[str, int] = {}
    addr_first_name: dict[int, str] = {}
    intra_name_dups: list[tuple[str, int, int]] = []
    intra_addr_conflicts: list[tuple[int, str, str]] = []
    raw_count = 0
    for md in md_files:
        for nm, addr, _src in extract_candidates(md):
            raw_count += 1
            existing_addr = name_first_addr.get(nm)
            if existing_addr is not None and existing_addr != addr:
                intra_name_dups.append((nm, existing_addr, addr))
                continue
            existing_name = addr_first_name.get(addr)
            if existing_name is not None and existing_name != nm:
                intra_addr_conflicts.append((addr, existing_name, nm))
                continue
            name_first_addr[nm] = addr
            addr_first_name[addr] = nm
            name_map[addr] = nm

    print(
        f"raw mentions: {raw_count}, unique (addr->name) kept: {len(name_map)} "
        f"(name dups skipped: {len(intra_name_dups)}, "
        f"addr conflicts skipped: {len(intra_addr_conflicts)})"
    )

    lines = SYM_PATH.read_text(encoding="utf-8").splitlines()
    existing_addr_for_name: dict[str, int] = {}
    for line in lines:
        m = SYM_LINE.match(line)
        if not m:
            continue
        cur_name = m.group("name")
        if is_placeholder(cur_name):
            continue
        existing_addr_for_name.setdefault(cur_name, int(m.group("addr"), 16))

    renamed = 0
    already_matching = 0
    kept_non_placeholder = 0
    cross_source_collisions: list[tuple[str, int, int]] = []
    seen_addrs: set[int] = set()
    out_lines: list[str] = []
    for line in lines:
        m = SYM_LINE.match(line)
        if not m:
            out_lines.append(line)
            continue
        cur_name = m.group("name")
        section = m.group("section")
        addr_str = m.group("addr")
        rest = m.group("rest")
        addr_int = int(addr_str, 16)
        seen_addrs.add(addr_int)
        new_name = name_map.get(addr_int)
        if new_name is None:
            out_lines.append(line)
            continue
        if cur_name == new_name:
            already_matching += 1
            out_lines.append(line)
            continue
        if not is_placeholder(cur_name):
            kept_non_placeholder += 1
            out_lines.append(line)
            continue
        existing_addr = existing_addr_for_name.get(new_name)
        if existing_addr is not None and existing_addr != addr_int:
            cross_source_collisions.append((new_name, existing_addr, addr_int))
            out_lines.append(line)
            continue
        out_lines.append(f"{new_name} = {section}:{addr_str};{rest}")
        renamed += 1

    not_in_symbols = sum(1 for a in name_map if a not in seen_addrs)

    SYM_PATH.write_text("\n".join(out_lines) + "\n", encoding="utf-8")
    print(f"renamed (placeholder -> mkgp2docs name): {renamed}")
    print(f"already-matching: {already_matching}")
    print(f"kept non-placeholder (externals/ghidra/dtk-named): {kept_non_placeholder}")
    print(f"cross-source collisions skipped: {len(cross_source_collisions)}")
    print(f"mkgp2docs addresses not present in symbols.txt: {not_in_symbols}")
    for nm, a1, a2 in intra_name_dups[:10]:
        print(f"  intra-dump name dup: {nm}  kept@{a1:#x}  skip@{a2:#x}")
    for a, n1, n2 in intra_addr_conflicts[:10]:
        print(f"  intra-dump addr conflict: @{a:#x}  kept={n1!r}  skip={n2!r}")
    for nm, a1, a2 in cross_source_collisions[:10]:
        print(f"  cross-source: {nm}  existing@{a1:#x}  mkgp2docs@{a2:#x}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
