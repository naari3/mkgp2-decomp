#!/usr/bin/env python3
"""cperm.py - text-level permuter for C/C++ TUs (pycparser-free), mkgp2-decomp.

Randomly rewrites one or more source regions (a function body and/or the inline
helpers it uses), recompiles with the TU's own ninja command (incl. the
extab_user / sdata2 postprocess), and hill-climbs on an asm diff score against
the dtk target asm. Works on any TU that mwcc compiles, C or C++.

usage (from repo root):
  python3 cperm.py SRC OBJ FN --region 'extern "C" void fn_802170F0(' [--region ...]
                   [--cc 2.6] [--workers 4] [--minutes 30] [--seed N] [--out DIR]

  SRC     source file (e.g. src/game/Foo.cpp); it is never modified
  OBJ     object name as in build (e.g. game/Foo)
  FN      target symbol name as in the target asm (.fn NAME,)
  REGION  a unique line prefix inside SRC; the region is that line up to its
          matching closing brace (a function or an inline helper).

Score = weighted asm diff (0 = byte-identical text modulo labels/@N names).
Every improvement is written to OUT/best_<score>.cpp. On a 0 the run stops.
A 0 is a candidate only: rebuild for real, check the .o, and the full main.dol
SHA (an `@N` rename shift is invisible to this score).
Mark permuter output that is not natural code with
`/* fakematch (permuter): ... */` + the natural code (docs/per_fn_matching_strategy.md).
"""
import argparse, difflib, glob, multiprocessing as mp, os, random, re, shlex, subprocess, sys, time

ROOT = os.getcwd()

# ---------------------------------------------------------------- target / build

def ninja_cmd(obj):
    out = subprocess.run(['ninja', '-t', 'commands', f'build/GNLJ82/src/{obj}.o'],
                         capture_output=True, text=True).stdout.strip().splitlines()[-1]
    parts = out.split(' && ')
    post = [p for p in parts[1:] if 'transform_dep' not in p]
    if os.environ.get('CPERM_SKIP_SDATA2'):  # literal order never changes the code score; ~2x faster
        post = [p for p in post if 'postprocess_sdata2' not in p]
    return shlex.split(parts[0]), post

LINE_RE = re.compile(r'/\* [0-9A-F]+ [0-9A-F]+  (?:.. .. .. ..) \*/\t(.*)')

def asm_body(text, fn):
    out = []; on = False
    for l in text.splitlines():
        if l.startswith('.fn ' + fn + ','): on = True; continue
        if on and l.startswith('.endfn'): break
        if on:
            m = LINE_RE.match(l)
            if m: out.append(m.group(1))
            elif l.strip().startswith('.L'): out.append('.L')
    # relocated symbol operands are compared by kind only (objdiff tolerates name drift: lbl_X vs ...bss.0)
    return [re.sub(r'[^\s,()]+@(ha|h|l|sda21)\b', r'S@\1', re.sub(r'\.L_[0-9A-F]+', '.L', re.sub(r'"?@\d+"?|jumptable_[0-9A-Fa-f]+', '@N', x))) for x in out]

def target_body(fn):
    for p in glob.glob('build/GNLJ82/asm/**/*.s', recursive=True):
        t = open(p).read()
        if ('.fn ' + fn + ',') in t: return asm_body(t, fn)
    sys.exit('target fn not found in build/GNLJ82/asm')

def score(a, b):
    if not b: return 10**6
    s = 0
    for op, i1, i2, j1, j2 in difflib.SequenceMatcher(None, a, b, autojunk=False).get_opcodes():
        if op == 'equal': continue
        if op == 'replace':
            n = min(i2 - i1, j2 - j1)
            for k in range(n):
                x, y = a[i1 + k].split(), b[j1 + k].split()
                s += 1 if x[:1] == y[:1] else 3
            s += 5 * abs((i2 - i1) - (j2 - j1))
        else:
            s += 5 * max(i2 - i1, j2 - j1)
    return s

