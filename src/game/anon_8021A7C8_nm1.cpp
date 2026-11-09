#include "game/anon_8021A7C8_nm1.h"

/*
 * 0x8021A7C8..0x8021B568: clCSOrgKartModel, the kart + driver model shown
 * on the result / course select screens (vtable lbl_804EDCFC, base
 * lbl_8048EAE8). The ctor addresses its joint-name literals off the TU
 * rodata pool (lbl_803C4E60). This ctor TU owns the resource strings,
 * animation IDs, driver/tire name tables, and model type/vtable records.
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


static const int animIds[4] = {0, 5, 42, 43};
static const char pool_803C4E70[9] = "mspacman";
static const char pool_803C4E7C[22] = "sp_tire_set_mario.dat";
static const char pool_803C4E94[22] = "sp_tire_set_luigi.dat";
static const char pool_803C4EAC[22] = "sp_tire_set_wario.dat";
static const char pool_803C4EC4[22] = "sp_tire_set_peach.dat";
static const char pool_803C4EDC[22] = "sp_tire_set_koopa.dat";
static const char pool_803C4EF4[24] = "sp_tire_set_kinopio.dat";
static const char pool_803C4F0C[23] = "sp_tire_set_donkey.dat";
static const char pool_803C4F24[22] = "sp_tire_set_yoshi.dat";
static const char pool_803C4F3C[23] = "sp_tire_set_pacman.dat";
static const char pool_803C4F54[25] = "sp_tire_set_mspacman.dat";
static const char pool_803C4F70[24] = "sp_tire_set_monster.dat";
static const char pool_803C4F88[24] = "sp_tire_set_waluigi.dat";
static const char pool_803C4FA0[24] = "sp_tire_set_mametch.dat";
static const char pool_803C4FB8[17] = "clCSOrgKartModel";
static const char pool_803C4FCC[19] = "clCSModelInterface";
static const char pool_803C4FE0[28] = "chara_peach_pony_null_joint";
static const char pool_803C4FFC[9] = "pony.dat";
static const char pool_803C5008[24] = "chara_%s_hand_goo_joint";
static const char pool_803C5020[23] = "chara_%s_hand_pa_joint";
static const char pool_803C5038[24] = "chara_%s_hand_fin_joint";
static const char pool_803C5050[14] = "cart_tire.dat";
static const char pool_803C5060[22] = "cart_tireset_fl_joint";
static const char pool_803C5078[22] = "cart_tireset_fr_joint";
static const char pool_803C5090[22] = "cart_tireset_rl_joint";
static const char pool_803C50A8[22] = "cart_tireset_rr_joint";
static const char pool_803C50C0[22] = "%s_cart_tire_fl_joint";
static const char pool_803C50D8[22] = "%s_cart_tire_fr_joint";
static const char pool_803C50F0[22] = "%s_cart_tire_rl_joint";
static const char pool_803C5108[22] = "%s_cart_tire_rr_joint";
static const char pool_803C5120[23] = "cart_big_tire_fl_joint";
static const char pool_803C5138[23] = "cart_big_tire_fr_joint";
static const char pool_803C5150[23] = "cart_big_tire_rl_joint";
static const char pool_803C5168[23] = "cart_big_tire_rr_joint";
static const char pool_803C5180[24] = "cart_kaku_tire_fl_joint";
static const char pool_803C5198[24] = "cart_kaku_tire_fr_joint";
static const char pool_803C51B0[24] = "cart_kaku_tire_rl_joint";
static const char pool_803C51C8[24] = "cart_kaku_tire_rr_joint";
static const char pool_803C51E0[23] = "cart_oil_tire_fl_joint";
static const char pool_803C51F8[23] = "cart_oil_tire_fr_joint";
static const char pool_803C5210[23] = "cart_oil_tire_rl_joint";
static const char pool_803C5228[23] = "cart_oil_tire_rr_joint";
static const char pool_803C5240[23] = "cart_oil_grid_fl_joint";
static const char pool_803C5258[23] = "cart_oil_grid_fr_joint";
static const char pool_803C5270[23] = "cart_oil_grid_rl_joint";
static const char pool_803C5288[23] = "cart_oil_grid_rr_joint";
static const char pool_803C52A0[24] = "cart_punk_grid_fl_joint";
static const char pool_803C52B8[24] = "cart_punk_grid_fr_joint";
static const char pool_803C52D0[24] = "cart_punk_grid_rl_joint";
static const char pool_803C52E8[24] = "cart_punk_grid_rr_joint";
static const char pool_803C5300[24] = "cart_punk_tire_fl_joint";
static const char pool_803C5318[24] = "cart_punk_tire_fr_joint";
static const char pool_803C5330[24] = "cart_punk_tire_rl_joint";
static const char pool_803C5348[24] = "cart_punk_tire_rr_joint";
static const char pool_803C5360[24] = "cart_snow_tire_fl_joint";
static const char pool_803C5378[24] = "cart_snow_tire_fr_joint";
static const char pool_803C5390[24] = "cart_snow_tire_rl_joint";
static const char pool_803C53A8[24] = "cart_snow_tire_rr_joint";

extern "C" {
extern const char lbl_806DAF78[];
extern const char lbl_806DAF80[];
extern const char lbl_806DAF88[];
extern const char lbl_806DAF90[];
extern const char lbl_806DAF98[];
extern const char lbl_806DAFA0[];
extern const char lbl_806DAFA8[];
extern const char lbl_806DAFB0[];
extern const char lbl_806DAFB8[];
extern const char lbl_806DAFC0[];
extern const char lbl_806DAFC8[];
extern const char lbl_806DAFD0[];
extern void *lbl_806D0488[2];
extern void *lbl_806D0490[2];
void fn_8021AAE8();
void fn_8021A7C8();
}
static const char *drivers[13] = {lbl_806DAF78, lbl_806DAF80, lbl_806DAF88, lbl_806DAF90, lbl_806DAF98, lbl_806DAFA0, lbl_806DAFA8, lbl_806DAFB0, lbl_806DAFB8, pool_803C4E70, lbl_806DAFC0, lbl_806DAFC8, lbl_806DAFD0};
static const char *tireFiles[13] = {pool_803C4E7C, pool_803C4E94, pool_803C4EAC, pool_803C4EC4, pool_803C4EDC, pool_803C4EF4, pool_803C4F0C, pool_803C4F24, pool_803C4F3C, pool_803C4F54, pool_803C4F70, pool_803C4F88, pool_803C4FA0};
/* Existing type records refer to the shared small-data RTTI descriptors. */
struct KartTypeInfo { void *name; void *bases; void *reserved; };
static KartTypeInfo modelType = { lbl_806D0488, 0, 0 };
/* The five remaining abstract model-interface slots have no implementation. */
extern "C" void *__vt__16clCSOrgKartModel[9] = {
    lbl_806D0490, 0, (void *)fn_8021AAE8, (void *)fn_8021A7C8,
    0, 0, 0, 0, 0
};


