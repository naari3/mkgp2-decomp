#!/usr/bin/env python3
"""Find mechanical wins left after other threads' landings.

  python3 -I tools/helpers/flipcheck.py [--claims FILE] [--try]

Run from the repo root after a build (needs build/GNLJ82/report.json).

1. FLIP: NonMatching TUs whose functions are all 100% in report.json.
   With --try, each one is flipped to Matching in configure.py, built, checked
   for main.dol OK, and reverted (the working tree is left as it was). Ones
   that pass can be landed as-is (claim first!). Ones that fail usually need
   DATA_ALIGN4_TUS or a weak-copy rename (see TIPS.md / docs/flip_hints.md).
2. DONE: open queue items whose every named function is already 100%
   (threads closed 28 of these by hand on 11/08). Prints the queue.py done
   commands; it does not run them.

--claims FILE: open unit-claim issue titles (one per line, from the GitHub MCP
list_issues with explicit page numbers). TUs named there are skipped. Without
it, check claims yourself before acting on any FLIP row.
"""
import argparse, json, os, re, subprocess, sys
from pathlib import Path

QUEUE = os.path.join(os.path.dirname(os.path.abspath(__file__)), "workqueue.py")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--claims")
    ap.add_argument("--try", dest="try_", action="store_true")
    a = ap.parse_args()
    r = json.load(open("build/GNLJ82/report.json"))
    # Inline-asm functions count as 100% in the report: never treat them as done.
    asm_re = re.compile(r"^\s*(?:static\s+|extern\s+)?asm\b[^;{(]*?\b(\w+)\s*\(", re.M)
    asm_fns, asm_srcs = set(), set()
    for f in list(Path("src").rglob("*.c")) + list(Path("src").rglob("*.cpp")):
        found = asm_re.findall(f.read_text(encoding="utf-8", errors="replace"))
        if found:
            asm_fns.update(found)
            asm_srcs.add(f.as_posix())
    claims = open(a.claims).read() if a.claims else ""
    fn_pct = {}
    flips = []
    for u in r["units"]:
        fs = u.get("functions") or []
        for f in fs:
            fn_pct[f["name"]] = f.get("fuzzy_match_percent", 0.0)
        md = u.get("metadata") or {}
        if fs and not md.get("complete") and all(f.get("fuzzy_match_percent") == 100.0 for f in fs):
            src = md.get("source_path", "")
            if src in asm_srcs:
                continue  # still has inline asm
            path = src[len("src/"):] if src.startswith("src/") else src
            if path and claims and path in claims:
                print(f"skip (claimed): {path}")
                continue
            flips.append(path)
    print(f"== FLIP candidates ({len(flips)}) ==")
    cfg = Path("configure.py")
    orig = cfg.read_text(encoding="utf-8")
    for path in flips:
        line = f'Object(NonMatching, "{path}"'
        if line not in orig:
            print(f"  {path}: not found as Object(NonMatching, ...) in configure.py")
            continue
        if not a.try_:
            print(f"  {path}")
            continue
        cfg.write_text(orig.replace(line, f'Object(Matching, "{path}"', 1), encoding="utf-8")
        try:
            p = subprocess.run("rm -f build/GNLJ82/main.dol build/GNLJ82/ok && ninja build/GNLJ82/ok",
                               shell=True, capture_output=True, text=True)
            ok = p.returncode == 0 and "main.dol: OK" in p.stdout
            print(f"  {path}: {'FLIPS CLEANLY (main.dol OK)' if ok else 'flip breaks main.dol'}")
        finally:
            cfg.write_text(orig, encoding="utf-8")
    if a.try_ and flips:
        subprocess.run("ninja build/GNLJ82/ok", shell=True, capture_output=True)
    print("== DONE candidates (open queue items already at 100%) ==")
    out = subprocess.run([sys.executable, "-I", QUEUE, "list", "--who", "flipcheck"],
                         capture_output=True, text=True).stdout
    for line in out.splitlines():
        m = re.match(r"\[ \] (Q\w+) (.*)", line)
        if not m:
            continue
        qid, rest = m.groups()
        head = rest.split("|")[0]
        names = [n for n in re.findall(r"\b([A-Za-z_]\w*)\b", head) if n in fn_pct]
        names = [n for n in names if not re.search(rf"{n}\s+done", head)]
        if names and not any(n in asm_fns for n in names) and all(fn_pct[n] == 100.0 for n in names):
            print(f"  python3 -I {QUEUE} done {qid} --note 'already 100% on main'   # {head.strip()}")


if __name__ == "__main__":
    main()
