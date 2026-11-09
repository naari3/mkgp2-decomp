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

Phase 4 (src/ sweep):
- Every function rename in symbols.txt is mirrored in src/**/*.{c,cpp}
  by replacing `\\bfn_<ADDR>\\b` -> `<new_name>`. Without this, src files
  defining `fn_<addr>(...)` keep exporting the old symbol while dtk's
  auto-asm callers reference the new name -> linker `undefined` errors.
- Addresses whose rename had no `fn_<addr>` ref in src/ are reported
  as WARN (likely the C body uses an alias-label name like
  `gTRKInterruptVectorTableEnd` at 0x800053E0; needs manual handling).

Run from the mkgp2-decomp project root.
"""
from __future__ import annotations

import json
import re
import sys
from pathlib import Path

DUMP_PATH = Path("tools/ghidra_symbol_dump.json")
SYM_PATH = Path("config/GNLJ82/symbols.txt")
SRC_DIR = Path("src")
SRC_GLOBS = ("*.c", "*.cpp")

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
    rename_pairs: list[tuple[int, str]] = []  # (addr_int, new_name) for Phase 4 src/ sweep
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
        # Track for Phase 4 src/ sweep: only addresses we actually renamed need
        # their C body identifier updated. Limit to .text (function) renames —
        # globals (.sdata/.bss) live in headers/externs and aren't body-defined
        # in src/*.c files with `fn_<addr>(` form.
        if section.startswith(".text") or section.startswith(".init"):
            rename_pairs.append((addr_int, new_name))

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

    # Phase 4: sweep src/ for fn_<ADDR> definitions/refs and rename to match.
    # Without this, src files defining `fn_<addr>(...)` keep exporting the old
    # symbol while dtk's auto-asm callers reference the new name -> link error.
    # Only matters for addresses we just renamed in this run.
    src_renames = sweep_src_rename(rename_pairs)
    print(f"src/ sweep: {src_renames['files_changed']} files, "
          f"{src_renames['replacements']} replacements")
    for path, n in src_renames["per_file"][:15]:
        print(f"  {path}: {n}")
    if src_renames["unswept_renames"]:
        print(f"WARN: {len(src_renames['unswept_renames'])} symbols.txt renames "
              f"had no `fn_<addr>` ref in src/. If the function is defined in C "
              f"under a different name (e.g. an alias label), you must manually "
              f"rename its C body to match the new symbol name. Examples:")
        for addr_hex, new_name in src_renames["unswept_renames"][:10]:
            print(f"  {addr_hex} -> {new_name}")
    return 0


def sweep_src_rename(rename_pairs: list[tuple[int, str]]) -> dict:
    """Sweep src/ for `fn_<ADDR>` identifiers and replace with the new name.

    rename_pairs: list of (address_int, new_name) for renames just performed
    in symbols.txt. Searches `src/**/*.{c,cpp}` for `\\bfn_<ADDR>\\b` (both
    upper- and lower-case hex) and replaces in place. Returns stats and the
    list of addresses whose `fn_<addr>` ref was NOT found anywhere in src/
    (these usually mean the C body uses a different name like an alias label
    and needs manual attention to avoid linker `undefined` errors).
    """
    if not SRC_DIR.exists():
        return {"files_changed": 0, "replacements": 0, "per_file": [],
                "unswept_renames": []}

    # Build {old_token: new_name}. Two case variants per addr (CW asm tends to
    # emit upper-case, but some sources may use lower-case).
    rename_map: dict[str, str] = {}
    for addr_int, new_name in rename_pairs:
        addr_upper = f"{addr_int:08X}"
        rename_map[f"fn_{addr_upper}"] = new_name
        rename_map[f"fn_{addr_upper.lower()}"] = new_name

    per_file: list[tuple[str, int]] = []
    total_replacements = 0
    swept_addrs: set[int] = set()

    src_files: list[Path] = []
    for pat in SRC_GLOBS:
        src_files.extend(SRC_DIR.rglob(pat))

    for path in src_files:
        try:
            txt = path.read_text(encoding="utf-8")
        except (OSError, UnicodeDecodeError):
            continue
        new_txt = txt
        file_replacements = 0
        for old, new in rename_map.items():
            if old not in new_txt:
                continue
            replaced = re.subn(r"\b" + re.escape(old) + r"\b", new, new_txt)
            if replaced[1]:
                new_txt = replaced[0]
                file_replacements += replaced[1]
                # Recover the addr from the old token (`fn_XXXXXXXX`)
                swept_addrs.add(int(old[3:], 16))
        if file_replacements:
            path.write_text(new_txt, encoding="utf-8")
            per_file.append((str(path).replace("\\", "/"), file_replacements))
            total_replacements += file_replacements

    unswept = [
        (f"0x{addr:08x}", new_name)
        for addr, new_name in rename_pairs
        if addr not in swept_addrs
    ]
    return {
        "files_changed": len(per_file),
        "replacements": total_replacements,
        "per_file": per_file,
        "unswept_renames": unswept,
    }


if __name__ == "__main__":
    sys.exit(main())
