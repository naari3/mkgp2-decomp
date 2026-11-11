/* clMRAirShip: deferred generation emits these definitions in reverse order.
 * Class tables, RTTI records and name strings are compiler-generated. */
#define lbl_806D8EA8 lbl_806D92AC
#define lbl_806D8EB0 lbl_806D92B4
#include "game/types/clMRAirShip_inlines.h"
#include "game/types/clMapEffectParts.h"
extern "C" {
extern int g_courseVariantIdx;
float LUT_Sin12Bit(float);
unsigned char fn_801379F0(Vec3f *, float);
void *FUN_8003b120(unsigned long);
void Object_DtorWithGXSync(void *, int);
void MemoryManager_Free(void *);
}
struct clMRAirShip : clMapEffectParts {
    clNormal3D *object;
    AirShipPathState *paths;
    float rotation, phase, phase2;
    clMRAirShip();
    virtual ~clMRAirShip();
    virtual void Update();
    virtual void Draw();
};
struct Path186Def {
    const char *joint[4];
    Vec3f *points;
    int count;
};
static const Vec3f lbl_80377030[12] = {
    {2690.0f, 210.0f, -845.0f},
    {2196.0f, 210.0f, -1750.0f},
    {1450.0f, 240.0f, -1915.0f},
    {675.0f, 240.0f, -1500.0f},
    {11.0f, 220.0f, -990.0f},
    {-348.0f, 220.0f, -264.0f},
    {-413.0f, 220.0f, 760.0f},
    {48.0f, 220.0f, 1672.0f},
    {877.0f, 220.0f, 1783.0f},
    {1578.0f, 220.0f, 1313.0f},
    {2100.0f, 210.0f, 760.0f},
    {2657.0f, 210.0f, 12.0f},
};
static const Vec3f lbl_803770C0[9] = {
    {-500.0f, 485.0f, -3600.0f},
    {-108.0f, 485.0f, -3100.0f},
    {540.0f, 485.0f, -3000.0f},
    {1280.0f, 485.0f, -2986.0f},
    {2120.0f, 485.0f, -3150.0f},
    {2470.0f, 485.0f, -3670.0f},
    {2110.0f, 485.0f, -4340.0f},
    {1297.0f, 485.0f, -4623.0f},
    {-440.0f, 485.0f, -4200.0f},
};
static const char lbl_8037712C[14] = "MRA_red_joint";
static const char lbl_8037713C[21] = "MRA_nlight_red_joint";
static const char lbl_80377154[22] = "MRA_npera_red_l_joint";
static const char lbl_8037716C[22] = "MRA_npera_red_r_joint";
static const char lbl_80377184[16] = "MRA_green_joint";
static const char lbl_80377194[23] = "MRA_nlight_green_joint";
static const char lbl_803771AC[24] = "MRA_npera_green_l_joint";
static const char lbl_803771C4[24] = "MRA_npera_green_r_joint";
static const Path186Def lbl_803771DC[2] = {
    {{lbl_8037712C, lbl_8037713C, lbl_80377154, lbl_8037716C}, (Vec3f *)lbl_80377030, 12},
    {{lbl_80377184, lbl_80377194, lbl_803771AC, lbl_803771C4}, (Vec3f *)lbl_803770C0, 9}
};
#define lbl_80377260 " DeleteMapEffect : clMRAirShip\n"
#define lbl_80377280 " CreateMapEffect : clMRAirShip\n"
#define lbl_803772A0 "MRA_airship_A.dat"
#define lbl_803772B4 "MRA_airship_B.dat"
#define lbl_803772C8 "MRA_airship_C.dat"
static inline Vec3f *CyclicPoint(AirShipPathState *path, int count, int index) {
    if (index >= count) index -= count;
    return &path->points[index];
}
static inline void CopyPoint(Vec3f *dst, const Vec3f *src) {
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}
clMRAirShip::clMRAirShip() {
    const Path186Def *def;
    int offset;
    int i;
    DebugPrintf(lbl_80377280);
    object = 0;
    paths = 0;
    rotation = 0.0f;
    phase = 0.0f;
    phase2 = 0.0f;
    const char *name = 0;
    switch (g_courseVariantIdx) {
    case 0: name = lbl_803772A0; break;
    case 1: name = lbl_803772B4; break;
    case 2: name = lbl_803772C8; break;
    }
    if (!name) return;
    object = new clNormal3D(name, 0);
    paths = (AirShipPathState *)FUN_8003b120(0xa8);
    def = lbl_803771DC;
    for (i = 0, offset = 0; i < 2; i++, offset += sizeof(AirShipPathState), def++) {
        (*(AirShipPathState *)((char *)paths + offset)).joint[0] = ResolveJointByName(object, def->joint[0]);
        (*(AirShipPathState *)((char *)paths + offset)).joint[1] = ResolveJointByName(object, def->joint[1]);
        (*(AirShipPathState *)((char *)paths + offset)).joint[2] = ResolveJointByName(object, def->joint[2]);
        (*(AirShipPathState *)((char *)paths + offset)).joint[3] = ResolveJointByName(object, def->joint[3]);
        (*(AirShipPathState *)((char *)paths + offset)).points = def->points;
        (*(AirShipPathState *)((char *)paths + offset)).count = def->count;
        (*(AirShipPathState *)((char *)paths + offset)).index = 0;
        (*(AirShipPathState *)((char *)paths + offset)).time = 0.0f;
        AirShipPathState *p = &(*(AirShipPathState *)((char *)paths + offset));
        for (int control = 0; control < 3; control++) {
            Vec3f *v = CyclicPoint(p, p->count, p->index + control);
            CopyPoint(&p->control[control], v);
        }
        p->control[0].x = 0.5f * (p->control[0].x+p->control[1].x);
        p->control[0].y = 0.5f * (p->control[0].y+p->control[1].y);
        p->control[0].z = 0.5f * (p->control[0].z+p->control[1].z);
        p->control[2].x = 0.5f * (p->control[1].x+p->control[2].x);
        p->control[2].y = 0.5f * (p->control[1].y+p->control[2].y);
        p->control[2].z = 0.5f * (p->control[1].z+p->control[2].z);
        CopyPoint(&(*(AirShipPathState *)((char *)paths + offset)).position, &(*(AirShipPathState *)((char *)paths + offset)).control[0]);
        (*(AirShipPathState *)((char *)paths + offset)).yaw = 0.0f;
    }
}

