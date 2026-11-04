#include "game/DrawQuad801F.h"

extern "C" void fn_801F8728(DrawNode801F *self) {
    DrawQuad801F quad(self->description);
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
        DrawPositionDepth801F(quad.x0,quad.y0,self->description->z);
        DrawColor801F(self->description->colors[0]);
        DrawPositionDepth801F(quad.x1,quad.y1,self->description->z);
        DrawColor801F(self->description->colors[1]);
        DrawPositionDepth801F(quad.x2,quad.y2,self->description->z);
        DrawColor801F(self->description->colors[2]);
        DrawPositionDepth801F(quad.x3,quad.y3,self->description->z);
        DrawColor801F(self->description->colors[3]);
    }
}
