/* NokoNoko_InitEntity (0x801884E8): places a NokoNoko at `pos`, picks its
 * kind from the shared random table and faces it along the nearest path
 * segment. */

typedef struct { float x, y, z; } Vec;

typedef struct NokoKind {
    int model;
    int anim;
    int extra;
    float speed;
    float radius;
} NokoKind;

typedef struct NokoNoko {
    struct NokoNoko *next;
    int kindTable;
    int kindIndex;
    int model;
    int anim;
    float frame;
    int extra;
    Vec pos;
    float yaw;
    float speed;
    float radius;
    int model2;
    float blend;
    float frame2;
} NokoNoko;

extern int lbl_806D1684;
extern const float lbl_806D9324;
extern const float lbl_806D9350;
extern float lbl_80495994[];
extern NokoKind *lbl_80495D28[];
extern Vec lbl_80377450[];
extern void Vec3_Subtract(Vec *a, Vec *b, Vec *out);
extern float PSVECSquareMag(Vec *v);
extern void Vec3_Normalize(Vec *src, Vec *dst);
extern float Vec3_Dot(Vec *a, Vec *b);
extern double atan2(double y, double x);
extern unsigned char Terrain_GetGroundHeight(Vec *pos, float *height, int a, int b);

#pragma exceptions on
NokoNoko *NokoNoko_InitEntity(NokoNoko *self, Vec *pos) {
    Vec d;
    Vec rel;
    Vec nearest;
    float h;
    unsigned int i;
    unsigned int best;
    unsigned int next;
    float bestDist;
    float dist;
    float t;

    self->next = 0;
    self->pos.x = pos->x;
    self->pos.y = pos->y;
    self->pos.z = pos->z;
    self->model2 = -1;
    self->blend = lbl_806D9324;
    self->frame2 = lbl_806D9324;
    if (lbl_806D1684 >= 0x40) {
        lbl_806D1684 = 0;
    }
    {
        float r = lbl_80495994[lbl_806D1684++];
        self->kindTable = lbl_806D9350 * r;
    }
    self->kindIndex = 0;
    self->model = lbl_80495D28[self->kindTable][self->kindIndex].model;
    self->anim = lbl_80495D28[self->kindTable][self->kindIndex].anim;
    self->extra = lbl_80495D28[self->kindTable][self->kindIndex].extra;
    self->speed = lbl_80495D28[self->kindTable][self->kindIndex].speed;
    self->radius = lbl_80495D28[self->kindTable][self->kindIndex].radius;
    self->frame = lbl_806D9324;
    for (i = 0; i < 21; i++) {
        Vec3_Subtract(lbl_80377450, &self->pos, &d);
        dist = PSVECSquareMag(&d);
        if ((int)i == 0 || dist < bestDist) {
            best = i;
            bestDist = dist;
        }
    }
    nearest.x = lbl_80377450[best].x;
    nearest.y = lbl_80377450[best].y;
    nearest.z = lbl_80377450[best].z;
    next = best + 1;
    if (next == 21) {
        next = 0;
    }
    Vec3_Subtract(&lbl_80377450[next], &lbl_80377450[best], &d);
    Vec3_Normalize(&d, &d);
    Vec3_Subtract(&self->pos, &nearest, &rel);
    t = Vec3_Dot(&rel, &d);
    nearest.x = d.x * t + nearest.x;
    nearest.y = d.y * t + nearest.y;
    nearest.z = d.z * t + nearest.z;
    rel.x = nearest.x - self->pos.x;
    rel.y = lbl_806D9324;
    rel.z = nearest.z - self->pos.z;
    Vec3_Normalize(&rel, &rel);
    self->yaw = atan2(rel.x, rel.z);
    if (Terrain_GetGroundHeight(&self->pos, &h, 0, 0)) {
        self->pos.y = h;
    }
    return self;
}
#pragma exceptions reset
