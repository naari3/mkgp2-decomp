/*
 * 0x8022CE04..0x802300C8: clEFacePoly / clEFacePolyEffect, the item
 * reaction drawn over a rival's face icon (pen scribble, pencil, ...).
 * Source file name from the rodata strings: imamura/EnmyFaceEffect.cpp.
 * The TU owns .rodata 0x803DAB54..0x803DAE88 and .bss 0x80679CE0..0x80679DE8.
 *
 * Built with -inline deferred -RTTI on -rostr: each vtable and RTTI name is
 * emitted with its class's destructor, which puts __vt__11clEFacePoly before
 * the switch tables and __vt__17clEFacePolyEffect after them, as in the
 * target. The real TU probably starts earlier (EnemyFaceDraw at 0x8022BFA8
 * reads the pool 0x803DA710 that ends where this .rodata starts, which is
 * why .rodata is pinned to 4-byte alignment in extab_user_renames.json).
 */

#include "game/types/size_t.h"
void *operator new(size_t size);
void operator delete(void *p) throw();

typedef float Mtx[3][4];

extern "C" {
void PSMTXIdentity(Mtx m);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXScale(Mtx m, float x, float y, float z);
void PSMTXTrans(Mtx m, float x, float y, float z);
void PSMTXRotRad(Mtx m, char axis, float rad);
float Sinf_LUT_Wrap(float deg);
float Cosf_LUT_Wrap(float deg);
int rand(void);
void PreloadResource(int id);
void fn_80120A08(int id);
void TEXReleasePalette(void *pal);
void MemoryManager_Free(void *p);
int fn_801DB8F0(void);
int fn_801DB890(int ctx, int item);
}

extern const float lbl_806DB668;
extern const float lbl_806DB66C;

#include "game/types/Vec3.h"

struct Vec3c : Vec3 {
    Vec3c() {}
    Vec3c(float a, float b, float c) { x = a; y = b; z = c; }
    Vec3c(const Vec3 &v) : Vec3(v) {}
    Vec3c(const Vec3c &v) : Vec3(v) {}
    ~Vec3c() {}
    void RotationMatrix(Mtx rot);
};

struct KartStatus {
    int i0;
    unsigned char b4;
    int i8;
    unsigned long long bits;
    unsigned long long bits2;
    unsigned char b20;
    float f24;
    float f28;
    int i2C;
    float f30, f34, f38, f3C, f40, f44, f48;
    int i4C;
    int i50;
    KartStatus(const KartStatus &o)
        : i0(o.i0), b4(o.b4), i8(o.i8), bits(o.bits), bits2(o.bits2), b20(o.b20), f24(o.f24), f28(o.f28),
          i2C(o.i2C), f30(o.f30), f34(o.f34), f38(o.f38), f3C(o.f3C), f40(o.f40), f44(o.f44), f48(o.f48),
          i4C(o.i4C), i50(o.i50) {}
    ~KartStatus();
};

struct KartRender {
    char pad0[0x304];
    KartStatus *status;
};

int fn_8023D1B4(KartRender *kart);
unsigned char fn_80231B74(int id);
int fn_80231A50(int id);

#include "game/types/clNormal3D.h"

/* Shared float table of a common header: every TU that includes it carries a
 * copy at the start of its .rodata (here 0x803DA710, never referenced). */
#pragma force_active on
extern const unsigned int EnmyFaceEffect_rodata_803DA710[0x111] = {0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x3F333333, 0x3F666666, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x4119999A, 0x4119999A, 0x41400000, 0x40E66667, 0x00000000, 0x4119999A, 0xC0E66667, 0x00000000, 0x4119999A, 0x40E66667, 0x00000000, 0xC119999A, 0xC0E66667, 0x00000000, 0xC119999A};
#pragma force_active reset

