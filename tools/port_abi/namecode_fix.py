#!/usr/bin/env python3
"""Retype the card-name check's patterns as arrays of 16-bit character codes.

NameCheck_ScanBannedWords holds a name as NameCode (unsigned short) values,
one Shift-JIS character each, and searches it with strstr/strcmp. That works
only when the patterns have the same layout as the name, i.e. are NameCode
arrays too. They were typed as byte arrays, strings and 32-bit words.

One-off (run 2026-11-10); kept as the record of what was changed and how.
"""
import ast, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
MAIN = os.path.join(ROOT, 'src/game/NameCheck_CardName.c')
SD2 = os.path.join(ROOT, 'src/game/autodata/sdata2_806D3060.c')
TABLES = os.path.join(ROOT, 'src/game/autodata/data_8040E450.c')
EXTRA = ['lbl_806D4740', 'lbl_806D4754', 'lbl_806D4758']

DEF = re.compile(r'((?:/\* [^\n]*? \*/\n)*)^((?:extern "C" )?const (?:unsigned int|char|unsigned char|int|short|unsigned short) )(\w+)((?:\[\d*\])?)( = )(\{.*?\}|"(?:\\.|[^"\\])*"|0x[0-9A-Fa-f]+|-?\d+);', re.M | re.S)


def tw(m):
    b = [int(x, 0) if not x.strip().startswith("'") else ord(ast.literal_eval(x.strip())) for x in m.group(1).split(',')]
    return '0x%02X%02X%02X%02X' % tuple(b)


def data(typ, dims, init):
    width = 4 if 'int' in typ else 2 if 'short' in typ else 1
    if init.startswith('"'):
        b = ast.literal_eval('b' + init)
        n = int(dims[1:-1]) if dims[1:-1] else len(b) + 1
        return b + b'\0' * (n - len(b))
    if init.startswith('{'):
        body = re.sub(r'TEXT_WORD\(([^)]*)\)', tw, init[1:-1])
        vals = [int(x, 0) for x in body.replace('\n', ' ').split(',') if x.strip()]
    else:
        vals = [int(init, 0)]
    out = b''.join((v & ((1 << 8 * width) - 1)).to_bytes(width, 'big') for v in vals)
    if dims[1:-1]: out += b'\0' * (int(dims[1:-1]) * width - len(out))
    return out


def convert(path, names, typ_out):
    s = open(path, encoding='utf-8').read()
    done = set()
    def repl(m):
        name = m.group(3)
        if name not in names: return m.group(0)
        b = data(m.group(2), m.group(4), m.group(6))
        assert len(b) % 2 == 0, name
        codes = [int.from_bytes(b[i:i + 2], 'big') for i in range(0, len(b), 2)]
        try: text = b.rstrip(b'\0').decode('cp932')
        except UnicodeDecodeError: text = None
        done.add(name)
        pre = m.group(2).split('const')[0]
        note = ''.join(l + '\n' for l in m.group(1).split('\n') if l and 'Shift-JIS text' not in l and 'decl:' not in l)
        return '%s%sconst %s %s[%d] = { %s };' % (note, pre, typ_out, name, len(codes), ', '.join('0x%04X' % c if c else '0' for c in codes))
    s2 = DEF.sub(repl, s)
    open(path, 'w', encoding='utf-8').write(s2)
    return done


def main():
    s = open(MAIN, encoding='utf-8').read()
    i = s.index('static const char *const sBannedWords[1067] = {'); j = s.index('};', i)
    words = re.findall(r'\(const char \*\)(\w+)', s[i:j])
    t = open(TABLES, encoding='utf-8').read()
    a = t.index('NameDelimiterPair NameCheck_ScanBannedWords_data_8040E450[12]')
    b = t.index('};', t.index('NameCheck_ScanBannedWords_data_8040E4B0[5]'))
    delim = re.findall(r'&(lbl_\w+)', t[a:b])
    names = set(words) | set(delim) | set(EXTRA)
    d1 = convert(MAIN, names, 'unsigned short')
    d2 = convert(SD2, names, 'unsigned short')
    print('%d names: %d in NameCheck_CardName.c, %d in sdata2_806D3060.c, missing %s' % (
        len(names), len(d1), len(d2), sorted(names - d1 - d2)[:10]))


if __name__ == '__main__':
    main()
