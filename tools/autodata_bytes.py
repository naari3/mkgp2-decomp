#!/usr/bin/env python3
"""Type the objects that the data units define as byte arrays but that hold numbers.

`tools/autodata.py gen` keeps the declared type when the using unit says
`extern const unsigned char x[]`, so tables that the code reads through casts
(`*(float *)(x + 0x10)`, a struct copy out of `x + 0x3FC`) were written as bytes
in the console's order. A little-endian build then reads every number wrong.

This pass rewrites such a definition as 32-bit words and lets `autodata.py infer`
type it from the values (float / small integer columns, row structs, pools of
strings and numbers). What stays as bytes: text (ASCII / Shift-JIS), all-zero
objects, sizes that are not a multiple of 4, objects whose values fit none of the
kinds, and objects with a byte-wide access on a member that would not be `char`
(--evidence, from tools/port_abi/bytes_evidence.py).

    python3 tools/autodata_bytes.py --names FILE          # object names, for bytes_evidence.py
    python3 tools/autodata_bytes.py [--evidence PKL] [--dry] [units...]
    python3 tools/autodata_bytes.py --list                # what is still a numeric byte array, and why
"""
import argparse, glob, os, pickle, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import autodata as A

DEF = re.compile(r'(?m)^((?:static )?(?:const )?)((?:unsigned |signed )?char|unk8) (\w+)((?:\[[0-9]+\])+)( __attribute__\(\(aligned\(8\)\)\))? = \{\n(.*?)\n\};', re.S)


def objects(text):
    for m in DEF.finditer(text):
        body = re.sub(r'/\*.*?\*/', '', m.group(6), flags=re.S)
        if '"' in body or "'" in body: continue
        vals = [int(x, 0) & 0xFF for x in re.findall(r'-?0x[0-9A-Fa-f]+|-?\d+', body)]
        n = 1
        for d in re.findall(r'\d+', m.group(4)): n *= int(d)
        if len(vals) != n: continue
        yield m, bytes(vals)


def is_text(bs):
    body = bs.rstrip(b'\0')
    return bool(body) and all(texty(part) for part in body.split(b'\0') if part)


def texty(t):
    """ASCII, half-width katakana and Shift-JIS two-byte characters only"""
    i = 0
    while i < len(t):
        x = t[i]
        if 0x20 <= x < 0x7F or x in (9, 10, 13) or 0xA1 <= x <= 0xDF: i += 1; continue
        if (0x81 <= x <= 0x9F or 0xE0 <= x <= 0xEA) and i + 1 < len(t) and (0x40 <= t[i + 1] <= 0x7E or 0x80 <= t[i + 1] <= 0xFC):
            i += 2; continue
        return False
    return True


def floats_too(bs, o, end):
    ws = [int.from_bytes(bs[i:i + 4], 'big') for i in range(o, end, 4)]
    return all(w == 0 or (A.floatlike(w) and A.fmt_float(w)) for w in ws)


def text_at(bs, o, referenced, refs=()):
    """length in bytes (terminator and padding to 4 included) of a string starting at o, or 0"""
    e = bs.find(b'\0', o)
    if e < 0 or e == o: return 0
    t = bs[o:e]
    if not texty(t): return 0
    if len(t) < 3 and not referenced: return 0
    end = (e + 4) & ~3
    if any(bs[e:end]): return 0
    # the code points at a place inside: the string starts there, and what is in front is something else
    # (the last float of a table followed by a joint name, with no terminator between)
    if any(o < r < e for r in refs): return 0
    # a first word that is also a float needs the code's word that a string starts here
    w0 = int.from_bytes(bs[o:o + 4], 'big')
    if not referenced and A.floatlike(w0) and A.fmt_float(w0): return 0
    # bytes that read as text and as floats alike (`42 85 55 56 44 7A 00 00` is 66.6667, 1000.0, and
    # `3F 66 66 66 00 00 00 00` is 0.9, 0.0): floats, also when the code points there (it points at
    # float triples as well as at names)
    if floats_too(bs, o, end): return 0
    return end - o


