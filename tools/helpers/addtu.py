# addtu.py <tu> <start> <end> [Matching|NonMatching] [extra python args string e.g. 'extra_cflags=["-Cpp_exceptions on"]']
import re,sys,subprocess,os
os.chdir('/home/claude/mkgp2-decomp')
tu,lo,hi=sys.argv[1],sys.argv[2],sys.argv[3]
kind=sys.argv[4] if len(sys.argv)>4 else 'Matching'
extra=sys.argv[5] if len(sys.argv)>5 else ''
blk=subprocess.run(['python3','/tmp/claude-0/mksplit.py',tu,lo,hi],capture_output=True,text=True).stdout
s=open('config/GNLJ82/splits.txt').read()
assert tu+':\n' not in s
ents=list(re.finditer(r'^(\S+):\n((?:\t[^\n]*\n)+)',s,re.M))
lo_i=int(lo,16);prev=None;ins=None
for e in ents:
    m=re.search(r'\.text\s+start:0x([0-9A-F]+)',e.group(2))
    if not m: continue
    a=int(m.group(1),16)
    if a>lo_i and a<0x80400000 and ins is None: ins=e.start()
    if a<lo_i: prev=e.group(1) if (prev is None or a>prevaddr) else prev; 
    if a<lo_i and (prev==e.group(1)): prevaddr=a
    if a<lo_i:
        if 'pa' not in dir() or a>pa: pa=a;prev=e.group(1)
s=s[:ins]+blk+'\n'+s[ins:]
open('config/GNLJ82/splits.txt','w').write(s)
c=open('configure.py').read()
m=re.search(r'^(\s*)Object\((?:Matching|NonMatching|Equivalent), "%s"[^\n]*\n'%re.escape(prev),c,re.M)
assert m,('prev not in configure',prev)
line='%sObject(%s, "%s"%s),\n'%(m.group(1),kind,tu,(', '+extra) if extra else '')
c=c[:m.end()]+line+c[m.end():]
open('configure.py','w').write(c)
print(blk,'after',prev)
