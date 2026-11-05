#include "game/SpriteTex801F_private.h"
/* Set a pixel-space texture rectangle, optionally reversing either axis. */
extern "C" void fn_801F6D58(SpriteTex801F *s, const TextureRect801F *rect, unsigned char flipX, unsigned char flipY) {
    float invW=lbl_806DA710 / s->h18;
    float invH=lbl_806DA710 / s->h1A;
    float h=rect->height;
    float y=rect->y;
    float x=rect->x;
    float w=rect->width;
    s->width=w;
    s->height=h;
    float left=(lbl_806DA714+x)*invW;
    float right=invW*((x+w)-lbl_806DA714);
    float top=(lbl_806DA714+y)*invH;
    float bottom=invH*((y+h)-lbl_806DA714);
    if(flipX) { s->u0=right; s->u1=left; }
    else { s->u0=left; s->u1=right; }
    if(flipY) { s->v1=bottom; s->v0=top; }
    else { s->v1=top; s->v0=bottom; }
    LoadSpriteMatrix801F(s);
}
