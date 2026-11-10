/*
 * 0x8014219C..0x8014388C: podium pose effect. A camera fly-in over a stage
 * model with up to six posed character models (PoseChar). Vtable
 * WinPose_vtable_8048EDE4, base FxBase (lbl_8048EB44, see SpriteEffects.c). Two shared
 * prop models (s_propA/s_propB) are reference-counted across PoseChars and
 * have their matrices copied from character joints each frame.
 */
#pragma cplusplus on

typedef float Mtx[3][4];
typedef float (*MtxPtr)[4];

struct Vec3 {
    float x, y, z;
};

struct JObj {
    unsigned char pad0[0x8];
    JObj *next;
    JObj *parent;
    JObj *child;
    unsigned int flags;
    unsigned char pad18[4];
    float rotX, rotY, rotZ, rotW;
    float scaleX, scaleY, scaleZ;
    Vec3 translate;
    Mtx mtx;
};

struct clNormal3D {
    char _opaque[0x5C];
    clNormal3D(const char *res, int flags);
};

struct Scene3D {
    virtual ~Scene3D();
    virtual unsigned char Begin();
    virtual void End();
    char pad[0x3080];
    Scene3D(const char *res);
};

struct SceneModel {
    char pad[0x28];
    SceneModel(const char *res, int flags);
};

struct PoseTbl {
    char names[0x164];
    float scale[13];
    char pad198[0x2B4 - 0x198];
    const char *fmt[12];
    char pad2E4[0x384 - 0x2E4];
    char propA[0x10];
    char propB[0x10];
};

void *operator new(unsigned long);
void operator delete(void *);

extern "C" {
extern const char *PodiumPose_data_8048ED58[6];
extern const char *PodiumPose_data_8048ED70[13];
extern const char *PodiumPose_data_8048EDA4[13];
extern clNormal3D *PodiumPose_bss_806D1568;
extern clNormal3D *PodiumPose_bss_806D156C;
extern JObj *PodiumPose_bss_806D1570;
extern JObj *PodiumPose_bss_806D1574;
extern int PodiumPose_bss_806D1578;

extern const char lbl_806D7AA0[7]; /* lbl_806D7AA0 */
extern const char lbl_806D7AA8[5]; /* "jobj" */
extern const char lbl_806D7AC0[4]; /* "mtx" */
extern void __assert(const char *file, int line, const char *expr);
extern void HSD_JObjSetupMatrixSub(JObj *jobj);
extern void HSD_JObjSetMtxDirtySub(JObj *jobj);
extern void HSD_JObjSetFlagsAll(JObj *jobj, unsigned int flags);
extern JObj *ResolveJointByName(void *model, const char *name);
extern JObj *Archive_GetRootJObj(void *model);
extern void Object_RenderJObjTree(void *model, int mask);
extern void Object_RenderJObjEx(void *model, JObj *jobj, int mask);
extern void Object_DtorWithGXSync(void *model, int flag);
extern void Object_SetJObjScaleXYZ(void *model, float x, float y, float z);
extern void Object_SetJObjPositionVec(void *model, Vec3 *pos);
extern void JObj_SetRotationQuat(void *model, float x, float y, float z);
extern void Object_SetField8_AndDirty(void *model, float frame);
extern void Object_JObjUpdate_be4(void *model, int flags);
extern void clNormal3D_Exec(void *model);
extern void clNormal3D_SetFlags(void *model, unsigned int set, unsigned int clear);
extern void clNormal3D_SetScale(void *model, int a, float b, float c, float d, float e);
extern void LObjList_ApplyForCObj(SceneModel *list);
extern void LObjList_Destroy(SceneModel *list, int flag);
extern void CObj_DebugVizPathFlush(Scene3D *cam);
extern void CObj_LoadProjMatrix(Scene3D *cam, Vec3 *v);
extern void CObj_ApplyScissor(Scene3D *cam, Vec3 *v);
extern void CObj_LoadIntoGX(Scene3D *cam, Vec3 *v);
extern void CObj_ApplyViewport(Scene3D *cam, Vec3 *v);
extern void fn_80181F18(Vec3 *a, Vec3 *b, Vec3 *c, Vec3 *out, float t);
extern float Sinf_LUT_Wrap(float deg);
extern int sprintf(char *buf, const char *fmt, ...);
extern void PSMTXCopy(const Mtx src, Mtx dst);
extern void PSMTXIdentity(Mtx m);
extern void PSMTXScale(Mtx m, float x, float y, float z);
extern void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
}

