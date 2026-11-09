#!/usr/bin/env python3
"""Merge a run of over-split C TUs back into one TU (one source file).

Why: a function whose target reaches several data objects off ONE base
register (MWCC section anchor, regalloc_patterns 13 / matching_rules 6,
docs/reports/pool_audit.md) can only match when the objects and the function
are in the same TU. When the original TU was split into per-function files,
every file between the function and the data owner has to go back into one
TU. By hand (docs/wip/clsound_merge, 19 TUs) that took hours; this script does
the mechanical part.

    python3 tools/merge_tus.py plan  --first 0x801A1798 --last 0x801B6C94
    python3 tools/merge_tus.py apply --first 0x801A1798 --last 0x801B6C94 \
        [--into game/sprite/fn_801A1798.c] [--pool pool.c --pool-sec .data:LO:HI]
    ninja; python3 tools/merge_tus.py prune-renames --tu game/sprite/fn_801A1798.c

`first`/`last` are the .text start addresses of the first and last TU
(config/GNLJ82/splits.txt). C TUs only, and all must share the same flags
apart from -Cpp_exceptions and -use_lmw_stmw (those become pragmas).

How the sections stay byte-identical: each TU is run through its own compile
command with -E, and every identifier of that preprocessed text gets a `_pN`
suffix except C keywords, `__` builtins, `#pragma` lines and the TU's own
global function definitions. So headers that disagree between TUs no longer
clash, every call to another TU's function stays a call to an outside symbol
(no auto-inlining of a function the merged file defined earlier), and
tools/extab_user_renames.json maps the suffixed symbols back after compiling
(`prune-renames` drops the entries that did not become symbols).

`--pool FILE`: C definitions put at the top (tools/data2c.py output; made
`static`, which MWCC needs before it addresses them off a section anchor).
A section's `extern T NAME[dims];` of a pool object is dropped and every use
of NAME becomes `(*(T (*)[dims])&NAME)`, the object read with the type that
section declared.

`apply` also rewrites config/GNLJ82/splits.txt (one block; each section's
ranges must be contiguous; `--pool-sec` adds the pool's range), configure.py
(one NonMatching Object with -Cpp_exceptions on), tools/extab_order.json (the
target extabindex order read from the split objects) and `git rm`s the
merged-away sources. The result is generated text: rewrite by hand only the
sections you need to work on.
Undo: `git checkout -- . && git reset -q HEAD -- src && git checkout -- src`.
"""
from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SPLITS = ROOT / 'config/GNLJ82/splits.txt'
CONFIGURE = ROOT / 'configure.py'
RENAMES = ROOT / 'tools/extab_user_renames.json'
ORDER = ROOT / 'tools/extab_order.json'
OBJDUMP = ROOT / 'build/binutils/powerpc-eabi-objdump'
NM = ROOT / 'build/binutils/powerpc-eabi-nm'
CANON = ['extab', 'extabindex', '.text', '.ctors', '.dtors', '.rodata', '.data', '.bss',
         '.sdata', '.sbss', '.sdata2', '.sbss2']


def read_blocks():
    text = SPLITS.read_text()
    blocks = []
    for m in re.finditer(r'^(\S[^\n]*):\n((?:\t[^\n]*\n)*)', text, re.M):
        secs = []
        for l in m.group(2).splitlines():
            mm = re.match(r'\t(\S+)\s+start:0x([0-9A-Fa-f]+) end:0x([0-9A-Fa-f]+)(.*)$', l)
            if mm:
                secs.append((mm.group(1), int(mm.group(2), 16), int(mm.group(3), 16), mm.group(4)))
        blocks.append(dict(name=m.group(1), secs=secs, span=(m.start(), m.end())))
    return text, blocks


def text_start(b):
    return next((s[1] for s in b['secs'] if s[0] == '.text'), None)


def select(blocks, first, last):
    tus = sorted((b for b in blocks if text_start(b) is not None and first <= text_start(b) <= last), key=text_start)
    if not tus or text_start(tus[0]) != first or text_start(tus[-1]) != last:
        sys.exit('first/last must be .text start addresses of TUs')
    return tus


def object_line(cfg, name):
    m = re.search(r'^([ \t]*)Object\((\w+), "%s"(.*)\),?[ \t]*$' % re.escape(name), cfg, re.M)
    if not m:
        sys.exit(f'{name}: no Object() in configure.py')
    return m, re.findall(r'"(-[^"]*)"', m.group(3))


