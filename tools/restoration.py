#!/usr/bin/env python3
"""How far the sources are from the form the game was written in.

The matched percentage says the bytes are right. It does not say whether a class
is a class again, whether a struct has one definition, whether data has a type
or whether a function has a name. This counts those, from tracked files only
(no build; about 5 s), for the "Source restoration" page of the Pages site
(tools/gen_restoration_page.py) and for its history.

    python3 tools/restoration.py                 # table
    python3 tools/restoration.py --json          # everything, with the per-class list
    python3 tools/restoration.py --summary       # the flat numbers one history row holds

    # history (CI, progress-data branch): one JSON line per commit
    python3 tools/restoration.py append   --history F --sha SHA --ts ISO
    python3 tools/restoration.py backfill --history F [--ref origin/main] [--limit N]

`backfill` adds one row per past day (the last first-parent commit of the day)
that the file does not have yet, by checking those commits out into a temporary
worktree and measuring them with today's tools. Details: docs/notes/restoration.md.
"""
import argparse, collections, json, os, re, shutil, subprocess, sys, tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, HERE)

SRC_EXT = ('.c', '.cpp', '.cp', '.h', '.hpp', '.inc')
ADDR_NAME = re.compile(r'_8[0-9A-Fa-f]{7}(_|\b)')
# `*(T *)((char *)p + 0x10)` written out, and the per-file macros that hide it
OFFSET_MACRO = re.compile(r'^[ \t]*#[ \t]*define[ \t]+(\w+)\(([\w, ]*)\)[ \t]+(\(?\*?[ \t]*\([^()]*\*[ \t]*\)[ \t]*\(.*\+.*)$', re.M)
OFFSET_CAST = re.compile(r'\*\s*\(\s*[\w ]+\*+\s*\)\s*\(\s*\(\s*(?:unsigned |signed )?(?:char|u8|s8)\s*\*\s*\)')
# members nobody has named yet: unk_10, unk10, field_0x10, field10
UNK_MEMBER = re.compile(r'\b(?:unk|field)_?(?:0x)?[0-9A-Fa-f]+\b\s*(?:\[[^\]\n]*\])*\s*(?::\s*\d+\s*)?;')
TYPEDEF = re.compile(r'^(?:typedef\s+)?(struct|union|class)\s+([A-Za-z_]\w*)\s*(?::[^{;]*)?\{', re.M)


def _modules(root, dol):
    """port_readiness / rtti_classes / nonmatching_check pointed at `root`."""
    import port_readiness as P
    P.ROOT = root
    mods = {'P': P}
    try:
        import rtti_classes as R
        R.ROOT = root
        R.TSV = os.path.join(root, 'docs', 'notes', 'rtti_classes.tsv')
        if dol:
            R.find_dol = lambda: dol
        mods['R'] = R
    except Exception:
        pass
    try:
        import nonmatching_check as N
        N.ROOT = root
        mods['N'] = N
    except Exception:
        pass
    return mods


def sources(root):
    """path -> text of the tracked game sources and headers."""
    out = {}
    names = subprocess.run(['git', 'ls-files', '--', 'src/game', 'include/game'], cwd=root,
                           capture_output=True, text=True).stdout.split('\n')
    for f in names:
        if f.endswith(SRC_EXT):
            try:
                out[f] = open(os.path.join(root, f), encoding='utf-8', errors='replace').read()
            except OSError:
                pass
    return out


