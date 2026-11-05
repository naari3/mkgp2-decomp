#include "game/TextureRect801FPrivate.h"
extern "C" {
extern const float lbl_806DA710;
void GXLoadTexMtxImm(const float (*)[4], unsigned int, int);
void fn_801F6C2C(TextureSprite801F *self, const TextureRect801F *rect,
                   unsigned char flipX, unsigned char flipY) {
    float half;
    float invHeight;
    float one;
    float invWidth;
    float y;
    float height;
    float x;
    float width;
    one = lbl_806DA710;
    half = lbl_806DA714;
    invWidth = one / self->desc.h18;
    invHeight = one / self->desc.h1A;
    height = rect->height;
    y = rect->y;
    x = rect->x;
    width = rect->width;
    self->desc.width = width;
    self->desc.height = height;
    float left = (half + x) * invWidth;
    float right = invWidth * ((x + width) - half);
    float top = (half + y) * invHeight;
    float bottom = invHeight * ((y + height) - half);
    if (flipX) { self->desc.u0 = right; self->desc.u1 = left; }
    else { self->desc.u0 = left; self->desc.u1 = right; }
    if (flipY) { self->desc.v1 = bottom; self->desc.v0 = top; }
    else { self->desc.v1 = top; self->desc.v0 = bottom; }
    PSMTXScale(self->textureMatrix, self->desc.u1 - self->desc.u0,
              self->desc.v0 - self->desc.v1, lbl_806DA710);
    PSMTXTransApply(self->textureMatrix, self->textureMatrix,
                   self->desc.u0, self->desc.v1, lbl_806DA718);
    GXLoadTexMtxImm(self->textureMatrix, 30, 1);
}
}
