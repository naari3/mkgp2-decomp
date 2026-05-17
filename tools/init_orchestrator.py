#!/usr/bin/env python3
"""Initialize .orchestrator/state.json from project SoT.

Reads (all from project root):
  - config/GNLJ82/symbols.txt        all symbols (functions + objects + labels)
  - config/GNLJ82/splits.txt         TU address ranges
  - tools/ghidra_symbol_dump.json    Ghidra named functions (informational)
  - configure.py                      Object(Matching|NonMatching, ...) declarations
  - build/GNLJ82/report.json (opt)   per-function fuzzy_match_percent

Writes:
  - .orchestrator/state.json
  - .orchestrator/log.jsonl  (appends a session_start event)

Refuses to overwrite an existing state.json without --force.

Schema reference: docs/orchestrator_state_schema.md
"""
from __future__ import annotations

import argparse
import datetime as dt
import json
import os
import re
import sys
import tempfile
from pathlib import Path
from typing import Optional


HERE = Path(__file__).resolve().parent
ROOT = HERE.parent
ORCH_DIR = ROOT / ".orchestrator"
SYM_PATH = ROOT / "config" / "GNLJ82" / "symbols.txt"
SPLITS_PATH = ROOT / "config" / "GNLJ82" / "splits.txt"
DUMP_PATH = ROOT / "tools" / "ghidra_symbol_dump.json"
CONFIGURE_PATH = ROOT / "configure.py"
REPORT_PATH = ROOT / "build" / "GNLJ82" / "report.json"


def atomic_write_json(path: Path, data: dict) -> None:
    """Write JSON via tempfile + os.replace. Atomic on Windows and POSIX."""
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


SYM_LINE = re.compile(
    r"^(?P<name>\S+)\s*=\s*(?P<section>[.\w]+):(?P<addr>0x[0-9a-fA-F]+);\s*(?P<rest>.*)$"
)


def load_symbols() -> dict[int, dict]:
    """Parse symbols.txt -> {addr: {name, section, size, scope, kind}}."""
    result: dict[int, dict] = {}
    for line in SYM_PATH.read_text(encoding="utf-8").splitlines():
        m = SYM_LINE.match(line)
        if not m:
            continue
        rest = m.group("rest")
        # Strip leading "// " if present so we parse attribute tokens cleanly.
        if rest.startswith("//"):
            rest = rest[2:].lstrip()
        kind: Optional[str] = None
        size: Optional[int] = None
        scope: str = "global"
        for tok in rest.split():
            if tok.startswith("type:"):
                kind = tok[5:]
            elif tok.startswith("size:"):
                v = tok[5:]
                try:
                    size = int(v, 16) if v.lower().startswith("0x") else int(v)
                except ValueError:
                    size = None
            elif tok.startswith("scope:"):
                scope = tok[6:]
        addr = int(m.group("addr"), 16)
        result[addr] = {
            "name": m.group("name"),
            "section": m.group("section"),
            "size": size,
            "scope": scope,
            "kind": kind,
        }
    return result


def load_splits() -> dict[str, list[tuple[str, int, int]]]:
    """Parse splits.txt -> {tu_path: [(section, start, end), ...]}."""
    entries: dict[str, list[tuple[str, int, int]]] = {}
    current: Optional[str] = None
    in_sections = False
    for raw in SPLITS_PATH.read_text(encoding="utf-8").splitlines():
        line = raw.rstrip()
        if not line:
            continue
        if line == "Sections:":
            in_sections = True
            current = None
            continue
        if not line[0].isspace():
            # Unindented line: TU header "<path>:" possibly with attrs
            if line.endswith(":") or ":" in line.split(None, 1)[0]:
                in_sections = False
                # Take everything up to the first ':' as the path
                header = line.split(":", 1)[0].strip()
                current = header
                entries.setdefault(current, [])
                continue
            continue
        if in_sections:
            continue
        if current is None:
            continue
        m = re.match(r"\s+(\S+)\s+(.+)$", line)
        if not m:
            continue
        section = m.group(1)
        attrs = m.group(2)
        sm = re.search(r"start:(0x[0-9a-fA-F]+)", attrs)
        em = re.search(r"end:(0x[0-9a-fA-F]+)", attrs)
        if sm and em:
            entries[current].append(
                (section, int(sm.group(1), 16), int(em.group(1), 16))
            )
    return entries


