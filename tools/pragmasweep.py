#!/usr/bin/env python3
"""pragmasweep.py: brute-force compiler version x opt_* pragmas x declaration order.

Run from the repo root after a normal build (build/GNLJ82/asm and the TU's
ninja command must exist). Nothing in the repo is modified: every variant is
compiled from a scratch copy next to the source (.psweep_wN.<ext>, removed
afterwards) into /tmp/pragmasweep.

One function:
  python3 tools/pragmasweep.py fn game/Foo FN [--cc 1.3,2.6] [--k 2] [--decl 200] [-j 4]
    game/Foo   object path as in configure.py, without the extension
    FN         target symbol (as in build/GNLJ82/asm)
  Prints the variants ranked by diff lines (0 = match) and writes the best
  source to /tmp/pragmasweep/<FN>.best.<ext>.

All near misses:
  python3 tools/pragmasweep.py batch [--min 90] [--max-size 2000] [--md docs/reports/pragmasweep_results.md]
  Sweeps every function below 100% in a NonMatching TU with fuzzy >= --min,
  and writes a Markdown table (original vs best diff lines, best setting,
  who claims the TU). Resumable: results are cached in /tmp/pragmasweep/cache.json.

Pragma sets (--set, for fn and batch): default = the opt_* list below;
extended = optimization_level 1/2/3, optimize_for_size, fp_contract off,
unroll/vectorize off plus the three strongest opt_* ones; all = both.

What is swept:
  - mw_version: --cc (default 1.2.5n,1.3,1.3.2,2.0,2.6,2.7; the TU's own first)
  - pragmas: none, each of PRAGMAS alone, and every pair (--k 2), wrapped
    around the function with #pragma push/pop
  - declaration order (--decl N): N random orders of the plain declarations
    at the top of the function body, tried on the 3 best settings above
Scoring is the number of +/- lines of a unified diff of the function body
against the target, with labels, bl targets and @ha/@l/@sda21 symbols
normalized (objdiff tolerates those names).
"""
import argparse, difflib, glob, itertools, json, os, random, re, shutil, subprocess, sys
from concurrent.futures import ThreadPoolExecutor

PRAGMAS = ['opt_common_subs off', 'opt_propagation off', 'opt_lifetimes off',
           'opt_dead_assignments off', 'opt_loop_invariants off',
           'opt_strength_reduction off', 'peephole off', 'scheduling off']
# --set extended: optimizer-level pragmas. These found fn_80246DE4
# (optimization_level 3) and fn_8021E0FC (optimization_level 2) after the
# default set had been run.
PRAGMAS_EXT = ['optimization_level 3', 'optimization_level 2', 'optimization_level 1',
               'optimize_for_size on', 'fp_contract off', 'opt_unroll_loops off',
               'opt_vectorize_loops off', 'opt_lifetimes off', 'opt_common_subs off',
               'opt_propagation off',
               # unroll budget: fn_8028AAC0 (4x instead of 8x, rule loop-unroll-budget)
               'opt_unroll_instr_count 16', 'opt_unroll_instr_count 8', 'opt_unroll_instr_count 32']
PRAGMA_SETS = {'default': PRAGMAS, 'extended': PRAGMAS_EXT, 'all': list(dict.fromkeys(PRAGMAS + PRAGMAS_EXT))}
CCS = ['1.2.5n', '1.3', '1.3.2', '2.0', '2.6', '2.7']
TMP = os.path.join(__import__('tempfile').gettempdir(), 'pragmasweep')
# build/tools binaries; on Windows CreateProcess needs the .exe suffix and backslashes
DTK = os.path.normpath('build/tools/dtk' + ('.exe' if os.name == 'nt' else ''))
OBJDIFF_CLI = os.path.normpath('build/tools/objdiff-cli' + ('.exe' if os.name == 'nt' else ''))
_GC = re.compile(r'GC([\\/])[^\\/]+([\\/])mwcceppc')


