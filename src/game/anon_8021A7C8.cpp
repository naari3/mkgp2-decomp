/*
 * 0x8021A7C8..0x8021B568: clCSOrgKartModel, the kart + driver model shown
 * on the result / course select screens (vtable lbl_804EDCFC, base
 * lbl_8048EAE8). The ctor addresses its joint-name literals off the TU
 * rodata pool (lbl_803C4E60), which this TU does not own.
 */

struct HSD_JObj {
    char pad00[0x14];
    unsigned int flags;
    char pad18[0x38 - 0x18];
    float tx;
    float ty;
    float tz;
    float mtx[3][4];
};

struct Vec3 {
    float x;
    float y;
    float z;
};

struct clNormal3D {
    char pad[0x5C];
    clNormal3D(const char *file, unsigned char flag);
    ~clNormal3D();
};

struct CharData {
    char pad00[0x4];
    const char *driverFile;
    const char *animFile;
    char pad0C[0x18 - 0xC];
    const char **anims;
};

void *operator new(unsigned long size);
void operator delete(void *p) throw();

extern "C" {
extern char lbl_806DAFD8[7];
extern char lbl_806DAFE0[5];
extern const char *lbl_804EDC88[13];
extern const char *lbl_804EDCBC[13];
extern const float lbl_806DAFE8;
extern const float lbl_806DAFEC;
extern const float lbl_806DAFF0;
extern const float lbl_806DAFF4;
void __assert(const char *file, int line, const char *expr);
void HSD_JObjSetupMatrixSub(HSD_JObj *jobj);
void HSD_JObjSetMtxDirtySub(HSD_JObj *jobj);
void HSD_JObjSetFlags(HSD_JObj *jobj, unsigned int flags);
void HSD_JObjSetFlagsAll(HSD_JObj *jobj, unsigned int flags);
void *fn_8013BC98(void);
void *fn_8013C3B8(void);
void fn_8013BB1C(void *cam, float a, float b);
unsigned char fn_8013BC38(void *cam);
void fn_8013C34C(void *l);
void fn_8013BBFC(void *cam);
void fn_8013BB9C(void *cam);
void fn_8013C334(void *l);
void fn_8013BCA0(void);
void fn_8013C3C0(void);
void fn_8013BD7C(void);
void fn_8013C428(void);
void Object_RenderJObjTree(clNormal3D *n, int mask);
void Object_SetAnimBinding(clNormal3D *n, void *anim, int a);
void Object_DriveAnimMatrix(clNormal3D *n);
void clNormal3D_Exec(clNormal3D *n);
void clNormal3D_SetScale(clNormal3D *n, void *anim, float t, float a, float b, float c);
void clNormal3D_SetFlags(clNormal3D *n, unsigned int flags, int a);
HSD_JObj *Archive_GetRootJObj(clNormal3D *n);
void ObjectTree_BlendOrCopy_Timed(clNormal3D *n, HSD_JObj *src, HSD_JObj *dst, float t, int a);
HSD_JObj *ResolveJointByName(clNormal3D *n, const char *name);
const char **GetKartModelNameEntry(int character, int variant);
CharData *GetCharacterDataEntry(int character);
int sprintf(char *buf, const char *fmt, ...);
}

static inline unsigned char JObjMtxIsDirty(HSD_JObj *jobj) {
    if (jobj == 0) {
        __assert(lbl_806DAFD8, 0x25D, lbl_806DAFE0);
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
        __assert(lbl_806DAFD8, 0x47C, lbl_806DAFE0);
    }
    if (jobj != 0) {
        if (JObjMtxIsDirty(jobj)) {
            HSD_JObjSetupMatrixSub(jobj);
        }
    }
}

static inline void JObjGetTranslation(HSD_JObj *jobj, Vec3 *t) {
    if (jobj == 0) {
        __assert(lbl_806DAFD8, 0x3E4, lbl_806DAFE0);
    }
    t->x = jobj->tx;
    t->y = jobj->ty;
    t->z = jobj->tz;
}

