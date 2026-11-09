#!/usr/bin/env python3
"""Detect printf-style calls whose argument count does not match the format string in the DOL
(rule debug-format-arg-count, regalloc_patterns 49: DetermineTitle matched after passing every
argument "Fixed TitleID loop No : %d, id : %d" names; a missing vararg moves the values the
target computes into r5/r6 back into r3).

The format is resolved from a string literal, a `lbl_XXXXXXXX` symbol, or `base + 0xNN` where
base is a symbol or a local initialised with one (`char *pool = lbl_8030E598;`); the bytes come
from orig/GNLJ82/sys/main.dol. Only functions declared with `...` somewhere in src/ or include/
are checked.

Usage: python3 tools/fmt_args_detect.py [--all] [--md docs/sweeps/fmt_args.md]
  default: only calls inside near-miss functions (< 100% in build/GNLJ82/report.json)
"""
import argparse, json, os, re, struct, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'tools'))
import pragmasweep as ps  # noqa: E402

SPEC = re.compile(r'%(?:%|[-+ #0]*(\*|\d+)?(?:\.(\*|\d+))?(?:hh|h|ll|l|L)?[diouxXcsfeEgGpn])')


class Dol:
    def __init__(self, path):
        self.d = open(path, 'rb').read()
        offs = struct.unpack('>18I', self.d[0:0x48])
        addrs = struct.unpack('>18I', self.d[0x48:0x90])
        sizes = struct.unpack('>18I', self.d[0x90:0xD8])
        self.secs = [(a, o, s) for a, o, s in zip(addrs, offs, sizes) if s]

    def cstr(self, addr, limit=400):
        for a, o, s in self.secs:
            if a <= addr < a + s:
                b = self.d[o + addr - a:o + addr - a + limit]
                return b.split(b'\0', 1)[0].decode('latin-1')
        return None


def count_args(fmt):
    n = 0
    for m in SPEC.finditer(fmt):
        if m.group(0) == '%%':
            continue
        n += 1 + (m.group(1) == '*') + (m.group(2) == '*')
    return n


def strip_comments(s):
    return re.sub(r'/\*.*?\*/|//[^\n]*', lambda m: ' ' * len(m.group(0)) if '\n' not in m.group(0)
                  else re.sub(r'[^\n]', ' ', m.group(0)), s, flags=re.S)


def split_args(s):
    out, d, cur, q = [], 0, '', None
    i = 0
    while i < len(s):
        ch = s[i]
        if q:
            cur += ch
            if ch == '\\':
                cur += s[i + 1]
                i += 1
            elif ch == q:
                q = None
        elif ch in '"\'':
            q = ch
            cur += ch
        elif ch in '([{':
            d += 1
            cur += ch
        elif ch in ')]}':
            d -= 1
            cur += ch
        elif ch == ',' and d == 0:
            out.append(cur.strip())
            cur = ''
        else:
            cur += ch
        i += 1
    if cur.strip():
        out.append(cur.strip())
    return out


def close_paren(s, i):
    d, q = 0, None
    for j in range(i, len(s)):
        ch = s[j]
        if q:
            if ch == '\\':
                continue
            if ch == q and s[j - 1] != '\\':
                q = None
        elif ch in '"\'':
            q = ch
        elif ch == '(':
            d += 1
        elif ch == ')':
            d -= 1
            if d == 0:
                return j
    return -1


