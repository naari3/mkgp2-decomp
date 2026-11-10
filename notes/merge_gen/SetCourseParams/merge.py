import re,json,subprocess,sys
W='/tmp/claude-0/z/sm/'
OUT='src/game/SetCourseParams.c'
files=open(W+'files.txt').read().split()
cfg=subprocess.run(['git','show','HEAD:configure.py'],capture_output=True,text=True).stdout
def orig(f): return subprocess.run(['git','show','HEAD:src/'+f],capture_output=True,text=True).stdout
POOL={'SetCourseParams_bss_805AC600','KartDriverArray_StaticCtor_bss_805AC6C0','SetCourseParams_bss_805AC6CC','SetCourseParams_bss_805B24CC','RaceResult_StoreLatest_bss_805B256C','SetCourseParams_bss_805B2580','g_playerData','SetCourseParams_bss_805D275C','RaceSlot_ResetAll_bss_805D2938','SetCourseParams_bss_805D2948'}
srcs={f:orig(f) for f in files}
HAND=json.load(open(W+'hand.json'))
for f in files:
    for a,b in HAND.get(f,{}).get('replace',[]):
        assert a in srcs[f],(f,a); srcs[f]=srcs[f].replace(a,b)
DEFINED=set()
for f,t in srcs.items():
    DEFINED|=set(re.findall(r'^(?:extern "C" )?(?:static )?(?:const )?(?:int|void|unsigned \w+|float|char|short|signed char|\w+)\s*\**\s*(\w+)\s*\([^;{]*\)\s*\{',t,re.M))
print(sorted(DEFINED),file=sys.stderr)
REN={}
out=[open(W+'head.txt').read()]
for n,f in enumerate(files,1):
    src=srcs[f]
    fl=re.search(r'Object\(\w+, "%s"([^\n]*)\)'%re.escape(f),cfg).group(1)
    h=HAND.get(f,{})
    exc=h.get('exc','-Cpp_exceptions on' in fl); lmw='-use_lmw_stmw on' in fl
    cpp=h.get('cpp',False)
    ids=set(h.get('rename',[])); macros=[]; und=[]
    ids|=set(re.findall(r'typedef (?:struct|union) (\w+)',src))|set(re.findall(r'^\}\s*(\w+);',src,re.M))
    ids|=set(re.findall(r'^typedef .*\}\s*(\w+);\s*$',src,re.M))
    ids|=set(re.findall(r'^(?:struct|union|class) (\w+)\s*[;{:]',src,re.M))
    ids|=set(re.findall(r'^static inline [\w\s\*]+?\b(\w+)\(',src,re.M))
    und+=re.findall(r'^#define (\w+)',src,re.M)
    def fix(mm):
        body=mm.group(1)
        if '(' in body:
            nm=re.search(r'(\w+)\s*\(',body).group(1)
            if nm in DEFINED: return mm.group(0)
            ids.add(nm); return mm.group(0)
        b=re.match(r'((?:const\s+|volatile\s+)*(?:struct\s+|unsigned\s+|signed\s+)?(?:long long|\w+))\s*(.*)$',body,re.S)
        base,decls=b.group(1),b.group(2)
        keep=[]
        for d in decls.split(','):
            d=d.strip(); dm=re.match(r'(\**)\s*(\w+)\s*((?:\[[^\]]*\])*)$',d)
            star,nm,dims=dm.groups()
            if nm in POOL:
                if h.get('nopoolmacro'): continue
                dl=re.findall(r'\[([^\]]*)\]',dims)
                if len(dl)==0: macros.append('#define %s (*(%s %s*)%s)'%(nm,base,star,nm))
                elif len(dl)==1: macros.append('#define %s ((%s %s*)%s)'%(nm,base,star,nm))
                else: macros.append('#define %s ((%s %s(*)%s)%s)'%(nm,base,star,''.join('[%s]'%x for x in dl[1:]),nm))
                und.append(nm); continue
            ids.add(nm); keep.append(d)
        if not keep: return ''
        return 'extern %s %s;'%(base,', '.join(keep))
    src=re.sub(r'^extern\s+(?!"C")([^;{]+?);',fix,src,flags=re.M)
    ids-=set(h.get('norename',[]))
    for i in ids: REN['%s_p%d'%(i,n)]=i
    macros+=h.get('macros',[]); und+=h.get('undef',[])
    e='on' if exc else 'off'
    src=src.replace('#pragma exceptions reset','#pragma exceptions '+e)
    src=src.replace('#pragma use_lmw_stmw reset','#pragma use_lmw_stmw '+('on' if lmw else 'off'))
    pre=['#define %s %s_p%d'%(i,i,n) for i in sorted(ids)]+macros+['#pragma exceptions %s\n#pragma use_lmw_stmw %s'%(e,'on' if lmw else 'off')]
    post=['#undef %s'%i for i in sorted(ids)+sorted(set(und))]
    body=re.sub(r'\n{3,}','\n\n',src).strip()
    out.append('/* ==== %s ==== */'%f.split('/')[-1])
    if cpp: out.append('#pragma cplusplus on')
    out+=pre; out.append(body); out+=post
    out.append('#pragma cplusplus off')
    out.append('')
open(OUT,'w').write('\n'.join(out))
json.dump(REN,open(W+'ren.json','w'),indent=1)
