#!/usr/bin/env python3
"""Declare runs of bit-fields through the BITFIELDSn macros.

MWCC for PowerPC allocates bit-fields from the most significant bit, x86
compilers from the least significant. include/game/types/bitfields.h has
macros that declare the members of one storage unit in source order under
MWCC and in reverse order elsewhere. This tool rewrites direct declarations:

    unsigned char local:1, reserved:6;      BITFIELDS3(unsigned char local:1,
    unsigned char dirty:1;              ->      unsigned char reserved:6, unsigned char dirty:1)

    python3 tools/bitfield_runs.py --check [paths]   # list bit-fields still declared directly
    python3 tools/bitfield_runs.py [paths]           # rewrite in place

A run of adjacent bit-field declarations is cut into storage units (8, 16 or
32 bits by the declared type; a member that does not fit, or has a type of
another size, starts a new unit). A unit the members do not fill gets the
_PAD form with the unnamed rest as first argument. Under MWCC the macros
expand to the old tokens, so objects do not change.
"""
import os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INCLUDE = '#include "game/types/bitfields.h"'
SIZES = {'char': 8, 'short': 16, 'int': 32, 'long': 32,
         'u8': 8, 's8': 8, 'u16': 16, 's16': 16, 'u32': 32, 's32': 32,
         'uchar': 8, 'ushort': 16, 'uint': 32, 'BOOL': 32, 'bool': 8}
TYPE = r'(?:(?:unsigned|signed|const|volatile)\s+)*(?:char|short|int|long|u8|s8|u16|s16|u32|s32|uchar|ushort|uint|unsigned|signed)(?:\s+int)?'
DECL = r'\w*\s*:\s*\d+'
STMT = re.compile(r'(?P<type>%s)\s+(?P<decls>%s(?:\s*,\s*%s)*)\s*;' % (TYPE, DECL, DECL))
GAP = re.compile(r'(?:\s|/\*.*?\*/|//[^\n]*)*', re.S)


def type_bits(t):
    words = t.split()
    for w in reversed(words):
        if w in SIZES:
            return SIZES[w]
    return 32      # bare unsigned / signed


def find_runs(text):
    """-> [(start, end, [(type, name, width)], [comments])]"""
    runs = []
    pos = 0
    while True:
        m = STMT.search(text, pos)
        if not m:
            break
        # must start a statement: previous significant char is { ; } or )
        k = m.start() - 1
        while k >= 0 and text[k] in ' \t\r\n':
            k -= 1
        prev_ok = k < 0 or text[k] in '{;}/' or text[k] == ')'
        line_start = text.rfind('\n', 0, m.start()) + 1
        if not prev_ok or text[line_start:m.start()].lstrip().startswith(('#', '//', '*')) \
                or re.match(r'\s*(case|default|return)\b', text[line_start:m.end()]) \
                or '?' in text[line_start:m.start()]:
            pos = m.end()
            continue
        members, comments = [], []
        start = m.start()
        end = m.end()
        cur = m
        while True:
            for d in cur.group('decls').split(','):
                name, width = d.split(':')
                members.append((' '.join(cur.group('type').split()), name.strip(), int(width)))
            end = cur.end()
            g = GAP.match(text, end)
            nxt = STMT.match(text, g.end())
            if not nxt:
                break
            comments += re.findall(r'/\*.*?\*/|//[^\n]*', text[end:g.end()], re.S)
            cur = nxt
        runs.append((start, end, members, comments))
        pos = end
    return runs


def units(members):
    out, cur, used, size = [], [], 0, 0
    for t, n, w in members:
        b = type_bits(t)
        if cur and (b != size or used + w > size or w == 0):
            out.append((cur, size - used, size))
            cur, used = [], 0
        size = b
        if w == 0:
            continue
        cur.append((t, n, w))
        used += w
        if used == size:
            out.append((cur, 0, size))
            cur, used = [], 0
    if cur:
        out.append((cur, size - used, size))
    return out


def render(members, indent):
    lines = []
    for mem, rest, size in units(members):
        for i in range(0, len(mem), 8):
            part = mem[i:i + 8]
            last = i + 8 >= len(mem)
            args = ['%s %s:%d' % (t, n, w) if n else '%s :%d' % (t, w) for t, n, w in part]
            if rest and last:
                if len(part) == 8:      # no BITFIELDS8_PAD: split off the last member
                    lines.append('BITFIELDS7(%s)' % ', '.join(args[:7]))
                    args = args[7:]
                    part = part[7:]
                lines.append('BITFIELDS%d_PAD(%s :%d, %s)' % (len(part), part[-1][0], rest, ', '.join(args)))
            else:
                lines.append('BITFIELDS%d(%s)' % (len(part), ', '.join(args)))
    # more than 8 members in one unit: the parts are reversed one by one off
    # MWCC, so they must be emitted last part first there; keep it simple
    return ('\n' + indent).join(lines)


def process(path, check):
    raw = open(path, 'rb').read()
    nl = '\r\n' if b'\r\n' in raw else '\n'
    text = raw.decode('latin-1').replace('\r\n', '\n')
    runs = find_runs(text)
    if not runs:
        return 0
    n = sum(len(r[2]) for r in runs)
    if check:
        for start, end, members, _ in runs:
            print('%s:%d: %s' % (os.path.relpath(path, ROOT), text.count('\n', 0, start) + 1,
                                 ', '.join('%s:%d' % (m[1], m[2]) for m in members)))
        return n
    for start, end, members, comments in reversed(runs):
        for mem, rest, size in units(members):
            if len(mem) > 8:
                sys.exit('%s: more than 8 bit-fields in one storage unit (%s...), do this one by hand' % (path, mem[0][1]))
        line_start = text.rfind('\n', 0, start) + 1
        indent = re.match(r'[ \t]*', text[line_start:]).group()
        new = render(members, indent)
        if comments:
            new += ' ' + ' '.join(c if c.startswith('/*') else '/* %s */' % c[2:].strip() for c in comments)
        text = text[:start] + new + text[end:]
    if INCLUDE not in text:
        lines = text.split('\n')
        at = 0      # top of the file, or right after a header's include guard
        for i, l in enumerate(lines[:40]):
            if l.startswith('#define') and i and lines[i - 1].startswith('#ifndef'):
                at = i + 1
                break
            if l.startswith('#'):
                break
        lines.insert(at, INCLUDE)
        text = '\n'.join(lines)
    open(path, 'wb').write(text.replace('\n', nl).encode('latin-1'))
    return n


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    check = '--check' in sys.argv
    paths = args or [os.path.join(ROOT, 'src', 'game'), os.path.join(ROOT, 'include', 'game'),
                     os.path.join(ROOT, 'src', 'triforce'), os.path.join(ROOT, 'include', 'triforce'),
                     os.path.join(ROOT, 'src', 'sound'), os.path.join(ROOT, 'src', 'ui'),
                     os.path.join(ROOT, 'src', 'util'), os.path.join(ROOT, 'src', 'resource')]
    total = files = 0
    for p in paths:
        fl = [p] if os.path.isfile(p) else [
            os.path.join(d, f) for d, _, fs in os.walk(p) for f in fs
            if f.endswith(('.c', '.cpp', '.cp', '.inc', '.h', '.hpp')) and f != 'bitfields.h']
        for f in sorted(fl):
            k = process(f, check)
            total += k
            files += bool(k)
    print('%d bit-field member(s) in %d file(s)%s' % (total, files, ' declared directly' if check else ' rewritten'), file=sys.stderr)
    return 1 if check and total else 0


if __name__ == '__main__':
    sys.exit(main())
