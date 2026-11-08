#!/usr/bin/env python3
"""Pool-ownership audit: find functions whose TARGET code addresses data
through a pooled base (one `lis/addi rB, lbl_X@ha/@l`, then `addi rY, rB, off`
or `off(rB)` reaching past lbl_X into neighbouring objects), and check which
TU owns that data in splits.txt.

CW only does this for objects DEFINED in the same TU (section-anchor
addressing, TIPS "Pooled-data lis" / "Section-anchor addressing"), so:
  OWN-SELF   pool owned by the function's own TU            -> nothing to do
  UNOWNED    pool range owned by no TU (auto_ data)          -> the TU should own it
  OTHER      pool owned by another TU                        -> the fn belongs to that TU
                                                                (merge) or the owner is wrong
Only functions that are still NonMatching (<100% in report.json) or written
as inline asm (tools/scan_asm_fns.py) are listed.

Usage (after ninja): python3 tools/pool_audit.py [--claims FILE] [--md docs/pool_audit.md] [--all]
"""
import argparse, bisect, collections, os, re, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import tu_audit as T  # noqa: E402

INSN = re.compile(r"^/\* ([0-9A-F]{8}) [0-9A-F]{8}  [0-9A-F ]{11} \*/\t(\S+)\s*(.*)$")
FN = re.compile(r'^\.fn ("[^"]+"|[^,\s]+)')
ENDFN = re.compile(r'^\.endfn')
HA = re.compile(r'^(r\d+),\s*("[^"]+"|[^\s@]+)@ha$')
LO = re.compile(r'^(r\d+),\s*(r\d+),\s*("[^"]+"|[^\s@]+)@l$')
SDA = re.compile(r'^(r\d+),\s*(r2|r13),\s*("[^"]+"|[^\s@]+)@sda21$')
DISP = re.compile(r'(-?0x[0-9a-fA-F]+|-?\d+)\((r\d+)\)')
NOWRITE = ('st', 'cmp', 'tw', 'dcb', 'icb', 'b', 'mt')


def ival(s):
    return int(s, 16) if s.lstrip('-').startswith('0x') else int(s)


def scan_fn(lines):
    """-> {base symbol: set(offsets)} for pooled bases in one function body."""
    ha, base = {}, {}           # reg -> sym (lis), reg -> sym (full address)
    out = collections.defaultdict(set)
    for op, args in lines:
        a = args.replace(' ', '')
        ops = a.split(',') if a else []
        m = HA.match(a) if op == 'lis' else None
        if m:
            ha[m.group(1)] = m.group(2).strip('"'); base.pop(m.group(1), None); continue
        m = LO.match(a) if op == 'addi' else None
        if m and m.group(2) in ha:
            base[m.group(1)] = ha[m.group(2)].strip('"')
            if m.group(1) != m.group(2): pass
            continue
        m = SDA.match(a) if op == 'addi' else None
        if m:
            base[m.group(1)] = m.group(3).strip('"'); continue
        # uses
        if op == 'addi' and len(ops) == 3 and ops[1] in base:
            try: out[base[ops[1]]].add(ival(ops[2]))
            except ValueError: pass
        for d, r in DISP.findall(a):
            if r in base: out[base[r]].add(ival(d))
        if op.endswith('x') and len(ops) == 3 and (ops[1] in base or ops[2] in base) and op[:1] in 'lsa':
            out[base[ops[1] if ops[1] in base else ops[2]]].add('x')
        # invalidate written register
        if ops and not op.startswith(NOWRITE) and re.fullmatch(r'r\d+', ops[0]):
            if not (op == 'addi' and len(ops) == 3 and ops[1] in base and ops[0] == ops[1] and False):
                base.pop(ops[0], None); ha.pop(ops[0], None)
        if op.startswith('bl'):  # volatile regs die at calls
            for r in [r for r in base if int(r[1:]) <= 12]: base.pop(r)
            for r in [r for r in ha if int(r[1:]) <= 12]: ha.pop(r)
    return out


def parse_bodies():
    fns = {}
    for dp, _, fs in os.walk(T.ASM_DIR):
        for f in fs:
            if not f.endswith('.s'): continue
            cur = None; body = []
            for line in open(os.path.join(dp, f), encoding='utf-8', errors='replace'):
                m = FN.match(line)
                if m: cur = m.group(1).strip('"'); body = []; continue
                if cur and ENDFN.match(line): fns[cur] = body; cur = None; continue
                if cur:
                    m = INSN.match(line)
                    if m: body.append((m.group(2), m.group(3)))
    return fns


