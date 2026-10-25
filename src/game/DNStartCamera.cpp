/*
 * 0x8022929C..0x80229998: clDNStartCamera (Dino Dino Jungle start-line
 * cameramen). Ten cameramen turn to face the player while the player is in
 * the start area, and six of them fire flashes (the clDNFlash FlashPart
 * helpers) at random intervals. The TU owns .rodata 0x803D08F0..0x803D0DB0,
 * addressed off one hoisted base.
 */

typedef float Mtx[3][4];

struct Vec3f {
    float x, y, z;
};

struct HSD_JObj {
    char pad00[0x14];
    unsigned int flags;
    char pad18[0x1C - 0x18];
    Vec3f rotate;
    char pad28[0x38 - 0x28];
    Vec3f translate;
    Mtx mtx;
};

struct clNormal3D {
    char _opaque[0x5C];
    clNormal3D(const char *res, int flags);
    ~clNormal3D();
};

struct KartRender;

class GXChannel {
public:
    GXChannel(void *root, void *desc, int flags, int mode);
    ~GXChannel();
    void PushTransform(Mtx m);

private:
    char pad[0x14];
};

struct FlashPoint {
    Vec3f pos;
    unsigned char used;
};

struct FlashPart {
    unsigned char active;
    float scale;
    float alpha;
    float dscale;
    int life;
    FlashPoint *owner;
    void Tick();
    void Start(FlashPoint *pt);
    void Init();
};

struct CamFlash {
    FlashPoint pt;
    FlashPart fp;
    int timer;
};

struct clMapEffectParts {
    virtual ~clMapEffectParts() {}
    virtual void Update();
    virtual void Draw();
    virtual void Enable(int on);
    clMapEffectParts() {}
};

struct clDNStartCamera : clMapEffectParts {
    clNormal3D *flash;
    clNormal3D *cam;
    HSD_JObj *men[10];
    HSD_JObj *flashJoints[6];
    unsigned char hidden;
    CamFlash flashes[6];

    clDNStartCamera(HSD_JObj *at);
    virtual void Enable(int on);
    virtual ~clDNStartCamera();
    virtual void Update();
    virtual void Draw();
};

extern "C" {
extern KartRender *g_playerRenderObj;
extern const char lbl_806DB4E0[7];
extern const char lbl_806DB4E8[5];
extern const float lbl_806DB4F0;
extern const float lbl_806DB4F4;
extern const float lbl_806DB4F8;
void __assert(const char *file, int line, const char *cond);
HSD_JObj *Archive_GetRootJObj(clNormal3D *m);
void *HSD_JObjGetDObj(HSD_JObj *jobj);
void HSD_JObjSetFlags(HSD_JObj *jobj, int flags);
void HSD_JObjSetMtxDirtySub(HSD_JObj *jobj);
void HSD_JObjSetupMatrixSub(HSD_JObj *jobj);
void fn_80182954(HSD_JObj *jobj, int on);
void Object_DtorWithGXSync(clNormal3D *m, int flag);
void Object_SetColorAlphaOnly(clNormal3D *m, int idx, float alpha);
void Object_RenderJObjTree(clNormal3D *m, int flags);
void Object_SetJObjPositionX(clNormal3D *m, float v);
void Object_SetJObjPositionY(clNormal3D *m, float v);
void Object_SetJObjField40(clNormal3D *m, float v);
void clNormal3D_SetScale(clNormal3D *m, int anim, float t, float a, float b, float c);
void clNormal3D_Exec(clNormal3D *m);
void Object_DriveAnimMatrix(clNormal3D *m);
HSD_JObj *ResolveJointByName(clNormal3D *m, const char *name);
void PSMTXScale(Mtx m, float x, float y, float z);
const float *KartDriver_GetKartRootMtx(KartRender *k);
double atan2(double y, double x);
int sprintf(char *buf, const char *fmt, ...);
int rand(void);
}

extern const unsigned int lbl_803D08F0[0x102] = {
    0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x3F333333, 0x3F666666,
    0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556,
    0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556,
    0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556,
    0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556,
    0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000,
    0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556,
    0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556,
    0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556,
    0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556,
    0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556,
    0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556,
    0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000,
    0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556,
    0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556,
    0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556,
    0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556,
    0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556,
    0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556,
    0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000,
    0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556,
    0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556,
    0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556,
    0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556,
    0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556,
    0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556,
    0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000,
    0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556,
    0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556,
    0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB,
    0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB,
    0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB,
    0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB,
    0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000,
    0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB,
    0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB,
    0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB,
    0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB,
    0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB,
    0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB,
    0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000,
    0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB,
    0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB,
};
extern const float lbl_803D0CF8[4] = {300.0f, -7900.0f, 1500.0f, -300.0f};
extern const char lbl_803D0D08[0x10] = "clDNStartCamera";
extern const char lbl_803D0D18[0x14] = "clMapEffectParts";
extern const char lbl_803D0D2C[0x28] = "!(jobj->flags & JOBJ_USE_QUATERNION)";
extern const char lbl_803D0D54[0x14] = "DNA_cameraman_a.dat";
extern const char lbl_803D0D68[0x10] = "ef_camflash.dat";
extern const char lbl_803D0D78[0xC] = "%s%c_joint";
extern const char lbl_803D0D84[0x18] = "cameraman_a_cameraman_";
extern const char lbl_803D0D9C[0x14] = "cameraman_a_flash_";

static inline float JObjGetTranslationX(HSD_JObj *jobj) {
    if (jobj == 0) {
        __assert(lbl_806DB4E0, 0x3F1, lbl_806DB4E8);
    }
    return jobj->translate.x;
}

