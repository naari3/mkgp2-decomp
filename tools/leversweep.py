#!/usr/bin/env python3
"""leversweep.py: diagnosis-triggered source rewrites ("levers") over the near misses.

Each lever is one mechanical source rewrite that landed a function by hand
(the commit is in LEVERS below). A lever is tried on a function only when

  1. its SOURCE trigger finds the shape it rewrites in the function's
     definition (a pointer parameter, a call to a TU-local static inline,
     a walking pointer in a for loop, ...), and
  2. its DIAG trigger accepts the shape of the objdiff diff
     (tools/regswap_classify.analyze: reg_only / reg+sched / no_reg ..., plus
     which mnemonics sit in the mismatching window).

So the batch is diagnose-then-pick, not a blind permuter: a function sees only
the levers whose two triggers fire, typically 0-3 levers and 1-30 variants.

Every variant is compiled from a scratch copy (pragmasweep.Unit.compile_score,
the TU's own compiler) and scored by diff lines; the best improvement is
re-scored with objdiff and written to OUT/hits/ (src/ is never written).

    python3 tools/leversweep.py list                 levers, rule ids, class
    python3 tools/leversweep.py fn UNIT FN [--levers a,b] [-j 4] [--show]
    python3 tools/leversweep.py batch [--min 90] [--max 100] [--levers ..]
        [--out docs/sweeps/leversweep] [-j 4] [--only FN,FN] [--retry]
    python3 tools/leversweep.py selftest             replays landed fixes

batch writes OUT/results.jsonl (one row per function: triggers fired, variants,
best) and OUT/summary.md. Land a hit claim-first, as with any sweep, and record
it with `rewrite_rules.py record` after it is on main.
"""
from __future__ import annotations

import argparse
import itertools
import json
import os
import re
import subprocess
import sys
import time
from concurrent.futures import ThreadPoolExecutor

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import pragmasweep as ps  # noqa: E402
import regswap_classify as rc  # noqa: E402

ps.DTK = getattr(ps, 'DTK', 'build/tools/dtk')
FAIL = 10 ** 6

# --------------------------------------------------------------------------
# small C text helpers (text level on purpose: the levers are textual)

ID = r'[A-Za-z_]\w*'
CKW = {'if', 'for', 'while', 'switch', 'return', 'sizeof', 'do', 'else', 'case', 'goto', 'new', 'delete',
       'throw', 'catch', 'try', 'break', 'continue', 'default'}
SCALARS = {'int', 'unsigned', 'signed', 'short', 'long', 'char', 'float', 'double', 'u8', 'u16', 'u32', 's8',
           's16', 's32', 'f32', 'f64', 'BOOL', 'bool', 'size_t', 'uint', 'u64', 's64'}
FLOATS = {'float', 'double', 'f32', 'f64', 'Real', 'real'}


def strip_comments(s):
    return re.sub(r'/\*.*?\*/|//[^\n]*', lambda m: ' ' * len(m.group(0)) if '\n' not in m.group(0)
                  else re.sub(r'[^\n]', ' ', m.group(0)), s, flags=re.S)


def match_paren(s, i, o='(', c=')'):
    """index just past the bracket closing the one at s[i]."""
    d = 0
    for j in range(i, len(s)):
        if s[j] == o:
            d += 1
        elif s[j] == c:
            d -= 1
            if d == 0:
                return j + 1
    return -1


def split_args(s):
    out, d, cur = [], 0, ''
    for ch in s:
        if ch in '([{':
            d += 1
        elif ch in ')]}':
            d -= 1
        if ch == ',' and d == 0:
            out.append(cur.strip())
            cur = ''
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def param_list(head):
    i = head.find('(')
    j = match_paren(head, i)
    inner = head[i + 1:j - 1].strip()
    if inner in ('', 'void'):
        return []
    return split_args(inner)


def param_name(p):
    m = re.search(r'(' + ID + r')\s*(?:\[[^\]]*\])*\s*$', p)
    return m.group(1) if m else None


def param_type(p):
    n = param_name(p)
    return p[:p.rfind(n)].strip() if n else p


def is_float_type(t):
    t = re.sub(r'\b(const|volatile|register)\b', '', t).strip()
    return '*' not in t and '&' not in t and t.split()[-1:] and t.split()[-1] in FLOATS


def sub_ident(text, name, repl):
    return re.sub(r'(?<![\w.>])' + re.escape(name) + r'\b(?!\s*::)', lambda _: repl, text)


def sub_ident_any(text, name, repl):
    """also after . / -> (for renaming locals; members never share these names)."""
    return re.sub(r'(?<![\w])' + re.escape(name) + r'\b', lambda _: repl, text)


def is_simple(e):
    e = e.strip()
    return bool(re.fullmatch(r'-?\d+[uUlLfF]*|-?\d*\.\d+[fF]?|0x[0-9a-fA-F]+[uUlL]*|' + ID
                             + r'(?:(?:->|\.)' + ID + r'|\[\s*(?:' + ID + r'|\d+)\s*\])*', e))


# --------------------------------------------------------------------------
# function context

class Fx:
    def __init__(self, unit, fn, demangled=None):
        self.u = ps.Unit(unit)
        self.unit, self.fn = unit, fn
        self.text = self.u.text
        d, self.sym = self.u.resolve(fn, demangled)
        self._scopes = None
        if not d:
            # templates / out-of-class methods we cannot locate: only TU-wide levers run
            self.sym = self.u.compiled_name(fn)
            self.d = (0, 0, 1)
            self._scopes = []
            self.head = self.body = ''
            self.params = []
            self.cpp = self.u.ext != '.c'
            self.cc = self.u.cc
            self.diag = None
            self.L = self.R = None
            return
        self.d = d
        ls, bs, be = d
        self.head = self.text[ls:bs]
        self.body = self.text[bs:be - 1]
        self.params = param_list(self.head)
        self.cpp = self.u.ext != '.c'
        self.cc = self.u.cc
        self.diag = None
        self.L = self.R = None

    def with_body(self, body, head=None, prelude='', pragmas=(), text=None):
        """full TU text with the definition replaced."""
        ls, bs, be = self.d
        t = text if text is not None else self.text
        if text is not None:  # caller rewrote other parts; find the def again
            d = ps.find_def(t, self.fn, None, self.sym)
            if not d:
                return None
            ls, bs, be = d
        f = (head or self.head) + body + '}'
        if pragmas:
            f = '#pragma push\n' + ''.join(f'#pragma {p}\n' for p in pragmas) + f + '\n#pragma pop'
        return t[:ls] + prelude + f + t[be:]

    def scopes(self):
        """[(name, body_start, body_end)] spans of the function body and of the
        TU-local inline functions it calls (transitively, 3 levels): a lever's
        shape often sits in a helper the function expands."""
        if self._scopes is not None:
            return self._scopes
        ls, bs, be = self.d
        out = [(self.fn, bs, be - 1)]
        inl = tu_inline_spans(self)
        todo, seen = [self.text[bs:be - 1]], set()
        for _ in range(3):
            nxt = []
            for b in todo:
                for name in set(re.findall(r'(?<![\w.>])(' + ID + r')\s*\(', strip_comments(b))):
                    if name in inl and name not in seen:
                        seen.add(name)
                        s0, s1 = inl[name]
                        out.append((name, s0, s1))
                        nxt.append(self.text[s0:s1])
            todo = nxt
        self._scopes = out
        return out

    def scoped(self, f):
        """apply f(body) -> [(label, new_body)] to every scope; -> [(label, tu_text)]."""
        res = []
        for name, s0, s1 in self.scopes():
            for lab, nb in f(self.text[s0:s1]):
                if nb is None or nb == self.text[s0:s1]:
                    continue
                res.append((lab if name == self.fn else f'[{name}] {lab}', self.text[:s0] + nb + self.text[s1:]))
        return res

    def diagnose(self):
        """objdiff alignment of the CURRENT build object vs the target (needs a build)."""
        rep = getattr(Fx, '_rep', None)
        if rep is None:
            rep = Fx._rep = {u['name']: u for u in json.load(open('build/GNLJ82/report.json'))['units']}
        unit = {'target_path': f'build/GNLJ82/obj/{self.unit}.o', 'base_path': f'build/GNLJ82/src/{self.unit}.o'}
        r = rc.run_objdiff(unit, self.fn)
        if not r:
            self.diag = {'kind': 'unknown'}
            return self.diag
        self.L, self.R = r
        self.diag = rc.analyze(self.L, self.R)
        win = set()
        for i in range(max(len(self.L), len(self.R))):
            for side in (self.L, self.R):
                x = side[i] if i < len(side) else {}
                if x.get('diff_kind') and x.get('instruction'):
                    win.add(rc.ops(x['instruction'])[0])
        self.diag['window'] = sorted(win)
        return self.diag

    def win(self, *mns):
        w = set((self.diag or {}).get('window', []))
        return any(m in w or any(x.startswith(m) for x in w) for m in mns)

    def regdiff(self):
        return (self.diag or {}).get('kind') in ('reg_only', 'reg+sched', 'reg+other')


# --------------------------------------------------------------------------
# levers. gen(fx) -> [(label, full_tu_text)]

LEVERS = {}


def lever(name, rule, cls, commit, desc):
    def deco(f):
        LEVERS[name] = dict(name=name, rule=rule, cls=cls, commit=commit, desc=desc, gen=f)
        return f
    return deco


# The table of today's levers that are NOT implemented here (semi / manual).
NOT_AUTOMATED = [
    ('inline-asm r2/r13 fixed offsets -> symbol refs', '-', 'auto (nothing left)', '71b5ffd4',
     'grep: no game TU has a numeric r2/r13 displacement in inline asm any more (only TRK, already matching)'),
    ('split the pool at `addi rX, anchor, N`', 'anchor-addi-object-boundary', 'semi (detect only)', '§40',
     '`leversweep.py detect` lists the functions and offsets; the split edits the pool source and symbols.txt'),
    ('rolled-loop + opt_unroll_instr_count', 'loop-unroll-budget', 'semi', '833c85a',
     'pragma half is automatic (pragmasweep --set extended sweeps opt_unroll_instr_count 8/16/32); '
     'rolling a hand-unrolled loop back needs the loop count and the induction step, which differ per site'),
    ('base vtable store in the ctor body', 'base-init-in-body', 'semi', '§36',
     'needs the base class vtable symbol and a ctor that has address locals; trigger (prologue lis/addi swap) is '
     'cheap but there were 2 C++ ctors near misses with that shape, done by hand'),
    ('avoid IRO CSE temps', '-', 'semi', '3cc4b0e',
     'the rewrite (read through a cast pointer / hoist before) is a fakematch-flavoured choice per site; '
     'shapesweep hoist covers the hoist half, the trigger needs a mwtrace TEMPNEW trace'),
    ('pool-owner TU merges', 'merge-pool-owner', 'semi', '7653d99',
     'pool_audit.py finds them; the merge edits splits.txt/configure.py/symbols and has to respect claims'),
    ('TU merges (correct structure)', 'merge-pool-owner', 'manual', '5d5f466b',
     'tu_audit.py proposes; each merge is a splits/configure/extab job checked against main.dol'),
]


