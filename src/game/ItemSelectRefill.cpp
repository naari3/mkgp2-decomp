#include "game/ItemSelectRefillPrivate.h"
static inline void CompleteChoice(RefillChoice *choice, int slot, const RefillLayout *layout, const int *resources, void *playerData) {

        if (choice->selected == 1) fn_8023AA0C(choice, 1);
        while (true) {
            if (choice->done == 1) break;
            fn_8023AA0C(choice, 1);
        }
        choice->selected = 1;
        choice->timer = 0;
        SpriteAnimParamBlock_Reload(choice->groups[1], slot + 0x4e);
        int resource = (short) Item_GetDescriptorField0(PlayerData_ResolveUnlockedIdByIndex(playerData,
            RefillItem(layout, choice->column, choice->row)), 0);
        SpriteAnimParamBlock_SetAnimParamCached(choice->groups[1], resources[slot], resource);
        SpriteAnimParamBlock_SetAnimParamCached(choice->groups[1], 0x13b9, resource);
        choice->slots[slot][0] = choice->column;
        choice->slots[slot][1] = choice->row;
        choice->count = slot + 1;
        choice->phase = 0;
        choice->done = 0;
}
static inline void SetRefillPosition(RefillSprite *sprite, float x, float y) {
    sprite->x = x;
    sprite->y = y;
}
#pragma push
#pragma opt_propagation off
extern "C" void fn_802386E0(ItemSelectState *self) {
    void *playerData = g_playerData;
    const RefillLayout *layout = &lbl_803DC0C0;
    const int *resources = layout->resources;
    const float *ys = layout->y;
    const float *xs = layout->x;
    while (self->field14c < 3) {
        int slot = self->field14c;
        CompleteChoice((RefillChoice *)self->iconArray, slot, layout, resources, g_playerData);
        RefillChoice *choice;
        choice = (RefillChoice *)self->iconArray;
        int column = choice->column;
        int row = choice->row;
        int *slots = (int *)self;
        slots[self->field14c * 3 + 0x57] = column;
        slots[self->field14c * 3 + 0x58] = row;
        slots[self->field14c * 3 + 0x59] = RefillItem(layout, column, row);
        int item = Item_GetDescriptorField0(PlayerData_ResolveUnlockedIdByIndex(playerData,
            slots[self->field14c * 3 + 0x59]), 0);
        SpriteAnimParamBlock_SetAnimParamCached(self->groups[self->field14c + 3], 0x13b9, item);
        SetRefillPosition(((RefillGroup *)self->groups[self->field14c + 3])->sprite,
            xs[column], ys[row]);
        SpriteHandle_SetActiveFlag(self->itemSprites[row * 11 + column], 0);
        int oldResource = 0x1424;
        if (self->field14c == 1) oldResource = 0x1423;
        if (self->field14c == 2) oldResource = 0x1425;
        SpriteAnimParamBlock_SetAnimParamCached(self->groups[6], oldResource, item);
        ++self->field14c;
    }
}
#pragma pop

