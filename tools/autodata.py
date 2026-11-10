#!/usr/bin/env python3
"""Give initialised data that no source defines yet a C definition (data-only TUs).

A PC port cannot use data linked from the original binary: every object has to be
defined in source, with a type, so it can be compiled for another byte order. Giving
each object to "the TU that uses it" (tools/own_data.py) stalls on link-order cycles,
section anchors and shared tables (docs/gave_up.md, "Data-ownership wind-down"), so
this tool does the mechanical half first: each unowned run of a data section becomes
one data-only TU under src/game/autodata/, holding the objects in address order.
Functions keep their `extern` declarations, so no code changes. A definition can be
moved into its real TU later by cut and paste plus a splits.txt edit.

  python3 tools/autodata.py runs [--sec .rodata]         # unowned runs, largest first
  python3 tools/autodata.py gen SEC LO [HI] [--dry]      # write the TU(s) for a run / range
  python3 tools/autodata.py gen --all --sec .rodata      # every run of a section
  python3 tools/autodata.py check [UNIT ...]             # built .o == target .o (bytes + relocs)
  python3 tools/autodata.py drop UNIT ...                # remove a generated TU again
  python3 tools/autodata.py report [--md FILE]           # bytes: no C / C but unk / typed

Types, in this order:
  1. the type the sources declare (`extern const float lbl_X[];`), when every
     declaration agrees and it is a scalar or pointer type;
  2. content: strings, pointer tables (relocations), float tables, small integers;
  3. `unk32` / `unk16` / `unk8` (include/game/autodata.h): layout not known yet. These are
     the objects that still need a real type; a struct type declared by a user TU is
     noted in a comment next to the definition (`/* decl: T */`).
Not generated (the range stays in its auto unit): compiler jump tables and any object
whose relocation targets a local label.

After `gen`, run configure (tools/cloud_setup.sh shows the flags) and ninja; main.dol
must stay OK. Notes: docs/notes/autodata.md.
"""
import argparse, bisect, collections, glob, json, math, os, re, struct, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import data2c as D  # noqa: E402
import tu_audit as T  # noqa: E402

ROOT = T.ROOT
VER = T.VER
SPLITS = os.path.join(ROOT, 'config', VER, 'splits.txt')
SYMBOLS = os.path.join(ROOT, 'config', VER, 'symbols.txt')
OUTDIR = os.path.join(ROOT, 'src', 'game', 'autodata')
ALIGN4 = os.path.join(OUTDIR, 'align4.txt')
SECS = ('.rodata', '.data', '.sdata', '.sdata2')
SMALL = ('.sdata', '.sdata2')
IDENT = re.compile(r'^[A-Za-z_]\w*$')
DECL = re.compile(r'^[ \t]*extern\s+(?:"C"\s+)?([^;{}()=]+);', re.M)
DECL1 = re.compile(r'^(.*?)([A-Za-z_]\w*)\s*((?:\[[^\]]*\]\s*)*)$', re.S)
DECLN = re.compile(r'^\s*(\**)\s*([A-Za-z_]\w*)\s*((?:\[[^\]]*\]\s*)*)$', re.S)


def parse_decl(text):
    """`extern T a[3], *b;` body -> [(base type, name, dims)]"""
    parts = text.split(',')
    m = DECL1.match(parts[0].strip())
    if not m or not m.group(1).strip(): return []
    base = ' '.join(m.group(1).split())
    out = [(base, m.group(2), re.sub(r'\s', '', m.group(3)))]
    root = base.rstrip('* ').strip()
    for p in parts[1:]:
        m = DECLN.match(p)
        if not m: break
        out.append(((root + ' ' + m.group(1)).strip(), m.group(2), re.sub(r'\s', '', m.group(3))))
    return out


SYMREF = re.compile(r'^"?([^"+\-]+)"?(?:([+\-])(0x[0-9a-fA-F]+|\d+))?$')


def unit_name(sec, lo):
    return 'game/autodata/%s_%08X.c' % (sec.strip('.'), lo)


# ---------------------------------------------------------------- model

class Ctx:
    def __init__(self):
        self.m = T.Model(open(SPLITS).read())
        self.objs = {}
        for sec in SECS:
            ads = [a for a, o in self.m.objs.items() if o['sec'] == sec]
            if not ads: continue
            self.objs[sec] = D.load(sec, min(ads), max(a + self.m.objs[a]['size'] for a in ads) + 1)
            for o in self.objs[sec]:   # `.double 1.5` -> the 64-bit pattern
                o['items'] = [(k, v) if k != '8' else
                              ('8', '0x%016X' % struct.unpack('>Q', struct.pack('>d', float(v)))[0]) for k, v in o['items']]
        self._decls = None

    def owned(self, sec, a):
        u = self.m.unit_at(sec, a)
        return u is not None

    def runs(self, sec):
        """Maximal runs of consecutive unowned objects, cut at objects we cannot emit."""
        out, cur = [], []
        for o in self.objs.get(sec, []):
            if self.owned(sec, o['addr']) or self.skip_reason(o):
                if cur: out.append(cur)
                cur = []
                continue
            cur.append(o)
        if cur: out.append(cur)
        res = []
        for r in out:
            while r and r[0]['name'].startswith(('gap_', 'pad_')): r = r[1:]
            while r and r[-1]['name'].startswith(('gap_', 'pad_')): r = r[:-1]
            if r: res.append(r)
        return res

    def skip_reason(self, o):
        if o['name'].startswith('jumptable_'): return 'jump table'
        if not IDENT.match(o['name']): return 'name is not a C identifier'
        for k, v in o['items']:
            if k == 's' or D.isnum(v): continue
            m = SYMREF.match(v)
            if not m: return 'unparsed relocation ' + v
            s = m.group(1)
            if s.startswith('.L') or not IDENT.match(s): return 'relocation to ' + s
        return None

    def decls(self):
        """name -> Counter{(base type, dims)} from every `extern` declaration in src/ and include/."""
        if self._decls is None:
            idx = collections.defaultdict(collections.Counter)
            where = {}
            for top in ('src', 'include'):
                for dp, dn, fs in os.walk(os.path.join(ROOT, top)):
                    if 'autodata' in dp: continue
                    for f in fs:
                        if not f.endswith(('.c', '.cpp', '.cp', '.h', '.hpp', '.inc')): continue
                        p = os.path.join(dp, f)
                        t = open(p, encoding='utf-8', errors='replace').read()
                        if 'extern' not in t: continue
                        for m in DECL.finditer(t):
                            for base, name, dims in parse_decl(m.group(1)):
                                idx[name][(base, dims)] += 1
                                where.setdefault((name, (base, dims)), os.path.relpath(p, ROOT))
            self._decls, self._where = idx, where
        return self._decls


def core_type(base):
    return ' '.join(re.sub(r'\b(const|volatile|struct|union|enum)\b', '', base).split())


CANON = {'u8': 'unsigned char', 's8': 'signed char', 'uchar': 'unsigned char', 'Uint8': 'unsigned char',
         'Sint8': 'signed char', 'BOOL8': 'unsigned char', 'bool': 'unsigned char',
         'u16': 'unsigned short', 's16': 'short', 'ushort': 'unsigned short', 'Uint16': 'unsigned short',
         'Sint16': 'short', 'wchar_t': 'unsigned short',
         'u32': 'unsigned int', 's32': 'int', 'uint': 'unsigned int', 'BOOL': 'int', 'Uint32': 'unsigned int',
         'Sint32': 'int', 'size_t': 'unsigned long', 'f32': 'float', 'f64': 'double',
         'u64': 'unsigned long long', 's64': 'long long'}
