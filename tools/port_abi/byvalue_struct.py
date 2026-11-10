#!/usr/bin/env python3
"""Find calls and prototypes that pass a struct by value where the definition
takes a pointer or reference (or the reverse).

    python3 tools/port_abi/byvalue_struct.py        # suspects
    python3 tools/port_abi/byvalue_struct.py -v     # every compared cast / prototype count

MWCC passes a struct argument as the address of a copy, so
`((void (*)(void *, Key))f)(l, key)` reaches `void f(List *l, Key *key)` with
the same PowerPC code as a by-value definition would.  A host compiler pushes
the struct's bytes and the callee reads them as a pointer.

Compared with each non-member definition in src/:
  - function-pointer casts applied to the function's name, written inline
    `((R (*)(A, B))name)(...)` or through a typedef of the same file;
  - prototypes of the name (and of its `name_pN` aliases).
A parameter is "by value" when its type is not a pointer, reference, array or
known scalar, and is declared `struct` / `class` / `union` somewhere in the
sources (or is spelled with one of those keywords).  Text based.
"""
import glob, re, sys

SCALAR = set('''void char short int long float double signed unsigned bool BOOL u8 s8 u16 s16 u32 s32 u64 s64 f32 f64
size_t wchar_t unk8 unk16 unk32 GXBool OSTime OSTick'''.split())
KW = {'if', 'while', 'for', 'switch', 'return', 'sizeof', 'else', 'goto', 'case', 'new', 'delete', 'typedef', 'do', 'throw', 'defined'}


def strip(s):
    s = re.sub(r'/\*.*?\*/', lambda m: re.sub(r'[^\n]', ' ', m.group(0)), s, flags=re.S)
    s = re.sub(r'//[^\n]*', '', s)
    return re.sub(r'"(?:\\.|[^"\\\n])*"', '""', s)


def split_args(a):
    out, d, cur = [], 0, ''
    for c in a:
        if c in '([{<': d += 1
        elif c in ')]}>': d -= 1
        if c == ',' and d == 0:
            out.append(cur.strip()); cur = ''
        else: cur += c
    if cur.strip(): out.append(cur.strip())
    return out


files = sorted(set(f for pat in ('src/**/*.c', 'src/**/*.cpp', 'src/**/*.inc', 'include/game/**/*.h') for f in glob.glob(pat, recursive=True)))
text = {f: strip(open(f, encoding='utf-8', errors='replace').read()) for f in files}
aggr = set()
for s in text.values():
    aggr.update(re.findall(r'\b(?:struct|class|union)\s+([A-Za-z_]\w*)\s*(?::[^{;]*)?\{', s))
    aggr.update(re.findall(r'\}\s*([A-Za-z_]\w*)\s*;', s))
arr = set()
for s in text.values():
    arr.update(re.findall(r'typedef\s+[\w \t\*]+?\b([A-Za-z_]\w*)\s*\[', s))      # typedef float Mtx[3][4];
    arr.update(re.findall(r'typedef\s+[\w \t]+?\*\s*([A-Za-z_]\w*)\s*;', s))        # typedef struct X *XPtr;
aggr = {re.sub(r'_p\d+$', '', a) for a in aggr} - SCALAR - arr


def kind(p):
    """'P' pointer/reference/array, 'A' aggregate by value, 'S' scalar, None unknown"""
    p = re.sub(r'\b(?:const|volatile|register|__restrict|restrict)\b', ' ', p).strip()
    if not p or p == 'void' or p == '...': return None
    if '*' in p or '&' in p or '[' in p or '(' in p: return 'P'
    words = [re.sub(r'_p\d+$', '', w) for w in p.split()]
    if words[0] in ('struct', 'class', 'union'): return 'A'
    if all(w in SCALAR for w in words): return 'S'
    if words[0] in SCALAR: return 'S'            # `int flag`
    return 'A' if words[0] in aggr else 'S'


def kinds(params):
    return [kind(p) for p in split_args(params) if p.strip() not in ('', 'void')]


HEAD = r'^[ \t]*((?:[A-Za-z_][\w]*|""|\*|&)(?:[ \t\*&]+(?:[A-Za-z_]\w*|""))*[ \t\*&]+)'
DEF = re.compile(HEAD + r'([A-Za-z_]\w*)\s*\(([^;{}]*?)\)\s*\{', re.M)
PROTO = re.compile(HEAD + r'([A-Za-z_]\w*)\s*\(([^;{}=]*?)\)\s*;', re.M)
FNPTR = r'[\w \t\*]+?\(\s*\*\s*\)\s*\(([^()]*(?:\([^()]*\)[^()]*)*)\)'
CAST_INLINE = re.compile(r'\(\s*\(\s*' + FNPTR + r'\s*\)\s*&?\s*([A-Za-z_]\w*)\s*\)\s*\(')
CAST_NAMED = re.compile(r'\(\s*\(\s*([A-Za-z_]\w*)\s*\)\s*&?\s*([A-Za-z_]\w*)\s*\)\s*\(')
TYPEDEF = re.compile(r'typedef\s+[\w \t\*]+?\(\s*\*\s*([A-Za-z_]\w*)\s*\)\s*\(([^;]*?)\)\s*;')

defs = {}
for f, s in text.items():
    if not f.startswith('src/'): continue
    for m in DEF.finditer(s):
        if m.group(2) in KW or m.group(1).split()[0] in KW or re.search(r'\bstatic\b', m.group(1)): continue
        defs.setdefault(m.group(2), []).append((f, s.count('\n', 0, m.start(2)) + 1, kinds(m.group(3)), ' '.join(m.group(3).split())))


def compare(name, where, how, params):
    out = []
    for df, dl, dk, dp in defs.get(name, []):
        uk = kinds(params)
        for i, (a, b) in enumerate(zip(uk, dk)):
            if {a, b} == {'A', 'P'}:
                out.append('%s: %s of %s passes argument %d %s\n    use:        (%s)\n    definition: (%s) at %s:%d'
                           % (where, how, name, i + 1, 'by value, the definition takes a pointer' if a == 'A' else 'by pointer, the definition takes it by value',
                              ' '.join(params.split()), dp, df, dl))
                break
    return out


hits, seen = [], 0
for f, s in text.items():
    tds = {m.group(1): m.group(2) for m in TYPEDEF.finditer(s)}
    for m in CAST_INLINE.finditer(s):
        name = re.sub(r'_p\d+$', '', m.group(2))
        if name in defs:
            seen += 1; hits += compare(name, '%s:%d' % (f, s.count('\n', 0, m.start()) + 1), 'cast', m.group(1))
    for m in CAST_NAMED.finditer(s):
        name = re.sub(r'_p\d+$', '', m.group(2))
        if m.group(1) in tds and name in defs:
            seen += 1; hits += compare(name, '%s:%d' % (f, s.count('\n', 0, m.start()) + 1), 'cast (%s)' % m.group(1), tds[m.group(1)])
    for m in PROTO.finditer(s):
        name = re.sub(r'_p\d+$', '', m.group(2))
        if name in KW or name not in defs or m.group(1).split()[0] in KW: continue
        if m.group(0)[0] in ' \t' and not re.match(r'\s*extern\b', m.group(0)): continue
        seen += 1; hits += compare(name, '%s:%d' % (f, s.count('\n', 0, m.start(2)) + 1), 'prototype', m.group(3))
for h in sorted(set(hits)): print(h)
print('%d suspects' % len(set(hits)) + (' (%d casts and prototypes compared, %d aggregate type names)' % (seen, len(aggr)) if '-v' in sys.argv else ''))
