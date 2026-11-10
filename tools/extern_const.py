#!/usr/bin/env python3
"""Give file-scope `const` definitions an explicit `extern`.

    const T name = {...};   ->   extern const T name = {...};

In C a file-scope const object has external linkage; in C++ it is internal
unless declared extern. MWCC emits the same object either way, but units that
are compiled as C++ on another compiler (most of src/game for the PC port)
lose the definition, and every other unit that refers to the name fails to
link. With the explicit `extern` both languages agree.

    python3 tools/extern_const.py --check [paths]   # list definitions lacking it
    python3 tools/extern_const.py [paths]           # rewrite in place

Only column-0 definitions with an initializer are touched (a declaration
without one would turn into a pure declaration), and only in .c units that are
compiled as C++ at least in part: those configure.py compiles with -lang=c++
and those with `#pragma cplusplus on`. Real .cpp files are left alone: there
MWCC already treats the const as internal. Pass --all to cover
plain C units as well (harmless, but a large diff).
"""
import os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
START = re.compile(rb'^const\s+[A-Za-z_]')


def process(data):
    lines = data.split(b'\n')
    hits = []
    depth = 0          # brace depth, so struct members / function bodies are skipped
    in_block_comment = False
    for i, line in enumerate(lines):
        code = line
        if in_block_comment:
            end = code.find(b'*/')
            if end < 0:
                continue
            code = code[end + 2:]
            in_block_comment = False
        code = re.sub(rb'/\*.*?\*/', b'', code)
        code = re.sub(rb'"(\\.|[^"\\])*"', b'""', code)
        code = re.sub(rb"'(\\.|[^'\\])*'", b"''", code)
        code = code.split(b'//')[0]
        start = code.find(b'/*')
        if start >= 0:
            code = code[:start]
            in_block_comment = True
        if depth == 0 and START.match(line) and code is not None:
            # statement text up to the first of = ; ( {
            text = b' '.join([code] + lines[i + 1:i + 6])
            m = re.search(rb'[=;({]', text)
            if m and m.group() == b'=':
                hits.append(i)
        depth += code.count(b'{') - code.count(b'}')
        if depth < 0:
            depth = 0
    return lines, hits


def cxx_units():
    """.c files that configure.py compiles with -lang=c++"""
    out = set()
    for m in re.finditer(r'Object\([^\n]*?"([^"]+\.c)"[^\n]*-lang[= ]c\+\+', open(os.path.join(ROOT, 'configure.py')).read()):
        out.add(os.path.join(ROOT, 'src', m.group(1)))
    return out


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    check = '--check' in sys.argv
    paths = args or [os.path.join(ROOT, 'src')]
    every = '--all' in sys.argv
    flagged = cxx_units()
    total = 0
    for p in paths:
        files = [p] if os.path.isfile(p) else [
            os.path.join(d, f) for d, _, fs in os.walk(p) for f in fs
            if f.endswith(('.c', '.cpp', '.inc', '.cp'))]
        for f in sorted(files):
            data = open(f, 'rb').read()
            if not every and f.endswith('.c') and f not in flagged \
                    and not re.search(rb'#\s*pragma\s+cplusplus\s+on', data):
                continue
            if f.endswith(('.cpp', '.cp')) or (not every and f.endswith('.inc')):
                continue    # real C++: the const is internal under MWCC as well
            lines, hits = process(data)
            if not hits:
                continue
            total += len(hits)
            if check:
                for i in hits:
                    print('%s:%d: %s' % (os.path.relpath(f, ROOT), i + 1,
                                         lines[i][:80].decode('latin-1')))
            else:
                for i in hits:
                    lines[i] = b'extern ' + lines[i]
                open(f, 'wb').write(b'\n'.join(lines))
    print('%d definition(s)%s' % (total, ' lack extern' if check else ' rewritten'), file=sys.stderr)
    return 1 if check and total else 0


if __name__ == '__main__':
    sys.exit(main())
