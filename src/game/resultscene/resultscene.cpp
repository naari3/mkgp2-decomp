#include "game/resultscene_private.h"

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

extern "C" {
extern void fn_8016219C(void *, int, void *);
extern char lbl_806CF910[4];
}

struct ResultBuf {
    int a;
    int b;
    void **data;
    ResultBuf(int count) {
        a = 0; b = 0; data = 0;
        fn_8016219C(this, count, lbl_806CF910);
    }
    ~ResultBuf() { if (data) delete data; }
};

struct ResultBufMid : ResultBuf {
    ResultBufMid(int n) : ResultBuf(n) {}
    ~ResultBufMid() {}
};

struct ResultBuf1 : ResultBufMid {
    ResultBuf1(int n) : ResultBufMid(n) {}
    ~ResultBuf1();
};

ResultBuf1::~ResultBuf1() {}

struct ResultBuf2 : ResultBufMid {
    ResultBuf2(int n) : ResultBufMid(n) {}
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
    SpriteHolder(void *p) : s(p) {}
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
    CoinPrompt(int a, int b, int c, int d, int e);
    char body[0x20];
    ~CoinPrompt();
};

struct PtrVecBase {
    int cap;
    int n;
    void **data;
    ~PtrVecBase() { if (data) delete data; }
};

struct PtrVecMid : PtrVecBase {
    ~PtrVecMid() {}
};

struct PtrVec : PtrVecMid {
    ~PtrVec() {}
};

struct CoinPopupDetail {
    CoinPopupDetail(int mode, int active, int index);
    ~CoinPopupDetail();
    unsigned char active;
    char pad1[3];
    ResultBuf2 sprites;
    int state;
    int pad14;
    int mode;
    float ax;
    float ay;
    float bx;
    float by;
    int idxA;
    int idxB;
    int credits;
    unsigned char creditOn;
    unsigned char on;
    unsigned char extra;
    char pad3b;
    int nextIdx;
    int x40;
    int x44;
    int creditMgr;
    unsigned char changed;
    char pad4d[3];
    ResultBuf1 bufs;
    SpriteHolder h5c;
    SpriteHolder h60;
    SpriteHolder h64;
    SpriteHolder h68;
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
    ResultTop(int id) : id(id), x8(0), xc(0) {}
    virtual ~ResultTop() {}
    int id, x8, xc;
};

struct ResultMid : ResultTop {
    ResultMid(int id) : ResultTop(id) {}
    virtual ~ResultMid() {}
};

struct ResultSub : ResultMid {
    ResultSub(int a, int b);
    virtual ~ResultSub();
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    int mode;
    int state;
    float timer;
    unsigned char flag;
    char pad1d[3];
    float timer2;
    float scale;
    int resource;
    unsigned char hasTitle, titleChanged;
    char pad2e[2];
    int title, rank, character;
    void *sprite;
    ResultPopupText *texts[2];
    void *anims[3];
    CoinPrompt *prompt;
    CoinPopupDetail *detail;
    float alpha;
};

