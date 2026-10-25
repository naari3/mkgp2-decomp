/*
 * Kart alert panel @ 0x802506F8..0x80250F34 (vtable lbl_804EF130).
 *
 * Watches the kart slots for a kart carrying the 0x8000 state flag and
 * shows its driver's name (or character name) with two sprites; OnItem
 * keeps the panel up while the local kart holds items 0x2E..0x31.
 */

#include "game/FlowScene.h"

struct Vec2 {
    float x;
    float y;
};

struct NameBuf {
    int w[3];
};

struct PcbSlot {
    unsigned char b0_0 : 1;
    unsigned char role : 3;
    unsigned char b0_4 : 4;
    char pad01[2];
    unsigned char hasName : 1;
    unsigned char b3_1 : 7;
    char pad04[0x12];
    unsigned short name[6];
};

struct KartState {
    char pad00[0x10];
    unsigned long long flags;
};

struct Kart {
    char pad000[0x1F4];
    int slot;
    int chr;
    char pad1FC[0x304 - 0x1FC];
    KartState *state;
};

extern "C" {
extern const Vec2 lbl_806DC0E0;
extern const float lbl_806DC0E8;
extern const float lbl_806DC0EC;
extern const float lbl_806DC0F0;
extern const char lbl_806DC0F4[4];
extern const char lbl_803F0AD8[];
extern const Vec2 lbl_803F0FC4[3];
extern const char lbl_803F1020[];
extern const char lbl_803F1034[];
extern const char *lbl_804EF0C8[];
extern const char *lbl_804EF0FC[];
extern Kart *g_playerRenderObj;
extern int g_localPcbRole;
Kart *GetKartSlotKartVariant(int slot);
PcbSlot *PcbSlot_GetByIndex(int slot);
unsigned short *wcsncpy(unsigned short *dst, const unsigned short *src, unsigned long n);
int SpriteHandle_CreateDefault(ResCtrl *ctrl, int layer);
void SpriteHandle_Destroy(int sprite);
void SpriteHandle_SetActiveFlag(int sprite, unsigned char active);
void SpriteHandle_RecomputeCull(int sprite);
void SpriteHandle_SetCornerAlpha(int sprite, int alpha);
void SpriteLayer_SetResource(int sprite, int id);
void fn_80121E10(ResCtrl *ctrl);
void fn_8020A734(FlowFader *fader, int frames, float from, float to);
float fn_8020A6CC(FlowFader *fader);
void *fn_801F8E58(void);
void fn_801F8A34(void *a, TextManager *tm, int layer);
void fn_801F9014(TextManager *tm, const unsigned short *text, ...);
void DebugPrintf(const char *fmt, ...);
}

struct SpriteBox {
    int handle;
    SpriteBox(ResCtrl *rc, int layer) { handle = SpriteHandle_CreateDefault(rc, layer); }
    ~SpriteBox() {
        if (handle >= 0) {
            SpriteHandle_Destroy(handle);
            handle = -1;
        }
    }
    void SetResource(int id) {
        if (handle >= 0) {
            SpriteLayer_SetResource(handle, id);
        }
    }
    void SetActive(unsigned char on) {
        if (handle >= 0) {
            SpriteHandle_SetActiveFlag(handle, on);
        }
    }
    void SetAlpha(int a) {
        if (handle >= 0) {
            SpriteHandle_SetCornerAlpha(handle, a);
        }
    }
    void Cull() {
        if (handle >= 0) {
            SpriteHandle_RecomputeCull(handle);
        }
    }
};

/* 0x230-byte text box built by TexMgr_Init; no dtor. */
struct TextBox {
    char body[0x230];
    TextBox();
    ~TextBox() {}
    TextManager *tm() { return (TextManager *)this; }
};

static inline bool HasFlag(Kart *k, unsigned long long mask) {
    return (k->state->flags & mask) != 0;
}

static inline unsigned char TestFlag(Kart *k, unsigned long long mask) {
    unsigned char r;
    if ((k->state->flags & mask) == 0) {
        r = 0;
    } else {
        r = 1;
    }
    return r;
}

struct KartAlertPanel {
    virtual ~KartAlertPanel();
    unsigned char active;
    unsigned char hold;
    unsigned char hidden;
    VHolder<FlowFaderF> fader;
    SpriteBox *sprites[2];
    TextBox *text;
    Kart *kart;
    int timer;
    int item;
    KartAlertPanel();
    void OnItem(int id, Kart *k);
    void Update();
    void Refresh();
    virtual void _key();
};

