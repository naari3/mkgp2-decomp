import random,subprocess,itertools,os,sys
D="/tmp/claude-0/cc"
CC=sys.argv[3] if len(sys.argv)>3 else "2.6"
tgt=open('/tmp/claude-0/obj.s').read().splitlines()
def score(src,cc=CC):
    fn=f'{D}/r{os.getpid()}.cpp'; o=fn+'.o'
    open(fn,'w').write("struct Matrix44 { float m[4][4]; };\nstruct Vec3 { float x, y, z; };\n"+src)
    r=subprocess.run(f"build/tools/wibo build/compilers/GC/{cc}/mwcceppc.exe -nodefaults -proc gekko -align powerpc -enum int -fp hardware -Cpp_exceptions off -O4,p -inline auto -RTTI off -fp_contract on -lang=c++ -c {fn} -o {o}",shell=True,capture_output=True)
    if r.returncode: return 999
    out=subprocess.run(f"build/binutils/powerpc-eabi-objdump -d --no-show-raw-insn {o}",shell=True,capture_output=True,text=True).stdout
    l=out[out.index('<fn_8019EB9C'):].splitlines()[1:]
    l=[x.split('\t',1)[1].strip() if '\t' in x else x for x in l]
    l=l[:l.index('blr')+1] if 'blr' in l else l
    import difflib
    return sum(1 for d in difflib.ndiff(tgt,l) if d[:1] in '+-')
def gen(R):
    lines=[]
    vloc = R.random()<0.6
    order = list('xyz'); R.shuffle(order)
    V={c:(f"v{c}" if vloc else f"v->{c}") for c in 'xyz'}
    mstyle=R.choice(['m','a','col'])
    def M(i):
        if mstyle=='m': return f"m[{i}]"
        if mstyle=='a': return f"a->m[{i//4}][{i%4}]"
        return f"c{i%4}[{i-(i%4)}]"
    pre=[]
    if mstyle=='m': pre.append("const float *m = &a->m[0][0];")
    if mstyle=='col':
        for k in range(3): pre.append(f"const float *c{k} = &a->m[0][{k}];")
    if vloc:
        for c in order: pre.append(f"float v{c} = v->{c};")
    R.shuffle(pre)
    lines+=pre
    form=R.choice(['expr','acc','acc2','pe','split'])
    corder=list(range(3)); 
    if R.random()<0.5: R.shuffle(corder)
    names='xyz'
    declare_top=R.random()<0.4
    if declare_top: lines.append("float x, y, z;")
    T="" if declare_top else "float "
    for k in corder:
        n=names[k]
        a = f"{V['x']} * {M(k)}" if k==2 else f"{M(k)} * {V['x']}"
        b = f"{V['y']} * {M(4+k)}"; c=f"{V['z']} * {M(8+k)}"; d=M(12+k)
        if form=='expr': lines.append(f"{T}{n} = {d} + ({c} + ({a} + {b}));")
        elif form=='acc': lines+= [f"{T}{n} = {a} + {b};", f"{n} = {c} + {n};", f"{n} = {d} + {n};"]
        elif form=='acc2': lines+= [f"{T}{n} = {a} + {b};", f"{n} = {d} + ({c} + {n});"]
        elif form=='pe': lines+= [f"{T}{n} = {a} + {b};", f"{n} += {c};", f"{n} += {d};"]
        else: lines+= [f"{T}{n} = {c} + ({a} + {b});", f"{n} = {d} + {n};"]
    lines.append("out->x = x; out->y = y; out->z = z;")
    src="void fn_8019EB9C(Matrix44 *a, Vec3 *out, const Vec3 *v) {\n    "+"\n    ".join(lines)+"\n}\n"
    pr=R.choice(['','','opt_common_subs off','opt_propagation off','opt_common_subs off\n#pragma opt_propagation off','opt_lifetimes off','opt_common_subs off\n#pragma opt_lifetimes off'])
    if pr: src="#pragma "+pr+"\n"+src
    return src
seed=int(sys.argv[1]); R=random.Random(seed); best=999
for it in range(int(sys.argv[2])):
    s=gen(R); sc=score(s)
    if sc<best:
        best=sc; print(sc,flush=True); open(f'{D}/best_{seed}_{sc}.cpp','w').write(s)
    if sc==0: print("MATCH"); break