def ptr_params(fx):
    out = []
    for i, p in enumerate(fx.params):
        n = param_name(p)
        t = param_type(p)
        if n and '*' in t and '__restrict' not in p and n != 'this' and '(' not in p:
            out.append((i, n))
    return out


@lever('restrict-input-ptrs', 'restrict-input-ptrs', 'auto', 'fa1d62e (§30)',
       '__restrict on pointer parameters (subsets): lets loads be hoisted over stores through other pointers')
def gen_restrict(fx):
    if not (fx.win('lwz', 'lfs', 'lha', 'lhz', 'lbz', 'lfd') and fx.win('st')):
        return []
    pp = ptr_params(fx)
    if not pp or len(pp) > 5:
        return []
    out = []
    subsets = [s for k in range(1, len(pp) + 1) for s in itertools.combinations(pp, k)]
    for s in subsets[:31]:
        ps_ = list(fx.params)
        for i, n in s:
            p = ps_[i]
            k = p.rfind('*')
            ps_[i] = p[:k + 1] + ' __restrict ' + p[k + 1:].lstrip()
        head = rewrite_params(fx.head, ps_)
        out.append(('restrict ' + ','.join(n for _, n in s), fx.with_body(fx.body, head=head)))
    # const pointee (const-pointee-hoist): same shape, cheaper alias
    for i, n in pp:
        p = fx.params[i]
        if p.lstrip().startswith('const') or re.match(r'\s*(void|char)\b', p):
            continue
        ps_ = list(fx.params)
        ps_[i] = 'const ' + p.lstrip()
        out.append((f'const *{n}', fx.with_body(fx.body, head=rewrite_params(fx.head, ps_))))
    return out


def rewrite_params(head, params):
    i = head.find('(')
    j = match_paren(head, i)
    return head[:i + 1] + ', '.join(params) + head[j - 1:]


# ---- arg-order-prototype (§37)

def find_proto(fx, name):
    """(param list, ret type, defined_here) of a callee from the TU or its includes."""
    srcs = [fx.text]
    for p in sorted(includes_of(fx)):
        try:
            srcs.append(open(p, errors='replace').read())
        except OSError:
            pass
    for t in srcs:
        t2 = strip_comments(t)
        for m in re.finditer(r'(?:^|[;}\n])\s*((?:extern\s+"C"\s+)?(?:(?:static|inline|extern|const|unsigned|signed|struct)\s+)*'
                             + ID + r'[\s*&]+)' + re.escape(name) + r'\s*\(', t2):
            k = m.end() - 1
            e = match_paren(t2, k)
            if e < 0:
                continue
            after = t2[e:e + 40].lstrip()
            ps_ = split_args(t2[k + 1:e - 1])
            if ps_ == ['void']:
                ps_ = []
            return ps_, m.group(1).strip(), after.startswith('{')
    return None


def includes_of(fx):
    if not hasattr(fx, '_inc'):
        ip = re.findall(r'-i\s+(\S+)|-I(\S+)', fx.u.cmd)
        ipaths = [a or b for a, b in ip]
        sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
        import shapesweep as ss
        fx._inc = ss.includes(fx.u.src, fx.text, ipaths, set())
    return fx._inc


def interleavings(kinds):
    """all orders of the parameter indices that keep ints in order and floats in order."""
    ints = [i for i, k in enumerate(kinds) if not k]
    fls = [i for i, k in enumerate(kinds) if k]
    n = len(kinds)
    out = []
    for pos in itertools.combinations(range(n), len(fls)):
        order, ii, ff = [], iter(ints), iter(fls)
        for j in range(n):
            order.append(next(ff) if j in pos else next(ii))
        if order != list(range(n)):
            out.append(order)
    return out


@lever('arg-order-prototype', 'arg-order-prototype', 'auto', '28b9fb6 (§37)',
       'reorder int/float parameters of a callee prototype (same registers, other evaluation order)')
def gen_argorder(fx):
    if not (fx.win('lf', 'fmr') and fx.win('lwz', 'mr', 'addi', 'li')):
        return []
    scopes = fx.scopes()
    out = []
    seen = set()
    for _, s0, s1 in scopes:
        for m in re.finditer(r'(?<![\w.>])(' + ID + r')\s*\(', strip_comments(fx.text[s0:s1])):
            name = m.group(1)
            if name in CKW or name in seen:
                continue
            seen.add(name)
            pr = find_proto(fx, name)
            if not pr:
                continue
            params, ret, here = pr
            if here or len(params) < 2 or len(params) > 7:
                continue
            kinds = [is_float_type(param_type(p) if param_name(p) else p) for p in params]
            if not any(kinds) or all(kinds):
                continue
            rt = re.sub(r'\b(extern|static|inline)\b|"C"', '', ret).strip()
            for order in interleavings(kinds)[:12]:
                wname = f'{name}__lv{"".join(map(str, order))}'
                wp = [f'{(param_type(params[i]) if param_name(params[i]) else params[i])} a{i}' for i in order]
                call = f'{name}({", ".join(f"a{i}" for i in range(len(params)))})'
                wrapper = f'static inline {rt} {wname}({", ".join(wp)}) {{ {"" if rt == "void" else "return "}{call}; }}\n'
                t = fx.text
                first = None
                ok = True
                for _, a0, a1 in sorted(scopes, key=lambda x: -x[1]):
                    nb = rewrite_calls(t[a0:a1], name, lambda args: f'{wname}({", ".join(args[i] for i in order)})'
                                       if len(args) == len(order) else None)
                    if nb is None:
                        ok = False
                        break
                    if nb != t[a0:a1]:
                        t = t[:a0] + nb + t[a1:]
                        first = a0 if first is None else min(first, a0)
                if not ok or first is None:
                    continue
                ins = func_start(t, first)
                out.append((f'{name} order {order}', t[:ins] + wrapper + t[ins:]))
    return out


def func_start(t, body_start):
    """start of the line holding the head of the function whose body opens at body_start."""
    i = t.rfind('(', 0, body_start)
    i = t.rfind('\n', 0, i) + 1
    while i > 0:
        j = t.rfind('\n', 0, i - 1) + 1
        prev = t[j:i].strip()
        if prev and not prev.endswith((';', '}', '*/')) and not prev.startswith('#'):
            i = j
        else:
            break
    return i


def rewrite_calls(body, name, f):
    res, i = '', 0
    for m in re.finditer(r'(?<![\w.>])' + re.escape(name) + r'\s*\(', body):
        if m.start() < i:
            continue
        k = m.end() - 1
        e = match_paren(body, k)
        if e < 0:
            return None
        new = f(split_args(body[k + 1:e - 1]))
        if new is None:
            return None
        res += body[i:m.start()] + new
        i = e
    return res + body[i:]


# ---- index-for-walk (025713e): `p = base; for (i = 0; ..; ++i, ++p) .. p[k] ..` -> base[i + k]

@lever('index-for-walk', 'addr-on-demand', 'auto', '025713e',
       'walking pointer in a counted loop -> indexed access off the base (codegen temp instead of a named IV)')
def gen_index(fx):
    if not fx.regdiff() and not fx.win('addi', 'lwzu', 'lbzu', 'lhzu', 'stwu', 'lfsu'):
        return []
    return fx.scoped(index_rewrites)


def index_rewrites(b):
    out = []
    for m in re.finditer(r'for\s*\(', b):
        k = m.end() - 1
        e = match_paren(b, k)
        if e < 0:
            continue
        hdr = split_top_semis(b[k + 1:e - 1])
        if len(hdr) != 3:
            continue
        init, cond, inc = hdr
        incs = [x.strip() for x in split_args(inc)]
        ivm = re.fullmatch(r'(' + ID + r')\s*=\s*0', init.strip()) or \
            re.search(r'(?:^|,)\s*(' + ID + r')\s*=\s*0\s*(?:,|$)', init)
        if not ivm:
            continue
        iv = ivm.group(1)
        walkers = []
        for x in incs:
            w = re.fullmatch(r'(?:\+\+\s*(' + ID + r')|(' + ID + r')\s*\+\+|(' + ID + r')\s*\+=\s*1)', x)
            if w:
                n = w.group(1) or w.group(2) or w.group(3)
                if n != iv:
                    walkers.append(n)
        for p in walkers:
            # base: `p = E` in the for init or the last `p = E;` before the loop
            base = None
            im = re.search(r'(?:^|,)\s*' + re.escape(p) + r'\s*=\s*([^,]+)', init)
            pre_assign = None
            if im:
                base = im.group(1).strip()
            else:
                ams = list(re.finditer(r'(?<![\w.>])' + re.escape(p) + r'\s*=\s*([^;=][^;]*);', b[:m.start()]))
                if ams:
                    base = ams[-1].group(1).strip()
                    pre_assign = ams[-1]
                    # p must not be used between the assignment and the loop
                    if re.search(r'\b' + re.escape(p) + r'\b', b[ams[-1].end():m.start()]):
                        continue
            if not base:
                continue
            # loop body
            bs_ = e
            while bs_ < len(b) and b[bs_] in ' \t\n':
                bs_ += 1
            if b[bs_:bs_ + 1] == '{':
                be_ = match_paren(b, bs_, '{', '}')
            else:
                be_ = b.find(';', bs_) + 1
            if be_ <= 0:
                continue
            lb = b[bs_:be_]
            rest = b[be_:]
            if re.search(r'(?<![\w.>])' + re.escape(p) + r'\b', rest) and not re.search(
                    r'(?<![\w.>])' + re.escape(p) + r'\s*=[^=]', rest.split(re.escape(p))[0] if False else rest[:400]):
                pass
            if re.search(r'(?<![\w.>])' + re.escape(p) + r'\b', rest):
                # used after the loop: only safe if reassigned before any read; skip
                nxt = re.search(r'(?<![\w.>])' + re.escape(p) + r'\b(\s*=[^=])?', rest)
                if not nxt.group(1):
                    continue
            bse = base if is_simple(base) else f'({base})'
            for form in ('base', 'p'):
                nb_ = lb
                src = bse if form == 'base' else p
                nb_ = re.sub(r'(?<![\w.>])' + re.escape(p) + r'\s*\[\s*([^\]]+?)\s*\]',
                             lambda mm: f'{src}[{iv} + {mm.group(1)}]' if mm.group(1) != '0' else f'{src}[{iv}]', nb_)
                nb_ = re.sub(r'\*\s*' + re.escape(p) + r'\b(?!\s*\[)', f'{src}[{iv}]', nb_)
                nb_ = re.sub(r'(?<![\w.>])' + re.escape(p) + r'\s*->', f'{src}[{iv}].', nb_)
                if re.search(r'(?<![\w.>])' + re.escape(p) + r'\b', nb_.replace(f'{p}[{iv}', '')) and form == 'base':
                    continue  # p used as a value: not a pure walker
                ninc = ', '.join(x for x in incs if not re.fullmatch(
                    r'(?:\+\+\s*' + re.escape(p) + r'|' + re.escape(p) + r'\s*\+\+|' + re.escape(p) + r'\s*\+=\s*1)', x))
                ninit = init
                nb2 = b
                if form == 'base':
                    if im:
                        ninit = re.sub(r'(^|,)\s*' + re.escape(p) + r'\s*=\s*[^,]+', r'\1', init).strip(' ,')
                        ninit = ninit or f'{iv} = 0'
                    elif pre_assign is not None:
                        pass  # keep the assignment (dead if unused; the compiler drops it)
                newfor = f'for ({ninit}; {cond.strip()}; {ninc})'
                nb2 = b[:m.start()] + newfor + b[e:bs_] + nb_ + b[be_:]
                if form == 'base' and pre_assign is not None:
                    nb2 = nb2[:pre_assign.start()] + nb2[pre_assign.end():]
                out.append((f'{p} -> {src}[{iv}]', nb2))
    return out


