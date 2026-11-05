#include "game/SpriteTex801F_private.h"
/* Set a pixel-space texture rectangle, optionally reversing either axis. */
extern "C" void fn_801F6D58(SpriteTex801F *s, const TextureRect801F *rect, unsigned char flipX, unsigned char flipY) {
    float invW=1.0f / s->h18;
    float invH=1.0f / s->h1A;
    float x, y, h;
    h=rect->height;
    y=rect->y;
    x=rect->x;
    float w=rect->width;
    s->width=w;
    s->height=h;
    float left=(0.5f+x)*invW;
    float right=invW*((x+w)-0.5f);
    float top=(0.5f+y)*invH;
    float bottom=invH*((y+h)-0.5f);
    if(flipX) { s->u0=right; s->u1=left; }
    else { s->u0=left; s->u1=right; }
    if(flipY) { s->v1=bottom; s->v0=top; }
    else { s->v1=top; s->v0=bottom; }
    LoadSpriteMatrix801F(s);
}
