typedef struct { float x, y, z; } Vec3;

typedef struct Slot {
    Vec3 pos;
    float bob;
    float yaw;
    float pad14;
    float t;
    int timer;
} Slot;

typedef struct Path {
    Vec3 p0;
    Vec3 p1;
    Vec3 p2;
} Path;

typedef struct Obj801879E4 {
    void *vt;
    void *model;
    Slot *slots;
} Obj801879E4;

extern const Path lbl_80377368[3];
extern const float lbl_806D92F4;
extern const float lbl_806D92F8;
extern const float lbl_806D92FC;
extern const float lbl_806D9300;
extern const float lbl_806D9304;
extern const float lbl_806D9308;
extern const float lbl_806D930C;
extern const float lbl_806D9310;
extern void fn_80181F18(const Vec3 *p0, const Vec3 *p1, const Vec3 *p2, Vec3 *out, float t);
extern double atan2(double y, double x);
extern float LookupSin(float x);

static inline void Vec3Copy(Vec3 *d, const Vec3 *s) {
    d->x = s->x;
    d->y = s->y;
    d->z = s->z;
}

void fn_801879E4(Obj801879E4 *o) {
    int i;
    Slot *s;
    float ox, oz;
    if (o->slots == 0) return;
    for (i = 0; i < 3; i++) {
        s = &o->slots[i];
        if (s->timer > 0 && --s->timer == 0) {
            s->t = lbl_806D92F4;
            Vec3Copy(&s->pos, &lbl_80377368[i].p0);
        }
        if (s->timer == 0) {
            s->t += lbl_806D92F8;
            ox = s->pos.x;
            oz = s->pos.z;
            fn_80181F18(&lbl_80377368[i].p0, &lbl_80377368[i].p1, &lbl_80377368[i].p2, &s->pos, s->t);
            s->yaw = atan2(s->pos.x - ox, s->pos.z - oz);
            s->bob = lbl_806D92FC * LookupSin(lbl_806D9300 * s->t) - lbl_806D9300;
            s->yaw = lbl_806D9304 * LookupSin(lbl_806D9308 * (lbl_806D930C * s->t)) + s->yaw;
            if (s->t > lbl_806D9310) s->timer = 0x3c;
        }
    }
}
