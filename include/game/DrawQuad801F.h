#ifndef DRAW_QUAD_801F_H
#define DRAW_QUAD_801F_H
extern "C" {
void GXBegin(int, int, unsigned short);
extern const float lbl_806DA714;
extern const float lbl_806DA718;
extern const float lbl_806DA734;
}
struct DrawDesc801F {
    float x,y,anchorX,anchorY,z;
    int i14;
    unsigned short h18,h1A;
    float u0,v1,u1,v0;
    int i2C;
    float width,height,angle,scaleX,scaleY;
    unsigned int colors[4];
};
struct DrawNode801F {
    void *vtable;
    DrawDesc801F *description;
    unsigned char depth;
    unsigned char pad[3];
    int mode;
};
struct DrawQuad801F {
    float x0,y0,x1,y1,x2,y2,x3,y3;
    DrawQuad801F(DrawDesc801F *d) {
        float w = (float)__fabs(d->width * d->scaleX);
        float h = (float)__fabs(d->height * d->scaleY);
        float sinPart, cosPart;
        float dx, dy;
        if (lbl_806DA718 == d->angle) {
            sinPart = lbl_806DA718;
            dx = lbl_806DA718;
            cosPart = lbl_806DA734;
        } else {
            float s = lbl_806DA714 * d->anchorX;
            cosPart = lbl_806DA714 * d->anchorY;
            sinPart = w * s;
            dx = h * s;
        }
        dy = h * cosPart;
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
    ~DrawQuad801F() {}
};
static inline void DrawPosition801F(float x, float y) {
    *(volatile float *)0xCC008000 = x;
    *(volatile float *)0xCC008000 = y;
}
static inline void DrawPositionDepth801F(float x, float y, float z) {
    *(volatile float *)0xCC008000 = x;
    *(volatile float *)0xCC008000 = y;
    *(volatile float *)0xCC008000 = z;
}
static inline void DrawUV801F(float u, float v) {
    *(volatile float *)0xCC008000 = u;
    *(volatile float *)0xCC008000 = v;
}
static inline void DrawColor801F(unsigned int color) {
    *(volatile unsigned int *)0xCC008000 = color;
}
#endif
