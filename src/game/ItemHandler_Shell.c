/* ItemHandler_Shell @ 0x8003E8BC: shell hit handler; waits out the initial
 * spin, then runs the stage timer like KartItem_TickEffectStage_a. */

typedef struct ItemKartFlag {
    unsigned char pad0[4];
    unsigned char active; /* 0x4 */
} ItemKartFlag;

typedef struct ItemKart {
    unsigned char pad000[0x174];
    unsigned char field174;
    unsigned char pad175[0x1CC - 0x175];
    float dt; /* 0x1CC */
    unsigned char pad1D0[0x1E0 - 0x1D0];
    float stunTime; /* 0x1E0 */
    float field1E4;
    unsigned char pad1E8[0x205 - 0x1E8];
    unsigned char flag205;
    unsigned char pad206[0x290 - 0x206];
    int counter290;
    float field294;
    unsigned char field298;
    unsigned char pad299[0x29C - 0x299];
    void *field29C;
    float timer2A0;
    int hitDir; /* 0x2A4 */
    unsigned char pad2A8[0x2B0 - 0x2A8];
    unsigned char field2B0;
    unsigned char pad2B1[2];
    unsigned char iseActive; /* 0x2B3 */
    int field2B4;
    unsigned char pad2B8[0x2C0 - 0x2B8];
    int currentItemId; /* 0x2C0 */
    unsigned char pad2C4[4];
    int currentISESlot; /* 0x2C8 */
    unsigned char pad2CC[0x2DC - 0x2CC];
    void *iseSlots[20]; /* 0x2DC */
    void *field32C;
    unsigned char pad330[0x35C - 0x330];
    ItemKartFlag *field35C;
    ItemKartFlag *field360;
} ItemKart;

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

typedef struct ItemPick {
    ItemKart *kart;
    int field4;
    int field8;
} ItemPick;

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
