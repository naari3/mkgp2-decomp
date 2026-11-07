#ifndef DRAW_QUAD_8728_PRIVATE_H
#define DRAW_QUAD_8728_PRIVATE_H
#include "game/DrawQuad801F.h"
struct DrawQuad8728 {
    float x0,y0,x1,y1,x2,y2,x3,y3;
    DrawQuad8728(DrawDesc801F *d) {
        double width = __fabs(d->width * d->scaleX);
        double height = __fabs(d->height * d->scaleY);
        SetCorners(d, width, height);
    }
    void SetCorners(DrawDesc801F *d, float w, float h) {
        float sinPart, dx, dy, wx;
        Project(d, w, h, sinPart, dx, dy, wx);
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
    static inline void Project(DrawDesc801F *d, float w, float h,
                               float &sinPart, float &dx, float &dy, float &wx) {
        float cosine;
        if (lbl_806DA718 == d->angle) {
            dx = lbl_806DA718;
            sinPart = dx;
            cosine = lbl_806DA734;
        } else {
            float sine = lbl_806DA714 * d->anchorX;
            cosine = lbl_806DA714 * d->anchorY;
            sinPart = w * sine;
            dx = h * sine;
        }
        dy = h * cosine;
        wx = w * cosine;
    }
    ~DrawQuad8728() {}
};
#endif
