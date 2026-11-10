#ifndef GAME_ANON_8021BC44_TYPES_H
#define GAME_ANON_8021BC44_TYPES_H
#include "game/singleton.h"
#include "game/anon_8021BC44Private.h"

/*
 * 0x8021BC44..0x8021ED1C: time attack result scene (vtable TimeAttackResult_vtable_804EDD98,
 * base lbl_803FE0C8). Shows the lap time and rank, lets a new record enter
 * its name, then offers the coin continue panel.
 *
 * anon_8021BC44_nm1 owns the rodata pool 0x803C5400..0x803C65E0
 * (src/game/anon_8021BC44_nm1_rodata.inc); its statics give the section anchor.
 */

void *operator new(unsigned long size);
void operator delete(void *p) throw();

#include "game/types/InputState.h"

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
    void SetSize(float w, float h) {
        width = w;
        height = h;
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
    Sprite(int res, int a, float x0, float x1, float y0, float y1, float z0, float z1);
    ~Sprite();
    void SetAnimParam(int key, short value);
    void SetPos(float px, float py) {
        x = px;
        y = py;
    }
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

template <class T> struct PtrVec : PtrVecBase<T> {
    PtrVec() {}
    ~PtrVec() {}
    T *begin() { return this->data; }
    T *end() { return this->data + this->count; }
    void DeleteAll() {
        for (T *it = begin(); it != end(); it++) {
            delete *it;
        }
    }
};

/* 0x230-byte text sprite (ctor TexMgr_Init). */
struct TextSprite {
    char pad000[0x18];
    int visible;
    char pad01C[0x22C - 0x1C];
    float spacing;
    TextSprite();
};

/* 0x230-byte text manager (ctor fn_80149214, dtor dtor_800869D0). */
struct TextManager {
    char pad[0x230];
    TextManager();
    ~TextManager();
};

/* Row of text sprites (ctor fn_802174A8, dtor dtor_80217404). */
struct TextRow {
    PtrVec<TextSprite *> sprites;
    int layer;
    int align;
    int visible;
    unsigned char alpha;
    float x;
    float y;
    float sx;
    float sy;
    unsigned char dirty;
    TextRow();
    ~TextRow();
    void SetPos(float px, float py) {
        dirty = 1;
        x = px;
        y = py;
    }
    void SetVisible(int v) {
        dirty = 1;
        visible = v;
    }
    void SetLayer(int l) {
        dirty = 1;
        layer = l;
    }
};

struct SpriteBox {
    int id;
    SpriteBox(ResCtrl *rc, int layer);
    ~SpriteBox();
};

struct CoinPrompt {
    char body[0x20];
    CoinPrompt(int a, int b, int c, int d, int e);
    ~CoinPrompt();
};

struct CreditHud {
    ~CreditHud();
};

struct clCSPartsInerface {
    int obj;
    unsigned char active;
    float x, y;
    float alpha;
    void SetPos(float px, float py) { x = px; y = py; }
    virtual ~clCSPartsInerface();
    virtual void m0C();
    virtual void m10();
    virtual void Update();
    virtual void Draw();
};

struct clCSPartsResultTimeNum : clCSPartsInerface {
    char pad18[0x1C - 0x18];
    ~clCSPartsResultTimeNum();
    clCSPartsResultTimeNum(int res);
};

struct clCSPartsResultRecord : clCSPartsInerface {
    char pad18[0x24 - 0x18];
    unsigned char done;
    char pad25[0xD0 - 0x25];
    ~clCSPartsResultRecord();
    clCSPartsResultRecord();
};

struct TitlePart {
    virtual void v08();
    virtual void Release();
    virtual void Update();
    virtual void Draw();
    unsigned char done;
};

struct ItemMsgWnd {
    char body[0x5C];
    ItemMsgWnd();
    ~ItemMsgWnd();
};

struct CoinPopupDetail {
    int pad00;
    char list04[0xC];
    int state;
    int pad14;
    int mode;
    float rect[4];
    char pad2C[0x24];
    char list50[0x10];
    Sprite *center;
    char pad64[8];
    float offs[8];
    CoinPopupDetail(int a, int b, int c);
    void SetRect(float x0, float y0, float x1, float y1);
    unsigned char IsOpen() { return state == 1; }
    int Choice() {
        if (state < 2) {
            return 2;
        }
        return mode;
    }
};

struct DetailHolder {
    CoinPopupDetail *p;
    DetailHolder(CoinPopupDetail *q) : p(q) {}
    ~DetailHolder();
};


struct NameObj {
    virtual ~NameObj();
};

struct NameEntry {
    KeyBoard board;
    char pad28[2];
    unsigned short name[(0x40 - 0x2A) / 2];
    Own<Sprite> cursor;
    char *bufs[4][15];
    int state;
    char pad138[0x148 - 0x138];
    PtrVec<NameObj *> objs;
    NameEntry(bool english);
    ~NameEntry();
    bool Done() { return state == 5; }
};

struct TaEntry {
    int time;
    unsigned char cup;
    bool longRound;
    bool reverse;
    int cc;
    int chara;
    int kart;
    void Set(int k, int ch, int c, bool rev, bool lng, int cu, int t) { time = t; cup = cu; longRound = lng; reverse = rev; cc = c; chara = ch; kart = k; }
};

struct PlayerData {
    char pad000[0x14];
    TaEntry last;
    char pad028[0x19B - 0x28];
    unsigned char b19B;
    unsigned char b19C;
    char pad19D[0x1B1 - 0x19D];
    unsigned char b1B1;
};

struct RecName {
    unsigned short c[6];
};

struct ModeInfo {
    unsigned char b0;
    unsigned char flag;
};

struct ItemDisplay;

extern "C" {
extern const float lbl_806DB064[2];
extern const float lbl_806DB06C[2];
extern const float lbl_806DB074;
extern const float lbl_806DB078;
extern const float lbl_806DB07C;
extern const float lbl_806DB080;
extern const float lbl_806DB084;
extern const float lbl_806DB08C;
extern const float lbl_806DB090;
extern const float lbl_806DB094;
extern const float lbl_806DB098;
extern const float lbl_806DB09C;
extern const float lbl_806DB0A0;
extern const float lbl_806DB0A4;
extern const float lbl_806DB0A8;
extern const float lbl_806DB0AC;
extern const float lbl_806DB0B0;
extern const float lbl_806DB0B4;
extern const float lbl_806DB0B8;
extern const float lbl_806DB0C8;
extern const float lbl_806DB0CC;
extern const float lbl_806DB0D0;
extern const float lbl_806DB0D4;
extern const float lbl_806DB0D8;
extern const float lbl_806DB0DC;
extern const float lbl_806DB0E0;
extern const float lbl_806DB0E4;
extern const float lbl_806DB0E8;
extern const float lbl_806DB0EC;
extern const float lbl_806DB0F0;
extern const float lbl_806DB0F4;
extern const float lbl_806DB0F8;
extern const float lbl_806DB0FC;
extern const float lbl_806DB100;
extern const float lbl_806DB104;
extern const float lbl_806DB108;
extern const float lbl_806DB10C;
extern const float lbl_806DB110;
extern const float lbl_806DB114;
extern const float lbl_806DB118;
extern const float lbl_806DB11C;
extern const float lbl_806DB120;
extern const float lbl_806DB124;
extern const float lbl_806DB128;
extern const float lbl_806DB12C;
extern const float lbl_806DB130;
extern const float lbl_806DB134;
extern const float lbl_806DB140;
extern const float lbl_806DB144;
extern const float lbl_806DB148;
extern const float lbl_806DB14C;
extern const float lbl_806DB150;
extern const float lbl_806DB154;
extern const float lbl_806DB158;
extern const float lbl_806DB15C;
extern const float lbl_806DB160;
extern const float lbl_806DB164;
extern const float lbl_806DB168;
extern const float lbl_806DB16C;
extern const float lbl_806DB170;
extern const float lbl_806DB174;
extern const float lbl_806DB178;
extern const float lbl_806DB17C;
extern const float lbl_806DB180;
extern const float lbl_806DB184;
extern InputState *g_pInputState;
extern char lbl_806DB088[4];
extern char lbl_806DB138[8];
extern char lbl_806D04A8[8];
extern char lbl_806D04B0[8];
extern TaEntry lbl_80679C88;
extern PlayerData g_playerData;
extern ItemMsgWnd *lbl_806D1A88;
extern void *lbl_806D1A60;
extern float g_totalRaceTime;
extern int g_reverseRoundFlag;
extern int g_longRoundFlag;
extern int g_cupId;
extern int g_ccClass;
extern int g_characterId;
extern int g_kartVariant;
extern int g_roundIndex;
int isJapanese(void);
void DebugPrintf(const char *fmt, ...);
void HSD_StateInvalidate(int state);
void fn_8011FAB8(void);
void fn_8011FAFC(ResCtrl *r, int layer);
void fn_80121E10(ResCtrl *r);
int SpriteHandle_CreateDefault(ResCtrl *ctrl, int layer);
void SpriteHandle_Destroy(int sprite);
void SpriteHandle_SetActiveFlag(int sprite, int active);
void SpriteHandle_SetCornerAlpha(int sprite, unsigned char alpha);
void SpriteHandle_RecomputeCull(int sprite);
void fn_80144C1C(clCSPartsResultRecord *p);
void **fn_80146000(void *vec, int index);
void *fn_80160238(void);
void *fn_80271340(void *p, int off, void *to, void *from, int a);
void fn_80160588(CoinPopupDetail *p, int dir, bool b);
void fn_8016039C(CoinPopupDetail *p);
void fn_801618CC(CoinPopupDetail *p, int a, int b);
void fn_80161888(CoinPopupDetail *p);
int fn_80167744(int digit, float time);
void fn_80167A24(int a, int b, float x, float y, float s, float sx, float sy, float alpha, float time);
void fn_801685A4(int a, void *tex, float x, float y, float s, float sx, float sy, float alpha, ...);
void fn_80169334(int a, int res, int c, float x, float y, float z, float s, float alpha);
void fn_801695E0(int a, int res, int c, float x, float y, float alpha);
void fn_801699D8(int a, int b);
unsigned char fn_80169DF0(void);
float fn_8018A8D4(void);
int fn_8018AD70(void);
int fn_8018AE34(void);
int fn_8018AEF8(void);
int fn_8018AFC0(void);
int fn_8018B088(void);
void fn_8018B14C(unsigned short *buf);
void fn_8018B248(void);
const char *fn_8018B300(void);
void fn_8018B31C(PlayerData *pd, int chara, int kart, int cc, int cup, int lng, int rev, int coins, int a, int b, int c, int d, float time);
void fn_8018CC64(void);
unsigned char fn_8019FE78(Sprite *s);
void fn_801A0004(Sprite *s);
void fn_801A0550(Sprite *s);
void Sprite_AdvanceAnim(Sprite *s, float step);
void Sprite_SetupAnim(Sprite *s, int a, int b, int c);
void fn_801BDB60(NameEntry *n);
void fn_801BE170(NameEntry *n);
short fn_801D8DB4(int cup, int round, int idx);
float fn_801D8D3C(int cup, int lng);
void fn_801F8E90(TextSprite *t);
void fn_801F8FCC(TextSprite *t, int mode);
void fn_801F9014(TextSprite *t, const unsigned short *s, ...);
void TexMgr_SetTexture(TextSprite *t, const char *s, ...);
void TexMgr_Apply(TextSprite *t);
void fn_801F93EC(void *t, float x, float y);
ItemDisplay *ItemDisplay_GetOrCreate(void);
void ItemDisplay_Start(ItemDisplay *d, int id);
void fn_8020AAD4(ItemDisplay *d);
void fn_802170F0(TextRow *row, int alpha);
void fn_8021713C(TextRow *row);
void fn_80217298(TextRow *row, const char *text, unsigned char r, unsigned char g, unsigned char b, float spacing);
void fn_80217390(TextRow *row);
void fn_8021A0B0(void *fx);
void fn_8021A0DC(void *fx);
void fn_80232284(ItemMsgWnd *w, float t);
void fn_8023CCCC(CoinPrompt *p, float a, float b);
void fn_8023CCF8(CoinPrompt *p, float a, float b);
void fn_8023CD24(CoinPrompt *p, float a, float b);
void fn_8023CD3C(CoinPrompt *p, float a, float b);
void fn_8023CD54(CoinPrompt *p);
void fn_8023CDA8(CoinPrompt *p);
void fn_8023CEB4(CoinPrompt *p);
void fn_8023CFC8(CoinPrompt *p);
void fn_8023CFD4(CoinPrompt *p);
ModeInfo *fn_8024F588(void);
void *GetTextureByIdAndLang(int id, int lang);
const char *GetTextureByIdAndLang_s(int id, int lang);
int GetEarnedCoins(void);
int GetCoinMilage(PlayerData *pd);
int TaRecord_GetLastInsertedRank(void);
float TaRecord_GetTime_Current(int idx);
RecName *TaRecord_GetEntry_Current(int rank);
unsigned char has_title_changed(void);
float LUT_Sin12Bit(float x);
float Saturate_Double(float x, float lo, float hi);
void SetRumbleMode(int a, int b, int c);
void RumbleUpdate(void);
unsigned short *wcsncpy(unsigned short *dst, const unsigned short *src, unsigned long n);
void PtrVec_InsertFill(void *v, void *pos, int n, const void *val);
}

static inline void SetCourseAnim(Sprite *s, int key, int idx) {
    s->SetAnimParam(key, fn_801D8DB4(g_cupId, g_roundIndex, idx));
}

static inline int IsReverse() {
    return g_reverseRoundFlag == 1;
}

static inline InputState *GetInput() {
    return SINGLETON_INSTANCE(g_pInputState);
}

static inline void SetInput(unsigned char en) {
    InputState *in = GetInput();
    in->enabled = en;
    in->held = 0;
    in->edge = 0;
}

static inline ItemMsgWnd *ItemMsg_Get() {
    return lbl_806D1A88 ? lbl_806D1A88 : (lbl_806D1A88 = new ItemMsgWnd);
}

static inline void SetXY(Sprite *s, float x, float y) {
    s->x = x;
    s->y = y;
}

inline void CoinPopupDetail::SetRect(float x0, float y0, float x1, float y1) {
    rect[0] = x0;
    rect[1] = y0;
    rect[2] = x1;
    rect[3] = y1;
    SetXY((Sprite *)*fn_80146000(list04, 0), rect[0], rect[1]);
    SetXY((Sprite *)*fn_80146000(list04, 1), rect[2], rect[3]);
    fn_801F93EC(*fn_80146000(list50, 0), rect[0] + offs[0], rect[1] + offs[1]);
    fn_801F93EC(*fn_80146000(list50, 1), rect[0] + offs[2], rect[1] + offs[3]);
    fn_801F93EC(*fn_80146000(list50, 2), rect[2] + offs[4], rect[3] + offs[5]);
    fn_801F93EC(*fn_80146000(list50, 3), rect[2] + offs[6], rect[3] + offs[7]);
    SetXY(center, 0.5f * (rect[2] - rect[0]) + rect[0], 0.5f * (rect[3] - rect[1]) + rect[1]);
}

inline NameEntry::~NameEntry() {
    for (NameObj **it = objs.begin(); it != objs.end(); it++) {
        delete *it;
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 15; j++) {
            operator delete(bufs[i][j]);
        }
    }
    SetInput(0);
    if (lbl_806D1A88 != 0) {
        delete lbl_806D1A88;
        lbl_806D1A88 = 0;
    }
    fn_801699D8(0, 0);
    fn_801699D8(1, 0);
}

