/*
 * 0x801375D8..0x80138CE4: course object culling and occluder setup.
 * Activation and the per-frame update live in CourseObjects_80138CE4.cpp.
 */
#pragma cplusplus on

#include "game/types/Vec3f.h"
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

/* TOP-END */

extern "C" {
extern float (*CourseObjects_801375D8_bss_806D1518)[4];
extern float *CourseObjects_801375D8_bss_806D151C;
extern Vec3f CourseObjects_801375D8_bss_80677CB8;
extern Occluder *CourseObjects_801375D8_bss_806D1524;
extern Occluder *CourseObjects_801375D8_bss_806D1520;
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
unsigned char fn_801375D8(const Vec3f *p, float r);
unsigned char fn_80137718(const Vec3f *p, Vec3f *out, float r);
unsigned char fn_801379F0(const Vec3f *p, float r);
void fn_80137C8C(float (*m)[4], float *frustum);
unsigned char fn_80137E50(OccluderShape *s);
void fn_80138578(void);
void fn_801385CC(JObj *jobj);
void fn_8013879C(float *frustum, float fovy, float aspect, float zfar, float znear);
Occluder *fn_80138A50(Occluder *o, const Vec3f *a, const Vec3f *b, const Vec3f *c, const Vec3f *d);

}

static inline unsigned char SphereInViewFrustum(const Vec3f *p, Vec3f *v, float r)
{
    v->z = CourseObjects_801375D8_bss_806D1518[2][0] * p->x + CourseObjects_801375D8_bss_806D1518[2][1] * p->y + CourseObjects_801375D8_bss_806D1518[2][2] * p->z + CourseObjects_801375D8_bss_806D1518[2][3];
    if (v->z - r > CourseObjects_801375D8_bss_806D151C[16]) {
        return 0;
    }
    if (v->z + r < CourseObjects_801375D8_bss_806D151C[17]) {
        return 0;
    }
    v->x = CourseObjects_801375D8_bss_806D1518[0][0] * p->x + CourseObjects_801375D8_bss_806D1518[0][1] * p->y + CourseObjects_801375D8_bss_806D1518[0][2] * p->z + CourseObjects_801375D8_bss_806D1518[0][3];
    if (v->x * CourseObjects_801375D8_bss_806D151C[0] + v->z * CourseObjects_801375D8_bss_806D151C[2] > r) {
        return 0;
    }
    if (v->x * CourseObjects_801375D8_bss_806D151C[4] + v->z * CourseObjects_801375D8_bss_806D151C[6] > r) {
        return 0;
    }
    v->y = CourseObjects_801375D8_bss_806D1518[1][0] * p->x + CourseObjects_801375D8_bss_806D1518[1][1] * p->y + CourseObjects_801375D8_bss_806D1518[1][2] * p->z + CourseObjects_801375D8_bss_806D1518[1][3];
    if (v->y * CourseObjects_801375D8_bss_806D151C[9] + v->z * CourseObjects_801375D8_bss_806D151C[10] > r) {
        return 0;
    }
    if (v->y * CourseObjects_801375D8_bss_806D151C[13] + v->z * CourseObjects_801375D8_bss_806D151C[14] > r) {
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

/* Same frustum test as SphereInViewFrustum, writing the view-space centre to CourseObjects_801375D8_bss_80677CB8. */
static inline unsigned char SphereInViewFrustumGlobal(const Vec3f *p, float r)
{
    CourseObjects_801375D8_bss_80677CB8.z = CourseObjects_801375D8_bss_806D1518[2][0] * p->x + CourseObjects_801375D8_bss_806D1518[2][1] * p->y + CourseObjects_801375D8_bss_806D1518[2][2] * p->z + CourseObjects_801375D8_bss_806D1518[2][3];
    if (CourseObjects_801375D8_bss_80677CB8.z - r > CourseObjects_801375D8_bss_806D151C[16]) {
        return 0;
    }
    if (CourseObjects_801375D8_bss_80677CB8.z + r < CourseObjects_801375D8_bss_806D151C[17]) {
        return 0;
    }
    float x = CourseObjects_801375D8_bss_806D1518[0][0] * p->x + CourseObjects_801375D8_bss_806D1518[0][1] * p->y + CourseObjects_801375D8_bss_806D1518[0][2] * p->z + CourseObjects_801375D8_bss_806D1518[0][3];
    CourseObjects_801375D8_bss_80677CB8.x = x;
    if (x * CourseObjects_801375D8_bss_806D151C[0] + CourseObjects_801375D8_bss_80677CB8.z * CourseObjects_801375D8_bss_806D151C[2] > r) {
        return 0;
    }
    if (x * CourseObjects_801375D8_bss_806D151C[4] + CourseObjects_801375D8_bss_80677CB8.z * CourseObjects_801375D8_bss_806D151C[6] > r) {
        return 0;
    }
    CourseObjects_801375D8_bss_80677CB8.y = CourseObjects_801375D8_bss_806D1518[1][0] * p->x + CourseObjects_801375D8_bss_806D1518[1][1] * p->y + CourseObjects_801375D8_bss_806D1518[1][2] * p->z + CourseObjects_801375D8_bss_806D1518[1][3];
    if (CourseObjects_801375D8_bss_80677CB8.y * CourseObjects_801375D8_bss_806D151C[9] + CourseObjects_801375D8_bss_80677CB8.z * CourseObjects_801375D8_bss_806D151C[10] > r) {
        return 0;
    }
    if (CourseObjects_801375D8_bss_80677CB8.y * CourseObjects_801375D8_bss_806D151C[13] + CourseObjects_801375D8_bss_80677CB8.z * CourseObjects_801375D8_bss_806D151C[14] > r) {
        return 0;
    }
    return 1;
}

extern "C" unsigned char fn_801375D8(const Vec3f *p, float r)
{
    return SphereInViewFrustumGlobal(p, r);
}

extern "C" unsigned char fn_80137718(const Vec3f *p, Vec3f *out, float r)
{
    if (out == 0) {
        out = &CourseObjects_801375D8_bss_80677CB8;
    }
    if (!SphereInViewFrustum(p, out, r)) {
        return 0;
    }
    for (Occluder *o = CourseObjects_801375D8_bss_806D1524; o != 0; o = o->activeNext) {
        if (!SphereNotOccluded(o, out, r)) {
            return 0;
        }
    }
    return 1;
}

extern "C" unsigned char fn_801379F0(const Vec3f *p, float r)
{
    if (!SphereInViewFrustumGlobal(p, r)) {
        return 0;
    }
    for (Occluder *o = CourseObjects_801375D8_bss_806D1524; o != 0; o = o->activeNext) {
        if (!SphereNotOccluded(o, &CourseObjects_801375D8_bss_80677CB8, r)) {
            return 0;
        }
    }
    return 1;
}

extern "C" void fn_80137C8C(float (*m)[4], float *frustum)
{
    Occluder *o;
    Occluder *tail;
    CourseObjects_801375D8_bss_806D1518 = m;
    CourseObjects_801375D8_bss_806D151C = frustum;
    CourseObjects_801375D8_bss_806D1524 = 0;
    tail = 0;
    for (o = CourseObjects_801375D8_bss_806D1520; o != 0; o = o->next) {
        Vec3f v;
        if (SphereInViewFrustum(&o->center, &v, o->radius) && fn_80137E50(&o->shape)) {
            if (tail == 0) {
                CourseObjects_801375D8_bss_806D1524 = o;
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
    if (CourseObjects_801375D8_bss_806D1518 == 0 || s == 0) {
        return 0;
    }
    PSMTXMultVec(CourseObjects_801375D8_bss_806D1518, &s->pts[0], &v0);
    PSMTXMultVec(CourseObjects_801375D8_bss_806D1518, &s->pts[1], &v1);
    PSMTXMultVec(CourseObjects_801375D8_bss_806D1518, &s->pts[2], &v2);
    PSMTXMultVec(CourseObjects_801375D8_bss_806D1518, &s->pts[3], &v3);
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
    Occluder *p = CourseObjects_801375D8_bss_806D1520;
    while (p) {
        Occluder *next = p->next;
        if (p) {
            MemoryManager_TimedFree(p);
        }
        p = next;
    }
    CourseObjects_801375D8_bss_806D1520 = 0;
    CourseObjects_801375D8_bss_806D1524 = 0;
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
                        if ((p = CourseObjects_801375D8_bss_806D1520) == 0) {
                            CourseObjects_801375D8_bss_806D1520 = o;
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

/* Bounds vector of the occluder setup: an array-backed vec, so whole-vector
 * copies are word copies (lwz/stw) like the target. */
struct OccVec {
    float v[3];
};

static inline void OccVecMax(OccVec *m, const Vec3f *p)
{
    if (p->x > m->v[0]) {
        m->v[0] = p->x;
    }
    if (p->y > m->v[1]) {
        m->v[1] = p->y;
    }
    if (p->z > m->v[2]) {
        m->v[2] = p->z;
    }
}

static inline void OccVecMin(OccVec *m, const Vec3f *p)
{
    if (p->x < m->v[0]) {
        m->v[0] = p->x;
    }
    if (p->y < m->v[1]) {
        m->v[1] = p->y;
    }
    if (p->z < m->v[2]) {
        m->v[2] = p->z;
    }
}

static inline void OccVecSet(Vec3f *dst, const Vec3f *src)
{
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}

/* Occluder from four corner points: stores the quad and a bounding sphere
 * (center of the AABB, radius to its max corner). */
extern "C" Occluder *fn_80138A50(Occluder *o, const Vec3f *a, const Vec3f *b, const Vec3f *c, const Vec3f *d)
{
    OccVec mx;
    OccVec mn;

    o->next = 0;
    o->activeNext = 0;
    o->center.x = 0.0f;
    o->center.y = 0.0f;
    o->center.z = 0.0f;
    o->radius = 0.0f;
    OccVecSet(&o->shape.pts[0], a);
    OccVecSet(&o->shape.pts[1], b);
    OccVecSet(&o->shape.pts[2], c);
    OccVecSet(&o->shape.pts[3], d);
    mx = *(const OccVec *)a;
    mn = mx;
    OccVecMax(&mx, b);
    OccVecMin(&mn, b);
    OccVecMax(&mx, c);
    OccVecMin(&mn, c);
    OccVecMax(&mx, d);
    OccVecMin(&mn, d);
    o->center.x = 0.5f * (mx.v[0] + mn.v[0]);
    o->center.y = 0.5f * (mx.v[1] + mn.v[1]);
    o->center.z = 0.5f * (mx.v[2] + mn.v[2]);
    Vec3_Subtract((Vec3f *)&mx, &o->center, (Vec3f *)&mx);
    o->radius = Vec3_Magnitude((Vec3f *)&mx);
    return o;
}
