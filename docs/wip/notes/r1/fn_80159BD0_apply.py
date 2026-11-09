import re,sys
p='/home/user/mkgp2-decomp/src/game/SceneList_80157EA8.cpp'
s=open('/tmp/claude-0/z/bd/base.cpp').read()
body=open(sys.argv[1]).read()
body=re.sub(r'\bF([0-9A-F]{3})\b',r'lbl_806D8\1',body)
a=s.index('extern "C" asm void fn_80159BD0(')
b=s.index('\n}\n',a)+3
s=s[:a]+body+s[b:]
# prototypes
rep={'extern void Item_GetDescriptorField8();':'extern int Item_GetDescriptorField8(int);',
'extern void fn_8013BEC8();':'struct ItemColor;\nextern ItemColor *fn_8013BEC8(int);',
'extern void fn_80168B90();':'void fn_80168B90(int layer, const void *s, float x, float y, float r, float g, float b, float a, ...);',
'extern void fn_8016918C();':'void fn_8016918C(int layer, int id, int f, float x, float y, float sx, float sy, float r, float g, float b, float a);',
'extern void fn_8023D938();':'extern const char *fn_8023D938(int, int);',
'extern void fn_8023DAA8();':'extern const char *fn_8023DAA8(int);',
'    char pad68[4];\n    int rule;':'    int equipped;\n    int rule;'}
for k,v in rep.items():
    assert k in s,k; s=s.replace(k,v)
need=sorted(set(re.findall(r'lbl_806D8[0-9A-F]{3}',body)))
decl=''
for n in need:
    if not re.search(r'^extern .*\b%s\b'%n,s,re.M): decl+='extern const float %s;\n'%n
s=s.replace('extern const float lbl_806D84DC;',decl+'extern const float lbl_806D84DC;',1)
open(p,'w').write(s)
print(decl)