inline SpriteBox::SpriteBox(ResCtrl *rc, int layer) {
    id = SpriteHandle_CreateDefault(rc, layer);
}

inline SpriteBox::~SpriteBox() {
    if (id >= 0) {
        SpriteHandle_Destroy(id);
        id = -1;
    }
}

/* "New record" banner with two text rows (0x70C bytes). */
struct RecordBanner {
    TextManager text[3];
    TextRow rows[2];
    Own<Sprite> flash;
    SpriteBox *glow;
    SpriteBox *label;
    SpriteBox *back;
    int state;
    int timer;
    unsigned char done;
    RecordBanner();
    ~RecordBanner() {
        if (glow != 0) {
            delete glow;
            glow = 0;
        }
        if (label != 0) {
            delete label;
            label = 0;
        }
        if (back != 0) {
            delete back;
            back = 0;
        }
    }
    void Update();
    void Draw() {
        if (state == 0 || state == 2) {
            fn_801A0004(flash.p);
        }
        fn_80217390(&rows[0]);
        fn_80217390(&rows[1]);
    }
};

struct Blink {
    Sprite *spr;
    unsigned char active;
    unsigned char closing;
    int t;
    Blink() : active(0), closing(0), t(0) { spr = new Sprite(0x9E, 1, 394.0f, 394.0f, 1.0f, 1.0f, 0.0f, 0.0f); }
    ~Blink() { delete spr; }
    void Open() {
        if (active == 1 && closing == 0) {
            return;
        }
        active = 1;
        closing = 0;
        t = 0;
    }
    void Close() {
        if (active == 0 || closing == 1) {
            return;
        }
        closing = 1;
        t = 0;
    }
};

