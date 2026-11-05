/*
 * 0x801375D8..0x80139898: course object culling, activation and the per-frame update.
 */
#pragma cplusplus on

struct Vec3f {
    float x, y, z;
};
struct OccluderShape {
    Vec3f pts[4];
    float zmax;
    float planes[5][4];
};
struct Occluder {
    Occluder *next;
    Occluder *activeNext;
    OccluderShape shape;
    Vec3f center;
    float radius;

    inline Occluder(const Vec3f *a, const Vec3f *b, const Vec3f *c, const Vec3f *d);
};
struct PObj {
    char pad0[4];
    PObj *next;
};
struct DObj {
    char pad0[4];
    DObj *next;
    char pad8[4];
    PObj *pobj;
};
struct JObj {
    char pad0[8];
    JObj *next;
    JObj *parent;
    JObj *child;
};
struct CourseObj {
    char pad0[4];
    float x, y, z;
    char pad10[8];
    int state;
    float f1C;
    float px, py, pz;
    char pad2C[4];
    float f30;
    float f34;
    char pad38[0xc0 - 0x38];
};

/* TOP-END */

extern "C" {
extern float (*lbl_806D1518)[4];
extern float *lbl_806D151C;
extern Vec3f lbl_80677CB8;
extern Occluder *lbl_806D1524;
extern Occluder *lbl_806D1520;
void PSMTXMultVec(const float (*m)[4], const Vec3f *src, Vec3f *dst);
void PSVECCrossProduct(const Vec3f *a, const Vec3f *b, Vec3f *axb);
void Vec3_Normalize(const Vec3f *src, Vec3f *dst);
extern unsigned int lbl_806D73E0;
void MemoryManager_TimedFree(void *p);

DObj *HSD_JObjGetDObj(JObj *jobj);
unsigned int HSD_JObjGetFlags(JObj *jobj);
unsigned char fn_80185FE8(JObj *jobj, PObj *pobj, Vec3f *a, Vec3f *b, Vec3f *c, Vec3f *d);
double tan(double);
extern unsigned int lbl_806D73E4;
float Vec3_Magnitude(const Vec3f *v);
void Vec3_Subtract(const Vec3f *a, const Vec3f *b, Vec3f *out);
extern struct CourseObj *lbl_806D1534;
extern int lbl_806D1538;
extern const float lbl_806D73E8;
extern const float lbl_806D73EC;
extern void Archive_GetRootJObj();
extern void GXChannel_Init();
extern void GXChannel_PushTransform();
extern void LinkedNode_GetField10_OrFallback();
extern void Mtx4x4_TransposeTo4x3();
extern void Object_SetColorAlphaOnly();
extern void PSVECAdd();
extern void cos();
extern void dtor_8007D9C4();
extern void sin();
extern unsigned int lbl_806D1528;
extern unsigned int lbl_806D152C;
extern unsigned int lbl_806D1530;
extern unsigned int lbl_806D73F0;
extern unsigned int lbl_806D73F4;
extern unsigned int lbl_806D73F8;
extern unsigned int lbl_806D73FC;
extern unsigned int lbl_806D7400;
unsigned long OSGetTick(void);
void Profiler_RecordFrame(int id, float ms);
extern const float lbl_806D7404;
extern unsigned int lbl_806D7408;
extern void __dt__11ScopedTimerFv();
unsigned char fn_801375D8(const Vec3f *p, float r);
unsigned char fn_80137718(const Vec3f *p, Vec3f *out, float r);
unsigned char fn_801379F0(const Vec3f *p, float r);
void fn_80137C8C(float (*m)[4], float *frustum);
unsigned char fn_80137E50(OccluderShape *s);
void fn_80138578(void);
void fn_801385CC(JObj *jobj);
void fn_8013879C(float *frustum, float fovy, float aspect, float zfar, float znear);
Occluder *fn_80138A50(Occluder *o, const Vec3f *a, const Vec3f *b, const Vec3f *c, const Vec3f *d);
void CourseObjects_Activate(void);
void fn_80138D48(void);
asm void fn_80138DB8(void);
void fn_80139810(void);

#pragma section R ".extab_user"

__declspec(section ".extab_user") static const unsigned char extab_fn_80138A50[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; void *f11; unsigned int f12; void *f13; unsigned int f14; void *f15; unsigned int f16; void *f17; } extab_fn_80138DB8 = { 0x408A0000, 0x000004B8, 0x00030028, 0x00000554, 0x00030030, 0x00000614, 0x00030038, 0x000006CC, 0x00CC0040, 0x00000000, 0x8200005C, (void *)&dtor_8007D9C4, 0x82000048, (void *)&dtor_8007D9C4, 0x82000034, (void *)&dtor_8007D9C4, 0x82000020, (void *)&dtor_8007D9C4 };


#pragma section R ".extabindex_user"

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80138A50 = {
    (void *)&fn_80138A50, 0x00000294, (void *)extab_fn_80138A50
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80138DB8 = {
    (void *)&fn_80138DB8, 0x00000A58, (void *)&extab_fn_80138DB8
};


}

class ScopedTimer {
public:
    inline ScopedTimer(int slot) {
        m_slot = slot;
        m_startTick = OSGetTick();
    }
    inline ~ScopedTimer() {
        Profiler_RecordFrame(m_slot,
            (float)(((OSGetTick() - m_startTick) * 8) /
                ((*(unsigned int *)0x800000F8 / 4) / 125000)) / lbl_806D7404);
    }

private:
    unsigned int m_startTick;
    volatile int m_slot;
};




static inline unsigned char SphereInViewFrustum(const Vec3f *p, Vec3f *v, float r)
{
    v->z = lbl_806D1518[2][0] * p->x + lbl_806D1518[2][1] * p->y + lbl_806D1518[2][2] * p->z + lbl_806D1518[2][3];
    if (v->z - r > lbl_806D151C[16]) {
        return 0;
    }
    if (v->z + r < lbl_806D151C[17]) {
        return 0;
    }
    v->x = lbl_806D1518[0][0] * p->x + lbl_806D1518[0][1] * p->y + lbl_806D1518[0][2] * p->z + lbl_806D1518[0][3];
    if (v->x * lbl_806D151C[0] + v->z * lbl_806D151C[2] > r) {
        return 0;
    }
    if (v->x * lbl_806D151C[4] + v->z * lbl_806D151C[6] > r) {
        return 0;
    }
    v->y = lbl_806D1518[1][0] * p->x + lbl_806D1518[1][1] * p->y + lbl_806D1518[1][2] * p->z + lbl_806D1518[1][3];
    if (v->y * lbl_806D151C[9] + v->z * lbl_806D151C[10] > r) {
        return 0;
    }
    if (v->y * lbl_806D151C[13] + v->z * lbl_806D151C[14] > r) {
        return 0;
    }
    return 1;
}

static inline unsigned char SphereNotOccluded(const Occluder *o, const Vec3f *v, float r)
{
    if (o->shape.zmax < v->z + r) {
        return 1;
    }
    if (v->x * o->shape.planes[0][0] + v->y * o->shape.planes[0][1] + v->z * o->shape.planes[0][2] + o->shape.planes[0][3] > -r) {
        return 1;
    }
    if (v->x * o->shape.planes[1][0] + v->y * o->shape.planes[1][1] + v->z * o->shape.planes[1][2] + o->shape.planes[1][3] > -r) {
        return 1;
    }
    if (v->x * o->shape.planes[2][0] + v->y * o->shape.planes[2][1] + v->z * o->shape.planes[2][2] + o->shape.planes[2][3] > -r) {
        return 1;
    }
    if (v->x * o->shape.planes[3][0] + v->y * o->shape.planes[3][1] + v->z * o->shape.planes[3][2] + o->shape.planes[3][3] > -r) {
        return 1;
    }
    if (v->x * o->shape.planes[4][0] + v->y * o->shape.planes[4][1] + v->z * o->shape.planes[4][2] + o->shape.planes[4][3] > -r) {
        return 1;
    }
    return 0;
}

extern "C" asm unsigned char fn_801375D8(const Vec3f *p, float r) { /* 0x801375D8 size:0x140 */
    nofralloc
    lwz r5, lbl_806D1518(r13)
    lis r4, lbl_80677CB8@ha
    lfs f7, 0x4(r3)
    addi r4, r4, lbl_80677CB8@l
    lfs f0, 0x24(r5)
    lfs f3, 0x20(r5)
    fmuls f0, f0, f7
    lfs f8, 0x0(r3)
    lfs f4, 0x28(r5)
    lfs f2, 0x8(r3)
    fmadds f0, f3, f8, f0
    lfs f3, 0x2c(r5)
    lwz r3, lbl_806D151C(r13)
    fmadds f0, f4, f2, f0
    fadds f0, f3, f0
    stfs f0, 0x8(r4)
    fsubs f4, f0, f1
    lfs f3, 0x40(r3)
    fcmpo cr0, f4, f3
    ble fn_801375D8_L_80137630
    li r3, 0x0
    blr
    fn_801375D8_L_80137630:
    fadds f4, f0, f1
    lfs f3, 0x44(r3)
    fcmpo cr0, f4, f3
    bge fn_801375D8_L_80137648
    li r3, 0x0
    blr
    fn_801375D8_L_80137648:
    lfs f3, 0x4(r5)
    lfs f4, 0x0(r5)
    fmuls f3, f3, f7
    lfs f5, 0x8(r5)
    lfs f6, 0xc(r5)
    fmadds f3, f4, f8, f3
    fmadds f3, f5, f2, f3
    fadds f5, f6, f3
    stfs f5, 0x0(r4)
    lfs f3, 0x8(r3)
    lfs f4, 0x0(r3)
    fmuls f3, f0, f3
    fmadds f3, f5, f4, f3
    fcmpo cr0, f3, f1
    ble fn_801375D8_L_8013768C
    li r3, 0x0
    blr
    fn_801375D8_L_8013768C:
    lfs f3, 0x18(r3)
    lfs f4, 0x10(r3)
    fmuls f3, f0, f3
    fmadds f3, f5, f4, f3
    fcmpo cr0, f3, f1
    ble fn_801375D8_L_801376AC
    li r3, 0x0
    blr
    fn_801375D8_L_801376AC:
    lfs f3, 0x14(r5)
    lfs f4, 0x10(r5)
    fmuls f3, f3, f7
    lfs f5, 0x18(r5)
    lfs f6, 0x1c(r5)
    fmadds f3, f4, f8, f3
    fmadds f2, f5, f2, f3
    fadds f4, f6, f2
    stfs f4, 0x4(r4)
    lfs f2, 0x28(r3)
    lfs f3, 0x24(r3)
    fmuls f2, f0, f2
    fmadds f2, f4, f3, f2
    fcmpo cr0, f2, f1
    ble fn_801375D8_L_801376F0
    li r3, 0x0
    blr
    fn_801375D8_L_801376F0:
    lfs f2, 0x38(r3)
    lfs f3, 0x34(r3)
    fmuls f0, f0, f2
    fmadds f0, f4, f3, f0
    fcmpo cr0, f0, f1
    ble fn_801375D8_L_80137710
    li r3, 0x0
    blr
    fn_801375D8_L_80137710:
    li r3, 0x1
    blr
}

extern "C" unsigned char fn_80137718(const Vec3f *p, Vec3f *out, float r)
{
    if (out == 0) {
        out = &lbl_80677CB8;
    }
    if (!SphereInViewFrustum(p, out, r)) {
        return 0;
    }
    for (Occluder *o = lbl_806D1524; o != 0; o = o->activeNext) {
        if (!SphereNotOccluded(o, out, r)) {
            return 0;
        }
    }
    return 1;
}

extern "C" asm unsigned char fn_801379F0(const Vec3f *p, float r) { /* 0x801379F0 size:0x29C */
    nofralloc
    lwz r5, lbl_806D1518(r13)
    lis r4, lbl_80677CB8@ha
    lfs f7, 0x4(r3)
    addi r4, r4, lbl_80677CB8@l
    lfs f0, 0x24(r5)
    lfs f3, 0x20(r5)
    fmuls f0, f0, f7
    lfs f8, 0x0(r3)
    lfs f4, 0x28(r5)
    lfs f2, 0x8(r3)
    fmadds f0, f3, f8, f0
    lfs f3, 0x2c(r5)
    lwz r3, lbl_806D151C(r13)
    fmadds f0, f4, f2, f0
    fadds f0, f3, f0
    stfs f0, 0x8(r4)
    fsubs f4, f0, f1
    lfs f3, 0x40(r3)
    fcmpo cr0, f4, f3
    ble fn_801379F0_L_80137A48
    li r0, 0x0
    b fn_801379F0_L_80137B2C
    fn_801379F0_L_80137A48:
    fadds f4, f0, f1
    lfs f3, 0x44(r3)
    fcmpo cr0, f4, f3
    bge fn_801379F0_L_80137A60
    li r0, 0x0
    b fn_801379F0_L_80137B2C
    fn_801379F0_L_80137A60:
    lfs f3, 0x4(r5)
    lfs f4, 0x0(r5)
    fmuls f3, f3, f7
    lfs f5, 0x8(r5)
    lfs f6, 0xc(r5)
    fmadds f3, f4, f8, f3
    fmadds f3, f5, f2, f3
    fadds f5, f6, f3
    stfs f5, 0x0(r4)
    lfs f3, 0x8(r3)
    lfs f4, 0x0(r3)
    fmuls f3, f0, f3
    fmadds f3, f5, f4, f3
    fcmpo cr0, f3, f1
    ble fn_801379F0_L_80137AA4
    li r0, 0x0
    b fn_801379F0_L_80137B2C
    fn_801379F0_L_80137AA4:
    lfs f3, 0x18(r3)
    lfs f4, 0x10(r3)
    fmuls f3, f0, f3
    fmadds f3, f5, f4, f3
    fcmpo cr0, f3, f1
    ble fn_801379F0_L_80137AC4
    li r0, 0x0
    b fn_801379F0_L_80137B2C
    fn_801379F0_L_80137AC4:
    lfs f3, 0x14(r5)
    lfs f4, 0x10(r5)
    fmuls f3, f3, f7
    lfs f5, 0x18(r5)
    lfs f6, 0x1c(r5)
    fmadds f3, f4, f8, f3
    fmadds f2, f5, f2, f3
    fadds f4, f6, f2
    stfs f4, 0x4(r4)
    lfs f2, 0x28(r3)
    lfs f3, 0x24(r3)
    fmuls f2, f0, f2
    fmadds f2, f4, f3, f2
    fcmpo cr0, f2, f1
    ble fn_801379F0_L_80137B08
    li r0, 0x0
    b fn_801379F0_L_80137B2C
    fn_801379F0_L_80137B08:
    lfs f2, 0x38(r3)
    lfs f3, 0x34(r3)
    fmuls f0, f0, f2
    fmadds f0, f4, f3, f0
    fcmpo cr0, f0, f1
    ble fn_801379F0_L_80137B28
    li r0, 0x0
    b fn_801379F0_L_80137B2C
    fn_801379F0_L_80137B28:
    li r0, 0x1
    fn_801379F0_L_80137B2C:
    clrlwi. r0, r0, 24
    bne fn_801379F0_L_80137B3C
    li r3, 0x0
    blr
    fn_801379F0_L_80137B3C:
    lfs f4, 0x8(r4)
    lis r3, lbl_80677CB8@ha
    addi r3, r3, lbl_80677CB8@l
    fneg f3, f1
    fadds f0, f4, f1
    lwz r4, lbl_806D1524(r13)
    lfs f1, 0x4(r3)
    lfs f2, 0x0(r3)
    b fn_801379F0_L_80137C7C
    fn_801379F0_L_80137B60:
    lfs f5, 0x38(r4)
    fcmpo cr0, f5, f0
    bge fn_801379F0_L_80137B74
    li r0, 0x1
    b fn_801379F0_L_80137C68
    fn_801379F0_L_80137B74:
    lfs f5, 0x40(r4)
    lfs f6, 0x3c(r4)
    fmuls f5, f1, f5
    lfs f7, 0x44(r4)
    lfs f8, 0x48(r4)
    fmadds f5, f2, f6, f5
    fmadds f5, f4, f7, f5
    fadds f5, f8, f5
    fcmpo cr0, f5, f3
    ble fn_801379F0_L_80137BA4
    li r0, 0x1
    b fn_801379F0_L_80137C68
    fn_801379F0_L_80137BA4:
    lfs f5, 0x50(r4)
    lfs f6, 0x4c(r4)
    fmuls f5, f1, f5
    lfs f7, 0x54(r4)
    lfs f8, 0x58(r4)
    fmadds f5, f2, f6, f5
    fmadds f5, f4, f7, f5
    fadds f5, f8, f5
    fcmpo cr0, f5, f3
    ble fn_801379F0_L_80137BD4
    li r0, 0x1
    b fn_801379F0_L_80137C68
    fn_801379F0_L_80137BD4:
    lfs f5, 0x60(r4)
    lfs f6, 0x5c(r4)
    fmuls f5, f1, f5
    lfs f7, 0x64(r4)
    lfs f8, 0x68(r4)
    fmadds f5, f2, f6, f5
    fmadds f5, f4, f7, f5
    fadds f5, f8, f5
    fcmpo cr0, f5, f3
    ble fn_801379F0_L_80137C04
    li r0, 0x1
    b fn_801379F0_L_80137C68
    fn_801379F0_L_80137C04:
    lfs f5, 0x70(r4)
    lfs f6, 0x6c(r4)
    fmuls f5, f1, f5
    lfs f7, 0x74(r4)
    lfs f8, 0x78(r4)
    fmadds f5, f2, f6, f5
    fmadds f5, f4, f7, f5
    fadds f5, f8, f5
    fcmpo cr0, f5, f3
    ble fn_801379F0_L_80137C34
    li r0, 0x1
    b fn_801379F0_L_80137C68
    fn_801379F0_L_80137C34:
    lfs f5, 0x80(r4)
    lfs f6, 0x7c(r4)
    fmuls f5, f1, f5
    lfs f7, 0x84(r4)
    lfs f8, 0x88(r4)
    fmadds f5, f2, f6, f5
    fmadds f5, f4, f7, f5
    fadds f5, f8, f5
    fcmpo cr0, f5, f3
    ble fn_801379F0_L_80137C64
    li r0, 0x1
    b fn_801379F0_L_80137C68
    fn_801379F0_L_80137C64:
    li r0, 0x0
    fn_801379F0_L_80137C68:
    clrlwi. r0, r0, 24
    bne fn_801379F0_L_80137C78
    li r3, 0x0
    blr
    fn_801379F0_L_80137C78:
    lwz r4, 0x4(r4)
    fn_801379F0_L_80137C7C:
    cmplwi r4, 0x0
    bne fn_801379F0_L_80137B60
    li r3, 0x1
    blr
}

extern "C" void fn_80137C8C(float (*m)[4], float *frustum)
{
    Occluder *o;
    Occluder *tail;
    lbl_806D1518 = m;
    lbl_806D151C = frustum;
    lbl_806D1524 = 0;
    tail = 0;
    for (o = lbl_806D1520; o != 0; o = o->next) {
        Vec3f v;
        if (SphereInViewFrustum(&o->center, &v, o->radius) && fn_80137E50(&o->shape)) {
            if (tail == 0) {
                lbl_806D1524 = o;
                tail = o;
                o->activeNext = 0;
            } else {
                tail->activeNext = o;
                tail = o;
                o->activeNext = 0;
            }
        }
    }
}

static inline void MakePlane(float *plane, const Vec3f *a, const Vec3f *b, const Vec3f *c)
{
    Vec3f e1;
    Vec3f e2;
    Vec3f n;
    e1.x = b->x - a->x;
    e1.y = b->y - a->y;
    e1.z = b->z - a->z;
    e2.x = c->x - a->x;
    e2.y = c->y - a->y;
    e2.z = c->z - a->z;
    PSVECCrossProduct(&e1, &e2, &n);
    Vec3_Normalize(&n, &n);
    plane[0] = n.x;
    plane[1] = n.y;
    plane[2] = n.z;
    plane[3] = -(n.x * a->x + n.y * a->y + n.z * a->z);
}

extern "C" unsigned char fn_80137E50(OccluderShape *s)
{
    Vec3f v0;
    Vec3f v1;
    Vec3f v2;
    Vec3f v3;
    if (lbl_806D1518 == 0 || s == 0) {
        return 0;
    }
    PSMTXMultVec(lbl_806D1518, &s->pts[0], &v0);
    PSMTXMultVec(lbl_806D1518, &s->pts[1], &v1);
    PSMTXMultVec(lbl_806D1518, &s->pts[2], &v2);
    PSMTXMultVec(lbl_806D1518, &s->pts[3], &v3);
    s->zmax = v0.z;
    if (v1.z > s->zmax) {
        s->zmax = v1.z;
    }
    if (v2.z > s->zmax) {
        s->zmax = v2.z;
    }
    if (v3.z > s->zmax) {
        s->zmax = v3.z;
    }
    Vec3f origin;
    origin.x = 0.0f;
    origin.y = 0.0f;
    origin.z = 0.0f;
    MakePlane(s->planes[0], &v0, &v1, &v2);
    if (s->planes[0][3] > 0.0f) {
        MakePlane(s->planes[1], &origin, &v0, &v1);
        MakePlane(s->planes[2], &origin, &v1, &v2);
        MakePlane(s->planes[3], &origin, &v2, &v3);
        MakePlane(s->planes[4], &origin, &v3, &v0);
        return 0;
    }
    MakePlane(s->planes[0], &v2, &v1, &v0);
    MakePlane(s->planes[1], &origin, &v1, &v0);
    MakePlane(s->planes[2], &origin, &v2, &v1);
    MakePlane(s->planes[3], &origin, &v3, &v2);
    MakePlane(s->planes[4], &origin, &v0, &v3);
    return 1;
}

extern "C" void fn_80138578(void)
{
    Occluder *p = lbl_806D1520;
    while (p) {
        Occluder *next = p->next;
        if (p) {
            MemoryManager_TimedFree(p);
        }
        p = next;
    }
    lbl_806D1520 = 0;
    lbl_806D1524 = 0;
}

void *operator new(unsigned long size);
void operator delete(void *p);

inline Occluder::Occluder(const Vec3f *a, const Vec3f *b, const Vec3f *c, const Vec3f *d)
{
    fn_80138A50(this, a, b, c, d);
}

static inline PObj *DObjPObj(DObj *d)
{
    return d != 0 ? d->pobj : 0;
}

static inline PObj *PObjNext(PObj *p)
{
    return p != 0 ? p->next : 0;
}

static inline DObj *DObjNext(DObj *d)
{
    return d != 0 ? d->next : 0;
}

static inline JObj *JObjChild(JObj *j)
{
    return j == 0 ? 0 : j->child;
}

static inline JObj *JObjNext(JObj *j)
{
    return j == 0 ? 0 : j->next;
}

static inline JObj *JObjParent(JObj *j)
{
    return j == 0 ? 0 : j->parent;
}

extern "C" void fn_801385CC(JObj *root)
{
    Vec3f v[4];

    if (root) {
        JObj *jobj = root;
        int depth = 0;
        JObj *next;

        while (jobj) {
            for (DObj *dobj = HSD_JObjGetDObj(jobj); dobj; dobj = DObjNext(dobj)) {
                for (PObj *pobj = DObjPObj(dobj); pobj; pobj = PObjNext(pobj)) {
                    if (fn_80185FE8(jobj, pobj, &v[0], &v[1], &v[2], &v[3])) {
                        Occluder *o = new Occluder(&v[0], &v[1], &v[2], &v[3]);
                        Occluder *p;
                        if ((p = lbl_806D1520) == 0) {
                            lbl_806D1520 = o;
                        } else {
                            while (p->next) {
                                p = p->next;
                            }
                            p->next = o;
                        }
                    }
                }
            }
            if (!(HSD_JObjGetFlags(jobj) & 0x1000) && (next = JObjChild(jobj))) {
                depth++;
                goto advance;
            }
            if (depth <= 0 || !(next = JObjNext(jobj))) {
                do {
                    next = JObjParent(jobj);
                    depth--;
                    if (!next) {
                        break;
                    }
                    jobj = next;
                } while (!(next = JObjNext(jobj)));
                if (depth <= 0) {
                    break;
                }
            }
        advance:
            jobj = next;
        }
    }
}

extern "C" void fn_8013879C(float *frustum, float fovy, float aspect, float zfar, float znear)
{
    Vec3f origin;
    Vec3f b;
    Vec3f c;
    if (frustum != 0) {
        frustum[16] = -zfar;
        frustum[17] = -znear;
        float t = tan(0.5f * fovy);
        float w = t * aspect;
        origin.x = 0.0f;
        origin.y = 0.0f;
        origin.z = 0.0f;
        b.x = frustum[17] * w;
        b.y = -frustum[17] * t;
        b.z = frustum[17];
        c.x = b.x;
        c.y = -b.y;
        c.z = b.z;
        MakePlane(&frustum[0], &origin, &b, &c);
        b.x = -frustum[17] * w;
        b.y = frustum[17] * t;
        b.z = frustum[17];
        c.x = b.x;
        c.y = -b.y;
        c.z = b.z;
        MakePlane(&frustum[4], &origin, &b, &c);
        b.x = -frustum[17] * w;
        b.y = -frustum[17] * t;
        b.z = frustum[17];
        c.x = -b.x;
        c.y = b.y;
        c.z = b.z;
        MakePlane(&frustum[8], &origin, &b, &c);
        b.x = frustum[17] * w;
        b.y = frustum[17] * t;
        b.z = frustum[17];
        c.x = -b.x;
        c.y = b.y;
        c.z = b.z;
        MakePlane(&frustum[12], &origin, &b, &c);
    }
}

extern "C" asm Occluder *fn_80138A50(Occluder *o, const Vec3f *a, const Vec3f *b, const Vec3f *c, const Vec3f *d) { /* 0x80138A50 size:0x294 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    lfs f0, lbl_806D73E0(r2)
    stw r0, 0x34(r1)
    li r0, 0x0
    stw r31, 0x2c(r1)
    mr r31, r3
    stw r0, 0x0(r3)
    stw r0, 0x4(r3)
    stfs f0, 0x8c(r3)
    stfs f0, 0x90(r3)
    stfs f0, 0x94(r3)
    stfs f0, 0x98(r3)
    lfs f0, 0x0(r4)
    stfs f0, 0x8(r3)
    lfs f0, 0x4(r4)
    stfs f0, 0xc(r3)
    lfs f0, 0x8(r4)
    stfs f0, 0x10(r3)
    lfs f0, 0x0(r5)
    stfs f0, 0x14(r3)
    lfs f0, 0x4(r5)
    stfs f0, 0x18(r3)
    lfs f0, 0x8(r5)
    stfs f0, 0x1c(r3)
    lfs f0, 0x0(r6)
    stfs f0, 0x20(r3)
    lfs f0, 0x4(r6)
    stfs f0, 0x24(r3)
    lfs f0, 0x8(r6)
    stfs f0, 0x28(r3)
    lfs f0, 0x0(r7)
    stfs f0, 0x2c(r3)
    lfs f0, 0x4(r7)
    stfs f0, 0x30(r3)
    lfs f0, 0x8(r7)
    stfs f0, 0x34(r3)
    lwz r0, 0x0(r4)
    lwz r3, 0x4(r4)
    stw r0, 0x8(r1)
    stw r0, 0x14(r1)
    stw r3, 0x18(r1)
    lfs f0, 0x14(r1)
    lwz r0, 0x8(r4)
    stw r3, 0xc(r1)
    stw r0, 0x1c(r1)
    lfs f1, 0x0(r5)
    stw r0, 0x10(r1)
    fcmpo cr0, f1, f0
    ble fn_80138A50_L_80138B1C
    stfs f1, 0x14(r1)
    fn_80138A50_L_80138B1C:
    lfs f1, 0x4(r5)
    lfs f0, 0x18(r1)
    fcmpo cr0, f1, f0
    ble fn_80138A50_L_80138B30
    stfs f1, 0x18(r1)
    fn_80138A50_L_80138B30:
    lfs f1, 0x8(r5)
    lfs f0, 0x1c(r1)
    fcmpo cr0, f1, f0
    ble fn_80138A50_L_80138B44
    stfs f1, 0x1c(r1)
    fn_80138A50_L_80138B44:
    lfs f1, 0x0(r5)
    lfs f0, 0x8(r1)
    fcmpo cr0, f1, f0
    bge fn_80138A50_L_80138B58
    stfs f1, 0x8(r1)
    fn_80138A50_L_80138B58:
    lfs f1, 0x4(r5)
    lfs f0, 0xc(r1)
    fcmpo cr0, f1, f0
    bge fn_80138A50_L_80138B6C
    stfs f1, 0xc(r1)
    fn_80138A50_L_80138B6C:
    lfs f1, 0x8(r5)
    lfs f0, 0x10(r1)
    fcmpo cr0, f1, f0
    bge fn_80138A50_L_80138B80
    stfs f1, 0x10(r1)
    fn_80138A50_L_80138B80:
    lfs f1, 0x0(r6)
    lfs f0, 0x14(r1)
    fcmpo cr0, f1, f0
    ble fn_80138A50_L_80138B94
    stfs f1, 0x14(r1)
    fn_80138A50_L_80138B94:
    lfs f1, 0x4(r6)
    lfs f0, 0x18(r1)
    fcmpo cr0, f1, f0
    ble fn_80138A50_L_80138BA8
    stfs f1, 0x18(r1)
    fn_80138A50_L_80138BA8:
    lfs f1, 0x8(r6)
    lfs f0, 0x1c(r1)
    fcmpo cr0, f1, f0
    ble fn_80138A50_L_80138BBC
    stfs f1, 0x1c(r1)
    fn_80138A50_L_80138BBC:
    lfs f1, 0x0(r6)
    lfs f0, 0x8(r1)
    fcmpo cr0, f1, f0
    bge fn_80138A50_L_80138BD0
    stfs f1, 0x8(r1)
    fn_80138A50_L_80138BD0:
    lfs f1, 0x4(r6)
    lfs f0, 0xc(r1)
    fcmpo cr0, f1, f0
    bge fn_80138A50_L_80138BE4
    stfs f1, 0xc(r1)
    fn_80138A50_L_80138BE4:
    lfs f1, 0x8(r6)
    lfs f0, 0x10(r1)
    fcmpo cr0, f1, f0
    bge fn_80138A50_L_80138BF8
    stfs f1, 0x10(r1)
    fn_80138A50_L_80138BF8:
    lfs f1, 0x0(r7)
    lfs f0, 0x14(r1)
    fcmpo cr0, f1, f0
    ble fn_80138A50_L_80138C0C
    stfs f1, 0x14(r1)
    fn_80138A50_L_80138C0C:
    lfs f1, 0x4(r7)
    lfs f0, 0x18(r1)
    fcmpo cr0, f1, f0
    ble fn_80138A50_L_80138C20
    stfs f1, 0x18(r1)
    fn_80138A50_L_80138C20:
    lfs f1, 0x8(r7)
    lfs f0, 0x1c(r1)
    fcmpo cr0, f1, f0
    ble fn_80138A50_L_80138C34
    stfs f1, 0x1c(r1)
    fn_80138A50_L_80138C34:
    lfs f1, 0x0(r7)
    lfs f0, 0x8(r1)
    fcmpo cr0, f1, f0
    bge fn_80138A50_L_80138C48
    stfs f1, 0x8(r1)
    fn_80138A50_L_80138C48:
    lfs f1, 0x4(r7)
    lfs f0, 0xc(r1)
    fcmpo cr0, f1, f0
    bge fn_80138A50_L_80138C5C
    stfs f1, 0xc(r1)
    fn_80138A50_L_80138C5C:
    lfs f1, 0x8(r7)
    lfs f0, 0x10(r1)
    fcmpo cr0, f1, f0
    bge fn_80138A50_L_80138C70
    stfs f1, 0x10(r1)
    fn_80138A50_L_80138C70:
    lfs f1, 0x14(r1)
    addi r3, r1, 0x14
    lfs f0, 0x8(r1)
    mr r5, r3
    lfs f3, lbl_806D73E4(r2)
    addi r4, r31, 0x8c
    fadds f2, f1, f0
    lfs f1, 0xc(r1)
    lfs f0, 0x10(r1)
    fmuls f2, f3, f2
    stfs f2, 0x8c(r31)
    lfs f2, 0x18(r1)
    fadds f1, f2, f1
    fmuls f1, f3, f1
    stfs f1, 0x90(r31)
    lfs f1, 0x1c(r1)
    fadds f0, f1, f0
    fmuls f0, f3, f0
    stfs f0, 0x94(r31)
    bl Vec3_Subtract
    addi r3, r1, 0x14
    bl Vec3_Magnitude
    stfs f1, 0x98(r31)
    mr r3, r31
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

extern "C" void CourseObjects_Activate(void)
{
    for (CourseObj *o = lbl_806D1534; o < lbl_806D1534 + lbl_806D1538; o++) {
        if (o->state == 0) {
            o->state = 1;
            o->f34 = lbl_806D73E8;
            o->f1C = lbl_806D73E8;
            o->px = o->x;
            o->py = o->y;
            o->pz = o->z;
            o->f30 = lbl_806D73E8;
        }
    }
}

extern "C" void fn_80138D48(void)
{
    for (CourseObj *o = lbl_806D1534; o < lbl_806D1534 + lbl_806D1538; o++) {
        if (o->state == 0 || o->state == 1) {
            o->state = 2;
            o->f34 = lbl_806D73EC;
            o->f1C = lbl_806D73E8;
            o->px = o->x;
            o->py = o->y;
            o->pz = o->z;
            o->f30 = lbl_806D73E8;
        }
    }
}

extern "C" asm void fn_80138DB8(void) { /* 0x80138DB8 size:0xA58 */
    nofralloc
    stwu r1, -0x260(r1)
    mflr r0
    stw r0, 0x264(r1)
    stfd f31, 0x250(r1)
    psq_st f31, 0x258(r1), 0, 0
    stfd f30, 0x240(r1)
    psq_st f30, 0x248(r1), 0, 0
    stmw r24, 0x220(r1)
    lwz r0, lbl_806D1538(r13)
    cmpwi r0, 0x0
    beq fn_80138DB8_L_801397EC
    lwz r31, lbl_806D1534(r13)
    b fn_80138DB8_L_801391F0
    fn_80138DB8_L_80138DEC:
    li r0, 0x0
    stb r0, 0x38(r31)
    lwz r0, 0x18(r31)
    cmpwi r0, 0x0
    beq fn_80138DB8_L_801391EC
    cmpwi r0, 0x4
    beq fn_80138DB8_L_801391EC
    lfs f1, 0x34(r31)
    lfs f0, lbl_806D73E8(r2)
    fcmpo cr0, f1, f0
    cror eq, lt, eq
    beq fn_80138DB8_L_801391EC
    lfs f1, lbl_806D73F0(r2)
    addi r3, r31, 0x20
    addi r4, r1, 0x14
    bl fn_80137718
    clrlwi. r0, r3, 24
    beq fn_80138DB8_L_801391EC
    lfs f1, 0x1c(r1)
    lfs f0, lbl_806D73F4(r2)
    fcmpo cr0, f1, f0
    ble fn_80138DB8_L_801391EC
    li r0, 0x1
    lfs f2, lbl_806D73E8(r2)
    stb r0, 0x38(r31)
    addi r24, r1, 0xf0
    lfs f0, lbl_806D73EC(r2)
    stfs f2, 0x1e0(r1)
    stfs f2, 0x1f4(r1)
    stfs f2, 0x208(r1)
    stfs f2, 0x21c(r1)
    stfs f2, 0xf0(r1)
    stfs f2, 0x104(r1)
    stfs f2, 0x118(r1)
    stfs f2, 0x12c(r1)
    stfs f2, 0x1e4(r1)
    stfs f2, 0x1e8(r1)
    stfs f2, 0x1ec(r1)
    stfs f2, 0x1f0(r1)
    stfs f2, 0x1f8(r1)
    stfs f2, 0x1fc(r1)
    stfs f2, 0x200(r1)
    stfs f2, 0x204(r1)
    stfs f2, 0x20c(r1)
    stfs f2, 0x210(r1)
    stfs f2, 0x214(r1)
    stfs f2, 0x218(r1)
    stfs f0, 0x21c(r1)
    stfs f0, 0x208(r1)
    stfs f0, 0x1f4(r1)
    stfs f0, 0x1e0(r1)
    lfs f30, 0x30(r31)
    stfs f2, 0xf4(r1)
    fmr f1, f30
    stfs f2, 0xf8(r1)
    stfs f2, 0xfc(r1)
    stfs f2, 0x100(r1)
    stfs f2, 0x108(r1)
    stfs f2, 0x10c(r1)
    stfs f2, 0x110(r1)
    stfs f2, 0x114(r1)
    stfs f2, 0x11c(r1)
    stfs f2, 0x120(r1)
    stfs f2, 0x124(r1)
    stfs f2, 0x128(r1)
    stfs f0, 0x12c(r1)
    stfs f0, 0x118(r1)
    stfs f0, 0x104(r1)
    stfs f0, 0xf0(r1)
    bl cos
    frsp f31, f1
    fmr f1, f30
    bl sin
    frsp f1, f1
    li r5, 0x0
    li r0, 0x2
    stfs f31, 0xf0(r1)
    mr r4, r5
    addi r6, r1, 0x70
    fneg f0, f1
    stfs f1, 0x110(r1)
    stfs f31, 0x118(r1)
    stfs f0, 0xf8(r1)
    mtctr r0
    fn_80138DB8_L_80138F3C:
    lfs f7, 0x0(r24)
    slwi r0, r5, 2
    lfs f6, 0x1e0(r1)
    addi r3, r5, 0x1
    lfs f5, 0x4(r24)
    fmuls f8, f7, f6
    lfs f4, 0x1f0(r1)
    lfs f3, 0x8(r24)
    lfs f2, 0x200(r1)
    fmadds f8, f5, f4, f8
    lfs f1, 0xc(r24)
    lfs f0, 0x210(r1)
    lfs f6, 0x1e4(r1)
    fmadds f8, f3, f2, f8
    lfs f4, 0x1f4(r1)
    lfs f2, 0x204(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x214(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x1e8(r1)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x1f8(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x208(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x218(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0x1ec(r1)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x1fc(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x20c(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x21c(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    lfs f7, 0x10(r24)
    slwi r0, r5, 2
    lfs f6, 0x1e0(r1)
    addi r3, r5, 0x1
    lfs f5, 0x14(r24)
    addi r4, r4, 0x1
    fmuls f8, f7, f6
    lfs f4, 0x1f0(r1)
    lfs f3, 0x18(r24)
    lfs f1, 0x1c(r24)
    addi r24, r24, 0x20
    fmadds f8, f5, f4, f8
    lfs f2, 0x200(r1)
    lfs f0, 0x210(r1)
    fmadds f8, f3, f2, f8
    lfs f6, 0x1e4(r1)
    lfs f4, 0x1f4(r1)
    lfs f2, 0x204(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x214(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x1e8(r1)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x1f8(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x208(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x218(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0x1ec(r1)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x1fc(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x20c(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x21c(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    bdnz fn_80138DB8_L_80138F3C
    lfs f7, 0x70(r1)
    addi r3, r1, 0x1e0
    lfs f6, 0x74(r1)
    addi r4, r31, 0x3c
    stfs f7, 0xf0(r1)
    lfs f5, 0x78(r1)
    stfs f6, 0xf4(r1)
    lfs f4, 0x7c(r1)
    stfs f5, 0xf8(r1)
    lfs f3, 0x80(r1)
    stfs f4, 0xfc(r1)
    lfs f2, 0x84(r1)
    stfs f3, 0x100(r1)
    lfs f1, 0x88(r1)
    stfs f2, 0x104(r1)
    lfs f0, 0x8c(r1)
    stfs f1, 0x108(r1)
    lfs f7, 0x90(r1)
    stfs f0, 0x10c(r1)
    lfs f6, 0x94(r1)
    lfs f5, 0x98(r1)
    lfs f4, 0x9c(r1)
    lfs f3, 0xa0(r1)
    lfs f2, 0xa4(r1)
    lfs f1, 0xa8(r1)
    lfs f0, 0xac(r1)
    stfs f7, 0x110(r1)
    lwz r24, 0xf0(r1)
    stfs f6, 0x114(r1)
    lwz r25, 0xf4(r1)
    stfs f5, 0x118(r1)
    lwz r26, 0xf8(r1)
    stfs f4, 0x11c(r1)
    lwz r27, 0xfc(r1)
    stfs f3, 0x120(r1)
    lwz r28, 0x100(r1)
    stfs f2, 0x124(r1)
    lwz r29, 0x104(r1)
    stfs f1, 0x128(r1)
    lwz r30, 0x108(r1)
    stfs f0, 0x12c(r1)
    lwz r12, 0x10c(r1)
    lwz r11, 0x110(r1)
    lwz r10, 0x114(r1)
    lwz r9, 0x118(r1)
    lwz r8, 0x11c(r1)
    lwz r7, 0x120(r1)
    lwz r6, 0x124(r1)
    lwz r5, 0x128(r1)
    lwz r0, 0x12c(r1)
    stw r24, 0x1e0(r1)
    stw r25, 0x1e4(r1)
    stw r26, 0x1e8(r1)
    stw r27, 0x1ec(r1)
    stw r28, 0x1f0(r1)
    stw r29, 0x1f4(r1)
    stw r30, 0x1f8(r1)
    stw r12, 0x1fc(r1)
    stw r11, 0x200(r1)
    stw r10, 0x204(r1)
    stw r9, 0x208(r1)
    stw r8, 0x20c(r1)
    stw r7, 0x210(r1)
    stw r6, 0x214(r1)
    stw r5, 0x218(r1)
    stw r0, 0x21c(r1)
    lfs f2, 0x28(r31)
    lfs f1, 0x24(r31)
    lfs f0, 0x20(r31)
    stfs f0, 0x210(r1)
    stfs f1, 0x214(r1)
    stfs f2, 0x218(r1)
    bl Mtx4x4_TransposeTo4x3
    fn_80138DB8_L_801391EC:
    addi r31, r31, 0xc0
    fn_80138DB8_L_801391F0:
    lwz r0, lbl_806D1538(r13)
    lwz r3, lbl_806D1534(r13)
    mulli r0, r0, 0xc0
    add r0, r3, r0
    cmplw r31, r0
    blt fn_80138DB8_L_80138DEC
    lwz r3, lbl_806D1528(r13)
    li r4, 0x0
    bl LinkedNode_GetField10_OrFallback
    bl HSD_JObjGetDObj
    mr r31, r3
    lwz r3, lbl_806D1528(r13)
    li r4, 0x0
    bl LinkedNode_GetField10_OrFallback
    mr r4, r3
    mr r5, r31
    addi r3, r1, 0x5c
    lis r6, 0x4000
    li r7, 0x1
    bl GXChannel_Init
    lwz r24, lbl_806D1534(r13)
    b fn_80138DB8_L_80139280
    fn_80138DB8_L_80139248:
    lbz r0, 0x38(r24)
    cmplwi r0, 0x0
    beq fn_80138DB8_L_8013927C
    lwz r0, 0x0(r24)
    cmpwi r0, 0x1
    bne fn_80138DB8_L_8013927C
    lwz r3, lbl_806D1528(r13)
    li r4, 0x0
    lfs f1, 0x34(r24)
    bl Object_SetColorAlphaOnly
    addi r3, r1, 0x5c
    addi r4, r24, 0x3c
    bl GXChannel_PushTransform
    fn_80138DB8_L_8013927C:
    addi r24, r24, 0xc0
    fn_80138DB8_L_80139280:
    lwz r0, lbl_806D1538(r13)
    lwz r3, lbl_806D1534(r13)
    mulli r0, r0, 0xc0
    add r0, r3, r0
    cmplw r24, r0
    blt fn_80138DB8_L_80139248
    addi r3, r1, 0x5c
    li r4, -0x1
    bl dtor_8007D9C4
    lwz r3, lbl_806D152C(r13)
    li r4, 0x0
    bl LinkedNode_GetField10_OrFallback
    bl HSD_JObjGetDObj
    mr r31, r3
    lwz r3, lbl_806D152C(r13)
    li r4, 0x0
    bl LinkedNode_GetField10_OrFallback
    mr r4, r3
    mr r5, r31
    addi r3, r1, 0x48
    lis r6, 0x4000
    li r7, 0x1
    bl GXChannel_Init
    lwz r24, lbl_806D1534(r13)
    b fn_80138DB8_L_8013931C
    fn_80138DB8_L_801392E4:
    lbz r0, 0x38(r24)
    cmplwi r0, 0x0
    beq fn_80138DB8_L_80139318
    lwz r0, 0x0(r24)
    cmpwi r0, 0x2
    bne fn_80138DB8_L_80139318
    lwz r3, lbl_806D152C(r13)
    li r4, 0x0
    lfs f1, 0x34(r24)
    bl Object_SetColorAlphaOnly
    addi r3, r1, 0x48
    addi r4, r24, 0x3c
    bl GXChannel_PushTransform
    fn_80138DB8_L_80139318:
    addi r24, r24, 0xc0
    fn_80138DB8_L_8013931C:
    lwz r0, lbl_806D1538(r13)
    lwz r3, lbl_806D1534(r13)
    mulli r0, r0, 0xc0
    add r0, r3, r0
    cmplw r24, r0
    blt fn_80138DB8_L_801392E4
    addi r3, r1, 0x48
    li r4, -0x1
    bl dtor_8007D9C4
    lwz r3, lbl_806D152C(r13)
    li r4, 0x0
    bl LinkedNode_GetField10_OrFallback
    cmplwi r3, 0x0
    bne fn_80138DB8_L_8013935C
    li r24, 0x0
    b fn_80138DB8_L_80139360
    fn_80138DB8_L_8013935C:
    lwz r24, 0x8(r3)
    fn_80138DB8_L_80139360:
    lwz r3, lbl_806D152C(r13)
    li r4, 0x0
    bl LinkedNode_GetField10_OrFallback
    cmplwi r3, 0x0
    bne fn_80138DB8_L_8013937C
    li r3, 0x0
    b fn_80138DB8_L_80139380
    fn_80138DB8_L_8013937C:
    lwz r3, 0x8(r3)
    fn_80138DB8_L_80139380:
    bl HSD_JObjGetDObj
    mr r5, r3
    mr r4, r24
    addi r3, r1, 0x34
    lis r6, 0x4000
    li r7, 0x1
    bl GXChannel_Init
    lwz r24, lbl_806D1534(r13)
    b fn_80138DB8_L_801393DC
    fn_80138DB8_L_801393A4:
    lbz r0, 0x38(r24)
    cmplwi r0, 0x0
    beq fn_80138DB8_L_801393D8
    lwz r0, 0x0(r24)
    cmpwi r0, 0x2
    bne fn_80138DB8_L_801393D8
    lwz r3, lbl_806D152C(r13)
    li r4, 0x0
    lfs f1, 0x34(r24)
    bl Object_SetColorAlphaOnly
    addi r3, r1, 0x34
    addi r4, r24, 0x3c
    bl GXChannel_PushTransform
    fn_80138DB8_L_801393D8:
    addi r24, r24, 0xc0
    fn_80138DB8_L_801393DC:
    lwz r0, lbl_806D1538(r13)
    lwz r3, lbl_806D1534(r13)
    mulli r0, r0, 0xc0
    add r0, r3, r0
    cmplw r24, r0
    blt fn_80138DB8_L_801393A4
    addi r3, r1, 0x34
    li r4, -0x1
    bl dtor_8007D9C4
    lwz r3, lbl_806D1530(r13)
    bl Archive_GetRootJObj
    bl HSD_JObjGetDObj
    mr r31, r3
    lwz r3, lbl_806D1530(r13)
    bl Archive_GetRootJObj
    mr r4, r3
    mr r5, r31
    addi r3, r1, 0x20
    lis r6, 0x4000
    li r7, 0x1
    bl GXChannel_Init
    lwz r25, lbl_806D1534(r13)
    b fn_80138DB8_L_801397C8
    fn_80138DB8_L_80139438:
    lbz r0, 0x38(r25)
    cmplwi r0, 0x1
    bne fn_80138DB8_L_801397C4
    lwz r0, 0x18(r25)
    cmpwi r0, 0x3
    bne fn_80138DB8_L_801397C4
    lfs f31, lbl_806D73E8(r2)
    mr r24, r25
    li r26, 0x0
    fn_80138DB8_L_8013945C:
    lfs f1, 0x70(r24)
    fcmpo cr0, f1, f31
    cror eq, gt, eq
    bne fn_80138DB8_L_801397B4
    lfs f0, lbl_806D73F8(r2)
    addi r3, r25, 0x20
    addi r4, r24, 0x74
    addi r5, r1, 0x8
    fdivs f30, f1, f0
    bl PSVECAdd
    lfs f0, lbl_806D73E8(r2)
    li r5, 0x0
    lfs f3, lbl_806D73EC(r2)
    li r0, 0x2
    lfs f1, 0x34(r25)
    addi r7, r1, 0x1a0
    stfs f0, 0x160(r1)
    fsubs f2, f3, f30
    lfs f5, lbl_806D7400(r2)
    mr r4, r5
    lfs f4, lbl_806D73FC(r2)
    addi r6, r1, 0xb0
    stfs f0, 0x174(r1)
    fnmsubs f4, f5, f30, f4
    stfs f0, 0x188(r1)
    fmuls f30, f2, f1
    stfs f0, 0x19c(r1)
    stfs f3, 0x188(r1)
    stfs f3, 0x174(r1)
    stfs f3, 0x160(r1)
    stfs f0, 0x1a0(r1)
    stfs f0, 0x1b4(r1)
    stfs f0, 0x1c8(r1)
    stfs f0, 0x1dc(r1)
    stfs f0, 0x164(r1)
    stfs f0, 0x168(r1)
    stfs f0, 0x16c(r1)
    stfs f0, 0x170(r1)
    stfs f0, 0x178(r1)
    stfs f0, 0x17c(r1)
    stfs f0, 0x180(r1)
    stfs f0, 0x184(r1)
    stfs f0, 0x18c(r1)
    stfs f0, 0x190(r1)
    stfs f0, 0x194(r1)
    stfs f0, 0x198(r1)
    stfs f3, 0x19c(r1)
    stfs f4, 0x160(r1)
    stfs f4, 0x174(r1)
    stfs f4, 0x188(r1)
    stfs f0, 0x1a4(r1)
    stfs f0, 0x1a8(r1)
    stfs f0, 0x1ac(r1)
    stfs f0, 0x1b0(r1)
    stfs f0, 0x1b8(r1)
    stfs f0, 0x1bc(r1)
    stfs f0, 0x1c0(r1)
    stfs f0, 0x1c4(r1)
    stfs f0, 0x1cc(r1)
    stfs f0, 0x1d0(r1)
    stfs f0, 0x1d4(r1)
    stfs f0, 0x1d8(r1)
    stfs f3, 0x1dc(r1)
    stfs f3, 0x1c8(r1)
    stfs f3, 0x1b4(r1)
    stfs f3, 0x1a0(r1)
    mtctr r0
    fn_80138DB8_L_80139568:
    lfs f7, 0x0(r7)
    slwi r0, r5, 2
    lfs f6, 0x160(r1)
    addi r3, r5, 0x1
    lfs f5, 0x4(r7)
    fmuls f8, f7, f6
    lfs f4, 0x170(r1)
    lfs f3, 0x8(r7)
    lfs f2, 0x180(r1)
    fmadds f8, f5, f4, f8
    lfs f1, 0xc(r7)
    lfs f0, 0x190(r1)
    lfs f6, 0x164(r1)
    fmadds f8, f3, f2, f8
    lfs f4, 0x174(r1)
    lfs f2, 0x184(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x194(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x168(r1)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x178(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x188(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x198(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0x16c(r1)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x17c(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x18c(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x19c(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    lfs f7, 0x10(r7)
    slwi r0, r5, 2
    lfs f6, 0x160(r1)
    addi r3, r5, 0x1
    lfs f5, 0x14(r7)
    addi r4, r4, 0x1
    fmuls f8, f7, f6
    lfs f4, 0x170(r1)
    lfs f3, 0x18(r7)
    lfs f1, 0x1c(r7)
    addi r7, r7, 0x20
    fmadds f8, f5, f4, f8
    lfs f2, 0x180(r1)
    lfs f0, 0x190(r1)
    fmadds f8, f3, f2, f8
    lfs f6, 0x164(r1)
    lfs f4, 0x174(r1)
    lfs f2, 0x184(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x194(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x168(r1)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x178(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x188(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x198(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0x16c(r1)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x17c(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x18c(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x19c(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    bdnz fn_80138DB8_L_80139568
    lfs f2, 0xc0(r1)
    addi r3, r1, 0x1a0
    lfs f1, 0xc4(r1)
    addi r4, r1, 0x130
    lfs f0, 0xc8(r1)
    stfs f2, 0x1b0(r1)
    lfs f7, 0xb0(r1)
    stfs f1, 0x1b4(r1)
    lfs f6, 0xb4(r1)
    stfs f0, 0x1b8(r1)
    lfs f5, 0xb8(r1)
    lfs f4, 0xbc(r1)
    lfs f3, 0xcc(r1)
    lfs f2, 0xe0(r1)
    lfs f1, 0xe4(r1)
    lfs f0, 0xe8(r1)
    stfs f7, 0x1a0(r1)
    lfs f7, 0xd0(r1)
    stfs f6, 0x1a4(r1)
    lfs f6, 0xd4(r1)
    stfs f5, 0x1a8(r1)
    lfs f5, 0xd8(r1)
    stfs f4, 0x1ac(r1)
    lfs f4, 0xdc(r1)
    stfs f3, 0x1bc(r1)
    lfs f3, 0xec(r1)
    stfs f2, 0x1d0(r1)
    lfs f2, 0x8(r1)
    stfs f1, 0x1d4(r1)
    lfs f1, 0xc(r1)
    stfs f0, 0x1d8(r1)
    lfs f0, 0x10(r1)
    stfs f7, 0x1c0(r1)
    stfs f6, 0x1c4(r1)
    stfs f5, 0x1c8(r1)
    stfs f4, 0x1cc(r1)
    stfs f3, 0x1dc(r1)
    stfs f2, 0x1d0(r1)
    stfs f1, 0x1d4(r1)
    stfs f0, 0x1d8(r1)
    bl Mtx4x4_TransposeTo4x3
    fmr f1, f30
    lwz r3, lbl_806D1530(r13)
    li r4, 0x0
    bl Object_SetColorAlphaOnly
    addi r3, r1, 0x20
    addi r4, r1, 0x130
    bl GXChannel_PushTransform
    fn_80138DB8_L_801397B4:
    addi r26, r26, 0x1
    addi r24, r24, 0x10
    cmpwi r26, 0x5
    blt fn_80138DB8_L_8013945C
    fn_80138DB8_L_801397C4:
    addi r25, r25, 0xc0
    fn_80138DB8_L_801397C8:
    lwz r0, lbl_806D1538(r13)
    lwz r3, lbl_806D1534(r13)
    mulli r0, r0, 0xc0
    add r0, r3, r0
    cmplw r25, r0
    blt fn_80138DB8_L_80139438
    addi r3, r1, 0x20
    li r4, -0x1
    bl dtor_8007D9C4
    fn_80138DB8_L_801397EC:
    psq_l f31, 0x258(r1), 0, 0
    lfd f31, 0x250(r1)
    psq_l f30, 0x248(r1), 0, 0
    lfd f30, 0x240(r1)
    lmw r24, 0x220(r1)
    lwz r0, 0x264(r1)
    mtlr r0
    addi r1, r1, 0x260
    blr
}

extern "C" void fn_80139810(void)
{
    ScopedTimer t(0x25);
    fn_80138DB8();
}

