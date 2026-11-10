#!/usr/bin/env python3
"""Find prototypes whose return type class differs from the definition.

    python3 tools/port_abi/return_class.py        # float/double on one side only
    python3 tools/port_abi/return_class.py -a     # also void against integer/pointer

On PowerPC a float result in f1 is ignored by a caller that thinks the
function is void, and an integer caller reads r3.  On 32-bit x86 a float
result comes back on the x87 stack: a caller that does not pop it fills the
stack (NaN in later loads), and a caller that pops a result that was never
pushed reads NaN.  Classes: F (float, double), V (void), I (everything else).

Compares every non-member definition in src/ with the prototypes of the same
name in src/ and include/game, also the `name_pN` aliases of the merged units.
Names with no C definition are reported when their prototypes disagree among
themselves.  Prototypes inside class bodies and in src/game/autodata (address-only
uses) are not read.  Text based: typedefs of float other than f32 / f64 are not known.
"""
import glob, re, sys

KW = {'if', 'while', 'for', 'switch', 'return', 'sizeof', 'else', 'goto', 'case', 'new', 'delete', 'typedef', 'do', 'throw', 'defined'}
FL = {'float', 'double', 'f32', 'f64', 'long double'}


def strip(s):
    s = re.sub(r'/\*.*?\*/', lambda m: re.sub(r'[^\n]', ' ', m.group(0)), s, flags=re.S)
    s = re.sub(r'//[^\n]*', '', s)
    return re.sub(r'"(?:\\.|[^"\\\n])*"', '""', s)


def cls(t):
    t = re.sub(r'\b(?:extern|static|inline|const|volatile|virtual|asm|__declspec\([^)]*\)|__attribute__\(\([^)]*\)\))\b', ' ', t)
    t = re.sub(r'""', ' ', t)
    t = re.sub(r'\b(?:DECL_\w+|WEAKFUNC|SECTION_\w+)\b', ' ', t)
    t = re.sub(r'_p\d+\b', '', ' '.join(t.split()))
    if not t or t.split()[0] in KW: return None
    if '*' in t or '&' in t: return 'I'
    if t == 'void': return 'V'
    return 'F' if t in FL else 'I'


HEAD = r'^[ \t]*((?:[A-Za-z_][\w]*|""|\*|&|__declspec\([^)]*\))(?:[ \t\*&]+(?:[A-Za-z_]\w*|""|__declspec\([^)]*\)))*[ \t\*&]+)'
DEF = re.compile(HEAD + r'([A-Za-z_]\w*)\s*\(([^;{}]*?)\)\s*(?:const\s*)?\{', re.M)
PROTO = re.compile(HEAD + r'([A-Za-z_]\w*)\s*\(([^;{}=]*?)\)\s*;', re.M)

files = [f for pat in ('src/**/*.c', 'src/**/*.cpp', 'src/**/*.inc', 'src/**/*.h', 'include/game/**/*.h', 'include/**/*.h') for f in glob.glob(pat, recursive=True)]
files = sorted(set(files))
defs, protos = {}, {}
perfile = {}
for f in files:
    s = strip(open(f, encoding='utf-8', errors='replace').read())
    for rx, tab in ((DEF, defs), (PROTO, protos)):
        for m in rx.finditer(s):
            name = m.group(2)
            if name in KW: continue
            c = cls(m.group(1))
            if c is None: continue
            if tab is defs and re.search(r'\bstatic\b', m.group(1)): continue
            if tab is protos:
                if f.startswith('src/game/autodata/'): continue          # address-only uses in data tables
                if m.group(0)[0] in ' \t' and not re.match(r'\s*extern\b', m.group(0)): continue   # class members, continuation lines
                k = m.start() - 1
                while k >= 0 and s[k] in ' \t\n\r': k -= 1
                if k >= 0 and s[k] not in ';}{)' and not s[max(0, s.rfind('\n', 0, k)):k + 1].lstrip().startswith('#'): continue
            base = re.sub(r'_p\d+$', '', name)
            line = s.count('\n', 0, m.start(2)) + 1
            tab.setdefault(base, {}).setdefault(c, []).append('%s:%d' % (f, line))
            if tab is protos: perfile.setdefault((base, f), set()).add(c)
            if tab is protos and base != name and re.search(r'\bstatic\b', m.group(1)):
                tab[base][c].pop()

show_all = '-a' in sys.argv
n = 0
for name in sorted(set(defs) | set(protos)):
    d = defs.get(name, {})
    p = {c: v for c, v in protos.get(name, {}).items() if v}
    if len(d) > 1: continue                      # same name defined twice with different classes: separate statics
    if d:
        dc = next(iter(d))
        # a file that also declares the name correctly: the other declaration is the
        # `extern void name();` list of an inline-asm block (MWCC only)
        bad = {c: [w for w in v if dc not in perfile.get((name, w.rsplit(':', 1)[0]), ())] for c, v in p.items() if c != dc}
        bad = {c: v for c, v in bad.items() if v}
        if not show_all: bad = {c: v for c, v in bad.items() if 'F' in (c, dc)}
        if not bad: continue
        n += 1
        print('%s: defined %s in %s' % (name, dc, d[dc][0]))
    else:
        p = {c: [w for w in v if len(perfile.get((name, w.rsplit(':', 1)[0]), ())) < 2] for c, v in p.items()}
        p = {c: v for c, v in p.items() if v}
        if len(p) < 2 or (not show_all and 'F' not in p): continue
        n += 1
        bad = p
        print('%s: no C definition, prototypes disagree' % name)
    for c in sorted(bad):
        for w in bad[c][:6]: print('    declared %s at %s' % (c, w))
        if len(bad[c]) > 6: print('    ... %d more' % (len(bad[c]) - 6))
print('%d names' % n)