def unescape(lit):
    try:
        return bytes(lit, 'latin-1').decode('unicode_escape')
    except Exception:
        return lit


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--all', action='store_true')
    ap.add_argument('--md')
    a = ap.parse_args()
    dol = Dol(ROOT / 'orig/GNLJ82/sys/main.dol')
    syms = {}
    for l in open(ROOT / 'config/GNLJ82/symbols.txt'):
        m = re.match(r'(\S+) = \.\w+:0x([0-9A-F]+);', l)
        if m:
            syms[m.group(1)] = int(m.group(2), 16)
    # varargs functions
    va = set()
    for base in ('src', 'include'):
        for dp, _, fs in os.walk(ROOT / base):
            for f in fs:
                if f.endswith(('.c', '.cpp', '.h', '.hpp', '.inc')):
                    try:
                        t = open(os.path.join(dp, f), encoding='latin-1').read()
                    except OSError:
                        continue
                    for m in re.finditer(r'\b([A-Za-z_]\w*)\s*\([^;{}()]*\.\.\.\s*\)', t):
                        va.add(re.sub(r'_p\d+$', '', m.group(1)))
    rep = json.load(open(ROOT / 'build/GNLJ82/report.json'))
    rows = []
    for u in rep['units']:
        name = u['name'].split('/', 1)[1]
        near = {f['name']: f.get('fuzzy_match_percent', 0) for f in u.get('functions', [])
                if f.get('fuzzy_match_percent', 0) < 100}
        if not near and not a.all:
            continue
        src = next((ROOT / 'src' / (name + e) for e in ('.c', '.cpp') if (ROOT / 'src' / (name + e)).exists()), None)
        if not src:
            continue
        text = strip_comments(src.read_text(encoding='latin-1'))
        spans = []
        for fn, pct in near.items():
            d = ps.find_def(text, fn, None, fn)
            if d:
                spans.append((d[1], d[2], fn, pct))
        locals_ = {m.group(1): m.group(2) for m in
                   re.finditer(r'\b(\w+)\s*=\s*(?:\([^()]*\)\s*)?&?\s*(?:\(\*\([^;]*?\)&)?(\w+?)(?:_p\d+)?\)?\s*;', text)
                   if re.sub(r'_p\d+$', '', m.group(2)) in syms}

        def resolve(arg):
            lits = re.findall(r'"((?:\\.|[^"\\])*)"', arg)
            if lits and re.fullmatch(r'\s*(?:\([^()]*\)\s*)?(?:"(?:\\.|[^"\\])*"\s*)+', arg):
                return unescape(''.join(lits))
            m = re.fullmatch(r'(?:\([^()]*\)\s*)*\(?\s*&?\s*(\w+?)(?:_p\d+)?\s*(?:\+\s*(0x[0-9A-Fa-f]+|\d+))?\s*\)?', arg)
            if not m:
                return None
            base, off = m.group(1), int(m.group(2) or '0', 0)
            base = locals_.get(base, locals_.get(base + '', base))
            base = re.sub(r'_p\d+$', '', base)
            if base not in syms:
                return None
            return dol.cstr(syms[base] + off)

        for m in re.finditer(r'\b([A-Za-z_]\w*)\s*\(', text):
            callee = re.sub(r'_p\d+$', '', m.group(1))
            if callee not in va:
                continue
            o = m.end() - 1
            c = close_paren(text, o)
            if c < 0:
                continue
            # skip declarations / definitions
            tail = text[c + 1:c + 40].lstrip()
            if '...' in text[o:c] or tail.startswith('{'):
                continue
            args = split_args(text[o + 1:c])
            for i, arg in enumerate(args):
                fmt = resolve(arg)
                if fmt is None or '%' not in fmt:
                    continue
                want, got = count_args(fmt), len(args) - i - 1
                if want != got:
                    inside = next(((fn, pct) for s0, s1, fn, pct in spans if s0 <= m.start() < s1), None)
                    if inside or a.all:
                        line = text.count('\n', 0, m.start()) + 1
                        rows.append((name, src.suffix, line, inside, callee, fmt, want, got))
                break
    out = ['# printf-style calls whose argument count differs from the format string', '',
           f'{len(rows)} calls. Generated by tools/fmt_args_detect.py (rule debug-format-arg-count, regalloc_patterns 49).',
           'Pass one argument per conversion: a missing vararg changes which register the value before the call is computed in.',
           '', '| function | % | file:line | call | format (DOL) | conversions | args passed |', '|---|---|---|---|---|---|---|']
    for name, ext, line, inside, callee, fmt, want, got in sorted(rows, key=lambda r: (r[3] is None, r[0], r[2])):
        fn, pct = inside if inside else ('(matched function)', 100.0)
        f = fmt.replace('|', '\\|').replace('\n', '\\n')[:90]
        out.append(f'| `{fn}` | {pct:.2f} | src/{name}{ext}:{line} | {callee} | `{f}` | {want} | {got} |')
    text = '\n'.join(out) + '\n'
    if a.md:
        Path(a.md).write_text(text)
        print(f'{len(rows)} calls -> {a.md}')
    else:
        print(text)


if __name__ == '__main__':
    main()
