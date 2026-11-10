/* --- owned .rodata 0x802EDF20..0x802EDFD8 (tools/own_data.py) --- */
#pragma force_active on
extern "C" const char clItemBox_Ctor_GroundSnap_rodata_802EDF20[184] = { 99, 108, 73, 116, 101, 109, 66, 111, 120, 58, 58, 115, 101, 116, 117, 112, 58, 58, 99, 108, 71, 114, 111, 117, 110, 100, 67, 111, 108, 108, 58, 58, 99, 104, 107, 80, 111, 105, 110, 116, 32, 110, 111, 32, 103, 114, 111, 117, 110, 100, 32, 115, 101, 97, 114, 99, 104, 10, 0, 0, 105, 116, 101, 109, 95, 98, 111, 120, 46, 100, 97, 116, 0, 0, 0, 0, 105, 116, 101, 109, 95, 98, 111, 120, 95, 104, 97, 104, 101, 110, 95, 110, 117, 108, 108, 49, 95, 106, 111, 105, 110, 116, 0, 0, 105, 116, 101, 109, 95, 98, 111, 120, 95, 98, 95, 98, 111, 120, 95, 106, 111, 105, 110, 116, 0, 0, 0, 0, 105, 116, 101, 109, 95, 98, 111, 120, 95, 97, 95, 98, 111, 120, 95, 106, 111, 105, 110, 116, 0, 0, 0, 0, 105, 116, 101, 109, 95, 98, 111, 120, 95, 105, 116, 101, 109, 95, 98, 111, 120, 95, 110, 117, 108, 108, 95, 106, 111, 105, 110, 116, 0, 0, 0, 0 };
#pragma force_active reset
extern "C" /*
 * clItemBox: item box objects and the manager's assets, 0x8005EA94..0x8005F5CC.
 * The parts below were separate split TUs. The .data at 0x803F9C60 holds the
 * compiler's member-function-pointer constants (&clItemBox::PopOut, ...): two
 * from the constructors, four from the step table initializer, which the
 * __sinit (clItemBoxManager_InitStateTable) copies into clItemBox_data_803F9CA8.
 * Built with -inline deferred, which emits functions in reverse source order,
 * so the source runs from the asset functions down to TransitionToDebris.
 * The PMF temporaries are created at parse time, which puts the GroundSnap
 * constant (0x803F9C60) before the XYZ one (0x803F9C6C), as in the target.
 */
void *operator new(unsigned long);
void operator delete(void *);

extern "C" {
extern const float lbl_806D29A8;
void DebugPrintf(const char *, ...);
}

class GXChannel {
public:
    GXChannel(void *jobj, void *texObj, int a, int b);
    unsigned char data[0x14];
};

/* Step functions: clItemBox_StepFn_PopOut, clItemBox_StepFn_Bobbing,
 * fn_8005E7E4 and fn_8005E794 (renamed in extab_user_renames.json). */
struct clItemBox {
    int PopOut();
    int Bobbing();
    int Debris();
    int Idle();
};
typedef int (clItemBox::*clItemBoxStep)();

extern "C" clItemBoxStep clItemBox_data_803F9CA8[4];

/*
 * clItemBoxManager channel binding and asset lifetime, 0x8005F194..0x8005F53C.
 */


#include "game/types/Normal3D.h"


extern "C" {
extern int clItemBox_data_806CEEA0;
extern GXChannel *clItemBox_bss_806D10B0;
extern GXChannel *clItemBox_bss_806D10B4;
extern GXChannel *clItemBox_bss_806D10B8;
extern Normal3D *clItemBox_bss_806D10BC;
extern void *clItemBox_bss_806D10C0;
extern void *clItemBox_bss_806D10C4;
extern Normal3D *clItemBox_bss_806D10C8;
extern void *clItemBox_bss_806D10CC;
extern char lbl_802EDEF8[];
extern char lbl_802EDF14[];

void GXChannel_Bind(GXChannel *channel);
void GXChannel_Unbind(GXChannel *channel);
void dtor_8007D9C4(GXChannel *channel, int flag);
void Object_DtorWithGXSync(void *object, int flag);
void *ResolveJointByName(void *object, const char *name);
void JObj_Hide(void *object, void *jobj, int flags);
void HSD_JObjSetFlags(void *jobj, int flags);
void *HSD_JObjGetDObj(void *jobj);

void clItemBoxManager_UnbindCurrent(void);
void clItemBoxManager_Bind(int index);
void clItemBoxManager_TeardownAssets(void);
void clItemBoxManager_LoadAssets(void);
}

