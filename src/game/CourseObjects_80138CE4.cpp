/*
 * 0x80138CE4..0x80139898: course object activation and the per-frame update/draw.
 *
 * Split from CourseObjects_801375D8.cpp: the target has two separate 0.0f pool
 * entries (lbl_806D73E0 used only before 0x80138CE4, lbl_806D73E8 only from here
 * on), and MWCC pools every 0.0f literal of one TU into a single constant, so
 * this was an original TU boundary.
 */
#pragma cplusplus on

#include "game/types/Vec3f.h"
struct DObj;
struct JObj {
    char pad0[8];
    JObj *next;
    JObj *parent;
    JObj *child;
};
struct CourseObjTrail {
    float time;
    Vec3f offset;
};
struct CourseObj {
    int type;
    float x, y, z;
    char pad10[8];
    int state;
    float f1C;
    Vec3f p;
    char pad2C[4];
    float f30;
    float f34;
    unsigned char visible;
    float mtx[3][4];
    char pad6C[4];
    CourseObjTrail trail[5];
};

extern "C" {
extern struct CourseObj *lbl_806D1534;
extern int lbl_806D1538;
extern const float lbl_806D73E8;
extern const float lbl_806D73EC;
extern void *lbl_806D1528;
extern void *lbl_806D152C;
extern void *lbl_806D1530;
extern const float lbl_806D7404;

DObj *HSD_JObjGetDObj(JObj *jobj);
JObj *Archive_GetRootJObj(void *model);
JObj *LinkedNode_GetField10_OrFallback(void *model, int idx);
void Mtx4x4_TransposeTo4x3(const void *src, void *dst);
void Object_SetColorAlphaOnly(void *model, int idx, float alpha);
void PSVECAdd(const Vec3f *a, const Vec3f *b, Vec3f *ab);
double cos(double);
double sin(double);
unsigned long OSGetTick(void);
void Profiler_RecordFrame(int id, float ms);
unsigned char fn_80137718(const Vec3f *p, Vec3f *out, float r);
void CourseObjects_Activate(void);
void fn_80138D48(void);
void fn_80138DB8(void);
void fn_80139810(void);
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

struct GXChannel {
    GXChannel(JObj *jobj, DObj *dobj, unsigned int flags, int n);
    ~GXChannel();
    unsigned char pad[0x14];
};

extern "C" int GXChannel_PushTransform(GXChannel *ch, float (*m)[4]);

static inline JObj *JObjNext(JObj *j)
{
    return j == 0 ? 0 : j->next;
}

/* 4x4 matrix helpers, compiled as C. */
#pragma cplusplus off

#include "game/types/Matrix44.h"

static inline void Mtx44Identity(struct Matrix44 *m)
{
    int i;
    for (i = 0; i < 16; ++i) m->v[i] = 0.0f;
    m->v[0] = m->v[5] = m->v[10] = m->v[15] = lbl_806D73EC;
}

static inline void Mtx44Concat(struct Matrix44 *out, const struct Matrix44 *a, const struct Matrix44 *b)
{
    float tmp[16];
    float *m;
    int k, i, j;
    if (out == a || out == b) m = tmp;
    else m = out->v;
    k = 0;
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j) {
            float sum = a->v[k] * b->v[j];
            sum += a->v[k + 1] * b->v[4 + j];
            sum += a->v[k + 2] * b->v[8 + j];
            sum += a->v[k + 3] * b->v[12 + j];
            m[k + j] = sum;
        }
        k += 4;
    }
    if (out == a || out == b) {
        for (i = 0; i < 16; ++i) out->v[i] = tmp[i];
    }
}

static inline float Cosine(float angle) { return (float)cos(angle); }
static inline float Sine(float angle) { return (float)sin(angle); }

static inline void Mtx44RotateY(struct Matrix44 *out, const struct Matrix44 *in, float angle)
{
    struct Matrix44 rot;
    float c, s;
    Mtx44Identity(&rot);
    c = Cosine(angle);
    s = Sine(angle);
    rot.v[0] = c; rot.v[8] = s; rot.v[10] = c; rot.v[2] = -s;
    Mtx44Concat(&rot, &rot, in);
    *out = rot;
}

static inline void Mtx44SetTranslation(struct Matrix44 *m, float x, float y, float z)
{
    m->v[12] = x; m->v[13] = y; m->v[14] = z;
}

#pragma cplusplus reset

