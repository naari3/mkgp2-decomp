#include "game/anon_8021A7C8_nm1.h"

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

extern KartModelNames lbl_804EDC88;
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


extern "C" KartModelResources lbl_803C4E60;


clCSOrgKartModel::clCSOrgKartModel(int character_, int variant, unsigned char withDriver, unsigned char flag) {
    KartModelNames *names = &lbl_804EDC88;
    KartModelResources *resources = &lbl_803C4E60;
    fn_8013BD7C();
    fn_8013C428();
    camA = lbl_806DAFE8;
    camB = lbl_806DAFE8;
    character = character_;
    animSel = 0;
    animTime = lbl_806DAFE8;
    animEnd = lbl_806DAFF0;
    kart = 0;
    tires = 0;
    driver = 0;
    driverAnim = 0;
    kartAnim = 0;
    anims[0] = 0;
    anims[1] = 0;
    anims[2] = 0;
    anims[3] = 0;
    pony = 0;
    ponyJoint = 0;
    if (character < 0 || character >= 13) {
        return;
    }
    const char **ent = GetKartModelNameEntry(character, variant);
    CharData *cd = GetCharacterDataEntry(character);
    kart = new clNormal3D(ent[0], flag);
    char buf[0x20];
    if (withDriver == 1) {
        driver = new clNormal3D(cd->driverFile, flag);
        driverAnim = new clNormal3D(cd->animFile, 0);
        clNormal3D_SetScale(driver, 0, lbl_806DAFE8, lbl_806DAFEC, lbl_806DAFE8, lbl_806DAFE8);
        switch (character) {
        case 3:
            ponyJoint = ResolveJointByName(driver, resources->name_180);
            pony = new clNormal3D(resources->name_19C, flag);
            clNormal3D_SetScale(pony, 0, lbl_806DAFE8, lbl_806DAFEC, lbl_806DAFE8, lbl_806DAFF4);
            break;
        }
        sprintf(buf, resources->name_1A8, names->drivers[character]);
        handJoints[0] = ResolveJointByName(driver, buf);
        sprintf(buf, resources->name_1C0, names->drivers[character]);
        handJoints[1] = ResolveJointByName(driver, buf);
        sprintf(buf, resources->name_1D8, names->drivers[character]);
        handJoints[2] = ResolveJointByName(driver, buf);
        HSD_JObjSetFlags(handJoints[1], 0x10);
        HSD_JObjSetFlags(handJoints[2], 0x10);
    }
    if (variant >= 2) {
        tires = new clNormal3D(names->tires[character_], flag);
    } else {
        tires = new clNormal3D(resources->name_1F0, flag);
    }
    tireJoints[0] = ResolveJointByName(tires, resources->name_200);
    tireJoints[1] = ResolveJointByName(tires, resources->name_218);
    tireJoints[2] = ResolveJointByName(tires, resources->name_230);
    tireJoints[3] = ResolveJointByName(tires, resources->name_248);
    Vec3 t;
    sprintf(buf, resources->name_260, names->drivers[character]);
    JObjGetTranslation(ResolveJointByName(kart, buf), &t);
    JObjSetTranslate(tireJoints[0], &t);
    sprintf(buf, resources->name_278, names->drivers[character]);
    JObjGetTranslation(ResolveJointByName(kart, buf), &t);
    JObjSetTranslate(tireJoints[1], &t);
    sprintf(buf, resources->name_290, names->drivers[character]);
    JObjGetTranslation(ResolveJointByName(kart, buf), &t);
    JObjSetTranslate(tireJoints[2], &t);
    sprintf(buf, resources->name_2A8, names->drivers[character]);
    JObjGetTranslation(ResolveJointByName(kart, buf), &t);
    JObjSetTranslate(tireJoints[3], &t);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_2C0), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_2D8), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_2F0), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_308), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_320), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_338), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_350), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_368), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_380), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_398), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_3B0), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_3C8), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_3E0), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_3F8), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_410), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_428), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_440), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_458), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_470), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_488), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_4A0), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_4B8), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_4D0), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_4E8), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_500), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_518), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_530), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, resources->name_548), 0x10);
    if (withDriver == 1) {
        for (int i = 0; i < 4; i++) {
            anims[i] = new clNormal3D(cd->anims[resources->animIds[i]], 0);
        }
        clNormal3D_SetScale(driverAnim, anims[0], lbl_806DAFF4, lbl_806DAFE8, lbl_806DAFE8, lbl_806DAFE8);
        ObjectTree_BlendOrCopy_Timed(driver, Archive_GetRootJObj(driverAnim), Archive_GetRootJObj(driver), lbl_806DAFE8, 0);
        if (flag) {
            clNormal3D_SetFlags(kart, 0x40000000, 0);
            clNormal3D_SetFlags(driver, 0x40000000, 0);
        }
    }
}

