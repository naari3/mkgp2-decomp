/*
 * 0x8020AAD4..0x8020AE50: ItemDisplay roulette sprite state machine
 * (hide, start, draw, per-frame update).
 */

#include "game/ItemDisplay.h"

struct Sprite {
    int field00;
    int style;
    int field08;
    float x;
    float y;
    char pad14[0x30 - 0x14];
    Sprite(int anim, int loop, int arg);
};

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
    if (self->state != 3 && self->state != 0) {
        self->state = 3;
        Sprite_SetupAnim(self->sprite, 0xC7, 1, 0);
        Sprite_SetAnimParam(self->sprite, 0x1AD4, self->currentItemId);
    }
}

extern "C" void ItemDisplay_Start(ItemDisplay *self, int item) {
    if (self->state != 0) {
        self->pendingItemId = item;
        return;
    }
    self->state = 1;
    if (self->sprite == 0) {
        self->sprite = new Sprite(0xC8, 0, 0);
        Sprite_SetAnimParam(self->sprite, 0x1AD4, item);
        fn_801A0550(self->sprite);
    } else {
        Sprite_SetupAnim(self->sprite, 0xC8, 1, 0);
        Sprite_SetAnimParam(self->sprite, 0x1AD4, item);
    }
    self->currentItemId = item;
    self->pendingItemId = -1;
    Sprite_SetPos(self->sprite, lbl_806DABF8, lbl_806DABFC);
    self->sprite->style = self->styleId;
}

extern "C" void fn_8020AC34(ItemDisplay *self) {
    if (self->sprite != 0) {
        fn_801A0004(self->sprite);
    }
}

extern "C" void ItemDisplay_Update(ItemDisplay *self) {
    switch (self->state) {
    case 0:
        break;
    case 1:
        if (!fn_8019FE78(self->sprite)) {
            Sprite_SetupAnim(self->sprite, 0x1DD, 1, 0);
            Sprite_SetAnimParam(self->sprite, 0x1AD4, self->currentItemId);
            self->state = 2;
        }
        break;
    case 2:
        if (self->pendingItemId >= 0) {
            fn_8020AAD4(self);
        }
        break;
    case 3:
        if (!fn_8019FE78(self->sprite)) {
            self->state = 0;
            int item = self->pendingItemId;
            if (item >= 0) {
                ItemDisplay_Start(self, item);
            } else {
                fn_801A0500(self->sprite);
            }
        }
        break;
    }
    if (self->sprite != 0) {
        Sprite_AdvanceAnim(self->sprite, lbl_806DAC00);
    }
}