def split_top_semis(s):
    out, d, cur = [], 0, ''
    for ch in s:
        if ch in '([{':
            d += 1
        elif ch in ')]}':
            d -= 1
        if ch == ';' and d == 0:
            out.append(cur)
            cur = ''
        else:
            cur += ch
    out.append(cur)
    return out


# ---- inline-to-named-locals (a4d82de, 963b6e1)

def tu_inline_spans(fx):
    """name -> (body_start, body_end) of inline functions (static inline, class-body
    or `inline` methods) defined anywhere in the TU text."""
    t = strip_comments(fx.text)
    out = {}
    for m in re.finditer(r'\binline\b[^;{}()]*?\b(' + ID + r')\s*\(', t):
        name = m.group(1)
        k = m.end() - 1
        e = match_paren(t, k)
        if e < 0:
            continue
        j = e
        while j < len(t) and (t[j] in ' \t\n' or t[j:j + 5] == 'const'):
            j += 5 if t[j:j + 5] == 'const' else 1
        if t[j:j + 1] != '{':
            continue
        be = match_paren(t, j, '{', '}')
        out.setdefault(name, (j + 1, be - 1))
    return out


def tu_inlines(fx):
    """name -> (params, ret, body) of static inline functions defined before fn."""
    ls = fx.d[0]
    t = strip_comments(fx.text[:ls])
    out = {}
    for m in re.finditer(r'(?:static\s+)?inline\s+(?:static\s+)?([\w\s\*&:]+?)\b(' + ID + r')\s*\(', t):
        name = m.group(2)
        k = m.end() - 1
        e = match_paren(t, k)
        if e < 0:
            continue
        j = e
        while j < len(t) and t[j] in ' \t\n':
            j += 1
        if t[j:j + 1] != '{':
            continue
        be = match_paren(t, j, '{', '}')
        ps_ = split_args(t[k + 1:e - 1])
        if ps_ == ['void']:
            ps_ = []
        out[name] = (ps_, m.group(1).strip(), fx.text[j + 1:be - 1])
    return out


DECL_LINE = re.compile(r'^\s*((?:const\s+|unsigned\s+|signed\s+|struct\s+|volatile\s+)*' + ID
                       + r'(?:\s*[\*&]+\s*|\s+))(' + ID + r')\s*(?:=\s*(.+?))?\s*;\s*$')


def split_stmts(body):
    """top-level statements of a block (text), keeping nested blocks intact."""
    out, d, cur, i = [], 0, '', 0
    s = body
    while i < len(s):
        ch = s[i]
        cur += ch
        if ch in '({[':
            d += 1
        elif ch in ')}]':
            d -= 1
            if ch == '}' and d == 0:
                # end of a block statement unless followed by else / ;
                rest = s[i + 1:].lstrip()
                if not rest.startswith('else') and not rest.startswith(';') and not rest.startswith('while'):
                    out.append(cur.strip())
                    cur = ''
        elif ch == ';' and d == 0:
            out.append(cur.strip())
            cur = ''
        i += 1
    if cur.strip():
        out.append(cur.strip())
    return [x for x in out if x]


def body_decls(body):
    """(decl lines [(type, name, init)], first index after the leading decls) of a block."""
    st = split_stmts(body)
    decls = []
    for s in st:
        mm = DECL_LINE.match(s)
        if mm and mm.group(1).split()[0] not in CKW and mm.group(1).strip() not in ('return',):
            decls.append((mm.group(1).strip(), mm.group(2), mm.group(3)))
        else:
            break
    return decls, st


NESTED_DECL = re.compile(r'(?m)^([ \t]+)((?:const\s+|unsigned\s+|signed\s+|struct\s+)*' + ID
                         + r'(?:\s*\*+\s*|\s+))(' + ID + r')\s*=\s*([^;{}]+);[ \t]*$')
FOR_DECL = re.compile(r'\bfor\s*\(\s*((?:unsigned\s+|signed\s+)?' + ID + r'(?:\s*\*+\s*|\s+))(' + ID + r')\s*=')


def deep_hoist(stmts):
    """clNormal3D_SetScale (db18fae2): declarations nested in the inline's blocks and loop headers
    (`JObj **cursor = table;`, `for (int i = 0;`) also become named locals.
    -> ([(type, name, None)], stmts)"""
    found, out = [], []
    for s in stmts:
        def nd(m):
            if m.group(2).split()[0] in CKW or m.group(2).strip() in ('return', 'goto', 'else'):
                return m.group(0)
            found.append((m.group(2).strip(), m.group(3), None))
            return f'{m.group(1)}{m.group(3)} = {m.group(4)};'

        def fd(m):
            if m.group(1).split()[0] in CKW:
                return m.group(0)
            found.append((m.group(1).strip(), m.group(2), None))
            return f'for ({m.group(2)} ='
        s2 = NESTED_DECL.sub(nd, s) if '\n' in s else s
        out.append(FOR_DECL.sub(fd, s2))
    names = [n for _, n, _ in found]
    if len(set(names)) != len(names):
        return [], stmts
    return found, out


def expand_inline(fx, ibody, iparams, args, used_names, subst_simple=True, deep=False):
    """-> (new decls [(type,name)], stmts text, return expr or None) or None."""
    decls, st = body_decls(ibody)
    rest = st[len(decls):]
    deep_found = []
    if deep:
        deep_found, rest = deep_hoist(rest)
        if not deep_found:
            return None
    # mixed decls later in the body (C++/C99): also hoist simple ones
    hoisted, stmts = [], []
    for s in rest:
        mm = DECL_LINE.match(s)
        if mm and mm.group(1).split()[0] not in CKW and not s.startswith('return'):
            hoisted.append((mm.group(1).strip(), mm.group(2), mm.group(3)))
            if mm.group(3):
                stmts.append(f'{mm.group(2)} = {mm.group(3)};')
        else:
            stmts.append(s)
    ret = None
    if stmts and stmts[-1].startswith('return'):
        ret = stmts[-1][6:].rstrip(';').strip() or None
        stmts = stmts[:-1]
    if any(re.search(r'\breturn\b', s) for s in stmts):
        return None
    if any(re.match(r'\s*(static|typedef)\b', s) for s in stmts):
        return None
    if '[' in ''.join(n for _, n, _ in decls + hoisted):
        return None
    newdecls = []
    ren = {}
    hoisted = hoisted + deep_found
    for t, n, init in decls + hoisted:
        nn = n
        while nn in used_names:
            nn = nn + '_'
        used_names.add(nn)
        ren[n] = nn
        newdecls.append((t, nn, init if (t, n, init) in decls else None))
    pre = []
    for (t, n, init) in newdecls:
        if init:
            pre.append(f'{n} = {init};')
    code = '\n'.join(pre + stmts)
    rexp = ret
    # rename locals
    for o, n in ren.items():
        if o != n:
            code = sub_ident(code, o, n)
            rexp = sub_ident(rexp, o, n) if rexp else rexp
    # parameters
    pdecl, passign = [], []
    for p, a in zip(iparams, args):
        pn = param_name(p)
        if not pn:
            return None
        written = re.search(r'(?<![\w.>])' + re.escape(pn) + r'\s*(=[^=]|\+\+|--|[-+*/|&^]=)', code) or \
            re.search(r'(\+\+|--)\s*' + re.escape(pn) + r'\b', code)
        if subst_simple and is_simple(a) and not written:
            code = sub_ident(code, pn, a)
            rexp = sub_ident(rexp, pn, a) if rexp else rexp
        else:
            nn = pn
            while nn in used_names:
                nn += '_'
            used_names.add(nn)
            code = sub_ident(code, pn, nn)
            rexp = sub_ident(rexp, pn, nn) if rexp else rexp
            pdecl.append((param_type(p), nn, None))
            passign.append(f'{nn} = {a};')
    code = '\n'.join(passign) + ('\n' if passign else '') + code
    return pdecl + [(t, n, None) for t, n, _ in newdecls], code, rexp


@lever('inline-to-named-locals', 'inline-boundary', 'auto', 'a4d82de, 963b6e1',
       'write a multi-statement static inline out at the call site: its locals become named locals '
       '(numbered below every frontend temp) instead of inline temps')
def gen_inline(fx):
    if not fx.regdiff():
        return []
    inl = tu_inlines(fx)
    if not inl:
        return []
    return fx.scoped(lambda body: inline_rewrites(body, inl))


