#!/usr/bin/env python3
"""Sweep the order of independent statements inside one function.

    python3 tools/stmtsweep.py --tu src/game/X.c --fn NAME [--max 2000] [--apply]

Finds runs of consecutive one-line statements at the same indentation in
the function body (assignments, expression statements; no control flow,
no declarations), builds a conservative dependency graph for each run and
tries dependency-safe orders. Runs are swept one after another, greedily
keeping the best order of each (TextRenderer_DrawEntry bc31b3a matched this
way after a declaration-order sweep). Score is objdiff's match percent for
--fn; a change is kept only when no other function in the TU drops.

Dependencies: a statement reads/writes the names it uses (the left-hand
side of `x = ...`, `x++`, `x += ...` is written). Locals (params and
declarations in the swept function) are tracked by name. Globals, `x->f` /
`x.f` (keyed by field name: different fields never alias) and `*p` / `a[i]`
(MEM, aliases all memory) are memory. A call reads and writes MEM, so it
stays ordered against every memory access. Two statements are ordered when
one writes what the other reads or writes. --strict-mem makes every field
access MEM.

Runs with at most --max orders are swept exhaustively; bigger runs use a
first-improvement hill-climb over single-statement moves (--max builds).
--body sweeps an inline helper's statements while scoring --fn.

Run from the repo root after a build. Claim the TU before applying.
Status 11-08: rediscovers TextRenderer_DrawEntry (99.54 -> 100 in 73 builds).
"""
import argparse, itertools, json, re, subprocess, sys

OBJDIFF = os.path.normpath('build/tools/objdiff-cli' + ('.exe' if os.name == 'nt' else ''))
CTRL = re.compile(r'^\s*(if|else|for|while|do|switch|case|default|return|break|continue|goto|\{|\}|#|//|/\*)')
TYPE_START = re.compile(r'^\s*(const\s+|static\s+|unsigned\s+|signed\s+|struct\s+|volatile\s+)*'
                        r'(int|long|short|char|float|double|void|u8|u16|u32|s8|s16|s32|f32|f64|bool|[A-Z]\w*)\b[\s\*&]+\w+\s*(=|;|\[|,)')
IDENT = re.compile(r'[A-Za-z_]\w*')
KEYW = {'sizeof', 'int', 'unsigned', 'char', 'short', 'long', 'float', 'double', 'const', 'void', 'signed'}


def scores(obj_rel):
    r = subprocess.run(['ninja', f'build/GNLJ82/src/{obj_rel}.o'], capture_output=True, text=True)
    if r.returncode:
        return None
    r = subprocess.run([OBJDIFF, 'diff', '-1', f'build/GNLJ82/obj/{obj_rel}.o', '-2', f'build/GNLJ82/src/{obj_rel}.o', '-o', '-'],
                       capture_output=True, text=True)
    try:
        d = json.loads(r.stdout)
    except ValueError:
        return None
    return {s['name']: s['match_percent'] for s in d.get('right', {}).get('symbols', [])
            if s.get('instructions') and s.get('match_percent') is not None}


def body_span(text, fn):
    m = re.search(r'\b' + re.escape(fn) + r'\s*\([^;{]*\)\s*\{', text)
    if not m:
        return None
    i = m.end(); depth = 1
    while i < len(text) and depth:
        if text[i] == '{': depth += 1
        elif text[i] == '}': depth -= 1
        i += 1
    return m.end(), i - 1


FIELDS = True   # --strict-mem turns this off
LOCALS = None   # names declared in the swept function; anything else is a global
MEMBER = re.compile(r'(->|\.)\s*([A-Za-z_]\w*)')
NUMBER = re.compile(r'\b(0[xX][0-9a-fA-F]+|\d+(\.\d*)?([eE][-+]?\d+)?)[uUlLfF]*\b')
CALL = re.compile(r'([A-Za-z_]\w*)\s*\(')


def names(expr):
    """Plain identifiers of an expression (no member names, numbers, called functions)."""
    e = NUMBER.sub(' ', MEMBER.sub(' ', expr))
    fns = {m.group(1) for m in CALL.finditer(e)}
    return {x for x in IDENT.findall(e) if x not in KEYW and x not in fns}


def has_call(expr):
    return any(m.group(1) not in KEYW for m in CALL.finditer(NUMBER.sub(' ', expr)))


