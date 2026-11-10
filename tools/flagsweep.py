#!/usr/bin/env python3
"""flagsweep.py [extra mwcc flags...]: recompile every NonMatching unit with extra
flags (default: -inline deferred) and print the functions whose diff-line count
against the target drops (ALL=1 prints every function: unit fn old new).
Needs a finished ninja build. Scratch objects go to /tmp/flagsweep."""
import sys,re,subprocess,os,json,shlex,difflib,glob
from multiprocessing import Pool
os.chdir(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))); os.makedirs('/tmp/flagsweep',exist_ok=True)
extra=sys.argv[1:] or ['-inline','deferred']
bn=open('build.ninja').read()
rep=json.load(open('build/GNLJ82/report.json'))
conf=open('configure.py').read()
units=re.findall(r'Object\(NonMatching, "([^"]+)"',conf)
fnmap={u['name'][5:]:[f['name'] for f in u.get('functions',[]) if f.get('fuzzy_match_percent',0)<100] for u in rep['units']}
def body(path,fn):
    out=[];on=False
    for l in open(path,errors='replace'):
        if l.startswith('.fn '+fn+','): on=True;continue
        if on and l.startswith('.endfn'): break
        if on:
            m=re.match(r'/\* [0-9A-F]+ [0-9A-F]+  (.. .. .. ..) \*/\t(.*)',l)
            if m: out.append(m.group(2))
    return [re.sub(r'[^ ,(]+@(ha|l|sda21)',r'SYM@\1',re.sub(r'\.L_[0-9A-F]+','.L',x)) for x in out]
def nd(a,b):
    return sum(1 for l in difflib.unified_diff(a,b,lineterm='',n=0) if l[:1] in '+-' and not l.startswith(('+++','---')))
def work(unit):
    base=unit.rsplit('.',1)[0]
    fns=fnmap.get(base) or []
    if not fns: return []
    m=re.search(r'build build/GNLJ82/src/%s\.o: (\S+).*?\n  cflags = (.*?)\n  basedir'%re.escape(base),bn,re.S)
    if not m: return []
    cf=shlex.split(m.group(2).replace('$\n',''))
    mv=re.search(r'compilers/([^/]+/[^/]+)/mwcceppc',bn[m.start():m.start()+4000])
    ver=re.search(r'mw_version = (\S+)',bn[m.start():bn.index('\n\n',m.start())])
    ver=ver.group(1) if ver else 'GC/1.3.2'
    tag=base.replace('/','_')
    out='/tmp/flagsweep/'+tag+'.o'
    r=subprocess.run(['build/tools/wibo','build/tools/sjiswrap.exe','build/compilers/%s/mwcceppc.exe'%ver]+cf+extra+['-c','src/'+unit,'-o',out],capture_output=True,text=True)
    if r.returncode: return [(unit,'COMPILE FAIL',0,0)]
    # rename via postprocess (needs path mapping) : copy to fake path
    res=[]
    s1='/tmp/flagsweep/'+tag+'.new.s'; s0='/tmp/flagsweep/'+tag+'.old.s'
    subprocess.run(['build/tools/dtk','elf','disasm',out,s1],capture_output=True)
    subprocess.run(['build/tools/dtk','elf','disasm','build/GNLJ82/src/'+base+'.o',s0],capture_output=True)
    t='build/GNLJ82/asm/'+base+'.s'
    if not os.path.exists(t) or not os.path.exists(s1): return []
    # mangled names in new object: map by renames json
    ren=json.load(open('tools/extab_user_renames.json')).get('src/'+unit,{})
    inv={v.split(':')[-1]:k for k,v in ren.items()}
    for f in fns:
        a=body(t,f); o=body(s0,f); n=body(s1,f) or body(s1,inv.get(f,'?'))
        if not a or not n: continue
        d0=nd(a,o); d1=nd(a,n)
        if d1<d0 or os.environ.get("ALL"): res.append((unit,f,d0,d1))
    return res
if __name__=='__main__':
    with Pool(8) as p:
        for r in p.imap_unordered(work,units):
            for x in r: print(*x,flush=True)
