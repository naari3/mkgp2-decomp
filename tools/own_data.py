#!/usr/bin/env python3
"""Give unowned .rodata/.data runs to the one TU whose code uses them (tu_audit OWN rows).

  python3 tools/own_data.py list [--min 0x40] [--matching]     # candidates (Matching TUs)
  python3 tools/own_data.py apply TU SEC LO HI                  # patch source + splits.txt
  python3 tools/own_data.py revert TU                           # git checkout the TU source

apply: generates the objects with tools/data2c.py (force_active), inserts them after the
last top-level #include / extern-"C"-free preamble line of the TU source, deletes
single-name `extern ... NAME[...];` declarations of the defined names (they would clash
with the const definitions), and adds `SEC start:LO end:HI` to the TU's splits.txt block.
Always verify with a clean build (main.dol OK) and a report diff: C functions that now see
defined objects can switch to section-anchor addressing and regress.
"""
import argparse, json, os, re, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SPLITS = os.path.join(ROOT, 'config', 'GNLJ82', 'splits.txt')
ORDER = ['extab', 'extabindex', '.text', '.ctors', '.dtors', '.rodata', '.data', '.bss', '.sdata', '.sbss', '.sdata2', '.sbss2']


def candidates(minsize, claims):
    sys.path.insert(0, os.path.join(ROOT, 'tools'))
    import tu_audit as T
    m = T.Model(open(SPLITS).read(), T.load_claims(claims, False) if claims else ())
    out = []
    for r in T.find_owns(m):
        if r['sec'] not in ('.rodata', '.data') or m.status_of(r['unit']) != 'Matching':
            continue
        if r['end'] - r['start'] < minsize:
            continue
        out.append(dict(tu=m.units[r['unit']]['name'], sec=r['sec'], lo=r['start'], hi=r['end'],
                        uses=r['uses'], claim=m.claim_of(r['unit']) or ''))
    out.sort(key=lambda x: x['hi'] - x['lo'], reverse=True)
    return out


def src_of(tu):
    for ext in ('', ):
        p = os.path.join(ROOT, 'src', tu + ext)
        if os.path.exists(p):
            return p
    raise SystemExit('no source for ' + tu)


def patch_splits(tu, sec, lo, hi):
    lines = open(SPLITS).read().split('\n')
    try:
        i = lines.index(tu + ':')
    except ValueError:
        raise SystemExit('TU not in splits.txt: ' + tu)
    j = i + 1
    while j < len(lines) and lines[j].startswith('\t'):
        j += 1
    block = lines[i + 1:j]
    if any(l.split()[0] == sec for l in block):
        raise SystemExit(f'{tu} already has {sec}')
    new = '\t%-11s start:0x%08X end:0x%08X' % (sec, lo, hi)
    k = len(block)
    for n, l in enumerate(block):
        if ORDER.index(l.split()[0]) > ORDER.index(sec):
            k = n
            break
    block.insert(k, new)
    lines[i + 1:j] = block
    open(SPLITS, 'w').write('\n'.join(lines))


def preprocess(tu):
    """The TU preprocessed by its own compile command (mwcc -E), or ''."""
    o = os.path.join('build', 'GNLJ82', 'src', os.path.splitext(tu)[0] + '.o')
    cmds = subprocess.run(['ninja', '-t', 'commands', o], cwd=ROOT, capture_output=True, text=True).stdout.strip().splitlines()
    if not cmds: return ''
    cmd = cmds[-1].split(' && ')[0]
    cmd = re.sub(r' -MMD', '', cmd)
    cmd = re.sub(r' -c (\S+) -o \S+$', r' -E \1', cmd)
    r = subprocess.run(cmd, shell=True, cwd=ROOT, capture_output=True, text=True, errors='replace')
    return r.stdout if r.returncode == 0 else ''


def decl_types(tu, names):
    """{name: [base type, dims]} from `extern TYPE NAME[...];` declarations the TU sees."""
    text = preprocess(tu)
    out = {}
    for n in names:
        for m in re.finditer(r'(?:^|[;{}\n])\s*extern\s+(?:"C"\s+)?([^;{}()=#"]*?)\b%s\s*((?:\[[^\]]*\])*)\s*;' % re.escape(n), text):
            base = m.group(1).strip()
            if base and ',' not in base:
                out[n] = [base, m.group(2)]
    return out


