/* Result-scene objects, .text 0x8015C41C..0x8016219C.
 * This span's extabindex is not in ascending order, so dtk can't split it
 * further; it stays one NonMatching TU and gains functions as they match. */

struct VObj {
    virtual ~VObj();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
};

extern "C" {
extern void *Alloc(unsigned long size);
extern void HSD_StateInvalidate(int state);
}

struct SceneBase {
    SceneBase() { done = 0; }
    virtual ~SceneBase() {}
    virtual void Destroy() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    unsigned char done;
};

struct ResultSub {
    ResultSub(int a, int b);
    virtual ~ResultSub();
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    char pad4[0x10];
    int state;
    char pad18[0x60 - 0x18];
};

extern "C" {
extern unsigned char fn_8019083C(int id);
extern int fn_801909A4(int id);
}

extern "C" {
extern int g_cupId;
extern const char lbl_80368CF0[];
extern void DebugPrintf(const char *fmt, ...);
extern void fn_8014017C(void *p);
extern void fn_8011F994(int i);
}

struct ResultSceneX : SceneBase {
    ResultSceneX(int c) {
        cup = c;
        xc = 0;
        obj = 0;
        g_cupId = 0;
        if (cup < 0 || cup > 5) {
            DebugPrintf(lbl_80368CF0);
            cup = 0;
        }
    }
    virtual ~ResultSceneX();
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    int cup;
    int xc;
    VObj *obj;
};

ResultSceneX::~ResultSceneX() {
    if (obj) delete obj;
    if (fn_8019083C(2)) fn_801909A4(2);
}

struct ResultBuf {
    int a;
    int b;
    char *data;
    ~ResultBuf() { if (data) delete data; }
};

struct ResultBufMid : ResultBuf {
    ~ResultBufMid() {}
};

struct ResultBuf1 : ResultBufMid {
    ~ResultBuf1();
};

ResultBuf1::~ResultBuf1() {}

struct ResultBuf2 : ResultBufMid {
    ~ResultBuf2();
};

ResultBuf2::~ResultBuf2() {}

struct ResultInnerBase {
    char pad[0x14];
};

struct ResultInner : ResultInnerBase {
    virtual ~ResultInner();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
};

extern "C" {
extern void Sprite_Destroy(void *s, int flag);
extern void fn_80140810(void *p, int flag);
extern void fn_80121210(void);
}

struct ResultPart {
    virtual ~ResultPart() {}
    virtual void v0C() {}
    virtual void v10() {}
    virtual int v14() { return 1; }
};

struct ResultPartB : ResultPart {
    virtual ~ResultPartB();
    char pad4[0x1c - 4];
    void *p1c;
    ResultInner *inner;
    void *sprite;
};

ResultPartB::~ResultPartB() {
    Sprite_Destroy(sprite, 1);
    fn_80140810(p1c, 1);
    delete inner;
    fn_80121210();
}

extern "C" void fn_80192348(int id);

struct SpriteHolder {
    void *s;
    ~SpriteHolder() throw();
};

SpriteHolder::~SpriteHolder() throw() {
    Sprite_Destroy(s, 1);
}

struct ResultPartC : ResultPart {
    virtual ~ResultPartC();
    int idx;
    char pad8[0x6c - 8];
    SpriteHolder spr;
};

ResultPartC::~ResultPartC() {
    if (idx % 2 == 0) {
        fn_80192348(0x20);
    } else {
        fn_80192348(0x21);
    }
}

extern "C" {
extern void LObjList_Destroy(void *l, int flag);
extern void KartDriver_Dtor(void *k, int flag);
}

struct ResultPair {
    char pad[0xc];
    VObj *a;
    VObj *b;
    ~ResultPair() {
        delete a;
        delete b;
    }
};

struct ResultKart {
    void *driver;
    ~ResultKart() { KartDriver_Dtor(driver, 1); }
};

