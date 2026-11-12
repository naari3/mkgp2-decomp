#!/usr/bin/env python3
"""List word tables whose values look like bytes packed into the top of a word.

    python3 tools/port_abi/byte_words.py [-v]

A table written as `void *x[]` or `unsigned int x[]` keeps each word in host
order.  A reader that takes single bytes of such a word (a struct with a
`char type; pad[3]` member, say) finds them only on a big-endian machine.
Reported: definitions of word arrays (also brace-nested ones) that contain a
value 0xNN000000 with NN outside the float exponent ranges (0x3x, 0x4x, 0xBx,
0xCx), or 0xNNNN0000 / 0xNNMM00KK shapes with small bytes.  -v prints the
values.  The list is a starting point: each table needs its readers looked at.
"""
import glob, re, sys

DEF = re.compile(r'^((?:static\s+|const\s+|extern\s+)*)(void \*|const void \*|char \*|const char \*|unsigned int|int|u32|s32|unsigned long|long|unk32)\s*(\w+)((?:\[[^\]]*\])+) = \{', re.M)
NUM = re.compile(r'(?<![\w.])(0[xX][0-9A-Fa-f]+)\b')
FLOATTOP = set(range(0x38, 0x50)) | set(range(0xB8, 0xD0))


def body_at(s, i):
    d = 0
    for j in range(i, len(s)):
        if s[j] == '{': d += 1
        elif s[j] == '}':
            d -= 1
            if d == 0: return s[i:j + 1]
    return s[i:]


tot = 0
for f in sorted(glob.glob('src/**/*.c', recursive=True) + glob.glob('src/**/*.cpp', recursive=True) + glob.glob('src/**/*.inc', recursive=True)):
    s = open(f, encoding='utf-8', errors='replace').read()
    for m in DEF.finditer(s):
        b = body_at(s, m.end() - 1)
        vals = [int(x, 16) for x in NUM.findall(b)]
        sus = [v for v in vals if 0 < v <= 0xFFFFFFFF and v & 0xFFFFFF == 0 and (v >> 24) not in FLOATTOP and v != 0x80000000]
        sus += [v for v in vals if v > 0xFFFF and v & 0xFFFF == 0 and v & 0xFF0000 and (v >> 24) < 0x10 and ((v >> 16) & 0xFF) < 0x40]
        if not sus: continue
        tot += 1
        print('%s:%d: %s%s%s: %d of %d values' % (f, s.count('\n', 0, m.start()) + 1, m.group(2), m.group(3), m.group(4), len(sus), len(vals)))
        if '-v' in sys.argv: print('    ' + ' '.join(sorted({'0x%08X' % v for v in sus})[:16]))
print('%d tables' % tot)
