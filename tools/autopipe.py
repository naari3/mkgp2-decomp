#!/usr/bin/env python3
"""autopipe.py: unattended brute-force matching pipeline.

Loops over the near-miss functions of report.json (highest fuzzy % first) and,
for each one, runs the existing tools in order:

  1. pragmasweep  (tools/pragmasweep.py, objdiff scoring, --set all, k=2):
                  compiler version x opt_* pragma pairs around the function
  2. decl order   permutations of the leading plain declarations on the best
                  few settings from stage 1 (exhaustive up to 6 decls)
  3. permuter     cperm.py (setup/tools) on the best stage-1/2 source

A stage-1/2 hit (100%) is applied to the source (and configure.py when the
compiler changes), verified (report.json: the fn is 100% and NO function in
the project got worse; clean build main.dol OK), committed, rebased onto
origin/main and pushed straight to main. A permuter hit is NOT landed: its
source goes to OUT/review/ for a human/Claude rewrite (fakematch rule).

Everything else is parked in the shared queue (setup/tools/queue.py) with the
best score, and appended to OUT/results.jsonl so restarts skip it.

usage (repo root, after a normal build):
  MKGP2_THREAD=autopipeK python3 tools/autopipe.py run --shard K/N [--min 80] [--max-size 4000] [--perm-minutes 8]
                                [--limit N] [--only FN] [--no-push] [--no-perm]
  python3 tools/autopipe.py status

Claims: TUs listed in --claims (default OUT/claims.txt; refresh it from the
open `unit-claim` issues) are skipped, and so is any fn held by another thread
in the queue. The pipeline holds at most one queue item at a time.
Stop switch: create OUT/STOP or /mnt/project-files/setup/GRIND_STOP.
"""
import argparse, glob, importlib.util, json, os, re, shutil, subprocess, sys, time
from datetime import datetime, timezone

ROOT = os.getcwd()
SETUP = '/mnt/project-files/setup'
OUT = os.environ.get('AUTOPIPE_DIR', f'{SETUP}/autopipe')
WHO = os.environ.get('MKGP2_THREAD', 'autopipe')
REPORT = 'build/GNLJ82/report.json'

sys.path.insert(0, os.path.join(ROOT, 'tools'))
import pragmasweep as ps  # noqa: E402


def _load(name, path):
    spec = importlib.util.spec_from_file_location(name, path)
    m = importlib.util.module_from_spec(spec); spec.loader.exec_module(m); return m


Q = _load('mkgp2queue', f'{SETUP}/tools/queue.py')   # (its name shadows stdlib queue)
CPERM = f'{SETUP}/tools/cperm.py'


def log(*a):
    print(f'[{datetime.now().strftime("%H:%M:%S")}]', *a, flush=True)


def sh(cmd, **kw):
    return subprocess.run(cmd, shell=isinstance(cmd, str), capture_output=True, text=True, **kw)


# ------------------------------------------------------------------ report

def load_report():
    rep = json.load(open(REPORT))
    fns = {}
    for u in rep['units']:
        obj = re.sub(r'^main/', '', u['name'])
        for f in u.get('functions', []):
            fns[(obj, f['name'])] = (f.get('fuzzy_match_percent', 0.0), int(f['size']),
                                     f.get('metadata', {}).get('demangled_name'))
    return fns


def nonmatching():
    return {m.group(1): m.group(2) for m in
            re.finditer(r'Object\(NonMatching,\s*"([^"]+)\.(c|cpp|cp)"', open('configure.py').read())}


def candidates(a):
    rep = load_report(); nm = nonmatching()
    out = [(p, obj, fn, size, dm) for (obj, fn), (p, size, dm) in rep.items()
           if obj in nm and a.min <= p < 100 and size <= a.max_size]
    out.sort(key=lambda t: -t[0])
    return out


def claims(path):
    try:
        return {l.strip() for l in open(path) if l.strip() and not l.startswith('#')}
    except OSError:
        return set()


def done_keys():
    """fn -> pct at the time of the last attempt (retry only if the % moved)."""
    d = {}
    for p in glob.glob(f'{OUT}/results*.jsonl'):
        for l in open(p):
            try:
                r = json.loads(l); d[(r['obj'], r['fn'])] = r.get('pct')
            except ValueError:
                pass
    return d


def record(r):
    r['t'] = datetime.now(timezone.utc).isoformat(timespec='seconds')
    # one file per thread: appends from several containers to one file on the
    # rclone mount lose lines (last write wins)
    with open(f'{OUT}/results_{WHO}.jsonl', 'a') as f:
        f.write(json.dumps(r) + '\n')


