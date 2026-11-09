#!/usr/bin/env python3
"""declsweep.py: brute-force the ORDER of a function's leading local declarations.

CW numbers user variables in declaration order and that number breaks
register-coloring ties, so a near-miss that is only a register permutation
can match with the right order (CharaSelect_SetupCharacterDisplay, 664ab80).

usage (repo root, after a normal build):
  python3 declsweep.py SRC OBJ FN [-n 600] [-j 6] [--cc 2.6]
    SRC  src/game/Foo.c      OBJ game/Foo      FN function name (or mangled)
Only the block of plain declarations (no initializer) right after the
function's opening brace is permuted. Prints the best score and writes the
best source to /tmp/claude-0/declsweep/<FN>.best.<ext>.
"""
import argparse, os, re, random, subprocess, sys, glob, difflib, shutil
from concurrent.futures import ThreadPoolExecutor

ap = argparse.ArgumentParser()
ap.add_argument('src'); ap.add_argument('obj'); ap.add_argument('fn')
ap.add_argument('-n', type=int, default=600); ap.add_argument('-j', type=int, default=6)
ap.add_argument('--cc'); ap.add_argument('--mine')
ap.add_argument('--hoist', action='store_true', help='first hoist scalar/pointer declarations from the whole body to the top')
a = ap.parse_args()
ROOT = os.getcwd()
cmd = subprocess.run(['ninja', '-t', 'commands', f'build/GNLJ82/src/{a.obj}.o'], capture_output=True, text=True).stdout.strip().splitlines()[-1]
cc = cmd.split(' && ')[0].replace(' -MMD', '')
if a.cc: cc = re.sub(r'GC/[^/]+/mwcceppc', f'GC/{a.cc}/mwcceppc', cc)

def body(path, fn, raw=False):
    out = []; on = False
    for l in open(path, errors='replace'):
        if l.startswith('.fn ' + fn + ','): on = True; continue
        if on and l.startswith('.endfn'): break
        if on:
            m = re.match(r'/\* [0-9A-F]+ [0-9A-F]+  (.. .. .. ..) \*/\t(.*)', l)
            if m:
                x = re.sub(r'^bl \S+', 'bl F', re.sub(r'\.L_[0-9A-F]+', '.L', m.group(2)))
                x = re.sub(r'[\w"@.$]+@(ha|l|sda21)', r'S@\1', x)
                out.append(x)
    return out

tp = [p for p in glob.glob('build/GNLJ82/asm/**/*.s', recursive=True) if '.fn ' + a.fn + ',' in open(p, errors='replace').read()]
if not tp: sys.exit('target fn not found in build/GNLJ82/asm')
T = body(tp[0], a.fn)
ext = os.path.splitext(a.src)[1]
srcdir = os.path.dirname(os.path.abspath(a.src))

def score(text, k):
    d = f'/tmp/claude-0/declsweep/w{k}'; os.makedirs(d, exist_ok=True)
    for f in glob.glob(d + '/*.o') + glob.glob(d + '/.*.o'): os.remove(f)
    sp = os.path.join(srcdir, f'.declsweep_w{k}{ext}')
    open(sp, 'w').write(text)
    c = re.sub(r'-c \S+ -o \S+', f'-c {sp} -o {d}', cc)
    r = subprocess.run(c, shell=True, capture_output=True, text=True)
    o = glob.glob(d + '/*.o') + glob.glob(d + '/.*.o')
    if not o:
        if k == 0: print('compile failed:', (r.stdout + r.stderr)[-1500:])
        return 10**6
    subprocess.run(['build/tools/dtk', 'elf', 'disasm', o[0], d + '/m.s'], capture_output=True)
    B = body(d + '/m.s', a.mine or a.fn)
    if not B: return 10**6
    return sum(1 for l in difflib.unified_diff(T, B, lineterm='', n=0) if l[:1] in '+-' and not l.startswith(('+++', '---')))

s = open(a.src).read()
name = re.escape(a.fn if not a.mine else a.fn)
m = re.search(r'\b' + name + r'\s*\([^;{]*\)\s*\{\n', s)
if not m:
    m = re.search(r'::\s*\w+\s*\([^;{]*\)\s*\{\n', s) if a.mine else None
