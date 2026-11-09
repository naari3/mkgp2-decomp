#!/usr/bin/env python3
"""tracesweep.py: permuter scored by the compiler's own decisions (mwtrace).

For near misses whose cause is already known from a trace ("loop 1's `mode`
must be a temp", "`converted` must be numbered after the in-loop lhz"), but
whose source shape is not. Every variant is compiled with the native,
trace-patched mweppc (tools/mwtrace.py, ~0.15 s, no wine, parallel-safe) and
ranked by

  1. --want: a Python predicate over the trace that states the mechanism
     directly (True = the variant reached the target's allocator state),
  2. diff lines of the function body against the target (0 = match),

so a shape that fixes the mechanism but breaks something else still ranks
above one that changes nothing, and can be repaired by hand or by a second
template. The top --confirm variants are then compiled with the unit's REAL
compiler and scored by objdiff (native GC/2.6 stands in for GC/1.x units).

Variants come from a TEMPLATE: the function's full definition (optionally
preceded by helper functions / macros), with choice points

    {{ alt1 | alt2 | alt3 }}           one independent choice
    {{name: alt1 | alt2 }}             choices with the same name move together
                                       (pick index k in every point named `name`)
    {{name}}                           repeat the named point (same alternatives)
    {{%name: a | b | c }}              every order of the items, one per line, indented
                                       like the point (declaration order sweeps)
    Points may nest. Write `{ x; }` with spaces next to a point's braces.

`|` separates alternatives (`||` is the C operator and is left alone); an
alternative may be empty. The variants are the cartesian product of the
choice points (or a random --sample of it). The template replaces the
function's definition in a scratch copy of the TU; src/ is never written.

    python3 tools/tracesweep.py run UNIT FN TEMPLATE [--want EXPR] [-j 8]
        [--sample N] [--confirm 3] [--show 15] [--keep-going]
    python3 tools/tracesweep.py trace UNIT FN [--template T --pick 0,1,..]
        print the trace object's summary (vregs, temps, creators, colours) for
        the current source or for one variant: use it to write --want
    python3 tools/tracesweep.py selftest
        replays landed fixes (tools/tracesweep/selftest/*.tmpl): each template
        holds the pre-fix and the landed shape; the sweep must rank the landed
        one first with diff 0. Run it after changing the scorer.

--want is evaluated with `T` bound to the variant's Trace (see class Trace):
    T.kind('mode')            'local' | 'temp' | 'argument' | 'toc' | None
    T.vreg('converted')       virtual register number of a named local / @temp
    T.reg('item')             machine register it was coloured to (31 for r31)
    T.creator('@741')         compiler function that made the @temp (SplitOffRange, ...)
    T.temps('SplitOffRange')  the @temps that creator made
    T.defs(r'LHZ')            vregs written by pre-RA PCode lines matching the regex
    T.vdef(r'^LHZ ', k=0)     vreg written by the k-th matching pre-RA line (None if none)
    T.pdef(r'-31560', k=0)    machine register written by the k-th matching post-RA line
    T.num(r'^LWZ ', k=0)      vreg number written by the k-th matching pre-RA line (10**6 if none)
    T.named(r'^LWZ ', k=0)    that line writes a named local (or a temp MR'd into one)
    T.pre                     [(block, srcline, insn)] PCode before regalloc
    T.order                   vregs in colouring order (first coloured first)
    T.pre_text / T.post_text  the PCode as one string, for multi-line re.search
    T.line_regs(srcline)      machine registers written on that source line (post-RA)
--probe EXPR logs any such value per variant (log + table), e.g. the register the
want-condition is about, to see which choices move it at all.
e.g. --want "T.vreg('converted') > min(T.defs(r'^LHZ'))"
     --want "T.reg(T.loopvar(1)) == 28"

Results: /tmp/tracesweep/<FN>.log.jsonl (every variant: picks, want, score)
and /tmp/tracesweep/<FN>.best.<ext> (best variant's definition).
"""
from __future__ import annotations

