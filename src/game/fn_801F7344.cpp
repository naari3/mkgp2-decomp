#include "game/SpriteTex801F_private.h"
extern "C" void fn_801F7344(TextureOwner801F *owner,SpriteTex801F *s) {
    SelectSpriteTexture801F(owner,s,0);
    s->i2C=0;
    s->x=lbl_806DA72C;
    s->y=lbl_806DA730;
    s->z=lbl_806DA710;
    float h,w;
    fn_801F6574(&w,&h);
    if(s->x>=w) s->x-=w; else if(s->x < -w) s->x+=w;
    if(s->y>=h) s->y-=h; else if(s->y < -h) s->y+=h;
    s->angle=lbl_806DA718;
    while(s->angle>lbl_806DA728) s->angle-=lbl_806DA728;
    while(s->angle<lbl_806DA718) s->angle+=lbl_806DA728;
    s->anchorX=(float)sin(s->angle);
    s->anchorY=-(float)cos(s->angle);
    s->scaleX=lbl_806DA710;
    s->scaleY=lbl_806DA710;
    s->colors[0]=-1; s->colors[1]=-1; s->colors[2]=-1; s->colors[3]=-1;
}
