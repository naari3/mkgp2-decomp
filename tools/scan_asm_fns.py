#!/usr/bin/env python3
"""Scan committed sources for asm_fn escapes and NonMatching units.

"Matched" in dtk report.json counts every function inside an
`Object(Matching, ...)` TU — including functions written as
`asm void fn() { nofralloc ... }` (byte-identical but zero decomp value,
see docs/per_fn_matching_strategy.md). This module recovers the
distinction from repo-tracked sources only, so it works both locally and
in CI:

  - asm fns:      regex scan of src/**/*.c|cpp for asm function definitions
  - NonMatching:  Object(NonMatching, ...) entries in configure.py
  - sizes/addrs:  config/GNLJ82/symbols.txt

CLI: python tools/scan_asm_fns.py [--json]
Importable: scan_repo(root) -> dict (see below).
"""
from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path
from typing import Any, Dict

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent

# `asm void Name(`, optionally prefixed by __declspec(section ...) / static.
ASM_FN_RE = re.compile(
    r"^\s*(?:__declspec\([^)]*\)\s*)?(?:static\s+)?"
    r"asm\s+[A-Za-z_][\w]*(?:\s*\*+|\s+)\s*([A-Za-z_]\w*)\s*\(",
    re.MULTILINE,
)

BLOCK_COMMENT_RE = re.compile(r"/\*.*?\*/", re.DOTALL)
LINE_COMMENT_RE = re.compile(r"//[^\n]*")

NONMATCHING_RE = re.compile(
    r"Object\(\s*NonMatching\s*,\s*[\"']([^\"']+)[\"']"
)

SYM_FN_RE = re.compile(
    r"^(?P<name>\S+) = (?P<section>[.\w]+):(?P<addr>0x[0-9a-fA-F]+); "
    r"//.*type:function(?:.*size:(?P<size>0x[0-9a-fA-F]+))?"
)


def _strip_comments(text: str) -> str:
    return LINE_COMMENT_RE.sub("", BLOCK_COMMENT_RE.sub("", text))


def _load_fn_symbols(root: Path) -> Dict[str, Dict[str, int]]:
    out: Dict[str, Dict[str, int]] = {}
    sym = root / "config" / "GNLJ82" / "symbols.txt"
    if not sym.is_file():
        return out
    for line in sym.read_text(encoding="utf-8").splitlines():
        m = SYM_FN_RE.match(line)
        if not m:
            continue
        out[m.group("name")] = {
            "addr": int(m.group("addr"), 16),
            "size": int(m.group("size"), 16) if m.group("size") else 0,
        }
    return out


def scan_repo(root: Path = ROOT) -> Dict[str, Any]:
    """{asm_fns: {name: {addr, size, tu}}, nonmatching_units: [tu...],
        asm_fn_count, asm_fn_code}"""
    symbols = _load_fn_symbols(root)
    asm_fns: Dict[str, Dict[str, Any]] = {}
    src = root / "src"
    if src.is_dir():
        for path in sorted(src.rglob("*")):
            if path.suffix not in (".c", ".cpp"):
                continue
            text = _strip_comments(path.read_text(encoding="utf-8", errors="replace"))
            tu = path.relative_to(src).as_posix()
            for m in ASM_FN_RE.finditer(text):
                name = m.group(1)
                info = symbols.get(name)
                if not info:
                    # local asm helper (e.g. GetR2) — not an address-mapped
                    # function in the binary, irrelevant to matched counts
                    continue
                asm_fns[name] = {
                    "addr": info["addr"],
                    "size": info["size"],
                    "tu": tu,
                }
    nonmatching: list[str] = []
    cfg = root / "configure.py"
    if cfg.is_file():
        nonmatching = NONMATCHING_RE.findall(cfg.read_text(encoding="utf-8"))
    return {
        "asm_fns": asm_fns,
        "nonmatching_units": nonmatching,
        "asm_fn_count": len(asm_fns),
        "asm_fn_code": sum(v["size"] for v in asm_fns.values()),
    }


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--root", type=Path, default=ROOT)
    ap.add_argument("--json", action="store_true", help="full JSON dump")
    args = ap.parse_args()
    data = scan_repo(args.root)
    if args.json:
        print(json.dumps(data, indent=2))
        return 0
    print(f"asm fns: {data['asm_fn_count']} ({data['asm_fn_code']} bytes)")
    for name, v in sorted(data["asm_fns"].items(), key=lambda kv: kv[1]["addr"]):
        print(f"  0x{v['addr']:08x} {v['size']:>5}B {name}  ({v['tu']})")
    print(f"NonMatching units: {len(data['nonmatching_units'])}")
    for tu in data["nonmatching_units"]:
        print(f"  {tu}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