if not m:
    import json
    try:
        ren = json.load(open('tools/extab_user_renames.json')).get(a.src, {})
        for k, v in ren.items():
            if v == a.fn and '__' in k:
                meth = k.split('__')[0] or ('~' if k.startswith('__dt') else '')
                if k.startswith('__ct__') or k.startswith('__dt__'):
                    mm = re.match(r'__[cd]t__(\d+)(\w+?)F', k); cls = mm.group(2)[:int(mm.group(1))]
                    meth = cls if k.startswith('__ct') else '~' + cls
                    m = re.search(re.escape(cls) + r'::' + re.escape(meth) + r'\s*\([^;{]*\)[^;{]*\{\n', s)
                else:
                    m = re.search(r'::' + re.escape(meth) + r'\s*\([^;{]*\)[^;{]*\{\n', s)
                if m: break
    except Exception as e:
        print('rename lookup failed', e)
if not m: sys.exit('function definition not found in source')
start = m.end()
orig = score(s, 0)
print(f'original score {orig}', flush=True)
if a.hoist:
    # find the end of the function body
    depth = 1; j = start
    while depth and j < len(s):
        if s[j] == '{': depth += 1
        elif s[j] == '}': depth -= 1
        j += 1
    bodytxt = s[start:j - 1]
    TYPES = r'(?:const\s+)?(?:unsigned\s+|signed\s+)?(?:int|short|char|long|float|double|u8|u16|u32|s8|s16|s32|f32|f64|bool|BOOL|[A-Z]\w*\s*\*+|struct\s+\w+\s*\*+|\w+\s*\*+)'
    dre = re.compile(r'^(\s+)(' + TYPES + r')\s*(\**)\s*([A-Za-z_]\w*)\s*(=\s*([^;]*))?;\s*$')
    bl = bodytxt.split('\n'); names = {}; hoisted = []
    for l in bl:
        mm = dre.match(l)
        if mm and mm.group(2).split()[0] not in ('return', 'delete', 'goto', 'case'):
            names[mm.group(4)] = names.get(mm.group(4), 0) + 1
    newb = []
    for l in bl:
        mm = dre.match(l)
        if mm and names.get(mm.group(4)) == 1 and not mm.group(2).startswith('const'):
            t = (mm.group(2) + ' ' + mm.group(3)).strip()
            hoisted.append('    ' + t + ' ' + mm.group(4) + ';')
            if mm.group(5): newb.append(mm.group(1) + mm.group(4) + ' = ' + mm.group(6).strip() + ';')
            continue
        newb.append(l)
    # keep existing leading decls first
    s = s[:start] + '\n'.join(hoisted) + '\n' + '\n'.join(newb) + s[j - 1:]
    print(f'hoisted {len(hoisted)} declarations', flush=True)
lines = s[start:].split('\n')
decl_re = re.compile(r'^\s+(?:const\s+|unsigned\s+|signed\s+|struct\s+|register\s+|volatile\s+|static\s+)*[A-Za-z_][\w:]*(?:<[^>]*>)?(?:\s*[\*&]+\s*|\s+)[\*&]*[A-Za-z_]\w*(?:\[[^\]]*\])*\s*(?:=[^;{}]*)?;\s*(?://.*|/\*.*\*/)?\s*$')
KW = ('return', 'goto', 'break', 'continue', 'delete', 'throw', 'case', 'else')
blk = []
for l in lines:
    if decl_re.match(l) and l.split()[0] not in KW: blk.append(l)
    else: break
if len(blk) < 3: sys.exit(f'only {len(blk)} leading declarations; nothing to permute')
head = s[:start]; rest = '\n'.join(lines[len(blk):])
base = score(s, 0)
print(f'{a.fn}: {len(blk)} decls, base score {base}', flush=True)
random.seed(1)
cands = []
for i in range(a.n):
    b = blk[:]; random.shuffle(b); cands.append(b)
best = (base, None)
import queue
slots = queue.Queue()
for k in range(1, a.j + 1): slots.put(k)
def job(i):
    b = cands[i]
    k = slots.get()
    try:
        return score(head + '\n'.join(b) + '\n' + rest, k), i
    finally:
        slots.put(k)
try:
    with ThreadPoolExecutor(a.j) as ex:
        for sc, i in ex.map(job, range(len(cands))):
            if sc < best[0]:
                best = (sc, i); print(f'  improved: {sc}', flush=True)
            if sc == 0: break
finally:
    for k in range(a.j + 1):
        p = os.path.join(srcdir, f'.declsweep_w{k}{ext}')
        if os.path.exists(p): os.remove(p)
os.makedirs('/tmp/claude-0/declsweep', exist_ok=True)
if best[1] is not None:
    out = f'/tmp/claude-0/declsweep/{a.fn}.best{ext}'
    open(out, 'w').write(head + '\n'.join(cands[best[1]]) + '\n' + rest)
    print(f'BEST {best[0]} (base {base}) -> {out}')
else:
    print(f'BEST {base} (no improvement)')
