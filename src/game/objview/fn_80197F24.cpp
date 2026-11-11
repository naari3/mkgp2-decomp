/* clWCYukinko: deferred definitions follow reverse target address order.
 * The compiler owns the class vtable, base list, RTTI and type names. */
#include "game/types/size_t.h"
#include "game/types/HSD_JObj.h"
#include "game/types/Vec3f.h"
#include "game/types/clNormal3D.h"
#include "game/types/clMapEffectParts.h"
void *operator new(size_t);
void operator delete(void *) throw();
typedef float Mtx[3][4];
struct HSD_DObj;
struct GXChannel {
    GXChannel(HSD_JObj *, HSD_DObj *, unsigned int, int);
    ~GXChannel();
    unsigned char storage[0x14];
};
struct Entry {
    clNormal3D *model;
    HSD_JObj *scrollJoint, *sourceJoint;
    int delay;
};
struct Particle {
    float scale, growth, alpha;
    Vec3f velocity, pos, xAxis, yAxis, zAxis;
};
struct Obj987Position { Vec3f pos; float yaw; };
struct clWCYukinko : clMapEffectParts {
    Entry *items;
    int count;
    clNormal3D *model;
    Particle *particles;
    int delayIndex, scaleIndex, velocityIndex;
    clWCYukinko();
    virtual ~clWCYukinko();
    virtual void Update();
    virtual void Draw();
};
typedef clWCYukinko Owner;
extern "C" {
void *GetCourseScene3D(void);
Mtx *CObj_GetProjMatrix_Cached(void *);
HSD_JObj *Archive_GetRootJObj(clNormal3D *);
HSD_DObj *HSD_JObjGetDObj(HSD_JObj *);
void PSMTXScale(Mtx, float, float, float);
void PSMTXConcat(const Mtx, const Mtx, Mtx);
void Object_SetColorAlphaOnly(clNormal3D *, int, float);
void GXChannel_PushTransform(GXChannel *, Mtx);
void Object_GetJObjPositionVec(clNormal3D *, Vec3f *);
void clNormal3D_Exec(clNormal3D *);
void Object_RenderJObjTree(clNormal3D *, int);
unsigned char fn_801379F0(Vec3f *, float);
unsigned char fn_80137718(Vec3f *, Vec3f *, float);
void DebugPrintf(const char *, ...);
void Object_DtorWithGXSync(void *, int);
void MemoryManager_Free(void *);
void fn_8016C394(int);
void clNormal3D_SetScale(clNormal3D *, int, float, float, float, float);
HSD_JObj *ResolveJointByName(clNormal3D *, const char *);
extern void CObj_LoadProjMatrix(void *, Vec3f *);
extern void Vec3_Subtract(const Vec3f *, const Vec3f *, Vec3f *);
extern float PSVECSquareMag(const Vec3f *);
extern void fn_80182B50(HSD_JObj *, float, float);
extern void HSD_JObjSetupMatrixSub(HSD_JObj *);
extern void __assert(char *, int, char *);
extern unsigned char fn_8016C360(int);
extern unsigned char SoundMgr_PlaySE(int);
extern void fn_8016C288(int, Vec3f *);
extern float lbl_80495A94[], lbl_80495994[];
extern const float lbl_806D9654, lbl_806D9658, lbl_806D965C, lbl_806D9660, lbl_806D9664;
extern const float lbl_806D9678, lbl_806D967C, lbl_806D9680, lbl_806D9684, lbl_806D9688, lbl_806D968C;
extern char lbl_806D9668[7], lbl_806D9670[5];
}
// Original shared pool: short/long placements, origin, type names and resources.
extern "C" const Obj987Position lbl_8037DB78[2] = {
    {{973.456787109375f, 447.79998779296875f, -2931.159912109375f}, -0.5060005784034729f},
    {{1366.4639892578125f, 447.79998779296875f, -2712.1298828125f}, -0.5060005784034729f},
};
extern "C" const Obj987Position lbl_8037DB98[4] = {
    {{928.9713134765625f, 463.651611328125f, -2973.179931640625f}, -0.5152333974838257f},
    {{2680.0f, 295.0f, -3675.0f}, -9.155996322631836f},
    {{3530.0f, 190.0f, -3650.0f}, -9.805992126464844f},
    {{3750.0f, 63.0f, -2830.179931640625f}, 0.9075711965560913f},
};
// Shared origin used by the nearest-particle calculation in fn_801980C8.
extern "C" const Vec3f lbl_8037DBD8 = {0.0f, 0.0f, 0.0f};


