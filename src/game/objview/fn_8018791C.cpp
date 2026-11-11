/* clMRPukupuku, 0x8018791C..0x80187D2C. Deferred emission reverses
 * these out-of-line definitions. The compiler owns the vtable and RTTI. */
#include "game/types/clMRPukupuku.h"
#include "game/types/Path.h"
#include "game/types/size_t.h"
void *operator new(size_t);
void operator delete(void *);
extern "C" {
void DebugPrintf(const char *, ...);
void *FUN_8003b120(unsigned long);
void Object_DtorWithGXSync(void *, int);
void MemoryManager_Free(void *);
unsigned char fn_801379F0(Vec3 *, float);
void Object_SetJObjPositionVec(void *, Vec3 *);
void Object_SetJObjRotationX(void *, float);
void Object_SetJObjRotationY(void *, float);
void Object_SetJObjRotationZ(void *, float);
void Object_RenderJObjTree(void *, int);
void fn_80181F18(const Vec3 *, const Vec3 *, const Vec3 *, Vec3 *, float);
double atan2(double, double);
float LookupSin(float);
extern const float lbl_806D92F0;
extern const float lbl_806D92F4;
extern const float lbl_806D92F8;
extern const float lbl_806D92FC;
extern const float lbl_806D9300;
extern const float lbl_806D9304;
extern const float lbl_806D9308;
extern const float lbl_806D930C;
extern const float lbl_806D9310;
}

extern const Path lbl_80377368[3] = {
    { { 340.1803f, -408.622f, -3607.14f }, { 105.9669f, 12.6597f, -4003.29f }, { -79.0158f, -389.73f, -4383.93f } },
    { { 354.5148f, -408.463f, -4526.88f }, { 403.1689f, -49.6883f, -4071.17f }, { 442.1717f, -392.301f, -3610.22f } },
    { { 620.166f, -408.762f, -4532.42f }, { 723.8622f, -74.7206f, -4075.58f }, { 808.1324f, -393.497f, -3685.97f } }
};

clMRPukupuku::clMRPukupuku() {
    int i;
    DebugPrintf(" CreateMapEffect : clMRPukupuku\n");
    model = 0;
    slots = 0;
    model = new clNormal3D("MRA_puku.dat", 0);
    if (model == 0) return;
    slots = (PukupukuPlacement *)FUN_8003b120(0x60);
    if (slots == 0) return;
    for (i = 0; i < 3; i++) {
        slots[i].pos.x = lbl_806D92F4;
        slots[i].pos.y = lbl_806D92F4;
        slots[i].pos.z = lbl_806D92F4;
        slots[i].bob = lbl_806D92F4;
        slots[i].yaw = lbl_806D92F4;
        slots[i].roll = lbl_806D92F4;
        slots[i].t = lbl_806D92F4;
        slots[i].timer = 0;
    }
}

clMRPukupuku::~clMRPukupuku() {
    if (model != 0) Object_DtorWithGXSync(model, 1);
    if (slots != 0) MemoryManager_Free(slots);
    DebugPrintf(" DeleteMapEffect : clMRPukupuku\n");
}

static inline void Vec3Copy(Vec3 *d, const Vec3 *s) {
    d->x = s->x;
    d->y = s->y;
    d->z = s->z;
}

void clMRPukupuku::Update() {
    int i;
    PukupukuPlacement *s;
    float ox, oz;
    if (slots == 0) return;
    for (i = 0; i < 3; i++) {
        s = &slots[i];
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

void clMRPukupuku::Draw() {
    int i;
    PukupukuPlacement *p;
    if (slots == 0) {
        return;
    }
    for (i = 0; i < 3; i++) {
        p = &slots[i];
        if (p->timer == 0 && fn_801379F0(&p->pos, lbl_806D92F0)) {
            Object_SetJObjPositionVec(model, &p->pos);
            Object_SetJObjRotationX(model, p->bob);
            Object_SetJObjRotationY(model, p->yaw);
            Object_SetJObjRotationZ(model, p->roll);
            Object_RenderJObjTree(model, 7);
        }
    }
}

#pragma readonly_strings on
