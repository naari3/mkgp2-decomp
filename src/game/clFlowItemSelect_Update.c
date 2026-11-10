#pragma cplusplus on
#include "game/clFlowItemSelect_Update_private.h"

#pragma exceptions on
extern "C" void clFlowItemSelect_Update(ItemSelectFlow *self) {
    ItemSelectFlow *cursor;
    int i;
    RumbleUpdate();
    ++self->ticks;
    if (self->intro <= 15) {
        if (++self->intro >= 9) {
            SpriteHandle_SetActiveFlag(self->handle, 1);
            SpriteHandle_SetCornerAlpha(self->handle, (int)(lbl_806D9DBC * (((float)self->intro - lbl_806D9DD0) / lbl_806D9DD4)));
        } else {
            float alpha, y;
            UI_PlaySeDecide();
            y = lbl_806D9DDC * (float)(self->intro / 8) + lbl_806D9DD8;
            self->groups[0]->sprite->y = y;
            self->groups[1]->sprite->y = y;
            self->groups[2]->sprite->y = y;
            alpha = (float)self->intro * lbl_806D9DE0;
            self->groups[0]->sprite->alpha = alpha;
            self->groups[1]->sprite->alpha = alpha;
            self->groups[2]->sprite->alpha = alpha;
        }
        if (self->intro == 16) {
            SpriteAnimParamBlock_Reload(self->groups[3], 70);
            fn_8019FF6C(self->groups[3]->sprite, 1);
            if (self->mode == 0) {
                SpriteGroup_CreateOrInit(&self->groups[4], clFlowItemSelect_Update_data_806CFE18, 1, lbl_806D9DE4, lbl_806D9DE8);
                self->groups[4]->sprite->layer = 6;
            }
            SpriteHandle_SetCornerAlpha(self->handle, 255);
            self->brightness = lbl_806D9DEC;
            fn_801699D8(0, 1);
        }
    }
    for (i = 0, cursor = self; i < 3; ++i, cursor = (ItemSelectFlow *)((char *)cursor + 4)) {
        ItemSelectRoll *roll = cursor->rolls[0];
        int item, value;
        if (--roll->timer == 0 && roll->locked != 1) {
            do {
                item = roll->entries[Rand15() % roll->count].item;
                switch (item) {
                case -2: item = roll->fallback[1]; break;
                case -3: item = roll->fallback[2]; break;
                case -4: item = roll->fallback[0]; break;
                case -5: item = roll->fallback[3]; break;
                case -6: item = roll->fallback[4]; break;
                }
            } while (item == roll->item);
            roll->item = item;
            roll->timer = 6;
        }
        item = cursor->rolls[0]->item;
        SpriteAnimParamBlock_SetKey(cursor->groups[0], 0x13b9, Item_GetDescriptorField0(item, 0));
        value = Item_GetDescriptorFieldC(item);
        SpriteAnimParamBlock_SetKey(cursor->groups[0], 0x1e1d, value < 0 ? -1 : value + 0x1e1d);
        value = Item_GetDescriptorField8(item);
        SpriteAnimParamBlock_SetKey(cursor->groups[0], 0x17a4, value < 0 ? -1 : value + 0x17a3);
    }
    ItemSelectFlow *animCursor;
    for (i = 0, animCursor = self; i < 5; ++i, animCursor = (ItemSelectFlow *)((char *)animCursor + 4)) {
        if (animCursor->groups[0]) Sprite_AdvanceAnim(animCursor->groups[0]->sprite, lbl_806D9DF0);
    }
    SpriteHandle_RecomputeCull(self->handle);
    fn_8023CDA8(self->child);
    if (self->mode <= 1) {
        self->brightness -= lbl_806D9DF4;
        if (self->brightness < lbl_806D9DB0) self->brightness = lbl_806D9DF8;
    } else self->brightness = lbl_806D9DF8;
    SetScreenBrightness(self->brightness);
    fn_801B7EF8();
    ItemDisplay_Update(ItemDisplay_GetOrCreate());
    fn_801CB818(self);
}
#pragma exceptions reset
