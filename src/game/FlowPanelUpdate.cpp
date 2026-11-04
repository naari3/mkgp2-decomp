#include "game/FlowPanelNative.h"
extern "C" {
extern const float lbl_806DA1C0, lbl_806DA1C4, lbl_806DA1C8;
extern const float lbl_806DA1E0, lbl_806DA1E4, lbl_806DA1E8, lbl_806DA1EC;
extern const float lbl_806DA1F0, lbl_806DA1F4;
unsigned char fn_8019FE78(PanelSprite *);
void fn_801A0500(PanelSprite *);
void Sprite_SetupAnim(PanelSprite *, int, int, int);
void Sprite_SetAnimTime(PanelSprite *, float);
unsigned char Sprite_AdvanceAnim(PanelSprite *, float);
void fn_801FE1D0();
void fn_801D92D0(FlowPanel *, int *);
}
union PanelColor {
    unsigned int rgba;
    struct { unsigned int rgb : 24; unsigned int a : 8; } channel;
};
static inline void ClosePanel(FlowPanel *self) {
    if (self->state != 0 && self->state != 3) {
        self->state = 3;
        self->timer = 0;
        self->alpha = 128;
        self->layout = -1;
        if (self->labelA) Sprite_SetupAnim(self->labelA, 15, 1, 0);
        else self->labelA = new PanelSprite(15, 1, 0);
        Sprite_SetAnimTime(self->labelA, lbl_806DA1C4);
        self->labelA->layer = self->layer;
        for (int i = 0; i < 3; i++) {
            TexMgr_SetTexture(self->texts[i]->tm(), lbl_806DA1AC);
            self->texts[i]->tm()->color = 0xFFFFFF00;
        }
        fn_80121E10(self->icons[1]);
        fn_80121E10(self->icons[0]);
        fn_80121E10(self->icons[2]);
        if (self->labelB) fn_801A0500(self->labelB);
        fn_801FE1D0();
    }
}
extern "C" void fn_801D9B70(FlowPanel *self, unsigned char pressed) {
    switch (self->state) {
    case 0: self->timer = 0; break;
    case 1:
        if (self->timer <= 10) {
            self->alpha = (int)(lbl_806DA1E0 * (self->timer / lbl_806DA1C8));
        }
        if (self->timer >= 8) {
            float t = ((float)self->timer - 8.0f) * 0.125f;
            if (t > 1.0f) t = 1.0f;
            PanelColor c;
            c.rgba = 0xFFFFFF00;
            c.channel.a = (int)(lbl_806DA1EC * t);
            self->texts[0]->tm()->color = c.rgba;
            self->texts[1]->tm()->color = c.rgba;
            self->texts[2]->tm()->color = c.rgba;
        }
        if (!fn_8019FE78(self->labelA)) {
            self->state = 2;
            self->timer = 0;
            fn_801A0500(self->labelA);
            self->icons[0]->resId = 0x1E86;
            self->texts[0]->tm()->color = -1;
            self->texts[1]->tm()->color = -1;
            self->texts[2]->tm()->color = -1;
        }
        break;
    case 2:
        if ((self->timer >= 180 || pressed) && self->autoClose == 1) ClosePanel(self);
        break;
    case 3:
        if (self->timer <= 15) {
            self->alpha = (int)(lbl_806DA1E0 * (lbl_806DA1C0 - self->timer / lbl_806DA1F0));
        }
        {
            float t = lbl_806DA1C0 - self->timer / lbl_806DA1F0;
            if (t < lbl_806DA1C4) t = lbl_806DA1C4;
            PanelColor c;
            c.rgba = 0xFFFFFF00;
            c.channel.a = (int)(lbl_806DA1EC * t);
            self->texts[0]->tm()->color = c.rgba;
            self->texts[1]->tm()->color = c.rgba;
            self->texts[2]->tm()->color = c.rgba;
        }
        if (!fn_8019FE78(self->labelA) || self->timer >= 20) {
            self->state = 0;
            self->timer = 0;
            fn_801A0500(self->labelA);
            if (self->queued == 1) {
                fn_801D92D0(self, &self->field24);
                self->layout = self->nextLayout;
                self->nextLayout = -1;
                self->queued = 0;
                self->field24 = 0;
                self->field28 = 0;
                self->strings[0] = lbl_806DA1AC;
                self->strings[1] = lbl_806DA1AC;
                self->strings[2] = lbl_806DA1AC;
                self->field38 = 0;
                self->field3C = -1;
            }
        }
        break;
    }
    if (self->labelA) Sprite_AdvanceAnim(self->labelA, lbl_806DA1F4);
    if (self->labelB) Sprite_AdvanceAnim(self->labelB, lbl_806DA1F4);
    self->timer++;
}
