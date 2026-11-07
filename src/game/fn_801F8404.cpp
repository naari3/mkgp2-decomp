#include "game/DrawQuadScaled801FPrivate.h"

static inline void DrawPositionDepth8404(float x, float y, const DrawDesc801F *description) {
    float z = description->z;
    DrawPositionDepth801F(x, y, z);
}
extern "C" void fn_801F8404(DrawNode801F *self) {
    DrawQuad7F50 quad(self->description);
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
        DrawPositionDepth8404(quad.x0,quad.y0,self->description);
        DrawUV801F(self->description->u0,self->description->v0);
        DrawPositionDepth8404(quad.x1,quad.y1,self->description);
        DrawUV801F(self->description->u0,self->description->v1);
        DrawPositionDepth8404(quad.x2,quad.y2,self->description);
        DrawUV801F(self->description->u1,self->description->v1);
        DrawPositionDepth8404(quad.x3,quad.y3,self->description);
        DrawUV801F(self->description->u1,self->description->v0);
    }
}