def asm_fns():
    try:
        import scan_asm_fns
        from pathlib import Path
        r = scan_asm_fns.scan_repo(Path(T.ROOT))
        names = set()
        for v in (r.get('asm_fns') or r.get('fns') or []):
            names.add(v['name'] if isinstance(v, dict) else v)
        return names
    except Exception:
        return set()


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--claims'); ap.add_argument('--md', default='docs/pool_audit.md')
    ap.add_argument('--all', action='store_true', help='also list matched functions')
    a = ap.parse_args()
    claims = T.load_claims(a.claims, False) if a.claims else ()
    m = T.Model(open(os.path.join(T.ROOT, 'config', T.VER, 'splits.txt')).read(), claims)
    bodies = parse_bodies()
    asmset = asm_fns()
    # symbol table sorted per section for "which object is base+off"
    persec = collections.defaultdict(list)
    for ad, o in m.objs.items():
        if o['kind'] != 'fn': persec[o['sec']].append((ad, o['size'], o['name']))
    for v in persec.values(): v.sort()
    starts = {s: [x[0] for x in v] for s, v in persec.items()}

    def obj_at(sec, ad):
        i = bisect.bisect_right(starts[sec], ad) - 1
        return persec[sec][i] if i >= 0 else None

    rows = []
    for name, body in bodies.items():
        fa = m.byname.get(name)
        if fa is None or m.objs.get(fa, {}).get('kind') != 'fn': continue
        uid = m.fn_unit(fa)
        if uid is None: continue
        u = m.units[uid]
        rep = m.report.get(u['stem']) or m.report.get(u['name']) or {}
        pct = rep.get(fa)
        is_asm = name in asmset or u['auto']
        nonm = pct is not None and pct < 100.0
        if not (a.all or is_asm or nonm): continue
        for bsym, offs in scan_fn(body).items():
            ba = m.byname.get(bsym)
            bo = m.objs.get(ba) if ba is not None else None
            if not bo or bo['kind'] == 'fn': continue
            sec = bo['sec']
            if sec not in persec: continue
            num = sorted(o for o in offs if o != 'x')
            # pooled = reaches an object other than the base symbol
            hit = set()
            for off in num:
                ob = obj_at(sec, ba + off)
                if ob and ob[0] != ba: hit.add(ob)
            if not hit and 'x' not in offs: continue
            if not hit and bo['size'] and max(num or [0]) < bo['size']: continue
            span = (ba, max([ba + bo['size']] + [x[0] + x[1] for x in hit]))
            owners = collections.Counter(m.unit_at(sec, x) for x in [ba] + [h[0] for h in hit])
            own = owners.most_common(1)[0][0]
            if own == uid: cls = 'OWN-SELF'
            elif own is None: cls = 'UNOWNED'
            else: cls = 'OTHER'
            if len(owners) > 1: cls += '+MIXED'
            users = m.user_units(ba) | {uid}
            rows.append(dict(fn=name, fa=fa, tu=u['name'], uid=uid, pct=pct, asm=is_asm, sec=sec, base=bsym,
                             span=span, nobj=len(hit) + 1, cls=cls,
                             owner=(m.units[own]['name'] if own is not None else '-'),
                             claim=', '.join(dict.fromkeys(c for c in (m.claim_of(uid), m.claim_of(own) if own is not None else None) if c)),
                             users=sorted(m.units[x]['name'] for x in users if x is not None)))
    rows.sort(key=lambda r: (r['cls'].startswith('OWN-SELF'), r['cls'], r['span'][0]))
    # concrete fix per row: which TU should own which range, merge or not
    groups = collections.defaultdict(set)
    for r in rows:
        if r['cls'].startswith('UNOWNED'): groups[(r['sec'], r['span'][0])].add(r['tu'])
    for r in rows:
        S, E = r['span']; rng = f"{r['sec']} {S:08X}..{E:08X}"
        if r['cls'].startswith('OWN-SELF'): r['fix'] = ''
        elif r['cls'].startswith('UNOWNED'):
            tus = sorted(groups[(r['sec'], S)])
            r['fix'] = (f"merge {' + '.join(tus)}; merged TU owns {rng}" if len(tus) > 1
                        else f"{r['tu']} owns {rng} (no merge)")
        else:
            r['fix'] = f"merge {r['tu']} into {r['owner']} (owner already has {rng})"
    def cl(who):
        return who or ''
    cnt = collections.Counter(r['cls'] for r in rows)
    md = ['# Pool-ownership audit', '',
          'Generated by `tools/pool_audit.py`. A row is a function (NonMatching or inline asm) whose target',
          'code reaches several data objects from one hoisted base (`lis/addi` or `addi rX, r2/r13`).',
          'CW only does that for objects the same TU defines, so the pool should be owned by the',
          "function's TU. UNOWNED: no TU owns the range (give it to the TU, KartPreview 489e672c).",
          'OTHER: another TU owns it (merge the function into that TU, or fix the owner).', '',
          'Counts: ' + ', '.join(f'{k} {v}' for k, v in sorted(cnt.items())), '',
          'fix: the concrete change. "X owns RANGE": add a `.sec start..end` split for RANGE to X in',
          'config/GNLJ82/splits.txt and define every object of RANGE in X before its functions',
          '(statics for TU-private ones, global `lbl_` names for ones other TUs reference; wrap',
          'unreferenced ones in `#pragma force_active on/reset`). RANGE is the part the function',
          'reaches; extend it to the TU\'s real rodata start (often the common float table',
          '{1.0, 0.7, 0.9, 0, 500, ...}) and add a pad symbol if the split starts after padding.',
          'claim: open unit-claim issue (login #number) on the function TU or the owner TU.', '',
          '| class | function | TU | % | sec | base | span | objs | owner | other users | claim | fix |',
          '| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |']
    for r in rows:
        pct = 'asm' if r['asm'] and (r['pct'] is None or r['pct'] >= 100) else ('%.2f' % r['pct'] if r['pct'] is not None else '?')
        others = [x for x in r['users'] if x != r['tu']]
        md.append(f"| {r['cls']} | `{r['fn']}` | {r['tu']} | {pct} | {r['sec']} | `{r['base']}` | "
                  f"{r['span'][0]:08X}..{r['span'][1]:08X} | {r['nobj']} | {r['owner']} | "
                  f"{', '.join(others[:4])}{' …' if len(others) > 4 else ''} | {cl(r['claim'])} | {r['fix']} |")
    open(os.path.join(T.ROOT, a.md), 'w').write('\n'.join(md) + '\n')
    print(cnt); print('wrote', a.md)


if __name__ == '__main__':
    main()
