#include "game/types/clMnYesNo.h"
extern "C" {
extern const int lbl_803C25A8[42]  = {
    96, 255, 0, 200, 64, 0, 0, 96,
    255, 0, 96, 255, 0, 96, 255, 0,
    96, 255, 0, 96, 255, 0, 96, 255,
    0, 96, 255, 0, 96, 255, 0, 96,
    255, 0, 96, 255, 0, 96, 255, 0,
    96, 255
};
}
static inline clMnYesNoWindow *CastYesNoTask(clMnTaskInterface *task) {
    return dynamic_cast<clMnYesNoWindow *>(task);
}
extern "C" {
extern const float lbl_803C2688[3] = {
    -4.0f, -14.0f, 0.0f
};
extern const float lbl_803C2694[3] = {
    52.0f, -94.0f, 7.0f
};
extern const float lbl_803C26A0[3] = {
    -14.0f, 0.0f, -107.0f
};
extern const float lbl_803C26AC[3] = {
    -94.0f, 7.0f, 9e+01f
};
}
static inline clMnYesNoInterface *CastYesNoButton(clMnTaskInterface *task) {
    return dynamic_cast<clMnYesNoInterface *>(task);
}
static inline clMnCdAllow *CastYesNoCursor(clMnTaskInterface *task) {
    return dynamic_cast<clMnCdAllow *>(task);
}
static inline clMnSelYes *CastYesNoButtonL(clMnTaskInterface *task) {
    return dynamic_cast<clMnSelYes *>(task);
}
static inline clMnSelNo *CastYesNoButtonR(clMnTaskInterface *task) {
    return dynamic_cast<clMnSelNo *>(task);
}






/* Use the original RTTI records through the CW cast runtime. */
extern "C" {
void *fn_80271340(void *, int, void *, void *, int);
extern unsigned char FlowTask_RTTI_806D02A0[8];
extern unsigned char YesNoButtonL_RTTI_806D02C0[8];
extern unsigned char YesNoButtonR_RTTI_806D02C8[8];
extern unsigned char YesNoCursor_RTTI_806D02B8[8];
}
















/* Use the original RTTI records through the CW cast runtime. */
extern "C" {
void *fn_80271340(void *, int, void *, void *, int);
extern unsigned char FlowTask_RTTI_806D02A0[8];
extern unsigned char YesNoCursor_RTTI_806D02B8[8];
extern unsigned char YesNoButton_RTTI_806D02B0[8];
}














static inline void SpawnSpark(FlowSceneList *l, int id, int layer, float x, float y, unsigned char flag) {
    fn_801F4DF0(l, new clMnCdAllowDraw(id, layer, x, y, flag), 0);
}










/*
 * Selector sparkle and right-hand button drawing (0x802052E0..0x80205DCC).
 */

extern "C" {
void fn_8011FAFC(ResCtrl *ctrl, int layer);
void fn_80121E10(ResCtrl *ctrl);
float fn_8020A6CC(FlowFader *fader);
void *fn_801F8E58(void);
void fn_801F8A34(void *a, TextManager *tm, int layer);
void fn_801F93D0(TextManager *tm, float sx, float sy);
void fn_80270C78(void *arr, void *dtor);
extern const float lbl_806DAB58;
extern const float lbl_806DAB5C;
extern const float lbl_806DAB60;
extern const float lbl_806DAB64;
extern const float lbl_806DAB68;
extern const float lbl_806DAB00[2];
extern const float lbl_806DAB08[2];
extern const float lbl_803C26A0[3];
extern const float lbl_803C26AC[3];
}












/*
 * Selector sparkle and right-hand button drawing (0x802052E0..0x80205DCC).
 */

extern "C" {
void fn_8011FAFC(ResCtrl *ctrl, int layer);
void fn_80121E10(ResCtrl *ctrl);
float fn_8020A6CC(FlowFader *fader);
void *fn_801F8E58(void);
void fn_801F8A34(void *a, TextManager *tm, int layer);
void fn_801F93D0(TextManager *tm, float sx, float sy);
void fn_80270C78(void *arr, void *dtor);
extern const float lbl_806DAB58;
extern const float lbl_806DAB5C;
extern const float lbl_806DAB60;
extern const float lbl_806DAB64;
extern const float lbl_806DAB68;
extern const float lbl_806DAB00[2];
extern const float lbl_806DAB08[2];
extern const float lbl_803C26A0[3];
extern const float lbl_803C26AC[3];
}

static inline float ButtonX(const clMnYesNoInterface *button, float offset) {
    return button->scaleX * offset + (button->x + button->field34);
}

static inline float ButtonY(const clMnYesNoInterface *button, float offset) {
    return button->scaleY * offset + (button->y + button->field38);
}

static inline void PlaceButton(clMnYesNoInterface *button, ResCtrl &c, unsigned int col, float ox, float oy) {
    c.SetColor(col);
    c.SetScaleXY(button->scaleX, button->scaleY);
    float px = ButtonX(button, ox);
    float py = ButtonY(button, oy);
    c.Show(px, py, lbl_806DAB20);
}

