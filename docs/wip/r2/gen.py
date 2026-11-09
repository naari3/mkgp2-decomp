import re
D='/tmp/claude-0/cfm/'
def rd(f): return [l for l in open(D+f).read().split('\n') if not l.startswith('#include')]
def cut(lines, start_pred):
    for i,l in enumerate(lines):
        if start_pred(l): return '\n'.join(lines[:i]), '\n'.join(lines[i:])
    raise Exception('no')
a=rd('fn_801CE800.c'); a=[l for l in a if l!='#pragma force_active on']
pre800,fn800=cut(a,lambda l:l.startswith('void fn_801CE800('))
fn918='\n'.join(rd('fn_801CE918.cpp'))
fnB78='\n'.join(rd('fn_801CEB78.cpp'))
preF188,fnF188=cut(rd('fn_801CF188.c'),lambda l:l.startswith('void fn_801CF188('))
preUpd,fnUpd=cut(rd('clFlowCourse_Update.cpp'),lambda l:l.startswith('extern "C" int clFlowCourse_Update('))
c=rd('clFlowCourse.cpp')
def idx(p): return [i for i,l in enumerate(c) if l.startswith(p)][0]
iD=idx('CourseFlow::~CourseFlow()'); iP=idx('inline CoursePulse::CoursePulse()'); iI=idx('CourseFlow::CourseFlow()')
i16=idx('extern "C" int fn_801D161C'); iF=idx('static inline int FadeAlpha'); i84=idx('extern "C" void fn_801D1684')
def ren(t): return re.sub(r'\bCourseCup\b','FlowCourseCup',re.sub(r'\bSetSpritePosition\b','FlowSetSpritePosition',t))
preC=ren('\n'.join(c[:iD]+c[iP:iI]+c[iF:i84]))
fnD=ren('\n'.join(c[iD:iP])); fnI=ren('\n'.join(c[iI:i16])); fn16=ren('\n'.join(c[i16:iF])); fn84=ren('\n'.join(c[i84:]))
head=open(D+'head.cpp').read()
out=head+'''namespace course_sel {
extern "C" {
'''+pre800+'''
}
}
namespace course_draw {
extern "C" {
'''+preF188+'''
}
}
namespace course_update {
'''+preUpd+'''
}
'''+preC+'''

/* With -inline deferred CW generates the functions at the end of the TU in
 * reverse source order, so they are defined here from last to first. */
#pragma push
#pragma dont_inline on
'''+fn84+'''
#pragma pop
'''+fn16+'\n'+fnI+'\n'+fnD+'''
namespace course_update {
'''+fnUpd+'''
}
namespace course_draw {
extern "C" {
'''+fnF188+'''
}
}
namespace course_rows {
'''+fnB78+'\n'+fn918+'''
}
namespace course_sel {
extern "C" {
'''+fn800+'''
}
}
'''
open('/home/user/mkgp2-decomp/src/game/clFlowCourse.cpp','w').write(out)
