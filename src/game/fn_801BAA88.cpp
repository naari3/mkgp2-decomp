/*
 * 0x801BAA88..0x801C1F88: clFlowCard, the card flow that runs after
 * credits go in: it reads (or cleans) the player's magnetic card, offers
 * the "insert card / play without card" choice, prints a new card and
 * shows card reader errors.  Each step is its own small scene object
 * owned by the flow; they share the nsMenuUtil fade nodes for the
 * captions.
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
    bool IsHeld() { return held == 1; }
};

struct ResCtrl {
    int resId;
    int field4, mode, fieldc;
    unsigned char flag;
    float x, y, z, width, height, field28, scaleX, scaleY;
    unsigned int colors[4];
    bool flipX;
    bool flipY;
    int t0, t1, t2, t3;
    ResCtrl();
    ~ResCtrl() {}
    void SetSize(float w, float h) {
        width = w;
        height = h;
    }
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
};

template <class T> struct Own {
    T *p;
    Own(T *q) throw() : p(q) {}
    ~Own() throw() { delete p; }
    T *operator->() const throw() { return p; }
};

/* Same as Own, but its destructor is never inlined. */
template <class T> struct OwnX {
    T *p;
    OwnX(T *q) throw() : p(q) {}
    ~OwnX() throw();
    T *operator->() const throw() { return p; }
};

template <class T> OwnX<T>::~OwnX() throw() {
    delete p;
}

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

/* 0x8C-byte two-button yes/no panel (ctor fn_80161914, dtor fn_80161F28). */
struct ChoicePanel {
    int x0;
    PtrVec<Sprite *> buttons;
    int state;
    int x14;
    int result;
    float ax, ay, bx, by;
    char pad2C[0x50 - 0x2C];
    PtrVec<TextSprite *> labels;
    int x5C;
    Sprite *cursor;
    int x64;
    int x68;
    float labelOfs[4][2];
    ChoicePanel(int a, int b, int c);
    ~ChoicePanel();
    int Choice() {
        if (state < 2) {
            return 2;
        }
        return result;
    }
    bool IsOpen() { return state == 1 ? true : false; }
    void SetCursor(float x, float y) {
        cursor->x = x;
        cursor->y = y;
    }
    void SetButton(int i, float x, float y) {
        Sprite *s = buttons.at(i);
        s->x = x;
        s->y = y;
    }
};

/* 0x68-byte message window (ctor fn_801DA06C, dtor fn_801D9F88). */
struct MsgWindow {
    int busy;
    int kind;
    char pad08[0x18];
    unsigned char open;
    unsigned char shown;
    char pad22[0x68 - 0x22];
    MsgWindow();
    ~MsgWindow();
};

/* 0x10-byte credit counter (ctor fn_8024E2A4, dtor fn_8024E244). */
struct CreditView {
    int x0;
    int x4;
    unsigned char ready;
    char pad09[7];
    CreditView(int mode);
    ~CreditView();
};

/* 0x5C-byte screen fader (ctor fn_802325FC, dtor fn_80232550). */
struct Fader {
    char pad[0x5C];
    Fader();
    ~Fader();
};

