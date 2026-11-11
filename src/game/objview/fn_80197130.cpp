// clWCSnow: compiler-emitted RTTI and virtual table, deferred function order.
#include "game/objview/part_render_private.h"
#include "game/types/clMapEffectParts.h"
#include "game/types/size_t.h"
void *operator new(size_t);
void operator delete(void *) throw();
struct PartTable { void *data; PartTable(const void *, int); };
struct ViewParticle {
    unsigned char active;
    unsigned char pad[3];
    float x, y, depth, alpha;
    float speed, amplitude, angle, angularSpeed;
};
struct clWCSnow : clMapEffectParts {
    clNormal3D *model;
    PartTable *table;
    ViewParticle *particles;
    int delay;
    unsigned char reset, enabled;
    unsigned char pad16[2];
    Vec3f position;
    int randomX, randomY, randomParam, randomDelay;
    clWCSnow();
    virtual ~clWCSnow();
    virtual void Update();
    virtual void Draw();
};
extern "C" {
void CObj_LoadProjMatrix(void *, Vec3f *);
void CObj_ApplyScissor(void *, Vec3f *);
unsigned char fn_80123480(void *, Vec3f *);
void Vec3_Subtract(const Vec3f *, const Vec3f *, Vec3f *);
void Vec3_Normalize(const Vec3f *, Vec3f *);
float Vec3_Dot(const Vec3f *, const Vec3f *);
float LUT_Sin12Bit(float);
extern float lbl_80495994[];
extern float lbl_80495A94[];
void Object_DtorWithGXSync(void *, int);
void fn_80123B48(void *, int);
void MemoryManager_Free(void *);
extern const float lbl_806D95F0;
void clNormal3D_SetFlags(clNormal3D *, unsigned int, int);
void *FUN_8003b120(unsigned long);
}
extern "C" const Vec3f lbl_8037DA90[2][5] = {
  {
    {154.16258239746094f, 0.0f, -3856.409423828125f},
    {2851.61767578125f, 0.0f, -3856.40966796875f},
    {2851.617431640625f, 0.0f, -2856.40966796875f},
    {154.16261291503906f, 0.0f, -2856.409423828125f},
    {0.0f, 0.0f, 0.0f}
  },
  {
    {2431.533203125f, 0.0f, -3633.733642578125f},
    {3803.733154296875f, 0.0f, -4088.46630859375f},
    {4258.4658203125f, 0.0f, -2716.266357421875f},
    {2886.265869140625f, 0.0f, -2261.53369140625f},
    {0.0f, 0.0f, 0.0f}
  }
};
#define lbl_8037DB28 " DeleteMapEffect : clWCSnow\n"
#define lbl_8037DB48 " CreateMapEffect : clWCSnow\n"
#define lbl_8037DB68 "ef_snow.dat"
clWCSnow::clWCSnow() {
    int i;
    DebugPrintf(lbl_8037DB48);
    model = 0;
    table = 0;
    particles = 0;
    delay = 0;
    reset = 1;
    enabled = 0;
    position.x = lbl_806D95F0;
    position.y = lbl_806D95F0;
    position.z = lbl_806D95F0;
    randomX = 0;
    randomY = 0;
    randomParam = 0;
    randomDelay = 0;
    model = new clNormal3D(lbl_8037DB68, 1);
    clNormal3D_SetFlags(model, 0x40000000, 0);
    table = new PartTable(lbl_8037DA90, 2);
    particles = (ViewParticle *)FUN_8003b120(50 * sizeof(ViewParticle));
    for (i = 0; i < 50; i++) {
        particles[i].active = 0;
    }
}
clWCSnow::~clWCSnow() {
    Object_DtorWithGXSync(model, 1);
    fn_80123B48(table, 1);
    MemoryManager_Free(particles);
    DebugPrintf(lbl_8037DB28);
}
static inline ViewParticle *FindFree(clWCSnow *o) {
    int i;
    for (i = 0; i < 50; i++) {
        if (o->particles[i].active == 0) return &o->particles[i];
    }
    return 0;
}
static inline float RandomX(clWCSnow *o, float lo, float hi) {
    if (o->randomX >= 64) o->randomX = 0;
    return (hi - lo) * lbl_80495994[o->randomX++] + lo;
}
static inline float RandomY(clWCSnow *o, float lo, float hi) {
    if (o->randomY >= 48) o->randomY = 0;
    return (hi - lo) * lbl_80495A94[o->randomY++] + lo;
}
static inline float RandomDelay(clWCSnow *o, float lo, float hi) {
    if (o->randomDelay >= 64) o->randomDelay = 0;
    return (hi - lo) * lbl_80495994[o->randomDelay++] + lo;
}
static inline float RandomParam(clWCSnow *o, float lo, float hi) {
    if (o->randomParam >= 48) o->randomParam = 0;
    return (hi - lo) * lbl_80495A94[o->randomParam++] + lo;
}

