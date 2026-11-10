#!/usr/bin/env python3
"""List code that addresses a data symbol past its end (regalloc_patterns 90).

A source that lays a struct or array view over `lbl_X` and reads fields beyond the
size of that object (`lbl_X + 0x41c` where lbl_X is 0x3fc bytes) compiles to the
same address, but the compiler cannot place the load inside the object, so struct
copies and load/store scheduling come out differently from the target
(CarObjectManager_RunKartKartCollisionSweep 98.95 -> 100 after the values became
their own objects).  This looks at OUR object files, so it needs no source parsing:
every .text relocation `symbol+addend` whose addend is outside the symbol's size in
symbols.txt is reported with the object that really lives at that address.

Pooled accesses the compiler makes itself use a section anchor (`...rodata.0`,
`@123`), not a named symbol, so they are not reported.

Usage (after ninja):  python3 tools/oob_read_detect.py [--min 0] [--max 99.999] [--md docs/sweeps/oob_read.md]
"""
import argparse, bisect, collections, json, re, subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
OBJDUMP = ROOT / 'build/binutils/powerpc-eabi-objdump'
SYM = re.compile(r'^(\S+) = (\.?\w+):0x([0-9A-Fa-f]+); // type:object(?: size:0x([0-9A-Fa-f]+))?')
HDR = re.compile(r'^[0-9a-f]+ <(.+)>:$')
REL = re.compile(r'^\s*[0-9a-f]+: (R_PPC_\S+)\s+(\S+?)([+-]0x[0-9a-f]+)?$')


def symbols():
    by_name, addrs = {}, []
    for l in (ROOT / 'config/GNLJ82/symbols.txt').read_text().splitlines():
        m = SYM.match(l)
        if m and m.group(4):
            a, s = int(m.group(3), 16), int(m.group(4), 16)
            by_name[m.group(1)] = (a, s, m.group(2))
            addrs.append((a, s, m.group(1)))
    addrs.sort()
    return by_name, addrs


def owner(addrs, a):
    k = bisect.bisect_right(addrs, (a, 1 << 40, '')) - 1
    if k >= 0 and addrs[k][0] <= a < addrs[k][0] + addrs[k][1]:
        return f'{addrs[k][2]}+0x{a - addrs[k][0]:x}'
    return '?'


def scan(obj, by_name, addrs):
    out = subprocess.run([str(OBJDUMP), '-dr', '-j', '.text', str(obj)], capture_output=True, text=True).stdout
    hits, cur = collections.OrderedDict(), None
    for l in out.splitlines():
        m = HDR.match(l)
        if m:
            cur = m.group(1)
            continue
        m = REL.match(l)
        if not m or m.group(1) in ('R_PPC_REL24', 'R_PPC_REL14'):
            continue
        sym, add = m.group(2), int(m.group(3) or '0', 16)
        if sym not in by_name:
            continue
        a, s, _sec = by_name[sym]
        if 0 <= add < s or (add == s and s == 0):
            continue
        hits.setdefault((cur, sym, add), (s, owner(addrs, a + add)))
    return hits


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--min', type=float, default=0)
    ap.add_argument('--max', type=float, default=99.999)
    ap.add_argument('--md')
    a = ap.parse_args()
    by_name, addrs = symbols()
    rep = json.load(open(ROOT / 'build/GNLJ82/report.json'))
    rows = []
    for u in rep['units']:
        fz = {f['name']: f.get('fuzzy_match_percent', 0) for f in u.get('functions', [])}
        if not any(a.min <= p <= a.max for p in fz.values()):
            continue
        obj = ROOT / 'build/GNLJ82/src' / (u['name'].split('/', 1)[1] + '.o')
        if not obj.exists():
            continue
        for (fn, sym, add), (size, own) in scan(obj, by_name, addrs).items():
            p = fz.get(fn)
            if p is None or not (a.min <= p <= a.max):
                continue
            rows.append((p, u['name'].split('/', 1)[1], fn, sym, size, add, own))
    rows.sort(key=lambda r: (-r[0], r[1], r[2]))
    lines = ['| % | unit | function | symbol (size) | addend | object really there |', '|---|---|---|---|---|---|']
    for p, unit, fn, sym, size, add, own in rows:
        lines.append(f'| {p:.2f} | {unit} | `{fn}` | `{sym}` (0x{size:x}) | {"-" if add < 0 else ""}0x{abs(add):x} | `{own}` |')
    text = (f'# Reads past the end of a data symbol in near misses ({len(rows)} sites, '
            f'{len(set(r[2] for r in rows))} functions)\n\n'
            'regalloc_patterns 90: give the values their own objects (symbols.txt already has them) '
            'instead of a view over the neighbour. Made by tools/oob_read_detect.py.\n\n' + '\n'.join(lines) + '\n')
    if a.md:
        Path(a.md).parent.mkdir(parents=True, exist_ok=True)
        Path(a.md).write_text(text)
        print(f'wrote {a.md}: {len(rows)} sites in {len(set(r[2] for r in rows))} functions')
    else:
        print(text)


if __name__ == '__main__':
    main()
