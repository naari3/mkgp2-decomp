/*
 * 0x801CDDC4..0x801CDF10: GP "please" panel draw (sprites, texts, and a
 * full screen fade quad driven by the frame counter).
 */

#include "game/FlowScene.h"

struct Sprite;

struct OptSprite {
    Sprite *sprite;
    unsigned char visible;
};

struct GpPleasePanel {
    void *vt;
    int timer;
    int pad08;
    Sprite *bg;
    void *title;
    void *texts[3];
    char pad20[0x30 - 0x20];
    unsigned char fading;
    void *anim;
    OptSprite *badge;
};

extern "C" {
void fn_801A0004(Sprite *s);
void fn_8023CD54(void *anim);
void *fn_801F8E58(void);
void fn_801F8A34(void *mgr, void *text, int layer);
void fn_8011FAFC(ResCtrl *ctrl, int layer);
void fn_801CDDC4(GpPleasePanel *self);
}

void fn_801CDDC4(GpPleasePanel *self)
{
    void *mgr;
    int i;

    fn_801A0004(self->bg);
    fn_8023CD54(self->anim);
    if (self->badge->visible) {
        fn_801A0004(self->badge->sprite);
    }
    mgr = fn_801F8E58();
    fn_801F8A34(mgr, self->title, 5);
    for (i = 0; i < 3; i++) {
        fn_801F8A34(mgr, self->texts[i], 5);
    }
    if (self->fading == 1) {
        ResCtrl ctrl;
        ctrl.mode = 2;
        ctrl.SetSize(640.0f, 480.0f);
        ctrl.Show(320.0f, 240.0f, 1.0f);
        ctrl.SetColor((unsigned char)(255.0f * (self->timer / 30.0f)));
        fn_8011FAFC(&ctrl, 7);
    }
}