def find_tu(addr: int, ranges: list[tuple[int, int, str]]) -> Optional[str]:
    """Linear search over (start, end, tu). Fine for ~thousands of entries."""
    for start, end, tu in ranges:
        if start <= addr < end:
            return tu
    return None


def load_ghidra_named_addrs() -> set[int]:
    """Return set of function addrs that appear in Ghidra's named dump.

    Informational only: orchestrator eligibility is decided by the current
    symbols.txt name (see is_placeholder_name), not by Ghidra dump membership,
    because names can also come from mkgp2docs / externals.txt imports.
    """
    if not DUMP_PATH.exists():
        return set()
    data = json.loads(DUMP_PATH.read_text(encoding="utf-8"))
    fn = data.get("functions", {})
    return {int(k, 16) for k in fn.keys()}


PLACEHOLDER_NAME_RE = re.compile(
    r"""^(
        fn_[0-9a-fA-F]+        |
        lbl_[0-9a-fA-F]+       |
        data_[0-9a-fA-F]+      |
        FUN_[0-9a-fA-F]+       |
        SUB_[0-9a-fA-F]+       |
        LAB_[0-9a-fA-F]+       |
        DAT_[0-9a-fA-F]+       |
        thunk_FUN_[0-9a-fA-F]+ |
        thunk_SUB_[0-9a-fA-F]+
    )$""",
    re.VERBOSE,
)


def is_placeholder_name(name: str) -> bool:
    """True if the current symbols.txt name is a placeholder (no meaning yet)."""
    return bool(PLACEHOLDER_NAME_RE.match(name))


OBJECT_RE = re.compile(
    r"""Object\(\s*
        (?P<flag>Matching|NonMatching|Equivalent)\s*,\s*
        ["'](?P<path>[^"']+)["']
        \s*[\),]""",
    re.VERBOSE,
)


def load_configure_objects() -> dict[str, str]:
    """Parse configure.py -> {tu_path: flag}.

    flag is one of "Matching" / "NonMatching" / "Equivalent".
    tu_path is the literal string passed to Object(), relative to src/.
    Object(MatchingFor(...), ...) is intentionally not matched; those entries
    default to no flag (status=pending).
    """
    src = CONFIGURE_PATH.read_text(encoding="utf-8")
    result: dict[str, str] = {}
    for m in OBJECT_RE.finditer(src):
        result[m.group("path")] = m.group("flag")
    return result


def load_report_fuzzy() -> dict[str, float]:
    """Best-effort parse of report.json -> {function_name: fuzzy_match_percent}.

    Empty if report missing or structure unrecognized.
    """
    if not REPORT_PATH.exists():
        return {}
    try:
        data = json.loads(REPORT_PATH.read_text(encoding="utf-8"))
    except Exception:
        return {}
    out: dict[str, float] = {}
    # Try a few plausible shapes.
    units = (
        data.get("units")
        or data.get("measures", {}).get("units")
        or []
    )
    for unit in units:
        for fn in unit.get("functions") or []:
            name = fn.get("name")
            pct = fn.get("fuzzy_match_percent")
            if name is None or pct is None:
                continue
            try:
                out[name] = float(pct)
            except (TypeError, ValueError):
                continue
    return out