import argparse
import glob
import hashlib
import itertools
import json
import os
import random
import re
import shutil
import subprocess
import sys
import tempfile
import threading
import time
from concurrent.futures import ThreadPoolExecutor

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import mwtrace  # noqa: E402
import pragmasweep as ps  # noqa: E402

TMP = os.path.join(tempfile.gettempdir(), 'tracesweep')
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SELFTEST = os.path.join(ROOT, 'tools', 'tracesweep', 'selftest')

# --------------------------------------------------------------------------
# templates

def _split_alts(body):
    """Split a choice body at top-level `|` (not `||`, not inside a nested {{ }})."""
    alts, depth, cur, i = [], 0, [], 0
    while i < len(body):
        if body.startswith('{{', i):
            depth += 1; cur.append('{{'); i += 2; continue
        if body.startswith('}}', i):
            depth -= 1; cur.append('}}'); i += 2; continue
        if body.startswith('||', i):
            cur.append('||'); i += 2; continue
        if body[i] == '|' and depth == 0:
            alts.append(''.join(cur)); cur = []; i += 1; continue
        cur.append(body[i]); i += 1
    alts.append(''.join(cur))
    return alts


def parse_template(t: str):
    """-> (pieces, axes): pieces = list of str | (axis, [pieces per alternative]);
    axes = list of (name, n_alternatives). Points with the same name share one axis.
    Choice points may nest."""
    axes, names, refs = [], {}, {}

    def parse(s):
        out, pos = [], 0
        while True:
            i = s.find('{{', pos)
            if i < 0:
                out.append(s[pos:])
                return out
            out.append(s[pos:i])
            depth, j = 1, i + 2
            while depth:
                if j >= len(s):
                    raise SystemExit('unbalanced {{ in template')
                if s.startswith('{{', j):
                    depth += 1; j += 2
                elif s.startswith('}}', j):
                    depth -= 1; j += 2
                else:
                    j += 1
            body = s[i + 2:j - 2]
            ref = re.fullmatch(r'\s*(\w+)\s*', body)
            if ref and ref.group(1) in names:  # {{name}}: repeat that point's alternatives
                out.append((names[ref.group(1)], refs[ref.group(1)]))
                pos = j
                continue
            perm = body.lstrip().startswith('%')
            if perm:
                body = body.lstrip()[1:]
            m = re.match(r'\s*(\w+)\s*:(?!:)', body)
            name = m.group(1) if m else None
            if m:
                body = body[m.end():]
            alts = [a.strip('\n') if '\n' in a else a.strip() for a in _split_alts(body)]
            if perm:  # {{%name: a | b | c}}: every order of the items, one per line
                ind = re.match(r'[ \t]*', s[s.rfind('\n', 0, i) + 1:i]).group(0)
                alts = [('\n' + ind).join(o) for o in itertools.permutations(alts)]
            if name and name in names:
                ax = names[name]
                if axes[ax][1] != len(alts):
                    raise SystemExit(f'linked point {name!r}: {len(alts)} alternatives, earlier {axes[ax][1]}')
            else:
                axes.append((name or f'p{len(axes)}', len(alts)))
                ax = len(axes) - 1
                if name:
                    names[name] = ax
            alt_pieces = [parse(a) for a in alts]
            if name and name not in refs:
                refs[name] = alt_pieces
            out.append((ax, alt_pieces))
            pos = j
    pieces = parse(t)
    return pieces, axes


def render(pieces, pick):
    out = []
    for p in pieces:
        out.append(p if isinstance(p, str) else render(p[1][pick[p[0]]], pick))
    return ''.join(out)


def picks(axes, sample=0, seed=0):
    sizes = [a[1] for a in axes]
    total = 1
    for s in sizes:
        total *= s
    if sample and sample < total:
        rnd = random.Random(seed)
        seen = {tuple([0] * len(sizes))}
        out = [tuple([0] * len(sizes))]
        while len(out) < sample:
            p = tuple(rnd.randrange(s) for s in sizes)
            if p not in seen:
                seen.add(p)
                out.append(p)
        return out, total
    return list(itertools.product(*[range(s) for s in sizes])), total


# --------------------------------------------------------------------------
# trace

