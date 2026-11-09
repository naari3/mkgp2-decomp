#!/usr/bin/env python3
"""autosweep.py - unattended sweep of mechanical matching fixes, mkgp2-decomp.

Run from the repo root after a normal full build (build/GNLJ82/report.json must exist).
Needs cperm.py beside it (Builder / asm parsing are reused).

  python3 autosweep.py list  [--all]          # NonMatching fns per TU, skips TUs with an open unit-claim
  python3 autosweep.py cc    [--jobs 4] [--units u1,u2] [--out DIR]
        Per-TU compiler version switch (GC/1.2.5n .. 2.7, plus a few flag variants).
        A HIT = some fn that was not 0 diff becomes 0 and no fn that was 0 gets worse.
        Results: DIR/cc.json (default /tmp/autosweep). Apply a hit with `apply`.
  python3 autosweep.py apply UNIT VERSION [FLAGS]
        Sets mw_version= (and appends extra_cflags) on that Object(...) line in configure.py.
  python3 autosweep.py perm  [--max-score 40] [--minutes 8] [--workers 4] [--units ...]
        Runs cperm.py (text permuter, C and C++) on every remaining near miss, smallest
        score first, with the best compiler found by `cc`. 0s land in DIR/perm/<fn>/best_00000.*
  python3 autosweep.py verify UNIT
        Rebuilds that TU for real and prints its functions' fuzzy % from a fresh report.

Scores are cperm's weighted asm diff of dtk disasm (labels and @N names normalized),
so a 0 is a candidate: land it only after a clean build (`rm -rf build/GNLJ82/src`),
`ninja` main.dol OK and the report showing the fn at 100%.
Claims: open GitHub `unit-claim` issues (title + body) are fetched with `gh api`; a TU
whose path appears in any of them is skipped (use --all to include them anyway).
"""
import argparse, concurrent.futures as cf, json, os, re, shlex, subprocess, sys, time
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cperm  # noqa: E402

OUT = '/tmp/autosweep'
VERSIONS = ['1.2.5n', '1.3', '1.3.2', '1.3.2r', '2.0', '2.5', '2.6', '2.7']
FLAGS = ['', '-use_lmw_stmw on', '-inline deferred', '-fp_contract off']
REPO = 'naari3/mkgp2-decomp'

# ------------------------------------------------------------------ inputs

def report():
    return json.load(open('build/GNLJ82/report.json'))

def claims():
    """Concatenated title+body text of every open unit-claim issue."""
    try:
        r = subprocess.run(['gh', 'api', '-X', 'GET', 'search/issues', '--paginate',
                            '-f', f'q=repo:{REPO} is:issue label:unit-claim state:open', '-f', 'per_page=100',
                            '--jq', '.items[] | "#\\(.number) \\(.title)\\n\\(.body)"'],
                           capture_output=True, text=True, timeout=120)
        return r.stdout
    except Exception as e:
        print('WARNING: could not fetch claims:', e, file=sys.stderr)
        return ''

def nonmatching_objects():
    """configure.py source paths marked NonMatching -> line number."""
    out = {}
    for i, l in enumerate(open('configure.py')):
        m = re.search(r'Object\(\s*NonMatching\s*,\s*"([^"]+)"', l)
        if m: out[m.group(1)] = i
    return out

def candidates(include_claimed=False, units=None):
    nm = nonmatching_objects(); cl = '' if include_claimed else claims()
    res = []
    for u in report()['units']:
        sp = u.get('metadata', {}).get('source_path', '')
        if not sp.startswith('src/'): continue
        path = sp[4:]
        if path not in nm or not os.path.exists(sp): continue
        obj = os.path.splitext(path)[0]
        if units and obj not in units and path not in units: continue
        bad = [(f['name'], f.get('fuzzy_match_percent', 0)) for f in u.get('functions', [])
               if f.get('fuzzy_match_percent', 0) < 100]
        if not bad: continue
        claimed = bool(cl) and (path in cl or obj + '.' in cl)
        if claimed and not include_claimed: continue
        res.append(dict(unit=u['name'], src=sp, obj=obj, fns=bad, claimed=claimed))
    return res

# ------------------------------------------------------------------ asm

