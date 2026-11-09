import subprocess,itertools
def run(src):
    r=subprocess.run(['bash','-c','python3 /tmp/claude-0/put.py && /tmp/claude-0/try.sh'],input=src,capture_output=True,text=True)
    return r.stdout.strip()
P={'x':"vz * a->m[2][0] + (a->m[0][0] * vx + vy * a->m[1][0])",'y':"vz * a->m[2][1] + (a->m[0][1] * vx + vy * a->m[1][1])",'z':"vz * a->m[2][2] + (vx * a->m[0][2] + vy * a->m[1][2])"}
T={'x':'a->m[3][0]','y':'a->m[3][1]','z':'a->m[3][2]'}
H='static inline float Add2(float a, float b) { return a + b; }\n'
def f(c,m):
    return {'pt':f"Add2({P[c]}, {T[c]})",'tp':f"Add2({T[c]}, {P[c]})",'pl':f"{T[c]} + ({P[c]})",'tmp':None}[m]
best=99
for ms in itertools.product(['pt','tp','pl'],repeat=3):
  for p in ['opt_propagation off','']:
    body="    float vx = v->x;\n    float vy = v->y;\n    float vz = v->z;\n    float x, y, z;\n"
    body+="".join(f"    {c} = {f(c,m)};\n" for c,m in zip('xyz',ms))+"    out->x = x; out->y = y; out->z = z;\n"
    pre=f"#pragma push\n#pragma {p}\n" if p else ""; post="\n#pragma pop" if p else ""
    src=H+pre+"void fn_8019EB9C(Matrix44 *a, Vec3 *out, const Vec3 *v) {\n"+body+"}"+post+"\n"
    r=int(run(src))
    if r<=best: best=r; print(r,ms,repr(p),flush=True); open(f'/tmp/claude-0/g9best_{r}.cpp','w').write(src)
    if r==0: raise SystemExit
