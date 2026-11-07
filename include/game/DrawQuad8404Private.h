#include "game/DrawQuad801F.h"
struct DrawQuad8404 {
    float x0,y0,x1,y1,x2,y2,x3,y3;
    DrawQuad8404(DrawDesc801F *d) {
        double width = __fabs(d->width * d->scaleX);
        double height = __fabs(d->height * d->scaleY);
        float w = width;
        float h = height;
        float sinPart, cosPart;
        float dx;
        if (lbl_806DA718 == d->angle) {
            dx = lbl_806DA718;
            sinPart = dx;
            cosPart = lbl_806DA734;
        } else {
            float sine = lbl_806DA714 * d->anchorX;
            cosPart = lbl_806DA714 * d->anchorY;
            dx = h * sine;
            sinPart = w * sine;
        }
        SetCorners(d, w, h, sinPart, cosPart, dx);
    }
    void SetCorners(DrawDesc801F *d, float w, float h, float sinPart, float cosPart, float dx) {
        float dy = h * cosPart;
        float wx = w * cosPart;
        float left = d->x - dx;
        float top = d->y - dy;
        float right = d->x + dx;
        float bottom = d->y + dy;
        x0 = wx + left;
        y0 = top - sinPart;
        x1 = wx + right;
        y1 = bottom - sinPart;
        x2 = right - wx;
        y2 = sinPart + bottom;
        x3 = left - wx;
        y3 = sinPart + top;
    }
    ~DrawQuad8404() {}
};
