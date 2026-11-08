#!/usr/bin/env python3
"""Emit C definitions for a range of data objects from the dtk asm (build/GNLJ82/asm/*.s),
so a TU can OWN its pool (pool_audit.py "X owns RANGE").

  python3 tools/data2c.py .rodata 0x802E9F80 0x802EAF00 [--force-active] > /tmp/pool.c

Objects are emitted in address order. `gap_*` padding objects are skipped (the compiler's
own alignment recreates them; check main.dol OK). Strings become `const char x[] = "..."`
(octal escapes for non-ASCII, so SJIS bytes survive), all-word objects become
`unsigned int x[n]` or `void *x[n]` when they hold relocations, anything else becomes an
`unsigned char` array. `.obj X, local` -> static. Rodata objects are const.
A pointer to an object defined later in the range gets a forward `extern` declaration
(globals only). Symbols outside the range are listed as needed externs on stderr.
"""
import argparse, glob, os, re, struct, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
HDR = re.compile(r'^# (\.\w+):0x[0-9A-Fa-f]+ \| 0x([0-9A-Fa-f]+) \| size: 0x([0-9A-Fa-f]+)')
OBJ = re.compile(r'^\.obj ("[^"]+"|\S+), (global|local|weak)')


def parse_string(s):
    out, i = bytearray(), 0
    while i < len(s):
        c = s[i]
        if c != '\\':
            out += c.encode('latin-1', 'replace') if ord(c) < 256 else c.encode('utf-8'); i += 1; continue
        n = s[i + 1]
        if n == 'x':
            j = i + 2
            while j < len(s) and s[j] in '0123456789abcdefABCDEF' and j < i + 4: j += 1
            out.append(int(s[i + 2:j], 16)); i = j; continue
        if n in '01234567':
            j = i + 1
            while j < len(s) and s[j] in '01234567' and j < i + 4: j += 1
            out.append(int(s[i + 1:j], 8)); i = j; continue
        out.append({'n': 10, 't': 9, 'r': 13, '0': 0, '"': 34, '\\': 92, "'": 39, 'a': 7, 'b': 8, 'f': 12, 'v': 11}[n])
        i += 2
    return bytes(out)


def c_string(b):
    s, prev_oct = '', False
    for x in b:
        ch = chr(x)
        if x in (34, 92): s += '\\' + ch; prev_oct = False
        elif x == 10: s += '\\n'; prev_oct = False
        elif x == 9: s += '\\t'; prev_oct = False
        elif 32 <= x < 127:
            if prev_oct and ch in '01234567': s += '""'
            s += ch; prev_oct = False
        else: s += '\\%03o' % x; prev_oct = True
    return '"' + s + '"'


def load(sec, lo, hi):
    objs = []
    for f in sorted(glob.glob(os.path.join(ROOT, 'build', 'GNLJ82', 'asm', '**', '*.s'), recursive=True)):
        cur = None
        for line in open(f, encoding='utf-8', errors='replace'):
            m = HDR.match(line)
            if m:
                a = int(m.group(2), 16)
                cur = dict(sec=m.group(1), addr=a, size=int(m.group(3), 16), items=[]) \
                    if m.group(1) == sec and lo <= a < hi else None
                continue
            if cur is None: continue
            m = OBJ.match(line)
            if m: cur['name'] = m.group(1).strip('"'); cur['bind'] = m.group(2); continue
            t = line.split(' # ')[0].strip()
            if t.startswith('.endobj'): objs.append(cur); cur = None; continue
            if t.startswith('.string '): cur['items'].append(('s', parse_string(t[8:].strip()[1:-1]) + b'\0'))
            elif t.startswith('.4byte '): cur['items'] += [('4', v.strip()) for v in t[7:].split(',')]
            elif t.startswith('.2byte '): cur['items'] += [('2', v.strip()) for v in t[7:].split(',')]
            elif t.startswith('.byte '): cur['items'] += [('1', v.strip()) for v in t[6:].split(',')]
            elif t.startswith('.float '): cur['items'] += [('4', '0x%08X' % struct.unpack('>I', struct.pack('>f', float(v)))[0]) for v in t[7:].split(',')]
            elif t.startswith('.double '): cur['items'] += [('8', v.strip()) for v in t[8:].split(',')]
            elif t.startswith('.skip '): cur['items'] += [('1', '0')] * int(t[6:], 0)
    # stale asm files from older splits can repeat an object: keep one per address
    uniq = {}
    for o in objs:
        uniq.setdefault(o['addr'], o)
    return sorted(uniq.values(), key=lambda o: o['addr'])


