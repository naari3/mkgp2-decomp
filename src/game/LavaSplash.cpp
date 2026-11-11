/*
 * 0x80170EE0..0x80171754: clLavaSplash, a set of 30 lava splash bursts of 10
 * sparks each: draw, update (each burst scales in, holds and fades by its timer
 * while sparks fall), spawn, destructor and constructor. The TU owns
 * .rodata 0x8036E728..0x8036E840 (class names and resource names), which
 * CW addresses through one hoisted base. Real C++ ctor for its EH actions;
 * mangled names are bridged in tools/extab_user_renames.json.
 */

#include "game/types/Vec3f.h"

struct Spark {
    Vec3f pos;
    Vec3f vel;
    float drag;
    float gravity;
};

struct SparkBurst {
    unsigned char active;
    char pad01[0x3];
    float t;
    Vec3f pos;
    float size;
    float scale;
    unsigned char visible;
    char pad1D[0x3];
    Spark sparks[10];
};

#include "game/types/clNormal3D.h"

typedef float Mtx[3][4];

#include "game/types/GXChannel.h"

#include "game/types/clMapEffectParts.h"

struct clLavaSplash : clMapEffectParts {
    clNormal3D *modelA;
    clNormal3D *modelB;
    clNormal3D *modelC;
    void *joints[8];
    SparkBurst bursts[30];
    int randIdx;

    clLavaSplash();
    virtual ~clLavaSplash();
    virtual void Update();
    virtual void Draw();
    int Spawn(float x, float y, float z, float size);
    void UnusedResources();
};

extern const char LavaSplash_rodata_8036E728[0x18] = {0};
extern "C" {
extern float lbl_80495994[64];
void PSVECAdd(Vec3f *, Vec3f *, Vec3f *);
double sin(double);
double cos(double);
void Object_DtorWithGXSync(void *, int);
void MemoryManager_TimedFree(void *);
void DebugPrintf(const char *, ...);
int sprintf(char *, const char *, ...);
void *ResolveJointByName(void *, char *);
void *Archive_GetRootJObj(void *);
void HSD_JObjSetFlags(void *, int);
void HSD_JObjClearFlags(void *, int);
void *HSD_JObjGetDObj(void *);
unsigned char fn_801379F0(Vec3f *, float);
void PSMTXScale(Mtx, float, float, float);
void Object_SetJObjPositionVec(void *, Vec3f *);
void Object_SetJObjScaleXYZ(void *, float, float, float);
void Object_RenderJObjTree(void *, int);
}

/* Uncalled pool owner, as clLineManager::PrintLines (fakematch). */
void clLavaSplash::UnusedResources() {
    DebugPrintf("KP_yougan_yuka.dat");
    DebugPrintf("KP_yougan_taki.dat");
    DebugPrintf("clLavaLake");
    DebugPrintf("clLavaFalls");
}

#pragma exceptions on

clLavaSplash::clLavaSplash() {
    int i;
    char name[0x20];

    DebugPrintf(" CreateMapEffect : clLavaSplash\n");
    modelA = new clNormal3D("magma_fluid_in.dat", 0);
    modelB = new clNormal3D("magma_fluid_out.dat", 0);
    modelC = new clNormal3D("magma_drop.dat", 0);
    for (i = 0; i < 30; i++) {
        bursts[i].active = 0;
    }
    if (modelB) {
        for (i = 0; i < 8; i++) {
            sprintf(name, "magma_fluid3_mf%d_joint", i + 1);
            joints[i] = ResolveJointByName(modelB, name);
        }
    }
    if (modelC) {
        HSD_JObjSetFlags(Archive_GetRootJObj(modelC), 0x200);
    }
    randIdx = 0;
}

#pragma exceptions reset
clLavaSplash::~clLavaSplash() {
    if (modelA) Object_DtorWithGXSync(modelA, 1);
    if (modelB) Object_DtorWithGXSync(modelB, 1);
    if (modelC) Object_DtorWithGXSync(modelC, 1);
    DebugPrintf(" DeleteMapEffect : clLavaSplash\n");
}

