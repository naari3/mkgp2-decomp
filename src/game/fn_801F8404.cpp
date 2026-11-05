#include "game/DrawQuad8404Private.h"

extern "C" void fn_801F8404(DrawNode801F *self) {
    DrawQuad8404 quad(self->description);
    GXBegin(128,0,4);
    if (!self->depth) {
        DrawPosition801F(quad.x0,quad.y0);
        DrawUV801F(self->description->u0,self->description->v0);
        DrawPosition801F(quad.x1,quad.y1);
        DrawUV801F(self->description->u0,self->description->v1);
        DrawPosition801F(quad.x2,quad.y2);
        DrawUV801F(self->description->u1,self->description->v1);
        DrawPosition801F(quad.x3,quad.y3);
        DrawUV801F(self->description->u1,self->description->v0);
    } else {
        DrawPositionDepth801F(quad.x0,quad.y0,self->description->z);
        DrawUV801F(self->description->u0,self->description->v0);
        DrawPositionDepth801F(quad.x1,quad.y1,self->description->z);
        DrawUV801F(self->description->u0,self->description->v1);
        DrawPositionDepth801F(quad.x2,quad.y2,self->description->z);
        DrawUV801F(self->description->u1,self->description->v1);
        DrawPositionDepth801F(quad.x3,quad.y3,self->description->z);
        DrawUV801F(self->description->u1,self->description->v0);
    }
}