# ------------------------------------------------------------------ queue claim

def q_claim(fn, obj, pct):
    """Take the open queue item that names fn, or add one. Returns id or None
    (someone else holds it)."""
    st, order = Q.state()
    rx = re.compile(r'\b' + re.escape(fn) + r'\b')
    mine = None
    for i in order:
        s = st[i]
        if not rx.search(s['text']): continue
        if s['status'] == 'claimed' and s['who'] != WHO:
            if datetime.now(timezone.utc) - s['t'] < Q.timedelta(hours=Q.STALE_H):
                return None
        if s['status'] in ('open', 'claimed') and mine is None:
            mine = i
    if mine is None:
        text = f'{fn} | {obj} | {pct:.2f} | autopipe'
        mine = 'N' + Q.hashlib.sha1(text.encode()).hexdigest()[:6]
        if mine not in st:
            Q.append(WHO, 'add', mine, text=text)
    Q.append(WHO, 'take', mine)
    time.sleep(Q.SETTLE)
    st, _ = Q.state()
    s = st.get(mine)
    if s and s['status'] == 'claimed' and s['who'] == WHO:
        return mine
    return None


def q_close(i, op, note):
    Q.append(WHO, op, i, note=note[:300])
    try:
        Q.render()
    except Exception:
        pass


# ------------------------------------------------------------------ stages

def stage_sweep(u, d, fn, a):
    """Stage 1 (pragmas x cc) and 2 (decl order). Returns sorted [(score, cc, prags, order)]."""
    import itertools, random
    from concurrent.futures import ThreadPoolExecutor
    ps.OBJDIFF = True
    prag = ps.PRAGMA_SETS['all']
    ccs = [u.cc] + [c for c in ps.CCS if c != u.cc] if u.cc in ps.CCS else list(ps.CCS)
    combos = [()] + [(p,) for p in prag] + list(itertools.combinations(prag, 2))
    jobs = [(cc, p, None) for cc in ccs for p in combos]
    stop = [False]

    def run(j):
        if stop[0]: return (10**6,) + j
        cc, p, o = j
        s = u.compile_score(ps.variant(u.text, d, p, o), fn, cc, ps.worker_id())
        if s == 0: stop[0] = True
        return (s, cc, p, o)

    def runall(lst):
        stop[0] = False
        with ThreadPoolExecutor(a.jobs, initializer=ps._init_worker) as ex:
            return list(ex.map(run, lst))

    t0 = time.time()
    res = runall(jobs)
    res.sort(key=lambda r: (r[0], len(r[2]), r[1] != u.cc))
    log(f'  stage1 {len(jobs)} variants {time.time()-t0:.0f}s best {res[0][0]}')
    if res[0][0] == 0: return res, 'pragma'
    blk = ps.decl_block(u.text, d[1])
    if blk:
        n = len(blk[2])
        if n <= 6:
            orders = list(itertools.permutations(range(n)))
        else:
            rnd = random.Random(1); orders = set()
            while len(orders) < a.decl: orders.add(tuple(rnd.sample(range(n), n)))
            orders = list(orders)
        top = []
        for r in res:  # distinct settings
            if r[0] >= 10**6: break
            if (r[1], r[2]) not in [(x[1], x[2]) for x in top]: top.append(r)
            if len(top) >= a.decl_top: break
        lst = [(cc, p, o) for (_, cc, p, _) in top for o in orders if list(o) != list(range(n))]
        t0 = time.time()
        res += runall(lst)
        res.sort(key=lambda r: (r[0], len(r[2]), r[1] != u.cc))
        log(f'  stage2 {len(lst)} decl variants ({n} decls) {time.time()-t0:.0f}s best {res[0][0]}')
        if res[0][0] == 0: return res, 'decl'
    return res, None