#define PUT_BUTTON(c, res, col, ox, oy, lay) \
    fn_80121E10(&c); \
    c.resId = res; \
    PlaceButton(this, c, col, ox, oy); \
    fn_8011FAFC(&c, lay)

static inline float SpriteX(const clMnYesNoInterface *button, float offset) {
    return offset * button->scaleX + (button->x + button->field34);
}

static inline float SpriteY(const clMnYesNoInterface *button, float offset) {
    return offset * button->scaleY + (button->y + button->field38);
}

static inline void PlaceButtonSprite(clMnYesNoInterface *button, ResCtrl &c, unsigned int col, float ox, float oy) {
    c.SetColor(col);
    c.SetScaleXY(button->scaleX, button->scaleY);
    float py;
    float px;
    px = SpriteX(button, ox);
    py = SpriteY(button, oy);
    c.Show(px, py, lbl_806DAB20);
}

static inline void DrawButtonSprites(clMnSelNo *button) {
    ResCtrl c;
    int lay = button->layer;
    unsigned int col = button->Color();
    float f = fn_8020A6CC(button->fade.p);
    fn_80121E10(&c);
    c.resId = 0x72F;
    PlaceButtonSprite(button, c, col, lbl_806DAB00[0], lbl_806DAB08[0]);
    fn_8011FAFC(&c, lay);
    fn_80121E10(&c);
    c.resId = 0x72E;
    c.SetColor(col);
    c.SetScaleXY(button->scaleX, button->scaleY);
    float px = ButtonX(button, lbl_806DAB00[1] + f);
    float py = SpriteY(button, lbl_806DAB08[1]);
    c.Show(px, py, lbl_806DAB20);
    fn_8011FAFC(&c, lay);
}



static inline float TextRow(float row, float origin) {
    return row + origin;
}





/*
 * Selector sparkle and right-hand button drawing (0x802052E0..0x80205DCC).
 */

extern "C" {
void fn_8011FAFC(ResCtrl *ctrl, int layer);
void fn_80121E10(ResCtrl *ctrl);
float fn_8020A6CC(FlowFader *fader);
void *fn_801F8E58(void);
void fn_801F8A34(void *a, TextManager *tm, int layer);
void fn_801F93D0(TextManager *tm, float sx, float sy);
void fn_80270C78(void *arr, void *dtor);
extern const float lbl_806DAB58;
extern const float lbl_806DAB5C;
extern const float lbl_806DAB60;
extern const float lbl_806DAB64;
extern const float lbl_806DAB68;
extern const float lbl_806DAB00[2];
extern const float lbl_806DAB08[2];
extern const float lbl_803C26A0[3];
extern const float lbl_803C26AC[3];
}








/*
 * Left-hand selector button background and update (0x80205DCC..0x8020615C).
 */

extern "C" {
float fn_8020A6CC(FlowFader *fader);
void *fn_801F8E58(void);
void fn_801F8A34(void *a, TextManager *tm, int layer);
void fn_801F93D0(TextManager *tm, float sx, float sy);
int CreditMgr_GetPlayState(int slot);
int CreditMgr_GetCreditCount(int slot);
extern unsigned char lbl_80598A60[];
extern const int lbl_803C25A8[42];
extern const float lbl_806DAB34;
extern const float lbl_806DAB38;
extern const float lbl_806DAB3C;
extern const float lbl_806DAB4C;
extern const float lbl_806DAB60;
extern const float lbl_806DAB68;
extern const float lbl_806DAB78;
extern const float lbl_806DAB7C;
extern const float lbl_806DAB80;
extern const float lbl_806DAB84;
extern const float lbl_806DAB88;
extern const float lbl_806DAB8C;
extern const float lbl_806DAB90;
extern const float lbl_806DAB94;
extern const float lbl_806DAB98;
extern const float lbl_806DAB9C;
extern const float lbl_806DABA0;
extern const float lbl_806DAB00[2];
extern const float lbl_806DAB08[2];
extern const float lbl_803C2688[3];
extern const float lbl_803C2694[3];
}

static inline float LocalX(const clMnYesNoInterface *button, float offset) {
    return offset * button->scaleX + (button->x + button->field34);
}

static inline float LocalY(const clMnYesNoInterface *button, float offset) {
    return offset * button->scaleY + (button->y + button->field38);
}

static inline float SlidingX(const clMnYesNoInterface *button, float offset, float slide) {
    return button->scaleX * (offset + slide) + (button->x + button->field34);
}

static inline void DrawBackground(clMnSelYes *button) {
    ResCtrl c;
    int lay = button->layer;
    unsigned int col = button->Color();
    float f = -fn_8020A6CC(button->fade.p);
    fn_80121E10(&c);
    c.resId = 0x72F;
    c.SetColor(col);
    c.SetScaleXY(button->scaleX, button->scaleY);
    float px = LocalX(button, lbl_806DAB00[0]);
    float py = LocalY(button, lbl_806DAB08[0]);
    c.Show(px, py, lbl_806DAB20);
    fn_8011FAFC(&c, lay);
    fn_80121E10(&c);
    c.resId = 0x72E;
    c.SetColor(col);
    c.SetScaleXY(button->scaleX, button->scaleY);
    float px2 = SlidingX(button, lbl_806DAB00[1], f);
    float py2 = LocalY(button, lbl_806DAB08[1]);
    c.Show(px2, py2, lbl_806DAB20);
    fn_8011FAFC(&c, lay);
}




