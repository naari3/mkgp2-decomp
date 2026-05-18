#!/usr/bin/env python3
"""One-shot scaffold for a dtk reversed-extab group bundle (WIP).

Wires the steps that used to be hand-done before sub-agent dispatch:
  1. extract_fn_asm.py  -> src/<lib>/<file>.c (asm_fn body + extab emit +
     extern decls)
  2. extab presence sniff (auto_*_text*.s has `.section extab`?) selects
     the build lib + extab_padding kwarg
  3. configure.py: insert `Object(Matching, "<path>", extab_padding=...)`
     into the chosen lib's objects list
  4. splits.txt: insert `<path>:` block with extab/extabindex/.text ranges
     in address order
  5. extab_user_renames.json: merge per-TU rename map (if extab present)
  6. configure.py + ninja build/GNLJ82/ok -> SHA-1 OK verification
  7. state.json: flip the group's pending fns to status `asm_fn`

If step 6 fails the script exits non-zero leaving the file in place; the
caller decides whether to revert. No automatic revert (failure modes vary
and need human eyes).

## CURRENT LIMITATIONS (WIP, do not use blindly)

This tool's reach is narrow. Two failure modes confirmed empirically against
mkgp2-decomp (2026-05-18):

1. **`li rD, <sym>@sda21` instructions**: mwcc inline asm rejects both
   `li rD, sym@sda21` and the obvious workaround `addi rD, 0, sym@sda21`
   ("illegal object reference in constant expression"). Groups whose
   functions use this idiom (mwcc-generated short pointer loads from sdata)
   will fail at compile time. extract_fn_asm.py applies the rewrite anyway
   for future-proofing; need a different form (perhaps `addi rD, r13, ...`
   with explicit offset arithmetic) to actually work.

2. **Cross-lib helper groups**: this tool assumes `game_extab` (extab
   present) or `game` (text only) for lib placement. Groups containing
   Runtime.PPCEABI.H helpers (`__save_fpr`, `__restore_fpr`, `__div2u`,
   etc.) or sysdolphin/baselib/HSD/init functions belong in their own libs
   with different cflags / mw_version. Auto-routing by function name prefix
   isn't implemented; pass `--lib <name>` manually or skip the group.

3. **First-attempt only**: extract_fn_asm.py was originally written for
   `auto_fn_8002F640_text` (HeapStats, numeric-only extab) and
   `auto_03_801223E8_text` (text-only, plain cache+search game code).
   Those are the two groups proven to scaffold end-to-end with this tool.
   Other groups may surface previously-unseen mwcc inline-asm corner cases.

When this tool fails:
- The .c file, configure.py edit, splits.txt edit, state.json edit, and
  renames.json edit are all left in place. You'll need to manually:
    git restore configure.py config/GNLJ82/splits.txt tools/extab_user_renames.json
    rm src/<path>.c
    # then revert state.json fn entries from `asm_fn` back to `pending`

Usage:
  python tools/scaffold_mega_bundle.py --group <group_id>
                                       [--tu <src/path/to.c>]
                                       [--lib <lib_name>]
                                       [--no-build]

  --group  is the basename of build/GNLJ82/asm/<gid>.s (e.g.
           `auto_03_801223E8_text`).
  --tu     defaults to `src/game/<derived>.c` from the group id (drops the
           `auto_` prefix, normalises hex digits).
  --lib    overrides the auto-pick (`game_extab` if extab present, else
           `game`). Pass `--lib <name>` if the group belongs to sysdolphin
           etc.
  --no-build  skip the verification build (lets you inspect the wiring
              before kicking off ninja).
"""
from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
DEFAULT_ASM_DIR = REPO_ROOT / "build" / "GNLJ82" / "asm"
DEFAULT_SYMBOLS_TXT = REPO_ROOT / "config" / "GNLJ82" / "symbols.txt"
SPLITS_TXT = REPO_ROOT / "config" / "GNLJ82" / "splits.txt"
CONFIGURE_PY = REPO_ROOT / "configure.py"
STATE_JSON = REPO_ROOT / ".orchestrator" / "state.json"
EXTAB_GROUPS_JSON = REPO_ROOT / ".orchestrator" / "extab_groups.json"
RENAMES_JSON = REPO_ROOT / "tools" / "extab_user_renames.json"
EXTRACT_FN_ASM = REPO_ROOT / "tools" / "extract_fn_asm.py"

GROUP_ID_RE = re.compile(r'^auto_(.+)_text$')


