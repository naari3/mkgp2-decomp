#!/usr/bin/env python3
"""Find prototypes whose float/integer parameter order differs from the
function's definition or library header.

    python3 tools/port_abi/arg_class_order.py            # library functions (SDK, MSL, HSD, MusyX)
    python3 tools/port_abi/arg_class_order.py --all      # also functions defined in src/game
    python3 tools/port_abi/arg_class_order.py -v         # also differing parameter counts

PowerPC numbers float and integer arguments separately, so
`f(mtx, pm, vp, sx, sy, sz, x, y, z)` reaches `f(x, y, z, mtx, pm, vp, ...)`
with the same registers.  A compiler with one argument list needs the real
order.  For each function the reference is its non-member definition, or,
when no C definition is found, its prototype in a library header
(include/dolphin, include/libc, include/musyx, libs/).  Every other prototype
of the name (also `name_pN`) is compared by the sequence of parameter classes:
F = float / double by value, I = everything else.  Text based; variadic and
unprototyped `()` declarations are skipped.
"""
import glob, os, re, sys

FL = {'float', 'double', 'f32', 'f64', 'long double'}
KW = {'if', 'while', 'for', 'switch', 'return', 'sizeof', 'else', 'goto', 'case', 'new', 'delete', 'typedef', 'do', 'throw', 'defined'}
LIBDIRS = ('src/dolphin/', 'src/MSL', 'src/Runtime', 'src/sysdolphin/', 'src/musyx/', 'src/TRK', 'src/amcstubs/', 'src/OdemuExi2/', 'src/odenotstub/',
           'include/dolphin/', 'include/libc/', 'include/musyx/', 'include/musyx_libc/', 'include/sysdolphin/', 'libs/')


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


def classes(params):
    p = params.strip()
    if p == '' : return None            # unprototyped (C) / unknown
    if p == 'void': return ''
    if '...' in p: return None
    out = ''
    for a in split_args(p):
        a = re.sub(r'\b(?:const|volatile|register|__restrict|restrict)\b', ' ', a)
        if '*' in a or '&' in a or '[' in a or '(' in a: out += 'I'; continue
        words = [re.sub(r'_p\d+$', '', w) for w in a.split()]
        if not words: return None
        t = words[0] if words[0] not in ('long',) else ' '.join(words[:2])
        out += 'F' if (words[0] in FL or t in FL) else 'I'
    return out


HEAD = r'^[ \t]*((?:[A-Za-z_][\w]*|""|\*|&)(?:[ \t\*&]+(?:[A-Za-z_]\w*|""))*[ \t\*&]+)'
DEF = re.compile(HEAD + r'([A-Za-z_]\w*)\s*\(([^;{}]*?)\)\s*\{', re.M)
PROTO = re.compile(HEAD + r'([A-Za-z_]\w*)\s*\(([^;{}=]*?)\)\s*;', re.M)

pats = ['src/**/*.c', 'src/**/*.cpp', 'src/**/*.inc', 'src/**/*.h', 'include/**/*.h', 'libs/**/*.h']
files = sorted(set(f for pat in pats for f in glob.glob(pat, recursive=True) if os.path.isfile(f)))
defs, protos = {}, {}
for f in files:
    try: s = strip(open(f, encoding='utf-8', errors='replace').read())
    except OSError: continue
    lib = f.startswith(LIBDIRS)
    for rx, isdef in ((DEF, True), (PROTO, False)):
        for m in rx.finditer(s):
            name = m.group(2)
            if name in KW or m.group(1).split()[0] in KW: continue
            if not isdef:
                if m.group(0)[0] in ' \t' and not re.match(r'\s*extern\b', m.group(0)): continue
                k = m.start() - 1
                while k >= 0 and s[k] in ' \t\n\r': k -= 1
                if k >= 0 and s[k] not in ';}{)' and not s[max(0, s.rfind('\n', 0, k)):k + 1].lstrip().startswith('#'): continue
            c = classes(m.group(3))
            if c is None: continue
            base = re.sub(r'_p\d+$', '', name)
            ent = (c, '%s:%d' % (f, s.count('\n', 0, m.start(2)) + 1), ' '.join(m.group(3).split()), lib)
            if isdef:
                if not re.search(r'\bstatic\b', m.group(1)): defs.setdefault(base, []).append(ent)
            else:
                protos.setdefault(base, []).append(ent)

want_all = '--all' in sys.argv
verbose = '-v' in sys.argv
n = places = 0
for name in sorted(protos):
    ref = None
    d = defs.get(name, [])
    if d:
        if len({e[0] for e in d}) > 1: continue          # several definitions: per-unit statics
        ref = d[0]
    else:
        libp = [e for e in protos[name] if e[3]]
        if not libp or len({e[0] for e in libp}) > 1: continue
        ref = libp[0]
    if not ref[3] and not want_all: continue
    bad = []
    for e in protos[name]:
        if e[0] == ref[0] or e[1] == ref[1]: continue
        if len(e[0]) != len(ref[0]):
            if verbose: bad.append(e)
            continue
        bad.append(e)
    if not bad: continue
    n += 1; places += len(bad)
    print('%s: %s (%s) at %s' % (name, ref[0] or 'void', ref[2], ref[1]))
    for e in bad: print('    %s (%s) at %s' % (e[0] or 'void', e[2], e[1]))
print('%d functions, %d prototypes' % (n, places))
