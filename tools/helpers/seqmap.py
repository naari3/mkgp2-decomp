#!/usr/bin/env python3
"""seqmap.py obj.o 0xSTART [count] : pair object functions (in order) with target functions from START."""
import sys,re,subprocess,os
ROOT=os.environ.get("MKROOT","/home/claude/mkgp2-decomp")
o=sys.argv[1]; st=int(sys.argv[2],16)
out=subprocess.run([f"{ROOT}/build/binutils/powerpc-eabi-nm","-n","-S",o],capture_output=True,text=True).stdout
mine=[(l.split()[3],int(l.split()[1],16)) for l in out.splitlines() if len(l.split())==4 and l.split()[2] in "tT"]
tgt=[]
for l in open(f"{ROOT}/config/GNLJ82/symbols.txt"):
    m=re.match(r'(\S+) = \.text:0x([0-9A-F]+); // type:function size:0x([0-9A-F]+)',l)
    if m and int(m.group(2),16)>=st: tgt.append((int(m.group(2),16),int(m.group(3),16),m.group(1)))
tgt.sort()
for (n,s),(a,ts,tn) in zip(mine,tgt):
    print(f"{n:32s} {s:5x}  {a:08X} {ts:5x} {tn} {'' if s==ts else '<<'}")