static inline void clItemBoxManager_UnbindInline(void)
{
    switch (clItemBox_data_806CEEA0) {
    case 0:
        GXChannel_Unbind(clItemBox_bss_806D10B4);
        break;
    case 1:
        GXChannel_Unbind(clItemBox_bss_806D10B0);
        break;
    case 2:
        GXChannel_Unbind(clItemBox_bss_806D10B8);
        break;
    default:
        DebugPrintf(lbl_802EDF14);
        break;
    }
    clItemBox_data_806CEEA0 = -1;
}

void clItemBoxManager_LoadAssets(void)
{
    char *strings = lbl_802EDEF8;

    if (clItemBox_bss_806D10BC == 0) {
        clItemBox_bss_806D10BC = new Normal3D(strings + 0x64, 1);
        JObj_Hide(clItemBox_bss_806D10BC, ResolveJointByName(clItemBox_bss_806D10BC, strings + 0x74), 0x10);
        clItemBox_bss_806D10C0 = ResolveJointByName(clItemBox_bss_806D10BC, strings + 0x90);
        clItemBox_bss_806D10C4 = ResolveJointByName(clItemBox_bss_806D10BC, strings + 0xA8);
        HSD_JObjSetFlags(clItemBox_bss_806D10C4, 0x400);
    }
    if (clItemBox_bss_806D10C8 == 0) {
        clItemBox_bss_806D10C8 = new Normal3D(strings + 0x64, 0);
        JObj_Hide(clItemBox_bss_806D10C8, ResolveJointByName(clItemBox_bss_806D10C8, strings + 0xC0), 0x10);
        clItemBox_bss_806D10CC = ResolveJointByName(clItemBox_bss_806D10C8, strings + 0x74);
    }
    clItemBox_bss_806D10B0 = new GXChannel(clItemBox_bss_806D10C0, HSD_JObjGetDObj(clItemBox_bss_806D10C0), 1, 0);
    clItemBox_bss_806D10B4 = new GXChannel(clItemBox_bss_806D10C4, HSD_JObjGetDObj(clItemBox_bss_806D10C4), 1, 0);
    clItemBox_bss_806D10B8 = new GXChannel(clItemBox_bss_806D10CC, HSD_JObjGetDObj(clItemBox_bss_806D10CC), 1, 0);
}

void clItemBoxManager_TeardownAssets(void)
{
    dtor_8007D9C4(clItemBox_bss_806D10B0, 1);
    clItemBox_bss_806D10B0 = 0;
    dtor_8007D9C4(clItemBox_bss_806D10B4, 1);
    clItemBox_bss_806D10B4 = 0;
    dtor_8007D9C4(clItemBox_bss_806D10B8, 1);
    clItemBox_bss_806D10B8 = 0;
    Object_DtorWithGXSync(clItemBox_bss_806D10BC, 1);
    clItemBox_bss_806D10BC = 0;
    clItemBox_bss_806D10C0 = 0;
    clItemBox_bss_806D10C4 = 0;
    Object_DtorWithGXSync(clItemBox_bss_806D10C8, 1);
    clItemBox_bss_806D10C8 = 0;
    clItemBox_bss_806D10CC = 0;
}

void clItemBoxManager_Bind(int index)
{
    if (clItemBox_data_806CEEA0 != -1) {
        DebugPrintf(lbl_802EDEF8);
        clItemBoxManager_UnbindInline();
    }
    switch (index) {
    case 0:
        GXChannel_Bind(clItemBox_bss_806D10B4);
        break;
    case 1:
        GXChannel_Bind(clItemBox_bss_806D10B0);
        break;
    case 2:
        GXChannel_Bind(clItemBox_bss_806D10B8);
        break;
    default:
        DebugPrintf(lbl_802EDF14);
        break;
    }
    clItemBox_data_806CEEA0 = index;
}

