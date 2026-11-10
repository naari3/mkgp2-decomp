/* ItemEffect tick bodies of the C7 effect family (0x80054B2C..0x80056150):
 * the shared base dtor, the per-effect Tick overriders, two non-virtual
 * workers and the out-of-line C7Owner<N> holder dtors (emitted last).
 *
 * Built with -inline deferred, so the functions are written in REVERSE
 * address order (text comes out reversed, .rodata initializer templates
 * stay in parse order, as in the target 0x802EDB20..0x802EDB68).
 * The extab order (holder dtors first) is declared in tools/extab_order.json.
 * Renaming map (@N labels) lives in tools/extab_user_renames.json: re-dump
 * `nm` after any edit, the numbers shift. */
#include "game/C7ItemOwnersPrivate.h"
#include "game/MathInline.h"

extern "C" {
float Saturate_Double(float v, float lo, float hi);
unsigned char CarObject_IsAirborne(void *kart);
unsigned char KartItem_GetCarObjectState_2bc(void *kart);
void KartItem_SetCarObjectField2d4Float(void *kart, float v);
void KartItem_SetCarObjectField1c8Float(void *kart, float v);
void KartItem_SetCarVelocityVec3(void *kart, void *v);
void KartItem_StopCarObjectSE(void *kart, float v);
void KartItem_ForwardToCarMovement_8019a4e0(void *kart, void *mtx);
void KartItem_ForwardToCarMovement_8019a6a4(void *kart, void *mtx);
void KartItem_TryArmBoostOnLanding(void *kart, int arg);
unsigned char SpecialFaceMesh_RaycastThunk(void *mesh, Vec3f *from, Vec3f *to, Vec3f *hit, Vec3f *normal);
extern void *lbl_806D1138;
extern const float lbl_806D2888; /* 0.2513274f (= 0.08 * pi) */
void CarObject_SetPosition(void *kart, void *pos);
double cos(double);
double sin(double);
}

struct FxMatrix {
    float v[16];
};

/* Same row-major concat as clItemBoxResponder_DrawDebrisParticle.c. */
static inline void FxConcat(FxMatrix *out, const FxMatrix *a, const FxMatrix *b) {
    float tmp[16];
    float *m;
    int k, i, j;
    if (out == a || out == b) m = tmp;
    else m = out->v;
    k = 0;
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j) {
            float sum = a->v[k] * b->v[j];
            sum += a->v[k + 1] * b->v[4 + j];
            sum += a->v[k + 2] * b->v[8 + j];
            sum += a->v[k + 3] * b->v[12 + j];
            m[k + j] = sum;
        }
        k += 4;
    }
    if (out == a || out == b) {
        for (i = 0; i < 16; ++i) out->v[i] = tmp[i];
    }
}

static inline void FxIdentity(FxMatrix *m) {
    int i;
    for (i = 0; i < 16; ++i) m->v[i] = 0.0f;
    m->v[0] = m->v[5] = m->v[10] = m->v[15] = 1.0f;
}

static inline float FxCos(float angle) { return (float)cos(angle); }
static inline float FxSin(float angle) { return (float)sin(angle); }

static inline void FxRotateY(FxMatrix *out, const FxMatrix *in, float angle) {
    FxMatrix rot;
    float c, s;
    FxIdentity(&rot);
    c = FxCos(angle);
    s = FxSin(angle);
    rot.v[0] = c; rot.v[8] = s; rot.v[10] = c; rot.v[2] = -s;
    FxConcat(&rot, &rot, in);
    *out = rot;
}

/* C7Vec (C7ItemCtorPrivate.h): its empty out-of-line dtor is dtor_80036E40. */
struct FxVec {
    float x, y, z;
    FxVec() {}
    ~FxVec() {}
    void Set(float vx, float vy, float vz) {
        x = vx;
        y = vy;
        z = vz;
    }
};

static inline void FxSetTrans(FxMatrix *m, float x, float y, float z) {
    m->v[12] = x;
    m->v[13] = y;
    m->v[14] = z;
}

struct FxOwners {
    void *kart;

    bool IsLanded() {
        if (CarObject_IsAirborne(kart) == 1 || KartItem_GetCarObjectState_2bc(kart) == 1) {
            return true;
        }
        return false;
    }
};

/* Init is declared first and never defined, so this TU does not emit the
 * base vtable (KartItemSubObject_vtable_803F7738). */