extern "C" {
extern InputState *g_pInputState;
extern Fader *lbl_806D1A88;
extern const float lbl_806D9A24;
extern const float lbl_806D9A28;
extern const float lbl_806D9A2C;
extern const float lbl_806D9A30;
extern const float lbl_806D9A34;
extern const float lbl_806D9A38;
extern const float lbl_806D9A3C;
extern const float lbl_806D9A40;
extern const float lbl_806D9A68;
extern const float lbl_806D9A70;
extern const float lbl_806D9A74;
extern const float lbl_806D9A78;
extern const float lbl_806D9AB0;
extern const float lbl_806D9AB8;
extern const float lbl_806D9ABC;
extern const float lbl_806D9AC0;
extern const float lbl_806D9AC4;
extern const float lbl_806D9AC8;
extern const float lbl_806D9ACC;
extern const float lbl_806D9AD4;
extern const float lbl_806D9AD8;
extern const float lbl_806D9ADC;
extern const float lbl_806D9AE0;
extern const float lbl_806D9AE8;
extern const float lbl_806D9AEC;
extern const float lbl_806D9A0C[2];
extern const float lbl_806D9A14[2];
extern const float lbl_806D9A1C[2];
extern char lbl_8039A33C[];
extern const char lbl_806D9A44[4];
extern char lbl_80399870[];
extern char lbl_805D275C[];
extern unsigned char g_playerData[];

void DebugPrintf(const char *fmt, ...);
int isJapanese(void);
void SetScreenBrightness(float b);
void fn_8011FAB8(void);
void fn_8011FAFC(ResCtrl *r, int layer);
void fn_801A0004(Sprite *s);
unsigned char Sprite_AdvanceAnim(Sprite *s, float step);
void *fn_801F8E58(void);
void fn_801F8A34(void *mgr, void *t, int layer);
void fn_801F8E90(void *t);
void fn_801F8FCC(void *t, int mode);
void fn_801F9014(void *t, const char *s, ...);
void fn_801F93D0(void *t, float sx, float sy);
void fn_801F93EC(void *t, float x, float y);
void TexMgr_SetTexture(void *t, const char *s, ...);
const char *GetTextureByIdAndLang(int id, int lang);

void fn_80160588(ChoicePanel *p, int dir, bool press);
void fn_8016039C(ChoicePanel *p);
void fn_80161888(ChoicePanel *p);
void fn_801618CC(ChoicePanel *p, int a, int b);
void fn_801D9180(MsgWindow *w, int a);
void clFlowKart_SetupTextLayout(MsgWindow *w, int kind);
void fn_801D919C(MsgWindow *w);
void fn_801D9A2C(MsgWindow *w);
void fn_801D9B70(MsgWindow *w, bool held);
void fn_8024E05C(CreditView *v);
void fn_8024E094(CreditView *v);
void fn_8024E1DC(CreditView *v);
void fn_802321F8(Fader *f);
void fn_80232284(Fader *f, float b);
void *ItemDisplay_GetOrCreate(void);
void fn_8020AAD4(void *d);
void fn_8020AC34(void *d);
void ItemDisplay_Update(void *d);
void ItemDisplay_Start(void *d, int id);

void SetRumbleMode(int a, int b, int c);
void fn_801699D8(int a, int b);
void fn_801B87D8(void);
void fn_801B8918(int id);
void fn_801D7610(void *p, int a);
unsigned char fn_801D6F30(void *pd, int id, int a);
void PlayerData_ResetForFlow(void);
void PlayStats_IncVs4PJoin(void);
unsigned char ServiceValue_Get(void);
unsigned char ServiceEnable_Get(void);

unsigned char card_eject_state_machine(void);
void card_eject_init(void);
unsigned char card_rw_kick_state_machine(void);
int Sci2Card_GetPrintErrorCode(void);
unsigned char Sci2Card_GetByteFlag1224(void);
unsigned char Sci2Card_GetReceiptTestFlag(void);
int Sci2Card_GetUnpackStatusCode(void);
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

static inline Fader *GetFader() {
    return lbl_806D1A88 ? lbl_806D1A88 : (lbl_806D1A88 = new Fader);
}

struct FadeTrack {
    unsigned char active;
    float from;
    float to;
    float speed;
    float t;
    float value;
    FadeTrack() : speed(lbl_806D9A74), t(lbl_806D9A74) {}
    void Set(float f, float e, float s) {
        from = f;
        to = e;
        speed = s;
        t = lbl_806D9A74;
        value = f;
        active = 1;
    }
    void Step() {
        if (active == 1) {
            value = from * (lbl_806D9A34 - t) + to * t;
            t += speed;
            if (t > lbl_806D9A34) {
                t = lbl_806D9A34;
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
    FadeObj(Sprite *s, int d) : sprite(s), delay(d) {
        shown = 0;
        flush = 0;
        tracks[0].active = 0;
        tracks[1].active = 0;
        tracks[2].active = 0;
        tracks[3].active = 0;
        tracks[4].active = 0;
    }
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
                Sprite_AdvanceAnim(sprite, lbl_806D9A70);
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

/* A caption line: a fade node drawing one text sprite. */
struct TextNode : FadeObj {
    TextSprite text;
    int layer;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    float scale;
    TextNode(float x, float y, const char *s) {
        tracks[3].Set(x, x, lbl_806D9A34);
        tracks[4].Set(y, y, lbl_806D9A34);
        text.visible = 1;
        fn_801F8FCC(&text, 1);
        fn_801F9014(&text, s);
        fn_801F8E90(&text);
        r = 0xFF;
        g = 0xFF;
        b = 0xFF;
        scale = lbl_806D9A34;
        layer = 7;
    }
    ~TextNode() {}
    void Draw();
};

/* The card reader error screen: a dimmed backdrop, the error caption
 * and the "E<code>" line. */
#define DRAW_CARD_ERROR(TEX, CODE, COND)                                \
    {                                                                   \
        ResCtrl rc;                                                     \
        rc.mode = 2;                                                    \
        rc.SetSize(lbl_806D9A24, lbl_806D9A28);                         \
        rc.Show(lbl_806D9A2C, lbl_806D9A30, lbl_806D9A34);              \
        rc.SetColor(0xFF);                                              \
        fn_8011FAFC(&rc, 6);                                            \
        TextSprite t;                                                   \
        fn_801F8FCC(&t, 1);                                             \
        t.visible = 1;                                                  \
        t.spacing = lbl_806D9A38;                                       \
        t.color = 0xFFFFFFFF;                                           \
        fn_801F93EC(&t, lbl_806D9A2C, lbl_806D9A30);                    \
        TexMgr_SetTexture(&t, GetTextureByIdAndLang(0x99, -1));         \
        fn_801F8E90(&t);                                                \
        fn_801F8A34(fn_801F8E58(), &t, 7);                              \
        fn_801F93EC(&t, lbl_806D9A2C, lbl_806D9A3C);                    \
        TexMgr_SetTexture(&t, TEX);                                     \
        fn_801F8E90(&t);                                                \
        fn_801F8A34(fn_801F8E58(), &t, 7);                              \
        if (COND) {                                                     \
            fn_801F93EC(&t, lbl_806D9A2C, lbl_806D9A40);                \
            TexMgr_SetTexture(&t, lbl_806D9A44, CODE);                         \
            fn_801F8E90(&t);                                            \
            fn_801F8A34(fn_801F8E58(), &t, 7);                          \
        }                                                               \
    }

/* 0x30: "insert your card" step (main flow +0x24). */
struct CardEntry {
    int state;
    float bright;
    Own<MsgWindow> msg;
    OwnX<ChoicePanel> panel;
    Own<CreditView> credit;
    PtrVec<FadeObj *> nodes;
    unsigned char ok;
    unsigned char withItems;
    int errCode;
    const char *errTex;
    unsigned char x2C;
    CardEntry(unsigned char withItems);
    ~CardEntry();
    bool IsDone() { return state == 5 ? true : false; }
    void SetError(int code, int tex) {
        errCode = code;
        errTex = GetTextureByIdAndLang(tex, -1);
        state = 7;
    }
};

extern "C" {
void fn_801BBAF0(CardEntry *self);
void fn_801BBDD4(CardEntry *self);
void fn_801BBF24(CardEntry *self);
void fn_801BBFD4(CardEntry *self);
void fn_801BC018(CardEntry *self);
void fn_801BC1E4(CardEntry *self);
}

extern "C" void fn_801BB6D4(CardEntry *self) {
    if (self->state == 7) {
        DRAW_CARD_ERROR(self->errTex, self->errCode, self->errCode != 0)
    } else {
        fn_8016039C(self->panel.p);
        fn_801D9A2C(self->msg.p);
        fn_8024E05C(self->credit.p);
        for (FadeObj **it = self->nodes.begin(); it != self->nodes.end(); it++) {
            (*it)->Render();
        }
        if (self->withItems == 1) {
            fn_802321F8(GetFader());
            fn_8020AC34(ItemDisplay_GetOrCreate());
        }
    }
}

CardEntry::~CardEntry() {
    if (withItems == 0) {
        fn_801B87D8();
        SetScreenBrightness(lbl_806D9AB0);
    } else {
        fn_8020AAD4(ItemDisplay_GetOrCreate());
        fn_80232284(GetFader(), lbl_806D9AB0);
    }
    SetInput(0);
    for (FadeObj **it = nodes.begin(); it != nodes.end(); it++) {
        delete *it;
    }
    if (!Sci2Card_GetByteFlag1224()) {
        PlayerData_ResetForFlow();
        fn_801D7610(lbl_805D275C, 1);
    }
}

extern "C" void fn_801BBAF0(CardEntry *self) {
    switch (self->state) {
    case 0:
        fn_801BC1E4(self);
        break;
    case 1:
        fn_801BC018(self);
        break;
    case 2:
        fn_801BBFD4(self);
        break;
    case 3:
        fn_801BBDD4(self);
        break;
    case 4:
        if (self->credit->ready != 0 && self->panel->state == 6 && self->msg->busy == 0) {
            self->state = 5;
        }
        break;
    case 7:
        break;
    case 6:
        if (self->msg->busy == 0) {
            PlayerData_ResetForFlow();
            self->state = 3;
            card_eject_init();
            clFlowKart_SetupTextLayout(self->msg.p, 2);
            self->msg->shown = 0;
        }
        break;
    }
    if (self->state != 1) {
        fn_80160588(self->panel.p, 0, 0);
    }
    fn_801D9B70(self->msg.p, GetInput()->held == 1);
    fn_8024E094(self->credit.p);
    if (self->withItems == 0) {
        SetScreenBrightness(self->bright);
    } else {
        fn_80232284(GetFader(), self->bright);
        ItemDisplay_Update(ItemDisplay_GetOrCreate());
    }
    for (FadeObj **it = self->nodes.begin(); it != self->nodes.end(); it++) {
        (*it)->Tick();
    }
}

static inline bool CardEntry_EjectDone(CardEntry *self) {
    switch (Sci2Card_GetPrintErrorCode()) {
    case 0x69:
        DebugPrintf(lbl_8039A33C);
        break;
    case 2:
        self->errTex = GetTextureByIdAndLang(0x9F, -1);
        self->state = 7;
        break;
    case 0x64:
    case 0x6A:
        self->SetError(0x37, 0x9C);
        break;
    case 0x68:
        self->SetError(0x35, 0x9A);
        break;
    case 0x65:
        self->SetError(0x33, 0x9B);
        break;
    case 1:
        return false;
    }
    return true;
}

extern "C" void fn_801BBDD4(CardEntry *self) {
    if (card_eject_state_machine() == 1) {
        if (!CardEntry_EjectDone(self)) {
            fn_801BBF24(self);
            self->state = 4;
        }
    }
}

extern "C" void fn_801BBF24(CardEntry *self) {
    fn_80161888(self->panel.p);
    fn_801D919C(self->msg.p);
    if (self->withItems == 0) {
        fn_801B87D8();
    } else {
        fn_8020AAD4(ItemDisplay_GetOrCreate());
    }
    for (FadeObj **it = self->nodes.begin(); it != self->nodes.end(); it++) {
        FadeObj *n = *it;
        n->tracks[0].Set(lbl_806D9A34, lbl_806D9A74, lbl_806D9AC0);
    }
    fn_801699D8(0, 0);
}

extern "C" void fn_801BBFD4(CardEntry *self) {
    if (self->msg->busy == 0) {
        fn_801BBF24(self);
        self->state = 4;
    }
}

extern "C" void fn_801BC018(CardEntry *self) {
    int dir = GetInput()->dir;
    bool press = GetInput()->held == 1;
    if (press == 1) {
        SetRumbleMode(0, 1, 1);
    }
    if (self->credit->ready == 1) {
        fn_80160588(self->panel.p, dir, press);
        self->bright -= lbl_806D9A78;
        if (self->bright < lbl_806D9A74) {
            self->bright = lbl_806D9AB0;
        }
    } else {
        fn_80160588(self->panel.p, 0, 0);
    }
    if (self->panel->Choice() == 1 || self->bright <= lbl_806D9A74) {
        PlayerData_ResetForFlow();
        fn_801618CC(self->panel.p, 1, 1);
        self->state = 3;
        card_eject_init();
        clFlowKart_SetupTextLayout(self->msg.p, 2);
        self->msg->shown = 0;
        self->ok = 0;
    } else if (self->panel->Choice() == 0) {
        PlayStats_IncVs4PJoin();
        self->state = 2;
        self->bright = lbl_806D9AB0;
        clFlowKart_SetupTextLayout(self->msg.p, 0x18);
        self->msg->shown = 1;
        self->ok = 1;
        if (self->withItems == 0) {
            g_playerData[0x1D9] = 2;
        }
    }
}

extern "C" void fn_801BC1E4(CardEntry *self) {
    if (self->panel->IsOpen() == 1) {
        if (Sci2Card_GetReceiptTestFlag() == 1 && Sci2Card_GetUnpackStatusCode() == 5) {
            fn_801618CC(self->panel.p, 1, 0);
            self->msg->shown = 1;
            clFlowKart_SetupTextLayout(self->msg.p, 7);
            self->state = 6;
            self->bright = lbl_806D9AB0;
            self->ok = 0;
        } else if (ServiceValue_Get()) {
            fn_801618CC(self->panel.p, 1, 0);
            self->msg->shown = 1;
            clFlowKart_SetupTextLayout(self->msg.p, 6);
            self->state = 6;
            self->bright = lbl_806D9AB0;
            self->ok = 0;
        } else {
            self->state = 1;
            fn_801699D8(0, 1);
        }
    }
}

CardEntry::CardEntry(unsigned char items)
    : state(0), bright(lbl_806D9AB8), msg(new MsgWindow()), panel(new ChoicePanel(0, 0, 10)),
      credit(new CreditView(3)) {
    withItems = items;
    x2C = 0;
    ChoicePanel *p = panel.p;
    p->ax = lbl_806D9AC4;
    p->ay = lbl_806D9AD4;
    p->bx = lbl_806D9AC8;
    p->by = lbl_806D9AD4;
    p->SetButton(0, p->ax, p->ay);
    p->SetButton(1, p->bx, p->by);
    fn_801F93EC(p->labels.at(0), p->ax + p->labelOfs[0][0], p->ay + p->labelOfs[0][1]);
    fn_801F93EC(p->labels.at(1), p->ax + p->labelOfs[1][0], p->ay + p->labelOfs[1][1]);
    fn_801F93EC(p->labels.at(2), p->bx + p->labelOfs[2][0], p->by + p->labelOfs[2][1]);
    fn_801F93EC(p->labels.at(3), p->bx + p->labelOfs[3][0], p->by + p->labelOfs[3][1]);
    float cx = p->ax + lbl_806D9AD8 * (p->bx - p->ax);
    float cy = p->ay + lbl_806D9AD8 * (p->by - p->ay);
    Sprite *c = p->cursor;
    c->x = cx;
    c->y = cy;
    msg->open = 1;
    if (withItems == 0) {
        fn_801B8918(0x1AD6);
        SetScreenBrightness(bright);
    } else {
        ItemDisplay_Start(ItemDisplay_GetOrCreate(), 0x1AD6);
        fn_80232284(GetFader(), bright);
    }
    SetInput(1);
    const float *pScale = &lbl_806D9A0C[isJapanese()];
    const float *pX = &lbl_806D9A14[isJapanese()];
    const float *pSp = &lbl_806D9A1C[isJapanese()];
    TextNode *n;

    n = new TextNode(*pX, lbl_806D9ADC, GetTextureByIdAndLang(0x87, -1));
    n->layer = 4;
    n->tracks[0].Set(lbl_806D9A74, lbl_806D9A34, lbl_806D9AC0);
    n->text.spacing = (int)*pSp;
    fn_801F8E90(&n->text);
    n->scale = *pScale;
    nodes.push_back(n);

    n = new TextNode(*pX, lbl_806D9AE0, GetTextureByIdAndLang(0x88, -1));
    n->layer = 4;
    n->tracks[0].Set(lbl_806D9A74, lbl_806D9A34, lbl_806D9AC0);
    n->text.spacing = (int)*pSp;
    fn_801F8E90(&n->text);
    n->scale = *pScale;
    nodes.push_back(n);

    if (isJapanese() == 1) {
        static const char *quote = "\x27";
        n = new TextNode(*pX - lbl_806D9ACC, lbl_806D9AE8, quote);
        n->layer = 4;
        n->tracks[0].Set(lbl_806D9A74, lbl_806D9A34, lbl_806D9AC0);
        n->scale = *pScale;
        nodes.push_back(n);
    }

    n = new TextNode(*pX, lbl_806D9AEC, GetTextureByIdAndLang(0x89, -1));
    n->layer = 4;
    n->tracks[0].Set(lbl_806D9A74, lbl_806D9A34, lbl_806D9AC0);
    n->text.spacing = (int)*pSp;
    fn_801F8E90(&n->text);
    n->scale = *pScale;
    nodes.push_back(n);
}

void TextNode::Draw() {
    fn_801F93EC(&text, tracks[3].value, tracks[4].value);
    if (tracks[0].active == 1) {
        text.color = PackColor(r, g, b, (int)(lbl_806D9A68 * tracks[0].value));
    }
    float sx = lbl_806D9A34;
    float sy = sx;
    if (tracks[1].active == 1) {
        sx = tracks[1].value;
    }
    if (tracks[2].active == 1) {
        sy = tracks[2].value;
    }
    fn_801F93D0(&text, sx * scale, sy * scale);
    fn_801F8A34(fn_801F8E58(), &text, layer);
}

/* 0x24: "buy a new card" step (main flow +0x20). */
struct CardBuy {
    int coins;
    int state;
    float bright;
    Own<MsgWindow> msg;
    OwnX<ChoicePanel> panel;
    Own<CreditView> credit;
    const char *errTex;
    int errCode;
    unsigned char skip;
    unsigned char rewrite;
    unsigned char kicked;
    CardBuy(unsigned char rewrite);
    ~CardBuy();
    bool IsDone() { return state == 6 ? true : false; }
    void SetError(int code, int tex) {
        errCode = code;
        errTex = GetTextureByIdAndLang(tex, -1);
        state = 8;
    }
};

extern "C" {
extern const char lbl_806D9AB4[4];
extern signed char lbl_806D184C;
int CreditMgr_GetCoinCount(int a, int b);
int CreditMgr_GetCreditCount(int slot);
void CreditMgr_SetActiveSlot(int slot);
void CreditMgr_TryConfirmPlay(int slot);
void fn_801B7CD0(int a);
void card_save_trigger(int a);
unsigned char CardSave_Tick(void);
int CardRW_GetSubState(void);
int card_rw_get_substate(void);
unsigned char card_rw_state_machine(void);
void fn_801BD1E4(CardBuy *self);
void fn_801BD32C(CardBuy *self);
void fn_801BD368(CardBuy *self);
void fn_801BD56C(CardBuy *self);
void fn_801BD744(CardBuy *self);
}

extern "C" void fn_801BCDAC(CardBuy *self) {
    if (self->state == 8) {
        DRAW_CARD_ERROR(self->errTex, self->errCode, self->errCode != 0)
    } else {
        if (self->skip == 0) {
            fn_8016039C(self->panel.p);
        }
        fn_801D9A2C(self->msg.p);
        fn_8024E05C(self->credit.p);
    }
}

CardBuy::~CardBuy() {
    fn_801B87D8();
    SetScreenBrightness(lbl_806D9AB0);
    SetInput(0);
}

extern "C" void fn_801BD038(CardBuy *self) {
    switch (self->state) {
    case 0:
        if (self->panel->IsOpen() == 1) {
            self->state = 1;
            fn_801699D8(0, 1);
        }
        break;
    case 1:
        fn_801BD744(self);
        break;
    case 2:
        fn_801BD56C(self);
        break;
    case 3:
        fn_801BD368(self);
        break;
    case 4:
        fn_801BD1E4(self);
        break;
    case 5:
        if (self->skip != 0 || (self->credit->ready != 0 && self->panel->state == 6)) {
            if (self->msg->busy == 0) {
                self->state = 6;
            }
        }
        break;
    case 6:
        break;
    case 7:
        if (self->msg->busy == 0) {
            PlayerData_ResetForFlow();
            self->msg->shown = 0;
            if (self->rewrite == 1) {
                self->state = 3;
                card_rw_kick_state_machine();
            } else {
                self->state = 4;
                card_eject_init();
                clFlowKart_SetupTextLayout(self->msg.p, 2);
            }
        }
        break;
    case 8:
        lbl_806D184C = -1;
        return;
    }
    fn_801D9B70(self->msg.p, GetInput()->held == 1);
    if (self->skip == 0) {
        if (self->state != 1) {
            fn_80160588(self->panel.p, 0, 0);
        }
        fn_8024E094(self->credit.p);
    }
    SetScreenBrightness(self->bright);
}

extern "C" void fn_801BD1E4(CardBuy *self) {
    char *s = lbl_80399870;
    if (card_eject_state_machine() == 1) {
        switch (Sci2Card_GetPrintErrorCode()) {
        case 0x69:
            DebugPrintf(s + 0xACC);
            break;
        case 2:
            DebugPrintf(s + 0xAF4);
            break;
        case 0x64:
        case 0x6A:
            self->SetError(0x37, 0x9C);
            break;
        case 0x68:
            self->SetError(0x35, 0x9A);
            break;
        case 0x65:
            self->SetError(0x33, 0x9B);
            break;
        case 1:
            DebugPrintf(s + 0xB24);
            fn_801BD32C(self);
            self->state = 5;
            break;
        }
    }
}

extern "C" void fn_801BD32C(CardBuy *self) {
    fn_80161888(self->panel.p);
    fn_801D919C(self->msg.p);
    fn_801B87D8();
}

static inline bool CardBuy_RWError(CardBuy *self) {
    switch (Sci2Card_GetPrintErrorCode()) {
    case 0x66:
        self->SetError(0x34, 0x9D);
        return true;
    case 0x68:
        self->SetError(0x35, 0x9A);
        return true;
    case 0x69:
        self->SetError(0x36, 0x9E);
        return true;
    case 0x64:
    case 0x6A:
    case 0xFF:
        self->SetError(0x37, 0x9C);
        return true;
    case 0x65:
        self->SetError(0x33, 0x9B);
        return true;
    case 1:
        return false;
    }
    return false;
}

extern "C" void fn_801BD368(CardBuy *self) {
    switch (card_rw_get_substate()) {
    case 0:
    case 1:
        if (self->msg->kind != 5) {
            fn_801D919C(self->msg.p);
            clFlowKart_SetupTextLayout(self->msg.p, 5);
        }
        break;
    case 2:
    case 3:
        if (self->msg->kind != 2) {
            fn_801D919C(self->msg.p);
            clFlowKart_SetupTextLayout(self->msg.p, 2);
        }
        break;
    }
    if (self->kicked == 0) {
        if (!card_rw_kick_state_machine()) {
            return;
        }
        self->kicked = 1;
    }
    if (card_rw_state_machine()) {
        if (!CardBuy_RWError(self)) {
            PlayerData_ResetForFlow();
            fn_801BD32C(self);
            self->state = 5;
        }
    }
}

extern "C" void fn_801BD56C(CardBuy *self) {
    char *s = lbl_80399870;
    if (CardSave_Tick() == 1) {
        switch (Sci2Card_GetPrintErrorCode()) {
        case 0x66:
            DebugPrintf(s + 0xB4C);
            break;
        case 0x69:
            DebugPrintf(s + 0xB74);
            break;
        case 2:
            self->SetError(0, 0x9F);
            break;
        case 0x64:
        case 0x6A:
            self->SetError(0x37, 0x9C);
            break;
        case 0x68:
            self->SetError(0x35, 0x9A);
            break;
        case 0x65:
            self->SetError(0x33, 0x9B);
            break;
        case 1:
            DebugPrintf(s + 0xB9C);
            fn_801BD32C(self);
            CreditMgr_TryConfirmPlay(3);
            self->state = 5;
            break;
        }
    } else if (CardRW_GetSubState() == 1) {
        if (self->msg->kind != 3) {
            fn_801D919C(self->msg.p);
            clFlowKart_SetupTextLayout(self->msg.p, 3);
            self->msg->shown = 0;
        }
    } else if (CardRW_GetSubState() == 2) {
        if (self->msg->busy != 0) {
            fn_801D919C(self->msg.p);
        }
    }
}

extern "C" void fn_801BD744(CardBuy *self) {
    int dir = GetInput()->dir;
    bool press = GetInput()->held == 1;
    if (press == 1) {
        SetRumbleMode(0, 1, 1);
    }
    if (self->credit->ready == 1) {
        fn_80160588(self->panel.p, dir, press);
        self->bright -= lbl_806D9A78;
        if (self->bright < lbl_806D9A74) {
            self->bright = lbl_806D9A74;
        }
    } else {
        fn_80160588(self->panel.p, 0, 0);
    }
    int coins = CreditMgr_GetCoinCount(0, -1);
    if (self->coins != coins) {
        self->bright = lbl_806D9AB8;
    }
    self->coins = coins;
    if (self->panel->Choice() == 1 || self->bright <= lbl_806D9A74) {
        fn_801618CC(self->panel.p, 1, 1);
        fn_801699D8(0, 0);
        self->msg->shown = 0;
        if (self->rewrite == 1) {
            self->state = 3;
            clFlowKart_SetupTextLayout(self->msg.p, 5);
        } else {
            PlayerData_ResetForFlow();
            self->state = 4;
            card_eject_init();
            clFlowKart_SetupTextLayout(self->msg.p, 2);
        }
    } else if (self->panel->Choice() == 0) {
        if (CreditMgr_GetCreditCount(3) > 0) {
            fn_8024E1DC(self->credit.p);
            self->panel->state = 1;
            if (GetInput()) {
                SetInput(1);
            }
        } else {
            self->state = 2;
            self->bright = lbl_806D9AB0;
            card_save_trigger(1);
            clFlowKart_SetupTextLayout(self->msg.p, 10);
            self->msg->shown = 0;
            fn_801699D8(0, 0);
        }
    }
}

CardBuy::CardBuy(unsigned char rw)
    : coins(CreditMgr_GetCoinCount(0, -1)), state(0), bright(lbl_806D9AB8), msg(new MsgWindow()),
      panel(new ChoicePanel(0, 0, 5)), credit(new CreditView(3)), errTex(lbl_806D9AB4), errCode(0) {
    skip = 0;
    rewrite = rw;
    kicked = 0;
    msg->open = 1;
    CreditMgr_SetActiveSlot(3);
    fn_801B7CD0(-1);
    fn_801B7CD0(3);
    if (ServiceValue_Get()) {
        msg->shown = 1;
        clFlowKart_SetupTextLayout(msg.p, 6);
        state = 7;
        bright = lbl_806D9AB0;
        skip = 1;
    } else if (Sci2Card_GetReceiptTestFlag() == 1) {
        msg->shown = 1;
        clFlowKart_SetupTextLayout(msg.p, 7);
        state = 7;
        bright = lbl_806D9AB0;
        skip = 1;
    } else {
        fn_801B8918(0x1AD6);
        SetScreenBrightness(lbl_806D9AB8);
    }
    SetInput(1);
}

/* 0x20: "insert coins" step (main flow +0x10). */
struct CoinWait {
    OwnX<ChoicePanel> panel;
    int state;
    float bright;
    int coins;
    const char *errTex;
    int errCode;
    Own<CreditView> credit;
    Own<MsgWindow> msg;
    CoinWait();
    ~CoinWait();
    bool IsDone() { return state == 5 ? true : false; }
    void SetError(int code, int tex) {
        errCode = code;
        errTex = GetTextureByIdAndLang(tex, -1);
        state = 8;
    }
};

extern "C" {
extern int g_gameMode;
void *GetInputManager(void);
void *InputMgr_GetPlayer(void *mgr, int idx);
void fn_801C03D0(CoinWait *self);
void fn_801C043C(CoinWait *self);
void fn_801C0568(CoinWait *self);
void fn_801C07C8(CoinWait *self);
void fn_801C0824(CoinWait *self);
}

extern "C" void fn_801C0060(CoinWait *self) {
    if (self->state == 8) {
        DRAW_CARD_ERROR(self->errTex, self->errCode, self->errCode != 0)
    } else {
        if (self->state != 7) {
            fn_8016039C(self->panel.p);
        }
        fn_801D9A2C(self->msg.p);
        fn_8024E05C(self->credit.p);
    }
}

CoinWait::~CoinWait() {
    SetScreenBrightness(lbl_806D9AB0);
}

extern "C" void fn_801C03B0(CoinWait *self);

extern "C" void fn_801C02C4(CoinWait *self) {
    switch (self->state) {
    case 0:
        fn_801C07C8(self);
        break;
    case 1:
        fn_801C0568(self);
        break;
    case 2:
        fn_801C043C(self);
        break;
    case 3:
        fn_801C03B0(self);
        break;
    case 4:
        if (self->panel->state == 6) {
            self->state = 5;
        }
        break;
    case 6:
        if (self->credit->ready == 1) {
            self->state = 1;
        }
        break;
    case 7:
        if (self->msg->busy == 0) {
            self->state = 5;
        }
        break;
    case 5:
    case 8:
        break;
    }
    if (self->state != 1) {
        fn_80160588(self->panel.p, 0, 0);
    }
    fn_801D9B70(self->msg.p, 0);
    fn_8024E094(self->credit.p);
}

extern "C" void fn_801C03B0(CoinWait *self) {
    fn_801C03D0(self);
}

extern "C" void fn_801C03D0(CoinWait *self) {
    self->state = 4;
    fn_80161888(self->panel.p);
    if (self->msg->busy != 0) {
        fn_801D919C(self->msg.p);
    }
    self->bright = lbl_806D9AB0;
    fn_801B87D8();
    SetScreenBrightness(lbl_806D9AB0);
    fn_801699D8(0, 0);
}

extern "C" void fn_801C043C(CoinWait *self) {
    if (CardSave_Tick()) {
        switch (Sci2Card_GetPrintErrorCode()) {
        case 1:
            fn_801C03D0(self);
            CreditMgr_TryConfirmPlay(2);
            break;
        case 2:
            self->SetError(0, 0x9F);
            break;
        case 0x64:
        case 0x6A:
            self->SetError(0x37, 0x9C);
            break;
        case 0x68:
            self->SetError(0x35, 0x9A);
            break;
        case 0x65:
            self->SetError(0x33, 0x9B);
            break;
        case 0x69:
            break;
        }
    }
}

extern "C" void fn_801C0568(CoinWait *self) {
    InputState *in = GetInput();
    InputMgr_GetPlayer(GetInputManager(), 0);
    unsigned char press = in->held == 1;
    fn_80160588(self->panel.p, in->dir, press);
    if (press == 1) {
        SetRumbleMode(0, 1, 1);
    }
    int coins = CreditMgr_GetCoinCount(0, -1);
    if (self->coins != coins) {
        self->bright = lbl_806D9AB8;
    }
    self->coins = coins;
    if (self->panel->Choice() == 1) {
        fn_801C03D0(self);
    } else if (self->panel->Choice() == 0) {
        if (CreditMgr_GetCreditCount(2) > 0) {
            fn_8024E1DC(self->credit.p);
            self->state = 6;
            self->panel->state = 1;
            if (GetInput()) {
                SetInput(1);
            }
        } else {
            card_save_trigger(0);
            self->state = 2;
            self->bright = lbl_806D9AB0;
            SetScreenBrightness(lbl_806D9AB0);
            if (fn_801D6F30(g_playerData, 0x33, 0) == 1 || fn_801D6F30(g_playerData, 0x3A, 0) == 1 ||
                fn_801D6F30(g_playerData, 0x3F, 0) == 1) {
                clFlowKart_SetupTextLayout(self->msg.p, 1);
            } else {
                clFlowKart_SetupTextLayout(self->msg.p, 0);
            }
            return;
        }
    }
    self->bright -= lbl_806D9A78;
    if (self->bright < lbl_806D9A74) {
        self->bright = lbl_806D9ABC;
    }
    SetScreenBrightness(self->bright);
    if (self->bright <= lbl_806D9A74) {
        fn_801618CC(self->panel.p, 1, 1);
        fn_801C03D0(self);
    }
}

extern "C" void fn_801C07C8(CoinWait *self) {
    if (self->panel->state == 1) {
        if (Sci2Card_GetReceiptTestFlag() == 1) {
            fn_801C0824(self);
        } else {
            self->state = 1;
        }
    }
}

extern "C" void fn_801C0824(CoinWait *self) {
    self->state = 7;
    self->bright = lbl_806D9AB0;
    clFlowKart_SetupTextLayout(self->msg.p, 7);
    self->msg->shown = 1;
    fn_801618CC(self->panel.p, 1, 0);
    fn_80161888(self->panel.p);
}

CoinWait::CoinWait()
    : panel(new ChoicePanel(1, 0, 4)), state(1), bright(lbl_806D9AB8), coins(CreditMgr_GetCoinCount(0, -1)),
      errTex(lbl_806D9AB4), errCode(0), credit(new CreditView(2)), msg(new MsgWindow()) {
    msg->open = 1;
    fn_801D9180(msg.p, 5);
    CreditMgr_SetActiveSlot(2);
    fn_801B7CD0(-1);
    fn_801B7CD0(2);
    if (ServiceValue_Get()) {
        msg->shown = 1;
        clFlowKart_SetupTextLayout(msg.p, 6);
        state = 7;
        bright = lbl_806D9AB0;
    } else if (Sci2Card_GetReceiptTestFlag() == 1) {
        msg->shown = 1;
        clFlowKart_SetupTextLayout(msg.p, 7);
        state = 7;
        bright = lbl_806D9AB0;
    } else {
        msg->shown = 0;
        fn_801B8918(0x1AD5);
    }
    fn_801699D8(0, 1);
}

/* 0x30: card check / cleaning / read step (main flow +0x0C). */
struct CardRead {
    unsigned char mode;
    OwnX<ChoicePanel> panel;
    int state;
    int retries;
    float bright;
    Own<MsgWindow> msg;
    int next;
    unsigned char newCard;
    unsigned char readOk;
    unsigned char prompted;
    unsigned char skip;
    unsigned char pinged;
    const char *errTex;
    int errCode;
    int pingFails;
    CardRead(unsigned char mode);
    ~CardRead();
    bool IsDone() { return state == 7 ? true : false; }
    void SetError(int code, int tex) {
        errCode = code;
        errTex = GetTextureByIdAndLang(tex, -1);
        state = 10;
    }
    void Eject(int text) {
        state = 5;
        if (msg->busy == 0) {
            fn_801D919C(msg.p);
        }
        clFlowKart_SetupTextLayout(msg.p, text);
        card_eject_init();
    }
};

extern "C" {
extern unsigned char lbl_806D12AD;
unsigned char card_cleaning_state_machine(void);
void card_send_cleaning_cmd_init(void);
void card_send_ping_cmd_init(void);
void card_send_read_cmd_init(void);
unsigned char card_ping_state_machine(void);
unsigned char card_read_tick(void);
unsigned char Sci2Card_WaitPingStatus(void);
void Sci2Card_ResetRetryAndStatus(void);
void Sci2Card_BeginSpace(void);
void *Sci2Card_Singleton_Get(void);
unsigned char Sci2Card_IsStatus1OneTwoThree(void *c);
void fn_801C0D64(CardRead *self);
void fn_801C0D94(CardRead *self);
void fn_801C0DF4(CardRead *self);
unsigned char fn_801C0F20(CardRead *self);
void fn_801C0FA8(CardRead *self);
void fn_801C10F0(CardRead *self);
void fn_801C1268(CardRead *self);
void fn_801C14A0(CardRead *self);
}

extern "C" void fn_801C0A0C(CardRead *self) {
    if (self->state == 10) {
        DRAW_CARD_ERROR(self->errTex, self->errCode, 1)
    } else {
        fn_8016039C(self->panel.p);
        fn_801D9A2C(self->msg.p);
    }
}

CardRead::~CardRead() {
    SetScreenBrightness(lbl_806D9AB0);
}

extern "C" void fn_801C0C30(CardRead *self) {
    switch (self->state) {
    case 0:
        card_cleaning_state_machine();
        if (self->panel->state == 1) {
            self->state = 1;
            fn_801699D8(0, 1);
        }
        break;
    case 1:
        fn_801C14A0(self);
        break;
    case 2:
        fn_801C1268(self);
        break;
    case 4:
        fn_801C10F0(self);
        break;
    case 3:
        fn_801C0FA8(self);
        break;
    case 5:
        fn_801C0DF4(self);
        break;
    case 6:
        if (self->panel->state == 6) {
            self->state = 7;
        }
        break;
    case 8:
        fn_801C0D64(self);
        break;
    case 9:
        if (self->msg->busy == 0) {
            self->state = self->next;
        }
        break;
    case 7:
    case 10:
        break;
    }
    if (self->skip == 0 && self->state != 1) {
        fn_80160588(self->panel.p, 0, 0);
    }
    fn_801D9B70(self->msg.p, GetInput()->held == 1);
    SetScreenBrightness(self->bright);
}

extern "C" void fn_801C0D64(CardRead *self) {
    if (self->msg->busy == 0) {
        fn_801C0D94(self);
    }
}

extern "C" void fn_801C0D94(CardRead *self) {
    self->bright = lbl_806D9AB0;
    SetScreenBrightness(lbl_806D9AB0);
    self->state = 6;
    fn_80161888(self->panel.p);
    if (lbl_806D12AD == 0) {
        fn_801B87D8();
    }
    fn_801699D8(0, 0);
}

extern "C" void fn_801C0DF4(CardRead *self) {
    if (self->msg->kind != 2 && self->msg->busy == 0) {
        clFlowKart_SetupTextLayout(self->msg.p, 2);
        self->msg->shown = 0;
    }
    if (card_eject_state_machine()) {
        switch (Sci2Card_GetPrintErrorCode()) {
        case 1:
            if (!fn_801C0F20(self)) {
                card_send_cleaning_cmd_init();
                fn_801D919C(self->msg.p);
                self->msg->shown = 1;
                self->state = 1;
                self->bright = lbl_806D9AB8;
            }
            break;
        case 7:
            if (!fn_801C0F20(self)) {
                card_eject_init();
            }
            break;
        case 0x64:
            self->SetError(0x37, 0x9C);
            break;
        case 0x68:
            self->SetError(0x35, 0x9A);
            break;
        }
    }
}

extern "C" unsigned char fn_801C0F20(CardRead *self) {
    self->retries--;
    Sci2Card_ResetRetryAndStatus();
    if (self->retries <= 0) {
        self->state = 8;
        if (self->msg->busy != 0) {
            fn_801D919C(self->msg.p);
        }
        clFlowKart_SetupTextLayout(self->msg.p, 0x19);
        fn_801618CC(self->panel.p, 1, 0);
        return 1;
    }
    return 0;
}

extern "C" void fn_801C0FA8(CardRead *self) {
    if (card_cleaning_state_machine()) {
        switch (Sci2Card_GetPrintErrorCode()) {
        case 6:
        case 0x64:
            self->pinged = 0;
            card_send_ping_cmd_init();
            self->state = 4;
            break;
        case 0x68:
            self->SetError(0x35, 0x9A);
            break;
        case 0x65:
            self->SetError(0x33, 0x9B);
            break;
        case 0x6A:
            self->SetError(0x37, 0x9C);
            break;
        case 0x69:
        default:
            if (Sci2Card_GetByteFlag1224() == 1) {
                fn_801618CC(self->panel.p, 0, 0);
                self->state = 2;
                card_send_read_cmd_init();
            } else {
                self->pinged = 0;
                card_send_ping_cmd_init();
                self->state = 4;
            }
            break;
        }
    }
}

extern "C" void fn_801C10F0(CardRead *self) {
    if (self->pinged == 0) {
        if (!card_ping_state_machine()) {
            return;
        }
    } else if (!Sci2Card_WaitPingStatus()) {
        return;
    }
    if (Sci2Card_GetPrintErrorCode() >= 0x65) {
        if (!fn_801C0F20(self)) {
            card_send_ping_cmd_init();
        }
        return;
    }
    switch (Sci2Card_GetPrintErrorCode()) {
    case 6:
    case 0x64:
        if (++self->pingFails >= 3) {
            self->SetError(0x37, 0x9C);
        } else {
            Sci2Card_ResetRetryAndStatus();
            card_send_cleaning_cmd_init();
            self->state = 3;
        }
        break;
    case 1:
        if (Sci2Card_GetByteFlag1224() == 1 || Sci2Card_IsStatus1OneTwoThree(Sci2Card_Singleton_Get()) == 1) {
            fn_801618CC(self->panel.p, 0, 0);
            self->state = 2;
            Sci2Card_ResetRetryAndStatus();
            card_send_read_cmd_init();
        } else if (self->pinged == 0) {
            self->pinged = 1;
            Sci2Card_BeginSpace();
        } else {
            fn_801C0D94(self);
        }
        break;
    default:
        fn_801618CC(self->panel.p, 0, 0);
        Sci2Card_ResetRetryAndStatus();
        card_send_read_cmd_init();
        self->state = 2;
        break;
    }
}

extern "C" void fn_801C1268(CardRead *self) {
    if (card_read_tick()) {
        switch (Sci2Card_GetPrintErrorCode()) {
        case 1:
        case 3:
            switch (Sci2Card_GetUnpackStatusCode()) {
            case 1:
            case 2:
            case 4:
                if ((signed char)g_playerData[0x1D9] != 2) {
                    self->readOk = 1;
                }
                fn_801618CC(self->panel.p, 0, 0);
                fn_801C0D94(self);
                break;
            case 6:
                PlayerData_ResetForFlow();
                self->Eject(0x11);
                break;
            case 5:
                if ((signed char)g_playerData[0x1D9] != 2) {
                    self->readOk = 1;
                }
                fn_801C0D94(self);
                self->newCard = 1;
                self->state = 6;
                break;
            default:
                self->Eject(0x12);
                break;
            }
            break;
        case 0x67:
            self->Eject(0x15);
            break;
        case 4:
            self->Eject(0x10);
            break;
        case 5:
            self->Eject(0x13);
            break;
        case 2:
        default:
            self->Eject(0x14);
            break;
        }
    }
}

extern "C" void fn_801C14A0(CardRead *self) {
    if (card_cleaning_state_machine() == 1) {
        switch (Sci2Card_GetPrintErrorCode()) {
        case 6:
            card_send_cleaning_cmd_init();
            break;
        case 0x64:
            if (!fn_801C0F20(self)) {
                card_send_cleaning_cmd_init();
                break;
            }
            return;
        case 0x68:
            self->SetError(0x35, 0x9A);
            return;
        case 0x65:
            self->SetError(0x33, 0x9B);
            return;
        case 0x6A:
            self->SetError(0x37, 0x9C);
            return;
        case 0x69:
        default:
            if (Sci2Card_GetByteFlag1224() == 1) {
                fn_801618CC(self->panel.p, 0, 0);
                self->state = 2;
                fn_801D919C(self->msg.p);
                card_send_read_cmd_init();
            } else {
                card_send_cleaning_cmd_init();
            }
            break;
        }
    }
    InputState *in = GetInput();
    int dir = in->dir;
    bool press = in->held == 1;
    if (Sci2Card_GetByteFlag1224() == 1) {
        dir = 0;
        press = 0;
        fn_801618CC(self->panel.p, 0, 0);
    }
    if (self->msg->busy == 0) {
        fn_80160588(self->panel.p, dir, press);
        self->bright -= lbl_806D9A78;
        if (self->bright < lbl_806D9A74) {
            self->bright = lbl_806D9AB0;
        }
        if (press == 1) {
            SetRumbleMode(0, 1, 1);
        }
    } else {
        fn_80160588(self->panel.p, 0, 0);
    }
    if (self->panel->Choice() == 1 || self->bright <= lbl_806D9A74) {
        fn_801618CC(self->panel.p, 1, 1);
        self->state = 3;
        return;
    }
    if (self->panel->Choice() == 0 && !Sci2Card_GetByteFlag1224()) {
        self->panel->state = 1;
        if (GetInput()) {
            SetInput(1);
        }
        if (self->bright > lbl_806D9A74 && self->msg->busy == 0) {
            clFlowKart_SetupTextLayout(self->msg.p, 4);
            SetInput(1);
            if (self->prompted == 0) {
                self->prompted = 1;
                self->bright = lbl_806D9AB8;
            }
        }
    }
}

CardRead::CardRead(unsigned char m)
    : mode(m), panel(new ChoicePanel(1, 0, 1)), state(0), retries(g_gameMode == 2 ? 2 : 3), bright(lbl_806D9AB8),
      msg(new MsgWindow()) {
    newCard = 0;
    readOk = 0;
    prompted = 0;
    skip = 0;
    pinged = 0;
    errTex = lbl_806D9AB4;
    errCode = 0;
    pingFails = 0;
    msg->open = 1;
    fn_801D9180(msg.p, 5);
    if (ServiceValue_Get() || !ServiceEnable_Get()) {
        msg->shown = 1;
        clFlowKart_SetupTextLayout(msg.p, 6);
        state = 9;
        bright = lbl_806D9AB0;
        next = 7;
        skip = 1;
    } else {
        fn_801B8918(0x1AD4);
        if (Sci2Card_GetByteFlag1224() == 1) {
            card_send_read_cmd_init();
            fn_801618CC(panel.p, 0, 0);
            state = 2;
        } else {
            card_send_cleaning_cmd_init();
        }
    }
}

extern "C" {
extern const float lbl_806D9A48;
extern const float lbl_806D9A98;
extern const float lbl_806D9AD0;
void fn_8019FF6C(Sprite *s, int a);
void RumbleUpdate(void);
void fn_80121210(void);
void clRom_PurgeAll(void);
void fn_80169C44(void);
void CardRegister_KickoffArm(void);
void SetSyncTarget(int t);
void InitBGM(void);
void SetupBgSprites(int a);
unsigned char IsCardValid(void);
void InitRumbleController(int a);
}

struct NameEntry;

/* --- the card flow itself --- */

struct KeyLabel {
    int res;
    int x;
    int y;
};

extern "C" int fn_801F96D0(unsigned short code);

/* One key of the name entry keyboard (0x20). */
struct NameKey {
    short x;
    short y;
    unsigned short code;
    int res;
    int lit;
    char pad10[4];
    unsigned char blink;
    unsigned char sel;
    float t;
    float t2;
    void Select() {
        lit = 1;
        blink = 0;
        sel = 1;
        t = lbl_806D9A74;
    }
    void Deselect() {
        lit = 0;
        sel = 0;
    }
    NameKey(short px, short py, unsigned short c) : x(px), y(py), code(c), res(0x2B00), lit(0) {
        blink = 1;
        sel = 0;
        t = lbl_806D9A74;
        t2 = lbl_806D9A74;
        if (code == 9) {
            res = 0x2B00;
        } else if (code == 0x8140) {
            res = 0x1912;
        } else {
            res = fn_801F96D0(code);
        }
    }
};

struct KeyTable {
    const unsigned short *chars;
    const unsigned short *marks[2];
};
extern "C" KeyTable lbl_8049A8F8[4];

/* A group of keys that light up together (0x1C). */
struct KeyGroup {
    struct {
        short x;
        short y;
        int res;
    } img[2];
    struct {
        short x;
        short y;
    } label;
    int x14;
    signed char cols[4];
    bool HasCol(int c) {
        for (int i = 0; i < 4; i++) {
            if (cols[i] == c) {
                return true;
            }
        }
        return false;
    }
};

extern "C" {
unsigned long strlen(const char *s);
char *strcpy(char *d, const char *s);
void *FUN_8003b120(unsigned long n);
void SharedPtr_Init(void *sp, void *p);
extern const char lbl_8039A484[];
extern const char lbl_8039A4EC[];
}

inline void *operator new(unsigned long, void *p) {
    return p;
}

struct ClStr {
    char *ptr;
    ClStr(const char *s) {
        SharedPtr_Init(this, FUN_8003b120(strlen(s) + 1));
        strcpy(ptr, s);
    }
    ~ClStr();
};

struct exception {
    exception() {}
    virtual ~exception();
};

struct logic_error : exception {
    ClStr msg;
    logic_error(const char *s) : msg(s) {}
    virtual ~logic_error();
};

struct length_error : logic_error {
    length_error(const char *s) : logic_error(s) {}
    virtual ~length_error();
};

struct out_of_range : logic_error {
    out_of_range(const char *s) : logic_error(s) {}
    virtual ~out_of_range();
};

template <class T> struct KeyVecBase {
    int cap;
    int count;
    T *data;
    KeyVecBase() : cap(0), count(0), data(0) {}
    ~KeyVecBase();
    void init(unsigned long n, T v);
    void clear();
    T &at(unsigned long i);
};

template <class T> void KeyVecBase<T>::init(unsigned long n, T v) {
    if (n == 0) {
        return;
    }
    if (n > 0x09249249) {
        throw length_error(lbl_8039A484);
    }
    data = (T *)operator new(n * sizeof(T));
    cap = n;
    T *end = data + n;
    T *p = data;
    for (; p < end; p++) {
        try {
            new (p) T(v);
        } catch (...) {
            throw;
        }
        count++;
    }
}

template <class T> T &KeyVecBase<T>::at(unsigned long i) {
    if (i >= count) {
        throw out_of_range(lbl_8039A4EC);
    }
    return data[i];
}

template <class T> KeyVecBase<T>::~KeyVecBase() {
    clear();
    if (data) {
        operator delete(data);
    }
}

template <class T> void KeyVecBase<T>::clear() {
    T *end = data + count;
    for (T *p = data; p < end; p++) {
        p->~T();
    }
    count = 0;
}

template <class T> struct KeyVecMid : KeyVecBase<T> {
    KeyVecMid(unsigned long n, const T &v) { this->init(n, v); }
    ~KeyVecMid() {}
};
template <class T> struct KeyVec : KeyVecMid<T> {
    KeyVec(unsigned long n, const T &v) : KeyVecMid<T>(n, v) {}
    ~KeyVec() {}
};

/* 0x154: card name entry keyboard (main flow +0x14). */
extern "C" KeyGroup lbl_806792B8;
extern "C" const int lbl_80399E6C[4][3];
extern "C" const KeyGroup lbl_80399E9C[5];

static inline int FindCol(const KeyGroup &kg, int dir) {
    if (dir == 0) {
        return -1;
    }
    if (dir < 0) {
        for (int i = 0; i < 4; i++) {
            if (kg.cols[i] != 100) {
                return kg.cols[i];
            }
        }
    } else if (dir > 0) {
        for (int i = 3; i > 0; i--) {
            if (kg.cols[i] != 100) {
                return kg.cols[i];
            }
        }
    }
    return -1;
}

static inline int PickCol(const KeyGroup &kg, const int &col) {
    for (int i = 0; i < 4; i++) {
        if (kg.cols[i] == col) {
            return col;
        }
    }
    return kg.cols[0];
}

struct KeyBoard {
    unsigned char ascii;
    KeyVec<KeyGroup> groups;
    int group;
    int page;
    unsigned char shift;
    int lastCol;
    int saveCol;
    int saveRow;
    bool Navigate();
    void SelectGroupOf(int col) {
        for (unsigned long i = 0; i < groups.count; i++) {
            if (groups.data[i].HasCol(col) == 1) {
                group = i;
                return;
            }
        }
    }
    int PeekAction() {
        if (shift == 0) {
            return -1;
        }
        if (group == 3) {
            return 4;
        }
        if (group == 4) {
            return 5;
        }
        return lbl_80399E6C[page][group];
    }
    int TakeAction() {
        if (shift == 0) {
            return -1;
        }
        shift = 0;
        if (group == 3) {
            return 4;
        }
        if (group == 4) {
            return 5;
        }
        return page = lbl_80399E6C[page][group];
    }
    KeyBoard(int a) : ascii(a), groups(5, lbl_806792B8) {
        group = -1;
        page = (unsigned char)a == 1 ? 0 : 2;
        shift = 0;
        lastCol = -1;
        const KeyGroup *src = lbl_80399E9C;
        for (unsigned long i = 0; i < groups.count; i++) {
            groups.at(i) = *src;
            src++;
        }
    }
};

struct NameBuf {
    unsigned short c[8];
    int pos;
    bool Add(unsigned short ch);
    unsigned short Get(int i) { return c[i + 1]; }
    void Back() {
        if (pos > 0) {
            c[pos + 1] = 0x8162;
            pos--;
        } else if (pos == 0) {
            c[1] = 0x8162;
        }
    }
    NameBuf() {
        pos = 0;
        c[7] = 0;
        for (int i = 0; i < 7; i++) {
            c[i] = 0x8162;
        }
    }
};

/* 0x94: fading resource label node (vtable lbl_8048EF20). */
struct ResNode : FadeObj {
    short res;
    int layer;
    unsigned char flag;
    ResNode(short r, float x, float y) : FadeObj(0, 30) {
        res = r;
        layer = 7;
        flag = 0;
        tracks[3].Set(x, x, lbl_806D9A34);
        tracks[4].Set(y, y, lbl_806D9A34);
    }
    virtual void Update();
    virtual void Draw();
};

struct NameEntry {
    KeyBoard board;
    NameBuf name;
    unsigned char started;
    Own<Sprite> frame;
    NameKey *keys[4][15];
    int state;
    int mode;
    int col;
    int row;
    float bright;
    PtrVec<FadeObj *> nodes;
    NameEntry(bool ascii);
    void BuildKeys();
    void Draw();
    void DrawKeys();
    void Commit();
    void Update();
    ~NameEntry() {
        for (FadeObj **it = nodes.begin(); it != nodes.end(); it++) {
            delete *it;
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 15; j++) {
                delete keys[i][j];
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
    bool IsDone() { return state == 5 ? true : false; }
};

/* 0x44 card printer job (ctor fn_80232F9C). */
struct PrintJob {
    virtual ~PrintJob();
    virtual int Update();
    char pad04[0x40];
    PrintJob();
};

struct SpritePair {
    Own<Sprite> a;
    Own<Sprite> b;
    unsigned char show;
    SpritePair() : a(new Sprite(0x4A, 1, 0)), b(new Sprite(0x74, 1, 0)) {
        Sprite *s = a.p;
        s->x = lbl_806D9ACC;
        s->y = lbl_806D9A48;
        fn_8019FF6C(a.p, 1);
        s = b.p;
        s->x = lbl_806D9AD0;
        s->y = lbl_806D9A98;
        fn_8019FF6C(b.p, 1);
    }
    void Advance() {
        Sprite_AdvanceAnim(a.p, lbl_806D9A70);
        Sprite_AdvanceAnim(b.p, lbl_806D9A70);
    }
};

struct clFlowBase {
    clFlowBase();
    virtual ~clFlowBase();
};

struct clFlowCard : clFlowBase {
    int next;
    Own<SpritePair> sprites;
    CardRead *read;
    CoinWait *coin;
    NameEntry *name;
    PrintJob *print;
    int state;
    CardBuy *buy;
    CardEntry *entry;
    unsigned char newCard;
    unsigned char readOk;
    clFlowCard();
    ~clFlowCard();
    virtual int Update();
};

int clFlowCard::Update() {
    sprites->Advance();
    RumbleUpdate();
    if (state == 0) {
        fn_801C0C30(read);
        if (read->IsDone() == 1) {
            newCard = read->newCard;
            readOk = read->readOk;
            delete read;
            read = 0;
            fn_80121210();
            clRom_PurgeAll();
            if (ServiceValue_Get() == 1 || !ServiceEnable_Get()) {
                state = 6;
            } else if (g_gameMode == 2) {
                state = 6;
            } else if (readOk == 1) {
                entry = new CardEntry(0);
                state = 5;
            } else if (newCard == 1) {
                buy = new CardBuy(0);
                state = 4;
            } else if (Sci2Card_GetByteFlag1224() == 1) {
                print = new PrintJob();
                state = 3;
                sprites->show = 0;
            } else {
                coin = new CoinWait();
                state = 1;
            }
        }
    } else if (state == 4) {
        fn_801BD038(buy);
        if (buy->IsDone() == 1) {
            delete buy;
            buy = 0;
            fn_80121210();
            clRom_PurgeAll();
            if (Sci2Card_GetByteFlag1224() == 1) {
                print = new PrintJob();
                state = 3;
                sprites->show = 0;
            } else {
                state = 6;
            }
        }
    } else if (state == 5) {
        fn_801BBAF0(entry);
        if (entry->IsDone() == 1) {
            if (entry->ok == 0) {
                newCard = 0;
            }
            delete entry;
            entry = 0;
            fn_80121210();
            clRom_PurgeAll();
            if (newCard == 1) {
                buy = new CardBuy(1);
                state = 4;
            } else if (Sci2Card_GetByteFlag1224() == 1) {
                print = new PrintJob();
                state = 3;
                sprites->show = 0;
            } else {
                state = 6;
            }
        }
    } else if (state == 1) {
        fn_801C02C4(coin);
        if (coin->IsDone() == 1) {
            delete coin;
            coin = 0;
            fn_80121210();
            clRom_PurgeAll();
            if (Sci2Card_GetUnpackStatusCode() == 1) {
                name = new NameEntry(isJapanese() == 0);
                sprites->show = 0;
                state = 2;
            } else {
                state = 6;
            }
        }
    } else if (state == 2) {
        name->Update();
        if (name->IsDone() == 1) {
            delete name;
            name = 0;
            fn_80121210();
            clRom_PurgeAll();
            state = 3;
            sprites->show = 0;
            print = new PrintJob();
        }
    } else if (state == 3) {
        if (print->Update() != -1) {
            state = 6;
        }
    }
    if (state == 6) {
        next = 11;
    }
    return next;
}

clFlowCard::~clFlowCard() {
    fn_80169C44();
    delete read;
    delete coin;
    delete name;
    delete print;
    delete buy;
    delete entry;
    if (Sci2Card_GetByteFlag1224() == 1) {
        CardRegister_KickoffArm();
    }
}

clFlowCard::clFlowCard() : sprites(new SpritePair()), read(new CardRead(0)) {
    coin = 0;
    name = 0;
    print = 0;
    state = 0;
    buy = 0;
    entry = 0;
    newCard = 0;
    readOk = 0;
    SetSyncTarget(9);
    next = -1;
    InitBGM();
    SetupBgSprites(0);
    SetupBgSprites(1);
    if (!IsCardValid()) {
        state = 6;
    }
    InitRumbleController(1);
}

extern "C" ResCtrl fn_801BB58C(const KeyLabel *k);

extern "C" void fn_801BB474(const KeyLabel *list, int n, int layer) {
    const KeyLabel *p = list;
    for (int i = 0; i < n; i++) {
        ResCtrl r = fn_801BB58C(p);
        fn_8011FAFC(&r, layer);
        p++;
    }
}

extern "C" ResCtrl fn_801BB58C(const KeyLabel *k) {
    ResCtrl r;
    r.resId = k->res;
    r.Show(k->x, k->y, lbl_806D9A34);
    return r;
}
extern "C" {
extern const float lbl_806D9A7C;
extern const float lbl_806D9A80;
extern const float lbl_806D9A84;
extern const float lbl_806D9A88;
extern const float lbl_806D9A8C;
extern const float lbl_806D9A90;
extern const float lbl_806D9A94;
extern const float lbl_806D9A9C;
extern const float lbl_806D9AA0;
extern const float lbl_806D9AA4;
extern const float lbl_806D9AA8;
extern const float lbl_806D9AAC;
void fn_801BEDF0(NameEntry *self);
}

NameEntry::NameEntry(bool ascii) : board(ascii), started(ascii), frame(new Sprite(0x150, 1, 0)), state(0), mode(ascii == 1 ? 0 : 2),
      col(0), row(0), bright(lbl_806D9A7C) {
    Sprite *f = frame.p;
    f->x = lbl_806D9A2C;
    f->y = lbl_806D9A80;
    fn_801B8918(0x1AD8);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 15; j++) {
            keys[i][j] = 0;
        }
    }
    BuildKeys();
    Sprite *s;
    FadeObj *o;
    ResNode *r;
    {
        s = new Sprite(0x3F, 1, 0);
        fn_8019FF6C(s, 1);
        s->x = lbl_806D9A84;
        s->y = lbl_806D9A40;
        s->sx = lbl_806D9A88;
        s->sy = lbl_806D9A88;
        o = new FadeObj(s, 30);
        o->tracks[0].Set(lbl_806D9A74, lbl_806D9A34, lbl_806D9A8C);
        nodes.push_back(o);
    }
    {
        s = new Sprite(0x4A, 1, 0);
        fn_8019FF6C(s, 1);
        s->x = lbl_806D9A90;
        s->y = lbl_806D9A48;
        o = new FadeObj(s, 30);
        o->tracks[0].Set(lbl_806D9A74, lbl_806D9A34, lbl_806D9A8C);
        nodes.push_back(o);
    }
    {
        s = new Sprite(0x75, 1, 0);
        fn_8019FF6C(s, 1);
        s->x = lbl_806D9A94;
        s->y = lbl_806D9A98;
        o = new FadeObj(s, 30);
        o->tracks[0].Set(lbl_806D9A74, lbl_806D9A34, lbl_806D9A8C);
        nodes.push_back(o);
    }
    {
        s = new Sprite(0x74, 1, 0);
        fn_8019FF6C(s, 1);
        s->x = lbl_806D9A9C;
        s->y = lbl_806D9A98;
        o = new FadeObj(s, 30);
        o->tracks[0].Set(lbl_806D9A74, lbl_806D9A34, lbl_806D9A8C);
        nodes.push_back(o);
    }
    {
        r = new ResNode(0x1875, lbl_806D9AA0, lbl_806D9AA4);
        r->tracks[0].Set(lbl_806D9A74, lbl_806D9A34, lbl_806D9A8C);
        nodes.push_back(r);
    }
    {
        r = new ResNode(0x1873, lbl_806D9AA8, lbl_806D9AA4);
        r->tracks[0].Set(lbl_806D9A74, lbl_806D9A34, lbl_806D9A8C);
        nodes.push_back(r);
    }
    {
        r = new ResNode(0x1874, lbl_806D9AAC, lbl_806D9AA4);
        r->tracks[0].Set(lbl_806D9A74, lbl_806D9A34, lbl_806D9A8C);
        nodes.push_back(r);
    }
}

void NameEntry::BuildKeys() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 15; j++) {
            delete keys[i][j];
        }
    }
    int y = 0xEC;
    int n = 0;
    for (int r = 0; r < 4; r++) {
        int gx = 0x3C;
        short sy = y;
        for (int g = 0; g < 3; g++) {
            short x = gx;
            for (int k = 0; k < 5; k++) {
                int col = g * 5 + k;
                unsigned int code = lbl_8049A8F8[mode].chars[n];
                if (n != 59) {
                    if (code != 0x8140) {
                        keys[r][col] = new NameKey(x, sy, code);
                    } else {
                        keys[r][col] = new NameKey(x, sy, 9);
                    }
                } else {
                    keys[r][col] = new NameKey(x, sy, 0x8140);
                }
                n++;
                x += 0x20;
            }
            gx += 0xBB;
        }
        y += 0x26;
    }
}

extern "C" {
void PlayCursorMoveSE(void);
void fn_801B7C40(void);
}

bool KeyBoard::Navigate() {
    if (group < 0) {
        return false;
    }
    int dx = GetInput()->dir;
    int btn = GetInput()->held;
    int vert = dx != 0 ? 0 : (btn == 3 ? 1 : 0);
    if (btn == 1) {
        SetRumbleMode(0, 1, 1);
    }
    if (btn == 3) {
        SetRumbleMode(1, 1, 1);
    }
    if (dx != 0 || vert != 0) {
        PlayCursorMoveSE();
    }
    int g = group;
    if (dx != 0) {
        g = group + dx;
        int min = 0;
        if (ascii == 0) {
            min = 2;
        }
        if (g < min) {
            saveCol = 14;
            saveRow = 3;
            g = -1;
        } else if ((unsigned long)g > groups.count - 1) {
            saveCol = 0;
            saveRow = 0;
            g = -1;
        }
        if (g != -1) {
            int col = FindCol(groups.at(g), -dx);
            if (col != -1) {
                lastCol = col;
            }
        }
    } else if (vert != 0) {
        saveCol = PickCol(groups.at(g), lastCol);
        if (vert < 0) {
            saveRow = 3;
        } else {
            saveRow = 0;
        }
        g = -1;
    }
    group = g;
    if (group == -1) {
        return false;
    }
    if (btn == 1) {
        shift = 1;
        if (group < 3) {
            fn_801B7C40();
        }
    } else {
        shift = 0;
    }
    return true;
}

struct KanaOut {
    unsigned short c;
};

static inline int ConvertKana(unsigned short prev, unsigned short ch, KanaOut *out) {
    int type = -1;
    if (ch == 0x814A) {
        type = 0;
    }
    if (ch == 0x818B) {
        type = 1;
    }
    if (prev == 0x8162 && type < 0) {
        out->c = ch;
        return 1;
    }
    if (type < 0) {
        out->c = ch;
        return 1;
    }
    for (int t = 0; t < 4; t++) {
        for (int i = 0; i < 60; i++) {
            if (prev == lbl_8049A8F8[t].chars[i] && lbl_8049A8F8[t].marks[type][i] != 0x8140) {
                out->c = lbl_8049A8F8[t].marks[type][i];
                return 0;
            }
        }
    }
    return -1;
}

bool NameBuf::Add(unsigned short ch) {
    bool full = false;
    if (pos < 5) {
        bool next = false;
        KanaOut out;
        int res;
        if (c[pos + 1] != 0x8162) {
            next = true;
            res = ConvertKana(c[pos + 1], ch, &out);
        } else {
            res = ConvertKana(c[pos], ch, &out);
        }
        if (res == 0) {
            if (next == 1) {
                c[pos + 1] = out.c;
                if (++pos >= 5) {
                    pos = 4;
                    full = true;
                }
            } else {
                c[pos] = out.c;
            }
        } else if (res == 1) {
            c[pos + 1] = out.c;
            if (++pos >= 5) {
                pos = 4;
                full = true;
            }
        }
    }
    if (full == 1 && pos >= 4) {
        return false;
    }
    return true;
}

extern "C" {
extern const float lbl_806D9A4C;
extern const float lbl_806D9A58;
extern const float lbl_806D9A5C;
extern const double lbl_806D9A60;
extern const float lbl_806D9A6C;
extern const int lbl_80399E5C[4];
int fn_801F9778(unsigned short ch);
void fn_80121E10(ResCtrl *rc);
double sin(double x);
}

static inline float sinf(float x) {
    return sin(x);
}

void NameEntry::DrawKeys() {
    NameKey *k;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 15; j++) {
            k = keys[i][j];
            if (k->res == 0x2B00) {
                continue;
            }
            if (k->blink != 1) {
                k->t += lbl_806D9A58;
                if (k->t > lbl_806D9A34) {
                    k->t -= lbl_806D9A34;
                    if (k->sel == 0) {
                        k->blink = 1;
                    }
                }
                k->t2 += lbl_806D9A5C;
                if (k->t2 >= lbl_806D9A34) {
                    k->t2 -= lbl_806D9A34;
                    if (k->sel == 0) {
                        k->blink = 1;
                    }
                }
            }
            ResCtrl rc;
            if (k->lit == 1) {
                rc.resId = 0x1913;
                rc.Show(k->x, k->y, lbl_806D9A34);
                float a = k->blink == 1 ? lbl_806D9A34 : sinf(lbl_806D9A60 * k->t2);
                rc.t1 = 4;
                rc.t0 = 1;
                rc.t2 = 1;
                unsigned int c = PackColor(0xFF, 0xFF, 0xFF, (int)(lbl_806D9A68 * a));
                rc.SetColor(c);
                fn_8011FAFC(&rc, 7);
            }
            fn_80121E10(&rc);
            rc.resId = k->res;
            rc.Show(k->x, k->y, lbl_806D9A34);
            float sy = k->blink == 1 ? lbl_806D9A34 : lbl_806D9A6C * sinf(lbl_806D9A60 * k->t) + lbl_806D9A34;
            float sx = k->blink == 1 ? lbl_806D9A34 : lbl_806D9A6C * sinf(lbl_806D9A60 * k->t) + lbl_806D9A34;
            rc.scaleX = sx;
            rc.scaleY = sy;
            fn_8011FAFC(&rc, 7);
        }
    }
}