def plan(a):
    _, blocks = read_blocks()
    cfg = CONFIGURE.read_text()
    for b in select(blocks, a.first, a.last):
        m, flags = object_line(cfg, b['name'])
        other = [f'{s[0]} {s[1]:#x}..{s[2]:#x}' for s in b['secs'] if s[0] not in ('.text', 'extab', 'extabindex')]
        print(f"{text_start(b):#x} {b['name']:50} {m.group(2):12} {' '.join(flags):40} {' '.join(other)}")


C_KEYWORDS = set('''auto break case char const continue default do double else enum extern float for goto if
inline int long register restrict return short signed sizeof static struct switch typedef union unsigned void
volatile while asm _Bool defined'''.split())

TOKEN = re.compile(r'''
    (?P<str>"(?:\\.|[^"\\\n])*") |
    (?P<chr>'(?:\\.|[^'\\\n])*') |
    (?P<num>\.?\d(?:[eEpP][+-]|[\w.])*) |
    (?P<id>[A-Za-z_]\w*) |
    (?P<ws>\s+) |
    (?P<op>.)''', re.X | re.S)


def preprocess(name):
    """The TU's own compile command with -E: the text the compiler saw."""
    cmd = subprocess.run(['ninja', '-t', 'commands', f'build/GNLJ82/src/{Path(name).with_suffix("")}.o'],
                         cwd=ROOT, capture_output=True, text=True).stdout.strip().splitlines()[-1]
    cmd = re.sub(r' -o \S+', '', cmd.split(' && ')[0].replace(' -MMD', '')).replace(' -c ', ' -E ')
    r = subprocess.run(cmd, shell=True, cwd=ROOT, capture_output=True)
    if r.returncode:
        sys.exit(f'{name}: preprocessing failed\n' + r.stderr.decode('latin-1')[-2000:])
    text = r.stdout.decode('latin-1')
    return '\n'.join(l for l in text.splitlines() if not l.startswith('/* #line'))


def top_level(toks):
    """Yield (start, end, kind) token ranges of top-level declarations:
    'fn' for a function definition (ends at its '}'), 'decl' otherwise."""
    depth = paren = 0
    start = 0
    is_fn = False
    for i, (k, t) in enumerate(toks):
        if k != 'op':
            continue
        if t == '(':
            paren += 1
        elif t == ')':
            paren -= 1
        elif t == '{':
            if depth == 0 and paren == 0:
                sig = [x[1] for x in toks[start:i] if x[0] != 'ws']
                is_fn = bool(sig) and sig[-1] == ')' and '=' not in sig
            depth += 1
        elif t == '}':
            depth -= 1
            if depth == 0 and is_fn:
                yield start, i + 1, 'fn'
                start = i + 1
                is_fn = False
        elif t == ';' and depth == 0 and paren == 0:
            yield start, i + 1, 'decl'
            start = i + 1