#define s_propA PodiumPose_bss_806D1568
#define s_propB PodiumPose_bss_806D156C
#define s_jointA PodiumPose_bss_806D1570
#define s_jointB PodiumPose_bss_806D1574
#define s_propRef PodiumPose_bss_806D1578

extern "C" {
extern void Alloc();
extern void clNormal3D_Construct();
extern unsigned int lbl_806D7A78;
extern unsigned int lbl_806D7A88;
extern void MemoryManager_TimedFree();

}

static inline unsigned char JObjMtxIsDirty(JObj *jobj) {
    unsigned char result;
    if (!jobj) {
        __assert(lbl_806D7AA0, 0x25D, lbl_806D7AA8);
    }
    result = 0;
    if (!(jobj->flags & 0x00800000) && (jobj->flags & 0x40)) {
        result = 1;
    }
    return result;
}

static inline void JObjSetupMatrix(JObj *jobj) {
    if (!jobj) {
        return;
    }
    if (JObjMtxIsDirty(jobj)) {
        HSD_JObjSetupMatrixSub(jobj);
    }
}

static inline MtxPtr JObjGetMtxPtr(JObj *jobj) {
    if (!jobj) {
        __assert(lbl_806D7AA0, 0x47C, lbl_806D7AA8);
    }
    JObjSetupMatrix(jobj);
    return jobj->mtx;
}

static inline void JObjSetMtxDirty(JObj *jobj) {
    if (jobj && !JObjMtxIsDirty(jobj)) {
        HSD_JObjSetMtxDirtySub(jobj);
    }
}

static inline void JObjCopyMtx(JObj *jobj, MtxPtr mtx) {
    if (!jobj) {
        __assert(lbl_806D7AA0, 0x495, lbl_806D7AA8);
    }
    if (!mtx) {
        __assert(lbl_806D7AA0, 0x496, lbl_806D7AC0);
    }
    PSMTXCopy(mtx, jobj->mtx);
    jobj->flags |= 0x03800000;
    JObjSetMtxDirty(jobj);
}

static inline float JObjGetScaleX(JObj *jobj) {
    if (!jobj) {
        __assert(lbl_806D7AA0, 0x383, lbl_806D7AA8);
    }
    return jobj->scaleX;
}

static inline float JObjGetScaleY(JObj *jobj) {
    if (!jobj) {
        __assert(lbl_806D7AA0, 0x38F, lbl_806D7AA8);
    }
    return jobj->scaleY;
}

static inline float JObjGetScaleZ(JObj *jobj) {
    if (!jobj) {
        __assert(lbl_806D7AA0, 0x39B, lbl_806D7AA8);
    }
    return jobj->scaleZ;
}

static inline JObj *JObjGetParent(JObj *jobj) {
    return !jobj ? 0 : jobj->parent;
}

static inline void JObjGetTranslation(JObj *jobj, Vec3 *t) {
    if (!jobj) {
        __assert(lbl_806D7AA0, 0x3E4, lbl_806D7AA8);
    }
    *t = jobj->translate;
}

static inline float JObjGetRotationY(JObj *jobj) {
    if (!jobj) {
        __assert(lbl_806D7AA0, 0x2FA, lbl_806D7AA8);
    }
    return jobj->rotY;
}

/* Inverse of the accumulated joint scale, so a prop keeps its own size. */
static inline void InvWorldScale(JObj *jobj, Mtx m) {
    if (jobj) {
        float sx, sy, sz;
        sx = sy = sz = 1.0f;
        do {
            sx *= JObjGetScaleX(jobj);
            sy *= JObjGetScaleY(jobj);
            sz *= JObjGetScaleZ(jobj);
            jobj = JObjGetParent(jobj);
        } while (jobj);
        PSMTXIdentity(m);
        PSMTXScale(m, 1.0f / sx, 1.0f / sy, 1.0f / sz);
    }
}

struct FxData {
    int obj;
    unsigned char active;
    float x, y;
    float alpha;
};

struct FxBase : FxData {
    FxBase() {
        obj = 0;
        active = 0;
        x = 0.0f;
        y = 0.0f;
        alpha = 1.0f;
    }
    virtual ~FxBase() {}
    virtual void m0C();
    virtual void m10();
    virtual void Update();
    virtual void Draw();
    virtual void m1C();
};


