import re,sys,os
S='/tmp/claude-0/-home-user-mkgp2-decomp/e0ce56b7-f975-5000-bf19-fb87ae98bd81/scratchpad/'
s=open(S+'rh/orig.cpp').read()
def rep(a,b):
    global s
    assert s.count(a)==1,a
    s=s.replace(a,b)
rep("    char pad8[8];\n    char res[11][0x58];","    int frame;\n    unsigned char fC;\n    char padD[3];\n    char res[11][0x58];")
rep("asm void fn_80147900(struct HudResSet *o);\n","void fn_80147900(struct HudResSet *o);\n")
rep("asm void fn_80147CE8(void);","asm void fn_80147CE8(struct HudResSet *o);")
rep("asm void fn_80147AF4(void);","asm void fn_80147AF4(struct HudResSet *o);")
rep('extern "C" asm void fn_80147CE8(void) {','extern "C" asm void fn_80147CE8(struct HudResSet *o) {')
rep('extern "C" asm void fn_80147AF4(void) {','extern "C" asm void fn_80147AF4(struct HudResSet *o) {')
for fn in os.environ.get('CFNS','fn_80147900').split(','):
    m=re.search(r'__declspec\(section "\.extab_user"\) static const unsigned char extab_%s\[8\] = \{\n.*?\n\};\n'%fn,s,re.S); s=s[:m.start()]+s[m.end():]
    m=re.search(r'__declspec\(section "\.extabindex_user"\) static const struct \{ void \*fn; unsigned int fn_size; void \*extab; \} extabindex_%s = \{\n.*?\n\};\n'%fn,s,re.S); s=s[:m.start()]+s[m.end():]
i=s.index('extern "C" asm void fn_80147900(struct HudResSet *o) {'); j=s.index('\n}\n',i)+3
s=s[:i]+open(os.environ.get('F900',S+'rh/f900.cpp')).read()+s[j:]
if os.environ.get('FAF4'):
    i=s.index('extern "C" asm void fn_80147AF4(struct HudResSet *o) {'); j=s.index('\n}\n',i)+3
    s=s[:i]+open(os.environ['FAF4']).read()+s[j:]
    s=s.replace('asm void fn_80147AF4(struct HudResSet *o);','void fn_80147AF4(struct HudResSet *o);')
open(sys.argv[1],'w').write(s)
