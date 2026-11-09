import subprocess,itertools
def run(src):
    r=subprocess.run(['bash','-c','python3 /tmp/claude-0/put.py && /tmp/claude-0/try.sh'],input=src,capture_output=True,text=True)
    return r.stdout.strip() or r.stderr[-200:]
X="m[3][0] + (v.z*m[2][0] + (m[0][0]*v.x + v.y*m[1][0]))"
Y="m[3][1] + (v.z*m[2][1] + (m[0][1]*v.x + v.y*m[1][1]))"
Z="m[3][2] + (v.z*m[2][2] + (v.x*m[0][2] + v.y*m[1][2]))"
VEC_PLAIN="struct V3 { float x, y, z; };\n"
VEC_CTOR="struct V3 { float x, y, z; V3() {} V3(float a, float b, float c) : x(a), y(b), z(c) {} };\n"
VEC_CTOR_ASSIGN="struct V3 { float x, y, z; V3() {} V3(float a, float b, float c) { x = a; y = b; z = c; } };\n"
VEC_CC="struct V3 { float x, y, z; V3() {} V3(float a, float b, float c) : x(a), y(b), z(c) {} V3(const V3& o) : x(o.x), y(o.y), z(o.z) {} V3& operator=(const V3& o) { x = o.x; y = o.y; z = o.z; return *this; } };\n"
MTX="struct M4 { float m[4][4];\n"
methods={
 'ret_ctor': f"  V3 operator*(const V3& v) const {{ return V3({X}, {Y}, {Z}); }}\n",
 'ret_local': f"  V3 operator*(const V3& v) const {{ V3 r; r.x = {X}; r.y = {Y}; r.z = {Z}; return r; }}\n",
 'ret_xyz': f"  V3 operator*(const V3& v) const {{ float x = {X}; float y = {Y}; float z = {Z}; return V3(x, y, z); }}\n",
 'out_ref': f"  void Transform(const V3& v, V3& out) const {{ out.x = {X}; out.y = {Y}; out.z = {Z}; }}\n",
}
calls={
 'assign': "    *(V3*)out = *(const M4*)a * *(const V3*)v;\n",
 'tmp': "    V3 t = *(const M4*)a * *(const V3*)v;\n    *(V3*)out = t;\n",
 'tmp_fields': "    V3 t = *(const M4*)a * *(const V3*)v;\n    out->x = t.x; out->y = t.y; out->z = t.z;\n",
 'xform_tmp': "    V3 t;\n    ((const M4*)a)->Transform(*(const V3*)v, t);\n    *(V3*)out = t;\n",
 'xform_copyin': "    V3 s = *(const V3*)v;\n    ((const M4*)a)->Transform(s, *(V3*)out);\n",
}
res=[]
for vn,vec in [('plain',VEC_PLAIN),('ctor',VEC_CTOR),('ctorassign',VEC_CTOR_ASSIGN),('cc',VEC_CC)]:
  for mn,meth in methods.items():
    if vn=='plain' and mn in ('ret_ctor','ret_xyz'): continue
    for cn,call in calls.items():
      if (mn=='out_ref') != cn.startswith('xform'): continue
      src=vec+MTX+meth+"};\n"+"void fn_8019EB9C(Matrix44 *a, Vec3 *out, const Vec3 *v) {\n"+call+"}\n"
      r=run(src); print(r,vn,mn,cn,flush=True)
