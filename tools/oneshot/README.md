# One-shot symbol seeding tools

Used once in 2026-05..07 to seed `config/GNLJ82/symbols.txt` from Ghidra and
`mkgp2-patch` (externals.txt, mkgp2docs). Kept for re-seeding; not part of the
build or the matching workflow. Run from the repo root.

- `ghidra_dump_raw.java` (in Ghidra) -> `_ghidra_dump_functions.json`,
  `_ghidra_dump_globals.txt`; `_build_ghidra_dump.py` -> `tools/ghidra_symbol_dump.json`
- `import_symbols_from_ghidra.py`, `import_symbols_from_externals.py`,
  `import_symbols_from_mkgp2docs.py`: rename placeholders in symbols.txt
- `_dump_orphan_list.py`, `_query_orphans_template.java`, `add_orphan_symbols.py`:
  add symbols for addresses dtk did not know