struct ResultKarts {
    VObj *obj;
    void *lobj;
    ResultKart *karts[13];
    ~ResultKarts() {
        int i;
        delete obj;
        LObjList_Destroy(lobj, 1);
        for (i = 0; i < 13; i++) delete karts[i];
    }
};

struct ResultPartY : ResultPart {
    virtual ~ResultPartY();
    char pad4[0x2c - 4];
    ResultKarts *karts;
    char *buf;
    ResultPair *pair;
};

ResultPartY::~ResultPartY() {
    delete pair;
    if (buf) delete buf;
    delete karts;
    fn_80121210();
}

struct ItemMsgWnd {
    ItemMsgWnd();
    char body[0x5c];
};

struct CoinPrompt {
    ~CoinPrompt();
};

struct CoinPopupDetail {
    ~CoinPopupDetail();
};

struct ResultText {
    ~ResultText() {}
};

extern "C" {
extern ItemMsgWnd *lbl_806D1A88;
extern void fn_80232284(ItemMsgWnd *wnd, float t);
extern void SpriteAnimHandle_Destroy(void *h, int flag);
extern void SpriteHandle_Destroy(void *h);
extern void fn_801699D8(int a, int b);
extern void fn_80169C44(void);
extern void fn_80120A08(int id);
}

static inline ItemMsgWnd *ItemMsg_Get() {
    return lbl_806D1A88 ? lbl_806D1A88 : (lbl_806D1A88 = new ItemMsgWnd);
}

struct ResultTop {
    virtual ~ResultTop() {}
};

struct ResultMid : ResultTop {
    virtual ~ResultMid() {}
};

struct ResultScreenObj : ResultMid {
    virtual ~ResultScreenObj();
    char pad4[0x3c - 4];
    void *sprite;
    ResultText *texts[2];
    void *anims[3];
    CoinPrompt *prompt;
    CoinPopupDetail *detail;
};

ResultScreenObj::~ResultScreenObj() {
    int i;
    if (prompt) delete prompt;
    if (detail) delete detail;
    for (i = 0; i < 3; i++) {
        if (anims[i]) {
            SpriteAnimHandle_Destroy(anims[i], 1);
            anims[i] = 0;
        }
    }
    for (i = 0; i < 2; i++) {
        if (texts[i]) {
            delete texts[i];
            texts[i] = 0;
        }
    }
    SpriteHandle_Destroy(sprite);
    fn_801699D8(0, 0);
    fn_80169C44();
    fn_80120A08(0x971);
    fn_80120A08(0x972);
    fn_80120A08(0x1ad9);
    fn_80120A08(0x1ada);
    fn_80120A08(0x152c);
    fn_80232284(ItemMsg_Get(), -1.0f);
}

struct ResultSceneA : SceneBase {
    ResultSceneA() {
        started = 0;
        sub = new ResultSub(0, 0);
    }
    virtual ~ResultSceneA() {
        if (sub) sub->Destroy();
    }
    virtual void Destroy() { delete this; }
    virtual void Update() {
        if (!started) started = 1;
        sub->Update();
        if (sub->state == 99) done = 1;
    }
    virtual void Draw() {
        if (started) {
            sub->Draw();
            HSD_StateInvalidate(-1);
        }
    }
    unsigned char started;
    ResultSub *sub;
};