class ScaffoldTransaction:
    """Snapshot mutated files before edits so a baseline-build failure can
    revert the scaffold atomically. Captures content at first snapshot()
    per path (later writes to the same path don't overwrite the snapshot)."""

    def __init__(self) -> None:
        self.snapshots: dict[Path, bytes | None] = {}

    def snapshot(self, path: Path) -> None:
        if path in self.snapshots:
            return
        self.snapshots[path] = path.read_bytes() if path.exists() else None

    def revert(self) -> list[Path]:
        reverted: list[Path] = []
        for path, content in self.snapshots.items():
            if content is None:
                if path.exists():
                    path.unlink()
                    reverted.append(path)
            else:
                cur = path.read_bytes() if path.exists() else None
                if cur != content:
                    path.write_bytes(content)
                    reverted.append(path)
        return reverted


def derive_lib_from_text_start(text_start: int, extab_present: bool) -> str:
    """Auto-pick the configure.py lib for a new auto_* group by checking which
    existing lib's TU address range contains text_start. Falls back to
    `game_extab`/`game` if no match.

    Strategy: parse configure.py to get (lib_name -> [tu_path, ...]), parse
    splits.txt to get (tu_path -> (.text start, .text end)), build per-lib
    [min, max] range, then test text_start against each.
    """
    src = CONFIGURE_PY.read_text(encoding="utf-8")
    splits_src = SPLITS_TXT.read_text(encoding="utf-8")

    path_to_text = {}
    tu_block_re = re.compile(
        r'^([^\s][^:\n]*\.(?:c|cpp|s)):\s*\n((?:\t[^\n]*\n)+)', re.MULTILINE
    )
    code_sec_re = re.compile(
        r'(?:\.init|\.text|\.ctors|\.dtors)\s+start:0x([0-9A-Fa-f]+)\s+end:0x([0-9A-Fa-f]+)'
    )
    for m in tu_block_re.finditer(splits_src):
        starts, ends = [], []
        for s, e in code_sec_re.findall(m.group(2)):
            starts.append(int(s, 16))
            ends.append(int(e, 16))
        if starts:
            path_to_text[m.group(1)] = (min(starts), max(ends))

    lib_ranges: dict[str, tuple[int, int]] = {}
    lib_re = re.compile(r'"lib":\s*"([^"]+)"')
    for lib_m in lib_re.finditer(src):
        lib_name = lib_m.group(1)
        objs_m = re.search(r'"objects":\s*\[', src[lib_m.end():])
        if not objs_m:
            continue
        objs_open = lib_m.end() + objs_m.end()
        depth, i = 1, objs_open
        while i < len(src) and depth > 0:
            if src[i] == '[':
                depth += 1
            elif src[i] == ']':
                depth -= 1
            i += 1
        objs_block = src[objs_open:i - 1]
        starts, ends = [], []
        for path in re.findall(r'Object\([^,]+,\s*"([^"]+)"', objs_block):
            if path in path_to_text:
                s, e = path_to_text[path]
                starts.append(s)
                ends.append(e)
        if starts:
            lib_ranges[lib_name] = (min(starts), max(ends))

    candidate = None
    for lib_name, (lo, hi) in lib_ranges.items():
        if lo <= text_start < hi:
            candidate = lib_name
            break
    if candidate is None:
        return 'game_extab' if extab_present else 'game'

    if extab_present:
        if candidate == 'game':
            return 'game_extab' if 'game_extab' in lib_ranges else 'game'
        extab_variant = candidate + '_extab'
        if extab_variant in lib_ranges:
            return extab_variant
    return candidate


def derive_tu_path(group_id: str) -> Path:
    """Derive a neutral TU path from the dtk group id.

    `auto_03_801223E8_text` -> `src/game/auto_801223E8_block.c`
    `auto_fn_800A8F4C_text` -> `src/game/auto_800A8F4C_block.c`
    `auto_dtor_8005CCBC_text` -> `src/game/auto_8005CCBC_block.c`
    """
    m = GROUP_ID_RE.match(group_id)
    if not m:
        sys.exit(f"unrecognised group_id format: {group_id!r}")
    suffix = m.group(1)
    # Take the last underscore-separated token; for group ids the address is
    # always the final segment regardless of any `fn_` / `dtor_` / `NN_` prefix.
    addr = suffix.split('_')[-1]
    return Path("src/game") / f"auto_{addr.upper()}_block.c"


