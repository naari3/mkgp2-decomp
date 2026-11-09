#!/usr/bin/env python3
"""Classify near-miss functions by the shape of their register diff.

    python3 tools/regswap_classify.py [--min 97] [--claims FILE] [--json OUT] [--md OUT]

Run from the repo root after `ninja build/GNLJ82/report.json`. For every
function in report.json at or above --min fuzzy percent (and below 100), it
runs `objdiff-cli diff` on the unit's target/base objects and uses objdiff's
own instruction alignment (left = target, right = ours) to build a signature:

  kind      reg_only      every diff is an argument mismatch on registers
            reg+sched     registers plus reordered/rematerialised instructions
                          (same mnemonics in the diff window, other order/form)
            reg+other     registers plus immediates, relocations or opcodes
            no_reg        no register mismatch at all (schedule, reloc, data)
  class     which registers are permuted: gpr_saved (r14-r31), gpr_vol
            (r3-r12), r0, fpr_saved (f14-f31), fpr_vol; joined with '+'
  shape     swap (A<->B), shift (saved regs all moved by the same +-k),
            cycle (one longer permutation), multi (several independent ones)
  where     place of the first mismatching instruction: prologue, loop,
            after_call, switch, epilogue, body
  value     what the target's first mismatching register holds, from its
            defining instruction: &local, global, param, call_result, const,
            float_const, load, induction, address_calc, other

--claims FILE: lines "<owner> <configure path>"; TUs owned by someone other
than naari3 are marked [claimed].
"""
import argparse, collections, json, os, re, subprocess, sys
from concurrent.futures import ThreadPoolExecutor

OBJDIFF = 'build/tools/objdiff-cli'
REG = re.compile(r'^(r|f)(\d+)$')
BRANCH_CALL = {'bl', 'bla'}
STORE_FIRST = re.compile(r'^(st|cmp|tw|dcb|icb|mt|b)')  # first operand is not a destination


def reg_class(r):
    m = REG.match(r)
    if not m:
        return None
    k, n = m.group(1), int(m.group(2))
    if k == 'r':
        if n == 0: return 'r0'
        if n in (1, 2, 13): return 'rsys'
        return 'gpr_saved' if n >= 14 else 'gpr_vol'
    return 'fpr_saved' if n >= 14 else 'fpr_vol'


def ops(ins):
    """formatted 'lwz r3, 0x8(r4)' -> ('lwz', ['r3', '0x8', 'r4'])"""
    f = ins['formatted']
    parts = f.split(None, 1)
    mn = parts[0]
    args = []
    if len(parts) > 1:
        for a in re.split(r',\s*', parts[1]):
            m = re.match(r'^(.*)\((\w+)\)$', a)
            if m:
                args += [m.group(1), m.group(2)]
            else:
                args.append(a)
    return mn, args


def norm(ins):
    mn, args = ops(ins)
    return (mn, tuple('R' if REG.match(a) and a[0] == 'r' else 'F' if REG.match(a) else a for a in args))


def run_objdiff(unit, fn):
    r = subprocess.run([OBJDIFF, 'diff', '-1', unit['target_path'], '-2', unit['base_path'], '-o', '-', fn],
                       capture_output=True, text=True, timeout=120)
    try:
        d = json.loads(r.stdout)
    except ValueError:
        return None
    def pick(side):
        for s in d.get(side, {}).get('symbols', []):
            if s.get('instructions') and (s['name'] == fn or s['name'].startswith(fn + '__')):
                return s
        return None
    L, R = pick('left'), pick('right')
    if not L or not R:
        return None
    return L['instructions'], R['instructions']


def defining(left, i, reg):
    """Walk back in the target from i to the instruction that writes reg."""
    for j in range(i, -1, -1):
        ins = left[j].get('instruction')
        if not ins: continue
        mn, a = ops(ins)
        if not a or a[0] != reg or STORE_FIRST.match(mn):
            # lwzu/lbzu etc write their base too
            if mn.endswith('u') and len(a) >= 3 and a[-1] == reg and not mn.startswith('st'):
                return j, mn, a
            continue
        return j, mn, a
    return None