int clLavaSplash::Spawn(float x, float y, float z, float size) {
    int i;
    int j;

    if (modelA == 0 || modelB == 0 || modelC == 0) {
        return 0;
    }
    for (i = 0; i < 30; i++) {
        if (!bursts[i].active) {
            bursts[i].t = 0.0f;
            bursts[i].size = size;
            bursts[i].pos.x = x;
            bursts[i].pos.y = y;
            bursts[i].pos.z = z;
            for (j = 0; j < 10; j++) {
                float angle = 6.2831855f * lbl_80495994[randIdx];
                randIdx++;
                if (randIdx >= 64) {
                    randIdx = 0;
                }
                bursts[i].sparks[j].vel.x = size * (float)sin(angle);
                bursts[i].sparks[j].vel.z = size * (float)cos(angle);
                bursts[i].sparks[j].vel.y = size * (1.5f + lbl_80495994[randIdx]);
                bursts[i].sparks[j].pos.x = x;
                bursts[i].sparks[j].pos.y = y;
                bursts[i].sparks[j].pos.z = z;
                bursts[i].sparks[j].drag = 0.1f * size;
                bursts[i].sparks[j].gravity = 0.2f * size;
            }
            bursts[i].active = 1;
            return 1;
        }
    }
    return 0;
}

void clLavaSplash::Update() {
    int i;
    int j;

    if (modelA == 0 || modelB == 0 || modelC == 0) {
        return;
    }
    for (i = 0; i < 30; i++) {
        if (bursts[i].active) {
            bursts[i].t += 1.0f;
            if (bursts[i].t > 37.0f) {
                bursts[i].active = 0;
            } else {
                if (bursts[i].t <= 7.0f) {
                    bursts[i].scale = 1.5707964f * bursts[i].t / 7.0f;
                } else if (bursts[i].t <= 15.0f) {
                    bursts[i].scale = 1.5707964f * (15.0f - bursts[i].t) / 8.0f;
                } else {
                    bursts[i].scale = 0.0f;
                }
                bursts[i].scale *= 11.0f;
            }
            for (j = 0; j < 10; j++) {
                PSVECAdd(&bursts[i].sparks[j].vel, &bursts[i].sparks[j].pos, &bursts[i].sparks[j].pos);
                bursts[i].sparks[j].vel.y = bursts[i].sparks[j].vel.y - bursts[i].sparks[j].gravity;
            }
        }
    }
}

void clLavaSplash::Draw() {
    SparkBurst *b;
    int i;
    Mtx m;

    if (modelA == 0 || modelB == 0 || modelC == 0) {
        return;
    }
    for (b = bursts; b <= &bursts[29]; b++) {
        b->visible = 0;
        if (b->active) {
            b->visible = fn_801379F0(&b->pos, 15.0f * b->size);
        }
    }
    {
        GXChannel ch(Archive_GetRootJObj(modelA), HSD_JObjGetDObj(Archive_GetRootJObj(modelA)), 0x40000000, 1);

        for (b = bursts; b <= &bursts[29]; b++) {
            if (b->visible && b->scale > 0.0f) {
                PSMTXScale(m, b->size, b->size * b->scale, b->size);
                m[0][3] = b->pos.x;
                m[1][3] = b->pos.y;
                m[2][3] = b->pos.z;
                ch.PushTransform(m);
            }
        }
    }
    for (b = bursts; b <= &bursts[29]; b++) {
        if (b->visible && b->t <= 15.0f) {
            for (i = 0; i < 8; i++) {
                HSD_JObjSetFlags(joints[i], 0x10);
            }
            HSD_JObjClearFlags(joints[(int)(b->t / 2.0f)], 0x10);
            Object_SetJObjPositionVec(modelB, &b->pos);
            Object_SetJObjScaleXYZ(modelB, b->size, b->size, b->size);
            Object_RenderJObjTree(modelB, 7);
        }
    }
    {
        GXChannel ch(Archive_GetRootJObj(modelC), HSD_JObjGetDObj(Archive_GetRootJObj(modelC)), 0x40000000, 1);

        for (b = bursts; b <= &bursts[29]; b++) {
            if (b->visible) {
                int j;

                for (j = 0; j < 10; j++) {
                    PSMTXScale(m, b->sparks[j].drag, b->sparks[j].drag, b->sparks[j].drag);
                    m[0][3] = b->sparks[j].pos.x;
                    m[1][3] = b->sparks[j].pos.y;
                    m[2][3] = b->sparks[j].pos.z;
                    ch.PushTransform(m);
                }
            }
        }
    }
}