/* .rodata 0x803608D0..0x80360C70 (TU-owned; the ctor addresses it from the section start) */
extern "C" {
extern const char lbl_803608D0[0x17] = "ceremony_take2_1_joint";
extern const char lbl_803608E8[0x17] = "ceremony_take2_2_joint";
extern const char lbl_80360900[0x17] = "ceremony_take2_3_joint";
extern const char lbl_80360918[0x17] = "ceremony_take2_4_joint";
extern const char lbl_80360930[0x17] = "ceremony_take2_5_joint";
extern const char lbl_80360948[0x17] = "ceremony_take2_6_joint";
extern const char lbl_80360960[0xE] = "mario_set.dat";
extern const char lbl_80360970[0xE] = "luigi_set.dat";
extern const char lbl_80360980[0xE] = "wario_set.dat";
extern const char lbl_80360990[0xE] = "peach_set.dat";
extern const char lbl_803609A0[0xE] = "koopa_set.dat";
extern const char lbl_803609B0[0x10] = "kinopio_set.dat";
extern const char lbl_803609C0[0xF] = "donkey_set.dat";
extern const char lbl_803609D0[0xE] = "yoshi_set.dat";
extern const char lbl_803609E0[0xF] = "pacman_set.dat";
extern const char lbl_803609F0[0x11] = "mspacman_set.dat";
extern const char lbl_80360A04[0x10] = "monster_set.dat";
extern const char lbl_80360A14[0x10] = "waluigi_set.dat";
extern const char lbl_80360A24[0x10] = "mametch_set.dat";
}
static const float sPoseScale[13] = {
    0.9f, 0.9f, 0.9f, 0.9f, 1.0f, 1.0f, 1.0f, 0.9f, 0.9f, 0.9f, 1.0f, 0.87f, 1.0f,
};
extern "C" {
extern const char lbl_80360A68[0x13] = "chara_%s_1st_joint";
extern const char lbl_80360A7C[0x13] = "chara_%s_2st_joint";
extern const char lbl_80360A90[0x13] = "chara_%s_3st_joint";
extern const char lbl_80360AA4[0x15] = "chara_%s_other_joint";
extern const char lbl_80360ABC[0x17] = "chara_1st_l_hand_joint";
extern const char lbl_80360AD4[0x17] = "chara_1st_r_hand_joint";
extern const char lbl_80360AEC[0x17] = "chara_2st_l_hand_joint";
extern const char lbl_80360B04[0x17] = "chara_2st_r_hand_joint";
extern const char lbl_80360B1C[0x17] = "chara_3st_l_hand_joint";
extern const char lbl_80360B34[0x17] = "chara_3st_r_hand_joint";
extern const char lbl_80360B4C[0x19] = "chara_other_l_hand_joint";
extern const char lbl_80360B68[0x19] = "chara_other_r_hand_joint";
}
static const char *const sPoseJointFmt[12] = {
    lbl_80360A68, lbl_80360A7C, lbl_80360A90, lbl_80360AA4,
    lbl_80360ABC, lbl_80360AD4, lbl_80360AEC, lbl_80360B04,
    lbl_80360B1C, lbl_80360B34, lbl_80360B4C, lbl_80360B68,
};
extern "C" {
extern const char lbl_80360BB4[0x9] = "mspacman";
extern const Vec3 PodiumPose_rodata_80360BC0[6] = {
    {0.0f, 20.0f, 36.5f},
    {0.0f, 13.0f, -28.0f},
    {-0.0f, 4.197254f, 43.202705f},
    {0.0f, 13.0f, -28.0f},
    {0.0f, 3.0f, 64.57f},
    {0.0f, 13.0f, -28.0f},
};
extern const int PodiumPose_rodata_80360C08[5] = {40, 140, 0, 40, 10};
extern const char lbl_80360C1C[0x12] = "clCSPartsPlatform";
extern const char lbl_80360C30[0x12] = "clCSPartsInerface";
}
static const char sCeremonyFile[0x10] = "ceremony.dat";
static const char sTrophyFile[0x10] = "trpy_hanyou.dat";
static const char sFlowerFile[0xC] = "flower.dat";

struct PoseChar {
    int kind;
    int mode;
    Vec3 pos;
    Vec3 rot;
    clNormal3D *model;
    JObj *head;
    JObj *propJointB;
    JObj *propJointA;
    float frame;

    PoseChar(int kind, int mode, Vec3 *pos, Vec3 *rot, float *scale);
    ~PoseChar() {
        if (model) {
            Object_DtorWithGXSync(model, 1);
        }
        if (s_propRef > 0) {
            if (--s_propRef == 0) {
                if (s_propA) {
                    Object_DtorWithGXSync(s_propA, 1);
                }
                if (s_propB) {
                    Object_DtorWithGXSync(s_propB, 1);
                }
                s_propA = 0;
                s_propB = 0;
                s_jointA = 0;
                s_jointB = 0;
            }
        }
    }
    void DrawScaled();
    void Draw();
};