class Builder:
    def __init__(self, obj, fn, cc, wdir):
        self.obj, self.fn, self.wdir = obj, fn, wdir
        args, self.post = ninja_cmd(obj)
        if cc: args = [re.sub(r'GC/[^/]+/mwcceppc', f'GC/{cc}/mwcceppc', a) for a in args]
        if '-MMD' in args: args.remove('-MMD')
        self.args = args
        self.o = os.path.join(wdir, 'src', obj + '.o')   # path must contain /src/ for the rename hook
        os.makedirs(os.path.dirname(self.o), exist_ok=True)

    def build(self, src_path):
        a = list(self.args); i = a.index('-c'); a[i + 1] = src_path; a[i + 3] = self.o
        if os.path.exists(self.o): os.remove(self.o)
        r = subprocess.run(a, capture_output=True, text=True)
        if r.returncode or not os.path.exists(self.o): return None
        tgt = f'build/GNLJ82/src/{self.obj}.o'
        for p in self.post:
            pa = [self.o if x == tgt else x for x in shlex.split(p)]
            if 'postprocess_sdata2' in p and '--target' not in p:
                pa += ['--target', f'build/GNLJ82/obj/{self.obj}.o']
            if subprocess.run(pa, capture_output=True).returncode: return None
        s = os.path.join(self.wdir, 'out.s')
        if subprocess.run(['build/tools/dtk', 'elf', 'disasm', self.o, s], capture_output=True).returncode:
            return None
        return asm_body(open(s).read(), self.fn)

# ---------------------------------------------------------------- regions

def auto_regions(src, srcpath, fn):
    """Target function (by name, or by its C++ name from extab_user_renames.json) + inline helpers."""
    import json
    names = [fn + '(']
    try:
        ren = json.load(open('tools/extab_user_renames.json')).get(os.path.relpath(srcpath, ROOT), {})
        for mangled, tgt in ren.items():
            if tgt != fn: continue
            m = re.match(r'(\w+?)__(\d+)(\w+)', mangled)
            if mangled.startswith('__ct__'):
                m2 = re.match(r'__ct__(\d+)(\w+)', mangled); n = int(m2.group(1)); c = m2.group(2)[:n]
                names.append(f'{c}::{c}(')
            elif mangled.startswith('__dt__'):
                m2 = re.match(r'__dt__(\d+)(\w+)', mangled); n = int(m2.group(1)); c = m2.group(2)[:n]
                names.append(f'{c}::~{c}(')
            elif m:
                n = int(m.group(2)); names.append(f'{m.group(3)[:n]}::{m.group(1)}(')
    except Exception:
        pass
    out = []
    for nm in names:
        for mm in re.finditer(re.escape(nm), src):
            # definition: followed by ')' ... '{' before ';'
            rest = src[mm.end():]
            k = rest.find('{'); sc = rest.find(';')
            if k >= 0 and (sc < 0 or k < sc):
                ls = src.rfind('\n', 0, mm.start()) + 1
                out.append(src[ls:mm.end()])
                break
        if out: break
    if not out: sys.exit(f'cannot find definition of {fn} ({names})')
    for mm in re.finditer(r'^[ \t]*(?:static\s+)?inline\b[^;{]*\(', src, re.M):
        line = src[mm.start():mm.end()]
        rest = src[mm.end():]; k = rest.find('{'); sc = rest.find(';')
        if k >= 0 and (sc < 0 or k < sc) and src.count(line) == 1:
            out.append(line)
    return out

def find_region(src, prefix):
    """Region = body of the first occurrence of PREFIX that is a definition ('{' before ';')."""
    i = -1
    while True:
        i = src.find(prefix, i + 1)
        if i < 0: raise SystemExit(f'region definition not found: {prefix!r}')
        rest = src[i + len(prefix):]; k = rest.find('{'); sc = rest.find(';')
        if k >= 0 and (sc < 0 or k < sc): break
    j = i + len(prefix) + k; d = 0
    for k in range(j, len(src)):
        if src[k] == '{': d += 1
        elif src[k] == '}':
            d -= 1
            if d == 0: return (j + 1, k)   # body without the outer braces
    raise SystemExit('unbalanced braces')

