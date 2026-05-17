#!/usr/bin/env python3
"""Build .orchestrator/extab_groups.json from dtk auto_*_text*.s asm files.

Background:
  dtk packs .text functions into "reversed extab groups" — each group is one
  auto_*_text_*.s asm file produced by `ninja build/GNLJ82/main.dol`. Inside
  one group, multiple .text functions share contiguous .extab + .extabindex
  data that dtk treats as indivisible. Trying to split such a group into
  multiple TUs in splits.txt produces:

      Conflicting splits within reversed extab group

  (Observed in iter0 batch_text_80121c34 / Stub_NoOp_80121c34 and iter1
  batch_text_8002f8cc / isJapanese; both refused single-function dispatch.)

Therefore: a function whose enclosing auto_*_text_*.s contains >1 .fn
declarations CANNOT be matched as a singleton batch — it must be bundled
with every other function in the same group.

This script: parses every build/GNLJ82/asm/auto_*_text*.s file, extracts the
.fn declarations and their addresses (via cross-ref with symbols.txt), and
writes a mapping that the orchestrator's batch planner (cycle CASE 5) uses
to bundle correctly.

Prerequisite:
  `python configure.py && ninja build/GNLJ82/main.dol` must have been run
  at least once so that build/GNLJ82/asm/ is populated.

Output: .orchestrator/extab_groups.json
  {
    "version": 1,
    "generated_at": "ISO-8601",
    "groups": {
      "auto_fn_8002F640_text": {
        "asm_path": "build/GNLJ82/asm/auto_fn_8002F640_text.s",
        "function_addresses": ["0x8002f640", "0x8002f7e0", "0x8002f8cc", ...]
      },
      ...
    },
    "fn_to_group": {
      "0x8002f640": "auto_fn_8002F640_text",
      "0x8002f8cc": "auto_fn_8002F640_text",
      ...
    },
    "singletons": ["auto_fn_8002BCA0_text", ...]  // bundle not required
  }

Singleton groups (1 .fn) are recorded for transparency but do not impose
a bundling constraint — a singleton may still be dispatched alone.
"""
from __future__ import annotations

import datetime as dt
import json
import os
import re
import sys
import tempfile
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent
ASM_GLOB = "build/GNLJ82/asm/auto_*_text*.s"
SYMBOLS_PATH = ROOT / "config" / "GNLJ82" / "symbols.txt"
OUT_PATH = ROOT / ".orchestrator" / "extab_groups.json"

SYM_LINE = re.compile(
    r"^(?P<name>\S+)\s*=\s*(?P<section>[.\w]+):(?P<addr>0x[0-9a-fA-F]+);"
)
FN_DECL = re.compile(r"^\.fn\s+(?P<name>\S+)\s*,", re.MULTILINE)


def atomic_write_json(path: Path, data: dict) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    fd, tmp = tempfile.mkstemp(prefix=".", suffix=".tmp", dir=path.parent)
    try:
        with os.fdopen(fd, "w", encoding="utf-8") as f:
            json.dump(data, f, indent=2, ensure_ascii=False)
        os.replace(tmp, path)
    except Exception:
        try:
            os.unlink(tmp)
        except OSError:
            pass
        raise


def load_addr_for_name() -> dict[str, int]:
    """Map function-name -> address (decimal int) from symbols.txt."""
    out: dict[str, int] = {}
    for line in SYMBOLS_PATH.read_text(encoding="utf-8").splitlines():
        m = SYM_LINE.match(line)
        if not m:
            continue
        out[m.group("name")] = int(m.group("addr"), 16)
    return out


def parse_unit(asm_path: Path, addr_for: dict[str, int]) -> list[tuple[int, str]]:
    """Return list of (addr, name) for .fn declarations in unit, sorted by addr."""
    content = asm_path.read_text(encoding="utf-8")
    fns: list[tuple[int, str]] = []
    missing: list[str] = []
    for m in FN_DECL.finditer(content):
        name = m.group("name")
        if name not in addr_for:
            missing.append(name)
            continue
        fns.append((addr_for[name], name))
    if missing:
        print(
            f"  WARN: {asm_path.name}: {len(missing)} .fn names not in symbols.txt: "
            f"{missing[:3]}{'...' if len(missing) > 3 else ''}",
            file=sys.stderr,
        )
    fns.sort()
    return fns


def main() -> int:
    asm_paths = sorted((ROOT).glob(ASM_GLOB))
    if not asm_paths:
        sys.exit(
            f"no asm files under {ASM_GLOB}. "
            "Run `python configure.py && ninja build/GNLJ82/main.dol` first."
        )

    addr_for = load_addr_for_name()
    print(f"loaded {len(addr_for)} symbol addresses")
    print(f"walking {len(asm_paths)} auto_*_text*.s files...")

    groups: dict[str, dict] = {}
    singletons: list[str] = []
    fn_to_group: dict[str, str] = {}
    multi_fn_groups = 0
    fns_in_groups = 0

    for asm_path in asm_paths:
        unit_name = asm_path.stem
        rel_asm = str(asm_path.relative_to(ROOT)).replace("\\", "/")
        fns = parse_unit(asm_path, addr_for)
        if not fns:
            continue
        if len(fns) == 1:
            singletons.append(unit_name)
            continue
        multi_fn_groups += 1
        fns_in_groups += len(fns)
        addrs = [f"0x{a:08x}" for a, _ in fns]
        groups[unit_name] = {
            "asm_path": rel_asm,
            "function_addresses": addrs,
            "function_names": [name for _, name in fns],
        }
        for addr_str in addrs:
            fn_to_group[addr_str] = unit_name

    now = dt.datetime.now(dt.timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")
    out = {
        "version": 1,
        "generated_at": now,
        "groups": groups,
        "fn_to_group": fn_to_group,
        "singletons": singletons,
    }
    atomic_write_json(OUT_PATH, out)

    print(f"\nwrote: {OUT_PATH.relative_to(ROOT)}")
    print(f"singleton units (no bundling needed): {len(singletons)}")
    print(f"multi-function groups (bundling required): {multi_fn_groups}")
    print(f"  total functions in such groups: {fns_in_groups}")
    print(f"  largest group size:")
    if groups:
        largest = max(groups.values(), key=lambda g: len(g["function_addresses"]))
        print(f"    {len(largest['function_addresses'])} fns in "
              f"{Path(largest['asm_path']).stem}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