struct WinPose : FxBase {
    clNormal3D *stage;
    Scene3D *cam;
    SceneModel *lights;
    PoseChar *chars[6];
    int timer;
    int state;
    unsigned char started;

    virtual void m10();
    WinPose(unsigned char setCam);
    virtual ~WinPose();
    virtual void m0C();
    virtual void Update();
    virtual void m1C();
    int IsDone();
    unsigned char Spawn(int slot, int kind);
};

int WinPose::IsDone() {
    return (state == 5) ? 1 : 0;
}

void WinPose::m1C() {
    JObj *root;
    JObj *front;
    JObj *back;
    int i;

    if (cam->Begin()) {
        LObjList_ApplyForCObj(lights);
        CObj_DebugVizPathFlush(cam);
        root = Archive_GetRootJObj(stage);
        front = !root ? 0 : root->child;
        back = !front ? 0 : front->next;
        Object_RenderJObjTree(stage, 1);
        Object_RenderJObjEx(stage, back, 6);
        for (i = 5; i >= 0; i--) {
            if (chars[i]) {
                chars[i]->Draw();
            }
        }
        Object_RenderJObjEx(stage, front, 6);
        cam->End();
    }
}

void WinPose::Update() {
    PoseChar *c;
    int i;
    float t;
    Vec3 p0;
    Vec3 p1;
    Vec3 p2;
    Vec3 eye;
    Vec3 viewport;

    clNormal3D_Exec(stage);
    for (i = 0; i < 6; i++) {
        c = chars[i];
        if (c && c->kind >= 0 && c->kind < 13) {
            c->frame += 1.0f;
            if (c->mode == 0) {
                if (c->frame >= 180.0f) {
                    c->frame = 120.0f;
                }
            } else if (c->kind == 11 || c->kind == 12) {
                if (c->frame >= 60.0f) {
                    c->frame = 0.0f;
                }
            } else {
                if (c->frame >= 30.0f) {
                    c->frame = 0.0f;
                }
            }
            Object_SetJObjPositionVec(c->model, &c->pos);
            JObj_SetRotationQuat(c->model, c->rot.x, c->rot.y, c->rot.z);
            Object_SetField8_AndDirty(c->model, c->frame);
            clNormal3D_Exec(c->model);
        }
    }
    if (started) {
        CObj_LoadProjMatrix(cam, &eye);
        CObj_ApplyScissor(cam, &viewport);
        switch (state) {
        case 0:
            if (timer >= PodiumPose_rodata_80360C08[0]) {
                timer = 0;
                state = 1;
            }
            break;
        case 1: {
            t = 0.5f * Sinf_LUT_Wrap(180.0f * (1.0f - (float)timer / (float)PodiumPose_rodata_80360C08[1])) + 0.5f;
            p0 = PodiumPose_rodata_80360BC0[0];
            p1 = PodiumPose_rodata_80360BC0[2];
            p2 = PodiumPose_rodata_80360BC0[4];
            fn_80181F18(&p0, &p1, &p2, &eye, t);
            if (timer >= PodiumPose_rodata_80360C08[1]) {
                timer = 0;
                state = 4;
            }
            break;
        }
        case 2:
            if (timer >= PodiumPose_rodata_80360C08[2]) {
                timer = 0;
                state = 3;
            }
            break;
        case 3: {
            t = 0.5f * ((float)timer / (float)PodiumPose_rodata_80360C08[3]) + 0.5f;
            p0 = PodiumPose_rodata_80360BC0[0];
            p1 = PodiumPose_rodata_80360BC0[2];
            p2 = PodiumPose_rodata_80360BC0[4];
            fn_80181F18(&p0, &p1, &p2, &eye, t);
            if (timer >= PodiumPose_rodata_80360C08[3]) {
                timer = 0;
                state = 4;
            }
            break;
        }
        case 4:
            if (timer >= PodiumPose_rodata_80360C08[4]) {
                timer = 0;
                state = 5;
            }
            break;
        }
        CObj_LoadIntoGX(cam, &eye);
        CObj_ApplyViewport(cam, &viewport);
        timer++;
    }
}

