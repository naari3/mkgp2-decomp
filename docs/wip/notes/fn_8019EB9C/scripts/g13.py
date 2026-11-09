import subprocess,itertools,random
def run(src):
    r=subprocess.run(['bash','-c','python3 /tmp/claude-0/put.py && /tmp/claude-0/try.sh'],input=src,capture_output=True,text=True)
    return r.stdout.strip() or '999'
H="static inline float Add(float a, float b) { return a + b; }\nstatic inline float Mul(float a, float b) { return a * b; }\n"
def comp(k,ch,V):
    vx,vy,vz=V
    m=lambda r:f"a->m[{r}][{k}]"
    p0=(f"{vx} * {m(0)}" if k==2 else f"{m(0)} * {vx}") if not ch[0] else (f"Mul({vx}, {m(0)})" if k==2 else f"Mul({m(0)}, {vx})")
    p1=f"{vy} * {m(1)}" if not ch[1] else f"Mul({vy}, {m(1)})"
    p2=f"{vz} * {m(2)}" if not ch[2] else f"Mul({vz}, {m(2)})"
    inner=f"({p0} + {p1})" if not ch[3] else f"Add({p0}, {p1})"
    mid=f"({p2} + {inner})" if not ch[4] else f"Add({p2}, {inner})"
    return f"{m(3)} + {mid}" if not ch[5] else (f"Add({mid}, {m(3)})" if ch[6] else f"Add({m(3)}, {mid})")
R=random.Random(1); best=99
for it in range(400):
    ch=[R.random()<0.5 for _ in range(7)]
    loc=R.random()<0.6
    order=list('xyz'); R.shuffle(order)
    V=('vx','vy','vz') if loc else ('v->x','v->y','v->z')
    body="".join(f"    float v{c} = v->{c};\n" for c in order) if loc else ""
    body+="".join(f"    float {n} = {comp(k,ch,V)};\n" for k,n in enumerate('xyz'))+"    out->x = x; out->y = y; out->z = z;\n"
    src=H+"void fn_8019EB9C(Matrix44 *a, Vec3 *out, const Vec3 *v) {\n"+body+"}\n"
    r=int(run(src))
    if r<=best: best=r; print(r,ch,loc,order,flush=True); open(f'/tmp/claude-0/g13_{r}.cpp','w').write(src)
    if r==0: raise SystemExit