struct FadeTrack {
    unsigned char active;
    float from;
    float to;
    float speed;
    float t;
    float value;
    FadeTrack() : speed(lbl_806DB074), t(lbl_806DB074) {}
    void Set(float f, float e, float s) {
        from = f;
        to = e;
        speed = s;
        t = lbl_806DB074;
        value = f;
        active = 1;
    }
    void Step() {
        if (active == 1) {
            value = from * (lbl_806DB07C - t) + to * t;
            t += speed;
            if (t > lbl_806DB07C) {
                t = lbl_806DB07C;
            }
        }
    }
};

struct FadeObj {
    virtual ~FadeObj();
    virtual void Update();
    virtual void Draw();
    virtual void _keyF();
    Sprite *sprite;
    int delay;
    FadeTrack tracks[5];
    unsigned char shown;
    unsigned char flush;
    FadeObj() : sprite(0), delay(20) {
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
                Sprite_AdvanceAnim(sprite, lbl_806DB0E4);
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

struct FadeText : FadeObj {
    TextSprite text;
    int layer;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    float scale;
    FadeText(const unsigned short *s, float x) {
        tracks[3].Set(lbl_806DB09C, lbl_806DB09C, lbl_806DB07C);
        tracks[4].Set(x, x, lbl_806DB07C);
        text.visible = 1;
        fn_801F8FCC(&text, 1);
        fn_801F9014(&text, s);
        fn_801F8E90(&text);
        r = 0xFF;
        g = 0xFF;
        b = 0xFF;
        scale = lbl_806DB07C;
        layer = 7;
    }
    FadeText(const char *s, float x) {
        tracks[3].Set(lbl_806DB09C, lbl_806DB09C, lbl_806DB07C);
        tracks[4].Set(x, x, lbl_806DB07C);
        text.visible = 1;
        fn_801F8FCC(&text, 1);
        TexMgr_SetTexture(&text, s);
        fn_801F8E90(&text);
        r = 0xFF;
        g = 0xFF;
        b = 0xFF;
        scale = lbl_806DB07C;
        layer = 7;
    }
    virtual void _keyT();
    void SetSpacing(float sp) {
        text.spacing = sp;
        fn_801F8E90(&text);
    }
};

/* Coin continue panel (0x1C bytes). */
struct CoinContinue {
    int state;
    float timer;
    DetailHolder detail;
    Own<CoinPrompt> prompt;
    PtrVec<FadeObj *> objs;
    CoinContinue();
    ~CoinContinue();
    void Draw();
    void Update();
    void Select();
};

static inline unsigned int PackColor(int r, int g, int b, int a) {
    return ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | (a & 0xFF);
}

#include "game/types/SceneBase.h"

struct TimeAttackResult : SceneBase {
    virtual void _key();
    int state;
    float timer;
    float x10;
    float x14;
    unsigned char x18;
    unsigned char noRecord;
    int rank;
    unsigned char showBanner;
    float time;
    float best;
    float fade;
    CreditHud *credit;
    clCSPartsResultTimeNum *digits[9];
    clCSPartsResultRecord *record;
    RecordBanner *banner;
    TitlePart *title;
    CoinContinue *coin;
    RecName name;
    NameEntry *entry;
    Own<CoinPrompt> prompt;
    Own<Sprite> course;
    Own<Blink> blink;
    TimeAttackResult();
    ~TimeAttackResult();
    void Destroy();
    void Update();
    void Draw();
    void DrawResult(float alpha);
};


#endif