def all_bodies(s_path):
    text = open(s_path, errors='replace').read(); out = {}
    for m in re.finditer(r'^\.fn ([^,\s]+),', text, re.M):
        out[m.group(1)] = [JT.sub('@N', x) for x in cperm.asm_body(text[m.start():], m.group(1))]
    return out

JT = re.compile(r'jumptable_[0-9A-Fa-f]+')

def target_bodies(obj, wdir):
    s = os.path.join(wdir, 'target.s')
    if not os.path.exists(s):
        o = f'build/GNLJ82/obj/{obj}.o'
        if not os.path.exists(o): return {}
        subprocess.run(['build/tools/dtk', 'elf', 'disasm', o, s], capture_output=True)
    return all_bodies(s) if os.path.exists(s) else {}

class TUBuilder(cperm.Builder):
    """cperm.Builder that returns every function of the TU, with optional extra flags."""
    def __init__(self, obj, cc, flags, wdir):
        os.makedirs(wdir, exist_ok=True)
        super().__init__(obj, '', cc, wdir)
        if flags:
            i = self.args.index('-c'); self.args[i:i] = shlex.split(flags)

    def build_all(self, src_path):
        if self.build(src_path) is None and not os.path.exists(os.path.join(self.wdir, 'out.s')):
            return None
        s = os.path.join(self.wdir, 'out.s')
        return all_bodies(s) if os.path.exists(s) else None

    def build(self, src_path):
        s = os.path.join(self.wdir, 'out.s')
        if os.path.exists(s): os.remove(s)
        return super().build(src_path)

def scores(tgt, mine):
    return {fn: (cperm.score(body, mine.get(fn, [])) if mine is not None else 10**6) for fn, body in tgt.items()}

# ------------------------------------------------------------------ cc sweep

def cur_version(obj):
    cmd = subprocess.run(['ninja', '-t', 'commands', f'build/GNLJ82/src/{obj}.o'],
                         capture_output=True, text=True).stdout
    m = re.search(r'GC/([^/]+)/mwcceppc', cmd)
    return m.group(1) if m else '?'

def sweep_unit(c, out, flags_list):
    obj = c['obj']; wd = os.path.join(out, 'cc', obj.replace('/', '_'))
    os.makedirs(wd, exist_ok=True)
    tgt = target_bodies(obj, wd)
    if not tgt: return dict(c, error='no target obj')
    names = [f for f, _ in c['fns']] + [f for f in tgt if f not in dict(c['fns'])]
    tgt = {f: tgt[f] for f in names if f in tgt}
    base_v = cur_version(obj)
    try:
        b0 = TUBuilder(obj, None, '', os.path.join(wd, 'base'))
    except Exception as e:
        return dict(c, error=f'builder: {e!r}')
    base = scores(tgt, b0.build_all(c['src']))
    res = dict(c, version=base_v, base={f: s for f, s in base.items() if s}, hits=[], improved=[])
    for v in VERSIONS:
        for fl in flags_list:
            if v == base_v and not fl: continue
            try:
                b = TUBuilder(obj, v, fl, os.path.join(wd, f'{v}_{re.sub(r"[^a-z0-9]", "", fl)}'))
                sc = scores(tgt, b.build_all(c['src']))
            except Exception:
                continue
            worse = [f for f in tgt if sc[f] > base[f]]
            newzero = [f for f in tgt if sc[f] == 0 and base[f] > 0]
            if worse: continue
            rec = dict(version=v, flags=fl, fixed=newzero, total=sum(sc.values()), base_total=sum(base.values()),
                       left={f: s for f, s in sc.items() if s})
            if newzero: res['hits'].append(rec)
            elif rec['total'] < rec['base_total']: res['improved'].append(rec)
    return res

