import sys,itertools,collections; sys.path.insert(0,__import__('os').path.dirname(__file__))
from search import run
P=['vz * a->m[2][0] + (a->m[0][0] * vx + vy * a->m[1][0])',
   'vz * a->m[2][1] + (a->m[0][1] * vx + vy * a->m[1][1])',
   'vz * a->m[2][2] + (vx * a->m[0][2] + vy * a->m[1][2])']
Q=['vz * t%s + (a->m[0][0] * vx + vy * a->m[1][0])',
   'vz * t%s + (a->m[0][1] * vx + vy * a->m[1][1])',
   'vz * t%s + (vx * a->m[0][2] + vy * a->m[1][2])']
def comp(i,w):
    c='xyz'[i]
    if w: return f'    t{c} = a->m[2][{i}];\n    {c} = {Q[i]%c};\n    t{c} = a->m[3][{i}];\n    {c} = t{c} + {c};\n'
    return f'    {c} = {P[i]};\n    t{c} = a->m[3][{i}];\n    {c} = t{c} + {c};\n'
V=[]
for ws in itertools.product([0,1],repeat=3):
 if ws==(0,0,0): continue
 body=''.join(comp(i,ws[i]) for i in range(3))
 for lo in itertools.permutations(['x','y','z','tx','ty','tz']):
    decl='    float vx;\n    float vy;\n    float vz;\n'+''.join(f'    float {c};\n' for c in lo)
    code=f'#pragma push\n#pragma opt_propagation off\n#pragma opt_lifetimes off\nvoid fn_8019EB9C(Matrix44 *a, Vec3 *out, const Vec3 *v) {{\n{decl}    vx = v->x;\n    vy = v->y;\n    vz = v->z;\n{body}    out->x = x; out->y = y; out->z = z;\n}}\n#pragma pop\n'
    V.append(((ws,lo),code))
res=sorted(run(V,8),key=lambda r:r[1])
print(len(V),collections.Counter(n for k,n in res))
best={}
for k,n in res:
  best.setdefault(k[0],(n,k))
for w,v in best.items(): print(v)
