/*
 * 0x802300CC..0x80230400: clEName3D, the driver name plate shown with a
 * rival's face icon. Owns .rodata 0x803DAE88..0x803DAF98 and the name table
 * plus vtable in .data 0x804EE1C8..0x804EE23C.
 */

void *operator new(unsigned long size);
void operator delete(void *p) throw();

extern "C" {
int isJapanese(void);
void *PcbSlot_GetByIndex(int slot);
void *wcsncpy(unsigned short *dst, const unsigned short *src, unsigned long n);
void TexMgr_SetTexture(void *tex, const char *name, ...);
void fn_801F9014(void *tex, const unsigned short *name, ...);
void fn_801F8FCC(void *tex, int on);
void fn_801F8FF0(void *tex, int on);
void fn_801F8E90(void *tex);
void TexMgr_Apply(void *tex);
void *fn_801F8E58(void);
void fn_801F8E54(void);
void fn_801F93DC(void *tex, float x, float y, float z);
void fn_801F93D0(void *tex, float sx, float sy);
void fn_801F8A34(void *list, void *tex, int prio);
extern int g_gameMode;
extern int g_localPcbRole;
}

struct KartStatus {
    char pad0[0x10];
    unsigned long long bits;
};

struct KartRender {
    char pad0[0x1F4];
    int slot;
    int chara;
    char pad1FC[0x304 - 0x1FC];
    KartStatus *status;
};

struct PcbSlot {
    unsigned char b0;
    unsigned char b1;
    unsigned char b2;
    unsigned char b3;
    char pad4[0x16 - 4];
    unsigned short name[6];
};

struct TexMgr {
    char pad[0x230];
    TexMgr();
};

static const float kOffsetX[4] = {7.0f, 0.0f, 14.0f, 0.0f};

static const char *kNamesJ[13] = {
    "マリオ", "ルイージ", "ワリオ", "ピーチ", "クッパ", "キノピオ", "ドンキー",
    "ヨッシー", "パックマン", "ミズパック", "アカベイ", "ワルイージ", "まめっち",
};

static const char *kNamesE[13] = {
    "ＭＡＲＩＯ", "ＬＵＩＧＩ", "ＷＡＲＩＯ", "ＰＥＡＣＨ", "ＫＩＮＧ", "ＴＯＡＤ", "ＤＫ",
    "ＹＯＳＨＩ", "ＰＡＣ", "Ｍｓ．Ｐ", "ＲＥＤ", "ＷＡＬＵ", "ＭＡＭＥ",
};

class clEName3D {
public:
    virtual ~clEName3D();
    KartRender *kart;
    float x, y, z;
    float scale;
    int prio;
    int big;
    TexMgr *tex;
    void *list;

    clEName3D(KartRender *k, int p);
    void Draw();
    void SetPos(const float *pos);
};

void clEName3D::Draw() {
    unsigned char hidden;
    float s = 1.5300002f * scale;
    if ((kart->status->bits & 0x8000000000ULL) == 0) {
        hidden = 0;
    } else {
        hidden = 1;
    }
    if (hidden != 1 && !(scale < 0.5f)) {
        float px = s * kOffsetX[big * 2] + x;
        s *= 0.875f;
        fn_801F93DC(tex, px, y, z);
        fn_801F93D0(tex, s, s);
        fn_801F8A34(list, tex, prio);
    }
}

void clEName3D::SetPos(const float *pos) {
    x = pos[0];
    y = pos[1];
    z = pos[2];
}

clEName3D::~clEName3D() {
    if (tex) {
        delete tex;
    }
    fn_801F8E54();
}

clEName3D::clEName3D(KartRender *k, int p) {
    kart = k;
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    scale = 1.0f;
    prio = p;
    big = 0;
    tex = new TexMgr();
    list = fn_801F8E58();
    int chara = k->chara;
    const char *name;
    if (isJapanese() == 0) {
        name = kNamesJ[chara];
    } else {
        name = kNamesE[chara];
    }
    unsigned short wname[6] = {0xFFFF};
    if (k->slot != 6) {
        PcbSlot *s = (PcbSlot *)PcbSlot_GetByIndex(k->slot);
        if (((s->b0 >> 4) & 7) == g_localPcbRole && ((s->b3 >> 7) & 1)) {
            wcsncpy(wname, s->name, 12);
        }
    }
    if (wname[0] == 0xFFFF) {
        TexMgr_SetTexture(tex, name);
    } else {
        fn_801F9014(tex, wname);
    }
    if (g_gameMode == 2) {
        big = 1;
    }
    if (big == 1) {
        fn_801F8FCC(tex, 0);
    } else {
        fn_801F8FCC(tex, 1);
    }
    fn_801F8FCC(tex, 1);
    fn_801F8FF0(tex, 1);
    fn_801F8E90(tex);
    TexMgr_Apply(tex);
}
