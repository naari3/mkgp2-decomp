#ifndef DRAW_QUAD_7F50_MATCH_PRIVATE_H
#define DRAW_QUAD_7F50_MATCH_PRIVATE_H
#include "game/DrawQuad801F.h"
struct DrawQuad7F50 {
    float x0,y0,x1,y1,x2,y2,x3,y3;
    DrawQuad7F50(DrawDesc801F *d) {
        float h, w, top, left, sinPart, wx, dx, right, bottom, cosPart, dy;
        double width = __fabs(d->width * d->scaleX);
        double height = __fabs(d->height * d->scaleY);
        w = width;
        h = height;
        if (lbl_806DA718 == d->angle) {
            dx = lbl_806DA718;
            sinPart = dx;
            cosPart = lbl_806DA734;
        } else {
            float sine = lbl_806DA714 * d->anchorX;
            cosPart = lbl_806DA714 * d->anchorY;
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
