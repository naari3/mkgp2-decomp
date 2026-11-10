#!/usr/bin/env python3
"""Compile the NON_MATCHING side of a unit and score it against the target.

Some functions are kept as inline asm in the default build (so main.dol stays
byte-identical) and carry a behaviourally equivalent C version for the PC
port:

    #ifdef NON_MATCHING
    void Foo(...) { ...equivalent C... }
    #else
    asm void Foo(...) { nofralloc ... }
    #endif

This tool makes sure that C side keeps compiling. It takes the unit's real
compile command from build.ninja, adds -DNON_MATCHING, writes the object to
build/GNLJ82/nonmatching/ (never linked) and prints the objdiff percentage of
every function that only exists as C under NON_MATCHING. Rules:
docs/matching_rules.md section 0 (2026-11-10) and docs/nonmatching_c.md.

usage:
  tools/nonmatching_check.py                 # every unit with a NON_MATCHING block
  tools/nonmatching_check.py game/RivalRun   # one unit (configure.py path, with or without ext)
  tools/nonmatching_check.py --list          # units and guarded functions
  tools/nonmatching_check.py UNIT --diff FN  # instruction diff of one function
exit status 1 if any unit fails to compile.
"""
import argparse
import difflib
import json
import os
import re
import shlex
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BUILD = "build/GNLJ82"
OUTROOT = BUILD + "/nonmatching"
GUARD_RE = re.compile(r"^[ \t]*#[ \t]*if(?:n?def[ \t]+NON_MATCHING\b|[ \t]+!?\s*defined[ \t]*\(?[ \t]*NON_MATCHING\b)", re.M)
IFDEF_RE = re.compile(r"^[ \t]*#[ \t]*if(?:def[ \t]+NON_MATCHING\b|[ \t]+defined[ \t]*\(?[ \t]*NON_MATCHING\b)")
ASM_DEF_RE = re.compile(r"^[^\n;{}#]*\basm\b[^\n;{}]*?\b([A-Za-z_]\w*)\s*\([^;{}]*\)\s*\{", re.M)


INC_RE = re.compile(r'^[ \t]*#[ \t]*include[ \t]+"([^"\n]+\.inc)"[^\n]*$', re.M)


def read_expanded(path, depth=0):
    """Source text with local `#include "x.inc"` fragments spliced in (some
    units keep their functions in .inc files next to the .c)."""
    try:
        text = open(path, encoding="utf-8", errors="replace").read()
    except OSError:
        return ""
    if depth > 4:
        return text

    def sub(m):
        for base in (os.path.dirname(path), ROOT, os.path.join(ROOT, "include")):
            inc = os.path.join(base, m.group(1))
            if os.path.isfile(inc):
                return read_expanded(inc, depth + 1)
        return m.group(0)

    return INC_RE.sub(sub, text)


def guarded_units():
    out = []
    for base, _, files in os.walk(os.path.join(ROOT, "src")):
        for f in files:
            if not f.endswith((".c", ".cpp", ".cp")):
                continue
            p = os.path.join(base, f)
            text = read_expanded(p)
            if GUARD_RE.search(text):
                out.append(os.path.relpath(p, ROOT))
    return sorted(out)


NOT_GUARD_RE = re.compile(r"^[ \t]*#[ \t]*if(?:ndef[ \t]+NON_MATCHING\b|[ \t]+!\s*defined[ \t]*\(?[ \t]*NON_MATCHING\b)")
ASM_LINE_RE = re.compile(r"\s*(?:extern\s+\"C\"\s+)?(?:[\w\*]+\s+)*asm\s+[^;{}(]*?\b([A-Za-z_]\w*)\s*\([^;{}]*\)\s*\{")


def guarded_functions(src):
    """Names of asm functions that are compiled only without NON_MATCHING:
    the #else arm of `#ifdef NON_MATCHING`, or the body of `#ifndef NON_MATCHING`."""
    text = read_expanded(os.path.join(ROOT, src))
    names = []
    depth = []  # True = this arm is the asm side
    for line in text.splitlines(True):
        s = line.strip()
        if s.startswith("#"):
            d = s[1:].strip()
            if d.startswith("if"):
                if IFDEF_RE.match(line):
                    depth.append([False, True])
                elif NOT_GUARD_RE.match(line):
                    depth.append([True, True])
                else:
                    depth.append([False, False])
            elif d.startswith("else") and depth and depth[-1][1]:
                depth[-1][0] = not depth[-1][0]
            elif d.startswith("endif") and depth:
                depth.pop()
        elif any(x[0] for x in depth):
            m = ASM_LINE_RE.match(line)
            if m:
                names.append(m.group(1))
    return names


def resolve(unit):
    unit = unit.replace("\\", "/")
    if unit.startswith("src/"):
        unit = unit[4:]
    for ext in ("", ".c", ".cpp", ".cp"):
        if os.path.isfile(os.path.join(ROOT, "src", unit + ext)):
            return "src/" + unit + ext
    sys.exit("no such unit: " + unit)


def compile_cmd(src):
    """(compile argv, object path, post-process shell commands, error)."""
    obj = BUILD + "/" + os.path.splitext(src)[0] + ".o"
    r = subprocess.run(["ninja", "-t", "commands", "-s", obj], cwd=ROOT, capture_output=True, text=True)
    lines = [l for l in r.stdout.splitlines() if "mwcceppc" in l]
    if not lines:
        return None, None, None, "no compile command for " + obj
    steps = lines[-1].split(" && ")
    args = shlex.split(steps[0])
    outdir = OUTROOT + "/" + os.path.dirname(src)  # keeps src/: postprocess_extab_user keys on it
    os.makedirs(os.path.join(ROOT, outdir), exist_ok=True)
    args = [a for a in args if a != "-MMD"]
    i = args.index("-o")
    args[i + 1] = outdir
    c = args.index("-c")
    args[c:c] = ["-DNON_MATCHING"]
    # one error is not enough when writing a long function
    if "-maxerrors" in args:
        args[args.index("-maxerrors") + 1] = os.environ.get("NM_MAXERRORS", "8")
    out = outdir + "/" + os.path.splitext(os.path.basename(src))[0] + ".o"
    # the unit's own object post-processing (symbol renames, extab clean-up),
    # so function names line up with the target; best effort
    post = [st.replace(obj, out) for st in steps[1:] if "transform_dep" not in st]
    return args, out, post, None


