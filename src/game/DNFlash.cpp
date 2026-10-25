/*
 * 0x802280F8..0x80228D64: clDNFlash (Dino Dino Jungle camera flashes).
 * Flash points are read from DNA_cameraF_trans.dat into a 3x3 grid of
 * areas; while the player is near, flashes pop at random points of the
 * player's row and column, and a burst plays when the player drives through
 * one of four trigger boxes in the right direction. The TU owns .rodata
 * 0x803D0390..0x803D08A8, addressed off one hoisted base. The static
 * initializer (fn_80228D64, fills the trigger box bounds) and its min/max
 * helpers stay in asm.
 */

void *operator new(unsigned long size);
void operator delete(void *p) throw();

typedef float Mtx[3][4];

struct Vec3f {
    float x, y, z;
};

struct HSD_JObj {
    char pad00[8];
    HSD_JObj *next;
    HSD_JObj *parent;
    HSD_JObj *child;
    unsigned int flags;
    char pad18[0x38 - 0x18];
    Vec3f translate;
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
};

struct FlashPartObj : FlashPart {
    FlashPartObj();
};

struct TriggerBox {
    Vec3f a;
    Vec3f b;
};

struct clMapEffectParts {
    virtual ~clMapEffectParts() {}
    virtual void Update();
    virtual void Draw();
    virtual void Enable(int on);
    clMapEffectParts() {}
};

struct clDNFlash : clMapEffectParts {
    clNormal3D *fx;
    int timer;
    unsigned char inside;
    int burst;
    int counts[9];
    FlashPoint points[9][30];
    FlashPart parts[20];
    FlashPart *free[2];

    clDNFlash();
    virtual void Enable(int on);
    virtual ~clDNFlash();
    virtual void Update();
    virtual void Draw();
    unsigned char Check();
    void Spawn();
};

extern "C" {
extern KartRender *g_playerRenderObj;
extern int g_longRoundFlag;
extern int g_reverseRoundFlag;
extern const char lbl_806DB4A4[7];
extern const char lbl_806DB4AC[5];
extern const float lbl_806DB490;
extern const int lbl_806DB494;
extern const float lbl_806DB498;
extern const float lbl_806DB49C;
extern const float lbl_806DB4A0;
extern Vec3f lbl_804EE008[4];
extern Vec3f lbl_804EE038[4];
void __assert(const char *file, int line, const char *cond);
HSD_JObj *Archive_GetRootJObj(clNormal3D *m);
void *HSD_JObjGetDObj(HSD_JObj *jobj);
void HSD_JObjSetFlags(HSD_JObj *jobj, int flags);
void fn_80182954(HSD_JObj *jobj, int on);
float (*Object_GetJObjLocalMatrix(clNormal3D *m))[4];
void Object_DtorWithGXSync(clNormal3D *m, int flag);
void Object_SetColorAlphaOnly(clNormal3D *m, int idx, float alpha);
void PSMTXScale(Mtx m, float x, float y, float z);
void PSMTXMultVec(float (*m)[4], Vec3f *src, Vec3f *dst);
const float *KartDriver_GetKartRootMtx(KartRender *k);
float *KartMovement_GetVelocityPtr(KartRender *k);
void DebugPrintf(const char *fmt, ...);
int rand(void);
}

extern const unsigned int lbl_803D0390[0x102] = {
    0x3F800000, 0x3F333333, 0x3F666666, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000,
    0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000,
    0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000,
    0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000,
    0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000,
    0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000,
    0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000,
    0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000,
    0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000,
    0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x00000000,
};
extern const float lbl_803D0798[3] = {9.0f, 11.0f, 7.0f};
extern const float lbl_803D07A4[3] = {2000.0f, 3300.0f, 10000.0f};
extern const float lbl_803D07B0[3] = {-3700.0f, -5700.0f, -15000.0f};
extern const TriggerBox lbl_803D07BC[4] = {
    {{4709.0f, 0.0f, -5895.0f}, {4493.0f, 0.0f, -5820.0f}},
    {{3515.0f, 0.0f, -7468.0f}, {3428.0f, 0.0f, -7700.0f}},
    {{4300.0f, 0.0f, -2580.0f}, {4265.0f, 0.0f, -2455.0f}},
    {{3150.0f, 0.0f, -3577.0f}, {3220.0f, 0.0f, -3683.0f}},
};
extern const char lbl_803D081C[0xC] = "clDNFlash";
extern const char lbl_803D0828[0x14] = "clMapEffectParts";
extern const char lbl_803D083C[0x20] = " DeleteMapEffect : clDNFlash\n";
extern const char lbl_803D085C[0x20] = " CreateMapEffect : clDNFlash\n";
extern const char lbl_803D087C[0x10] = "ef_camflash.dat";
extern const char lbl_803D088C[0x1C] = "DNA_cameraF_trans.dat";

