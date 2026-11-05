#include "game/SpriteAnimTraversal_private.h"

static inline float SpriteAnim_RotateX(float x, float y, float angle) {
    float c = (float)cos(angle);
    float sn = (float)sin(angle);
    return x * c - y * sn;
}

static inline float SpriteAnim_RotateY(float x, float y, float angle) {
    float c = (float)cos(angle);
    float sn = (float)sin(angle);
    return x * sn + y * c;
}

unsigned char fn_8019F5BC(SpriteAnim *s, SpriteAnimFrame *frames,
                             int r, int g, int b, int a, int wanted, SpriteAnimSample *out,
                             float x, float y, float sx, float sy, float angle, float alpha) {
    int sorted[120], ids[120];
    int *nextId = ids;
    int count = 0, i, j, rank;
    SpriteAnimFrame *scan;
    short red, green, blue, opacity;
    for (i = 0; i < 120; i++) { ids[i] = -1; sorted[i] = -1; }
    for (scan = frames;; scan++) {
        for (i = 0; i < count; i++) { if (ids[i] == scan->layer) break; }
        if (i == count) { *nextId++ = scan->layer; count++; }
        if (scan->flags & 1) break;
        if (count >= 120) return 0;
    }
    for (i = 0; i < count; i++) {
        rank = 0;
        for (j = 0; j < count; j++) { if (ids[j] < ids[i]) rank++; }
        sorted[rank] = ids[i];
    }
    red = r; green = g; blue = b; opacity = a;
    for (i = 0; i < count; i++) {
        SpriteAnimFrame *f;
        int resource = -1, child = -1, last = 0, index = 0;
        float px, py, scaleX, scaleY, rotation, newAlpha;
        short rr, gg, bb, aa;
        for (f = frames;; f++, index++) {
            if (f->layer == sorted[i]) {
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
        px = SpriteAnim_RotateX(f->x, f->y, angle) * (float)__fabs(sx) + x;
        py = SpriteAnim_RotateY(f->x, f->y, angle) * (float)__fabs(sy) + y;
        scaleX = sx * f->scaleX; scaleY = sy * f->scaleY;
        rotation = angle + f->rotation;
        newAlpha = alpha * f->alpha;
        rr = red + f->redOffset; gg = green + f->greenOffset;
        bb = blue + f->blueOffset; aa = opacity + f->alphaOffset;
        if (resource != -1) {
            if ((short)wanted != s->data->resources[frames[resource].resource]) continue;
            out->x = px; out->y = py; out->scaleX = scaleX; out->scaleY = scaleY;
            out->red = f->red; out->green = f->green; out->blue = f->blue;
            out->alpha = newAlpha; out->rotation = rotation;
            out->redOffset = rr; out->greenOffset = gg;
            out->blueOffset = bb; out->alphaOffset = aa;
            return 1;
        } else if (fn_8019F5BC(s, frames[child].child, rr, gg, bb, aa, wanted, out,
                               px, py, scaleX, scaleY, rotation, newAlpha)) {
            return 1;
        }
    }
    return 0;
}
