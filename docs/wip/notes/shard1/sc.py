# sc.py SRC OBJ FN [-d]  : score SRC (a file) for FN, print diff with -d
import sys, os, difflib
sys.path.insert(0, '/mnt/project-files/setup/tools')
import cperm
src, obj, fn = sys.argv[1:4]
b = cperm.Builder(obj, fn, os.environ.get('CC_') or None, '/tmp/claude-0/sc/w')
t = cperm.target_body(fn); o = b.build(src)
print('score', cperm.score(t, o) if o else 'FAIL')
if '-d' in sys.argv and o:
    for l in difflib.unified_diff(t, o, 'target', 'ours', lineterm='', n=2): print(l)
