# hill.py file fnmap : pairwise-swap hill climbing on decl lines in //DB..//DE
import sys,subprocess,itertools
p,fn=sys.argv[1:3]
def score(L):
    open(p,'w').write('\n'.join(L))
    out=subprocess.run(['python3','/tmp/claude-0/t/cmp.py',p,'--cc','GC/1.2.5','--preset','base','-fp_contract','off','--map',fn,'--only',fn.split('=')[0],'-v'],capture_output=True,text=True,cwd='/home/claude/mkgp2-decomp').stdout
    if 'diffs=' not in out: return 99999
    return out.count('\n   *')
L=open(p).read().split('\n'); s=L.index('    //DB')+1; e=L.index('    //DE')
best=score(L); print('start',best,flush=True)
improved=True
while improved and best>0:
    improved=False
    for i,j in itertools.combinations(range(s,e),2):
        M=L[:]; M[i],M[j]=M[j],M[i]; n=score(M)
        if n<best: best=n;L=M;improved=True;print(best,L[i].strip(),'<->',L[j].strip(),flush=True)
        if best==0: break
open(p,'w').write('\n'.join(L)); print('final',best)
