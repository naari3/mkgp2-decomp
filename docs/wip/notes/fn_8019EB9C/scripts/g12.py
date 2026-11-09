import subprocess,itertools
def run(src):
    r=subprocess.run(['bash','-c','python3 /tmp/claude-0/put.py && /tmp/claude-0/try.sh'],input=src,capture_output=True,text=True)
    return r.stdout.strip() or '999'
VECS={
'ctor':"struct V3 { float x, y, z; V3() {} V3(float a, float b, float c) : x(a), y(b), z(c) {}\n  V3 operator+(const V3& o) const { return V3(x + o.x, y + o.y, z + o.z); }\n  V3 operator+ADD };\n",
'ctor_rev':"struct V3 { float x, y, z; V3() {} V3(float a, float b, float c) : x(a), y(b), z(c) {}\n  V3 operator+(const V3& o) const { return V3(o.x + x, o.y + y, o.z + z); }\n  V3 operator+ADD };\n",
'local':"struct V3 { float x, y, z; V3() {} V3(float a, float b, float c) : x(a), y(b), z(c) {}\n  V3 operator+(const V3& o) const { V3 r; r.x = x + o.x; r.y = y + o.y; r.z = z + o.z; return r; }\n  V3 operator+ADD };\n",
'pluseq':"struct V3 { float x, y, z; V3() {} V3(float a, float b, float c) : x(a), y(b), z(c) {}\n  V3& operator+=(const V3& o) { x += o.x; y += o.y; z += o.z; return *this; }\n  V3 operator+(const V3& o) const { V3 r(*this); r += o; return r; }\n };\n",
}
ROT="V3(v.z*m[2][0] + (m[0][0]*v.x + v.y*m[1][0]), v.z*m[2][1] + (m[0][1]*v.x + v.y*m[1][1]), v.z*m[2][2] + (v.x*m[0][2] + v.y*m[1][2]))"
TR="V3(m[3][0], m[3][1], m[3][2])"
TRREF="*(const V3*)m[3]"
bodies={
 'rot_plus_tr': f"return {ROT} + {TR};",
 'rot_plus_trref': f"return {ROT} + {TRREF};",
 'tr_plus_rot': f"return {TR} + {ROT};",
 'trref_plus_rot': f"return {TRREF} + {ROT};",
 'rotfn_plus': "return Rotate(v) + " + TRREF + ";",
 'rotfn_plus_tr': "return Rotate(v) + " + TR + ";",
 'rotvar': f"V3 r = Rotate(v); return r + {TRREF};",
 'rotvar_pe': f"V3 r = Rotate(v); r += {TRREF}; return r;",
}
for vn,vec in VECS.items():
  vec=vec.replace("  V3 operator+ADD };\n","};\n")
  for bn,b in bodies.items():
    if 'pe' in bn and vn!='pluseq': continue
    for call in ["    *(V3*)out = *(const M4*)a * *(const V3*)v;\n","    V3 t = *(const M4*)a * *(const V3*)v;\n    out->x = t.x; out->y = t.y; out->z = t.z;\n"]:
      src=vec+"struct M4 { float m[4][4];\n  V3 Rotate(const V3& v) const { return "+ROT+"; }\n  V3 operator*(const V3& v) const { "+b+" }\n};\nvoid fn_8019EB9C(Matrix44 *a, Vec3 *out, const Vec3 *v) {\n"+call+"}\n"
      r=run(src); print(r,vn,bn,'assign' if 'V3 t' not in call else 'tmp',flush=True)
      open(f'/tmp/claude-0/g12_{vn}_{bn}_{len(call)}.cpp','w').write(src)
      if r=='0': raise SystemExit