void NameEntry::Draw() {
    fn_801A0004(frame.p);
    DrawKeys();
    for (int i = 0; i < 5; i++) {
        ResCtrl rc;
        unsigned short ch = name.Get(i);
        if (ch == 0x8140) {
            rc.resId = 0x2AF7;
        } else if (ch != 0x8162) {
            rc.resId = fn_801F9778(ch);
        } else {
            rc.resId = fn_801F9778(0x8151);
        }
        rc.Show(0xB0 + i * 0x48, lbl_806D9A4C, lbl_806D9A34);
        if (i == name.pos) {
            rc.SetColor(0xE0E020FF);
        }
        fn_8011FAFC(&rc, 7);
    }
    int g = 0;
    if (board.ascii == 0) {
        g = 2;
    }
    for (; g < board.groups.count; g++) {
        int res;
        if (g < 3) {
            res = lbl_80399E5C[lbl_80399E6C[board.page][g]];
        } else {
            res = g + 0x190D;
        }
        int sel = board.group == g;
        KeyGroup &kg = board.groups.at(g);
        int n = (bool)sel == true ? 1 : 0;
        {
            ResCtrl rc;
            rc.resId = kg.img[n].res;
            rc.Show(kg.img[n].x, kg.img[n].y, lbl_806D9A34);
            fn_8011FAFC(&rc, 7);
        }
        {
            ResCtrl lc;
            lc.resId = res;
            lc.Show(kg.label.x, kg.label.y, lbl_806D9A34);
            fn_8011FAFC(&lc, 7);
        }
    }
    fn_802321F8(GetFader());
    for (FadeObj **it = nodes.begin(); it != nodes.end(); it++) {
        (*it)->Render();
    }
}

