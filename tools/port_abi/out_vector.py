#!/usr/bin/env python3
"""Find calls that pass the address of a scalar local to a parameter the
callee indexes beyond [0] (the callee writes or reads more than one element).

    python3 tools/port_abi/out_vector.py        # list suspects
    python3 tools/port_abi/out_vector.py -v     # also list the indexed parameters

Text based: definitions are found by regex, bodies by brace matching.  A
callee parameter counts when its body contains `p[N]` with N >= 1 or
`*(p + N)`.  A call counts when the argument in that position is `&name` and
`name` is declared in the calling file as a plain scalar (not an array, not a
struct).  `Foo_Reordered` wrappers (docs/notes/port_abi.md) are followed.
"""
import glob, re, sys

SCALAR = r'(?:float|double|f32|f64|int|long|short|char|s8|u8|s16|u16|s32|u32|unsigned(?:\s+(?:int|long|short|char))?|BOOL|bool)'
DEF = re.compile(r'^[A-Za-z_][\w \t\*]*?[ \*]([A-Za-z_]\w*)\s*\(([^;{}()]*)\)\s*\{', re.M)
KW = {'if', 'while', 'for', 'switch', 'return', 'sizeof'}


def strip(s):
    s = re.sub(r'/\*.*?\*/', lambda m: re.sub(r'[^\n]', ' ', m.group(0)), s, flags=re.S)
    s = re.sub(r'//[^\n]*', '', s)
    return re.sub(r'"(?:\\.|[^"\\\n])*"', '""', s)


def body_at(s, i):
    d = 0
    for j in range(i, len(s)):
        if s[j] == '{': d += 1
        elif s[j] == '}':
            d -= 1
            if d == 0: return s[i:j + 1]
    return s[i:]


def split_args(a):
    out, d, cur = [], 0, ''
    for c in a:
        if c in '([{': d += 1
        elif c in ')]}': d -= 1
        if c == ',' and d == 0:
            out.append(cur.strip()); cur = ''
        else: cur += c
    if cur.strip(): out.append(cur.strip())
    return out


def call_args(s, i):
    d = 0
    for j in range(i, len(s)):
        if s[j] == '(': d += 1
        elif s[j] == ')':
            d -= 1
            if d == 0: return split_args(s[i + 1:j])
    return []


files = sorted(glob.glob('src/game/**/*.c', recursive=True) + glob.glob('src/game/**/*.cpp', recursive=True))
heads = sorted(glob.glob('include/game/**/*.h', recursive=True))
raw = {f: open(f, encoding='utf-8', errors='replace').read() for f in files + heads}
text = {f: strip(raw[f]) for f in raw}