def inline_rewrites(body, inl):
    sb = strip_comments(body)
    used = set(re.findall(ID, body))
    out = []
    for name, (ips, ret, ib) in inl.items():
        has_nested = bool(deep_hoist(split_stmts(ib))[0])
        if len(split_stmts(ib)) < 2 and not body_decls(ib)[0] and not has_nested:
            continue  # one-liners are shapesweep 'expand'
        if re.search(r'\b' + re.escape(name) + r'\s*\(', strip_comments(ib)):
            continue  # recursive
        for m in re.finditer(r'(?<![\w.>])' + re.escape(name) + r'\s*\(', sb):
            k = m.end() - 1
            e = match_paren(sb, k)
            args = split_args(sb[k + 1:e - 1])
            if len(args) != len(ips):
                continue
            # the enclosing statement: from the previous ; { } to the next ;
            s0 = max(sb.rfind(';', 0, m.start()), sb.rfind('{', 0, m.start()), sb.rfind('}', 0, m.start())) + 1
            s1 = sb.find(';', e)
            if s1 < 0:
                continue
            pre_call = sb[s0:m.start()].strip()
            post_call = sb[e:s1].strip()
            if post_call:
                continue
            if pre_call.startswith(('if', 'while', 'for', 'switch', 'else', 'case', 'return')) or '(' in pre_call:
                continue
            for subst, where in [(s_, w_) for s_ in (True, False) for w_ in ('front', 'back')] + \
                    ([(True, 'deep')] if has_nested else []):
                    deep = where == 'deep'
                    r = expand_inline(None, ib, ips, args, set(used), subst, deep)
                    if not r:
                        continue
                    nd, code, rexp = r
                    if pre_call:
                        if not rexp:
                            continue
                        dm = DECL_LINE.match(pre_call + ' 0;')
                        if dm and '=' in pre_call and dm.group(1).split()[0] not in CKW:
                            continue  # `T x = F(..)` (would need the decl split)
                        code += f'\n{pre_call} {rexp};'
                    elif rexp and re.search(r'\(|=', rexp):
                        code += f'\n{rexp};'
                    ind = re.match(r'[ \t]*', body[body.rfind('\n', 0, s0) + 1:]).group(0) or '    '
                    code_i = '\n'.join(ind + l.strip() for l in code.split('\n') if l.strip())
                    nb = body[:s0] + '\n' + code_i + body[s1 + 1:]
                    nb0 = nb
                    # §38 (eccac843): the hoisted locals' declaration order is the colouring
                    # order (later decl = lower vreg), so sweep it too. Floats first: FPR
                    # numbering is independent of the GPR locals.
                    orders = [('', nd)]
                    if len(nd) > 1:
                        fl = [x for x in nd if is_float_type(x[0])]
                        seen = {tuple(nd)}
                        cand = [list(reversed(nd))]
                        if len(nd) <= 4:
                            cand += [list(q) for q in itertools.permutations(nd)]
                        elif 1 < len(fl) <= 4:
                            others = [x for x in nd if not is_float_type(x[0])]
                            cand += [list(q) + others for q in itertools.permutations(fl)]
                            cand += [others + list(q) for q in itertools.permutations(fl)]
                        else:
                            cand += [nd[k:] + nd[:k] for k in range(1, len(nd))]
                        for q in cand:
                            if tuple(q) not in seen:
                                seen.add(tuple(q))
                                orders.append((' order ' + ','.join(x[1] for x in q), q))
                    if deep:
                        # the call-site block's own locals (arguments read into locals) sit between:
                        # the first k hoisted locals go to the function front, the rest right
                        # before the expanded code (C++ only), every order when there are <= 4.
                        perms = list(itertools.permutations(nd)) if len(nd) <= 4 else \
                            [tuple(nd), tuple(reversed(nd))] + [tuple(nd[k:] + nd[:k]) for k in range(1, len(nd))]
                        dl = lambda q, ind_: ''.join(  # noqa: E731
                            f'{ind_}{t_} {n_};\n' if not t_.endswith(('*', '&')) else f'{ind_}{t_}{n_};\n'
                            for t_, n_, _ in q)
                        for q in perms:
                            for k in range(len(q) + 1):
                                nbk = body[:s0] + '\n' + dl(q[k:], ind) + code_i + body[s1 + 1:]
                                nbk = '\n' + dl(q[:k], '    ') + nbk.lstrip('\n')
                                out.append((f'{name}@{m.start()} deep front {",".join(x[1] for x in q[:k])} '
                                            f'| site {",".join(x[1] for x in q[k:])}', nbk))
                        continue
                    for olabel, od in orders:
                        nb = nb0
                        decl_txt = ''.join(f'    {t} {n};\n' if not t.endswith(('*', '&')) else f'    {t}{n};\n'
                                           for t, n, _ in od)
                        if where == 'front':
                            nb = '\n' + decl_txt + nb.lstrip('\n')
                        else:
                            ds, st = body_decls(nb)
                            idx = 0
                            for x in st[:len(ds)]:
                                idx = nb.find(x, idx) + len(x)
                            nb = nb[:idx] + '\n' + decl_txt.rstrip('\n') + nb[idx:]
                        out.append((f'{name}@{m.start()} {"subst" if subst else "locals"} {where}{olabel}', nb))
    return out


# ---- mul-fuse (§39, d38113c): products through an inline helper do not fuse into fmadds; and the reverse

OPND = r'(?:' + ID + r'(?:\s*(?:\.|->)\s*' + ID + r'|\s*\[[^\[\]]*\])*|\d+\.\d*[fF]?)'
PROD_RE = re.compile(r'(?<![\w.>\]\)*/])(' + OPND + r')\s*\*\s*(' + OPND + r')(?!\s*[\w\[(*/.]|\s*->)')
TYPEWORDS = SCALARS | {'const', 'struct', 'void', 'static', 'volatile', 'register', 'Vec', 'Mtx', 'class'}


def mul_sites(b):
    """products `A * B` of simple operands inside a statement that also adds/subtracts."""
    sb = strip_comments(b)
    if len(sb) != len(b):
        return []
    out = []
    for m in PROD_RE.finditer(sb):
        if m.group(1).split('.')[0].split('-')[0].strip() in TYPEWORDS | CKW:
            continue
        s0 = max(sb.rfind(';', 0, m.start()), sb.rfind('{', 0, m.start()), sb.rfind('}', 0, m.start())) + 1
        s1 = sb.find(';', m.end())
        stmt = sb[s0:s1 if s1 >= 0 else len(sb)]
        if not re.search(r'[^+\-eE(,=*/<>!&|?:]\s*[+\-]', stmt):
            continue
        if re.match(r'\s*(?:' + ID + r'\s+)+\**\s*$', sb[s0:m.start()] + m.group(1) + ' ') and '=' not in sb[s0:m.start()]:
            continue  # `T *x;` declaration
        out.append((m.start(), m.end(), m.group(1), m.group(2), s0))
    return out


@lever('mul-fuse', 'inline-mul-blocks-fmadd', 'auto', 'd38113c (§39)',
       'fmadds/fmsubs on one side, fmuls + fadds on the other: route products through an inline mul(a, b) '
       '(blocks fusing, changes FPR numbering), or the reverse: paste inline mul helpers / single-use product '
       'locals back so they fuse')
def gen_mul(fx):
    if not fx.win('fmadd', 'fmsub', 'fnmadd', 'fnmsub', 'fmul'):
        return []
    single = any(x in ('fmuls', 'fmadds', 'fmsubs', 'fnmsubs', 'fnmadds', 'fadds', 'fsubs')
                 for x in (fx.diag or {}).get('window', []))
    ft = 'float' if single or not fx.win('fmul', 'fmadd', 'fmsub') else 'double'
    hname = 'mul__lv'
    helper = f'static inline {ft} {hname}({ft} a, {ft} b) {{ return a * b; }}\n'

    def unfuse(b):
        sites = mul_sites(b)
        if not sites:
            return []
        def apply(sel):
            nb, last = '', 0
            for (a, e, x, y, _) in sites:
                if (a, e) in sel:
                    nb += b[last:a] + f'{hname}({x}, {y})'
                    last = e
            return nb + b[last:]
        res = [('mul inline: all products', apply({(a, e) for a, e, *_ in sites}))]
        by_stmt = {}
        for a, e, x, y, s0 in sites:
            by_stmt.setdefault(s0, []).append((a, e))
        if len(by_stmt) > 1:
            for s0, l in list(by_stmt.items())[:10]:
                res.append((f'mul inline: stmt@{s0}', apply(set(l))))
        if len(sites) > 1:
            for a, e, x, y, _ in sites[:12]:
                res.append((f'mul inline: {x}*{y}@{a}', apply({(a, e)})))
        for s0, l in list(by_stmt.items())[:6]:
            if len(l) > 1:  # everything but one product of the statement
                for skip in l[:4]:
                    res.append((f'mul inline: stmt@{s0} except @{skip[0]}', apply(set(l) - {skip})))
        return res

    out = [(lab, helper + t) for lab, t in fx.scoped(unfuse)]

    # reverse 1: TU inline helpers that are a bare product -> written out
    mulinl = []
    for name, (ips, ret, ib) in (tu_inlines(fx) or {}).items():
        mm = re.match(r'\s*return\s+(' + ID + r')\s*\*\s*(' + ID + r')\s*;\s*$', strip_comments(ib).strip())
        if mm and len(ips) in (1, 2) and {mm.group(1), mm.group(2)} <= {param_name(q) for q in ips}:
            mulinl.append((name, [param_name(q) for q in ips], mm.group(1), mm.group(2)))

    def fuse_inl(b):
        res = []
        for name, pn, x, y in mulinl:
            def f(args, pn=pn, x=x, y=y):
                if len(args) != len(pn) or not all(is_simple(a) for a in args):
                    return None
                mp = dict(zip(pn, args))
                return f'({mp[x]} * {mp[y]})'
            nb = rewrite_calls(b, name, f)
            if nb and nb != b:
                res.append((f'fuse: write {name}() out', nb))
        return res

    # reverse 2: `t = A * B;` with t read once afterwards -> substitute the product
    def fuse_local(b):
        sb = strip_comments(b)
        if len(sb) != len(b):
            return []
        res, allsub = [], b
        for m in re.finditer(r'(?m)^([ \t]*)(?:(?:float|double|f32|f64)\s+)?(' + ID + r')\s*=\s*(' + OPND
                             + r'\s*\*\s*' + OPND + r')\s*;[ \t]*\n', sb):
            v, prod = m.group(2), m.group(3)
            uses = [u for u in re.finditer(r'(?<![\w.>])' + re.escape(v) + r'\b(?!\s*(?:=[^=]|\())', sb)
                    if not m.start() <= u.start() < m.end()]
            if len(uses) != 1 or uses[0].start() < m.end():
                continue
            if re.search(r'(?<![\w.>])' + re.escape(v) + r'\s*(?:[-+*/]?=[^=]|\+\+|--)', sb[m.end():]):
                continue
            u = uses[0]
            keepdecl = f'{m.group(1)}{m.group(0).split(v)[0].strip()} {v};\n' if m.group(0).strip().startswith(
                ('float', 'double', 'f32', 'f64')) else ''
            nb = b[:m.start()] + keepdecl + b[m.end():u.start()] + f'({prod})' + b[u.end():]
            res.append((f'fuse: {v} -> ({prod})', nb))
        if len(res) > 1:
            # all at once, back to front so offsets hold
            nb = b
            for lab, _ in reversed(res):
                v = lab.split()[1]
                one = [x for x in fuse_local_one(nb, v)]
                if one:
                    nb = one[0]
            if nb != b:
                res.append(('fuse: all single-use product locals', nb))
        return res[:14]

    def fuse_local_one(b, v):
        m = re.search(r'(?m)^([ \t]*)(?:(float|double|f32|f64)\s+)?' + re.escape(v) + r'\s*=\s*(' + OPND
                      + r'\s*\*\s*' + OPND + r')\s*;[ \t]*\n', b)
        if not m:
            return []
        u = re.search(r'(?<![\w.>])' + re.escape(v) + r'\b(?!\s*(?:=[^=]|\())', b[m.end():])
        if not u:
            return []
        keep = f'{m.group(1)}{m.group(2)} {v};\n' if m.group(2) else ''
        k = m.end()
        return [b[:m.start()] + keep + b[k:k + u.start()] + f'({m.group(3)})' + b[k + u.end():]]

    out += fx.scoped(fuse_inl)
    out += fx.scoped(fuse_local)
    # the pragma half, both directions (the pragma of the function an inline lands in decides)
    out.append(('fp_contract off', fx.with_body(fx.body, pragmas=('fp_contract off',))))
    out.append(('fp_contract on', fx.with_body(fx.body, pragmas=('fp_contract on',))))
    return [(l, t) for l, t in out if t]


