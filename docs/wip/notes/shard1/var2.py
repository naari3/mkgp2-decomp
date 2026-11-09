import sys,subprocess,os
path,obj,fn=sys.argv[1:4]
base=open(path).read()
blocks=open(sys.argv[4]).read().split('====\n')
orig=blocks[0].rstrip('\n'); assert orig in base
for i,v in enumerate(blocks[1:]):
    open('/tmp/claude-0/sc/v'+os.path.splitext(path)[1],'w').write(base.replace(orig,v.rstrip('\n')))
    r=subprocess.run(['python3','/tmp/claude-0/sc/sc.py','/tmp/claude-0/sc/v'+os.path.splitext(path)[1],obj,fn],capture_output=True,text=True)
    print(i,r.stdout.strip(),r.stderr[-300:])
