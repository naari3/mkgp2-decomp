#!/usr/bin/env python3
"""Find initialized data whose definition uses a narrower element than its users read.

    python3 tools/port_abi/data_width.py        # suspects
    python3 tools/port_abi/data_width.py -v     # also the users whose type is a struct
    python3 tools/port_abi/data_width.py --content   # also byte arrays whose bytes look like big-endian words

An object defined as bytes (or shorts) keeps the console's byte order on a
little-endian host; a user that reads it as short / int / float then gets
swapped values.  For every definition in src/ whose element type is 1 or 2
bytes wide and whose initializer is not a string literal or all zero, this
lists the `extern` declarations and pointer casts of the same name (also
`name_pN`, the per-piece alias used in concatenated units) whose element type
is wider.  A user whose type is a struct or typedef name is only listed with
-v unless the struct is known to hold nothing but bytes.  Text based.
"""
import glob, re, sys

W = {'char': 1, 'unsigned char': 1, 'signed char': 1, 'u8': 1, 's8': 1, 'unk8': 1, 'BOOL8': 1, 'bool': 1, 'GXColor': 1,
     'short': 2, 'unsigned short': 2, 'signed short': 2, 'u16': 2, 's16': 2, 'unk16': 2, 'wchar_t': 2,
     'int': 4, 'unsigned int': 4, 'unsigned': 4, 'signed int': 4, 'long': 4, 'unsigned long': 4, 'u32': 4, 's32': 4,
     'unk32': 4, 'float': 4, 'f32': 4, 'double': 8, 'f64': 8, 'long long': 8, 'unsigned long long': 8, 'u64': 8, 's64': 8,
     'size_t': 4, 'BOOL': 4}
QUAL = r'(?:const|volatile|static|extern|__declspec\([^)]*\))'


def norm(t):
    t = re.sub(r'\b%s\b' % QUAL, ' ', t)
    return ' '.join(t.split())


def strip(s):
    s = re.sub(r'/\*.*?\*/', ' ', s, flags=re.S)
    return re.sub(r'//[^\n]*', '', s)


files = [f for pat in ('src/**/*.c', 'src/**/*.cpp', 'src/**/*.inc', 'include/game/**/*.h') for f in glob.glob(pat, recursive=True)]
text = {f: strip(open(f, encoding='utf-8', errors='replace').read()) for f in files}

DEFN = re.compile(r'^((?:%s\s+)*(?:unsigned\s+|signed\s+)?[A-Za-z_]\w*)\s+([A-Za-z_]\w*)\s*((?:\[[^\]]*\]\s*)*)=\s*([^;]*);' % QUAL, re.M)
defs = {}
bytedefs = {}
for f, s in text.items():
    if not f.startswith('src/'): continue
    for m in DEFN.finditer(s):
        t = norm(m.group(1))
        if W.get(t, 9) > 2: continue
        if re.match(r'\s*static\b', m.group(0)): continue
        init = m.group(4).strip()
        if init.startswith('"') or (init.startswith('{') and init[1:].lstrip().startswith('"')): continue
        vals = re.findall(r'-?(?:0[xX][0-9A-Fa-f]+|\d+)', init)
        if not any(int(v, 0) for v in vals): continue
        if W[t] == 1 and len(vals) < 2: continue
        # text: every byte printable or NUL / CR / LF / Shift-JIS lead bytes -> skipped when it looks like a string pool
        defs[m.group(2)] = (t, f, len(vals))
        if W[t] == 1 and len(vals) >= 4: bytedefs[m.group(2)] = (f, [int(v, 0) & 0xFF for v in vals])

names = '|'.join(sorted(map(re.escape, defs), key=len, reverse=True))
USE_EXT = re.compile(r'\bextern\s+(?:"C"\s+)?([^;{}()=]*?[\s\*])((?:%s))(?:_p\d+)?\s*((?:\[[^\]]*\]\s*)*)[;,]' % names)
USE_CAST = re.compile(r'\(\s*((?:const\s+|volatile\s+)*(?:struct\s+)?(?:unsigned\s+|signed\s+)?[A-Za-z_]\w*)\s*\*+\s*\)\s*\(?\s*&?\s*((?:%s))(?:_p\d+)?\b' % names)
hits = {}
for f, s in text.items():
    for rx, kind in ((USE_EXT, 'extern'), (USE_CAST, 'cast')):
        for m in rx.finditer(s):
            name = m.group(2)
            dt, df, _ = defs[name]
            if f == df: continue
            ut = norm(m.group(1)).replace('struct ', '').rstrip('* ').strip()
            if '*' in m.group(1) and kind == 'extern': uw = 4          # an array of pointers
            else: uw = W.get(ut)
            if uw is None:
                if '-v' in sys.argv: hits.setdefault(name, set()).add('%s: %s as %s (%s, width unknown)' % (f, kind, ut, kind))
                continue
            if uw > W[dt]: hits.setdefault(name, set()).add('%s: %s as %s' % (f, kind, ut))
for name in sorted(hits):
    dt, df, n = defs[name]
    print('%s: %s[%d] in %s' % (name, dt, n, df))
    for h in sorted(hits[name]): print('    ' + h)
if '--content' in sys.argv:
    # byte arrays whose content looks like big-endian words rather than text
    n = 0
    for name in sorted(bytedefs, key=lambda k: (bytedefs[k][0], k)):
        f, b = bytedefs[name]
        if name in hits: continue
        words = [b[i:i + 4] for i in range(0, len(b) - 3, 4)]
        small = sum(1 for w in words if w[0] == 0 and w[1] == 0 and (w[2] or w[3]))
        flt = sum(1 for w in words if w[0] in (0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0xBD, 0xBE, 0xBF, 0xC0, 0xC1, 0xC2, 0xC3) and w[3] == 0 and (w[2] == 0 or w[1] & 0x0F == 0))
        texty = sum(1 for x in b if 0x20 <= x < 0x7F or x in (0, 9, 10, 13) or x >= 0x81) == len(b) and small == 0
        if (small + flt) * 2 >= len(words) and not texty:
            n += 1
            print('%s: %d bytes in %s: %d small-integer words, %d float-like words of %d' % (name, len(b), f, small, flt, len(words)))
    print('%d byte arrays look like words' % n)
print('%d of %d narrow definitions have a wider user' % (len(hits), len(defs)))
