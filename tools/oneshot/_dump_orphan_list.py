"""Write orphan addresses as a TSV so the Ghidra script can consume them."""
from __future__ import annotations
import json, re, sys
from pathlib import Path

sys.path.insert(0, "tools")
from import_symbols_from_mkgp2docs import extract_candidates  # type: ignore

GHIDRA_DUMP = Path("tools/ghidra_symbol_dump.json")
SYM_PATH = Path("config/GNLJ82/symbols.txt")
DOCS_DIR = Path("../../dolphin-emu/dolphin/mkgp2docs").resolve()
OUT = Path("tools/_orphan_addrs.tsv")

SYM_LINE = re.compile(
    r"^(?P<name>\S+)\s*=\s*(?P<section>[.\w]+):(?P<addr>0x[0-9a-fA-F]+);(?P<rest>.*)$"
)
sym_addrs: set[int] = set()
for line in SYM_PATH.read_text(encoding="utf-8").splitlines():
    m = SYM_LINE.match(line)
    if m:
        sym_addrs.add(int(m.group("addr"), 16))

ghidra: dict[int, str] = {}
dump = json.loads(GHIDRA_DUMP.read_text(encoding="utf-8"))
for addr_str, info in dump.get("functions", {}).items():
    ghidra[int(addr_str, 16)] = info.get("name", "")
for addr_str, info in dump.get("globals", {}).items():
    ghidra.setdefault(int(addr_str, 16), info.get("name", ""))

mkdocs: dict[int, str] = {}
name_first: dict[str, int] = {}
addr_first: dict[int, str] = {}
for md in sorted(DOCS_DIR.glob("*.md")):
    for nm, addr, _src in extract_candidates(md):
        if name_first.get(nm) not in (None, addr):
            continue
        if addr_first.get(addr) not in (None, nm):
            continue
        name_first.setdefault(nm, addr)
        addr_first.setdefault(addr, nm)
        mkdocs[addr] = nm

union = sorted(set(ghidra) | set(mkdocs))
orphans = [a for a in union if a not in sym_addrs]

lines = ["addr\tghidra_name\tmkdocs_name"]
for a in orphans:
    lines.append(f"0x{a:08x}\t{ghidra.get(a, '')}\t{mkdocs.get(a, '')}")
OUT.write_text("\n".join(lines) + "\n", encoding="utf-8")
print(f"wrote {len(orphans)} orphan addrs -> {OUT}")