def stage_perm(u, d, fn, best, a):
    """Stage 3: cperm on the best source. Returns (score, path of best source or None)."""
    _, cc, p, o = best
    text = ps.variant(u.text, d, p, o)
    pdir = os.path.dirname(os.path.abspath(u.src))
    src = os.path.join(pdir, f'.autopipe_{fn}{u.ext}')
    open(src, 'w').write(text)
    od = f'/tmp/autopipe/perm/{fn}'
    shutil.rmtree(od, ignore_errors=True); os.makedirs(od)
    # explicit region: cperm's own lookup keys extab renames by the src path,
    # which is the scratch copy here (C++ methods were not found)
    ls = d[0]; line = u.text[ls:u.text.find('\n', ls)]
    pre = line[:line.find('(') + 1] if '(' in line else line
    if u.text.count(pre) != 1: pre = line
    cmd = ['python3', '-I', CPERM, src, u.obj, fn, '--minutes', str(a.perm_minutes),
           '--workers', str(a.jobs), '--out', od, '--cc', cc, '--region', pre]
    env = dict(os.environ, CPERM_SKIP_SDATA2='1')
    try:
        r = subprocess.run(cmd, capture_output=True, text=True, timeout=a.perm_minutes * 60 + 180, cwd=ROOT, env=env)
        outp = r.stdout + r.stderr
    except subprocess.TimeoutExpired as e:
        outp = str(e.stdout or '')
    finally:
        os.remove(src)
        for f in os.listdir(pdir):
            if f.startswith('.cperm_w'): os.remove(os.path.join(pdir, f))
    bests = sorted(glob.glob(f'{od}/best_*'))
    if not bests:
        log('  stage3 no result:', outp.strip().splitlines()[-1:] if outp.strip() else '')
        return None, None
    sc = int(re.search(r'best_(\d+)', bests[0]).group(1))
    log(f'  stage3 perm best {sc}')
    return sc, bests[0]


# ------------------------------------------------------------------ apply / verify / land

def set_cc(obj, cc):
    ext = nonmatching()[obj]
    L = open('configure.py').read().split('\n')
    key = f'"{obj}.{ext}"'
    for i, l in enumerate(L):
        if 'Object(' in l and key in l:
            v = f'GC/{cc}'
            if 'mw_version=' in l: l = re.sub(r'mw_version="[^"]*"', f'mw_version="{v}"', l)
            else: l = re.sub(r'\)(\s*,?\s*(#.*)?)$', f', mw_version="{v}")\\1', l, count=1)
            L[i] = l; open('configure.py', 'w').write('\n'.join(L)); return True
    return False


def configure():
    return sh(['python3', 'configure.py', '--binutils', 'build/binutils', '--compilers', 'build/compilers',
               '--wrapper', 'build/tools/wibo'])


def build_report():
    configure()
    r = sh(['ninja', REPORT])
    return r.returncode == 0, r.stdout[-3000:]


def clean_build_ok():
    # ninja tracks extab_user_renames.json / extab_order.json / postprocess_*.py
    # since 7858633, so a fresh main.dol link is enough (no rm -rf build/GNLJ82/src)
    if os.path.exists('build/GNLJ82/main.dol'): os.remove('build/GNLJ82/main.dol')
    configure()
    r = sh(['ninja', 'all_source', 'progress', REPORT, 'build/GNLJ82/ok'])
    return r.returncode == 0 and 'main.dol: OK' in r.stdout, r.stdout[-3000:]


def regressions(before, after):
    bad = []
    for k, (p, _, _) in before.items():
        q = after.get(k)
        if q is None or q[0] + 1e-6 < p: bad.append((k, p, q[0] if q else None))
    return bad


def try_flip_matching(obj):
    """If every fn of the TU is now 100%, try Object(Matching) and keep it only on main.dol OK."""
    rep = load_report()
    mine = [p for (o, _), (p, _, _) in rep.items() if o == obj]
    if not mine or min(mine) < 100: return False
    ext = nonmatching()[obj]
    txt = open('configure.py').read()
    new = txt.replace(f'Object(NonMatching, "{obj}.{ext}"', f'Object(Matching, "{obj}.{ext}"', 1)
    if new == txt: return False
    open('configure.py', 'w').write(new)
    ok, _ = clean_build_ok()
    if not ok:
        open('configure.py', 'w').write(txt)
        return False
    return True


def git(*args):
    return sh(['git'] + list(args))


def sync_main():
    """Rebase the local branch on origin/main. Returns True if HEAD moved."""
    old = git('rev-parse', 'HEAD').stdout.strip()
    for i in range(4):
        if git('fetch', '-q', 'origin', 'main').returncode == 0: break
        time.sleep(2 ** (i + 1))
    r = git('rebase', 'origin/main')
    if r.returncode:
        git('rebase', '--abort'); log('rebase failed:', r.stdout[-500:], r.stderr[-500:]); return False
    return git('rev-parse', 'HEAD').stdout.strip() != old