class Trace:
    def __init__(self, lines):
        self.lines = lines
        self.kinds, self.names, self.byname = {}, {}, {}
        self.creators, self.phys, self.order, self.pre, self.post = {}, {}, [], [], []
        for l in lines:
            f = l.split()
            if not f:
                continue
            if f[0] == 'VREG' and len(f) >= 4:
                v = int(f[2][1:])
                self.kinds[v] = f[1]
                self.names[v] = f[3] if len(f) > 3 else ''
                self.byname.setdefault(self.names[v], v)
            elif f[0] == 'TEMPNEW':
                m = re.search(r'outer=(\S+)', l)
                c = re.search(r'caller=(\S+)', l)
                o = m.group(1) if m else '-'
                self.creators[f[1]] = c.group(1) if o == '-' and c else o
            elif f[0] == 'IGNODE' and f[1] == 'r':
                self.phys[int(f[2])] = int(f[4])
            elif f[0] == 'COLOR' and f[1] == 'r':
                self.order.append(int(f[2]))
            elif f[0] == 'PCODE':
                m = re.match(r'PCODE (pre|post) B(\d+) (-?\d+) (.*)', l)
                if m:
                    (self.pre if m.group(1) == 'pre' else self.post).append(
                        (int(m.group(2)), int(m.group(3)), m.group(4)))

    @property
    def post_text(self):
        """post-RA PCode, one instruction per line (for multi-line regexes)."""
        return '\n'.join(i for _, _, i in self.post)

    @property
    def pre_text(self):
        return '\n'.join(i for _, _, i in self.pre)

    def vreg(self, name):
        return self.byname.get(name)

    def kind(self, name):
        v = self.vreg(name)
        return self.kinds.get(v) if v is not None else None

    def reg(self, name_or_vreg):
        v = name_or_vreg if isinstance(name_or_vreg, int) else self.vreg(name_or_vreg)
        return self.phys.get(v) if v is not None else None

    def creator(self, temp):
        return self.creators.get(temp)

    def temps(self, creator):
        return [t for t, c in self.creators.items() if c == creator]

    def defs(self, pat):
        rx = re.compile(pat)
        out = []
        for _, _, insn in self.pre:
            if rx.search(insn):
                out += [int(x) for x in re.findall(r'\br(\d+)!', insn) if int(x) >= 32]
        return out or [10 ** 6]

    def vdef(self, pat, k=0):
        """vreg written by the k-th pre-RA PCode line matching pat (None if absent)."""
        rx = re.compile(pat)
        hits = [insn for _, _, insn in self.pre if rx.search(insn)]
        if len(hits) <= k:
            return None
        m = re.search(r'\br(\d+)!', hits[k])
        return int(m.group(1)) if m else None

    def num(self, pat, k=0):
        """vreg number written by the k-th pre-RA line matching pat (10**6 if absent)."""
        v = self.vdef(pat, k)
        return 10 ** 6 if v is None else v

    def named(self, pat, k=0):
        """True if the k-th pre-RA line matching pat writes a named local, or a
        temp that is copied straight into one (`MR rL!,rV`)."""
        v = self.vdef(pat, k)
        if v is None:
            return False
        if self.kinds.get(v) == 'local':
            return True
        rx = re.compile(r'^MR r(\d+)!,r%d\b' % v)
        return any(self.kinds.get(int(m.group(1))) == 'local'
                   for _, _, insn in self.pre for m in [rx.search(insn)] if m)

    def pdef(self, pat, k=0):
        """machine register written by the k-th post-RA PCode line matching pat."""
        rx = re.compile(pat)
        hits = [insn for _, _, insn in self.post if rx.search(insn)]
        if len(hits) <= k:
            return None
        m = re.search(r'\br(\d+)!', hits[k])
        return int(m.group(1)) if m else None

    def vmatch(self, pat, k=0, post=False):
        """int(group 1) of the k-th PCode line (pre-RA, or post-RA with post=True)
        matching pat, e.g. T.vmatch(r'^LHZX r\\d+!,r(\\d+),') = the lhzx base."""
        rx = re.compile(pat)
        hits = [m for _, _, insn in (self.post if post else self.pre) for m in [rx.search(insn)] if m]
        return int(hits[k].group(1)) if len(hits) > k else None

    def uses(self, pat):
        rx = re.compile(pat)
        out = []
        for _, _, insn in self.pre:
            if rx.search(insn):
                out += [int(x) for x in re.findall(r'\br(\d+)\b(?!!)', insn) if int(x) >= 32]
        return out

    def line_regs(self, srcline):
        return sorted({int(x) for _, s, insn in self.post if s == srcline
                       for x in re.findall(r'\br(\d+)!', insn)})

    def rank(self, name_or_vreg):
        v = name_or_vreg if isinstance(name_or_vreg, int) else self.vreg(name_or_vreg)
        return self.order.index(v) if v in self.order else None

    def summary(self):
        out = []
        for v in sorted(self.kinds):
            n = self.names[v]
            c = f' by {self.creators.get(n)}' if n.startswith('@') else ''
            out.append(f'r{v:<4} {self.kinds[v]:<8} {n:<12} -> r{self.phys.get(v, "?")}{c}')
        return '\n'.join(out)


