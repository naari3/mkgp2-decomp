/*
 * Cancel the held item unless it is locked, 0x800404C4..0x80040600.
 */

#include "game/types/CancelFlag.h"

#include "game/types/CancelKart.h"

extern const float lbl_806D256C;
extern const float lbl_806D2570;
extern const float lbl_806D25B8;

void ISESlot_Deactivate(void *slot);
void ItemEffectState_Init(void *state, int id);
void fn_80173B68(void *p, int v);
void fn_80173BE8(void *p);
void SetAnimState(CancelKart *self, int anim_id, int unk_zero, int trigger_flag,
                  float f1, float f2, float f3, float f4);

static inline void CancelCurrentItem(CancelKart *kart) {
    int slot = kart->currentISESlot;

    if (slot != -1) {
        if (kart->iseActive == 1) {
            ISESlot_Deactivate(kart->iseSlots[slot]);
        }
        kart->field2B0 = 0;
        kart->iseActive = 0;
        kart->field2B4 = 0;
        kart->currentISESlot = -1;
        kart->currentItemId = -1;
        kart->flag205 = 0;
        if (kart->field32C != 0) {
            ItemEffectState_Init(kart->field32C, -1);
        }
        kart->field174 = 0;
        fn_80173B68(kart->field29C, 0);
        fn_80173BE8(kart->field29C);
        if (kart->field35C != 0) {
            kart->field35C->active = 0;
        }
        if (kart->field360 != 0) {
            kart->field360->active = 0;
        }
        fn_80173BE8(kart->field29C);
    }
    SetAnimState(kart, -1, 0, 1, lbl_806D2570, lbl_806D2570, lbl_806D25B8, lbl_806D256C);
    kart->hitDir = 0;
}

#pragma exceptions on

int KartItem_CancelIfNotForced(CancelKart *kart) {
    int item;

    if (kart->currentISESlot == -1) {
        return -1;
    }
    if (kart->field178 > 0) {
        return -1;
    }
    item = kart->currentItemId;
    if (kart->hitDir != 0) {
        CancelCurrentItem(kart);
    }
    return item;
}

#pragma exceptions reset
