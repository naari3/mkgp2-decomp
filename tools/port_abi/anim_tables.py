#!/usr/bin/env python3
"""Rewrite AnimState descriptions written as `void *x[2n]` into `AnimEntry x[n]`.

    python3 tools/port_abi/anim_tables.py          # list
    python3 tools/port_abi/anim_tables.py --fix    # rewrite

Shape: even elements are 0 or `(void *)0xNN000000` (the type byte and three
padding bytes), odd elements are an address or 0, and the last pair is
`(void *)0xD000000, 0`.  See docs/notes/port_abi.md.
"""
import glob, re, sys

DEF = re.compile(r'^((?:static\s+|const\s+)*)void \*(\w+)\[(\d*)\] = \{([^{}]*)\};', re.M)
fix = '--fix' in sys.argv
n = 0
for f in sorted(glob.glob('src/**/*.c', recursive=True) + glob.glob('src/**/*.cpp', recursive=True) + glob.glob('src/**/*.inc', recursive=True)):
    s = open(f, encoding='utf-8', errors='replace').read()
    def rep(m):
        global n
        items = [x.strip() for x in m.group(4).split(',') if x.strip()]
        if len(items) < 2 or len(items) % 2: return m.group(0)
        rows = []
        for i in range(0, len(items), 2):
            t, d = items[i], items[i + 1]
            tm = re.fullmatch(r'(?:\(void \*\))?\s*(0[xX][0-9A-Fa-f]+|0)', t)
            if not tm: return m.group(0)
            v = int(tm.group(1), 0)
            if v & 0xFFFFFF or (v >> 24) > 0x7F: return m.group(0)
            if not re.fullmatch(r'(?:\(void \*\))?\s*(&?\w+|0[xX]0|0)', d): return m.group(0)
            d = re.sub(r'^\(void \*\)\s*', '', d)
            rows.append((v >> 24, '0' if d in ('0', '0x0', '0X0') else d))
        if rows[-1] != (13, '0') or any(t == 13 for t, _ in rows[:-1]): return m.group(0)
        n += 1
        print('%s: %s (%d entries)' % (f, m.group(2), len(rows)))
        body = ',\n'.join('    { %d, { 0, 0, 0 }, %s }' % r for r in rows)
        return '%sAnimEntry %s[%d] = {\n%s\n};' % (m.group(1), m.group(2), len(rows), body)
    t = DEF.sub(rep, s)
    if fix and t != s:
        if 'game/types/AnimEntry.h' not in t:
            inc = '#include "game/types/AnimEntry.h"\n'
            k = t.find('#include')
            t = inc + t if k < 0 else t[:k] + inc + t[k:]
        open(f, 'w').write(t)
print('%d tables' % n)
