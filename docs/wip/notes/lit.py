# usage (from anywhere): python3 lit.py src/game/Foo.c game/Foo FnName [k=2]
# Needs fd.py next to it; restores the source unless a 0-diff variant is found.
# lit.py src obj fn [maxk]: try replacing extern float labels with literals (per occurrence, subsets up to maxk)
import sys,re,struct,subprocess,itertools,os
__file__=os.path.abspath(__file__)
R='/home/claude/mkgp2-decomp';os.chdir(R)
path,obj,fn=sys.argv[1:4];maxk=int(sys.argv[4]) if len(sys.argv)>4 else 2
dol=open('orig/GNLJ82/sys/main.dol','rb').read()
offs=struct.unpack('>18I',dol[:72]);addrs=struct.unpack('>18I',dol[72:144]);sz=struct.unpack('>18I',dol[144:216])
def rd(a):
    for o,ad,s in zip(offs,addrs,sz):
        if ad<=a<ad+s: return dol[o+a-ad:o+a-ad+4]
def lit(a):
    b=rd(a); 
    if b is None: return None
    v=struct.unpack('>f',b)[0]
    for p in range(1,12):
        s='%.*g'%(p,v)
        if struct.pack('>f',float(s))==b: break
    if 'e' not in s and '.' not in s: s+='.0'
    if v!=v or abs(v)==float('inf'): return None
    return s+'f'
src=open(path).read()
# function body span
m=re.search(r'\b'+re.escape(fn)+r'\s*\([^;{]*\)\s*\{',src)
start=m.end(); depth=1;i=start
while depth: 
    c=src[i]; depth+= (c=='{')-(c=='}'); i+=1
end=i
occ=[(mm.start(),mm.end(),mm.group(0)) for mm in re.finditer(r'lbl_806D[0-9A-F]{4}',src[start:end])]
occ=[(a+start,b+start,n) for a,b,n in occ]
lits={n:lit(int(n[4:],16)) for _,_,n in occ}
occ=[o for o in occ if lits[o[2]]]
print(len(occ),'occurrences', {k:v for k,v in lits.items()})
def score(s):
    open(path,'w').write(s)
    r=subprocess.run(['ninja','build/GNLJ82/src/'+obj+'.o'],capture_output=True,text=True)
    if r.returncode: return 999
    d=subprocess.run(['python3',os.path.join(os.path.dirname(os.path.abspath(__file__)),'fd.py'),obj,fn],capture_output=True,text=True).stdout
    return len([l for l in d.splitlines() if l[:1] in '+-' and not l.startswith(('+++','---'))])
best=None
import signal
def _term(*a): raise KeyboardInterrupt
signal.signal(signal.SIGTERM, _term)
try:
    groups=[[o for o in occ if o[2]==n] for n in sorted(set(o[2] for o in occ))]
    cands=[[o] for o in occ]+[g for g in groups if len(g)>1]
    for k in range(1,maxk+1):
        for combo in itertools.combinations(range(len(cands)),k):
            sel=set()
            for c in combo: sel|=set(cands[c])
            s=src
            for a,b,n in sorted(sel,reverse=True): s=s[:a]+lits[n]+s[b:]
            n=score(s)
            if best is None or n<best[0]: best=(n,s); print('k',k,'score',n,flush=True)
            if n==0: raise StopIteration
except StopIteration: pass
finally:
    if best and best[0]==0: open(path,'w').write(best[1]); print('MATCH')
    else: open(path,'w').write(src); subprocess.run(['ninja','build/GNLJ82/src/'+obj+'.o'],capture_output=True)