struct ResultScreenObj : ResultMid {
    virtual ~ResultScreenObj();
    char pad10[0x3c - 0x10];
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

CoinPopupDetail::~CoinPopupDetail() {
    void **it;
    for (it = sprites.data; it != sprites.data + sprites.b; ++it) Sprite_Destroy(*it, 1);
    for (it = bufs.data; it != bufs.data + bufs.b; ++it) {
        if (*it) delete (char *)*it;
    }
}

struct InputPlayer {
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual float Stick();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual unsigned int Pressed(int mask);
};

struct ResultPartE608Sprite {
    char pad[0x20];
    float alpha;
};

struct ResultPartE608 {
    void *vt;
    int idx;
    int timer;
    int phase;
    unsigned char done;
    char pad11[0x48 - 0x11];
    unsigned int col[4];
    char pad58[0x6c - 0x58];
    ResultPartE608Sprite *spr;
};

extern "C" {
extern void *GetInputManager(void);
extern InputPlayer *InputMgr_GetPlayer(void *mgr, int index);
extern void Sprite_AdvanceAnim(void *s, float dt);
extern const float lbl_806D86A4;
extern const float lbl_806D86E8;
extern const float lbl_806D8674;
extern const float lbl_806D878C;
extern const float lbl_806D8790;

void fn_8015E608(ResultPartE608 *o) {
    InputPlayer *pl;
    if (o->done == 1) return;
    pl = InputMgr_GetPlayer(GetInputManager(), 0);
    switch (o->phase) {
    case 0: {
        float t = (float)o->timer / lbl_806D86A4;
        unsigned int c;
        o->spr->alpha = t;
        c = __rlwimi(0xFFFFFF00, (int)(lbl_806D86E8 * t), 0, 24, 31);
        o->col[0] = c;
        o->col[1] = c;
        o->col[2] = c;
        o->col[3] = c;
        if (o->timer >= 30) {
            o->timer = 0;
            o->phase++;
        }
        break;
    }
    case 1:
        if (o->timer >= 600 || pl->Pressed(0x2000) || pl->Stick() >= lbl_806D8790) {
            o->timer = 0;
            o->phase++;
        }
        break;
    case 2: {
        float t = lbl_806D8674 - (float)o->timer / lbl_806D86A4;
        unsigned int c;
        o->spr->alpha = t;
        c = __rlwimi(0xFFFFFF00, (int)(lbl_806D86E8 * t), 0, 24, 31);
        o->col[0] = c;
        o->col[1] = c;
        o->col[2] = c;
        o->col[3] = c;
        if (o->timer >= 30) {
            o->timer = 0;
            o->done = 1;
            o->phase++;
        }
        break;
    }
    }
    o->timer++;
    Sprite_AdvanceAnim(o->spr, lbl_806D878C);
}
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
extern void fn_80160588(void *self, int n, int confirm);
extern void fn_80161720(CoinPopupDetail *self);
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
    fn_80161720((CoinPopupDetail *)o);
}

int fn_801618CC(Obj80161888 *o, int v, int unused) {
    if (o->ready == 0) return 0;
    o->next = v;
    o->cur = -1;
    fn_80160588(o, 0, unused);
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
extern void fn_8016039C(CoinPopupDetail *p);
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
    if (s->p58) fn_8016039C((CoinPopupDetail *)s->p58);
    fn_801678FC(7, 0.0f, 0.0f, 0.0f, s->alpha);
}

struct ResCtrlR {
    ResCtrlR();
    ~ResCtrlR() {}
    int id;
    int pad4;
    int mode;
    int padc;
    unsigned char enable;
    unsigned char pad11[3];
    float x;
    float y;
    float z;
    float u;
    float v;
    char pad28[0x34 - 0x28];
    int c0;
    int c1;
    int c2;
    int c3;
    char pad44[0x58 - 0x44];
};

extern void fn_80121E10(ResCtrlR *r);
extern void fn_8011FAFC_r(ResCtrlR *r, int n);
extern const float lbl_806D87CC;
extern const float lbl_806D87D0;
extern const float lbl_806D87D4;
extern const float lbl_806D87D8;
extern const float lbl_806D87DC;
extern const float lbl_806D87E0;
extern const float lbl_806D87E4;
extern const float lbl_806D87E8;
extern const float lbl_806D87EC;

void fn_8016039C(CoinPopupDetail *o) {
    void **it;
    void *mgr;
    if (o->on) {
        ResCtrlR r;
        r.mode = 2;
        r.u = lbl_806D87CC;
        r.v = lbl_806D87D0;
        r.enable = 1;
        r.x = lbl_806D87D4;
        r.y = lbl_806D87D8;
        r.z = lbl_806D87DC;
        r.c0 = 0x80;
        r.c1 = 0x80;
        r.c2 = 0x80;
        r.c3 = 0x80;
        fn_8011FAFC_r(&r, 4);
        fn_801A0004(o->h5c.s);
        if (o->extra) {
            fn_80121E10(&r);
            r.id = 0x1aea;
            r.enable = 1;
            r.x = lbl_806D87D4;
            r.y = lbl_806D87E0;
            r.z = lbl_806D87DC;
            fn_8011FAFC_r(&r, 4);
            fn_801A0004(o->h64.s);
            fn_80121E10(&r);
            r.id = 0x1875;
            r.enable = 1;
            r.x = lbl_806D87E4;
            r.y = lbl_806D87E8;
            r.z = lbl_806D87DC;
            fn_8011FAFC_r(&r, 4);
            fn_801A0004(o->h68.s);
            fn_80121E10(&r);
            r.id = 0x1874;
            r.enable = 1;
            r.x = lbl_806D87EC;
            r.y = lbl_806D87E8;
            r.z = lbl_806D87DC;
            fn_8011FAFC_r(&r, 4);
        }
    }
    for (it = o->sprites.data; it != o->sprites.data + o->sprites.b; ++it) fn_801A0004(*it);
    mgr = fn_801F8E58();
    {
        void **jt;
        for (jt = o->bufs.data; jt != o->bufs.data + o->bufs.b; ++jt) fn_801F8A34(mgr, *jt, 5);
    }
    fn_801A0004(o->h60.s);
}

typedef struct {
    int a;
    int a4;
    const char *textA;
    const char *textB;
    int b;
    int b14;
    const char *textC;
    const char *textD;
} PopupInfo;

typedef struct {
    int pad0;
    int pad4;
    int anim8;
    int animC;
    int anim10;
    int anim14;
    int anim18;
} PopupAnim;

extern PopupInfo *lbl_806CF908[2];
extern PopupAnim lbl_80368D80[];
extern int isJapanese(void);
extern void **fn_80146000(void *v, int i);
extern unsigned char fn_801A024C(void *s);
extern void Sprite_SetupAnim(void *sprite, int anim, int loop, int arg);
extern void fn_80161128(CoinPopupDetail *o);

static inline PopupInfo *PopupInfo_Get(int k) {
    return &lbl_806CF908[isJapanese()][k];
}

void fn_80161444(CoinPopupDetail *o) {
    int cnt = 0;
    void **it;
    for (it = o->sprites.data; it != o->sprites.data + o->sprites.b; ++it) {
        if (!fn_801A024C(*it)) cnt++;
    }
    if (cnt == 2) {
        if (o->mode == 0) {
            Sprite_SetupAnim(*fn_80146000(&o->sprites, 0), lbl_80368D80[PopupInfo_Get(o->idxA)->a].anim8, 1, 0);
        } else {
            Sprite_SetupAnim(*fn_80146000(&o->sprites, 1), lbl_80368D80[PopupInfo_Get(o->idxB)->b].anim8, 1, 0);
        }
        fn_80161128(o);
        o->x40 = 0x80;
        o->x44 = 0;
        o->state = 5;
        o->extra = 0;
        Sprite_SetupAnim(o->h5c.s, 0x11, 1, 0);
    }
}

void fn_80161720(CoinPopupDetail *o) {
    int anim;
    if (o->mode == 0) {
        anim = lbl_80368D80[PopupInfo_Get(o->idxA)->a].animC;
    } else {
        anim = lbl_80368D80[PopupInfo_Get(o->idxA)->a].anim14;
    }
    Sprite_SetupAnim(*fn_80146000(&o->sprites, 0), anim, 1, 0);
    if (o->mode == 1) {
        anim = lbl_80368D80[PopupInfo_Get(o->idxB)->b].animC;
    } else {
        anim = lbl_80368D80[PopupInfo_Get(o->idxB)->b].anim14;
    }
    Sprite_SetupAnim(*fn_80146000(&o->sprites, 1), anim, 1, 0);
    fn_80161128(o);
    o->state = 3;
}

extern void fn_801FE348(void);
extern void fn_801A0500(void *s);
extern void TexMgr_SetTexture(void *tm, const char *fmt, ...);
extern const char lbl_806D884C[4];

void fn_801615A4(CoinPopupDetail *o) {
    if (o->active) {
        fn_801FE348();
        if (o->mode == 0) {
            Sprite_SetupAnim(*fn_80146000(&o->sprites, 1), lbl_80368D80[PopupInfo_Get(o->idxB)->b].anim18, 1, 0);
            TexMgr_SetTexture(*fn_80146000(&o->bufs, 2), lbl_806D884C);
            TexMgr_SetTexture(*fn_80146000(&o->bufs, 3), lbl_806D884C);
        } else {
            Sprite_SetupAnim(*fn_80146000(&o->sprites, 0), lbl_80368D80[PopupInfo_Get(o->idxA)->a].anim18, 1, 0);
            TexMgr_SetTexture(*fn_80146000(&o->bufs, 0), lbl_806D884C);
            TexMgr_SetTexture(*fn_80146000(&o->bufs, 1), lbl_806D884C);
        }
        fn_801A0500(o->h60.s);
        fn_80161128(o);
        o->state = 4;
    }
}

typedef struct {
    char pad[0xc];
    float x;
    float y;
    float sx;
    float sy;
} PopupSprite;

typedef struct {
    char pad[0x20];
    unsigned int col;
} PopupText;

extern void Sprite_SetAnimParam(void *spr, short from, short to);
extern unsigned char lbl_80598A60[0x2a];
extern void fn_80160A90(CoinPopupDetail *o);

static inline void PopupSprite_SetPos(PopupSprite *s, float x, float y) {
    s->x = x;
    s->y = y;
}

static inline void PopupSprite_SetScale(PopupSprite *s, float k) {
    s->sx = k;
    s->sy = k;
}

static inline void PopupText_SetCol(PopupText *t, unsigned int c) {
    t->col = c;
}

#define POPUP_SPR(o, i) ((PopupSprite *)*fn_80146000(&(o)->sprites, (i)))
#define POPUP_TXT(o, i) ((PopupText *)*fn_80146000(&(o)->bufs, (i)))

void fn_80161128(CoinPopupDetail *o) {
    PopupSprite_SetPos(POPUP_SPR(o, 0), o->ax, o->ay);
    PopupSprite_SetPos(POPUP_SPR(o, 1), o->bx, o->by);
    Sprite_SetAnimParam(*fn_80146000(&o->sprites, 0), 0x23e7, 0x1ecd);
    Sprite_SetAnimParam(*fn_80146000(&o->sprites, 1), 0x23e7, 0x1ecd);
    {
        PopupInfo *inf = PopupInfo_Get(o->idxA);
        Sprite_SetAnimParam(*fn_80146000(&o->sprites, 0), 0x1cfb, inf->a4);
    }
    {
        PopupInfo *inf = PopupInfo_Get(o->idxB);
        Sprite_SetAnimParam(*fn_80146000(&o->sprites, 1), 0x1cfb, inf->b14);
    }
    Sprite_SetAnimParam(*fn_80146000(&o->sprites, 1), 0x1565, 0x1566);
    Sprite_SetAnimParam(*fn_80146000(&o->sprites, 1), 0x1cf5, 0x1cf6);
    Sprite_SetAnimParam(*fn_80146000(&o->sprites, 1), 0x1563, 0x1564);
    if ((signed char)lbl_80598A60[0x20] == 2) {
        Sprite_SetAnimParam(*fn_80146000(&o->sprites, 0), 0x1cfb, 0x1d01);
    }
    if (o->mode == 0) {
        PopupSprite_SetScale(POPUP_SPR(o, 0), 1.0f);
        PopupSprite_SetScale(POPUP_SPR(o, 1), 0.8f);
        PopupText_SetCol(POPUP_TXT(o, 0), 0xFFFFFFFF);
        PopupText_SetCol(POPUP_TXT(o, 1), 0xFFFFFFFF);
        PopupText_SetCol(POPUP_TXT(o, 2), 0xC3D7F5FF);
        PopupText_SetCol(POPUP_TXT(o, 3), 0xC3D7F5FF);
    } else {
        PopupSprite_SetScale(POPUP_SPR(o, 0), 0.8f);
        PopupSprite_SetScale(POPUP_SPR(o, 1), 1.0f);
        PopupText_SetCol(POPUP_TXT(o, 0), 0xC3D7F5FF);
        PopupText_SetCol(POPUP_TXT(o, 1), 0xC3D7F5FF);
        PopupText_SetCol(POPUP_TXT(o, 2), 0xFFFFFFFF);
        PopupText_SetCol(POPUP_TXT(o, 3), 0xFFFFFFFF);
    }
    fn_80160A90(o);
}

}