indexed = {}   # fn -> {pos: max index}
for f in files:
    s = text[f]
    for m in DEF.finditer(s):
        name = m.group(1)
        if name in KW: continue
        body = body_at(s, m.end() - 1)
        for pos, p in enumerate(split_args(m.group(2))):
            pm = re.match(r'.*\*\s*(?:const\s+)?([A-Za-z_]\w*)$', p, re.S)
            if not pm: continue
            if re.match(r'\s*(?:const\s+)?(?:void|char|struct\b.*|[A-Z]\w*)\s*\*', p) and not re.match(r'\s*(?:const\s+)?(?:Vec\w*|f32|BOOL)\s*\*', p):
                pass  # still count: indexing decides
            v = pm.group(1)
            if re.search(r'\b%s\s*=[^=]' % v, body): continue  # reassigned: a cursor
            mx = 0
            for im in re.finditer(r'(?<![\w.>])%s\s*\[\s*(\d+)\s*\]' % v, body): mx = max(mx, int(im.group(1)))
            for im in re.finditer(r'\*\s*\(\s*%s\s*\+\s*(\d+)\s*\)' % v, body): mx = max(mx, int(im.group(1)))
            for im in re.finditer(r'\(\s*\(\s*(?:float|f32|int|s32|u32|long|unsigned int)\s*\*\s*\)\s*%s\s*\)\s*\[\s*(\d+)\s*\]' % v, body): mx = max(mx, int(im.group(1)))
            for im in re.finditer(r'\(\s*(?:unsigned\s+)?(?:char|u8|s8)\s*\*\s*\)\s*%s\s*\+\s*(0x[0-9A-Fa-f]+|\d+)' % v, body): mx = max(mx, int(im.group(1), 0) // 4)
            if mx: indexed.setdefault(name, {})[pos] = max(mx, indexed.get(name, {}).get(pos, 0))

# Foo_Reordered(a0, ...) { return Foo(a8, a9, a0, ...); }
reorder = {}
for f, s in text.items():
    for m in re.finditer(r'(\w+)_Reordered\s*\(([^)]*)\)\s*\{\s*(?:return\s+)?(\w+)\s*\(([^)]*)\)', s):
        if m.group(1) != m.group(3): continue
        wp = [re.search(r'(\w+)$', a).group(1) for a in split_args(m.group(2))]
        reorder.setdefault(f, {})[m.group(1)] = [wp.index(a) if a in wp else None for a in split_args(m.group(4))]

if '-v' in sys.argv:
    for n in sorted(indexed): print(n, indexed[n])

by_base = {}
for h in heads: by_base.setdefault(h.split('/')[-1], []).append(h)
hits = 0
for f in files:
    s = text[f]
    incs = [h for n in re.findall(r'#\s*include\s*"(?:[^"]*/)?([^"/]+)"', raw[f]) for h in by_base.get(n, [])]
    lines = s.split('\n')
    for m in re.finditer(r'(?<![\w.>:])([A-Za-z_]\w*)\s*\(', s):
            name = m.group(1)
            if name not in indexed: continue
            poss = indexed[name]
            line = s.count('\n', 0, m.start()) + 1
            args = call_args(s, m.end() - 1)
            mp = None
            for src in [f] + incs:
                if name in reorder.get(src, {}): mp = reorder[src][name]
            for pos, mx in poss.items():
                wpos = mp[pos] if mp and pos < len(mp) else pos
                if wpos is None or wpos >= len(args): continue
                am = re.fullmatch(r'(?:\([\w \*]+\))?\s*&\s*([A-Za-z_]\w*)', args[wpos])
                if not am: continue
                v = am.group(1)
                dm = None
                for k in range(line - 1, max(line - 600, -1), -1):
                    dm = re.match(r'\s*(?:static\s+|const\s+|volatile\s+)*(%s)\s[^;()]*?\b%s\s*([\[=,;])' % (SCALAR, v), lines[k]) or \
                         re.match(r'\s*(?:struct\s+)?([A-Za-z_]\w*)\s[^;()]*?\b%s\s*([\[=,;])' % v, lines[k])
                    if dm: break
                if not dm or dm.group(2) == '[' or not re.fullmatch(SCALAR, dm.group(1)): continue
                print('%s:%d: %s(arg %d = &%s, %s) callee uses [%d]' % (f, line, name, wpos + 1, v, dm.group(1), mx))
                hits += 1
for f in files:
    s = text[f]; lines = s.split('\n')
    for m in re.finditer(r'\(\s*(?:struct\s+)?([A-Z]\w*)\s*\*\s*\)\s*&\s*([A-Za-z_]\w*)\s*[,)]', s):
        if re.fullmatch(SCALAR, m.group(1)): continue
        line = s.count('\n', 0, m.start()) + 1
        v = m.group(2); dm = None
        for k in range(line - 1, max(line - 600, -1), -1):
            dm = re.match(r'\s*(?:static\s+|const\s+|volatile\s+)*(?:struct\s+)?([A-Za-z_]\w*(?:\s+(?:int|long|short|char))?)\s[^;()]*?\b%s\s*([\[=,;])' % v, lines[k])
            if dm: break
        if not dm or dm.group(2) == '[' or not re.fullmatch(SCALAR, dm.group(1)): continue
        print('%s:%d: (%s *)&%s, %s local cast to a struct pointer' % (f, line, m.group(1), v, dm.group(1)))
        hits += 1
print('%d suspect call(s); %d callees index a pointer parameter' % (hits, len(indexed)))
