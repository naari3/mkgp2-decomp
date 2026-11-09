import json,re,glob,sys,os
os.chdir(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
lo,hi=int(sys.argv[1],16),int(sys.argv[2],16)
r=json.load(open('build/GNLJ82/report.json'))
items=[]
for u in r['units']:
    for f in u.get('functions',[]):
        a=int(f['metadata']['virtual_address']); 
        if lo<=a<hi: items.append((a,int(f['size']),f.get('fuzzy_match_percent',0),f['name'],u['name']))
items.sort()
# extab sizes by fn
etbsz={};fnetb={}
for p in glob.glob('build/GNLJ82/asm/auto_*.s'):
    L=open(p).read().split('\n')
    cur=None
    for i,l in enumerate(L):
        m=re.match(r'# extab:0x[0-9A-F]+ \| 0x([0-9A-F]+) \| size: 0x([0-9A-F]+)',l)
        if m: etbsz[int(m.group(1),16)]=int(m.group(2),16)
        m=re.match(r'\.obj "@eti_([0-9A-F]+)"',l)
        if m:
            fn=L[i+1].split()[1] if L[i+1].strip().startswith('.4byte') else L[i+2].split()[1]
            j=i+1
            while '@etb_' not in L[j]: j+=1
            fnetb[fn]=int(re.search(r'@etb_([0-9A-F]+)',L[j]).group(1),16)
runs=[];cur=[]
for it in items:
    pend=it[4].startswith('main/auto')
    if pend: cur.append(it)
    elif cur: runs.append(cur);cur=[]
if cur: runs.append(cur)
for run in runs:
    sz=sum(x[1] for x in run)
    eh=sum(1 for x in run if x[3] in fnetb and etbsz.get(fnetb[x[3]],8)>8)
    print('%08X-%08X n=%d size=%d ehact=%d max=%d | %s'%(run[0][0],run[-1][0]+run[-1][1],len(run),sz,eh,max(x[1] for x in run),' '.join('%s(%d)'%(x[3],x[1]) for x in run)[:300]))