struct RYScene {
    virtual ~RYScene();
    virtual unsigned char v0C();
    virtual void v10();
};

struct RYKart {
    void *driver;
    int x4;
    float z;
};

struct RYKarts {
    RYScene *scene;
    void *lobj;
    RYKart *karts[13];
    unsigned char on;
};

struct RYSub {
    int n;
    float x;
    float y;
    float z;
};

struct RYEntry {
    int on;
    float x;
    float y;
    float z;
    float rx;
    float ry;
    float rz;
    float scale;
    float vx, vy, vz;
    RYSub subs[10];
};

struct RYPair {
    unsigned char stopped;
    char pad1[3];
    int timer;
    int interval;
    VObj *a;
    VObj *b;
    RYEntry e[3];
};

struct ResultPartYD {
    void *vt;
    char pad4[0x14 - 4];
    unsigned char active;
    char pad15[0x2c - 0x15];
    RYKarts *karts;
    char *buf;
    RYPair *pair;
    char pad38[0x90 - 0x38];
    char res90[1];
};

extern "C" {
extern void fn_8013D660(VObj *p, float x, float y);
extern void fn_8013D4B0(VObj *p, float a);
extern void fn_8013D608(VObj *p, float x, float y, float z);
extern void fn_8013D59C(VObj *p, float x, float y, float z);
extern void fn_8011FAB8(void);
extern void SetCourseScene3D(RYScene *s);
extern void LObjList_ApplyForCObj(void *l);
extern void CObj_DebugVizPathFlush(RYScene *s);
extern void KartDriver_RenderTimed(void *d, int a, int b);

static inline void RYEntry_Draw(RYPair *p, RYEntry *e) {
        if (e->on >= 0) {
            int j;
            float sc;
            for (j = 0; j < 10; j++) {
                if (e->subs[j].n >= 0) {
                    float t = (float)e->subs[j].n / 15.0f;
                    float ssc;
                    t = lbl_806D8674 - t;
                    ssc = 0.035f * t;
                    VObj *b = p->b;
                    fn_8013D660(b, e->subs[j].x, e->subs[j].y);
                    fn_8013D4B0(p->b, t);
                    fn_8013D608(p->b, ssc, ssc, ssc);
                    p->b->v0C();
                }
            }
            sc = 0.05f * e->scale;
            fn_8013D660(p->a, e->x, e->y);
            fn_8013D59C(p->a, 0.017453292f * e->rx, 0.017453292f * e->ry, 0.017453292f * e->rz);
            fn_8013D608(p->a, sc, sc, sc);
            p->a->v0C();
        }
}

static inline void RYPair_Draw(RYPair *p) {
    int i;
    for (i = 0; i < 3; i++) RYEntry_Draw(p, &p->e[i]);
}

static inline void RYKarts_Draw(RYKarts *k) {
    if (k->on) {
        SetCourseScene3D(k->scene);
        if (k->scene->v0C()) {
            int i;
            LObjList_ApplyForCObj(k->lobj);
            CObj_DebugVizPathFlush(k->scene);
            for (i = 0; i < 13; i++) {
                RYKart *kt = k->karts[i];
                if (!(kt->z < -70.0f || kt->z > 70.0f)) {
                    KartDriver_RenderTimed(kt->driver, 0, 1);
                }
            }
            k->scene->v10();
        }
        SetCourseScene3D(0);
    }
}

static inline void RYBuf_Draw(char *buf) {
    fn_8011FAFC(buf + 0x58, 0);
    fn_8011FAFC(buf, 0);
}

void fn_8015DEBC(ResultPartYD *o) {
    if (o->active) {
        RYBuf_Draw(o->buf);
        fn_8011F994(0);
        RYPair_Draw(o->pair);
        fn_8011FAB8();
        RYKarts_Draw(o->karts);
        fn_8011FAFC(o->res90, 7);
        HSD_StateInvalidate(-1);
        o->active = 0;
    }
}

}

extern "C" {
extern void *lbl_806D10A0;
extern unsigned char g_playerData[];
extern unsigned char get_title_result(void *t, int *a, int *b, int *c);

static inline void *TitleTracker_Get(void) {
    void *t = lbl_806D10A0;
    if (!t) t = 0;
    return t;
}

int has_title_changed(void) {
    int a;
    int c;
    int b;
    void *t = TitleTracker_Get();
    if (!t || !get_title_result(t, &a, &b, &c)) return 0;
    if (a == 0) return 0;
    if (a == g_playerData[0x19b] && b == g_playerData[0x19c] && c == g_playerData[0x1b1]) return 0;
    return 1;
}
}

