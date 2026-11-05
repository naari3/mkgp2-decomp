#ifndef SPRITE_ANIM_TRAVERSAL_PRIVATE_H
#define SPRITE_ANIM_TRAVERSAL_PRIVATE_H

/* Private views of the animation records consumed by the traversal routines. */
typedef struct SpriteAnimFrame {
    unsigned char flags;
    signed char layer;
    signed char count;
    unsigned char reserved3;
    short resource;
    short reserved6;
    struct SpriteAnimFrame *child;
    float time;
    float x, y, scaleX, scaleY, rotation;
    float red, green, blue, alpha;
    short redOffset, greenOffset, blueOffset, alphaOffset;
    float matrix[6];
} SpriteAnimFrame;

typedef struct SpriteAnimData {
    unsigned char reserved[0x14];
    float length;
    SpriteAnimFrame *frames;
    short *resources;
} SpriteAnimData;

typedef struct SpriteAnim {
    unsigned char flags;
    unsigned char reserved1[3];
    void *resourceContext;
    float time;
    float x, y, scaleX, scaleY, rotation, alpha;
    const char *name;
    SpriteAnimData *data;
} SpriteAnim;

typedef struct SpriteAnimSample {
    float x, y, scaleX, scaleY, rotation;
    float red, green, blue, alpha;
    short redOffset, greenOffset, blueOffset, alphaOffset;
} SpriteAnimSample;

extern double cos(double);
extern double sin(double);
extern float lbl_806D97D8;
extern float lbl_806D97DC;
extern unsigned char fn_8019F5BC(SpriteAnim *, SpriteAnimFrame *, int, int, int, int, int, SpriteAnimSample *, float, float, float, float, float, float);
extern void fn_8019FA30(SpriteAnim *, SpriteAnimFrame *, float *, int, int, int, int, float);

/* Compose two affine 2D transforms, permitting the output to alias either input. */
static inline void SpriteAnim_Concat(float *out, const float *a, const float *b) {
    float t[6];
    int i;
    t[0] = a[0] * b[0] + a[1] * b[3];
    t[1] = a[0] * b[1] + a[1] * b[4];
    t[2] = a[2] + (a[0] * b[2] + a[1] * b[5]);
    t[3] = a[3] * b[0] + a[4] * b[3];
    t[4] = a[3] * b[1] + a[4] * b[4];
    t[5] = a[5] + (a[3] * b[2] + a[4] * b[5]);
    for (i = 0; i < 6; i++) out[i] = t[i];
}

#endif
