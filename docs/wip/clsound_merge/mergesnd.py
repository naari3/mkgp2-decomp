import re,sys
S='/tmp/claude-0/-home-user-mkgp2-decomp/15521061-eb47-585c-8649-47758aaad732/scratchpad/'
files=open(S+'sndfiles.txt').read().split()
flags={}
REN={}
cfg=open('configure.py').read()
for f in files:
    m=re.search(r'Object\(\w+, "%s"([^\n]*)\)'%re.escape(f),cfg); flags[f]=m.group(1)
out=['/* clsound voice/listener unit, .text 0x801913B0..0x801933D0, merged from the',
     ' * over-split per-function files (fn_801913B0 needs the listener pool that',
     ' * fn_80192F04 owns: .data 0x80495F20..0x80495F48). */',
     '#define lbl_80495F20 lbl_80495F20_hdr','#include "game/clsound_spatial_private.h"','#undef lbl_80495F20',
     'ClSoundVec lbl_80495F20 = {0.0f, 0.0f, 0.0f};','ClSoundVec lbl_80495F2C = {0.0f, 0.0f, 0.0f};',
     'typedef struct FogEye { ClSoundVec pos; float w; } FogEye;','FogEye lbl_80495F38 = {{0.0f, 0.0f, 0.0f}, 0.0f};','']
DEFINED=set()
for f in files:
    t=open(S+'fn_801913B0.orig.c').read() if f.endswith('fn_801913B0.c') else open('src/'+f).read()
    DEFINED|=set(re.findall(r'^(?:int|void|unsigned \w+|float|char|short)\s*\*?\s*(\w+)\s*\([^;]*\)\s*\{',t,re.M))
    DEFINED|=set(re.findall(r'^asm\s+[\w\s\*]+?\b(\w+)\s*\(',t,re.M))
print(sorted(DEFINED))
for n,f in enumerate(files):
    src=open(S+'fn_801913B0.orig.c').read() if f.endswith('fn_801913B0.c') else open('src/'+f).read()
    if f.endswith('fn_80192F04.c'):
        src=src.replace('#define lbl_80495F20 lbl_80495F20_hdr\n#include "game/clsound_spatial_private.h"\n#undef lbl_80495F20\n','')
        src=re.sub(r'typedef struct FogEye \{\n    ClSoundVec pos;\n    float w;\n\} FogEye;\n','',src)
        src=src.replace('ClSoundVec lbl_80495F20 = {0.0f, 0.0f, 0.0f};\nClSoundVec lbl_80495F2C = {0.0f, 0.0f, 0.0f};\nFogEye lbl_80495F38 = {{0.0f, 0.0f, 0.0f}, 0.0f};\n','')
    if f.endswith('fn_801913B0.c'):
        src=src.replace('#include "game/clsound_spatial_private.h"\n','').replace('ClSoundListener* listener = &lbl_80495F20;','ClSoundListener* listener = (ClSoundListener *)&lbl_80495F20;')
    # local identifiers to rename
    ids=set(re.findall(r'typedef struct (\w+)',src))|set(re.findall(r'^\}\s*(\w+);',src,re.M))|set(re.findall(r'static inline [\w\s\*]+?\b(\w+)\(',src))
    POOLM=[];POOLD=[];DROP=[]
    ids-= {'lbl_80495F20'}
    for m in re.finditer(r'^extern\s+(?:const\s+)?[\w\s\*]+?\b(\w+)\s*(\[[^\]]*\])?\s*;',src,re.M):
        nm=m.group(1)
        if nm in ('lbl_80495F20','lbl_80495F2C','lbl_80495F38'):
            ty=re.match(r'^extern\s+((?:const\s+)?[\w\s\*]+?)\b'+nm,m.group(0)).group(1).strip()
            POOLM.append('#define %s (*(%s *)&%s)'%(nm,ty,nm)); POOLD.append(nm); DROP.append(m.group(0)); continue
        ids.add(nm); REN['%s_p%d'%(nm,n)]=nm
    for m in re.finditer(r'^extern\s+(?:const\s+)?[\w\s\*]+?\b(\w+)\s*\([^;{]*\)\s*;',src,re.M):
        nm=m.group(1)
        if nm in DEFINED:
            mm=re.match(r'^extern\s+(.*?)\b'+nm+r'\s*\((.*)\)\s*;',m.group(0),re.S)
            POOLM.append('#define %s ((%s (*)(%s))%s)'%(nm,mm.group(1).strip(),mm.group(2),nm)); POOLD.append(nm)
            DROP.append(m.group(0)); continue
        ids.add(nm); REN['%s_p%d'%(nm,n)]=nm
    for d in DROP: src=src.replace(d,'')
    p='_p%d'%n
    exc='-Cpp_exceptions on' in flags[f]; lmw='-use_lmw_stmw on' in flags[f]
    out.append('/* ==== %s (0x%s) ==== */'%(f,f.split('fn_')[-1][:8] if 'fn_' in f else ''))
    for i in sorted(ids): out.append('#define %s %s%s'%(i,i,p))
    out+=POOLM
    out.append('#pragma exceptions %s'%('on' if exc else 'off'))
    if lmw: out.append('#pragma use_lmw_stmw on')
    out.append(src.rstrip())
    if lmw: out.append('#pragma use_lmw_stmw reset')
    out.append('#pragma exceptions reset')
    for i in sorted(ids): out.append('#undef %s'%i)
    for i in POOLD: out.append('#undef %s'%i)
    out.append('')
open('src/game/clsound/fn_801913B0.c','w').write('\n'.join(out)+'\n')
import json
json.dump(REN,open(S+'snd_ren.json','w'),indent=1)
