/*
 * 0x8020AAD4..0x8020AE50: ItemDisplay roulette sprite state machine
 * (hide, start, draw, per-frame update).
 */

#include "game/ItemDisplay.h"

#include "game/types/Sprite.h"

extern "C" {
void Sprite_SetupAnim(Sprite *sprite, int anim, int loop, int arg);
void Sprite_SetAnimParam(Sprite *sprite, int id, short value);
void Sprite_AdvanceAnim(Sprite *sprite, float dt);
unsigned char fn_8019FE78(Sprite *sprite);
void fn_801A0004(Sprite *sprite);
int fn_801A0500(Sprite *sprite);
void fn_801A0550(Sprite *sprite);
extern const float lbl_806DABF8;
extern const float lbl_806DABFC;
extern const float lbl_806DAC00;
}

static inline void Sprite_SetPos(Sprite *sprite, float x, float y) {
    sprite->x = x;
    sprite->y = y;
}

extern "C" void fn_8020AAD4(ItemDisplay *self) {
    if (self->state == 3 || self->state == 0) {
        return;
    }
    self->state = 3;
    Sprite_SetupAnim(self->sprite, 0xC7, 1, 0);
    Sprite_SetAnimParam(self->sprite, 0x1AD4, self->currentItemId);
}
