# probe.py SRC OBJNAME FN [CC] [extra flags...]  -- compile SRC (path, may be scratch) with the TU's ninja cmd but CC override, diff FN
import subprocess,sys,re,os,glob,shlex,difflib
R=os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))  # repo root
os.chdir(R)
S=os.path.join(R,'build')  # objects go to build/pp/
src,obj,fn=sys.argv[1:4]; cc=sys.argv[4] if len(sys.argv)>4 and sys.argv[4]!='-' else None; extra=sys.argv[5:]
cmd=subprocess.run(['ninja','-t','commands','build/GNLJ82/src/'+obj+'.o'],capture_output=True,text=True).stdout.strip().splitlines()[-1]
c1=cmd.split(' && ')[0]; post=[x for x in cmd.split(' && ')[1:] if 'transform_dep' not in x]
args=shlex.split(c1)
if cc: args=[re.sub(r'GC/[^/]+/mwcceppc',f'GC/{cc}/mwcceppc',a) for a in args]
i=args.index('-c'); args[i+1]=src; o=S+'/pp/src/'+obj+'.o'; os.makedirs(os.path.dirname(o),exist_ok=True); args[i+3]=o
j=args.index('-MMD'); del args[j]
args[i-1:i-1]=extra
r=subprocess.run(args,capture_output=True,text=True)
if r.returncode: print('COMPILE FAIL',r.stdout[-1500:],r.stderr[-500:]); sys.exit(2)
for p in post:
    pa=shlex.split(p); pa=[o if a.endswith(obj+'.o') else a for a in pa]; subprocess.run(pa,capture_output=True)
def body(path):
    out=[];on=False
    for l in open(path):
        if l.startswith('.fn '+fn+','): on=True;continue
        if on and l.startswith('.endfn'): break
        if on:
            m=re.match(r'/\* [0-9A-F]+ [0-9A-F]+  (.. .. .. ..) \*/\t(.*)',l)
            if m: out.append(m.group(2))
            elif l.strip().startswith('.L'): out.append(l.strip())
    return out
subprocess.run(['build/tools/dtk','elf','disasm',o,S+'/probe.s'],check=True,capture_output=True)
t=None
for p in glob.glob('build/GNLJ82/asm/**/*.s',recursive=True):
    if ('.fn '+fn+',') in open(p).read(): t=p;break
norm=lambda L:[re.sub(r'\.L_[0-9A-F]+','.L',re.sub(r'@\d+','@N',x)) for x in L]
a=norm(body(t));b=norm(body(S+'/probe.s'))
d=[l for l in difflib.unified_diff(a,b,'target','mine',lineterm='',n=2)]
n=sum(1 for l in d if l[:1] in '+-' and not l.startswith(('+++','---')))
print('DIFF',n,'len',len(a),len(b))
if '-v' in os.environ.get('PV',''): print('\n'.join(d))
