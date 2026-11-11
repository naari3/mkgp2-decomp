#!/usr/bin/env python3
"""Check the VALUES of float/double literals that postprocess_sdata2.py renames.

postprocess_sdata2.py points an anonymous literal (`1.0f` in the source) at the
target's `lbl_806Dxxxx` by code position only.  The link then uses the original
pool, so main.dol matches whatever number the source wrote: a wrong literal is
invisible to the build (KartTireFX wrote 1000.0f where the program has 1.0f).

  rm -rf build/GNLJ82/src
  MKGP2_LIT_LOG=/tmp/lit.log ninja          # every unit logs its literal uses
  python3 tools/literal_value_audit.py /tmp/lit.log

Lists each use whose source value differs from the original bytes of the symbol
it is renamed to.  For a Matching unit the position is exact, so every line is
a real error in the source.  For a NonMatching unit the code layout differs and
a line may only mean the loads come in another order: read those by hand.
A new distinct literal in a unit shifts the `@N` numbers that
extab_user_renames.json relies on; when that breaks the link, read the value
through the named constant instead (`extern const float lbl_806Dxxxx;`).
"""
import collections, os, re, struct, sys

def main():
    log = sys.argv[1]
    d = open('orig/GNLJ82/sys/main.dol', 'rb').read()
    o = struct.unpack('>18I', d[0:72]); a = struct.unpack('>18I', d[72:144]); s = struct.unpack('>18I', d[144:216])
    def rd(addr, n):
        for oo, aa, ss in zip(o, a, s):
            if ss and aa <= addr < aa + ss:
                return d[oo + addr - aa:oo + addr - aa + n]
        return b'\0' * n  # .sbss/.sbss2/.bss
    sym = {}
    for l in open('config/GNLJ82/symbols.txt'):
        m = re.match(r'(\S+) = \.(\w+):0x([0-9A-Fa-f]+);', l)
        if m: sym[m.group(1)] = int(m.group(3), 16)
    status = {}
    for l in open('configure.py'):
        m = re.search(r'Object\((\w+), "([^"]+)"', l)
        if m: status[os.path.splitext(m.group(2))[0]] = m.group(1)
    def val(b):
        if len(b) == 4: return repr(struct.unpack('>f', b)[0])
        if len(b) == 8: return repr(struct.unpack('>d', b)[0]) + ' (double)'
        return b.hex()
    # A weak inline destructor copy that the link discards: its position
    # coincides with an unrelated target reloc, so the line means nothing.
    known = {('game/SpriteHandle', '__dt__11ScopedTimerFv')}
    bad = collections.OrderedDict(); n = 0
    for l in open(log):
        path, fn, off, new, sz, hx = l.rstrip('\n').split('\t'); sz = int(sz); n += 1
        if not hx or new not in sym: continue
        ob = rd(sym[new], sz)
        if ob.hex() != hx:
            unit = path.split('/src/', 1)[-1].rsplit('.', 1)[0]
            if (unit, fn) in known: continue
            bad.setdefault((unit, fn, hx, new, ob.hex()), []).append(int(off))
    print('%d literal uses checked, %d differ' % (n, sum(len(v) for v in bad.values())))
    for (unit, fn, hx, new, oh), offs in bad.items():
        print('%-11s %s | %s | source %s | original %s = %s | at %s' % (
            status.get(unit, '?'), unit, fn, val(bytes.fromhex(hx)), new, val(bytes.fromhex(oh)),
            ','.join('+0x%x' % x for x in offs)))
    return 1 if any(status.get(k[0]) == 'Matching' for k in bad) else 0

if __name__ == '__main__':
    sys.exit(main())
