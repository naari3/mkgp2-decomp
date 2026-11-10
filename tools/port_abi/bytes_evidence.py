#!/usr/bin/env python3
"""How the code reads the objects that the data units define as byte arrays.

Compiles every unit to optimised LLVM IR with clang (flags from mkgp2-pc
port/tools/compile_census.py, so run it from a root where port/ and src/ are
both visible) and records, per global, the typed loads and stores at constant
offsets, the block copies, and the accesses through a scaled index.
Writes $PORT_ABI_OUT/bytes_evidence.pkl for tools/autodata_bytes.py --evidence.

    python3 tools/port_abi/bytes_evidence.py NAMES_FILE [dirs...]

NAMES_FILE: one object name per line (tools/autodata_bytes.py --names FILE writes it).
"""
import collections, concurrent.futures, os, pickle, re, subprocess, sys
sys.path.insert(0, 'port/tools')
import compile_census as cc
OUT = os.environ.get("PORT_ABI_OUT", os.getcwd())
names = set(open(sys.argv[1]).read().split())
SZ = {'i8': 1, 'i16': 2, 'i32': 4, 'i64': 8, 'float': 4, 'double': 8, 'ptr': 4}
CE = re.compile(r'getelementptr (?:inbounds )?(?:nuw )?\(((?:\[\d+ x )*i8\]*), ptr @([\w.$]+)((?:, i\d+ -?\d+)*)\)')

def ce_offset(ty, idx):
    """offset of a constant GEP over nested arrays of i8"""
    dims = [int(x) for x in re.findall(r'\[(\d+) x', ty)]
    ix = [int(x) for x in re.findall(r'i\d+ (-?\d+)', idx)]
    if not ix: return 0
    # first index scales the whole type
    sizes = []
    total = 1
    for d in dims: total *= max(d, 1)
    cur = total if dims else 1
    off = ix[0] * (cur if dims else 1)
    rem = dims[:]
    for i in ix[1:]:
        if not rem: return None
        d = rem.pop(0)
        inner = 1
        for x in rem: inner *= x
        off += i * inner
    return off

