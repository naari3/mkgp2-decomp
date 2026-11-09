import subprocess,re,json
files=open('/tmp/claude-0/z/sm/files.txt').read().split()
etb=[];eti=[]
for f in files:
    o='build/GNLJ82/obj/'+re.sub(r'\.(c|cpp)$','.o',f)
    r=subprocess.run(['build/binutils/powerpc-eabi-objdump','-r','-j','extabindex',o],capture_output=True,text=True).stdout
    rows=[l.split() for l in r.splitlines() if 'R_PPC_ADDR32' in l]
    # pairs: offset%12==0 fn, ==8 extab sym
    d={}
    for off,_,sym in rows:
        off=int(off,16); d.setdefault(off//12,{})[off%12]=sym
    for k in sorted(d):
        eti.append(d[k][0]); etb.append((d[k][8],d[k][0]))
    print(f,[(d[k][0],d[k][8]) for k in sorted(d)])
def key(s):
    m=re.search(r'([0-9A-Fa-f]{8})',s[0]); return int(m.group(1),16)
etb.sort(key=key)
json.dump({'extab':[b for a,b in etb],'extabindex':eti,'etbsyms':etb},open('/tmp/claude-0/z/sm/eto.json','w'),indent=1)
