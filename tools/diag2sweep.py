#!/usr/bin/env python3
"""diag2sweep.py: turn a `regfix diag` conclusion into a tracesweep run.

regfix diag says which allocator inputs must change ("hold temp X in a NAMED
local", "create X after Y", ...); tracesweep searches source shapes, scored by
the compiler's own trace. This module writes the tracesweep template and the
--want predicate for a diag result, so the source search starts from the
mechanism instead of a hand-written template.

  python3 tools/regfix.py diag UNIT FN [--start-tu F] --tracesweep [--run]

Generated (tools/regfix.py calls generate()):
  * --want: one conjunction per diag solution, OR-ed. Per edit kind:
      name X        T.named(PAT_X, k)            X's def writes a named local
      renumber X>Y  T.num(PAT_X, k) > T.num(PAT_Y, k')   (X created after Y)
      swapnum X,Y   the numbers of X and Y swapped
    PAT_X is X's defining pre-RA PCode line with every vreg generalised
    (`^LWZ r\\d+!,r\\d+,44$`), k its index among the lines matching PAT_X.
    Kinds with no source-visible mechanism (forbid, phantom, merge, edges) add
    no term; the diff ranks those variants.
  * the template: the function's definition with choice points on the source
    lines diag named:
      hoist  every member/index chain prefix on those lines (self->groups[0],
             p->a.b, t[i]) can be held in a named local (`__typeof__(E) hN;`):
             none / every occurrence / all but the first / the first only
             (regalloc_patterns 35, rule low-numbered-neighbours-sweep1);
      inline a call of a static inline whose pointer parameter is only read
             through `p->f` can pass those fields as named locals of the caller
             (`F__nl(..., nl_row, nl_column)`; a4d82de, rule
             inline-wrapper-named-locals): the inline's locals are frontend
             temps, the caller's named locals are numbered below every temp.
Files: /tmp/regfix/FN.diag.tmpl (+ the run's log in /tmp/tracesweep).
"""
from __future__ import annotations

import re

CHAIN = re.compile(r'(?<![\w.>&])([A-Za-z_]\w*)((?:\s*(?:->|\.)\s*[A-Za-z_]\w*|\[[^\[\]\n]*\])+)')
STEP = re.compile(r'\s*(?:->|\.)\s*[A-Za-z_]\w*|\[[^\[\]\n]*\]')
KEYWORDS = {'return', 'sizeof', 'if', 'while', 'for', 'switch', 'case', 'else', 'do', 'goto', 'new', 'delete'}


# --------------------------------------------------------------------------
# trace side: the defining PCode line of a vreg -> a pattern + index

def pre_lines(trace_lines):
    out = []
    for l in trace_lines:
        m = re.match(r'PCODE pre B(\d+) (-?\d+) (.*)', l)
        if m:
            out.append((int(m.group(2)), m.group(3)))
    return out


def gen_pat(insn):
    """`LWZ r66!,r32,44` -> regex with every virtual register generalised."""
    op, _, args = insn.partition(' ')
    parts = []
    for a in args.split(','):
        m = re.fullmatch(r'([rf])(\d+)(!?)', a.strip())
        if m and int(m.group(2)) >= 32:
            parts.append(m.group(1) + r'\d+' + ('!' if m.group(3) else ''))
        else:
            parts.append(re.escape(a.strip()))
    return '^' + re.escape(op) + (' ' + ','.join(parts) if args else '') + '$'


def def_site(pre, v):
    """(srcline, pattern, k) of vreg v's first defining pre-RA line, or None."""
    rx = re.compile(r'\b' + re.escape(v) + '!')
    for i, (ln, insn) in enumerate(pre):
        if rx.search(insn):
            pat = re.compile(gen_pat(insn))
            k = sum(1 for _, x in pre[:i] if pat.search(x))
            return ln, gen_pat(insn), k
    return None


def want_expr(sols, pre):
    """OR over diag solutions of the AND of their source-visible edits."""
    terms, lines, kinds = [], set(), set()
    for es in sols:
        parts = []
        for e in es:
            a = def_site(pre, e['a'])
            b = def_site(pre, e['b']) if e.get('b') else None
            for s in (a, b):
                if s and s[0] > 0:
                    lines.add(s[0])
            kinds.add(e['kind'])
            if not a:
                continue
            if e['kind'] == 'name':
                parts.append(f"T.named(r'{a[1]}', {a[2]})")
            elif e['kind'] in ('renumber', 'swapnum') and b:
                rel = '>' if e['kind'] == 'swapnum' or (e.get('extra') or 0) > 0 else '<'
                if e['kind'] == 'swapnum':
                    rel = '<' if e['a'][1:].isdigit() and int(e['a'][1:]) > int(e['b'][1:]) else '>'
                parts.append(f"T.num(r'{a[1]}', {a[2]}) {rel} T.num(r'{b[1]}', {b[2]})")
        if parts:
            terms.append('(' + ' and '.join(parts) + ')')
    return (' or '.join(dict.fromkeys(terms)) or None), lines, kinds