/*
 * Left-hand selector credit display (0x8020615C..0x802064D8).
 */

extern "C" {
float fn_8020A6CC(FlowFader *fader);
void *fn_801F8E58(void);
void fn_801F8A34(void *a, TextManager *tm, int layer);
void fn_801F93D0(TextManager *tm, float sx, float sy);
int CreditMgr_GetPlayState(int slot);
int CreditMgr_GetCreditCount(int slot);
extern unsigned char lbl_80598A60[];
extern const int lbl_803C25A8[42];
extern const float lbl_806DAB34;
extern const float lbl_806DAB38;
extern const float lbl_806DAB3C;
extern const float lbl_806DAB4C;
extern const float lbl_806DAB60;
extern const float lbl_806DAB68;
extern const float lbl_806DAB78;
extern const float lbl_806DAB7C;
extern const float lbl_806DAB80;
extern const float lbl_806DAB84;
extern const float lbl_806DAB88;
extern const float lbl_806DAB8C;
extern const float lbl_806DAB90;
extern const float lbl_806DAB94;
extern const float lbl_806DAB98;
extern const float lbl_806DAB9C;
extern const float lbl_806DABA0;
extern const float lbl_806DAB00[2];
extern const float lbl_806DAB08[2];
extern const float lbl_803C2688[3];
extern const float lbl_803C2694[3];
}





/*
 * Left-hand selector button and the shared button animation
 * (0x80205DCC..0x80207324).
 */

extern "C" {
float fn_8020A6CC(FlowFader *fader);
void *fn_801F8E58(void);
void fn_801F8A34(void *a, TextManager *tm, int layer);
void fn_801F93D0(TextManager *tm, float sx, float sy);
int CreditMgr_GetPlayState(int slot);
int CreditMgr_GetCreditCount(int slot);
extern unsigned char lbl_80598A60[];
extern const int lbl_803C25A8[42];
extern const float lbl_806DAB34;
extern const float lbl_806DAB38;
extern const float lbl_806DAB3C;
extern const float lbl_806DAB4C;
extern const float lbl_806DAB60;
extern const float lbl_806DAB68;
extern const float lbl_806DAB78;
extern const float lbl_806DAB7C;
extern const float lbl_806DAB80;
extern const float lbl_806DAB84;
extern const float lbl_806DAB88;
extern const float lbl_806DAB8C;
extern const float lbl_806DAB90;
extern const float lbl_806DAB94;
extern const float lbl_806DAB98;
extern const float lbl_806DAB9C;
extern const float lbl_806DABA0;
extern const float lbl_806DAB00[2];
extern const float lbl_806DAB08[2];
extern const float lbl_803C2688[3];
extern const float lbl_803C2694[3];
}








/*
 * Left-hand selector button and the shared button animation
 * (0x80205DCC..0x80207324).
 */

extern "C" {
float fn_8020A6CC(FlowFader *fader);
void *fn_801F8E58(void);
void fn_801F8A34(void *a, TextManager *tm, int layer);
void fn_801F93D0(TextManager *tm, float sx, float sy);
int CreditMgr_GetPlayState(int slot);
int CreditMgr_GetCreditCount(int slot);
extern unsigned char lbl_80598A60[];
extern const int lbl_803C25A8[42];
extern const float lbl_806DAB34;
extern const float lbl_806DAB38;
extern const float lbl_806DAB3C;
extern const float lbl_806DAB4C;
extern const float lbl_806DAB60;
extern const float lbl_806DAB68;
extern const float lbl_806DAB78;
extern const float lbl_806DAB7C;
extern const float lbl_806DAB80;
extern const float lbl_806DAB84;
extern const float lbl_806DAB88;
extern const float lbl_806DAB8C;
extern const float lbl_806DAB90;
extern const float lbl_806DAB94;
extern const float lbl_806DAB98;
extern const float lbl_806DAB9C;
extern const float lbl_806DABA0;
extern const float lbl_806DAB00[2];
extern const float lbl_806DAB08[2];
extern const float lbl_803C2688[3];
extern const float lbl_803C2694[3];
}







/*
 * Left-hand selector button and the shared button animation
 * (0x80205DCC..0x80207324).
 */

