#!/usr/bin/env python3
"""Rewrite a table written as an array of words into an array of rows.

    python3 tools/port_abi/word_rows.py FILE SYMBOL ROWTYPE FORMAT

FORMAT has one letter per word of a row:
    p  address or 0 (the cast is dropped)      f  float
    i  int (decimal)   x  unsigned (hex)       h  two 16-bit values
    b  one byte and three padding bytes: `b, { 0, 0, 0 }`
    B  four separate bytes
The definition `void *SYMBOL[n]` / `unsigned int SYMBOL[n]` becomes
`ROWTYPE SYMBOL[n / len(FORMAT)]`; the row type itself is written by hand.
Used for the tables listed in docs/notes/port_abi.md ("Word tables read as
bytes"); the object file must come out unchanged.
"""
import re, struct, sys
sys.path.insert(0, 'tools')
from autodata import fmt_float

f, sym, typ, fmt = sys.argv[1:5]
s = open(f, encoding='utf-8').read()
m = re.search(r'(?:/\* decl:[^\n]*\*/\n)?((?:static |const )*)(?:void \*|unsigned int |int )' + sym + r'\[(\d*)\] = \{(.*?)\n?\};', s, re.S)
if not m: sys.exit('no word-array definition of ' + sym)
items = [re.sub(r'^\(void \*\)\s*', '', x.strip()) for x in m.group(3).split(',') if x.strip()]
if len(items) % len(fmt): sys.exit('%d words do not divide into rows of %d' % (len(items), len(fmt)))


def num(x):
    try: return int(x, 0) & 0xFFFFFFFF
    except ValueError: sys.exit('not a number: ' + x)


rows = []
for i in range(0, len(items), len(fmt)):
    out = []
    for c, x in zip(fmt, items[i:i + len(fmt)]):
        if c == 'p':
            if re.fullmatch(r'0[xX]?0*', x): x = '0'
            elif re.fullmatch(r'0[xX][0-9A-Fa-f]+|\d+', x): sys.exit('number in a pointer column: ' + x)
            out.append(x)
            continue
        v = num(x)
        if c == 'f':
            t = fmt_float(v)
            if t is None: sys.exit('not a float: ' + x)
            out.append(t)
        elif c == 'i': out.append(str(v - (1 << 32) if v >> 31 else v))
        elif c == 'x': out.append('0x%X' % v if v > 9 else str(v))
        elif c == 'h': out += [str(v >> 16), str(v & 0xFFFF)]
        elif c == 'b':
            if v & 0xFFFFFF: sys.exit('padding bytes are not zero: ' + x)
            out.append('%d, { 0, 0, 0 }' % (v >> 24))
        elif c == 'B': out += [str(b) for b in struct.pack('>I', v)]
        else: sys.exit('bad format letter ' + c)
    rows.append('    { ' + ', '.join(out) + ' }')
new = '%s%s %s[%d] = {\n%s\n};' % (m.group(1), typ, sym, len(rows), ',\n'.join(rows))
open(f, 'w').write(s[:m.start()] + new + s[m.end():])
print('%s: %s is %s[%d]' % (f, sym, typ, len(rows)))
