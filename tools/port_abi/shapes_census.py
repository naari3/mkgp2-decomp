#!/usr/bin/env python3
"""Collects, per function name, every argument shape it is called with and
defined with (C++ callers included) into $PORT_ABI_OUT/shapes.pkl, the input
of byvalue_fix.py.

Part of the call-ABI sweep described in docs/notes/port_abi.md. Needs clang
and a checkout of mkgp2-pc (its port/tools/compile_census.py supplies the
compile flags); run from a directory where `port/`, `src/`, `include/`,
`configure.py` and `config/` are all visible (for example the mkgp2-pc
checkout itself, or a scratch directory of symlinks to both repositories).
Intermediate files go to $PORT_ABI_OUT (default: the current directory).
"""
import os
OUT = os.environ.get("PORT_ABI_OUT", os.getcwd())
import sys,collections,concurrent.futures,os
src=open(os.path.dirname(os.path.abspath(__file__))+'/types_census.py').read().split('\nfiles = []')[0].split('"""',2)[2]
exec(src)
import re
S_OUT=os.path.join(os.environ.get('PORT_ABI_OUT', os.getcwd()), 'shapes.pkl')
def dm(n):
    m=re.match(r'_Z(\d+)',n)
    if m:
        k=int(m.group(1)); return n[m.end():m.end()+k]
    return n

files=[]
for d in ["game","sound","ui","util","resource","triforce"]:
    for base,_,names in os.walk(os.path.join(ROOT,"src",d)):
        files+=[os.path.relpath(os.path.join(base,n),ROOT) for n in names if n.endswith((".c",".cpp"))]
with concurrent.futures.ThreadPoolExecutor(max_workers=os.cpu_count()) as ex: res=list(ex.map(scan,sorted(files)))
shapes=collections.defaultdict(lambda: collections.defaultdict(set))
for path,d,calls in res:
    for n,k in d.items():
        n=dm(n)
        if not n.startswith('_Z'): shapes[n][tuple(x for x in k)].add('DEF '+path)
    for n,k,knr in calls:
        n=dm(n)
        if not n.startswith('_Z'): shapes[n][k].add(path)

import pickle
pickle.dump({n:{k:sorted(v) for k,v in sh.items()} for n,sh in shapes.items()}, open(S_OUT,'wb'))
