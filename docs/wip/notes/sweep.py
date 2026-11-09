# sweep.py obj fn [fn...]: try compiler versions/flags; print diff counts
import subprocess,sys,re,os,glob,shlex,difflib,itertools
from concurrent.futures import ThreadPoolExecutor
R='/home/claude/mkgp2-decomp';os.chdir(R)
obj=sys.argv[1];fns=sys.argv[2:]
ext='.cpp' if os.path.exists('src/'+obj+'.cpp') else '.c'
cmd=subprocess.run(['ninja','-t','commands','build/GNLJ82/src/'+obj+'.o'],capture_output=True,text=True).stdout.strip().splitlines()[-1]
cc=cmd.split(' && ')[0]
def body(path,fn):
    out=[];on=False
    for l in open(path,errors='replace'):
        if l.startswith('.fn '+fn+','): on=True;continue
        if on and l.startswith('.endfn'): break
        if on:
            m=re.match(r'/\* [0-9A-F]+ [0-9A-F]+  (.. .. .. ..) \*/\t(.*)',l)
            if m:
                x=re.sub(r'\.L_[0-9A-F]+','.L',m.group(2))
                x=re.sub(r'[\w"@.$]+@(ha|l|sda21)',r'S@\1',x)
                out.append(x)
    return out
tgt={}
for fn in fns:
    for p in glob.glob('build/GNLJ82/asm/**/*.s',recursive=True):
        s=open(p,errors='replace').read()
        if ('.fn '+fn+',') in s: tgt[fn]=body(p,fn);break
vers=['1.3.2','1.3','1.3.2r','1.2.5n','2.0','2.5','2.6','2.7']
flags=['','-inline noauto','-use_lmw_stmw on','-inline noauto -use_lmw_stmw on','-O4,s']
def run(v,f):
    d='/tmp/claude-0/sw/%s/%s_%s'%(obj.replace('/','_'),v,re.sub(r'\W','',f))
    os.makedirs(d,exist_ok=True)
    c=cc.replace('GC/1.3.2/','GC/%s/'%v).replace(' -MMD ',' ')+' '+f
    c=re.sub(r'-o \S+','-o '+d,c)
    r=subprocess.run(c,shell=True,capture_output=True,text=True)
    o=glob.glob(d+'/*.o')
    if r.returncode or not o: return (v,f,'FAIL')
    subprocess.run(['build/tools/dtk','elf','disasm',o[0],d+'/m.s'],capture_output=True)
    res=[]
    for fn in fns:
        a=tgt.get(fn,[]);b=body(d+'/m.s',fn)
        n=sum(1 for l in difflib.unified_diff(a,b,lineterm='',n=0) if l[:1] in '+-' and not l.startswith(('+++','---')))
        res.append(n)
    return (v,f,res)
with ThreadPoolExecutor(8) as ex:
    for v,f,res in ex.map(lambda p:run(*p),itertools.product(vers,flags)):
        print(v,repr(f),res)
