import subprocess,itertools
def run(src):
    r=subprocess.run(['bash','-c','python3 /tmp/claude-0/put.py && /tmp/claude-0/try.sh'],input=src,capture_output=True,text=True)
    return r.stdout.strip()
P={'x':"vz * a->m[2][0] + (a->m[0][0] * vx + vy * a->m[1][0])",'y':"vz * a->m[2][1] + (a->m[0][1] * vx + vy * a->m[1][1])",'z':"vz * a->m[2][2] + (vx * a->m[0][2] + vy * a->m[1][2])"}
T={'x':'a->m[3][0]','y':'a->m[3][1]','z':'a->m[3][2]'}
for hb in ['a + b','b + a']:
 H=f'static inline float Add2(float a, float b) {{ return {hb}; }}\n'
 for store in ['vars','direct','varsdecl']:
  for decl in itertools.permutations('xyz'):
   for p in ['opt_propagation off','','opt_propagation off\n#pragma opt_lifetimes off','opt_propagation off\n#pragma opt_common_subs off']:
    body="".join(f"    float v{c} = v->{c};\n" for c in decl)
    if store=='vars':
        body+="    float x, y, z;\n"+"".join(f"    {c} = Add2({P[c]}, {T[c]});\n" for c in 'xyz')+"    out->x = x; out->y = y; out->z = z;\n"
    elif store=='varsdecl':
        body+="".join(f"    float {c} = Add2({P[c]}, {T[c]});\n" for c in 'xyz')+"    out->x = x; out->y = y; out->z = z;\n"
    else:
        body+="".join(f"    out->{c} = Add2({P[c]}, {T[c]});\n" for c in 'xyz')
    pre=f"#pragma push\n#pragma {p}\n" if p else ""; post="\n#pragma pop" if p else ""
    src=H+pre+"void fn_8019EB9C(Matrix44 *a, Vec3 *out, const Vec3 *v) {\n"+body+"}"+post+"\n"
    r=run(src)
    print(r,hb,store,''.join(decl),repr(p),flush=True)
    if r=='0': open('/tmp/claude-0/WIN.cpp','w').write(src); raise SystemExit