static inline int SlotMode(int slot) { return slot < 3 ? slot : -1; }
static inline int SlotMode2(int slot) { int m = -1; if (slot < 3) m = slot; return m; }

unsigned char WinPose::Spawn(int slot, int kind) {
    float scale;
    Vec3 pos;
    Vec3 rot;
    int mode;
    JObj *joint;

    if (slot < 0 || slot >= 6) {
        return 0;
    }
    if (kind < 0 || kind >= 13) {
        return 0;
    }
    if (chars[slot]) {
        return 0;
    }
    scale = 1.0f;
    if (slot < 3) {
        mode = slot;
    } else {
        mode = -1;
    }
    joint = ResolveJointByName(stage, PodiumPose_data_8048ED58[slot]);
    JObjGetTranslation(joint, &pos);
    joint = ResolveJointByName(stage, PodiumPose_data_8048ED58[slot]);
    rot.x = 0.0f;
    rot.y = 0.0f;
    rot.z = 0.0f;
    if (mode == 0) {
        pos.z += 2.0f;
    }
    if (mode == 1) {
        scale = 0.9f;
    }
    if (mode == 2) {
        scale = 0.9f;
    }
    if (mode == -1) {
        rot.y = JObjGetRotationY(joint) - 3.1415927f;
    }
    chars[slot] = new PoseChar(kind, mode, &pos, &rot, &scale);
    return 1;
}

WinPose::~WinPose() {
    int i;

    Object_DtorWithGXSync(stage, 1);
    delete cam;
    LObjList_Destroy(lights, 1);
    for (i = 0; i < 6; i++) {
        if (chars[i]) {
            delete chars[i];
        }
    }
}

WinPose::WinPose(unsigned char setCam) {
    started = 0;
    timer = 0;
    state = 0;
    stage = 0;
    cam = 0;
    lights = 0;
    chars[0] = 0;
    chars[1] = 0;
    chars[2] = 0;
    chars[3] = 0;
    chars[4] = 0;
    chars[5] = 0;
    stage = new clNormal3D(sCeremonyFile, 0);
    Object_JObjUpdate_be4(stage, 0x10);
    clNormal3D_SetFlags(stage, 0x40000000, 0);
    clNormal3D_SetScale(stage, 0, 0.0f, 1.0f, 0.0f, 0.0f);
    cam = new Scene3D(sCeremonyFile);
    lights = new SceneModel(sCeremonyFile, 1);
    if (setCam == 1) {
        Vec3 v;
        v.x = PodiumPose_rodata_80360BC0[0].x;
        v.y = PodiumPose_rodata_80360BC0[0].y;
        v.z = PodiumPose_rodata_80360BC0[0].z;
        CObj_LoadIntoGX(cam, &v);
        v.x = PodiumPose_rodata_80360BC0[1].x;
        v.y = PodiumPose_rodata_80360BC0[1].y;
        v.z = PodiumPose_rodata_80360BC0[1].z;
        CObj_ApplyViewport(cam, &v);
    }
}

void PoseChar::DrawScaled() {
    Mtx a;
    Mtx b;

    Object_RenderJObjTree(model, 7);
    if ((mode == 0 || mode == 1) && propJointA) {
        InvWorldScale(propJointA, a);
        a[0][0] *= 0.7f;
        a[1][1] *= 0.7f;
        a[2][2] *= 0.7f;
        PSMTXConcat(JObjGetMtxPtr(propJointA), a, a);
    }
    if ((mode == 0 || mode == 2) && propJointB) {
        InvWorldScale(propJointB, b);
        b[0][0] *= 0.7f;
        b[1][1] *= 0.7f;
        b[2][2] *= 0.7f;
        PSMTXConcat(JObjGetMtxPtr(propJointB), b, b);
    }
    if (mode == 0 && s_jointA && propJointA) {
        JObjCopyMtx(s_jointA, a);
        Object_RenderJObjTree(s_propA, 7);
    }
    if (mode == 1 && s_jointB && propJointA) {
        JObjCopyMtx(s_jointB, a);
        Object_RenderJObjTree(s_propB, 7);
    }
    if ((mode == 0 || mode == 2) && s_jointB && propJointB) {
        JObjCopyMtx(s_jointB, b);
        Object_RenderJObjTree(s_propB, 7);
    }
}

