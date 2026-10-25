/*
 * 0x80230644..0x80231D50: clFaceEffect, the reaction icon (tears, sweat,
 * pencil scribble, ...) drawn on a rival's face icon, plus the helper
 * functions that pick a player's emblem / name plate resources.
 * Owns .rodata 0x803DAF98..0x803DB630 and .data 0x804EE248..0x804EE398.
 */

void *operator new(unsigned long size);
void operator delete(void *p) throw();

typedef float Mtx[3][4];

struct Vec3 {
    float x, y, z;
};

extern "C" {
void PSMTXIdentity(Mtx m);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXMultVec(const Mtx m, const Vec3 *src, Vec3 *dst);
float Sinf_LUT_Wrap(float deg);
float Cosf_LUT_Wrap(float deg);
void PreloadResource(int id);
void fn_80120A08(int id);
void *PcbSlot_GetByIndex(int slot);
unsigned char fn_8016C360(int id);
void fn_8016C394(int id);
void SoundMgr_PlaySE(int id);
void *GetCourseScene3D(void);
Mtx *CObj_GetProjMatrix_Cached(void *scene);
unsigned char GetVBlankFlag(void);
unsigned char VBlankValue_Get(void);
extern int g_cupId;
extern int g_roundIndex;
extern int g_consecutiveWinsTier;
extern unsigned char g_namCamFlag;
}

struct PlayerData {
    char pad0[0x19D];
    unsigned char b19D;
};
extern "C" PlayerData g_playerData;

struct ResCtrl {
    int resId;
    int field4, mode, fieldc;
    unsigned char flag, pad11[3];
    float x, y, z, width, height, field28, scaleX, scaleY;
    unsigned int colors[4];
    bool flipX;
    bool flipY;
    char pad46[2];
    int tail[4];
    ResCtrl();
    ~ResCtrl() {}
    void Show(float px, float py, float pz) {
        flag = 1;
        x = px;
        y = py;
        z = pz;
    }
    void SetScale(float s) {
        scaleX = s;
        scaleY = s;
    }
    void SetColor(unsigned int c) {
        colors[0] = c;
        colors[1] = c;
        colors[2] = c;
        colors[3] = c;
    }
};

extern "C" {
void fn_8011FAFC(ResCtrl *r, int prio);
void fn_80121E10(ResCtrl *r);
}

struct PcbSlot {
    unsigned char b0, b1, b2;
    unsigned char b3_0 : 2;
    unsigned char active : 1;
    unsigned char b3_3 : 5;
    unsigned char b4, b5;
    unsigned short h6_0 : 7;
    unsigned short tier : 4;
    unsigned short h6_11 : 5;
};

struct KartStatus {
    char pad0[0x10];
    unsigned long long bits;
    unsigned long long bits2;
};

struct KartRender {
    char pad0[0x1F4];
    int slot;
    int chara;
    char pad1FC[0x2D0 - 0x1FC];
    unsigned char special;
    char pad2D1[0x304 - 0x2D1];
    KartStatus *status;
};

extern "C" int fn_8023D1B4(KartRender *kart);

struct Sprite {
    int id;
    int prio;
    int i8;
    float x, y;
    float sx, sy;
    float f1C;
    float alpha;
    char pad24[0xC];
    Sprite(int id, int flag, float x, float y, float sx, float sy, float t, float a);
    void SetPos(float px, float py) {
        x = px;
        y = py;
    }
    void SetScale(float px, float py) {
        sx = px;
        sy = py;
    }
    ~Sprite();
};

extern "C" {
unsigned char fn_8019FE78(Sprite *s);
void fn_801A0004(Sprite *s);
void Sprite_SetAnimTime(Sprite *s, float t);
unsigned char Sprite_AdvanceAnim(Sprite *s, float dt);
}

struct clNormal3D {
    char _opaque[0x5C];
    clNormal3D(const char *res, int flags);
    ~clNormal3D();
};

extern "C" {
void Object_JObjUpdate_870(clNormal3D *o, int flags);
void Object_SetJObjScaleXYZ(clNormal3D *o, float x, float y, float z);
void Object_SetAnimBinding(clNormal3D *o, Mtx m, int flag);
void Object_SetColorAlphaOnly(clNormal3D *o, int idx, float a);
void Object_DriveAnimMatrix(clNormal3D *o);
void Object_RenderJObjTree(clNormal3D *o, int mask);
}


