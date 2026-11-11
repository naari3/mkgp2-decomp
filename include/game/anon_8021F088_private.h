/* Private coin-mileage views shared only by the split anon_8021F088 TUs.
 * The two switches preserve the original inline visibility at each cut. */
/*
 * 0x8021F088..0x80224ECC: csSceneCoinMilage.cpp, clCSSceneCoinMilage
 * (vtable clCSSceneCoinMilage_vtable_804EDE44, base clSceneInterface lbl_803FE0C8).
 *
 * After a race the scene rains coins, adds up the coins earned this game
 * into the coin mileage, then walks through every item the new mileage
 * unlocks and finally shows how many coins are left to the next one.
 *
 * The menu nodes it draws (nsMenuUtil::clMenuNode, vtable lbl_8048EF34):
 * clGetCoinLine / clGetSumLine (one line of the coin breakdown),
 * clCoinPerfect (the "perfect" bonus) and clGetCoinSum (the mileage total).
 */

#include "game/types/size_t.h"
void *operator new(size_t size);
void operator delete(void *p) throw();

#include "game/types/InputState.h"

/* Layout copies only real fields; opt in without changing older TUs. */
struct ResCtrl {
    int resId;
    int field4, mode, fieldc;
    unsigned char flag;
#ifndef COIN_RESCTRL_IMPLICIT_PADDING
    unsigned char pad11[3];
#endif
    float x, y, z, width, height, field28, scaleX, scaleY;
    unsigned int colors[4];
    bool flipX;
    bool flipY;
#ifndef COIN_RESCTRL_IMPLICIT_PADDING
    char pad46[2];
#endif
#ifdef COIN_RESCTRL_IMPLICIT_PADDING
    int tail0, tail1, tail2, tail3;
#else
    int tail[4];
#endif
    ResCtrl();
    ~ResCtrl() {}
    void Show(float px, float py, float pz) {
        flag = 1;
        x = px;
        y = py;
        z = pz;
    }
    void SetColor(unsigned int c) {
        colors[0] = c;
        colors[1] = c;
        colors[2] = c;
        colors[3] = c;
    }
};

/* 0x30-byte animated sprite (dtor Sprite_Destroy). */
struct Sprite {
    int x0;
    int layer;
    int x8;
    float x;
    float y;
    float sx;
    float sy;
    char pad1C[4];
    float alpha;
    char pad24[0x30 - 0x24];
    Sprite(int res, int a, int b);
    ~Sprite();
    void SetAnimParam(int key, short value);
    void SetPos(float px, float py) { x = px; y = py; }
};

template <class T> struct Own {
    T *p;
    Own(T *q) : p(q) {}
    ~Own() throw() { delete p; }
};

template <class T> struct PtrVecData {
    int cap;
    int count;
    T *data;
    PtrVecData() : cap(0), count(0), data(0) {}
    ~PtrVecData() {
        if (data) {
            operator delete(data);
        }
    }
};

template <class T> struct PtrVecBase : PtrVecData<T> {
    PtrVecBase() {}
    ~PtrVecBase() {}
};

extern "C" {
void PtrVec_InsertFill(void *v, void *pos, int n, const void *val);
void **fn_80146000(void *vec, int index);
}

template <class T> struct PtrVec : PtrVecBase<T> {
    PtrVec() {}
    ~PtrVec() {}
    T *begin() { return this->data; }
    T *end() { return this->data + this->count; }
    void push_back(const T &v) { PtrVec_InsertFill(this, end(), 1, &v); }
    T &at(int i) { return *(T *)fn_80146000(this, i); }
};

/* 0x230-byte text sprite (ctor TexMgr_Init). */
struct TextSprite {
    char pad000[0x18];
    int visible;
    char pad01C[4];
    unsigned int color;
    char pad024[0x22C - 0x24];
    float spacing;
    TextSprite();
    ~TextSprite() {}
};

/* 0x230-byte text manager (ctor fn_80149214, dtor dtor_800869D0). */
struct TextManager {
    char pad000[0x18];
    int visible;
    char pad01C[0x22C - 0x1C];
    float spacing;
    TextManager();
    ~TextManager();
};