def push_main(a):
    if a.no_push: return True
    for i in range(4):
        r = git('push', 'origin', 'HEAD:main')
        if r.returncode == 0:
            git('push', '-q', '-f', 'origin', f'HEAD:{a.branch}')
            return True
        if 'rejected' in r.stderr or 'non-fast-forward' in r.stderr or 'fetch first' in r.stderr:
            if not sync_main(): return False
            ok, _ = clean_build_ok()
            if not ok: return False
        else:
            time.sleep(2 ** (i + 1))
    return False


def land(u, d, fn, best, how, before, a):
    _, cc, p, o = best
    orig_src = u.text; orig_cfg = open('configure.py').read()

    def revert():
        open(u.src, 'w').write(orig_src); open('configure.py', 'w').write(orig_cfg)
        build_report()

    open(u.src, 'w').write(ps.variant(u.text, d, p, o))
    if cc != u.cc and not set_cc(u.obj, cc):
        revert(); return False, 'could not set compiler'
    ok, out = build_report()
    if not ok:
        revert(); return False, 'build failed: ' + out[-300:]
    after = load_report()
    pct = after.get((u.obj, fn), (0,))[0]
    bad = regressions(before, after)
    if pct < 100 or bad:
        revert(); return False, f'verify: fn {pct:.3f}%, regressions {bad[:3]}'
    flipped = try_flip_matching(u.obj)
    ok, out = clean_build_ok()
    if not ok:
        revert(); return False, 'clean build not OK: ' + out[-300:]
    setting = f'GC/{cc}' + (' + ' + ', '.join(p) if p else '') + (' + decl order' if o else '')
    msg = (f'autopipe: match {fn} ({setting})\n\n{u.obj}: {how} stage hit; report verified with no '
           f'regressions{", TU now Matching" if flipped else ""}, clean build main.dol OK.\n\n'
           'Co-Authored-By: Claude Opus 5.5 <noreply@anthropic.com>\n'
           f'Claude-Session: {a.session}')
    git('add', u.src, 'configure.py')
    r = git('commit', '-q', '-m', msg)
    if r.returncode:
        revert(); return False, 'commit failed: ' + r.stderr[-300:]
    if sync_main():
        ok, out = clean_build_ok()
        if not ok:
            git('reset', '-q', '--hard', 'origin/main'); build_report()
            return False, 'after rebase clean build not OK'
    if not push_main(a):
        git('reset', '-q', '--hard', 'origin/main'); build_report()
        return False, 'push failed'
    sha = git('rev-parse', '--short', 'HEAD').stdout.strip()
    with open(f'{OUT}/landed_{WHO}.log', 'a') as f:
        f.write(f'{datetime.now(timezone.utc).isoformat(timespec="seconds")} {sha} {fn} {u.obj} {setting}'
                f'{" [TU Matching]" if flipped else ""}\n')
    return True, f'{sha} {setting}{" [TU Matching]" if flipped else ""}'


# ------------------------------------------------------------------ main loop

def stopped():
    return os.path.exists(f'{OUT}/STOP') or os.path.exists(f'{SETUP}/GRIND_STOP')


def one(p, obj, fn, size, dm, a):
    u = ps.Unit(obj)
    # postprocess_sdata2 (a python process per compile) was ~60% of a small TU's
    # variant time and never changed a score (checked on 4 fns x 6 variants);
    # the real build in land() still runs it.
    u.post = [x for x in u.post if 'postprocess_sdata2' not in x]
    d, _ = u.resolve(fn, dm)
    if not d:
        return {'outcome': 'nodef'}
    before = load_report()
    res, how = stage_sweep(u, d, fn, a)
    best = res[0]
    r = {'stage12_best': best[0], 'cc': best[1], 'pragmas': list(best[2]), 'order': list(best[3]) if best[3] else None,
         'own_cc': u.cc, 'base': next((x[0] for x in res if x[1] == u.cc and not x[2] and not x[3]), None)}
    if how:
        ok, info = land(u, d, fn, best, how, before, a)
        r.update(outcome='landed' if ok else 'land_failed', info=info)
        if ok: return r
    if a.no_perm or best[0] >= 10**6:
        r.setdefault('outcome', 'nomatch'); return r
    sc, path = stage_perm(u, d, fn, best, a)
    r['perm_best'] = sc
    if sc == 0:
        os.makedirs(f'{OUT}/review', exist_ok=True)
        dst = f'{OUT}/review/{fn}{u.ext}'
        shutil.copy(path, dst)
        r.update(outcome='perm_match', review=dst, perm_cc=best[1])
    else:
        r.setdefault('outcome', 'nomatch')
    return r


