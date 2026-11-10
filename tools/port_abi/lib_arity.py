#!/usr/bin/env python3
"""Calls from game code to library functions (HSD, SDK, MSL, MusyX ...) that
pass fewer arguments than the library definition takes.

mkgp2-pc port/tools/arity_census.py compares calls with definitions it can
compile; the library directories are outside its reach, so a call such as
`GetCourseDataPtr(); x = HSD_LObjLoadDesc();` (argument left in r3) is not
seen there. This is a text scan: definitions are read from the library
sources, calls from src/game, src/ui, src/sound and src/triforce.

usage: python3 tools/port_abi/lib_arity.py
"""
import os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
LIB = ['src/sysdolphin', 'src/dolphin', 'src/MSL_C', 'src/Runtime.PPCEABI.H', 'src/musyx', 'src/thp',
       'src/zlib', 'src/util', 'src/resource', 'src/init', 'src/odemuexi2', 'src/TRK_MINNOW_DOLPHIN']
USE = ['src/game', 'src/ui', 'src/sound', 'src/triforce']
DEFN = re.compile(r'^(?!\s)(?:static\s+|inline\s+|extern\s+)*[A-Za-z_][\w \t\*]*?\b([A-Za-z_]\w*)\s*\(([^;{}()]*(?:\([^()]*\)[^;{}()]*)*)\)\s*\{', re.M)
KEYWORDS = {'if', 'while', 'for', 'switch', 'return', 'sizeof'}


def strip(s):
    s = re.sub(r'/\*.*?\*/', lambda m: re.sub(r'[^\n]', ' ', m.group(0)), s, flags=re.S)
    s = re.sub(r'//[^\n]*', '', s)
    return re.sub(r'"(?:\\.|[^"\\\n])*"', '""', s)


def split(a):
    out, d, cur = [], 0, ''
    for c in a:
        if c in '([{': d += 1
        if c in ')]}': d -= 1
        if c == ',' and d == 0: out.append(cur); cur = ''
        else: cur += c
    out.append(cur)
    return [x.strip() for x in out]


def nparams(p):
    p = p.strip()
    if p in ('', 'void'): return 0
    if '...' in p: return None
    return len(split(p))


def files(dirs):
    for d in dirs:
        for dp, _, ff in os.walk(os.path.join(ROOT, d)):
            for f in sorted(ff):
                if f.endswith(('.c', '.cpp', '.inc')): yield os.path.join(dp, f)


def main():
    defs = {}
    for f in files(LIB):
        s = strip(open(f, encoding='utf-8', errors='replace').read())
        for m in DEFN.finditer(s):
            if 'static' in m.group(0).split('(')[0]: continue
            n = nparams(m.group(2))
            if n: defs[m.group(1)] = (n, os.path.relpath(f, ROOT))
    call = re.compile(r'\b(' + '|'.join(sorted(map(re.escape, defs))) + r')\s*\(')
    found = 0
    for f in files(USE):
        s = strip(open(f, encoding='utf-8', errors='replace').read())
        local = {m.group(1) for m in DEFN.finditer(s)}
        for m in call.finditer(s):
            name = m.group(1)
            if name in local: continue
            line_start = s.rfind('\n', 0, m.start()) + 1
            head = s[line_start:m.start()]
            i, d = m.end() - 1, 0
            j = i
            while j < len(s):
                if s[j] == '(': d += 1
                elif s[j] == ')':
                    d -= 1
                    if d == 0: break
                j += 1
            args = s[i + 1:j]
            # a prototype: starts at column 0 or is preceded only by a type
            if re.match(r'^\s*(?:extern\b|typedef\b|[A-Za-z_][\w \t\*]*[\w\*]\s+\**$)', head) and '=' not in head and 'return' not in head:
                continue
            if 'REG_ARGS' in args: continue
            n = 0 if not args.strip() else len(split(args))
            want = defs[name][0]
            if n < want:
                found += 1
                print('%s:%d: %s called with %d, defined with %d in %s' % (
                    os.path.relpath(f, ROOT), s.count('\n', 0, m.start()) + 1, name, n, want, defs[name][1]))
    print('# %d calls' % found)


if __name__ == '__main__':
    main()
