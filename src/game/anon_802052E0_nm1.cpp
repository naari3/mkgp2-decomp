#include "game/YesNoButtonRMatchPrivate.h"

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

static inline float ButtonX(const YesNoButton *button, float offset) {
    return button->scaleX * offset + (button->x + button->field34);
}

static inline float ButtonY(const YesNoButton *button, float offset) {
    return button->scaleY * offset + (button->y + button->field38);
}

static inline void PlaceButton(YesNoButton *button, ResCtrl &c, unsigned int col, float ox, float oy) {
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

static inline float SpriteX(const YesNoButton *button, float offset) {
    return offset * button->scaleX + (button->x + button->field34);
}

static inline float SpriteY(const YesNoButton *button, float offset) {
    return offset * button->scaleY + (button->y + button->field38);
}

static inline void PlaceButtonSprite(YesNoButton *button, ResCtrl &c, unsigned int col, float ox, float oy) {
    c.SetColor(col);
    c.SetScaleXY(button->scaleX, button->scaleY);
    float py;
    float px;
    px = SpriteX(button, ox);
    py = SpriteY(button, oy);
    c.Show(px, py, lbl_806DAB20);
}

static inline void DrawButtonSprites(YesNoButtonR *button) {
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

void YesNoButtonR::Update() {
    DrawButtonSprites(this);
    DrawLabel();
    Animate();
}

static inline float TextRow(float row, float origin) {
    return row + origin;
}

void YesNoButtonR::DrawLabel() {
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

