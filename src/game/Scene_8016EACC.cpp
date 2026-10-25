/*
 * 0x8016EACC..0x8016F158: screen-space particle layer (three layers, 60
 * particles placed in view space from normalized screen coordinates):
 * draw, update/spawn, destructor, constructor.
 */

typedef float Mtx[3][4];

struct Vec3f {
    float x, y, z;
};

struct ScreenParticle {
    unsigned char active;
    char pad01[0x3];
    float u;
    float v;
    float depth;
    int layer;
    float scale;
    float alpha;
    float phase;
    float dphase;
};

struct clNormal3D {
    char _opaque[0x5C];
    clNormal3D(const char *res, int flags);
};

struct ScreenParticleLayer {
    void *model;
    void *roots[3];
    ScreenParticle parts[60];
    int spawnTimer;
    int randA;
    int randB;
    int randC;
    int randD;
    int randE;

    ScreenParticleLayer();
};

class GXChannel {
public:
    GXChannel(void *root, void *desc, int flags, int mode);
    ~GXChannel();
    void PushTransform(Mtx m);

private:
    char pad[0x14];
};

extern "C" {
void *GetCourseScene3D(void);
float *CObj_GetProjMatrix_Cached(void *);
void Scene3D_GetCameraPos(void *, float *, float *);
double tan(double);
void *fn_802D0758(void *);
void fn_8025DF40(float *, Vec3f *, Vec3f *);
void PSMTXScale(Mtx, float, float, float);
void PSMTXConcat(Mtx, float *, Mtx);
void Object_SetColorAlphaOnly(void *, int, float);
float LookupSin(float);
float LookupCos(float);
void Object_DtorWithGXSync(void *, int);
void MemoryManager_TimedFree(void *);
extern float lbl_80495994[64];
extern float lbl_80495A94[48];
void *Archive_GetRootJObj(void *);
void fn_80182954(void *, int);
void *ResolveJointByName(void *, const char *);
}

static inline float Rand64(int *idx) {
    if (*idx >= 64) {
        *idx = 0;
    }
    return lbl_80495994[(*idx)++];
}

static inline float Rand48(int *idx) {
    if (*idx >= 48) {
        *idx = 0;
    }
    return lbl_80495A94[(*idx)++];
}

extern "C" {

void fn_8016EACC(ScreenParticleLayer *self) {
    int layer;
    int i;
    void *scene;
    float *proj;
    float fov;
    float aspect;
    float tanHalf;
    float tanHalfX;

    if (self->model == 0) {
        return;
    }
    scene = GetCourseScene3D();
    proj = CObj_GetProjMatrix_Cached(scene);
    Scene3D_GetCameraPos(scene, &fov, &aspect);
    tanHalf = tan(0.5f * (0.017453292f * fov));
    tanHalfX = tanHalf * aspect;
    for (layer = 0; layer < 3; layer++) {
        GXChannel ch(self->roots[layer], fn_802D0758(self->roots[layer]), 0x40000000, 1);

        for (i = 0; i < 60; i++) {
            if (self->parts[i].active && self->parts[i].layer == layer) {
                Vec3f pos;
                Mtx m;
                float z = self->parts[i].depth;
                float hh;
                float hw;
                hw = z * tanHalfX;
                hh = -z * tanHalf;

                pos.x = self->parts[i].u * (-hw - hw) + hw;
                pos.y = self->parts[i].v * (-hh - hh) + hh;
                pos.z = z;
                fn_8025DF40(proj, &pos, &pos);
                PSMTXScale(m, self->parts[i].scale, self->parts[i].scale, self->parts[i].scale);
                PSMTXConcat(m, proj, m);
                m[0][3] = pos.x;
                m[1][3] = pos.y;
                m[2][3] = pos.z;
                Object_SetColorAlphaOnly(self->model, 0, self->parts[i].alpha);
                ch.PushTransform(m);
            }
        }
    }
}

void fn_8016EC80(ScreenParticleLayer *self) {
    int i;

    if (self->model == 0) {
        return;
    }
    if (self->spawnTimer != 0) {
        self->spawnTimer--;
    }
    for (i = 0; i < 60; i++) {
        ScreenParticle *p = &self->parts[i];

        if (p->active) {
            p->u += 0.0055555557f * LookupSin(p->phase) + 0.0055555557f;
            p->v -= 0.008333334f * LookupCos(p->phase) + 0.008333334f;
            p->alpha = 0.6f - 0.4f * LookupCos(2.0f * p->phase);
            if (p->u > 1.0f) {
                p->u -= 1.0f;
            }
            if (p->u < 0.0f) {
                p->u += 1.0f;
            }
            if (p->v <= 0.0f) {
                p->active = 0;
            } else {
                p->phase += p->dphase;
                if (p->phase < 0.0f) {
                    p->phase += 6.2831855f;
                }
                if (p->phase >= 6.2831855f) {
                    p->phase -= 6.2831855f;
                }
            }
        } else if (self->spawnTimer == 0) {
            p->active = 1;
            p->u = Rand64(&self->randA);
            p->v = 1.0f;
            p->depth = -18.0f * Rand48(&self->randB) + -12.0f;
            p->layer = 3.0f * Rand64(&self->randC);
            p->scale = 0.02f * Rand64(&self->randC) + 0.01f;
            p->alpha = 1.0f;
            p->phase = 0.0f;
            p->dphase = (12.566371f * Rand48(&self->randD) - 6.2831855f) / 60.0f;
            self->spawnTimer = 4.0f * Rand48(&self->randE);
        }
    }
}

ScreenParticleLayer *fn_8016EFA8(ScreenParticleLayer *self, short flag) {
    if (self) {
        if (self->model) {
            Object_DtorWithGXSync(self->model, 1);
        }
        self->model = 0;
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

}

/* TU-owned .rodata 0x8036D920: CW addresses it through one hoisted base. */
static const char sHinokoModel[0x10] = "ef_hinokos.dat";
static const char sHinokoJointO[0x10] = "_hinoko_o_joint";
static const char sHinokoJointR[0x10] = "_hinoko_r_joint";
static const char sHinokoJointY[0x10] = "_hinoko_y_joint";

ScreenParticleLayer::ScreenParticleLayer() {
    int i;

    model = new clNormal3D(sHinokoModel, 1);
    fn_80182954(Archive_GetRootJObj(model), 1);
    roots[0] = ResolveJointByName(model, sHinokoJointO);
    roots[1] = ResolveJointByName(model, sHinokoJointR);
    roots[2] = ResolveJointByName(model, sHinokoJointY);
    for (i = 0; i < 60; i++) {
        parts[i].active = 0;
        parts[i].scale = 0.01f;
    }
    spawnTimer = 0;
    randA = 0;
    randB = 0;
    randC = 0;
    randD = 0;
    randE = 0;
}
