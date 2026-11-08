#!/usr/bin/env python3
"""Sweep the integer types of locals (int <-> long <-> unsigned ...) for register-only near misses.

    python3 tools/typesweep.py --tu src/game/X.cpp [--fn NAME] [--apply]
    python3 tools/typesweep.py --census build/regswap_census.json [--min 99] [--apply]

MWCC colors registers on its IR, where `int`, `long` and `unsigned int` are
different types (signed vs logical shifts, different conversion nodes) even
when the final instructions are the same. Changing one local's type can move
it between r0 and r4 or between two saved registers (fn_801D1684: `int alpha`
-> `unsigned int alpha` 99.16 -> 100; ItemSelectState_Init: a clamp as `long`).

For every declaration of a plain integer local (in the TU's function bodies
and static inlines) the sweep tries the other types of the same width, one
declaration at a time, greedily keeping a change when the TU's summed objdiff
match rises and no function drops. Run from the repo root after a build.
"""
import argparse, json, re, subprocess

OBJDIFF = 'build/tools/objdiff-cli'
W32 = ['int', 'long', 'unsigned int', 'unsigned long']
W16 = ['short', 'unsigned short', 'int']
W8 = ['unsigned char', 'signed char', 'int', 'unsigned int']
ALTS = {}
for g in (W32, W16, W8):
    for t in g:
        ALTS.setdefault(t, [])
        ALTS[t] += [x for x in g if x != t and x not in ALTS[t]]
ALTS['unsigned'] = ALTS['unsigned int']
ALTS['u32'] = ALTS['unsigned int']; ALTS['s32'] = ALTS['int']
ALTS['u8'] = ALTS['unsigned char']; ALTS['s8'] = ALTS['signed char']
ALTS['u16'] = ALTS['unsigned short']; ALTS['s16'] = ALTS['short']
TYPES = sorted(ALTS, key=len, reverse=True)
DECL = re.compile(r'(?m)^(\s+|.*\(\s*)(' + '|'.join(re.escape(t) for t in TYPES) + r')(\s+)([A-Za-z_]\w*)(\s*(?:=|;|,|\[))')


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


def sites(text):
    out = []
    for m in DECL.finditer(text):
        pre = m.group(1)
        if 'for' in pre or pre.strip().startswith(('return', 'extern', 'typedef', 'static')):
            if not pre.strip().startswith('for') and '(' in pre:
                continue
        if pre.strip() and '(' in pre and not pre.strip().startswith('for'):
            continue  # parameter lists are left alone
        out.append((m.start(2), m.end(2), m.group(2), m.group(4)))
    return out


def sweep(src, only_fn=None, apply=False):
    obj_rel = src[4:].rsplit('.', 1)[0]
    orig = open(src).read()
    base = scores(obj_rel)
    if base is None:
        print(f'{src}: does not build'); return
    if all(v >= 100 for v in base.values()):
        return
    cur, cur_sc = orig, base
    changes = []
    i = 0
    while True:
        ss = sites(cur)
        if i >= len(ss): break
        s, e, ty, name = ss[i]
        best = None
        for alt in ALTS.get(ty, []):
            t = cur[:s] + alt + cur[e:]
            open(src, 'w').write(t)
            sc = scores(obj_rel)
            if sc is None: continue
            if any(sc.get(k, 0) < v - 1e-6 for k, v in cur_sc.items()):
                continue
            if only_fn and sc.get(only_fn, 0) <= cur_sc.get(only_fn, 0) + 1e-6:
                continue
            gain = sum(sc.values()) - sum(cur_sc.values())
            if gain > 1e-6 and (best is None or gain > best[0]):
                best = (gain, alt, t, sc)
        if best:
            ups = {k: (round(cur_sc.get(k, 0), 2), round(v, 2)) for k, v in best[3].items() if v > cur_sc.get(k, 0) + 1e-6}
            changes.append(f'{ty} {name} -> {best[1]}: {ups}')
            print(f'  {src}: {changes[-1]}', flush=True)
            cur, cur_sc = best[2], best[3]
        i += 1
    open(src, 'w').write(cur if apply else orig)
    if not apply:
        scores(obj_rel)
    print(f'{src}: {len(changes)} change(s)' + (' applied' if apply and changes else ''), flush=True)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--tu'); ap.add_argument('--fn')
    ap.add_argument('--census'); ap.add_argument('--min', type=float, default=97)
    ap.add_argument('--apply', action='store_true')
    a = ap.parse_args()
    if a.tu:
        sweep(a.tu, a.fn, a.apply); return
    rows = json.load(open(a.census))
    seen = set()
    for r in sorted(rows, key=lambda r: -r.get('pct', 0)):
        src = r.get('src')
        if not src or src in seen or r.get('pct', 0) < a.min: continue
        if r.get('claim') and r['claim'] != 'naari3': continue
        seen.add(src)
        sweep(src, None, a.apply)


if __name__ == '__main__':
    main()
