#!/usr/bin/env python3
"""List calls that pass the address of a scalar parameter or scalar local
where the callee's definition (anywhere in the tree; the caller's own extern
is often written to suit the caller) takes a pointer to something else, or an
untyped pointer.

Why: Terrain_GetGroundHeightWithPenetration writes three floats through its
third argument, and two callers passed the address of an int parameter. With
MWCC the extra eight bytes land in unused stack; with another compiler they
overwrite live values (port request 43). The shape to look for is
"&scalar" handed to a pointer parameter of a different type.

Usage: python3 tools/port_abi/param_address.py [src/game]
Heuristic, text based. Review each line by hand.
"""
import os
import re
import sys

SCALAR = r'(?:unsigned |signed )?(?:int|short|char|long|float|double|u8|s8|u16|s16|u32|s32|f32|BOOL)'
FUNC = re.compile(r'^(?:extern "C" )?[A-Za-z_][\w \*]*?\b(\w+)\s*\(([^;{}()]*)\)\s*(?:const\s*)?\{', re.M)
DECL = re.compile(r'\b(\w+)\s*\(([^;{}()]*)\)\s*;')


def params(text):
    out = []
    for p in text.split(','):
        p = p.strip()
        m = re.match(r'^(.*?)(\w+)$', p)
        out.append((m.group(1).strip(), m.group(2)) if m else (p, ''))
    return out


def body_of(s, start):
    depth, i = 1, start
    while i < len(s) and depth:
        depth += {'{': 1, '}': -1}.get(s[i], 0)
        i += 1
    return s[start:i]


def split_args(a):
    out, depth, cur = [], 0, ''
    for c in a:
        if c in '([':
            depth += 1
        elif c in ')]':
            depth -= 1
        if c == ',' and depth == 0:
            out.append(cur.strip())
            cur = ''
        else:
            cur += c
    out.append(cur.strip())
    return out


def main():
    root = sys.argv[1] if len(sys.argv) > 1 else 'src/game'
    hits = 0
    defs = {}
    for d, _, fs in os.walk(root):
        for f in sorted(fs):
            if f.endswith(('.c', '.cpp')):
                t = open(os.path.join(d, f), encoding='utf-8', errors='replace').read()
                for m in FUNC.finditer(t):
                    if 'static' not in m.group(0).split('(')[0]:
                        defs[m.group(1)] = m.group(2).split(',')
    for d, _, fs in os.walk(root):
        for f in sorted(fs):
            if not f.endswith(('.c', '.cpp')):
                continue
            path = os.path.join(d, f)
            s = open(path, encoding='utf-8', errors='replace').read()
            protos = {}
            for m in FUNC.finditer(s):
                protos.setdefault(m.group(1), m.group(2).split(','))
            for k, v in defs.items():
                protos.setdefault(k, v)
            for m in DECL.finditer(s):
                protos.setdefault(m.group(1), m.group(2).split(','))
            for m in FUNC.finditer(s):
                body = body_of(s, m.end())
                scal = {}
                for t, n in params(m.group(2)):
                    if re.fullmatch(SCALAR, t):
                        scal[n] = t
                for lm in re.finditer(r'^\s*(' + SCALAR + r')\s+(\w+)\s*(?:=[^;,]*)?;', body, re.M):
                    scal.setdefault(lm.group(2), lm.group(1))
                for cm in re.finditer(r'\b(\w+)\s*\(', body):
                    callee = cm.group(1)
                    if callee not in protos:
                        continue
                    args = split_args(body_of(body.replace('(', '{').replace(')', '}'), cm.end())[:-1]
                                      .replace('{', '(').replace('}', ')'))
                    for i, a in enumerate(args):
                        am = re.fullmatch(r'&(\w+)', a)
                        if not am or am.group(1) not in scal or i >= len(protos[callee]):
                            continue
                        want = protos[callee][i].strip()
                        have = scal[am.group(1)]
                        base = re.sub(r'\b\w+$', '', want).strip() if not want.endswith('*') else want
                        pointee = base.replace('const', '').replace('*', '').strip()
                        if '*' not in base:
                            continue
                        if pointee in (have, 'void', '') and pointee != 'void':
                            continue
                        if pointee == 'void' or pointee != have:
                            line = s.count('\n', 0, m.end() + cm.start()) + 1
                            print('%s:%d: %s() arg %d: &%s is %s, parameter is "%s"'
                                  % (path, line, callee, i + 1, am.group(1), have, want))
                            hits += 1
    print('%d candidates' % hits)


if __name__ == '__main__':
    main()
