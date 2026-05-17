#!/usr/bin/env python3
"""Apply a parsed HANDOFF dict to project SoT files.

Editing targets (all under project root, atomic write via tempfile+rename):
  - configure.py                          (config.libs[].objects[] に Object 追加)
  - config/GNLJ82/splits.txt              (entry 追加)
  - config/GNLJ82/symbols.txt             (scope / 属性更新)

Optional inputs (HANDOFF.md sections):
  - configure_py.add_objects[]
  - splits_txt.add_entries[]
  - symbols_txt.set_scope[]
  - symbols_txt.set_attr[]   (e.g. align, force_active)
  - docs_notes[]              (append to docs/notes/<path>.md)

CLI:
  python tools/apply_handoff.py <HANDOFF.md> [--dry-run] [--no-docs]

Verifies the parsed handoff first (via parse_handoff.parse). Returns:
  exit 0 if everything applied (or would apply in dry-run)
  exit 1 on parse/validation error
  exit 2 on apply error (e.g. lib not found in configure.py)

Idempotency: applying the same handoff twice is safe — splits.txt entries
that already exist are skipped, configure.py duplicate Object lines are
skipped, symbols.txt re-application of the same scope is a no-op.

Schema reference: docs/sub_agent_role.md
"""
from __future__ import annotations

import argparse
import json
import os
import re
import sys
import tempfile
from pathlib import Path
from typing import Optional

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
from parse_handoff import parse, HandoffParseError  # noqa: E402

ROOT = HERE.parent
CONFIGURE_PATH = ROOT / "configure.py"
SPLITS_PATH = ROOT / "config" / "GNLJ82" / "splits.txt"
SYMBOLS_PATH = ROOT / "config" / "GNLJ82" / "symbols.txt"


