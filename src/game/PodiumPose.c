/*
 * 0x8014219C..0x8014388C: podium pose effect. A camera fly-in over a stage
 * model with up to six posed character models (PoseChar). Vtable
 * lbl_8048EDE4, base FxBase (lbl_8048EB44, see SpriteEffects.c). Two shared
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
extern PoseTbl lbl_803608D0;
extern const char *lbl_8048ED58[6];
extern const char *lbl_8048ED70[13];
extern const char *lbl_8048EDA4[13];
extern int lbl_80360C08[5];
extern Vec3 lbl_80360BC0[5];
extern char lbl_80360C44[];
extern clNormal3D *lbl_806D1568;
extern clNormal3D *lbl_806D156C;
extern JObj *lbl_806D1570;
extern JObj *lbl_806D1574;
extern int lbl_806D1578;

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

#define s_propA lbl_806D1568
#define s_propB lbl_806D156C
#define s_jointA lbl_806D1570
#define s_jointB lbl_806D1574
#define s_propRef lbl_806D1578

extern "C" {
extern void Alloc();
extern void clNormal3D_Construct();
extern unsigned int lbl_806D7A78;
extern unsigned int lbl_806D7A88;
extern void MemoryManager_TimedFree();
asm void __ct__8PoseCharFiiP4Vec3P4Vec3Pf(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; void *f9; unsigned int f10; void *f11; unsigned int f12; void *f13; } extab_fn_80143450 = { 0x404A0000, 0x00000074, 0x00000020, 0x00000094, 0x00000028, 0x0000017C, 0x00000030, 0x00000000, 0x8A800018, (void *)&MemoryManager_TimedFree, 0x8A800018, (void *)&MemoryManager_TimedFree, 0x8A800018, (void *)&MemoryManager_TimedFree };

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80143450 = {
    (void *)&__ct__8PoseCharFiiP4Vec3P4Vec3Pf, 0x00000430, (void *)&extab_fn_80143450
};

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
            if (timer >= lbl_80360C08[0]) {
                timer = 0;
                state = 1;
            }
            break;
        case 1: {
            t = 0.5f * Sinf_LUT_Wrap(180.0f * (1.0f - (float)timer / (float)lbl_80360C08[1])) + 0.5f;
            p0 = lbl_80360BC0[0];
            p1 = lbl_80360BC0[2];
            p2 = lbl_80360BC0[4];
            fn_80181F18(&p0, &p1, &p2, &eye, t);
            if (timer >= lbl_80360C08[1]) {
                timer = 0;
                state = 4;
            }
            break;
        }
        case 2:
            if (timer >= lbl_80360C08[2]) {
                timer = 0;
                state = 3;
            }
            break;
        case 3: {
            t = 0.5f * ((float)timer / (float)lbl_80360C08[3]) + 0.5f;
            p0 = lbl_80360BC0[0];
            p1 = lbl_80360BC0[2];
            p2 = lbl_80360BC0[4];
            fn_80181F18(&p0, &p1, &p2, &eye, t);
            if (timer >= lbl_80360C08[3]) {
                timer = 0;
                state = 4;
            }
            break;
        }
        case 4:
            if (timer >= lbl_80360C08[4]) {
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
    joint = ResolveJointByName(stage, lbl_8048ED58[slot]);
    JObjGetTranslation(joint, &pos);
    joint = ResolveJointByName(stage, lbl_8048ED58[slot]);
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
    stage = new clNormal3D(lbl_80360C44, 0);
    Object_JObjUpdate_be4(stage, 0x10);
    clNormal3D_SetFlags(stage, 0x40000000, 0);
    clNormal3D_SetScale(stage, 0, 0.0f, 1.0f, 0.0f, 0.0f);
    cam = new Scene3D(lbl_80360C44);
    lights = new SceneModel(lbl_80360C44, 1);
    if (setCam == 1) {
        Vec3 v;
        v.x = lbl_80360BC0[0].x;
        v.y = lbl_80360BC0[0].y;
        v.z = lbl_80360BC0[0].z;
        CObj_LoadIntoGX(cam, &v);
        v.x = lbl_80360BC0[1].x;
        v.y = lbl_80360BC0[1].y;
        v.z = lbl_80360BC0[1].z;
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

extern "C" asm void __ct__8PoseCharFiiP4Vec3P4Vec3Pf(void) { /* 0x80143450 size:0x430 */
    nofralloc
    stwu r1, -0xc0(r1)
    mflr r0
    stw r0, 0xc4(r1)
    stfd f31, 0xb0(r1)
    psq_st f31, 0xb8(r1), 0, 0
    stmw r24, 0x90(r1)
    lwz r0, lbl_806D1578(r13)
    lis r9, lbl_803608D0@ha
    mr r29, r3
    mr r30, r4
    cmpwi r0, 0x0
    mr r25, r5
    mr r26, r6
    mr r27, r7
    mr r28, r8
    addi r31, r9, lbl_803608D0@l
    bne fn_80143450_L_80143510
    li r0, 0x0
    li r3, 0x5c
    stw r0, lbl_806D1568(r13)
    stw r0, lbl_806D156C(r13)
    stw r0, lbl_806D1570(r13)
    stw r0, lbl_806D1574(r13)
    bl Alloc
    mr. r24, r3
    beq fn_80143450_L_801434C4
    addi r4, r31, 0x384
    li r5, 0x0
    bl clNormal3D_Construct
    fn_80143450_L_801434C4:
    stw r24, lbl_806D1568(r13)
    li r3, 0x5c
    bl Alloc
    mr. r24, r3
    beq fn_80143450_L_801434E4
    addi r4, r31, 0x394
    li r5, 0x0
    bl clNormal3D_Construct
    fn_80143450_L_801434E4:
    lwz r3, lbl_806D1568(r13)
    stw r24, lbl_806D156C(r13)
    cmplwi r3, 0x0
    beq fn_80143450_L_801434FC
    bl Archive_GetRootJObj
    stw r3, lbl_806D1570(r13)
    fn_80143450_L_801434FC:
    lwz r3, lbl_806D156C(r13)
    cmplwi r3, 0x0
    beq fn_80143450_L_80143510
    bl Archive_GetRootJObj
    stw r3, lbl_806D1574(r13)
    fn_80143450_L_80143510:
    lwz r3, lbl_806D1578(r13)
    li r0, 0x0
    lfs f1, 0x0(r26)
    addi r3, r3, 0x1
    lfs f0, 0x4(r26)
    stw r3, lbl_806D1578(r13)
    lfs f4, 0x8(r26)
    stw r30, 0x0(r29)
    lfs f3, 0x0(r27)
    stw r25, 0x4(r29)
    lfs f2, 0x4(r27)
    stfs f1, 0x8(r29)
    lfs f1, 0x8(r27)
    stfs f0, 0xc(r29)
    lfs f0, lbl_806D7A88(r2)
    stfs f4, 0x10(r29)
    stfs f3, 0x14(r29)
    stfs f2, 0x18(r29)
    stfs f1, 0x1c(r29)
    stw r0, 0x20(r29)
    stw r0, 0x24(r29)
    stw r0, 0x28(r29)
    stw r0, 0x2c(r29)
    stfs f0, 0x30(r29)
    lwz r0, 0x0(r29)
    cmpwi r0, 0x0
    blt fn_80143450_L_80143584
    cmpwi r0, 0xd
    blt fn_80143450_L_8014358C
    fn_80143450_L_80143584:
    mr r3, r29
    b fn_80143450_L_80143864
    fn_80143450_L_8014358C:
    slwi r0, r0, 2
    addi r4, r31, 0x164
    lfs f1, 0x0(r28)
    li r3, 0x5c
    lfsx f0, r4, r0
    fmuls f31, f1, f0
    bl Alloc
    mr. r24, r3
    beq fn_80143450_L_801435CC
    lwz r0, 0x0(r29)
    lis r4, lbl_8048ED70@ha
    addi r4, r4, lbl_8048ED70@l
    li r5, 0x0
    slwi r0, r0, 2
    lwzx r4, r4, r0
    bl clNormal3D_Construct
    fn_80143450_L_801435CC:
    stw r24, 0x20(r29)
    fmr f1, f31
    fmr f2, f31
    fmr f3, f31
    lwz r3, 0x20(r29)
    bl Object_SetJObjScaleXYZ
    lfs f1, lbl_806D7A88(r2)
    li r4, 0x0
    lwz r3, 0x20(r29)
    fmr f3, f1
    lfs f2, lbl_806D7A78(r2)
    fmr f4, f1
    bl clNormal3D_SetScale
    lis r3, lbl_8048EDA4@ha
    slwi r28, r30, 2
    addi r30, r3, lbl_8048EDA4@l
    lwz r4, 0x2b4(r31)
    lwzx r5, r30, r28
    addi r3, r1, 0x68
    crxor 6, 6, 6
    bl sprintf
    addi r3, r31, 0x2b4
    lwzx r5, r30, r28
    lwz r4, 0x8(r3)
    addi r3, r1, 0x48
    crxor 6, 6, 6
    bl sprintf
    addi r3, r31, 0x2b4
    lwzx r5, r30, r28
    lwz r4, 0x4(r3)
    addi r3, r1, 0x28
    crxor 6, 6, 6
    bl sprintf
    addi r3, r31, 0x2b4
    lwzx r5, r30, r28
    lwz r4, 0xc(r3)
    addi r3, r1, 0x8
    crxor 6, 6, 6
    bl sprintf
    lwz r0, 0x4(r29)
    cmpwi r0, 0x0
    bne fn_80143450_L_801436EC
    lwz r3, 0x20(r29)
    addi r4, r1, 0x68
    bl ResolveJointByName
    stw r3, 0x24(r29)
    addi r3, r31, 0x2b4
    lwz r4, 0x10(r3)
    lwz r3, 0x20(r29)
    bl ResolveJointByName
    stw r3, 0x28(r29)
    addi r3, r31, 0x2b4
    lwz r4, 0x14(r3)
    lwz r3, 0x20(r29)
    bl ResolveJointByName
    stw r3, 0x2c(r29)
    addi r4, r1, 0x48
    lwz r3, 0x20(r29)
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x20(r29)
    addi r4, r1, 0x28
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x20(r29)
    addi r4, r1, 0x8
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    b fn_80143450_L_80143860
    fn_80143450_L_801436EC:
    cmpwi r0, 0x1
    bne fn_80143450_L_8014376C
    lwz r3, 0x20(r29)
    addi r4, r1, 0x48
    bl ResolveJointByName
    stw r3, 0x24(r29)
    addi r3, r31, 0x2b4
    lwz r4, 0x20(r3)
    lwz r3, 0x20(r29)
    bl ResolveJointByName
    stw r3, 0x28(r29)
    addi r3, r31, 0x2b4
    lwz r4, 0x24(r3)
    lwz r3, 0x20(r29)
    bl ResolveJointByName
    stw r3, 0x2c(r29)
    addi r4, r1, 0x68
    lwz r3, 0x20(r29)
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x20(r29)
    addi r4, r1, 0x28
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x20(r29)
    addi r4, r1, 0x8
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    b fn_80143450_L_80143860
    fn_80143450_L_8014376C:
    cmpwi r0, 0x2
    bne fn_80143450_L_801437EC
    lwz r3, 0x20(r29)
    addi r4, r1, 0x28
    bl ResolveJointByName
    stw r3, 0x24(r29)
    addi r3, r31, 0x2b4
    lwz r4, 0x18(r3)
    lwz r3, 0x20(r29)
    bl ResolveJointByName
    stw r3, 0x28(r29)
    addi r3, r31, 0x2b4
    lwz r4, 0x1c(r3)
    lwz r3, 0x20(r29)
    bl ResolveJointByName
    stw r3, 0x2c(r29)
    addi r4, r1, 0x68
    lwz r3, 0x20(r29)
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x20(r29)
    addi r4, r1, 0x48
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x20(r29)
    addi r4, r1, 0x8
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    b fn_80143450_L_80143860
    fn_80143450_L_801437EC:
    lwz r3, 0x20(r29)
    addi r4, r1, 0x8
    bl ResolveJointByName
    stw r3, 0x24(r29)
    addi r3, r31, 0x2b4
    lwz r4, 0x28(r3)
    lwz r3, 0x20(r29)
    bl ResolveJointByName
    stw r3, 0x28(r29)
    addi r3, r31, 0x2b4
    lwz r4, 0x2c(r3)
    lwz r3, 0x20(r29)
    bl ResolveJointByName
    stw r3, 0x2c(r29)
    addi r4, r1, 0x68
    lwz r3, 0x20(r29)
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x20(r29)
    addi r4, r1, 0x48
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x20(r29)
    addi r4, r1, 0x28
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    fn_80143450_L_80143860:
    mr r3, r29
    fn_80143450_L_80143864:
    psq_l f31, 0xb8(r1), 0, 0
    lfd f31, 0xb0(r1)
    lmw r24, 0x90(r1)
    lwz r0, 0xc4(r1)
    mtlr r0
    addi r1, r1, 0xc0
    blr
}

void WinPose::m0C() {
    started = 1;
}
