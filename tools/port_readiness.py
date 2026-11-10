#!/usr/bin/env python3
"""Port-readiness numbers in one go (what the PC port needs besides matched functions).

The matched-function count does not move when data gets a type, a struct gets one
shared definition, a symbol gets a name or an asm function gets an equivalent C body.
This prints those four things, from tracked files only (no build needed, about 3 s):

  python3 tools/port_readiness.py            # table
  python3 tools/port_readiness.py --json     # machine readable (CI, Pages)
  python3 tools/port_readiness.py --md       # markdown table (for a landing report)

1. Initialised data (.rodata/.data/.sdata/.sdata2 objects of symbols.txt, bytes):
     no C      not inside any unit of splits.txt (still linked from the original binary)
     unk       defined in src/game/autodata as unk32/unk16/unk8 (layout not known)
     typed     defined in src/game/autodata with a real type
     in TU     inside a normal source unit (owned by the TU that uses it)
2. Types: struct/union/class names defined at file scope in more than one file of
   src/game + include/game, and names shared through include/game/types.
3. Symbols of symbols.txt with a real name (not lbl_/fn_/address style), data and code.
4. Game functions that are inline asm in the default build: with and without an
   equivalent C body under NON_MATCHING (docs/nonmatching_c.md).

Details: docs/notes/port_readiness.md.
"""
import argparse, collections, json, os, re, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
VER = 'GNLJ82'
DATA_SECS = ('.rodata', '.data', '.sdata', '.sdata2')
SYM = re.compile(r'^(\S+) = (\.?\w+):0x([0-9A-Fa-f]+); // (.*)$')
UNNAMED = re.compile(r'^(lbl_|fn_|gap_|pad_|jumptable_|@|\.\.\.|switch_|sub_|dtor_8|anon_|auto_|zz_)|_8[0-9A-Fa-f]{7}$')
AUTODEF = re.compile(r'^(?!extern)([^ /#\n][^=\n]*?)\b(\w+)((?:\[[^\]\n]*\])*)(?: __attribute__\(\(aligned\(8\)\)\))? = ', re.M)
TYPEDEF = re.compile(r'^(?:typedef\s+)?(struct|union|class)\s+([A-Za-z_]\w*)\s*(?::[^{;]*)?\{', re.M)


def read(p):
    return open(os.path.join(ROOT, p), encoding='utf-8', errors='replace').read()


def splits_ranges():
    """section -> sorted [(lo, hi, unit)]"""
    out = collections.defaultdict(list)
    unit = None
    for line in read('config/%s/splits.txt' % VER).split('\n'):
        if line and not line[0].isspace() and line.endswith(':'):
            unit = line[:-1]; continue
        m = re.match(r'^\s+(\.?\w+)\s+start:0x([0-9A-Fa-f]+)\s+end:0x([0-9A-Fa-f]+)', line)
        if m and unit and unit != 'Sections':
            out[m.group(1)].append((int(m.group(2), 16), int(m.group(3), 16), unit))
    for v in out.values(): v.sort()
    return out


def symbols():
    out = []
    for line in read('config/%s/symbols.txt' % VER).split('\n'):
        m = SYM.match(line)
        if not m: continue
        attrs = m.group(4)
        size = re.search(r'size:0x([0-9A-Fa-f]+)', attrs)
        kind = re.search(r'type:(\w+)', attrs)
        out.append((m.group(1), m.group(2), int(m.group(3), 16), int(size.group(1), 16) if size else 0,
                    kind.group(1) if kind else ''))
    return out


def data_numbers(syms, ranges):
    import bisect
    unk_names, typed_names = set(), set()
    d = os.path.join(ROOT, 'src', 'game', 'autodata')
    if os.path.isdir(d):
        for f in sorted(os.listdir(d)):
            if not f.endswith('.c'): continue
            for m in AUTODEF.finditer(read('src/game/autodata/' + f)):
                (unk_names if re.search(r'\bunk(8|16|32)\b', m.group(1)) else typed_names).add(m.group(2))
    res = {s: {'no_c': 0, 'unk': 0, 'typed': 0, 'in_tu': 0} for s in DATA_SECS}
    for name, sec, addr, size, kind in syms:
        if sec not in res or kind != 'object' or name.startswith(('gap_', 'pad_')): continue
        rs = ranges.get(sec, [])
        i = bisect.bisect_right(rs, (addr, 1 << 40, '')) - 1
        unit = rs[i][2] if i >= 0 and rs[i][0] <= addr < rs[i][1] else None
        if unit is None: k = 'no_c'
        elif unit.startswith('game/autodata/'): k = 'unk' if name in unk_names else 'typed'
        else: k = 'in_tu'
        res[sec][k] += size
    tot = {k: sum(r[k] for r in res.values()) for k in ('no_c', 'unk', 'typed', 'in_tu')}
    return {'sections': res, 'total': tot, 'raw_word_arrays': raw_word_arrays()}


