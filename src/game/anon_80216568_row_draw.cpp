#include "game/CoinMilestone.h"
#include "game/FadeLogo.h"



/* ---- text sprite row ---- */

/* 0x230-byte text sprite (ctor TexMgr_Init). */
#include "game/types/TextSprite.h"

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

extern "C" void fn_80217390(TextRow *row) {
    void *list = fn_801F8E58();
    for (TextSprite **it = row->sprites.begin(); it != row->sprites.end(); it++) {
        fn_801F8A34(list, *it, row->layer);
    }
}

