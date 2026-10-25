/*
 * 0x8021BC44..0x8021ED1C: time attack result scene (vtable lbl_804EDD98,
 * base lbl_803FE0C8). Shows the lap time and rank, lets a new record enter
 * its name, then offers the coin continue panel.
 *
 * The draw helpers address their position tables and debug strings off the
 * TU rodata pool (lbl_803C5400), which this TU does not own.
 */

void *operator new(unsigned long size);
void operator delete(void *p) throw();

struct InputState {
    char pad00[4];
    unsigned char enabled;
    char pad05[0xF];
    int dir;
    int held;
    int edge;
};

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
    virtual ~clCSPartsInerface();
    virtual void m0C();
    virtual void m10();
    virtual void Update();
    virtual void Draw();
};

struct clCSPartsResultTimeNum : clCSPartsInerface {
    char pad18[0x1C - 0x18];
    clCSPartsResultTimeNum(int res);
};

struct clCSPartsResultRecord : clCSPartsInerface {
    char pad18[0x24 - 0x18];
    unsigned char done;
    char pad25[0xD0 - 0x25];
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

struct NameEntryHead {
    int x0;
};

struct NameEntryBase {
    char pad04[0x2A - 0x4];
    unsigned short name[(0x40 - 0x2A) / 2];
    ~NameEntryBase();
};

struct NameObj {
    virtual ~NameObj();
};

struct NameEntry : NameEntryHead, NameEntryBase {
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

/* Rodata pool of this TU. */
struct ResultPool {
    char pad000[0xF14];
    float partX[9];
    short courseRes[8][2];
    float rowY[3];
    char padF64[0xFA0 - 0xF64];
    char fmtName[0x10];
    char fmt1[0xC];
    char fmt2[0xC];
    char fmt3[0xC];
    char fmt4[0xC];
    char fmt5[0xC];
    char fmt6[0xC];
    char padFF8[0x1028 - 0xFF8];
    char recJa1[0x10];
    char recJa2[0x10];
    char recEn1[0x14];
    char recEn2[0x10];
};

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
extern ResultPool lbl_803C5400;
extern char lbl_803C63F8[];
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
    return g_pInputState == 0 ? (InputState *)0 : g_pInputState;
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
    Blink() : active(0), closing(0), t(0) { spr = new Sprite(0x9E, 1, lbl_806DB080, lbl_806DB080, lbl_806DB07C, lbl_806DB07C, lbl_806DB074, lbl_806DB074); }
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

struct SceneBase {
    virtual ~SceneBase() {}
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    bool done;
    SceneBase() : done(false) {}
};

struct TimeAttackResult : SceneBase {
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
    virtual void _key();
};

TimeAttackResult::~TimeAttackResult() {
    for (int i = 0; i < 9; i++) {
        if (digits[i] != 0) {
            delete digits[i];
            digits[i] = 0;
        }
    }
    if (credit != 0) {
        delete credit;
        credit = 0;
    }
    if (record != 0) {
        delete record;
        record = 0;
    }
    if (banner != 0) {
        delete banner;
        banner = 0;
    }
    if (entry) {
        NameEntry *e = entry;
        delete e;
    }
    if (title != 0) {
        title->Release();
    }
    if (coin != 0) {
        delete coin;
    }
}

TimeAttackResult::TimeAttackResult()
    : state(0), timer(lbl_806DB074), x18(0), noRecord(0), rank(-1), showBanner(0), time(lbl_806DB074), best(lbl_806DB078), fade(lbl_806DB07C),
      credit(0), record(0), banner(0), title(0), coin(0), entry(0), prompt(new CoinPrompt(0x74, -1, 0x1872, -1, 4)),
      course(new Sprite(0x14F, 0, 0)), blink(new Blink) {
    ResultPool *P = &lbl_803C5400;
    rank = TaRecord_GetLastInsertedRank();
    noRecord = fn_80169DF0();
    showBanner = fn_8024F588()->flag;
    time = g_totalRaceTime;
    name.c[0] = 0;
    name.c[1] = 0;
    name.c[2] = 0;
    name.c[3] = 0;
    name.c[4] = 0;
    name.c[5] = 0;
    best = time;
    TaEntry *e = &lbl_80679C88;
    e->time = lbl_806DB084 * g_totalRaceTime;
    e->cup = g_cupId;
    e->longRound = g_longRoundFlag;
    e->reverse = g_reverseRoundFlag == 1;
    e->cc = g_ccClass;
    e->chara = g_characterId;
    e->kart = g_kartVariant;
    if (fn_8018B300() != 0) {
        DebugPrintf(lbl_806DB088, fn_8018B300());
        unsigned short buf[5];
        fn_8018B14C(buf);
        for (int i = 0; i < 5; i++) {
            DebugPrintf(P->fmtName, i, buf[i]);
        }
        DebugPrintf(P->fmt1, fn_8018B088());
        DebugPrintf(P->fmt2, fn_8018AFC0());
        DebugPrintf(P->fmt3, fn_8018AEF8());
        DebugPrintf(P->fmt4, fn_8018AE34());
        DebugPrintf(P->fmt5, fn_8018AD70());
        DebugPrintf(P->fmt6, fn_8018A8D4());
    }
    if (noRecord == 0) {
        g_playerData.last = lbl_80679C88;
    }
    for (int i = 0; i < 9; i++) {
        int res = fn_80167744(8 - i, time) + 0x1531;
        digits[i] = new clCSPartsResultTimeNum(res);
        digits[i]->obj = 1;
        digits[i]->m0C();
    }
    record = new clCSPartsResultRecord;
    record->obj = 1;
    record->m0C();
    title = (TitlePart *)fn_80271340(fn_80160238(), 0, lbl_806D04B0, lbl_806D04A8, 0);
    showBanner = fn_8024F588()->flag;
    fn_8023CEB4(prompt.p);
    fn_8023CD3C(prompt.p, lbl_806DB08C, lbl_806DB090);
    fn_8023CCF8(prompt.p, lbl_806DB094, lbl_806DB098);
    entry = 0;
    course.p->layer = 0;
    course.p->SetPos(lbl_806DB09C, lbl_806DB0A0);
    SetCourseAnim(course.p, 0xA9C, 0);
    SetCourseAnim(course.p, 0xA9D, 1);
    fn_801A0550(course.p);
    course.p->alpha = lbl_806DB07C;
    blink.p->spr->layer = 5;
    blink.p->spr->x = fn_801D8D3C(g_cupId, g_longRoundFlag);
    blink.p->spr->y = lbl_806DB0A4;
    SetInput(1);
}

void TimeAttackResult::Draw() {
    ResCtrl bg;
    unsigned int c = lbl_806DB0A8 * fade;
    bg.mode = 2;
    bg.SetSize(lbl_806DB0AC, lbl_806DB0B0);
    bg.Show(lbl_806DB09C, lbl_806DB0A0, lbl_806DB07C);
    bg.SetColor(c);
    fn_8011FAFC(&bg, 7);
    if (done != 1) {
        fn_801A0004(course.p);
        ResCtrl band;
        unsigned int c2 = PackColor(0x3C, 0x28, 0x0A, (int)(lbl_806DB0B4 * course.p->alpha));
        band.mode = 2;
        band.SetSize(lbl_806DB0AC, lbl_806DB0B0);
        band.Show(lbl_806DB09C, lbl_806DB0A0, lbl_806DB07C);
        band.SetColor(c2);
        fn_8011FAFC(&band, 0);
        fn_8023CD54(prompt.p);
        if (banner != 0) {
            banner->Draw();
        }
        if (state >= 16 && state <= 18) {
            title->Draw();
        }
        if (state >= 19 && state <= 21 && coin != 0) {
            coin->Draw();
        }
        if (entry != 0) {
            fn_801BDB60(entry);
        }
        if (state >= 10 && state <= 12) {
            record->Draw();
        }
        Blink *b = blink.p;
        if (b->active) {
            fn_801A0004(b->spr);
        }
        HSD_StateInvalidate(-1);
    }
}

void TimeAttackResult::Update() {
    if (done) {
        return;
    }
    unsigned char pressed = 0;
    if (state == 23) {
        done = 1;
        return;
    }
    if (GetInput()->held == 1) {
        SetRumbleMode(0, 1, 1);
        pressed = 1;
    }
    switch (state) {
    case 0:
        fade = lbl_806DB07C - timer / lbl_806DB0D0;
        if (timer >= lbl_806DB0D0) {
            timer = lbl_806DB074;
            state = 1;
            fn_801699D8(0, 1);
            if (g_reverseRoundFlag == 1) {
                blink.p->Open();
            }
        }
        break;
    case 1:
        DrawResult(timer / lbl_806DB0D0);
        if (timer >= lbl_806DB0D0) {
            timer = lbl_806DB074;
            state = 2;
            fn_8023CFD4(prompt.p);
        }
        break;
    case 2:
        DrawResult(lbl_806DB07C);
        if (timer >= lbl_806DB0D4 || pressed) {
            fn_8023CFC8(prompt.p);
            timer = lbl_806DB074;
            if (showBanner == 1) {
                state = 4;
            } else {
                state = 3;
            }
            if (g_reverseRoundFlag == 1) {
                blink.p->Close();
            }
        }
        break;
    case 3:
        DrawResult(lbl_806DB07C - timer / lbl_806DB0D0);
        if (timer >= lbl_806DB0D0) {
            timer = lbl_806DB074;
            if (rank >= 0 && rank < 10) {
                if (noRecord == 1) {
                    state = 10;
                } else {
                    state = 7;
                }
            } else {
                state = 13;
            }
        }
        break;
    case 4:
        if (banner == 0) {
            banner = new RecordBanner;
        }
        DrawResult(lbl_806DB07C);
        if (timer >= lbl_806DB0D0) {
            timer = lbl_806DB074;
            state = 5;
        }
        break;
    case 5:
        DrawResult(lbl_806DB07C);
        if (banner->done) {
            timer = lbl_806DB074;
            state = 6;
        }
        break;
    case 6:
        DrawResult(lbl_806DB07C);
        if (timer >= lbl_806DB0D0) {
            timer = lbl_806DB074;
            if (banner != 0) {
                delete banner;
                banner = 0;
            }
            if (rank >= 0 && rank < 10) {
                if (noRecord == 0) {
                    state = 7;
                } else {
                    state = 10;
                }
            } else {
                state = 13;
            }
        }
        break;
    case 7:
        entry = new NameEntry(isJapanese() == 0);
        ItemDisplay_Start(ItemDisplay_GetOrCreate(), 0x1AD8);
        state = 8;
        break;
    case 8:
        fn_801BE170(entry);
        if (entry->Done() == 1) {
            unsigned short buf[5];
            wcsncpy(buf, entry->name, 5);
            for (int i = 0; i < 5; i++) {
                if (buf[i] == 0x8162) {
                    buf[i] = 0;
                }
            }
            name.c[0] = buf[0];
            name.c[1] = buf[1];
            name.c[2] = buf[2];
            name.c[3] = buf[3];
            name.c[4] = buf[4];
            delete entry;
            entry = 0;
            fn_8020AAD4(ItemDisplay_GetOrCreate());
            RecName *rec = TaRecord_GetEntry_Current(rank);
            rec->c[0] = name.c[0];
            rec->c[1] = name.c[1];
            rec->c[2] = name.c[2];
            rec->c[3] = name.c[3];
            rec->c[4] = name.c[4];
            rec->c[5] = name.c[5];
            SetInput(1);
            state = 9;
            timer = lbl_806DB074;
        }
        break;
    case 9:
        timer = lbl_806DB074;
        state = 10;
        break;
    case 10:
        fn_80144C1C(record);
        timer = lbl_806DB074;
        state = 11;
        break;
    case 11:
        record->Update();
        if (timer >= lbl_806DB0D8 || (timer >= lbl_806DB0DC && pressed)) {
            record->m10();
            timer = lbl_806DB074;
            state = 12;
        }
        break;
    case 12:
        record->Update();
        if (record->done == 1) {
            state = 13;
            timer = lbl_806DB074;
        }
        break;
    case 13:
        fade = timer / lbl_806DB0E0;
        if (timer >= lbl_806DB0E0) {
            timer = lbl_806DB074;
            fade = lbl_806DB07C;
            state = 14;
        }
        break;
    case 14:
        course.p->alpha = lbl_806DB074;
        timer = lbl_806DB074;
        state = 15;
        if (has_title_changed() == 1 || noRecord != 0) {
            state = 15;
        } else {
            state = 22;
        }
        fn_8021A0DC(lbl_806D1A60);
        break;
    case 15:
        fade = lbl_806DB07C - timer / lbl_806DB0D0;
        if (timer >= lbl_806DB0D0) {
            timer = lbl_806DB074;
            fade = lbl_806DB074;
            if (has_title_changed() == 1) {
                state = 16;
            } else if (noRecord != 0) {
                state = 19;
            } else {
                state = 22;
            }
        }
        break;
    case 16:
        if (timer <= lbl_806DB07C) {
            fn_801699D8(0, 0);
        }
        title->Update();
        if (timer >= lbl_806DB0E0) {
            state = 17;
            timer = lbl_806DB074;
        }
        break;
    case 17:
        title->Update();
        if (title->done == 1) {
            state = 18;
            timer = lbl_806DB074;
            fn_801699D8(0, 1);
        }
        break;
    case 18:
        title->Update();
        if (timer >= lbl_806DB0E0) {
            if (noRecord != 0) {
                state = 19;
            } else {
                state = 22;
            }
            timer = lbl_806DB074;
            fade = lbl_806DB07C;
            fn_8021A0DC(lbl_806D1A60);
        }
        break;
    case 19:
        if (coin == 0) {
            fn_8018CC64();
            int lng = g_longRoundFlag;
            int rev = g_reverseRoundFlag;
            int cup = g_cupId;
            int cc = g_ccClass;
            int kart = g_kartVariant;
            int chara = g_characterId;
            int earned = GetEarnedCoins();
            fn_8018B31C(&g_playerData, chara, kart, cc, cup, lng, rev, GetCoinMilage(&g_playerData) + earned,
                        g_playerData.b19B, g_playerData.b19C, g_playerData.b1B1, 1, g_totalRaceTime);
            DebugPrintf(lbl_803C63F8, fn_8018B300());
            coin = new CoinContinue;
        }
        if (fade > lbl_806DB074) {
            fade = lbl_806DB07C - timer / lbl_806DB0E0;
        }
        coin->Update();
        if (timer >= lbl_806DB0E0) {
            state = 20;
            timer = lbl_806DB074;
        }
        break;
    case 20:
        coin->Update();
        if (coin->state == 3) {
            state = 21;
            timer = lbl_806DB074;
        }
        break;
    case 21:
        fade = timer / lbl_806DB0E0;
        if (timer >= lbl_806DB0E0) {
            state = 22;
            timer = lbl_806DB074;
        }
        break;
    case 22:
        fn_801699D8(0, 0);
        fn_8021A0B0(lbl_806D1A60);
        state = 23;
        break;
    }
    if (banner != 0) {
        banner->Update();
    }
    timer += lbl_806DB07C;
    Sprite_AdvanceAnim(course.p, lbl_806DB0E4);
    fn_8023CDA8(prompt.p);
    RumbleUpdate();
    Blink *b = blink.p;
    if (b->active) {
        if (b->t <= 8) {
            float a;
            if (!b->closing) {
                a = b->t * lbl_806DB0E8;
            } else {
                a = lbl_806DB07C - b->t * lbl_806DB0E8;
            }
            b->spr->alpha = a;
            if (b->t++ == 8 && b->closing) {
                b->active = 0;
                b->closing = 0;
            }
        }
        Sprite_AdvanceAnim(b->spr, lbl_806DB0E4);
    }
}

void RecordBanner::Update() {
    InputState *in = GetInput();
    switch (state) {
    case 0: {
        int a = lbl_806DB0B8 * (timer / lbl_806DB0EC);
        if (a >= 128) {
            a = 128;
        }
        if (back->id >= 0) {
            SpriteHandle_SetCornerAlpha(back->id, a);
        }
        if (!fn_8019FE78(flash.p)) {
            state++;
            if (glow->id >= 0) {
                SpriteHandle_SetActiveFlag(glow->id, 1);
            }
            if (label->id >= 0) {
                SpriteHandle_SetActiveFlag(label->id, 1);
            }
            timer = 0;
            if (back->id >= 0) {
                SpriteHandle_SetCornerAlpha(back->id, 128);
            }
        }
        break;
    }
    case 1:
        if (timer <= 10) {
            int a = lbl_806DB0A8 * (timer / lbl_806DB0F0);
            fn_802170F0(&rows[0], a);
            fn_802170F0(&rows[1], a);
        }
        if (in->held == 1 || timer >= 240) {
            state++;
            timer = 0;
            if (glow->id >= 0) {
                SpriteHandle_SetActiveFlag(glow->id, 0);
            }
            if (label->id >= 0) {
                SpriteHandle_SetActiveFlag(label->id, 0);
            }
            Sprite_SetupAnim(flash.p, 0x48, 1, 0);
        }
        break;
    case 2: {
        if (timer <= 10) {
            int a = lbl_806DB0A8 * (lbl_806DB07C - timer / lbl_806DB0F0);
            fn_802170F0(&rows[0], a);
            fn_802170F0(&rows[1], a);
        }
        int a = lbl_806DB0B8 * (lbl_806DB07C - timer / lbl_806DB0EC);
        if (a < 0) {
            a = 0;
        }
        if (back->id >= 0) {
            SpriteHandle_SetCornerAlpha(back->id, a);
        }
        if (!fn_8019FE78(flash.p)) {
            state++;
            timer = 0;
            done = 1;
        }
        break;
    }
    case 3:
        return;
    }
    if (label->id >= 0) {
        SpriteHandle_RecomputeCull(label->id);
    }
    if (glow->id >= 0) {
        SpriteHandle_RecomputeCull(glow->id);
    }
    if (back->id >= 0) {
        SpriteHandle_RecomputeCull(back->id);
    }
    Sprite_AdvanceAnim(flash.p, lbl_806DB0E4);
    timer++;
}

RecordBanner::RecordBanner() : flash(new Sprite(0x49, 1, 0)), glow(0), label(0), state(0), timer(0), done(0) {

    ResultPool *P = &lbl_803C5400;
    rows[0].SetPos(lbl_806DB128, lbl_806DB12C);
    rows[1].SetPos(lbl_806DB128, lbl_806DB130);
    if (isJapanese() == 1) {
        fn_80217298(&rows[0], P->recJa1, 0xE0, 0x20, 0x20, lbl_806DB134);
        fn_80217298(&rows[1], P->recJa2, 0xFF, 0xFF, 0xFF, lbl_806DB134);
    } else {
        fn_80217298(&rows[0], P->recEn1, 0xE0, 0x20, 0x20, lbl_806DB134);
        fn_80217298(&rows[0], lbl_806DB138, 0xFF, 0xFF, 0xFF, lbl_806DB134);
        fn_80217298(&rows[1], P->recEn2, 0xFF, 0xFF, 0xFF, lbl_806DB134);
    }
    for (int i = 0; i < 2; i++) {
        rows[i].SetVisible(1);
        rows[i].SetLayer(6);
        fn_802170F0(&rows[i], 0);
        fn_8021713C(&rows[i]);
    }
    flash.p->SetPos(lbl_806DB09C, lbl_806DB140);
    flash.p->layer = 5;
    ResCtrl rc;
    rc.resId = 0x192A;
    rc.Show(lbl_806DB09C, lbl_806DB140, lbl_806DB07C);
    label = new SpriteBox(&rc, 6);
    if (label->id >= 0) {
        SpriteHandle_SetActiveFlag(label->id, 0);
    }
    fn_80121E10(&rc);
    rc.resId = 0x1D08;
    rc.Show(lbl_806DB144, lbl_806DB148, lbl_806DB07C);
    glow = new SpriteBox(&rc, 6);
    if (glow->id >= 0) {
        SpriteHandle_SetActiveFlag(glow->id, 0);
    }
    fn_80121E10(&rc);
    rc.mode = 2;
    rc.SetSize(lbl_806DB0AC, lbl_806DB0B0);
    rc.Show(lbl_806DB09C, lbl_806DB0A0, lbl_806DB07C);
    rc.SetColor(0);
    back = new SpriteBox(&rc, 5);
}

void TimeAttackResult::DrawResult(float alpha) {
    ResultPool *P = &lbl_803C5400;
    float k;
    float pulse = lbl_806DB07C - LUT_Sin12Bit(lbl_806DB14C * x14);
    fn_80169334(1, 0x152F, 0, lbl_806DB09C, lbl_806DB150, lbl_806DB154, lbl_806DB07C, alpha);
    fn_801695E0(1, P->courseRes[g_cupId - 1][g_longRoundFlag], 0, lbl_806DB158, lbl_806DB0A4, alpha);
    fn_801695E0(1, 0x1530, 0, lbl_806DB15C, lbl_806DB160, alpha);
    for (int i = 0; i < 9; i++) {
        if (lbl_806DB074 == k) {
            digits[i]->m0C();
        }
        digits[i]->x = P->partX[i];
        digits[i]->y = lbl_806DB164;
        digits[i]->alpha = alpha;
        digits[i]->Update();
        digits[i]->Draw();
    }
    fn_80169334(1, 0x1540, 1, lbl_806DB09C, lbl_806DB168, lbl_806DB154, lbl_806DB07C, alpha);
    fn_80169334(1, 0x1540, 1, lbl_806DB09C, lbl_806DB16C, lbl_806DB154, lbl_806DB07C, alpha);
    const float *lx = &lbl_806DB064[isJapanese()];
    const float *vx = &lbl_806DB06C[isJapanese()];
    if (rank >= 0) {
        if (rank < 10) {
            fn_801685A4(1, GetTextureByIdAndLang(0x3A, -1), *lx, P->rowY[0], lbl_806DB07C, pulse, pulse,
                        alpha);
            fn_801685A4(1, GetTextureByIdAndLang(0x3B, -1), *vx, P->rowY[0], lbl_806DB07C, pulse, pulse,
                        alpha, rank + 1);
        } else {
            fn_801685A4(1, GetTextureByIdAndLang(0x3A, -1), *lx, P->rowY[0], lbl_806DB07C, lbl_806DB07C, lbl_806DB07C,
                        alpha);
            fn_801685A4(1, GetTextureByIdAndLang(0x3B, -1), *vx, P->rowY[0], lbl_806DB07C, lbl_806DB07C, lbl_806DB07C,
                        alpha, rank + 1);
        }
    }
    if (time < best || best < lbl_806DB074) {
        fn_801685A4(1, GetTextureByIdAndLang(0x40, -1), *lx, P->rowY[1], lbl_806DB07C, pulse, pulse,
                    alpha);
        fn_80167A24(1, 0, *vx, P->rowY[1], lbl_806DB07C, pulse, pulse, alpha, time);
    } else {
        fn_801685A4(1, GetTextureByIdAndLang(0x40, -1), *lx, P->rowY[1], lbl_806DB07C, lbl_806DB07C, lbl_806DB07C,
                    alpha);
        fn_80167A24(1, 0, *vx, P->rowY[1], lbl_806DB07C, lbl_806DB07C, lbl_806DB07C, alpha, best);
    }
    if (g_ccClass != 0) {
        Saturate_Double((x10 - lbl_806DB170) / lbl_806DB174, lbl_806DB074, lbl_806DB07C);
        if (rank == 0) {
            if (isJapanese() == 1) {
                fn_801685A4(1, GetTextureByIdAndLang(0x3C, -1), *lx, P->rowY[2], lbl_806DB07C, pulse,
                            pulse, alpha);
            } else {
                fn_801685A4(1, GetTextureByIdAndLang(0x3C, -1), *lx, P->rowY[2], lbl_806DB07C, pulse,
                            pulse, alpha);
            }
            fn_80167A24(1, 0, *vx, P->rowY[2], lbl_806DB07C, pulse, pulse, alpha,
                        TaRecord_GetTime_Current(0));
        } else {
            if (isJapanese() == 1) {
                fn_801685A4(1, GetTextureByIdAndLang(0x3C, -1), *lx, P->rowY[2], lbl_806DB07C, lbl_806DB07C,
                            lbl_806DB07C, alpha);
            } else {
                fn_801685A4(1, GetTextureByIdAndLang(0x3C, -1), *lx, P->rowY[2], lbl_806DB07C, lbl_806DB07C,
                            lbl_806DB07C, alpha);
            }
            fn_80167A24(1, 0, *vx, P->rowY[2], lbl_806DB07C, lbl_806DB07C, lbl_806DB07C, alpha,
                        TaRecord_GetTime_Current(0));
        }
    }
    if (rank == 0) {
        fn_801695E0(1, 0x153D, 0, lbl_806DB178, lbl_806DB17C, alpha);
        fn_801695E0(1, 0x153E, 0, lbl_806DB180, lbl_806DB17C, alpha);
        fn_801695E0(1, 0x153F, 0, lbl_806DB09C, lbl_806DB184, alpha);
    }
}

void TimeAttackResult::Destroy() {
    delete this;
}

extern "C" TimeAttackResult *fn_8021E0C0(void) {
    return new TimeAttackResult;
}

CoinContinue::~CoinContinue() {
    SetInput(0);
    objs.DeleteAll();
}

void CoinContinue::Draw() {
    for (FadeObj **it = objs.begin(); it != objs.end(); it++) {
        (*it)->Render();
    }
    fn_8023CD54(prompt.p);
    fn_8016039C(detail.p);
}

void CoinContinue::Update() {
    switch (state) {
    case 0:
        if (detail.p->IsOpen() == 1) {
            state = 1;
        }
        break;
    case 1:
        Select();
        break;
    case 2:
        if (detail.p->state == 6) {
            fn_8020AAD4(ItemDisplay_GetOrCreate());
            FadeObj *o = *(FadeObj **)fn_80146000(&objs, 0);
            o->tracks[0].Set(lbl_806DB07C, lbl_806DB074, lbl_806DB0F4);
            o = *(FadeObj **)fn_80146000(&objs, 1);
            o->tracks[0].Set(lbl_806DB07C, lbl_806DB074, lbl_806DB0F4);
            state = 3;
        }
        break;
    case 3:
        break;
    }
    fn_80232284(ItemMsg_Get(), timer);
    if (state != 1) {
        fn_80160588(detail.p, 0, 0);
    }
    fn_8023CDA8(prompt.p);
    for (FadeObj **it = objs.begin(); it != objs.end(); it++) {
        (*it)->Tick();
    }
}

void CoinContinue::Select() {
    int dir = GetInput()->dir;
    fn_80160588(detail.p, dir, GetInput()->held == 1);
    timer -= lbl_806DB0F8;
    if (timer < lbl_806DB074) {
        timer = lbl_806DB074;
    }
    if (timer <= lbl_806DB074) {
        fn_801618CC(detail.p, 1, 0);
        fn_80161888(detail.p);
        state = 2;
    }
    if (detail.p->Choice() == 1) {
        fn_8018B248();
        state = 2;
    } else if (detail.p->Choice() == 0) {
        g_playerData.last = lbl_80679C88;
        state = 2;
    }
    if (state == 2) {
        fn_8023CFC8(prompt.p);
        timer = lbl_806DB078;
    }
}

CoinContinue::CoinContinue()
    : state(0), timer(lbl_806DB0FC), detail(new CoinPopupDetail(0, 1, 0xB)), prompt(new CoinPrompt(0x74, 0x4A, 0x1874, 0x1875, 5)) {
    SetInput(1);
    detail.p->SetRect(lbl_806DB100, lbl_806DB104, lbl_806DB108, lbl_806DB104);
    ItemDisplay_Start(ItemDisplay_GetOrCreate(), 0x1AE8);
    fn_8023CD3C(prompt.p, lbl_806DB110, lbl_806DB090);
    fn_8023CCF8(prompt.p, lbl_806DB0CC, lbl_806DB098);
    fn_8023CD24(prompt.p, lbl_806DB114, lbl_806DB098);
    fn_8023CCCC(prompt.p, lbl_806DB0C8, lbl_806DB098);
    fn_8023CEB4(prompt.p);
    fn_8023CFD4(prompt.p);
    FadeObj *o = new FadeText((const unsigned short *)GetTextureByIdAndLang(0x75, -1), lbl_806DB118);
    o->tracks[0].Set(lbl_806DB074, lbl_806DB07C, lbl_806DB0F4);
    ((FadeText *)o)->layer = 5;
    ((FadeText *)o)->scale = lbl_806DB11C;
    ((FadeText *)o)->SetSpacing(lbl_806DB120);
    PtrVec_InsertFill(&objs, objs.end(), 1, &o);
    o = new FadeText((const char *)fn_8018B300(), lbl_806DB124);
    o->tracks[0].Set(lbl_806DB074, lbl_806DB07C, lbl_806DB0F4);
    ((FadeText *)o)->layer = 5;
    ((FadeText *)o)->scale = lbl_806DB11C;
    ((FadeText *)o)->SetSpacing(lbl_806DB120);
    PtrVec_InsertFill(&objs, objs.end(), 1, &o);
    TextSprite tmp;
    tmp.visible = 1;
    TexMgr_SetTexture(&tmp, (const char *)GetTextureByIdAndLang(0x75, -1));
    TexMgr_Apply(&tmp);
    TexMgr_SetTexture(&tmp, (const char *)fn_8018B300());
    TexMgr_Apply(&tmp);
}
