#include "game/SpriteAnimTraversal_private.h"

unsigned char fn_8019F5BC(SpriteAnim *s, SpriteAnimFrame *frames,
                             int r, int g, int b, int a, int wanted, SpriteAnimSample *out,
                             float x, float y, float sx, float sy, float angle, float alpha) {
    int ids[120], sorted[120];
    int count = 0, i, j, rank;
    SpriteAnimFrame *scan;
    short red, green, blue, opacity;
    for (i = 0; i < 120; i++) { ids[i] = -1; sorted[i] = -1; }
    for (scan = frames;; scan++) {
        for (i = 0; i < count; i++) { if (ids[i] == scan->layer) break; }
        if (i == count) ids[count++] = scan->layer;
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
        {
            float fx = f->x, fy = f->y;
            float c = (float)cos(angle);
            float sn = (float)sin(angle);
            float fx2 = f->x, fy2 = f->y;
            px = (fx * c - fy * sn) * (float)__fabs(sx) + x;
            c = (float)cos(angle);
            sn = (float)sin(angle);
            py = (fx2 * sn + fy2 * c) * (float)__fabs(sy) + y;
        }
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