def value_kind(left, i, reg, calls):
    d = defining(left, i, reg)
    if not d:
        return 'param' if reg in ('r3', 'r4', 'r5', 'r6', 'r7', 'r8', 'f1', 'f2', 'f3') else 'other'
    j, mn, a = d
    src = a[1:] if len(a) > 1 else []
    if mn == 'addi' and src and src[0] == 'r1': return '&local'
    if mn in ('lis',) or (mn == 'addi' and any('@' in s for s in src)): return 'global'
    if mn in ('li', 'lis'): return 'const'
    if mn in ('lfs', 'lfd') and any('@' in s or 'lbl_' in s for s in src): return 'float_const'
    if mn in ('lfs', 'lfd') and len(src) >= 2 and src[1] == 'r2': return 'float_const'
    if mn == 'mr' and src:
        if any(c < j and j - c <= 3 for c in calls) and src[0] in ('r3', 'f1'): return 'call_result'
        if j < 12 and src[0] in ('r3', 'r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10'): return 'param'
        return value_kind(left, j - 1, src[0], calls) if j > 0 else 'param'
    if mn == 'fmr' and src:
        if j < 12 and src[0] in ('f1', 'f2', 'f3', 'f4'): return 'param'
        return value_kind(left, j - 1, src[0], calls) if j > 0 else 'param'
    if mn == 'addi' and src and src[0] == a[0]: return 'induction'
    if mn in ('add', 'addi', 'mulli', 'slwi', 'rlwinm'): return 'address_calc'
    if mn.startswith('l'): return 'load'
    if mn.startswith('f'): return 'float_arith'
    return 'other'


def perm_shape(mapping):
    """mapping: target reg -> our reg (only where they differ)."""
    seen, cycles, chains = set(), [], []
    for a in mapping:
        if a in seen: continue
        cur, path = a, []
        while cur in mapping and cur not in seen:
            seen.add(cur); path.append(cur); cur = mapping[cur]
        (cycles if cur == a else chains).append(path)
    groups = cycles + chains
    if not groups: return 'none'
    def num(r): return int(r[1:])
    deltas = {num(mapping[a]) - num(a) for a in mapping}
    if len(mapping) >= 3 and len(deltas) <= 2 and all(abs(x) == 1 for x in deltas) and len(groups) == 1:
        return 'shift'
    if len(groups) == 1:
        g = groups[0]
        return 'swap' if len(g) == 2 and g in cycles else ('cycle' if g in cycles else 'chain')
    return 'multi'