def apply(tu, sec, lo, hi):
    pre = subprocess.run([sys.executable, os.path.join(ROOT, 'tools', 'data2c.py'), sec, '0x%X' % lo, '0x%X' % hi],
                         capture_output=True, text=True)
    allnames = re.findall(r'^(?:static )?(?:const )?[\w ]*?\**\s*(?:const )?(\w+)\[\d*\] =', pre.stdout, re.M)
    types = decl_types(tu, allnames)
    tf = os.path.join('/tmp', 'own_data_types.json')
    json.dump(types, open(tf, 'w'))
    gen = subprocess.run([sys.executable, os.path.join(ROOT, 'tools', 'data2c.py'), sec, '0x%X' % lo, '0x%X' % hi,
                          '--force-active', '--types', tf], capture_output=True, text=True)
    if gen.returncode:
        raise SystemExit(gen.stderr)
    body = gen.stdout
    need = re.findall(r'needs externs: (.*)', gen.stderr)
    names = re.findall(r'^(?:static )?[^=\n]*?(\w+)\s*(?:\[\d*\])*\s*=', body, re.M)
    p = src_of(tu)
    s = open(p).read()
    cpp = p.endswith('.cpp') or p.endswith('.cp')
    ext = ''
    if need:
        ext = ''.join('extern %s %s[];\n' % ('char', n) for n in need[0].split(', ')
                      if not re.search(r'\b%s\b' % re.escape(n), s))
    if cpp:
        body = re.sub(r'^(?!static|#|extern|\s|})', 'extern "C" ', body, flags=re.M)
        ext = re.sub(r'^extern ', 'extern "C" ', ext, flags=re.M)
    for n in names:
        s = re.sub(r'^[ \t]*extern\s+[^;\n(]*\b%s\s*(\[[^\]]*\])*\s*;[ \t]*\n' % re.escape(n), '', s, flags=re.M)
    # insertion point: after the last top-level #include (or the top of the file)
    incs = [m.end() for m in re.finditer(r'^#include[^\n]*\n', s, re.M)]
    at = incs[-1] if incs else 0
    blk = ('/* --- owned %s 0x%08X..0x%08X (tools/own_data.py) --- */\n' % (sec, lo, hi)) + ext + body
    s = s[:at] + blk + s[at:]
    open(p, 'w').write(s)
    patch_splits(tu, sec, lo, (hi + 3) & ~3)
    print('applied', tu, sec, hex(lo), hex(hi), len(names), 'objects')


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sp = ap.add_subparsers(dest='cmd', required=True)
    l = sp.add_parser('list'); l.add_argument('--min', default='0x40'); l.add_argument('--claims'); l.add_argument('--json')
    a = sp.add_parser('apply'); a.add_argument('tu'); a.add_argument('sec'); a.add_argument('lo'); a.add_argument('hi')
    a2 = ap
    x = ap.parse_args()
    if x.cmd == 'list':
        c = candidates(int(x.min, 0), x.claims)
        if x.json:
            json.dump(c, open(x.json, 'w'), indent=1)
        print(len(c), 'runs', sum(r['hi'] - r['lo'] for r in c), 'bytes')
        for r in c[:80]:
            print('%-55s %-7s %08X %08X %6X %s' % (r['tu'], r['sec'], r['lo'], r['hi'], r['hi'] - r['lo'], r['claim']))
    elif x.cmd == 'apply':
        apply(x.tu, x.sec, int(x.lo, 16), int(x.hi, 16))


if __name__ == '__main__':
    main()


def order_conflicts(tu, sec, lo):
    """Units whose .text order disagrees with their `sec` order relative to `tu` if `tu` got
    `sec` at `lo` (dtk would fail with 'Cyclic dependency ... link order')."""
    units, cur = {}, None
    for line in open(SPLITS):
        if line and not line[0].isspace() and line.rstrip().endswith(':'):
            cur = line.rstrip()[:-1]; units[cur] = {}; continue
        m = re.match(r'\t(\S+)\s+start:0x([0-9A-Fa-f]+) end:0x([0-9A-Fa-f]+)', line)
        if m and cur:
            units[cur][m.group(1)] = int(m.group(2), 16)
    me = units.get(tu, {})
    if '.text' not in me:
        return []
    t0 = me['.text']
    bad = []
    for u, secs in units.items():
        if u == tu or sec not in secs or '.text' not in secs:
            continue
        if (secs['.text'] < t0) != (secs[sec] < lo):
            bad.append(u)
    return bad
