/* NokoNoko_CheckHitAndKill (0x801888B8): knocks out every NokoNoko inside the given
 * sphere; returns 1 if any was hit. */

typedef struct { float x, y, z; } Vec;
typedef struct NokoNoko {
    struct NokoNoko *next;
    char pad04[0x8];
    int state;
    int model;
    float frame;
    char pad18[0x4];
    Vec pos;
    float yaw;
    float x2C;
    float x30;
    int model2;
    float blend;
    float frame2;
} NokoNoko;

extern unsigned char g_nokonokoEnable;
extern NokoNoko *g_nokonokoHead;
extern Vec lbl_80677ED8;
extern float lbl_806D168C;
extern const float lbl_806D9324;
extern const float lbl_806D933C;
extern const float lbl_806D934C;
extern float Vec3_Magnitude(Vec *v);
extern void Vec3_Normalize(Vec *src, Vec *dst);
extern double atan2(double, double);
extern void SoundMgr_PlaySE(int id);
extern void DrawEffect_SpawnWithDescriptor(int kind, Vec pos);

static inline unsigned char NokoNoko_TryHit(NokoNoko *n, Vec *pos, float r, Vec *out) {
    Vec d;

    if (n->state >= 4) {
        return 0;
    }
    d.x = pos->x - n->pos.x;
    d.y = pos->y - (lbl_806D933C + n->pos.y);
    d.z = pos->z - n->pos.z;
    if (Vec3_Magnitude(&d) < r) {
        Vec3_Normalize(&d, &d);
        n->pos.x = pos->x - d.x * r;
        n->pos.y = pos->y - d.y * r;
        n->pos.z = pos->z - d.z * r;
        n->yaw = atan2(d.x, d.z);
        SoundMgr_PlaySE(0xCB);
        d.x = n->pos.x;
        d.y = n->pos.y;
        d.z = n->pos.z;
        d.y += lbl_806D934C;
        DrawEffect_SpawnWithDescriptor(2, d);
        n->state = 4;
        n->model = 3;
        n->frame = lbl_806D9324;
        n->x2C = lbl_806D9324;
        n->x30 = lbl_806D9324;
        n->model2 = n->model;
        n->blend = lbl_806D9324;
        n->frame2 = n->frame;
        if (out != 0) {
            out->x = d.x;
            out->y = d.y;
            out->z = d.z;
        }
        return 1;
    }
    return 0;
}

#pragma exceptions on
int NokoNoko_CheckHitAndKill(Vec *pos, Vec *out, float radius) {
    int hit;
    NokoNoko *n;
    float r;

    if (g_nokonokoEnable == 0 || pos == 0 || radius <= lbl_806D9324) {
        return; /* sic: original returns whatever is in r3 */
    }
    hit = 0;
    lbl_80677ED8.x = pos->x;
    lbl_80677ED8.y = pos->y;
    lbl_80677ED8.z = pos->z;
    r = lbl_806D933C + radius;
    lbl_806D168C = radius;
    for (n = g_nokonokoHead; n != 0; n = n->next) {
        if (NokoNoko_TryHit(n, pos, r, out) == 1) {
            hit = 1;
        }
    }
    return hit;
}
#pragma exceptions reset