# ---------------------------------------------------------------- mutations
IDENT = r'[A-Za-z_]\w*'
ATOM = rf'(?:{IDENT}(?:(?:->|\.){IDENT}|\[[^\[\]]+\])*|\d+(?:\.\d*)?f?)'
DECL_RE = re.compile(rf'^(\s*)((?:const\s+|unsigned\s+|signed\s+|static\s+)*{IDENT}(?:\s*\*+\s*|\s+)){IDENT}\s*=\s*[^;]+;\s*$')
TYPES = ['int', 'unsigned int', 'short', 'unsigned char', 'char', 'long', 'float', 'bool']

def lines_of(body):
    return body.split('\n')

def simple_stmt(l):
    s = l.strip()
    return s.endswith(';') and '{' not in s and '}' not in s and not s.startswith(('return', 'break', 'continue', 'case', 'default', 'goto'))

def m_swap_adjacent(b):
    L = lines_of(b); idx = [i for i in range(len(L) - 1) if simple_stmt(L[i]) and simple_stmt(L[i + 1])
                            and len(L[i]) - len(L[i].lstrip()) == len(L[i + 1]) - len(L[i + 1].lstrip())]
    if not idx: return None
    i = random.choice(idx); L[i], L[i + 1] = L[i + 1], L[i]; return '\n'.join(L)

def m_move_decl(b):
    L = lines_of(b); idx = [i for i, l in enumerate(L) if DECL_RE.match(l)]
    if not idx: return None
    i = random.choice(idx); ind = L[i][:len(L[i]) - len(L[i].lstrip())]
    j = i + random.choice([-2, -1, 1, 2])
    if not (0 <= j < len(L)) or not simple_stmt(L[j]) or not L[j].startswith(ind) or L[j][len(ind):len(ind)+1].isspace(): return None
    l = L.pop(i); L.insert(j, l); return '\n'.join(L)

def m_split_decl(b):
    L = lines_of(b); idx = [i for i, l in enumerate(L) if DECL_RE.match(l)]
    if not idx: return None
    i = random.choice(idx); m = DECL_RE.match(L[i]); ind, ty = m.group(1), m.group(2)
    rest = L[i][m.end(2):]; name = rest.split('=')[0].strip()
    L[i:i + 1] = [f'{ind}{ty}{name};', f'{ind}{rest.strip()}']; return '\n'.join(L)

def m_commute(b):
    ops = [r'\+', r'\*', '&', r'\|', '==', '!=', r'\^']
    ms = [m for op in ops for m in re.finditer(rf'(?<![\w\]\)>.])({ATOM})\s*({op})\s*({ATOM})(?![\w\[(.]|->)', b)]
    ms = [m for m in ms if not (m.group(2) in ('&', '*') and b[max(0, m.start() - 1):m.start()].strip() == '')
          or m.start() == 0 or b[m.start() - 1] not in '(,=' ]
    if not ms: return None
    m = random.choice(ms)
    return b[:m.start()] + f'{m.group(3)} {m.group(2)} {m.group(1)}' + b[m.end():]

def m_flip_cmp(b):
    flip = {'<': '>', '>': '<', '<=': '>=', '>=': '<='}
    ms = list(re.finditer(rf'({ATOM})\s*(<=|>=|<|>)\s*({ATOM})', b))
    ms = [m for m in ms if '<' not in m.group(0)[:-1].replace(m.group(2), '', 1) and not m.group(0).startswith('template')]
    if not ms: return None
    m = random.choice(ms)
    return b[:m.start()] + f'{m.group(3)} {flip[m.group(2)]} {m.group(1)}' + b[m.end():]