extern "C" {
extern const float lbl_806D87C8;
extern const float lbl_806D87C4;
extern const float lbl_806D8848;
extern const float lbl_806D87F4;
extern void fn_801F93D0(void *t, float sx, float sy);
extern void fn_801F93C8(void *t, float angle);

void fn_80160A90(CoinPopupDetail *o) {
    float offset = lbl_806D87C8;
    float scale = lbl_806D87DC;
    float pos[12];
    if (isJapanese()) {
        offset = lbl_806D87C4;
        scale = lbl_806D8848;
    }
    fn_8019FF8C(*fn_80146000(&o->sprites, 0), 0x23e5, pos);
    fn_801F93EC(*fn_80146000(&o->bufs, 0), (12.0f + pos[0]) + offset, 12.0f + pos[1]);
    fn_801F93D0(*fn_80146000(&o->bufs, 0), pos[2] * scale, pos[3] * scale);
    fn_801F93C8(*fn_80146000(&o->bufs, 0), pos[4]);
    {
        unsigned int c = POPUP_TXT(o, 0)->col;
        c = __rlwimi(c, (int)(lbl_806D87F4 * pos[8]), 0, 24, 31);
        POPUP_TXT(o, 0)->col = c;
    }
    fn_8019FF8C(*fn_80146000(&o->sprites, 0), 0x1ecd, pos);
    fn_801F93EC(*fn_80146000(&o->bufs, 1), pos[0] + offset, pos[1]);
    fn_801F93D0(*fn_80146000(&o->bufs, 1), pos[2] * scale, pos[3] * scale);
    fn_801F93C8(*fn_80146000(&o->bufs, 1), pos[4]);
    {
        unsigned int c = POPUP_TXT(o, 1)->col;
        c = __rlwimi(c, (int)(lbl_806D87F4 * pos[8]), 0, 24, 31);
        POPUP_TXT(o, 1)->col = c;
    }
    fn_8019FF8C(*fn_80146000(&o->sprites, 1), 0x23e5, pos);
    fn_801F93EC(*fn_80146000(&o->bufs, 2), (12.0f + pos[0]) + offset, 12.0f + pos[1]);
    fn_801F93D0(*fn_80146000(&o->bufs, 2), pos[2] * scale, pos[3] * scale);
    fn_801F93C8(*fn_80146000(&o->bufs, 2), pos[4]);
    {
        unsigned int c = POPUP_TXT(o, 2)->col;
        c = __rlwimi(c, (int)(lbl_806D87F4 * pos[8]), 0, 24, 31);
        POPUP_TXT(o, 2)->col = c;
    }
    fn_8019FF8C(*fn_80146000(&o->sprites, 1), 0x1ecd, pos);
    fn_801F93EC(*fn_80146000(&o->bufs, 3), pos[0] + offset, pos[1]);
    fn_801F93D0(*fn_80146000(&o->bufs, 3), pos[2] * scale, pos[3] * scale);
    fn_801F93C8(*fn_80146000(&o->bufs, 3), pos[4]);
    {
        unsigned int c = POPUP_TXT(o, 3)->col;
        c = __rlwimi(c, (int)(lbl_806D87F4 * pos[8]), 0, 24, 31);
        POPUP_TXT(o, 3)->col = c;
    }
}
}


extern "C" {
extern int CreditMgr_GetCreditCount(int slot);
extern int CreditMgr_GetCoinsPerCredit(int slot);
extern void fn_801F8E90(void *text);
extern void fn_8019FF6C(void *sprite, int enabled);
extern PopupInputState *g_pInputState;

static inline PopupInputState *PopupInput_Get() {
    PopupInputState *p = g_pInputState;
    if (!p) p = 0;
    return p;
}

void fn_80160E04(CoinPopupDetail *o) {
    if (o->state < 2 && o->creditOn == 1) {
        unsigned char unavailable;
        int credits = CreditMgr_GetCreditCount(o->creditMgr);
        unavailable = 0;
        if (credits <= 0 || CreditMgr_GetCoinsPerCredit(o->creditMgr) == -1) unavailable = 1;
        if (!unavailable && o->credits != credits) {
            o->credits = credits;
            if (!isJapanese()) {
                PopupInfo *info = PopupInfo_Get(o->idxA);
                void **text = fn_80146000(&o->bufs, 0);
                TexMgr_SetTexture(*text, info->textA, CreditMgr_GetCreditCount(o->creditMgr));
                fn_801F8E90(*fn_80146000(&o->bufs, 0));
            } else {
                PopupInfo *info = PopupInfo_Get(o->idxA);
                void **text = fn_80146000(&o->bufs, 1);
                TexMgr_SetTexture(*text, info->textB, CreditMgr_GetCreditCount(o->creditMgr));
                fn_801F8E90(*fn_80146000(&o->bufs, 1));
            }
        } else if (unavailable == 1) {
            o->creditOn = 0;
            o->idxA = o->nextIdx;
            o->nextIdx = 0;
            o->mode = 0;
            {
                PopupInfo *info = PopupInfo_Get(o->idxA);
                TexMgr_SetTexture(*fn_80146000(&o->bufs, 0), info->textA);
            }
            {
                PopupInfo *info = PopupInfo_Get(o->idxA);
                TexMgr_SetTexture(*fn_80146000(&o->bufs, 1), info->textB);
            }
            fn_801F8E90(*fn_80146000(&o->bufs, 0));
            fn_801F8E90(*fn_80146000(&o->bufs, 1));
            if (o->state == 0) {
                PopupInfo *info = PopupInfo_Get(o->idxA);
                Sprite_SetupAnim(*fn_80146000(&o->sprites, 0), lbl_80368D80[info->a].pad0, 1, 0);
            } else {
                PopupInfo *info = PopupInfo_Get(o->idxA);
                Sprite_SetupAnim(*fn_80146000(&o->sprites, 0), lbl_80368D80[info->a].pad4, 1, 0);
                fn_8019FF6C(*fn_80146000(&o->sprites, 0), 1);
            }
            if (PopupInput_Get()) {
                PopupInputState *input = PopupInput_Get();
                input->active = 1;
                input->x18 = 0;
                input->x1c = 0;
            }
            o->changed = 1;
            fn_80161128(o);
        }
    }
}
}