# ---- local-array-init (5eca6fc): block-local array initialiser <-> copy from a named const object

TU_CONST_RE = re.compile(r'(?m)^(?:static\s+)?const\s+((?:unsigned\s+|signed\s+|struct\s+)?' + ID + r'(?:\s*\*)?)\s+('
                         + ID + r')\s*\[\s*(\w*)\s*\]\s*=\s*(\{[^{};]*\})\s*;')
LOCAL_ARR_RE = re.compile(r'(?m)^([ \t]*)(?:static\s+)?(const\s+)?((?:unsigned\s+|signed\s+|struct\s+)?' + ID
                          + r'(?:\s*\*)?)\s+(' + ID + r')\s*\[\s*(\w*)\s*\]\s*=\s*(\{[^{};]*\})\s*;[ \t]*\n')


@lever('local-array-init', 'local-array-init', 'auto', '5eca6fc',
       'a table reached through a named const object vs an anonymous init blob: turn a TU-level const array '
       'into a block-local array initialiser at its use (function top / nested block), or the reverse '
       '(local initialiser -> static const table, direct use or struct copy)')
def gen_arrinit(fx):
    if not fx.win('lwz', 'stw', 'lis', 'addi', 'lbz', 'stb', 'lhz', 'lha', 'sth', 'lfs', 'stfs'):
        return []
    out = []
    consts = [(m.group(1).strip(), m.group(2), m.group(3), m.group(4)) for m in TU_CONST_RE.finditer(fx.text)]

    def to_local(b):
        res = []
        sb = strip_comments(b)
        for ty, name, n, init in consts:
            us = [u.start() for u in re.finditer(r'(?<![\w.>])' + re.escape(name) + r'\b', sb)]
            if not us or len(sb) != len(b):
                continue
            ln = name + '_l'
            while re.search(r'\b' + ln + r'\b', b):
                ln += '_'
            decl = f'{ty} {ln}[{n}] = {init};'
            nb = sub_ident(b, name, ln)
            for cq in ('', 'const '):
                res.append((f'{name} -> {cq}local array at top', '\n    ' + cq + decl + nb))
                # nested block from the statement of the first use to the end of the scope
                s0, d = 0, 0
                for k in range(us[0] - 1, -1, -1):  # start of the top-level statement holding the use
                    ch = sb[k]
                    if ch in ')]}':
                        d += 1
                    elif ch in '([{':
                        d = max(d - 1, 0)  # the use itself may sit inside parentheses
                    elif ch == ';' and d == 0:
                        s0 = k + 1
                        break
                    if d == 0 and ch == '}' and sb.count('{', 0, k + 1) == sb.count('}', 0, k + 1):
                        s0 = k + 1
                        break
                if sb.count('{', 0, s0) == sb.count('}', 0, s0) and s0 > 0:
                    res.append((f'{name} -> {cq}local array in a nested block',
                                b[:s0] + '\n    {\n    ' + cq + decl + sub_ident(b[s0:], name, ln).rstrip()
                                + '\n    }\n'))
                    e1 = sb.find(';', us[-1])
                    while e1 >= 0 and sb.count('{', s0, e1) != sb.count('}', s0, e1):
                        e1 = sb.find('}', e1 + 1)
                    if 0 <= e1 < len(sb.rstrip()) - 1:
                        res.append((f'{name} -> {cq}local array in a block closed after the last use',
                                    b[:s0] + '\n    {\n    ' + cq + decl + sub_ident(b[s0:e1 + 1], name, ln)
                                    + '\n    }' + b[e1 + 1:]))
        return res

    out += fx.scoped(to_local)

    # reverse: local `T a[N] = {...};` -> TU const
    for sname, s0, s1 in fx.scopes():
        b = fx.text[s0:s1]
        for m in LOCAL_ARR_RE.finditer(b):
            ind, cq, ty, name, n, init = m.groups()
            if re.search(r'[A-Za-z_]\w*\s*[\[(.]|->', re.sub(r'0[xX][0-9a-fA-F]+|\d+\.?\d*[fFuUlL]*', '', init)) \
                    and not re.fullmatch(r'[\s{},\w.+\-]*', init):
                continue  # non-constant initialiser
            rest = b[:m.start()] + '\x00' + b[m.end():]
            if re.search(r'(?<![\w.>])' + re.escape(name) + r'\s*\[[^\]]*\]\s*(?:[-+*/|&^]?=[^=]|\+\+|--)', rest):
                continue  # written
            cn = name + '__lvc'
            lab0 = name if sname == fx.fn else f'[{sname}] {name}'
            ins = func_start(fx.text, min(fx.d[1], s0) if fx.d[1] else s0)
            def build(prelude, nb):
                return fx.text[:ins] + prelude + fx.text[ins:s0] + nb + fx.text[s1:]
            for st in ('static ', ''):
                nb = sub_ident(rest, name, cn).replace('\x00', '')
                out.append((f'{lab0} -> {st}const table, direct', build(f'{st}const {ty} {cn}[{n}] = {init};\n', nb)))
            cnt = n or str(init.count(',') + 1)
            sdef = f'struct {cn}_s {{ {ty} a[{cnt}]; }};\nstatic const struct {cn}_s {cn} = {{ {init} }};\n'
            nb = sub_ident(rest, name, name + '.a').replace('\x00', f'{ind}struct {cn}_s {name} = {cn};\n')
            out.append((f'{lab0} -> struct copy from a const table', build(sdef, nb)))
            nb = sub_ident(rest, name, name + '.a').replace('\x00', f'{ind}struct {cn}_s {name};\n{ind}{name} = {cn};\n')
            out.append((f'{lab0} -> struct assignment from a const table', build(sdef, nb)))
    return [(l, t) for l, t in out if t]


# ---- single-expr (0b362350): a value built in two steps through a local -> one expression at its use

@lever('single-expr', 'single-expr-local', 'auto', '0b362350',
       'a local assigned once and read once (`end = a + b; ... f(end - 1)`) is substituted into its use, so '
       'the whole value is one expression (operand association and temp numbering change); per scope, '
       'so it also reaches the locals of TU inlines')
def gen_single(fx):
    if not (fx.regdiff() or fx.win('add', 'sub', 'addi', 'subi', 'mr')):
        return []

    def f(b):
        sb = strip_comments(b)
        if len(sb) != len(b):
            return []
        res = []
        for m in re.finditer(r'(?m)^([ \t]*)((?:(?:const|unsigned|signed)\s+)*' + ID + r'[ \t\*]+)?(' + ID
                             + r')\s*=\s*([^;{}=]+);[ \t]*\n', sb):
            ty, v, e = m.group(2), m.group(3), m.group(4).strip()
            if ty and ty.split()[0] in CKW | {'return'}:
                continue
            if re.search(ID + r'\s*\(', re.sub(r'\(\s*(?:const\s+|unsigned\s+)?' + ID + r'[\s\*]*\)', '', e)):
                continue  # calls: moving them changes evaluation order
            if '++' in e or '--' in e or '?' in e:
                continue
            allu = [u for u in re.finditer(r'(?<![\w.>])' + re.escape(v) + r'\b', sb)]
            later = [u for u in allu if u.start() >= m.end()]
            if len(later) != 1 or len([u for u in allu if u.start() < m.start()]) > (0 if ty else 1):
                continue
            u = later[0]
            if re.match(r'\s*(?:[-+*/|&^]?=[^=]|\+\+|--)', sb[u.end():]) or sb[max(0, u.start() - 2):u.start()] in ('++', '--') \
                    or sb[u.start() - 1] == '&':
                continue
            # the use must be in straight-line code after the def: no loop keyword between
            mid = sb[m.end():u.start()]
            if re.search(r'\b(for|while|do|goto|case|default)\b', mid) or mid.count('}') > mid.count('{'):
                continue
            # operands of e must not be written in between
            ops_ = set(re.findall(ID, e))
            if any(re.search(r'(?<![\w.>])' + re.escape(o) + r'\s*(?:[-+*/|&^]?=[^=]|\+\+|--)', mid) for o in ops_):
                continue
            keep = f'{m.group(1)}{ty.strip()} {v};\n' if ty else ''
            res.append((f'single expr: {v} -> ({e[:30]})', b[:m.start()] + keep + b[m.end():u.start()] + f'({e})'
                        + b[u.end():]))
        return res[:16]

    return fx.scoped(f)


# ---- try-scope-inside-if (11f056f)

TRY_RE = re.compile(r'try\s*\{\s*([^{};]*?\b(' + ID + r')\s*=\s*new\s*\([^;]*;)\s*if\s*\(\s*\2\s*\)\s*([^{};]+;)\s*\}'
                    r'\s*catch\s*\(\s*\.\.\.\s*\)\s*\{\s*throw\s*;\s*\}', re.S)


@lever('try-scope-inside-if', 'try-scope-inside-if', 'auto', '11f056f',
       'open the try after `if (q)` of a placement new, so the EH marker `stw r1` is inside the null check')
def gen_try(fx):
    if not fx.cpp or 'try' not in fx.text:
        return []

    def f(b):
        res = []
        for m in TRY_RE.finditer(b):
            rep = f'{m.group(1)}\n        if ({m.group(2)}) {{\n            try {{\n                {m.group(3).strip()}\n' \
                  f'            }} catch (...) {{\n                throw;\n            }}\n        }}'
            res.append((f'try@{m.start()}', b[:m.start()] + rep + b[m.end():]))
        return res
    out = fx.scoped(f)
    # the same lever applies to inline helpers / templates the fn expands: rewrite the whole TU once
    if not out and TRY_RE.search(fx.text):
        t = TRY_RE.sub(lambda m: f'{m.group(1)}\n        if ({m.group(2)}) {{\n            try {{\n                '
                       f'{m.group(3).strip()}\n            }} catch (...) {{\n                throw;\n            }}\n        }}',
                       fx.text)
        out.append(('try (TU-wide)', t))
    return out