def cmd_cc(a):
    cs = candidates(a.all, a.units)
    print(f'{len(cs)} TUs, {sum(len(c["fns"]) for c in cs)} NonMatching fns', flush=True)
    flags = FLAGS if a.flags else ['']
    out = []; path = os.path.join(a.out, 'cc.json')
    with cf.ProcessPoolExecutor(a.jobs) as ex:
        futs = {ex.submit(sweep_unit, c, a.out, flags): c for c in cs}
        for f in cf.as_completed(futs):
            try: r = f.result()
            except Exception as e: r = dict(futs[f], error=repr(e))
            out.append(r)
            if r.get('hits'):
                best = max(r['hits'], key=lambda h: (len(h['fixed']), -h['total']))
                print(f'HIT  {r["obj"]}: {r.get("version")} -> {best["version"]} {best["flags"]!r} fixes {best["fixed"]}', flush=True)
            elif r.get('improved'):
                best = min(r['improved'], key=lambda h: h['total'])
                print(f'impr {r["obj"]}: {best["base_total"]} -> {best["total"]} with {best["version"]} {best["flags"]!r}', flush=True)
            json.dump(out, open(path, 'w'), indent=1)
    print('wrote', path)

# ------------------------------------------------------------------ apply

def cmd_apply(a):
    path = a.unit if '.' in os.path.basename(a.unit) else None
    nm = nonmatching_objects()
    if not path:
        path = next((p for p in nm if os.path.splitext(p)[0] == a.unit.removeprefix('main/')), None)
    if path not in nm: sys.exit('not a NonMatching Object: ' + a.unit)
    L = open('configure.py').read().split('\n'); i = nm[path]; l = L[i]
    v = a.version if a.version.startswith('GC/') else 'GC/' + a.version
    if 'mw_version=' in l: l = re.sub(r'mw_version="[^"]*"', f'mw_version="{v}"', l)
    else: l = re.sub(r'\)(\s*,?\s*(#.*)?)$', f', mw_version="{v}")\\1', l, count=1)
    if a.flags:
        new = ', '.join(f'"{x}"' for x in re.findall(r'-\S+(?: (?!-)\S+)?', a.flags))
        if 'extra_cflags=[' in l: l = l.replace('extra_cflags=[', f'extra_cflags=[{new}, ', 1)
        else: l = re.sub(r'\)(\s*,?\s*(#.*)?)$', f', extra_cflags=[{new}])\\1', l, count=1)
    L[i] = l; open('configure.py', 'w').write('\n'.join(L)); print(l.strip())

# ------------------------------------------------------------------ perm

def cmd_perm(a):
    if a.list:
        todo = []
        for l in open(a.list):
            if not l.strip() or l.startswith('#'): continue
            i, sc, src, obj, fn, cc = l.split()
            todo.append((int(i), int(sc), src, obj, fn, None if cc == '-' else cc))
        if a.shard:
            k, n = map(int, a.shard.split('/')); todo = [t for t in todo if t[0] % n == k]
        return run_perm(a, [t[1:] for t in todo])
    ccres = {}
    p = os.path.join(a.out, 'cc.json')
    if os.path.exists(p):
        for r in json.load(open(p)): ccres[r['obj']] = r
    todo = []
    for c in candidates(a.all, a.units):
        r = ccres.get(c['obj']) or {}
        base = r.get('base')
        cc = None
        if r.get('improved') or r.get('hits'):
            best = min(r.get('hits', []) + r.get('improved', []), key=lambda h: h['total'])
            if not best['flags']: cc = best['version']; base = best['left']
        if base is None:
            wd = os.path.join(a.out, 'cc', c['obj'].replace('/', '_')); os.makedirs(wd, exist_ok=True)
            tgt = target_bodies(c['obj'], wd)
            try: base = {f: s for f, s in scores(tgt, TUBuilder(c['obj'], None, '', os.path.join(wd, 'base')).build_all(c['src'])).items() if s}
            except Exception: continue
        nm = dict(c['fns'])
        for fn, s in base.items():
            if fn in nm and a.min_score <= s <= a.max_score and s > 0: todo.append((s, c['src'], c['obj'], fn, cc))
    todo.sort()
    if a.write_list:
        with open(a.write_list, 'w') as f:
            f.write('# index score src obj fn cc  (autosweep.py perm --list THIS --shard K/N runs index % N == K)\n')
            for i, (s, src, obj, fn, cc) in enumerate(todo): f.write(f'{i} {s} {src} {obj} {fn} {cc or "-"}\n')
        print('wrote', a.write_list, len(todo)); return
    if a.shard:
        k, n = map(int, a.shard.split('/')); todo = todo[k::n]
    run_perm(a, todo)

