#!/usr/bin/env python3
"""List data defined as an array of words that some reader declares or casts to another type.

    python3 tools/port_abi/word_readers.py [-a]

For each `void *x[]`, `unsigned int x[]`, `int x[]` definition with values:
other declarations of x (`extern T x[]`) and casts applied to x
(`(T *)x`, `(T *)&x`, `(*(T (*)[])&x)`) whose T is not a word type.  A reader
that takes bytes or 16-bit halves of such a table sees them in the wrong
order on a little-endian machine; the table should be defined with the
reader's type (word_rows.py, word_bytes.py, track_keys.py).  Tables whose
values are all zero or all addresses are left out unless -a is given.
"""
import glob, re, sys
from collections import defaultdict

WORD = {'void *', 'unsigned int', 'int', 'u32', 's32', 'unk32', 'unsigned long', 'long', 'float', 'f32', 'void', 'const void *', 'char *', 'const char *'}
DEF = re.compile(r'^((?:extern "C" |extern |static |const )*)(void \*|const void \*(?:const)?|unsigned int|int|u32|s32|unk32) ?(\w+)((?:\[[^\]]*\])+) = \{', re.M)
files = sorted(glob.glob('src/**/*.c', recursive=True) + glob.glob('src/**/*.cpp', recursive=True) + glob.glob('src/**/*.inc', recursive=True) + glob.glob('include/**/*.h', recursive=True))
text = {f: open(f, encoding='utf-8', errors='replace').read() for f in files}
defs = {}
for f, s in text.items():
    for m in DEF.finditer(s):
        d, j = 0, m.end() - 1
        for j in range(m.end() - 1, len(s)):
            if s[j] == '{': d += 1
            elif s[j] == '}':
                d -= 1
                if d == 0: break
        body = s[m.end():j]
        nums = [int(x, 16) for x in re.findall(r'(?<![\w.])0[xX]([0-9A-Fa-f]+)\b', body)]
        if '-a' not in sys.argv and not any(0 < v < 0x80000000 and not 0x30000000 <= v < 0x50000000 or 0xD0000000 <= v for v in nums): continue
        defs[m.group(3)] = (f, s.count('\n', 0, m.start()) + 1, m.group(2))
ev = defaultdict(set)
ID = re.compile(r'\b(' + '|'.join(sorted(map(re.escape, defs), key=len, reverse=True)) + r')\b') if defs else None
for f, s in text.items():
    for m in ID.finditer(s):
        n = m.group(1)
        ls = s.rfind('\n', 0, m.start()) + 1
        pre = s[ls:m.start()]
        d = re.match(r'\s*(?:extern "C" |extern |static |const )*([\w ]+?\**)\s*$', pre)
        after = s[m.end():m.end() + 2]
        if d and after[:1] in '[;' and 'extern' in pre:
            t = d.group(1).replace('const ', '').strip()
            if t and t not in WORD and not t.endswith('*'): ev[n].add('declared %s (%s)' % (t, f))
            continue
        c = re.search(r'\(\*?\(?\s*(?:const\s+)?((?:unsigned |signed |struct )?\w+)\s*(?:\(\*\)(?:\[[^\]]*\])+|\*)\s*\)\s*\(?\s*(?:\(\s*(?:const\s+)?(?:unsigned\s+)?char\s*\*\s*\)\s*)?&?\s*$', pre)
        if c:
            t = c.group(1)
            if t not in WORD and t not in ('const', 'unsigned'): ev[n].add('cast to %s (%s)' % (t, f))
for n in sorted(ev, key=lambda n: defs[n][:2]):
    f, ln, t = defs[n]
    print('%s:%d: %s%s: %s' % (f, ln, t if t.endswith('*') else t + ' ', n, '; '.join(sorted(ev[n]))[:200]))
print('%d of %d word tables with values have a reader of another type' % (len(ev), len(defs)))