extern "C" {
extern const float lbl_806D880C;
extern const float lbl_806D8834;
extern const float lbl_806D87F0;
extern const float lbl_806D8838;
extern const float lbl_806D8830;
extern int Clamp_Int(int v, int lo, int hi);
extern void fn_801FE390(void);

void fn_80160588(void *self, int step, int inputConfirm) {
    CoinPopupDetail *o = (CoinPopupDetail *)self;
    unsigned char confirm = inputConfirm;
    if (o->state == 0) {
        if (o->x44 <= 10) {
            o->x40 = (int)(lbl_806D8834 * ((float)o->x44 / lbl_806D880C));
            o->x44++;
        }
        int cnt = 0;
        void **it;
        for (it = o->sprites.data; it != o->sprites.data + o->sprites.b; ++it) {
            if (!fn_801A024C(*it)) cnt++;
        }
        if (cnt == 2 && fn_801A024C(o->h60.s) != 1) {
            Sprite_SetupAnim(o->h60.s, 0x9c, 1, 0);
            fn_8019FF6C(o->h60.s, 1);
            o->state = 1;
            if (PopupInput_Get()) {
                PopupInputState *input = PopupInput_Get();
                input->active = 1;
                input->x18 = 0;
                input->x1c = 0;
            }
            o->extra = 1;
            o->pad14 = -1;
        }
    } else if (o->state == 1) {
        if (!confirm) o->changed = 0;
        if (confirm == 1 && !o->changed) {
            o->state = 2;
            if (PopupInput_Get()) {
                PopupInputState *input = PopupInput_Get();
                input->active = 0;
                input->x18 = 0;
                input->x1c = 0;
            }
        } else {
            int old = o->mode;
            o->mode = Clamp_Int(old + step, 0, 1);
            if (old != o->mode) fn_801FE390();
        }
    } else if (o->state == 2) {
        fn_80161720(o);
    } else if (o->state == 3) {
        fn_801615A4(o);
    } else if (o->state == 4) {
        fn_80161444(o);
    } else if (o->state == 5) {
        if (o->x44 <= 15) {
            o->x40 = (int)(lbl_806D8834 * (lbl_806D87DC - (float)o->x44 / lbl_806D87F0));
            o->x44++;
        }
        int cnt = 0;
        void **it;
        for (it = o->sprites.data; it != o->sprites.data + o->sprites.b; ++it) {
            if (!fn_801A024C(*it)) cnt++;
        }
        if (cnt == 2) o->state = 6;
    }
    if (o->pad14 != o->mode && o->state < 3 && o->state > 0) {
        int anim;
        if (o->mode == 0) anim = lbl_80368D80[PopupInfo_Get(o->idxA)->a].pad4;
        else anim = lbl_80368D80[PopupInfo_Get(o->idxA)->a].anim14;
        Sprite_SetupAnim(*fn_80146000(&o->sprites, 0), anim, 1, 0);
        if (o->mode == 1) anim = lbl_80368D80[PopupInfo_Get(o->idxB)->b].pad4;
        else anim = lbl_80368D80[PopupInfo_Get(o->idxB)->b].anim14;
        Sprite_SetupAnim(*fn_80146000(&o->sprites, 1), anim, 1, 0);
        fn_8019FF6C(*fn_80146000(&o->sprites, 0), 1);
        fn_8019FF6C(*fn_80146000(&o->sprites, 1), 1);
        ((PopupCursorSprite *)o->h60.s)->y = o->mode == 0 ? lbl_806D87C8 : lbl_806D8838;
        fn_80161128(o);
        o->pad14 = o->mode;
    }
    void **it;
    for (it = o->sprites.data; it != o->sprites.data + o->sprites.b; ++it) {
        Sprite_AdvanceAnim(*it, lbl_806D8830);
    }
    Sprite_AdvanceAnim(o->h5c.s, lbl_806D8830);
    Sprite_AdvanceAnim(o->h60.s, lbl_806D8830);
    Sprite_AdvanceAnim(o->h64.s, lbl_806D8830);
    Sprite_AdvanceAnim(o->h68.s, lbl_806D8830);
    fn_80160E04(o);
    fn_80160A90(o);
}
}


extern "C" {
extern unsigned char SoundMgr_Play(int id);
extern void Sprite_SetAnimTime(void *s, float time);
extern unsigned char fn_8019FE78(void *s);
extern void fn_80140344(void *p);
extern const float lbl_806D8678;
extern const float lbl_806D8784;
extern const float lbl_806D86F0;
extern const float lbl_806D8788;

void fn_8015E1E8(ResultPartBUpdate *o) {
    if (o->stage == 6) return;
    if (!o->soundStarted) {
        if (SoundMgr_Play(o->sound)) o->soundStarted = 1;
    }
    unsigned char pressed = PopupInput_Get()->x18 == 1;
    switch (o->stage) {
    case 0: {
        unsigned int c = (unsigned char)(int)(lbl_806D86E8 * (lbl_806D8674 - o->timer / lbl_806D86A4));
        o->fadeCol[0] = c;
        o->fadeCol[1] = c;
        o->fadeCol[2] = c;
        o->fadeCol[3] = c;
        if (o->timer >= lbl_806D86A4) {
            o->timer = lbl_806D8678;
            o->stage = 1;
        }
        break;
    }
    case 1:
        if (o->timer >= lbl_806D8784 || (unsigned char)pressed) {
            o->timer = lbl_806D8678;
            o->stage = 2;
        }
        break;
    case 2: {
        unsigned int c = (unsigned char)(int)(lbl_806D8784 * (o->timer / lbl_806D86A4));
        o->innerCol[0] = c;
        o->innerCol[1] = c;
        o->innerCol[2] = c;
        o->innerCol[3] = c;
        if (o->timer >= lbl_806D86A4) {
            o->timer = lbl_806D8678;
            o->stage = 3;
            Sprite_SetAnimTime(o->sprite, lbl_806D8678);
        }
        break;
    }
    case 3:
        if (!fn_8019FE78(o->sprite)) {
            o->timer = lbl_806D8678;
            o->stage = 4;
        }
        break;
    case 4:
        if (o->timer >= lbl_806D86F0 || (unsigned char)pressed == 1) {
            o->timer = lbl_806D8678;
            o->stage = 5;
        }
        break;
    case 5: {
        unsigned int c = (unsigned char)(int)(lbl_806D86E8 * (o->timer / lbl_806D8788));
        o->fadeCol[0] = c;
        o->fadeCol[1] = c;
        o->fadeCol[2] = c;
        o->fadeCol[3] = c;
        if (o->timer >= lbl_806D8788) {
            o->timer = lbl_806D8678;
            o->stage = 6;
        }
        break;
    }
    }
    o->timer += lbl_806D8674;
    o->inner->v14();
    fn_80140344(o->p1c);
    if (o->stage >= 3) Sprite_AdvanceAnim(o->sprite, lbl_806D878C);
    if (!o->on) o->on = 1;
}
}



extern "C" {
extern const float lbl_806D8818, lbl_806D881C, lbl_806D8850, lbl_806D8854;
extern const float lbl_806D8804, lbl_806D87FC, lbl_806D8800;
extern void fn_801F8FCC(void *text, int mode);
}

