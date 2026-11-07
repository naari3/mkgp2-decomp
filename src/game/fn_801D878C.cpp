#include "game/FlowKartDraw_private.h"
static inline unsigned int FKColor(unsigned char r,unsigned char g,unsigned char b,unsigned char a) { return (r<<24)|(g<<16)|(b<<8)|a; }
static inline void FKDrawText(FKDrawView *self,FKDrawPart *part,unsigned char r,unsigned char g,unsigned char b) {
    float y=self->y+part->y;
    float x=self->x+part->x;
    const char *s=part->text;
    TextManager t;
    TexMgr_SetTexture(&t,s);
    fn_801F93EC(&t,x,y);
    unsigned char a=(int)(lbl_806DA190*self->alpha);
    t.scale=lbl_806DA194;
    t.color=FKColor(r,g,b,a);
    fn_801F8A34(fn_801F8E58(),&t,self->layer);
}
static inline void FKDrawWhiteText(FKDrawView *self,FKDrawPart *part) {
    float y=self->y+part->y;
    float x=self->x+part->x;
    const char *s=part->text;
    TextManager t;
    TexMgr_SetTexture(&t,s);
    fn_801F93EC(&t,x,y);
    int a=(int)(lbl_806DA190*self->alpha);
    t.scale=lbl_806DA194;
    t.color=__rlwimi(0xFFFFFF00U,a,0,24,31);
    fn_801F8A34(fn_801F8E58(),&t,self->layer);
}
extern "C" void fn_801D878C(FKDrawView *self) {
    fn_801A0004(self->sprite);
    if ((unsigned char)(lbl_8039E9F8[self->index].primary >= 0) == 1)
        FKDrawText(self,&self->primary,0xE0,0x20,0x20);
    for (int i=0;i<3;++i) {
        if ((unsigned char)(lbl_8039E9F8[self->index].secondary[i] >= 0) == 1) {
            FKDrawWhiteText(self,&self->secondary[i]);
        }
    }
}