extern "C" {
float fn_8020A6CC(FlowFader *fader);
void *fn_801F8E58(void);
void fn_801F8A34(void *a, TextManager *tm, int layer);
void fn_801F93D0(TextManager *tm, float sx, float sy);
int CreditMgr_GetPlayState(int slot);
int CreditMgr_GetCreditCount(int slot);
extern unsigned char lbl_80598A60[];
extern const int lbl_803C25A8[42];
extern const float lbl_806DAB34;
extern const float lbl_806DAB38;
extern const float lbl_806DAB3C;
extern const float lbl_806DAB4C;
extern const float lbl_806DAB60;
extern const float lbl_806DAB68;
extern const float lbl_806DAB78;
extern const float lbl_806DAB7C;
extern const float lbl_806DAB80;
extern const float lbl_806DAB84;
extern const float lbl_806DAB88;
extern const float lbl_806DAB8C;
extern const float lbl_806DAB90;
extern const float lbl_806DAB94;
extern const float lbl_806DAB98;
extern const float lbl_806DAB9C;
extern const float lbl_806DABA0;
extern const float lbl_806DAB00[2];
extern const float lbl_806DAB08[2];
extern const float lbl_803C2688[3];
extern const float lbl_803C2694[3];
}






/* Reuse the original RTTI records through the CW cast runtime. */
extern "C" {
void *fn_80271340(void *, int, void *, void *, int);
extern unsigned char FlowTask_RTTI_806D02A0[8];
extern unsigned char YesNoTask_RTTI_806D02A8[8];
extern unsigned char YesNoButtonL_RTTI_806D02C0[8];
extern unsigned char YesNoButtonR_RTTI_806D02C8[8];
}







/*
 * clMnYesNoInterface base ctor and the yes/no popup service (0x80207324..0x80207E3C):
 * open/close entry points, option queries and service init/shutdown.
 */

extern "C" {
void DebugPrintf(const char *fmt, ...);
int fn_80202E4C(int msg);
int fn_80202E20(int msg);
const char *fn_80202D70(int msg, int line);
const char *fn_80202CC0(int msg, int line);
clMnYesNoWindow *fn_80204778(int kind, unsigned char defYes, int layer, int id);
extern const float lbl_806DAB34;
extern const float lbl_806DAB38;
extern const float lbl_806DAB3C;
extern const float lbl_806DAB98;
extern const float lbl_806DABA4;
extern const char lbl_803C2764[];
extern const char lbl_803C2780[];
extern FlowSceneList *lbl_806D19F8;
extern int lbl_806D19FC;

void fn_80207760(bool show);
void fn_80207810(void);
void fn_80207848(void);
int fn_80207880(void);
int fn_802078B4(void);
int fn_802078F8(void);
int fn_80207AD8(int kind, unsigned char defYes);
int fn_80207B28(unsigned char v);
unsigned char fn_80207C64(void);
int fn_80207CC4(int choice);
void fn_80207D38(void);
void fn_80207DA8(int layer);
}













static inline void CloseButton(clMnYesNoInterface *b) {
    if (b && b->state <= 1) {
        if (b->selected) {
            fn_8020A734(b->appear.p, 5, lbl_806DAB20, lbl_806DAB18);
            fn_8020A734(b->offX.p, 0xA, lbl_806DAB10, lbl_806DAB10);
            fn_8020A734(b->offY.p, 0xA, lbl_806DAB10, lbl_806DAB10);
            fn_8020A7CC(b->alphaF.p, 0xFF, 0xFF, 0xA);
        } else {
            fn_8020A734(b->appear.p, 0xA, lbl_806DAB20, lbl_806DAB10);
        }
        b->state = 2;
    }
}







































clMnYesNoInterface::clMnYesNoInterface(int kind_, bool flag, int layer_, int id)
    : clMnTaskInterface(id), layer(layer_), kind(kind_), state(0), fade(new FlowFaderF(lbl_806DAB10)), x(lbl_806DAB10),
      y(lbl_806DABA4), field34(lbl_806DAB10), field38(lbl_806DAB10), scale(lbl_806DAB20), scaleX(lbl_806DAB20),
      scaleY(lbl_806DAB20), alpha(0xFF), selected(0), appear(new FlowFaderF(lbl_806DAB10)),
      offX(new FlowFaderF(lbl_806DAB10)), offY(new FlowFaderF(lbl_806DAB10)), alphaF(new FlowFaderI),
      pulse(new FlowFaderF(lbl_806DAB10)), zoomX(new FlowFaderF(lbl_806DAB10)), zoomY(new FlowFaderF(lbl_806DAB10)) {
    PreloadResource(0x72F);
    PreloadResource(0x72E);
    if (flag) {
        field18 = fn_80202E4C(kind_);
        text0 = fn_80202D70(kind_, 0);
        text1 = fn_80202D70(kind_, 1);
    } else {
        field18 = fn_80202E20(kind_);
        text0 = fn_80202CC0(kind_, 0);
        text1 = fn_80202CC0(kind_, 1);
    }
    scale = lbl_806DAB10;
    scaleX = scale;
    scaleY = scale;
    alpha = 0xFF;
    fn_8020A734(fade.p, 1, lbl_806DAB10, lbl_806DAB10);
    fn_8020A734(appear.p, 0xF, lbl_806DAB10, lbl_806DAB98);
    fn_8020A734(offX.p, 1, lbl_806DAB10, lbl_806DAB10);
    fn_8020A734(offY.p, 1, lbl_806DAB10, lbl_806DAB10);
    fn_8020A7CC(alphaF.p, 0xFF, 0xFF, 1);
    if (selected) {
        fn_8020A734(pulse.p, 1, lbl_806DAB20, lbl_806DAB20);
    } else {
        fn_8020A734(pulse.p, 1, lbl_806DAB18, lbl_806DAB18);
    }
    fn_8020A734(zoomX.p, 1, lbl_806DAB20, lbl_806DAB20);
    fn_8020A734(zoomY.p, 1, lbl_806DAB20, lbl_806DAB20);
}