BUILTIN = re.compile(r'^(?:(?:unsigned|signed|char|short|int|long|float|double|void)\s*)+$')


def canon(core):
    """Spell a declared type with builtin names only (this TU includes no project header).
    Pointers to anything that is not a builtin become `void *`."""
    if '*' in core:
        b = core.split('*')[0].strip()
        b = CANON.get(b, b)
        return (b if BUILTIN.match(b) else 'void') + ' ' + '*' * core.count('*')
    return CANON.get(core, core)


def scalar_width(core):
    return next((k for k, v in D.SCALARS.items() if core in v), None)


# ---------------------------------------------------------------- emit

def words_of(o):
    bs = D.obj_bytes(o)
    if bs is None or len(bs) != o['size'] or o['size'] % 4: return None
    return [int.from_bytes(bs[i:i + 4], 'big') for i in range(0, len(bs), 4)]


def floatlike(w):
    e = (w >> 23) & 0xFF
    return 0x66 <= e <= 0x98


def fmt_float(w):
    f = struct.unpack('>f', struct.pack('>I', w))[0]
    if not math.isfinite(f): return None
    t = '%.9g' % f
    if struct.pack('>f', float(t)) != struct.pack('>I', w): return None
    for prec in range(1, 9):   # shortest text that round-trips
        s = '%.*g' % (prec, f)
        if struct.pack('>f', float(s)) == struct.pack('>I', w):
            t = repr(float(s)) if 1e-4 <= abs(float(s)) < 1e9 else s   # 20.0, not 2e+01
            break
    if '.' not in t and 'e' not in t and 'n' not in t: t += '.0'
    return t + 'f'


def fmt_double(q):
    f = struct.unpack('>d', struct.pack('>Q', q))[0]
    if not math.isfinite(f): return None
    t = repr(f)
    if struct.pack('>d', float(t)) != struct.pack('>Q', q): return None
    if '.' not in t and 'e' not in t and 'n' not in t: t += '.0'
    return t


def wrap(vals, per=8, ind='    '):
    return ',\n'.join(ind + ', '.join(vals[i:i + per]) for i in range(0, len(vals), per))


