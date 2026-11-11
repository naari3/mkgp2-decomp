#!/usr/bin/env python3
"""List base classes whose tail padding a derived class member lands in under clang.

    python3 tools/port_abi/tail_padding.py ROOT

ROOT is a tree holding this repository's src/ and include/ next to
mkgp2-pc's port/tools and port/compat (the flags come from
port/tools/compile_census.py).  Every game .cpp is laid out by clang
(-fdump-record-layouts, with a sizeof of each class it defines so the layout
is computed) and a base is reported when the member after it starts before
sizeof(base).  MWCC never does that; the fix is to name the padding as a
member of the base.  docs/notes/port_abi.md, "Tail padding of base classes".
"""
import sys,subprocess,os,re,glob
from concurrent.futures import ThreadPoolExecutor
sys.path.insert(0,sys.argv[1]+'/port/tools')
import compile_census as c
def run(p):
    cmd=["clang","-target",c.TARGET]+c.BASE+["-include",c.COMPAT,"-Xclang","-fdump-record-layouts","-fsyntax-only"]
    cmd=[x for x in cmd if x not in("-fno-caret-diagnostics",)]
    cmd+=["-x","c++","-std=gnu++98"]
    src=open(p,errors='replace').read()
    txt=src
    for inc in re.findall(r'#include "(game/[^"]+)"',src):
        try: txt+=open(c.ROOT+'/include/'+inc,errors='replace').read()
        except OSError: pass
    names=sorted(set(re.findall(r'^(?:struct|class) (\w+)\b[^;{]*\{',txt,re.M)))
    w='/tmp/tp_%d.cpp'%abs(hash(p))
    open(w,'w').write('#include "%s"\n'%p+''.join('static int __sz_%d = sizeof(%s);\n'%(i,n) for i,n in enumerate(names)))
    r=subprocess.run(cmd+["-ferror-limit=0",w],cwd=c.ROOT,capture_output=True,text=True,errors="replace")
    os.remove(w)
    out=r.stdout
    recs={}
    for blk in out.split('*** Dumping AST Record Layout')[1:]:
        L=[l for l in blk.split('\n') if '|' in l]
        if not L: continue
        m=re.match(r'\s*0 \| (?:struct|class|union) (.+)$',L[0])
        if not m: continue
        name=m.group(1).strip()
        sz=re.search(r'sizeof=(\d+), dsize=(\d+)',blk)
        if not sz: continue
        items=[]
        for l in L[1:]:
            mm=re.match(r'\s*(\d+)(?::[\d-]+)? \|(\s+)(.*)$',l)
            if mm and len(mm.group(2))==3: items.append((int(mm.group(1)),mm.group(3)))
        recs[name]=(int(sz.group(1)),int(sz.group(2)),items)
    res=[]
    for name,(s,d,items) in recs.items():
        for i,(o,t) in enumerate(items):
            mb=re.match(r'(?:struct|class) (.+?) \((?:primary )?base\)',t)
            if mb and mb.group(1) in recs and i+1<len(items):
                bs=recs[mb.group(1)][0]
                if items[i+1][0] < o+bs and 'vtable pointer' not in items[i+1][1] and 'base)' not in items[i+1][1] or (items[i+1][0] < o+bs and 'base)' in items[i+1][1]):
                    res.append((p.replace(c.ROOT+'/',''),mb.group(1),bs,recs[mb.group(1)][1],name,items[i+1][1],items[i+1][0]-o))
    return res
files=[f for f in sorted(glob.glob(c.ROOT+'/src/game/**/*.cpp',recursive=True))]
with ThreadPoolExecutor(8) as ex:
    for res in ex.map(run,files):
        for r in res: print('%s: base %s (size 0x%X, data 0x%X) <- %s::%s at 0x%X'%r)
