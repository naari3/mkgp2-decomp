import subprocess,re,sys,itertools,os
from multiprocessing import Pool
base=open("/tmp/claude-0/vs_base.c").read().split("\n")
lines=[2494,2504,2506,2513,2543,2580,2608,2682,2697,2710]
DECL=["    int i;","    int peers = 0;","    int slot;"]
di=base.index(DECL[0]); assert base[di+1]==DECL[1] and base[di+2]==DECL[2]
CC='build/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/1.3.2/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -multibyte -i include -i build/GNLJ82/include -DBUILD_VERSION=0 -DVERSION_GNLJ82 -DNDEBUG=1 -Cpp_exceptions on -lang=c -c {src} -o {out}'
def norm(txt):
    out=[]
    for l in txt.split("\n"):
        l=l.strip()
        if not l or "R_PPC" in l or "Unknown" in l or ":" not in l: continue
        l=re.sub(r"^[0-9a-f]+:\s*","",l); l=re.sub(r"0x[0-9a-f]+ <[^>]*>","",l)
        out.append(l)
    return out
T=norm(subprocess.run("llvm-objdump -d --no-show-raw-insn --disassemble-symbols=VSMode_Init build/GNLJ82/obj/game/VSMode_FrameUpdate.o",shell=True,capture_output=True,text=True).stdout)
import difflib
def gen(state):
    loops,perm=state
    L=list(base)
    for ln,st in zip(lines,loops):
        s=L[ln-1].replace("for (int i = 0","for (i = 0")
        if st: s=s.replace("for (i = 0","for (int i = 0")
        L[ln-1]=s
    for k,p in enumerate(perm): L[di+k]=DECL[p]
    return "\n".join(L)
def score(state):
    w=os.getpid()
    src=f"src/game/_sw{w}.c"; out=f"/tmp/claude-0/sw{w}"
    os.makedirs(out,exist_ok=True)
    open(src,"w").write(gen(state))
    r=subprocess.run(CC.format(src=src,out=out),shell=True,capture_output=True,text=True)
    o=f"{out}/_sw{w}.o"
    if r.returncode: return (99999,state)
    O=norm(subprocess.run(f"llvm-objdump -d --no-show-raw-insn --disassemble-symbols=VSMode_Init {o}",shell=True,capture_output=True,text=True).stdout)
    d=sum(1 for x in difflib.unified_diff(T,O,lineterm="",n=0) if x[:1] in "+-" and x[:3] not in ("+++","---"))
    return (d,state)
if __name__=="__main__":
    states=[(lp,pm) for pm in itertools.permutations(range(3)) for lp in itertools.product([False,True],repeat=len(lines))]
    if len(sys.argv)>1: states=states[:int(sys.argv[1])]
    best=None
    with Pool(4) as p:
        for i,(d,st) in enumerate(p.imap_unordered(score,states,chunksize=8)):
            if best is None or d<best[0]:
                best=(d,st); print(i,d,st,flush=True)
    print("BEST",best)
    open("/tmp/claude-0/vs_sweep.c","w").write(gen(best[1]))
    for f in os.listdir("src/game"):
        if f.startswith("_sw"): os.remove("src/game/"+f)
