#!/usr/bin/env python3
"""Classes of the original program, read from the RTTI the game was built with.

MWCC (`-RTTI on`) leaves, for every polymorphic class:
  * a record {name string, base list or 0}      (8 bytes, mostly .sdata)
  * a base list {record, offset}... 0           (.data, only with bases)
  * a vtable {record, offset to top, slots...}  (.data)
This reads all three from main.dol and prints one row per vtable: its real
class name, its bases, the unit that would own it and the functions in its
slots. It is the map for turning hand-written vtables into real classes
(mkgp2-pc docs/port/cxx_abi_decision.md, docs/notes/rtti_classes.md).

    python3 tools/rtti_classes.py            # table
    python3 tools/rtti_classes.py --tsv      # machine-readable
    python3 tools/rtti_classes.py --class clScreenEffect
"""
import argparse, bisect, collections, os, re, struct, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
import port_readiness as P


class Dol:
    def __init__(self, path):
        self.d = open(path, 'rb').read()
        offs = struct.unpack('>18I', self.d[0:0x48]); addrs = struct.unpack('>18I', self.d[0x48:0x90])
        sizes = struct.unpack('>18I', self.d[0x90:0xD8])
        self.segs = [(a, a + s, o) for o, a, s in zip(offs, addrs, sizes) if s]

    def off(self, a):
        for lo, hi, o in self.segs:
            if lo <= a < hi: return o + a - lo
        return None

    def u32(self, a):
        o = self.off(a)
        return struct.unpack('>I', self.d[o:o + 4])[0] if o is not None else None

    def cstr(self, a, limit=200):
        o = self.off(a)
        if o is None: return None
        e = self.d.find(b'\0', o, o + limit)
        if e <= o: return None
        s = self.d[o:e]
        return s.decode('ascii') if all(32 <= c < 127 for c in s) else None


def find_dol():
    for p in ('orig/GNLJ82/sys/main.dol', 'build/GNLJ82/main.dol'):
        if os.path.exists(os.path.join(ROOT, p)): return os.path.join(ROOT, p)
    return None


NAME = re.compile(r'^[A-Za-z_][\w:<>, *&]*$')


TSV = os.path.join(ROOT, 'docs', 'notes', 'rtti_classes.tsv')


def collect_from_tsv():
    """Without main.dol (CI): classes and slots from the committed table, units
    and symbol names from today's splits.txt / symbols.txt."""
    syms = P.symbols(); ranges = P.splits_ranges()
    name_at = {a: n for n, s, a, z, k in syms if s == '.data'}
    fn_addr = {n: a for n, s, a, z, k in syms if s == '.text'}

    def unit(section, a):
        for lo, hi, u in ranges.get(section, []):
            if lo <= a < hi: return u
        return None
    out = []; records = {}
    for line in open(TSV).read().split('\n')[1:]:
        c = line.split('\t')
        if len(c) < 6: continue
        a = int(c[0], 16); slots = [s for s in c[5].split(',') if s]
        fus = collections.Counter(unit('.text', fn_addr[s]) for s in slots if s in fn_addr)
        out.append({'addr': a, 'symbol': c[3] if '+' in c[3] else name_at.get(a, c[3]), 'class': c[1], 'bases': [(b, 0) for b in c[2].split(',') if b],
                    'offset_to_top': int(c[6]) if len(c) > 6 else 0, 'slots': slots, 'data_unit': unit('.data', a), 'slot_units': dict(fus), 'record': 0})
        records[c[1]] = 1
    return out, records