def derive_status(
    *,
    has_named_symbol: bool,
    tu_hint: Optional[str],
    matching_flag: Optional[str],
) -> str:
    """Map (has_named_symbol, tu_hint, matching_flag) -> status.

    See docs/orchestrator_state_schema.md for the state machine.
    """
    if tu_hint and matching_flag == "NonMatching":
        return "nonmatching"
    if tu_hint and matching_flag == "Matching":
        return "matched"
    if not has_named_symbol:
        return "excluded"
    return "pending"


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--force", action="store_true",
                        help="overwrite existing state.json")
    args = parser.parse_args()

    state_path = ORCH_DIR / "state.json"
    log_path = ORCH_DIR / "log.jsonl"
    if state_path.exists() and not args.force:
        sys.exit(
            f"state.json already exists at {state_path}. "
            f"Use --force to overwrite, or run tools/orch_recover.py to resume."
        )

    symbols = load_symbols()
    splits = load_splits()
    ghidra_addrs = load_ghidra_named_addrs()
    configure_objs = load_configure_objects()
    fuzzy = load_report_fuzzy()

    ranges: list[tuple[int, int, str]] = []
    for tu, sections in splits.items():
        for _sec, start, end in sections:
            ranges.append((start, end, tu))
    ranges.sort()

    functions_out: dict[str, dict] = {}
    fn_count = 0
    status_counts: dict[str, int] = {}

    for addr, sym in sorted(symbols.items()):
        if sym.get("kind") != "function":
            continue
        fn_count += 1
        ghidra_named = addr in ghidra_addrs
        has_named_symbol = not is_placeholder_name(sym["name"])
        tu_hint = find_tu(addr, ranges)
        matching_flag = configure_objs.get(tu_hint) if tu_hint else None
        fpct = fuzzy.get(sym["name"])
        status = derive_status(
            has_named_symbol=has_named_symbol,
            tu_hint=tu_hint,
            matching_flag=matching_flag,
        )
        status_counts[status] = status_counts.get(status, 0) + 1

        addr_key = f"0x{addr:08x}"
        functions_out[addr_key] = {
            "name": sym["name"],
            "section": sym["section"],
            "size": sym.get("size"),
            "has_named_symbol": has_named_symbol,
            "ghidra_named": ghidra_named,
            "tu_hint": tu_hint,
            "status": status,
            "batch_id": None,
            "dependencies": [],
            "callers": [],
            "fuzzy_match_percent": fpct,
            "last_attempt_at": None,
            "notes": "",
        }

    now = dt.datetime.now(dt.timezone.utc)
    session_id = "sess_" + now.strftime("%Y-%m-%dT%H-%M-%S")
    now_iso = now.strftime("%Y-%m-%dT%H:%M:%SZ")

    ghidra_mtime_iso: Optional[str] = None
    if DUMP_PATH.exists():
        ts = dt.datetime.fromtimestamp(DUMP_PATH.stat().st_mtime, tz=dt.timezone.utc)
        ghidra_mtime_iso = ts.strftime("%Y-%m-%dT%H:%M:%SZ")

    state = {
        "version": 1,
        "session_id": session_id,
        "synced_from_sot_at": now_iso,
        "ghidra_dump_path": str(DUMP_PATH.relative_to(ROOT)).replace("\\", "/"),
        "ghidra_dump_mtime": ghidra_mtime_iso,
        "functions": functions_out,
        "batches": {},
        "active_subs": {},
    }

    atomic_write_json(state_path, state)

    log_path.parent.mkdir(parents=True, exist_ok=True)
    with log_path.open("a", encoding="utf-8") as f:
        f.write(json.dumps({
            "ts": now_iso,
            "event": "session_start",
            "session_id": session_id,
            "source": "init_orchestrator.py",
            "stats": {
                "functions_total": fn_count,
                **{f"status_{k}": v for k, v in status_counts.items()},
            },
        }, ensure_ascii=False) + "\n")

    print(f"session_id: {session_id}")
    print(f"wrote: {state_path.relative_to(ROOT)}")
    print(f"functions total: {fn_count}")
    for k in sorted(status_counts):
        print(f"  {k}: {status_counts[k]}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