clMnYesNoInterface::~clMnYesNoInterface() {}

void clMnYesNoInterface::Animate() {
    bool sel = selected;
    field34 = fn_8020A6CC(offX.p);
    field38 = fn_8020A6CC(offY.p);
    FlowFaderF *ap = appear.p;
    float p = fn_8020A6CC(pulse.p);
    float a = fn_8020A6CC(ap);
    a *= p;
    scale = lbl_806DAB18 * a;
    scaleX = scale * fn_8020A6CC(zoomX.p);
    scaleY = scale * fn_8020A6CC(zoomY.p);
    alpha = fn_8020A788(alphaF.p);
    fade.p->Step();
    pulse.p->Step();
    if (pulse.p->Done()) {
        float v = fn_8020A6CC(pulse.p);
        if (lbl_806DAB24 == v) {
            if (sel) {
                fn_8020A734(fade.p, 5, lbl_806DAB30, lbl_806DAB2C);
                fn_8020A734(pulse.p, 5, lbl_806DAB24, lbl_806DAB20);
            } else {
                fn_8020A734(fade.p, 5, lbl_806DAB30, lbl_806DAB14);
                fn_8020A734(pulse.p, 5, lbl_806DAB24, lbl_806DAB1C);
            }
        } else if (lbl_806DAB1C == v) {
            if (sel) {
                fn_8020A734(fade.p, 5, lbl_806DAB14, lbl_806DAB30);
                fn_8020A734(pulse.p, 5, lbl_806DAB1C, lbl_806DAB24);
            } else {
                fn_8020A734(fade.p, 5, lbl_806DAB14, lbl_806DAB10);
                fn_8020A734(pulse.p, 5, lbl_806DAB1C, lbl_806DAB18);
            }
        }
    }
    zoomX.p->Step();
    zoomY.p->Step();
    if (sel) {
        if (zoomX.p->Done()) {
            float v = fn_8020A6CC(zoomX.p);
            if (lbl_806DAB24 == v) {
                fn_8020A734(zoomX.p, 5, lbl_806DAB24, lbl_806DAB28);
                fn_8020A734(zoomY.p, 5, lbl_806DAB28, lbl_806DAB24);
            } else if (lbl_806DAB28 == v) {
                fn_8020A734(zoomX.p, 0xF, lbl_806DAB28, lbl_806DAB90);
                fn_8020A734(zoomY.p, 0xF, lbl_806DAB24, lbl_806DAB94);
            } else if (lbl_806DAB90 == v) {
                fn_8020A734(zoomX.p, 5, lbl_806DAB90, lbl_806DAB94);
                fn_8020A734(zoomY.p, 5, lbl_806DAB94, lbl_806DAB90);
            } else if (lbl_806DAB94 == v) {
                fn_8020A734(zoomX.p, 0xA, lbl_806DAB94, lbl_806DAB20);
                fn_8020A734(zoomY.p, 0xA, lbl_806DAB90, lbl_806DAB20);
            } else {
                fn_8020A734(zoomX.p, 0xF, lbl_806DAB20, lbl_806DAB24);
                fn_8020A734(zoomY.p, 0xF, lbl_806DAB20, lbl_806DAB28);
            }
        }
    }
    appear.p->Step();
    offX.p->Step();
    offY.p->Step();
    alphaF.p->Step();
    if (appear.p->Done()) {
        float v = fn_8020A6CC(appear.p);
        switch (state) {
        case 0:
            if (lbl_806DAB98 == v) {
                fn_8020A734(appear.p, 5, lbl_806DAB98, lbl_806DAB20);
                return;
            }
            fn_8020A734(appear.p, 1, lbl_806DAB20, lbl_806DAB20);
            state = 1;
            return;
        case 2:
            if (lbl_806DAB18 == v) {
                fn_8020A734(appear.p, 5, lbl_806DAB18, lbl_806DAB9C);
                return;
            }
            if (lbl_806DAB9C == v) {
                fn_8020A734(appear.p, 0xF, lbl_806DAB9C, lbl_806DAB34);
                fn_8020A734(offX.p, 0xF, lbl_806DAB10, lbl_806DABA0 - x);
                fn_8020A734(offY.p, 0xF, lbl_806DAB10, lbl_806DAB4C - y);
                fn_8020A7CC(alphaF.p, 0xFF, 0, 0xF);
                return;
            }
            state = 3;
            return;
        case 3:
            field0C = 1;
            state = -1;
            break;
        }
    }
}

