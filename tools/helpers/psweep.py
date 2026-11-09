#!/usr/bin/env python3
"""psweep.py SRC OBJ FN 'anchor line prefix' [ccs...]
Sweep compiler x (one or two) #pragma inserted before the function anchor.
Prints best results; writes hits to SRC.hit.<cc>.<n>"""
import sys,subprocess,os,itertools
S=os.path.dirname(os.path.abspath(__file__))
src,obj,fn,anchor=sys.argv[1:5]; ccs=sys.argv[5:] or ['-','1.2.5n','1.3','1.3.2','2.6','2.7','3.0a5']
s=open(src).read(); assert anchor in s
P=["opt_propagation off","opt_common_subs off","opt_lifetimes off","opt_dead_assignments off","opt_strength_reduction off","opt_loop_invariants off","opt_unroll_loops off","scheduling off","peephole off","optimization_level 3","optimization_level 2","optimize_for_size on","fp_contract off"]
combos=[()]+[(a,) for a in P]+list(itertools.combinations(P,2))
ext=os.path.splitext(src)[1]; d=os.path.dirname(os.path.abspath(src)); tmp=os.path.join(d,'.psw_%d%s'%(os.getpid(),ext))
res=[]
try:
  for cc in ccs:
    for c in combos:
      pr=''.join('#pragma %s\n'%x for x in c)
      open(tmp,'w').write(s.replace(anchor,pr+anchor,1))
      r=subprocess.run(['python3',S+'/probe.py',tmp,obj,fn,cc],capture_output=True,text=True).stdout.strip().splitlines()
      n=int(r[-1].split()[1]) if r and r[-1].startswith('DIFF') else 9999
      res.append((n,cc,c))
      if n==0: print('HIT',cc,c,flush=True)
finally:
  os.path.exists(tmp) and os.remove(tmp)
res.sort()
for x in res[:8]: print(x)