# --------------------------------------------------------------------------
# source side

def stmt_start(text, pos):
    """Index of the start of the statement containing pos (after the previous
    ; { } outside parentheses), or None when a read cannot be hoisted in front
    of it (loop header, else branch, case label, unbraced body)."""
    depth = 0
    i = pos - 1
    while i >= 0:
        c = text[i]
        if c in ')]':
            depth += 1
        elif c in '([':
            depth -= 1             # pos is inside a call / condition: keep walking out
        elif c in ';{}' and depth <= 0:
            if c == ';':
                k = max(text.rfind('{', 0, i), text.rfind('}', 0, i))
                if text.count('(', k + 1, i) > text.count(')', k + 1, i):
                    return None    # inside a for(;;) header
            j = i + 1
            while j < len(text) and text[j] in ' \t\n':
                j += 1
            if re.match(r'(for|while|do|else|case|default|switch)\b', text[j:j + 8]):
                return None
            if re.match(r'if\s*\(', text[j:j + 6]):
                # only when pos is inside the condition itself
                k, d = text.index('(', j), 0
                while k < len(text):
                    d += {'(': 1, ')': -1}.get(text[k], 0)
                    if d == 0:
                        break
                    k += 1
                if pos > k:
                    return None    # unbraced if body
            return j
        i -= 1
    return None


def enclosing_block(text, pos, lo):
    """Index just after the `{` of the innermost block containing pos (>= lo)."""
    depth = 0
    i = pos - 1
    while i >= lo:
        c = text[i]
        if c == '}':
            depth += 1
        elif c == '{':
            if depth == 0:
                return i + 1
            depth -= 1
        i -= 1
    return lo


def chain_prefixes(m):
    """Prefixes (with at least one step) of a matched access chain, as (start, end)."""
    base_end = m.start(2)
    out, j = [], base_end
    for s in STEP.finditer(m.group(2)):
        j = base_end + s.end()
        out.append((m.start(1), j))
    return out


def is_rvalue(text, end):
    rest = text[end:end + 3]
    if re.match(r'\s*(=(?!=)|\+\+|--|[-+*/|&^]=|<<=|>>=|\()', rest + text[end + 3:end + 6]):
        return False
    return True


def static_inlines(text):
    out = {}
    for m in re.finditer(r'(?m)^static\s+inline\s+([\w\s\*]+?)\s*\b(\w+)\s*\(([^)]*)\)\s*\{', text):
        j, depth = m.end(), 1
        while depth and j < len(text):
            depth += {'{': 1, '}': -1}.get(text[j], 0)
            j += 1
        out[m.group(2)] = (m.group(1).strip(), m.group(3), text[m.end():j - 1])
    return out


def inline_variant(name, ret, params, body):
    """F with every `p->f` read of one pointer param replaced by extra params.
    -> (helper text, pointer param index, [(field, type text, param name)]) or None."""
    ps = [p.strip() for p in params.split(',') if p.strip()]
    for pi, p in enumerate(ps):
        m = re.match(r'(.*?\*)\s*(\w+)$', p)
        if not m:
            continue
        ptype, pn = m.group(1).strip(), m.group(2)
        reads = re.findall(r'\b' + pn + r'\s*->\s*(\w+)(?!\s*(?:=(?!=)|\+\+|--|[-+*/|&^]=|\[|\.|->))', body)
        if not reads or re.search(r'\b' + pn + r'\b(?!\s*->)', body):
            continue                 # p used as a whole: keep it
        if re.search(r'\b' + pn + r'\s*->\s*\w+\s*(=(?!=)|\+\+|--|[-+*/|&^]=)', body):
            continue                 # written through: not a pure reader
        fields, b2, newp = [], body, []
        for f in dict.fromkeys(reads):
            lm = re.search(r'(?m)^\s*([\w\s\*]+?)\s+(\w+)\s*=\s*' + pn + r'\s*->\s*' + f + r'\s*;[ \t]*\n', b2)
            if lm and not re.search(r'\b' + pn + r'\s*->\s*' + f + r'\b', b2[:lm.start()] + b2[lm.end():]):
                b2 = b2[:lm.start()] + b2[lm.end():]
                fields.append((f, lm.group(1).strip(), lm.group(2)))
            else:
                pname = f + '__nl'
                b2 = re.sub(r'\b' + pn + r'\s*->\s*' + f + r'\b', pname, b2)
                fields.append((f, f'__typeof__((({ptype})0)->{f})', pname))
            newp.append(f'{fields[-1][1]} {fields[-1][2]}')
        rest = [q for k, q in enumerate(ps) if k != pi]
        helper = f'static inline {ret} {name}__nl({", ".join(rest + newp) or "void"}) {{{b2}}}\n'
        return helper, pi, fields
    return None