def swap_cc(cmd, cc):
    """cmd with its compiler switched to GC/<cc>, keeping the path separator
    (ninja writes backslashes on Windows, and cmd.exe needs them in the exe path)."""
    return _GC.sub(lambda m: f'GC{m[1]}{cc}{m[2]}mwcceppc', cmd)

OBJDIFF = False  # --objdiff: score = (100 - objdiff match %) * 100 instead of diff lines

import threading
_tl = threading.local(); _ids = iter(range(10**6)); _idlock = threading.Lock()
def _init_worker():
    with _idlock: _tl.id = next(_ids)
def worker_id():
    if not hasattr(_tl, 'id'): _init_worker()
    return _tl.id


def norm_body(path, fn):
    out = []; on = False
    for l in open(path, errors='replace'):
        if l.startswith('.fn ' + fn + ','): on = True; continue
        if on and l.startswith('.endfn'): break
        if on:
            m = re.match(r'/\* [0-9A-F]+ [0-9A-F]+  (.. .. .. ..) \*/\t(.*)', l)
            if m:
                x = re.sub(r'^bl \S+', 'bl F', re.sub(r'\.L_[0-9A-F]+', '.L', m.group(2)))
                x = re.sub(r'[\w"@.$<>,]+@(ha|l|sda21)', r'S@\1', x)
                out.append(x)
    return out


_tcache = {}
def target_body(fn):
    if fn in _tcache: return _tcache[fn]
    hits = [p for p in glob.glob('build/GNLJ82/asm/**/*.s', recursive=True)
            if ('.fn ' + fn + ',') in open(p, errors='replace').read()]
    _tcache[fn] = norm_body(hits[0], fn) if hits else None
    return _tcache[fn]


