/* ItemHandler_Shell @ 0x8003E8BC: shell hit handler; waits out the initial
 * spin, then runs the stage timer like KartItem_TickEffectStage_a. */

#include "game/types/ItemKartFlag.h"

#include "game/types/ItemKart.h"

void ISESlot_Deactivate(void *slot);
void ISESlot_StopEffect(void *slot, int a, int b);
void ItemEffectState_Init(void *state, int id);
void fn_80173B68(void *p, int v);
void fn_80173BE8(void *p);

static inline void ClearCurrentItem(ItemKart *kart)
{
    if (kart->iseActive == 1) {
        ISESlot_Deactivate(kart->iseSlots[kart->currentISESlot]);
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

#include "game/types/ItemPick.h"

extern const float lbl_806D2590;
extern const float lbl_806D2594;
extern const float lbl_806D2598;
extern const float lbl_806D257C;
ItemPick *ItemEffectMgr_GetPickedSlot(void *state);

int ItemHandler_Shell(ItemKart *kart)
{
    if (kart->stunTime < lbl_806D2590) {
        kart->stunTime = kart->stunTime + kart->dt;
        if (kart->stunTime >= lbl_806D2590) {
            kart->timer2A0 = 0.0f;
        }
        return 1;
    }
    if (kart->timer2A0 <= 0.0f) {
        float scale = 0.0f;

        if (kart->field294 < 0.0f) {
            if (kart->field32C != 0 && ItemEffectMgr_GetPickedSlot(kart->field32C) != 0) {
                int rank = ItemEffectMgr_GetPickedSlot(kart->field32C)->field8;

                if (rank == 1) {
                    rank = 2;
                } else if (rank == 2) {
                    rank = 1;
                }
                scale = rank;
            }
        } else {
            scale = kart->field294;
        }
        kart->stunTime = 20.0f * scale + 10.0f + kart->dt;
        ISESlot_StopEffect(kart->iseSlots[kart->currentISESlot], 0, 1);
    }
    kart->timer2A0 = kart->timer2A0 + kart->dt;
    if (kart->timer2A0 >= lbl_806D2594 && kart->field298 == 1) {
        kart->field298 = 0;
        if (kart->counter290 > 0 && --kart->counter290 == 0) {
            ClearCurrentItem(kart);
            kart->field1E4 = lbl_806D257C + kart->stunTime;
        }
    }
    if (kart->timer2A0 >= lbl_806D2598 && kart->counter290 != 0) {
        kart->field298 = 1;
        kart->timer2A0 = 0.0f;
    }
    return 1;
}
