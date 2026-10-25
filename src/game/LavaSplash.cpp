/*
 * 0x80170EE0..0x80171754: clLavaSplash, a set of 30 lava splash bursts of 10
 * sparks each: draw, update (each burst scales in, holds and fades by its timer
 * while sparks fall), spawn, destructor and constructor. The TU owns
 * .rodata 0x8036E728..0x8036E840 (class names and resource names), which
 * CW addresses through one hoisted base. Real C++ ctor for its EH actions;
 * mangled names are bridged in tools/extab_user_renames.json.
 */

struct Vec3f {
    float x, y, z;
};

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

struct clNormal3D {
    char _opaque[0x5C];
    clNormal3D(const char *res, int flags);
};

typedef float Mtx[3][4];

class GXChannel {
public:
    GXChannel(void *root, void *desc, int flags, int mode);
    ~GXChannel();
    void PushTransform(Mtx m);

private:
    char pad[0x14];
};

struct clMapEffectParts {
    virtual void vKeyFunction();
    virtual ~clMapEffectParts();
    clMapEffectParts() {}
};

struct clLavaSplash : clMapEffectParts {
    clNormal3D *modelA;
    clNormal3D *modelB;
    clNormal3D *modelC;
    void *joints[8];
    SparkBurst bursts[30];
    int randIdx;

    clLavaSplash();
    virtual void vKeyFunction2();
};

extern const char lbl_8036E728[0x18] = {0};
extern const char lbl_8036E740[0x10] = "clLavaSplash";
extern const char lbl_8036E750[0x14] = "clMapEffectParts";
static const char sDeleteMsg[0x24] = " DeleteMapEffect : clLavaSplash\n";
static const char sCreateMsg[0x24] = " CreateMapEffect : clLavaSplash\n";
static const char sFluidInModel[0x14] = "magma_fluid_in.dat";
static const char sFluidOutModel[0x14] = "magma_fluid_out.dat";
static const char sDropModel[0x10] = "magma_drop.dat";
static const char sFluidJoint[0x18] = "magma_fluid3_mf%d_joint";
extern const char lbl_8036E7FC[0x14] = "KP_yougan_yuka.dat";
extern const char lbl_8036E810[0x14] = "KP_yougan_taki.dat";
extern const char lbl_8036E824[0xC] = "clLavaLake";
extern const char lbl_8036E830[0x10] = "clLavaFalls";

extern "C" {
extern char lbl_804912B4[];
extern char lbl_80490FE0[];
extern float lbl_80495994[64];
void fn_8025E264(Vec3f *, Vec3f *, Vec3f *);
double sin(double);
double cos(double);
void Object_DtorWithGXSync(void *, int);
void MemoryManager_TimedFree(void *);
void DebugPrintf(const char *, ...);
int sprintf(char *, const char *, ...);
void *ResolveJointByName(void *, char *);
void *Archive_GetRootJObj(void *);
void fn_802D07D4(void *, int);
void fn_802D0B48(void *, int);
void *fn_802D0758(void *);
unsigned char fn_801379F0(Vec3f *, float);
void PSMTXScale(Mtx, float, float, float);
void Object_SetJObjPositionVec(void *, Vec3f *);
void Object_SetJObjScaleXYZ(void *, float, float, float);
void Object_RenderJObjTree(void *, int);
}