def sniff_extab_present(asm_path: Path) -> bool:
    """True if the asm file has `.section extab` (manual emit needed)."""
    with asm_path.open(encoding="utf-8") as f:
        for line in f:
            if line.startswith('.section extab'):
                return True
            if line.startswith('.text'):
                return False
    return False


def sniff_section_ranges(asm_path: Path) -> dict[str, tuple[int, int]]:
    """Return {section: (start_addr, end_addr_exclusive)} for extab /
    extabindex / .text. dtk emits leading `# 0xAAAA..0xBBBB | size: 0xCC`
    comments before each section header."""
    out: dict[str, tuple[int, int]] = {}
    pending: tuple[int, int] | None = None
    with asm_path.open(encoding="utf-8") as f:
        for line in f:
            line = line.rstrip()
            if line.startswith('# 0x') and '..0x' in line:
                m = re.match(r'#\s*0x([0-9A-Fa-f]+)\.\.0x([0-9A-Fa-f]+)\s*\|', line)
                if m:
                    pending = (int(m.group(1), 16), int(m.group(2), 16))
                    continue
            if pending is None:
                continue
            if line.startswith('.section extab,'):
                out['extab'] = pending
                pending = None
            elif line.startswith('.section extabindex,'):
                out['extabindex'] = pending
                pending = None
            elif line == '.text':
                out['.text'] = pending
                pending = None
    return out


def load_group_function_addrs(group_id: str) -> list[str]:
    if not EXTAB_GROUPS_JSON.is_file():
        sys.exit(f"missing {EXTAB_GROUPS_JSON} — run tools/build_extab_map.py first")
    data = json.loads(EXTAB_GROUPS_JSON.read_text(encoding="utf-8"))
    g = data['groups'].get(group_id)
    if g is None:
        sys.exit(f"group_id {group_id!r} not in extab_groups.json")
    return g['function_addresses']


def run_extract(group_id: str, tu_path: Path) -> dict:
    """Invoke extract_fn_asm.py and return the parsed renames mapping (if any)."""
    renames_out = REPO_ROOT / "build" / "tmp" / f"{group_id}_renames.json"
    renames_out.parent.mkdir(parents=True, exist_ok=True)
    cmd = [
        sys.executable, str(EXTRACT_FN_ASM), group_id,
        "--tu", str(tu_path).replace('\\', '/'),
        "--out-c", str(tu_path),
        "--out-renames", str(renames_out),
    ]
    subprocess.check_call(cmd)
    if not renames_out.is_file():
        return {}
    return json.loads(renames_out.read_text(encoding="utf-8"))


def prepend_comment_header(tu_path: Path, group_id: str, extab_present: bool) -> None:
    body = tu_path.read_text(encoding="utf-8")
    fn_count_hint = "all fns" if extab_present else f"text-only group"
    extab_hint = (
        "\n * Held as asm_fn with manually emitted extab/extabindex via "
        '__declspec(section ".extab_user"/".extabindex_user"). '
        "tools/postprocess_extab_user.py renames sections + symbols to the\n"
        " * extab/extabindex + @etb_/@eti_ form dtk expects."
        if extab_present
        else "\n * No extab/extabindex entries (dtk groups by `auto_*_text*.s` "
             "file boundary, not by extab presence)."
    )
    header = (
        "/*\n"
        f" * dtk reversed-extab group `{group_id}` bundle (1 TU, indivisible)."
        f"{extab_hint}\n"
        " *\n"
        " * Phase 3a/3b probe: all fns held as asm_fn initially, promote 1 fn at a\n"
        " * time via sub-agent dispatch (asm_fn -> matched).\n"
        " *\n"
        f" * Generated by `python tools/scaffold_mega_bundle.py --group {group_id}`.\n"
        " * Re-run to regenerate; hand edits below this header may be overwritten.\n"
        " *\n"
        " * See docs/per_fn_matching_strategy.md and docs/large_extab_group_strategy.md.\n"
        " */\n\n"
    )
    tu_path.write_text(header + body, encoding="utf-8")