def run_perm(a, todo):
    print(f'{len(todo)} near misses (score <= {a.max_score})', flush=True)
    me = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'cperm.py')
    log = open(os.path.join(a.out, 'perm.log'), 'a')
    for s, src, obj, fn, cc in todo:
        od = os.path.join(a.out, 'perm', fn)
        if os.path.exists(os.path.join(od, 'done')): continue
        cmd = ['python3', me, src, obj, fn, '--minutes', str(a.minutes), '--workers', str(a.workers), '--out', od]
        if cc: cmd += ['--cc', cc]
        print(f'[{time.strftime("%H:%M:%S")}] {fn} ({obj}) start score {s}', flush=True)
        try:
            r = subprocess.run(cmd, capture_output=True, text=True, timeout=a.minutes * 60 + 120)
            o = r.stdout
        except subprocess.TimeoutExpired as e:
            o = (e.stdout or b'').decode() if isinstance(e.stdout, bytes) else (e.stdout or '')
        log.write(f'=== {fn} {obj} {s}\n{o}\n'); log.flush()
        os.makedirs(od, exist_ok=True); open(os.path.join(od, 'done'), 'w').write(o[-2000:])
        tag = 'MATCH' if 'MATCH ->' in o else (o.strip().splitlines() or ['?'])[-1]
        print(f'    {tag}', flush=True)
        for f in os.listdir(os.path.dirname(os.path.abspath(src))):
            if f.startswith('.cperm_w'): os.remove(os.path.join(os.path.dirname(os.path.abspath(src)), f))

# ------------------------------------------------------------------ verify / list

def cmd_verify(a):
    obj = a.unit.removeprefix('main/')
    subprocess.run(['python3', 'configure.py', '--binutils', 'build/binutils', '--compilers', 'build/compilers',
                    '--wrapper', 'build/tools/wibo'], capture_output=True)
    r = subprocess.run(['ninja', 'build/GNLJ82/report.json'], capture_output=True, text=True)
    if r.returncode: print(r.stdout[-2000:]); sys.exit(1)
    for u in report()['units']:
        if u['name'] == 'main/' + obj:
            for f in u.get('functions', []): print(f'{f.get("fuzzy_match_percent", 0):8.3f} {f["name"]}')

def cmd_list(a):
    cs = candidates(a.all, a.units)
    for c in cs:
        print(('C ' if c['claimed'] else '  ') + c['obj'], ' '.join(f'{f}:{p:.1f}' for f, p in c['fns']))
    print(len(cs), 'TUs', sum(len(c['fns']) for c in cs), 'fns')

def main():
    ap = argparse.ArgumentParser(); sp = ap.add_subparsers(dest='cmd', required=True)
    def common(p):
        p.add_argument('--all', action='store_true', help='include TUs with an open unit-claim')
        p.add_argument('--units', type=lambda s: set(s.split(',')))
        p.add_argument('--out', default=OUT)
    p = sp.add_parser('list'); common(p)
    p = sp.add_parser('cc'); common(p); p.add_argument('--jobs', type=int, default=os.cpu_count() or 4)
    p.add_argument('--flags', action='store_true', help=f'also try {FLAGS[1:]}')
    p = sp.add_parser('perm'); common(p); p.add_argument('--max-score', type=int, default=40); p.add_argument('--min-score', type=int, default=1)
    p.add_argument('--shard', help='K/N: only near misses with index %% N == K (0-based; for parallel threads)')
    p.add_argument('--list', help='candidate list written by --write-list (shared by all shards)')
    p.add_argument('--write-list', help='write the ordered candidate list to this file and exit')
    p.add_argument('--minutes', type=float, default=8); p.add_argument('--workers', type=int, default=os.cpu_count() or 4)
    p = sp.add_parser('apply'); p.add_argument('unit'); p.add_argument('version'); p.add_argument('flags', nargs='?')
    p = sp.add_parser('verify'); p.add_argument('unit')
    a = ap.parse_args()
    if hasattr(a, 'out'): os.makedirs(a.out, exist_ok=True)
    dict(list=cmd_list, cc=cmd_cc, perm=cmd_perm, apply=cmd_apply, verify=cmd_verify)[a.cmd](a)

if __name__ == '__main__':
    main()
