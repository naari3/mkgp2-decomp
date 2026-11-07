#include "game/DrawQuad7F50Private.h"
static inline void DrawPositionDepth7F50(float x, float y, const DrawDesc801F *description) {
    float z = description->z;
    DrawPositionDepth801F(x, y, z);
}
extern "C" void fn_801F7F50(DrawNode801F *self) {
    DrawQuad7F50 quad(self->description);
    GXBegin(128, 0, 4);
    if (!self->depth) {
        DrawPosition801F(quad.x0, quad.y0);
        DrawColor801F(self->description->colors[0]);
        DrawUV801F(self->description->u0, self->description->v0);
        DrawPosition801F(quad.x1, quad.y1);
        DrawColor801F(self->description->colors[1]);
        DrawUV801F(self->description->u0, self->description->v1);
        DrawPosition801F(quad.x2, quad.y2);
        DrawColor801F(self->description->colors[2]);
        DrawUV801F(self->description->u1, self->description->v1);
        DrawPosition801F(quad.x3, quad.y3);
        DrawColor801F(self->description->colors[3]);
        DrawUV801F(self->description->u1, self->description->v0);
    } else {
        DrawPositionDepth7F50(quad.x0, quad.y0, self->description);
        DrawColor801F(self->description->colors[0]);
        DrawUV801F(self->description->u0, self->description->v0);
        DrawPositionDepth7F50(quad.x1, quad.y1, self->description);
        DrawColor801F(self->description->colors[1]);
        DrawUV801F(self->description->u0, self->description->v1);
        DrawPositionDepth7F50(quad.x2, quad.y2, self->description);
        DrawColor801F(self->description->colors[2]);
        DrawUV801F(self->description->u1, self->description->v1);
        DrawPositionDepth7F50(quad.x3, quad.y3, self->description);
        DrawColor801F(self->description->colors[3]);
        DrawUV801F(self->description->u1, self->description->v0);
    }
}