def segments(bs, refs, copies, doubles=()):
    """-> [(kind, offset, bytes)]: 's' string, 'f' floats, 'i' small integers, 'x' bytes nobody could type.
    refs: offsets whose address the code passes on; copies: (offset, length) block copies (structs)."""
    n = len(bs)
    numeric = set()
    for o, ln in copies:
        if o is None or not ln or o % 4: continue
        t = bs[o:o + ln].rstrip(b'\0')
        if len(t) >= 3 and b'\0' not in t and texty(t) and not floats_too(bs, o, min(n, (o + ln + 3) & ~3)): continue   # a string copied as a block
        numeric.update(range(o, min(n, o + ln), 4))
    segs = []

    def add(k, o, ln):
        if segs and segs[-1][0] == k and k != 's' and segs[-1][1] + segs[-1][2] == o:
            segs[-1] = (k, segs[-1][1], segs[-1][2] + ln)
        else:
            segs.append((k, o, ln))
    o = 0
    while o < n:
        if o not in numeric:
            ln = text_at(bs, o, o in refs, refs)
            if ln and not any(x in numeric for x in range(o, o + ln, 4)):
                add('s', o, ln); o += ln; continue
        w = int.from_bytes(bs[o:o + 4], 'big')
        if o + 8 <= n and (o in doubles or (w == 0x43300000 and int.from_bytes(bs[o + 4:o + 8], 'big') in (0, 0x80000000))):
            # a double (0x4330000000000000 / ...80000000 are the int-to-float conversion constants).
            # As a struct member it must sit on a multiple of 8, else it stays bytes.
            segs.append(('d' if o % 8 == 0 else 'x', o, 8)); o += 8; continue
        if w == 0: k = segs[-1][0] if segs and segs[-1][0] in ('f', 'i') and o not in refs else 'i'
        elif w < 0x10000 or w >= 0xFFFF0000: k = 'i'
        elif A.floatlike(w) and A.fmt_float(w): k = 'f'
        else: k = 'x'
        if o in refs and segs and segs[-1][0] == k: segs.append((k, o, 4))   # a new object starts here
        else: add(k, o, 4)
        o += 4
    # a lone small integer next to untyped bytes is more likely part of them (00 00 00 01 as four bytes)
    for i, (k, o_, ln) in enumerate(segs):
        if k == 'i' and ln == 4 and ((i and segs[i - 1][0] == 'x') or (i + 1 < len(segs) and segs[i + 1][0] == 'x')):
            segs[i] = ('x', o_, ln)
    out = []
    for k, o_, ln in segs:
        if out and k == 'x' and out[-1][0] == 'x' and out[-1][1] + out[-1][2] == o_ and o_ not in refs: out[-1] = ('x', out[-1][1], out[-1][2] + ln)
        else: out.append((k, o_, ln))
    return out


def render_pool(name, quals, attr, bs, segs):
    CT = {'f': 'float', 'i': 'int'}
    mem, vals = [], []
    for k, o, ln in segs:
        if k == 's':
            mem.append('    char s_%03X[%d];' % (o, ln)); vals.append('    ' + A.D.c_string(bs[o:o + ln].rstrip(b'\0')))
        elif k == 'd':
            mem.append('    double d_%03X;' % o); vals.append('    ' + A.fmt_double(int.from_bytes(bs[o:o + 8], 'big')))
        elif k == 'x':
            mem.append('    unsigned char x_%03X[%d];' % (o, ln))
            vals.append('    { ' + ', '.join('0x%02X' % x for x in bs[o:o + ln]) + ' }')
        else:
            ws = [int.from_bytes(bs[i:i + 4], 'big') for i in range(o, o + ln, 4)]
            vs = [A.fmt_float(w) if k == 'f' else str(w if w < 0x80000000 else w - (1 << 32)) for w in ws]
            if len(ws) == 1:
                mem.append('    %s %s_%03X;' % (CT[k], k, o)); vals.append('    ' + vs[0])
            else:
                mem.append('    %s %s_%03X[%d];' % (CT[k], k, o, len(ws))); vals.append('    { ' + ', '.join(vs) + ' }')
    tn = name + '_Pool'
    typ = ('/* was a byte array; cut into strings, floats and small integers by value and by how the code\n'
           ' * reaches it (address taken: a new member; block copy: numbers). x_ members are bytes that fit\n'
           ' * none of these and are still in the console\'s byte order if they are wider than a byte. */\n'
           'typedef struct %s {\n%s\n} %s;' % (tn, '\n'.join(mem), tn))
    return typ, '%s%s %s%s = {\n%s\n};' % (quals, tn, name, attr, ',\n'.join(vals))