clMnSelYes::~clMnSelYes() {
    delete[] texts;
}

void clMnSelYes::Finish() {
    delete this;
}

void clMnSelYes::DrawLabel() {
    ResCtrl c;
    int lay = layer;
    float f = -fn_8020A6CC(fade.p);
    float oy = lbl_806DAB10;
    unsigned int col = Color();
    if (kind == 1) {
        oy = lbl_806DAB8C;
    }
    if (field6C && state <= 1) {
        fn_80121E10(&c);
        c.resId = 0x730;
        c.SetColor((col & ~0xFF) | fn_8020A788(fader70.p));
        float sy = scaleY * fn_8020A6CC(fader78.p);
        float sx = scaleX * fn_8020A6CC(fader74.p);
        c.SetScaleXY(sx, sy);
        float px = scaleX * (lbl_803C2688[0] + f) + (x + field34);
        float py = scaleY * (lbl_803C2694[0] + oy) + (y + field38);
        c.Show(px, py, lbl_806DAB20);
        fn_8011FAFC(&c, lay);
    }
    if (!isJapanese()) {
        int res = 0x729;
        float px;
        float py;
        px = scaleX * (lbl_803C2688[1] + f) + (x + field34);
        py = scaleY * (lbl_803C2694[1] + oy) + (y + field38);
        if (kind == 0) {
            res = 0x74C;
            px += lbl_806DAB68 * scaleX;
        } else if (kind == 1) {
            res = 0x74E;
            px += lbl_806DAB68 * scaleX;
        }
        PutAbs(c, res, col, px, py, lay);
    } else {
        float py;
        float px;
        px = scaleX * (lbl_803C2688[1] + f) + (x + field34);
        py = scaleY * (lbl_803C2694[1] + oy) + (y + field38);
        PutAbs(c, 0x729, col, px, py, lay);
    }
    fn_80121E10(&c);
    c.resId = field18;
    c.SetColor(col);
    c.SetScaleXY(scaleX, scaleY);
    float px = ButtonX(this, lbl_803C2688[2] + f);
    float py = ButtonY(this, lbl_803C2694[2] + oy);
    c.Show(px, py, lbl_806DAB20);
    fn_8011FAFC(&c, lay);
}

#pragma push
#pragma opt_lifetimes off
void clMnSelYes::DrawCredits() {
    const char *pool = (const char *)lbl_803C25A8;
    int lay = layer;
    float oy;
    float f = -fn_8020A6CC(fade.p);
    oy = lbl_806DAB10;
    unsigned int col = Color();
    if (kind == 1) {
        oy = lbl_806DAB60;
    }
    bool show = 0;
    int credits = 0;
    if (kind == 1) {
        if (CreditMgr_GetPlayState(2) == 3) {
            show = 0;
        } else {
            show = 1;
            credits = CreditMgr_GetCreditCount(2);
        }
    } else if (kind == 2 || kind == 10) {
        if (CreditMgr_GetPlayState(3) == 3) {
            show = 0;
        } else {
            show = 1;
            credits = CreditMgr_GetCreditCount(3);
        }
    } else if (kind == 11 || kind == 12) {
        if (CreditMgr_GetPlayState(4) == 3) {
            show = 0;
        } else {
            show = 1;
            credits = CreditMgr_GetCreditCount(4);
        }
    } else if (kind == 3 || kind == 4) {
        if (CreditMgr_GetPlayState(1) == 3) {
            show = 0;
        } else {
            show = 1;
            credits = CreditMgr_GetCreditCount(1);
        }
    }
    if (credits <= 0) {
        field80 = 1;
    }
    if (show) {
        if (!field80) {
            if (!isJapanese()) {
                if (lbl_80598A60[0x27] == 0) {
                    if (CreditMgr_GetCoinCount(0, -1) == 0) {
                        TexMgr_SetTexture(&texts[0], pool + 0x148, credits);
                    } else {
                        TexMgr_SetTexture(&texts[0], pool + 0x158, credits);
                    }
                } else if (CreditMgr_GetCoinCount(0, -1) == 0) {
                    TexMgr_SetTexture(&texts[0], pool + 0x16C, credits);
                } else {
                    TexMgr_SetTexture(&texts[0], pool + 0x178, credits);
                }
                TexMgr_SetTexture(&texts[1], pool + 0x188);
            } else {
                TexMgr_SetTexture(&texts[0], pool + 0x19C);
                TexMgr_SetTexture(&texts[1], pool + 0x1AC, credits);
            }
        } else {
            TexMgr_SetTexture(&texts[0], text0);
            TexMgr_SetTexture(&texts[1], text1);
        }
    }
    oy = lbl_806DAB84 + oy;
    f = lbl_806DAB88 + f;
    for (int i = 0; i < 2; i++) {
        float dy = (float)(i * 0x1C);
        texts[i].color = col;
        fn_801F93EC(&texts[i], scaleX * f + (x + field34), scaleY * (dy + oy) + (y + field38));
        fn_801F93D0(&texts[i], scaleX, scaleY);
        fn_801F8A34(fn_801F8E58(), &texts[i], lay);
    }
}

