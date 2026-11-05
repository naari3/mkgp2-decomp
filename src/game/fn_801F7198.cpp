#include "game/SpriteTex801F_private.h"
static inline void SelectTexture(TextureOwner801F *owner, SpriteTex801F *s, unsigned int index) {
    unsigned int count=owner->bank->count;
    if ((unsigned char)(index >= count) == 1) __assert(lbl_803BF050,0x476,lbl_803BF05C);
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
extern "C" void fn_801F7198(TextureOwner801F *owner, SpriteTex801F *s, unsigned int index) {
    SelectTexture(owner, s, index);
}