def m_bool_form(b):
    c = [(r'(\([^()]*\S)\s*!=\s*0\)', r'\1 ? 1 : 0)'), (r'([=,(]\s*)([^;,()?]+?)\s*!=\s*0\s*;', r'\1\2 ? 1 : 0;'),
         (r'\?\s*1\s*:\s*0', '!= 0'), (r'!\s*(' + ATOM + r')(?=\s*[)&|;])', r'\1 == 0')]
    random.shuffle(c)
    for pat, rep in c:
        ms = list(re.finditer(pat, b))
        if ms:
            m = random.choice(ms); return b[:m.start()] + m.expand(rep) + b[m.end():]
    return None

def m_incdec(b):
    ms = list(re.finditer(rf'(\+\+|--)({IDENT})\b|\b({IDENT})(\+\+|--)', b))
    if not ms: return None
    m = random.choice(ms)
    r = f'{m.group(2)}{m.group(1)}' if m.group(1) else f'{m.group(4)}{m.group(3)}'
    return b[:m.start()] + r + b[m.end():]

def m_temp_expr(b):
    # hoist a member/array read into a local just before its statement
    L = lines_of(b); cand = []
    for i, l in enumerate(L):
        if not simple_stmt(l): continue
        for m in re.finditer(rf'{IDENT}(?:->|\.){IDENT}(?:(?:->|\.){IDENT})*', l):
            if re.match(r'\s*(=[^=]|\+\+|--|[-+*/|&^]=)', l[m.end():]) or l[m.end():m.end()+1] == '(':
                continue
            cand.append((i, m))
    if not cand: return None
    i, m = random.choice(cand); ind = L[i][:len(L[i]) - len(L[i].lstrip())]
    t = f'_t{random.randint(0, 999)}'; ty = random.choice(['int', 'unsigned int', 'float', 'auto_ptr'])
    if ty == 'auto_ptr': return None
    L[i] = L[i][:m.start()] + t + L[i][m.end():]
    L.insert(i, f'{ind}{ty} {t} = {m.group(0)};'); return '\n'.join(L)

def m_retype(b):
    L = lines_of(b); idx = [i for i, l in enumerate(L) if DECL_RE.match(l)]
    if not idx: return None
    i = random.choice(idx); m = DECL_RE.match(L[i]); ty = m.group(2).strip()
    if '*' in ty or ty not in TYPES: return None
    nt = random.choice([t for t in TYPES if t != ty])
    L[i] = m.group(1) + nt + ' ' + L[i][m.end(2):]; return '\n'.join(L)

def m_brace(b):
    L = lines_of(b); idx = [i for i, l in enumerate(L) if simple_stmt(l)]
    if not idx: return None
    i = random.choice(idx); ind = L[i][:len(L[i]) - len(L[i].lstrip())]
    k = i + 1 if random.random() < .5 and i + 1 < len(L) and simple_stmt(L[i + 1]) else i
    L[i] = ind + '{ ' + L[i].strip(); L[k] = L[k] + ' }'; return '\n'.join(L)

def m_register(b):
    L = lines_of(b); idx = [i for i, l in enumerate(L) if DECL_RE.match(l)]
    if not idx: return None
    i = random.choice(idx); m = DECL_RE.match(L[i])
    if 'register' in L[i]: L[i] = L[i].replace('register ', '', 1)
    else: L[i] = m.group(1) + 'register ' + L[i][len(m.group(1)):]
    return '\n'.join(L)

MUTS = [(m_swap_adjacent, 3), (m_move_decl, 3), (m_split_decl, 1), (m_commute, 3), (m_flip_cmp, 1),
        (m_bool_form, 1), (m_incdec, 1), (m_temp_expr, 2), (m_retype, 1), (m_brace, 1), (m_register, 1)]

def mutate(regs):
    regs = list(regs)
    for _ in range(random.choice([1, 1, 1, 2, 3])):
        i = random.randrange(len(regs))
        for _ in range(20):
            f = random.choices([m for m, _ in MUTS], [w for _, w in MUTS])[0]
            r = f(regs[i])
            if r is not None and r != regs[i]: regs[i] = r; break
    return regs