KartAlertPanel::KartAlertPanel()
    : active(0), hold(0), hidden(1), fader(new FlowFaderF(lbl_806DC0E8)), text(0), kart(0),
      timer(0), item(-1) {
    ResCtrl rc;
    rc.resId = 0x1ECD;
    rc.Show(lbl_806DC0E0.x + lbl_803F0FC4[0].x, lbl_806DC0E0.y + lbl_803F0FC4[0].y, lbl_806DC0EC);
    sprites[0] = new SpriteBox(&rc, 4);
    sprites[0]->SetActive(0);
    fn_80121E10(&rc);
    rc.resId = 0x1ECD;
    rc.Show(lbl_806DC0E0.x + lbl_803F0FC4[1].x, lbl_806DC0E0.y + lbl_803F0FC4[1].y, lbl_806DC0EC);
    sprites[1] = new SpriteBox(&rc, 4);
    sprites[1]->SetActive(0);
    text = new TextBox;
    TexMgr_SetTexture(text->tm(), lbl_806DC0F4);
    fn_801F93EC(text->tm(), lbl_806DC0E0.x + lbl_803F0FC4[2].x, lbl_806DC0E0.y + lbl_803F0FC4[2].y);
}

KartAlertPanel::~KartAlertPanel() {
    for (int i = 0; i < 2; i++) {
        if (sprites[i]) {
            delete sprites[i];
            sprites[i] = 0;
        }
    }
    if (text) {
        delete text;
        text = 0;
    }
}

void KartAlertPanel::OnItem(int id, Kart *k) {
    if (k) {
        Kart *pl = g_playerRenderObj;
        if (pl == k) {
            int old = item;
            item = id;
            if (id == 0x2E || id == 0x2F || id == 0x30 || id == 0x31) {
                if (old != item) {
                    if (timer == 0) {
                        timer = 0x9A;
                    }
                    hold = 1;
                    fn_8020A734(fader.p, 10, lbl_806DC0E8, lbl_806DC0E8);
                    DebugPrintf(lbl_803F1034);
                }
                return;
            }
        }
        if (hold == 1) {
            if (timer == 0) {
                hold = 0;
                kart = 0;
                DebugPrintf(lbl_803F1020);
            }
            if (pl) {
                if (!HasFlag(pl, 0x0800000000000000ULL)) {
                    hold = 0;
                    kart = 0;
                    DebugPrintf(lbl_803F1020);
                }
            }
        }
    }
}

void KartAlertPanel::Update() {
    unsigned char vis = 1;
    Refresh();
    fader.p->Step();
    if (fn_8020A6CC(fader.p) <= lbl_806DC0E8 && fader.p->Done()) {
        active = 0;
        hidden = 1;
    }
    if (hold == 1 || !active) {
        vis = 0;
    }
    if (timer != 0) {
        timer--;
    }
    {
        int alpha = lbl_806DC0F0 * fn_8020A6CC(fader.p);
        int i;
        for (i = 0; i < 2; i++) {
            sprites[i]->SetAlpha(alpha);
            sprites[i]->SetActive(vis);
            sprites[i]->Cull();
        }
        text->tm()->color = 0xFFFFFF00 | (alpha & 0xFF);
        if (vis == 1) {
            fn_801F8A34(fn_801F8E58(), text->tm(), 4);
        }
    }
}

void KartAlertPanel::Refresh() {
    const char *base = lbl_803F0AD8;
    unsigned char found = 0;
    Kart *k;
    int i;
    for (i = 0; i < 6; i++) {
        k = GetKartSlotKartVariant(i);
        if (k && TestFlag(k, 0x800000000000ULL) == 1) {
            found = 1;
            break;
        }
    }
    if (!found) {
        if (!hidden && active == 1) {
            FlowFaderF *f;
            hold = 0;
            hidden = 1;
            kart = 0;
            f = fader.p;
            fn_8020A734(f, 10, fn_8020A6CC(f), lbl_806DC0E8);
            DebugPrintf(base + 0x524);
        }
    } else if (hold != 1 && kart != k) {
        int slot;
        unsigned char local;
        const char *tex;
        NameBuf name;
        kart = k;
        active = 1;
        hold = 0;
        hidden = 0;
        local = 0;
        slot = kart->slot;
        if (slot != 6) {
            int role = PcbSlot_GetByIndex(slot)->role;
            if (role == g_localPcbRole) {
                local = 1;
            }
        }
        {
            int chr = kart->chr;
            tex = isJapanese() == 0 ? lbl_804EF0C8[chr] : lbl_804EF0FC[chr];
        }
        name = *(const NameBuf *)(base + 0x50C);
        if (local) {
            PcbSlot *p = PcbSlot_GetByIndex(slot);
            if (p->hasName) {
                wcsncpy((unsigned short *)&name, p->name, 0xC);
            }
        }
        sprites[0]->SetResource(0x14AB);
        if (local == 1) {
            sprites[1]->SetResource(0x14AC + slot);
        } else {
            sprites[1]->SetResource(0x1ECD);
        }
        if (*(unsigned short *)&name != 0xFFFF) {
            fn_801F9014(text->tm(), (unsigned short *)&name);
        } else {
            TexMgr_SetTexture(text->tm(), tex);
        }
        fn_8020A734(fader.p, 10, lbl_806DC0E8, lbl_806DC0EC);
        DebugPrintf(base + 0x534);
    }
}
