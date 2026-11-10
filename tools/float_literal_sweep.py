#!/usr/bin/env python3
"""Lever: read-only float/double constants written as `extern` loads -> literals.

A constant read through `extern const float lbl_806Dxxxx` is a memory load for
the optimizer; the literal is a constant (other vreg creation order, CSE and
fmadd fusion).  FlashFadeOverlay_Draw went 99.65 -> 100 this way (11-09).
tools/postprocess_sdata2.py maps the anonymous literal symbols back to the
target's names, so no .sdata2 split is needed.

  float_literal_sweep.py                 every not-yet-matching function
  float_literal_sweep.py UNIT [FN]       one unit, e.g. game/HomingMarkerUpdate
Output: docs/sweeps/float_literal.md (objdiff score, lower is better, 0 = match).
"""
import json, os, re, struct, sys
from concurrent.futures import ThreadPoolExecutor
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import pragmasweep as ps
import leversweep as L

DOL = 'orig/GNLJ82/sys/main.dol'
_d = open(DOL, 'rb').read()
_o = struct.unpack('>18I', _d[0:72]); _a = struct.unpack('>18I', _d[72:144]); _s = struct.unpack('>18I', _d[144:216])

def rd(addr, n):
    for o, a, s in zip(_o, _a, _s):
        if s and a <= addr < a + s:
            return _d[o + addr - a:o + addr - a + n]

SYMS = {}
for l in open('config/GNLJ82/symbols.txt'):
    m = re.match(r'(\w+) = \.(sdata2|rodata):0x([0-9A-Fa-f]+);.*?size:0x([0-9A-Fa-f]+)', l)
    if m: SYMS[m.group(1)] = (m.group(2), int(m.group(3), 16), int(m.group(4), 16))

def lit(sym, ty):
    if sym not in SYMS: return None
    sec, addr, size = SYMS[sym]
    if ty in ('float', 'f32'):
        if size != 4: return None
        b = rd(addr, 4); v = struct.unpack('>f', b)[0]
        if v != v or v in (float('inf'), float('-inf')): return None
        if b == b'\x80\x00\x00\x00': return '(-0.0f)'
        for n in range(1, 10):
            t = '%.*g' % (n, v)
            if struct.pack('>f', float(t)) == b: break
        else: return None
        if not re.search(r'[.e]', t): t += '.0'
        t += 'f'
    else:
        if size != 8: return None
        b = rd(addr, 8); v = struct.unpack('>d', b)[0]
        if v != v or abs(v) == float('inf'): return None
        t = repr(v)
        if struct.pack('>d', float(t)) != b: return None
        if b[:4] == b'\x43\x30\x00\x00': return None   # int->float bias, never a source literal
    return '(%s)' % t if t.startswith('-') else t

DECL = re.compile(r'^[ \t]*extern\s+(?:"C"\s+)?(?:const\s+)?(float|double|f32|f64)\s+(?:const\s+)?(lbl_\w+(?:\s*,\s*lbl_\w+)*)\s*;[^\n]*\n', re.M)

def rewrite(text):
    """-> (new text, number of symbols replaced).  The extern lines stay (unused externs are harmless)."""
    decls = {}
    src = text
    for h in re.findall(r'#include "([^"]+)"', text):
        p = os.path.join('include', h)
        if os.path.exists(p): src += open(p, errors='replace').read()
    for m in DECL.finditer(src):
        for sym in re.findall(r'lbl_\w+', m.group(2)): decls[sym] = m.group(1)
    keep = [m.span() for m in DECL.finditer(text)]
    def sub_outside(pat, rep, t):
        out = []; pos = 0
        for a, b in [m.span() for m in DECL.finditer(t)]:
            out.append(re.sub(pat, rep, t[pos:a])); out.append(t[a:b]); pos = b
        out.append(re.sub(pat, rep, t[pos:]))
        return ''.join(out)
    n = 0
    for sym, ty in decls.items():
        v = lit(sym, ty)
        if v is None: continue
        if re.search(r'&\s*%s\b|\b%s\s*\[' % (sym, sym), text): continue   # address taken / array use
        new = sub_outside(r'\b%s\b' % sym, lambda m: v, text)
        if new != text: n += 1
        text = new
    return text, n

def near_misses(only_unit=None, only_fn=None):
    r = json.load(open('build/GNLJ82/report.json'))
    for u in r['units']:
        name = u['name'].replace('main/', '')
        if only_unit and name != only_unit: continue
        for f in u.get('functions', []):
            p = f.get('fuzzy_match_percent', 0)
            if 0 < p < 100 and (not only_fn or f['name'] == only_fn):
                yield name, f['name'], p

def main():
    ps.OBJDIFF = True
    jobs = list(near_misses(*sys.argv[1:3]))
    rows = []
    def run(j):
        unit, fn, pct = j
        try:
            fx = L.Fx(unit, fn)
        except Exception as e:
            return None
        t, n = rewrite(fx.text)
        if not n: return None
        tag = re.sub(r'\W', '_', unit + fn)[-40:]
        base = fx.u.compile_score(fx.text, fn, fx.cc, 'fb' + tag)
        new = fx.u.compile_score(t, fn, fx.cc, 'fn' + tag)
        return (unit, fn, pct, n, base, new)
    with ThreadPoolExecutor(4) as ex:
        for r in ex.map(run, jobs):
            if r:
                rows.append(r); print(r, flush=True)
    rows.sort(key=lambda r: (r[5] - r[4], r[0]))
    os.makedirs('docs/sweeps', exist_ok=True)
    with open('docs/sweeps/float_literal.md', 'w') as f:
        f.write('# float literal sweep\n\n`python3 tools/float_literal_sweep.py`: extern float/double constants replaced by literals.\nScore = objdiff score of the function (lower is better, 0 = match).\n\n| unit | fn | % | symbols | base | literal |\n|---|---|---|---|---|---|\n')
        for r in rows: f.write('| %s | `%s` | %.2f | %d | %s | %s |\n' % r)
    print(len(rows), 'functions;', sum(1 for r in rows if r[5] < r[4]), 'better;', sum(1 for r in rows if r[5] == 0), 'match')

if __name__ == '__main__':
    main()
