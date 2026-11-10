#include "game/SpriteAnimTraversal_private.h"

static inline float SpriteAnim_Cos(float angle) { return (float)cos(angle); }

static inline float SpriteAnim_Sin(float angle) { return (float)sin(angle); }

static inline float SpriteAnim_RotateX(float x, float y, float angle) {
    float c = SpriteAnim_Cos(angle);
    float sn = SpriteAnim_Sin(angle);
    return x * c - y * sn;
}

static inline float SpriteAnim_RotateY(float x, float y, float angle) {
    float c = SpriteAnim_Cos(angle);
    float sn = SpriteAnim_Sin(angle);
    return x * sn + y * c;
}

static inline double SpriteAnim_Magnitude(float scale) { return __fabs(scale); }

static inline float SpriteAnim_ScaleTranslate(float value, float scale, float translation) {
    double magnitude = SpriteAnim_Magnitude(scale);
    return value * (float)magnitude + translation;
}

static inline void SpriteAnim_InitLayers(int *ids, int *sorted) {
    int i;
    for (i = 0; i < 120; i++) { ids[i] = -1; sorted[i] = -1; }
}

unsigned char fn_8019F5BC(SpriteAnim *s, SpriteAnimFrame *frames,
                             int r, int g, int b, int a, int wanted, SpriteAnimSample *out,
                             float x, float y, float sx, float sy, float angle, float alpha) {
    int sorted[120], ids[120];
    int *nextId;
    int count = 0, i, j, rank;
    SpriteAnimFrame *scan;
    short red, green, blue, opacity;
    SpriteAnim_InitLayers(ids, sorted);
    nextId = &ids[count]; /* not `ids`: target copies the CSE-d ids address into nextId */
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
        px = SpriteAnim_ScaleTranslate(SpriteAnim_RotateX(frames[last].x, frames[last].y, angle), sx, x);
        py = SpriteAnim_ScaleTranslate(SpriteAnim_RotateY(frames[last].x, frames[last].y, angle), sy, y);
        scaleX = sx * frames[last].scaleX; scaleY = sy * frames[last].scaleY;
        rotation = angle + frames[last].rotation;
        newAlpha = alpha * frames[last].alpha;
        rr = red + frames[last].redOffset; gg = green + frames[last].greenOffset;
        bb = blue + frames[last].blueOffset; aa = opacity + frames[last].alphaOffset;
        if (resource != -1) {
            if ((short)wanted != s->data->resources[frames[resource].resource]) continue;
            out->x = px; out->y = py; out->scaleX = scaleX; out->scaleY = scaleY;
            out->red = frames[last].red; out->green = frames[last].green; out->blue = frames[last].blue;
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
