#!/usr/bin/env python3
"""Re-number the anonymous `@N` extab renames of a TU after a source edit.

Why: CW names its automatic extab/extabindex entries `@N`, and N shifts every
time a literal, string or declaration is added or moved in the TU. The
`@N -> @etb_/@eti_` entries in tools/extab_user_renames.json then point at the
wrong objects (often a pooled float literal), the DOL breaks, and neither the
objdiff % nor pragmasweep/cperm scores notice. Threads fixed this by hand
(dump `objdump -t` of the raw .o, re-map, edit the json).

What it does, per TU:
  1. compiles the source with the exact mwcc command ninja uses, but stops
     before tools/postprocess_extab_user.py (raw object, real @N names);
  2. reads each extabindex entry (function, extab) of the raw object and of
     the target object build/GNLJ82/obj/<tu>.o (@eti_/@etb_);
  3. joins them by function name (raw names go through the TU's non-@ renames
     first, so `__ct__...` -> `fn_...` style mappings are honoured);
  4. replaces only the TU's `@N -> @etb_*/@eti_*` keys in the json.
Other `@N` keys (e.g. `"@108": "global:lbl_..."` string literals) are kept as
they are. Output per TU: ok / STALE (names differ; usually harmless while the
old numbers point at nothing) / RISKY (an old @N now names a literal or other
non-extab object; this broke main.dol in b853d71, though not every such case
does). Run it whenever main.dol fails after an edit in a C++/EH TU.

Usage (repo root, after configure.py):
  python3 tools/extab_renumber.py src/game/kartmove/fn_8019C15C.cpp   # dry run
  python3 tools/extab_renumber.py src/game/Foo.cpp --write
  python3 tools/extab_renumber.py --all-changed [--write]  # TUs changed vs origin/main
Exit code 1 when a dry run finds stale entries (usable as a pre-push check).
Only fix TUs you hold the claim for; the json is shared.
After --write, the object is rebuilt by ninja on the next build (the json is
an implicit dependency since the build-deps change; on older checkouts touch
the source).
"""
from __future__ import annotations

import argparse
import json
import os
import re
import shlex
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
RENAMES = ROOT / "tools" / "extab_user_renames.json"
BUILD = ROOT / "build" / "GNLJ82"
READELF = ROOT / "build" / "binutils" / "powerpc-eabi-readelf"


def src_to_obj(src: str) -> tuple[Path, Path]:
    rel = Path(src).with_suffix(".o")
    if rel.parts[0] != "src":
        raise SystemExit(f"{src}: expected a path under src/")
    built = BUILD / rel
    target = BUILD / "obj" / Path(*rel.parts[1:])
    return built, target


def mwcc_command(built: Path, outdir: str) -> str:
    out = subprocess.run(["ninja", "-t", "commands", str(built.relative_to(ROOT))],
                         cwd=ROOT, capture_output=True, text=True)
    if out.returncode != 0 or not out.stdout.strip():
        raise SystemExit(f"ninja has no command for {built}: {out.stderr.strip()}")
    cmd = out.stdout.strip().splitlines()[-1]
    first = cmd.split(" && ")[0]
    if "mwcceppc" not in first:
        raise SystemExit(f"unexpected compile command: {first[:200]}")
    # -o <dir> -> scratch dir; the object keeps its basename.
    first = re.sub(r"(-o\s+)(\S+)", lambda m: m.group(1) + shlex.quote(outdir), first, count=1)
    # The .d file goes next to -o; keep -MMD harmless.
    return first


def readelf(path: Path, flag: str) -> str:
    return subprocess.run([str(READELF), flag, "-W", str(path)], capture_output=True,
                          text=True, check=True).stdout


def section_names(path: Path) -> dict[int, str]:
    names = {}
    for line in readelf(path, "-S").splitlines():
        m = re.match(r"\s*\[\s*(\d+)\]\s+(\S+)", line)
        if m:
            names[int(m.group(1))] = m.group(2)
    return names


def symbols(path: Path):
    """[(value, size, type, ndx, name)]"""
    out = []
    for line in readelf(path, "-s").splitlines():
        p = line.split()
        if len(p) >= 8 and p[0].rstrip(":").isdigit():
            try:
                val = int(p[1], 16)
            except ValueError:
                continue
            ndx = int(p[6]) if p[6].isdigit() else -1
            out.append((val, int(p[2], 0) if p[2].isdigit() else 0, p[3], ndx, p[7]))
    return out


def symbol_sections(path: Path) -> dict[str, str]:
    """{local @N name: section name} for a raw object."""
    secs = section_names(path)
    return {n: secs.get(nd, "?") for _, _, _, nd, n in symbols(path) if n.startswith("@")}


def is_anon(key: str) -> bool:
    return re.fullmatch(r"@\d+", key) is not None


def extabindex_entries(path: Path) -> list[tuple[str, str, str]]:
    """[(function, extab symbol, extabindex symbol)] in entry order."""
    secs = section_names(path)
    idx_sec = next((i for i, n in secs.items() if n == "extabindex"), None)
    tab_sec = next((i for i, n in secs.items() if n == "extab"), None)
    if idx_sec is None:
        return []
    syms = symbols(path)
    idx_at = {v: n for v, _, t, nd, n in syms if nd == idx_sec and t == "OBJECT"}
    tab_at = {v: n for v, _, t, nd, n in syms if nd == tab_sec and t == "OBJECT"}
    relocs: dict[int, tuple[str, int]] = {}
    cur = False
    for line in readelf(path, "-r").splitlines():
        if line.startswith("Relocation section"):
            cur = "'.relaextabindex'" in line or "'.rela.extabindex'" in line
            continue
        if not cur:
            continue
        p = line.split()
        if len(p) >= 5 and re.fullmatch(r"[0-9a-f]{8}", p[0]):
            name = p[4]
            add = int(p[6], 16) if len(p) >= 7 and p[5] == "+" else 0
            relocs[int(p[0], 16)] = (name, add)
    out = []
    for off in sorted(o for o in relocs if o % 12 == 0):
        fn, _ = relocs[off]
        tab_name, tab_add = relocs.get(off + 8, ("?", 0))
        if tab_name == "extab":  # section-relative reloc
            tab_name = tab_at.get(tab_add, "?")
        out.append((fn, tab_name, idx_at.get(off, "?")))
    return out