extern "C" void CourseObjects_Activate(void)
{
    for (CourseObj *o = lbl_806D1534; o < lbl_806D1534 + lbl_806D1538; o++) {
        if (o->state == 0) {
            o->state = 1;
            o->f34 = lbl_806D73E8;
            o->f1C = lbl_806D73E8;
            o->p.x = o->x;
            o->p.y = o->y;
            o->p.z = o->z;
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
            o->p.x = o->x;
            o->p.y = o->y;
            o->p.z = o->z;
            o->f30 = lbl_806D73E8;
        }
    }
}

extern "C" void fn_80138DB8(void)
{
    CourseObj *o;
    int i;

    if (lbl_806D1538 == 0) {
        return;
    }
    for (o = lbl_806D1534; o < lbl_806D1534 + lbl_806D1538; o++) {
        Vec3f v;
        o->visible = 0;
        if (o->state == 0 || o->state == 4) {
            continue;
        }
        if (o->f34 <= lbl_806D73E8) {
            continue;
        }
        if (!fn_80137718(&o->p, &v, 24.0f)) {
            continue;
        }
        if (v.z > -2000.0f) {
            Matrix44 m;
            o->visible = 1;
            Mtx44Identity(&m);
            Mtx44RotateY(&m, &m, o->f30);
            Mtx44SetTranslation(&m, o->p.x, o->p.y, o->p.z);
            Mtx4x4_TransposeTo4x3(&m, o->mtx);
        }
    }
    {
        GXChannel ch(LinkedNode_GetField10_OrFallback(lbl_806D1528, 0),
            HSD_JObjGetDObj(LinkedNode_GetField10_OrFallback(lbl_806D1528, 0)), 0x40000000, 1);
        for (o = lbl_806D1534; o < lbl_806D1534 + lbl_806D1538; o++) {
            if (o->visible && o->type == 1) {
                Object_SetColorAlphaOnly(lbl_806D1528, 0, o->f34);
                GXChannel_PushTransform(&ch, o->mtx);
            }
        }
    }
    {
        GXChannel ch(LinkedNode_GetField10_OrFallback(lbl_806D152C, 0),
            HSD_JObjGetDObj(LinkedNode_GetField10_OrFallback(lbl_806D152C, 0)), 0x40000000, 1);
        for (o = lbl_806D1534; o < lbl_806D1534 + lbl_806D1538; o++) {
            if (o->visible && o->type == 2) {
                Object_SetColorAlphaOnly(lbl_806D152C, 0, o->f34);
                GXChannel_PushTransform(&ch, o->mtx);
            }
        }
    }
    {
        JObj *jobj = JObjNext(LinkedNode_GetField10_OrFallback(lbl_806D152C, 0));
        GXChannel ch(jobj, HSD_JObjGetDObj(JObjNext(LinkedNode_GetField10_OrFallback(lbl_806D152C, 0))), 0x40000000, 1);
        for (o = lbl_806D1534; o < lbl_806D1534 + lbl_806D1538; o++) {
            if (o->visible && o->type == 2) {
                Object_SetColorAlphaOnly(lbl_806D152C, 0, o->f34);
                GXChannel_PushTransform(&ch, o->mtx);
            }
        }
    }
    {
        GXChannel ch(Archive_GetRootJObj(lbl_806D1530), HSD_JObjGetDObj(Archive_GetRootJObj(lbl_806D1530)), 0x40000000, 1);
        for (o = lbl_806D1534; o < lbl_806D1534 + lbl_806D1538; o++) {
            if (o->visible == 1 && o->state == 3) {
                for (i = 0; i < 5; i++) {
                    CourseObjTrail *t = &o->trail[i];
                    if (t->time >= 0.0f) {
                        Vec3f pos;
                        Matrix44 m;
                        Matrix44 sc;
                        float mtx[3][4];
                        float f = t->time / 10.0f;
                        PSVECAdd(&o->p, &t->offset, &pos);
                        float scale = 1.5f - 0.8f * f;
                        float fade = lbl_806D73EC - f;
                        float alpha = fade * o->f34;
                        Mtx44Identity(&sc);
                        sc.v[0] = scale;
                        sc.v[5] = scale;
                        sc.v[10] = scale;
                        Mtx44Identity(&m);
                        Mtx44Concat(&m, &m, &sc);
                        Mtx44SetTranslation(&m, pos.x, pos.y, pos.z);
                        Mtx4x4_TransposeTo4x3(&m, mtx);
                        Object_SetColorAlphaOnly(lbl_806D1530, 0, alpha);
                        GXChannel_PushTransform(&ch, mtx);
                    }
                }
            }
        }
    }
}

extern "C" void fn_80139810(void)
{
    ScopedTimer t(0x25);
    fn_80138DB8();
}
