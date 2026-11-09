import re,sys
p='/home/user/mkgp2-decomp/src/game/SceneList_80157EA8.cpp'
s=open('/tmp/claude-0/z/a6/base.cpp').read()
body=open(sys.argv[1]).read()
body=re.sub(r'\bF([0-9A-F]{3})\b',r'lbl_806D8\1',body)
a=s.index('extern "C" asm void fn_8015A6E4(')
b=s.index('\n}\n',a)+3
s=s[:a]+body+s[b:]
rep={'extern void fn_8013C26C();':'const char *fn_8013C26C(int,int);',
'extern void fn_8013C4A4();':'void fn_8013C4A4(void *,float);',
'extern void fn_8013C5FC();':'void fn_8013C5FC(void *,float);',
'extern void fn_8013C674();':'void fn_8013C674(void *,float);',
'extern void fn_8013C6EC();':'void fn_8013C6EC(void *,float,float,float);',
'extern void fn_8013C7B0();':'void fn_8013C7B0(void *,float,float);',
'extern void fn_8013C91C();':'void fn_8013C91C(void *);',
'extern void fn_8013DAC8();':'void fn_8013DAC8(void *,int);',
'extern void fn_80167C60();':'void fn_80167C60(int,const void *,float,float,float,...);',
'extern void get_title_name_global();':'struct RankLog;\nconst char *get_title_name_global(RankLog *log);',
'extern void fn_80168B90();':'void fn_80168B90(int layer, const void *s, float x, float y, float r, float g, float b, float a, ...);',
}
for k,v in rep.items():
    assert k in s,k; s=s.replace(k,v)
need=sorted(set(re.findall(r'lbl_806D8[0-9A-F]{3}',body)))
decl=''
for n in need:
    if not re.search(r'^extern .*\b%s\b'%n,s,re.M): decl+='extern const float %s;\n'%n
s=s.replace('extern const float lbl_806D84DC;',decl+'extern const float lbl_806D84DC;',1)
open(p,'w').write(s)