extern "C" {
extern int g_characterId;
extern const unsigned short *lbl_8049A890[];
extern const unsigned short *lbl_8049A8C4[];
extern const char lbl_8039A31C[];
extern const char lbl_8039A32C[];
unsigned short *wcsncpy(unsigned short *dst, const unsigned short *src, unsigned long n);
unsigned char NameCheck_CardName(const unsigned short *name);
void fn_801FE2B8(void);
void fn_801B7C1C(void);
}

void NameEntry::Commit() {
    unsigned short tmp[5];
    wcsncpy(tmp, &name.c[1], 5);
    for (int i = 0; i < 5; i++) {
        if (tmp[i] == 0x8162) {
            tmp[i] = 0;
        }
    }
    unsigned short buf[6];
    buf[0] = tmp[0];
    buf[1] = tmp[1];
    buf[2] = tmp[2];
    buf[3] = tmp[3];
    buf[4] = tmp[4];
    buf[5] = 0;
    int n;
    for (n = 0; n < 5; n++) {
        if (buf[n] != 0) {
            break;
        }
    }
    if (NameCheck_CardName(buf) == 1) {
        for (int i = 0; i < 6; i++) {
            name.Back();
        }
        fn_801FE2B8();
        return;
    }
    if (n >= 5) {
        DebugPrintf(lbl_8039A31C, lbl_8039A32C);
        int chr = g_characterId;
        wcsncpy(buf, isJapanese() == 0 ? lbl_8049A890[chr] : lbl_8049A8C4[chr], 5);
        for (int i = 0; i < 5; i++) {
            name.Back();
        }
        for (int i = 0; i < 5; i++) {
            name.Add(buf[i]);
        }
        for (int i = 5; i >= 0; i--) {
            if (buf[i] != 0x8140) {
                break;
            }
            buf[i] = 0;
        }
    }
    wcsncpy((unsigned short *)g_playerData, buf, 5);
    state = 4;
    fn_801B87D8();
    fn_801B7C1C();
}

