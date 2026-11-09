import re,sys
asm=open('/home/user/mkgp2-decomp/build/GNLJ82/asm/auto_11_806D7998_sdata2.s').read()
vals={}
for m in re.finditer(r'\.obj lbl_806D8([0-9A-F]{3}), global\n\t\.float ([^\n]+)\n',asm):
    vals[m.group(1)]=m.group(2)
src=open(sys.argv[1]).read()
keep=set(sys.argv[3].split(',')) if len(sys.argv)>3 else set()
def r(m):
    k=m.group(1)
    if k in keep or k not in vals: return m.group(0)
    v=vals[k]
    if '.' not in v and 'e' not in v: v+='.0'
    return v+'f'
out=re.sub(r'\bF([0-9A-F]{3})\b',r,src)
open(sys.argv[2],'w').write(out)