def scan(path):
    cmd = ["clang", "-target", cc.TARGET, "-S", "-emit-llvm", "-O2", "-fno-exceptions", "-fno-rtti", "-fcommon",
           "-fno-strict-aliasing", "-fno-vectorize", "-fno-slp-vectorize", "-fno-unroll-loops"] + cc.base_flags(path)[1:]
    cmd += ["-include", cc.COMPAT]
    cmd += ["-x", "c++", "-std=gnu++98"] if cc.is_cxx(path, cc.TARGET) else [
        "-x", "c", "-std=gnu99", "-Wno-error=implicit-function-declaration", "-Wno-error=implicit-int",
        "-Wno-error=int-conversion", "-Wno-error=incompatible-pointer-types"]
    r = subprocess.run(cmd + [path, "-o", "-"], cwd=cc.ROOT, capture_output=True, text=True, errors="replace")
    ev = []
    if r.returncode: return path, None
    text = r.stdout
    if not any(('@' + n) in text for n in names if n in text): return path, ev
    for fn in re.split(r'\n(?=define )', text):
        if '@' not in fn: continue
        ptrs = {}   # ssa -> (global, base offset or None, stride or None)
        muls = {}
        for line in fn.split('\n'):
            hit = [m for m in CE.finditer(line) if m.group(2) in names]
            direct = [m for m in re.finditer(r'ptr (?:noundef |nonnull |readonly |align \d+ |dereferenceable\(\d+\) )*@([\w.$]+)', line) if m.group(1) in names]
            m = re.match(r'\s*(%[\w.]+) = (mul|shl) (?:nsw |nuw )*i32 (%[\w.]+), (\d+)', line)
            if m: muls[m.group(1)] = int(m.group(4)) if m.group(2) == 'mul' else 1 << int(m.group(4))
            # operand list: (global, offset) in this line
            ops = []
            for h in hit:
                ops.append((h.group(2), ce_offset(h.group(1), h.group(3)), None, h.group(0)))
            for d in direct:
                if not any(d.start() >= h.start() and d.end() <= h.end() for h in hit):
                    ops.append((d.group(1), 0, None, d.group(0)))
            for v, p in ptrs.items():
                if re.search(r'ptr (?:[a-z]+(?:\(\d+\))? |align \d+ )*' + re.escape(v) + r'(?![\w.])', line):
                    ops.append((p[0], p[1], p[2], 'ptr ' + v))
            if not ops: continue
            lm = re.match(r'\s*(%[\w.]+) = load (\w+), ptr', line)
            sm = re.match(r'\s*store (\w+) [^,]+, ptr', line)
            gm = re.match(r'\s*(%[\w.]+) = getelementptr (?:inbounds )?(?:nuw )?((?:\[\d+ x )*\w+\]*), ptr (@[\w.$]+|%[\w.]+|getelementptr[^)]*\))((?:, i\d+ [%\w.-]+)*)', line)
            for g, off, stride, tok in ops:
                if lm and line.index(tok) > line.index('load'):
                    ev.append((g, 'load', lm.group(2), off, stride))
                elif sm and line.rstrip().split(', ptr ')[-1].startswith(tok.replace('ptr ', '').split(',')[0][:20]) :
                    ev.append((g, 'store', sm.group(1), off, stride))
                elif 'llvm.memcpy' in line or 'llvm.memmove' in line:
                    mm = re.search(r'i32 (\d+), i1', line)
                    ev.append((g, 'copy', int(mm.group(1)) if mm else None, off, stride))
                elif gm:
                    ty = gm.group(2); idx = gm.group(4)
                    parts = re.findall(r'i\d+ ([%\w.-]+)', idx)
                    base = re.sub(r'[\[\]\dx ]', '', ty)
                    dims = [int(x) for x in re.findall(r'\[(\d+) x', ty)]
                    esz = SZ.get(base)
                    if esz is None or off is None: ptrs[gm.group(1)] = (g, None, None); ev.append((g, 'unknown', line.strip()[:120], off, stride)); continue
                    # element size per index level
                    sizes = []
                    tot = esz
                    for d in dims: tot *= max(d, 1)
                    level = tot
                    lev = [tot]
                    rem = dims[:]
                    while rem:
                        rem.pop(0); inner = esz
                        for x in rem: inner *= x
                        lev.append(inner)
                    o = off; st = stride; bad = False
                    for i, pv in enumerate(parts):
                        if i >= len(lev): bad = True; break
                        if re.match(r'-?\d+$', pv): o += int(pv) * lev[i]
                        else:
                            s2 = lev[i] * muls.get(pv, 1)
                            st = s2 if st is None else __import__('math').gcd(st, s2)
                    if bad: ptrs[gm.group(1)] = (g, None, None)
                    else: ptrs[gm.group(1)] = (g, o, st)
                else:
                    ev.append((g, 'other', line.strip()[:140], off, stride))
    return path, ev

files = []
for d in sys.argv[2:] or ["game", "sound", "ui", "util", "resource"]:
    for base, _, fs in os.walk(os.path.join(cc.ROOT, "src", d)):
        if 'autodata' in base: continue
        files += [os.path.relpath(os.path.join(base, n), cc.ROOT) for n in fs if n.endswith((".c", ".cpp"))]
# only units whose text (or includes) can mention a name: cheap prefilter by grep is not reliable with headers, so compile all
with concurrent.futures.ThreadPoolExecutor(max_workers=os.cpu_count()) as ex:
    res = list(ex.map(scan, sorted(files)))
evid = collections.defaultdict(list); failed = []
for path, ev in res:
    if ev is None: failed.append(path); continue
    for e in ev: evid[e[0]].append((path,) + e[1:])
pickle.dump({'evidence': dict(evid), 'failed': failed}, open(os.path.join(OUT, 'bytes_evidence.pkl'), 'wb'))
print(len(evid), 'objects with evidence;', len(failed), 'units did not compile')