/* 0x20-byte 3D model (ctor fn_8013D800). */
struct Model {
    virtual ~Model();
    virtual void Draw();
    char pad04[0x1C];
    Model(const void *res, int flag);
};

/* 0x64-byte item model group (ctor fn_8021ABFC). */
struct ItemModel {
    virtual ~ItemModel();
    char pad04[0x60];
    ItemModel(int id, int a, int b, int c);
};

struct KartPose {
    float pos[3];
    float rot[3];
    float scale;
};

struct ItemPose {
    float x, y;
    float rot[3];
    float scale;
};

/* One unlockable item of the coin mileage table. */
struct MilageItem {
    int coins;
    int type;
    int id;
};

struct Int5 {
    int v[5];
};

struct ItemDisplay {
    int x0;
    int state;
    int mode;
};

extern "C" {
extern InputState *g_pInputState;
extern int g_gameMode;
extern int g_cupId;
extern int g_characterId;
extern char g_playerData[];
extern void *lbl_806D1A60;
extern const float CoinResultScene_Init_rodata_803C6A18[3];
extern const float lbl_803C6A24[];
#if defined(__MWERKS__) || !defined(ANON_8021F088_POOL_OWNER)
/* views of objects that anon_8021F088_nm_8021F508.cpp defines as int[5], int[16] and float[12] */
extern const Int5 lbl_803C6B70;
extern const char lbl_803C6B84[0x40];
extern const float lbl_803C6BD4[3][4];
#endif
extern const int lbl_803C6BC4[4];
extern const char lbl_803C6C2C[];
extern const char lbl_803C6C58[];
extern const char lbl_803C6C70[];
extern const char lbl_803C6CBC[];
extern const char CoinResultScene_Init_rodata_803C6CD0[];
extern const float lbl_806DB190;
extern const float lbl_806DB194;
extern const float lbl_806DB198;
extern const float lbl_806DB19C;
extern const float lbl_806DB1A0;
extern const float lbl_806DB1A4;
extern const float lbl_806DB1A8;
extern const float lbl_806DB1AC;
extern const float lbl_806DB1B0;
extern const float lbl_806DB1B4;
extern const float lbl_806DB1B8;
extern const float lbl_806DB1BC;
extern const float lbl_806DB1C0;
extern const float lbl_806DB1C4;
extern const float lbl_806DB1C8;
extern const float lbl_806DB1CC;
extern const float lbl_806DB1D0;
extern const float lbl_806DB1D4;
extern const float lbl_806DB1D8;
extern const float lbl_806DB1DC;
extern const float lbl_806DB1E0;
extern const float lbl_806DB1E4;
extern const float lbl_806DB1E8;
extern const float lbl_806DB1EC;
extern const float lbl_806DB1F0;
extern const float lbl_806DB1F4;
extern const float lbl_806DB1F8;
extern const float lbl_806DB1FC;
extern const float lbl_806DB200;
extern const float lbl_806DB204;
extern const float lbl_806DB208;
extern const float lbl_806DB20C;
extern const char lbl_806DB210[4];
extern const float lbl_806DB214;
extern const float lbl_806DB218;
extern const float lbl_806DB21C;
extern const char lbl_806DB220[4];
extern const float lbl_806DB224;
extern const float lbl_806DB228;
extern const float lbl_806DB22C;
extern const float lbl_806DB230;
extern const float lbl_806DB234;
extern const float lbl_806DB238;
extern const float lbl_806DB23C;
extern const float lbl_806DB240;
extern const float lbl_806DB244;
extern const float lbl_806DB248;
extern const float lbl_806DB24C;
extern const float lbl_806DB250;
extern const float lbl_806DB254;
extern const float lbl_806DB258;
extern const float lbl_806DB25C;
extern const float lbl_806DB260;
extern const float lbl_806DB264;
extern const float lbl_806DB270;
extern const float lbl_806DB274;
extern const float lbl_806DB278;
extern const float lbl_806DB27C;
extern const float lbl_806DB280;
extern const float lbl_806DB284;
extern const float lbl_806DB288;
extern const float lbl_806DB28C;
extern const float lbl_806DB290;
extern const float lbl_806DB294;
extern const float lbl_806DB298;
extern const float lbl_806DB29C;
extern const char lbl_806DB2A0[8];
extern const float lbl_806DB2A8;
extern const float lbl_806DB2AC;
extern const float lbl_806DB2B0;
extern const float lbl_806DB2B4;
extern const float lbl_806DB2B8;
extern const float lbl_806DB2BC;
extern const float lbl_806DB2C0;
extern const float lbl_806DB2C4;
extern const float lbl_806DB2C8;
extern const float lbl_806DB2CC;
extern const float lbl_806DB2D0;
extern const float lbl_806DB2D4;
extern const float lbl_806DB2D8;
extern const float lbl_806DB2DC;
extern const float lbl_806DB2E0;
extern const float lbl_806DB2E4;
extern const float lbl_806DB2E8;
extern const float lbl_806DB2EC;
extern const float lbl_806DB2F0;
extern const float lbl_806DB2F4;
extern const float lbl_806DB2F8;
extern const float lbl_806DB2FC;
extern const float lbl_806DB300;
extern const float lbl_806DB304;
extern const float lbl_806DB308;
extern const float lbl_806DB30C;
extern const float lbl_806DB310;
extern const float lbl_806DB314;
extern const float lbl_806DB318;
extern const float lbl_806DB31C;
int isJapanese(void);
int rand(void);
double cos(double x);
int sprintf(char *buf, const char *fmt, ...);
char *strcpy(char *dst, const char *src);
void DebugPrintf(const char *fmt, ...);
void fn_8011F994(int a);
void fn_8011FAB8(void);
void fn_8011FAFC(ResCtrl *r, int layer);
void fn_80121E10(ResCtrl *r);
KartPose *fn_8013BE98(void);
void fn_8013BEC8(int id);
const char *fn_8013C26C(int id, int lang);
void fn_8013D4B0(Model *m, float a);
void fn_8013D59C(Model *m, float x, float y, float z);
void fn_8013D608(Model *m, float x, float y, float z);
void fn_8013D634(Model *m, float x, float y, float z);
void fn_8013D660(Model *m, float x, float y);
void fn_8013D738(Model *m, float a, float b);
void fn_8013DAC8(Model *m, int layer);
void fn_8013DBF8(void);
void fn_801699D8(int a, int b);
void fn_80169C44(void);
void fn_80192688(int id, int a);
unsigned char fn_8019FE78(Sprite *s);
void fn_8019FF8C(Sprite *s, int key, float *out);
void fn_801A0004(Sprite *s);
void fn_801A0500(Sprite *s);
void fn_801A1280(void);
void Sprite_AdvanceAnim(Sprite *s, float step);
void Sprite_SetupAnim(Sprite *s, int a, int b, int c);
void Sprite_SetAnimTime(Sprite *s, float t);
void *fn_801F8E58(void);
void fn_801F8A34(void *mgr, void *t, int layer);
void fn_801F8E90(void *t);
void fn_801F8FCC(void *t, int mode);
void fn_801F93D0(void *t, float sx, float sy);
void fn_801F93EC(void *t, float x, float y);
void TexMgr_SetTexture(void *t, const char *s, ...);
void TexMgr_Apply(void *t);
const char *GetTextureByIdAndLang(int id, int lang);
ItemDisplay *ItemDisplay_GetOrCreate(void);
void ItemDisplay_Start(ItemDisplay *d, int id);
void ItemDisplay_Stop(ItemDisplay *d);
void ItemDisplay_Destroy(void);
void fn_8020F38C(int a);
void fn_8020F3F0(void);
int fn_80209338(int chara);
int fn_802161CC(void);
int fn_802161D4(void);
int fn_802161DC(void);
int fn_802161EC(void);
int fn_802161F4(void);
int fn_802161FC(void);
int fn_8021620C(void);
void fn_8021651C(void *pd);
short fn_80216908(int a);
const char *fn_8021691C(int id);
int fn_80216960(int id);
int fn_80216974(int id);
int fn_80216988(int coins);
MilageItem *fn_802169F4(int index);
void fn_8021A0B0(void *fx);
void fn_8021A430(ItemModel *m, float a);
void fn_8021A4B8(ItemModel *m, float r, float g, float b, float a);
void fn_8021A578(ItemModel *m, float x, float y, float z);
void fn_8021A660(ItemModel *m, float x, float y, float z);
void fn_8021A7BC(ItemModel *m, float x, float y);
int fn_8023D710(int id);
const char *fn_8023D938(int id, int idx);
const char *fn_8023DAA8(int id);
const void *ItemRes_LookupByKey_Thunk(int id);
int Item_GetDescriptorField8(int id);
int Item_GetDescriptorFieldC(int id);
short Item_GetDescriptorField0(int id, int a);
void SoundMgr_Play(int id);
void SetSyncTarget(int id);
unsigned char IsSyncReached(void);
void SetRumbleMode(int a, int b, int c);
void RumbleUpdate(void);
void InitRumbleController(int a);
unsigned char IsCardValid(void);
void AddCoinsFromExtraStage(void);
void CalcEarnedCoins(void);
int GetEarnedCoins(void);
int GetCoinCount(void);
int GetCoinMilage(void *pd);
void AddCoinMilage(void *pd, int coins);
}

