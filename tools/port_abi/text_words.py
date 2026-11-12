#!/usr/bin/env python3
"""Find and rewrite array initialisers that hold text as numeric words.

A word counts as text when its four big-endian bytes are printable ASCII,
optionally followed by NUL padding. A run is two or more consecutive text
words that ends in a NUL (inside the last word, or a following 0 word) and
has at least five letters; that keeps out floats such as 0x3F333333
0x3F666666 ("?333?fff").

usage: python3 tools/port_abi/text_words.py [paths...]          list (default: src)
       python3 tools/port_abi/text_words.py --fix paths...      rewrite the runs
           as TEXT_WORD('a','b','c','d') (include/game/types/text_word.h),
           which is the same number under MWCC and the same bytes on a
           little-endian host.
       --short (first option) also takes one- and two-character full-width
           strings; use it on files known to hold text tables, after
           reading the listing (a lone word can be a number).
"""
import os, re, struct, sys

DEF = re.compile(r'^((?:__declspec\(section[ \t]*"[^"\n]*"\)[ \t]*)?(?![ \t]*")[^\n;{}()=#/]*?\b(\w+)[ \t]*(?:\[[^\]\n]*\][ \t]*)*(?:__attribute__\(\(aligned\(\d+\)\)\))?\s*=\s*\{)(.*?)(\s*\};)', re.M | re.S)
HEX = re.compile(r'^(?:\(\s*[\w \*]+\s*\)\s*)?(0x[0-9A-Fa-f]{6,8}|-?\d{7,10})[uUlL]*$')


ZERO = re.compile(r'^(?:\(\s*[\w \*]+\s*\)\s*)?(?:0x0+|0+|NULL|0\.0f?)[uUlL]*$')


def text_word(w):
    b = w.to_bytes(4, 'big')
    s = b.rstrip(b'\0')
    if not s or any((c < 0x20 and c not in (9, 10, 13)) or c > 0x7e for c in s):
        return False
    return True


def spans(body):
    """(start, end, text) of every comma-separated item; comments masked."""
    masked = re.sub(r'/\*.*?\*/', lambda m: ' ' * len(m.group(0)), body, flags=re.S)
    out, pos = [], 0
    for part in masked.split(','):
        st = part.strip()
        if st:
            a = pos + part.index(st)
            out.append((a, a + len(st), st))
        pos += len(part) + 1
    return out


def items(body):
    return [t for _, _, t in spans(body)]


LOOSE = False
SHORT = False   # --short: also one- and two-character full-width strings


def word_of(v):
    m = HEX.match(v) if v else None
    if not m: return None
    w = int(m.group(1), 0)
    if w < 0: w += 1 << 32          # negative decimal in an int array
    return w if 0 <= w <= 0xffffffff else None


def nice_float(w):
    f = struct.unpack('>f', w.to_bytes(4, 'big'))[0]
    if f != f or abs(f) > 1e9 or (f != 0 and abs(f) < 1e-6): return False
    return struct.pack('>f', float('%.4g' % f)) == w.to_bytes(4, 'big')


def valid(cur):
    """cur: [(index, word)]; is it one or more whole strings?"""
    if len(cur) < 2 and not SHORT: return False
    bs = b''.join(w.to_bytes(4, 'big') for _, w in cur).rstrip(b'\0')
    try: t = bs.decode('cp932')
    except UnicodeDecodeError: return False
    if any((ord(c) < 0x20 and c not in '\t\n\r') or c == '\x7f' for c in t): return False
    # half-width kana, private use and stray bytes: numbers that happen to decode
    if any((0x80 <= ord(c) < 0x3000 and c not in '\u00d7\u00f7\u00b0\u00b1') or 0xff61 <= ord(c) <= 0xff9f or 0xe000 <= ord(c) <= 0xf8ff for c in t): return False
    wide = all(ord(c) >= 0x80 for c in t) and len(t) >= (1 if SHORT else 3)   # only full-width text
    if sum(1 for c in t if c.isalnum()) < 5 and not wide: return False
    if not wide and any(ord(c) >= 0x80 for c in t) and len(t) < 8: return False   # short mixed: likely numbers
    if all(nice_float(w) for _, w in cur): return False
    return True


