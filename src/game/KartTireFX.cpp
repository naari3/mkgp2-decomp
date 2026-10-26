/* KartTireFX: per-kart tire model. Loads either the character's tire set
 * (sp_tire_set_*.dat) or the shared cart_tire.dat, resolves every tire,
 * grid and wheel-rotation joint by name, and switches the visible gear
 * stage (normal/kaku/oil/punk/snow) per side.
 *
 * The HSD JObj helpers below are this HSD version's jobj.h inlines (its
 * assert line numbers differ from melee's).
 *
 * Built with -inline deferred, so functions are written in reverse address
 * order: the compiler emits .text (and extab) reversed, while .rodata keeps
 * parse order. That is what puts the three local {1, 1, 1} scale
 * initializers first in .rodata (SetVisibleAll4Wheels, 84_8c, 88_90), then
 * the ResolveJoints strings, and the inline assert string last. */
#pragma readonly_strings on

typedef float Mtx[3][4];

struct Vec3 {
    float x;
    float y;
    float z;
};

struct HSD_JObj {
    char pad00[0x14];
    unsigned int flags; /* 0x14 */
    char pad18[0x4];
    float rotX;         /* 0x1C */
    char pad20[0xC];
    Vec3 scale;         /* 0x2C */
    char pad38[0xC];
    Mtx mtx;            /* 0x44 */
};

class clNormal3D {
public:
    clNormal3D(const char *filename, int useSkinModel);
    ~clNormal3D();

private:
    char data[0x5c];
};

void *operator new(unsigned long);
void operator delete(void *);

extern "C" {
void __assert(const char *file, int line, const char *cond);
void HSD_JObjSetMtxDirtySub(HSD_JObj *jobj);
void HSD_JObjSetupMatrixSub(HSD_JObj *jobj);
void HSD_JObjCheckDependAll(HSD_JObj *jobj);
void PSMTXCopy(const Mtx src, Mtx dst);
HSD_JObj *ResolveJointByName(clNormal3D *model, const char *name);
HSD_JObj *Archive_GetRootJObj(clNormal3D *model);
void Object_RenderJObjTree(clNormal3D *model, int mask);
void JObj_Show(clNormal3D *model, HSD_JObj *jobj, int flag);
void JObj_Hide(clNormal3D *model, HSD_JObj *jobj, int flag);

extern float lbl_803FE018[];
}

static inline bool HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    bool result;
    if (!jobj) {
        __assert("jobj.h", 0x25d, "jobj");
    }
    result = false;
    if (!(jobj->flags & 0x00800000) && (jobj->flags & 0x40)) {
        result = true;
    }
    return result;
}

#define HSD_JObjSetMtxDirty(jobj)                        \
    {                                                    \
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj)) {    \
            HSD_JObjSetMtxDirtySub(jobj);                \
        }                                                \
    }

