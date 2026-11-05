#include "game/HudSprite2454Private.h"
extern "C" int fn_80245420(HudSprite2454 *self, unsigned char draw) {
    int result=1;
    ResCtrl c;
    int layer=self->layer;
    float scale=self->scale * fn_8020A6CC(self->size);
    fn_80121E10(&c);
    c.resId=0x1CD3;
    float x=self->x;
    float y=self->y;
    c.Show(x,y,lbl_806DBE90);
    c.SetScale(scale);
    c.field28=fn_8020A6CC(self->rotation);
    c.tail[0]=1; c.tail[1]=1; c.tail[2]=1;
    unsigned int color=(unsigned char)fn_8020A788(self->color);
    c.SetColor((color<<24)|(color<<16)|(color<<8)|255);
    if (draw) fn_8011FAFC(&c,layer);
    HudTweenTick(self->size);
    HudTweenTick(self->rotation);
    HudTweenTick(self->color);
    if (self->size->frame >= self->size->limit) {
        if (lbl_806DBE90 == fn_8020A6CC(self->size)) {
            fn_8020A734(self->size,10,lbl_806DBE90,lbl_806DBE64);
            fn_8020A7CC(self->color,255,0,10);
        } else result=1;
    }
    return result;
}
