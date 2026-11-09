# psweep.py LIST... : per near-miss fn, wrap its definition in #pragma push/X/pop and score
import sys, os, re, multiprocessing as mp
sys.path.insert(0, '/mnt/project-files/setup/tools')
import cperm
PRAGMAS = ['opt_common_subs off', 'opt_lifetimes off', 'opt_propagation off', 'scheduling off',
           'scheduling 601', 'opt_dead_assignments off', 'opt_strength_reduction off',
           'opt_loop_invariants off', 'peephole off', 'opt_dead_code off',
           'opt_common_subs off\n#pragma opt_lifetimes off', 'opt_propagation off\n#pragma opt_common_subs off',
           'optimization_level 3', 'optimization_level 2', 'opt_unroll_loops off']
def job(arg):
    idx, srcp, obj, fn, cc = arg
    wd = f'/tmp/claude-0/ps/{fn}'; os.makedirs(wd, exist_ok=True)
    try:
        src = open(srcp).read()
        pre = cperm.auto_regions(src, srcp, fn)[0]
        i = src.find(pre); a, b = cperm.find_region(src, pre)
        start = src.rfind('\n', 0, i) + 1
        # include preceding 'extern "C"' etc on same line already; end after '}'
        end = b + 1
        B = cperm.Builder(obj, fn, None if cc == '-' else cc, wd)
        t = cperm.target_body(fn)
        base = B.build(srcp); s0 = cperm.score(t, base) if base else None
        res = []
        ext = os.path.splitext(srcp)[1]
        for p in PRAGMAS:
            v = src[:start] + '#pragma push\n#pragma ' + p + '\n' + src[start:end] + '\n#pragma pop\n' + src[end:]
            vp = os.path.join(wd, 'v' + ext); open(vp, 'w').write(v)
            o = B.build(vp); res.append((cperm.score(t, o) if o else 99999, p))
        res.sort()
        return f'{fn} base {s0} best {res[0][0]} [{res[0][1]!r}]' + (' MATCH' if res[0][0] == 0 else '')
    except BaseException as e:
        return f'{fn} ERR {e}'
if __name__ == '__main__':
    jobs = []
    for L in sys.argv[1:]:
        for l in open(L):
            if l.startswith('#') or not l.strip(): continue
            f = l.split(); jobs.append((int(f[0]), f[2], f[3], f[4], f[5]))
    with mp.Pool(4) as pool:
        for r in pool.imap_unordered(job, jobs): print(r, flush=True)
