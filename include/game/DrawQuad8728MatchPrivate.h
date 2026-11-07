#ifndef DRAW_QUAD_8728_MATCH_PRIVATE_H
#define DRAW_QUAD_8728_MATCH_PRIVATE_H
#include "game/DrawQuad801F.h"
struct DrawQuad7F50 {
    float x0,y0,x1,y1,x2,y2,x3,y3;
    DrawQuad7F50(DrawDesc801F *d) {
        float dy, cosPart, dx, w, h, sinPart, left, top, wx, right, bottom;
        w = d->width * d->scaleX;
        h = d->height * d->scaleY;
        double width = __fabs(w);
        double height = __fabs(h);
        w = width;
        h = height;
        if (lbl_806DA718 == d->angle) {
            dx = lbl_806DA718;
            sinPart = dx;
            cosPart = lbl_806DA734;
        } else {
            float sine = 0.5f * d->anchorX;
            cosPart = 0.5f * d->anchorY;
            sinPart = w * sine;
            dx = h * sine;
        }
        dy = h * cosPart;
        wx = w * cosPart;
        left = d->x - dx;
        top = d->y - dy;
        right = d->x + dx;
        bottom = d->y + dy;
        x0 = wx + left;
        y0 = top - sinPart;
        x1 = wx + right;
        y1 = bottom - sinPart;
        x2 = right - wx;
        y2 = sinPart + bottom;
        x3 = left - wx;
        y3 = sinPart + top;
    }
    ~DrawQuad7F50() {}
};

#endif