def class_numbers(mods, src, root):
    """One row per vtable of the original program (RTTI), and what the sources
    have for it today:
      real   the compiler emits the table from a class definition
      named  ... and that class has the name the RTTI record gives
      hand   the table is an initialised array (a data-only unit, or an array in
             a normal unit), so the class is not a class yet
    """
    R = mods['R']
    vts, records = R.collect()
    try:
        ren = json.load(open(os.path.join(root, 'tools', 'extab_user_renames.json'), encoding='utf-8'))
    except (OSError, ValueError):
        ren = {}
    keys_for = collections.defaultdict(set)          # symbol -> mangled __vt__ names used for it
    for m in ren.values():
        if not isinstance(m, dict):
            continue
        for k, v in m.items():
            if k.startswith('__vt__') and isinstance(v, str):
                keys_for[v.split(':')[-1]].add(k)
    syms = sorted({v['symbol'].split('+')[0] for v in vts
                   if v['data_unit'] and not v['data_unit'].startswith('game/autodata/')})
    arrays = set()
    if syms:
        rx = re.compile(r'\b(' + '|'.join(map(re.escape, syms)) + r'|__vt__\w+)\s*(?:\[[^\]\n]*\])?\s*(?:ATTRIBUTE_ALIGN\(\d+\)\s*)?=\s*\{')
        for f, t in src.items():
            if f.startswith('src/game/autodata/'):
                continue
            for m in rx.finditer(t):
                arrays.add(m.group(1))
    rows = []
    for v in vts:
        sym = v['symbol'].split('+')[0]
        unit = v['data_unit'] or ''
        keys = keys_for.get(sym, set())
        if not unit or unit.startswith('game/autodata/') or sym in arrays or (keys & arrays):
            state = 'hand'
        else:
            short = v['class'].split('<')[0].split('::')[-1]
            tag = '%d%s' % (len(short), short)
            ok = any(k.endswith(tag) for k in keys) if '<' not in v['class'] else any(short in k for k in keys)
            state = 'named' if ok or sym.startswith('__vt__') or short in sym else 'real'
        bases = [b[0] for b in v['bases']]
        rows.append({'class': v['class'], 'bases': bases, 'family': bases[0] if bases else v['class'],
                     'symbol': v['symbol'], 'unit': unit, 'slots': len(v['slots']), 'state': state})
    c = collections.Counter(r['state'] for r in rows)
    return {'tables': len(rows), 'real': c['real'] + c['named'], 'named': c['named'], 'hand': c['hand'],
            'class_names': len({r['class'] for r in rows}), 'rows': rows}


def type_numbers(src):
    where = collections.defaultdict(set)
    ndefs = 0
    for f, t in src.items():
        if f.startswith(('include/game/types/', 'src/game/autodata/')):
            continue
        for m in TYPEDEF.finditer(t):
            where[m.group(2)].add(f); ndefs += 1
    shared = sum(1 for f in src if f.startswith('include/game/types/') and f.endswith('.h'))
    dup = {n: len(fs) for n, fs in where.items() if len(fs) > 1}
    unk = sum(len(UNK_MEMBER.findall(t)) for t in src.values())
    return {'definitions': ndefs, 'names': len(where), 'dup_names': len(dup),
            'extra_copies': sum(v - 1 for v in dup.values()), 'shared_headers': shared, 'unk_members': unk,
            'top_dups': sorted(dup.items(), key=lambda kv: (-kv[1], kv[0]))[:60]}


def offset_numbers(src):
    per = {}
    macro = direct = 0
    for f, t in src.items():
        m = sum(max(0, len(re.findall(r'\b' + re.escape(x.group(1)) + r'\s*\(', t)) - 1) for x in OFFSET_MACRO.finditer(t))
        c = len(OFFSET_CAST.findall(t))
        if m or c:
            per[f] = m + c
        macro += m; direct += c
    return {'accesses': macro + direct, 'through_macros': macro, 'written_out': direct, 'files': len(per),
            'top_files': sorted(per.items(), key=lambda kv: (-kv[1], kv[0]))[:40]}


def unit_numbers(src):
    units = [f for f in src if f.startswith('src/game/') and f.endswith(('.c', '.cpp', '.cp'))]
    data_only = [f for f in units if f.startswith('src/game/autodata/')]
    code = [f for f in units if not f.startswith('src/game/autodata/')]
    addr = [f for f in code if ADDR_NAME.search(os.path.basename(f)) or re.match(r'(anon|auto|fn|unit)_', os.path.basename(f))]
    return {'units': len(code), 'addr_named': len(addr), 'data_only': len(data_only)}


def collect(root=ROOT, dol=None):
    mods = _modules(root, dol)
    P = mods['P']
    src = sources(root)
    out = {}

    def part(name, fn):
        try:
            out[name] = fn()
        except BaseException as e:      # an old tree may lack a file; the rest still counts
            out[name] = {'error': repr(e)}
    syms = []
    try:
        syms = P.symbols()
    except BaseException:
        pass
    part('classes', lambda: class_numbers(mods, src, root))
    part('types', lambda: type_numbers(src))
    part('data', lambda: P.data_numbers(syms, P.splits_ranges()))
    part('symbols', lambda: P.symbol_numbers(syms))
    part('offsets', lambda: offset_numbers(src))
    part('units', lambda: unit_numbers(src))
    part('asm', P.asm_numbers)
    return out


