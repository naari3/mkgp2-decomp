# try.py file fn  -- reads variants from stdin separated by lines '====', first block is the original snippet
import sys,subprocess,re
path,obj,fn=sys.argv[1],sys.argv[2],sys.argv[3]
blocks=sys.stdin.read().split('====\n')
orig=blocks[0];src=open(path).read();assert orig in src
for i,v in enumerate(blocks[1:]):
    open(path,'w').write(src.replace(orig,v))
    r=subprocess.run(['ninja','build/GNLJ82/src/'+obj+'.o'],capture_output=True,text=True)
    if r.returncode: print(i,'COMPILE FAIL',r.stdout[-500:]);continue
    d=subprocess.run(['python3',__import__('os').path.join(__import__('os').path.dirname(__import__('os').path.abspath(__file__)),'fd.py'),obj,fn],capture_output=True,text=True).stdout
    n=len([l for l in d.splitlines() if l[:1] in '+-' and not l.startswith(('+++','---'))])
    print('variant',i,'difflines',n)
    if n==0: print('MATCH'); sys.exit(0)
open(path,'w').write(src)
