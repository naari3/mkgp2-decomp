#include "game/HudFlow20Private.h"
extern "C" {
extern int g_countdownPhase;
extern const float lbl_806DBF18, lbl_806DBF1C, lbl_806DBF20, lbl_806DBF24;
#include "game/types/HudPosition.h"
extern const HudPosition HudFlow20Update_rodata_803EF74C[];
void SpriteHandle_SetActiveFlag(void *, int);
void SpriteHandle_RecomputeCull(void *);
void fn_8011F744(void *,float,float);
void fn_8011F804(void *,float,float);
}
extern "C" void fn_80245E6C(HudFlow20 *self) {
    switch (self->state) {
    case -1:
        if (g_countdownPhase <= 3) {
            self->state = 0;
            SpriteHandle_SetActiveFlag(self->sprite, 1);
        }
        return;
    case 0:
        self->x.p->Step();
        if (self->x.p->Done()) {
            self->state = 1;
            self->x.p->Set(lbl_806DBF18,lbl_806DBF18,1);
        }
        break;
    case 1:
        if (g_countdownPhase <= 2) {
            self->y.p->Set(lbl_806DBF1C,lbl_806DBF20,4);
            self->state = 2;
        }
        break;
    case 2:
        if (self->y.p->Done() && self->y.p->Value() == lbl_806DBF1C)
            self->state = 3;
        break;
    case 3: break;
    case 4:
        self->x.p->Step();
        if (self->x.p->Done()) {
            self->state = 5;
            SpriteHandle_SetActiveFlag(self->sprite,0);
            SpriteHandle_RecomputeCull(self->sprite);
            return;
        }
        break;
    case 5: return;
    default: return;
    }
    if (self->next > 0 && --self->next <= 0) {
        self->next = 0;
        self->state = 4;
        self->x.p->Set(lbl_806DBF18,lbl_806DBF24,7);
    }
    float offset = HudFlow20Update_rodata_803EF74C[self->index].x - self->x.p->Value();
    FlowFaderF *y = self->y.p;
    fn_8011F744(self->sprite,y->Value(),y->Value());
    fn_8011F804(self->sprite,offset,HudFlow20Update_rodata_803EF74C[self->index].y);
    SpriteHandle_SetActiveFlag(self->sprite,1);
    SpriteHandle_RecomputeCull(self->sprite);
    self->y.p->Step();
    if (self->y.p->Done()) {
        float value = self->y.p->Value();
        if (lbl_806DBF20 == value)
            self->y.p->Set(lbl_806DBF20,lbl_806DBF1C,4);
        else if (lbl_806DBF1C == value)
            self->y.p->Set(lbl_806DBF1C,lbl_806DBF1C,1);
    }
}
