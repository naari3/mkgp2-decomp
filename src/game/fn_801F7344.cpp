#include "game/SpriteTex801F_private.h"
static inline void SelectSpriteTextureU43(TextureOwner801F *owner,SpriteTex801F *s) {
    unsigned int count=owner->bank->count;
    unsigned int index=0;
    if ((unsigned char)(count == 0)) __assert(lbl_803BF050,0x476,lbl_803BF05C);
    unsigned int last=count-1;
    while(index>=count) index=last;
    s->i14=index;
    TextureEntry801F *entries=owner->bank->textures;
    s->h18=entries[s->i14].width;
    s->h1A=entries[s->i14].height;
    float h=s->h1A;
    float w=s->h18;
    float invW=lbl_806DA710 / s->h18;
    float invH=lbl_806DA710 / s->h1A;
    s->width=w;
    s->height=h;
    s->u0=lbl_806DA714 * invW;
    s->u1=invW*((lbl_806DA718+w)-lbl_806DA714);
    s->v1=lbl_806DA714 * invH;
    s->v0=invH*((lbl_806DA718+h)-lbl_806DA714);
    LoadSpriteMatrix801F(s);
}

extern "C" void fn_801F7344(TextureOwner801F *owner,SpriteTex801F *s) {
    SelectSpriteTextureU43(owner,s);
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