# --------------------------------------------------------------------------
# compiling

class Sweep:
    def __init__(self, unit, fn, keep_going=False, base_text=None):
        self.u = ps.Unit(unit)
        if base_text is not None:      # replay from another TU text (regfix diag --start-tu)
            self.u.text = base_text
        self.unit = unit
        self.fn = fn
        d, self.cname = self.u.resolve(fn)
        if not d:
            raise SystemExit(f'{fn}: definition not found in {self.u.src}')
        self.span = d
        self.cmd, self.ver, self.nv = mwtrace.command(unit)
        self.target = ps.target_body(fn)
        if self.target is None:
            raise SystemExit(f'{fn}: no target asm (build first)')
        self.lock = threading.Lock()
        self.ids = itertools.count()
        self.local = threading.local()
        os.makedirs(TMP, exist_ok=True)

    def text_with(self, definition):
        ls, _, be = self.span
        t = self.u.text
        return t[:ls] + definition + t[be:]

    def _wid(self):
        if not hasattr(self.local, 'id'):
            with self.lock:
                self.local.id = next(self.ids)
        return self.local.id

    def native(self, text, want_lines=True):
        """Compile with the traced native compiler -> (Trace, diff lines, error)."""
        wk = self._wid()
        d = os.path.join(TMP, f'w{os.getpid()}_{wk}')
        os.makedirs(d, exist_ok=True)
        for f in glob.glob(d + '/*'):
            os.remove(f)
        sp = os.path.join(os.path.dirname(os.path.abspath(self.u.src)), f'.tsweep_{os.getpid()}_w{wk}{self.u.ext}')
        with open(sp, 'w') as fh:
            fh.write(text)
        cmd = list(self.cmd)
        cmd[cmd.index('-c') + 1] = sp
        obj = os.path.join(d, 'out.o')
        cmd[cmd.index('-o') + 1] = obj
        tf = os.path.join(d, 'trace.txt')
        env = dict(os.environ, MWCC_TRACE=tf, MWCC_TRACE_FN=self.cname)
        r = subprocess.run(cmd, cwd=ROOT, env=env, capture_output=True, text=True)
        os.remove(sp)
        if r.returncode or not os.path.exists(obj):
            err = (r.stdout + r.stderr).strip().splitlines()
            return None, 10 ** 6, ' / '.join(x for x in err if 'rror' in x)[:300] or 'compile failed'
        lines = open(tf).read().splitlines() if os.path.exists(tf) else []
        T = Trace(mwtrace.symbolize(cmd[0], lines))
        subprocess.run([ps.DTK, 'elf', 'disasm', obj, d + '/m.s'], capture_output=True)
        B = ps.norm_body(d + '/m.s', self.cname) or ps.norm_body(d + '/m.s', self.fn)
        if not B:
            return T, 10 ** 6, 'function not emitted'
        import difflib
        n = sum(1 for l in difflib.unified_diff(self.target, B, lineterm='', n=0)
                if l[:1] in '+-' and not l.startswith(('+++', '---')))
        return T, n, None

    def real(self, text):
        """Real compiler (the unit's own GC version), objdiff fuzzy % -> (pct, diff lines)."""
        ps.OBJDIFF = True
        s = self.u.compile_score(text, self.fn, self.u.cc, 1000 + self._wid())
        ps.OBJDIFF = False
        lines = self.u.compile_score(text, self.fn, self.u.cc, 1000 + self._wid())
        return (None if s >= 10 ** 6 else 100.0 - s / 100.0), lines