static inline void JObjSetTranslate(HSD_JObj *jobj, Vec3 *t) {
    if (jobj == 0) {
        __assert(lbl_806DAFD8, 0x3A9, lbl_806DAFE0);
    }
    jobj->tx = t->x;
    jobj->ty = t->y;
    jobj->tz = t->z;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

struct clCSModelInterface {
    virtual ~clCSModelInterface() {}
    virtual void Draw() = 0;
    virtual void _keyM();
};

struct clCSOrgKartModel : clCSModelInterface {
    clNormal3D *kart;
    clNormal3D *tires;
    clNormal3D *driver;
    clNormal3D *driverAnim;
    clNormal3D *anims[4];
    clNormal3D *pony;
    HSD_JObj *ponyJoint;
    HSD_JObj *tireJoints[4];
    HSD_JObj *handJoints[3];
    int character;
    int animSel;
    float animTime;
    float animEnd;
    void *kartAnim;
    float camA;
    float camB;
    clCSOrgKartModel(int character_, int variant, unsigned char withDriver, unsigned char flag);
    virtual void _keyM();
    ~clCSOrgKartModel();
    void Draw();
    void Update();
    void DrawPony() {
        if (pony != 0) {
            HSD_JObj *j = ponyJoint;
            if (j != 0) {
                JObjSetupMatrix(j);
                Object_SetAnimBinding(pony, j->mtx, 0);
                Object_DriveAnimMatrix(pony);
                Object_RenderJObjTree(pony, 7);
            }
        }
    }
};

void clCSOrgKartModel::Draw() {
    if (fn_8013BC98() != 0 && fn_8013C3B8() != 0) {
        if (kartAnim != 0) {
            Object_RenderJObjTree(kart, 7);
            Object_RenderJObjTree(tires, 7);
            if (driver != 0) {
                Object_RenderJObjTree(driver, 7);
            }
            DrawPony();
        } else {
            fn_8013BB1C(fn_8013BC98(), camA, camB);
            if (fn_8013BC38(fn_8013BC98())) {
                fn_8013C34C(fn_8013C3B8());
                fn_8013BBFC(fn_8013BC98());
                Object_RenderJObjTree(kart, 7);
                Object_RenderJObjTree(tires, 7);
                if (driver != 0) {
                    Object_RenderJObjTree(driver, 7);
                }
                DrawPony();
                fn_8013BB9C(fn_8013BC98());
                fn_8013C334(fn_8013C3B8());
            }
        }
    }
}

void clCSOrgKartModel::Update() {
    if (kartAnim != 0) {
        Object_SetAnimBinding(kart, kartAnim, 0);
    }
    if (driver != 0) {
        clNormal3D *a;
        if (animSel == 2) {
            a = anims[2];
        } else if (animSel == 3) {
            a = anims[3];
        } else {
            a = anims[1];
        }
        clNormal3D_SetScale(driverAnim, a, animTime, lbl_806DAFE8, lbl_806DAFE8, lbl_806DAFE8);
        ObjectTree_BlendOrCopy_Timed(driver, Archive_GetRootJObj(driverAnim), Archive_GetRootJObj(driver), lbl_806DAFE8, 0);
        Object_DriveAnimMatrix(driver);
        if (pony != 0) {
            clNormal3D_Exec(pony);
        }
        float t = animTime + lbl_806DAFEC;
        animTime = t;
        if (t >= animEnd) {
            animTime = lbl_806DAFE8;
        }
    }
}

clCSOrgKartModel::~clCSOrgKartModel() {
    if (kart != 0) {
        delete kart;
    }
    if (tires != 0) {
        delete tires;
    }
    if (driver != 0) {
        delete driver;
    }
    if (driverAnim != 0) {
        delete driverAnim;
    }
    for (int i = 0; i < 4; i++) {
        if (anims[i] != 0) {
            delete anims[i];
        }
    }
    if (pony != 0) {
        delete pony;
    }
    fn_8013BCA0();
    fn_8013C3C0();
}