clCSOrgKartModel::clCSOrgKartModel(int character_, int variant, unsigned char withDriver, unsigned char flag) {
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
            ponyJoint = ResolveJointByName(driver, pool_803C4FE0);
            pony = new clNormal3D(pool_803C4FFC, flag);
            clNormal3D_SetScale(pony, 0, lbl_806DAFE8, lbl_806DAFEC, lbl_806DAFE8, lbl_806DAFF4);
            break;
        }
        sprintf(buf, pool_803C5008, drivers[character]);
        handJoints[0] = ResolveJointByName(driver, buf);
        sprintf(buf, pool_803C5020, drivers[character]);
        handJoints[1] = ResolveJointByName(driver, buf);
        sprintf(buf, pool_803C5038, drivers[character]);
        handJoints[2] = ResolveJointByName(driver, buf);
        HSD_JObjSetFlags(handJoints[1], 0x10);
        HSD_JObjSetFlags(handJoints[2], 0x10);
    }
    if (variant >= 2) {
        tires = new clNormal3D(tireFiles[character_], flag);
    } else {
        tires = new clNormal3D(pool_803C5050, flag);
    }
    tireJoints[0] = ResolveJointByName(tires, pool_803C5060);
    tireJoints[1] = ResolveJointByName(tires, pool_803C5078);
    tireJoints[2] = ResolveJointByName(tires, pool_803C5090);
    tireJoints[3] = ResolveJointByName(tires, pool_803C50A8);
    Vec3 t;
    sprintf(buf, pool_803C50C0, drivers[character]);
    JObjGetTranslation(ResolveJointByName(kart, buf), &t);
    JObjSetTranslate(tireJoints[0], &t);
    sprintf(buf, pool_803C50D8, drivers[character]);
    JObjGetTranslation(ResolveJointByName(kart, buf), &t);
    JObjSetTranslate(tireJoints[1], &t);
    sprintf(buf, pool_803C50F0, drivers[character]);
    JObjGetTranslation(ResolveJointByName(kart, buf), &t);
    JObjSetTranslate(tireJoints[2], &t);
    sprintf(buf, pool_803C5108, drivers[character]);
    JObjGetTranslation(ResolveJointByName(kart, buf), &t);
    JObjSetTranslate(tireJoints[3], &t);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C5120), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C5138), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C5150), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C5168), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C5180), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C5198), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C51B0), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C51C8), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C51E0), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C51F8), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C5210), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C5228), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C5240), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C5258), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C5270), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C5288), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C52A0), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C52B8), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C52D0), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C52E8), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C5300), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C5318), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C5330), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C5348), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C5360), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C5378), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C5390), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, pool_803C53A8), 0x10);
    if (withDriver == 1) {
        const int *id = animIds;
        for (int i = 0; i < 4; id++, i++) {
            anims[i] = new clNormal3D(cd->anims[*id], 0);
        }
        clNormal3D_SetScale(driverAnim, anims[0], lbl_806DAFF4, lbl_806DAFE8, lbl_806DAFE8, lbl_806DAFE8);
        ObjectTree_BlendOrCopy_Timed(driver, Archive_GetRootJObj(driverAnim), Archive_GetRootJObj(driver), lbl_806DAFE8, 0);
        if (flag) {
            clNormal3D_SetFlags(kart, 0x40000000, 0);
            clNormal3D_SetFlags(driver, 0x40000000, 0);
        }
    }
}