CoinPopupDetail::CoinPopupDetail(int initialMode, int enabled, int index)
    : active(enabled), sprites(2), state(0), pad14(2), mode(initialMode),
      ax(lbl_806D8818), ay(lbl_806D8850), bx(lbl_806D881C), by(lbl_806D8850),
      idxA(index), idxB(index), credits(-1), creditOn(0), on(0), extra(0),
      nextIdx(0), x40(0), x44(0), creditMgr(-1), changed(1), bufs(4),
      h5c(new ResultPopupSprite(0x12, 1, 0)),
      h60(new ResultPopupSprite(0x9d, 1, 0)),
      h64(new ResultPopupSprite(0x4a, 1, 0)),
      h68(new ResultPopupSprite(0x74, 1, 0)) {
    if (idxA == 4 || idxA == 5 || idxA == 7 || idxA == 8) {
        creditOn = 1;
        nextIdx = idxA;
        int idx = 3;
        if (!lbl_80598A60[0x27]) idx = 2;
        idxA = idx;
        switch (nextIdx) {
        case 4: creditMgr = 2; break;
        case 5: creditMgr = 3; break;
        case 7: creditMgr = 1; break;
        case 8: creditMgr = 1; break;
        }
    }
    void **it;
    for (it = sprites.data; it != sprites.data + sprites.b; ++it) *it = 0;
    for (it = bufs.data; it != bufs.data + bufs.b; ++it) *it = 0;
    *fn_80146000(&sprites, 0) = new ResultPopupSprite(
        mode == 0 ? lbl_80368D80[PopupInfo_Get(idxA)->a].pad0 : lbl_80368D80[PopupInfo_Get(idxA)->a].anim10,
        1, 0);
    *fn_80146000(&sprites, 1) = new ResultPopupSprite(
        mode == 1 ? lbl_80368D80[PopupInfo_Get(idxB)->b].pad0 : lbl_80368D80[PopupInfo_Get(idxB)->b].anim10,
        1, 0);
    Sprite_SetAnimParam(*fn_80146000(&sprites, 0), 0x23e7, 0x1ecd);
    Sprite_SetAnimParam(*fn_80146000(&sprites, 1), 0x23e7, 0x1ecd);
    for (it = bufs.data; it != bufs.data + bufs.b; ++it) {
        *it = new ResultPopupText;
        TexMgr_SetTexture(*it, lbl_806D884C);
        ((ResultPopupText *)*it)->font = 1;
        fn_801F8FCC(*it, 1);
        ((ResultPopupText *)*it)->advance = lbl_806D8854;
    }
    {
        PopupInfo *info = PopupInfo_Get(idxA);
        TexMgr_SetTexture(*fn_80146000(&bufs, 0), info->textA);
    }
    {
        PopupInfo *info = PopupInfo_Get(idxA);
        TexMgr_SetTexture(*fn_80146000(&bufs, 1), info->textB);
    }
    {
        PopupInfo *info = PopupInfo_Get(idxB);
        TexMgr_SetTexture(*fn_80146000(&bufs, 2), info->textC);
    }
    {
        PopupInfo *info = PopupInfo_Get(idxB);
        TexMgr_SetTexture(*fn_80146000(&bufs, 3), info->textD);
    }
    for (it = bufs.data; it != bufs.data + bufs.b; ++it) fn_801F8E90(*it);
    fn_80160E04(this);
    PopupSprite_SetPos((PopupSprite *)h5c.s, lbl_806D87D4, lbl_806D8850);
    PopupSprite_SetPos((PopupSprite *)h60.s, lbl_806D87D4, lbl_806D8850);
    ((ResultPopupSprite *)h60.s)->angle = mode == 0 ? lbl_806D87C8 : lbl_806D8838;
    PopupSprite_SetPos((PopupSprite *)h64.s, lbl_806D8804, lbl_806D87E8);
    fn_8019FF6C(h64.s, 1);
    PopupSprite_SetPos((PopupSprite *)h68.s, lbl_806D87FC, lbl_806D8800);
    fn_8019FF6C(h68.s, 1);
    fn_80161128(this);
}

extern "C" {
extern unsigned char fn_80169DF0(void);
extern void InitRumbleController(int on);
extern void PreloadResource(int id);
extern const float lbl_806D8828, lbl_806D8858, lbl_806D885C;
extern const float lbl_806D8860, lbl_806D8864, lbl_806D8868, lbl_806D886C, lbl_806D8870;
extern const float lbl_806D8874, lbl_806D8878;
extern const char lbl_806CF914[4], lbl_806CF918[4], lbl_806CF91C[4];
extern int g_characterId;
extern const char *get_title_name(void *, int, unsigned char, int, int);
extern const char *get_title_name_global(void *);
extern void SpriteGroup_CreateOrInit(void **, const char *, int, float, float);
extern void SpriteAnimParamBlock_SetAnimParamCached(void *, int, int);
extern void *SpriteHandle_CreateDefault(ResCtrlR *, int);
extern void SpriteHandle_SetActiveFlag(void *, int);
extern void fn_8011F804(void *, float, float);
extern void SpriteHandle_RecomputeCull(void *);
extern void fn_8023CD3C(CoinPrompt *, float, float);
extern void fn_8023CCF8(CoinPrompt *, float, float);
extern void fn_8023CCA0(CoinPrompt *, int);
}

ResultSub::ResultSub(int a, int b) : ResultMid(b) {
    mode = a;
    state = 0;
    timer = lbl_806D87C8;
    flag = fn_80169DF0();
    timer2 = lbl_806D87C8;
    hasTitle = 1;
    titleChanged = 0;
    resource = 0x1ad9;
    title = 0;
    rank = 0;
    character = 0;
    sprite = (void *)-1;
    scale = lbl_806D8828;
    alpha = lbl_806D87C8;
    detail = 0;
    if (!g_playerData[0x19b]) hasTitle = 0;
    void *tracker = TitleTracker_Get();
    if (tracker) get_title_result(tracker, &title, &rank, &character);
    InitRumbleController(1);
    PreloadResource(0x1ad9);
    PreloadResource(0x1ada);
    anims[0] = 0;
    anims[1] = 0;
    anims[2] = 0;
    SpriteGroup_CreateOrInit(&anims[0], lbl_806CF914, 0, lbl_806D87D4, lbl_806D87D8);
    SpriteGroup_CreateOrInit(&anims[1], lbl_806CF918, 0, lbl_806D87D4, lbl_806D87D8);
    SpriteGroup_CreateOrInit(&anims[2], lbl_806CF91C, 0, lbl_806D8858, lbl_806D885C);
    SpriteAnimParamBlock_SetAnimParamCached(anims[2], 0x1ad4, 0x1ad9);
    ((ResultPopupSprite *)*(void **)anims[1])->alpha = lbl_806D87C8;
    fn_8019FF6C(*(void **)anims[1], 1);
    texts[0] = new ResultPopupText;
    int charId = g_characterId;
    TexMgr_SetTexture(texts[0], get_title_name(TitleTracker_Get(), title, rank, charId, character));
    texts[0]->color = 0xFFFFFF00;
    texts[0]->font = 1;
    fn_801F8FCC(texts[0], 1);
    if (isJapanese() == 1) {
        fn_801F93D0(texts[0], lbl_806D8860, lbl_806D8860);
        texts[0]->advance = lbl_806D8864;
    }
    fn_801F8E90(texts[0]);
    texts[1] = new ResultPopupText;
    TexMgr_SetTexture(texts[1], get_title_name_global(TitleTracker_Get()));
    texts[1]->color = 0xFFFFFF00;
    fn_801F8FCC(texts[1], 1);
    texts[1]->advance = lbl_806D8828;
    if (!isJapanese()) fn_801F93EC(texts[1], lbl_806D8868, lbl_806D886C);
    else fn_801F93EC(texts[1], lbl_806D8870, lbl_806D886C);
    fn_801F8E90(texts[1]);
    PreloadResource(0x152c);
    ResCtrlR r;
    r.id = 0x152c;
    sprite = SpriteHandle_CreateDefault(&r, 1);
    SpriteHandle_SetActiveFlag(sprite, 0);
    fn_8011F804(sprite, lbl_806D87D4, lbl_806D886C);
    SpriteHandle_RecomputeCull(sprite);
    prompt = new CoinPrompt(0x74, -1, 0x1872, -1, 5);
    fn_8023CD3C(prompt, lbl_806D8874, lbl_806D8800);
    fn_8023CCF8(prompt, lbl_806D8878, lbl_806D87E8);
    fn_8023CCA0(prompt, 0);
}