def insert_object_in_configure(tu_rel: str, lib_name: str, extab_present: bool) -> None:
    """Insert `Object(Matching, "<tu_rel>", [extab_padding=...]) ` into the
    `lib_name` lib's objects list. Idempotent (skips if already present)."""
    src = CONFIGURE_PY.read_text(encoding="utf-8")
    if f'"{tu_rel}"' in src:
        return  # already wired

    extab_kwarg = ', extab_padding=b"\\x00\\x00"' if extab_present else ''
    new_obj = f'            Object(Matching, "{tu_rel}"{extab_kwarg}),\n'

    # Find the lib block: `"lib": "<lib_name>",` -> next `"objects": [` -> insert
    # before the closing `],`.
    lib_marker = f'"lib": "{lib_name}",'
    idx_lib = src.find(lib_marker)
    if idx_lib < 0:
        sys.exit(f'lib "{lib_name}" not found in configure.py')
    idx_objects = src.find('"objects": [', idx_lib)
    if idx_objects < 0:
        sys.exit(f'"objects": [ block not found after lib "{lib_name}"')
    # Find matching close bracket — assume no nested brackets in the literal list.
    idx_close = src.find('],', idx_objects)
    if idx_close < 0:
        sys.exit("could not locate objects list close bracket")
    new_src = src[:idx_close] + new_obj + src[idx_close:]
    CONFIGURE_PY.write_text(new_src, encoding="utf-8")


def insert_splits_entry(tu_rel: str, ranges: dict[str, tuple[int, int]]) -> None:
    """Insert a `<tu_rel>:` block in splits.txt at the address-sorted slot
    (sorted by the .text start). Idempotent."""
    src = SPLITS_TXT.read_text(encoding="utf-8")
    if f'\n{tu_rel}:' in src:
        return

    text_start = ranges['.text'][0]

    # Build new block.
    lines = [f'{tu_rel}:']
    for sec in ('extab', 'extabindex', '.text'):
        if sec in ranges:
            s, e = ranges[sec]
            sec_field = sec.ljust(11)
            lines.append(f'\t{sec_field} start:0x{s:08X} end:0x{e:08X}')
    new_block = '\n'.join(lines) + '\n\n'

    # Find insertion point: the first existing TU block whose .text start
    # is greater than ours.
    tu_block_re = re.compile(r'^([A-Za-z_][^:\n]*\.(?:c|cpp|s)):', re.MULTILINE)
    text_start_re = re.compile(r'^\t\.text\s+start:0x([0-9A-Fa-f]+)', re.MULTILINE)

    insert_at = None
    for m in tu_block_re.finditer(src):
        block_end = src.find('\n\n', m.end())
        if block_end < 0:
            block_end = len(src)
        block = src[m.start():block_end]
        ts_m = text_start_re.search(block)
        if ts_m and int(ts_m.group(1), 16) > text_start:
            insert_at = m.start()
            break

    if insert_at is None:
        # Append at end (or before trailing blank lines).
        new_src = src.rstrip('\n') + '\n\n' + new_block
    else:
        new_src = src[:insert_at] + new_block + src[insert_at:]
    SPLITS_TXT.write_text(new_src, encoding="utf-8")


def merge_renames(tu_rel: str, snippet: dict) -> None:
    """Merge per-TU rename map into tools/extab_user_renames.json."""
    if not snippet or tu_rel not in snippet or not snippet[tu_rel]:
        return
    existing = json.loads(RENAMES_JSON.read_text(encoding="utf-8")) if RENAMES_JSON.is_file() else {}
    if "_comment" not in existing:
        existing["_comment"] = ("Per-TU mapping of user-emitted extab/extabindex C "
                                "symbol names to the anonymous local @etb_/@eti_ names "
                                "dtk dol split writes. Maintained by "
                                "tools/scaffold_mega_bundle.py + manual edits.")
    existing[tu_rel] = snippet[tu_rel]
    RENAMES_JSON.write_text(json.dumps(existing, indent=2, ensure_ascii=False) + '\n', encoding="utf-8")


def update_state_asm_fn(group_id: str, fn_addrs: list[str], tu_rel: str) -> int:
    """Flip the group's fns in state.json to status `asm_fn`. Returns count updated."""
    if not STATE_JSON.is_file():
        return 0
    data = json.loads(STATE_JSON.read_text(encoding="utf-8"))
    fns = data.get('functions', {})
    ts = subprocess.check_output(
        ['python', '-c', 'import datetime as d; print(d.datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%SZ"))'],
        text=True,
    ).strip()
    n = 0
    for a in fn_addrs:
        fn = fns.get(a) or fns.get(a.lower())
        if fn is None:
            continue
        if fn.get('status') == 'excluded':
            continue  # leave placeholders alone
        fn['status'] = 'asm_fn'
        fn['last_attempt_at'] = ts
        fn['tu_hint'] = tu_rel
        fn['notes'] = f'scaffolded via scaffold_mega_bundle.py from {group_id}'
        n += 1
    STATE_JSON.write_text(json.dumps(data, indent=2, ensure_ascii=False) + '\n', encoding="utf-8")
    return n


