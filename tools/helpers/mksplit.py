# mksplit.py <tu path e.g. game/Foo.c> <start> <end> : print splits.txt block with extab ranges
import re,sys,glob,os
os.chdir('/home/claude/mkgp2-decomp')
tu,lo,hi=sys.argv[1],int(sys.argv[2],16),int(sys.argv[3],16)
syms={}
for l in open('config/GNLJ82/symbols.txt'):
    m=re.match(r'(\S+) = \.text:0x([0-9A-F]+);.*size:0x([0-9A-F]+)',l)
    if m: syms[m.group(1)]=int(m.group(2),16)
etb={};eti=[]
for p in glob.glob('build/GNLJ82/asm/**/*.s',recursive=True):
    L=open(p).read().split('\n')
    for i,l in enumerate(L):
        m=re.match(r'# extab:0x[0-9A-F]+ \| 0x([0-9A-F]+) \| size: 0x([0-9A-F]+)',l)
        if m: etb[int(m.group(1),16)]=int(m.group(2),16)
        m=re.match(r'\.obj "@eti_([0-9A-F]+)"',l)
        if m:
            j=i+1
            while not L[j].strip().startswith('.4byte'): j+=1
            fn=L[j].split()[1]; e=re.search(r'@etb_([0-9A-F]+)',L[j+2]).group(1)
            eti.append((int(m.group(1),16),fn,int(e,16)))
sel=[(a,fn,e) for a,fn,e in set(eti) if fn in syms and lo<=syms[fn]<hi]
print(tu+':')
if sel:
    es=[e for _,_,e in sel]; ia=[a for a,_,_ in sel]
    print('\textab       start:0x%08X end:0x%08X'%(min(es),max(es)+etb.get(max(es),8)))
    print('\textabindex  start:0x%08X end:0x%08X'%(min(ia),max(ia)+12))
    # sanity: contiguous?
    if (max(ia)+12-min(ia))//12!=len(sel): print('# WARNING extabindex not contiguous',len(sel))
print('\t.text       start:0x%08X end:0x%08X'%(lo,hi))