extern "C" {
extern int rand(void);
extern const float lbl_806D86EC, lbl_806D8770, lbl_806D8774, lbl_806D8778, lbl_806D877C, lbl_806D8780;

static inline void RYSub_Reset(RYSub *sub) {
    sub->n = -1;
    sub->x = sub->y = sub->z = lbl_806D8678;
}

static inline void RYEntry_Reset(RYEntry *entry) {
    entry->on = -1;
    entry->x = entry->y = entry->z = lbl_806D8678;
    entry->rx = entry->ry = entry->rz = lbl_806D8678;
    entry->vx = entry->vy = entry->vz = lbl_806D8678;
    entry->scale = lbl_806D8674;
    for (int j = 0; j < 10; ++j) RYSub_Reset(&entry->subs[j]);
}

static inline void RYEntry_AdvanceSubs(RYEntry *entry) {
    for (int j = 0; j < 10; ++j) {
        RYSub *sub = &entry->subs[j];
        if (sub->n >= 0) {
            if (++sub->n >= 15) RYSub_Reset(sub);
        }
    }
}

void fn_8015D9F0(RYPair *p) {
    if (!p->stopped) {
        if (++p->timer >= p->interval) {
            for (int i = 0; i < 3; ++i) {
                if (p->e[i].on < 0) {
                    p->e[i].on = 0;
                    p->e[i].vx = lbl_806D86EC * (float)-(rand() % 20 + 40);
                    p->e[i].vy = lbl_806D8678;
                    p->e[i].vz = lbl_806D8678;
                    p->e[i].x = lbl_806D8770 + (float)(rand() % 600);
                    p->e[i].y = lbl_806D8774;
                    break;
                }
            }
            p->timer = 0;
            p->interval = rand() % 100 + 60;
        }
    }
    for (int i = 0; i < 3; ++i) {
        if (p->e[i].on >= 0) {
            p->e[i].vy += lbl_806D86EC;
            p->e[i].x += p->e[i].vx;
            p->e[i].y += p->e[i].vy;
            p->e[i].on++;
            if ((p->e[i].on & 3) == 0) {
                RYEntry *entry = &p->e[i];
                for (int j = 0; j < 10; ++j) {
                    RYSub *sub = &entry->subs[j];
                    if (sub->n < 0) {
                        sub->n = 0;
                        sub->x = (lbl_806D86EC * (float)(rand() % 70) + p->e[i].x) + lbl_806D8778;
                        sub->y = (p->e[i].y - lbl_806D86EC * (float)(rand() % 150)) - lbl_806D877C;
                        sub->z = p->e[i].z;
                        break;
                    }
                }
            }
            RYEntry_AdvanceSubs(&p->e[i]);
            if (p->e[i].y >= lbl_806D8780) RYEntry_Reset(&p->e[i]);
        }
    }
}
}