template <class T> T Min(const T &a, const T &b) {
    return a < b ? a : b;
}

static inline int AreaIndex(float x, float z) {
    int ix = -1;
    int iz = ix;
    for (int i = 0; i < 3; i++) {
        if (x < lbl_803D07A4[i]) {
            ix = i;
            break;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (z > lbl_803D07B0[i]) {
            iz = i;
            break;
        }
    }
    if (ix < 0 || iz < 0) {
        return -1;
    }
    return ix + iz * 3;
}

static inline int AreaIndexV(const Vec3f &p) {
    int ix = -1;
    int iz = ix;
    for (int i = 0; i < 3; i++) {
        if (p.x < lbl_803D07A4[i]) {
            ix = i;
            break;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (p.z > lbl_803D07B0[i]) {
            iz = i;
            break;
        }
    }
    if (ix < 0 || iz < 0) {
        return -1;
    }
    return ix + iz * 3;
}

static inline void GetTranslation(HSD_JObj *jobj, Vec3f *out) {
    if (jobj == 0) {
        __assert(lbl_806DB4A4, 0x3E4, lbl_806DB4AC);
    }
    *out = jobj->translate;
}

static inline HSD_JObj *JObjNext(HSD_JObj *jobj) {
    if (jobj == 0) {
        return 0;
    }
    return jobj->next;
}

static inline HSD_JObj *JObjChild(HSD_JObj *jobj) {
    if (jobj == 0) {
        return 0;
    }
    return jobj->child;
}

void clDNFlash::Draw() {
    Mtx m;

    if (fx == 0) {
        return;
    }
    GXChannel ch(Archive_GetRootJObj(fx), HSD_JObjGetDObj(Archive_GetRootJObj(fx)), 0x40000000, 1);
    for (int i = 0; i < 20; i++) {
        if (parts[i].active && parts[i].owner) {
            PSMTXScale(m, parts[i].scale, parts[i].scale, parts[i].scale);
            m[0][3] = parts[i].owner->pos.x;
            m[1][3] = parts[i].owner->pos.y;
            m[2][3] = parts[i].owner->pos.z;
            Object_SetColorAlphaOnly(fx, 0, parts[i].alpha);
            ch.PushTransform(m);
        }
    }
}

#pragma dont_inline on
unsigned char clDNFlash::Check() {
    if (burst > 0) {
        return 0;
    }
    KartRender *k;
    if ((k = g_playerRenderObj) == 0) {
        return 0;
    }
    const float *m = KartDriver_GetKartRootMtx(k);
    int t = 0;
    float x = m[3];
    float z = m[11];
    if (g_longRoundFlag == 1) {
        t = 2;
    }
    if (g_reverseRoundFlag == 1) {
        t++;
    }
    unsigned char prev = inside;
    float mnx = lbl_804EE008[t].x;
    inside = 0;
    if (x < mnx) {
        return 0;
    }
    if (x > lbl_804EE038[t].x) {
        return 0;
    }
    if (z < lbl_804EE008[t].z) {
        return 0;
    }
    if (z > lbl_804EE038[t].z) {
        return 0;
    }
    float nx = -(lbl_803D07BC[t].b.x - lbl_803D07BC[t].a.x);
    float nz = lbl_803D07BC[t].b.z - lbl_803D07BC[t].a.z;
    nx *= KartMovement_GetVelocityPtr(k)[2];
    if (nz * KartMovement_GetVelocityPtr(k)[0] + nx < lbl_806DB490) {
        return 0;
    }
    inside = 1;
    return prev != 1;
}
#pragma dont_inline reset

void clDNFlash::Spawn() {
    int list[5];

    if (g_playerRenderObj == 0) {
        return;
    }
    const float *m = KartDriver_GetKartRootMtx(g_playerRenderObj);
    int area = AreaIndex(m[3], m[11]);
    if (area < 0) {
        return;
    }
    int col = area % 3;
    int n = 0;
    list[n++] = area - col;
    list[n++] = list[0] + 1;
    list[n++] = list[1] + 1;
    if (area != col) {
        list[n++] = col;
    }
    if (area != col + 3) {
        list[n++] = col + 3;
    }
    if (area != col + 6) {
        list[n++] = col + 6;
    }
    FlashPoint *pt = 0;
    int start = rand() % 5;
    for (int tries = 0; tries < 5; tries++) {
        int k = rand() % counts[list[start]];
        for (int j = Min(counts[list[start]], lbl_806DB494); j > 0; j--) {
            if (k >= counts[list[start]]) {
                k = 0;
            }
            if (points[list[start]][k].used != 1) {
                pt = &points[list[start]][k];
                break;
            }
            k++;
        }
        if (pt) {
            break;
        }
        if (++start >= 5) {
            start = 0;
        }
    }
    if (pt == 0) {
        return;
    }
    for (int i = 0; i < 2; i++) {
        if (free[i]) {
            FlashPart *p = free[i];
            pt->used = 1;
            p->owner = pt;
            p->active = 1;
            p->life = 8;
            p->scale = lbl_803D0798[rand() % 3];
            p->dscale = lbl_806DB498;
            p->alpha = lbl_806DB49C;
            free[i] = 0;
            return;
        }
    }
}

void clDNFlash::Update() {
    if (Check() == 1) {
        burst = 180;
    }
    if (--timer <= 0) {
        Spawn();
        timer = rand() % 10;
    }
    if (burst > 0) {
        Spawn();
        burst--;
    }
    for (int i = 0; i < 20; i++) {
        if (!parts[i].active) {
            if (free[0]) {
                free[1] = &parts[i];
            } else {
                free[0] = &parts[i];
            }
        } else if (--parts[i].life <= 0) {
            parts[i].owner->used = 0;
            parts[i].owner = 0;
            parts[i].active = 0;
        } else {
            parts[i].scale += parts[i].dscale;
            if (parts[i].life <= 5) {
                parts[i].alpha -= lbl_806DB4A0;
            }
        }
    }
}

clDNFlash::~clDNFlash() {
    if (fx) {
        delete fx;
        fx = 0;
    }
    DebugPrintf(lbl_803D083C);
}

clDNFlash::clDNFlash() {
    fx = 0;
    timer = 0;
    inside = 0;
    burst = 0;
    DebugPrintf(lbl_803D085C);
    fx = new clNormal3D(lbl_803D087C, 1);
    fn_80182954(Archive_GetRootJObj(fx), 1);
    HSD_JObjSetFlags(Archive_GetRootJObj(fx), 0x200);
    for (int i = 0; i < 20; i++) {
        parts[i].active = 0;
        parts[i].owner = 0;
    }
    for (int i = 0; i < 20; i++) {
        counts[i] = 0;
    }
    free[0] = free[1] = 0;
    clNormal3D *path = new clNormal3D(lbl_803D088C, 0);
    float(*lm)[4] = Object_GetJObjLocalMatrix(path);
    HSD_JObj *jobj = Archive_GetRootJObj(path);
    HSD_JObj *next = 0;
    for (; jobj; jobj = next) {
        Vec3f p;
        GetTranslation(jobj, &p);
        PSMTXMultVec(lm, &p, &p);
        int area = AreaIndexV(p);
        if (area < 0) {
            continue;
        }
        if (counts[area] < 30) {
            points[area][counts[area]].pos.x = p.x;
            points[area][counts[area]].pos.y = p.y;
            points[area][counts[area]].pos.z = p.z;
            points[area][counts[area]].used = 0;
            counts[area]++;
        }
        next = JObjNext(jobj);
        if (next == 0) {
            next = JObjChild(jobj);
        }
    }
    Object_DtorWithGXSync(path, 1);
}

void FlashPart::Tick() {
    if (!active) {
        return;
    }
    if (--life <= 0) {
        owner->used = 0;
        owner = 0;
        active = 0;
        return;
    }
    scale += dscale;
    if (life <= 5) {
        alpha -= lbl_806DB4A0;
    }
}

void FlashPart::Start(FlashPoint *pt) {
    pt->used = 1;
    owner = pt;
    active = 1;
    life = 8;
    scale = lbl_803D0798[rand() % 3];
    dscale = lbl_806DB498;
    alpha = lbl_806DB49C;
}

FlashPartObj::FlashPartObj() {
    active = 0;
    scale = lbl_806DB49C;
    alpha = lbl_806DB490;
    dscale = lbl_806DB490;
    life = 0;
    owner = 0;
}