def renumber(src: str, renames: dict) -> tuple[dict, list[str], list[str]]:
    """Return (new mapping for the TU, problems, harmful).

    harmful: old @N keys that now name something other than an extab entry in
    the raw object (e.g. a pooled float literal). Those renames corrupt the
    object (postprocess_sdata2 / dtk then see a wrong name) and break the DOL.
    """
    built, target = src_to_obj(src)
    problems: list[str] = []
    old = dict(renames.get(src, {}))
    if not target.exists():
        return old, [f"no target object {target} (run ninja once)"], []
    with tempfile.TemporaryDirectory() as td:
        cmd = mwcc_command(built, td)
        r = subprocess.run(cmd, shell=True, cwd=ROOT, capture_output=True, text=True)
        raw = Path(td) / built.name
        if r.returncode != 0 or not raw.exists():
            return old, [f"compile failed:\n{r.stdout}{r.stderr}"], []
        mine = extabindex_entries(raw)
        raw_secs = symbol_sections(raw)
    theirs = {fn: (tab, idx) for fn, tab, idx in extabindex_entries(target)}
    named = {k: v for k, v in old.items() if not is_anon(k)}
    new_at: dict[str, str] = {}
    for fn, tab, idx in mine:
        tname = named.get(fn, fn)
        if tname.startswith(("extern:", "global:")):
            tname = tname.split(":", 1)[1]
        if tname not in theirs:
            continue  # e.g. a weak copy the linker drops; target has no entry
        ttab, tidx = theirs[tname]
        for a, b in ((tab, ttab), (idx, tidx)):
            if is_anon(a) and b.startswith(("@etb_", "@eti_")):
                new_at[a] = b
            elif a != b and not is_anon(a) and named.get(a) != b:
                problems.append(f"{fn}: named extab symbol {a} vs target {b} (not touched)")
    harmful = []
    for k, v in old.items():
        if is_anon(k) and v.startswith(("@etb_", "@eti_")) and k in raw_secs \
                and raw_secs[k] not in ("extab", "extabindex"):
            harmful.append(f"{k} is now a {raw_secs[k]} object but is renamed to {v}")
    if not new_at and not any(is_anon(k) for k in old):
        return old, problems, harmful
    # Rebuild in the original key order: non-@ keys stay, the @ extab block is
    # replaced where it first appeared.
    result: dict[str, str] = {}
    inserted = False
    for k, v in old.items():
        if is_anon(k) and v.startswith(("@etb_", "@eti_")):
            if not inserted:
                result.update(sorted(new_at.items(), key=lambda kv: int(kv[0][1:])))
                inserted = True
            continue
        result[k] = v
    if not inserted:
        result.update(sorted(new_at.items(), key=lambda kv: int(kv[0][1:])))
    return result, problems, harmful


def changed_tus() -> list[str]:
    out = subprocess.run(["git", "diff", "--name-only", "origin/main", "--", "src"],
                         cwd=ROOT, capture_output=True, text=True, check=True).stdout
    return [l for l in out.split() if l.endswith((".c", ".cpp"))]


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("src", nargs="*")
    ap.add_argument("--all-changed", action="store_true", help="every src/ file changed vs origin/main")
    ap.add_argument("--write", action="store_true")
    a = ap.parse_args()
    os.chdir(ROOT)
    tus = list(a.src) + (changed_tus() if a.all_changed else [])
    if not tus:
        ap.error("give a source path or --all-changed")
    text = RENAMES.read_text(encoding="utf-8")
    renames = json.loads(text)
    stale = bad = 0
    for src in tus:
        src = Path(src).as_posix()
        old = renames.get(src, {})
        new, problems, harmful = renumber(src, renames)
        ext = lambda m: {k: v for k, v in m.items() if is_anon(k) and v.startswith(("@etb_", "@eti_"))}
        old_at, new_at = ext(old), ext(new)
        if old_at == new_at:
            print(f"{src}: ok ({len(old_at)} @N extab renames)")
        else:
            stale += 1
            bad += bool(harmful)
            print(f"{src}: {'RISKY' if harmful else 'STALE'}")
            for k in sorted(set(old_at) | set(new_at), key=lambda s: int(s[1:])):
                if old_at.get(k) != new_at.get(k):
                    print(f"    {k}: {old_at.get(k, '-')} -> {new_at.get(k, '-')}")
            for h in harmful:
                print(f"    !! {h}")
            if a.write:
                renames[src] = new
        for p in problems:
            print(f"    note: {p}")
    if a.write and stale:
        RENAMES.write_text(json.dumps(renames, indent=2, ensure_ascii=False), encoding="utf-8")
        print(f"wrote {RENAMES.relative_to(ROOT)}")
        for src in tus:  # make ninja rebuild even without the json dependency
            Path(src).touch()
    if stale and not a.write:
        print(f"{stale} TU(s) stale ({bad} RISKY = a rename now hits a non-extab object). "
              "Re-run with --write to fix.")
    return 1 if stale and not a.write else 0


if __name__ == "__main__":
    sys.exit(main())
