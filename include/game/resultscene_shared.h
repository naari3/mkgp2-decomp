#ifndef GAME_RESULTSCENE_SHARED_H
#define GAME_RESULTSCENE_SHARED_H

#include "game/resultscene_private.h"
#include "game/singleton.h"

typedef struct {
    int pad0;
    int pad4;
    int anim8;
    int animC;
    int anim10;
    int anim14;
    int anim18;
} PopupAnim;

/* This TU owns its rodata (0x803682B0..0x80369238). Code reaches it through
 * the section anchor, which is what schedules the pool address early in the
 * ResultPartY ctor. */
extern "C" {
extern const char lbl_806D8798[];
extern const char lbl_806D879C[];
extern const char lbl_806D87A4[];
extern const char lbl_806D87AC[];
extern const char lbl_806D87B4[];
extern const char lbl_806D87BC[];
extern const unsigned char resultscene_rodata_803682B0[0x408];
extern const int lbl_803686B8[13];
extern const float lbl_803686EC[3];
extern const float lbl_803686F8[3];
extern const float resultscene_rodata_80368704[3][4];
extern const char lbl_80368734[];
extern const char lbl_80368748[];
extern const char lbl_8036875C[];
extern const char lbl_80368768[];
extern const char lbl_80368778[];
extern const char lbl_80368784[];
extern const char lbl_80368794[];
extern const char lbl_803687A8[];
extern const char lbl_803687BC[];
extern const char lbl_803687CC[];
extern const char lbl_803687E0[];
extern const char lbl_803687F8[];
extern const char lbl_80368808[];
extern const char lbl_80368818[];
extern const char lbl_80368830[];
extern const char lbl_80368840[];
extern const char lbl_80368854[];
extern const char lbl_80368864[];
extern const char lbl_80368878[];
extern const char lbl_80368888[];
extern const char lbl_80368898[];
extern const char lbl_803688A8[];
extern const char lbl_803688B4[];
extern const char lbl_803688C4[];
extern const char lbl_803688D4[];
extern const char lbl_803688E0[];
extern const char lbl_803688F0[];
extern const char lbl_80368900[];
extern const char lbl_80368914[];
extern const char lbl_80368928[];
extern const char lbl_8036893C[];
extern const char lbl_8036894C[];
extern const char lbl_80368958[];
extern const char lbl_8036896C[];
extern const char lbl_8036897C[];
extern const unsigned char data_8048FE08_rodata_80368990[0x10];
extern const char lbl_803689A0[];
extern const char lbl_803689B0[];
extern const char lbl_803689C0[];
extern const char lbl_803689D0[];
extern const char lbl_803689E4[];
extern const char lbl_803689F4[];
extern const char lbl_80368A04[];
extern const char lbl_80368A14[];
extern const char lbl_80368A28[];
extern const char lbl_80368A38[];
extern const char lbl_80368A4C[];
extern const char lbl_80368A5C[];
extern const char lbl_80368A6C[];
extern const char lbl_80368A7C[];
extern const char lbl_80368A90[];
extern const char lbl_80368AA0[];
extern const char lbl_80368AB0[];
extern const char lbl_80368AC0[];
extern const char lbl_80368AD0[];
extern const char lbl_80368AE4[];
extern const char lbl_80368AF0[];
extern const char lbl_80368B00[];
extern const char lbl_80368B10[];
extern const char lbl_80368B24[];
extern const char lbl_80368B34[];
extern const char lbl_80368B48[];
extern const char lbl_80368B54[];
extern const char lbl_80368B64[];
extern const char lbl_80368B74[];
extern const char lbl_80368B84[];
extern const char lbl_80368B90[];
extern const char lbl_80368BA0[];
extern const char lbl_80368BAC[];
extern const char lbl_80368BC0[];
extern const char lbl_80368BD0[];
extern const char lbl_80368BE0[];
extern const char lbl_80368BF0[];
extern const char lbl_80368C04[];
extern const char lbl_80368C14[];
extern const char lbl_80368C20[];
extern const char lbl_80368C30[];
extern const char lbl_80368C40[];
extern const char lbl_80368C50[];
extern const char lbl_80368C60[];
extern const char lbl_80368C74[];
extern const unsigned char Scene_8015BF18_rodata_80368C84[0x18];
extern const char lbl_80368C9C[];
extern const char lbl_80368CAC[0x14];
extern const char lbl_80368CC0[0xC];
extern const char lbl_80368CCC[0x14];
extern const char lbl_80368CE0[0x10];
extern const char lbl_80368CF0[];
extern const char lbl_80368D28[];
extern const char lbl_80368D38[];
extern const char lbl_80368D5C[];
extern const char lbl_80368D6C[];
extern const PopupAnim resultscene_nm1_rodata_80368D80[4] __attribute__((aligned(8)));
extern const unsigned char resultscene_rodata_80368DF0[0xC];
extern const unsigned char resultscene_rodata_80368DFC[0x10];
extern const unsigned char resultscene_rodata_80368E0C[0x10];
extern const unsigned char resultscene_rodata_80368E1C[0x10];
extern const unsigned char resultscene_rodata_80368E2C[0xC];
extern const unsigned char resultscene_rodata_80368E38[0xC];
extern const unsigned char resultscene_rodata_80368E44[0xC];
extern const unsigned char resultscene_rodata_80368E50[0xC];
extern const unsigned char resultscene_rodata_80368E5C[0x10];
extern const unsigned char resultscene_rodata_80368E6C[0x10];
extern const unsigned char resultscene_rodata_80368E7C[0xC];
extern const unsigned char resultscene_rodata_80368E88[0xC];
extern const unsigned char resultscene_rodata_80368E94[0xC];
extern const unsigned char resultscene_rodata_80368EA0[0xC];
extern const void *const sdata_806CF750_rodata_80368EAC[96];
extern const char lbl_8036902C[];
extern const char lbl_80369038[];
extern const char lbl_80369048[];
extern const void *const sdata_806CF750_rodata_80369054[96];
extern const char lbl_803691D4[];
extern const char lbl_803691E8[];
extern const char lbl_803691FC[];
extern const char lbl_80369210[];
extern const char lbl_80369224[];

}

