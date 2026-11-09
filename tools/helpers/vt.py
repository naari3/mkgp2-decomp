# vt.py SRC OBJ FN VARIANTS [CC]: variants file blocks sep by ====\n; block0 = original snippet
import sys,subprocess,os
src,obj,fn,vf=sys.argv[1:5]; cc=sys.argv[5] if len(sys.argv)>5 else '-'
H=os.path.dirname(os.path.abspath(__file__)); S=os.path.join(os.path.dirname(os.path.dirname(H)),'build')
bl=open(vf).read().split('====\n'); s=open(src).read(); assert bl[0] in s, 'orig not found'
ext=os.path.splitext(src)[1]
for i,v in enumerate(bl[1:]):
    p=S+'/var'+ext; open(p,'w').write(s.replace(bl[0],v))
    r=subprocess.run(['python3',os.path.join(H,'probe.py'),p,obj,fn,cc]+sys.argv[6:],capture_output=True,text=True)
    print(i,r.stdout.strip().splitlines()[0] if r.stdout else r.stderr[-300:])