#pragma pop

void clMnSelYes::Update() {
    DrawBackground(this);
    DrawLabel();
    if (field6D) {
        DrawCredits();
    }
    Animate();
    if (field6C) {
        fader70.p->Step();
        fader74.p->Step();
        fader78.p->Step();
        if (fader74.p->Done()) {
            float v = fn_8020A6CC(fader74.p);
            if (lbl_806DAB38 == v) {
                fn_8020A734(fader74.p, 5, lbl_806DAB38, lbl_806DAB3C);
                fn_8020A734(fader78.p, 5, lbl_806DAB3C, lbl_806DAB38);
                return;
            }
            if (lbl_806DAB3C == v) {
                fn_8020A734(fader74.p, 0xF, lbl_806DAB3C, lbl_806DAB78);
                fn_8020A734(fader78.p, 0xF, lbl_806DAB38, lbl_806DAB7C);
                return;
            }
            if (lbl_806DAB78 == v) {
                fn_8020A7CC(fader70.p, 0xFF, 0, 0xF);
                fn_8020A734(fader74.p, 5, lbl_806DAB78, lbl_806DAB7C);
                fn_8020A734(fader78.p, 5, lbl_806DAB7C, lbl_806DAB78);
                return;
            }
            if (lbl_806DAB7C == v) {
                fn_8020A7CC(fader70.p, 0xFF, 0, 0xF);
                fn_8020A734(fader74.p, 0xA, lbl_806DAB7C, lbl_806DAB80);
                fn_8020A734(fader78.p, 0xA, lbl_806DAB78, lbl_806DAB80);
                return;
            }
            fn_8020A7CC(fader70.p, 0, 0xFF, 0x14);
            fn_8020A734(fader74.p, 0xF, lbl_806DAB34, lbl_806DAB38);
            fn_8020A734(fader78.p, 0xF, lbl_806DAB34, lbl_806DAB3C);
        }
    }
}

void clMnSelYes::Draw() {}

clMnSelNo::~clMnSelNo() {
    delete[] texts;
}

void clMnSelNo::Finish() {
    delete this;
}

void clMnSelNo::DrawLabel() {
    ResCtrl c;
    int lay = layer;
    float f = fn_8020A6CC(fade.p);
    float oy = lbl_806DAB10;
    float tx;
    unsigned int col = Color();
    if (kind == 1) {
        oy = lbl_806DAB60;
    }
    if (!isJapanese()) {
        int res = 0x72A;
        float py;
        float px = scaleX * (lbl_803C26A0[0] + f) + (x + field34);
        py = scaleY * (lbl_803C26AC[0] + oy) + (y + field38);
        if (kind == 0) {
            res = 0x74D;
            px += lbl_806DAB64 * scaleX;
        } else if (kind == 1) {
            res = 0x74F;
            px += lbl_806DAB68 * scaleX;
        }
        PutAbs(c, res, col, px, py, lay);
    } else {
        float py;
        float px;
        px = scaleX * (lbl_803C26A0[0] + f) + (x + field34);
        py = scaleY * (lbl_803C26AC[0] + oy) + (y + field38);
        PutAbs(c, 0x72A, col, px, py, lay);
    }
    PUT_BUTTON(c, field18, col, lbl_803C26A0[1] + f, lbl_803C26AC[1] + oy, lay);
    if (field70) {
        tx = lbl_803C26A0[2] + f;
        oy = lbl_803C26AC[2] + oy;
        for (int i = 0; i < 2; i++) {
            texts[i].color = col;
            fn_801F93EC(&texts[i], scaleX * tx + (x + field34), scaleY * TextRow((float)(i * 0x1C), oy) + (y + field38));
            fn_801F93D0(&texts[i], scaleX, scaleY);
            fn_801F8A34(fn_801F8E58(), &texts[i], lay);
        }
    }
}

void clMnSelNo::Update() {
    DrawButtonSprites(this);
    DrawLabel();
    Animate();
}

void clMnSelNo::Draw() {}

clMnCdAllowDraw::~clMnCdAllowDraw() {}

void clMnCdAllowDraw::Finish() {
    delete this;
}

void clMnCdAllowDraw::Update() {
    ResCtrl c;
    float off = fn_8020A6CC(offset.p);
    float s = fn_8020A6CC(scale.p);
    unsigned int col = (unsigned int)(lbl_806DAB58 * fn_8020A6CC(alpha.p)) | ~0xFF;
    float px;
    if (flag) {
        px = x + off;
    } else {
        px = x - off;
    }
    c.resId = 0x8A3;
    c.Show(px, y, lbl_806DAB20);
    c.SetColor(col);
    c.SetScale(s);
    c.flipX = flag == 0;
    c.flipY = 0;
    fn_8011FAFC(&c, layer);
    offset.p->Step();
    scale.p->Step();
    alpha.p->Step();
    if (alpha.p->Done()) {
        if (lbl_806DAB20 == fn_8020A6CC(alpha.p)) {
            fn_8020A734(alpha.p, 0xA, lbl_806DAB20, lbl_806DAB5C);
            return;
        }
        field0C = 1;
    }
}

