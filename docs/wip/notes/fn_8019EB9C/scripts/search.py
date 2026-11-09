# Parallel variant scorer: compiles each variant of fn_8019EB9C straight with mwcc (no ninja), diff lines vs target.
# Run from the repo root after a full build (needs build/GNLJ82/asm).
import subprocess,sys,re,os,glob,difflib,tempfile
from concurrent.futures import ThreadPoolExecutor
R='.'; os.chdir(R)
FN='fn_8019EB9C'
SRC=open('src/game/kartmove/carobject.cpp').read()
ORIG=open('docs/wip/notes/fn_8019EB9C/scripts/orig_block.txt').read()
def body(path):
    out=[];on=False
    for l in open(path):
        if l.startswith('.fn '+FN+','): on=True;continue
        if on and l.startswith('.endfn'): break
        if on:
            m=re.match(r'/\* [0-9A-F]+ [0-9A-F]+  (.. .. .. ..) \*/\t(.*)',l)
            if m: out.append(m.group(2))
    return out
T=body([p for p in glob.glob('build/GNLJ82/asm/**/*.s',recursive=True) if ('.fn '+FN+',') in open(p).read()][0])
CMD='build/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/2.6/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -multibyte -i include -i build/GNLJ82/include -i src/game/kartmove -DBUILD_VERSION=0 -DVERSION_GNLJ82 -DNDEBUG=1 -lang=c++ -Cpp_exceptions on -c {src} -o {obj}'
def score(code):
    os.makedirs('build/fn_8019EB9C_search',exist_ok=True); d=tempfile.mkdtemp(dir='build/fn_8019EB9C_search')
    s=d+'/c.cpp'; o=d+'/c.o'
    open(s,'w').write(SRC.replace(ORIG,code+'\n'))
    r=subprocess.run(CMD.format(src=s,obj=o),shell=True,capture_output=True,text=True)
    if r.returncode: return 9999,r.stdout[-300:]
    subprocess.run(['build/tools/dtk','elf','disasm',o,d+'/m.s'],capture_output=True)
    b=body(d+'/m.s')
    n=sum(1 for l in difflib.unified_diff(T,b,lineterm='',n=0) if l[:1] in '+-' and not l.startswith(('+++','---')))
    subprocess.run(['rm','-rf',d])
    return n,b
def run(variants,jobs=16):
    with ThreadPoolExecutor(jobs) as ex:
        return list(ex.map(lambda kv:(kv[0],score(kv[1])[0]),variants))
if __name__=='__main__':
    for f in sys.argv[1:]:
        print(f,score(open(f).read())[0])
