/* Deferred generation: out-of-line definitions follow reverse target order. */
#include "game/CoinMilestone.h"
#include "game/types/clCpopTasks.h"
#include "game/FadeLogo.h"
/* ---- text sprite row ---- */

/* 0x230-byte text sprite (ctor TexMgr_Init). */
struct TextSprite {
    char pad000[0x8];
    float width;
    char pad00C[0x18 - 0xC];
    int visible;
    char pad01C[0x20 - 0x1C];
    unsigned int color;
    char pad024[0x22C - 0x24];
    float spacing;
    TextSprite();
};

extern "C" {
void PtrVec_InsertFill(void *v, void *pos, int n, const void *val);
void fn_801F93D0(TextSprite *t, float sx, float sy);
void *fn_801F8E58(void);
void fn_801F8A34(void *list, TextSprite *t, int layer);
extern const float lbl_806DAEC0;
extern const float lbl_806DAEC4;
extern const float lbl_806DAEC8;
extern const float lbl_806DAECC;
extern const float lbl_806DAED0;
}

/* FlowScene.h declares these on TextManager; same object. */
static inline void SetText(TextSprite *t, const char *s) {
    TexMgr_SetTexture((TextManager *)t, s);
}
static inline void SetPos(TextSprite *t, float x, float y) {
    fn_801F93EC((TextManager *)t, x, y);
}
static inline void SetAlign(TextSprite *t, int mode) {
    fn_801F8FCC((TextManager *)t, mode);
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

template <class T> struct PtrVec : PtrVecBase<T> {
    PtrVec() {}
    ~PtrVec() {}
    T *begin() { return this->data; }
    T *end() { return this->data + this->count; }
    void push_back(const T &v) { PtrVec_InsertFill(this, end(), 1, &v); }
};

static inline unsigned int PackColor(int r, int g, int b, int a) {
    return ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | (a & 0xFF);
}

#include "game/types/TextRow.h"

/* ---- "insert card" prompt ---- */

#include "game/types/FadeKeyBase.h"

#include "game/types/FadeKey.h"

struct FadeSeq {
    virtual ~FadeSeq();
    virtual bool Done();
    virtual void Update();
    bool loop;
    FadeKey *head;
    FadeKey *cur;
    FlowFaderF *tween;
    FadeSeq(FadeKey *h, bool l);
};

extern "C" {
extern const float lbl_803C4B90[6];
extern const float lbl_806DAED8;
extern const float lbl_806DAEDC;
extern const float lbl_806DAEE0;
extern const float lbl_806DAEE4;
extern const float lbl_806DAEE8;
extern const float lbl_806DAEEC;
extern const float lbl_806DAEF0;
extern const float lbl_806DAEF4;
extern const float lbl_806DAEF8;
extern const float lbl_806DAEFC;
extern const float lbl_806DAF00;
extern const float lbl_806DAF04;
extern const float lbl_806DAF08;
extern const float lbl_806DAF0C;
extern const float lbl_806DAF10;
extern const float lbl_806DAF14;
extern const float lbl_806DAF18;
extern const float lbl_806DAF1C;
extern const float lbl_806DAF20;
extern const float lbl_806DAF24;
extern const float lbl_806DAF28;
extern int g_cupId;
unsigned char IsCardValid(void);
void PreloadResource(int res);
void fn_8011FAFC(ResCtrl *ctrl, int layer);
void fn_80121E10(ResCtrl *ctrl);
}

static inline unsigned int PackGray(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    return (r << 24) | (g << 16) | (b << 8) | a;
}

static inline int PromptRes() {
    return IsCardValid() == 1 ? 0xB1A : 0xCD7;
}

/* Card logo that zooms in, pulses and then glows (vtable CardPrompt_vtable_804EDBB0). */
struct clCpopSuccess : clCTaskInterface {
    int layer;
    int state;
    FlowFaderI *alpha;
    FlowFaderF *scale;
    clCpopSuccess(int layer_, int id_);
    ~clCpopSuccess();
    void Finish();
    void Update();
    void Draw();
    void Intro();
    void Hold();
};

/* Task list host that runs one clCpopFail1 (vtable CardLogoScene_vtable_804EDBDC). */
struct clCpopFail : clCTaskInterface {
    VHolder<TaskListImpl> list;
    clCpopFail(int layer_, int id_);
    ~clCpopFail();
    void Finish();
    void Update();
    void Draw();
};

/* Card logo bouncing in (vtable CardLogo_vtable_804EDC08). */
struct clCpopFail1 : clCTaskInterface {
    int layer;
    VHolder<FadeKey> key1;
    VHolder<FadeSeq> seq1;
    VHolder<FadeKey> key2;
    VHolder<FadeSeq> seq2;
    VHolder<FadeKey> key3;
    VHolder<FadeSeq> seq3;
    clCpopFail1(int layer_, int id_);
    ~clCpopFail1();
    void Finish();
    void Update();
    void Draw();
};

void clCpopFail::Finish() {
    delete this;
}

void clCpopSuccess::Finish() {
    delete this;
}

clCpopFail1::clCpopFail1(int layer_, int id_) : clCTaskInterface(id_), layer(layer_) {
    key1.Reset(new FadeKey(11, lbl_806DAF14, lbl_806DAF18));
    key1.p->Append(8, lbl_806DAF1C);
    key1.p->Append(7, lbl_806DAF18);
    key1.p->Append(0x5A, lbl_806DAF18);
    key2.Reset(new FadeKey(11, lbl_806DAED8, lbl_806DAF20));
    key2.p->Append(8, lbl_806DAF24);
    key2.p->Append(7, lbl_806DAED8);
    key2.p->Append(0x5A, lbl_806DAED8);
    key3.Reset(new FadeKey(11, lbl_806DAED8, lbl_806DAF28));
    key3.p->Append(8, lbl_806DAEF8);
    key3.p->Append(7, lbl_806DAED8);
    key3.p->Append(0x5A, lbl_806DAED8);
    seq1.Reset(new FadeSeq(key1.p, false));
    seq2.Reset(new FadeSeq(key2.p, false));
    seq3.Reset(new FadeSeq(key3.p, false));
}

clCpopFail1::~clCpopFail1() {
}

void clCpopFail1::Finish() {
    delete this;
}

void clCpopFail1::Update() {
    ResCtrl rc;
    if (g_cupId == 14) {
        rc.resId = 0x14B6;
    } else if (IsCardValid() == 1) {
        rc.resId = 0xB1B;
    } else {
        rc.resId = 0xCD8;
    }
    rc.Show(lbl_806DAF10, seq1.p->tween->Value(), lbl_806DAED8);
    rc.SetScaleXY(seq2.p->tween->Value(), seq3.p->tween->Value());
    fn_8011FAFC(&rc, layer);
    seq1.p->Update();
    seq2.p->Update();
    seq3.p->Update();
    if (seq1.p->Done()) {
        field0C = 1;
    }
}

void clCpopFail1::Draw() {
}

clCpopFail::clCpopFail(int layer_, int id_) : clCTaskInterface(id_), list(new TaskListImpl) {
    TaskListImpl *l = list.p;
    l->Add(new clCpopFail1(layer_, 0), 0);
}

clCpopFail::~clCpopFail() {
}

extern "C" void fn_8021819C(void) {
    if (g_cupId == 14) {
        PreloadResource(0x14B6);
    } else if (IsCardValid() == 1) {
        PreloadResource(0xB1B);
    } else {
        PreloadResource(0xCD8);
    }
}

void clCpopFail::Update() {
    if (list.p->entries.count <= 0) {
        field0C = 1;
    }
    list.p->Update();
    list.p->Draw();
}

void clCpopFail::Draw() {
}

clCpopSuccess::clCpopSuccess(int layer_, int id_) : clCTaskInterface(id_), layer(layer_), state(0) {
    alpha = new FlowFaderI[4];
    scale = new FlowFaderF[5];
    alpha[0].Set(0, 0, 6);
    alpha[1].Set(0xFF, 0xFF, 6);
    scale[0].Set(lbl_806DAF00, lbl_806DAF00, 6);
    scale[1].Set(lbl_806DAF00, lbl_806DAF00, 6);
    alpha[2].Set(0, 0xFF, 12);
    scale[2].Set(lbl_806DAF00, lbl_806DAEF4, 12);
    alpha[3].Set(0, 0, 1);
    scale[3].Set(lbl_806DAED8, lbl_806DAED8, 1);
    scale[4].Set(lbl_806DAEEC, lbl_806DAEEC, 1);
}

clCpopSuccess::~clCpopSuccess() {
    delete[] scale;
    delete[] alpha;
}

extern "C" void fn_80217E9C(void) {
    if (IsCardValid() == 1) {
        PreloadResource(0xB1A);
    } else {
        PreloadResource(0xCD7);
    }
}

void clCpopSuccess::Intro() {
    float sx = scale[0].Value();
    float sy = scale[1].Value();
    int a0 = alpha[0].Value();
    int a1 = alpha[1].Value();
    ResCtrl rc;
    rc.resId = PromptRes();
    rc.SetScaleXY(sx, sy);
    rc.Show(lbl_803C4B90[0], lbl_803C4B90[1], lbl_806DAED8);
    rc.SetColor(a0 | 0xFFFFFF00);
    fn_8011FAFC(&rc, layer);
    rc.mode = 3;
    rc.SetColor(a1 | 0xFFFFFF00);
    fn_8011FAFC(&rc, layer);
    float gs = scale[2].Value();
    unsigned char g = alpha[2].Value();
    fn_80121E10(&rc);
    rc.resId = PromptRes();
    rc.SetScaleXY(gs, gs);
    rc.tail[0] = 1;
    rc.tail[1] = 1;
    rc.tail[2] = 1;
    rc.Show(lbl_803C4B90[0], lbl_803C4B90[1], lbl_806DAED8);
    rc.SetColor(PackGray(g, g, g, 0xFF));
    fn_8011FAFC(&rc, layer);
    alpha[2].Step();
    scale[2].Step();
    if (scale[2].Done()) {
        float v = scale[2].Value();
        if (lbl_806DAEF4 == v) {
            alpha[2].Set(0xFF, 0x7F, 6);
            scale[2].Set(lbl_806DAEF4, lbl_806DAEF8, 6);
        } else if (lbl_806DAEF8 == v) {
            alpha[2].Set(0x7F, 0, 5);
            scale[2].Set(lbl_806DAEF8, lbl_806DAEFC, 5);
        }
    }
    alpha[0].Step();
    alpha[1].Step();
    scale[0].Step();
    scale[1].Step();
    if (scale[0].Done()) {
        float v = scale[0].Value();
        if (lbl_806DAF00 == v) {
            scale[0].Set(lbl_806DAF00, lbl_806DAF04, 9);
            scale[1].Set(lbl_806DAF00, lbl_806DAF04, 9);
            alpha[0].Set(0, 0xFF, 9);
        } else if (lbl_806DAF04 == v) {
            scale[0].Set(lbl_806DAED8, lbl_806DAF08, 3);
            scale[1].Set(lbl_806DAED8, lbl_806DAF08, 3);
        } else if (lbl_806DAF08 == v) {
            scale[0].Set(lbl_806DAF08, lbl_806DAED8, 3);
            scale[1].Set(lbl_806DAF08, lbl_806DAED8, 3);
        } else if (lbl_806DAED8 == v) {
            scale[0].Set(lbl_806DAED8, lbl_806DAF0C, 0x4F);
            scale[1].Set(lbl_806DAED8, lbl_806DAF0C, 0x4F);
            alpha[1].Set(0xFF, 0, 14);
        } else {
            scale[0].Set(lbl_806DAED8, lbl_806DAEDC, 5);
            scale[1].Set(lbl_806DAED8, lbl_806DAEE4, 5);
            alpha[1].Set(0, 0xFF, 5);
            alpha[2].Set(0, 0, 5);
            scale[2].Set(lbl_806DAEDC, lbl_806DAEDC, 5);
            scale[3].Set(lbl_806DAEE4, lbl_806DAEE4, 5);
            scale[4].Set(lbl_806DAEEC, lbl_806DAEEC, 5);
            state = 1;
        }
    }
}

void clCpopSuccess::Hold() {
    float sx = scale[0].Value();
    float sy = scale[1].Value();
    int a0 = alpha[0].Value();
    int a1 = alpha[1].Value();
    ResCtrl rc;
    rc.resId = PromptRes();
    rc.SetScaleXY(sx, sy);
    rc.Show(lbl_803C4B90[0], lbl_803C4B90[1], lbl_806DAED8);
    rc.SetColor(a0 | 0xFFFFFF00);
    fn_8011FAFC(&rc, layer);
    rc.mode = 3;
    rc.SetColor(a1 | 0xFFFFFF00);
    fn_8011FAFC(&rc, layer);
    float gx = scale[2].Value();
    float gy = scale[3].Value();
    float off = scale[4].Value();
    unsigned char g = alpha[2].Value();
    fn_80121E10(&rc);
    rc.resId = PromptRes();
    rc.SetScaleXY(gx, gy);
    rc.tail[0] = 1;
    rc.tail[1] = 1;
    rc.tail[2] = 1;
    rc.Show(lbl_803C4B90[0] + off, lbl_803C4B90[1], lbl_806DAED8);
    rc.SetColor(PackGray(g, g, g, 0xFF));
    fn_8011FAFC(&rc, layer);
    rc.Show(lbl_803C4B90[0] - off, lbl_803C4B90[1], lbl_806DAED8);
    fn_8011FAFC(&rc, layer);
    alpha[0].Step();
    alpha[1].Step();
    scale[0].Step();
    scale[1].Step();
    alpha[2].Step();
    scale[2].Step();
    scale[3].Step();
    scale[4].Step();
    if (scale[2].Done()) {
        if (scale[2].Value() == lbl_806DAEDC) {
            alpha[0].Set(0, 0, 1);
            alpha[1].Set(0, 0, 1);
            alpha[2].Set(0, 0xFF, 10);
            scale[2].Set(lbl_806DAEDC, lbl_806DAEE0, 10);
            scale[3].Set(lbl_806DAEE4, lbl_806DAEE8, 10);
            scale[4].Set(lbl_806DAEEC, lbl_806DAEF0, 10);
        } else {
            field0C = 1;
        }
    }
}

void clCpopSuccess::Update() {
    switch (state) {
    case 0:
        Intro();
        break;
    case 1:
        Hold();
        break;
    }
}

void clCpopSuccess::Draw() {
}

extern "C" TextRow *fn_802174A8(TextRow *row) {
    row->sprites.cap = 0;
    row->sprites.count = 0;
    row->sprites.data = 0;
    row->layer = 6;
    row->align = 0;
    row->visible = 1;
    row->alpha = 0xFF;
    row->dirty = 0;
    row->x = row->y = lbl_806DAEC0;
    row->sx = row->sy = lbl_806DAED0;
    return row;
}

TextRow::~TextRow() {
    for (TextSprite **it = sprites.begin(); it != sprites.end(); it++) {
        if (*it != 0) {
            delete *it;
        }
    }
}
