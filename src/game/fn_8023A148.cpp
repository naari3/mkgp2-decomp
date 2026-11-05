#include "game/ItemSelectPresentationPrivate.h"
struct PresentationInput { unsigned char pad[0x14]; int direction, confirm; };
extern "C" {
extern PresentationInput *g_pInputState;
void fn_8023F1C8(void *); void fn_801FE390(); void fn_801FE348();
void Sprite_AdvanceAnim(RefillSprite *, float); void SpriteHandle_RecomputeCull(int);
}
static inline void SetTextAlpha(ItemSelectPresentation *self, int alpha) {
    unsigned int title = 0xe0202000 | (unsigned char)alpha;
    unsigned int color = __rlwimi(0xffffff00, alpha, 0, 24, 31);
    *(unsigned int *)(self->texts[0][0]->data + 0x20) = title;
    *(unsigned int *)(self->texts[0][1]->data + 0x20) = color;
    *(unsigned int *)(self->texts[0][2]->data + 0x20) = color;
    *(unsigned int *)(self->texts[0][3]->data + 0x20) = color;
    *(unsigned int *)(self->texts[1][0]->data + 0x20) = title;
    *(unsigned int *)(self->texts[1][1]->data + 0x20) = color;
    *(unsigned int *)(self->texts[1][2]->data + 0x20) = color;
    *(unsigned int *)(self->texts[1][3]->data + 0x20) = color;
    *(unsigned int *)(self->texts[2][0]->data + 0x20) = title;
    *(unsigned int *)(self->texts[2][1]->data + 0x20) = color;
    *(unsigned int *)(self->texts[2][2]->data + 0x20) = color;
    *(unsigned int *)(self->texts[2][3]->data + 0x20) = color;
}
static inline float ClampLow(float value, float limit) {
    return value < limit ? limit : value;
}
static inline float ClampHigh(float value, float limit) {
    return value > limit ? limit : value;
}
extern "C" void fn_8023A148(ItemSelectPresentation *self) {
    PresentationInput *input = g_pInputState == 0 ? (PresentationInput *)0 : g_pInputState;
    switch (self->phase) {
    case 0: break;
    case 1:
        if (self->timer == 6) {
            fn_8023F1C8(self->groups[0]);
            SpriteHandle_SetActiveFlag(self->handle, 1);
        }
        if (self->timer < 6) {
            float alpha = ClampLow((float)((self->timer - 2) / 3), lbl_806DB888);
            self->groups[1]->sprite->alpha = alpha;
            self->groups[2]->sprite->alpha = alpha;
        }
        if (self->timer >= 15) {
            self->groups[6]->sprite->alpha = lbl_806DB8CC;
            self->phase = 2;
        }
        break;
    case 2: {
        float alpha = self->groups[3]->sprite->alpha;
        int textAlpha = (int)(lbl_806DB894 * alpha);
        int direction = (g_pInputState == 0 ? (PresentationInput *)0 : g_pInputState)->direction;
        if (self->automatic) {
            alpha = lbl_806DB888;
            direction = 1;
            textAlpha = 0;
        }
        if (direction) {
            int previous = self->selected;
            self->selected += direction;
            if (self->selected < 0) self->selected = 0;
            if (self->selected > 1) self->selected = 1;
            if (previous != self->selected) fn_801FE390();
            int other = (~self->selected) & 1;
            SpriteAnimParamBlock_Reload(self->groups[self->selected + 1], 0x1a8);
            SpriteAnimParamBlock_Reload(self->groups[other + 1], 0x1a7);
            PresentationScale(self->groups[self->selected + 1]->sprite, lbl_806DB8CC);
            PresentationScale(self->groups[other + 1]->sprite, lbl_806DB964);
            PresentationParams(self);
            if (self->selected == 0) self->groups[6]->sprite->field1c = lbl_806DB888;
            else self->groups[6]->sprite->field1c = lbl_806DB968 * lbl_806D0738;
        }
        if (self->selected == 0) {
            alpha = ClampLow(alpha - lbl_806DB96C, lbl_806DB888);
        } else {
            alpha = ClampHigh(alpha + lbl_806DB96C, lbl_806DB8CC);
        }
        if (!self->automatic) {
            self->groups[3]->sprite->alpha = alpha;
            self->groups[4]->sprite->alpha = alpha;
            self->groups[5]->sprite->alpha = alpha;
            SetTextAlpha(self, textAlpha);
        }
        if (input->confirm == 1 || self->automatic == 1) {
            fn_801FE348();
            SpriteAnimParamBlock_Reload(self->groups[self->selected + 1], 0x59);
            if (self->selected == 1) PresentationParams(self);
            self->timer = 0;
            self->phase = 3;
        }
        break;
    }
    case 3:
        if (self->timer >= 7 && self->timer <= 15 && self->selected == 1) {
            unsigned char current = *(unsigned int *)(self->texts[0][0]->data + 0x20);
            int alpha = (int)(lbl_806DB894 * (lbl_806DB8CC - (self->timer - 7) * lbl_806DB918));
            if ((unsigned char)alpha > current) alpha = current;
            SetTextAlpha(self, alpha);
        }
        if (self->timer == 15) {
            SpriteAnimParamBlock_Reload(self->groups[0], 0x48);
            PresentationParams(self);
            SpriteHandle_SetActiveFlag(self->handle, 0);
        }
        if (self->timer == 22) {
            self->groups[0]->sprite->alpha = lbl_806DB888;
            self->groups[1]->sprite->alpha = lbl_806DB888;
            self->groups[2]->sprite->alpha = lbl_806DB888;
            self->groups[3]->sprite->alpha = lbl_806DB888;
            self->groups[4]->sprite->alpha = lbl_806DB888;
            self->groups[5]->sprite->alpha = lbl_806DB888;
            self->groups[6]->sprite->alpha = lbl_806DB888;
            SpriteHandle_SetActiveFlag(self->handle, 0);
            self->done = 1;
            self->phase = -1;
        }
        break;
    }
    self->timer++;
    for (int i = 0; i < 7; i++) {
        if (self->groups[i]) Sprite_AdvanceAnim(self->groups[i]->sprite, lbl_806DB8A8);
    }
    SpriteHandle_RecomputeCull(self->handle);
}
