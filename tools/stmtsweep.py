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

Dependencies: a statement reads/writes the identifiers it names (the
left-hand identifier of `x = ...`, `x++`, `x += ...` is written). Any
write through `->`, `.`, `[` or `*` writes MEM, any such access reads MEM,
and a statement containing a call reads and writes MEM. Two statements are
ordered when one writes what the other reads or writes.

Run from the repo root after a build. Claim the TU before applying.
Status 11-08: written at wind-down, not yet validated on a real function.
"""
import argparse, itertools, json, re, subprocess, sys

OBJDIFF = 'build/tools/objdiff-cli'
CTRL = re.compile(r'^\s*(if|else|for|while|do|switch|case|default|return|break|continue|goto|\{|\}|#|//|/\*)')
TYPE_START = re.compile(r'^\s*(const\s+|static\s+|unsigned\s+|signed\s+|struct\s+|volatile\s+)*'
                        r'(int|long|short|char|float|double|void|u8|u16|u32|s8|s16|s32|f32|f64|bool|[A-Z]\w*)\b[\s\*&]+\w+\s*(=|;|\[)')
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


def effects(stmt):
    s = stmt.strip().rstrip(';')
    reads, writes = set(), set()
    call = re.search(r'\w\s*\(', re.sub(r'\(\s*(unsigned\s+|signed\s+|const\s+)*\w+\s*\**\s*\)', '', s))
    m = re.match(r'^(.*?)(\+\+|--|[-+*/%&|^]?=)(?!=)(.*)$', s)
    if m and '==' not in m.group(2):
        lhs, op, rhs = m.group(1), m.group(2), m.group(3)
    else:
        lhs, op, rhs = '', '', s
    if re.search(r'->|\.|\[|^\s*\*', lhs):
        writes.add('MEM')
        reads |= {x for x in IDENT.findall(lhs) if x not in KEYW}
    elif lhs.strip():
        v = IDENT.findall(lhs)
        if v: writes.add(v[-1])
        if op not in ('=',): reads |= set(v)
    if re.search(r'->|\.|\[|\*\s*\w', rhs + (lhs if 'MEM' in writes else '')):
        reads.add('MEM')
    reads |= {x for x in IDENT.findall(rhs) if x not in KEYW}
    if s.endswith(('++', '--')) or s.startswith(('++', '--')):
        v = IDENT.findall(s)
        if v: writes.add(v[0]); reads.add(v[0])
    if call:
        reads.add('MEM'); writes.add('MEM')
    return reads, writes


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


def topo_orders(stmts, cap):
    eff = [effects(s) for s in stmts]
    n = len(stmts)
    before = [set() for _ in range(n)]
    for a in range(n):
        for b in range(a + 1, n):
            ra, wa = eff[a]; rb, wb = eff[b]
            if (wa & rb) or (wa & wb) or (ra & wb):
                before[b].add(a)
    out = []
    def rec(done, order):
        if len(out) >= cap: return
        if len(order) == n:
            out.append(list(order)); return
        for k in range(n):
            if k not in done and before[k] <= done:
                done.add(k); order.append(k)
                rec(done, order)
                order.pop(); done.discard(k)
    rec(set(), [])
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--tu', required=True); ap.add_argument('--fn', required=True)
    ap.add_argument('--max', type=int, default=2000)
    ap.add_argument('--apply', action='store_true')
    a = ap.parse_args()
    src = a.tu; obj_rel = src[4:].rsplit('.', 1)[0]
    orig = open(src).read()
    sp = body_span(orig, a.fn)
    if not sp:
        sys.exit(f'{a.fn} not found in {src}')
    base = scores(obj_rel)
    if base is None:
        sys.exit('base does not build')
    cur = orig; cur_sc = base
    fnkey = next((k for k in base if k == a.fn or k.startswith(a.fn + '__')), a.fn)
    print(f'base {fnkey} {base.get(fnkey)}', flush=True)
    bs, be = sp
    lines = cur[bs:be].split('\n')
    for (s, e) in list(runs(lines)):
        stmts = lines[s:e]
        orders = topo_orders(stmts, a.max)
        if len(orders) <= 1:
            continue
        best = None
        for o in orders[1:]:
            nl = lines[:s] + [stmts[k] for k in o] + lines[e:]
            text = cur[:bs] + '\n'.join(nl) + cur[be:]
            open(src, 'w').write(text)
            sc = scores(obj_rel)
            if sc is None: continue
            if any(sc.get(k, 0) < v - 1e-6 for k, v in cur_sc.items() if k != fnkey):
                continue
            g = sc.get(fnkey, 0) - cur_sc.get(fnkey, 0)
            if g > 1e-6 and (best is None or g > best[0]):
                best = (g, nl, text, sc)
                if sc.get(fnkey, 0) >= 100: break
        if best:
            print(f'  run at line {s} ({e - s} stmts, {len(orders)} orders): {cur_sc.get(fnkey):.2f} -> {best[3].get(fnkey):.2f}', flush=True)
            lines, cur, cur_sc = best[1], best[2], best[3]
            be = bs + len('\n'.join(lines))
        else:
            print(f'  run at line {s} ({e - s} stmts, {len(orders)} orders): no gain', flush=True)
        if cur_sc.get(fnkey, 0) >= 100: break
    open(src, 'w').write(cur if a.apply else orig)
    if not a.apply:
        scores(obj_rel)
    print(f'final {fnkey} {cur_sc.get(fnkey)}' + (' (applied)' if a.apply else ''), flush=True)


if __name__ == '__main__':
    main()
