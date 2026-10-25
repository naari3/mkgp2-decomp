/* NokoNoko_FindNearest (0x801887BC): nearest live NokoNoko (state < 4) to a point. */

typedef struct { float x, y, z; } Vec;
typedef struct NokoNoko {
    struct NokoNoko *next;
    char pad04[0x8];
    int state;
    char pad10[0xC];
    Vec pos;
} NokoNoko;

extern NokoNoko *g_nokonokoHead;
extern void Vec3_Subtract(const Vec *a, const Vec *b, Vec *out);
extern float PSVECSquareMag(const Vec *v);

#pragma exceptions on
int NokoNoko_FindNearest(const Vec *pos, Vec *out) {
    NokoNoko *best;
    NokoNoko *n;
    float bestDist;
    float d;
    Vec diff;

    if (pos == 0 || out == 0) {
        return 0;
    }
    best = 0;
    for (n = g_nokonokoHead; n != 0; n = n->next) {
        if (n->state < 4) {
            Vec3_Subtract(pos, &n->pos, &diff);
            if (best == 0) {
                best = n;
                bestDist = PSVECSquareMag(&diff);
            } else {
                d = PSVECSquareMag(&diff);
                if (d < bestDist) {
                    best = n;
                    bestDist = d;
                }
            }
        }
    }
    if (best != 0) {
        out->x = best->pos.x;
        out->y = best->pos.y;
        out->z = best->pos.z;
        return 1;
    }
    return 0;
}
#pragma exceptions reset