def build_template(src, fn_span, lines, cpp, max_axes=6):
    """-> (helpers, def template text, notes)."""
    ls, _, end = fn_span
    text = src
    body_lo = text.index('{', ls) + 1
    line_starts = [0] + [m.end() for m in re.finditer('\n', text)]

    def line_span(n):
        a = line_starts[n - 1]
        b = text.find('\n', a)
        return a, (b if b >= 0 else len(text))
    # a diagnosed line inside a multi-line statement: take the whole statement
    ext = set()
    for n in lines:
        if 0 < n <= len(line_starts):
            a = line_starts[n - 1]
            if not (body_lo <= a < end):
                continue
            j, depth = a, 0
            while j < end:
                c = text[j]
                depth += {'(': 1, ')': -1}.get(c, 0)
                if c == '\n':
                    n += 1
                if (c == ';' and depth <= 0) or c in '{}':
                    break
                ext.add(n)
                j += 1
            ext.add(n)
    lines = sorted(set(lines) | ext)
    edits = []           # (pos, end, kind, payload) applied back to front
    notes, helpers = [], []
    inl = static_inlines(text[:ls])
    # occurrences of chain prefixes on the diagnosed lines (continuation lines of
    # a statement included: a diagnosed line inside a call spanning lines)
    occ = {}
    seen_pos = set()
    for n in sorted(lines):
        if n <= 0 or n > len(line_starts):
            continue
        a, b = line_span(n)
        if a < body_lo or b > end:
            continue
        for m in CHAIN.finditer(text, a, b):
            if m.group(1) in KEYWORDS:
                continue
            for s, e in chain_prefixes(m):
                if (s, e) in seen_pos or not is_rvalue(text, e):
                    continue
                seen_pos.add((s, e))
                if s > 0 and text[s - 1] == '&':
                    continue
                key = re.sub(r'\s+', '', text[s:e])
                occ.setdefault(key, []).append((s, e))
    # inline calls on those lines
    calls = []
    for n in sorted(lines):
        if n <= 0 or n > len(line_starts):
            continue
        a, b = line_span(n)
        if a < body_lo or b > end:
            continue
        for m in re.finditer(r'\b(\w+)\s*\(', text[a:b]):
            nm = m.group(1)
            if nm not in inl:
                continue
            p0 = a + m.end()
            depth, j = 1, p0
            while depth and j < len(text):
                depth += {'(': 1, ')': -1}.get(text[j], 0)
                j += 1
            iv = inline_variant(nm, *inl[nm])
            if not iv:
                continue
            args = [x.strip() for x in re.split(r',(?![^()]*\))', text[p0:j - 1])]
            helper, pi, fields = iv
            if pi >= len(args) or not re.fullmatch(r'[\w\->\.\[\]]+', args[pi]):
                continue
            calls.append((a + m.start(), j, nm, args, pi, fields, helper))
    # rank hoist candidates: more occurrences first, then shorter
    cands = sorted(occ.items(), key=lambda kv: (-len(kv[1]), len(kv[0])))[:max_axes - min(len(calls), 2)]
    ax = 0
    for key, pos in cands:
        pos.sort()
        h = f'h{ax}'
        ax += 1
        expr = text[pos[0][0]:pos[0][1]]
        # modes: 0 none, 1 all, 2 all but first, 3 first only
        named = lambda mode, i: (mode == 1) or (mode == 2 and i > 0) or (mode == 3 and i == 0)  # noqa: E731
        first_stmt = stmt_start(text, pos[0][0])
        if cpp and first_stmt is not None:
            dpos = first_stmt
        else:
            dpos = enclosing_block(text, pos[0][0], body_lo)
        decl = f'__typeof__({expr}) {h};'
        edits.append((dpos, dpos, 'decl', f'{{{{{h}: | {decl} | {decl} | {decl} }}}} '))
        for i, (s, e) in enumerate(pos):
            alts = [None if not named(m_, i) else h for m_ in range(4)]   # None = original text
            edits.append((s, e, 'repl', (h, alts)))
            st = stmt_start(text, s)
            if st is not None:
                asg = [f'{h} = {expr}; ' if named(m_, i) else '' for m_ in range(4)]
                edits.append((st, st, 'asg', '{{' + h + ': ' + ' | '.join(asg) + ' }}'))
        notes.append(f'{h}: hold `{expr}` in a named local ({len(pos)} occurrence(s) on the diagnosed lines)')
    for k, (s, e, nm, args, pi, fields, helper) in enumerate(calls[:2]):
        c = f'c{k}'
        helpers.append(helper)
        A = args[pi]
        rest = [x for i, x in enumerate(args) if i != pi]
        names = [f'nl{k}_{f}' for f, _, _ in fields]
        call2 = f'{nm}__nl({", ".join(rest + names)})'
        edits.append((s, e, 'repl', (c, [None, call2])))
        st = stmt_start(text, s)
        decls = ' '.join(f'{t if not t.startswith("__typeof__") else f"__typeof__({A}->{f})"} {n};'
                         for (f, t, _), n in zip(fields, names))
        asg = ' '.join(f'{n} = {A}->{f};' for (f, _, _), n in zip(fields, names))
        if cpp and st is not None:
            init = ' '.join(f'{t if not t.startswith("__typeof__") else f"__typeof__({A}->{f})"} {n} = {A}->{f};'
                            for (f, t, _), n in zip(fields, names))
            edits.append((st, st, 'asg', '{{' + c + ': | ' + init + ' }} '))
        else:
            dpos = enclosing_block(text, s, body_lo)
            edits.append((dpos, dpos, 'decl', '{{' + c + ': | ' + decls + ' }} '))
            if st is not None:
                edits.append((st, st, 'asg', '{{' + c + ': | ' + asg + ' }} '))
        notes.append(f'{c}: call {nm}__nl with {", ".join(f for f, _, _ in fields)} read into named locals '
                     f'(inline-wrapper-named-locals)')
    # replacements: nested prefixes share their start; build each group's
    # point from the shortest out (an outer point's "original" alternative
    # holds the inner point + the rest of the text)
    order = {'decl': 0, 'asg': 1}
    ins = [x for x in edits if x[2] != 'repl']
    groups = {}
    for s, e, _, pl in edits:
        if _ == 'repl':
            groups.setdefault(s, []).append((e, pl))
    reps = []
    for s, lst in groups.items():
        lst.sort(key=lambda x: x[0])
        prev_end, prev_txt = s, ''
        for e, (h, alts) in lst:
            orig = prev_txt + text[prev_end:e]
            prev_txt = '{{' + h + ': ' + ' | '.join(orig if a is None else a for a in alts) + ' }}'
            prev_end = e
        reps.append((s, prev_end, 'repl', prev_txt))
    allx = sorted(reps + ins, key=lambda x: (x[0], order.get(x[2], 2)), reverse=True)
    t = text[ls:end]
    for s, e, kind, payload in allx:
        t = t[:s - ls] + payload + t[e - ls:]
    return helpers, t, notes


def generate(src_text, fn, rep, trace_lines, find_def, cpp):
    """-> dict(template=str, want=str|None, notes=[...]) or None."""
    pre = pre_lines(trace_lines)
    sols = []
    for rc in ('gpr', 'fpr'):
        c = rep.get('classes', {}).get(rc)
        if c:
            sols += c.get('solutions', [])
    if not sols:
        return None
    want, lines, kinds = want_expr(sols, pre)
    for rc in ('gpr', 'fpr'):          # the mismatching vregs' lines too
        c = rep.get('classes', {}).get(rc)
        for v in (c or {}).get('bad', []):
            s = def_site(pre, v)
            if s and s[0] > 0:
                lines.add(s[0])
    span = find_def(src_text, fn)
    if not span:
        return None
    helpers, t, notes = build_template(src_text, span, lines, cpp)
    return {'template': ''.join(helpers) + t, 'want': want, 'notes': notes, 'lines': sorted(lines)}