extern "C" {

extern void MemoryManager_TimedFree(void *p);
extern void fn_8011FAFC(void *p, int n);
extern void fn_801A0004(void *p);
extern void fn_80160588(void *self, int n);
extern void fn_80161720(void *self);
extern char lbl_80490A58[];
extern const float lbl_806D86A4;
extern const float lbl_806D86D8;

void fn_8015CB24(VObj *p) {
    delete p;
}

typedef struct {
    char pad0[0x10];
    float a;
    char pad14[0x28 - 0x14];
    float b;
} Obj8015CD40;

int fn_8015CD40(Obj8015CD40 *o) {
    if (o->a > lbl_806D86D8 || o->b >= lbl_806D86A4) return 1;
    return 0;
}

typedef struct {
    char pad0[0x10];
    int state;
} Obj8015E1D4;

unsigned char fn_8015E1D4(Obj8015E1D4 *o) {
    return o->state == 6;
}

typedef struct {
    char pad0[0x10];
    unsigned char mode;
    char pad11[3];
    char sub[0x6c - 0x14];
    void *p6c;
} Obj8015E804;

void fn_8015E804(Obj8015E804 *o) {
    if (o->mode != 1) {
        fn_8011FAFC(o->sub, 3);
        fn_801A0004(o->p6c);
    }
}

unsigned char fn_8015E84C(Obj8015E804 *o) {
    return o->mode;
}


void fn_80160364(VObj *p) {
    delete p;
}

typedef struct {
    unsigned char active;
    char pad1[0x10 - 1];
    int ready;
    int cur;
    int next;
} Obj80161888;

int fn_801618CC(Obj80161888 *o, int v, int unused);

void fn_80161888(Obj80161888 *o) {
    o->active = 1;
    fn_801618CC(o, o->next, 1);
    fn_80161720(o);
}

int fn_801618CC(Obj80161888 *o, int v, int unused) {
    if (o->ready == 0) return 0;
    o->next = v;
    o->cur = -1;
    fn_80160588(o, 0);
    return 1;
}

SceneBase *fn_80160238(void) {
    return new ResultSceneA;
}

SceneBase *fn_8015CB5C(int cup) {
    return new ResultSceneX(cup);
}

typedef struct {
    char pad0[0x10];
    int stage;
    char pad14[4];
    unsigned char on;
    char pad19[3];
    void *p1c;
    ResultInner *inner;
    void *p24;
    char res28[0x80 - 0x28];
    char res80[4];
} Obj8015E48C;

void fn_8015E48C(Obj8015E48C *o) {
    int i;
    if (o->on) {
        o->inner->v1C();
        fn_8014017C(o->p1c);
        fn_8011FAFC(o->res28, 0);
        fn_8011FAFC(o->res80, 7);
        if (o->stage >= 3) fn_801A0004(o->p24);
        for (i = 0; i < 8; i++) fn_8011F994(i);
        HSD_StateInvalidate(-1);
        o->on = 0;
    }
}

extern void fn_8023CD54(void *p);
extern void fn_8019FF8C(void *obj, int id, float *out);
extern void fn_801F93EC(void *t, float x, float y);
extern void *fn_801F8E58(void);
extern void fn_801F8A34(void *a, void *b, int c);
extern void fn_8016039C(void *p);
extern void fn_801678FC(int mode, float r, float g, float b, float a);

typedef struct {
    void *obj;
} ResultItem;

typedef struct {
    char pad0[0x14];
    int state;
    char pad18[0x40 - 0x18];
    void *texts[2];
    ResultItem *items[3];
    void *p54;
    void *p58;
    float alpha;
} ResultScreen;

void fn_8015F0FC(ResultScreen *s) {
    int i;
    if (s->state == 99) return;
    for (i = 0; i < 3; i++) {
        if (s->items[i]) fn_801A0004(s->items[i]->obj);
    }
    if (s->p54) fn_8023CD54(s->p54);
    if (s->items[0]) {
        float pos[14];
        void *mgr;
        int j;
        fn_8019FF8C(s->items[0]->obj, 0x23e5, pos);
        fn_801F93EC(s->texts[0], pos[0], 12.0f + pos[1]);
        mgr = fn_801F8E58();
        for (j = 0; j < 2; j++) fn_801F8A34(mgr, s->texts[j], 6);
    }
    if (s->p58) fn_8016039C(s->p58);
    fn_801678FC(7, 0.0f, 0.0f, 0.0f, s->alpha);
}

}