#define lbl_8037DC04 " DeleteMapEffect : clWCYukinko\n"
#define lbl_8037DC24 " CreateMapEffect : clWCYukinko\n"
#define lbl_8037DC44 "map_chara_yukinko_short_A.dat"
#define lbl_8037DC64 "map_chara_yukinko_short_B.dat"
#define lbl_8037DC84 "map_chara_yukinko_short_C.dat"
#define lbl_8037DCA4 "map_chara_yukinko_long_A.dat"
#define lbl_8037DCC4 "map_chara_yukinko_long_B.dat"
#define lbl_8037DCE4 "map_chara_yukinko_long_C.dat"
#define lbl_8037DD04 "map_chara_uv_effect_joint"
#define lbl_8037DD20 "map_chara_mouth_joint"
#define lbl_8037DD38 "ef_snowmark.dat"
extern "C" {
extern int g_longRoundFlag, g_courseVariantIdx;
void *FUN_8003b120(unsigned long);
void Object_SetJObjPositionVec(clNormal3D *, const Vec3f *);
void Object_SetJObjRotationY(clNormal3D *, float);
}

clWCYukinko::clWCYukinko() {
    int i;
    const char *resource;
    const Obj987Position *positions;
    DebugPrintf(lbl_8037DC24);
    items = 0;
    count = 0;
    model = 0;
    particles = 0;
    delayIndex = 0;
    scaleIndex = 0;
    velocityIndex = 0;
    resource = 0;
    if (g_longRoundFlag == 0) {
        switch (g_courseVariantIdx) {
        case 0: resource = lbl_8037DC44; break;
        case 1: resource = lbl_8037DC64; break;
        case 2: resource = lbl_8037DC84; break;
        }
        positions = lbl_8037DB78;
        count = 2;
    } else {
        switch (g_courseVariantIdx) {
        case 0: resource = lbl_8037DCA4; break;
        case 1: resource = lbl_8037DCC4; break;
        case 2: resource = lbl_8037DCE4; break;
        }
        positions = lbl_8037DB98;
        count = 4;
    }
    if (resource == 0 || positions == 0 || count <= 0) return;
    items = (Entry *)FUN_8003b120(count * sizeof(Entry));
    for (i = 0; i < count; i++) {
        items[i].model = new clNormal3D(resource, 0);
        clNormal3D_SetScale(items[i].model, 0, 0.0f, 1.0f, 0.0f, 0.0f);
        Object_SetJObjPositionVec(items[i].model, &positions[i].pos);
        Object_SetJObjRotationY(items[i].model, positions[i].yaw);
        items[i].scrollJoint = ResolveJointByName(items[i].model, lbl_8037DD04);
        items[i].sourceJoint = ResolveJointByName(items[i].model, lbl_8037DD20);
        items[i].delay = 0;
    }
    model = new clNormal3D(lbl_8037DD38, 1);
    particles = (Particle *)FUN_8003b120(60 * sizeof(Particle));
    for (i = 0; i < 60; i++) particles[i].alpha = -1.0f;
}

clWCYukinko::~clWCYukinko() {
    int i;
    if (count != 0) {
        for (i = 0; i < count; i++) {
            Object_DtorWithGXSync(items[i].model, 1);
        }
        MemoryManager_Free(items);
    }
    Object_DtorWithGXSync(model, 1);
    MemoryManager_Free(particles);
    fn_8016C394(0x2d);
    DebugPrintf(lbl_8037DC04);
}