RAWARR = re.compile(r'^(?:static |const |volatile )*(unsigned int|u32|unsigned long|uint|undefined4)\s+(\w+)\[(\d*)\]'
                    r'\s*(?:ATTRIBUTE_ALIGN\(\d+\)|__attribute__\(\(aligned\(\d+\)\)\))?\s*=\s*\{(.*?)\};', re.M | re.S)


def raw_word_arrays():
    """Initialised `unsigned int x[] = {...}` of 64 bytes or more in normal TUs: word dumps whose
    real element type (floats, shorts, records) is not written down yet."""
    files = subprocess.run(['git', 'ls-files', '--', 'src/game'], cwd=ROOT, capture_output=True, text=True).stdout.split('\n')
    n = size = 0
    for f in files:
        if not f.endswith(('.c', '.cpp', '.cp')) or f.startswith('src/game/autodata/'): continue
        for m in RAWARR.finditer(read(f)):
            b = 4 * (int(m.group(3)) if m.group(3) else m.group(4).count(',') + 1)
            if b >= 64: n += 1; size += b
    return {'objects': n, 'bytes': size}


def type_numbers():
    files = subprocess.run(['git', 'ls-files', '--', 'src/game', 'include/game'], cwd=ROOT,
                           capture_output=True, text=True).stdout.split('\n')
    where = collections.defaultdict(set)
    ndefs = 0
    for f in files:
        if not f.endswith(('.c', '.cpp', '.cp', '.h', '.hpp', '.inc')): continue
        if f.startswith(('include/game/types/', 'src/game/autodata/')): continue
        for m in TYPEDEF.finditer(read(f)):
            where[m.group(2)].add(f); ndefs += 1
    td = os.path.join(ROOT, 'include', 'game', 'types')
    shared = len([f for f in os.listdir(td) if f.endswith('.h')]) if os.path.isdir(td) else 0
    dup = {n: len(fs) for n, fs in where.items() if len(fs) > 1}
    return {'definitions_in_sources': ndefs, 'names': len(where), 'names_in_several_files': len(dup),
            'extra_copies': sum(v - 1 for v in dup.values()), 'shared_headers': shared}


def symbol_numbers(syms):
    out = {}
    for label, pred in (('data', lambda s, k: k == 'object' and s in DATA_SECS + ('.bss', '.sbss', '.sbss2')),
                        ('functions', lambda s, k: k == 'function')):
        names = [n for n, s, a, z, k in syms if pred(s, k) and not n.startswith(('gap_', 'pad_'))]
        named = sum(1 for n in names if not UNNAMED.search(n))
        out[label] = {'total': len(names), 'named': named}
    return out


def asm_numbers():
    sys.path.insert(0, os.path.join(ROOT, 'tools'))
    try:
        from pathlib import Path
        import scan_asm_fns
        import nonmatching_check as N
        asm = {n: v for n, v in scan_asm_fns.scan_repo(Path(ROOT))['asm_fns'].items() if v['tu'].startswith('game/')}
        with_c = set()
        for u in N.guarded_units():
            with_c.update(N.guarded_functions(u))
        real = {n: v for n, v in asm.items() if v['size'] > 16}     # 8-byte thunks are not work
        have = {n for n in real if n in with_c}
        return {'asm_functions': len(real), 'asm_bytes': sum(v['size'] for v in real.values()),
                'with_c_body': len(have), 'with_c_bytes': sum(real[n]['size'] for n in have),
                'without_c_body': sorted(n for n in real if n not in have)}
    except Exception as e:   # the page must not fail because of this section
        return {'error': repr(e)}


def vtable_numbers(syms):
    """Vtables of the original program (tools/rtti_classes.py reads them from
    main.dol), how many a data-only unit still writes out by hand, and how many
    class names the sources use for them. mkgp2-pc docs/port/cxx_abi_decision.md."""
    try:
        import rtti_classes
        vts, records = rtti_classes.collect()
    except BaseException as e:   # no main.dol: the page must not fail because of this
        return {'error': repr(e)}
    pairs = re.findall(r'"(__vt__[^"]+)"\s*:\s*"([^"]+)"', read('tools/extab_user_renames.json'))
    hand = [v for v in vts if (v['data_unit'] or '').startswith('game/autodata/')]
    real = {v['class'] for v in vts}
    named = sum(1 for v in vts if v['class'].split('<')[0].split('::')[-1] in v['symbol'])
    return {'tables': len(vts), 'hand_written': len(hand), 'real_classes': len(real),
            'symbol_has_real_name': named, 'source_class_names': len({c for c, _ in pairs}), 'uses': len(pairs)}


def collect():
    syms = symbols()
    return {'data': data_numbers(syms, splits_ranges()), 'types': type_numbers(),
            'symbols': symbol_numbers(syms), 'asm': asm_numbers(), 'vtables': vtable_numbers(syms)}


def pct(a, b):
    return '%.1f%%' % (100.0 * a / b) if b else '-'