def mem_keys(expr):
    """Memory locations an expression touches: 'M.<field>' for x->f / x.f
    (field-name disambiguation), 'MEM' for anything else (*p, a[i])."""
    keys = set()
    for m in MEMBER.finditer(NUMBER.sub(' ', expr)):
        keys.add('M.' + m.group(2) if FIELDS else 'MEM')
    if re.search(r'\[|(^|[^\w)\]\s]\s*|^\s*)\*\s*[\w(]', expr):
        keys.add('MEM')
    return keys


def is_mem(k):
    return k == 'MEM' or k[:2] in ('M.', 'G.')


def conflict(a, b):
    """True when key sets a and b may name the same location."""
    if a & b: return True
    return ('MEM' in a and any(map(is_mem, b))) or ('MEM' in b and any(map(is_mem, a)))


def effects(stmt):
    """(reads, writes) of one statement. Locals are plain names, globals 'G.x',
    struct fields 'M.f', everything else 'MEM'. A call reads and writes MEM."""
    s = stmt.strip().rstrip(';').strip()
    reads, writes = set(), set()
    m = re.match(r'^(.*?[^=!<>+\-*/%&|^])((?:<<|>>|[-+*/%&|^])?=)(?!=)(.*)$', s)
    if m:
        lhs, op, rhs = m.group(1), m.group(2), m.group(3)
    else:
        m = re.match(r'^(\+\+|--)(.*)$|^(.*?)(\+\+|--)$', s)
        if m:
            lhs = m.group(2) if m.group(2) is not None else m.group(3)
            op, rhs = '++', ''
        else:
            lhs, op, rhs = '', '', s
    lhs = lhs.strip()
    if lhs:
        last = re.search(r'(->|\.)\s*([A-Za-z_]\w*)\s*$', lhs)
        if last and FIELDS:
            writes.add('M.' + last.group(2))
            inner = lhs[:last.start()]
            reads |= mem_keys(inner) | names(inner)
        elif re.match(r'^[A-Za-z_]\w*$', lhs):
            writes.add(lhs)
        else:
            writes.add('MEM'); reads |= mem_keys(lhs) | names(lhs)
        if op != '=':
            reads |= writes
    reads |= mem_keys(rhs) | names(rhs)
    if has_call(s):
        reads.add('MEM'); writes.add('MEM')
    if LOCALS is not None:
        g = lambda ks: {('G.' + k if not is_mem(k) and k not in LOCALS else k) for k in ks}
        reads, writes = g(reads), g(writes)
    return reads, writes


def local_names(text, start, end):
    """Parameter and local names of the function whose body is text[start:end]."""
    p = text.rfind('(', 0, text.rfind(')', 0, start) + 1)
    out = set()
    for prm in text[p + 1:text.rfind(')', 0, start)].split(','):
        v = IDENT.findall(prm.split('=')[0])
        if v: out.add(v[-1])
    for line in text[start:end].split('\n'):
        l = re.sub(r'^\s*for\s*\(', '', line)
        if not TYPE_START.match(l):
            continue
        l = l.split(';')[0]
        depth = 0; piece = ''; pieces = []
        for ch in l:
            if ch in '([{': depth += 1
            elif ch in ')]}': depth -= 1
            if ch == ',' and depth == 0:
                pieces.append(piece); piece = ''
            else:
                piece += ch
        pieces.append(piece)
        for i, pc in enumerate(pieces):
            pc = pc.split('=')[0].split('[')[0]
            v = IDENT.findall(pc)
            if v: out.add(v[-1])
    return out


def runs(lines):
    """Yield (start, end) index ranges of consecutive simple statements (>=2)."""
    i = 0
    while i < len(lines):
        j = i
        ind = None
        while j < len(lines):
            l = lines[j]
            if not l.strip().endswith(';') or CTRL.match(l) or TYPE_START.match(l) or l.count(';') != 1:
                break
            li = len(l) - len(l.lstrip())
            if ind is None: ind = li
            if li != ind: break
            j += 1
        if j - i >= 2:
            yield i, j
            i = j
        else:
            i += 1


def deps(stmts):
    eff = [effects(s) for s in stmts]
    n = len(stmts)
    before = [set() for _ in range(n)]
    for a in range(n):
        for b in range(a + 1, n):
            ra, wa = eff[a]; rb, wb = eff[b]
            if conflict(wa, rb) or conflict(wa, wb) or conflict(ra, wb):
                before[b].add(a)
    return before


def legal(order, before):
    seen = set()
    for k in order:
        if not before[k] <= seen:
            return False
        seen.add(k)
    return True


