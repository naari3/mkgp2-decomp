#!/usr/bin/env python3
"""Find functions whose target extab entry carries EH actions.

An extab entry longer than 8 bytes has action records (DELETEPOINTER /
DESTROYBASE / DESTROYLOCAL / ...): the function contains real C++ EH
constructs (ctor with base/member cleanup, new-expression guards, locals
with dtors). These are the C++-retrofit family proven by
docs/notes/cpp-ctor-retrofit-mangled-bridge.md — plain C + manual extab
tends to hit register-identity parks there, while a genuine class/ctor
reproduces both codegen and extab.

Reads:
  - build/GNLJ82/main.dol   (byte-identical rebuild; original extab content)
  - config/GNLJ82/symbols.txt  (@etb_/@eti_ local symbols = entry addresses)
  - SoT status via plan_units.load_functions (matched/asm_fn/pending/...)

Usage:
  python tools/scan_extab_actions.py              # summary + candidates
  python tools/scan_extab_actions.py --all        # every fn with actions
  python tools/scan_extab_actions.py --units      # pending clusters ranked
"""
from __future__ import annotations

import argparse
import re
import struct
import sys
from collections import defaultdict
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent
sys.path.insert(0, str(HERE))

from plan_units import load_functions, prefix_of  # noqa: E402
from scan_asm_fns import scan_repo  # noqa: E402

DOL = ROOT / "build" / "GNLJ82" / "main.dol"
SYMS = ROOT / "config" / "GNLJ82" / "symbols.txt"


class Dol:
    def __init__(self, path: Path):
        self.data = path.read_bytes()
        offs = struct.unpack(">18I", self.data[0x00:0x48])
        addrs = struct.unpack(">18I", self.data[0x48:0x90])
        sizes = struct.unpack(">18I", self.data[0x90:0xD8])
        self.sections = [
            (a, a + s, o) for o, a, s in zip(offs, addrs, sizes) if s > 0
        ]

    def read(self, addr: int, size: int) -> bytes:
        for lo, hi, off in self.sections:
            if lo <= addr and addr + size <= hi:
                fo = off + (addr - lo)
                return self.data[fo:fo + size]
        raise ValueError(f"address 0x{addr:08x} not in any dol section")


def collect_local_addrs(prefix: str) -> list[int]:
    pat = re.compile(rf"^@{prefix}_([0-9a-fA-F]{{8}}) = ")
    out = []
    for line in SYMS.read_text(encoding="utf-8").splitlines():
        m = pat.match(line)
        if m:
            out.append(int(m.group(1), 16))
    return sorted(set(out))


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--all", action="store_true",
                    help="list every function with extab actions")
    ap.add_argument("--units", action="store_true",
                    help="rank pending clusters by action-fn count")
    args = ap.parse_args()

    if not DOL.is_file():
        sys.exit("build/GNLJ82/main.dol not found — run ninja first")
    dol = Dol(DOL)

    etb = collect_local_addrs("etb")
    eti = collect_local_addrs("eti")
    if not etb or not eti:
        sys.exit("no @etb_/@eti_ symbols in symbols.txt")

    # extab entry size = next entry start - this start (last: assume 8+action
    # up to 0x200 cap; read terminator instead)
    etb_size: dict[int, int] = {}
    for i, a in enumerate(etb):
        end = etb[i + 1] if i + 1 < len(etb) else a + 8
        etb_size[a] = end - a

    fns = load_functions()
    asm_names = set(scan_repo()["asm_fns"])

    rows = []
    for a in eti:
        fn_addr, fn_size, etb_addr = struct.unpack(">3I", dol.read(a, 12))
        esize = etb_size.get(etb_addr)
        if esize is None:
            continue
        if esize <= 8:
            continue  # no action records
        info = fns.get(fn_addr)
        name = info["name"] if info else f"(0x{fn_addr:08x})"
        status = info["status"] if info else "?"
        if info and name in asm_names:
            status = "asm_fn"
        rows.append({
            "fn": fn_addr, "name": name, "size": fn_size,
            "status": status, "extab_size": esize,
        })

    by_status: dict[str, list[dict]] = defaultdict(list)
    for r in rows:
        by_status[r["status"]].append(r)

    print(f"extab entries with EH actions: {len(rows)} fns")
    for st in ("matched", "asm_fn", "nonmatching", "pending", "excluded", "?"):
        if st in by_status:
            print(f"  {st:<12} {len(by_status[st])}")

    print("\n== retrofit candidates: asm_fn / nonmatching with actions ==")
    for r in sorted(by_status.get("asm_fn", []) + by_status.get("nonmatching", []),
                    key=lambda r: r["fn"]):
        print(f"  0x{r['fn']:08x} {r['size']:>5}B extab={r['extab_size']:>3}B "
              f"{r['status']:<12} {r['name']}")

    if args.units:
        clusters: dict[str, list[dict]] = defaultdict(list)
        for r in by_status.get("pending", []):
            if not r["name"].startswith(("fn_", "lbl_", "dtor_")):
                clusters[prefix_of(r["name"])].append(r)
        print("\n== pending clusters with action fns (class-first 推奨) ==")
        ranked = sorted(clusters.items(), key=lambda kv: -len(kv[1]))
        for pre, rs in ranked[:30]:
            total = sum(r["size"] for r in rs)
            print(f"  {pre:<24} action_fns={len(rs):<3} ({total}B)")

    if args.all:
        print("\n== all fns with extab actions ==")
        for r in sorted(rows, key=lambda r: r["fn"]):
            print(f"  0x{r['fn']:08x} {r['size']:>5}B extab={r['extab_size']:>3}B "
                  f"{r['status']:<12} {r['name']}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
