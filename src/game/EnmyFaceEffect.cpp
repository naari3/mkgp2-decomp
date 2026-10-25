/*
 * 0x8022CE04..0x802300C8: clEFacePoly / clEFacePolyEffect, the item
 * reaction drawn over a rival's face icon (pen scribble, pencil, ...).
 * Source file name from the rodata strings: imamura/EnmyFaceEffect.cpp.
 * The TU owns .rodata 0x803DAB54..0x803DAE88 and .bss 0x80679CE0..0x80679DE8.
 */

void *operator new(unsigned long size);
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

struct Vec3 {
    float x, y, z;
};

struct Vec3c : Vec3 {
    Vec3c(const Vec3 &v) : Vec3(v) {}
    ~Vec3c();
};

static inline Vec3 MakeVec3(float x, float y, float z) {
    Vec3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

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

struct clNormal3D {
    char _opaque[0x5C];
    clNormal3D(const char *res, int flags);
    ~clNormal3D();
};

extern const unsigned int lbl_803DAB54[];
extern const unsigned int lbl_803DADC4[];
extern const char lbl_803DAE40[];
extern const char lbl_803DAE5C[];
extern const char lbl_803DAE70[];

extern const unsigned int lbl_803DAB54[156] = {0x00000C68, 0x00000C69, 0x00000C66, 0x00000C67, 0x00000C63, 0x00000C65, 0x00000C64, 0x00000C6A, 0x00000C6B, 0x00000C28, 0x00000C49, 0x00000C32, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xC1F80000, 0x00000000, 0x00000000, 0x41F80000, 0x00000000, 0x00000000, 0x41F80000, 0x42180000, 0x00000000, 0xC1F80000, 0x42180000, 0x00000000, 0xC1F80000, 0xC2180000, 0x00000000, 0x41F80000, 0xC2180000, 0x00000000, 0x41F80000, 0x00000000, 0x00000000, 0xC1F80000, 0x00000000, 0x00000000, 0xC20E9999, 0x00000000, 0x00000000, 0x420E9999, 0x00000000, 0x00000000, 0x420E9999, 0x420E9999, 0x00000000, 0xC20E9999, 0x420E9999, 0x00000000, 0xC20E9999, 0xC20E9999, 0x00000000, 0x420E9999, 0xC20E9999, 0x00000000, 0x420E9999, 0x00000000, 0x00000000, 0xC20E9999, 0x00000000, 0x00000000, 0xC20E9999, 0x00000000, 0x00000000, 0x420E9999, 0x00000000, 0x00000000, 0x420E9999, 0x422B8247, 0x00000000, 0xC20E9999, 0x422B8247, 0x00000000, 0xC20E9999, 0xC1B7048E, 0x00000000, 0x420E9999, 0xC1B7048E, 0x00000000, 0x420E9999, 0x00000000, 0x00000000, 0xC20E9999, 0x00000000, 0x00000000, 0xC20E9999, 0x00000000, 0x00000000, 0x420E9999, 0x00000000, 0x00000000, 0x420E9999, 0x422CB456, 0x00000000, 0xC20E9999, 0x422CB456, 0x00000000, 0xC20E9999, 0xC22CB456, 0x00000000, 0x420E9999, 0xC22CB456, 0x00000000, 0x420E9999, 0x00000000, 0x00000000, 0xC20E9999, 0x00000000, 0x00000000, 0xC24ACF13, 0x00000000, 0x00000000, 0x424ACF13, 0x00000000, 0x00000000, 0x424ACF13, 0x424ACF13, 0x00000000, 0xC24ACF13, 0x424ACF13, 0x00000000, 0xC24ACF13, 0xC24ACF13, 0x00000000, 0x424ACF13, 0xC24ACF13, 0x00000000, 0x424ACF13, 0x00000000, 0x00000000, 0xC24ACF13, 0x00000000, 0x00000000, 0xC1F80000, 0x41A00000, 0x00000000, 0x41F80000, 0x41A00000, 0x00000000, 0x41F80000, 0x42740000, 0x00000000, 0xC1F80000, 0x42740000, 0x00000000};
extern const unsigned int lbl_803DADC4[31] = {0x636C4546, 0x61636550, 0x6F6C7900, 0x43616E27, 0x74204C6F, 0x61642046, 0x696C6521, 0x21202D20, 0x456E6D79, 0x46616365, 0x45666665, 0x63742E63, 0x70702C26, 0x640A0000, 0x636C5370, 0x724D616E, 0x61676572, 0x3A3A5365, 0x74546578, 0x74757265, 0x20457272, 0x6F722121, 0x202D2069, 0x6D616D75, 0x72612F45, 0x6E6D7946, 0x61636545, 0x66666563, 0x742E6370, 0x702C2025, 0x64000000};
extern const char lbl_803DAE40[0x1C] = "it_j_00_rakugaki_pen.dat";
extern const char lbl_803DAE5C[0x14] = "it_v_02_pencil.dat";
extern const char lbl_803DAE70[0x18] = "clEFacePolyEffect";

struct PalSlot {
    unsigned char free;
    void *data;
    void *pal;
};

static Vec3c sPosA = MakeVec3(0.0f, 0.0f, 0.0f);
static Vec3c sPosB = MakeVec3(0.0f, 13.0f, 15.0f);
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

static inline void MakeMtx(Mtx out, float s, const Vec3 &p, const Vec3 &r) {
    Mtx tr, sc, rot;
    PSMTXIdentity(rot);
    PSMTXScale(sc, s, s, s);
    PSMTXTrans(tr, p.x, p.y, p.z);
    RotMtx(rot, r.x, r.y, r.z);
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
    virtual ~clEFacePolyEffect() {}

    int timer;
    int state;
    int type;
    int sub;
    int i14;
    float speed;
    float f1C;
    char pad20[4];
    Vec3 pos;
    Vec3 rot;
    float scale;
    Mtx mtxA;
    Mtx mtxB;
    Vec3 pos2;
    float scale2;
    Mtx mtxC;
    int mode;
    unsigned char done;
    float alpha;
    int anim;
    Vec3 vF0;
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
    Vec3 v14;
    float f20;
    int palIdx;
    KartRender *owner;
    clEFacePolyEffect *effect;
    clNormal3D *models[2];

    clEFacePoly(KartRender *o, int a, int b, int c);
    void Update();
};

void clEFacePoly::Update() {
    if (owner) {
        effect->Update();
    }
}

clEFacePoly::~clEFacePoly() {
    int i;
    for (i = 0; i < 2; i++) {
        if (models[i]) {
            delete models[i];
            models[i] = 0;
        }
    }
    for (i = 0; i < 12; i++) {
        fn_80120A08(lbl_803DAB54[12]);
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
                    TEXReleasePalette(&s->pal);
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
    models[0] = new clNormal3D(lbl_803DAE40, 0);
    models[1] = new clNormal3D(lbl_803DAE5C, 0);
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
        Vec3 r = rot;
        Vec3 p = pos;
        p.y = -(38.0f * (r.x / 65.0f) - p.y);
        r.x = 0.9f * r.x;
        MakeMtx(mtxB, scale, p, r);
        r.x = 1.1f * -rot.x;
        MakeMtx(mtxA, scale, p, r);
        return;
    }
    MakeMtx(mtxA, scale, pos, rot);
    MakeMtx(mtxB, scale, pos, rot);
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
        speed -= 0.4f;
        if (pos.y < 1.2f) {
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
