#include "game/FlowScene.h"
extern "C" void fn_8011FAFC(ResCtrl *, int);
#include "game/GaugePulse_private.h"
struct PulseOwner {
    void *vt;
    int field04, layer;
    unsigned char visible, pad[0x23];
    GaugePulse *pulse;
};
extern "C" const float lbl_806DBEBC;
extern "C" void fn_80244128(PulseOwner *self, float x, float y, float scale) {
    unsigned char visible = self->visible;
    if (scale <= 1.0f && scale >= lbl_806DBEBC) {
        if (!self->pulse) self->pulse = new GaugePulse(self->field04,self->layer);
    } else {
        if (self->pulse) { delete (VObject *)self->pulse; self->pulse = 0; }
    }
    if (self->pulse) {
        self->pulse->SetPosition(x,y);
        self->pulse->scale=scale;
        self->pulse->Draw(visible);
    }
}