static inline const ItemPose *ItemPoses() {
    return (const ItemPose *)(lbl_803C6A24 + 5);
}

static inline InputState *GetInput() {
    return g_pInputState == 0 ? (InputState *)0 : g_pInputState;
}

static inline void SetInput(unsigned char en) {
    InputState *in = GetInput();
    in->enabled = en;
    in->held = 0;
    in->edge = 0;
}

static inline unsigned int PackColor(int r, int g, int b, int a) {
    return ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | (a & 0xFF);
}

struct FadeTrack {
    unsigned char active;
    float from;
    float to;
    float speed;
    float t;
    float value;
    FadeTrack() : speed(lbl_806DB190), t(lbl_806DB190) {}
    void Set(float f, float e, float s) {
        from = f;
        to = e;
        speed = s;
        t = lbl_806DB190;
        value = f;
        active = 1;
    }
    void Step() {
        if (active == 1) {
            value = from * (lbl_806DB194 - t) + to * t;
            t += speed;
            if (t > lbl_806DB194) {
                t = lbl_806DB194;
            }
        }
    }
};

/* nsMenuUtil::clMenuNode */
struct FadeObj {
    virtual ~FadeObj() { delete sprite; }
    virtual void Update();
    virtual void Draw();
    Sprite *sprite;
    int delay;
    FadeTrack tracks[5];
    unsigned char shown;
    unsigned char flush;
    unsigned char pad86[2]; /* tail padding, named so a derived class cannot use it */
    FadeObj() : sprite(0), delay(0) {
        shown = 0;
        flush = 0;
        tracks[0].active = 0;
        tracks[1].active = 0;
        tracks[2].active = 0;
        tracks[3].active = 0;
        tracks[4].active = 0;
    }
    void Tick() {
        if (delay > 0) {
            delay--;
        } else {
            if (delay <= 0) {
                shown = 1;
            }
            for (int i = 0; i < 5; i++) {
                tracks[i].Step();
            }
            Update();
            if (sprite != 0) {
                if (tracks[0].active == 1) {
                    sprite->alpha = tracks[0].value;
                }
                if (tracks[1].active == 1) {
                    sprite->sx = tracks[1].value;
                }
                if (tracks[2].active == 1) {
                    sprite->sy = tracks[2].value;
                }
                if (tracks[3].active == 1) {
                    sprite->x = tracks[3].value;
                }
                if (tracks[4].active == 1) {
                    sprite->y = tracks[4].value;
                }
                Sprite_AdvanceAnim(sprite, lbl_806DB280);
            }
        }
    }
    void Render() {
        if (shown) {
            if (sprite != 0) {
                fn_801A0004(sprite);
            }
            Draw();
            if (flush == 1) {
                fn_8011FAB8();
            }
        }
    }
};

