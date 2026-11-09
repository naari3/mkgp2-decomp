#!/usr/bin/env python3
"""Sweep "name the inline's return value" variants (regalloc_patterns §16).

    python3 tools/retname_sweep.py [--census build/regswap_census.json] [--tu src/game/X.c] [--apply]

For every static inline in a near-miss TU whose `return` expression contains
a call, rewrite `return EXPR;` as `T __ret; ... __ret = EXPR; return __ret;`
with the `T __ret;` declaration tried at every position among the inline's
leading declarations. Each variant rebuilds the TU's object and scores all
its functions with objdiff. A variant is reported when the TU's summed
match goes up and no function goes down. With --apply the best variant is
left in the source (otherwise the file is restored).

Run from the repo root after a build. Skips TUs claimed by others when the
census rows carry a claim (see tools/regswap_classify.py --claims).
"""
import argparse, json, re, subprocess, sys

OBJDIFF = os.path.normpath('build/tools/objdiff-cli' + ('.exe' if os.name == 'nt' else ''))


def tu_scores(unit, obj_rel):
    r = subprocess.run(['ninja', f'build/GNLJ82/src/{obj_rel}.o'], capture_output=True, text=True)
    if r.returncode:
        return None
    r = subprocess.run([OBJDIFF, 'diff', '-1', f'build/GNLJ82/obj/{obj_rel}.o', '-2', f'build/GNLJ82/src/{obj_rel}.o',
                        '-o', '-'], capture_output=True, text=True)
    try:
        d = json.loads(r.stdout)
    except ValueError:
        return None
    out = {}
    for s in d.get('right', {}).get('symbols', []):
        if s.get('instructions') and s.get('match_percent') is not None:
            out[s['name']] = s['match_percent']
    return out


INLINE = re.compile(r'static inline\s+([^{;()]*?)\b(\w+)\s*\(([^)]*)\)\s*\{')


def find_inlines(text):
    """Yield (name, rettype, body_start, body_end) for each static inline."""
    for m in INLINE.finditer(text):
        ret = m.group(1).strip()
        if ret in ('void', '') or 'void' == ret.split()[-1]:
            continue
        i = m.end(); depth = 1
        while i < len(text) and depth:
            if text[i] == '{': depth += 1
            elif text[i] == '}': depth -= 1
            i += 1
        yield m.group(2), ret, m.end(), i - 1


def variants(text, name, ret, bs, be):
    body = text[bs:be]
    rets = list(re.finditer(r'\breturn\s+([^;]+);', body))
    if len(rets) != 1 or '(' not in rets[0].group(1):
        return []
    r = rets[0]
    # leading declarations: lines at the top of the body that look like `T a;` / `T a = x;`
    lines = body.split('\n')
    first = 1 if lines and lines[0].strip() == '' else 0
    decl_end = first
    while decl_end < len(lines) and re.match(r'\s*(const\s+)?(unsigned\s+|signed\s+)?\w[\w\s\*]*\b\w+\s*(=[^;]*)?;\s*$', lines[decl_end]) \
            and not lines[decl_end].strip().startswith('return'):
        decl_end += 1
    indent = re.match(r'\s*', lines[first] if first < len(lines) else '    ').group(0) or '    '
    out = []
    for pos in range(first, decl_end + 1):
        nl = list(lines)
        nl.insert(pos, f'{indent}{ret} __ret;')
        nb = '\n'.join(nl)
        nb = re.sub(r'\breturn\s+([^;]+);', lambda m: f'__ret = {m.group(1)};\n{indent}return __ret;', nb, count=1)
        out.append((pos - first, text[:bs] + nb + text[be:]))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--census', default='build/regswap_census.json')
    ap.add_argument('--tu')
    ap.add_argument('--apply', action='store_true')
    a = ap.parse_args()
    rows = json.load(open(a.census))
    tus = {}
    for r in rows:
        if not r.get('src') or (r.get('claim') and r['claim'] != 'naari3'):
            continue
        tus.setdefault(r['src'], r['unit'])
    if a.tu:
        tus = {a.tu: tus.get(a.tu, 'main/' + a.tu[4:].rsplit('.', 1)[0])}
    for src, unit in sorted(tus.items()):
        obj_rel = src[4:].rsplit('.', 1)[0]
        try:
            orig = open(src).read()
        except OSError:
            continue
        cands = list(find_inlines(orig))
        work = [(n, rt, bs, be) for n, rt, bs, be in cands if variants(orig, n, rt, bs, be)]
        if not work:
            continue
        base = tu_scores(unit, obj_rel)
        if base is None:
            continue
        best = None
        for n, rt, bs, be in work:
            for pos, text in variants(orig, n, rt, bs, be):
                open(src, 'w').write(text)
                sc = tu_scores(unit, obj_rel)
                if sc is None:
                    continue
                if any(sc.get(k, 0) < v - 1e-6 for k, v in base.items()):
                    continue
                gain = sum(sc.values()) - sum(base.values())
                if gain > 1e-6 and (best is None or gain > best[0]):
                    ups = {k: (round(base.get(k, 0), 2), round(v, 2)) for k, v in sc.items() if v > base.get(k, 0) + 1e-6}
                    best = (gain, n, pos, text, ups)
        open(src, 'w').write(orig)
        if best:
            print(f'{src}: inline {best[1]} __ret at decl pos {best[2]}: {best[4]}', flush=True)
            if a.apply:
                open(src, 'w').write(best[3])
        else:
            print(f'{src}: no gain ({len(work)} inlines)', flush=True)
        tu_scores(unit, obj_rel)


if __name__ == '__main__':
    main()