# ---- nonconst-zero-arm (clFlowCourse_Dtor / tracesweep 8d77ba2)

@lever('nonconst-zero-arm', 'nonconst-zero-arm', 'auto', 'gave_up clFlowCourse_Dtor',
       '`c ? x : 0` -> a zero that is not an EINTCONST (local `zero`, +opt_propagation off): gen_COND one-branch path')
def gen_zero(fx):
    if not (fx.win('neg', 'andc', 'subfe', 'subfc', 'srawi', 'addze', 'cntlzw', 'b', 'beq', 'bne', 'li', 'or')):
        return []
    def f(body):
        b = strip_comments(body)
        sites = [m for m in re.finditer(r'\?\s*0\s*:|:\s*0\s*(?=[);,\]])', b)]
        if len(sites) > 6:
            return []
        res = []
        for m in sites:
            rep = m.group(0).replace('0', 'zero')
            res.append((f'zero@{m.start()}', '\n    int zero = 0;' + body[:m.start()] + rep + body[m.end():]))
        return res
    out = []
    for lab, t in fx.scoped(f):
        out.append((lab, t))
        d = ps.find_def(t, fx.fn, None, fx.sym)
        if d:  # same, with opt_propagation off around the function
            out.append((lab + ' +prop off', t[:d[0]] + '#pragma push\n#pragma opt_propagation off\n' + t[d[0]:d[2]]
                        + '\n#pragma pop\n' + t[d[2]:]))
    return out


# ---- dead-def split (8d77ba2 TitleCheck_NewClearedRecord_Race)

@lever('dead-def-split', 'dead-def-split', 'auto', '8d77ba2',
       '`opt_dead_assignments off` + a dead `v = 0;` def of one local: adds a split range / changes numbering')
def gen_deaddef(fx):
    if fx.diag.get('kind') not in ('reg_only', 'reg+sched'):
        return []
    decls, st = body_decls(fx.body)
    names = [(t, n) for t, n, _ in decls if '*' in t or t.split()[-1] in SCALARS]
    if not names:
        return []
    idx = 0
    for s in st[:len(decls)]:
        idx = fx.body.find(s, idx) + len(s)
    out = []
    for t, n in names[:10]:
        nb = fx.body[:idx] + f'\n    {n} = 0;' + fx.body[idx:]
        out.append((f'dead {n}', fx.with_body(nb, pragmas=('opt_dead_assignments off',))))
    return out


# ---- later-loops-block-local-counter (regalloc_patterns 46, b879fcb TitleCheck_NewClearedRecord_Race)

def loop_sites(b, n):
    """(start, end) of every `for (n = ...) stmt` in b."""
    res = []
    for m in re.finditer(r'\bfor\s*\(\s*%s\s*=' % re.escape(n), b):
        o = b.index('(', m.start())
        c = match_paren(b, o)
        if c < 0:
            continue
        j = c
        while j < len(b) and b[j].isspace():
            j += 1
        if j < len(b) and b[j] == '{':
            e = match_paren(b, j, '{', '}')
            if e < 0:
                continue
        else:
            e = b.find(';', j) + 1
            if not e:
                continue
        res.append((m.start(), e))
    return res


@lever('block-local-counter', 'later-loops-block-local-counter', 'auto', 'b879fcb',
       'a function-level counter shared by several loops -> block-local `{ int i; for (...) }` for the later loops '
       '(later ranges are SplitOffRange temps coloured before named locals)')
def gen_blockloop(fx):
    if fx.diag.get('kind') not in ('reg_only', 'reg+sched'):
        return []
    def f(body):
        b = body
        decls, st = body_decls(strip_comments(b))
        res = []
        for t, n, init in decls:
            if '*' in t or t.split()[-1] not in SCALARS:
                continue
            sites = loop_sites(b, n)
            if len(sites) < 2 or len(sites) > 8:
                continue
            def wrap(idxs):
                nb = b
                for k in sorted(idxs, reverse=True):
                    s0, s1 = sites[k]
                    nb = nb[:s0] + f'{{ {t} {n}; ' + nb[s0:s1] + ' }' + nb[s1:]
                return nb
            later = list(range(1, len(sites)))
            res.append((f'{n}: later loops block-local', wrap(later)))
            res.append((f'{n}: all loops block-local', wrap(range(len(sites)))))
            if len(sites) > 2:
                for k in range(len(sites)):
                    res.append((f'{n}: loop {k} block-local', wrap([k])))
                res.append((f'{n}: last loop block-local', wrap([len(sites) - 1])))
            # first counter declared after the other leading locals
            dm = re.search(r'^[ \t]*%s\s+%s\s*;[ \t]*\n' % (re.escape(t), re.escape(n)), b, re.M)
            if dm and len(decls) > 1 and init is None:
                last = None
                for t2, n2, _ in decls:
                    for mm in re.finditer(r'^[ \t]*%s\s+%s\b[^;\n]*;[ \t]*\n' % (re.escape(t2), re.escape(n2)), b, re.M):
                        last = mm
                        break
                if last and last.end() > dm.end():
                    moved = b[:dm.start()] + b[dm.end():last.end()] + dm.group(0) + b[last.end():]
                    sites2 = loop_sites(moved, n)
                    nb = moved
                    for k in sorted(range(1, len(sites2)), reverse=True):
                        s0, s1 = sites2[k]
                        nb = nb[:s0] + f'{{ {t} {n}; ' + nb[s0:s1] + ' }' + nb[s1:]
                    res.append((f'{n}: later loops block-local + decl last', nb))
        return res
    return fx.scoped(f)


CHAIN_RE = re.compile(r'(?<![=!<>+\-*/&|^%])((?:[A-Za-z_][\w.\->\[\]]*\s*=\s*){2,})([-\w.]+)\s*;')


@lever('chain-assign-split', 'chain-assign-split', 'auto', 'f96d5c26',
       '`a = b = c = K;` written as separate statements (both orders): a chain stores right to left and keeps one '
       'value temp, separate statements store in source order (KartMovement_Init)')
def gen_chain(fx):
    def f(body):
        sites = []
        for m in CHAIN_RE.finditer(body):
            lhs = [x.strip() for x in m.group(1).split('=') if x.strip()]
            if m.start() and body[m.start() - 1] not in ' \t\n;{}':
                continue
            if any(not re.fullmatch(r'[A-Za-z_][\w.\->\[\]]*', x) for x in lhs):
                continue
            sites.append((m.start(), m.end(), lhs, m.group(2)))
        if not sites or len(sites) > 12:
            return []
        def build(idxs, rev):
            nb = body
            for k in sorted(idxs, reverse=True):
                s0, s1, lhs, v = sites[k]
                order = lhs[::-1] if rev else lhs
                nb = nb[:s0] + ' '.join(f'{x} = {v};' for x in order) + nb[s1:]
            return nb
        res = [('all chains split, source order', build(range(len(sites)), False)),
               ('all chains split, reverse order', build(range(len(sites)), True))]
        if len(sites) > 1:
            for k in range(len(sites)):
                res.append((f'chain {k} split, source order', build([k], False)))
                res.append((f'chain {k} split, reverse order', build([k], True)))
        return res
    return fx.scoped(f)


@lever('void-to-int', 'nonvoid-no-return', 'auto', 'b61e1de',
       'a `void` function declared `int` with no return statement: r3 stays live to the exit, so late temps '
       'avoid r3 (regalloc_patterns 66). Prototypes in the TU are rewritten too; a header prototype makes the '
       'variant fail to compile (then change the header by hand)')
def gen_voidint(fx):
    if not fx.head:
        return []
    ms = list(re.finditer(r'\bvoid(\s+)((?:\w+::)*~?\w+)(\s*\()', fx.head))
    if not ms:
        return []
    m = ms[-1]
    if re.search(r'\breturn\s+[^;]', strip_comments(fx.body)):
        return []
    short = m.group(2).split('::')[-1]
    out = []
    for ty in ('int', 'unsigned char'):
        head = fx.head[:m.start()] + ty + fx.head[m.start() + 4:]
        t = fx.with_body(fx.body, head=head)
        if not t:
            continue
        t = re.sub(r'\bvoid(\s+(?:\w+::)*' + re.escape(short) + r'\s*\()', ty + r'\1', t)
        out.append((f'void -> {ty}, no return statement', t))
    return out


CASTASSIGN_RE = re.compile(r'(?<![=!<>+\-*/&|^%])=\s*\((int|unsigned int|s32|u32|long|unsigned long|unsigned|short|s16|u16|unsigned short)\)\s*'
                           r'(?=[A-Za-z_(])')
NARROW_T = r'(?:u8|s8|char|unsigned char|signed char|bool|BOOL8|u16|s16|short|unsigned short)'


@lever('narrow-cast-toggle', 'dead-truncation-reschedules-block', 'auto', 'dd11664',
       '`narrow = (int)x;` <-> `narrow = x;`: a two-step conversion emits a truncation that dies later, the block '
       'is scheduled again after register allocation and two independent instructions swap (regalloc_patterns 69)')
def gen_narrowcast(fx):
    tu = strip_comments(fx.text) if hasattr(fx, 'text') else ''
    def f(body):
        res = []
        sites = [m for m in CASTASSIGN_RE.finditer(body)]
        if len(sites) <= 16:
            for k, m in enumerate(sites):
                res.append((f'drop ({m.group(1)}) cast of assignment {k}', body[:m.start()] + '= ' + body[m.end():]))
            if len(sites) > 1:
                nb = body
                for m in reversed(sites):
                    nb = nb[:m.start()] + '= ' + nb[m.end():]
                res.append(('drop every int cast on assignments', nb))
        names = set(re.findall(r'\b' + NARROW_T + r'\s+(\w+)\s*(?:=|;|,)', body))
        names |= set(re.findall(r'\bextern\s+(?:volatile\s+)?' + NARROW_T + r'\s+(\w+)\s*;', tu))
        adds = []
        for m in re.finditer(r'(?<![\w.>])(\w+)\s*=\s*(?![=(])(?=[A-Za-z_])', body):
            if m.group(1) in names:
                stmt = body[m.end():body.find(';', m.end())]
                if re.fullmatch(r'[\w.\->\[\]]+', stmt.strip()) and not re.fullmatch(r'\d\w*', stmt.strip()):
                    adds.append(m)
        if len(adds) <= 12:
            for k, m in enumerate(adds):
                res.append((f'add (int) cast to narrow assignment {k} ({m.group(1)})', body[:m.end()] + '(int)' + body[m.end():]))
        return res
    return fx.scoped(f)