/* nsMenuUtil::clFilterNode: a full screen colour fill (vtable lbl_8049B1AC). */
struct FilterNode : FadeObj {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    int layer;
    FilterNode() {
        r = 0;
        g = 0;
        b = 0;
        layer = 7;
    }
    ~FilterNode();
    void Draw();
};

/* clGetCoinLine (0x4E8): one line of the coin breakdown. */
struct clGetCoinLine : FadeObj {
    int value;
    int add;
    Model *model;
    float rot;
    Own<Sprite> spr;
    ResCtrl digits[3];
    ResCtrl glow[3];
    TextSprite text;
    int timer;
    int flashTimer;
    unsigned char flash;
    unsigned char pad4E5[3]; /* tail padding, named so a derived class cannot use it */
    clGetCoinLine(const char *label, int n, float y, Model *m);
#ifdef COIN_LINE_EXTERNAL_VTABLE
    virtual void _key();
#endif
#ifdef COIN_LINE_DTOR_INLINE
    ~clGetCoinLine() {}
#else
    ~clGetCoinLine();
#endif
    void Layout(float y);
    void Update();
#ifdef COIN_LINE_DRAW_OUTLINE
    void Draw();
#else
    void Draw() {
        float x = tracks[3].value;
        float y = tracks[4].value;
        spr.p->SetPos(x, y);
        fn_801A0004(spr.p);
        fn_8011F994(1);
        if (model != 0) {
            fn_8013D660(model, x - lbl_806DB2E0, lbl_806DB2E4 + y);
            fn_8013D634(model, lbl_806DB190, lbl_806DB190, lbl_806DB248);
            fn_8013D59C(model, lbl_806DB190, lbl_806DB1D8 * rot, lbl_806DB190);
            fn_8013D608(model, lbl_806DB2E8, lbl_806DB2E8, lbl_806DB2E8);
            model->Draw();
        }
        Layout(y);
        for (int i = 0; i < 3; i++) {
            fn_8011FAFC(&digits[i], 1);
        }
        if (flash) {
            for (int i = 0; i < 3; i++) {
                fn_8011FAFC(&glow[i], 1);
            }
        }
        void *mgr = fn_801F8E58();
        fn_801F93EC(&text, x - lbl_806DB2EC, y - lbl_806DB2F0);
        fn_801F8A34(mgr, &text, 1);
    }
#endif
    void Bump(int n) {
        add = n;
        flash = 1;
        flashTimer = 0;
    }
};