def analyze(left, right):
    n = max(len(left), len(right))
    calls = [i for i, x in enumerate(left) if x.get('instruction') and ops(x['instruction'])[0] in BRANCH_CALL]
    mapping_votes = collections.Counter()
    kinds = collections.Counter()
    first = None
    nonreg_arg = 0
    diff_lines = 0
    window_l, window_r = [], []
    for i in range(n):
        L = left[i] if i < len(left) else {}
        R = right[i] if i < len(right) else {}
        dk = L.get('diff_kind') or R.get('diff_kind')
        if not dk: continue
        diff_lines += 1
        kinds[dk] += 1
        li, ri = L.get('instruction'), R.get('instruction')
        if li: window_l.append(norm(li))
        if ri: window_r.append(norm(ri))
        if dk == 'DIFF_ARG_MISMATCH' and li and ri:
            ml, al = ops(li); mr_, ar = ops(ri)
            for x, y in zip(al, ar):
                if x == y: continue
                if REG.match(x) and REG.match(y):
                    mapping_votes[(x, y)] += 1
                    if first is None: first = (i, x)
                else:
                    nonreg_arg += 1
        elif first is None and li:
            m, a = ops(li)
            rr = [x for x in a if REG.match(x)]
            if rr: first = (i, rr[0])
    # resolve mapping: for each target reg take the most-voted our reg
    mapping = {}
    for (x, y), c in mapping_votes.most_common():
        if x not in mapping and y not in mapping.values():
            mapping[x] = y
    other = kinds['DIFF_REPLACE'] + kinds['DIFF_INSERT'] + kinds['DIFF_DELETE'] + kinds['DIFF_OP_MISMATCH']
    if not mapping:
        kind = 'no_reg'
    elif not other and not nonreg_arg:
        kind = 'reg_only'
    elif collections.Counter(m for m, _ in window_l) == collections.Counter(m for m, _ in window_r) and not nonreg_arg:
        kind = 'reg+sched'
    elif not nonreg_arg and other <= 6:
        kind = 'reg+sched'  # small mr/li/addi rematerialisation, see 'remat' below
    else:
        kind = 'reg+other'
    classes = sorted({reg_class(x) for x in mapping} | {reg_class(y) for y in mapping.values()} - {None})
    shape = perm_shape(mapping)
    where = 'body'
    val = None
    if first:
        i, reg = first
        # prologue: before the first non-save instruction after stwu
        pro = 0
        for j, x in enumerate(left):
            ins = x.get('instruction')
            if not ins: continue
            m, a = ops(ins)
            if m in ('stwu', 'mflr', 'stmw', 'stfd', 'psq_st') or (m == 'stw' and a and a[-1] == 'r1') \
                    or (m == 'mr' and j < 10) or (m == 'addi' and a[1:2] == ['r1'] and j < 6):
                pro = j + 1
                continue
            break
        def addr(x):
            ins = x.get('instruction') or {}
            return int(ins.get('address', '0'))
        backs = []
        for x in left:
            ins = x.get('instruction')
            if ins and 'branch_dest' in ins and int(ins['branch_dest']) < addr(x):
                backs.append((int(ins['branch_dest']), addr(x)))
        here = next((addr(left[k]) for k in range(i, len(left)) if left[k].get('instruction')), 0)
        loop = any(s <= here <= e for s, e in backs)
        has_switch = any(x.get('instruction') and ops(x['instruction'])[0] == 'bctr' for x in left)
        tail = sum(1 for x in left[i:] if x.get('instruction'))
        if i < pro: where = 'prologue'
        elif loop: where = 'loop'
        elif any(c < i and i - c <= 4 for c in calls): where = 'after_call'
        elif has_switch and any(x.get('instruction') and ops(x['instruction'])[0] == 'bctr' for x in left[max(0, i - 40):i]):
            where = 'switch'
        elif tail <= 12: where = 'epilogue'
        val = value_kind(left, i, reg, calls)
    remat = False
    for i in range(n):
        L = left[i] if i < len(left) else {}
        R = right[i] if i < len(right) else {}
        if (L.get('diff_kind') or R.get('diff_kind')) == 'DIFF_REPLACE' and L.get('instruction') and R.get('instruction'):
            a, b = ops(L['instruction'])[0], ops(R['instruction'])[0]
            if {a, b} & {'mr', 'fmr'} and a != b: remat = True
    cs = set(classes)
    family = ('fpr' if cs <= {'fpr_saved', 'fpr_vol'} else 'r0' if 'r0' in cs else
              'saved' if cs <= {'gpr_saved'} else 'volatile' if cs <= {'gpr_vol'} else
              'saved+volatile' if cs <= {'gpr_saved', 'gpr_vol'} else 'mixed') if cs else '-'
    return dict(family=family, kind=kind, classes='+'.join(classes) or '-', shape=shape, where=where, value=val or '-',
                mapping=' '.join(f'{a}->{b}' for a, b in sorted(mapping.items(), key=lambda t: (t[0][0], int(t[0][1:])))),
                diff_lines=diff_lines, remat=remat, nonreg_arg=nonreg_arg, ninstr=len([x for x in left if x.get('instruction')]))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--min', type=float, default=97.0)
    ap.add_argument('--claims')
    ap.add_argument('--json', default='build/regswap_census.json')
    ap.add_argument('--md')
    ap.add_argument('-j', type=int, default=os.cpu_count() or 4)
    a = ap.parse_args()
    rep = json.load(open('build/GNLJ82/report.json'))
    units = {u['name']: u for u in json.load(open('objdiff.json'))['units']}
    claimed = {}
    if a.claims:
        for line in open(a.claims):
            p = line.split()
            if len(p) >= 2: claimed[p[1]] = p[0]
    jobs = []
    for u in rep['units']:
        ou = units.get(u['name'])
        if not ou or 'base_path' not in ou: continue
        for f in u.get('functions', []):
            p = f.get('fuzzy_match_percent', 0)
            if a.min <= p < 100:
                jobs.append((u['name'], ou, f['name'], p, f.get('size')))

    def work(job):
        uname, ou, fn, p, size = job
        try:
            r = run_objdiff(ou, fn)
        except Exception as e:
            r = None
        if not r:
            return dict(unit=uname, fn=fn, pct=p, kind='error')
        res = analyze(*r)
        src = ou.get('metadata', {}).get('source_path', '')
        cp = src[4:] if src.startswith('src/') else src
        res.update(unit=uname, fn=fn, pct=round(p, 2), src=src, claim=claimed.get(cp, ''))
        return res

    with ThreadPoolExecutor(a.j) as ex:
        rows = list(ex.map(work, jobs))
    json.dump(rows, open(a.json, 'w'), indent=1)
    if a.md:
        write_md(rows, a.md, a.min)
    c = collections.Counter((r.get('family'), r['kind']) for r in rows)
    for k, v in c.most_common(25):
        print(v, *k)