def scores(src, out):
    target = BUILD + "/obj/" + os.path.splitext(src)[0][4:] + ".o"
    if not os.path.isfile(os.path.join(ROOT, target)):
        return {}
    js = out + ".diff.json"
    r = subprocess.run([BUILD.split("/")[0] + "/tools/objdiff-cli", "diff", "-c", "functionRelocDiffs=none", "-1", target, "-2", out, "-o", js],
                       cwd=ROOT, capture_output=True, text=True)
    if r.returncode:
        return {}
    d = json.load(open(os.path.join(ROOT, js)))
    res = {}
    have = {s.get("name") for s in d["right"]["symbols"]}
    for s in d["left"]["symbols"]:
        if "instructions" in s and s.get("name"):
            res[s["name"]] = (s.get("match_percent"), int(s.get("size", 0)), s["name"] in have)
    return res


_KNOWN = None


def unknown_symbols(out):
    """Undefined symbols of the NON_MATCHING object that config/GNLJ82/symbols.txt
    does not know: a call to a function that was never declared (implicit int),
    an old name, or a mangled ctor/vtable without a rename. The port cannot link these."""
    global _KNOWN
    if _KNOWN is None:
        _KNOWN = set()
        for l in open(os.path.join(ROOT, "config/GNLJ82/symbols.txt"), encoding="utf-8", errors="replace"):
            _KNOWN.add(l.split(" = ", 1)[0].strip())
    nm = os.path.join(ROOT, "build/binutils/powerpc-eabi-nm")
    r = subprocess.run([nm, "-u", out], cwd=ROOT, capture_output=True, text=True)
    names = [l.split()[-1] for l in r.stdout.splitlines() if l.strip()]
    return sorted(n for n in names if n not in _KNOWN)


def check(src):
    args, out, post, err = compile_cmd(src)
    if err:
        return src, False, err, {}
    r = subprocess.run(args, cwd=ROOT, capture_output=True, text=True)
    if r.returncode or not os.path.isfile(os.path.join(ROOT, out)):
        return src, False, (r.stdout + r.stderr).strip(), {}
    for st in post:
        p = subprocess.run(st, shell=True, cwd=ROOT, capture_output=True, text=True)
        if p.returncode:
            break  # e.g. extab reorder on compiler-made records: names may stay mangled
    sc = scores(src, out)
    sc["?unknown"] = unknown_symbols(out)
    return src, True, out, sc


def fn_text(obj, fn, tag):
    s = os.path.join(ROOT, OUTROOT, "_" + tag + ".s")
    subprocess.run([os.path.join(ROOT, "build/tools/dtk"), "elf", "disasm", obj, s], cwd=ROOT, check=True, capture_output=True)
    out, on = [], False
    for l in open(s):
        if l.startswith(".fn " + fn + ","):
            on = True
            continue
        if on and l.startswith(".endfn"):
            break
        if on:
            m = re.match(r"/\* [0-9A-F]+ [0-9A-F]+  (?:.. .. .. ..) \*/\t(.*)", l)
            if m:
                out.append(re.sub(r"\.L_[0-9A-F]+", ".L", m.group(1)))
            elif l.strip().startswith(".L"):
                out.append(".L:")
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("units", nargs="*")
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--diff", metavar="FN")
    ap.add_argument("--all-functions", action="store_true", help="print every function of the unit, not only guarded ones")
    ap.add_argument("-j", type=int, default=os.cpu_count() or 4)
    a = ap.parse_args()

    units = [resolve(u) for u in a.units] or guarded_units()
    if a.list:
        total = 0
        for u in units:
            fns = guarded_functions(u)
            total += len(fns)
            print(u + ": " + ", ".join(fns))
        print("%d units, %d functions with a NON_MATCHING C side" % (len(units), total))
        return 0

    bad = 0
    with ThreadPoolExecutor(a.j) as ex:
        results = list(ex.map(check, units))
    for src, ok, info, sc in results:
        if not ok:
            bad += 1
            print("FAIL %s\n%s" % (src, info))
            continue
        fns = guarded_functions(src)
        unknown = sc.pop("?unknown", [])
        print("ok   %s" % src)
        if unknown:
            bad += 1
            print("       UNKNOWN SYMBOLS (not in symbols.txt: undeclared function, old name or missing rename): " + ", ".join(unknown))
        names = sorted(sc) if a.all_functions else fns
        for fn in names:
            if fn not in sc:
                print("       %-48s (not found in the target object)" % fn)
                continue
            pct, size, have = sc[fn]
            if not have:
                print("       %-48s MISSING from the NON_MATCHING object" % fn)
                bad += 1
            elif a.all_functions and pct == 100.0 and fn not in fns:
                continue
            else:
                print("       %-48s %6.2f%%  (%d insns)" % (fn, pct or 0.0, size // 4))
        if a.diff:
            target = BUILD + "/obj/" + os.path.splitext(src)[0][4:] + ".o"
            t = fn_text(target, a.diff, "target")
            m = fn_text(info, a.diff, "mine")
            for l in difflib.unified_diff(t, m, "target", "nonmatching", lineterm="", n=3):
                print(l)
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
