import sys
p='src/game/kartmove/carobject.cpp'
s=open('/tmp/claude-0/carobject_orig.cpp').read()
start=s.index('void fn_8019EB9C(Matrix44 *a, Vec3 *out, const Vec3 *v) {')
end=s.index('\n}\n',start)+3
open(p,'w').write(s[:start]+sys.stdin.read()+s[end:])