static inline void HSD_JObjSetMtxDirtyInline(HSD_JObj *jobj)
{
    HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetupMatrix(HSD_JObj *jobj)
{
    if (!jobj || !HSD_JObjMtxIsDirty(jobj)) {
        return;
    }
    HSD_JObjSetupMatrixSub(jobj);
}

static inline void HSD_JObjSetRotationX(HSD_JObj *jobj, float x)
{
    if (!jobj) {
        __assert("jobj.h", 0x2a4, "jobj");
    }
    if (jobj->flags & 0x20000) {
        __assert("jobj.h", 0x2a5, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    }
    jobj->rotX = x;
    if (!(jobj->flags & 0x02000000)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetScale(HSD_JObj *jobj, Vec3 *scale)
{
    if (!jobj) {
        __assert("jobj.h", 0x316, "jobj");
    }
    if (!scale) {
        __assert("jobj.h", 0x317, "scale");
    }
    jobj->scale = *scale;
    if (!(jobj->flags & 0x02000000)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline float *HSD_JObjGetMtxPtr(HSD_JObj *jobj)
{
    if (!jobj) {
        __assert("jobj.h", 0x47c, "jobj");
    }
    HSD_JObjSetupMatrix(jobj);
    return jobj->mtx[0];
}

static inline void HSD_JObjCopyMtx(HSD_JObj *jobj, Mtx mtx)
{
    if (!jobj) {
        __assert("jobj.h", 0x495, "jobj");
    }
    if (!mtx) {
        __assert("jobj.h", 0x496, "mtx");
    }
    PSMTXCopy(mtx, jobj->mtx);
}

static inline void HSD_JObjSetUserMtx(HSD_JObj *jobj, Mtx mtx)
{
    HSD_JObjCopyMtx(jobj, mtx);
    jobj->flags |= 0x03800000;
    HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetUserMtxP(HSD_JObj *jobj, float *mtx)
{
    HSD_JObjSetUserMtx(jobj, (float (*)[4])mtx);
}

class KartTireFX {
public:
    KartTireFX(int kind, int mode, HSD_JObj *srcFL, HSD_JObj *srcFR, HSD_JObj *srcRL,
               HSD_JObj *srcRR);
    ~KartTireFX();

    unsigned char loaded; /* 0x00 */
    float frontSpin;      /* 0x04 */
    float rearSpin;       /* 0x08 */
    Vec3 scale;           /* 0x0C */
    int leftStage;        /* 0x18 */
    int rightStage;       /* 0x1C */
    clNormal3D *model;    /* 0x20 */
    HSD_JObj *src[4];     /* 0x24 */
    HSD_JObj *kakuTireFL; /* 0x34 */
    HSD_JObj *kakuTireFR; /* 0x38 */
    HSD_JObj *kakuTireRL; /* 0x3C */
    HSD_JObj *kakuTireRR; /* 0x40 */
    HSD_JObj *oilTireFL; /* 0x44 */
    HSD_JObj *oilTireFR; /* 0x48 */
    HSD_JObj *oilTireRL; /* 0x4C */
    HSD_JObj *oilTireRR; /* 0x50 */
    HSD_JObj *oilGridFL; /* 0x54 */
    HSD_JObj *oilGridFR; /* 0x58 */
    HSD_JObj *oilGridRL; /* 0x5C */
    HSD_JObj *oilGridRR; /* 0x60 */
    HSD_JObj *nomalTireFL; /* 0x64 */
    HSD_JObj *nomalTireFR; /* 0x68 */
    HSD_JObj *nomalTireRL; /* 0x6C */
    HSD_JObj *nomalTireRR; /* 0x70 */
    HSD_JObj *tiresetFL; /* 0x74 */
    HSD_JObj *tiresetFR; /* 0x78 */
    HSD_JObj *tiresetRL; /* 0x7C */
    HSD_JObj *tiresetRR; /* 0x80 */
    HSD_JObj *rotFL; /* 0x84 */
    HSD_JObj *rotFR; /* 0x88 */
    HSD_JObj *rotRL; /* 0x8C */
    HSD_JObj *rotRR; /* 0x90 */
    HSD_JObj *punkTireFL; /* 0x94 */
    HSD_JObj *punkTireFR; /* 0x98 */
    HSD_JObj *punkTireRL; /* 0x9C */
    HSD_JObj *punkTireRR; /* 0xA0 */
    HSD_JObj *punkGridFL; /* 0xA4 */
    HSD_JObj *punkGridFR; /* 0xA8 */
    HSD_JObj *punkGridRL; /* 0xAC */
    HSD_JObj *punkGridRR; /* 0xB0 */
    HSD_JObj *snowTireFL; /* 0xB4 */
    HSD_JObj *snowTireFR; /* 0xB8 */
    HSD_JObj *snowTireRL; /* 0xBC */
    HSD_JObj *snowTireRR; /* 0xC0 */
};

extern "C" {
void KartTireFX_ShowGearStageJObjs(KartTireFX *self);
unsigned char KartTireFX_ResolveJoints(KartTireFX *self, int kind, int mode);
}

KartTireFX::KartTireFX(int kind, int mode, HSD_JObj *srcFL, HSD_JObj *srcFR, HSD_JObj *srcRL,
                       HSD_JObj *srcRR)
{
    this->loaded = KartTireFX_ResolveJoints(this, kind, mode);
    this->leftStage = 0;
    this->rightStage = 0;
    this->frontSpin = 1.0f;
    this->rearSpin = 1.0f;
    this->src[0] = srcFL;
    this->src[1] = srcFR;
    this->src[2] = srcRL;
    this->src[3] = srcRR;
    /* Never true; the target keeps both compares. */
    if (kind < 0 && kind >= 13) {
        this->scale.x = 1000.0f;
        this->scale.y = 1000.0f;
        this->scale.z = 1000.0f;
    } else if (mode == 2 || mode == 3) {
        this->scale.x = 1000.0f;
        this->scale.y = 1000.0f;
        this->scale.z = 1000.0f;
    } else {
        this->scale.x = lbl_803FE018[kind];
        this->scale.y = lbl_803FE018[kind];
        this->scale.z = lbl_803FE018[kind];
    }
}

KartTireFX::~KartTireFX()
{
    if (this->loaded == 1) {
        if (this->model) {
            delete this->model;
        }
        this->model = 0;
    }
}

extern "C" {

int KartTireFX_ApplyAndRender(KartTireFX *self)
{
    if (self->loaded == 0) {
        return 0;
    }
    if (self->tiresetFL) {
        HSD_JObjSetUserMtxP(self->tiresetFL, HSD_JObjGetMtxPtr(self->src[0]));
    }
    if (self->tiresetFR) {
        HSD_JObjSetUserMtxP(self->tiresetFR, HSD_JObjGetMtxPtr(self->src[1]));
    }
    if (self->tiresetRL) {
        HSD_JObjSetUserMtxP(self->tiresetRL, HSD_JObjGetMtxPtr(self->src[2]));
    }
    if (self->tiresetRR) {
        HSD_JObjSetUserMtxP(self->tiresetRR, HSD_JObjGetMtxPtr(self->src[3]));
    }

    if (self->rotFL) {
        HSD_JObjSetRotationX(self->rotFL, self->frontSpin);
    }
    if (self->rotFR) {
        HSD_JObjSetRotationX(self->rotFR, self->frontSpin);
    }
    if (self->rotRL) {
        HSD_JObjSetRotationX(self->rotRL, self->rearSpin);
    }
    if (self->rotRR) {
        HSD_JObjSetRotationX(self->rotRR, self->rearSpin);
    }
    KartTireFX_ShowGearStageJObjs(self);
    HSD_JObjSetMtxDirtyInline(Archive_GetRootJObj(self->model));
    HSD_JObjCheckDependAll(Archive_GetRootJObj(self->model));
    Object_RenderJObjTree(self->model, 7);
    return 1;
}

void KartTireFX_SetPitch(KartTireFX *self, float value)
{
    self->frontSpin = value;
}

void KartTireFX_SetYaw(KartTireFX *self, float value)
{
    self->rearSpin = value;
}

void KartTireFX_AddSpinBoth(KartTireFX *self, float delta)
{
    self->frontSpin += delta;
    self->rearSpin += delta;
}

void KartTireFX_AddPitch(KartTireFX *self, float delta)
{
    self->frontSpin += delta;
}

void KartTireFX_AddYaw(KartTireFX *self, float delta)
{
    self->rearSpin += delta;
}

void KartTireFX_SetVisibleAll4Wheels(KartTireFX *self, int stage)
{
    self->leftStage = stage;
    self->rightStage = stage;
    if (stage == 0) {
        if (self->rotFL) {
            HSD_JObjSetScale(self->rotFL, &self->scale);
        }
        if (self->rotRL) {
            HSD_JObjSetScale(self->rotRL, &self->scale);
        }
        if (self->rotFR) {
            HSD_JObjSetScale(self->rotFR, &self->scale);
        }
        if (self->rotRR) {
            HSD_JObjSetScale(self->rotRR, &self->scale);
        }
    } else {
        Vec3 one = {1.0f, 1.0f, 1.0f};
        if (self->rotFL) {
            HSD_JObjSetScale(self->rotFL, &one);
        }
        if (self->rotRL) {
            HSD_JObjSetScale(self->rotRL, &one);
        }
        if (self->rotFR) {
            HSD_JObjSetScale(self->rotFR, &one);
        }
        if (self->rotRR) {
            HSD_JObjSetScale(self->rotRR, &one);
        }
    }
}

void KartTireFX_SetRollPair_Joints84_8c(KartTireFX *self, int stage)
{
    self->leftStage = stage;
    if (self->leftStage == 0) {
        if (self->rotFL) {
            HSD_JObjSetScale(self->rotFL, &self->scale);
        }
        if (self->rotRL) {
            HSD_JObjSetScale(self->rotRL, &self->scale);
        }
    } else {
        Vec3 one = {1.0f, 1.0f, 1.0f};
        if (self->rotFL) {
            HSD_JObjSetScale(self->rotFL, &one);
        }
        if (self->rotRL) {
            HSD_JObjSetScale(self->rotRL, &one);
        }
    }
}

void KartTireFX_SetRollPair_Joints88_90(KartTireFX *self, int stage)
{
    self->rightStage = stage;
    if (self->rightStage == 0) {
        if (self->rotFR) {
            HSD_JObjSetScale(self->rotFR, &self->scale);
        }
        if (self->rotRR) {
            HSD_JObjSetScale(self->rotRR, &self->scale);
        }
    } else {
        Vec3 one = {1.0f, 1.0f, 1.0f};
        if (self->rotFR) {
            HSD_JObjSetScale(self->rotFR, &one);
        }
        if (self->rotRR) {
            HSD_JObjSetScale(self->rotRR, &one);
        }
    }
}

unsigned char KartTireFX_ResolveJoints(KartTireFX *self, int kind, int mode)
{
    const char *tireSets[13] = {
        "sp_tire_set_mario.dat",   "sp_tire_set_luigi.dat",    "sp_tire_set_wario.dat",
        "sp_tire_set_peach.dat",   "sp_tire_set_koopa.dat",    "sp_tire_set_kinopio.dat",
        "sp_tire_set_donkey.dat",  "sp_tire_set_yoshi.dat",    "sp_tire_set_pacman.dat",
        "sp_tire_set_mspacman.dat", "sp_tire_set_monster.dat", "sp_tire_set_waluigi.dat",
        "sp_tire_set_mametch.dat",
    };

    if (mode == 2 || mode == 3) {
        self->model = new clNormal3D(tireSets[kind], 0);
    } else {
        self->model = new clNormal3D("cart_tire.dat", 0);
    }
    if (self->model == 0) {
        return 0;
    }
    self->kakuTireFL = ResolveJointByName(self->model, "cart_kaku_tire_fl_joint");
    self->kakuTireFR = ResolveJointByName(self->model, "cart_kaku_tire_fr_joint");
    self->kakuTireRL = ResolveJointByName(self->model, "cart_kaku_tire_rl_joint");
    self->kakuTireRR = ResolveJointByName(self->model, "cart_kaku_tire_rr_joint");
    self->oilTireFL = ResolveJointByName(self->model, "cart_oil_tire_fl_joint");
    self->oilTireFR = ResolveJointByName(self->model, "cart_oil_tire_fr_joint");
    self->oilTireRL = ResolveJointByName(self->model, "cart_oil_tire_rl_joint");
    self->oilTireRR = ResolveJointByName(self->model, "cart_oil_tire_rr_joint");
    self->oilGridFL = ResolveJointByName(self->model, "cart_oil_grid_fl_joint");
    self->oilGridFR = ResolveJointByName(self->model, "cart_oil_grid_fr_joint");
    self->oilGridRL = ResolveJointByName(self->model, "cart_oil_grid_rl_joint");
    self->oilGridRR = ResolveJointByName(self->model, "cart_oil_grid_rr_joint");
    self->nomalTireFL = ResolveJointByName(self->model, "cart_nomal_tire_fl_joint");
    self->nomalTireFR = ResolveJointByName(self->model, "cart_nomal_tire_fr_joint");
    self->nomalTireRL = ResolveJointByName(self->model, "cart_nomal_tire_rl_joint");
    self->nomalTireRR = ResolveJointByName(self->model, "cart_nomal_tire_rr_joint");
    self->tiresetFL = ResolveJointByName(self->model, "cart_tireset_fl_joint");
    self->tiresetFR = ResolveJointByName(self->model, "cart_tireset_fr_joint");
    self->tiresetRL = ResolveJointByName(self->model, "cart_tireset_rl_joint");
    self->tiresetRR = ResolveJointByName(self->model, "cart_tireset_rr_joint");
    self->rotFL = ResolveJointByName(self->model, "cart_tire_fl_rot_joint");
    self->rotFR = ResolveJointByName(self->model, "cart_tire_fr_rot_joint");
    self->rotRL = ResolveJointByName(self->model, "cart_tire_rl_rot_joint");
    self->rotRR = ResolveJointByName(self->model, "cart_tire_rr_rot_joint");
    self->punkTireFL = ResolveJointByName(self->model, "cart_punk_tire_fl_joint");
    self->punkTireFR = ResolveJointByName(self->model, "cart_punk_tire_fr_joint");
    self->punkTireRL = ResolveJointByName(self->model, "cart_punk_tire_rl_joint");
    self->punkTireRR = ResolveJointByName(self->model, "cart_punk_tire_rr_joint");
    self->punkGridFL = ResolveJointByName(self->model, "cart_punk_grid_fl_joint");
    self->punkGridFR = ResolveJointByName(self->model, "cart_punk_grid_fr_joint");
    self->punkGridRL = ResolveJointByName(self->model, "cart_punk_grid_rl_joint");
    self->punkGridRR = ResolveJointByName(self->model, "cart_punk_grid_rr_joint");
    self->snowTireFL = ResolveJointByName(self->model, "cart_snow_tire_fl_joint");
    self->snowTireFR = ResolveJointByName(self->model, "cart_snow_tire_fr_joint");
    self->snowTireRL = ResolveJointByName(self->model, "cart_snow_tire_rl_joint");
    self->snowTireRR = ResolveJointByName(self->model, "cart_snow_tire_rr_joint");
    return 1;
}

void KartTireFX_ShowGearStageJObjs(KartTireFX *self)
{
    if (self->leftStage == 0) {
        if (self->nomalTireFL) {
            JObj_Show(self->model, self->nomalTireFL, 0x10);
        }
        if (self->nomalTireRL) {
            JObj_Show(self->model, self->nomalTireRL, 0x10);
        }
    } else {
        if (self->nomalTireFL) {
            JObj_Hide(self->model, self->nomalTireFL, 0x10);
        }
        if (self->nomalTireRL) {
            JObj_Hide(self->model, self->nomalTireRL, 0x10);
        }
    }
    if (self->rightStage == 0) {
        if (self->nomalTireFR) {
            JObj_Show(self->model, self->nomalTireFR, 0x10);
        }
        if (self->nomalTireRR) {
            JObj_Show(self->model, self->nomalTireRR, 0x10);
        }
    } else {
        if (self->nomalTireRR) {
            JObj_Hide(self->model, self->nomalTireRR, 0x10);
        }
        if (self->nomalTireFR) {
            JObj_Hide(self->model, self->nomalTireFR, 0x10);
        }
    }
    if (self->leftStage == 1) {
        if (self->kakuTireFL) {
            JObj_Show(self->model, self->kakuTireFL, 0x10);
        }
        if (self->kakuTireRL) {
            JObj_Show(self->model, self->kakuTireRL, 0x10);
        }
    } else {
        if (self->kakuTireFL) {
            JObj_Hide(self->model, self->kakuTireFL, 0x10);
        }
        if (self->kakuTireRL) {
            JObj_Hide(self->model, self->kakuTireRL, 0x10);
        }
    }
    if (self->rightStage == 1) {
        if (self->kakuTireFR) {
            JObj_Show(self->model, self->kakuTireFR, 0x10);
        }
        if (self->kakuTireRR) {
            JObj_Show(self->model, self->kakuTireRR, 0x10);
        }
    } else {
        if (self->kakuTireFR) {
            JObj_Hide(self->model, self->kakuTireFR, 0x10);
        }
        if (self->kakuTireRR) {
            JObj_Hide(self->model, self->kakuTireRR, 0x10);
        }
    }
    if (self->leftStage == 4) {
        if (self->snowTireFL) {
            JObj_Show(self->model, self->snowTireFL, 0x10);
        }
        if (self->snowTireRL) {
            JObj_Show(self->model, self->snowTireRL, 0x10);
        }
    } else {
        if (self->snowTireFL) {
            JObj_Hide(self->model, self->snowTireFL, 0x10);
        }
        if (self->snowTireRL) {
            JObj_Hide(self->model, self->snowTireRL, 0x10);
        }
    }
    if (self->rightStage == 4) {
        if (self->snowTireFR) {
            JObj_Show(self->model, self->snowTireFR, 0x10);
        }
        if (self->snowTireRR) {
            JObj_Show(self->model, self->snowTireRR, 0x10);
        }
    } else {
        if (self->snowTireFR) {
            JObj_Hide(self->model, self->snowTireFR, 0x10);
        }
        if (self->snowTireRR) {
            JObj_Hide(self->model, self->snowTireRR, 0x10);
        }
    }
    if (self->leftStage == 2) {
        if (self->oilTireFL) {
            JObj_Show(self->model, self->oilTireFL, 0x10);
        }
        if (self->oilTireRL) {
            JObj_Show(self->model, self->oilTireRL, 0x10);
        }
        if (self->oilGridFL) {
            JObj_Show(self->model, self->oilGridFL, 0x10);
        }
        if (self->oilGridRL) {
            JObj_Show(self->model, self->oilGridRL, 0x10);
        }
    } else {
        if (self->oilTireFL) {
            JObj_Hide(self->model, self->oilTireFL, 0x10);
        }
        if (self->oilTireRL) {
            JObj_Hide(self->model, self->oilTireRL, 0x10);
        }
        if (self->oilGridFL) {
            JObj_Hide(self->model, self->oilGridFL, 0x10);
        }
        if (self->oilGridRL) {
            JObj_Hide(self->model, self->oilGridRL, 0x10);
        }
    }
    if (self->rightStage == 2) {
        if (self->oilTireFR) {
            JObj_Show(self->model, self->oilTireFR, 0x10);
        }
        if (self->oilTireRR) {
            JObj_Show(self->model, self->oilTireRR, 0x10);
        }
        if (self->oilGridFR) {
            JObj_Show(self->model, self->oilGridFR, 0x10);
        }
        if (self->oilGridRR) {
            JObj_Show(self->model, self->oilGridRR, 0x10);
        }
    } else {
        if (self->oilTireFR) {
            JObj_Hide(self->model, self->oilTireFR, 0x10);
        }
        if (self->oilTireRR) {
            JObj_Hide(self->model, self->oilTireRR, 0x10);
        }
        if (self->oilGridFR) {
            JObj_Hide(self->model, self->oilGridFR, 0x10);
        }
        if (self->oilGridRR) {
            JObj_Hide(self->model, self->oilGridRR, 0x10);
        }
    }
    if (self->leftStage == 3) {
        if (self->punkTireFL) {
            JObj_Show(self->model, self->punkTireFL, 0x10);
        }
        if (self->punkTireRL) {
            JObj_Show(self->model, self->punkTireRL, 0x10);
        }
        if (self->punkGridFL) {
            JObj_Show(self->model, self->punkGridFL, 0x10);
        }
        if (self->punkGridRL) {
            JObj_Show(self->model, self->punkGridRL, 0x10);
        }
    } else {
        if (self->punkTireFL) {
            JObj_Hide(self->model, self->punkTireFL, 0x10);
        }
        if (self->punkTireRL) {
            JObj_Hide(self->model, self->punkTireRL, 0x10);
        }
        if (self->punkGridFL) {
            JObj_Hide(self->model, self->punkGridFL, 0x10);
        }
        if (self->punkGridRL) {
            JObj_Hide(self->model, self->punkGridRL, 0x10);
        }
    }
    if (self->rightStage == 3) {
        if (self->punkGridFR) {
            JObj_Show(self->model, self->punkGridFR, 0x10);
        }
        if (self->punkGridRR) {
            JObj_Show(self->model, self->punkGridRR, 0x10);
        }
        if (self->punkTireFR) {
            JObj_Show(self->model, self->punkTireFR, 0x10);
        }
        if (self->punkTireRR) {
            JObj_Show(self->model, self->punkTireRR, 0x10);
        }
    } else {
        if (self->punkGridFR) {
            JObj_Hide(self->model, self->punkGridFR, 0x10);
        }
        if (self->punkGridRR) {
            JObj_Hide(self->model, self->punkGridRR, 0x10);
        }
        if (self->punkTireFR) {
            JObj_Hide(self->model, self->punkTireFR, 0x10);
        }
        if (self->punkTireRR) {
            JObj_Hide(self->model, self->punkTireRR, 0x10);
        }
    }
}

}