def rows(d):
    t = d['data']['total']
    all_data = sum(t[k] for k in ('no_c', 'unk', 'typed', 'in_tu'))
    ty, sy, a = d['types'], d['symbols'], d['asm']
    out = [
        ('Initialised data defined in the TU that uses it', '%s / %s bytes' % (f'{t["in_tu"]:,}', f'{all_data:,}'),
         pct(t['in_tu'], all_data), 'element types there are not audited yet'),
        ('  of that, still a plain unsigned int array (64 bytes or more)', f'{d["data"]["raw_word_arrays"]["bytes"]:,} bytes',
         pct(d['data']['raw_word_arrays']['bytes'], all_data), '%d objects; word dumps inside normal TUs' % d['data']['raw_word_arrays']['objects']),
        ('Initialised data in data-only TUs with a real type', f'{t["typed"]:,} bytes', pct(t['typed'], all_data), 'src/game/autodata'),
        ('Initialised data in data-only TUs, layout unknown (unk)', f'{t["unk"]:,} bytes', pct(t['unk'], all_data), 'to do: give it a type'),
        ('Initialised data with no C definition', f'{t["no_c"]:,} bytes', pct(t['no_c'], all_data), 'compiler jump tables once this is small'),
        ('Type names defined in more than one file', f'{ty["names_in_several_files"]:,} names',
         '', '%s extra copies; %s definitions, %s names in src/game + include/game' % (
             f'{ty["extra_copies"]:,}', f'{ty["definitions_in_sources"]:,}', f'{ty["names"]:,}')),
        ('Types shared through include/game/types', f'{ty["shared_headers"]:,} headers', '', ''),
        ('Data symbols with a name', '%s / %s' % (f'{sy["data"]["named"]:,}', f'{sy["data"]["total"]:,}'),
         pct(sy['data']['named'], sy['data']['total']), ''),
        ('Function symbols with a name', '%s / %s' % (f'{sy["functions"]["named"]:,}', f'{sy["functions"]["total"]:,}'),
         pct(sy['functions']['named'], sy['functions']['total']), ''),
    ]
    if 'error' in a:
        out.append(('Asm-only game functions', 'n/a', '', a['error']))
    else:
        out.append(('Asm-only game functions with an equivalent C body', '%d / %d' % (a['with_c_body'], a['asm_functions']),
                    pct(a['with_c_bytes'], a['asm_bytes']) + ' of bytes',
                    'left: ' + (', '.join(a['without_c_body'][:6]) + (' ...' if len(a['without_c_body']) > 6 else '') or 'none')))
    v = d['vtables']
    if 'error' in v:
        out.append(('Vtables written out by hand as data', 'n/a', '', v['error']))
    else:
        out.append(('Vtables written out by hand as data', '%s / %s' % (f'{v["hand_written"]:,}', f'{v["tables"]:,}'),
                    pct(v['hand_written'], v['tables']),
                    'to do: real classes, table from the compiler (0 = the port needs no ABI bridge); tools/rtti_classes.py'))
        out.append(('Vtables whose symbol carries the real class name', '%s / %s' % (f'{v["symbol_has_real_name"]:,}', f'{v["tables"]:,}'),
                    pct(v['symbol_has_real_name'], v['tables']),
                    '%s real classes (from RTTI); the sources use %s class names in %s declarations' % (
                        f'{v["real_classes"]:,}', f'{v["source_class_names"]:,}', f'{v["uses"]:,}')))
    return out


def html_section(d=None):
    """<h2> block for tools/gen_progress_page.py."""
    import html
    d = d or collect()
    trs = ''.join('<tr><td>%s</td><td style="text-align:right;white-space:nowrap">%s</td>'
                  '<td style="text-align:right">%s</td><td class="meta">%s</td></tr>' % tuple(html.escape(x) for x in r)
                  for r in rows(d))
    return ('  <h2>Port readiness (PC port prerequisites)</h2>\n'
            '  <p class="meta">Things the matched-function count does not show: typed data, one definition per type, '
            'names, and C for the functions that are still inline asm. From <code>tools/port_readiness.py</code>.</p>\n'
            '  <table><thead><tr><th>Item</th><th style="text-align:right">Now</th><th style="text-align:right">Share</th>'
            '<th>Note</th></tr></thead><tbody>%s</tbody></table>\n' % trs)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--json', action='store_true'); ap.add_argument('--md', action='store_true')
    a = ap.parse_args()
    d = collect()
    if a.json:
        print(json.dumps(d, indent=1)); return
    rs = rows(d)
    if a.md:
        print('| Item | Now | Share | Note |\n|---|---|---|---|')
        for r in rs: print('| %s | %s | %s | %s |' % r)
        return
    w = max(len(r[0]) for r in rs)
    for r in rs: print('%-*s  %26s  %-16s %s' % (w, r[0], r[1], r[2], r[3]))


if __name__ == '__main__':
    main()
