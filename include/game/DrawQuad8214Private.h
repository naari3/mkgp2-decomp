#ifndef DRAW_QUAD_8214_PRIVATE_H
#define DRAW_QUAD_8214_PRIVATE_H
#include "game/DrawQuad801F.h"

struct DrawQuadLocal8214 {
    float x0,y0,x1,y1,x2,y2,x3,y3;
    DrawQuadLocal8214(DrawDesc801F *d) {
        float h, w, top, left, sinPart, wx, dx, right, bottom, cosPart, dy, centerX, centerY;
        double width = __fabs(d->width * d->scaleX);
        double height = __fabs(d->height * d->scaleY);
        w = width;
        h = height;
        float zero = lbl_806DA718;
        if (zero == d->angle) {
            dx = zero;
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
        centerX = d->x;
        centerY = d->y;
        left = centerX - dx;
        top = centerY - dy;
        right = centerX + dx;
        bottom = centerY + dy;
        x0 = wx + left;
        y0 = top - sinPart;
        x1 = wx + right;
        y1 = bottom - sinPart;
        x2 = right - wx;
        y2 = sinPart + bottom;
        x3 = left - wx;
        y3 = sinPart + top;
    }
    ~DrawQuadLocal8214() {}
};

#endif
