#!/usr/bin/env python3
"""Wraps prototypes whose int/float parameter order differs from the
definition (rows `intflt` of types_census.py in $PORT_ABI_OUT/types.txt) with
a Foo_Reordered inline. Run from the mkgp2-decomp root.

Part of the call-ABI sweep described in docs/notes/port_abi.md. Needs clang
and a checkout of mkgp2-pc (its port/tools/compile_census.py supplies the
compile flags); run from a directory where `port/`, `src/`, `include/`,
`configure.py` and `config/` are all visible (for example the mkgp2-pc
checkout itself, or a scratch directory of symlinks to both repositories).
Intermediate files go to $PORT_ABI_OUT (default: the current directory).
"""
import os
OUT = os.environ.get("PORT_ABI_OUT", os.getcwd())
import re,os,sys,collections
S=os.environ.get('PORT_ABI_OUT', os.getcwd())
FLOATS={'float','double','f32','f64'}
work=collections.defaultdict(dict)
for l in open(S+'/types.txt'):
    kind,n,path,call,d,where=l.rstrip('\n').split('\t')
    if kind!='intflt': continue
    c=call[5:-1].split(','); d=d[4:-1].split(',')
    work[path].setdefault(n,(set(),d))[0].add(tuple(c))
def split(ps):
    out=[];d=0;cur=''
    for ch in ps:
        if ch in '([': d+=1
        if ch in ')]': d-=1
        if ch==',' and d==0: out.append(cur); cur=''
        else: cur+=ch
    if cur.strip(): out.append(cur)
    return [x.strip() for x in out]
QUAL=('const','volatile','register','struct','unsigned','signed','long','short')
def parse_param(p,i):
    if p in('void',''): return None
    if '...' in p: raise ValueError('varargs')
    if '(' in p or '[' in p:
        m=re.match(r'^([\w \t\*]*?)\(\s*\*\s*(\w*)\s*\)(.*)$',p)
        if m:
            name=m.group(2) or 'a%d'%i
            return ('%s(*%s)%s'%(m.group(1),name,m.group(3)), '%s(*)%s'%(m.group(1),m.group(3)), name, 'i')
        m=re.match(r'^(.*?)(\b[A-Za-z_]\w*)?\s*(\[.*)$',p)
        head,name,tail=m.group(1),m.group(2),m.group(3)
        if name in FLOATS or name in ('int','char') or not head.strip(): head=head+(name or ''); name=None
        name2=name or 'a%d'%i
        return ('%s %s%s'%(head.strip(),name2,tail), '%s %s'%(head.strip(),tail), name2, 'i')
    toks=re.findall(r'[A-Za-z_]\w*|\*|&',p)
    words=[t for t in toks if t not in('*','&')]
    ptr='*' in toks or '&' in toks
    core=[w for w in words if w not in QUAL]
    if re.search(r'[\*&]\s*(const\s+)?[A-Za-z_]\w*$',p) and not p.rstrip().endswith('const'): hasname=True
    elif ptr: hasname=False
    else: hasname = len(core)>=2 or (len(core)==1 and len(words)>=2 and words[-1]==core[-1] and words[-1] not in ('int','char','double','float') )
    if hasname:
        name=words[-1]; typ=p[:p.rindex(name)].strip()
    else: name='a%d'%i; typ=p.strip()
    cls='f' if (not ptr and any(w in FLOATS for w in re.findall(r'\w+',typ))) else 'i'
    sep='' if typ.endswith('*') else ' '
    return (typ+sep+name, typ, name, cls)
def gen(pre,name,params,shapes,d):
    ret=re.sub(r'^(extern\s+("C"\s+)?)','',pre.strip()).strip()
    if ret.startswith('static') or 'inline' in ret: raise ValueError('static/inline')
    ps=[parse_param(p,i) for i,p in enumerate(split(params))]
    ps=[p for p in ps if p]
    src=''.join(p[3] for p in ps)
    dc=''.join('f' if x in('float','double') else 'i' for x in d)
    if not any(''.join('f' if x in('float','double') else 'i' for x in k)==src for k in shapes): raise ValueError('prototype %s does not give call shapes %s'%(src,shapes))
    if sorted(src)!=sorted(dc): raise ValueError('class counts differ: %s vs def %s'%(src,dc))
    if src==dc: raise ValueError('same order')
    qi=[p for p in ps if p[3]=='i']; qf=[p for p in ps if p[3]=='f']
    order=[(qi if c=='i' else qf).pop(0) for c in dc]
    real=', '.join(p[1].strip() for p in order)
    args=', '.join(p[2] for p in order)
    wp=', '.join(p[0] for p in ps)
    body=('%s(%s);' if ret=='void' else 'return %s(%s);')%(name,args)
    return ['#else','/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */',
            'extern %s %s(%s);'%(ret,name,real),
            'static inline %s %s_Reordered(%s) { %s }'%(ret,name,wp,body),
            '#define %s %s_Reordered'%(name,name),'#endif']
SKIP=('#ifdef __MWERKS__','see docs/notes/port_abi.md. */')
done=0; fails=[]
for f,cs in sorted(work.items()):
    for n,(shapes,d) in cs.items():
        rx=re.compile(r'(?m)^([ \t]*)((?:extern\s+)?(?:"C"\s+)?[A-Za-z_][\w \t\*]*?[\s\*])('+re.escape(n)+r'(?:_p\d+)?)\s*\(([^;{}]*?)\)\s*;[^\n]*$')
        incs=[f]
        def collect(text,base,depth):
            for inc in re.findall(r'#include "([^"]+)"',text):
                for cand in ('include/'+inc, inc, os.path.join(base,inc)):
                    if os.path.exists(cand) and cand not in incs and not cand.startswith('include/game/types/'):
                        incs.append(cand)
                        if depth<2: collect(open(cand,encoding='latin-1').read(),os.path.dirname(cand),depth+1)
        collect(open(f,encoding='latin-1').read(),os.path.dirname(f),0)
        hit=False
        for cand in incs:
            raw=open(cand,'rb').read(); nl='\r\n' if b'\r\n' in raw else '\n'
            s=raw.decode('latin-1').replace('\r\n','\n'); ch=False
            for m in reversed(list(rx.finditer(s))):
                if m.group(2).split()[0] in('return','else','case','goto'): continue
                if s[:m.start()].rstrip().endswith(SKIP): hit=True; continue
                try: L=gen(m.group(2),m.group(3),m.group(4),shapes,d)
                except ValueError as e: fails.append((cand,n,str(e)[:170],m.group(0)[:120])); hit=True; continue
                s=s[:m.start()]+'#ifdef __MWERKS__\n'+m.group(0)+'\n'+'\n'.join(L)+s[m.end():]; hit=True; ch=True; done+=1
            if ch: open(cand,'wb').write(s.replace('\n',nl).encode('latin-1'))
        if not hit: fails.append((f,n,'no prototype',''))
print('rewritten',done,'failed',len(fails))
for x in fails: print('FAIL',*x,sep='\t')