def write_md(rows, path, mn):
    out = []
    w = out.append
    w(f'# Register-diff census of near-miss functions (>= {mn}%)\n')
    w('Generated by `python3 tools/regswap_classify.py --md docs/reports/regswap_census.md`. '
      'Signature = kind / register class / permutation shape / where it starts / what the '
      "target's first mismatching register holds. See the script docstring for the terms and "
      'docs/regalloc_patterns.md for the fixes. `[claimed]` = another contributor holds the TU.\n')
    by = collections.Counter(r['kind'] for r in rows)
    w('## Totals\n')
    w('| kind | functions |\n|---|---|')
    for k, v in by.most_common(): w(f'| {k} | {v} |')
    w('')
    groups = collections.defaultdict(list)
    for r in rows:
        if r['kind'] == 'error': continue
        groups[(r['family'], r['kind'])].append(r)
    w('## Groups (register family / kind)\n')
    w('family = which registers are permuted: saved (r14-r31 only), volatile (r3-r12 only), '
      'saved+volatile, r0 (r0 is one of them), fpr, mixed (GPR and FPR).\n')
    w('| # | family | kind | shape (counts) | where (counts) | value (counts) |\n|---|---|---|---|---|---|')
    order = sorted(groups.items(), key=lambda t: -len(t[1]))
    def cnt(rs, k):
        return ', '.join(f'{x} {n}' for x, n in collections.Counter(r[k] for r in rs).most_common())
    for (f, k), rs in order:
        w(f'| {len(rs)} | {f} | {k} | {cnt(rs, "shape")} | {cnt(rs, "where")} | {cnt(rs, "value")} |')
    w('')
    for (f, k), rs in order:
        w(f'### {f} / {k} ({len(rs)})\n')
        w('| function | % | lines | shape | where | value | mapping (target->ours) | TU |\n|---|---|---|---|---|---|---|---|')
        for r in sorted(rs, key=lambda r: (r['shape'], -r['pct'])):
            tag = ' [claimed]' if r.get('claim') and r['claim'] != 'naari3' else (' [ours]' if r.get('claim') else '')
            rm = ' remat' if r.get('remat') else ''
            w(f"| {r['fn']} | {r['pct']} | {r['diff_lines']}{rm} | {r['shape']} | {r['where']} | {r['value']} | {r['mapping']} | {r['src'][4:]}{tag} |")
        w('')
    per_tu = collections.defaultdict(list)
    for r in rows:
        if r['kind'] != 'error': per_tu[r.get('src', '')].append(r)
    many = sorted(((k, v) for k, v in per_tu.items() if len(v) >= 3), key=lambda t: -len(t[1]))
    if many:
        w('## TUs with three or more near misses\n')
        w('A shared cause (compiler version, pragma, a common inline) is likely; fix one, rerun the rest.\n')
        w('| TU | count | functions |\n|---|---|---|')
        for k, v in many:
            tag = ' [claimed]' if v[0].get('claim') and v[0]['claim'] != 'naari3' else ''
            w(f"| {k[4:]}{tag} | {len(v)} | {', '.join(r['fn'] for r in sorted(v, key=lambda r: -r['pct']))} |")
        w('')
    err = [r for r in rows if r['kind'] == 'error']
    if err:
        w('## Not diffed (objdiff gave no symbol)\n')
        w(', '.join(f"{r['fn']}" for r in err))
    open(path, 'w').write('\n'.join(out) + '\n')


if __name__ == '__main__':
    main()
