#!/usr/bin/env python3
"""mxident.py obj.o [lo hi] : find target functions (same size, masked relocs) for each func in obj."""
import os,sys,re
from elftools.elf.elffile import ELFFile
exec(open(os.path.join(os.path.dirname(__file__), "cmp.py")).read().split("def main")[0])
o=sys.argv[1]; lo=int(sys.argv[2],16) if len(sys.argv)>2 else 0x80298988; hi=int(sys.argv[3],16) if len(sys.argv)>3 else 0x802BD07C
syms=load_symbols()
bysize={}
for n,(a,s) in syms.items():
    if lo<=a<hi: bysize.setdefault(s,[]).append((a,n))
elf=ELFFile(open(o,"rb")); symtab=elf.get_section_by_name(".symtab"); secs=list(elf.iter_sections())
relocs={}
for s in secs:
    if s.header.sh_type=="SHT_RELA":
        for rel in s.iter_relocations(): relocs.setdefault(s.header.sh_info,set()).add(rel["r_offset"])
for sym in symtab.iter_symbols():
    if sym["st_info"]["type"]!="STT_FUNC": continue
    sh=sym["st_shndx"]; data=elf.get_section(sh).data()[sym["st_value"]:sym["st_value"]+sym["st_size"]]
    rl=relocs.get(sh,set()); hits=[]; near=[]
    for a,n in bysize.get(sym["st_size"],[]):
        t=read_va(a,len(data)); bad=0
        for i in range(len(data)//4):
            x=data[i*4:i*4+4]; y=t[i*4:i*4+4]
            if (sym["st_value"]+i*4) in rl or (sym["st_value"]+i*4+2) in rl:
                if x[0]>>2!=y[0]>>2: bad+=1
            elif x!=y: bad+=1
        if bad==0: hits.append(f"{a:08X}:{n}")
        elif bad<=max(2,len(data)//40): near.append(f"{a:08X}:{n}(~{bad})")
    print(f"{sym.name:34s} {sym['st_size']:5x} {' '.join(hits) or '-'} {' '.join(near[:3])}")
