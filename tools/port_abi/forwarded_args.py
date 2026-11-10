#!/usr/bin/env python3
"""Find definitions that take fewer parameters than a prototype of the same
name declares (the callers pass more), and say whether the body hands the
extra registers on.

    python3 tools/port_abi/forwarded_args.py        # the ones that forward
    python3 tools/port_abi/forwarded_args.py -a     # every definition with a wider prototype

MWCC leaves r4.. and f1.. untouched when a function does not name them, so a
wrapper written as `void W(T *self) { self->V(); }` still delivers the
caller's other arguments to V.  A host compiler does not.  "Forwards" means:
the body contains a member or pointer call, or a call that passes fewer
arguments than the callee's definition takes (its widest prototype when
no C definition is found).  Text based; see
docs/notes/port_abi.md.
"""
import glob, re, sys

KW = {'if', 'while', 'for', 'switch', 'return', 'sizeof', 'defined'}
VARIADIC = {'DebugPrintf', 'OSReport', 'OSPanic', 'printf', 'sprintf', 'snprintf', 'sscanf'}


def strip(s):
    s = re.sub(r'/\*.*?\*/', ' ', s, flags=re.S)
    s = re.sub(r'//[^\n]*', '', s)
    return re.sub(r'"(?:\\.|[^"\\\n])*"', '""', s)


def body_at(s, i):
    d = 0
    for j in range(i, len(s)):
        if s[j] == '{': d += 1
        elif s[j] == '}':
            d -= 1
            if d == 0: return s[i:j + 1]
    return s[i:]


def split_args(a):
    out, d, cur = [], 0, ''
    for c in a:
        if c in '([{': d += 1
        elif c in ')]}': d -= 1
        if c == ',' and d == 0:
            out.append(cur.strip()); cur = ''
        else: cur += c
    if cur.strip(): out.append(cur.strip())
    return out


def nparams(p, cxx):
    p = p.strip()
    if p == 'void': return 0
    if p == '': return 0 if cxx else None
    if '...' in p: return None
    return len(split_args(p))


DEF = re.compile(r'^[A-Za-z_][\w \t\*"]*?[ \*]([A-Za-z_]\w*)\s*\(([^;{}]*?)\)\s*\{', re.M)
PROTO = re.compile(r'^[ \t]*(?:extern\s+(?:"C"\s+)?)?[A-Za-z_][\w \t\*]*?[ \*]([A-Za-z_]\w*)\s*\(([^;{}]*?)\)\s*;', re.M)

srcs = glob.glob('src/game/**/*.c', recursive=True) + glob.glob('src/game/**/*.cpp', recursive=True) + glob.glob('src/game/**/*.inc', recursive=True)
heads = glob.glob('include/game/**/*.h', recursive=True)
defs, protos = {}, {}
for f in srcs + heads:
    s = strip(open(f, encoding='utf-8', errors='replace').read())
    cxx = f.endswith('.cpp') or 'cplusplus on' in s
    for m in DEF.finditer(s):
        if m.group(1) in KW or re.match(r'\s*static\b', m.group(0)): continue
        n = nparams(m.group(2), True)
        if n is not None: defs.setdefault(m.group(1), []).append((n, f, body_at(s, m.end() - 1)))
    for m in PROTO.finditer(s):
        if m.group(1) in KW or re.match(r'\s*(?:return|else|typedef)\b', m.group(0)): continue
        n = nparams(m.group(2), cxx)
        if n is not None: protos.setdefault(m.group(1), {}).setdefault(n, f)

arity = {k: max(n for n, _, _ in v) for k, v in defs.items()}
for k, v in protos.items():
    if k not in arity: arity[k] = max(v)  # defined in C++ member syntax or in asm
total = shown = 0
for name in sorted(defs):
    if len(defs[name]) != 1 or name not in protos: continue
    n, f, body = defs[name][0]
    wide = max(protos[name])
    if wide <= n: continue
    total += 1
    why = []
    for c in re.finditer(r'(->|\.)?\s*([A-Za-z_]\w*)\s*\(', body):
        cn = c.group(2)
        if cn in KW or cn in VARIADIC: continue
        d = 0
        for k in range(c.end() - 1, len(body)):
            if body[k] == '(': d += 1
            elif body[k] == ')':
                d -= 1
                if d == 0: break
        na = len(split_args(body[c.end():k]))
        if c.group(1): why.append('%s%s(%d)' % (c.group(1), cn, na))
        elif cn in arity and arity[cn] > na: why.append('%s(%d of %d)' % (cn, na, arity[cn]))
    if re.search(r'\(\s*\*+\s*\(?[\w>\-\.\[\]]+\)?\s*\)\s*\(', body): why.append('(*pointer)(...)')
    if why or '-a' in sys.argv:
        shown += 1
        print('%s: takes %d in %s, declared with %d in %s%s' % (name, n, f, wide, protos[name][wide], ('\n    forwards: ' + ', '.join(sorted(set(why)))) if why else ''))
print('%d definitions have a wider prototype; %d shown' % (total, shown))