# ---------------------------------------------------------------- driver

def assemble(src, spans, regs):
    out = []; last = 0
    for (a, b), r in zip(spans, regs):
        out.append(src[last:a]); out.append(r); last = b
    out.append(src[last:]); return ''.join(out)

def worker(wid, a, q_best, deadline, seed):
    try:
        _worker(wid, a, q_best, deadline, seed)
    except BaseException as e:
        print(f'w{wid} failed: {e!r}', flush=True)
        q_best.put((wid, None, None, 0))

def _worker(wid, a, q_best, deadline, seed):
    random.seed(seed + wid * 7919)
    src = open(a.src).read()
    spans = sorted(set(find_region(src, p) for p in a.region))
    spans = [sp for n, sp in enumerate(spans) if not any(o[0] <= sp[0] and sp[1] <= o[1] and o != sp for o in spans)]
    base = [src[x:y] for x, y in spans]
    wdir = os.path.join(a.out, f'w{wid}'); os.makedirs(wdir, exist_ok=True)
    B = Builder(a.obj, a.fn, a.cc, wdir); T = target_body(a.fn)
    ext = os.path.splitext(a.src)[1]; sp = os.path.join(os.path.dirname(os.path.abspath(a.src)), f'.cperm_w{wid}{ext}')
    def evaluate(regs):
        open(sp, 'w').write(assemble(src, spans, regs))
        return score(T, B.build(sp) or [])
    cur = base; cs = evaluate(cur); best = cs; n = 0
    q_best.put((wid, cs, assemble(src, spans, cur), 0))
    try:
        while time.time() < deadline and best > 0:
            cand = mutate(cur); s = evaluate(cand); n += 1
            if s < best:
                best = s; q_best.put((wid, s, assemble(src, spans, cand), n))
            if s <= cs or (s < 10**6 and random.random() < 0.03):
                cur, cs = cand, s
            if random.random() < 0.002: cur, cs = base, evaluate(base)   # restart
    finally:
        if os.path.exists(sp): os.remove(sp)
    q_best.put((wid, None, None, n))
    return

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('src'); ap.add_argument('obj'); ap.add_argument('fn')
    ap.add_argument('--region', action='append')
    ap.add_argument('--cc'); ap.add_argument('--workers', type=int, default=max(1, os.cpu_count() or 1))
    ap.add_argument('--minutes', type=float, default=30); ap.add_argument('--seed', type=int, default=int(time.time()))
    ap.add_argument('--out', default=None)
    a = ap.parse_args()
    if not a.region:
        a.region = auto_regions(open(a.src).read(), a.src, a.fn)
    print('regions:', [r.strip()[:60] for r in a.region], flush=True)
    a.out = a.out or os.path.join('/tmp', 'cperm_' + a.fn); os.makedirs(a.out, exist_ok=True)
    q = mp.Queue(); dl = time.time() + a.minutes * 60
    ps = [mp.Process(target=worker, args=(i, a, q, dl, a.seed)) for i in range(a.workers)]
    for p in ps: p.start()
    best = None; done = 0; total = 0; ext = os.path.splitext(a.src)[1]
    while done < len(ps):
        wid, s, text, n = q.get()
        if s is None: done += 1; total += n; continue
        if best is None or s < best:
            best = s; open(os.path.join(a.out, f'best_{s:05d}{ext}'), 'w').write(text)
            print(f'[{time.strftime("%H:%M:%S")}] w{wid} iter {n}: score {s}', flush=True)
            if s == 0:
                print('MATCH ->', os.path.join(a.out, f'best_00000{ext}'), flush=True)
                for p in ps: p.terminate()
                break
    for p in ps: p.join()
    print(f'done: best {best}, iters ~{total}', flush=True)

if __name__ == '__main__':
    main()
