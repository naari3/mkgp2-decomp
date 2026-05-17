#!/usr/bin/env python3
"""Import named symbols from mkgp2-patch/externals.txt into config/GNLJ82/symbols.txt.

externals.txt format: `Name=0xADDR  # optional comment` per line, '#' starts comments.
symbols.txt format:   `Name = .section:0xADDR; // type:T size:S scope:Z`

For each address present in both files, the symbols.txt entry's name is rewritten
to match externals.txt. Section/type/size/scope are preserved. Unmatched entries
in symbols.txt are left as-is (e.g. `fn_<addr>` placeholders). Collisions
(same address, different names across files) are reported.

Run from the mkgp2-decomp project root.
"""
from __future__ import annotations

import re
import sys
from pathlib import Path

EXT_PATH = Path("../../naari3/mkgp2-patch/externals.txt").resolve()
if not EXT_PATH.exists():
    # Fallback: try environment-style relative
    EXT_PATH = Path("../mkgp2-patch/externals.txt").resolve()
SYM_PATH = Path("config/GNLJ82/symbols.txt")

if not EXT_PATH.exists():
    sys.exit(f"externals.txt not found, looked at: {EXT_PATH}")
if not SYM_PATH.exists():
    sys.exit(f"symbols.txt not found, looked at: {SYM_PATH}")


def parse_externals(path: Path) -> dict[int, str]:
    result: dict[int, str] = {}
    collisions: list[tuple[int, str, str]] = []
    for raw in path.read_text(encoding="utf-8").splitlines():
        line = raw.split("#", 1)[0].strip()
        if not line or "=" not in line:
            continue
        name, addr = line.split("=", 1)
        name = name.strip()
        addr = addr.strip()
        if not addr.lower().startswith("0x"):
            continue
        try:
            addr_int = int(addr, 16)
        except ValueError:
            continue
        if addr_int in result and result[addr_int] != name:
            collisions.append((addr_int, result[addr_int], name))
        result[addr_int] = name
    for addr_int, a, b in collisions:
        print(f"WARN external collision @ 0x{addr_int:08x}: {a!r} vs {b!r} (keeping {b!r})")
    return result


SYM_LINE = re.compile(
    r"^(?P<name>\S+)\s*=\s*(?P<section>[.\w]+):(?P<addr>0x[0-9a-fA-F]+);(?P<rest>.*)$"
)


def main() -> int:
    externals = parse_externals(EXT_PATH)
    print(f"externals loaded: {len(externals)} addresses from {EXT_PATH}")

    lines = SYM_PATH.read_text(encoding="utf-8").splitlines()
    renamed = 0
    already_named = 0
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
        new_name = externals.get(addr_int)
        if new_name is None:
            out.append(line)
            continue
        if cur_name == new_name:
            already_named += 1
            out.append(line)
            continue
        # Replace the leading name only; keep formatting (single space around =).
        out.append(f"{new_name} = {section}:{addr_str};{rest}")
        renamed += 1

    SYM_PATH.write_text("\n".join(out) + "\n", encoding="utf-8")
    print(f"renamed: {renamed}")
    print(f"already-matching: {already_named}")
    print(f"externals not present in symbols.txt: {len(externals) - renamed - already_named}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