def cmd_run(a):
    os.makedirs(OUT, exist_ok=True)
    n = 0; t_end = time.time() + a.hours * 3600 if a.hours else None
    stop_on = set((a.stop_on or '').split(','))
    while not stopped():
        if t_end and time.time() > t_end:
            log('time budget used up'); return
        if git('status', '--porcelain', '--untracked-files=no').stdout.strip():
            sys.exit('working tree dirty; refusing to run')
        if sync_main():
            log('origin/main moved; rebuilding report'); build_report()
        cl = claims(a.claims); seen = done_keys()
        todo = [c for c in candidates(a) if c[1] not in cl and (c[1], c[2]) not in seen or
                (c[1] not in cl and seen.get((c[1], c[2])) is not None and abs(seen[(c[1], c[2])] - c[0]) > 0.01)]
        if a.only: todo = [c for c in todo if c[2] in a.only.split(',')]
        if a.shard:  # stable partition by fn name, so parallel threads never pick the same fn
            k, nsh = map(int, a.shard.split('/'))
            todo = [c for c in todo if int(Q.hashlib.sha1(c[2].encode()).hexdigest(), 16) % nsh == k]
        if not todo:
            log('nothing left to try'); return
        p, obj, fn, size, dm = todo[0]
        log(f'{fn} ({obj}) {p:.3f}% size {size}')
        qid = q_claim(fn, obj, p)
        if not qid:
            log('  held by another thread; skipping')
            record({'obj': obj, 'fn': fn, 'pct': p, 'outcome': 'held'}); continue
        try:
            r = one(p, obj, fn, size, dm, a)
        except Exception as e:  # keep going
            r = {'outcome': 'error', 'info': repr(e)[:300]}
            git('checkout', '--', '.'); build_report()
        r.update(obj=obj, fn=fn, pct=p, qid=qid)
        record(r)
        o = r['outcome']
        if o == 'landed':
            q_close(qid, 'done', 'autopipe ' + r['info'])
        elif o == 'perm_match':
            q_close(qid, 'release', '')   # back to open; a review is pending
            log('  PERM MATCH -> review', r['review'])
        else:
            q_close(qid, 'park', f'autopipe: pragma/decl best {r.get("stage12_best")} (base {r.get("base")}, '
                                 f'GC/{r.get("cc")} {",".join(r.get("pragmas") or []) or "-"}), perm best {r.get("perm_best")}'
                                 f'{"; " + r["info"] if r.get("info") else ""}')
        log(f'  -> {o} {r.get("info", "")}')
        n += 1
        if a.limit and n >= a.limit: return
        if o in stop_on:
            log(f'stop-on {o}'); return
    log('stop switch present')


def cmd_status(a):
    rows = [json.loads(l) for p in glob.glob(f'{OUT}/results*.jsonl') for l in open(p)]
    import collections
    print(collections.Counter(r['outcome'] for r in rows))
    for r in rows[-20:]:
        print(r['t'], r['outcome'], r['fn'], f"{r['pct']:.2f}", r.get('stage12_best'), r.get('perm_best'), r.get('info', ''))
    for p in sorted(glob.glob(f'{OUT}/landed*.log')): print(open(p).read())


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sp = ap.add_subparsers(dest='cmd', required=True)
    p = sp.add_parser('run')
    p.add_argument('--min', type=float, default=80); p.add_argument('--max-size', type=int, default=4000)
    p.add_argument('--perm-minutes', type=float, default=8); p.add_argument('--limit', type=int)
    p.add_argument('--decl', type=int, default=300, help='random orders when > 6 decls')
    p.add_argument('--decl-top', type=int, default=2, help='settings from stage 1 to sweep decl order on')
    p.add_argument('-j', '--jobs', type=int, default=os.cpu_count() or 4)
    p.add_argument('--only'); p.add_argument('--no-push', action='store_true'); p.add_argument('--no-perm', action='store_true')
    p.add_argument('--claims', default=f'{OUT}/claims.txt')
    p.add_argument('--hours', type=float, help='do not start a new fn after this many hours')
    p.add_argument('--stop-on', help='comma list of outcomes that end the run, e.g. landed,perm_match')
    p.add_argument('--shard', help='K/N (0-based): only fns with sha1(name) %% N == K; one shard per thread')
    p.add_argument('--branch', default=sh(['git', 'branch', '--show-current']).stdout.strip())
    p.add_argument('--session', default=os.environ.get('AUTOPIPE_SESSION', ''))
    sp.add_parser('status')
    a = ap.parse_args()
    {'run': cmd_run, 'status': cmd_status}[a.cmd](a)


if __name__ == '__main__':
    main()