/* Sprite ids: [0..8] item faces, [9] 0xC28, [10] 0xC49, [11] 0xC32. */
static const int sFaceSprites[24] = {0xC68, 0xC69, 0xC66, 0xC67, 0xC63, 0xC65, 0xC64, 0xC6A, 0xC6B, 0xC28, 0xC49, 0xC32, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
/* Quads: two rows of four corners each (upper half, lower half). */
static const Vec3 sQuadNormal[16] = {
    {-31.0f, 0.0f, 0.0f},
    {31.0f, 0.0f, 0.0f},
    {31.0f, 38.0f, 0.0f},
    {-31.0f, 38.0f, 0.0f},
    {-31.0f, -38.0f, 0.0f},
    {31.0f, -38.0f, 0.0f},
    {31.0f, 0.0f, 0.0f},
    {-31.0f, 0.0f, 0.0f},
    {-35.649998f, 0.0f, 0.0f},
    {35.649998f, 0.0f, 0.0f},
    {35.649998f, 35.649998f, 0.0f},
    {-35.649998f, 35.649998f, 0.0f},
    {-35.649998f, -35.649998f, 0.0f},
    {35.649998f, -35.649998f, 0.0f},
    {35.649998f, 0.0f, 0.0f},
    {-35.649998f, 0.0f, 0.0f}
};
static const Vec3 sQuadStandard[8] = {
    {-35.649998f, 0.0f, 0.0f},
    {35.649998f, 0.0f, 0.0f},
    {35.649998f, 42.877224f, 0.0f},
    {-35.649998f, 42.877224f, 0.0f},
    {-35.649998f, -22.877224f, 0.0f},
    {35.649998f, -22.877224f, 0.0f},
    {35.649998f, 0.0f, 0.0f},
    {-35.649998f, 0.0f, 0.0f}
};
static const Vec3 sQuadRight[8] = {
    {-35.649998f, 0.0f, 0.0f},
    {35.649998f, 0.0f, 0.0f},
    {35.649998f, 43.17611f, 0.0f},
    {-35.649998f, 43.17611f, 0.0f},
    {-35.649998f, -43.17611f, 0.0f},
    {35.649998f, -43.17611f, 0.0f},
    {35.649998f, 0.0f, 0.0f},
    {-35.649998f, 0.0f, 0.0f}
};
static const Vec3 sQuadWide[8] = {
    {-50.70222f, 0.0f, 0.0f},
    {50.70222f, 0.0f, 0.0f},
    {50.70222f, 50.70222f, 0.0f},
    {-50.70222f, 50.70222f, 0.0f},
    {-50.70222f, -50.70222f, 0.0f},
    {50.70222f, -50.70222f, 0.0f},
    {50.70222f, 0.0f, 0.0f},
    {-50.70222f, 0.0f, 0.0f}
};
static const Vec3 sQuadTop[4] = {
    {-31.0f, 2e+01f, 0.0f},
    {31.0f, 2e+01f, 0.0f},
    {31.0f, 61.0f, 0.0f},
    {-31.0f, 61.0f, 0.0f}
};


struct PalSlot {
    unsigned char free;
    void *data;
    void *pal;
};

static Vec3c sPosA = Vec3c(0.0f, 0.0f, 0.0f);
static Vec3c sPosB = Vec3c(0.0f, 13.0f, 15.0f);
static void *sBuffers[12];
static void *sPalettes[12];
static PalSlot sPalSlots[10];
static unsigned char sLoaded;

static inline void RotMtx(Mtx rot, float rx, float ry, float rz) {
    float sx = Sinf_LUT_Wrap(rx);
    float cx = Cosf_LUT_Wrap(rx);
    float sy = Sinf_LUT_Wrap(ry);
    float cy = Cosf_LUT_Wrap(ry);
    float sz = Sinf_LUT_Wrap(rz);
    float cz = Cosf_LUT_Wrap(rz);
    rot[1][1] = sx;
    rot[2][2] = sx;
    rot[2][1] = -cx;
    rot[1][2] = cx;
    rot[0][0] = sy;
    rot[2][2] *= sy;
    rot[2][0] = cy;
    rot[0][2] = -cy;
    rot[0][0] *= sz;
    rot[1][1] *= sz;
    rot[1][0] = -cz;
    rot[0][1] = cz;
}

inline void Vec3c::RotationMatrix(Mtx rot) {
    float rz = z;
    float ry = y;
    float rx = x;
    float sx = Sinf_LUT_Wrap(rx);
    float cx = Cosf_LUT_Wrap(rx);
    float sy = Sinf_LUT_Wrap(ry);
    float cy = Cosf_LUT_Wrap(ry);
    float sz = Sinf_LUT_Wrap(rz);
    float cz = Cosf_LUT_Wrap(rz);
    rot[1][1] = sx;
    rot[2][2] = sx;
    rot[2][1] = -cx;
    rot[1][2] = cx;
    rot[0][0] = sy;
    rot[2][2] *= sy;
    rot[2][0] = cy;
    rot[0][2] = -cy;
    rot[0][0] *= sz;
    rot[1][1] *= sz;
    rot[1][0] = -cz;
    rot[0][1] = cz;
}

static inline void MakeMtx(Mtx out, float s, const Vec3 &p, const Vec3 &r) {
    Mtx tr, sc, rot;
    PSMTXIdentity(rot);
    PSMTXScale(sc, s, s, s);
    PSMTXTrans(tr, p.x, p.y, p.z);
    RotMtx(rot, r.x, r.y, r.z);
    PSMTXConcat(rot, sc, out);
    PSMTXConcat(tr, out, out);
}

static inline void MakeMtxVec(Mtx out, float s, const Vec3c &p, Vec3c &r) {
    Mtx tr, sc, rot;
    PSMTXIdentity(rot);
    PSMTXScale(sc, s, s, s);
    PSMTXTrans(tr, p.x, p.y, p.z);
    r.RotationMatrix(rot);
    PSMTXConcat(rot, sc, out);
    PSMTXConcat(tr, out, out);
}

static inline void MakeMtxPivot(Mtx out, Mtx pivot, float s, const Vec3 &p, const Vec3 &r) {
    Mtx tr, sc, rot;
    PSMTXIdentity(rot);
    PSMTXScale(sc, s, s, s);
    RotMtx(rot, r.x, r.y, r.z);
    PSMTXTrans(tr, p.x, p.y, p.z);
    PSMTXConcat(pivot, sc, sc);
    PSMTXConcat(rot, sc, out);
    PSMTXConcat(tr, out, out);
}

class clEFacePolyEffect {
public:
    virtual ~clEFacePolyEffect();

    int timer;
    int state;
    int type;
    int sub;
    int i14;
    float speed;
    float f1C;
    char pad20[4];
    Vec3c pos;
    Vec3c rot;
    float scale;
    Mtx mtxA;
    Mtx mtxB;
    Vec3c pos2;
    float scale2;
    Mtx mtxC;
    int mode;
    unsigned char done;
    float alpha;
    int anim;
    Vec3c vF0;
    KartRender *owner;

    clEFacePolyEffect(KartRender *o) : timer(0), state(0), type(0), sub(0) {
        speed = 0.0f;
        scale = 1.0f;
        scale2 = 1.0f;
        mode = -1;
        done = 0;
        alpha = 1.0f;
        anim = -1;
        owner = o;
        pos.x = pos.y = pos.z = 0.0f;
        rot.x = rot.y = rot.z = 0.0f;
        pos2.x = pos2.y = pos2.z = 0.0f;
        vF0.x = vF0.y = vF0.z = 0.0f;
        PSMTXIdentity(mtxA);
        PSMTXIdentity(mtxB);
        PSMTXIdentity(mtxC);
    }

    void Clear() {
        sub = 0;
        i14 = 0;
        speed = 0.0f;
        f1C = 0.0f;
        timer = 0;
        state = 0;
        scale = 1.0f;
        scale2 = 1.0f;
        alpha = 1.0f;
        mode = -1;
        anim = -1;
        type = 0;
        done = 0;
        pos.x = pos.y = pos.z = 0.0f;
        rot.x = rot.y = rot.z = 0.0f;
        pos2.x = pos2.y = pos2.z = 0.0f;
        vF0.x = vF0.y = vF0.z = 0.0f;
        PSMTXIdentity(mtxA);
        PSMTXIdentity(mtxB);
        PSMTXIdentity(mtxC);
    }

    void Shake() {
        pos.x = 0.5f * (rand() % 10 - 5);
        pos.z = 0.5f * (rand() % 10 - 5);
    }

    void UpdSpin();
    void UpdDrop();
    void UpdBounce();
    void UpdSquash();
    void UpdStar();
    void UpdBanana();
    void UpdWobble();
    void UpdSlide();
    void Update();
    void Start(int item);
};

class clEFacePoly {
public:
    virtual ~clEFacePoly();

    unsigned char hasPal;
    int resId;
    int resId2;
    int i10;
    Vec3c v14;
    float f20;
    int palIdx;
    KartRender *owner;
    clEFacePolyEffect *effect;
    clNormal3D *models[2];

    clEFacePoly(KartRender *o, int a, int b, int c);
    void Update();
};

static inline void ReleaseFacePalettes() {
    int i;
    if (sLoaded) {
        sLoaded = 0;
        for (i = 0; i < 12; i++) {
            if (sPalettes[i]) {
                TEXReleasePalette(&sPalettes[i]);
                sPalettes[i] = 0;
            }
            if (sBuffers[i]) {
                MemoryManager_Free(sBuffers[i]);
                sBuffers[i] = 0;
            }
        }
        for (i = 0; i < 10; i++) {
            if (sPalSlots[i].free) {
                if (sPalSlots[i].pal) {
                    TEXReleasePalette(&sPalSlots[i].pal);
                    sPalSlots[i].pal = 0;
                }
                if (sPalSlots[i].data) {
                    MemoryManager_Free(sPalSlots[i].data);
                    sPalSlots[i].data = 0;
                }
                sPalSlots[i].free = 1;
            }
        }
    }
}

extern "C" void OSReport(const char *fmt, ...);

/* Built with -inline deferred: functions are emitted in reverse source order. */
clEFacePolyEffect::~clEFacePolyEffect() {}


void clEFacePolyEffect::Start(int item) {
    Clear();
    switch (fn_801DB890(fn_801DB8F0(), item)) {
    case 0:
        type = 0;
        break;
    case 1:
        type = 1;
        break;
    case 2:
        type = 2;
        break;
    case 3:
        type = 3;
        break;
    case 8:
        type = 4;
        break;
    case 4:
        type = 6;
        break;
    case 6:
        type = 7;
        break;
    case 9:
        type = 8;
        break;
    case 10:
        type = 8;
        break;
    case 5:
        type = 8;
        break;
    case 7:
        type = 8;
        break;
    }
    unsigned char hit;
    KartStatus ks = *owner->status;
    if ((ks.bits & 4) == 0) {
        hit = 0;
    } else {
        hit = 1;
    }
    if (hit == 1) {
        UpdSquash();
    }
    switch (item) {
    case 0x50:
        type = 9;
        break;
    case 0x9D:
    case 0x9E:
        type = 10;
        break;
    case 0x55:
        type = 11;
        break;
    case 0x8F:
        type = 12;
        break;
    case 0x88:
        type = 14;
        break;
    case 0x75:
        type = 15;
        break;
    case 0x93: {
        type = 13;
        int n = fn_8023D1B4(owner);
        if (n < 0) {
            anim = 4;
        } else {
            anim = n + 4;
        }
        break;
    }
    }
}

void clEFacePolyEffect::Update() {
    switch (type) {
    case 1:
    case 2:
        UpdDrop();
        break;
    case 3:
        UpdBounce();
        break;
    case 4:
        UpdSpin();
        break;
    case 5:
        UpdSquash();
        break;
    case 6:
        UpdStar();
        break;
    case 7:
        UpdBanana();
        break;
    case 8:
        UpdWobble();
        break;
    case 9:
        switch (state) {
        case 0:
            anim = 0;
            state = 1;
            break;
        case 1:
            alpha += 0.1f;
            if (alpha >= 1.0f) {
                alpha = 1.0f;
                state = 2;
                timer = 0;
            }
            break;
        case 2:
            if (++timer >= 600) {
                state = 3;
                timer = 0;
            }
            break;
        case 3:
            alpha -= 0.033333335f;
            if (alpha < 0.0f) {
                alpha = 0.0f;
                Clear();
            }
            break;
        }
        break;
    case 10:
        switch (state) {
        case 0:
            anim = 1;
            state = 1;
            break;
        case 1:
            alpha += 0.1f;
            if (alpha >= 1.0f) {
                alpha = 1.0f;
                state = 2;
                timer = 0;
            }
            break;
        case 2:
            if (++timer >= 600) {
                state = 3;
                timer = 0;
            }
            break;
        case 3:
            alpha -= 0.04f;
            if (alpha < 0.0f) {
                alpha = 0.0f;
                Clear();
            }
            break;
        }
        break;
    case 11:
    case 12:
        UpdSlide();
        break;
    case 13:
        switch (state) {
        case 0:
            vF0.z = 10.0f;
            vF0.y = -30.0f;
            vF0.x = 0.0f;
            alpha = 1.0f;
            state = 1;
            timer = 0;
            break;
        case 1:
            vF0.z += -0.25f;
            vF0.y += 0.75f;
            if (++timer >= 40) {
                state = 2;
                timer = 0;
                vF0.y = 0.0f;
                vF0.z = 0.0f;
            }
            break;
        case 2:
            if (++timer >= 600) {
                Clear();
            }
            break;
        }
        break;
    case 14:
        if (state < 10) {
            UpdDrop();
            if (type == 0) {
                state = 10;
                type = 14;
            }
            break;
        }
        switch (state) {
        case 10:
            pos2.z = 10.0f;
            pos2.y = -30.0f;
            anim = 7;
            state = 11;
            break;
        case 11:
            pos2.z += -0.25f;
            pos2.y += 0.75f;
            alpha += 0.025f;
            if (alpha >= 1.0f) {
                alpha = 1.0f;
                state = 12;
                timer = 0;
                pos2.y = 0.0f;
                pos2.z = 0.0f;
            }
            break;
        case 12:
            if (++timer >= 600) {
                state = 13;
                timer = 0;
            }
            break;
        case 13:
            alpha = 0.0f;
            Clear();
            break;
        }
        break;
    case 15:
        switch (state) {
        case 0:
            anim = 8;
            state = 1;
            break;
        case 1:
            alpha += 0.1f;
            if (alpha >= 1.0f) {
                alpha = 1.0f;
                state = 2;
                timer = 0;
            }
            break;
        case 2:
            if (++timer >= 600) {
                state = 3;
                timer = 0;
            }
            break;
        case 3:
            alpha = 0.0f;
            Clear();
            break;
        }
        break;
    }
}

void clEFacePolyEffect::UpdDrop() {
    switch (state) {
    case 0:
        rot.x += 8.0f;
        if (rot.x >= 60.0f) {
            int n = 40;
            state = 1;
            if (type == 2) {
                n = 60;
            }
            sub = n;
        }
        break;
    case 1:
        Shake();
        if (++timer >= sub) {
            pos.x = pos.y = pos.z = 0.0f;
            state = 2;
            timer = 0;
        }
        break;
    case 2:
        rot.x -= 8.0f;
        scale += 0.07f;
        if (rot.x <= -20.0f) {
            rot.x = 0.0f;
            state = 3;
        }
        break;
    case 3:
        if (scale > 1.0f) {
            scale -= 0.1f;
        }
        if (rot.x < 0.0f) {
            rot.x += 8.0f;
        }
        if (scale <= 1.0f && rot.x >= 0.0f) {
            scale = 1.0f;
            rot.x = 0.0f;
            PSMTXIdentity(mtxA);
            PSMTXIdentity(mtxB);
            Clear();
            return;
        }
        break;
    }
    float y = pos.y;
    pos.y -= 38.0f;
    Mtx pivot;
    PSMTXIdentity(pivot);
    PSMTXTrans(pivot, 0.0f, 38.0f, 0.0f);
    MakeMtxPivot(mtxB, pivot, scale, pos, rot);
    MakeMtxPivot(mtxA, pivot, scale, pos, rot);
    pos.y = y;
}

void clEFacePolyEffect::UpdBounce() {
    switch (state) {
    case 0:
        rot.x += 10.0f;
        if (rot.x >= 360.0f) {
            rot.x -= 360.0f;
        }
        if (++timer >= 120) {
            if (rot.x >= 60.0f) {
                rot.x -= 360.0f;
            }
            state = 1;
        }
        break;
    case 1:
        rot.x += 10.0f;
        if (rot.x >= 360.0f) {
            rot.x -= 360.0f;
        }
        if (rot.x >= 60.0f) {
            state = 2;
        }
        break;
    case 2:
        rot.x -= 8.0f;
        scale += 0.07f;
        if (rot.x <= -20.0f) {
            rot.x = 0.0f;
            state = 3;
        }
        break;
    case 3:
        if (scale > 1.0f) {
            scale -= 0.1f;
        }
        if (rot.x < 0.0f) {
            rot.x += 8.0f;
        }
        if (scale <= 1.0f && rot.x >= 0.0f) {
            scale = 1.0f;
            rot.x = 0.0f;
            Clear();
        }
        break;
    }
    MakeMtx(mtxA, scale, pos, rot);
    MakeMtx(mtxB, scale, pos, rot);
}

void clEFacePolyEffect::UpdSpin() {
    switch (state) {
    case 0:
        rot.y += 10.0f;
        if (rot.y >= 360.0f) {
            rot.y -= 360.0f;
        }
        if (++timer >= 90) {
            state = 1;
        }
        break;
    case 1:
        rot.y += 10.0f;
        if (rot.y >= 360.0f) {
            rot.y = 0.0f;
            state = 0;
            type = 0;
        }
        break;
    }
    MakeMtx(mtxA, scale, pos, rot);
    MakeMtx(mtxB, scale, pos, rot);
}

void clEFacePolyEffect::UpdSquash() {
    if (state >= 10) {
        rot.z += 8.0f;
        if (rot.z >= 360.0f) {
            rot.z -= 360.0f;
        }
        KartStatus ks = *owner->status;
        if ((ks.bits & 4) == 0 && rot.z <= 8.0f) {
            Clear();
        }
        return;
    }
    UpdDrop();
    if (type == 0) {
        state = 10;
    }
}

void clEFacePolyEffect::UpdStar() {
    switch (state) {
    case 0:
        if (1.0f == scale) {
            scale = 0.8f;
            speed = 3.0f;
        }
        rot.z += speed;
        if (++timer >= 120) {
            rot.z = 0.0f;
            sub = 0;
            speed = -0.4f;
            timer = 30;
            state = 1;
        }
        break;
    case 1:
        pos.y += speed;
        speed -= lbl_806DB668;
        if (pos.y < lbl_806DB66C) {
            speed = -speed;
        }
        if (--timer < 0) {
            pos.y = 0.0f;
            timer = 10;
            state = 2;
        }
        break;
    case 2:
        rot.x -= 6.0f;
        scale += 0.05f;
        if (rot.x <= -30.0f) {
            rot.x = 0.0f;
            state = 3;
        }
        break;
    case 3:
        if (scale > 1.0f) {
            scale -= 0.05f;
        }
        if (rot.x < 0.0f) {
            rot.x += 6.0f;
        }
        if (scale <= 1.0f && rot.x >= 0.0f) {
            scale = 1.0f;
            rot.x = 0.0f;
            Clear();
        }
        break;
    }
    MakeMtx(mtxA, scale, pos, rot);
    MakeMtx(mtxB, scale, pos, rot);
}

void clEFacePolyEffect::UpdBanana() {
    switch (state) {
    case 0:
        rot.x += 10.0f;
        if (rot.x >= 65.0f) {
            rot.x = 65.0f;
            timer = 0;
            state = 1;
        }
        break;
    case 1:
        Shake();
        if (++timer >= 60) {
            timer = 0;
            pos.x = pos.y = pos.z = 0.0f;
            state = 2;
        }
        break;
    case 2:
        rot.x -= 6.0f;
        scale += 0.05f;
        if (rot.x <= 0.0f) {
            sub = 1;
        }
        if (rot.x <= -30.0f) {
            rot.x = 0.0f;
            state = 3;
        }
        break;
    case 3:
        if (scale > 1.0f) {
            scale -= 0.05f;
        }
        if (rot.x < 0.0f) {
            rot.x += 6.0f;
        }
        if (scale <= 1.0f && rot.x >= 0.0f) {
            scale = 1.0f;
            rot.x = 0.0f;
            Clear();
            return;
        }
        break;
    }
    if (sub == 0) {
        Vec3c r(rot);
        Vec3c p(pos);
        p.y = -(38.0f * (r.x / 65.0f) - p.y);
        r.x *= 0.9f;
        MakeMtxVec(mtxB, scale, p, r);
        r.x = 1.1f * -rot.x;
        MakeMtxVec(mtxA, scale, p, r);
        return;
    }
    MakeMtxVec(mtxA, scale, pos, rot);
    MakeMtxVec(mtxB, scale, pos, rot);
}

void clEFacePolyEffect::UpdWobble() {
    switch (state) {
    case 0:
        Shake();
        if (++timer >= 50) {
            pos.x = pos.y = pos.z = 0.0f;
            state = 1;
            timer = 0;
        }
        break;
    case 1:
        rot.x -= 8.0f;
        scale += 0.07f;
        if (rot.x <= -20.0f) {
            rot.x = 0.0f;
            state = 2;
        }
        break;
    case 2:
        if (scale > 1.0f) {
            scale -= 0.1f;
        }
        if (rot.x < 0.0f) {
            rot.x += 8.0f;
        }
        if (scale <= 1.0f && rot.x >= 0.0f) {
            scale = 1.0f;
            rot.x = 0.0f;
            PSMTXIdentity(mtxA);
            PSMTXIdentity(mtxB);
            Clear();
            return;
        }
        break;
    }
    MakeMtx(mtxB, scale, pos, rot);
    MakeMtx(mtxA, scale, pos, rot);
}

void clEFacePolyEffect::UpdSlide() {
    switch (state) {
    case 0:
        switch (sub) {
        case 0:
            timer = 0;
            if (type == 11) {
                mode = 0;
                pos2.x = sPosA.x;
                pos2.y = sPosA.y;
                pos2.z = sPosA.z;
                scale2 = 1.5f;
                sub = 1;
            } else {
                mode = 1;
                pos2.x = sPosB.x;
                pos2.y = sPosB.y;
                pos2.z = sPosB.z;
                scale2 = 1.5f;
                sub = 2;
            }
            break;
        case 1:
            if (done == 1) {
                state = 1;
                mode = -1;
                anim = 2;
            }
            break;
        case 2:
            pos2.x = 20.0f * Cosf_LUT_Wrap(7.0f * timer) + sPosB.x;
            pos2.y -= 0.3f;
            if (++timer >= 120) {
                timer = 0;
                sub = 3;
            }
            break;
        case 3:
            scale2 -= 0.02f;
            pos2.x += 0.1f;
            if (++timer >= 30) {
                state = 1;
                timer = 0;
                mode = -1;
                anim = 3;
            }
            break;
        }
        break;
    case 1:
        if (++timer >= 600) {
            Clear();
            return;
        }
        break;
    }
    if (mode != -1) {
        Mtx sc, rot;
        PSMTXRotRad(rot, 'X', type == 11 ? 210.0f : 150.0f);
        PSMTXScale(sc, scale2, scale2, scale2);
        PSMTXTrans(mtxC, pos2.x, pos2.y, pos2.z);
        PSMTXConcat(rot, sc, sc);
        PSMTXConcat(mtxC, sc, mtxC);
    }
}

clEFacePoly::clEFacePoly(KartRender *o, int a, int b, int c) {
    hasPal = 0;
    resId = a;
    resId2 = b;
    i10 = c;
    f20 = 0.0f;
    palIdx = 0;
    owner = o;
    effect = 0;
    effect = new clEFacePolyEffect(o);
    v14.x = v14.y = v14.z = 0.0f;
    models[0] = new clNormal3D("it_j_00_rakugaki_pen.dat", 0);
    models[1] = new clNormal3D("it_v_02_pencil.dat", 0);
    PreloadResource(0xC28);
    PreloadResource(0xC49);
    PreloadResource(0xC32);
    PreloadResource(resId);
    PreloadResource(resId2);
    hasPal = fn_80231B74(resId);
    if (hasPal) {
        palIdx = fn_80231A50(resId);
    }
}

#pragma push
#pragma opt_lifetimes off
clEFacePoly::~clEFacePoly() {
    int i;
    for (i = 0; i < 2; i++) {
        if (models[i]) {
            delete models[i];
            models[i] = 0;
        }
    }
    for (i = 0; i < 12; i++) {
        fn_80120A08(sFaceSprites[12]);
    }
    if (effect) {
        delete effect;
        effect = 0;
    }
    if (hasPal) {
        int idx = palIdx;
        if (idx >= 0 && idx < 10) {
            PalSlot *s = &sPalSlots[idx];
            if (s->free) {
                if (sPalSlots[idx].pal) {
                    TEXReleasePalette(&sPalSlots[idx].pal);
                    sPalSlots[idx].pal = 0;
                }
                if (sPalSlots[idx].data) {
                    MemoryManager_Free(sPalSlots[idx].data);
                    sPalSlots[idx].data = 0;
                }
                s->free = 1;
            }
        }
    }
    ReleaseFacePalettes();
}
#pragma pop

void clEFacePoly::Update() {
    if (owner) {
        effect->Update();
    }
}

/* ---- drawing (was EnemyFaceDraw.cpp / fn_8022CDE4.c); -inline deferred
 * emits the functions below first. ---- */
typedef Vec3 FaceDrawVec;
typedef Mtx FaceMtx;
struct FaceVecView {
    /* Preserve the vector as a whole when copying between component views. */
    union { FaceDrawVec value; float components[3]; };
    FaceVecView() {}
    ~FaceVecView() {}
};
#include "game/types/FaceDrawKart.h"
struct FaceDrawSub {
    char pad00[0x40];
    FaceMtx m[2];
    char padA0[0x10];
    FaceMtx animMtx;
    int anim;
    unsigned char finished;
    char padE5[3];
    float alpha;
    int overlay;
    FaceVecView offset;
};
#include "game/types/FaceDrawModel.h"
union FaceDrawPipe { float f32; unsigned int u32; };
#include "game/types/at_address.h"
volatile FaceDrawPipe GXWGFifo AT_ADDRESS(0xCC008000);
#define FIFO GXWGFifo
extern "C" {
extern const float lbl_806D6DE4, lbl_806D6DE8;
extern const float lbl_806DB5E0, lbl_806DB5E8, lbl_806DB5EC, lbl_806DB5F0, lbl_806DB5F4;
void GXSetCullMode(int); void GXClearVtxDesc();
void GXSetVtxDesc(int,int); void GXSetVtxAttrFmt(int,int,int,int,int);
void GXSetNumChans(int); void GXSetChanCtrl(int,int,int,int,int,int,int);
void GXSetNumTevStages(int); void GXSetBlendMode(int,int,int,int);
void GXSetTevOrder(int,int,int,int); void GXSetTevOp(int,int);
void GXSetNumTexGens(int); void GXSetTexCoordGen2(int,int,int,int,int,int);
void GXSetCurrentMtx(int); void GXLoadPosMtxImm(FaceMtx,int);
void GXBegin(int,int,int); void HSD_StateInvalidate(int);
void *GetCourseScene3D(); void HSD_CObjGetViewingMtx(void *,FaceMtx);
float (*CObj_GetProjMatrix_Cached(void *))[4];
void CObj_LoadProjMatrix(void *,FaceDrawVec *);
void PSMTXScale(FaceMtx,float,float,float); void PSMTXTrans(FaceMtx,float,float,float);
void PSMTXCopy(const float (*)[4],FaceMtx);
void PSMTXConcat(const float (*)[4],const float (*)[4],FaceMtx);
void PSMTXMultVec(const float (*)[4],const FaceDrawVec *,FaceDrawVec *);
void Vec3_Normalize(FaceDrawVec *,FaceDrawVec *);
unsigned char fn_8011D890(int,float *,float *);
void DebugPrintf(const char *,...);
void Object_SetAnimBinding(void *,FaceMtx,int);
void Object_SetField8_AndDirty(void *,float);
void clNormal3D_Exec(void *); void Object_DriveAnimMatrix(void *);
void Object_RenderJObjTree(void *,int);
}

static inline void BuildFaceQuads(FaceDrawModel *self, FaceDrawVec *vertexBase, const FaceDrawVec *alternateBase, FaceMtx *world) {
    FaceMtx *matrix;
    const FaceDrawVec *standard;
    const FaceDrawVec *alternate;
    const FaceDrawVec *normal;
    FaceDrawVec *out;
    const FaceDrawVec *s, *a, *n;
    int i;
    out=vertexBase; normal=sQuadNormal; alternate=alternateBase; standard=sQuadStandard; matrix=world;
    for (i=0;i<2;++i) {
        int j;
        FaceDrawVec *q;
        q=out; n=normal; a=alternate; s=standard;
        for (j=0;j<4;++j) {
            if (self->left<0) PSMTXMultVec(*matrix,n,q);
            else if (self->variant==1) PSMTXMultVec(*matrix,a,q);
            else PSMTXMultVec(*matrix,s,q);
            ++q; ++n; ++a; ++s;
        }
        out+=4; normal+=4; alternate+=4; standard+=4; ++matrix;
    }
}
static inline void TransformQuads(FaceDrawVec *vertices, const FaceDrawVec *quads, FaceMtx *world, int &i, int &j) {
    FaceMtx *matrix;
    const FaceDrawVec *src;
    FaceDrawVec *out;
    src=quads; matrix=world; out=vertices;
    for (i=0;i<2;++i) {
        const FaceDrawVec *p;
        FaceDrawVec *q;
        q=out; p=src;
        for (j=0;j<4;++j) { PSMTXMultVec(*matrix,p,q); ++q; ++p; }
        out+=4; src+=4; ++matrix;
    }
}
static inline void FillFaceUV(float *uv, const float *rect) {
    float mid = lbl_806DB5EC * (rect[3] - rect[1]) + rect[1];
    uv[0]=rect[0]; uv[1]=mid; uv[2]=rect[2]; uv[3]=mid;
    uv[4]=rect[2]; uv[5]=rect[1]; uv[6]=rect[0]; uv[7]=rect[1];
    uv[8]=rect[0]; uv[9]=rect[3]; uv[10]=rect[2]; uv[11]=rect[3];
    uv[12]=rect[2]; uv[13]=mid; uv[14]=rect[0]; uv[15]=mid;
}

static inline void FillFaceUVExpanded(float *uv, const float *rect) {
    float bottom, left, right, top, factor, mid, difference;
    top=rect[1]; bottom=rect[3]; left=rect[0];
    difference=bottom-top;
    factor=lbl_806DB5EC;
    mid=factor*difference+top;
    right=rect[2];
    uv[0]=left; uv[1]=mid; uv[2]=right; uv[3]=mid;
    uv[4]=right; uv[5]=top; uv[6]=left; uv[7]=top;
    uv[8]=left; uv[9]=bottom; uv[10]=right; uv[11]=bottom;
    uv[12]=right; uv[13]=mid; uv[14]=left; uv[15]=mid;
}

/* Keep each vertex attribute write together; snapshot displacement after GXBegin. */
static inline void WriteFaceVertex(FaceDrawVec *p, float *uv, float x, float z, unsigned int color) {
    FIFO.f32=x+p->x; FIFO.f32=p->y; FIFO.f32=z+p->z;
    FIFO.u32=color; FIFO.f32=uv[0]; FIFO.f32=uv[1];
}
static inline void WriteFaceVertexPlain(FaceDrawVec *p, float *uv, unsigned int color) {
    FIFO.f32=p->x; FIFO.f32=p->y; FIFO.f32=p->z;
    FIFO.u32=color; FIFO.f32=uv[0]; FIFO.f32=uv[1];
}
static inline void DrawFaceQuad(FaceDrawVec *p, float *uv, FaceDrawVec *offset, unsigned int color) {
    GXBegin(0x80,0,4);
    float z, x; x=offset->x; z=offset->z;
    float f, u, v;
    u = uv[0]; v = uv[1];
    f = p[0].x; f = x + f; FIFO.f32=f;
    f = p[0].y; FIFO.f32=f;
    f = p[0].z; f = z + f; FIFO.f32=f;
    FIFO.u32=color; FIFO.f32=u; FIFO.f32=v;
    u = uv[2]; v = uv[3];
    f = p[1].x; f = x + f; FIFO.f32=f;
    f = p[1].y; FIFO.f32=f;
    f = p[1].z; f = z + f; FIFO.f32=f;
    FIFO.u32=color; FIFO.f32=u; FIFO.f32=v;
    u = uv[4]; v = uv[5];
    f = p[2].x; f = x + f; FIFO.f32=f;
    f = p[2].y; FIFO.f32=f;
    f = p[2].z; f = z + f; FIFO.f32=f;
    FIFO.u32=color; FIFO.f32=u; FIFO.f32=v;
    u = uv[6]; v = uv[7];
    f = p[3].x; f = x + f; FIFO.f32=f;
    f = p[3].y; FIFO.f32=f;
    f = p[3].z; f = z + f; FIFO.f32=f;
    FIFO.u32=color; FIFO.f32=u; FIFO.f32=v;
}
static inline void DrawFaceQuadCached(FaceDrawVec *p, float *uv, FaceDrawVec *offset, unsigned int color) {
    DrawFaceQuad(p,uv,offset,color);
}
static inline void DrawFaceQuadPlain(FaceDrawVec *p, float *uv, FaceDrawVec *offset, unsigned int color) {
    GXBegin(0x80,0,4);
    float f, u, v;
    u = uv[0]; v = uv[1];
    f = p[0].x; FIFO.f32=f;
    f = p[0].y; FIFO.f32=f;
    f = p[0].z; FIFO.f32=f;
    FIFO.u32=color; FIFO.f32=u; FIFO.f32=v;
    u = uv[2]; v = uv[3];
    f = p[1].x; FIFO.f32=f;
    f = p[1].y; FIFO.f32=f;
    f = p[1].z; FIFO.f32=f;
    FIFO.u32=color; FIFO.f32=u; FIFO.f32=v;
    u = uv[4]; v = uv[5];
    f = p[2].x; FIFO.f32=f;
    f = p[2].y; FIFO.f32=f;
    f = p[2].z; FIFO.f32=f;
    FIFO.u32=color; FIFO.f32=u; FIFO.f32=v;
    u = uv[6]; v = uv[7];
    f = p[3].x; FIFO.f32=f;
    f = p[3].y; FIFO.f32=f;
    f = p[3].z; FIFO.f32=f;
    FIFO.u32=color; FIFO.f32=u; FIFO.f32=v;
}

static inline void DrawPlainQuads(FaceDrawVec *&draw, float *tex, FaceDrawVec *offset, int &i) {
    for (i=0;i<2;++i) { DrawFaceQuadPlain(draw,tex,offset,0xffffffff); tex+=8; draw+=4; }
}
static inline void DrawQuads(FaceDrawVec *&draw, float *tex, FaceDrawVec *offset, int &i) {
    for (i=0;i<2;++i) { DrawFaceQuad(draw,tex,offset,0xffffffff); tex+=8; draw+=4; }
}
static inline void BuildOverlayQuads(FaceDrawModel *self, FaceDrawVec *vertexBase, const FaceDrawVec *&alternateBase, FaceMtx scale, FaceMtx translation, FaceMtx temporary, FaceMtx copy) {
    int j;
    FaceDrawVec *dstRow=vertexBase;
    for (int i=0;i<2;++i) {
        PSMTXCopy(self->sub->m[i],copy);
        FaceVecView localOffset;
        localOffset=self->sub->offset;
        copy[0][3]+=localOffset.value.x; copy[1][3]+=localOffset.value.y; copy[2][3]+=localOffset.value.z;
        PSMTXConcat(scale,copy,temporary);
        PSMTXConcat(translation,temporary,temporary);
        const FaceDrawVec *p;
        FaceDrawVec *q;
        q=dstRow; p=alternateBase;
        for (j=0;j<4;++j) { PSMTXMultVec(temporary,p,q); ++q; ++p; }
        alternateBase+=4; dstRow+=4;
    }
}
static inline void DrawCachedQuads(FaceDrawVec *&vertexBase, float *&uvBase, FaceDrawVec *offset, unsigned int color) {
    for (int i=0;i<2;++i) { DrawFaceQuadCached(vertexBase,uvBase,offset,color); uvBase+=8; vertexBase+=4; }
}
extern "C" void fn_8022BFA8(FaceDrawModel *self);
extern "C" void fn_8022CDE4(FaceDrawModel *self) {
    fn_8022BFA8(self);
}

/* The quad writers reuse `f`, `u`, `v` for every vertex and the target keeps
   one register per variable (v f0, u f1, f f2, x f3, z f4 = declaration order
   z, x, f, u, v), with the next u/v loaded right after the previous one is
   stored: live ranges are not split and the copies are not propagated. */
#pragma push
#pragma opt_lifetimes off
#pragma opt_propagation off
extern "C" void fn_8022BFA8(FaceDrawModel *self) {
    FaceDrawVec vertices[8];
    FaceMtx world[2], view, temporary, scale, translation, projection;
    float uv[16];
    FaceMtx copy;
    float rect[4];
    FaceDrawVec offset, eye;
    if (!self->kart) return;
    if (self->scale <= lbl_806DB5E0) {
        if (self->sub->anim == 0) {
            if (++self->timer >= 160) self->sub->finished=1;
        } else if (self->sub->anim == 1) {
            if (++self->timer >= 360) self->sub->finished=1;
        }
        return;
    }
    GXSetCullMode(0); GXClearVtxDesc();
    GXSetVtxDesc(9,1); GXSetVtxAttrFmt(0,9,1,4,0);
    GXSetVtxDesc(11,1); GXSetVtxAttrFmt(0,11,0,5,0);
    GXSetVtxDesc(13,1); GXSetVtxAttrFmt(0,13,1,4,0);
    GXSetNumChans(1); GXSetChanCtrl(4,0,1,1,0,0,2);
    GXSetNumTevStages(1); GXSetBlendMode(1,4,5,0);
    GXSetTevOrder(0,0,0,4); GXSetTevOp(0,0);
    GXSetNumTexGens(1); GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
    GXSetCurrentMtx(0);
    HSD_CObjGetViewingMtx(*(void **)((char *)GetCourseScene3D()+4),view);
    GXLoadPosMtxImm(view,0);
    PSMTXScale(scale,self->scale*lbl_806D6DE4,self->scale*lbl_806D6DE8,self->scale);
    PSMTXTrans(translation,self->x,self->y,self->z);
    PSMTXCopy(CObj_GetProjMatrix_Cached(GetCourseScene3D()),projection);
    projection[2][3]=lbl_806DB5E0; projection[1][3]=lbl_806DB5E0; projection[0][3]=lbl_806DB5E0;
    PSMTXConcat(projection,scale,scale);
    PSMTXConcat(scale,self->sub->m[0],world[0]);
    PSMTXConcat(translation,world[0],world[0]);
    PSMTXConcat(scale,self->sub->m[1],world[1]);
    PSMTXConcat(translation,world[1],world[1]);
    offset.z=lbl_806DB5E0; offset.y=lbl_806DB5E0; offset.x=lbl_806DB5E0;
    void *scene=GetCourseScene3D();
    if (scene) {
        CObj_LoadProjMatrix(scene,&eye);
        offset.x=eye.x-self->x; offset.z=eye.z-self->z;
        Vec3_Normalize(&offset,&offset);
        offset.x*=lbl_806DB5E8; offset.z*=lbl_806DB5E8;
    }
    if (self->left>0) {
        FaceDrawVec *draw=vertices;
        int i, j;
        TransformQuads(draw,sQuadNormal,world,i,j);
        if (!fn_8011D890(self->left,rect,0)) {
            DebugPrintf("clSprManager::SetTexture Error!! - imamura/EnmyFaceEffect.cpp, %d",0x5e2);
            HSD_StateInvalidate(0x7e); return;
        }
        FillFaceUV(uv,rect);
        DrawPlainQuads(draw,uv,&offset,i);
    }
    if (self->right>0) {
        FaceDrawVec *draw=vertices;
        int i, j;
        TransformQuads(draw,sQuadRight,world,i,j);
        fn_8011D890(self->right,rect,0);
        FillFaceUV(uv,rect);
        DrawQuads(draw,uv,&offset,i);
    }
    FaceDrawVec *vertexBase=vertices;
    float *uvBase;
    const FaceDrawVec *alternateBase=sQuadWide;
    BuildFaceQuads(self,vertexBase,alternateBase,world);
    fn_8011D890(self->face,rect,0);
    uvBase=uv;
    FillFaceUVExpanded(uvBase,rect); offset.x+=offset.x; offset.z+=offset.z;
    {
        FaceDrawVec *draw=vertexBase;
        float *tex=uvBase;
        for (int i=0;i<2;++i) { DrawFaceQuad(draw,tex,&offset,0xffffffff); tex+=8; draw+=4; }
    }
    if (self->kart->state==0) {
        FaceDrawVec *q=vertexBase;
        const FaceDrawVec *p=sQuadTop;
        for (int i=0;i<4;++i) { PSMTXMultVec(world[0],p,q); ++q; ++p; }
        fn_8011D890(sFaceSprites[9],rect,0);
        uvBase[0]=rect[0]; uvBase[1]=rect[3]; uvBase[2]=rect[2]; uvBase[3]=rect[3];
        uvBase[4]=rect[2]; uvBase[5]=rect[1]; uvBase[6]=rect[0]; uvBase[7]=rect[1];
        offset.x+=offset.x; offset.z+=offset.z;
        DrawFaceQuad(vertexBase,uvBase,&offset,0xffffffff);
    }
    int kind=self->sub->overlay;
    if (kind!=-1) {
        BuildOverlayQuads(self,vertexBase,alternateBase,scale,translation,temporary,copy);
        fn_8011D890(sFaceSprites[kind],rect,0);
        offset.x+=offset.x; offset.z+=offset.z;
        FillFaceUVExpanded(uvBase,rect);
        unsigned int color=0xffffff00;
        color=(color&~0xff)|((int)(lbl_806DB5F0*self->sub->alpha)&0xff);
        DrawCachedQuads(vertexBase,uvBase,&offset,color);
    }
    HSD_StateInvalidate(0x7e); GXSetCullMode(2);
    kind=self->sub->anim;
    if (kind!=-1) {
        float frame=++self->timer;
        if (kind==0) frame+=lbl_806DB5F4;
        PSMTXConcat(projection,self->sub->animMtx,temporary);
        PSMTXConcat(translation,temporary,temporary);
        Object_SetAnimBinding(self->models[kind],temporary,0);
        Object_SetField8_AndDirty(self->models[kind],frame);
        if (kind==0) {
            clNormal3D_Exec(self->models[kind]);
            if (self->timer>=160) self->sub->finished=1;
        } else if (kind==1) {
            clNormal3D_Exec(self->models[kind]);
            if (self->timer>=360) self->sub->finished=1;
        }
        Object_DriveAnimMatrix(self->models[kind]);
        Object_RenderJObjTree(self->models[kind],7);
    }
}
#pragma pop

/*
 * Never called, so the linker strips the code, but its format string
 * stays in .rodata between the clEFacePoly RTTI name and the model names.
 * The real body is unknown; it follows the draw function in the source
 * (its string precedes the draw function's).
 */
static void ReportLoadErrors(int line) {
    OSReport("Can't Load File!! - EnmyFaceEffect.cpp,&d\n", line);
}
