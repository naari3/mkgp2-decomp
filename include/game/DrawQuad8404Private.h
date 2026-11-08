#ifndef DRAW_QUAD_8404_PRIVATE_H
#define DRAW_QUAD_8404_PRIVATE_H
#include "game/DrawQuad801F.h"

struct DrawQuad8404 {
    float x0,y0,x1,y1,x2,y2,x3,y3;
    DrawQuad8404(DrawDesc801F *d) {
        float w, h, top, left, sinPart, wx, dx, right, bottom, cosPart, dy, centerX, centerY;
        w = d->width * d->scaleX;
        h = d->height * d->scaleY;
        double height = __fabs(h);
        double width = __fabs(w);
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
    ~DrawQuad8404() {}
};
#endif
