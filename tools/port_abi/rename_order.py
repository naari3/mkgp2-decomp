#!/usr/bin/env python3
"""Targets in tools/extab_user_renames.json that are reached under parameter
lists whose float/integer order differs.

A class declared in one unit can name a constructor or member function whose
real definition lives in another unit; the rename table joins the mangled
name to the real symbol. PowerPC passes floats and integers in separate
registers, so `(float, int, float, int)` and `(int, int, float, float)` call
the same code there. Elsewhere the order matters.

usage: python3 tools/port_abi/rename_order.py [-v]
"""
import collections, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))


def params(m):
    """Mangled CodeWarrior name -> string of i/f per parameter, or None."""
    mm = re.match(r'(?:__\w+?|\w+?)__(?:Q\d)?(\d+)', m)
    if not mm: return None
    k = mm.end(1) + int(mm.group(1))
    if m[k:k + 1] == 'C': k += 1
    if m[k:k + 1] != 'F': return None
    p, out, j = m[k + 1:], '', 0
    while j < len(p):
        c = p[j]
        if c in 'CUS': j += 1; continue
        if c in 'PR':
            j += 1
            while j < len(p) and p[j] in 'PRCUS': j += 1
            if j < len(p) and p[j].isdigit():
                n = re.match(r'\d+', p[j:]).group(0); j += len(n) + int(n)
            elif j < len(p) and p[j] in 'FQA': return None     # function pointer, nested name, array
            else: j += 1
            out += 'i'; continue
        if c in 'fd': out += 'f'
        elif c in 'iclsbxw': out += 'i'
        elif c == 'v': pass
        elif c == 'e': out += 'e'
        elif c.isdigit():
            n = re.match(r'\d+', p[j:]).group(0); j += len(n) + int(n); out += 'S'; continue
        else: return None
        j += 1
    return out


def main():
    by = collections.defaultdict(lambda: collections.defaultdict(set))
    cur = None
    for l in open(os.path.join(ROOT, 'tools', 'extab_user_renames.json')):
        m = re.match(r'\s*"((?:src|libs)/[^"]+)": \{', l)
        if m: cur = m.group(1); continue
        m = re.match(r'\s*"(\w+)": "(\w+)"', l)
        if m and cur:
            sh = params(m.group(1))
            if sh is not None: by[m.group(2)][sh].add((cur, m.group(1)))
    n = 0
    for t, d in sorted(by.items()):
        keys = [k for k in d if 'f' in k]
        if len({''.join(sorted(k)) for k in keys}) < len(keys):
            n += 1
            print(t, {k: len(v) for k, v in sorted(d.items())})
            if '-v' in sys.argv:
                for k, v in sorted(d.items()):
                    for f, mg in sorted(v): print('   %-12s %s  %s' % (k, f, mg))
    print('%d targets' % n)


if __name__ == '__main__':
    main()
