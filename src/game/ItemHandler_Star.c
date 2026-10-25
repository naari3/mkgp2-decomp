/* ItemHandler_Star @ 0x8003E540: per-frame handler while the kart holds a
 * star; counts the star down and clears the held item when it runs out. */

typedef struct ItemKartFlag {
    unsigned char pad0[4];
    unsigned char active; /* 0x4 */
} ItemKartFlag;

typedef struct ItemKart {
    unsigned char pad000[0x174];
    unsigned char field174;
    unsigned char pad175[0x1E0 - 0x175];
    float stunTime; /* 0x1E0 */
    unsigned char pad1E4[0x205 - 0x1E4];
    unsigned char flag205;
    unsigned char pad206[0x290 - 0x206];
    int counter290;
    unsigned char pad294[0x29C - 0x294];
    void *field29C;
    unsigned char pad2A0[4];
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
    void *iseSlots[13]; /* 0x2DC */
    float starTime; /* 0x310 */
    unsigned char starLocked; /* 0x314 */
    unsigned char pad315[0x32C - 0x315];
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

extern const float lbl_806D2570;
unsigned char Input_IsItemButtonPressed(void *input);
void RenderObj_UseItem(ItemKart *kart, int a, int b);

int ItemHandler_Star(ItemKart *kart, void *input)
{
    if (kart->starLocked == 1) {
        return;
    }
    if (Input_IsItemButtonPressed(input)) {
        RenderObj_UseItem(kart, 0, 0);
    }
    if (kart->counter290 > 10000) {
        if (--kart->counter290 == 10000) {
            ISESlot_StopEffect(kart->iseSlots[kart->currentISESlot], 0, 1);
        }
    }
    if ((kart->starTime -= lbl_806D2570) < 0.0f) {
        ClearCurrentItem(kart);
        kart->hitDir = 0;
    }
    return 1;
}