static inline float NextScale(Owner *o) {
    int i;
    if (o->scaleIndex >= 48) o->scaleIndex = 0;
    i = o->scaleIndex++;
    return lbl_80495A94[i];
}
static inline float NextVelocity(Owner *o) {
    int i;
    if (o->velocityIndex >= 64) o->velocityIndex = 0;
    i = o->velocityIndex++;
    return lbl_80495994[i];
}
static inline float NextDelay(Owner *o) {
    int i;
    if (o->delayIndex >= 64) o->delayIndex = 0;
    i = o->delayIndex++;
    return lbl_80495994[i];
}
static inline Particle *FindFree(Owner *o) {
    int i;
    for (i = 0; i < 60; i++) {
        if (lbl_806D9654 == o->particles[i].alpha) return &o->particles[i];
    }
    return 0;
}
static inline unsigned char MatrixDirty(HSD_JObj *j) {
    unsigned char dirty;
    if (j == 0) __assert(lbl_806D9668, 0x25D, lbl_806D9670);
    dirty = 0;
    if (!(j->flags & 0x800000) && (j->flags & 0x40)) dirty = 1;
    return dirty;
}
static inline void Spawn(Owner *o, Particle *p, HSD_JObj *j) {
    if (j == 0) __assert(lbl_806D9668, 0x47C, lbl_806D9670);
    if (j != 0 && MatrixDirty(j)) HSD_JObjSetupMatrixSub(j);
    p->pos.x = j->mtx[0][3];
    p->pos.y = j->mtx[1][3];
    p->pos.z = j->mtx[2][3];
    p->xAxis.x = j->mtx[0][0];
    p->xAxis.y = j->mtx[1][0];
    p->xAxis.z = j->mtx[2][0];
    p->yAxis.x = j->mtx[0][1];
    p->yAxis.y = j->mtx[1][1];
    p->yAxis.z = j->mtx[2][1];
    p->zAxis.x = -j->mtx[0][2];
    p->zAxis.y = j->mtx[1][2];
    p->zAxis.z = -j->mtx[2][2];
    p->scale = lbl_806D9678 + NextScale(o);
    {
        float r = NextScale(o);
        float k = lbl_806D967C;
        p->growth = k * r + k;
    }
    p->alpha = lbl_806D9678;
    p->velocity.x = lbl_806D9680 * NextVelocity(o) - lbl_806D9684;
    p->velocity.y = lbl_806D9684 * NextVelocity(o) - lbl_806D9678;
    p->velocity.z = lbl_806D9688;
}
static inline void UpdateParticle(Particle *p) {
            if (lbl_806D9654 != p->alpha) {
                p->pos.x += p->xAxis.x * p->velocity.x + p->yAxis.x * p->velocity.y + p->zAxis.x * p->velocity.z;
                p->pos.y += p->xAxis.y * p->velocity.x + p->yAxis.y * p->velocity.y + p->zAxis.y * p->velocity.z;
                p->pos.z += p->xAxis.z * p->velocity.x + p->yAxis.z * p->velocity.y + p->zAxis.z * p->velocity.z;
                p->scale += p->growth;
                p->velocity.z -= lbl_806D968C;
                if (p->velocity.z < lbl_806D9658) {
                    p->alpha = lbl_806D968C * p->velocity.z;
                    if (p->velocity.z < lbl_806D965C) p->alpha = lbl_806D9654;
                }
            }
}
#pragma push
#pragma opt_dead_assignments off
void clWCYukinko::Update() {
    Owner *o = this;
    Particle *p;
    int i;
    Entry *entry;
    Vec3f eye, pos, diff;
    float nearestDist, distance;
    if (o->count != 0) {
        CObj_LoadProjMatrix(GetCourseScene3D(), &eye);
        nearestDist = lbl_806D9654;
        Vec3f nearest = lbl_8037DBD8;
        for (i = 0; i < o->count; i++) {
            entry = &o->items[i];
            Object_GetJObjPositionVec(entry->model, &pos);
            Vec3_Subtract(&eye, &pos, &diff);
            distance = PSVECSquareMag(&diff);
            if (nearestDist < lbl_806D965C || distance < nearestDist) {
                nearestDist = distance;
                nearest.x = pos.x; nearest.y = pos.y; nearest.z = pos.z;
            }
            if (entry->scrollJoint != 0) fn_80182B50(entry->scrollJoint, lbl_806D965C, lbl_806D9660);
            if (entry->delay != 0) {
                entry->delay--;
            } else {
                if (entry->sourceJoint != 0 && distance < lbl_806D9664) {
                    p = FindFree(o);
                    if (p != 0) Spawn(o, p, entry->sourceJoint);
                }
                entry->delay = (int)(lbl_806D9658 * NextDelay(o)) + 2;
            }
        }
        if (!fn_8016C360(0x2D)) SoundMgr_PlaySE(0x2D);
        fn_8016C288(0x2D, &nearest);
        for (i = 0; i < 60; i++) {
            UpdateParticle(&o->particles[i]);
        }
    }
}
#pragma pop

extern "C" {
extern const float lbl_806D9648, lbl_806D964C, lbl_806D9650, lbl_806D9654, lbl_806D9658;
}
static inline void DrawParticles(Owner *o, Mtx *view, int& i) {
    Particle *p;
        GXChannel ch(Archive_GetRootJObj(o->model), HSD_JObjGetDObj(Archive_GetRootJObj(o->model)), 0x40000000, 1);
        Mtx m;
        for (i = 0; i < 60; i++) {
            p = &o->particles[i];
            if (lbl_806D9654 != p->alpha && fn_801379F0(&p->pos, lbl_806D9658)) {
                PSMTXScale(m, p->scale, p->scale, p->scale);
                PSMTXConcat(m, *view, m);
                m[0][3] = p->pos.x;
                m[1][3] = p->pos.y;
                m[2][3] = p->pos.z;
                Object_SetColorAlphaOnly(o->model, 0, p->alpha);
                GXChannel_PushTransform(&ch, m);
            }
        }
}

void clWCYukinko::Draw() {
    Owner *o = this;
    int i;
    Mtx *view;
    Entry *items;
    Vec3f pos;
    Vec3f projected;
    if (o->count != 0) {
        view = CObj_GetProjMatrix_Cached(GetCourseScene3D());
        for (i = 0; i < o->count; i++) {
            items = o->items;
            Object_GetJObjPositionVec(items[i].model, &pos);
            pos.y += lbl_806D9648;
            if (fn_80137718(&pos, &projected, lbl_806D964C)) {
                if (projected.z > lbl_806D9650) {
                    clNormal3D_Exec(items[i].model);
                }
                Object_RenderJObjTree(items[i].model, 7);
            }
        }
        DrawParticles(o, view, i);
    }
}
