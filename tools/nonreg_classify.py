#!/usr/bin/env python3
"""Classify what the NON-register part of a near miss is.

    python3 tools/nonreg_classify.py LIST [--md docs/nonreg_census.md]

LIST lines: `UNIT FN [pct]` (e.g. the not_reg_only rows of
docs/sweeps/regfix/diagsweep_shard*.jsonl; `--from-diagsweep` reads them).
Groups (first that applies):
  length:*  ours and the target differ in instruction count; the suffix says
            which opcodes are extra/missing (copy, address, extend, load, branch, mixed)
  stack     same opcodes in order, differing r1 offsets / frame size
  symbol    same opcodes in order, differing relocation / pool / sda offset
            (pool or anchor ownership, symbols.txt split)
  constant  same opcodes in order, a differing immediate that is no symbol
  order     same opcode multiset, different order (scheduler)
  opcode    same length, different opcodes (instruction selection)
"""
import argparse, collections, glob, json, os, re, sys
from concurrent.futures import ThreadPoolExecutor
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import regswap_classify as rc


def classify(left, right):
    L = [x['instruction'] for x in left if x.get('instruction')]
    R = [x['instruction'] for x in right if x.get('instruction')]
    lo, ro = [rc.ops(i) for i in L], [rc.ops(i) for i in R]
    d = dict(n_target=len(L), n_ours=len(R))
    if len(L) != len(R):
        tm = collections.Counter(m for m, _ in lo) - collections.Counter(m for m, _ in ro)
        om = collections.Counter(m for m, _ in ro) - collections.Counter(m for m, _ in lo)
        allm = set(tm) | set(om)
        fam = lambda ms: all(re.fullmatch(ms, m) for m in allm)   # noqa: E731
        sub = ('copy' if fam(r'f?mr\.?') else
               'address' if fam(r'lis|addis?|add|li|f?mr|subi') else
               'extend' if fam(r'exts[bh]\.?|clrlwi\.?|rlwinm\.?|andi\.|f?mr') else
               'load' if fam(r'l[bhw]zu?x?|lha|lf[sd]x?|st[bhw]u?x?|stf[sd]x?|f?mr|addi?|lis') else
               'branch' if fam(r'b\w*|cmp\w*|f?mr|li|cror|fcmp\w') else 'mixed')
        d['kind'] = 'length:' + sub
        d['detail'] = (f'{len(R) - len(L):+d} insns; target has ' + (' '.join(f'{m}x{c}' for m, c in sorted(tm.items())) or '-')
                       + ' / ours has ' + (' '.join(f'{m}x{c}' for m, c in sorted(om.items())) or '-'))
        return d
    lm, rm = [m for m, _ in lo], [m for m, _ in ro]
    if lm != rm:
        if collections.Counter(lm) == collections.Counter(rm):
            d['kind'] = 'order'
            d['detail'] = f'{sum(a != b for a, b in zip(lm, rm))} positions'
        else:
            d['kind'] = 'opcode'
            diff = collections.Counter(lm) - collections.Counter(rm)
            diff2 = collections.Counter(rm) - collections.Counter(lm)
            d['detail'] = 'target ' + ','.join(sorted(diff)) + ' / ours ' + ','.join(sorted(diff2))
        return d
    stack = sym = const = reg = 0
    ex = None
    for (m, a), (_, b), li, ri in zip(lo, ro, L, R):
        if a == b:
            continue
        for k, (x, y) in enumerate(zip(a, b)):
            if x == y:
                continue
            if rc.REG.match(x) and rc.REG.match(y):
                reg += 1
                continue
            base = a[k + 1] if k + 1 < len(a) else ''
            if 'r1' in (base,) or (m in ('stwu', 'addi') and a[:2] in (['r1', 'r1'],) ) or 'r1' in a[1:2] and m == 'addi':
                stack += 1
            elif re.search(r'[A-Za-z_@]', x.replace('0x', '')) or re.search(r'[A-Za-z_@]', y.replace('0x', '')) \
                    or base in ('r2', 'r13'):
                sym += 1
                ex = ex or f'{li["formatted"]}  vs  {ri["formatted"]}'
            else:
                const += 1
                ex = ex or f'{li["formatted"]}  vs  {ri["formatted"]}'
    d['kind'] = 'symbol' if sym else 'stack' if stack else 'constant' if const else 'reg_only'
    d['detail'] = f'sym {sym} stack {stack} const {const} reg {reg}' + (f'; e.g. {ex}' if ex else '')
    return d


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('list', nargs='?')
    ap.add_argument('--from-diagsweep', action='store_true')
    ap.add_argument('--md')
    ap.add_argument('-j', type=int, default=os.cpu_count() or 4)
    a = ap.parse_args()
    jobs = []
    if a.from_diagsweep:
        rows = {}
        key = lambda f: int((re.search(r'\.v(\d)\.jsonl', f) or [0, 1])[1])
        for f in sorted(glob.glob('docs/sweeps/regfix/diagsweep_shard*.jsonl'), key=key):
            for l in open(f):
                r = json.loads(l)
                rows[r['fn']] = r
        jobs = [(r['unit'], r['fn']) for r in rows.values() if r['status'] == 'not_reg_only']
    else:
        jobs = [tuple(l.split()[:2]) for l in open(a.list) if l.strip()]
    units = {u['name']: u for u in json.load(open('objdiff.json'))['units']}
    rep = {}
    for u in json.load(open('build/GNLJ82/report.json'))['units']:
        for f in u.get('functions', []):
            rep[f['name']] = (u['name'].split('/', 1)[-1] if u['name'] not in units else u['name'],
                              f.get('fuzzy_match_percent', 0))

    def work(job):
        unit, fn = job
        cur = rep.get(fn)
        ou = units.get(unit) or next((v for k, v in units.items() if k.endswith('/' + unit)), None)
        if cur and cur[1] >= 100:
            return dict(unit=unit, fn=fn, pct=100.0, kind='matched now', detail='')
        if not ou or 'base_path' not in ou:
            # the fn may have moved (TU merge): look it up in the report
            ou = units.get(cur[0]) if cur else None
            if not ou:
                return dict(unit=unit, fn=fn, kind='error', detail='unit not found', pct=0)
        try:
            r = rc.run_objdiff(ou, fn)
        except Exception as e:
            r = None
        if not r:
            return dict(unit=unit, fn=fn, kind='error', detail='objdiff', pct=cur[1] if cur else 0)
        d = classify(*r)
        d.update(unit=unit, fn=fn, pct=round(cur[1], 2) if cur else 0)
        return d

    with ThreadPoolExecutor(a.j) as ex:
        rows = list(ex.map(work, jobs))
    c = collections.Counter(r['kind'] for r in rows)
    out = ['# Non-register near misses by kind of diff', '',
           'Generated by `python3 tools/nonreg_classify.py --from-diagsweep --md docs/nonreg_census.md`',
           '(the gave_up rows >=90% that `regfix diag` refuses as not register-only).', '',
           '| kind | count | who |', '|---|---|---|']
    who = {'length:copy': 'a copy coalesced / not coalesced: named local vs temp (`regfix diag` with REGFIX_FORCE=1, mwsched coalesce)',
           'length:address': 'address rebuilt vs reused: anchor/pool ownership, CSE (regalloc_patterns 13/40, opt_common_subs)',
           'length:extend': 'integer width / signedness of a local or return type',
           'length:load': 'value reloaded vs kept: aliasing (__restrict, const), local snapshot',
           'length:branch': 'control flow shape: hand rewrite',
           'length:mixed': 'code shape: hand rewrite (objdiff)'}
    who.update(order='scheduler: `mwsched.py explain`, `regfix diag --sched`',
               stack='stack layout: local decl order / sizes (matching_rules 7)',
               symbol='pool/anchor ownership or symbols.txt split (pool_audit, regalloc_patterns 13/40)',
               constant='immediate differs: struct offset / literal', opcode='instruction selection: types, signedness, pragmas',
               reg_only='register only after all (rebuilt since the sweep)')
    who = dict(who)
    for k, v in c.most_common():
        out.append(f'| {k} | {v} | {who.get(k, "")} |')
    out += ['', '| kind | unit | fn | % | detail |', '|---|---|---|---|---|']
    for r in sorted(rows, key=lambda r: (r['kind'], r['unit'], r['fn'])):
        out.append(f"| {r['kind']} | {r['unit']} | `{r['fn']}` | {r.get('pct', 0)} | {r.get('detail', '')} |")
    text = '\n'.join(out) + '\n'
    if a.md:
        open(a.md, 'w').write(text)
    for k, v in c.most_common():
        print(v, k)


if __name__ == '__main__':
    main()