def rename_section(text, suffix, pool_names, renames):
    toks = [(m.lastgroup, m.group()) for m in TOKEN.finditer(text)]
    keep, decls, drop, insert = set(), {}, set(), {}
    for s, e, kind in top_level(toks):
        sig = [x for x in toks[s:e] if x[0] != 'ws']
        words = [x[1] for x in sig]
        if kind == 'fn':
            j = words.index('(')
            if 'static' not in words[:j] and j and sig[j - 1][0] == 'id':
                keep.add(words[j - 1])
            continue
        if not words or words[0] != 'extern' or '(' in words or not any(w in pool_names for w in words):
            continue
        # split `extern T a[2], *b;` into declarators; pool ones are dropped
        parts, cur, br = [], [], 0
        for w in words[1:-1]:
            br += (w == '[') - (w == ']')
            if w == ',' and br == 0:
                parts.append(cur)
                cur = []
            else:
                cur.append(w)
        parts.append(cur)

        def split_decl(part):
            j = part.index('[') if '[' in part else len(part)
            return part[:j - 1], part[j - 1], part[j:]
        pre, _, _ = split_decl(parts[0])
        base = [w for w in pre if w != '*']
        rest = []
        for n, part in enumerate(parts):
            lead, nm, dims = split_decl(part)
            ty = base + [w for w in lead if w == '*']
            if nm in pool_names:
                decls.setdefault(nm, (ty, dims))
            else:
                rest.append('extern ' + ' '.join(ty + [nm]) + ''.join(dims) + ';')
        drop.update(range(s, e))
        if rest:
            first = next(i for i in range(s, e) if toks[i][0] != 'ws')
            insert[first] = rest
    out = []
    line_start, directive = True, False
    for idx, (k, t) in enumerate(toks):
        if idx in insert:
            sub = {}
            out.append(rename_section(' '.join(insert[idx]), suffix, set(), sub))
            renames.update(sub)
        if idx in drop:
            if k == 'ws' and '\n' in t:
                out.append('\n' * t.count('\n'))
            continue
        if k == 'ws':
            if '\n' in t:
                line_start, directive = True, False
            out.append(t)
            continue
        if line_start and t == '#':
            directive = True
        line_start = False
        if directive or k != 'id' or t in C_KEYWORDS or t.startswith('__') or t in keep:
            out.append(t)
        elif t in pool_names:
            if t in decls:
                ty, dims = decls[t]
                ty = ' '.join(w + suffix if re.match(r'[A-Za-z_]\w*$', w) and w not in C_KEYWORDS
                              and not w.startswith('__') else w for w in ty)
                d = ''.join(dims)
                out.append(f'(*({ty} (*){d})&{t})' if d else f'(*({ty} *)&{t})')
            else:
                out.append(t)
        else:
            out.append(t + suffix)
            renames[t + suffix] = t
    return ''.join(out)


def target_extab_order(tus):
    order = []
    for b in tus:
        if not any(s[0] == 'extabindex' for s in b['secs']):
            continue
        obj = ROOT / 'build/GNLJ82/obj' / (str(Path(b['name']).with_suffix('')) + '.o')
        out = subprocess.run([str(OBJDUMP), '-r', '-j', 'extabindex', str(obj)], capture_output=True, text=True).stdout
        rows = sorted((int(m.group(1), 16), m.group(2)) for m in
                      re.finditer(r'^([0-9a-f]+)\s+R_PPC_ADDR32\s+(\S+)$', out, re.M))
        order += [sym for off, sym in rows if off % 12 == 0]
    return order


