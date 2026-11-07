#include "game/DrawQuadScaled801FPrivate.h"

static inline void DrawPositionDepth8728(float x, float y, const DrawDesc801F *description) {
    float z = description->z;
    DrawPositionDepth801F(x, y, z);
}
extern "C" void fn_801F8728(DrawNode801F *self) {
    DrawQuad7F50 quad(self->description);
    GXBegin(128,0,4);
    if (!self->depth) {
        DrawPosition801F(quad.x0,quad.y0);
        DrawColor801F(self->description->colors[0]);
        DrawPosition801F(quad.x1,quad.y1);
        DrawColor801F(self->description->colors[1]);
        DrawPosition801F(quad.x2,quad.y2);
        DrawColor801F(self->description->colors[2]);
        DrawPosition801F(quad.x3,quad.y3);
        DrawColor801F(self->description->colors[3]);
    } else {
        DrawPositionDepth8728(quad.x0,quad.y0,self->description);
        DrawColor801F(self->description->colors[0]);
        DrawPositionDepth8728(quad.x1,quad.y1,self->description);
        DrawColor801F(self->description->colors[1]);
        DrawPositionDepth8728(quad.x2,quad.y2,self->description);
        DrawColor801F(self->description->colors[2]);
        DrawPositionDepth8728(quad.x3,quad.y3,self->description);
        DrawColor801F(self->description->colors[3]);
    }
}
