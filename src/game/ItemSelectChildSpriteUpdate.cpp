#include "game/ItemSelectChildSprite.h"
#include "game/KartChoiceOwnerPrivate.h"
extern "C" {
extern unsigned char g_raceEnded;
int fn_8020A788(FlowFader *);
void SoundMgr_PlaySE(int);
void fn_8023DCEC(ItemSelectChildSprite *, int);
}
static inline unsigned char HasOverlayFlag(ChoiceStatus *status) {
    if ((status->bits & 0x40000000ULL) == 0) return 0;
    return 1;
}
extern "C" void fn_8023E324(ItemSelectChildSprite *self, int active) {
    switch (self->state) {
    case -1:
        if (g_countdownPhase < 4) {
            self->state = 0;
            SpriteHandle_SetActiveFlag(self->handle, 1);
            SpriteHandle_RecomputeCull(self->handle);
        }
        break;
    case 0:
        self->y = fn_8020A6CC(self->slide.p);
        self->slide.p->Step();
        if (self->slide.p->Done()) {
            self->state = 1;
            self->y = 0.0f;
        }
        break;
    case 1:
        if (g_countdownPhase <= 2) {
            self->state = 2;
            fn_8020A734(self->slide.p, 4, 1.0f, 1.2f);
        }
        break;
    case 2:
        self->scale = fn_8020A6CC(self->slide.p);
        self->slide.p->Step();
        if (self->slide.p->Done()) {
            self->state = 3;
            fn_8020A734(self->slide.p, 4, 1.2f, 1.0f);
            self->scale = 1.2f;
        }
        break;
    case 3:
        self->scale = fn_8020A6CC(self->slide.p);
        self->slide.p->Step();
        if (self->slide.p->Done()) {
            self->state = 4;
            self->scale = 1.0f;
        }
        break;
    case 4:
        if (g_raceEnded) {
            self->state = 5;
            fn_8020A734(self->slide.p, 7, 0.0f, 220.0f);
        }
        break;
    case 5:
        self->y = fn_8020A6CC(self->slide.p);
        self->slide.p->Step();
        if (self->slide.p->Done()) {
            self->state = 6;
            self->y = 220.0f;
        }
        break;
    case 6: return;
    default: return;
    }
    if (self->phase != 0) {
        int value = fn_8020A788(self->timer.p);
        if (value <= 5) self->color = 0x7f7f7fff;
        else {
            if (value == 6 && self->mode) SoundMgr_PlaySE(0x4e);
            self->color = -1;
        }
        self->timer.p->Step();
        if (self->timer.p->Done()) {
            ++self->phase;
            if (self->phase > 3) {
                self->phase = 0;
                fn_8020A7CC(self->timer.p, 0, 0, 1);
            } else self->timer.p->b = 0;
        }
    }
    if (self->countdown >= 10 && self->countdown <= 20) {
        self->fade->Step();
        if (self->countdown == 14) fn_8020A734(self->fade, 5, 0.8f, 0.4f);
        if (++self->countdown >= 20) self->countdown = 1;
    }
    if (self->countdown >= 30 && self->countdown <= 40) {
        self->fade->Step();
        if (++self->countdown >= 40) self->countdown = 0;
    }
    ItemSelectChildOverlay *overlay;
    unsigned char enabled = 0;
    void *car = GetPlayerCarObject();
    if (car) {
        ChoiceStatus *status = CarObject_GetRenderObj(car)->status;
        if (status && HasOverlayFlag(status) == 1) enabled = 1;
    }
    overlay = self->overlay;
    if (!overlay->active && enabled) {
        overlay->active = 1;
        fn_8020A734(overlay->fade.p, 10, 2.0f, 1.0f);
        fn_8020A7CC(overlay->alpha.p, 0, 255, 10);
    } else if (overlay->active && !enabled) {
        overlay->active = 0;
        fn_8020A734(overlay->fade.p, 10, 1.0f, 0.0f);
    }
    fn_8023DCEC(self, active);
}