def topo_orders(stmts, cap):
    """All dependency-safe orders, or None when there are more than cap."""
    before = deps(stmts)
    n = len(stmts)
    out = []
    def rec(done, order):
        if len(out) > cap: return
        if len(order) == n:
            out.append(list(order)); return
        for k in range(n):
            if k not in done and before[k] <= done:
                done.add(k); order.append(k)
                rec(done, order)
                order.pop(); done.discard(k)
    rec(set(), [])
    return None if len(out) > cap else out


def moves(order, before):
    """Orders reachable by moving one statement to another legal position."""
    n = len(order)
    for i in range(n):
        rest = order[:i] + order[i + 1:]
        for j in range(n):
            if j == i: continue
            o = rest[:j] + [order[i]] + rest[j:]
            if o != order and legal(o, before):
                yield o


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--tu', required=True); ap.add_argument('--fn', required=True)
    ap.add_argument('--max', type=int, default=2000)
    ap.add_argument('--apply', action='store_true')
    ap.add_argument('--body', help='sweep the statements of this function (e.g. an inline) '
                    'while scoring --fn; default --fn')
    ap.add_argument('--strict-mem', action='store_true',
                    help='treat every memory access as one location (default: x->f / x.f '
                    'only conflict with the same field name, calls, * and [])')
    a = ap.parse_args()
    global FIELDS
    FIELDS = not a.strict_mem
    src = a.tu; obj_rel = src[4:].rsplit('.', 1)[0]
    orig = open(src).read()
    sp = body_span(orig, a.body or a.fn)
    if not sp:
        sys.exit(f'{a.body or a.fn} not found in {src}')
    global LOCALS
    LOCALS = local_names(orig, *sp) | {'this'}
    base = scores(obj_rel)
    if base is None:
        sys.exit('base does not build')
    cur = orig; cur_sc = base
    fnkey = next((k for k in base if k == a.fn or k.startswith(a.fn + '__')), a.fn)
    print(f'base {fnkey} {base.get(fnkey)}', flush=True)
    bs, be = sp
    lines = cur[bs:be].split('\n')
    def try_order(o, s, e, stmts):
        nl = lines[:s] + [stmts[k] for k in o] + lines[e:]
        text = cur[:bs] + '\n'.join(nl) + cur[be:]
        open(src, 'w').write(text)
        sc = scores(obj_rel)
        if sc is None: return None
        if any(sc.get(k, 0) < v - 1e-6 for k, v in cur_sc.items() if k != fnkey):
            return None
        return (sc.get(fnkey, 0) - cur_sc.get(fnkey, 0), nl, text, sc)

    for (s, e) in list(runs(lines)):
        stmts = lines[s:e]
        orders = topo_orders(stmts, a.max)
        if orders is not None and len(orders) <= 1:
            continue
        before = deps(stmts)
        best = None
        if orders is not None:
            # small run: exhaustive
            mode = f'{len(orders)} orders'
            for o in orders[1:]:
                r = try_order(o, s, e, stmts)
                if r and r[0] > 1e-6 and (best is None or r[0] > best[0]):
                    best = r
                    if r[3].get(fnkey, 0) >= 100: break
        else:
            # large run: hill-climb over single-statement moves (first improvement)
            mode = f'>{a.max} orders, local search'
            o_cur = list(range(e - s)); base_fn = cur_sc.get(fnkey, 0)
            seen = {tuple(o_cur)}; builds = 0; improved = True
            while improved and builds < a.max:
                improved = False
                for o in moves(o_cur, before):
                    if tuple(o) in seen: continue
                    seen.add(tuple(o)); builds += 1
                    r = try_order(o, s, e, stmts)
                    if r and r[0] > 1e-6 and (best is None or r[0] > best[0]):
                        best = r; o_cur = o; improved = True
                        print(f'    move -> {r[3].get(fnkey):.2f} ({builds} builds)', flush=True)
                        break
                    if builds >= a.max: break
                if best and best[3].get(fnkey, 0) >= 100: break
        if best:
            print(f'  run at line {s} ({e - s} stmts, {mode}): {cur_sc.get(fnkey):.2f} -> {best[3].get(fnkey):.2f}', flush=True)
            lines, cur, cur_sc = best[1], best[2], best[3]
            be = bs + len('\n'.join(lines))
        else:
            print(f'  run at line {s} ({e - s} stmts, {mode}): no gain', flush=True)
        if cur_sc.get(fnkey, 0) >= 100: break
    open(src, 'w').write(cur if a.apply else orig)
    if not a.apply:
        scores(obj_rel)
    print(f'final {fnkey} {cur_sc.get(fnkey)}' + (' (applied)' if a.apply else ''), flush=True)


if __name__ == '__main__':
    main()