_S3T = r'(?:(?:\d\w*|[A-Za-z_][\w.]*(?:->[\w.]+)*(?:\[[^\[\]+]*\])*)(?:\s*(?:\*|<<)\s*(?:\d\w*|[A-Za-z_][\w.]*))?|\([^()+]*\)\s*\*\s*\d\w*)'
_S3PRE = r'(?:(?<=[=(,\[{;?:<>!&|])|(?<=return))\s*'
_S3POST = r'\s*(?=[;),\]?:<>=!&|])'
SUM3_RES = [
    re.compile(_S3PRE + r'(?P<a>%s)\s*\+\s*(?P<b>%s)\s*\+\s*(?P<c>%s)' % (_S3T, _S3T, _S3T) + _S3POST),
    re.compile(_S3PRE + r'(?P<a>%s)\s*\+\s*\(\s*(?P<b>%s)\s*\+\s*(?P<c>%s)\s*\)' % (_S3T, _S3T, _S3T) + _S3POST),
    re.compile(_S3PRE + r'\(\s*(?P<a>%s)\s*\+\s*(?P<b>%s)\s*\)\s*\+\s*(?P<c>%s)' % (_S3T, _S3T, _S3T) + _S3POST),
]


@lever('sum3-regroup', 'three-term-sum-grouping', 'auto', '3bf2c6a',
       'a three-term sum `a + b + c` (index or offset) in all 12 orders/groupings: the frontend rotates the add '
       'tree, so the emitted grouping is not the written one (regalloc_patterns 84, CalcEarnedCoins)')
def gen_sum3(fx):
    def f(body):
        sites, seen = [], set()
        for rx in SUM3_RES:
            for m in rx.finditer(body):
                a0 = m.start('a') if rx is not SUM3_RES[2] else body.rfind('(', 0, m.start('a') + 1)
                a0 = min(a0, m.start('a')) if rx is SUM3_RES[2] else a0
                e = m.end()
                while e > 0 and body[e - 1].isspace():
                    e -= 1
                if any(a0 < s1 and s0 < e for s0, s1 in seen):
                    continue
                terms = [m.group('a').strip(), m.group('b').strip(), m.group('c').strip()]
                if len(set(terms)) < 3 or all(re.fullmatch(r'\d\w*', t) for t in terms[1:]):
                    continue
                seen.add((a0, e))
                sites.append((a0, e, terms))
        if not sites or len(sites) > 6:
            return []
        res = []
        for k, (s0, s1, t) in enumerate(sites):
            cur = re.sub(r'\s+', '', body[s0:s1])
            for o in range(3):
                x = t[o]
                y, z = [t[i] for i in range(3) if i != o]
                for p, q in ((y, z), (z, y)):
                    for form in (f'({p} + {q}) + {x}', f'{x} + ({p} + {q})'):
                        if re.sub(r'\s+', '', form) == cur:
                            continue
                        res.append((f'sum {k} as `{form}`', body[:s0] + form + body[s1:]))
        return res
    return fx.scoped(f)


# --------------------------------------------------------------------------
# runner

def merge_variants(base, a, b):
    """3-way merge of two whole-TU variants of `base` (line based). None when their edits overlap."""
    import difflib
    bl, al, bbl = base.split('\n'), a.split('\n'), b.split('\n')
    ea = [o for o in difflib.SequenceMatcher(None, bl, al, autojunk=False).get_opcodes() if o[0] != 'equal']
    eb = [o for o in difflib.SequenceMatcher(None, bl, bbl, autojunk=False).get_opcodes() if o[0] != 'equal']
    for _, i1, i2, _, _ in ea:
        for _, k1, k2, _, _ in eb:
            if i1 < k2 + 1 and k1 < i2 + 1:  # overlapping or touching base ranges
                return None
    edits = [(i1, i2, al[j1:j2]) for _, i1, i2, j1, j2 in ea] + [(i1, i2, bbl[j1:j2]) for _, i1, i2, j1, j2 in eb]
    out = bl[:]
    for i1, i2, new in sorted(edits, reverse=True):
        out[i1:i2] = new
    return '\n'.join(out)


def run_fn(unit, fn, levers=None, jobs=4, demangled=None, show=False, log=None, pairs=0):
    fx = Fx(unit, fn, demangled)
    fx.diagnose()
    base = fx.u.compile_score(fx.text, fn, fx.cc, 'b')
    res = dict(obj=unit, fn=fn, kind=fx.diag.get('kind'), window=fx.diag.get('window'), base=base,
               fired={}, best=None)
    cands = []
    for name, lv in LEVERS.items():
        if levers and name not in levers:
            continue
        try:
            vs = [(l, t) for l, t in lv['gen'](fx) if t]
        except Exception as e:  # a lever bug must not stop a batch
            res['fired'][name] = f'error {type(e).__name__}: {e}'
            continue
        if vs:
            res['fired'][name] = len(vs)
            cands += [(name, l, t) for l, t in vs]
    if not cands:
        return res
    seen, uniq = set(), []
    for c in cands:
        h = hash(c[2])
        if h not in seen:
            seen.add(h)
            uniq.append(c)

    def score(i_c):
        i, (name, lab, t) = i_c
        return name, lab, t, fx.u.compile_score(t, fn, fx.cc, f'v{i % jobs}_{os.getpid()}_{i}')
    with ThreadPoolExecutor(jobs) as ex:
        scored = list(ex.map(score, enumerate(uniq)))
    scored.sort(key=lambda x: x[3])
    if pairs:
        # regalloc_patterns 62: levers that fail alone can match together. Combine variants of
        # DIFFERENT levers that each changed the diff (score != base), best `pairs` per lever.
        top = {}
        for name, lab, t, sc in scored:
            if sc != base and sc < FAIL and len(top.setdefault(name, [])) < pairs:
                top[name].append((lab, t))
        names = sorted(top)
        combos = []
        for x in range(len(names)):
            for y in range(x + 1, len(names)):
                for la, ta in top[names[x]]:
                    for lb, tb in top[names[y]]:
                        m = merge_variants(fx.text, ta, tb)
                        if m and hash(m) not in seen:
                            seen.add(hash(m))
                            combos.append((names[x] + '+' + names[y], la + ' & ' + lb, m))
        res['pairs'] = len(combos)
        if combos:
            def score2(i_c):
                i, (name, lab, t) = i_c
                return name, lab, t, fx.u.compile_score(t, fn, fx.cc, f'p{i % jobs}_{os.getpid()}_{i}')
            with ThreadPoolExecutor(jobs) as ex:
                scored += list(ex.map(score2, enumerate(combos)))
            scored.sort(key=lambda x: x[3])
    per = {}
    for name, lab, t, s in scored:
        if name not in per or s < per[name][1]:
            per[name] = (lab, s)
    res['per_lever'] = {k: {'label': v[0], 'score': v[1]} for k, v in per.items()}
    res['variants'] = len(uniq)
    res['compile_fail'] = sum(1 for x in scored if x[3] >= FAIL)
    if show:
        for name, lab, t, s in scored[:15]:
            print(f'  {s:>7}  {name:24} {lab}')
    name, lab, t, s = scored[0]
    if s < base:
        res['best'] = {'lever': name, 'label': lab, 'score': s}
        ps.OBJDIFF = True
        try:
            pct = fx.u.compile_score(t, fn, fx.cc, 'od')
            bpct = fx.u.compile_score(fx.text, fn, fx.cc, 'odb')
        finally:
            ps.OBJDIFF = False
        res['best']['pct'] = round(100 - pct / 100, 2) if pct < FAIL else None
        res['base_pct'] = round(100 - bpct / 100, 2) if bpct < FAIL else None
        if log:
            os.makedirs(os.path.join(log, 'hits'), exist_ok=True)
            open(os.path.join(log, 'hits', f'{fn}{fx.u.ext}'), 'w').write(t)
    return res


def candidates(mn, mx):
    rep = json.load(open('build/GNLJ82/report.json'))
    nm = set(re.findall(r'Object\(NonMatching,\s*"([^"]+)\.(?:c|cpp|cp)"', open('configure.py').read()))
    out = []
    for u in rep['units']:
        obj = re.sub(r'^main/', '', u['name'])
        if obj not in nm:
            continue
        for f in u.get('functions', []):
            p = f.get('fuzzy_match_percent', 0)
            if mn <= p < mx:
                out.append((p, obj, f['name'], f.get('metadata', {}).get('demangled_name')))
    # gave_up rows below --min are swept too
    gu = open('docs/gave_up.md').read()
    have = {x[2] for x in out}
    for u in rep['units']:
        obj = re.sub(r'^main/', '', u['name'])
        if obj not in nm:
            continue
        for f in u.get('functions', []):
            p = f.get('fuzzy_match_percent', 0)
            if p < mn and f['name'] not in have and f'`{f["name"]}`' in gu:
                out.append((p, obj, f['name'], f.get('metadata', {}).get('demangled_name')))
    out.sort(key=lambda x: -x[0])
    return out


def cmd_batch(a):
    os.makedirs(a.out, exist_ok=True)
    rp = os.path.join(a.out, 'results.jsonl')
    done = set()
    if os.path.exists(rp) and not a.retry:
        for l in open(rp):
            try:
                r = json.loads(l)
                done.add((r['obj'], r['fn']))
            except ValueError:
                pass
    lv = set(a.levers.split(',')) if a.levers else None
    cs = candidates(a.min, a.max)
    if a.only:
        keep = set(a.only.split(','))
        cs = [c for c in cs if c[2] in keep]
    print(f'{len(cs)} functions', flush=True)
    t0 = time.time()
    for p, obj, fn, dm in cs:
        if (obj, fn) in done:
            continue
        if a.hours and time.time() - t0 > a.hours * 3600:
            break
        t1 = time.time()
        try:
            r = run_fn(obj, fn, lv, a.jobs, dm, log=a.out, pairs=a.pairs)
        except SystemExit as e:
            r = dict(obj=obj, fn=fn, error=str(e))
        except Exception as e:
            r = dict(obj=obj, fn=fn, error=f'{type(e).__name__}: {e}')
        r['pct'] = p
        r['secs'] = round(time.time() - t1, 1)
        with open(rp, 'a') as f:
            f.write(json.dumps(r) + '\n')
        b = r.get('best')
        print(f'{p:6.2f} {fn:40} {r.get("kind", "-"):10} fired={r.get("fired", {})} '
              f'base={r.get("base")} best={b and (b["lever"], b["label"], b["score"], b.get("pct"))} '
              f'{r.get("error", "")} {r["secs"]}s', flush=True)
    summary(a.out)