static inline float JObjGetTranslationY(HSD_JObj *jobj) {
    if (jobj == 0) {
        __assert(lbl_806DB4E0, 0x3FD, lbl_806DB4E8);
    }
    return jobj->translate.y;
}

static inline float JObjGetTranslationZ(HSD_JObj *jobj) {
    if (jobj == 0) {
        __assert(lbl_806DB4E0, 0x409, lbl_806DB4E8);
    }
    return jobj->translate.z;
}

static inline unsigned char JObjMtxIsDirty(HSD_JObj *jobj) {
    if (jobj == 0) {
        __assert(lbl_806DB4E0, 0x25D, lbl_806DB4E8);
    }
    unsigned int flags = jobj->flags;
    unsigned char dirty = 0;
    if (!(flags & 0x00800000) && (flags & 0x40)) {
        dirty = 1;
    }
    return dirty;
}

static inline void JObjSetupMatrix(HSD_JObj *jobj) {
    if (jobj == 0) {
        __assert(lbl_806DB4E0, 0x47C, lbl_806DB4E8);
    }
    if (jobj != 0) {
        if (JObjMtxIsDirty(jobj)) {
            HSD_JObjSetupMatrixSub(jobj);
        }
    }
}

static inline void JObjSetRotationY(HSD_JObj *jobj, float y) {
    if (jobj == 0) {
        __assert(lbl_806DB4E0, 0x2B8, lbl_806DB4E8);
    }
    if (jobj->flags & 0x20000) {
        __assert(lbl_806DB4E0, 0x2B9, lbl_803D0D2C);
    }
    jobj->rotate.y = y;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

void clDNStartCamera::Draw() {
    Mtx m;

    if (hidden == 1) {
        return;
    }
    Object_RenderJObjTree(cam, 7);
    GXChannel ch(Archive_GetRootJObj(flash), HSD_JObjGetDObj(Archive_GetRootJObj(flash)), 0x40000000, 1);
    for (int i = 0; i < 6; i++) {
        if (flashes[i].fp.active) {
            PSMTXScale(m, flashes[i].fp.scale, flashes[i].fp.scale, flashes[i].fp.scale);
            m[0][3] = flashes[i].fp.owner->pos.x;
            m[1][3] = flashes[i].fp.owner->pos.y;
            m[2][3] = flashes[i].fp.owner->pos.z;
            Object_SetColorAlphaOnly(flash, 0, flashes[i].fp.alpha);
            ch.PushTransform(m);
        }
    }
}

void clDNStartCamera::Update() {
    KartRender *k;
    if ((k = g_playerRenderObj) == 0) {
        hidden = 0;
        return;
    }
    hidden = 1;
    const float *m = KartDriver_GetKartRootMtx(k);
    float a;
    float x = m[3];
    float z = m[11];
    if (x >= lbl_803D0CF8[0] && x <= lbl_803D0CF8[2] && z >= lbl_803D0CF8[1] && z <= lbl_803D0CF8[3]) {
        hidden = 0;
        for (int i = 0; i < 10; i++) {
            a = JObjGetTranslationX(men[i]) - x;
            a = atan2(a, JObjGetTranslationZ(men[i]) - z);
            JObjSetRotationY(men[i], lbl_806DB4F0 + a);
        }
    }
    for (int i = 0; i < 6; i++) {
        FlashPart *fp = &flashes[i].fp;
        if (!fp->active) {
            if (--flashes[i].timer > 0) {
                continue;
            }
            if (hidden == 1) {
                flashes[i].timer = 60;
                continue;
            }
            HSD_JObj *j = flashJoints[i];
            JObjSetupMatrix(j);
            flashes[i].pt.pos.x = j->mtx[0][3];
            flashes[i].pt.pos.y = j->mtx[1][3];
            flashes[i].pt.pos.z = j->mtx[2][3];
            flashes[i].fp.Start(&flashes[i].pt);
        } else {
            fp->Tick();
            if (!fp->active) {
                flashes[i].timer = rand() % 60;
            }
        }
    }
    if (hidden == 0) {
        clNormal3D_Exec(cam);
        Object_DriveAnimMatrix(cam);
    }
}

clDNStartCamera::~clDNStartCamera() {
    if (cam) {
        Object_DtorWithGXSync(cam, 1);
        cam = 0;
    }
    if (flash) {
        Object_DtorWithGXSync(flash, 1);
        flash = 0;
    }
}

clDNStartCamera::clDNStartCamera(HSD_JObj *at) {
    char name[0x40];

    flash = 0;
    cam = 0;
    hidden = 0;
    cam = new clNormal3D(lbl_803D0D54, 0);
    flash = new clNormal3D(lbl_803D0D68, 1);
    fn_80182954(Archive_GetRootJObj(flash), 1);
    HSD_JObjSetFlags(Archive_GetRootJObj(flash), 0x200);
    clNormal3D_SetScale(cam, 0, lbl_806DB4F4, lbl_806DB4F8, lbl_806DB4F4, lbl_806DB4F4);
    if (at) {
        Object_SetJObjPositionX(cam, JObjGetTranslationX(at));
        Object_SetJObjPositionY(cam, JObjGetTranslationY(at));
        Object_SetJObjField40(cam, JObjGetTranslationZ(at));
    }
    char c = 'a';
    for (int i = 0; i < 10; i++) {
        sprintf(name, lbl_803D0D78, lbl_803D0D84, c++);
        men[i] = ResolveJointByName(cam, name);
    }
    c = 'a';
    for (int i = 0; i < 6; i++) {
        flashes[i].timer = rand() % 10;
        flashes[i].fp.Init();
        flashes[i].pt.used = 0;
        sprintf(name, lbl_803D0D78, lbl_803D0D9C, c++);
        flashJoints[i] = ResolveJointByName(cam, name);
    }
}
