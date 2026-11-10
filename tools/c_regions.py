#!/usr/bin/env python3
"""Mark the C parts of mixed C / C++ source files for compilers other than MWCC.

A unit that MWCC starts in C and switches with `#pragma cplusplus on/off/reset`
is one C++ file for clang or MSVC. This tool brackets every part that MWCC
compiles as C with C_REGION_BEGIN / C_REGION_END (include/game/types/c_region.h:
`extern "C" { }` for other compilers, nothing for MWCC), so names keep C
linkage there. Objects do not change.

    python3 tools/c_regions.py            # all of src/game (files already marked are skipped)
    python3 tools/c_regions.py FILE...    # only these
    python3 tools/c_regions.py --check    # list files that have pragmas but no markers

A file is left alone, and reported, when a region would start and end in
different #if branches.
"""
import os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PRAGMA = re.compile(r'^\s*#\s*pragma\s+cplusplus\s+(on|off|reset)\b')
INCLUDE = re.compile(r'^\s*#\s*include\s+"([^"]+)"')
COND = re.compile(r'^\s*#\s*(if|ifdef|ifndef|elif|else|endif)\b')
HDR = '#include "game/types/c_region.h"'


def rd(p):
    return open(p, encoding='utf-8', errors='surrogateescape', newline='').read()


def lang_cxx_units():
    out = set()
    text = rd(os.path.join(ROOT, 'configure.py'))
    for m in re.finditer(r'Object\([^\n]*?"([^"]+\.c)"[^\n]*', text):
        if re.search(r'-lang[= ]c\+\+', m.group(0)):
            out.add('src/' + m.group(1))
    return out


def has_pragma(path):
    try:
        return any(PRAGMA.match(l) for l in rd(path).split('\n'))
    except OSError:
        return False


def resolve(inc, cur):
    for base in (os.path.dirname(cur), ROOT, os.path.join(ROOT, 'include'), os.path.join(ROOT, 'src'), os.path.join(ROOT, 'src/game')):
        p = os.path.join(base, inc)
        if os.path.isfile(p):
            return p
    return None


def plan(path, start_c, default_c):
    """Return (edits, end_mode_is_c) or (None, reason). edits: list of (line index, 'B'|'E')
    meaning insert BEGIN/END before that line."""
    lines = rd(path).split('\n')

    def switches(i, l):
        if PRAGMA.match(l):
            return True
        m = INCLUDE.match(l)
        if m:
            p = resolve(m.group(1), path)
            return bool(p and has_pragma(p))
        return False

    # conditional blocks that contain a mode switch: their directive lines
    # end a region, so that no region starts and ends in different branches
    flagged = set()
    stack = []
    for i, l in enumerate(lines):
        m = COND.match(l)
        if m:
            k = m.group(1)
            if k in ('if', 'ifdef', 'ifndef'):
                stack.append([[i], False])
            elif stack:
                stack[-1][0].append(i)
                if k == 'endif':
                    dirs, hit = stack.pop()
                    if hit:
                        flagged.update(dirs)
                        if stack:
                            stack[-1][1] = True
        elif stack and switches(i, l):
            stack[-1][1] = True

    edits = []
    c = start_c
    open_at = 0 if c else None
    saved = []          # per flagged block: [mode at #if, [end modes of finished branches], has_else]

    def close(i):
        nonlocal open_at
        if open_at is None:
            return
        j = open_at
        open_at = None
        if all(not l.strip() or l.lstrip().startswith('//') for l in lines[j:i]):
            return
        edits.append((j, 'B'))
        edits.append((i, 'E'))

    for i, l in enumerate(lines):
        if i in flagged:
            k = COND.match(l).group(1)
            if c:
                close(i)
            if k in ('if', 'ifdef', 'ifndef'):
                saved.append([c, [], False])
            elif k in ('elif', 'else'):
                saved[-1][1].append(c)
                saved[-1][2] = saved[-1][2] or k == 'else'
                c = saved[-1][0]
            else:
                at_if, ends, has_else = saved.pop()
                ends.append(c)
                if not has_else:
                    ends.append(at_if)
                if len(set(ends)) != 1:
                    return None, 'branches of the #if ending at line %d leave different modes' % (i + 1)
            open_at = i + 1 if c else None
            continue
        m = PRAGMA.match(l)
        if m:
            new_c = {'on': False, 'off': True, 'reset': default_c}[m.group(1)]
            if c and not new_c:
                close(i)
            elif new_c and not c:
                open_at = i + 1
            c = new_c
            continue
        m = INCLUDE.match(l)
        if m and c:
            p = resolve(m.group(1), path)
            if p and has_pragma(p):
                close(i)
                sub, end_c = plan(p, True, default_c)
                if sub is None:
                    return None, 'included %s: %s' % (m.group(1), end_c)
                c = end_c
                open_at = i + 1 if c else None
    if c:
        n = len(lines)
        while n > 0 and not lines[n - 1].strip():
            n -= 1
        close(n)
    return edits, c


def apply(path, edits):
    text = rd(path)
    nl = '\r\n' if '\r\n' in text else '\n'
    lines = text.split('\n')
    cr = '\r' if nl == '\r\n' else ''
    first = min(i for i, k in edits if k == 'B')
    depth = 0
    for l in lines[:first]:
        m = COND.match(l)
        if m:
            depth += {'if': 1, 'ifdef': 1, 'ifndef': 1, 'endif': -1}.get(m.group(1), 0)
    if depth:           # the first region is inside an #if: the header goes to the top
        first = -1
    for i, k in sorted(edits, key=lambda e: (-e[0], e[1] == 'B')):
        ins = ['C_REGION_BEGIN' + cr] if k == 'B' else ['C_REGION_END' + cr]
        if k == 'B' and i == first:
            ins = [HDR + cr] + ins
        lines[i:i] = ins
    if first == -1:
        lines[0:0] = [HDR + cr]
    open(path, 'w', encoding='utf-8', errors='surrogateescape', newline='').write('\n'.join(lines))


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    check = '--check' in sys.argv
    cxx = lang_cxx_units()
    files = []
    if args:
        files = [os.path.relpath(os.path.abspath(a), ROOT) for a in args]
    else:
        for base, _, names in os.walk(os.path.join(ROOT, 'src/game')):
            for n in sorted(names):
                if n.endswith(('.c', '.cpp', '.inc')):
                    files.append(os.path.relpath(os.path.join(base, n), ROOT))
    files.sort()
    done = skipped = 0
    for f in files:
        p = os.path.join(ROOT, f)
        text = rd(p)
        if not has_pragma(p):
            continue
        if 'C_REGION_BEGIN' in text:
            continue
        # a fragment starts in the mode of the file that includes it: C for
        # every .inc that carries these pragmas today
        default_c = not (f.endswith('.cpp') or f in cxx)
        edits, info = plan(p, default_c, default_c)
        if edits is None:
            print('SKIP %s: %s' % (f, info))
            skipped += 1
            continue
        if not edits:
            continue
        if check:
            print('unmarked: %s' % f)
        else:
            apply(p, edits)
        done += 1
    print('%d files %s, %d skipped' % (done, 'need markers' if check else 'marked', skipped))


if __name__ == '__main__':
    main()