def collect():
    path = find_dol()
    if path is None:
        if os.path.exists(TSV): return collect_from_tsv()
        sys.exit('main.dol not found (orig/GNLJ82/sys/main.dol or build/GNLJ82/main.dol) and no ' + TSV)
    dol = Dol(path)
    syms = P.symbols(); ranges = P.splits_ranges()
    sec = {}
    for n, s, a, z, k in syms: sec.setdefault(s, []).append((a, z, n))
    for v in sec.values(): v.sort()
    name_at = {a: n for n, s, a, z, k in syms if s != '.text' or k == 'function'}
    fn_at = {a: n for n, s, a, z, k in syms if s == '.text'}

    def unit(section, a):
        r = ranges.get(section, [])
        i = bisect.bisect_right(r, (a, 1 << 40, '')) - 1
        return r[i][2] if i >= 0 and r[i][0] <= a < r[i][1] else None

    def in_sec(a, names):
        return any(lo <= a < lo + max(z, 1) for s in names for lo, z, n in sec.get(s, []) if lo <= a < lo + max(z, 1)) if a else False

    text = (min(a for a, z, n in sec['.text']), max(a + z for a, z, n in sec['.text']))
    data_objs = sec.get('.data', [])
    data_lo, data_hi = data_objs[0][0], data_objs[-1][0] + data_objs[-1][1]
    # 1. RTTI records: 8-byte objects {pointer to a name string, 0 or pointer into .data}
    records = {}
    for s in ('.sdata', '.data'):
        for a, z, n in sec.get(s, []):
            if z != 8: continue
            p, b = dol.u32(a), dol.u32(a + 4)
            if p is None: continue
            nm = dol.cstr(p)
            if not nm or not NAME.match(nm): continue
            if b and not (data_lo <= b < data_hi): continue
            records[a] = {'name': nm, 'baselist': b, 'bases': []}
    # 2. base lists
    baselists = set()
    for a, r in records.items():
        b = r['baselist']
        if not b: continue
        baselists.add(b)
        for i in range(32):
            rec, off = dol.u32(b + 8 * i), dol.u32(b + 8 * i + 4)
            if not rec: break
            if rec in records: r['bases'].append((records[rec]['name'], off))
            else: break
    # 3. vtables: .data objects whose first word is a record and that are not base
    #    lists. One object can hold several tables (the secondary tables of a class
    #    with two bases follow the primary one: {record, negative offset, slots}).
    out = []
    addr_of = {v: k for k, v in fn_at.items()}
    for a, z, n in data_objs:
        if a in baselists or z < 8: continue
        if dol.u32(a) not in records: continue
        words = [dol.u32(a + 4 * i) for i in range(z // 4)]
        starts = [i for i in range(len(words) - 1) if words[i] in records and
                  (words[i + 1] == 0 or words[i + 1] >= 0xFFFF0000) and (i == 0 or words[i + 1] >= 0xFFFF0000)]
        if len(words) > 2 and words[2] in records: continue      # an unreferenced base list
        for k, i in enumerate(starts):
            end = starts[k + 1] if k + 1 < len(starts) else len(words)
            slots = [fn_at.get(f, '0' if not f else '0x%08X' % f) for f in words[i + 2:end]]
            while slots and slots[-1] == '0': slots.pop()     # alignment padding or trailing pure virtuals
            fus = collections.Counter(unit('.text', addr_of[s]) for s in slots if s in addr_of)
            rec = words[i]
            out.append({'addr': a + 4 * i, 'symbol': n if i == 0 else '%s+0x%X' % (n, 4 * i), 'class': records[rec]['name'],
                        'bases': records[rec]['bases'], 'offset_to_top': words[i + 1] - (1 << 32) if words[i + 1] else 0,
                        'slots': slots, 'data_unit': unit('.data', a), 'slot_units': dict(fus), 'record': rec})
    return out, records


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--tsv', action='store_true'); ap.add_argument('--class', dest='cls')
    a = ap.parse_args()
    vts, records = collect()
    if a.cls:
        for v in vts:
            if v['class'] == a.cls or v['symbol'] == a.cls:
                print('%s  vtable %s at 0x%08X (unit %s)' % (v['class'], v['symbol'], v['addr'], v['data_unit']))
                print('  bases:', ', '.join('%s+%d' % b for b in v['bases']) or '-')
                for i, s in enumerate(v['slots']): print('  slot %d (+0x%X): %s' % (i, 8 + 4 * i, s))
                print('  units of the slot functions:', v['slot_units'])
        return
    if a.tsv:
        print('address\tclass\tbases\tsymbol\tdata_unit\tslots\toffset_to_top')
        for v in vts:
            print('0x%08X\t%s\t%s\t%s\t%s\t%s' % (v['addr'], v['class'], ','.join(b[0] for b in v['bases']), v['symbol'],
                                                    v['data_unit'], ','.join(v['slots'])) + '\t%d' % v['offset_to_top'])
        return
    for v in vts:
        print('0x%08X  %-44s : %-40s %2d slots  %s' % (v['addr'], v['class'], ','.join(b[0] for b in v['bases']) or '-',
                                                      len(v['slots']), v['symbol']))
    names = collections.Counter(v['class'] for v in vts)
    print('\n%d vtables, %d classes with RTTI records, %d class names with a vtable' % (len(vts), len(records), len(names)))


if __name__ == '__main__':
    main()