void clMnCdAllowDraw::Draw() {}

clMnCdAllow::~clMnCdAllow() {
    fn_801F4D3C(list.p);
    fn_80120A08(0x8A3);
}

void clMnCdAllow::Finish() {
    delete this;
}

void clMnCdAllow::Update() {
    int t = fn_8020A788(timer.p);
    if (t % 15 == 0) {
        int id = (t / 15) * 2;
        FlowSceneList *l;
        bool f;
        int lay;
        float px;
        float py;
        l = list.p;
        lay = layer;
        f = visible;
        py = y;
        px = x;
        fn_801F4DF0(l, new clMnCdAllowDraw(id, lay, px, py, f), 0);
    }
    list.p->Update();
    timer.p->Step();
    if (timer.p->Done()) {
        timer.p->b = 0;
    }
}

void clMnCdAllow::Draw() {
    list.p->Draw();
}

clMnYesNoWindow::clMnYesNoWindow(int kind_, unsigned char defYes, int layer_, int id)
    : clMnTaskInterface(id), list(new SceneListImpl), layer(layer_), kind(kind_), choice(defYes ? 0 : 1), field20(0) {
    {
        FlowSceneList *l = list.p;
        fn_801F4DF0(l, new clMnSelYes(kind_, layer_), 0);
    }
    {
        FlowSceneList *l = list.p;
        fn_801F4DF0(l, new clMnSelNo(kind_, layer_), 0);
    }
    {
        clMnYesNoInterface *b = CastYesNoButton(fn_801F4DC0(list.p, 0));
        if (b) {
            if (kind_ == 0xD) {
                b->x = lbl_806DAB44;
                b->y = lbl_806DAB48;
            } else {
                b->x = lbl_806DAB44;
                b->y = lbl_806DAB4C;
            }
            b->SetSelected(choice == 0);
        }
    }
    {
        clMnYesNoInterface *b = CastYesNoButton(fn_801F4DC0(list.p, 1));
        if (b) {
            if (kind_ == 0xD) {
                b->x = lbl_806DAB50;
                b->y = lbl_806DAB48;
            } else {
                b->x = lbl_806DAB50;
                b->y = lbl_806DAB4C;
            }
            b->SetSelected(choice != 0);
        }
    }
    {
        FlowSceneList *l = list.p;
        fn_801F4DF0(l, new clMnCdAllow(layer_), 0x14);
    }
    clMnTaskInterface *c = fn_801F4DC0(list.p, 0xA);
    if (c) {
        bool v = choice == 0;
        CastYesNoCursor(c)->visible = v;
    }
}

clMnYesNoWindow::~clMnYesNoWindow() {}

extern "C" clMnYesNoWindow *fn_80204778(int kind, unsigned char defYes, int layer, int id) {
    return new clMnYesNoWindow(kind, defYes, layer, id);
}

void clMnYesNoWindow::Finish() {
    delete this;
}

void clMnYesNoWindow::Update() {
    clMnTaskInterface *t0 = fn_801F4DC0(list.p, 0);
    clMnSelYes *l = CastYesNoButtonL(t0);
    clMnTaskInterface *t1 = fn_801F4DC0(list.p, 1);
    clMnSelNo *r = CastYesNoButtonR(t1);
    int sel = choice;
    if (l && r) {
        YESNO_SET_SELECTED(l, sel == 0);
        YESNO_SET_SELECTED(r, sel != 0);
    }
    clMnTaskInterface *c = fn_801F4DC0(list.p, 0xA);
    if (c) {
        clMnCdAllow *cur = CastYesNoCursor(c);
        cur->visible = sel == 0;
    }
    if (list.p->entries.count <= 0) {
        field0C = 1;
    }
    list.p->Update();
}

void clMnYesNoWindow::Draw() {
    list.p->Draw();
}

/* Uncalled pool-order member, as clLineManager::PrintLines (layout fakematch).
 * These are the original selector formats and inline helper RTTI names. */
void clMnYesNoWindow::PrintPoolStrings() {
    DebugPrintf("\201@\203R\203C\203\223\202\360%d\226\207");
    DebugPrintf("\201@\203R\203C\203\223\202\360\202\240\202\306%d\226\207");
    DebugPrintf("\201@%d00\211~");
    DebugPrintf("\201@\202\240\202\306%d00\211~");
    DebugPrintf("\201@ \223\374\202\352\202\304\202\255\202\276\202\263\202\242");
    DebugPrintf("\201@Please insert");
    DebugPrintf("\201@ %d coin(s)");
    DebugPrintf("clMnYesNoManager::free()\n");
    DebugPrintf("clMnYesNoManager::load()\n");
    DebugPrintf("clFloatCounter");
    DebugPrintf("clCounterInterface");
    DebugPrintf("clIntCounter");
    DebugPrintf("clYTaskManager<clMnTaskInterface>");
}