void PoseChar::Draw() {
    Mtx m;
    Mtx s;

    if (kind < 0 || kind >= 13) {
        return;
    }
    if (kind == 12) {
        DrawScaled();
        return;
    }
    Object_RenderJObjTree(model, 7);
    if (mode == 0 && s_jointA && propJointA) {
        PSMTXCopy(JObjGetMtxPtr(propJointA), m);
        if (kind == 5) {
            PSMTXIdentity(s);
            PSMTXScale(s, 0.7f, 0.7f, 0.7f);
            PSMTXConcat(m, s, m);
        }
        JObjCopyMtx(s_jointA, m);
        Object_RenderJObjTree(s_propA, 7);
    }
    if (mode == 1 && s_jointB && propJointA) {
        JObjCopyMtx(s_jointB, JObjGetMtxPtr(propJointA));
        Object_RenderJObjTree(s_propB, 7);
    }
    if ((mode == 0 || mode == 2) && s_jointB && propJointB) {
        JObjCopyMtx(s_jointB, JObjGetMtxPtr(propJointB));
        Object_RenderJObjTree(s_propB, 7);
    }
}

static inline void PoseVecSet(Vec3 *v, float x, float y, float z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

PoseChar::PoseChar(int kind, int mode, Vec3 *pos, Vec3 *rot, float *scale) {
    char nameA[32];
    char nameB[32];
    char nameC[32];
    char nameD[32];
    float s;

    if (s_propRef == 0) {
        s_propA = 0;
        s_propB = 0;
        s_jointA = 0;
        s_jointB = 0;
        s_propA = new clNormal3D(sTrophyFile, 0);
        s_propB = new clNormal3D(sFlowerFile, 0);
        if (s_propA) {
            s_jointA = Archive_GetRootJObj(s_propA);
        }
        if (s_propB) {
            s_jointB = Archive_GetRootJObj(s_propB);
        }
    }
    {
        float px, rz, ry, rx, py, pz;
        px = pos->x; py = pos->y; pz = pos->z;
        s_propRef++;
        rx = rot->x;
        this->kind = kind;
        ry = rot->y;
        this->mode = mode;
        PoseVecSet(&this->pos, px, py, pz);
        rz = rot->z;
        PoseVecSet(&this->rot, rx, ry, rz);
    }
    model = 0;
    head = 0;
    propJointB = 0;
    propJointA = 0;
    frame = 0.0f;
    if (this->kind < 0 || this->kind >= 13) {
        return;
    }
    s = *scale * sPoseScale[this->kind];
    model = new clNormal3D(PodiumPose_data_8048ED70[this->kind], 0);
    Object_SetJObjScaleXYZ(model, s, s, s);
    clNormal3D_SetScale(model, 0, 0.0f, 1.0f, 0.0f, 0.0f);
    sprintf(nameA, sPoseJointFmt[0], PodiumPose_data_8048EDA4[kind]);
    sprintf(nameB, sPoseJointFmt[2], PodiumPose_data_8048EDA4[kind]);
    sprintf(nameC, sPoseJointFmt[1], PodiumPose_data_8048EDA4[kind]);
    sprintf(nameD, sPoseJointFmt[3], PodiumPose_data_8048EDA4[kind]);
    if (this->mode == 0) {
        head = ResolveJointByName(model, nameA);
        propJointB = ResolveJointByName(model, sPoseJointFmt[4]);
        propJointA = ResolveJointByName(model, sPoseJointFmt[5]);
        HSD_JObjSetFlagsAll(ResolveJointByName(model, nameB), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(model, nameC), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(model, nameD), 0x10);
    } else if (this->mode == 1) {
        head = ResolveJointByName(model, nameB);
        propJointB = ResolveJointByName(model, sPoseJointFmt[8]);
        propJointA = ResolveJointByName(model, sPoseJointFmt[9]);
        HSD_JObjSetFlagsAll(ResolveJointByName(model, nameA), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(model, nameC), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(model, nameD), 0x10);
    } else if (this->mode == 2) {
        head = ResolveJointByName(model, nameC);
        propJointB = ResolveJointByName(model, sPoseJointFmt[6]);
        propJointA = ResolveJointByName(model, sPoseJointFmt[7]);
        HSD_JObjSetFlagsAll(ResolveJointByName(model, nameA), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(model, nameB), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(model, nameD), 0x10);
    } else {
        head = ResolveJointByName(model, nameD);
        propJointB = ResolveJointByName(model, sPoseJointFmt[10]);
        propJointA = ResolveJointByName(model, sPoseJointFmt[11]);
        HSD_JObjSetFlagsAll(ResolveJointByName(model, nameA), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(model, nameB), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(model, nameC), 0x10);
    }
}

void WinPose::m0C() {
    started = 1;
}
