#!/usr/bin/env python3
"""Wraps prototypes that take a struct by value (or return one) while the
definition takes pointers: original under __MWERKS__, real prototype plus a
Foo_ByValue inline elsewhere. Reads $PORT_ABI_OUT/shapes.pkl. Run from the
mkgp2-decomp root; prints what it could not parse.

Part of the call-ABI sweep described in docs/notes/port_abi.md. Needs clang
and a checkout of mkgp2-pc (its port/tools/compile_census.py supplies the
compile flags); run from a directory where `port/`, `src/`, `include/`,
`configure.py` and `config/` are all visible (for example the mkgp2-pc
checkout itself, or a scratch directory of symlinks to both repositories).
Intermediate files go to $PORT_ABI_OUT (default: the current directory).
"""
import os
OUT = os.environ.get("PORT_ABI_OUT", os.getcwd())
import pickle,re,os,sys,collections
S=os.environ.get('PORT_ABI_OUT', os.getcwd())
sh=pickle.load(open(S+'/shapes.pkl','rb'))
SCALAR=set('Mtx44 Mtx Mtx34 void int float double char short long unsigned signed const volatile u8 u16 u32 u64 s8 s16 s32 s64 f32 f64 BOOL bool size_t uint ushort uchar register'.split())
def expandable(call,ref):
    c=list(call); r=list(ref)
    if c and c[0]=='sret': c[0]='ptr'
    if r and r[0]=='sret': r[0]='ptr'
    i=j=0; n=0
    while i<len(c) and j<len(r):
        if r[j] in('ptr','int') and c[i:i+3]==['float']*3 and r[j:j+3]!=['float']*3: i+=3; j+=1; n+=1
        elif c[i]==r[j] or {c[i],r[j]}<={'ptr','int'}: i+=1; j+=1
        else: return 0
    return n if i==len(c) and j==len(r) else 0
work=collections.defaultdict(dict)   # file -> callee -> (callshapes, defshape)
for n,shapes in sh.items():
    refs=[k for k,ps in shapes.items() if any(p.startswith('DEF ') for p in ps)]
    if not refs: continue
    refs=[k for k in refs if not n.endswith("_ByValue")]
    if not refs: continue
    r=sorted(refs,key=len)[0]
    for k,ps in shapes.items():
        if k!=r and (expandable(k,r) or (('sret' in k) and 'sret' not in r)):
            for p in ps:
                if not p.startswith('DEF '): work[p].setdefault(n,(set(),r))[0].add(k)
def split(ps):
    out=[];d=0;cur=''
    for ch in ps:
        if ch in '([': d+=1
        if ch in ')]': d-=1
        if ch==',' and d==0: out.append(cur); cur=''
        else: cur+=ch
    if cur.strip(): out.append(cur)
    return [x.strip() for x in out]
def parse_param(p,i):
    """-> (type, name, is_struct)"""
    if p in('void',''): return None
    if '...' in p: raise ValueError('complex param '+p)
    if '(' in p or '[' in p:
        m=re.match(r'^([\w \t\*]*?)\(\s*\*\s*(\w*)\s*\)(.*)$',p)
        if m:
            name=m.group(2) or 'a%d'%i
            return ('ARR', name, False, '%s(*%s)%s'%(m.group(1),name,m.group(3)))
        m=re.match(r'^(.*?)(\b[A-Za-z_]\w*)?\s*(\[.*)$',p)
        head,name,tail=m.group(1),m.group(2),m.group(3)
        if name in SCALAR or not head.strip(): head=(head+(name or '')); name=None
        name2=name or 'a%d'%i
        return ('ARR', name2, False, '%s %s%s'%(head.strip(),name2,tail))
    m=re.match(r'^(.*?)(\b[A-Za-z_]\w*)?$',p,re.S)
    toks=re.findall(r'[A-Za-z_]\w*|\*|&',p)
    words=[t for t in toks if t not in('*','&')]
    ptr='*' in toks or '&' in toks
    # name present? if last word is not a type-ish word and there are >=2 non-qualifier words
    core=[w for w in words if w not in('const','volatile','register','struct','unsigned','signed','long','short')]
    hasname = (len(core)>=2) or (len(core)==1 and len(words)>len(core) and words[-1]==core[-1] and any(w in('unsigned','signed','long','short') for w in words)) or (ptr and re.search(r'[\*&]\s*[A-Za-z_]\w*$',p) is not None)
    if hasname:
        name=words[-1]; typ=p[:p.rindex(name)].strip()
    else: name='a%d'%i; typ=p
    tw=[w for w in re.findall(r'[A-Za-z_]\w*',typ)]
    is_struct=(not ptr) and any(w not in SCALAR and w!='struct' for w in tw)
    return typ,name,is_struct