def summary(out):
    rows = [json.loads(l) for l in open(os.path.join(out, 'results.jsonl'))]
    last = {}
    for r in rows:
        # a later --levers X --retry run only replaces lever X's numbers
        k = (r['obj'], r['fn'])
        o = last.get(k)
        if o:
            r = dict(r)
            r['fired'] = {**o.get('fired', {}), **r.get('fired', {})}
            r['per_lever'] = {**(o.get('per_lever') or {}), **(r.get('per_lever') or {})}
            ob, nb = o.get('best'), r.get('best')
            if ob and (not nb or (ob.get('pct') or 0) > (nb.get('pct') or 0)):
                r['best'], r['base_pct'] = ob, o.get('base_pct')
        last[k] = r
    rows = list(last.values())
    st = {n: dict(fired=0, variants=0, improved=0, matched=0) for n in LEVERS}
    for r in rows:
        for n, v in r.get('fired', {}).items():
            if isinstance(v, int) and n in st:
                st[n]['fired'] += 1
                st[n]['variants'] += v
        for n, pl in (r.get('per_lever') or {}).items():
            if n in st and pl['score'] < r['base']:
                st[n]['improved'] += 1
                bb = r.get('best') or {}
                # diff lines can reach 0 below 100% (fn_80243464): trust objdiff
                if bb.get('lever') == n and bb.get('pct') == 100.0:
                    st[n]['matched'] += 1
    md = ['# leversweep results', '',
          f'{len(rows)} near misses swept by `tools/leversweep.py batch` (diagnosis-triggered levers).',
          '"fired" = both triggers matched, "improved" = fewer diff lines than the current source, '
          '"matched" = objdiff 100% (0 diff lines alone is not enough).', '',
          '| lever | rule | landed by | fired (fns) | variants | improved | matched |',
          '| --- | --- | --- | --- | --- | --- | --- |']
    for n, lv in LEVERS.items():
        s = st[n]
        md.append(f'| {n} | {lv["rule"]} | {lv["commit"]} | {s["fired"]} | {s["variants"]} | {s["improved"]} | {s["matched"]} |')
    md += ['', '## Improvements', '', '| fn | TU | % | base lines | best lines | objdiff % | lever | variant |',
           '| --- | --- | --- | --- | --- | --- | --- | --- |']
    for r in sorted(rows, key=lambda r: (r.get('best') or {}).get('score', 1e9)):
        b = r.get('best')
        if not b:
            continue
        md.append(f'| `{r["fn"]}` | {r["obj"]} | {r.get("pct", 0):.2f} | {r["base"]} | {b["score"]} | '
                  f'{r.get("base_pct")} -> {b.get("pct")} | {b["lever"]} | {b["label"]} |')
    md += ['', '## Levers not automated here', '', '| lever | rule | class | landed by | why |',
           '| --- | --- | --- | --- | --- |']
    for n, rule, cls, c, why in NOT_AUTOMATED:
        md.append(f'| {n} | {rule} | {cls} | {c} | {why} |')
    open(os.path.join(out, 'summary.md'), 'w').write('\n'.join(md) + '\n')
    print('wrote', os.path.join(out, 'summary.md'))


SELFTEST = [
    # (unit, fn, git rev BEFORE the landing, lever expected to match)
    ('game/PCBCheckRecv', 'PCBComm_ComputeSyncState', '025713e~1', 'index-for-walk'),
    ('game/fn_801BAA88', 'fn_801C1964', '11f056f~1', 'try-scope-inside-if'),
    ('game/AI_CalcVSTargetSpeed', 'AI_CalcVSTargetSpeed', '963b6e1~1', 'inline-to-named-locals'),
    ('game/JumpDistanceMode_Update', 'JumpDistanceMode_Update',
     [('JD_mul(d.x, d.x) + JD_mul(d.z, d.z)', 'd.x * d.x + d.z * d.z')], 'mul-fuse'),
    ('game/clFlowKart_Init', 'clFlowKart_UpdateDisplay',
     [('    int arr[5] = {0x16B4, 0x16B3, 0x16B2, 0x16B1, 0x16B0};\n', ''),
      ('static inline void HideParams(', 'static const int arr[5] = {0x16B4, 0x16B3, 0x16B2, 0x16B1, 0x16B0};\n'
       'static inline void HideParams(')], 'local-array-init'),
]


# ---- detect-only: anchor-addi-object-boundary (regalloc_patterns 40)

ADDI_RE = re.compile(r'^(addi|subi) (r\d+), (r\d+), (0x[0-9a-fA-F]+)$')


def anchor_addis(body):
    """{base reg: {offset}} of `addi rX, rB, N` (rX != rB, rB not r1/r2/r13, |N| >= 8)."""
    out = {}
    for l in body or []:
        m = ADDI_RE.match(l)
        if not m or m.group(2) == m.group(3) or m.group(3) in ('r1', 'r2', 'r13', 'r0'):
            continue
        n = int(m.group(4), 16) * (-1 if m.group(1) == 'subi' else 1)
        if abs(n) >= 8:
            out.setdefault(m.group(3), set()).add(n)
    return out


def cmd_detect(a):
    """List near misses whose target takes `addi rX, anchor, N` object addresses that ours never forms."""
    rows = []
    for pct, unit, fn, dem in candidates(a.min, a.max):
        try:
            u = ps.Unit(unit)
        except Exception:
            continue
        T = ps.target_body(fn)
        d = f'{ps.TMP}/det_{os.getpid()}'
        os.makedirs(d, exist_ok=True)
        subprocess.run([ps.DTK, 'elf', 'disasm', f'build/GNLJ82/src/{unit}.o', d + '/m.s'], capture_output=True)
        B = ps.norm_body(d + '/m.s', fn) or ps.norm_body(d + '/m.s', u.compiled_name(fn))
        if not T or not B:
            continue
        ta, ba = anchor_addis(T), anchor_addis(B)
        # the anchor = the base register with the most distinct offsets in the target (>= 2)
        if not ta:
            continue
        reg, offs = max(ta.items(), key=lambda kv: len(kv[1]))
        if len(offs) < 2:
            continue
        ours = set().union(*ba.values()) if ba else set()
        missing = sorted(offs - ours)
        extra = sorted(ours - set().union(*ta.values()))
        if missing:
            rows.append((pct, unit, fn, reg, missing, extra))
    md = ['# anchor-addi-object-boundary candidates (detect only)', '',
          'Near misses where the target forms `addi rX, <anchor>, N` for an N that our build never forms. '
          'By regalloc_patterns 40 each such N is the first byte of a real object in the pool: split the pool '
          'object there and index it directly. "ours only" = offsets we form and the target does not '
          '(a base + constant written by hand). Heuristic: the anchor is the base register with the most '
          'distinct offsets; a saved pointer to a big struct looks the same, so check the function.', '',
          '| fn | TU | % | anchor reg | target-only offsets | ours-only offsets |', '| --- | --- | --- | --- | --- | --- |']
    for pct, unit, fn, reg, mi, ex in sorted(rows, key=lambda r: -r[0]):
        md.append(f'| `{fn}` | {unit} | {pct:.2f} | {reg} | {", ".join(hex(x) for x in mi[:12])} | '
                  f'{", ".join(hex(x) for x in ex[:12])} |')
    os.makedirs(a.out, exist_ok=True)
    open(os.path.join(a.out, 'anchor_detect.md'), 'w').write('\n'.join(md) + '\n')
    print('\n'.join(md[4:]))


def cmd_selftest(a):
    ok = True
    for unit, fn, rev, lv in SELFTEST:
        src = next(f'src/{unit}{e}' for e in ('.c', '.cpp') if os.path.exists(f'src/{unit}{e}'))
        cur = open(src).read()
        if isinstance(rev, list):  # pre-image = the current source with the fix undone
            pre = cur
            for x, y in rev:
                assert x in pre, (fn, x)
                pre = pre.replace(x, y, 1)
        else:
            old = subprocess.run(['git', 'show', f'{rev}:{src}'], capture_output=True, text=True)
            if old.returncode:
                print('skip', fn, '(rev not in this clone: git fetch --deepen)')
                continue
            pre = old.stdout
        try:
            open(src, 'w').write(pre)
            fx = Fx(unit, fn)
            fx.diag = {'kind': 'reg+sched', 'window': ['stw', 'lwz', 'lfs', 'addi', 'mr', 'neg', 'b', 'fmuls', 'fmadds']}
            vs = LEVERS[lv]['gen'](fx)
            base = fx.u.compile_score(fx.text, fn, fx.cc, 'st')
            best = min((fx.u.compile_score(t, fn, fx.cc, f'st{i}'), l) for i, (l, t) in enumerate(vs)) if vs else None
        finally:
            open(src, 'w').write(cur)
        good = best is not None and best[0] < base
        ok &= good
        print(f'{"OK " if good else "BAD"} {fn}: {lv} base {base} -> {best}')
    sys.exit(0 if ok else 1)


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sp = p.add_subparsers(dest='cmd', required=True)
    sp.add_parser('list')
    f = sp.add_parser('fn')
    f.add_argument('unit')
    f.add_argument('fn')
    f.add_argument('--levers')
    f.add_argument('--demangled')
    f.add_argument('-j', '--jobs', type=int, default=4)
    f.add_argument('--show', action='store_true')
    f.add_argument('--pairs', type=int, default=0, help='also try pairs of variants from different levers (best N per lever that changed the diff)')
    f.add_argument('--out', default=None)
    b = sp.add_parser('batch')
    b.add_argument('--min', type=float, default=90)
    b.add_argument('--max', type=float, default=100)
    b.add_argument('--levers')
    b.add_argument('--only')
    b.add_argument('--retry', action='store_true')
    b.add_argument('--pairs', type=int, default=0)
    b.add_argument('--hours', type=float, default=0)
    b.add_argument('-j', '--jobs', type=int, default=4)
    b.add_argument('--out', default='docs/sweeps/leversweep')
    sp.add_parser('selftest')
    dt = sp.add_parser('detect', help='detect-only triggers (anchor-addi-object-boundary)')
    dt.add_argument('--min', type=float, default=80)
    dt.add_argument('--max', type=float, default=100)
    dt.add_argument('--out', default='docs/sweeps/leversweep')
    s = sp.add_parser('summary')
    s.add_argument('--out', default='docs/sweeps/leversweep')
    a = p.parse_args()
    if a.cmd == 'list':
        for n, lv in LEVERS.items():
            print(f'{n:24} auto  rule={lv["rule"]:22} {lv["commit"]:18} {lv["desc"]}')
        for n, rule, cls, c, why in NOT_AUTOMATED:
            print(f'{n:24} {cls:5} rule={rule:22} {c:18} {why}')
    elif a.cmd == 'fn':
        r = run_fn(a.unit, a.fn, set(a.levers.split(',')) if a.levers else None, a.jobs, a.demangled, a.show, a.out, pairs=a.pairs)
        print(json.dumps(r, indent=1))
    elif a.cmd == 'batch':
        cmd_batch(a)
    elif a.cmd == 'selftest':
        cmd_selftest(a)
    elif a.cmd == 'detect':
        cmd_detect(a)
    elif a.cmd == 'summary':
        summary(a.out)


if __name__ == '__main__':
    main()