/* clGetSumLine (0x548): the total line. */
struct clGetSumLine : clGetCoinLine {
#ifdef COIN_EXTERNAL_VTABLE_KEY
    /* An undefined first key keeps the original externally owned vtable. */
    virtual void ExternalVtableKey();
#endif
    ~clGetSumLine();
    unsigned char perfect;
    ResCtrl label;
    Own<Sprite> bar;
    clGetSumLine(int n, unsigned char p, float y);
    void Draw();
};

/* clCoinPerfect (0x3C0): the "perfect" bonus label. */
struct clCoinPerfect : FadeObj {
#ifdef COIN_EXTERNAL_DTOR_VTABLE
    void Update();
#endif
    ~clCoinPerfect();
    TextSprite text;
    ResCtrl r[3];
    clCoinPerfect(int n) {
        tracks[0].Set(lbl_806DB190, lbl_806DB194, lbl_806DB1F8);
        r[0].resId = (short)(n % 10 + 0x14BA);
        r[0].Show(lbl_806DB1FC, lbl_806DB200, lbl_806DB194);
        r[0].scaleX = lbl_806DB204;
        r[0].scaleY = lbl_806DB204;
        r[2].resId = 0x14C9;
        r[2].Show(lbl_806DB208, lbl_806DB200, lbl_806DB194);
        r[2].scaleX = lbl_806DB20C;
        r[2].scaleY = lbl_806DB20C;
        TexMgr_SetTexture(&text, lbl_806DB210, GetTextureByIdAndLang(0x72, -1));
        text.visible = 1;
        fn_801F93D0(&text, lbl_806DB214, lbl_806DB214);
        fn_801F93EC(&text, lbl_806DB218, lbl_806DB200);
        fn_801F8FCC(&text, 2);
        fn_801F8E90(&text);
        SoundMgr_Play(0x1B);
    }
#ifndef COIN_EXTERNAL_DTOR_VTABLE
    void Update();
#endif
    void Draw();
};