def evaluate(want, T):
    if not want:
        return None
    try:
        return bool(eval(want, {'re': re, 'min': min, 'max': max, 'any': any, 'all': all, 'len': len}, {'T': T}))
    except Exception as e:  # noqa: BLE001 - a predicate on a variant missing a name is just False
        return False if not os.environ.get('TRACESWEEP_DEBUG') else f'err {e}'


def run(unit, fn, template_text, want=None, jobs=8, sample=0, seed=0, confirm=3, show=15, quiet=False,
        log_name=None, probe=None, base_text=None):
    sw = Sweep(unit, fn, base_text=base_text)
    pieces, axes = parse_template(template_text)
    plist, total = picks(axes, sample, seed)
    if not quiet:
        print(f'{fn}: {len(axes)} choice points, {total} variants'
              + (f', sampling {len(plist)}' if len(plist) < total else '')
              + f'; {sw.u.cc} unit, oracle native GC/{sw.nv.replace("_", ".")}', flush=True)
    base_T, base_n, _ = sw.native(sw.u.text)
    if not quiet:
        print(f'current source: diff {base_n}, want={evaluate(want, base_T)}', flush=True)
    seen = {}
    results = []
    t0 = time.time()
    log = open(os.path.join(TMP, f'{log_name or fn}.log.jsonl'), 'w')

    def one(p):
        text = render(pieces, p)
        h = hashlib.sha1(text.encode()).hexdigest()
        with sw.lock:
            if h in seen:
                return None
            seen[h] = p
        T, n, err = sw.native(sw.text_with(text))
        w = evaluate(want, T) if T else False
        r = {'pick': list(p), 'want': w, 'diff': n, 'err': err, 'text': text}
        if probe and T:
            try:
                r['probe'] = eval(probe, {'re': re, 'min': min, 'max': max}, {'T': T})
            except Exception as e:  # noqa: BLE001
                r['probe'] = f'err {e}'
        return r

    with ThreadPoolExecutor(jobs) as ex:
        for i, r in enumerate(ex.map(one, plist)):
            if r is None:
                continue
            results.append(r)
            log.write(json.dumps({k: v for k, v in r.items() if k != 'text'}) + '\n')
            if not quiet and (i + 1) % 200 == 0:
                best = min(results, key=key)
                print(f'  {i + 1}/{len(plist)} {time.time() - t0:.0f}s best diff {best["diff"]} want={best["want"]}',
                      flush=True)
    log.close()
    results.sort(key=key)
    if not results:
        raise SystemExit('no variants compiled')
    best = results[0]
    with open(os.path.join(TMP, f'{log_name or fn}.best{sw.u.ext}'), 'w') as fh:
        fh.write(best['text'])
    if not quiet:
        nwant = sum(1 for r in results if r['want'] is True)
        nerr = sum(1 for r in results if r['err'])
        print(f'{len(results)} distinct variants in {time.time() - t0:.0f}s; want=True: {nwant}; errors: {nerr}')
        for r in results[:show]:
            desc = ' '.join(f'{axes[k][0]}={v}' for k, v in enumerate(r['pick']) if v)
            print(f'  diff {r["diff"]:>5}  want={r["want"]!s:<5}'
                  + (f' probe={r.get("probe")!s:<6}' if probe else '') + f' {desc or "(all first)"}'
                  + (f'  ERR {r["err"]}' if r['err'] else ''))
        if nerr == len(results):
            print('all variants failed to compile; first error:', results[0]['err'])
    for r in results[:confirm]:
        if r['err']:
            continue
        pct, lines = sw.real(sw.text_with(r['text']))
        r['real_pct'], r['real_diff'] = pct, lines
        if not quiet:
            print(f'  confirm (real GC/{sw.u.cc}) pick={r["pick"]}: objdiff {pct}%, diff {lines}')
    if not quiet:
        print(f'best source: {os.path.join(TMP, (log_name or fn) + ".best" + sw.u.ext)}')
    return results, axes


