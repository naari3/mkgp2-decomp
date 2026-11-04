#include "game/CoinMilestone.h"
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
    ~TextRow();
};

extern "C" void fn_80217298(TextRow *row, const char *text, unsigned char r, unsigned char g, unsigned char b, float spacing) {
    row->dirty = 1;
    TextSprite *t = new TextSprite;
    SetText(t, text);
    t->color = PackColor(r, g, b, row->alpha);
    SetPos(t, row->x, row->y);
    fn_801F93D0(t, row->sx, row->sy);
    t->visible = row->visible;
    SetAlign(t, row->align);
    t->spacing = spacing;
    row->sprites.push_back(t);
}

