#!/usr/bin/env python3
"""Take an address range out of a data-only unit (src/game/autodata) so a real
unit can own it.

    python3 tools/autodata_carve.py SEC LO HI [--dry]

The definitions in [LO, HI) are removed from the autodata file that holds them
and printed, so they can be pasted into (or replaced by real code in) the unit
that takes the range. The autodata file is shortened, or split in two when the
range is in its middle, and its splits.txt entry follows. Adding [LO, HI) to
the new owner's splits.txt entry is left to the caller.
Used for turning hand-written vtables into real classes (docs/notes/rtti_classes.md).
"""
import argparse, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
import port_readiness as P

DEF = re.compile(r'^(?!extern\b|#|/\*|\s|\}|typedef\b|struct\b.*\{\s*$)[^\n=;(]*?\b(\w+)(?:\[[^\]\n]*\])*(?: __attribute__\(\(aligned\(8\)\)\))?\s*(=|;)', re.M)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('sec'); ap.add_argument('lo'); ap.add_argument('hi'); ap.add_argument('--dry', action='store_true')
    a = ap.parse_args()
    lo, hi = int(a.lo, 16), int(a.hi, 16)
    ranges = P.splits_ranges()[a.sec]
    owner = [(l, h, u) for l, h, u in ranges if l <= lo and hi <= h]
    if not owner or not owner[0][2].startswith('game/autodata/'):
        sys.exit('range is not inside one autodata unit: %r' % (owner,))
    ulo, uhi, unit = owner[0]
    addr = {n: x for n, s, x, z, k in P.symbols() if s == a.sec}
    path = os.path.join(ROOT, 'src', unit)
    text = open(path).read()
    head_end = text.index('#pragma force_active on\n') + len('#pragma force_active on\n')
    tail_at = text.rindex('#pragma force_active reset')
    head, body, tail = text[:head_end], text[head_end:tail_at], text[tail_at:]
    # definitions with the comment lines right above them
    starts = []
    for m in DEF.finditer(body):
        if m.group(1) in addr:
            s = m.start()
            while True:
                prev = body.rfind('\n', 0, s - 1) + 1
                line = body[prev:s]
                if s > 0 and (line.startswith('/*') or line.startswith('//')): s = prev
                else: break
            starts.append((s, addr[m.group(1)]))
    starts.sort()
    if not starts: sys.exit('no definitions recognised in ' + unit)
    pieces = [(ad, body[s:(starts[i + 1][0] if i + 1 < len(starts) else len(body))]) for i, (s, ad) in enumerate(starts)]
    pre = body[:starts[0][0]]
    before = ''.join(p for ad, p in pieces if ad < lo)
    taken = ''.join(p for ad, p in pieces if lo <= ad < hi)
    after = ''.join(p for ad, p in pieces if ad >= hi)
    print(taken.rstrip())
    if a.dry: return
    sp_path = os.path.join(ROOT, 'config', P.VER, 'splits.txt'); sp = open(sp_path).read()
    line = '\t%-11s start:0x%08X end:0x%08X\n' % (a.sec, ulo, uhi)
    block = '%s:\n%s' % (unit, line)
    if block not in sp: sys.exit('splits.txt entry of %s has more than this one range; edit by hand' % unit)
    newblocks = []
    sname = a.sec.lstrip('.')

    def write(p_lo, p_hi, content, name):
        hdr = re.sub(r'0x[0-9A-F]{8}\.\.0x[0-9A-F]{8}', '0x%08X..0x%08X' % (p_lo, p_hi), head, count=1)
        open(os.path.join(ROOT, 'src', name), 'w').write(hdr + pre + content.rstrip('\n') + '\n\n' + tail)
        newblocks.append('%s:\n\t%-11s start:0x%08X end:0x%08X\n' % (name, a.sec, p_lo, p_hi))
    os.remove(path)
    if before.strip(): write(ulo, lo, before, unit)
    if after.strip(): write(hi, uhi, after, 'game/autodata/%s_%08X.c' % (sname, hi))
    sp = sp.replace(block, '\n'.join(newblocks).rstrip('\n') + '\n' if newblocks else '')
    sp = re.sub(r'\n{3,}', '\n\n', sp)
    open(sp_path, 'w').write(sp)
    sys.stderr.write('%s: kept %s\n' % (unit, ', '.join(b.split(':')[0] for b in newblocks) or 'nothing (unit removed)'))


if __name__ == '__main__':
    main()