extern "C" void fn_801FE2DC(void);

void NameEntry::Update() {
    if (state == 0) {
        if (Sprite_AdvanceAnim(frame.p, lbl_806D9A70) == 1) {
            return;
        }
        SetInput(1);
        state = 1;
        keys[row][col]->Select();
        fn_801699D8(0, 1);
        fn_801699D8(1, 1);
    } else if (state == 1) {
        int dx = GetInput()->dir;
        int btn = GetInput()->held;
        int vert = dx != 0 ? 0 : (btn == 3 ? 1 : 0);
        int c = col;
        int r = row;
        if (btn == 1) {
            SetRumbleMode(0, 1, 1);
        }
        if (btn == 3) {
            SetRumbleMode(1, 1, 1);
        }
        if (dx != 0 || vert != 0) {
            PlayCursorMoveSE();
        }
        do {
            c += dx;
            r += vert;
            if (c < 0) {
                c = 14;
                r--;
            } else if (c > 14) {
                c = 0;
                r++;
            }
        } while (r >= 0 && r <= 3 && keys[r][c]->res == 0x2B00);
        if (r < 0 || r > 3) {
            bool wrap = false;
            if (started == 0 && c < 5) {
                if (vert == 0) {
                    c = 5;
                } else {
                    wrap = true;
                }
            }
            if (wrap == 1) {
                keys[0][c]->Select();
                r = 0;
            } else {
                state = 3;
                board.SelectGroupOf(c);
                board.lastCol = c;
            }
            keys[row][col]->Deselect();
        } else if (dx != 0 || vert != 0) {
            keys[row][col]->Deselect();
            keys[r][c]->Select();
        } else if (btn == 1) {
            if (!name.Add(keys[r][c]->code)) {
                state = 3;
                board.SelectGroupOf(14);
                board.lastCol = 14;
                keys[row][col]->Deselect();
            }
            fn_801B7C40();
        }
        col = c;
        row = r;
    } else if (state == 3) {
        if (!board.Navigate()) {
            int oc = col;
            int orow = row;
            if (board.group == -1) {
                col = board.saveCol;
                row = board.saveRow;
            }
            keys[row][col]->Select();
            state = 1;
            if (col != oc || row != orow) {
                PlayCursorMoveSE();
            }
        } else {
            switch (board.PeekAction()) {
            case 0:
            case 1:
            case 2:
            case 3:
                mode = board.TakeAction();
                BuildKeys();
                break;
            case 4:
                name.Back();
                fn_801FE2DC();
                break;
            case 5:
                Commit();
                break;
            }
        }
    } else if (state == 4) {
        state = 5;
    }
    if (state == 1 || state == 3) {
        if (GetInput()->held == 2) {
            name.Back();
            fn_801FE2DC();
        }
    }
    bright -= lbl_806D9A78;
    if (bright < lbl_806D9A74) {
        bright = lbl_806D9A74;
    }
    fn_80232284(GetFader(), bright);
    if (state != 4 && state != 5 && bright <= lbl_806D9A74) {
        Commit();
    }
    for (FadeObj **it = nodes.begin(); it != nodes.end(); it++) {
        (*it)->Tick();
    }
}