def apply(a):
    text, blocks = read_blocks()
    tus = select(blocks, a.first, a.last)
    cfg = CONFIGURE.read_text()
    into = a.into or tus[0]['name']
    if into not in [b['name'] for b in tus]:
        sys.exit('--into must be one of the merged TUs')
    base_flags, info = None, []
    for b in tus:
        if not b['name'].endswith('.c'):
            sys.exit(f"{b['name']}: only C TUs are handled")
        _, flags = object_line(cfg, b['name'])
        rest = sorted(f for f in flags if f not in ('-Cpp_exceptions on', '-Cpp_exceptions off',
                                                       '-use_lmw_stmw on', '-use_lmw_stmw off'))
        if base_flags is None:
            base_flags = rest
        elif rest != base_flags:
            sys.exit(f"{b['name']}: flags {rest} differ from {base_flags}; not handled")
        info.append((b, '-Cpp_exceptions on' in flags, '-use_lmw_stmw on' in flags))

    pool_src = Path(a.pool).read_text() if a.pool else ''
    pool_names = set(re.findall(r'^(?:static\s+)?(?:const\s+)?[\w\s\*]+?\b(\w+)\s*(?:\[[^\]]*\])*\s*=', pool_src, re.M))
    pool_src = re.sub(r'^(?!static|extern|#|\s|\}|$)', 'static ', pool_src, flags=re.M)

    renames = {}
    end = max(s[2] for s in tus[-1]['secs'] if s[0] == '.text')
    out = [f'/* {len(tus)} TUs merged by tools/merge_tus.py, .text {a.first:#x}..{end:#x}.',
           ' * Each section is the preprocessed original TU with its names suffixed _pN',
           ' * (tools/extab_user_renames.json maps the symbols back). */']
    if pool_src:
        out += ['/* ==== pool (tools/data2c.py) ==== */', pool_src.rstrip(), '']
    for n, (b, exc, lmw) in enumerate(info):
        sec = rename_section(preprocess(b['name']), f'_p{n}', pool_names, renames)
        out += [f"/* ==== {b['name']} ({text_start(b):#x}) ==== */",
                f'#pragma exceptions {"on" if exc else "off"}',
                f'#pragma use_lmw_stmw {"on" if lmw else "off"}',
                sec.strip(), '#pragma use_lmw_stmw reset', '#pragma exceptions reset', '']
    (ROOT / 'src' / into).write_text('\n'.join(out) + '\n', encoding='latin-1')

    merged = {}
    for b in tus:
        for s in b['secs']:
            merged.setdefault(s[0], []).append(s)
    for ps in a.pool_sec or []:
        sec, lo, hi = ps.split(':')
        merged.setdefault(sec, []).append((sec, int(lo, 16), int(hi, 16), ''))
    lines = [f'{into}:']
    for sec, rs in sorted(merged.items(), key=lambda kv: CANON.index(kv[0]) if kv[0] in CANON else 99):
        rs.sort(key=lambda s: s[1])
        for x, y in zip(rs, rs[1:]):
            if x[2] != y[1]:
                sys.exit(f'{sec}: {x[2]:#x} != {y[1]:#x}, ranges not contiguous (another TU owns the gap?)')
        lines.append(f'\t{sec:<11} start:0x{rs[0][1]:08X} end:0x{rs[-1][2]:08X}{rs[0][3]}')
    new = text
    for b in reversed(tus):
        s, e = b['span']
        new = new[:s] + ('\n'.join(lines) + '\n' if b is tus[0] else '') + new[e:]
    SPLITS.write_text(re.sub(r'\n{3,}', '\n\n', new))

    for b in tus:
        m, _ = object_line(cfg, b['name'])
        if b['name'] == into:
            fl = ', '.join(f'"{f}"' for f in ['-Cpp_exceptions on'] + base_flags)
            cfg = cfg.replace(m.group(0), f'{m.group(1)}Object(NonMatching, "{into}", extra_cflags=[{fl}]),')
        else:
            cfg = cfg.replace(m.group(0) + '\n', '', 1)
    CONFIGURE.write_text(cfg)

    rj = json.loads(RENAMES.read_text())
    merged_r = {}
    for b in tus:
        merged_r.update(rj.pop('src/' + b['name'], {}) or {})
    merged_r.update(renames)
    rj['src/' + into] = merged_r
    RENAMES.write_text(json.dumps(rj, indent=2, ensure_ascii=False) + '\n')

    order = target_extab_order(tus)
    oj = json.loads(ORDER.read_text())
    for b in tus:
        oj.pop('src/' + b['name'], None)
    if order:
        oj['src/' + into] = order
    ORDER.write_text(json.dumps(oj, indent=2, ensure_ascii=False) + '\n')

    for b in tus:
        if b['name'] != into:
            subprocess.run(['git', 'rm', '-q', 'src/' + b['name']], cwd=ROOT, check=True)
    print(f'merged {len(tus)} TUs into src/{into}; {len(renames)} renames; extab order {len(order)}')
    print(f'next: ninja, then `python3 tools/merge_tus.py prune-renames --tu {into}`')


def prune_renames(a):
    """Drop the generated `_pN` renames that did not become symbols of the object."""
    obj = ROOT / 'build/GNLJ82/src' / (str(Path(a.tu).with_suffix('')) + '.o')
    syms = set(subprocess.run([str(NM), str(obj)], capture_output=True, text=True).stdout.split())
    rj = json.loads(RENAMES.read_text())
    key = 'src/' + a.tu
    before = len(rj[key])
    rj[key] = {k: v for k, v in rj[key].items() if not re.search(r'_p\d+$', k) or k in syms}
    RENAMES.write_text(json.dumps(rj, indent=2, ensure_ascii=False) + '\n')
    print(f'{key}: {before} -> {len(rj[key])} renames')


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sp = ap.add_subparsers(dest='cmd', required=True)
    for c in ('plan', 'apply'):
        p = sp.add_parser(c)
        p.add_argument('--first', type=lambda x: int(x, 0), required=True)
        p.add_argument('--last', type=lambda x: int(x, 0), required=True)
        if c == 'apply':
            p.add_argument('--into')
            p.add_argument('--pool')
            p.add_argument('--pool-sec', action='append')
    p = sp.add_parser('prune-renames')
    p.add_argument('--tu', required=True)
    a = ap.parse_args()
    {'plan': plan, 'apply': apply, 'prune-renames': prune_renames}[a.cmd](a)


if __name__ == '__main__':
    main()
