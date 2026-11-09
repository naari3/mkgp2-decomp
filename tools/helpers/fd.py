# usage: fd.py <src-relative obj path e.g. game/StrPcb_Commands> <fn>
import subprocess,sys,re,os,glob
os.chdir('/home/claude/mkgp2-decomp')
obj,fn=sys.argv[1],sys.argv[2]
def body(path):
    out=[];on=False
    for l in open(path):
        if l.startswith('.fn '+fn+','): on=True;continue
        if on and l.startswith('.endfn'): break
        if on:
            m=re.match(r'/\* [0-9A-F]+ [0-9A-F]+  (.. .. .. ..) \*/\t(.*)',l)
            if m: out.append(m.group(2))
            elif l.strip().startswith('.L'): out.append(l.strip())
    return out
o='/tmp/claude-0/d/mine.s'
subprocess.run(['build/tools/dtk','elf','disasm','build/GNLJ82/src/'+obj+'.o',o],check=True,capture_output=True)
t=None
for p in glob.glob('build/GNLJ82/asm/**/*.s',recursive=True):
    if ('.fn '+fn+',') in open(p).read(): t=p;break
a=body(t);b=body(o)
norm=lambda L:[re.sub(r'\.L_[0-9A-F]+','.L',x) for x in L]
a=norm(a);b=norm(b)
import difflib
for l in difflib.unified_diff(a,b,'target','mine',lineterm='',n=3): print(l)
