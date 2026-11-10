#!/usr/bin/env python3
"""Calls whose argument classes disagree with the definition: by-value struct
against pointer, float against double (K&R calls), int/float order, struct
return against an explicit result pointer. Prints tab-separated rows;
redirect to $PORT_ABI_OUT/types.txt for order_fix.py.

Part of the call-ABI sweep described in docs/notes/port_abi.md. Needs clang
and a checkout of mkgp2-pc (its port/tools/compile_census.py supplies the
compile flags); run from a directory where `port/`, `src/`, `include/`,
`configure.py` and `config/` are all visible (for example the mkgp2-pc
checkout itself, or a scratch directory of symlinks to both repositories).
Intermediate files go to $PORT_ABI_OUT (default: the current directory).
"""
import os
OUT = os.environ.get("PORT_ABI_OUT", os.getcwd())

import collections, concurrent.futures, os, re, subprocess, sys
sys.path.insert(0, 'port/tools')
import compile_census as cc, link_census as lc
ROOT = cc.ROOT

def split_args(text, i):
    depth, j, start, out = 0, i, i + 1, []
    while j < len(text):
        c = text[j]
        if c in "([{<": depth += 1
        elif c in ")]}>":
            depth -= 1
            if depth == 0: break
        elif c == "," and depth == 1:
            out.append(text[start:j]); start = j + 1
        j += 1
    last = text[start:j].strip()
    if last: out.append(last)
    return [a.strip() for a in out]

def cls(a):
    if a == '...': return '...'
    if 'byval' in a: return 'byval'
    if 'sret' in a: return 'sret'
    t = a.split()[0]
    if t.startswith('ptr'): return 'ptr'
    if t in ('float', 'double'): return t
    if re.match(r'i\d+$', t): return 'i64' if t == 'i64' else 'int'
    return t

def scan(path):
    cmd = ["clang", "-target", cc.TARGET, "-S", "-emit-llvm", "-O0", "-fno-exceptions", "-fno-rtti", "-fcommon"] + cc.base_flags(path)[1:]
    cmd += ["-include", cc.COMPAT]
    cmd += ["-x", "c++", "-std=gnu++98"] if cc.is_cxx(path, cc.TARGET) else [
        "-x", "c", "-std=gnu99", "-Wno-error=implicit-function-declaration", "-Wno-error=implicit-int",
        "-Wno-error=int-conversion", "-Wno-error=incompatible-pointer-types"]
    r = subprocess.run(cmd + [path, "-o", "-"], cwd=ROOT, capture_output=True, text=True, errors="replace")
    defs, calls = {}, []
    if r.returncode: return path, defs, calls
    for line in r.stdout.splitlines():
        if line.startswith("define "):
            m = re.search(r"@([A-Za-z_][\w.$]*)\(", line)
            if m: defs[lc.unsuffix(m.group(1))] = tuple(cls(a) for a in split_args(line, m.end() - 1))
        elif " call " in line or line.lstrip().startswith("call "):
            m = re.search(r"\bcall\b[^@]*?@([A-Za-z_][\w.$]*)\(", line)
            if m:
                knr = "(...)" in line[:m.start(1)]
                calls.append((lc.unsuffix(m.group(1)), tuple(cls(a) for a in split_args(line, m.end() - 1)), knr))
    return path, defs, calls

files = []
for d in sys.argv[1:] or ["game", "sound", "ui", "util", "resource", "triforce"]:
    for base, _, names in os.walk(os.path.join(ROOT, "src", d)):
        files += [os.path.relpath(os.path.join(base, n), ROOT) for n in names if n.endswith((".c", ".cpp"))]
with concurrent.futures.ThreadPoolExecutor(max_workers=os.cpu_count()) as ex:
    res = list(ex.map(scan, sorted(files)))
defs = {}
for path, d, _ in res:
    for n, k in d.items():
        if not n.startswith("_Z"): defs[n] = (k, path)
rows = collections.OrderedDict()
for path, _, calls in res:
    for n, k, knr in calls:
        if n not in defs: continue
        want = defs[n][0]
        if '...' in want: continue
        kinds = set()
        if ('byval' in k) != ('byval' in want) or (len(k) == len(want) and any((a == 'byval') != (b == 'byval') for a, b in zip(k, want))): kinds.add('byval')
        if len(k) == len(want):
            for a, b in zip(k, want):
                if {a, b} == {'float', 'double'}: kinds.add('fltdbl')
                elif (a in ('float', 'double')) != (b in ('float', 'double')): kinds.add('intflt')
                elif (a == 'i64') != (b == 'i64'): kinds.add('i64')
        elif knr and ('double' in k) and ('float' in want): kinds.add('fltdbl')
        if ('sret' in k) != ('sret' in want): kinds.add('sret')
        for kind in kinds:
            rows.setdefault((kind, n, path, k, want, defs[n][1]), 0)
            rows[(kind, n, path, k, want, defs[n][1])] += 1
for (kind, n, path, k, want, where), t in sorted(rows.items()):
    print(f"{kind}\t{n}\t{path}\tcall({','.join(k)})\tdef({','.join(want)})\t{where}")