extern "C" {
void fn_80170EE0(clLavaSplash *self) {
    SparkBurst *b;
    int i;
    Mtx m;

    if (self->modelA == 0 || self->modelB == 0 || self->modelC == 0) {
        return;
    }
    for (b = self->bursts; b <= &self->bursts[29]; b++) {
        b->visible = 0;
        if (b->active) {
            b->visible = fn_801379F0(&b->pos, 15.0f * b->size);
        }
    }
    {
        GXChannel ch(Archive_GetRootJObj(self->modelA), fn_802D0758(Archive_GetRootJObj(self->modelA)), 0x40000000, 1);

        for (b = self->bursts; b <= &self->bursts[29]; b++) {
            if (b->visible && b->scale > 0.0f) {
                PSMTXScale(m, b->size, b->size * b->scale, b->size);
                m[0][3] = b->pos.x;
                m[1][3] = b->pos.y;
                m[2][3] = b->pos.z;
                ch.PushTransform(m);
            }
        }
    }
    for (b = self->bursts; b <= &self->bursts[29]; b++) {
        if (b->visible && b->t <= 15.0f) {
            for (i = 0; i < 8; i++) {
                fn_802D07D4(self->joints[i], 0x10);
            }
            fn_802D0B48(self->joints[(int)(b->t / 2.0f)], 0x10);
            Object_SetJObjPositionVec(self->modelB, &b->pos);
            Object_SetJObjScaleXYZ(self->modelB, b->size, b->size, b->size);
            Object_RenderJObjTree(self->modelB, 7);
        }
    }
    {
        GXChannel ch(Archive_GetRootJObj(self->modelC), fn_802D0758(Archive_GetRootJObj(self->modelC)), 0x40000000, 1);

        for (b = self->bursts; b <= &self->bursts[29]; b++) {
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

void fn_80171190(clLavaSplash *self) {
    int i;
    int j;

    if (self->modelA == 0 || self->modelB == 0 || self->modelC == 0) {
        return;
    }
    for (i = 0; i < 30; i++) {
        if (self->bursts[i].active) {
            self->bursts[i].t += 1.0f;
            if (self->bursts[i].t > 37.0f) {
                self->bursts[i].active = 0;
            } else {
                if (self->bursts[i].t <= 7.0f) {
                    self->bursts[i].scale = 1.5707964f * self->bursts[i].t / 7.0f;
                } else if (self->bursts[i].t <= 15.0f) {
                    self->bursts[i].scale = 1.5707964f * (15.0f - self->bursts[i].t) / 8.0f;
                } else {
                    self->bursts[i].scale = 0.0f;
                }
                self->bursts[i].scale *= 11.0f;
            }
            for (j = 0; j < 10; j++) {
                fn_8025E264(&self->bursts[i].sparks[j].vel, &self->bursts[i].sparks[j].pos, &self->bursts[i].sparks[j].pos);
                self->bursts[i].sparks[j].vel.y = self->bursts[i].sparks[j].vel.y - self->bursts[i].sparks[j].gravity;
            }
        }
    }
}

int fn_801712E4(clLavaSplash *self, float x, float y, float z, float size) {
    int i;
    int j;

    if (self->modelA == 0 || self->modelB == 0 || self->modelC == 0) {
        return 0;
    }
    for (i = 0; i < 30; i++) {
        if (!self->bursts[i].active) {
            self->bursts[i].t = 0.0f;
            self->bursts[i].size = size;
            self->bursts[i].pos.x = x;
            self->bursts[i].pos.y = y;
            self->bursts[i].pos.z = z;
            for (j = 0; j < 10; j++) {
                float angle = 6.2831855f * lbl_80495994[self->randIdx];
                self->randIdx++;
                if (self->randIdx >= 64) {
                    self->randIdx = 0;
                }
                self->bursts[i].sparks[j].vel.x = size * (float)sin(angle);
                self->bursts[i].sparks[j].vel.z = size * (float)cos(angle);
                self->bursts[i].sparks[j].vel.y = size * (1.5f + lbl_80495994[self->randIdx]);
                self->bursts[i].sparks[j].pos.x = x;
                self->bursts[i].sparks[j].pos.y = y;
                self->bursts[i].sparks[j].pos.z = z;
                self->bursts[i].sparks[j].drag = 0.1f * size;
                self->bursts[i].sparks[j].gravity = 0.2f * size;
            }
            self->bursts[i].active = 1;
            return 1;
        }
    }
    return 0;
}

clLavaSplash *fn_801714E8(clLavaSplash *self, short flag) {
    if (self) {
        *(void **)self = lbl_804912B4;
        if (self->modelA) {
            Object_DtorWithGXSync(self->modelA, 1);
        }
        if (self->modelB) {
            Object_DtorWithGXSync(self->modelB, 1);
        }
        if (self->modelC) {
            Object_DtorWithGXSync(self->modelC, 1);
        }
        DebugPrintf(sDeleteMsg);
        if (self) {
            *(void **)self = lbl_80490FE0;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

}

#pragma exceptions on

clLavaSplash::clLavaSplash() {
    int i;
    char name[0x20];

    DebugPrintf(sCreateMsg);
    modelA = new clNormal3D(sFluidInModel, 0);
    modelB = new clNormal3D(sFluidOutModel, 0);
    modelC = new clNormal3D(sDropModel, 0);
    for (i = 0; i < 30; i++) {
        bursts[i].active = 0;
    }
    if (modelB) {
        for (i = 0; i < 8; i++) {
            sprintf(name, sFluidJoint, i + 1);
            joints[i] = ResolveJointByName(modelB, name);
        }
    }
    if (modelC) {
        fn_802D07D4(Archive_GetRootJObj(modelC), 0x200);
    }
    randIdx = 0;
}

#pragma exceptions reset