extern "C" {
extern unsigned long strlen(const char *text);
extern const char lbl_803682B0[];
extern ResultMessageRecord lbl_80490080[98];
extern const char lbl_806D8650[4];
extern const char lbl_806D8654[4];
extern const char lbl_806D865C[4];

/* Initialize cached lengths for the existing result-message records. */
void fn_8015E928(void) {
    const char *pool = lbl_803682B0;
    lbl_80490080[0].length = strlen(pool + 0x484);
    lbl_80490080[1].length = strlen(pool + 0x498);
    lbl_80490080[2].length = strlen(pool + 0x4ac);
    lbl_80490080[3].length = strlen(pool + 0x4b8);
    lbl_80490080[4].length = strlen(pool + 0x4c8);
    lbl_80490080[5].length = strlen(pool + 0x4d4);
    lbl_80490080[6].length = strlen(pool + 0x4e4);
    lbl_80490080[7].length = strlen(pool + 0x4f8);
    lbl_80490080[8].length = strlen(pool + 0x50c);
    lbl_80490080[9].length = strlen(pool + 0x51c);
    lbl_80490080[10].length = strlen(pool + 0x530);
    lbl_80490080[11].length = strlen(pool + 0x548);
    lbl_80490080[12].length = strlen(pool + 0x558);
    lbl_80490080[13].length = strlen(pool + 0x568);
    lbl_80490080[14].length = strlen(lbl_806D8650);
    lbl_80490080[15].length = strlen(pool + 0x580);
    lbl_80490080[16].length = strlen(pool + 0x590);
    lbl_80490080[17].length = strlen(pool + 0x5a4);
    lbl_80490080[18].length = strlen(pool + 0x5b4);
    lbl_80490080[19].length = strlen(pool + 0x5c8);
    lbl_80490080[20].length = strlen(pool + 0x5d8);
    lbl_80490080[21].length = strlen(pool + 0x5e8);
    lbl_80490080[22].length = strlen(pool + 0x5f8);
    lbl_80490080[23].length = strlen(pool + 0x604);
    lbl_80490080[24].length = strlen(pool + 0x614);
    lbl_80490080[25].length = strlen(pool + 0x624);
    lbl_80490080[26].length = strlen(pool + 0x630);
    lbl_80490080[27].length = strlen(pool + 0x640);
    lbl_80490080[28].length = strlen(pool + 0x650);
    lbl_80490080[29].length = strlen(pool + 0x664);
    lbl_80490080[30].length = strlen(pool + 0x678);
    lbl_80490080[31].length = strlen(pool + 0x68c);
    lbl_80490080[32].length = strlen(pool + 0x69c);
    lbl_80490080[33].length = strlen(pool + 0x6a8);
    lbl_80490080[34].length = strlen(pool + 0x6bc);
    lbl_80490080[35].length = strlen(pool + 0x6cc);
    lbl_80490080[36].length = strlen(pool + 0x6e0);
    lbl_80490080[37].length = strlen(pool + 0x6f0);
    lbl_80490080[38].length = strlen(pool + 0x700);
    lbl_80490080[39].length = strlen(pool + 0x710);
    lbl_80490080[40].length = strlen(pool + 0x720);
    lbl_80490080[41].length = strlen(pool + 0x734);
    lbl_80490080[42].length = strlen(pool + 0x744);
    lbl_80490080[43].length = strlen(pool + 0x754);
    lbl_80490080[44].length = strlen(pool + 0x764);
    lbl_80490080[45].length = strlen(pool + 0x778);
    lbl_80490080[46].length = strlen(pool + 0x788);
    lbl_80490080[47].length = strlen(pool + 0x79c);
    lbl_80490080[48].length = strlen(pool + 0x7ac);
    lbl_80490080[49].length = strlen(pool + 0x7bc);
    lbl_80490080[50].length = strlen(pool + 0x7cc);
    lbl_80490080[51].length = strlen(pool + 0x7e0);
    lbl_80490080[52].length = strlen(pool + 0x7f0);
    lbl_80490080[53].length = strlen(pool + 0x800);
    lbl_80490080[54].length = strlen(pool + 0x810);
    lbl_80490080[55].length = strlen(pool + 0x820);
    lbl_80490080[56].length = strlen(pool + 0x834);
    lbl_80490080[57].length = strlen(pool + 0x840);
    lbl_80490080[58].length = strlen(pool + 0x834);
    lbl_80490080[59].length = strlen(pool + 0x850);
    lbl_80490080[60].length = strlen(pool + 0x834);
    lbl_80490080[61].length = strlen(pool + 0x860);
    lbl_80490080[62].length = strlen(pool + 0x834);
    lbl_80490080[63].length = strlen(pool + 0x874);
    lbl_80490080[64].length = strlen(pool + 0x834);
    lbl_80490080[65].length = strlen(pool + 0x884);
    lbl_80490080[66].length = strlen(pool + 0x834);
    lbl_80490080[67].length = strlen(pool + 0x898);
    lbl_80490080[68].length = strlen(pool + 0x834);
    lbl_80490080[69].length = strlen(pool + 0x8a4);
    lbl_80490080[70].length = strlen(pool + 0x834);
    lbl_80490080[71].length = strlen(pool + 0x8b4);
    lbl_80490080[72].length = strlen(pool + 0x834);
    lbl_80490080[73].length = strlen(pool + 0x8c4);
    lbl_80490080[74].length = strlen(pool + 0x8d4);
    lbl_80490080[75].length = strlen(pool + 0x8e0);
    lbl_80490080[76].length = strlen(lbl_806D8654);
    lbl_80490080[77].length = strlen(pool + 0x8f0);
    lbl_80490080[78].length = strlen(lbl_806D8654);
    lbl_80490080[79].length = strlen(lbl_806D865C);
    lbl_80490080[80].length = strlen(pool + 0x8fc);
    lbl_80490080[81].length = strlen(pool + 0x910);
    lbl_80490080[82].length = strlen(pool + 0x484);
    lbl_80490080[83].length = strlen(pool + 0x920);
    lbl_80490080[84].length = strlen(pool + 0x910);
    lbl_80490080[85].length = strlen(pool + 0x484);
    lbl_80490080[86].length = strlen(pool + 0x930);
    lbl_80490080[87].length = strlen(pool + 0x484);
    lbl_80490080[88].length = strlen(pool + 0x940);
    lbl_80490080[89].length = strlen(pool + 0x954);
    lbl_80490080[90].length = strlen(pool + 0x484);
    lbl_80490080[91].length = strlen(pool + 0x964);
    lbl_80490080[92].length = strlen(pool + 0x970);
    lbl_80490080[93].length = strlen(pool + 0x980);
    lbl_80490080[94].length = strlen(pool + 0x990);
    lbl_80490080[95].length = strlen(pool + 0x9a0);
    lbl_80490080[96].length = strlen(pool + 0x9b0);
    lbl_80490080[97].length = strlen(pool + 0x9c4);
}
}

__declspec(section ".ctors") static void (*const resultMessageInit)(void) = fn_8015E928;


extern "C" {
extern const float lbl_80368704[][4];
extern const float lbl_806D8758, lbl_806D875C, lbl_806D8760;
extern void fn_80169468(int mode, int resource, int flags, float x, float y,
                        float r, float g, float b, float alpha);

void fn_8015D4F8(void *unused, int color, const char *text, float x, float y) {
    if (!text) return;
    unsigned long length = strlen(text);
    float alpha = lbl_806D8674;
    if (y >= lbl_806D8758) alpha -= (y - lbl_806D8758) * lbl_806D875C;
    const float *r = &lbl_80368704[color][0];
    const float *g = &lbl_80368704[color][1];
    const float *b = &lbl_80368704[color][2];
    for (unsigned int i = 0; i < length; ++i, ++text) {
        if (!*text) return;
        if (*text == 'i') {
            fn_80169468(1, 0x1dc5, 0, lbl_806D8760 * (float)i + x, y, *r, *g, *b, alpha);
        } else if (*text >= 'A' && *text <= 'Z') {
            fn_80169468(1, *text + 0x1d60, 0, lbl_806D8760 * (float)i + x, y, *r, *g, *b, alpha);
        } else if (*text >= 'a' && *text <= 'z') {
            fn_80169468(1, *text + 0x1d40, 0, lbl_806D8760 * (float)i + x, y, *r, *g, *b, alpha);
        } else if (*text == '.') {
            fn_80169468(1, 0x1dbb, 0, lbl_806D8760 * (float)i + x, y, *r, *g, *b, alpha);
        } else if (*text == '<') {
            fn_80169468(1, 0x1dbc, 0, lbl_806D8760 * (float)i + x, y, *r, *g, *b, alpha);
        } else if (*text == '>') {
            fn_80169468(1, 0x1dbd, 0, lbl_806D8760 * (float)i + x, y, *r, *g, *b, alpha);
        } else if (*text == '(') {
            fn_80169468(1, 0x1dbe, 0, lbl_806D8760 * (float)i + x, y, *r, *g, *b, alpha);
        } else if (*text == ')') {
            fn_80169468(1, 0x1dbf, 0, lbl_806D8760 * (float)i + x, y, *r, *g, *b, alpha);
        } else if (*text == '2') {
            fn_80169468(1, 0x1dc0, 0, lbl_806D8760 * (float)i + x, y, *r, *g, *b, alpha);
        } else if (*text == '?') {
            fn_80169468(1, 0x1dc1, 0, lbl_806D8760 * (float)i + x, y, *r, *g, *b, alpha);
        } else if (*text == '+') {
            fn_80169468(1, 0x1dc2, 0, lbl_806D8760 * (float)i + x, y, *r, *g, *b, alpha);
        } else if (*text == '-') {
            fn_80169468(1, 0x1dc3, 0, lbl_806D8760 * (float)i + x, y, *r, *g, *b, alpha);
        } else if (*text == '&') {
            fn_80169468(1, 0x1dc4, 0, lbl_806D8760 * (float)i + x, y, *r, *g, *b, alpha);
        }
    }
}
}