struct FxBase {
    virtual void Init();
    virtual bool Tick();
    virtual ~FxBase();
    void SetKartPos(float x, float y, float z) {
        FxVec p;
        p.Set(x, y, z);
        CarObject_SetPosition(owner->kart, &p);
    }
    FxOwners *owner;
};

struct FxSpin : FxBase {
    virtual void Init();
    virtual bool Tick();
    void Work();
    Vec3f pos;
    int count;
    float t;
    char pad1C[0x4C - 0x1C];
    Vec3f ctr;
    char pad58[0x5C - 0x58];
    FxMatrix mtx;
    int timer;
};

struct FxDamp : FxBase {
    virtual void Init();
    virtual bool Tick();
    float vel[3];
    float value;
    float step;
    int timer;
};

struct FxQuake : FxBase {
    virtual void Init();
    virtual bool Tick();
    void Work();
    Vec3f base;
    int count;
    char pad18[0x1C - 0x18];
    float vy;
    char pad20[0x54 - 0x20];
    Vec3f cur;
    char pad60[0x64 - 0x60];
    FxMatrix mtx;
    int timer;
};

struct FxImpact : FxBase {
    virtual void Init();
    virtual bool Tick();
    Vec3f vel;
    char pad14[0x44 - 0x14];
    Vec3f pos;
    char pad50[0x54 - 0x50];
    FxMatrix mtx;
    FxMatrix rot;
    int timer;
    char padD8[0xE4 - 0xD8];
    float angle;
    int count;
};

/* 0x80055F10..0x80056150: the C7Owner<C7Effect<3..0> > holder dtors
 * (header template in C7ItemOwnersPrivate.h), written as plain holder
 * classes so this TU emits strong copies. */
struct FxHolder3 { FxBase *p; ~FxHolder3() throw(); };
struct FxHolder2 { FxBase *p; ~FxHolder2() throw(); };
struct FxHolder1 { FxBase *p; ~FxHolder1() throw(); };
struct FxHolder0 { FxBase *p; ~FxHolder0() throw(); };

/* 0x800560C0 */
FxHolder0::~FxHolder0() throw() { delete p; }
/* 0x80056030 */
FxHolder1::~FxHolder1() throw() { delete p; }

/* 0x80055FA0 */
FxHolder2::~FxHolder2() throw() { delete p; }

/* 0x80055F10 */
FxHolder3::~FxHolder3() throw() { delete p; }

/* 0x80055C08 */
bool FxImpact::Tick() {
    if (timer <= 0) {
        return false;
    }
    angle += lbl_806D2888;
    count++;
    if (count > 25) {
        count = 0;
        timer--;
    }
    pos.x += vel.x;
    pos.y += vel.y;
    pos.z += vel.z;
    FxConcat(&mtx, &mtx, &rot);
    FxSetTrans(&mtx, pos.x, pos.y, pos.z);
    KartItem_ForwardToCarMovement_8019a6a4(owner->kart, &mtx);
    KartItem_SetCarVelocityVec3(owner->kart, &vel);
    return true;
}

/* 0x80055640 */
void FxQuake::Work() {
    if (timer <= 0) {
        cur.y -= 0.85f;
        SetKartPos(cur.x, cur.y, cur.z);
        return;
    }
    float angle = 0.0f;
    int r = timer % 60;
    if (r > 0) {
        angle = (float)(3.14159265358979323846 / 180.0 * (360.0f * ((float)r / 60.0f)));
    }
    float amp = 45.0f * FxSin(3.1415927f * Saturate_Double((float)timer / 60.0f, 0.0f, 1.0f));
    angle = 2.0f * angle;
    cur.x = amp * FxCos(angle) + base.x;
    cur.y += vy;
    cur.z = amp * FxSin(angle) + base.z;
    void *mesh;
    if ((mesh = lbl_806D1138) == 0) {
        mesh = 0;
    }
    if (mesh != 0) {
        Vec3f from = { base.x, cur.y + 25.0f, base.z };
        Vec3f to = { base.x, cur.y - vy, base.z };
        Vec3f hit;
        Vec3f normal;
        if (SpecialFaceMesh_RaycastThunk(mesh, &from, &to, &hit, &normal) == 1) {
            cur.y = hit.y - 25.0f;
        }
    }
    FxRotateY(&mtx, &mtx, 0.10471976f);
    FxSetTrans(&mtx, cur.x, cur.y, cur.z);
    vy += -0.85f;
    timer--;
    if (vy < 0.0f) {
        vy = 0.0f;
    }
    KartItem_ForwardToCarMovement_8019a4e0(owner->kart, &mtx);
}

