#include "game/SpriteAnimTraversal_private.h"

extern void fn_801A1174(int, void *, short, short, short);
extern void fn_801A109C(float *);
extern void fn_801A0FD4(float, float, float, float);
extern void fn_801A0E54(int, int, int, int);
extern void fn_801A0DF0(void);

static inline void SpriteAnim_DrawResources(SpriteAnim *s, SpriteAnimFrame *draw,
    float *composed, short rr, short gg, short bb, short aa,
    float cr, float cg, float cb, float newAlpha) {
    int j;
    int n = draw->count;
    int first = draw->resource;
    for (j = 0; j < n; j++) {
        fn_801A1174(s->data->resources[first + j], s->resourceContext, rr, gg, bb);
        fn_801A109C(composed);
        fn_801A0FD4(cr, cg, cb, newAlpha);
        fn_801A0E54(rr, gg, bb, aa);
        fn_801A0DF0();
    }
}

void fn_8019FA30(SpriteAnim *s, SpriteAnimFrame *frames, float *matrix,
                   int r, int g, int b, int a, float alpha) {
    int sorted[120], ids[120];
    int *nextId;
    int count = 0, i, j, rank;
    int layerIndex;
    SpriteAnimFrame *scan;
    short red, green, blue, opacity;
    for (i = 0; i < 120; i++) { ids[i] = -1; sorted[i] = -1; }
    nextId = ids;
    for (scan = frames;; scan++) {
        for (i = 0; i < count; i++) { if (ids[i] == scan->layer) break; }
        if (i == count) { *nextId++ = scan->layer; count++; }
        if (scan->flags & 1) break;
        if (count >= 120) return;
    }
    for (i = 0; i < count; i++) {
        rank = 0;
        for (j = 0; j < count; j++) { if (ids[j] < ids[i]) rank++; }
        sorted[rank] = ids[i];
    }
    red = r; green = g; blue = b; opacity = a;
    for (layerIndex = 0; layerIndex < count; layerIndex++) {
        SpriteAnimFrame *f;
        int resource = -1, child = -1, last = 0, index = 0;
        float composed[6];
        float newAlpha;
        short rr, gg, bb;
        int aa;
        for (f = frames;; f++, index++) {
            if (f->layer == sorted[layerIndex]) {
                if (f->time > s->time) break;
                if (f->flags & 2) { resource = -1; child = -1; }
                if (f->resource != -1) { resource = index; child = -1; }
                if (f->child != 0) { resource = -1; child = index; }
                last = index;
            }
            if (f->flags & 1) break;
        }
        if (resource == -1 && child == -1) continue;
        f = &frames[last];
        SpriteAnim_Concat(composed, matrix, f->matrix);
        newAlpha = alpha * f->alpha;
        rr = red + f->redOffset; gg = green + f->greenOffset;
        bb = blue + f->blueOffset; aa = (short)(opacity + f->alphaOffset);
        if (resource != -1) {
            SpriteAnim_DrawResources(s, &frames[resource], composed, rr, gg, bb, aa,
                                     f->red, f->green, f->blue, newAlpha);
        } else {
            fn_8019FA30(s, frames[child].child, composed, rr, gg, bb, aa, newAlpha);
        }
    }
}