def isnum(v):
    try: int(v, 0); return True
    except ValueError: return False


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('sec'); ap.add_argument('lo'); ap.add_argument('hi')
    ap.add_argument('--force-active', action='store_true')
    a = ap.parse_args()
    lo, hi = int(a.lo, 16), int(a.hi, 16)
    objs = [o for o in load(a.sec, lo, hi) if not o['name'].startswith('gap_')]
    const = 'const ' if a.sec in ('.rodata', '.sdata2') else ''
    defined = {o['name']: o for o in objs}
    out, fwd, ext = [], [], set()
    seen = set()
    for o in objs:
        st = 'static ' if o['bind'] == 'local' else ''
        n, sz, it = o['name'], o['size'], o['items']
        kinds = {k for k, _ in it}
        if kinds == {'s'} and len(it) == 1 and len(it[0][1]) == sz:
            out.append(f'{st}{const}char {n}[] = {c_string(it[0][1][:-1])};')
        elif kinds == {'4'} and sz == 4 * len(it):
            if all(isnum(v) for _, v in it):
                vals = ', '.join('0x%08X' % (int(v, 0) & 0xFFFFFFFF) for _, v in it)
                out.append(f'{st}{const}unsigned int {n}[{len(it)}] = {{ {vals} }};')
            else:
                el = []
                for _, v in it:
                    if isnum(v): el.append('(void *)0x%X' % (int(v, 0) & 0xFFFFFFFF)); continue
                    m = re.match(r'^"?([^"+\-]+)"?(?:([+\-])(0x[0-9a-fA-F]+|\d+))?$', v)
                    sym, sign, off = m.group(1), m.group(2), m.group(3)
                    if sym in defined and sym not in seen and sym != n:
                        if defined[sym]['bind'] == 'local':
                            sys.exit(f'forward ref to local {sym} from {n}: reorder by hand')
                        fwd.append(sym)
                    elif sym not in defined: ext.add(sym)
                    e = f'(void *)&{sym}' if not off else f'(void *)((char *)&{sym} {sign} {off})'
                    el.append(e)
                body = ',\n    '.join(el)
                out.append(f'{st}{const}void *{const}{n}[{len(it)}] = {{\n    {body}\n}};')
        else:
            bs = bytearray()
            for k, v in it:
                if k == 's': bs += v; continue
                if not isnum(v): sys.exit(f'{n}: relocation in non-word object')
                w = {'1': 1, '2': 2, '4': 4, '8': 8}[k]
                bs += (int(v, 0) & ((1 << (8 * w)) - 1)).to_bytes(w, 'big')
            if len(bs) != sz: sys.exit(f'{n}: parsed {len(bs)} bytes, size {sz:#x}')
            if sz % 4 == 0 and o['addr'] % 4 == 0:
                vals = ', '.join('0x%08X' % int.from_bytes(bs[i:i + 4], 'big') for i in range(0, sz, 4))
                out.append(f'{st}{const}unsigned int {n}[{sz // 4}] = {{ {vals} }};')
                seen.add(n)
                continue
            vals = ', '.join('0x%02X' % x for x in bs)
            out.append(f'{st}{const}unsigned char {n}[{sz}] = {{ {vals} }};')
        seen.add(n)
    res = []
    if ext: print('needs externs: ' + ', '.join(sorted(ext)), file=sys.stderr)
    bydef = {o['name']: d for o, d in zip(objs, out)}
    for s in dict.fromkeys(fwd):
        head = re.sub(r'\[\d+\]', '[]', bydef[s].split(' = ')[0])
        res.append(f'extern {head};  /* forward; defined below */')
    if a.force_active: res.append('#pragma force_active on')
    res += out
    if a.force_active: res.append('#pragma force_active reset')
    print('\n'.join(res))


if __name__ == '__main__':
    main()