/* clGetCoinSum (0x6E8): the coin mileage total. */
struct clGetCoinSum : FadeObj {
#ifdef COIN_EXTERNAL_DTOR_VTABLE
    void Update();
#endif
    ~clGetCoinSum();
    int value;
    Own<Sprite> spr;
    ResCtrl r[2];
    ResCtrl digits[5];
    TextSprite text;
    ResCtrl glow[5];
    unsigned char flash;
    unsigned char done;
    int timer;
    clGetCoinSum();
    void Layout();
#ifndef COIN_EXTERNAL_DTOR_VTABLE
    void Update();
#endif
    void Draw();
    void Flash() {
        flash = 1;
        done = 0;
        timer = 0;
    }
};



/* Window that shows one unlocked item (0x1190). */
struct ItemWnd {
    int coins;
    int state;
    int timer;
    int sub;
    MilageItem *entry;
    int itemId;
    Model *kart;
    ItemModel *item;
    Sprite *spr[3];
    TextManager texts[7];
    ResCtrl label;
    int labelLayer;
    ResCtrl digits[4];
    ResCtrl fade;
    ItemWnd()
        : state(0), timer(0), sub(0), entry(0), itemId(0), kart(0), item(0), labelLayer(5) {
        spr[0] = 0;
        spr[1] = 0;
        spr[2] = 0;
        spr[0] = new Sprite(0x192, 1, 0);
        spr[0]->SetPos(lbl_806DB1E8, lbl_806DB290);
        spr[0]->layer = 4;
        spr[0]->alpha = lbl_806DB190;
        label.resId = 0x1ECD;
        fade.mode = 2;
        fade.width = lbl_806DB224;
        fade.height = lbl_806DB274;
        fade.Show(lbl_806DB1E8, lbl_806DB2AC, lbl_806DB194);
        fade.SetColor(0);
        for (int i = 0; i < 3; i++) {
            texts[i].spacing = lbl_806DB2A8;
            texts[i].visible = 1;
            fn_801F8FCC(&texts[i], 1);
        }
        if (isJapanese() == 0) {
            fn_801F93EC(&texts[0], lbl_806DB1E8, lbl_806DB2C8);
            fn_801F93EC(&texts[1], lbl_806DB1E8, lbl_806DB2CC);
            fn_801F93EC(&texts[2], lbl_806DB1E8, lbl_806DB2D0);
        } else {
            fn_801F93EC(&texts[0], lbl_806DB2D4, lbl_806DB2C8);
            fn_801F93EC(&texts[1], lbl_806DB2D4, lbl_806DB2CC);
            fn_801F93EC(&texts[2], lbl_806DB2D4, lbl_806DB2D0);
        }
        texts[3].spacing = lbl_806DB2D8;
        texts[4].spacing = lbl_806DB2D8;
        texts[5].spacing = lbl_806DB2D8;
        texts[6].spacing = lbl_806DB2D8;
    }
    ~ItemWnd() {
        for (int i = 0; i < 3; i++) {
            if (spr[i] != 0) {
                delete spr[i];
                spr[i] = 0;
            }
        }
        if (kart) {
            delete kart;
            kart = 0;
        }
        if (item) {
            delete item;
            item = 0;
        }
    }
    void Setup(int n, MilageItem *e);
    void Update();
    void Open();
    void ShowKart();
    void ShowItem();
    void ShowTicket();
    void ShowOther();
    void SetTextAlpha(unsigned int c) {
        digits[0].SetColor(c);
        digits[1].SetColor(c);
        digits[2].SetColor(c);
        digits[3].SetColor(c);
    }
    void Draw() {
        /* one counter for all three loops: its later ranges are split-off
           temps numbered below the loop pointers (regalloc_patterns 73) */
        int i;
        for (i = 0; i < 3; i++) {
            if (spr[i] != 0) {
                fn_801A0004(spr[i]);
            }
        }
        void *mgr = fn_801F8E58();
        for (i = 0; i < 7; i++) {
            fn_801F8A34(mgr, &texts[i], 5);
        }
        for (i = 0; i < 4; i++) {
            fn_8011FAFC(&digits[i], 5);
        }
        fn_8011FAFC(&label, labelLayer);
        fn_8011FAFC(&fade, 3);
    }
};