/* Private declarations and inline bodies shared by the two remaining
 * NonMatching result-scene groups. The independent message-length initializer
 * occupies 0x8015E928..0x8015F0FC between those groups. */

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



extern "C" {
extern void fn_8016219C(void *, int, void *);
extern char resultscene_nm1_data_806CF910[4];
}

struct ResultBuf {
    int a;
    int b;
    void **data;
    ResultBuf(int count) {
        a = 0; b = 0; data = 0;
        fn_8016219C(this, count, resultscene_nm1_data_806CF910);
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



struct ResultBuf2 : ResultBufMid {
    ResultBuf2(int n) : ResultBufMid(n) {}
    ~ResultBuf2();
};



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



extern "C" void fn_80192348(int id);

#include "game/types/SpriteHolder.h"



struct ResultPartC : ResultPart {
    virtual ~ResultPartC();
    int idx;
    char pad8[0x6c - 8];
    SpriteHolder spr;
};



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

struct ResultPartY : ResultPart {
    ResultPartY(int idx);
    virtual ~ResultPartY();
    int mode;
    int half;
    int idx;
    float x10;
    unsigned char x14;
    char pad15[3];
    int x18;
    float x1c;
    int x20;
    float x24;
    float x28;
    ResultKarts *karts;
    char *buf;
    ResultPair *pair;
    ResCtrlR r38;
    ResCtrlR r90;
};



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
    float offs[4][2];
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
    unsigned char hasTitle;
    bool titleChanged;
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





struct InputPlayer {
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual float Stick();
    virtual void v1C();
    virtual unsigned char Held(int mask);
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

void fn_8015E608(ResultPartE608 *o) ;
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
extern void fn_80160588(void *self, int n, bool confirm);
extern void fn_80161720(CoinPopupDetail *self);
extern char ResultPart_vtable_80490A58[];
extern const float lbl_806D86A4;
extern const float lbl_806D86D8;

void fn_8015CB24(VObj *p) ;

typedef struct {
    char pad0[0x10];
    float a;
    char pad14[0x28 - 0x14];
    float b;
} Obj8015CD40;

int fn_8015CD40(Obj8015CD40 *o) ;

typedef struct {
    char pad0[0x10];
    int state;
} Obj8015E1D4;

unsigned char fn_8015E1D4(Obj8015E1D4 *o) ;

typedef struct {
    char pad0[0x10];
    unsigned char mode;
    char pad11[3];
    char sub[0x6c - 0x14];
    void *p6c;
} Obj8015E804;

void fn_8015E804(Obj8015E804 *o) ;

unsigned char fn_8015E84C(Obj8015E804 *o) ;


void fn_80160364(VObj *p) ;

typedef struct {
    unsigned char active;
    char pad1[0x10 - 1];
    int ready;
    int cur;
    int next;
} Obj80161888;

int fn_801618CC(Obj80161888 *o, int v, bool unused);

void fn_80161888(Obj80161888 *o);

SceneBase *fn_80160238(void) ;

SceneBase *fn_8015CB5C(int cup) ;

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

void fn_8015E48C(Obj8015E48C *o) ;

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

void fn_8015F0FC(ResultScreen *s) ;


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

void fn_8016039C(CoinPopupDetail *o) ;

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



extern PopupInfo *resultscene_nm1_data_806CF908[2];
extern const PopupAnim resultscene_nm1_rodata_80368D80[];
extern int isJapanese(void);
extern void **fn_80146000(void *v, int i);
extern unsigned char fn_801A024C(void *s);
extern void Sprite_SetupAnim(void *sprite, int anim, int loop, int arg);
extern void fn_80161128(CoinPopupDetail *o);

static inline PopupInfo *PopupInfo_Get(int k) {
    return &resultscene_nm1_data_806CF908[isJapanese()][k];
}

void fn_80161444(CoinPopupDetail *o) ;

void fn_80161720(CoinPopupDetail *o) ;

extern void fn_801FE348(void);
extern void fn_801A0500(void *s);
extern void TexMgr_SetTexture(void *tm, const char *fmt, ...);
extern const char lbl_806D884C[4];

void fn_801615A4(CoinPopupDetail *o) ;

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

void fn_80161128(CoinPopupDetail *o) ;

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
extern const float lbl_806D8760, lbl_806D86B8, lbl_806D86B4;
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
                    float t;
                    float ssc = 0.035f * (t = 1.0f - (float)e->subs[j].n / 15.0f);
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

void fn_8015DEBC(ResultPartYD *o) ;

}

extern "C" {
extern void *lbl_806D10A0;
extern unsigned char g_playerData[];
extern unsigned char get_title_result(void *t, int *a, int *b, int *c);

static inline void *TitleTracker_Get(void) {
    return SINGLETON_INSTANCE(lbl_806D10A0);
}

int has_title_changed(void) ;
}

extern "C" {
extern const float lbl_806D87C8;
extern const float lbl_806D87C4;
extern const float lbl_806D8848;
extern const float lbl_806D87F4;
extern void fn_801F93D0(void *t, float sx, float sy);
extern void fn_801F93C8(void *t, float angle);

void fn_80160A90(CoinPopupDetail *o) ;
}


extern "C" {
extern int CreditMgr_GetCreditCount(int slot);
extern int CreditMgr_GetCoinsPerCredit(int slot);
extern void fn_801F8E90(void *text);
extern void fn_8019FF6C(void *sprite, int enabled);
extern PopupInputState *g_pInputState;

static inline PopupInputState *PopupInput_Get() {
    return SINGLETON_INSTANCE(g_pInputState);
}

static inline PopupInputState *PopupInput_Peek() {
    return SINGLETON_INSTANCE(g_pInputState);
}

void fn_80160E04(CoinPopupDetail *o) ;
}


extern "C" {
extern const float lbl_806D880C;
extern const float lbl_806D8834;
extern const float lbl_806D87F0;
extern const float lbl_806D8838;
extern const float lbl_806D8830;
extern int Clamp_Int(int v, int lo, int hi);
extern void fn_801FE390(void);

static inline int Popup_CountIdle(CoinPopupDetail *o) {
    int cnt = 0;
    void **it;
    for (it = o->sprites.data; it != o->sprites.data + o->sprites.b; ++it) {
        if (!fn_801A024C(*it)) cnt++;
    }
    return cnt;
}

void fn_80160588(void *self, int step, bool confirm) ;
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

void fn_8015E1E8(ResultPartBUpdate *o) ;
}



extern "C" {
extern const float lbl_806D8818, lbl_806D881C, lbl_806D8850, lbl_806D8854;
extern const float lbl_806D8804, lbl_806D87FC, lbl_806D8800;
extern void fn_801F8FCC(void *text, int mode);
}



extern "C" {
extern unsigned char fn_80169DF0(void);
extern void InitRumbleController(int on);
extern void PreloadResource(int id);
extern const float lbl_806D8828, lbl_806D8858, lbl_806D885C;
extern const float lbl_806D8860, lbl_806D8864, lbl_806D8868, lbl_806D886C, lbl_806D8870;
extern const float lbl_806D8874, lbl_806D8878;
extern const char resultscene_nm1_data_806CF914[4], resultscene_nm1_data_806CF918[4], resultscene_nm1_data_806CF91C[4];
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



extern "C" {
extern void SetRumbleMode(int a, int b, int c);
extern void RumbleUpdate(void);
extern void SpriteAnimParamBlock_Reload(void *, int);
extern void SpriteHandle_SetCornerAlpha(void *, int);
extern void fn_8023CD24(CoinPrompt *, float, float);
extern void fn_8023CCCC(CoinPrompt *, float, float);
extern void fn_8023CDA8(CoinPrompt *);
extern void fn_8021A0B0(void *);
extern void *lbl_806D1A60;
extern const float lbl_806D87F8, lbl_806D8808, lbl_806D8810, lbl_806D8814;
extern const float lbl_806D8820, lbl_806D8824, lbl_806D882C;

static inline bool RSInput_Pressed(PopupInputState *in) {
    return in->x18 == 1;
}

static inline void RSDetail_Layout(CoinPopupDetail *d) {
    PopupSprite_SetPos(POPUP_SPR(d, 0), d->ax, d->ay);
    PopupSprite_SetPos(POPUP_SPR(d, 1), d->bx, d->by);
    fn_801F93EC(*fn_80146000(&d->bufs, 0), d->ax + d->offs[0][0], d->ay + d->offs[0][1]);
    fn_801F93EC(*fn_80146000(&d->bufs, 1), d->ax + d->offs[1][0], d->ay + d->offs[1][1]);
    fn_801F93EC(*fn_80146000(&d->bufs, 2), d->bx + d->offs[2][0], d->by + d->offs[2][1]);
    fn_801F93EC(*fn_80146000(&d->bufs, 3), d->bx + d->offs[3][0], d->by + d->offs[3][1]);
    {
        float k = lbl_806D8820;
        PopupSprite_SetPos((PopupSprite *)d->h60.s, k * (d->bx - d->ax) + d->ax, k * (d->by - d->ay) + d->ay);
    }
}

static inline void RSDetail_SetPos(CoinPopupDetail *d, float ax, float ay, float bx, float by) {
    d->ax = ax;
    d->ay = ay;
    d->bx = bx;
    d->by = by;
    RSDetail_Layout(d);
}

static inline int RSDetail_Mode(CoinPopupDetail *d) {
    return d->state < 2 ? 2 : d->mode;
}

static inline bool RSDetail_Accept(CoinPopupDetail *d) {
    return RSDetail_Mode(d) == 0;
}

static inline unsigned char RSDetail_Done(CoinPopupDetail *d) {
    return d->state == 6;
}

static inline void RSSub_SaveTitle(ResultSub *s) {
    void *t = TitleTracker_Get();
    if (s->titleChanged == 1 && t && get_title_result(t, &s->title, &s->rank, &s->character) == 1) {
        g_playerData[0x19b] = s->title;
        g_playerData[0x19c] = s->rank;
        g_playerData[0x1b1] = s->character;
    }
}

static inline void RSSub_DeletePrompt(ResultSub *s) {
    if (s->prompt) {
        delete s->prompt;
        s->prompt = 0;
    }
}

/* ResultSub::Update (vtable slot of resultscene_nm1_data_80490A90). NonMatching: only the
 * input pointer (r29) and the ItemMsgWnd singleton temp (r30) are swapped. */
void result_screen_update(ResultSub *s) ;

void fn_80161888(Obj80161888 *o) ;

int fn_801618CC(Obj80161888 *o, int v, bool unused) ;
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

static inline void RYPair_Spawn(RYPair *p) {
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
}

void fn_8015D9F0(RYPair *p) ;
}

extern "C" {
extern unsigned long strlen(const char *text);
extern ResultMessageRecord lbl_80490080[98];
extern const char lbl_806D8650[4];
extern const char lbl_806D8654[4];
extern const char lbl_806D865C[4];

/* Initialize cached lengths for the existing result-message records. */
void fn_8015E928(void) ;
}




extern "C" {
extern const float resultscene_rodata_80368704[][4];
extern const float lbl_806D8758, lbl_806D875C, lbl_806D8760;
#ifdef __MWERKS__
extern void fn_80169468(int mode, int resource, int flags, float x, float y,
                        float r, float g, float b, float alpha);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void fn_80169468(int, int, float, float, float, float, float, float, int);
static inline void fn_80169468_Reordered(int mode, int resource, int flags, float x, float y, float r, float g, float b, float alpha) { fn_80169468(mode, resource, x, y, r, g, b, alpha, flags); }
#define fn_80169468 fn_80169468_Reordered
#endif

void fn_8015D4F8(void *unused, float x, float y, int color, const char *text) ;
}

struct ResultFlake;
struct ResultVec { float x, y, z; };
extern "C" {
extern void KartMovement_ResetOnGoal(void *drv);
extern void PSMTXScale(float m[3][4], float x, float y, float z);
extern void PSMTXIdentity(float m[3][4]);
extern void PSMTXConcat(float a[3][4], float b[3][4], float ab[3][4]);
extern void PSMTXRotRad(float m[3][4], char axis, float rad);
extern void PSMTXTrans(float m[3][4], float x, float y, float z);
extern void CObj_LoadIntoGX(VObj *cam, ResultVec *v);
extern void CObj_ApplyViewport(VObj *cam, ResultVec *v);
extern void ProcessSystemTick(int);
extern int fn_80169E20(void);
extern void fn_8013D738(VObj *f, float a, float b);
extern void fn_8013D634(VObj *f, float x, float y, float z);
extern void ClSound_PlayBgmStream(int ch, int n);
extern unsigned char fn_801932F8(void);
extern void clStream_setVolume(int ch, unsigned char vol);
extern const short lbl_806D8664[4];
extern const float lbl_806D866C, lbl_806D8670, lbl_806D867C, lbl_806D8680, lbl_806D8684, lbl_806D8688;
extern const float lbl_806D868C, lbl_806D8690, lbl_806D8694, lbl_806D8698, lbl_806D869C, lbl_806D86A0;
extern const float lbl_806D86A8, lbl_806D86AC, lbl_806D86B0, lbl_806D86B4, lbl_806D86B8, lbl_806D86BC;
extern const float lbl_806D86C0, lbl_806D86C4, lbl_806D86C8;
}

struct ResultCam { char d[0x3084]; ResultCam(const char *path); };
struct ResultModel { char d[0x28]; ResultModel(const char *path, unsigned char flag); };
struct ResultDriver { char d[0x384]; ResultDriver(int a, int id, float *mtx, int b, int c, int d); };
struct ResultFlake { char d[0x20]; ResultFlake(const char *path, int flag); };


struct ResultKartSlot {
    ResultKartSlot(int n) {
        float t[3][4];
        float s[3][4];
        float r[3][4];
        driver = new ResultDriver(6, n, &out[0][0], 0, 0, 0);
        id = n;
        x = lbl_806D868C;
        KartMovement_ResetOnGoal(driver);
        PSMTXScale(s, lbl_806D8674, lbl_806D8674, lbl_806D8674);
        PSMTXIdentity(m);
        PSMTXConcat(s, m, m);
        PSMTXRotRad(r, 'Z', lbl_806D8690);
        PSMTXConcat(r, m, m);
        PSMTXRotRad(r, 'Y', lbl_806D8694);
        PSMTXConcat(r, m, m);
        PSMTXTrans(t, lbl_806D8698, lbl_806D8698, lbl_806D869C);
        PSMTXConcat(t, m, out);
    }
    ResultDriver *driver;
    int id;
    float x;
    float out[3][4];
    float m[3][4];
};

static inline void KartSlot_Place(ResultKartSlot *k, int i) {
    float t[3][4];
    k->x = lbl_806D86A4 * (float)i + lbl_806D86A0;
    PSMTXTrans(t, k->x, lbl_806D86A8, lbl_806D869C);
    PSMTXConcat(t, k->m, k->out);
}
static inline void KartSlot_Init(ResultKartSlot **slot, int id, int i) {
    float t[3][4];
    ResultKartSlot *k;
    *slot = new ResultKartSlot(id);
    (*slot)->x = lbl_806D86A4 * (float)i + lbl_806D86A0;
    k = *slot;
    PSMTXTrans(t, k->x, lbl_806D86A8, lbl_806D869C);
    PSMTXConcat(t, k->m, k->out);
}
static inline void KartSlot_Init2(ResultKartSlot **karts, int i) {
    float t[3][4];
    ResultKartSlot *k;
    karts[i] = new ResultKartSlot(lbl_803686B8[i]);
    karts[i]->x = lbl_806D86A4 * (float)i + lbl_806D86A0;
    k = karts[i];
    PSMTXTrans(t, k->x, lbl_806D86A8, lbl_806D869C);
    PSMTXConcat(t, k->m, k->out);
}
struct ResultKartSet {
    ResultKartSet() {
        int i;
        ResultVec v;
        cam = (VObj *)new ResultCam(lbl_80368CC0);
        model = new ResultModel(lbl_80368CC0, 0);
        on = 0;
        on2 = 0;
        v.x = lbl_806D8678;
        v.y = lbl_806D8678;
        v.z = lbl_806D8688;
        CObj_LoadIntoGX(cam, &v);
        v.z = lbl_806D8678;
        CObj_ApplyViewport(cam, &v);
        for (i = 0; i < 13; i++) {
            KartSlot_Init2(karts, i);
            ProcessSystemTick(0);
        }
    }
    VObj *cam;
    void *model;
    ResultKartSlot *karts[13];
    unsigned char on;
    unsigned char on2;
};

struct ResultFade {
    ResultFade(int h) {
        xb0 = 0;
        xb4 = 0;
        xb8 = 0;
        half = h;
        a.enable = 1;
        a.x = lbl_806D86AC;
        a.y = lbl_806D86B0;
        a.z = lbl_806D8674;
        a.c0 = -0x100;
        a.c1 = -0x100;
        a.c2 = -0x100;
        a.c3 = -0x100;
        b.enable = 1;
        b.x = lbl_806D86AC;
        b.y = lbl_806D86B0;
        b.z = lbl_806D8674;
        b.c0 = -0x100;
        b.c1 = -0x100;
        b.c2 = -0x100;
        b.c3 = -0x100;
    }
    ResCtrlR a;
    ResCtrlR b;
    int xb0, xb4, xb8;
    int half;
};


static inline void Flake_SetPos(VObj *f, const ResultVec &v) {
    fn_8013D634(f, v.x, v.y, v.z);
}


struct ResultFlakes : RYPair {
    ResultFlakes() {
        int i;
        stopped = 0;
        timer = 0;
        interval = 0x78;
        a = (VObj *)new ResultFlake(lbl_80368CCC, 1);
        b = (VObj *)new ResultFlake(lbl_80368CE0, 1);
        fn_8013D738(a, lbl_806D8678, lbl_806D8674);
        { const ResultVec *v = (const ResultVec *)lbl_803686EC; fn_8013D634(a, lbl_803686EC[0], v->y, v->z); }
        fn_8013D608(a, lbl_806D86B4, lbl_806D86B4, lbl_806D86B4);
        fn_8013D738(b, lbl_806D8678, lbl_806D8674);
        { const ResultVec *v = (const ResultVec *)lbl_803686F8; fn_8013D634(b, lbl_803686F8[0], v->y, v->z); }
        fn_8013D608(b, lbl_806D86B8, lbl_806D86B8, lbl_806D86B8);
        for (i = 0; i < 3; i++) RYEntry_Reset(&e[i]);
    }
};



struct ResultFadeV {
    int idA;
    char pad04[0x2c - 0x04];
    float sx, sy;
    unsigned int colA[4];
    char pad44[0x58 - 0x44];
    int idB;
    char pad5c[0x8c - 0x5c];
    unsigned int colB[4];
    char pad9c[0xb0 - 0x9c];
    int timer;
    int state;
    int step;
    int half;
};

struct ResultPartYU {
    void *vt;
    int mode;
    int half;
    int idx;
    float timer;
    unsigned char started;
    char pad15[3];
    int x18;
    float wait;
    int x20;
    float x24;
    float fade;
    ResultKartSet *karts;
    ResultFadeV *fadeObj;
    RYPair *pair;
    char pad38[0x6c - 0x38];
    unsigned int colA[4];
    char pad7c[0xc4 - 0x7c];
    unsigned int colB[4];
};

extern "C" {
extern void KartDriver_TriggerSlotC3Action(ResultDriver *d, float t);
extern void KartDriver_TickAction_79234(ResultDriver *d, float t);
extern void RenderObj_ItemStateMachine_Timed(ResultDriver *d, int n, float a, float b);
extern float Saturate_Double(float v, float lo, float hi);
#ifdef __MWERKS__
extern void fn_801695E0(int obj, int id, int flag, float x, float y, float a);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void fn_801695E0(int, int, float, float, float, int);
static inline void fn_801695E0_Reordered(int obj, int id, int flag, float x, float y, float a) { fn_801695E0(obj, id, x, y, a, flag); }
#define fn_801695E0 fn_801695E0_Reordered
#endif
#ifdef __MWERKS__
extern void fn_80169334(int obj, int id, int flag, float x, float y, float z, float a, float b);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void fn_80169334(int, int, float, float, float, float, float, int);
static inline void fn_80169334_Reordered(int obj, int id, int flag, float x, float y, float z, float a, float b) { fn_80169334(obj, id, x, y, z, a, b, flag); }
#define fn_80169334 fn_80169334_Reordered
#endif
extern void fn_80190A70(int a, int b);
extern const float lbl_806D86DC, lbl_806D86E0, lbl_806D86E4, lbl_806D86F4, lbl_806D86F8, lbl_806D86FC;
extern const float lbl_806D8700, lbl_806D8704, lbl_806D8708, lbl_806D870C, lbl_806D8710, lbl_806D8714;
extern const float lbl_806D8718, lbl_806D871C, lbl_806D8720, lbl_806D8724, lbl_806D8728, lbl_806D872C;
extern const float lbl_806D8730, lbl_806D8734, lbl_806D8738, lbl_806D873C, lbl_806D8740, lbl_806D8744;
extern const float lbl_806D8748, lbl_806D874C, lbl_806D8750, lbl_806D8754;

static inline void Slot_ResetPose(ResultKartSlot *k) {
    float s[3][4];
    float r[3][4];
    PSMTXScale(s, lbl_806D8674, lbl_806D8674, lbl_806D8674);
    PSMTXIdentity(k->m);
    PSMTXConcat(s, k->m, k->m);
    PSMTXRotRad(r, 'Z', lbl_806D8690);
    PSMTXConcat(r, k->m, k->m);
    PSMTXRotRad(r, 'Y', lbl_806D8694);
    PSMTXConcat(r, k->m, k->m);
}

static inline void Slot_Tilt(ResultKartSlot *k) {
    float x = k->x;
    if (x < lbl_806D86A0) {
        float s[3][4];
        float r[3][4];
        PSMTXScale(s, lbl_806D8674, lbl_806D8674, lbl_806D8674);
        PSMTXIdentity(k->m);
        PSMTXConcat(s, k->m, k->m);
        PSMTXRotRad(r, 'Z', lbl_806D8690);
        PSMTXConcat(r, k->m, k->m);
        PSMTXRotRad(r, 'Y', lbl_806D8700 * (lbl_806D8704 * (lbl_806D8674 - (x - lbl_806D86FC) / lbl_806D8708)) + lbl_806D8694);
        PSMTXConcat(r, k->m, k->m);
    }
}

static inline void Slot_Place(ResultKartSlot *k) {
    float t[3][4];
    PSMTXTrans(t, k->x, lbl_806D86A8, lbl_806D869C);
    PSMTXConcat(t, k->m, k->out);
}

static inline void Slot_Tick(ResultKartSlot *k) {
    KartDriver_TriggerSlotC3Action(k->driver, lbl_806D870C);
    KartDriver_TickAction_79234(k->driver, lbl_806D870C);
    RenderObj_ItemStateMachine_Timed(k->driver, 0, lbl_806D8678, lbl_806D8678);
}

static inline void KartSet_Update(ResultKartSet *ks) {
    int i;
    if (ks->on) {
        for (i = 0; i < 13; i++) {
            ResultKartSlot *k;
            if (ks->on2 == 1 && ks->karts[i]->x >= lbl_806D86A0) continue;
            ks->karts[i]->x -= lbl_806D86F8;
            k = ks->karts[i];
            if (k->x < lbl_806D86FC && ks->on2 == 0) {
                int j = i - 1;
                if (j < 0) j = 12;
                k->x = lbl_806D86A4 + ks->karts[j]->x;
                Slot_ResetPose(ks->karts[i]);
            }
            Slot_Tilt(ks->karts[i]);
            Slot_Place(ks->karts[i]);
            Slot_Tick(ks->karts[i]);
        }
    }
}

static inline void Fade_Next(ResultFadeV *f) {
    if (f->half == 0 && f->step == 1) f->step++;
    f->timer = 0;
    f->state = 1;
    f->idB = f->idA;
    f->colB[0] = -1;
    f->colB[1] = -1;
    f->colB[2] = -1;
    f->colB[3] = -1;
    f->colA[0] = -0x100;
    f->colA[1] = -0x100;
    f->colA[2] = -0x100;
    f->colA[3] = -0x100;
    if (f->step >= 13) {
        f->idA = 0x1ecd;
    } else {
        f->idA = f->step++ + lbl_806D8664[f->half];
    }
}

static inline void Col_SetAlpha(unsigned int *col, int a) {
    unsigned int c = (0xFFFFFF00 | (unsigned char)(a));
    col[0] = c;
    col[1] = c;
    col[2] = c;
    col[3] = c;
}

static inline void Fade_Update(ResultFadeV *f) {
    if (f->state == 1) {
        float t = (float)f->timer / lbl_806D86A4;
        int a = (int)(lbl_806D86E8 * t);
        float sc = lbl_806D86EC * (lbl_806D8674 - t) + lbl_806D8674;
        f->sx = sc;
        f->sy = sc;
        Col_SetAlpha(f->colA, a);
        Col_SetAlpha(f->colB, 0xff - a);
        if ((float)f->timer >= lbl_806D86A4) f->state = 2;
        f->timer++;
    }
}

void fn_8015CD74(ResultPartYU *o) ;
}


/* Keep the primary destructor in the first group. The later group also needs
 * this body available for the original member-destructor inline expansion. */
#ifdef RESULTSCENE_INLINE_SPRITE_HOLDER
inline SpriteHolder::~SpriteHolder() throw() {
    Sprite_Destroy(s, 1);
}
#endif

#endif