static inline void UpdateParticles(clWCSnow *o, float motion) {
    {
        int j;
        ViewParticle *q;
        int offset;
        for (j = 0, offset = 0; j < 50; offset += sizeof(ViewParticle), j++) {
            q = (ViewParticle *)((char *)o->particles + offset);
            if (q->active) {
                float speed;
                q->angle += q->angularSpeed;
                if (motion > 0.0f) q->depth += motion;
                speed = q->speed;
                q->x = q->amplitude * LUT_Sin12Bit(q->angle) + q->x;
                if (q->x < 0.0f) q->x += 1.0f;
                if (q->x > 1.0f) q->x -= 1.0f;
                q->y += speed;
                if (q->depth < -65.0f) {
                    if (o->enabled) { q->depth = -3.0f; q->alpha = 0.0f; }
                    else q->active = 0;
                } else if (q->depth > -3.0f) {
                    if (o->enabled) { q->depth = -65.0f; q->alpha = 0.0f; }
                    else q->active = 0;
                } else if (q->depth < -60.0f || q->depth > -5.0f) {
                    q->alpha = 0.0f;
                } else if (q->depth < -55.0f) {
                    q->alpha = 1.0f - -0.2f * (q->depth - -55.0f);
                } else if (q->depth > -10.0f) {
                    q->alpha = 1.0f - -0.2f * (-10.0f - q->depth);
                } else {
                    q->alpha = 1.0f;
                }
                if (q->y > 1.0f) q->active = 0;
            }
        }
    }
}

void clWCSnow::Update() {
    clWCSnow *o = this;
    int i;
    ViewParticle *p;
    unsigned char wasEnabled;
    void *scene;
    float motion = 0.0f;
    wasEnabled = o->enabled;
    scene = GetCourseScene3D();
    if (scene == 0) return;
    if (o->reset) {
        CObj_LoadProjMatrix(scene, &o->position);
        o->reset = 0;
    } else {
        Vec3f oldPosition;
        Vec3f eye;
        Vec3f delta;
        Vec3f direction;
        o->enabled = fn_80123480(o->table, &o->position);
        oldPosition.x = o->position.x;
        oldPosition.y = o->position.y;
        oldPosition.z = o->position.z;
        CObj_LoadProjMatrix(scene, &o->position);
        CObj_ApplyScissor(scene, &eye);
        Vec3_Subtract(&o->position, &oldPosition, &delta);
        Vec3_Subtract(&eye, &o->position, &direction);
        if (delta.x != 0.0f || delta.y != 0.0f || delta.z != 0.0f) {
            Vec3_Normalize(&direction, &direction);
            motion = Vec3_Dot(&delta, &direction);
            if (motion > 0.0f) {
                if (o->enabled) motion *= 0.05f;
                else motion *= 0.3f;
            }
        }
    }
    if (o->enabled) {
        if (!wasEnabled) {
            o->randomX = 0;
            o->randomY = 0;
            o->randomParam = 0;
            o->randomDelay = 0;
            for (i = 0; i < 25; i++) {
                p = FindFree(o);
                if (p == 0) break;
                p->active = 1;
                p->x = RandomX(o, 0.0f, 1.0f);
                p->y = RandomY(o, 0.0f, 1.0f);
                p->depth = RandomParam(o, -65.0f, -60.0f);
                p->alpha = 0.0f;
                p->speed = RandomParam(o, 0.003f, 0.008f);
                p->amplitude = RandomParam(o, 0.001f, 0.003f);
                p->angle = RandomParam(o, 0.0f, 360.0f);
                p->angularSpeed = RandomParam(o, 4.0f, 8.0f);
            }
            o->delay = 0;
        } else if (o->delay != 0) {
            o->delay--;
        } else {
            p = FindFree(o);
            if (p != 0) {
                p->active = 1;
                p->x = RandomX(o, 0.0f, 1.0f);
                p->y = 0.0f;
                p->depth = RandomParam(o, -60.0f, -10.0f);
                p->alpha = 0.0f;
                p->speed = RandomParam(o, 0.003f, 0.008f);
                p->amplitude = RandomParam(o, 0.001f, 0.003f);
                p->angle = RandomParam(o, 0.0f, 360.0f);
                p->angularSpeed = RandomParam(o, 4.0f, 8.0f);
                o->delay = (int)RandomDelay(o, 3.0f, 7.0f);
            }
        }
    }
    UpdateParticles(o, motion);
}
void clWCSnow::Draw() {
    clWCSnow *o = this;
    ViewParticle *p;
    void *scene;
    int i;
    Mtx *view;
    float width;
    float height;
    scene = GetCourseScene3D();
    if (scene != 0) {
        view = CObj_GetProjMatrix_Cached(scene);
        float angle;
        float aspect;
        Vec3f pos;
        Scene3D_GetCameraPos(scene, &angle, &aspect);
        height = tan(0.5f * (0.01745329238474369f * angle));
        width = height * aspect;
        GXChannel ch(Archive_GetRootJObj(o->model), HSD_JObjGetDObj(Archive_GetRootJObj(o->model)), 0x40000000, 1);
        Mtx m;
        for (i = 0; i < 50; i++) {
            p = &o->particles[i];
            if (p->active != 0 && 0.0f != p->alpha) {
                float y = -p->depth * height;
                float x = p->depth * width;
                pos.x = p->x * (-x - x) + x;
                pos.y = p->y * (-y - y) + y;
                pos.z = p->depth;
                PSMTXMultVec(*view, &pos, &pos);
                PSMTXScale(m, 0.1f, 0.1f, 0.1f);
                PSMTXConcat(m, *view, m);
                float z, py, px;
                px = pos.x; py = pos.y; z = pos.z;
                m[0][3] = px; m[1][3] = py; m[2][3] = z;
                Object_SetColorAlphaOnly(o->model, 0, p->alpha);
                GXChannel_PushTransform(&ch, m);
            }
        }
    }
}