/* "N more coins to the next item" window (0x1CC). */
struct NextWnd {
    Sprite *spr[2];
    ResCtrl back;
    ResCtrl label;
    ResCtrl digits[3];
    int value;
    int state;
    int timer;
    NextWnd() : value(0), state(0), timer(0) {
        spr[0] = 0;
        spr[1] = 0;
        spr[0] = new Sprite(0x12, 1, 0);
        spr[1] = new Sprite(0x149, 1, 0);
        spr[0]->alpha = lbl_806DB190;
        spr[1]->alpha = lbl_806DB190;
        spr[0]->layer = 4;
        spr[1]->layer = 5;
        spr[0]->SetPos(lbl_806DB1E8, lbl_806DB290);
        spr[1]->SetPos(lbl_806DB1E8, lbl_806DB2AC);
        spr[1]->SetAnimParam(0x1931, 0x1ECD);
        spr[1]->SetAnimParam(0x1932, 0x1ECD);
        back.mode = 2;
        back.width = lbl_806DB224;
        back.height = lbl_806DB274;
        back.Show(lbl_806DB1E8, lbl_806DB2AC, lbl_806DB194);
        back.SetColor(0);
        label.Show(lbl_806DB1E8, lbl_806DB290, lbl_806DB194);
        label.resId = 0x1E88;
        label.SetColor(0xFFFFFF00);
    }
    ~NextWnd() {
        for (int i = 0; i < 2; i++) {
            if (spr[i] != 0) {
                delete spr[i];
                spr[i] = 0;
            }
        }
    }
    void Start(int n);
    void Update();
    void Count();
    void SetDigitColor(unsigned int c) {
        digits[0].SetColor(c);
        digits[1].SetColor(c);
        digits[2].SetColor(c);
    }
    void Draw() {
        if (state != 0) {
            fn_8011FAFC(&back, 3);
            fn_8011FAFC(&label, 4);
            int i;
            for (i = 0; i < 3; i++) {
                fn_8011FAFC(&digits[i], 5);
            }
            for (i = 0; i < 2; i++) {
                if (spr[i] != 0) {
                    fn_801A0004(spr[i]);
                }
            }
        }
    }
};

struct Coin {
    float x;
    float y;
    float z;
    float vy;
    float vx;
    float rot;
    float vrot;
    unsigned char bounced;
};

struct SceneBase {
    virtual ~SceneBase() {}
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    unsigned char done;
    unsigned char pad5[3]; /* tail padding, named so a derived class cannot use it */
    SceneBase() : done(false) {}
};

struct clCSSceneCoinMilage : SceneBase {
#ifdef COIN_EXTERNAL_VTABLE_KEY
    /* An undefined first key keeps the original externally owned vtable. */
    virtual void ExternalVtableKey();
#endif
    Coin coins[30];
    int numCoins;
    Model *model;
    int x3d0;
    int milage;
    int earned;
    int bonus1;
    int bonus2;
    int x3e4;
    int perfectCoins;
    unsigned char hasPerfect;
    unsigned char hasBonus1;
    unsigned char hasBonus2;
    int counter;
    int itemIndex;
    int state;
    int sub;
    int timer;
    int wait;
    int tick;
    clGetCoinSum *sum;
    ItemWnd *wnd;
    NextWnd *next;
    clGetCoinLine *lines[4];
    clCoinPerfect *perfect;
    PtrVec<FadeObj *> nodes;
    clCSSceneCoinMilage();
    ~clCSSceneCoinMilage();
    void Destroy();
    void Update();
    void Draw();
    void StateNext();
    void StateItems();
    void StateSum();
    void StateLines();
    void StateCoins();
    int Total() {
        int n = earned;
        if (hasBonus1 == 1) {
            n += bonus1;
        }
        if (hasBonus2 == 1) {
            n += bonus2;
        }
        if (hasPerfect == 1) {
            n += perfectCoins;
        }
        return n;
    }
};

