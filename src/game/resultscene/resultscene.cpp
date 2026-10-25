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
    ~CoinPopupDetail();
    unsigned char active;
    char pad1[3];
    PtrVec sprites;
    int state;
    int pad14;
    int mode;
    float ax;
    float ay;
    float bx;
    float by;
    int idxA;
    int idxB;
    char pad34[0x39 - 0x34];
    unsigned char on;
    unsigned char extra;
    char pad3b[0x40 - 0x3b];
    int x40;
    int x44;
    char pad48[0x50 - 0x48];
    PtrVec bufs;
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

CoinPopupDetail::~CoinPopupDetail() {
    void **it;
    for (it = sprites.data; it != sprites.data + sprites.n; ++it) Sprite_Destroy(*it, 1);
    for (it = bufs.data; it != bufs.data + bufs.n; ++it) {
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
extern void fn_80160588(void *self, int n);
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
    char pad44[0x4c - 0x44];
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
    for (it = o->sprites.data; it != o->sprites.data + o->sprites.n; ++it) fn_801A0004(*it);
    mgr = fn_801F8E58();
    {
        void **jt;
        for (jt = o->bufs.data; jt != o->bufs.data + o->bufs.n; ++jt) fn_801F8A34(mgr, *jt, 5);
    }
    fn_801A0004(o->h60.s);
}

typedef struct {
    int a;
    int a4;
    char pad8[0x10 - 8];
    int b;
    int b14;
    char pad18[0x20 - 0x18];
} PopupInfo;

typedef struct {
    int pad0;
    int pad4;
    int anim8;
    int animC;
    int pad10;
    int anim14;
    int anim18;
} PopupAnim;

extern PopupInfo *lbl_806CF908[2];
extern PopupAnim lbl_80368D80[];
extern int isJapanese(void);
extern void **fn_80146000(PtrVec *v, int i);
extern unsigned char fn_801A024C(void *s);
extern void Sprite_SetupAnim(void *sprite, int anim, int loop, int arg);
extern void fn_80161128(CoinPopupDetail *o);

static inline PopupInfo *PopupInfo_Get(int k) {
    return &lbl_806CF908[isJapanese()][k];
}

void fn_80161444(CoinPopupDetail *o) {
    int cnt = 0;
    void **it;
    for (it = o->sprites.data; it != o->sprites.data + o->sprites.n; ++it) {
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