/* 0x80055558 */
bool FxQuake::Tick() {
    if (count < 3) {
        Work();
    }
    if (timer <= 0 && count++ > 3) {
        KartItem_SetCarObjectField2d4Float(owner->kart, 14.0f);
        *((unsigned char *)owner->kart + 0xD4) = 1;
        if (count > 6) {
            bool landed = owner->IsLanded();
            if (!landed) {
                KartItem_StopCarObjectSE(owner->kart, 0.1f);
            }
            return landed;
        }
    }
    return true;
}

struct FxJump : FxBase {
    virtual void Init();
    virtual bool Tick();
    void Snap() {
        void *mesh;
        if ((mesh = lbl_806D1138) == 0) {
            mesh = 0;
        }
        if (mesh != 0) {
            Vec3f from = { pos.x, pos.y + 25.0f, pos.z };
            Vec3f to = { pos.x, pos.y - vel.y, pos.z };
            Vec3f hit;
            Vec3f normal;
            if (SpecialFaceMesh_RaycastThunk(mesh, &from, &to, &hit, &normal) == 1) {
                pos.y = hit.y - 25.0f;
            }
        }
    }
    Vec3f vel;
    char pad14[0x44 - 0x14];
    Vec3f pos;
    char pad50[0x54 - 0x50];
    FxMatrix mtx;
    FxMatrix rot;
    char padD4[0xE0 - 0xD4];
    int timer;
};

/* 0x80055148 */
bool FxJump::Tick() {
    if (timer <= 0) {
        KartItem_SetCarObjectField2d4Float(owner->kart, 25.0f);
    } else {
        pos.x += vel.x;
        pos.y += vel.y;
        pos.z += vel.z;
        Snap();
        FxConcat(&mtx, &mtx, &rot);
        FxSetTrans(&mtx, pos.x, pos.y, pos.z);
        vel.y += -1.0f;
        timer--;
        KartItem_ForwardToCarMovement_8019a4e0(owner->kart, &mtx);
    }
    if (vel.y < 0.0f) {
        bool landed = owner->IsLanded();
        if (!landed) {
            KartItem_TryArmBoostOnLanding(owner->kart, 0);
        }
        return landed;
    }
    return true;
}

/* 0x800550D0 */
bool FxDamp::Tick() {
    if (timer <= 0) {
        return false;
    }
    timer--;
    value += step;
    KartItem_SetCarObjectField1c8Float(owner->kart, value);
    KartItem_SetCarVelocityVec3(owner->kart, vel);
    return true;
}

/* 0x80054C00 */
void FxSpin::Work() {
    t = Saturate_Double(0.05f + t, 0.0f, 1.0f);
    if (timer <= 0) {
        KartItem_SetCarObjectField2d4Float(owner->kart, 14.0f);
        *((unsigned char *)owner->kart + 0xD4) = 1;
        return;
    }
    ctr.x = pos.x;
    ctr.y = pos.y * (1.0f - t) + (17.0f + pos.y) * t;
    ctr.z = pos.z;
    void *mesh;
    if ((mesh = lbl_806D1138) == 0) {
        mesh = 0;
    }
    if (mesh != 0) {
        Vec3f from = { pos.x, ctr.y, pos.z };
        Vec3f to = { pos.x, ctr.y - 5.0f, pos.z };
        Vec3f hit;
        Vec3f normal;
        if (SpecialFaceMesh_RaycastThunk(mesh, &from, &to, &hit, &normal) == 1) {
            ctr.y = hit.y - 25.0f;
        }
    }
    FxRotateY(&mtx, &mtx, 0.20943952f);
    FxSetTrans(&mtx, ctr.x, ctr.y, ctr.z);
    timer--;
    KartItem_ForwardToCarMovement_8019a4e0(owner->kart, &mtx);
}

/* 0x80054B74 */
bool FxSpin::Tick() {
    Work();
    if (timer <= 0 && count++ > 3) {
        return owner->IsLanded();
    }
    return true;
}

/* 0x80054B2C */
FxBase::~FxBase() {}