def gen(indent,pre,name,params,call_shapes,defshape,fname):
    pre_s=pre.strip()
    ext=''
    ret=re.sub(r'^(extern\s+("C"\s+)?)','',pre_s).strip()
    static = ret.startswith('static')
    if static: raise ValueError('static')
    ps=[parse_param(p,i) for i,p in enumerate(split(params))]
    ps=[p for p in ps if p]
    rw=re.findall(r'[A-Za-z_]\w*',ret)
    ret_struct=('*' not in ret) and any(w not in SCALAR and w!='struct' and w!='inline' for w in rw)
    nstruct=sum(1 for p in ps if p[2])
    want=len(ps)+2*nstruct+(1 if ret_struct else 0)
    if not any(len(k)==want and (('sret' in k)==ret_struct) for k in call_shapes): raise ValueError('shape %s vs params %d structs %d ret_struct %s'%(call_shapes,len(ps),nstruct,ret_struct))
    if nstruct==0 and not ret_struct: raise ValueError('nothing by value')
    if len(defshape)!=len(ps)+(1 if ret_struct else 0): raise ValueError('def shape %s'%(defshape,))
    ps=[(p+(None,))[:4] for p in ps]
    real_params=', '.join(([ret+' *'] if ret_struct else [])+[(full if full else (t+' *' if s else t)) for t,n,s,full in ps]) or 'void'
    real_ret='void' if ret_struct else ret
    wparams=', '.join(full if full else ('%s %s'%(t,n) if not t.rstrip().endswith('*') else '%s%s'%(t,n)) for t,n,s,full in ps) or 'void'
    args=', '.join((['&port_ret'] if ret_struct else [])+[('&'+n if s else n) for t,n,s,full in ps])
    if ret_struct: body='%s port_ret; %s(%s); return port_ret;'%(ret,name,args)
    elif ret=='void': body='%s(%s);'%(name,args)
    else: body='return %s(%s);'%(name,args)
    base=re.sub(r'_p\d+$','',name)
    L=['#else','/* The definition takes these structs by address; see docs/notes/port_abi.md. */',
       'extern %s %s(%s);'%(real_ret,name,real_params),
       'static inline %s %s_ByValue(%s) { %s }'%(ret,name,wparams,body),
       '#define %s %s_ByValue'%(name,name),'#endif']
    return L
done=0; fails=[]
for f,cs in sorted(work.items()):
    raw=open(f,'rb').read(); nl='\r\n' if b'\r\n' in raw else '\n'
    s=raw.decode('latin-1').replace('\r\n','\n'); changed=False
    for n,(shapes,d) in cs.items():
        rx=re.compile(r'(?m)^([ \t]*)((?:extern\s+)?(?:"C"\s+)?[A-Za-z_][\w \t\*]*?[\s\*])('+re.escape(n)+r'(?:_p\d+)?)\s*\(([^;{}]*?)\)\s*;[^\n]*$')
        ms=list(rx.finditer(s))
        ms=[m for m in ms if m.group(2).split()[0] not in('return','else','case','goto')]
        if not ms:
            hit=False
            incs=[]
            def collect(text,base,depth):
                for inc in re.findall(r'#include "([^"]+)"',text):
                    for cand in ('include/'+inc, inc, os.path.join(base,inc)):
                        if os.path.exists(cand) and cand not in incs and not cand.startswith('include/game/types/'):
                            incs.append(cand)
                            if depth<2: collect(open(cand,encoding='latin-1').read(),os.path.dirname(cand),depth+1)
            collect(s,os.path.dirname(f),0)
            for cand in incs:
                for _ in (0,):
                    if True:
                        hs=open(cand,'rb').read().decode('latin-1')
                        for m in reversed(list(rx.finditer(hs))):
                            if hs[:m.start()].rstrip().endswith(('#ifdef __MWERKS__','see docs/notes/port_abi.md. */')): hit=True; continue
                            try: L=gen(m.group(1),m.group(2),m.group(3),m.group(4),shapes,d,cand)
                            except ValueError as e: fails.append((cand,n,str(e)[:150])); continue
                            hs=hs[:m.start()]+'#ifdef __MWERKS__\n'+m.group(0)+'\n'+'\n'.join(L)+hs[m.end():]; hit=True; done+=1
                            open(cand,'wb').write(hs.encode('latin-1'))
            if not hit: fails.append((f,n,'no prototype in file or headers'))
            continue
        ok=False
        for m in reversed(ms):
            if s[:m.start()].rstrip().endswith(('#ifdef __MWERKS__','see docs/notes/port_abi.md. */')): ok=True; continue
            try: L=gen(m.group(1),m.group(2),m.group(3),m.group(4),shapes,d,f)
            except ValueError as e:
                fails.append((f,n,str(e)[:150])); continue
            s=s[:m.start()]+'#ifdef __MWERKS__\n'+m.group(0)+'\n'+'\n'.join(L)+s[m.end():]; ok=True; changed=True; done+=1
    if changed: open(f,'wb').write(s.replace('\n',nl).encode('latin-1'))
print('rewritten',done,'failed',len(fails))
for x in fails: print('FAIL',*x,sep='\t')