def plan(bs, refs=(), copies=(), doubles=()):
    """-> (reason it stays, None, None) or (None, per-word kinds, segments or None for a row table)"""
    if not any(bs): return 'all zero', None, None
    if len(bs) % 4: return ('text' if is_text(bs) else 'size not a multiple of 4'), None, None
    words = [int.from_bytes(bs[i:i + 4], 'big') for i in range(0, len(bs), 4)]
    r = A.infer_rows(words) if len(words) >= 2 else None
    if len(words) == 1:
        k = A.column_kind(words)
        r = (1, [k]) if k in ('f', 'i') else None
    if r is not None and r[0] == 1 and r[1][0] == 'b': r = None
    numeric = r is not None and all(k in ('f', 'i') for k in r[1])
    if is_text(bs) and not (numeric and any(k == 'f' for k in r[1])): return 'text', None, None
    if A.text_pool(words) is not None: return 'text', None, None
    has_double = bool(doubles) or any(words[i] == 0x43300000 and words[i + 1] in (0, 0x80000000) for i in range(len(words) - 1))
    if len(bs) == 8 and has_double: return None, ['d', 'd'], [('d', 0, 8)]
    if r is not None and not refs and not has_double:
        p, kinds = r
        return None, [kinds[i % p] for i in range(len(words))], None
    segs = segments(bs, set(refs), copies, set(doubles))
    if not any(k in ('f', 'i', 'd') for k, _, _ in segs): return 'values fit no kind', None, None
    kinds = [None] * len(words)
    for k, o, ln in segs:
        for i in range(o // 4, (o + ln) // 4): kinds[i] = k
    return None, kinds, segs


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('units', nargs='*'); ap.add_argument('--names'); ap.add_argument('--evidence')
    ap.add_argument('--dry', action='store_true'); ap.add_argument('--list', action='store_true')
    ap.add_argument('--only', help='file with object names to convert (others are left)')
    a = ap.parse_args()
    files = [os.path.join(A.OUTDIR, os.path.basename(u) if u.endswith('.c') else os.path.basename(u) + '.c') for u in a.units] \
        or sorted(glob.glob(os.path.join(A.OUTDIR, '*.c')))
    ev = pickle.load(open(a.evidence, 'rb'))['evidence'] if a.evidence else {}
    only = set(open(a.only).read().split()) if a.only else None
    names, done, kept = [], 0, {}
    for f in files:
        text = open(f, encoding='utf-8').read()
        changed = []
        types = []

        def repl(m, bs):
            nonlocal done
            name = m.group(3)
            names.append(name)
            refs = sorted(set(e[3] for e in ev.get(name, ()) if e[1] == 'other' and e[3] is not None and e[3] % 4 == 0 and 0 < e[3] < len(bs)))
            copies = [(e[3], e[2]) for e in ev.get(name, ()) if e[1] == 'copy']
            doubles = [e[3] for e in ev.get(name, ()) if e[1] == 'load' and e[2] in ('i64', 'double') and e[3] is not None]
            why, kinds, segs = plan(bs, refs, copies, doubles)
            if why is None:
                for e in ev.get(name, ()):
                    if e[1] in ('load', 'store') and e[3] is not None and 0 <= e[3] < len(bs):
                        k = kinds[e[3] // 4]
                        want = {'i8': 's', 'i16': 's', 'float': 'f', 'i32': 'fi'}.get(e[2], '')
                        if e[2] == 'i8' and k not in ('s', 'x'): why = 'byte access at +0x%X (%s) on a %s member' % (e[3], e[0], k)
                        if e[2] == 'i16' and k not in ('s',): why = '16-bit access at +0x%X (%s)' % (e[3], e[0])
                        if e[2] == 'float' and k not in ('f', 'i'): why = 'float access at +0x%X on a %s member' % (e[3], k)
            if why is None and only is not None and name not in only: why = 'not selected'
            if why is not None:
                if why not in ('text', 'all zero'): kept[name] = (os.path.basename(f), len(bs), why)
                return m.group(0)
            done += len(bs); changed.append(name)
            if segs == [('d', 0, 8)]:
                return '/* a double (int-to-float conversion constant or read as one) */\n%sdouble %s[1]%s = {\n    %s\n};' % (
                    m.group(1), name, m.group(5) or '', A.fmt_double(int.from_bytes(bs, 'big')))
            if segs is not None:
                typ, text_ = render_pool(name, m.group(1), m.group(5) or '', bs, segs)
                types.append(typ)
                return text_
            if len(bs) == 4:   # one word: infer needs two
                w = int.from_bytes(bs, 'big')
                if kinds[0] == 'f':
                    return '/* element type read off the value (a float), not from code */\n%sfloat %s[1]%s = {\n    %s\n};' % (
                        m.group(1), name, m.group(5) or '', A.fmt_float(w))
                return '/* element type read off the value (a small integer), not from code */\n%sint %s[1]%s = {\n    %d\n};' % (
                    m.group(1), name, m.group(5) or '', w if w < 0x80000000 else w - (1 << 32))
            words = ['0x%08X' % int.from_bytes(bs[i:i + 4], 'big') for i in range(0, len(bs), 4)]
            return '%sunk32 %s[%d]%s = {\n%s\n};' % (m.group(1), name, len(words), m.group(5) or '', A.wrap(words))
        ms = list(objects(text))
        new = text
        for m, bs in reversed(ms):
            new = new[:m.start()] + repl(m, bs) + new[m.end():]
        if new != text and not a.dry and not a.list and not a.names:
            if '#include "game/autodata.h"' not in new: print('no autodata.h include in', f)
            if types:
                prag = '\n#pragma explicit_zero_data on'
                i = new.index(prag)
                new = new[:i].rstrip('\n') + '\n\n' + '\n\n'.join(reversed(types)) + '\n' + new[i:]
            open(f, 'w', encoding='utf-8').write(new)
            A.cmd_infer(argparse.Namespace(units=[os.path.basename(f)], raw=False, min_words=1))
            left = [n for n in changed if re.search(r'unk32 %s\[' % n, open(f, encoding='utf-8').read())]
            if left: print('  still unk32 after infer (check):', ' '.join(left))
    if a.names:
        open(a.names, 'w').write('\n'.join(names) + '\n'); return
    if a.list or a.dry:
        for n, (f, size, why) in sorted(kept.items(), key=lambda x: -x[1][1]): print('%-48s %5d  %-22s %s' % (n, size, f, why))
    print('%d bytes %s; %d numeric-looking objects stay bytes (%d bytes)' % (
        done, 'would be typed' if (a.dry or a.list) else 'typed', len(kept), sum(v[1] for v in kept.values())))


if __name__ == '__main__':
    main()