void clItemBoxManager_UnbindCurrent(void)
{
    clItemBoxManager_UnbindInline();
}

/* Observed constructor layout only; not a complete runtime class definition.
 * The 12-byte step value is a CW member-function pointer, not a word array.
 * External member destructors and array element constructors are bridged in
 * this TU's extab_user_renames entry. All EH is compiler-generated.
 */
extern "C" {
}

struct GroundPosition {
    float x, y, z;
    GroundPosition(float a, float b, float c) : x(a), y(b), z(c) {}
    ~GroundPosition();
};
extern "C" unsigned char Terrain_GetGroundHeight(GroundPosition *, float *, GroundPosition *, unsigned int *);
struct GroundParticle {
    char opaque[0x1C];
    float lifetime;
    char tail[0xC];
    GroundParticle();
    ~GroundParticle();
};
struct GroundDebris {
    unsigned char active;
    GroundParticle particles[15];
    GroundDebris() {
        active = 0;
        for (int i = 0; i < 15; ++i) particles[i].lifetime = lbl_806D29A8;
    }
};
struct GroundMotion {
    unsigned int flag;
    float x, y, z;
    GroundMotion() : flag(0), x(lbl_806D29A8), y(lbl_806D29A8), z(lbl_806D29A8) {}
};
struct GroundItemBox {
    float height;
    GroundDebris *debris;
    GroundPosition position;
    float timer;
    clItemBoxStep step;
    GroundMotion motion;
    GroundItemBox(float x, float z);
};
typedef char GroundParticleSize[(sizeof(GroundParticle) == 0x2C) ? 1 : -1];
typedef char GroundDebrisSize[(sizeof(GroundDebris) == 0x298) ? 1 : -1];
typedef char GroundItemBoxSize[(sizeof(GroundItemBox) == 0x34) ? 1 : -1];

GroundItemBox::GroundItemBox(float x, float z)
    : height(lbl_806D29A8), debris(0), position(x, lbl_806D29A8, z),
      timer(lbl_806D29A8), step(&clItemBox::PopOut)
{
    motion.flag = 0;
    if (!Terrain_GetGroundHeight(&position, &position.y, 0, 0)) DebugPrintf(clItemBox_Ctor_GroundSnap_rodata_802EDF20);
    height = position.y;
    if (!debris) debris = new GroundDebris;
}
/* Observed single-constructor lifetime views; no shared class definitions. */



struct ItemBoxVec {
    float x, y, z;
    ItemBoxVec(float a, float b, float c) : x(a), y(b), z(c) {}
    ~ItemBoxVec();
};

struct BoxVelocity {
    float x, y, z;
    BoxVelocity(float a, float b, float c) : x(a), y(b), z(c) {}
};

struct BoxParticle {
    unsigned char opaque00[0x1c];
    float age;
    unsigned char opaque20[0x0c];
    BoxParticle();
    ~BoxParticle();
};

struct BoxDebris {
    unsigned char active;
    unsigned char pad01[3];
    BoxParticle particles[15];
    BoxDebris()
    {
        active = 0;
        for (int i = 0; i < 15; ++i) {
            particles[i].age = lbl_806D29A8;
        }
    }
};

struct ItemBoxXYZ {
    float height;
    BoxDebris *debris;
    ItemBoxVec position;
    float spin;
    clItemBoxStep step;
    int state;
    BoxVelocity velocity;
    ItemBoxXYZ(float, float, float);
};

ItemBoxXYZ::ItemBoxXYZ(float x, float y, float z)
    : height(lbl_806D29A8), debris(0), position(x, y, z),
      spin(lbl_806D29A8), step(&clItemBox::PopOut), state(0),
      velocity(lbl_806D29A8, lbl_806D29A8, lbl_806D29A8)
{
    state = 0;
    height = position.y;
    if (debris == 0) {
        debris = new BoxDebris;
    }
}