const unsigned int lbl_803DAF98[267] = {0x3F800000, 0x3F333333, 0x3F666666, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0xC3960000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
static const int kCpuNameRes[30] = {0x00000C49, 0x00000C4A, 0x00000C4B, 0x00000C4C, 0x00000C51, 0x00000C52, 0x00000C53, 0x00000C54, 0x00000C59, 0x00000C5A, 0x00000C5B, 0x00000C5C, 0x00000C5E, 0x00000C61, 0x00000C62, 0x00000C4D, 0x00000C4E, 0x00000C4F, 0x00000C50, 0x00000C55, 0x00000C56, 0x00000C57, 0x00000C58, 0x00000C5D, 0x00000C5A, 0x00000C5B, 0x00000C60, 0x00000C5F, 0x00000C61, 0x00000C62};
static const int kNameRes[13] = {0x00000C32, 0x00000C33, 0x00000C3C, 0x00000C36, 0x00000C3E, 0x00000C3B, 0x00000C3D, 0x00000C37, 0x00000C34, 0x00000C3A, 0x00000C38, 0x00000C35, 0x00000C39};
static const int kFlagRes[4] = {0x00002B00, 0x00002B01, 0x00002B02, 0x00002B03};
static const int kEmblemRes[4] = {0x00000C24, 0x00000C25, 0x00000C26, 0x00000C27};
static const int kModeRes[10] = {0x00000C66, 0x00000C66, 0x00000C68, 0x00000C69, 0x00000C6B, 0x00000C6A, 0x00000C67, 0x00000C63, 0x00000C65, 0x00000C64};
const unsigned int lbl_803DB4B8[56] = {0x3F800000, 0x40800000, 0x3F000000, 0x40D00000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x41480000, 0x41080000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x41200000, 0x40800000, 0x41C00000, 0x40000000, 0x42000000, 0x40C00000, 0x41200000, 0x40C00000, 0x41900000, 0x41400000, 0x41E00000, 0x41C00000, 0x41A00000, 0x40800000, 0x42000000, 0x40E00000, 0x42240000, 0x41600000, 0xC1200000, 0x40800000, 0xC1C00000, 0x40000000, 0xC2000000, 0x40C00000, 0xC1200000, 0x40C00000, 0xC1900000, 0x41400000, 0xC1E00000, 0x41C00000, 0xC1A00000, 0x40800000, 0xC2000000, 0x40E00000, 0xC2240000, 0x41600000};

struct Vec2 {
    float x, y;
};

static const Vec2 kIconOffset[13] = {{0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 8.0f}, {0.0f, 0.0f}, {0.0f, 10.0f}, {0.0f, 0.0f}, {0.0f, -16.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 8.0f}};
static const Vec3 sPenOrigin = {0.0f, 0.0f, -3.0f};

struct EmblemRes {
    int score;
    short id;
    short id2;
};

struct RankKey {
    int type;
    int value;
};

static EmblemRes sEmblems[10] = {
    {0x46, 0xC44, 0x1CC9},  {0x136, 0xC40, 0x1CC5}, {0x226, 0xC3F, 0x1CC4}, {0x316, 0xC41, 0x1CC6},
    {0x406, 0xC42, 0x1CC7}, {0x4F6, 0xC45, 0x1CCA}, {0x5E6, 0xC47, 0x1CCC}, {0x6D6, 0xC43, 0x1CC8},
    {0x7C6, 0xC48, 0x1CCD}, {0x8B6, 0xC46, 0x1CCB},
};

static RankKey sRankKeys[26] = {
    {1, 0}, {4, 0}, {1, 10}, {4, 0}, {1, 30}, {4, 0}, {1, 40}, {4, 0}, {1, 60}, {4, 0},
    {1, 70}, {4, 0}, {1, 62}, {4, 0}, {1, 73}, {4, 0}, {0, 0}, {3, 0}, {0, 20}, {3, 0},
    {0, 46}, {3, 0}, {0, 66}, {3, 0}, {0, 92}, {3, 0},
};

static const float kGlowOffset[2] = {0.0f, 10.0f};
static const char kPencilRes[] = "it_v_02_pencil.dat";

class clFaceEffect {
public:
    virtual ~clFaceEffect();
    KartRender *kart;
    int prio;
    float x, y;
    float scale;
    Sprite *sprL;
    Sprite *sprR;
    unsigned char animOn;
    int mode;
    int timer;
    int resId;
    int state;
    int counter;
    float glow;
    float glowSpeed;
    int i40;
    int sub;
    clNormal3D *model;
    float penX, penY, penAlpha, penRot;
    float alpha;

    clFaceEffect(KartRender *k, int p);
    bool IsIdle();
    void Hide();
    void FadeOut();
    void Request(int m);
    void Force(int m);
    void SetMode(int m);
    void UpdateSpecial(unsigned char draw, float px, float py);
    void Dummy();
    void Update(unsigned char draw);
    void UpdateIcon(unsigned char draw, float px, float py);

    void UpdateSprites(unsigned char draw, float px, float py) {
        KartStatus *st = kart->status;
        if (!fn_8019FE78(sprL)) {
            animOn = 0;
        }
        unsigned long long b = st->bits;
        b |= st->bits2;
        if (b & 0x10000) {
            Sprite_SetAnimTime(sprL, 0.0f);
            Sprite_SetAnimTime(sprR, 0.0f);
            animOn = 1;
        }
        if (draw == 1) {
            sprL->alpha = 1.0f;
            sprR->alpha = 1.0f;
        } else {
            sprL->alpha = 0.0f;
            sprR->alpha = 0.0f;
        }
        sprL->SetPos(px, py);
        sprR->SetPos(px, py);
        sprL->SetScale(scale, scale);
        sprR->SetScale(-scale, scale);
    }
};

static inline unsigned char TestBits(KartStatus *st, unsigned long long mask) {
    unsigned char hit;
    if ((st->bits & mask) == 0) {
        hit = 0;
    } else {
        hit = 1;
    }
    return hit;
}

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

bool clFaceEffect::IsIdle() {
    int s = state;
    bool r = false;
    if (s == 7 || s == 0 || s == 5) {
        r = true;
    }
    return r;
}

void clFaceEffect::Hide() {
    state = 7;
}

void clFaceEffect::FadeOut() {
    state = 6;
}

void clFaceEffect::Request(int m) {
    mode = m;
    if (state != 2) {
        state = 1;
    }
}

void clFaceEffect::Force(int m) {
    mode = m;
    state = 1;
}

void clFaceEffect::SetMode(int m) {
    mode = m;
}

void clFaceEffect::UpdateSpecial(unsigned char draw, float px, float py) {
    if (mode == -1) {
        UpdateSprites(draw, px, py);
    } else {
        animOn = 0;
    }
    switch (state) {
    case 0:
        return;
    case 1:
        alpha = 0.0f;
        counter = 0;
        if (mode == 6) {
            state = 3;
            sub = 0;
            penX = 0.0f;
            penY = 0.0f;
            penRot = 0.0f;
            penAlpha = 0.0f;
        } else if (mode == 2 || mode == 3) {
            state = 4;
            alpha = 1.0f;
            counter = 0;
            glow = 0.0f;
        } else {
            state = 2;
            alpha = 0.0f;
            glow = 0.0f;
            glowSpeed = 0.1f;
        }
        if (mode == 0 || mode == 1) {
            if (fn_8016C360(0xD3) == 1) {
                fn_8016C394(0xD3);
            }
            SoundMgr_PlaySE(0xD3);
        }
        break;
    case 2:
        glow += glowSpeed;
        if (glow >= 1.0f) {
            glowSpeed = -glowSpeed;
            glow = 1.0f;
        }
        if (glow <= 0.0f) {
            glowSpeed = -glowSpeed;
            glow = 0.0f;
        }
        alpha += 0.01f;
        if (alpha >= 1.0f) {
            alpha = 1.0f;
            state = 4;
            counter = 0;
        }
        break;
    case 3:
        switch (sub) {
        case 0:
            penX = 0.0f;
            penY = 1.1333333f;
            penRot = -20.0f;
            sub = 1;
            counter = 0;
            penAlpha = 1.0f;
            break;
        case 1:
            penRot += 7.0f;
            penY += 0.012000021f;
            if (penRot >= 200.0f) {
                penRot = 200.0f;
                sub = 2;
                counter = 0;
                if (fn_8016C360(0xD3) == 1) {
                    fn_8016C394(0xD3);
                }
                SoundMgr_PlaySE(0xD3);
            }
            break;
        case 2:
            penX = ((1.4f * (30.0f * Cosf_LUT_Wrap(7.0f * counter)) + 320.0f) - 320.0f) / 160.0f;
            penY -= 0.0046666465f;
            if (++counter >= 120) {
                sub = 3;
                counter = 0;
            }
            break;
        case 3:
            alpha += 0.1f;
            if (alpha >= 1.0f) {
                penAlpha = 1.0f;
                alpha = 1.0f;
                sub = 4;
            }
            break;
        case 4:
            penAlpha -= 0.05f;
            penRot += -2.0f;
            penX += 0.01875f;
            if (penAlpha <= 0.0f) {
                penAlpha = 0.0f;
                state = 4;
                counter = 0;
            }
            break;
        }
        break;
    case 4:
        if (++counter == 600) {
            state = 5;
        }
        break;
    case 5:
        break;
    case 6:
        alpha -= 0.01f;
        if (alpha <= 0.0f) {
            alpha = 0.0f;
            state = 7;
        }
        break;
    case 7:
        state = 0;
        mode = -1;
        counter = 0;
        sub = 0;
        glow = 0.0f;
        alpha = 0.0f;
        break;
    }
    if (draw) {
        ResCtrl r;
        if (state == 2) {
            fn_80121E10(&r);
            r.resId = 0xC6C;
            r.Show(x + kGlowOffset[0], y + kGlowOffset[1], 1.0f);
            r.SetScale(0.4f * glow + 0.8f);
            r.SetColor((unsigned int)(255.0f * glow) | 0xFFFFFF00);
            fn_8011FAFC(&r, 4);
        }
        if (state == 3) {
            Mtx m, s;
            PSMTXIdentity(m);
            PSMTXIdentity(s);
            RotMtx(m, 0.0f, 0.0f, penRot);
            Vec3 v = sPenOrigin;
            v.x = penX;
            v.y = penY;
            PSMTXMultVec(*CObj_GetProjMatrix_Cached(GetCourseScene3D()), &v, &v);
            s[0][3] = v.x;
            s[1][3] = v.y;
            s[2][3] = v.z;
            s[2][2] = 0.05f;
            s[1][1] = 0.05f;
            s[0][0] = 0.05f;
            PSMTXConcat(s, m, m);
            Object_SetAnimBinding(model, m, 0);
            Object_SetColorAlphaOnly(model, 0, penAlpha);
            Object_DriveAnimMatrix(model);
            Object_RenderJObjTree(model, 7);
        }
        float px2 = x;
        float py2 = y;
        fn_80121E10(&r);
        r.resId = kModeRes[mode];
        r.Show(px2, py2, 1.0f);
        r.SetScale(scale);
        r.SetColor((unsigned int)(255.0f * alpha) | 0xFFFFFF00);
        fn_8011FAFC(&r, prio);
    }
}

void clFaceEffect::Dummy() {}

void clFaceEffect::Update(unsigned char draw) {
    KartRender *k = kart;
    float px = scale * kIconOffset[k->chara].x + x;
    float py = scale * kIconOffset[k->chara].y + y;
    if (k->special == 1) {
        UpdateSpecial(draw, px, py);
    } else {
        UpdateSprites(draw, px, py);
        UpdateIcon(draw, px, py);
    }
    if (animOn == 1) {
        Sprite_AdvanceAnim(sprL, 0.0165f);
        Sprite_AdvanceAnim(sprR, 0.0165f);
        fn_801A0004(sprL);
        fn_801A0004(sprR);
    }
}

void clFaceEffect::UpdateIcon(unsigned char draw, float px, float py) {
    KartStatus *st = kart->status;
    int prev = mode;
    if (TestBits(st, 0x10000) == 1) {
        mode = -1;
        prev = -1;
        timer = 0;
    }
    if (TestBits(st, 0x800000000ULL)) {
        mode = 0;
    } else if (st->bits & 0x1000000000ULL) {
        mode = 4;
    } else if (st->bits & 0x4000000000000ULL) {
        mode = 5;
    } else if (st->bits & 0x8000000000000ULL) {
        mode = 6;
    } else if (st->bits & 0x200ULL) {
        mode = 2;
    } else if (st->bits & 0x80000000000ULL) {
        mode = 3;
    } else if (st->bits & 0x10000000000000ULL) {
        int n = fn_8023D1B4(kart);
        if (n < 0) {
            mode = 7;
        } else {
            mode = n + 7;
        }
    } else {
        mode = -1;
    }
    if (mode != -1) {
        if (prev != mode) {
            timer = 600;
        } else if (TestBits(st, 0x10000) == 1) {
            timer = 600;
        }
        resId = kModeRes[mode];
    }
    if (timer != 0) {
        timer--;
    }
    if (timer != 0 && draw && animOn != 1) {
        ResCtrl r;
        fn_80121E10(&r);
        r.resId = resId;
        r.Show(px, py, 1.0f);
        r.SetScale(scale);
        fn_8011FAFC(&r, prio);
    }
}

clFaceEffect::~clFaceEffect() {
    fn_80120A08(0x540);
    fn_80120A08(0xC2F);
    fn_80120A08(0xC30);
    fn_80120A08(0xC31);
    if (model) {
        delete model;
        model = 0;
    }
    if (sprL) {
        delete sprL;
        sprL = 0;
    }
    if (sprR) {
        delete sprR;
        sprR = 0;
    }
}

clFaceEffect::clFaceEffect(KartRender *k, int p) {
    kart = k;
    prio = p;
    x = 0.0f;
    y = 0.0f;
    scale = 1.0f;
    animOn = 0;
    mode = -1;
    timer = 0;
    resId = -1;
    state = 0;
    counter = 0;
    glow = 0.0f;
    glowSpeed = 0.0f;
    i40 = 0;
    model = 0;
    alpha = 0.0f;
    PreloadResource(0xC2F);
    PreloadResource(0xC30);
    PreloadResource(0xC31);
    PreloadResource(0xC6C);
    model = new clNormal3D(kPencilRes, 0);
    Object_JObjUpdate_870(model, 0x200);
    Object_SetJObjScaleXYZ(model, 0.05f, 0.05f, 0.05f);
    sprL = new Sprite(100, 0, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f);
    sprR = new Sprite(100, 0, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 1.0f);
    sprL->prio = prio;
    sprR->prio = prio;
}

static inline unsigned char IsSlotActive(int slot) {
    unsigned char r;
    if (slot < 0 || slot > 3) {
        r = 0;
    } else if (!((PcbSlot *)PcbSlot_GetByIndex(slot))->active) {
        r = 0;
    } else {
        r = 1;
    }
    return r;
}

unsigned char FaceEffect_IsSlotActive(int slot) {
    if (slot < 0 || slot > 3) {
        return 0;
    }
    return ((PcbSlot *)PcbSlot_GetByIndex(slot))->active != 0;
}

static inline int ClampSlot(int slot) {
    if ((slot < 0 || slot > 3) && slot != 6) {
        slot = 0;
    }
    return slot;
}

static inline int EmblemResOf(int slot) {
    slot = ClampSlot(slot);
    if (slot == 6) {
        return -1;
    }
    return kEmblemRes[slot];
}

static inline int NameResOf(int chara, int slot, unsigned char useSlot) {
    if ((slot < 0 || slot > 3) && slot != 6) {
        slot = 0;
    }
    if (chara <= -1 || chara >= 13) {
        chara = 0;
    }
    if (slot >= 0 && slot <= 3) {
        int res = kNameRes[chara];
        int tier;
        if (useSlot == 1) {
            tier = ((PcbSlot *)PcbSlot_GetByIndex(slot))->tier;
        } else {
            tier = g_consecutiveWinsTier;
        }
        if (tier > 0) {
            res = sEmblems[tier - 1].id;
        }
        return res;
    }
    if (g_cupId == 14) {
        if (g_roundIndex < 4) {
            chara = 13;
        } else {
            chara = 14;
        }
    }
    return kCpuNameRes[chara];
}

int FaceEffect_GetSlotRes(int *flag, int *name, int *emblem, int slot, int chara) {
    if (IsSlotActive(slot) == 1) {
        *flag = kFlagRes[slot];
        *name = NameResOf(chara, slot, 1);
        *emblem = EmblemResOf(slot);
        return 1;
    }
    *emblem = -1;
    *name = -1;
    *flag = -1;
    return 0;
}

int FaceEffect_GetRes(int *flag, int *name, int *emblem, int slot, int chara, unsigned char useSlot) {
    unsigned char ok;
    if (useSlot == 1) {
        if (!GetVBlankFlag()) {
            ok = 0;
        } else if (VBlankValue_Get() == 1) {
            ok = 0;
        } else if (!g_namCamFlag) {
            ok = 0;
        } else {
            ok = 1;
        }
    } else if (!GetVBlankFlag()) {
        ok = 0;
    } else if (VBlankValue_Get() == 1) {
        ok = 0;
    } else if (!g_playerData.b19D) {
        ok = 0;
    } else if (!g_namCamFlag) {
        ok = 0;
    } else {
        ok = 1;
    }
    if (ok == 1 && slot != 6) {
        *flag = kFlagRes[slot];
        *name = NameResOf(chara, slot, useSlot);
        *emblem = EmblemResOf(slot);
        return 1;
    }
    *emblem = -1;
    *name = -1;
    *flag = -1;
    return 0;
}

short FaceEffect_GetEmblemId(int idx) {
    if (idx < 0 || (unsigned int)idx >= 10) {
        return -1;
    }
    return sEmblems[idx].id;
}

static inline unsigned char IsEmblemId(int id) {
    unsigned char r;
    if (id >= 0xC3F && id <= 0xC48) {
        r = 1;
    } else {
        r = 0;
    }
    return r;
}

int FaceEffect_EmblemIndex(int id) {
    if (IsEmblemId(id) == 0) {
        return -1;
    }
    EmblemRes *e = sEmblems;
    for (int i = 0; i < 10; i++, e++) {
        if (id == e->id) {
            return i;
        }
    }
    return 0;
}

unsigned char FaceEffect_IsEmblemId(int id) {
    if (id >= 0xC3F && id <= 0xC48) {
        return 1;
    }
    return 0;
}

int FaceEffect_GetEmblemRes(int slot) {
    return EmblemResOf(slot);
}

int FaceEffect_GetNameRes(int slot, int chara, unsigned char useSlot) {
    int res;
    if ((slot < 0 || slot > 3) && slot != 6) {
        slot = 0;
    }
    if (chara <= -1 || chara >= 13) {
        chara = 0;
    }
    if (slot >= 0 && slot <= 3) {
        res = kNameRes[chara];
        int tier;
        if (useSlot == 1) {
            tier = ((PcbSlot *)PcbSlot_GetByIndex(slot))->tier;
        } else {
            tier = g_consecutiveWinsTier;
        }
        if (tier > 0) {
            res = sEmblems[tier - 1].id;
        }
        return res;
    }
    if (g_cupId == 14) {
        if (g_roundIndex < 4) {
            chara = 13;
        } else {
            chara = 14;
        }
    }
    return kCpuNameRes[chara];
}

void FaceEffect_ShiftRankKeys() {
    sRankKeys[1].value = sRankKeys[2].value;
    sRankKeys[3].value = sRankKeys[4].value;
    sRankKeys[5].value = sRankKeys[6].value;
    sRankKeys[7].value = sRankKeys[8].value;
    sRankKeys[9].value = sRankKeys[10].value;
    sRankKeys[11].value = sRankKeys[12].value;
    sRankKeys[13].value = sRankKeys[14].value;
    sRankKeys[15].value = sRankKeys[16].value;
    sRankKeys[17].value = sRankKeys[18].value;
    sRankKeys[19].value = sRankKeys[20].value;
    sRankKeys[21].value = sRankKeys[22].value;
    sRankKeys[23].value = sRankKeys[24].value;
    sRankKeys[25].value = sRankKeys[26].value;
}

void FaceEffect_Dummy() {}