def main(argv: list[str] | None = None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--group", required=True, help="group_id (auto_..._text)")
    ap.add_argument("--tu", type=Path, help="override TU path (default derived from group id)")
    ap.add_argument("--lib", help="override target lib name in configure.py (default: auto-detect by .text start address)")
    ap.add_argument("--no-build", action="store_true", help="skip verification build")
    ap.add_argument("--no-revert", action="store_true", help="on build failure keep partial scaffold (for debugging)")
    args = ap.parse_args(argv)

    asm_path = DEFAULT_ASM_DIR / f"{args.group}.s"
    if not asm_path.is_file():
        sys.exit(f"asm file not found: {asm_path}")

    tu_path = args.tu if args.tu else derive_tu_path(args.group)
    if tu_path.is_absolute():
        tu_rel = str(tu_path.relative_to(REPO_ROOT)).replace('\\', '/')
    else:
        tu_rel = str(tu_path).replace('\\', '/')
    abs_tu = REPO_ROOT / tu_rel

    extab_present = sniff_extab_present(asm_path)
    ranges = sniff_section_ranges(asm_path)
    if '.text' not in ranges:
        sys.exit("could not sniff .text range from asm file")
    text_start = ranges['.text'][0]

    if args.lib:
        lib_name = args.lib
        lib_origin = "user-specified"
    else:
        lib_name = derive_lib_from_text_start(text_start, extab_present)
        lib_origin = f"auto-picked from .text start 0x{text_start:08X}"
    configure_path = tu_rel[len('src/'):] if tu_rel.startswith('src/') else tu_rel

    print(f"[scaffold] group={args.group} tu={tu_rel} lib={lib_name} ({lib_origin}) extab={extab_present}")

    tx = ScaffoldTransaction()
    tx.snapshot(abs_tu)
    tx.snapshot(CONFIGURE_PY)
    tx.snapshot(SPLITS_TXT)
    tx.snapshot(RENAMES_JSON)
    tx.snapshot(STATE_JSON)

    try:
        snippet = run_extract(args.group, abs_tu)
        prepend_comment_header(abs_tu, args.group, extab_present)
        print(f"[scaffold] wrote {tu_rel}")

        insert_object_in_configure(configure_path, lib_name, extab_present)
        print(f"[scaffold] inserted Object(Matching, \"{configure_path}\"{', extab_padding' if extab_present else ''}) into lib {lib_name}")

        insert_splits_entry(configure_path, ranges)
        print(f"[scaffold] inserted splits.txt entry for {configure_path}")

        if extab_present:
            merge_renames(tu_rel, snippet)
            print(f"[scaffold] merged renames for {tu_rel} into {RENAMES_JSON.name}")

        fn_addrs = load_group_function_addrs(args.group)
        n = update_state_asm_fn(args.group, fn_addrs, configure_path)
        print(f"[scaffold] state.json: marked {n} fn(s) as asm_fn")

        if args.no_build:
            print("[scaffold] --no-build set, skipping verification build")
            return 0

        print("[scaffold] running python configure.py && ninja build/GNLJ82/ok")
        subprocess.check_call([sys.executable, str(CONFIGURE_PY)], cwd=REPO_ROOT)
        res = subprocess.run(["ninja", "build/GNLJ82/ok"], cwd=REPO_ROOT)
        if res.returncode != 0:
            raise RuntimeError(f"baseline build failed (rc={res.returncode})")
        print(f"[scaffold] SUCCESS: baseline asm_fn bundle scaffolded ({len(fn_addrs)} fns).")
        print(f"[scaffold] next: dispatch sub(s) for promote_asm_fn on this TU.")
        return 0
    except Exception as e:
        print(f"[scaffold] FAILED: {e}", file=sys.stderr)
        if args.no_revert:
            print("[scaffold] --no-revert set, partial scaffold kept for debugging", file=sys.stderr)
        else:
            reverted = tx.revert()
            for p in reverted:
                rel = p.relative_to(REPO_ROOT) if p.is_absolute() else p
                print(f"[scaffold] reverted: {rel}", file=sys.stderr)
            print(f"[scaffold] revert complete ({len(reverted)} file(s) restored)", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