class Unit:
    def __init__(self, obj):
        self.obj = obj
        cands = [f'src/{obj}{e}' for e in ('.c', '.cpp', '.cp')]
        self.src = next((c for c in cands if os.path.exists(c)), None)
        if not self.src: raise SystemExit(f'no source for {obj}')
        r = subprocess.run(['ninja', '-t', 'commands', f'build/GNLJ82/src/{obj}.o'], capture_output=True, text=True)
        lines = [l for l in r.stdout.strip().splitlines() if 'mwcceppc' in l]
        if not lines: raise SystemExit(f'no compile command for {obj}')
        parts = lines[-1].split(' && ')
        self.cmd = parts[0].replace(' -MMD', '')
        # postprocess steps (extab renames etc.) so objdiff can pair symbols
        # (the object path is normalised to forward slashes so callers can .replace() it)
        op = f'build/GNLJ82/src/{obj}.o'
        self.post = [x.replace(op.replace('/', '\\'), op) for x in parts[1:] if op in x.replace('\\', '/')]
        m = re.search(r'GC[\\/]([^\\/]+)[\\/]mwcceppc', self.cmd)
        self.cc = m.group(1) if m else None
        self.text = open(self.src).read()
        self.ext = os.path.splitext(self.src)[1]
        self.renames = json.load(open('tools/extab_user_renames.json')).get(self.src, {}) if os.path.exists('tools/extab_user_renames.json') else {}

    def compiled_name(self, fn):
        # a definition under the target name itself wins over a stale rename entry
        if re.search(r'^[^\n;{}]*\b' + re.escape(fn) + r'\s*\([^;{]*\)\s*\{', self.text, re.M): return fn
        for k, v in self.renames.items():
            if v == fn: return k
        # renames are sometimes filed under another TU's key (moved code),
        # but a name the source itself defines wins (VSMode_FrameUpdate's
        # *_p0 rename once sent RankingMgr_UpdatePositions to a missing fn)
        if re.search(rf'\b{re.escape(fn)}\s*\(', self.text): return fn
        for tu in _all_renames().values():
            if not isinstance(tu, dict): continue
            for k, v in tu.items():
                if v == fn and not k.startswith('extab'): return k
        return fn

    def guess_compiled_name(self, fn):
        """Compile the TU as-is and return the emitted function whose body is
        closest to the target's (for methods/ctors with no rename entry)."""
        T = target_body(fn)
        if not T: return None
        d = f'{TMP}/guess{os.getpid()}'; os.makedirs(d, exist_ok=True)
        for f in glob.glob(d + '/*'): os.remove(f)
        c = re.sub(r'-c \S+ -o \S+', lambda _: f'-c {self.src} -o {d}', self.cmd)
        subprocess.run(c, shell=True, capture_output=True, text=True)
        o = glob.glob(d + '/*.o')
        if not o: return None
        subprocess.run([DTK, 'elf', 'disasm', o[0], d + '/m.s'], capture_output=True)
        names = re.findall(r'^\.fn (\S+?),', open(d + '/m.s', errors='replace').read(), re.M)
        best = (0.0, None)
        for n in names:
            B = norm_body(d + '/m.s', n)
            if not B or abs(len(B) - len(T)) > max(8, len(T) // 4): continue
            r = difflib.SequenceMatcher(None, T, B, autojunk=False).ratio()
            if r > best[0]: best = (r, n)
        return best[1] if best[0] >= 0.6 else None

    def resolve(self, fn, demangled=None):
        """(definition span, compiled symbol name) for fn, or (None, None)."""
        m = self.compiled_name(fn)
        d = find_def(self.text, fn, demangled, m)
        if d: return d, m
        g = self.guess_compiled_name(fn)
        if g and g != fn:
            d = find_def(self.text, fn, demangled, g)
            if d:
                self.renames = dict(self.renames); self.renames[g] = fn
                return d, g
        return None, None

    def objdiff_score(self, base_o, fn):
        """Raw (not post-processed) .o vs the target object, as objdiff's fuzzy %."""
        pct = _objdiff_pct(f'build/GNLJ82/obj/{self.obj}.o', base_o, fn, {fn, self.compiled_name(fn)})
        return 10**6 if pct is None else int(round((100.0 - pct) * 100))

    def compile_score(self, text, fn, cc, wk):
        d = f'{TMP}/w{os.getpid()}_{wk}'; os.makedirs(d, exist_ok=True)
        for f in glob.glob(d + '/*.o') + glob.glob(d + '/.*.o'): os.remove(f)
        sp = os.path.join(os.path.dirname(os.path.abspath(self.src)), f'.psweep_{os.getpid()}_w{wk}{self.ext}')
        open(sp, 'w').write(text)
        c = swap_cc(self.cmd, cc)
        c = re.sub(r'-c \S+ -o \S+', lambda _: f'-c {sp} -o {d}', c)
        subprocess.run(c, shell=True, capture_output=True, text=True)
        os.remove(sp)
        o = glob.glob(d + '/*.o') + glob.glob(d + '/.*.o')
        if not o: return 10**6
        for x in self.post:
            subprocess.run(x.replace(f'build/GNLJ82/src/{self.obj}.o', o[0]), shell=True, capture_output=True)
        if self.renames:  # the temp .file name defeats the TU lookup; rename directly
            subprocess.run(['llvm-objcopy'] + [f'--redefine-sym={k}={v}' for k, v in self.renames.items()] + [o[0]],
                           capture_output=True)
        if OBJDIFF:
            return self.objdiff_score(o[0], fn)
        subprocess.run([DTK, 'elf', 'disasm', o[0], d + '/m.s'], capture_output=True)
        T = target_body(fn)
        B = norm_body(d + '/m.s', fn) or norm_body(d + '/m.s', self.compiled_name(fn))
        if not B or T is None: return 10**6
        return sum(1 for l in difflib.unified_diff(T, B, lineterm='', n=0)
                   if l[:1] in '+-' and not l.startswith(('+++', '---')))


def _objdiff_pct(target_o, base_o, fn, names):
    r = subprocess.run([OBJDIFF_CLI, 'diff', '-1', target_o, '-2', base_o, '-o', '-', fn],
                       capture_output=True, text=True)
    try:
        d = json.loads(r.stdout)
    except ValueError:
        return None
    for sym in d.get('right', {}).get('symbols', []):
        nm = sym.get('name') or ''
        if (nm in names or any(nm.startswith(n + '__') for n in names)) and sym.get('match_percent') is not None:
            return sym['match_percent']
    return None


_rcache = None
def _all_renames():
    global _rcache
    if _rcache is None:
        p = 'tools/extab_user_renames.json'
        _rcache = json.load(open(p)) if os.path.exists(p) else {}
    return _rcache


def mangled_qual(m):
    """Draw__13SceneListImplFv -> SceneListImpl::Draw; __ct__/__dt__ -> ctor/dtor."""
    mm = re.match(r'(__ct|__dt|\w+?)__(\d+)(\w+)', m)
    if not mm: return None
    n = int(mm.group(2)); cls = mm.group(3)[:n]
    meth = {'__ct': cls, '__dt': '~' + cls}.get(mm.group(1), mm.group(1))
    return cls + '::' + meth


def find_def(text, fn, demangled=None, mangled=None):
    """Return (line_start, body_open_index_after_brace, body_end_index) of fn's definition."""
    pats = [r'\b' + re.escape(fn) + r'\s*\([^;{]*\)[^;{]*\{']
    if mangled and mangled != fn:
        if re.fullmatch(r'\w+', mangled) and not re.search(r'__\d|__F', mangled):
            pats.append(r'\b' + re.escape(mangled) + r'\s*\([^;{]*\)[^;{]*\{')  # extern "C" rename
        mf = re.match(r'(\w+?)__F', mangled)
        if mf and mf.group(1) != fn:
            pats.append(r'\b' + re.escape(mf.group(1)) + r'\s*\([^;{]*\)[^;{]*\{')
        q = mangled_qual(mangled)
        if q: demangled = demangled or q + '('
    if demangled and '::' in demangled:
        q = demangled.split('(')[0]
        pats.append(re.escape(q).replace(r'\:\:', r'\s*::\s*') + r'\s*\([^;{]*\)[^;{]*\{')
    for p in pats:
        m = re.search(p, text)
        if m:
            ls = text.rfind('\n', 0, m.start()) + 1
            j = m.end(); depth = 1
            while depth and j < len(text):
                ch = text[j]
                if ch == '{': depth += 1
                elif ch == '}': depth -= 1
                j += 1
            return ls, m.end(), j
    return None


DECL = re.compile(r'^\s+(?:const\s+|unsigned\s+|signed\s+|struct\s+|volatile\s+)*[A-Za-z_][\w:]*(?:\s*[\*&]+\s*|\s+)[\*&]*[A-Za-z_]\w*(?:\[[^\]]*\])*\s*;\s*$')
KW = ('return', 'goto', 'break', 'continue', 'delete', 'throw', 'case', 'else')


def decl_block(text, body_start):
    nl = text.find('\n', body_start)
    if nl < 0: return None
    pos = nl + 1; lines = []
    while True:
        e = text.find('\n', pos)
        if e < 0: break
        l = text[pos:e]
        if DECL.match(l) and l.split()[0] not in KW:
            lines.append(l); pos = e + 1
        else: break
    if len(lines) < 2: return None
    return nl + 1, pos, lines


def variant(text, d, prags, order=None):
    ls, bs, be = d
    if order is not None:
        blk = decl_block(text, bs)
        if blk:
            a, b, lines = blk
            # same total length, so the definition offsets stay valid
            text = text[:a] + '\n'.join(lines[i] for i in order) + '\n' + text[b:]
    if not prags: return text
    pre = '#pragma push\n' + ''.join(f'#pragma {p}\n' for p in prags)
    return text[:ls] + pre + text[ls:be] + '\n#pragma pop\n' + text[be:]


def sweep(obj, fn, ccs=None, k=2, decl=0, jobs=4, demangled=None, quiet=False):
    u = Unit(obj)
    d, _ = u.resolve(fn, demangled)
    if not d: return {'error': 'definition not found'}
    ccs = ccs or CCS
    if u.cc in ccs: ccs = [u.cc] + [c for c in ccs if c != u.cc]
    combos = [()]
    for n in range(1, k + 1): combos += list(itertools.combinations(PRAGMAS, n))
    jobsl = [(cc, p, None) for cc in ccs for p in combos]
    orig = u.compile_score(u.text, fn, u.cc, 0)
    res = []

    def run(i_j):
        i, (cc, p, order) = i_j
        t = variant(u.text, d, p, order)
        return (u.compile_score(t, fn, cc, worker_id()), cc, p, order)

    def runall(lst):
        out = []
        with ThreadPoolExecutor(jobs, initializer=_init_worker) as ex:
            for r in ex.map(run, enumerate(lst)):
                out.append(r)
                if r[0] == 0: break
        return out
    res += runall(jobsl)
    res.sort(key=lambda r: (r[0], len(r[2])))
    if decl and res and res[0][0] > 0:
        blk = decl_block(u.text, d[1])
        if blk:
            n = len(blk[2]); rnd = random.Random(1); orders = set()
            allp = list(itertools.permutations(range(n))) if n <= 6 else None
            while len(orders) < min(decl, len(allp) if allp else decl):
                orders.add(tuple(rnd.choice(allp)) if allp else tuple(rnd.sample(range(n), n)))
            top = res[:3]
            res += runall([(cc, p, o) for (_, cc, p, _) in top for o in orders])
            res.sort(key=lambda r: (r[0], len(r[2])))
    best = res[0]
    os.makedirs(TMP, exist_ok=True)
    bp = f'{TMP}/{fn}.best{u.ext}'
    open(bp, 'w').write(variant(u.text, d, best[2], best[3]))
    if not quiet:
        print(f'{obj} {fn}: original {orig} (GC/{u.cc}); best {best[0]}')
        seen = 0
        for s, cc, p, o in res:
            print(f'  {s:5d}  GC/{cc:7s} {", ".join(p) or "-"}{"  decl-order " + str(o) if o else ""}')
            seen += 1
            if seen >= 15: break
        print(f'best source: {bp}')
    return {'orig': orig, 'best': best[0], 'cc': best[1], 'pragmas': list(best[2]),
            'order': list(best[3]) if best[3] else None, 'own_cc': u.cc, 'best_src': bp}


def claims():
    """Open unit-claim issues, TU path -> author. Walks the issues API page by
    page (search and `gh --paginate` have both dropped claims before)."""
    out = {}; page = 1
    while True:
        r = subprocess.run(['gh', 'api', f'repos/naari3/mkgp2-decomp/issues?labels=unit-claim&state=open&per_page=100&page={page}',
                            '--jq', '.[] | select(.pull_request == null) | "\\(.user.login)\\t\\(.title)"'],
                           capture_output=True, text=True)
        rows = [l for l in r.stdout.splitlines() if l.strip()]
        if r.returncode or not rows: break
        for l in rows:
            who, t = l.split('\t', 1)
            m = re.search(r'retrofit:(\S+)', t)
            if m: out[re.sub(r'\.(c|cpp|cp)$', '', m.group(1))] = who
        page += 1
    return out


def cmd_batch(a):
    rep = json.load(open('build/GNLJ82/report.json'))
    nm = set(re.findall(r'Object\(NonMatching,\s*"([^"]+)\.(?:c|cpp|cp)"', open('configure.py').read()))
    cl = claims()
    os.makedirs(TMP, exist_ok=True)
    cpath = f'{TMP}/cache.json' if a.set == 'default' else f'{TMP}/cache_{a.set}.json'
    cache = json.load(open(cpath)) if os.path.exists(cpath) else {}
    todo = []
    for u in rep['units']:
        obj = re.sub(r'^main/', '', u['name'])
        if obj not in nm: continue
        for f in u.get('functions', []):
            p = f.get('fuzzy_match_percent', 0)
            if a.min <= p < 100 and int(f['size']) <= a.max_size:
                todo.append((p, obj, f['name'], f.get('metadata', {}).get('demangled_name'), int(f['size'])))
    todo.sort(key=lambda t: -t[0])
    print(f'{len(todo)} functions', flush=True)
    for p, obj, fn, dm, size in todo:
        key = f'{obj}:{fn}'
        if key in cache: continue
        try:
            r = sweep(obj, fn, k=a.k, decl=a.decl, jobs=a.jobs, demangled=dm, quiet=True)
        except SystemExit as e:
            r = {'error': str(e)}
        r.update({'pct': p, 'size': size})
        cache[key] = r
        json.dump(cache, open(cpath, 'w'), indent=0)
        print(key, r.get('orig'), '->', r.get('best'), r.get('cc'), r.get('pragmas'), r.get('error', ''), flush=True)
    rows = []
    for key, r in cache.items():
        obj, fn = key.split(':', 1)
        rows.append((r.get('best', 10**6), obj, fn, r))
    rows.sort(key=lambda x: (x[0] if isinstance(x[0], int) else 10**6))
    md = ['# pragmasweep results', '',
          f'Generated by `tools/pragmasweep.py batch` (min {a.min}%). Diff lines are',
          'unified-diff +/- lines of the function vs the target (0 = match).',
          '"own" is the TU\'s current compiler. Claimed TUs are listed for information only.', '',
          '| Function | TU | % | own cc: lines | best | best setting | claim |', '| --- | --- | --- | --- | --- | --- | --- |']
    for b, obj, fn, r in rows:
        if 'error' in r and 'best' not in r:
            md.append(f'| `{fn}` | {obj} | {r.get("pct", 0):.2f} | - | - | {r["error"]} | {cl.get(obj, "")} |'); continue
        setting = f'GC/{r["cc"]}' + (' + ' + ', '.join(r['pragmas']) if r['pragmas'] else '') + (' + decl order' if r.get('order') else '')
        md.append(f'| `{fn}` | {obj} | {r["pct"]:.2f} | GC/{r["own_cc"]}: {r["orig"]} | {r["best"]} | {setting} | {cl.get(obj, "")} |')
    open(a.md, 'w').write('\n'.join(md) + '\n')
    print('wrote', a.md)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sp = ap.add_subparsers(dest='cmd', required=True)
    p = sp.add_parser('fn'); p.add_argument('obj'); p.add_argument('fn')
    p.add_argument('--cc', type=lambda s: s.split(','))
    p.add_argument('--k', type=int, default=2); p.add_argument('--decl', type=int, default=0)
    p.add_argument('-j', '--jobs', type=int, default=os.cpu_count() or 4)
    p.add_argument('--demangled', help='Class::Method, if the def is not found by symbol name')
    p.add_argument('--set', choices=sorted(PRAGMA_SETS), default='default', help='pragma set to sweep')
    p = sp.add_parser('batch'); p.add_argument('--min', type=float, default=90)
    p.add_argument('--max-size', type=int, default=2000)
    p.add_argument('--k', type=int, default=2); p.add_argument('--decl', type=int, default=0)
    p.add_argument('-j', '--jobs', type=int, default=os.cpu_count() or 4)
    p.add_argument('--md', default='docs/reports/pragmasweep_results.md')
    p.add_argument('--set', choices=sorted(PRAGMA_SETS), default='default', help='pragma set to sweep')
    for q in sp.choices.values():
        q.add_argument('--objdiff', action='store_true',
                       help='score by objdiff fuzzy %% (printed as (100-%%)*100) instead of diff lines')
    a = ap.parse_args()
    global PRAGMAS, OBJDIFF
    OBJDIFF = a.objdiff
    PRAGMAS = PRAGMA_SETS[a.set]
    if a.cmd == 'fn':
        r = sweep(a.obj, a.fn, a.cc, a.k, a.decl, a.jobs, a.demangled)
        if 'error' in r: sys.exit(r['error'])
    else:
        cmd_batch(a)


if __name__ == '__main__':
    main()
