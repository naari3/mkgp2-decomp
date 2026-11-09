# permsel.py file fnmap name1 name2 ... : exhaustively permute the decl lines of given var names among their positions
import sys,subprocess,itertools,re
p,fn=sys.argv[1:3]; names=sys.argv[3:]
L=open(p).read().split('\n'); s=L.index('    //DB'); e=L.index('    //DE')
pos=[next(i for i in range(s,e) if re.search(r'[ *]'+re.escape(n)+';$',L[i])) for n in names]; pos.sort()
orig=[L[i] for i in pos]
def score(M):
    open(p,'w').write('\n'.join(M))
    out=subprocess.run(['python3','/tmp/claude-0/t/cmp.py',p,'--cc','GC/1.2.5','--preset','base','-fp_contract','off','--map',fn,'--only',fn.split('=')[0],'-v'],capture_output=True,text=True,cwd='/home/claude/mkgp2-decomp').stdout
    return out.count('\n   *') if 'diffs=' in out else 99999
best=None
for perm in itertools.permutations(orig):
    M=L[:]
    for i,l in zip(pos,perm): M[i]=l
    n=score(M)
    if best is None or n<best[0]: best=(n,M); print(n,[x.strip() for x in perm],flush=True)
    if n==0: break
open(p,'w').write('\n'.join(best[1])); print('final',best[0])
