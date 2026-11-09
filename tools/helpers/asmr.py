# asmr.py lo hi : print target asm of all functions in [lo,hi) compactly (incl. extab objs of auto files)
import re,glob,sys,os
os.chdir('/home/claude/mkgp2-decomp')
lo,hi=int(sys.argv[1],16),int(sys.argv[2],16)
fns=[]
for p in glob.glob('build/GNLJ82/asm/**/*.s',recursive=True):
    txt=open(p).read()
    for m in re.finditer(r'^\.fn (\S+), \w+\n(.*?)^\.endfn',txt,re.M|re.S):
        a=re.search(r'/\* ([0-9A-F]{8}) ',m.group(2))
        if not a: continue
        a=int(a.group(1),16)
        if lo<=a<hi: fns.append((a,m.group(1),m.group(2),p))
fns.sort()
for a,n,b,p in fns:
    print('== %08X %s  [%s]'%(a,n,os.path.basename(p)))
    for l in b.split('\n'):
        l=re.sub(r'^/\* [0-9A-F]+ [0-9A-F]+  .. .. .. .. \*/\t','',l)
        if l.strip(): print(l)
