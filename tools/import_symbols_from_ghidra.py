#!/usr/bin/env python3
"""Import named symbols from tools/ghidra_symbol_dump.json into config/GNLJ82/symbols.txt.

JSON format (produced by an out-of-band Ghidra MCP dump):
    {"functions": {"0xaddr": {"name": ..., "size": ...}},
     "globals":   {"0xaddr": {"name": ..., "type_hint": ...}}}

symbols.txt format: `Name = .section:0xADDR; // type:T size:S scope:Z`

Conflict policy:
- If symbols.txt at the address has a placeholder name (`fn_<addr>`,
  `lbl_<addr>`, `data_<addr>`), it gets renamed to the Ghidra name.
- If the existing name is anything else (e.g. PPCEABI runtime helpers
  dtk identified, externals.txt seeds), it is preserved untouched.
- Ghidra default-name leftovers (FUN_, SUB_, LAB_, DAT_, switchD_,
  thunk_FUN_, ...) are double-filtered out as a safety net even if
  they slipped through the dump's earlier filter.

Run from the mkgp2-decomp project root.
"""
from __future__ import annotations

import json
import re
import sys
from pathlib import Path

DUMP_PATH = Path("tools/ghidra_symbol_dump.json")
SYM_PATH = Path("config/GNLJ82/symbols.txt")

GHIDRA_DEFAULT_PREFIXES = (
    "fun_", "sub_", "lab_", "dat_", "ptr_",
    "switchd_", "switchdatad_", "cased_",
    "off_", "byte_", "word_", "dword_", "qword_",
    "thunk_fun_", "thunk_sub_",
)

PLACEHOLDER_PREFIXES = ("fn_", "lbl_", "data_")


def is_ghidra_default(name: str) -> bool:
    nl = name.lower()
    return any(nl.startswith(p) for p in GHIDRA_DEFAULT_PREFIXES)


def is_placeholder(name: str) -> bool:
    nl = name.lower()
    return any(nl.startswith(p) for p in PLACEHOLDER_PREFIXES)


SYM_LINE = re.compile(
    r"^(?P<name>\S+)\s*=\s*(?P<section>[.\w]+):(?P<addr>0x[0-9a-fA-F]+);(?P<rest>.*)$"
)


def main() -> int:
    if not DUMP_PATH.exists():
        sys.exit(f"dump not found: {DUMP_PATH}")
    if not SYM_PATH.exists():
        sys.exit(f"symbols.txt not found: {SYM_PATH}")

    dump = json.loads(DUMP_PATH.read_text(encoding="utf-8"))
    fn = dump.get("functions", {})
    gl = dump.get("globals", {})

    # Phase 1: dedup names within the Ghidra dump itself.
    # The linker requires every symbol name to map to exactly one address, so
    # if Ghidra has the same human-readable name (e.g. "LUT_Sine") on two
    # different addresses, only the first occurrence wins; the rest stay as
    # placeholders and are reported.
    name_map: dict[int, str] = {}
    ghidra_first_addr: dict[str, int] = {}
    intra_dump_dups: list[tuple[str, int, int]] = []  # (name, kept_addr, skipped_addr)
    skipped_default = 0
    for table_name, table in (("globals", gl), ("functions", fn)):
        for addr_str, info in table.items():
            nm = info.get("name", "")
            if is_ghidra_default(nm):
                skipped_default += 1
                continue
            addr_int = int(addr_str, 16)
            existing = ghidra_first_addr.get(nm)
            if existing is not None and existing != addr_int:
                intra_dump_dups.append((nm, existing, addr_int))
                continue
            ghidra_first_addr[nm] = addr_int
            name_map[addr_int] = nm  # functions overwrite globals at same addr

    print(
        f"ghidra dump: {len(fn)} fn + {len(gl)} gl, "
        f"after default-name filter: {len(name_map)} "
        f"(default-name skipped: {skipped_default}, "
        f"intra-dump name dups skipped: {len(intra_dump_dups)})"
    )

    # Phase 2: build "name -> address" index for the existing symbols.txt so
    # we can detect cross-source collisions (e.g. dtk auto-detected
    # __DBExceptionDestination at addr A, Ghidra wants to apply same name to
    # addr B). In such cases we keep the placeholder rather than create a
    # multiply-defined linker error.
    lines = SYM_PATH.read_text(encoding="utf-8").splitlines()
    existing_addr_for_name: dict[str, int] = {}
    for line in lines:
        m = SYM_LINE.match(line)
        if not m:
            continue
        cur_name = m.group("name")
        if is_placeholder(cur_name):
            continue
        addr_int = int(m.group("addr"), 16)
        # First wins; subsequent entries with the same name in symbols.txt are
        # themselves a pre-existing duplicate and not our problem to fix.
        existing_addr_for_name.setdefault(cur_name, addr_int)

    # Phase 3: rewrite pass.
    renamed = 0
    already_matching = 0
    kept_non_placeholder = 0
    cross_source_collisions: list[tuple[str, int, int]] = []  # (name, existing_addr, ghidra_addr)
    seen_addrs: set[int] = set()
    out: list[str] = []
    for line in lines:
        m = SYM_LINE.match(line)
        if not m:
            out.append(line)
            continue
        cur_name = m.group("name")
        section = m.group("section")
        addr_str = m.group("addr")
        rest = m.group("rest")
        addr_int = int(addr_str, 16)
        seen_addrs.add(addr_int)
        new_name = name_map.get(addr_int)
        if new_name is None:
            out.append(line)
            continue
        if cur_name == new_name:
            already_matching += 1
            out.append(line)
            continue
        if not is_placeholder(cur_name):
            kept_non_placeholder += 1
            out.append(line)
            continue
        # Cross-source collision: this Ghidra name is already used by another
        # symbol at a different address in symbols.txt.
        existing_addr = existing_addr_for_name.get(new_name)
        if existing_addr is not None and existing_addr != addr_int:
            cross_source_collisions.append((new_name, existing_addr, addr_int))
            out.append(line)
            continue
        out.append(f"{new_name} = {section}:{addr_str};{rest}")
        renamed += 1

    not_in_symbols = sum(1 for a in name_map if a not in seen_addrs)

    SYM_PATH.write_text("\n".join(out) + "\n", encoding="utf-8")
    print(f"renamed (fn_<addr> -> ghidra name): {renamed}")
    print(f"already-matching: {already_matching}")
    print(f"kept non-placeholder (externals.txt / dtk-named): {kept_non_placeholder}")
    print(f"cross-source collisions skipped: {len(cross_source_collisions)}")
    print(f"ghidra addresses not present in symbols.txt: {not_in_symbols}")
    for nm, a1, a2 in intra_dump_dups[:10]:
        print(f"  intra-dump dup: {nm}  kept@{a1:#x}  skip@{a2:#x}")
    for nm, a1, a2 in cross_source_collisions[:10]:
        print(f"  cross-source: {nm}  existing@{a1:#x}  ghidra@{a2:#x}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