def summary(d):
    """The flat numbers a history row holds. A part that failed leaves its keys out."""
    s = {}

    def ok(k):
        return k in d and 'error' not in d[k]
    if ok('classes'):
        c = d['classes']
        s.update(vt_total=c['tables'], vt_real=c['real'], vt_named=c['named'])
    if ok('types'):
        t = d['types']
        s.update(type_names=t['names'], type_dup_names=t['dup_names'], type_extra_copies=t['extra_copies'],
                 unk_members=t['unk_members'])
    if ok('data') and d['data'].get('total'):
        t = d['data']['total']
        tot = sum(t.values())
        if tot:
            s.update(data_total=tot, data_in_tu=t['in_tu'], data_typed=t['typed'], data_unk=t['unk'], data_no_c=t['no_c'])
    if ok('symbols'):
        y = d['symbols']
        if y['functions']['total']:
            s.update(fn_total=y['functions']['total'], fn_named=y['functions']['named'],
                     dsym_total=y['data']['total'], dsym_named=y['data']['named'])
    if ok('offsets'):
        s.update(offset_accesses=d['offsets']['accesses'])
    if ok('units'):
        u = d['units']
        s.update(units=u['units'], units_addr_named=u['addr_named'], units_data_only=u['data_only'])
    if ok('asm'):
        s.update(asm_fns=d['asm']['asm_functions'], asm_with_c=d['asm']['with_c_body'])
    return s


def pct(a, b):
    return '%.1f%%' % (100.0 * a / b) if b else '-'


def table(s):
    g = s.get
    rows = [
        ('Vtables the compiler emits from a class', '%s / %s' % (g('vt_real'), g('vt_total')), pct(g('vt_real', 0), g('vt_total', 0))),
        ('  of those, the class has its original name', '%s' % g('vt_named'), pct(g('vt_named', 0), g('vt_total', 0))),
        ('Type names with one definition', '%s / %s' % (g('type_names', 0) - g('type_dup_names', 0), g('type_names')),
         pct(g('type_names', 0) - g('type_dup_names', 0), g('type_names', 0))),
        ('Members still called unk_/field_', '%s' % g('unk_members'), ''),
        ('Initialised data defined by the unit that uses it', '%s / %s bytes' % (g('data_in_tu'), g('data_total')), pct(g('data_in_tu', 0), g('data_total', 0))),
        ('Functions with a name', '%s / %s' % (g('fn_named'), g('fn_total')), pct(g('fn_named', 0), g('fn_total', 0))),
        ('Data symbols with a name', '%s / %s' % (g('dsym_named'), g('dsym_total')), pct(g('dsym_named', 0), g('dsym_total', 0))),
        ('Accesses by byte offset', '%s' % g('offset_accesses'), ''),
        ('Source units still named by address', '%s / %s' % (g('units_addr_named'), g('units')), pct(g('units_addr_named', 0), g('units', 0))),
        ('Data-only units', '%s' % g('units_data_only'), ''),
        ('Inline-asm game functions', '%s (%s with C)' % (g('asm_fns'), g('asm_with_c')), ''),
    ]
    w = max(len(r[0]) for r in rows)
    return '\n'.join('%-*s  %22s  %s' % (w, *r) for r in rows)


# ---------------------------------------------------------------- history

def load_history(path):
    rows = []
    if os.path.isfile(path):
        for line in open(path, encoding='utf-8'):
            line = line.strip()
            if line:
                try:
                    rows.append(json.loads(line))
                except ValueError:
                    pass
    return rows


def write_history(path, rows):
    seen = {}
    for r in rows:
        seen[r['sha']] = r
    rows = sorted(seen.values(), key=lambda r: (_utc(r['ts']), r['sha']))
    os.makedirs(os.path.dirname(os.path.abspath(path)), exist_ok=True)
    with open(path, 'w', encoding='utf-8') as f:
        for r in rows:
            f.write(json.dumps(r, sort_keys=True, separators=(',', ':')) + '\n')