class Emitter:
    def __init__(self, ctx, sec, objs):
        self.ctx, self.sec, self.objs = ctx, sec, [o for o in objs if not o['name'].startswith(('gap_', 'pad_'))]
        self.const = sec in ('.rodata', '.sdata2')
        self.defined = {o['name']: o for o in self.objs}
        self.heads = {}
        self.seen = set()
        self.fwd, self.ext = [], set()
        self.stats = collections.Counter()

    # -- pointer expressions
    def ptr(self, v, cast, me):
        if D.isnum(v):
            x = int(v, 0) & 0xFFFFFFFF
            return '0' if x == 0 else '(%s)0x%X' % (cast, x)
        m = SYMREF.match(v)
        sym, sign, off = m.group(1), m.group(2), m.group(3)
        if sym in self.defined:
            if sym not in self.seen and sym != me and sym not in self.fwd: self.fwd.append(sym)
        else:
            self.ext.add(sym)
        kind = self.ctx.m.objs.get(self.ctx.m.byname.get(sym), {}).get('kind')
        if not off:
            return '(%s)%s%s' % (cast, '' if kind == 'fn' else '&', sym)
        return '(%s)((char *)&%s %s %s)' % (cast, sym, sign, off)

    def all_strings(self, it):
        ok = False
        for _, v in it:
            if D.isnum(v):
                if int(v, 0) != 0: return False
                continue
            m = SYMREF.match(v)
            if m.group(2): return False
            t = self.ctx.m.byname.get(m.group(1))
            to = self.byaddr.get(t)
            if not to or {k for k, _ in to['items']} != {'s'}: return False
            ok = True
        return ok

    def define(self, o):
        """-> (head, init, note). head is 'TYPE NAME[DIMS]' without const/static."""
        n, sz, it = o['name'], o['size'], o['items']
        kinds = {k for k, _ in it}
        rel = any(k != 's' and not D.isnum(v) for k, v in it)
        note = ''
        # 1. declared type
        ds = self.ctx.decls().get(n)
        if ds:
            cores = collections.Counter()
            for (base, dims), c in ds.items(): cores[core_type(base)] += c
            (base, dims), _ = max(ds.items(), key=lambda kv: (cores[core_type(kv[0][0])], kv[1]))
            orig = core_type(base)
            core = canon(orig)
            if len(cores) > 1:
                note = 'decl: ' + ' / '.join(sorted(cores))
            r = self.from_decl(o, core, dims, rel)
            if r:
                self.stats['decl'] += sz
                if core != orig and '*' in orig and not note: note = 'decl: ' + orig
                return r[0], r[1], note
            if not note: note = 'decl: ' + orig
        # 2. content
        if kinds == {'s'} and len(it) == 1 and len(it[0][1]) == sz:
            self.stats['string'] += sz
            return 'char %s[]' % n, D.c_string(it[0][1][:-1]), note
        if rel:
            w = it if kinds == {'4'} and sz == 4 * len(it) else \
                (D.as_words(it) if sz % 4 == 0 and o['addr'] % 4 == 0 else None)
            if w is None or len(w) * 4 != sz: raise Skip('%s: relocation in a non-word object' % n, o)
            strs = self.all_strings(w)
            cast = 'const char *' if strs else 'void *'
            el = [self.ptr(v, cast, n) for _, v in w]
            self.stats['ptr'] += sz
            pure = all(not D.isnum(v) or int(v, 0) == 0 for _, v in w)
            if not pure and not note: note = 'pointers mixed with values'
            c2 = 'const ' if self.const else ''
            return '%s%s%s[%d]' % (cast, c2, n, len(w)), '{\n' + wrap(el, 1 if not strs else 2) + '\n}', note
        if kinds == {'8'}:
            vals = [fmt_double(int(v, 0) & 0xFFFFFFFFFFFFFFFF) for _, v in it]
            if all(vals):
                self.stats['float'] += sz
                return ('double %s' % n, vals[0], note) if len(vals) == 1 else \
                    ('double %s[%d]' % (n, len(vals)), '{\n' + wrap(vals, 4) + '\n}', note)
        ws = words_of(o) if o['addr'] % 4 == 0 and kinds <= {'4', 's', '1', '2'} and kinds != {'1'} and kinds != {'2'} else None
        if ws is not None and kinds == {'4'}:
            nz = [w for w in ws if w]
            if nz and all(floatlike(w) for w in nz):
                vals = [fmt_float(w) for w in ws]
                if all(vals):
                    self.stats['float'] += sz
                    if len(ws) == 1 and self.sec in SMALL: return 'float %s' % n, vals[0], note
                    return 'float %s[%d]' % (n, len(ws)), '{\n' + wrap(vals) + '\n}', note
            if self.sec in SMALL and len(ws) == 1:
                w = ws[0]
                self.stats['int'] += sz
                return ('int %s' % n, str(w if w < 0x80000000 else w - (1 << 32)), note) if (w < 0x10000 or w >= 0xFFFF0000) \
                    else ('unsigned int %s' % n, '0x%08X' % w, note)
            self.stats['unk'] += sz
            return 'unk32 %s[%d]' % (n, len(ws)), '{\n' + wrap(['0x%08X' % w for w in ws]) + '\n}', note
        bs = D.obj_bytes(o)
        if bs is None or len(bs) != sz: raise Skip('%s: cannot read bytes' % n, o)
        if self.sec in SMALL and sz in (1, 2) and (kinds == {'1'} or kinds == {'2'}):
            self.stats['int'] += sz   # a char or short variable (scalars keep their 1- or 2-byte alignment)
            return '%s %s' % ('unsigned char' if sz == 1 else 'unsigned short', n), '0x%X' % int.from_bytes(bs, 'big'), note
        if kinds == {'1'} and sz > 1 and all(32 <= x < 127 for x in bs):
            self.stats['string'] += sz
            return 'char %s[%d]' % (n, sz), D.c_string(bs), (note + '; ' if note else '') + 'no terminator: the text continues in the next object'
        if kinds == {'2'} and sz % 2 == 0:
            self.stats['unk'] += sz
            vals = ['0x%04X' % int.from_bytes(bs[i:i + 2], 'big') for i in range(0, sz, 2)]
            return 'unk16 %s[%d]' % (n, sz // 2), '{\n' + wrap(vals, 12) + '\n}', note
        self.stats['unk'] += sz
        return 'unk8 %s[%d]' % (n, sz), '{\n' + wrap(['0x%02X' % x for x in bs], 16) + '\n}', note

    def from_decl(self, o, core, dims, rel):
        n, sz, it = o['name'], o['size'], o['items']
        if '*' in core:
            if {k for k, _ in it} != {'4'} or sz != 4 * len(it): return None
            cast = core
            el = [self.ptr(v, cast, n) for _, v in it]
            dd = D.dims_of(dims, len(it))
            if dd is None or (dd == '' and len(it) != 1): dd = '[%d]' % len(it)
            c2 = ' const ' if self.const else ' '
            if dd == '': return '%s%s%s' % (cast, c2 if self.const else '', n), el[0]
            return '%s%s%s%s' % (cast, c2 if self.const else '', n, dd), '{\n' + wrap(el, 1) + '\n}'
        if rel: return None
        w = scalar_width(core)
        if not w or sz % w: return None
        bs = D.obj_bytes(o)
        if bs is None or len(bs) != sz: return None
        cnt = sz // w
        if core in ('float', 'f32'):
            vals = [fmt_float(int.from_bytes(bs[i * 4:i * 4 + 4], 'big')) for i in range(cnt)]
        elif core in ('double', 'f64'):
            vals = [fmt_double(int.from_bytes(bs[i * 8:i * 8 + 8], 'big')) for i in range(cnt)]
        else:
            if w == 1 and 'char' in core and len(it) == 1 and it[0][0] == 's':
                dd = D.dims_of(dims, cnt)
                if dd is not None and dd.count('[') <= 1:
                    return '%s %s[]' % (core, n), D.c_string(bs[:-1])
            sg = core in D.SIGNED
            vals = [str(int.from_bytes(bs[i * w:(i + 1) * w], 'big', signed=True)) if sg else
                    '0x%X' % int.from_bytes(bs[i * w:(i + 1) * w], 'big') for i in range(cnt)]
        if not all(vals): return None
        dd = D.dims_of(dims, cnt)
        if dd is None or (dd == '' and cnt != 1): dd = '[%d]' % cnt
        if dd == '': return '%s %s' % (core, n), vals[0]
        if dd.count('[') > 1:   # multi-dimensional: brace the innermost rows
            inner = int(re.findall(r'\[(\d+)\]', dd)[-1])
            rows = ['{ ' + ', '.join(vals[i:i + inner]) + ' }' for i in range(0, cnt, inner)]
            mid = [int(x) for x in re.findall(r'\[(\d+)\]', dd)[1:-1]]
            for k in reversed(mid):
                rows = ['{ ' + ', '.join(rows[i:i + k]) + ' }' for i in range(0, len(rows), k)]
            return '%s %s%s' % (core, n, dd), '{\n' + wrap(rows, 1) + '\n}'
        return '%s %s%s' % (core, n, dd), '{\n' + wrap(vals, 8 if w >= 4 else 12) + '\n}'

    def natural_align(self, o, head):
        if 'double ' in head or ' long long ' in ' ' + head: return 8
        if self.sec not in SMALL: return 4
        t = head.split(' ' + o['name'])[0]
        t = t.replace('const', '').strip()
        if '*' in t or '[' in head: return 4
        w = {'unk8': 1, 'unk16': 2, 'unk32': 4}.get(t) or scalar_width(t) or 4
        return min(w, 4) if w != 8 else 8

    def run(self):
        """-> (pre, body, rest): rest = objects that must start another unit (placement
        after the previous object cannot be reproduced inside one TU)."""
        ctx = self.ctx
        self.byaddr = {o['addr']: o for s in SECS for o in ctx.objs.get(s, [])}
        lo = self.objs[0]['addr']
        body, cur, rest = [], lo, []
        for i, o in enumerate(self.objs):
            head, init, note = self.define(o)
            a = self.natural_align(o, head)
            nat = lo + (cur - lo + a - 1) // a * a
            attr = ''
            if nat != o['addr']:
                if (o['addr'] - lo) % 8 == 0 and lo + (cur - lo + 7) // 8 * 8 == o['addr'] \
                        and '*' not in head.split(o['name'])[0]:   # MWCC ignores the attribute on pointer types
                    attr = ' __attribute__((aligned(8)))'
                elif i and o['addr'] % 4 == 0 and o['addr'] >= cur:
                    rest = self.objs[i:]
                    break
                else:
                    raise Skip('%s at %08X: expected %08X after the previous object' % (o['name'], o['addr'], nat), o)
            cur = o['addr'] + o['size']
            st = 'static ' if o['bind'] == 'local' else ''
            cq = 'const ' if self.const and '*' not in head.split(o['name'])[0] else ''
            decl = st + cq + head
            self.heads[o['name']] = decl
            self.seen.add(o['name'])
            line = '%s%s = %s;' % (decl, attr, init)
            if note: line = '/* %s */\n' % note + line
            if attr: line = '/* 8-aligned in the original: probably the first object of a TU */\n' + line
            body.append(line)
        if rest:
            names = {o['name'] for o in rest}
            self.ext |= {s for s in self.fwd if s in names}
            self.fwd = [s for s in self.fwd if s not in names]
        pre = []
        fn_ext = sorted(s for s in self.ext if ctx.m.objs.get(ctx.m.byname.get(s), {}).get('kind') == 'fn')
        ob_ext = sorted(self.ext - set(fn_ext))
        for s in fn_ext: pre.append('extern void %s();' % s)
        for s in ob_ext: pre.append('extern char %s[];' % s)
        for s in self.fwd:
            h = re.sub(r'\[\]', '[%d]' % self.defined[s]['size'], self.heads[s])
            pre.append((h if h.startswith('static ') else 'extern ' + h) + ';')
        self.done = self.objs[:len(self.objs) - len(rest)]
        return pre, body, rest


class Skip(Exception):
    def __init__(self, msg, obj=None):
        Exception.__init__(self, msg); self.obj = obj


def trim(objs):
    while objs and objs[0]['name'].startswith(('gap_', 'pad_')): objs = objs[1:]
    while objs and objs[-1]['name'].startswith(('gap_', 'pad_')): objs = objs[:-1]
    return objs


def render(ctx, sec, objs):
    """-> [(lo, hi, source text, stats)]; more than one unit when the run has to be cut."""
    res = []
    while objs:
        while objs and objs[0]['name'].startswith(('gap_', 'pad_')): objs = objs[1:]
        if not objs: break
        em = Emitter(ctx, sec, objs)
        try:
            pre, body, rest = em.run()
        except Skip as e:   # leave that object in its auto unit, go on before and after it
            if e.obj is None: raise
            print('left out: %s' % e)
            k = next(i for i, o in enumerate(objs) if o['addr'] == e.obj['addr'])
            if k: res += render(ctx, sec, trim(objs[:k]))
            objs = objs[k + 1:]
            continue
        lo, hi = em.done[0]['addr'], em.done[-1]['addr'] + em.done[-1]['size']
        out = ['/* %s 0x%08X..0x%08X: data no source file defined yet, in address order.' % (sec, lo, hi),
               ' * Generated by tools/autodata.py (docs/notes/autodata.md). The functions that use',
               ' * these objects declare them `extern`. Edit freely: give `unk` objects their real',
               ' * type, or move a definition into the TU it belongs to (and shrink this file\'s',
               ' * range in splits.txt). */',
               '#include "game/autodata.h"', '']
        if pre: out += pre + ['']
        out += ['#pragma explicit_zero_data on   /* zero-initialised objects stay in the data section */',
                '#pragma force_active on', ''] + body + ['', '#pragma force_active reset', '']
        res.append((lo, hi, '\n'.join(out), em.stats))
        if rest:
            k = next(i for i, o in enumerate(objs) if o['addr'] == rest[0]['addr'])
            objs = objs[k:]
        else:
            objs = []
    return res


# ---------------------------------------------------------------- splits / files

def splits_insert(text, name, sec, lo, hi):
    """Insert the unit after the unit owning the nearest lower range of the same section."""
    units = T.parse_splits(text)
    best = None
    for u in units:
        r = u['ranges'].get(sec)
        if r and r[1] <= lo and (best is None or r[1] > best[0]): best = (r[1], u['name'])
    block = '%s:\n\t%-11s start:0x%08X end:0x%08X\n\n' % (name, sec, lo, hi)
    lines = text.split('\n')
    if best is None:
        # before the first unit that has this section
        nxt = min((u for u in units if sec in u['ranges']), key=lambda u: u['ranges'][sec][0])
        i = lines.index(nxt['name'] + ':')
        return '\n'.join(lines[:i] + block.rstrip('\n').split('\n') + [''] + lines[i:])
    i = lines.index(best[1] + ':')
    j = i + 1
    while j < len(lines) and lines[j].strip(): j += 1
    return '\n'.join(lines[:j + 1] + block.rstrip('\n').split('\n') + [''] + lines[j + 1:])


def splits_remove(text, name):
    lines = text.split('\n')
    if name + ':' not in lines: return text
    i = lines.index(name + ':')
    j = i + 1
    while j < len(lines) and lines[j].strip(): j += 1
    return '\n'.join(lines[:i] + lines[j + 1:])


def align4_set():
    if not os.path.exists(ALIGN4): return []
    return [l.strip() for l in open(ALIGN4) if l.strip() and not l.startswith('#')]


def align4_write(names):
    with open(ALIGN4, 'w') as f:
        f.write('# autodata units whose section starts at a 4-byte (not 8-byte) boundary;\n'
                '# configure.py pins their section alignment (tools/postprocess_data_alignment.py).\n')
        for n in sorted(set(names)): f.write(n + '\n')


def cmd_runs(a):
    ctx = Ctx()
    rows = []
    for sec in ([a.sec] if a.sec else SECS):
        for r in ctx.runs(sec):
            lo, hi = r[0]['addr'], r[-1]['addr'] + r[-1]['size']
            rows.append((hi - lo, sec, lo, hi, sum(1 for o in r if not o['name'].startswith(('gap_', 'pad_')))))
    for sz, sec, lo, hi, n in sorted(rows, reverse=True)[:a.top]:
        print('%-8s %08X %08X %7X %5d objs' % (sec, lo, hi, sz, n))
    print('total %d bytes in %d runs' % (sum(r[0] for r in rows), len(rows)))


def cmd_gen(a):
    ctx = Ctx()
    todo = []
    if a.all:
        for sec in ([a.sec] if a.sec else SECS):
            todo += [(sec, r) for r in ctx.runs(sec)]
    else:
        lo = int(a.lo, 16); hi = int(a.hi, 16) if a.hi else None
        for r in ctx.runs(a.sec):
            rr = [o for o in r if o['addr'] >= lo and (hi is None or o['addr'] < hi)]
            if hi is None and rr and r[0]['addr'] != lo: rr = [] if not any(o['addr'] == lo for o in r) else rr
            while rr and rr[0]['name'].startswith(('gap_', 'pad_')): rr = rr[1:]
            while rr and rr[-1]['name'].startswith(('gap_', 'pad_')): rr = rr[:-1]
            if rr: todo.append((a.sec, rr))
    text = open(SPLITS).read()
    al = align4_set()
    total = collections.Counter()
    made = 0
    pads = []
    for sec, objs in sorted(todo, key=lambda t: -(t[1][-1]['addr'] + t[1][-1]['size'] - t[1][0]['addr'])):
        if objs[-1]['addr'] + objs[-1]['size'] - objs[0]['addr'] < a.min: continue
        try:
            units = render(ctx, sec, objs)
        except Skip as e:
            print('skip %s: %s' % (unit_name(sec, objs[0]['addr']), e)); continue
        for lo, hi, src, st in units:
            name = unit_name(sec, lo)
            total += st
            made += 1
            print('%s %08X..%08X %s' % (name, lo, hi, dict(st)))
            if a.dry: continue
            os.makedirs(OUTDIR, exist_ok=True)
            open(os.path.join(ROOT, 'src', name), 'w', encoding='utf-8').write(src)
            text = splits_insert(text, name, sec, lo, (hi + 3) & ~3)   # dtk wants 4-aligned split ends
            # same for an existing unit that ends on an odd address just before this one
            prev = [o for o in ctx.objs[sec] if o['addr'] < lo and not o['name'].startswith(('gap_', 'pad_'))]
            if prev:
                pe = prev[-1]['addr'] + prev[-1]['size']
                if pe % 4 and (pe + 3 & ~3) < lo and ctx.owned(sec, prev[-1]['addr']):
                    pads.append('pad_%08X = %s:0x%08X; // type:object size:0x%X scope:local data:byte' % (pe, sec, pe, 4 - pe % 4))
            if hi % 4:   # name the pad bytes, or dtk's gap symbol crosses the unit end (objdiff: "size out of section bounds")
                pads.append('pad_%08X = %s:0x%08X; // type:object size:0x%X scope:local data:byte' % (hi, sec, hi, 4 - hi % 4))
            if lo % 8: al.append(name[:-2])
    if not a.dry:
        open(SPLITS, 'w').write(text)
        align4_write(al)
        if pads:
            with open(SYMBOLS, 'a') as f: f.write('\n'.join(pads) + '\n')
    print('%d units, bytes by type source: %s' % (made, dict(total)))


def cmd_drop(a):
    text = open(SPLITS).read()
    al = align4_set()
    for u in a.units:
        u = u if u.endswith('.c') else u + '.c'
        if not u.startswith('game/autodata/'): u = 'game/autodata/' + os.path.basename(u)
        for un in T.parse_splits(text):
            if un['name'] == u:
                ends = {r[1] for r in un['ranges'].values()}
                sy = open(SYMBOLS).read().split('\n')
                sy = [l for l in sy if not (l.startswith('pad_') and any(e - 4 < int(l[4:12], 16) < e for e in ends))]
                open(SYMBOLS, 'w').write('\n'.join(sy))
        text = splits_remove(text, u)
        p = os.path.join(ROOT, 'src', u)
        if os.path.exists(p): os.remove(p)
        al = [x for x in al if x != u[:-2]]
        print('dropped', u)
    open(SPLITS, 'w').write(text)
    align4_write(al)


# ---------------------------------------------------------------- struct types (retype)

def blob(o):
    """-> (bytes, {offset: relocation text})"""
    bs, rel = bytearray(), {}
    for k, v in o['items']:
        if k == 's': bs += v
        elif D.isnum(v):
            w = {'1': 1, '2': 2, '4': 4, '8': 8}[k]
            bs += (int(v, 0) & ((1 << (8 * w)) - 1)).to_bytes(w, 'big')
        else:
            rel[len(bs)] = v; bs += b'\0\0\0\0'
    return bytes(bs), rel


class StructInit:
    """Initialiser text for one object laid out as `count` elements of a cstruct type."""
    def __init__(self, ctx, o, t):
        import cstruct as C
        self.C, self.ctx, self.o, self.t = C, ctx, o, t
        self.bs, self.rel = blob(o)
        self.used = bytearray(len(self.bs))
        self.ext = set()

    def sym(self, v):
        m = SYMREF.match(v)
        sym, sign, off = m.group(1), m.group(2), m.group(3)
        self.ext.add(sym)
        kind = self.ctx.m.objs.get(self.ctx.m.byname.get(sym), {}).get('kind')
        if not off: return '(void *)%s%s' % ('' if kind == 'fn' else '&', sym)
        return '(void *)((char *)&%s %s %s)' % (sym, sign, off)

    def value(self, t, off):
        C = self.C
        k = t.kind
        if k == 'scalar':
            n = t.size
            raw = self.bs[off:off + n]
            if any(off + i in self.rel for i in range(n)): raise C.Unsupported('relocation in a %s member at +0x%X' % (t.name, off))
            for i in range(n): self.used[off + i] = 1
            x = int.from_bytes(raw, 'big')
            if t.name == 'float':
                r = fmt_float(x)
                if r is None: raise C.Unsupported('float member at +0x%X holds 0x%08X' % (off, x))
                return r
            if t.name == 'double':
                r = fmt_double(x)
                if r is None: raise C.Unsupported('double member at +0x%X' % off)
                return r
            if t.name in ('char', 'schar', 'short', 'int', 'llong'):
                return str(int.from_bytes(raw, 'big', signed=True))
            return str(x) if x < 10 else '0x%X' % x
        if k == 'ptr':
            for i in range(4): self.used[off + i] = 1
            if off in self.rel: return self.sym(self.rel[off])
            x = int.from_bytes(self.bs[off:off + 4], 'big')
            return '0' if x == 0 else '(void *)0x%X' % x
        if k == 'array':
            s, _ = t.elem.size_align()
            if t.elem.kind == 'scalar' and t.elem.name == 'char' and t.n > 1:
                raw = self.bs[off:off + t.n]
                txt = raw.rstrip(b'\0')
                if txt and len(txt) < t.n and all(32 <= c < 127 for c in txt) and not any(off + i in self.rel for i in range(t.n)):
                    for i in range(t.n): self.used[off + i] = 1
                    return D.c_string(txt)
            return '{ ' + ', '.join(self.value(t.elem, off + i * s) for i in range(t.n)) + ' }'
        if k == 'struct':
            t.layout()
            fs = t.fields[:1] if t.union else t.fields
            return '{ ' + ', '.join(self.value(ft, off + fo) for _, ft, fo in fs) + ' }'
        raise C.Unsupported(getattr(t, 'reason', 'unsupported type'))

    def run(self):
        C = self.C
        size, _ = self.t.size_align()
        if size == 0 or len(self.bs) % size: raise C.Unsupported('object size 0x%X is not a multiple of 0x%X' % (len(self.bs), size))
        vals = [self.value(self.t, i * size) for i in range(len(self.bs) // size)]
        for i, u in enumerate(self.used):
            if not u and (self.bs[i] or i in self.rel): raise C.Unsupported('non-zero padding at +0x%X' % i)
        for r in self.rel:
            if not self.used[r]: raise C.Unsupported('relocation in padding at +0x%X' % r)
        return vals


NOTE_DEF = re.compile(r'^/\* decl: ([^\n]*?) \*/\n((?:static )?(?:const )?)([^\n=]*?)\b(\w+)\[(\d+)\]( __attribute__\(\(aligned\(8\)\)\))? = \{\n.*?\n\};', re.M | re.S)


def cmd_retype(a):
    """Replace `/* decl: T */` blobs with struct initialisers of type T (layout from the declaring TU)."""
    import cstruct as C
    ctx = Ctx()
    ctx.decls()
    files = [os.path.join(OUTDIR, os.path.basename(u) if u.endswith('.c') else os.path.basename(u) + '.c') for u in a.units] \
        or sorted(glob.glob(os.path.join(OUTDIR, '*.c')))
    typesdir = os.path.join(ROOT, 'include', 'game', 'types')
    done_bytes = 0
    for f in files:
        text = open(f, encoding='utf-8').read()
        is_const = os.path.basename(f).split('_')[0] in ('rodata', 'sdata2')
        local = {}     # type name -> signature, defined in this file
        includes, defs, exts = [], [], set()
        defined_here = set(re.findall(r'^(?!extern)[^ /#\n][^=\n]*?\b(\w+)(?:\[[^\]\n]*\])*(?: __attribute__\(\(aligned\(8\)\)\))? = ', text, re.M))

        def repl(m):
            nonlocal done_bytes
            names, quals, oldtype, name, cnt, attr = m.groups()
            ad = ctx.m.byname.get(name)
            o = next((x for x in ctx.objs.get('.' + os.path.basename(f).split('_')[0], []) if x['addr'] == ad), None)
            if o is None: return m.group(0)
            srcs = ['src/' + ctx.m.units[u]['name'] for u in sorted(ctx.m.user_units(ad)) if not ctx.m.units[u]['auto']]
            srcs += [w for (n, key), w in ctx._where.items() if n == name]
            best = None
            why = []
            for tn in [x.strip() for x in names.split('/')]:
                if not IDENT.match(tn) or tn in D.SCALARS[1] + D.SCALARS[2] + D.SCALARS[4] + D.SCALARS[8]: continue
                for src in dict.fromkeys(srcs):
                    if not os.path.exists(os.path.join(ROOT, src)): continue
                    try:
                        t = C.find_type(src, tn)
                        if t is None or t.kind != 'struct': continue
                        si = StructInit(ctx, o, t)
                        vals = si.run()
                        sig = C.signature(t)
                    except C.Unsupported as e:
                        why.append('%s (%s): %s' % (tn, src, e)); continue
                    except Exception as e:
                        why.append('%s (%s): %r' % (tn, src, e)); continue
                    score = len(sig[1])
                    if best is None or score > best[0]: best = (score, tn, t, si, vals, sig, src)
                    break
            if best is None:
                print('  %s: no usable struct type (%s)' % (name, '; '.join(why[:3]) or names))
                return m.group(0)
            _, tn, t, si, vals, sig, src = best
            hdr = os.path.join(typesdir, tn + '.h')
            use_hdr = False
            if os.path.exists(hdr):
                try:
                    ht = C.find_type(os.path.relpath(hdr, ROOT), tn)
                    use_hdr = ht is not None and C.signature(ht) == sig
                except Exception:
                    use_hdr = False
            if use_hdr:
                inc = '#include "game/types/%s.h"' % tn
                if inc not in includes and inc not in text: includes.append(inc)
            elif tn in local:
                if local[tn] != sig:
                    print('  %s: another %s with a different layout is already in this file' % (name, tn))
                    return m.group(0)
            else:
                out = []
                try:
                    C.c_definition(t, tn, set(), out)
                except C.Unsupported as e:
                    print('  %s: %s' % (name, e)); return m.group(0)
                pend = []
                for d in out:
                    dn = re.search(r'\} (\w+);$', d).group(1)
                    if dn in local or ('typedef struct %s {' % dn) in text or ('typedef union %s {' % dn) in text: continue
                    h2 = os.path.join(typesdir, dn + '.h')
                    if os.path.exists(h2):   # a nested type that is already shared: must be the same layout
                        o2 = []
                        try:
                            C.c_definition(C.find_type(os.path.relpath(h2, ROOT), dn), dn, set(), o2)
                        except Exception:
                            o2 = []
                        if not o2 or o2[-1] != d:
                            print('  %s: nested %s differs from include/game/types/%s.h' % (name, dn, dn))
                            return m.group(0)
                        inc = '#include "game/types/%s.h"' % dn
                        if inc not in includes and inc not in text: includes.append(inc)
                        continue
                    pend.append((dn, '/* layout as declared in %s */\n%s' % (src, d)))
                for dn, d in pend:
                    local[dn] = None
                    defs.append(d)
                local[tn] = sig
            exts.update(si.ext)
            done_bytes += o['size']
            body = ',\n'.join('    ' + v for v in vals)
            if is_const and 'const' not in quals: quals += 'const '
            return '%s%s %s[%d]%s = {\n%s\n};' % (quals, tn, name, len(vals), attr or '', body)

        new = NOTE_DEF.sub(repl, text)
        if new == text: continue
        need = sorted(s for s in exts if s not in defined_here and not re.search(r'^extern [^\n]*\b%s(\(\)|\[\]);' % re.escape(s), new, re.M))
        ext_lines = ['extern %s;' % ('void %s()' % s if ctx.m.objs.get(ctx.m.byname.get(s), {}).get('kind') == 'fn' else 'char %s[]' % s) for s in need]
        head = '#include "game/autodata.h"\n'
        add = ''.join(i + '\n' for i in includes)
        tail = ''
        if ext_lines: tail += '\n' + '\n'.join(ext_lines) + '\n'
        if defs: tail += '\n' + '\n\n'.join(defs) + '\n'
        prag = '\n#pragma explicit_zero_data on'
        i = new.index(prag)
        new = new.replace(head, head + add, 1)
        i = new.index(prag)
        new = new[:i].rstrip('\n') + '\n' + tail + new[i:]
        open(f, 'w', encoding='utf-8').write(new)
        print('retyped', os.path.relpath(f, ROOT))
    print('%d bytes now have a struct type' % done_bytes)


# ---------------------------------------------------------------- rows inferred from the values (infer)

UNK32_DEF = re.compile(r'^((?:/\* [^\n]* \*/\n)?)((?:static )?(?:const )?)unk32 (\w+)\[(\d+)\]( __attribute__\(\(aligned\(8\)\)\))? = \{\n(.*?)\n\};', re.M | re.S)
RAW32_DEF = re.compile(r'^()((?:static )?(?:const )?)unsigned int (\w+)\[(\d+)\]( __attribute__\(\(aligned\(8\)\)\))? = \{[ \n]*((?:0x[0-9A-Fa-f]+[,\s]*)+?)[ \n]*\};', re.M)


def s16(x):
    return x - 0x10000 if x >= 0x8000 else x


def column_kind(vals):
    """'f' float column, 'i' small integers, 'b' one byte then three zero bytes, 's' two 16-bit values;
    None when the values do not decide."""
    nz = [v for v in vals if v]
    if not nz: return 'i'
    wide = [v for v in nz if not floatlike(v)]   # -0.0 and very small/large magnitudes: fine next to ordinary floats
    if len(wide) * 5 <= len(nz) and all(v == 0x80000000 or 0x40 <= ((v >> 23) & 0xFF) <= 0xC0 for v in wide) \
            and all(fmt_float(v) for v in vals): return 'f'
    if all(v < 0x10000 or v >= 0xFFFF0000 for v in nz): return 'i'
    if all(v & 0xFFFFFF == 0 for v in nz): return 'b'
    if all(abs(s16(v >> 16)) < 0x4000 and abs(s16(v & 0xFFFF)) < 0x4000 for v in nz): return 's'
    return None


def infer_rows(words):
    """-> (period, kinds) for the smallest period whose every column has a kind."""
    n = len(words)
    for p in range(1, min(64, n // 2) + 1):
        if n % p: continue
        kinds = [column_kind(words[c::p]) for c in range(p)]
        if all(kinds): return p, kinds
    return None


def text_pool(words):
    """The object as a list of C string literals when it is nothing but text (a string pool), else None."""
    bs = b''.join(w.to_bytes(4, 'big') for w in words)
    body = bs.rstrip(b'\0')
    if len(body) < 4 or len(bs) - len(body) > 4: return None
    printable = sum(1 for x in body if 32 <= x < 127)
    if any(not (32 <= x < 127 or x in (0, 9, 10, 13) or x >= 0x80) for x in body): return None
    if printable * 10 < len(body) * 6 or b'\0\0\0\0' in body: return None
    parts = body.split(b'\0')
    if any(len(x) == 1 for x in parts if x) and len(parts) > 2 and sum(len(x) <= 1 for x in parts) * 2 > len(parts): return None
    return parts


def _text_word(w):
    """0 no text, else number of characters: the non-zero bytes are a prefix and look like text
    (ASCII, or Shift-JIS double-byte pairs are checked by the caller on the whole run)."""
    bs = w.to_bytes(4, 'big').rstrip(b'\0')
    if not bs or b'\0' in bs: return 0
    if any(not (32 <= x < 127 or x in (9, 10, 13) or 0x81 <= x <= 0x9F or 0xE0 <= x <= 0xEA or 0x40 <= x <= 0xFC) for x in bs): return 0
    return len(bs)


def _sjis_ok(bs):
    i = 0
    while i < len(bs):
        x = bs[i]
        if x < 0x80: i += 1; continue
        if not (0x81 <= x <= 0x9F or 0xE0 <= x <= 0xEA) or i + 1 >= len(bs) or not (0x40 <= bs[i + 1] <= 0xFC): return False
        i += 2
    return True


def mixed_pool(words):
    """Split an anchor pool into strings and numbers: -> [(kind, first word, n words)] with kind
    's' (one NUL-terminated string, zero padded), 'f' or 'i'; None when a word fits nothing."""
    n = len(words)
    segs = []
    i = 0
    while i < n:
        j = i
        while j < n and _text_word(words[j]) == 4: j += 1
        if j < n and (_text_word(words[j]) or (j > i and words[j] == 0)):
            bs = b''.join(w.to_bytes(4, 'big') for w in words[i:j + 1]).rstrip(b'\0')
            ascii_ = sum(1 for x in bs if 32 <= x < 127)
            ok = _sjis_ok(bs) and (len(bs) >= 3 or (len(bs) == 2 and bs.isalpha() and segs and segs[-1][0] == 's'))
            if ok and len(bs) <= 4 and not (bs.isalnum() or ascii_ == len(bs) and not floatlike(words[i])): ok = False
            if ok and len(bs) == 4 and words[j] != 0 and j == i: ok = False   # four characters and no terminator
            if ok:
                segs.append(('s', i, j + 1 - i)); i = j + 1; continue
        w = words[i]
        if w < 0x10000 or w >= 0xFFFF0000: k = 'i'
        elif floatlike(w) and fmt_float(w): k = 'f'
        else: return None
        if segs and segs[-1][0] == k: segs[-1] = (k, segs[-1][1], segs[-1][2] + 1)
        else: segs.append((k, i, 1))
        i += 1
    if not any(k == 's' for k, _, _ in segs): return None
    return segs


def cmd_infer(a):
    """Give unk32 word tables a type read off the values: text pools, and rows whose every column is
    all floats, all small integers, single bytes or 16-bit pairs."""
    files = [os.path.join(OUTDIR, os.path.basename(u) if u.endswith('.c') else os.path.basename(u) + '.c') for u in a.units] \
        or sorted(glob.glob(os.path.join(OUTDIR, '*.c')))
    if a.raw:   # normal TUs: one-line `unsigned int x[N] = { ... };` word dumps
        files = [os.path.join(ROOT, u) for u in a.units]
    total = 0
    CT = {'f': 'float', 'i': 'int'}
    for f in files:
        text = open(f, encoding='utf-8').read()
        types = []

        def repl(m):
            nonlocal total
            note, quals, name, cnt, attr, body = m.groups()
            words = [int(x, 16) for x in re.findall(r'0x[0-9A-Fa-f]+', body)]
            if len(words) != int(cnt) or len(words) < a.min_words: return m.group(0)
            attr = attr or ''
            parts = text_pool(words)
            if parts is not None:
                total += 4 * len(words)
                lit = ' "\\0"\n    '.join(D.c_string(x) for x in parts)
                return '%s/* text only: a string pool (strings back to back, the code points into it) */\n%schar %s[%d]%s =\n    %s;' % (
                    note, quals, name, 4 * len(words), attr, lit)
            r = infer_rows(words)
            if r is None:
                segs = mixed_pool(words)
                if segs is None: return m.group(0)
                total += 4 * len(words)
                tn = name + '_Pool'
                mem, vals = [], []
                for k, i0, cnt_ in segs:
                    o = 4 * i0
                    if k == 's':
                        bs = b''.join(w.to_bytes(4, 'big') for w in words[i0:i0 + cnt_]).rstrip(b'\0')
                        mem.append('    char s_%03X[%d];' % (o, 4 * cnt_)); vals.append('    ' + D.c_string(bs))
                    else:
                        vs = [fmt_float(w) if k == 'f' else str(w if w < 0x80000000 else w - (1 << 32)) for w in words[i0:i0 + cnt_]]
                        if cnt_ == 1:
                            mem.append('    %s %s_%03X;' % (CT[k], k, o)); vals.append('    ' + vs[0])
                        else:
                            mem.append('    %s %s_%03X[%d];' % (CT[k], k, o, cnt_)); vals.append('    { ' + ', '.join(vs) + ' }')
                types.append('/* anchor pool cut into its strings and numbers by value (text, floats, small integers),\n'
                             ' * not from code */\n'
                             'typedef struct %s {\n%s\n} %s;' % (tn, '\n'.join(mem), tn))
                return '%s%s%s %s%s = {\n%s\n};' % (note, quals, tn, name, attr, ',\n'.join(vals))
            p, kinds = r

            def val(w, k):
                if k == 'f': return fmt_float(w)
                if k == 'i': return str(w if w < 0x80000000 else w - (1 << 32))
                if k == 'b': return '%d, { 0, 0, 0 }' % (w >> 24)
                return '%d, %d' % (s16(w >> 16), s16(w & 0xFFFF))
            if p == 1:
                if kinds[0] == 'b': return m.group(0)
                total += 4 * len(words)
                if kinds[0] == 's':
                    vals = [val(w, 's') for w in words]
                    return '%s/* element type read off the values (16-bit pairs), not from code */\n%sshort %s[%d]%s = {\n%s\n};' % (
                        note, quals, name, 2 * len(words), attr, wrap(vals, 6))
                ty = CT[kinds[0]]
                vals = [val(w, kinds[0]) for w in words]
                return '%s/* element type read off the values (all %s), not from code */\n%s%s %s[%d]%s = {\n%s\n};' % (
                    note, 'floats' if ty == 'float' else 'small integers', quals, ty, name, len(words), attr, wrap(vals))
            total += 4 * len(words)
            tn = name + '_Row'
            mem = []
            for c, k in enumerate(kinds):
                o = 4 * c
                if k in CT: mem.append('    %s %s_%02X;' % (CT[k], k, o))
                elif k == 'b': mem.append('    unsigned char b_%02X;\n    unsigned char pad_%02X[3];' % (o, o + 1))
                else: mem.append('    short s_%02X;\n    short s_%02X;' % (o, o + 2))
            types.append('/* row layout read off the values (per column: all floats, all small integers, one byte, or\n'
                         ' * two 16-bit values), not from code */\n'
                         'typedef struct %s {\n%s\n} %s;' % (tn, '\n'.join(mem), tn))
            rows = ['    { ' + ', '.join(val(words[i + c], kinds[c]) for c in range(p)) + ' }' for i in range(0, len(words), p)]
            return '%s%s%s %s[%d]%s = {\n%s\n};' % (note, quals, tn, name, len(words) // p, attr, ',\n'.join(rows))

        if a.raw:
            def raw_repl(m):
                if len(re.findall(r'[^,\s][^,]*', m.group(6))) != int(m.group(4)) or int(m.group(4)) < 16: return m.group(0)
                k = len(types)
                out = repl(m)
                mine = types[k:]; del types[k:]
                return ''.join(t + '\n' for t in mine) + out
            new = RAW32_DEF.sub(raw_repl, text)
        else:
            new = UNK32_DEF.sub(repl, text)
        if new == text: continue
        if types:
            prag = '\n#pragma explicit_zero_data on'
            i = new.index(prag)
            new = new[:i].rstrip('\n') + '\n\n' + '\n\n'.join(types) + '\n' + new[i:]
        open(f, 'w', encoding='utf-8').write(new)
        print('inferred', os.path.relpath(f, ROOT))
    print('%d bytes typed from their values' % total)


# ---------------------------------------------------------------- check (ELF compare)

def elf_sections(path):
    d = open(path, 'rb').read()
    shoff, = struct.unpack_from('>I', d, 0x20)
    shentsize, shnum, shstrndx = struct.unpack_from('>HHH', d, 0x2E)
    sh = [struct.unpack_from('>10I', d, shoff + i * shentsize) for i in range(shnum)]

    def cstr(base, off):
        return d[base + off:d.index(b'\0', base + off)].decode('latin-1')
    names = [cstr(sh[shstrndx][4], s[0]) for s in sh]
    symtab = next((i for i, s in enumerate(sh) if s[1] == 2), None)
    syms = []
    if symtab is not None:
        st = sh[symtab]; strb = sh[st[6]][4]
        for j in range(st[5] // 16):
            nm, val, size, info, other, shndx = struct.unpack_from('>IIIBBH', d, st[4] + j * 16)
            syms.append((cstr(strb, nm), val, size, info, shndx))
    out = {}
    for i, s in enumerate(sh):
        if s[1] in (1,) and names[i] in SECS:
            out[names[i]] = {'data': d[s[4]:s[4] + s[5]], 'align': s[8], 'rel': [], 'syms': {}}
    for i, s in enumerate(sh):
        if s[1] == 4 and names[s[7]] in out:
            for j in range(s[5] // 12):
                off, info, add = struct.unpack_from('>IIi', d, s[4] + j * 12)
                sy = syms[info >> 8]
                tgt = sy[0]
                if (sy[3] & 0xF) == 3:   # section symbol: resolve through the object at that offset
                    tgt = '%s+%X' % (names[sy[4]], add); add = 0
                out[names[s[7]]]['rel'].append((off, info & 0xFF, tgt, add))
    for nm, val, size, info, shndx in syms:
        if shndx < len(names) and names[shndx] in out and (info & 0xF) == 1:
            out[names[shndx]]['syms'][nm] = (val, size, info >> 4)
    return out


def check_unit(u):
    """-> None if the built object equals the target object, else a short reason."""
    stem = u[:-2] if u.endswith('.c') else u
    mine = os.path.join(ROOT, 'build', VER, 'src', stem + '.o')
    tgt = os.path.join(ROOT, 'build', VER, 'obj', stem + '.o')
    if not os.path.exists(mine): return 'not built'
    if not os.path.exists(tgt): return 'no target object'
    A, B = elf_sections(mine), elf_sections(tgt)
    for sec in B:
        if sec not in A: return 'no %s in built object' % sec
        a, b = A[sec], B[sec]
        if len(a['data']) != len(b['data']):
            # the split end is rounded up to 4, so the target may carry up to 3 pad bytes
            if not (len(a['data']) < len(b['data']) <= (len(a['data']) + 3 & ~3) and not any(b['data'][len(a['data']):])):
                return '%s size %X, target %X' % (sec, len(a['data']), len(b['data']))
            b['data'] = b['data'][:len(a['data'])]
        if a['data'] != b['data']:
            i = next(i for i in range(len(b['data'])) if a['data'][i] != b['data'][i])
            return '%s differs at +%X' % (sec, i)
        # relocations: compare by resolved (symbol, addend); local names differ, so map section+offset to target names
        tsym = {(v[0]): n for n, v in b['syms'].items()}
        asym = {(v[0]): n for n, v in a['syms'].items()}

        def norm(r, table):
            off, typ, tg, add = r
            if '+' in tg and tg.split('+')[0] == sec:
                o = int(tg.split('+')[1], 16)
                return (off, typ, table.get(o, tg), add)
            return (off, typ, tg, add)
        ra = sorted(norm(r, asym) for r in a['rel']); rb = sorted(norm(r, tsym) for r in b['rel'])
        if ra != rb:
            d = next((x, y) for x, y in zip(ra + [None], rb + [None]) if x != y)
            return '%s relocation differs: %s vs target %s' % (sec, d[0], d[1])
        for n, (v, s, bind) in b['syms'].items():
            if n.startswith(('gap_', 'pad_')): continue
            if n not in a['syms']: return 'symbol %s missing' % n
            if a['syms'][n][0] != v: return 'symbol %s at %X, target %X' % (n, a['syms'][n][0], v)
    for sec in A:
        if sec not in B and A[sec]['data']: return 'extra section %s (%d bytes)' % (sec, len(A[sec]['data']))
    return None


def cmd_check(a):
    units = a.units or sorted('game/autodata/' + os.path.basename(f) for f in glob.glob(os.path.join(OUTDIR, '*.c')))
    bad = 0
    for u in units:
        r = check_unit(u)
        if r: bad += 1; print('FAIL %s: %s' % (u, r))
    print('%d units, %d differ' % (len(units), bad))
    return 1 if bad else 0


# ---------------------------------------------------------------- report

def cmd_report(a):
    ctx = Ctx()
    rows = collections.OrderedDict()
    for sec in SECS:
        noc = sum(o['size'] for o in ctx.objs.get(sec, []) if not ctx.owned(sec, o['addr']) and not o['name'].startswith(('gap_', 'pad_')))
        rows[sec] = [noc, 0, 0]
    DEF = re.compile(r'^(?!extern)([^ /#\n][^=\n]*?)\b(\w+)((?:\[[^\]\n]*\])*)(?: __attribute__\(\(aligned\(8\)\)\))? = ', re.M)
    for f in sorted(glob.glob(os.path.join(OUTDIR, '*.c'))):
        sec = '.' + os.path.basename(f).split('_')[0]
        t = open(f, encoding='utf-8', errors='replace').read()
        for m in DEF.finditer(t):
            ad = ctx.m.byname.get(m.group(2))
            o = ctx.m.objs.get(ad)
            if not o: continue
            rows[sec][1 if re.search(r'\bunk(8|16|32)\b', m.group(1)) else 2] += o['size']
    lines = ['| Section | No C definition | In `src/game/autodata`, layout unknown (`unk*`) | In `src/game/autodata`, typed |',
             '|---|---|---|---|']
    for sec, (x, y, z) in rows.items():
        lines.append('| %s | %d | %d | %d |' % (sec, x, y, z))
    lines.append('| total | %d | %d | %d |' % tuple(sum(r[i] for r in rows.values()) for i in range(3)))
    out = '\n'.join(lines)
    print(out)
    if a.md:
        open(a.md, 'w').write('# Initialised data without a typed C definition\n\n'
                              'Bytes, from `python3 tools/autodata.py report` (docs/notes/autodata.md).\n\n' + out + '\n')


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest='cmd', required=True)
    p = sub.add_parser('runs'); p.add_argument('--sec'); p.add_argument('--top', type=int, default=40)
    p = sub.add_parser('gen'); p.add_argument('sec', nargs='?'); p.add_argument('lo', nargs='?'); p.add_argument('hi', nargs='?')
    p.add_argument('--all', action='store_true'); p.add_argument('--sec', dest='sec_opt'); p.add_argument('--dry', action='store_true')
    p.add_argument('--min', type=lambda x: int(x, 0), default=0)
    p = sub.add_parser('check'); p.add_argument('units', nargs='*')
    p = sub.add_parser('drop'); p.add_argument('units', nargs='+')
    p = sub.add_parser('retype'); p.add_argument('units', nargs='*')
    p = sub.add_parser('infer'); p.add_argument('units', nargs='*'); p.add_argument('--min-words', type=int, default=2)
    p.add_argument('--raw', action='store_true', help='units are normal source files: retype their unsigned int word dumps')
    p = sub.add_parser('report'); p.add_argument('--md')
    a = ap.parse_args()
    if a.cmd == 'gen' and a.sec_opt: a.sec = a.sec_opt
    return {'runs': cmd_runs, 'gen': cmd_gen, 'check': cmd_check, 'drop': cmd_drop, 'report': cmd_report, 'retype': cmd_retype, 'infer': cmd_infer}[a.cmd](a)


if __name__ == '__main__':
    sys.exit(main() or 0)
