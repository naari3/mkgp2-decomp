/*
 * 0x8021A7C8..0x8021B568: clCSOrgKartModel, the kart + driver model shown
 * on the result / course select screens (vtable clCSOrgKartModel_vtable_804EDCFC, base
 * clCSModelInterface_vtable_8048EAE8). One TU, built with -inline deferred and -RTTI on, so the
 * functions are written in reverse address order (ctor, dtor, Update, Draw).
 * The class action (RTTI + vtable) runs before the deferred ctor is
 * generated, so the ctor reaches the vtable through the .data section anchor
 * (lbl_804EDC88 + 0x74), like TaMode (docs/matching_rules.md section 6).
 */

#include "game/types/size_t.h"
#include "game/types/HSD_JObj.h"

#include "game/types/Vec3.h"

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

void *operator new(size_t size);
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
/* The frame comes before the anim pointer: same registers (r4/f1) as
 * (n, anim, t, ...), but the arguments are evaluated in this order, which
 * decides the schedule of the anim load (regalloc_patterns, arg-order). */
void clNormal3D_SetScale(clNormal3D *n, float t, void *anim, float a, float b, float c);
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
    t->x = jobj->translate.x;
    t->y = jobj->translate.y;
    t->z = jobj->translate.z;
}

static inline void JObjSetTranslate(HSD_JObj *jobj, Vec3 *t) {
    if (jobj == 0) {
        __assert(lbl_806DAFD8, 0x3A9, lbl_806DAFE0);
    }
    jobj->translate.x = t->x;
    jobj->translate.y = t->y;
    jobj->translate.z = t->z;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

struct clCSModelInterface {
    virtual ~clCSModelInterface() {}
    virtual void Draw();
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
    virtual ~clCSOrgKartModel();
    virtual void Draw();
    virtual void Slot4() = 0;
    virtual void Slot5() = 0;
    virtual void Slot6() = 0;
    virtual void Slot7() = 0;
    virtual void Slot8() = 0;
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
}
static const char *drivers[13] = {lbl_806DAF78, lbl_806DAF80, lbl_806DAF88, lbl_806DAF90, lbl_806DAF98, lbl_806DAFA0, lbl_806DAFA8, lbl_806DAFB0, lbl_806DAFB8, pool_803C4E70, lbl_806DAFC0, lbl_806DAFC8, lbl_806DAFD0};
static const char *tireFiles[13] = {pool_803C4E7C, pool_803C4E94, pool_803C4EAC, pool_803C4EC4, pool_803C4EDC, pool_803C4EF4, pool_803C4F0C, pool_803C4F24, pool_803C4F3C, pool_803C4F54, pool_803C4F70, pool_803C4F88, pool_803C4FA0};


#pragma push
#pragma optimize_for_size on
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
        clNormal3D_SetScale(driver, lbl_806DAFE8, 0, lbl_806DAFEC, lbl_806DAFE8, lbl_806DAFE8);
        switch (character) {
        case 3:
            ponyJoint = ResolveJointByName(driver, "chara_peach_pony_null_joint");
            pony = new clNormal3D("pony.dat", flag);
            clNormal3D_SetScale(pony, lbl_806DAFE8, 0, lbl_806DAFEC, lbl_806DAFE8, lbl_806DAFF4);
            break;
        }
        sprintf(buf, "chara_%s_hand_goo_joint", drivers[character]);
        handJoints[0] = ResolveJointByName(driver, buf);
        sprintf(buf, "chara_%s_hand_pa_joint", drivers[character]);
        handJoints[1] = ResolveJointByName(driver, buf);
        sprintf(buf, "chara_%s_hand_fin_joint", drivers[character]);
        handJoints[2] = ResolveJointByName(driver, buf);
        HSD_JObjSetFlags(handJoints[1], 0x10);
        HSD_JObjSetFlags(handJoints[2], 0x10);
    }
    if (variant >= 2) {
        tires = new clNormal3D(tireFiles[character_], flag);
    } else {
        tires = new clNormal3D("cart_tire.dat", flag);
    }
    tireJoints[0] = ResolveJointByName(tires, "cart_tireset_fl_joint");
    tireJoints[1] = ResolveJointByName(tires, "cart_tireset_fr_joint");
    tireJoints[2] = ResolveJointByName(tires, "cart_tireset_rl_joint");
    tireJoints[3] = ResolveJointByName(tires, "cart_tireset_rr_joint");
    Vec3 t;
    sprintf(buf, "%s_cart_tire_fl_joint", drivers[character]);
    JObjGetTranslation(ResolveJointByName(kart, buf), &t);
    JObjSetTranslate(tireJoints[0], &t);
    sprintf(buf, "%s_cart_tire_fr_joint", drivers[character]);
    JObjGetTranslation(ResolveJointByName(kart, buf), &t);
    JObjSetTranslate(tireJoints[1], &t);
    sprintf(buf, "%s_cart_tire_rl_joint", drivers[character]);
    JObjGetTranslation(ResolveJointByName(kart, buf), &t);
    JObjSetTranslate(tireJoints[2], &t);
    sprintf(buf, "%s_cart_tire_rr_joint", drivers[character]);
    JObjGetTranslation(ResolveJointByName(kart, buf), &t);
    JObjSetTranslate(tireJoints[3], &t);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_big_tire_fl_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_big_tire_fr_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_big_tire_rl_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_big_tire_rr_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_kaku_tire_fl_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_kaku_tire_fr_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_kaku_tire_rl_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_kaku_tire_rr_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_oil_tire_fl_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_oil_tire_fr_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_oil_tire_rl_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_oil_tire_rr_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_oil_grid_fl_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_oil_grid_fr_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_oil_grid_rl_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_oil_grid_rr_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_punk_grid_fl_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_punk_grid_fr_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_punk_grid_rl_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_punk_grid_rr_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_punk_tire_fl_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_punk_tire_fr_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_punk_tire_rl_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_punk_tire_rr_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_snow_tire_fl_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_snow_tire_fr_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_snow_tire_rl_joint"), 0x10);
    HSD_JObjSetFlagsAll(ResolveJointByName(tires, "cart_snow_tire_rr_joint"), 0x10);
    if (withDriver == 1) {
        const int *id = animIds;
        for (int i = 0; i < 4; id++, i++) {
            anims[i] = new clNormal3D(cd->anims[*id], 0);
        }
        clNormal3D_SetScale(driverAnim, lbl_806DAFF4, anims[0], lbl_806DAFE8, lbl_806DAFE8, lbl_806DAFE8);
        ObjectTree_BlendOrCopy_Timed(driver, Archive_GetRootJObj(driverAnim), Archive_GetRootJObj(driver), lbl_806DAFE8, 0);
        if (flag) {
            clNormal3D_SetFlags(kart, 0x40000000, 0);
            clNormal3D_SetFlags(driver, 0x40000000, 0);
        }
    }
}

#pragma pop

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
        clNormal3D_SetScale(driverAnim, animTime, a, lbl_806DAFE8, lbl_806DAFE8, lbl_806DAFE8);
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

#pragma readonly_strings on
