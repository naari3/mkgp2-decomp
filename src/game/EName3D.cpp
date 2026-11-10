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

#include "game/ItemEffectBusPrivate.h"

struct ItemEffectBus;

/* Merged from 14 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct KartRender KartRender;
struct KartRender {
    /* 0x000 */ unsigned char pad_000[0x1F4];
    /* 0x1F4 */ int slot;
    /* 0x1F8 */ int chara;
    /* 0x1FC */ unsigned char pad_1FC[0x3C];
    /* 0x238 */ int visible;
    /* 0x23C */ unsigned char middle[0x90];
    /* 0x2CC */ int coins;
    /* 0x2D0 */ unsigned char special;  /* also: active */
    /* 0x2D1 */ unsigned char pad_2D1[0x33];
    /* 0x304 */ struct ItemEffectBus *status;
};

#include "game/types/PcbSlot.h"

struct TexMgr {
    char pad[0x230];
    TexMgr();
};

extern const char lbl_806DB680[8];
extern const char lbl_806DB688[8];
extern const char lbl_806DB690[8];
extern const char lbl_806DB698[8];
extern const char lbl_806DB6A0[8];
extern const char lbl_806DB6A8[8];
extern const char lbl_806DB6B0[8];

static const char *kNamesJ[13] = {
    lbl_806DB680, "ルイージ", lbl_806DB688, lbl_806DB690, lbl_806DB698, "キノピオ", "ドンキー",
    "ヨッシー", "パックマン", "ミズパック", "アカベイ", "ワルイージ", "まめっち",
};

static const char *kNamesE[13] = {
    "ＭＡＲＩＯ", "ＬＵＩＧＩ", "ＷＡＲＩＯ", "ＰＥＡＣＨ", "ＫＩＮＧ", "ＴＯＡＤ", lbl_806DB6A0,
    "ＹＯＳＨＩ", lbl_806DB6A8, "Ｍｓ．Ｐ", lbl_806DB6B0, "ＷＡＬＵ", "ＭＡＭＥ",
};

static const float kOffsetX[4] = {7.0f, 0.0f, 14.0f, 0.0f};

#include "game/types/Vec3c.h"

class clEName3D {
public:
    virtual ~clEName3D();
    KartRender *kart;
    Vec3c pos;
    float scale;
    int prio;
    int big;
    TexMgr *tex;
    void *list;

    clEName3D(KartRender *k, int p);
    void Draw();
    void SetPos(const float *pos);
};

clEName3D::clEName3D(KartRender *k, int p) {
    kart = k;
    pos.x = 0.0f;
    pos.y = 0.0f;
    pos.z = 0.0f;
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

clEName3D::~clEName3D() {
    if (tex) {
        delete tex;
    }
    fn_801F8E54();
}

void clEName3D::SetPos(const float *v) {
    pos.x = v[0];
    pos.y = v[1];
    pos.z = v[2];
}

void clEName3D::Draw() {
    unsigned char hidden;
    float s = 1.5300002f * scale;
    if ((kart->status->mask & 0x8000000000ULL) == 0) {
        hidden = 0;
    } else {
        hidden = 1;
    }
    if (hidden != 1 && !(scale < 0.5f)) {
        float px = s * kOffsetX[big * 2] + pos.x;
        s *= 0.875f;
        fn_801F93DC(tex, px, pos.y, pos.z);
        fn_801F93D0(tex, s, s);
        fn_801F8A34(list, tex, prio);
    }
}