namespace itembox_dtor {
extern "C" {
/* clItemBox destructor: free the debris particle array, then the box
 * itself when called as a deleting destructor. */
typedef struct clItemBoxDebris {
    int count;                 /* 0x00 */
    unsigned char items[0x294]; /* 0x04: 15 particles of 0x2c */
} clItemBoxDebris;

typedef struct clItemBox {
    unsigned char pad00[0x4];
    clItemBoxDebris *debris; /* 0x04 */
} clItemBox;

extern void clItemBoxResponder_DebrisParticle_Dtor(void *self, short flag);
extern void __destroy_arr(void *arr, void *dtor, unsigned long size, unsigned long count);
extern void MemoryManager_TimedFree(void *p);

clItemBox *clItemBox_Dtor(clItemBox *self, short flag)
{
    clItemBoxDebris *debris;

    if (self != 0) {
        debris = self->debris;
        if (debris != 0) {
            __destroy_arr(debris->items, clItemBoxResponder_DebrisParticle_Dtor, 0x2c, 0xf);
            MemoryManager_TimedFree(debris);
        }
        self->debris = 0;
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

}
}
namespace itembox_tick {
extern "C" {
/* Run the item box's current step function, then load the step function
 * for the state it returned. Returns 1 while the box is idle/visible. */

struct clItemBoxT {
    unsigned char pad00[0x18];
    clItemBoxStep step; /* 0x18 */
    int state;          /* 0x24 */
};

extern "C" int clItemBox_Tick(clItemBoxT *self)
{
    self->state = (((clItemBox *)self)->*self->step)();
    self->step = clItemBox_data_803F9CA8[self->state];
    if (self->state == 1 || self->state == 0 || self->state == 3) {
        return 1;
    }
    return 0;
}

}
}
namespace itembox_draw {
extern "C" {
/* Draw an item box: through the debris responder in channel 2, otherwise
 * as the shared box model placed, spun and faded per box, when it is on
 * screen and in front of the camera. */
typedef struct Vec {
    float x, y, z;
} Vec;

typedef struct clItemBoxResponder {
    unsigned char broken; /* 0x00 */
} clItemBoxResponder;

typedef struct clItemBox {
    unsigned char pad00[0x4];
    clItemBoxResponder *responder; /* 0x04 */
    Vec pos;                       /* 0x08 */
    float spin;                    /* 0x14 */
    unsigned char pad18[0xc];
    int state;                     /* 0x24 */
    unsigned char pad28[0x8];
    float alpha;                   /* 0x30 */
} clItemBox;


extern int clItemBox_data_806CEEA0;
extern GXChannel *clItemBox_bss_806D10B0;
extern GXChannel *clItemBox_bss_806D10B4;
extern void *clItemBox_bss_806D10BC;
extern const float lbl_806D29E0;
extern const double lbl_806D29F0;
extern const float lbl_806D2A04;
extern const float lbl_806D2A08;
extern const float lbl_806D2A0C;
extern void clItemBoxResponder_DrawDebris(clItemBoxResponder *self);
extern unsigned char fn_80137718(const Vec *pos, Vec *out, float radius);
extern void Object_SetColorAlphaOnly(void *object, int joint, float alpha);
extern void Object_SetJObjPositionXYZ(void *object, float x, float y, float z);
extern void Object_SetJObjRotationY(void *object, float y);
extern void *Object_GetJObjLocalMatrix(void *object);
extern void GXChannel_PushTransform(GXChannel *ch, void *mtx);

static inline void clItemBox_DrawModel(clItemBox *self, Vec *view)
{
    Object_SetColorAlphaOnly(clItemBox_bss_806D10BC, 0, self->alpha);
    Object_SetJObjPositionXYZ(clItemBox_bss_806D10BC, self->pos.x, lbl_806D2A0C + self->pos.y, self->pos.z);
    Object_SetJObjRotationY(clItemBox_bss_806D10BC, lbl_806D29F0 * (lbl_806D29E0 * self->spin));
    if (clItemBox_data_806CEEA0 == 0) {
        GXChannel_PushTransform(clItemBox_bss_806D10B4, Object_GetJObjLocalMatrix(clItemBox_bss_806D10BC));
    } else {
        GXChannel_PushTransform(clItemBox_bss_806D10B0, Object_GetJObjLocalMatrix(clItemBox_bss_806D10BC));
    }
}

void clItemBox_Draw(clItemBox *self)
{
    Vec view;

    if (self->state == 3) {
        return;
    }
    if (clItemBox_data_806CEEA0 == 2) {
        clItemBoxResponder_DrawDebris(self->responder);
        return;
    }
    if (self->responder->broken == 1) {
        return;
    }
    if (!fn_80137718(&self->pos, &view, lbl_806D2A04) || view.z < lbl_806D2A08) {
        return;
    }
    clItemBox_DrawModel(self, &view);
}

}
}
namespace itembox_debris {
extern "C" {
/* clItemBox_TransitionToDebris (0x8005EA94): the item box was hit.  Switch to
 * the debris step (state 2) and burst all 15 debris pieces out of the box:
 * each flies in a random direction (flipped to the hit's side), biased by
 * 1.5x the hit direction, with a random scale and spin. */

typedef struct DebrisPiece {
    float pos[3];  /* 0x00 */
    float vel[3];  /* 0x0C */
    float accel;   /* 0x18 */
    float life;    /* 0x1C */
    float scale;   /* 0x20 */
    float spinA;   /* 0x24 */
    float spinB;   /* 0x28 */
} DebrisPiece;

typedef struct DebrisSet {
    unsigned char active;
    unsigned char pad01[3];
    DebrisPiece pieces[15]; /* 0x04 */
} DebrisSet;

typedef struct clItemBox {
    unsigned char pad00[0x4];
    DebrisSet *debris;  /* 0x04 */
    float pos[3];       /* 0x08 */
    unsigned char pad14[0x18 - 0x14];
    clItemBoxStep step; /* 0x18 */
    int state;          /* 0x24 */
    unsigned char pad28[0x2C - 0x28];
    float timer;        /* 0x2C */
} clItemBox;


extern float HSD_Randf(void);
extern float Saturate_Double(float v, float lo, float hi);

static inline void DebrisSet_Burst(DebrisSet *debris, const float *pos, float dx, float dy, float dz)
{
    unsigned int i;
    float rx;
    float ry;
    float rz;

    debris->active = 1;
    for (i = 0; i < 15; i++) {
        debris->pieces[i].pos[0] = pos[0];
        debris->pieces[i].pos[1] = pos[1];
        debris->pieces[i].pos[2] = pos[2];
        rx = 6.0f * (2.0f * (HSD_Randf() - 0.5f));
        ry = 6.0f * (2.0f * (HSD_Randf() - 0.5f));
        rz = 6.0f * (2.0f * (HSD_Randf() - 0.5f));
        if (dx * rx + dy * ry + dz * rz < 0.0f) {
            rx = -rx;
            ry = -ry;
            rz = -rz;
        }
        debris->pieces[i].vel[0] = rx + 1.5f * dx;
        debris->pieces[i].vel[1] = ry + 1.5f * dy;
        debris->pieces[i].vel[2] = rz + 1.5f * dz;
        debris->pieces[i].accel = 0.75f;
        debris->pieces[i].scale = Saturate_Double(3.0f * HSD_Randf(), 0.2f, 3.0f);
        debris->pieces[i].spinA = 360.0f * HSD_Randf();
        debris->pieces[i].spinB = 360.0f * HSD_Randf();
        debris->pieces[i].life = 0.3f;
    }
}

void clItemBox_TransitionToDebris(clItemBox *self, float hx, float hy, float hz)
{
    self->state = 2;
    self->step = clItemBox_data_803F9CA8[self->state];
    self->timer = 0.0f;
    DebrisSet_Burst(self->debris, self->pos, hx, hy, hz);
}

}
}
extern "C" {
clItemBoxStep clItemBox_data_803F9CA8[4] = {
    &clItemBox::PopOut,
    &clItemBox::Bobbing,
    &clItemBox::Debris,
    &clItemBox::Idle,
};
}