def runs(vals):
    """Runs of words that are text. A run starts at a boundary (start of the
    array, an item that is not a hex word, or a word holding a NUL byte) and
    ends at a word with trailing NULs or before a zero item."""
    out, cur, open_ = [], [], True
    for i, v in enumerate(vals + [None]):
        w = word_of(v)
        if w is None:
            if cur and ((v and ZERO.match(v)) or LOOSE) and valid(cur): out.append(cur)
            cur, open_ = [], True
            continue
        b = w.to_bytes(4, 'big')
        body = b.rstrip(b'\0')
        if not body or 0 in body:          # zero, small number, or NUL inside
            if cur and (not body or LOOSE) and valid(cur): out.append(cur)
            cur, open_ = [], True
            continue
        if not open_ and not LOOSE:
            if len(body) < 4: open_ = True  # that word ended something
            continue
        cur.append((i, w))
        if len(body) < 4:                   # terminator inside this word
            if valid(cur): out.append(cur)
            elif not LOOSE: pass
            cur, open_ = [], True
            continue
        # still inside a candidate; if it can no longer be text, close the gate
        try:
            b''.join(x.to_bytes(4, 'big') for _, x in cur).decode('cp932')
        except UnicodeDecodeError as e:
            if e.end < 4 * len(cur) - 1 and not LOOSE:   # not just a cut lead byte
                cur, open_ = [], False
    return out


def ch(c):
    if c == 0: return '0'
    if c < 0x20 and c not in (9, 10, 13) or c > 0x7e: return '0x%02X' % c
    if c in (0x27, 0x5c): return "'\\%s'" % chr(c)
    if c in (9, 10, 13): return {9: "'\\t'", 10: "'\\n'", 13: "'\\r'"}[c]
    return "'%s'" % chr(c)


def fix(path):
    s = open(path, encoding='utf-8').read()
    n = 0
    def repl(m):
        nonlocal n
        body = m.group(3)
        if '"' in body: return m.group(0)
        sp = spans(body)
        r = runs([t for _, _, t in sp])
        if not r: return m.group(0)
        edits = []
        for run in r:
            for k, (i, w) in enumerate(run):
                a, b, t = sp[i]
                hm = HEX.match(t)
                pre = t[:hm.start(1)]
                new = pre + 'TEXT_WORD(%s)' % ', '.join(ch(c) for c in w.to_bytes(4, 'big'))
                if hm.group(1).startswith('-'): new = '(int)' + new   # keeps a signed member signed
                edits.append((a, b, new))
            n += 1
        for a, b, new in sorted(edits, reverse=True):
            body = body[:a] + new + body[b:]
        return m.group(1) + body + m.group(4)
    s2 = DEF.sub(repl, s)
    if n:
        inc = '#include "game/types/text_word.h"\n'
        if inc not in s2: s2 = inc + s2
        open(path, 'w', encoding='utf-8').write(s2)
    return n


def scan(path):
    try: s = open(path, encoding='utf-8', errors='replace').read()
    except OSError: return []
    res = []
    for m in DEF.finditer(s):
        if '"' in m.group(3): continue
        vals = items(m.group(3))
        r = runs(vals)
        if r:
            res.append((m.group(2), m.group(1).strip(), len(vals), r, s.count('\n', 0, m.start()) + 1))
    return res


def main():
    global SHORT
    if sys.argv[1:2] == ['--short']:
        SHORT = True; del sys.argv[1]
    if sys.argv[1:2] == ['--fix']:
        for f in sys.argv[2:]:
            print('%s: %d runs' % (f, fix(f)))
        return
    global LOOSE
    if sys.argv[1:2] == ['--loose']:     # also runs without a terminator, for review
        LOOSE = True; del sys.argv[1]
    paths = sys.argv[1:] or ['src']
    n = 0
    for p in paths:
        fs = [p] if os.path.isfile(p) else sorted(os.path.join(d, f) for d, _, ff in os.walk(p) for f in ff if f.endswith(('.c', '.cpp', '.h', '.inc')))
        for f in fs:
            for name, head, cnt, r, line in scan(f):
                n += 1
                txt = ' | '.join(repr(b''.join(w.to_bytes(4, 'big') for _, w in run).rstrip(b'\0').decode('cp932', 'replace'))[1:-1] for run in r)
                print('%s:%d: %s  [%d items]  %s' % (f, line, head[:70], cnt, txt[:90]))
    print('%d objects' % n)


if __name__ == '__main__':
    main()