def key(r):
    return (0 if r['want'] is True else 1, r['diff'])


# --------------------------------------------------------------------------

def cmd_trace(a):
    sw = Sweep(a.unit, a.fn)
    text = sw.u.text
    if a.template:
        pieces, axes = parse_template(strip_header(open(a.template).read()))
        p = [int(x) for x in a.pick.split(',')] if a.pick else []
        p += [0] * (len(axes) - len(p))
        text = sw.text_with(render(pieces, p))
    T, n, err = sw.native(text)
    if err:
        sys.exit(err)
    print(f'diff {n}')
    print(T.summary())
    if a.want:
        print('want:', evaluate(a.want, T))


def cmd_run(a):
    tmpl = open(a.template).read()
    want = a.want
    m = re.search(r'^//\s*want:\s*(.+)$', tmpl, re.M) or re.search(r'^/\*\s*want:\s*(.+?)\s*\*/', tmpl, re.M)
    if not want and m:
        want = m.group(1).strip()
        print(f'want (from template): {want}')
    tmpl = strip_header(tmpl)
    run(a.unit, a.fn, tmpl, want, a.jobs, a.sample, a.seed, a.confirm, a.show, probe=a.probe)


def strip_header(t):
    """Template files may start with `// unit:`, `// fn:`, `// want:`, `// expect:` lines."""
    lines = t.splitlines(keepends=True)
    i = 0
    while i < len(lines) and re.match(r'//\s*(unit|fn|want|expect|note):', lines[i]):
        i += 1
    return ''.join(lines[i:])


def header(t, k):
    m = re.search(rf'^//\s*{k}:\s*(.+)$', t, re.M)
    return m.group(1).strip() if m else None


def cmd_selftest(a):
    ok = True
    for f in sorted(glob.glob(os.path.join(SELFTEST, '*.tmpl'))):
        t = open(f).read()
        unit, fn, want, expect = header(t, 'unit'), header(t, 'fn'), header(t, 'want'), header(t, 'expect')
        res, axes = run(unit, fn, strip_header(t), want, a.jobs, confirm=0, quiet=True,
                        log_name=f'selftest_{fn}')
        best = res[0]
        good = best['diff'] == 0 and (expect is None or ','.join(map(str, best['pick'])) == expect)
        ok &= good
        base = next((r for r in res if r['pick'] == [0] * len(axes)), None)
        print(f'{"PASS" if good else "FAIL"} {os.path.basename(f)}: best pick {best["pick"]} diff {best["diff"]} '
              f'want={best["want"]}; pre-fix shape diff {base["diff"] if base else "?"} '
              f'want={base["want"] if base else "?"}')
    sys.exit(0 if ok else 1)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    sub = ap.add_subparsers(dest='cmd', required=True)
    r = sub.add_parser('run')
    r.add_argument('unit')
    r.add_argument('fn')
    r.add_argument('template')
    r.add_argument('--want')
    r.add_argument('--probe', help='expression over T logged per variant (e.g. the register --want tests)')
    r.add_argument('-j', '--jobs', type=int, default=os.cpu_count() or 4)
    r.add_argument('--sample', type=int, default=0)
    r.add_argument('--seed', type=int, default=0)
    r.add_argument('--confirm', type=int, default=3)
    r.add_argument('--show', type=int, default=15)
    r.set_defaults(f=cmd_run)
    t = sub.add_parser('trace')
    t.add_argument('unit')
    t.add_argument('fn')
    t.add_argument('--template')
    t.add_argument('--pick')
    t.add_argument('--want')
    t.set_defaults(f=cmd_trace)
    s = sub.add_parser('selftest')
    s.add_argument('-j', '--jobs', type=int, default=os.cpu_count() or 4)
    s.set_defaults(f=cmd_selftest)
    a = ap.parse_args()
    a.f(a)


if __name__ == '__main__':
    main()