def atomic_write_text(path: Path, content: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    fd, tmp = tempfile.mkstemp(prefix=".", suffix=".tmp", dir=path.parent)
    try:
        with os.fdopen(fd, "w", encoding="utf-8", newline="\n") as f:
            f.write(content)
        os.replace(tmp, path)
    except Exception:
        try:
            os.unlink(tmp)
        except OSError:
            pass
        raise


# ─── configure.py ─────────────────────────────────────────────────────────

OBJ_LINE_DUP_RE_TMPL = (
    r"Object\(\s*(Matching|NonMatching|Equivalent)\s*,\s*"
    r"[\"']{path}[\"']\s*[\),]"
)


def find_lib_objects_ranges(lines: list[str]) -> dict[str, tuple[int, int]]:
    """Return {lib_name: (objects_open_line_idx, objects_close_line_idx)}.

    objects_close_line_idx points at the line containing the closing `],` or `]`
    of the lib's objects[] array.
    """
    result: dict[str, tuple[int, int]] = {}
    current_lib: Optional[str] = None
    obj_open: Optional[int] = None
    bracket_depth = 0
    for i, line in enumerate(lines):
        m = re.match(r'\s*"lib"\s*:\s*"([^"]+)"', line)
        if m:
            current_lib = m.group(1)
            obj_open = None
            bracket_depth = 0
            continue
        if current_lib is None:
            continue
        if obj_open is None:
            if re.search(r'"objects"\s*:\s*\[', line):
                obj_open = i
                # The opening [ may or may not be alone on the line. Track
                # bracket depth from this line.
                bracket_depth = line.count("[") - line.count("]")
                if bracket_depth == 0:
                    # objects: [] on one line — unlikely in this codebase, but
                    # handle: close = i
                    result[current_lib] = (obj_open, i)
                    current_lib = None
                    obj_open = None
            continue
        # We are inside the objects array
        bracket_depth += line.count("[") - line.count("]")
        if bracket_depth <= 0:
            result[current_lib] = (obj_open, i)
            current_lib = None
            obj_open = None
    return result


def apply_configure_objects(
    src: str,
    add_objects: list[dict],
    *,
    skipped: list[str],
) -> str:
    if not add_objects:
        return src
    lines = src.splitlines()
    lib_ranges = find_lib_objects_ranges(lines)

    # Group additions by lib
    by_lib: dict[str, list[str]] = {}
    for ao in add_objects:
        lib = ao["lib"]
        obj_literal = ao["object"]
        if lib not in lib_ranges:
            raise RuntimeError(
                f"lib {lib!r} not found in configure.py (known: "
                f"{sorted(lib_ranges)})"
            )
        # Idempotency: skip if a Matching/NonMatching/Equivalent line
        # already exists with the same path
        path_match = re.search(r'["\']([^"\']+)["\']', obj_literal)
        if path_match:
            path = path_match.group(1)
            dup_re = re.compile(OBJ_LINE_DUP_RE_TMPL.format(path=re.escape(path)))
            open_i, close_i = lib_ranges[lib]
            if any(dup_re.search(l) for l in lines[open_i:close_i + 1]):
                skipped.append(f"configure_py: {obj_literal} (duplicate)")
                continue
        by_lib.setdefault(lib, []).append(obj_literal)

    if not by_lib:
        return src

    # Insert from bottom up so earlier libs' line indices stay valid
    for lib in sorted(by_lib, key=lambda l: lib_ranges[l][1], reverse=True):
        open_i, close_i = lib_ranges[lib]
        close_line = lines[close_i]
        # Detect outer indent of the closing `]` for new entries (one level deeper)
        outer_match = re.match(r"(\s*)\]", close_line)
        outer_indent = outer_match.group(1) if outer_match else "        "
        inner_indent = outer_indent + "    "
        # If the existing last object line uses a different indent, mirror it
        for j in range(close_i - 1, open_i, -1):
            existing = lines[j]
            existing_m = re.match(r"(\s+)\S", existing)
            if existing_m:
                inner_indent = existing_m.group(1)
                break
        new_lines = [f"{inner_indent}{obj}," for obj in by_lib[lib]]
        lines[close_i:close_i] = new_lines

    return "\n".join(lines) + ("\n" if src.endswith("\n") else "")


# ─── splits.txt ───────────────────────────────────────────────────────────

PATH_HEADER_RE = re.compile(r"^([^\s:][^:]*):\s*$", re.MULTILINE)


def existing_split_paths(src: str) -> set[str]:
    return {m.group(1) for m in PATH_HEADER_RE.finditer(src)}


def apply_splits_entries(
    src: str,
    add_entries: list[dict],
    *,
    skipped: list[str],
) -> str:
    if not add_entries:
        return src
    existing_paths = existing_split_paths(src)
    new_blocks: list[str] = []
    for entry in add_entries:
        path = entry["path"]
        if path in existing_paths:
            skipped.append(f"splits_txt: {path} (path already present)")
            continue
        lines = [f"{path}:"]
        for sec in entry["sections"]:
            lines.append(
                f"\t{sec['section']}\tstart:{sec['start']} end:{sec['end']}"
            )
        new_blocks.append("\n".join(lines))
    if not new_blocks:
        return src
    return src.rstrip() + "\n\n" + "\n\n".join(new_blocks) + "\n"


# ─── symbols.txt ──────────────────────────────────────────────────────────

SYM_LINE_RE = re.compile(
    r"^(?P<name>\S+)(?P<gap>\s*=\s*)"
    r"(?P<section>[.\w]+):(?P<addr>0x[0-9a-fA-F]+);"
    r"(?P<rest>.*)$"
)


def update_symbol_attrs(
    line: str,
    *,
    set_scope: Optional[str] = None,
    set_attr: Optional[dict[str, str]] = None,
) -> Optional[str]:
    """Return updated line, or None if no change."""
    m = SYM_LINE_RE.match(line)
    if not m:
        return None
    rest = m.group("rest")
    # Preserve "// " comment prefix if present
    if rest.lstrip().startswith("//"):
        idx = rest.find("//")
        prefix = rest[: idx + 2]  # everything up to and including //
        tail = rest[idx + 2 :]
    else:
        prefix = " //"
        tail = " " + rest.strip() if rest.strip() else ""

    tokens = tail.split()

    def set_token(prefix_: str, value: str) -> None:
        for ti, t in enumerate(tokens):
            if t.startswith(prefix_):
                tokens[ti] = f"{prefix_}{value}"
                return
        tokens.append(f"{prefix_}{value}")

    changed = False
    if set_scope is not None:
        existing_scope: Optional[str] = None
        for t in tokens:
            if t.startswith("scope:"):
                existing_scope = t[6:]
                break
        if existing_scope != set_scope:
            set_token("scope:", set_scope)
            changed = True
    if set_attr:
        for k, v in set_attr.items():
            key_prefix = f"{k}:"
            existing_val = None
            for t in tokens:
                if t.startswith(key_prefix):
                    existing_val = t[len(key_prefix):]
                    break
            if existing_val != str(v):
                set_token(key_prefix, str(v))
                changed = True

    if not changed:
        return None
    new_tail = " ".join(tokens)
    return (
        f"{m.group('name')}{m.group('gap')}"
        f"{m.group('section')}:{m.group('addr')};"
        f"{prefix} {new_tail}".rstrip()
    )


def apply_symbols_changes(
    src: str,
    set_scope: list[dict],
    set_attr: list[dict],
    *,
    skipped: list[str],
) -> str:
    if not set_scope and not set_attr:
        return src
    by_name_scope = {item["name"]: item["scope"] for item in (set_scope or [])}
    by_name_attr: dict[str, dict[str, str]] = {}
    for item in set_attr or []:
        name = item["name"]
        attrs = {k: v for k, v in item.items() if k != "name"}
        by_name_attr.setdefault(name, {}).update(attrs)

    lines = src.splitlines()
    target_names = set(by_name_scope) | set(by_name_attr)
    found: set[str] = set()
    for i, line in enumerate(lines):
        m = SYM_LINE_RE.match(line)
        if not m:
            continue
        name = m.group("name")
        if name not in target_names:
            continue
        updated = update_symbol_attrs(
            line,
            set_scope=by_name_scope.get(name),
            set_attr=by_name_attr.get(name),
        )
        if updated is not None:
            lines[i] = updated
        found.add(name)

    missing = target_names - found
    for name in sorted(missing):
        skipped.append(f"symbols_txt: {name} (not found in symbols.txt)")
    return "\n".join(lines) + ("\n" if src.endswith("\n") else "")


# ─── docs/notes appender ──────────────────────────────────────────────────


def apply_docs_notes(notes: list[dict], *, skipped: list[str]) -> list[Path]:
    written: list[Path] = []
    for n in notes or []:
        rel = n.get("path")
        content = n.get("content")
        if not rel or not content:
            skipped.append(f"docs_notes: missing path or content ({n!r})")
            continue
        target = (ROOT / rel).resolve()
        if not str(target).startswith(str(ROOT)):
            skipped.append(f"docs_notes: path escapes project root ({rel})")
            continue
        target.parent.mkdir(parents=True, exist_ok=True)
        existing = target.read_text(encoding="utf-8") if target.exists() else ""
        sep = "\n\n" if existing and not existing.endswith("\n\n") else ""
        atomic_write_text(target, existing + sep + content + "\n")
        written.append(target)
    return written


# ─── main ─────────────────────────────────────────────────────────────────


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("handoff", type=Path)
    parser.add_argument("--dry-run", action="store_true")
    parser.add_argument("--no-docs", action="store_true",
                        help="skip docs_notes application")
    args = parser.parse_args()

    if not args.handoff.exists():
        print(f"handoff file not found: {args.handoff}", file=sys.stderr)
        return 2

    try:
        data = parse(args.handoff)
    except HandoffParseError as e:
        print(f"HANDOFF parse error: {e}", file=sys.stderr)
        return 1

    skipped: list[str] = []

    cp_add = (data.get("configure_py") or {}).get("add_objects") or []
    sp_add = (data.get("splits_txt") or {}).get("add_entries") or []
    sym = data.get("symbols_txt") or {}
    sym_scope = sym.get("set_scope") or []
    sym_attr = sym.get("set_attr") or []
    docs_notes = data.get("docs_notes") or []

    cur_configure = CONFIGURE_PATH.read_text(encoding="utf-8") if CONFIGURE_PATH.exists() else ""
    cur_splits = SPLITS_PATH.read_text(encoding="utf-8") if SPLITS_PATH.exists() else ""
    cur_symbols = SYMBOLS_PATH.read_text(encoding="utf-8") if SYMBOLS_PATH.exists() else ""

    new_configure = apply_configure_objects(cur_configure, cp_add, skipped=skipped)
    new_splits = apply_splits_entries(cur_splits, sp_add, skipped=skipped)
    new_symbols = apply_symbols_changes(
        cur_symbols, sym_scope, sym_attr, skipped=skipped
    )

    changes: list[str] = []
    if new_configure != cur_configure:
        changes.append(f"configure.py: +{new_configure.count(chr(10)) - cur_configure.count(chr(10))} lines")
    if new_splits != cur_splits:
        changes.append(f"splits.txt: +{new_splits.count(chr(10)) - cur_splits.count(chr(10))} lines")
    if new_symbols != cur_symbols:
        changes.append(f"symbols.txt: modified in place")

    if args.dry_run:
        print(f"DRY RUN apply summary for batch {data.get('batch_id')!r}:")
        for c in changes:
            print(f"  would apply: {c}")
        if docs_notes and not args.no_docs:
            print(f"  would append {len(docs_notes)} docs_notes entry(ies)")
        for s in skipped:
            print(f"  SKIP: {s}")
        return 0

    if new_configure != cur_configure:
        atomic_write_text(CONFIGURE_PATH, new_configure)
    if new_splits != cur_splits:
        atomic_write_text(SPLITS_PATH, new_splits)
    if new_symbols != cur_symbols:
        atomic_write_text(SYMBOLS_PATH, new_symbols)

    written_notes: list[Path] = []
    if docs_notes and not args.no_docs:
        written_notes = apply_docs_notes(docs_notes, skipped=skipped)

    print(f"applied handoff for batch {data.get('batch_id')!r}")
    for c in changes:
        print(f"  {c}")
    for n in written_notes:
        print(f"  wrote/appended: {n.relative_to(ROOT)}")
    for s in skipped:
        print(f"  SKIP: {s}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