clMRAirShip::~clMRAirShip() {
    if (object) Object_DtorWithGXSync(object, 1);
    if (paths) MemoryManager_Free(paths);
    DebugPrintf(lbl_80377260);
}
void clMRAirShip::Update() {
    int i;
    AirShipPathState *p;
    if (object == 0 || paths == 0) return;
    for (i = 0; i < 2; i++) {
        p = &paths[i];
        p->time += 0.0033333334140479565f;
        if (p->time > 1.0f) {
            p->time -= 1.0f;
            p->index++;
            if (p->index >= p->count) p->index = 0;
            { Vec3f *v = CyclicPoint(p, p->count, p->index); p->control[0].x = v->x; p->control[0].y = v->y; p->control[0].z = v->z; }
            { Vec3f *v = CyclicPoint(p, p->count, p->index+1); p->control[1].x = v->x; p->control[1].y = v->y; p->control[1].z = v->z; }
            { Vec3f *v = CyclicPoint(p, p->count, p->index+2); p->control[2].x = v->x; p->control[2].y = v->y; p->control[2].z = v->z; }
            p->control[0].x = 0.5f * (p->control[0].x + p->control[1].x);
            p->control[0].y = 0.5f * (p->control[0].y + p->control[1].y);
            p->control[0].z = 0.5f * (p->control[0].z + p->control[1].z);
            p->control[2].x = 0.5f * (p->control[1].x + p->control[2].x);
            p->control[2].y = 0.5f * (p->control[1].y + p->control[2].y);
            p->control[2].z = 0.5f * (p->control[1].z + p->control[2].z);
        }
        Vec3f old = p->position;
        Vec3f delta;
        fn_80181EA4(&p->control[0], &p->control[1], &p->control[2], &p->position, p->time);
        Vec3_Subtract(&p->position, &old, &delta);
        p->yaw = (float)atan2(delta.x, delta.z);
    }
    rotation += 0.2617993950843811f;
    if (rotation >= 6.2831854820251465f) rotation -= 6.2831854820251465f;
    phase += 0.002f;
    if (phase >= 1.0f) phase -= 1.0f;
    phase2 += 0.0002f;
    if (phase2 >= 1.0f) phase2 -= 1.0f;
}

static inline void SwingAirShipPathState(AirShipPathState *p, float swing, float turn) {
    HSD_JObj *joint = p->joint[1];
    if (joint) {
        HSD_JObjSetRotationX(joint, swing);
        HSD_JObjSetRotationY((HSD_JObj *)p->joint[1], turn);
    }
}
void clMRAirShip::Draw() {
    unsigned char visible[2];
    AirShipPathState *p;
    const AirShipPathState *renderPath;
    int i;
    HSD_JObj *joint;
    Vec3f probe;
    float swing, turn;
    if (object == 0 || paths == 0) return;
    swing = 1.0471975803375244f * LUT_Sin12Bit(360.0f * phase);
    turn = 6.2831854820251465f * phase2;
    for (i = 0; i < 2; i++) {
        p = &paths[i];
        probe.x = p->position.x;
        probe.y = 150.0f + p->position.y;
        probe.z = p->position.z;
        if (fn_801379F0(&probe, 400.0f)) {
            SwingAirShipPathState(p, swing, turn);
            joint = p->joint[2];
            if (joint) HSD_JObjSetRotationZ(joint, rotation);
            joint = p->joint[3];
            if (joint) HSD_JObjSetRotationZ(joint, rotation);
            visible[i] = 1;
        } else visible[i] = 0;
    }
    for (i = 0; i < 2; i++) {
        if (visible[i]) {
            p = &paths[i];
            joint = p->joint[0];
            if (joint) {
                HSD_JObjSetTranslate(joint, &p->position);
                HSD_JObjSetRotationY((HSD_JObj *)p->joint[0], p->yaw);
                HSD_JObjDispAll((HSD_JObj *)p->joint[0], 0, 1, 0);
            }
        }
    }
    for (i = 0; i < 2; i++) {
        if (visible[i]) {
            renderPath = &paths[i];
            joint = renderPath->joint[0];
            if (joint) {
                HSD_JObjSetTranslate(joint, &renderPath->position);
                HSD_JObjSetRotationY((HSD_JObj *)renderPath->joint[0], renderPath->yaw);
                HSD_JObjDispAll((HSD_JObj *)renderPath->joint[0], 0, 6, 0);
            }
        }
    }
}