def _utc(ts):
    from datetime import datetime, timezone
    return datetime.fromisoformat(ts.replace('Z', '+00:00')).astimezone(timezone.utc)


def find_dol(root=ROOT):
    for p in ('orig/GNLJ82/sys/main.dol', 'build/GNLJ82/main.dol'):
        if os.path.exists(os.path.join(root, p)):
            return os.path.join(root, p)
    return None


def cmd_append(a):
    rows = load_history(a.history)
    if any(r['sha'] == a.sha for r in rows):
        print('restoration history: %s already there' % a.sha[:9]); return 0
    row = {'sha': a.sha, 'ts': a.ts}
    row.update(summary(collect()))
    rows.append(row)
    write_history(a.history, rows)
    print('restoration history: appended %s (%d rows)' % (a.sha[:9], len(rows)))
    return 0


def cmd_backfill(a):
    rows = load_history(a.history)
    have_days = {_utc(r['ts']).date() for r in rows}
    log = subprocess.run(['git', 'log', '--first-parent', '--format=%H %cI', a.ref], cwd=ROOT,
                         capture_output=True, text=True, check=True).stdout.split('\n')
    last_of_day = {}
    for line in log:                       # newest first: the first commit seen for a day is its last
        if not line.strip():
            continue
        sha, ts = line.split(' ', 1)
        last_of_day.setdefault(_utc(ts).date(), (sha, ts))
    todo = [v for d, v in sorted(last_of_day.items(), reverse=True) if d not in have_days]
    if a.limit:
        todo = todo[:a.limit]
    if not todo:
        print('restoration history: no day missing'); return 0
    dol = find_dol()
    tmp = tempfile.mkdtemp(prefix='restoration_wt_')
    wt = os.path.join(tmp, 'wt')
    me = os.path.abspath(__file__)
    done = 0
    try:
        subprocess.run(['git', 'worktree', 'add', '--detach', '--force', wt, todo[0][0]], cwd=ROOT, check=True, capture_output=True)
        for sha, ts in todo:
            subprocess.run(['git', 'checkout', '--detach', '--force', '-q', sha], cwd=wt, check=True, capture_output=True)
            # a fresh interpreter per commit: the helper modules keep per-tree state
            r = subprocess.run([sys.executable, me, '--summary', '--root', wt] + (['--dol', dol] if dol else []),
                               capture_output=True, text=True)
            if r.returncode:
                print('restoration history: %s failed: %s' % (sha[:9], r.stderr.strip()[-300:]), file=sys.stderr)
                continue
            row = {'sha': sha, 'ts': ts, 'backfilled': True}
            row.update(json.loads(r.stdout))
            rows.append(row); done += 1
    finally:
        subprocess.run(['git', 'worktree', 'remove', '--force', wt], cwd=ROOT, capture_output=True)
        subprocess.run(['git', 'worktree', 'prune'], cwd=ROOT, capture_output=True)
        shutil.rmtree(tmp, ignore_errors=True)
    write_history(a.history, rows)
    print('restoration history: backfilled %d of %d missing days' % (done, len(todo)))
    return 0


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--json', action='store_true'); ap.add_argument('--summary', action='store_true')
    ap.add_argument('--root', default=ROOT, help='tree to measure (default: this checkout)')
    ap.add_argument('--dol', default=None, help='main.dol to read the RTTI from (default: orig/ of the tree)')
    sub = ap.add_subparsers(dest='cmd')
    p = sub.add_parser('append'); p.add_argument('--history', required=True)
    p.add_argument('--sha', required=True); p.add_argument('--ts', required=True)
    p = sub.add_parser('backfill'); p.add_argument('--history', required=True)
    p.add_argument('--ref', default='HEAD'); p.add_argument('--limit', type=int, default=0)
    a = ap.parse_args()
    if a.cmd == 'append':
        return cmd_append(a)
    if a.cmd == 'backfill':
        return cmd_backfill(a)
    d = collect(os.path.abspath(a.root), a.dol or find_dol(os.path.abspath(a.root)) or find_dol())
    if a.json:
        print(json.dumps(d, indent=1))
    elif a.summary:
        print(json.dumps(summary(d)))
    else:
        print(table(summary(d)))
    return 0


if __name__ == '__main__':
    sys.exit(main())
