/*
 * Equip an item on the kart, 0x8003FFD0..0x800404C4.
 */

typedef struct ItemData {
    unsigned char pad0[5];
    unsigned char kind; /* 0x5 */
    unsigned char pad6;
    signed char throwType; /* 0x7 */
    unsigned char effect; /* 0x8 */
} ItemData;

typedef struct EquipFlag {
    unsigned char pad0[4];
    unsigned char active; /* 0x4 */
} EquipFlag;

typedef struct EquipState {
    unsigned char pad00[0x15];
    unsigned char pending; /* 0x15 */
    unsigned char pad16[2];
    int itemId; /* 0x18 */
} EquipState;

typedef struct EquipKart {
    unsigned char pad000[0x174];
    unsigned char field174;
    unsigned char pad175[0x1F0 - 0x175];
    int currentState; /* 0x1F0 */
    int field1F4;
    int characterId; /* 0x1F8 */
    unsigned char pad1FC[0x205 - 0x1FC];
    unsigned char flag205;
    unsigned char pad206[0x218 - 0x206];
    int field218;
    unsigned char pad21C[0x29C - 0x21C];
    void *field29C;
    unsigned char pad2A0[4];
    int hitDir; /* 0x2A4 */
    unsigned char field2A8;
    unsigned char pad2A9[0x2B0 - 0x2A9];
    unsigned char field2B0;
    unsigned char field2B1;
    unsigned char pad2B2;
    unsigned char iseActive; /* 0x2B3 */
    int field2B4;
    unsigned char pad2B8[4];
    float field2BC;
    int currentItemId; /* 0x2C0 */
    unsigned char pad2C4;
    unsigned char field2C5;
    unsigned char pad2C6[2];
    int currentISESlot; /* 0x2C8 */
    unsigned char pad2CC[0x2DC - 0x2CC];
    void *iseSlots[10]; /* 0x2DC */
    unsigned char pad304[0x314 - 0x304];
    unsigned char field314;
    unsigned char pad315[0x32C - 0x315];
    void *field32C;
    unsigned char pad330[0x344 - 0x330];
    EquipState *field344;
    unsigned char field348;
    unsigned char pad349[0x35C - 0x349];
    EquipFlag *field35C;
    EquipFlag *field360;
    unsigned char pad364[0x370 - 0x364];
    int field370;
} EquipKart;

extern const float lbl_806D256C;
extern const float lbl_806D2570;
extern const float lbl_806D25B8;
extern float lbl_806CF07C;
extern float lbl_806CF080;
extern float lbl_806CF084;
extern float lbl_806CF088;

ItemData *GetItemDataEntry(int id);
void ISESlot_Deactivate(void *slot);
unsigned char ISESlot_IsActive(void *slot);
void ISESlot_Init(void *slot, EquipKart *kart, int a, int b, int item);
void ItemEffectState_Init(void *state, int id);
void JObj_SetExpressionByIndex(EquipKart *kart, int index);
void fn_80173B68(void *p, int v);
void fn_80173BE8(void *p);
void SetAnimState(EquipKart *self, int anim_id, int unk_zero, int trigger_flag,
                  float f1, float f2, float f3, float f4);

static inline ItemData *GetItemData(int id) {
    if (id >= 0x115) {
        return 0;
    }
    return GetItemDataEntry(id);
}

static inline int GetItemKind(int id) {
    return GetItemData(id)->kind;
}

#pragma exceptions on

int KartMovement_EquipItem(EquipKart *kart, int item) {
    EquipState *state;
    int slot;
    unsigned char effect;

    if (kart->currentState != 0) {
        return 0;
    }
    if (kart->currentItemId == item) {
        return 0;
    }
    if (kart->field2C5 == 1) {
        return 0;
    }
    state = kart->field344;
    state->pending = 1;
    state->itemId = item;

    slot = kart->currentISESlot;
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

    for (slot = 0; slot < 10; slot++) {
        if (!ISESlot_IsActive(kart->iseSlots[slot])) {
            break;
        }
    }
    if (slot >= 10) {
        SetAnimState(kart, -1, 0, 1, lbl_806D2570, lbl_806D2570, lbl_806D25B8, lbl_806D256C);
        kart->hitDir = 0;
        return 0;
    }

    effect = GetItemData(item)->effect;
    if (item == 0x6C) {
        effect = 6;
    } else if (item == 0x6D) {
        effect = 6;
    } else if (item == 0x6E) {
        effect = 6;
    }

    kart->field314 = 1;
    kart->field2B0 = 0;
    kart->iseActive = 1;
    kart->field2B1 = 0;
    kart->field2B4 = 0;
    kart->currentISESlot = slot;
    kart->currentItemId = item;
    if (kart->field32C != 0) {
        ItemEffectState_Init(kart->field32C, (signed char)effect);
    }
    kart->field2BC = lbl_806D256C;
    kart->field348 = 0;
    ISESlot_Init(kart->iseSlots[slot], kart, kart->field1F4, kart->field218, item);
    SetAnimState(kart, 1, 0, 1, lbl_806CF07C, lbl_806CF080, lbl_806CF084, lbl_806CF088);

    if (kart->characterId == 2 && kart->currentItemId == 0x51) {
        kart->hitDir = 3;
        kart->field2A8 = 0;
    } else if (kart->characterId == 2 && kart->currentItemId == 0x75) {
        kart->hitDir = 4;
        kart->field2A8 = 2;
    } else if (kart->characterId == 6 && kart->currentItemId == 0x34) {
        kart->hitDir = 3;
        kart->field2A8 = 1;
    } else if (kart->characterId == 7 && kart->currentItemId == 0x7A) {
        kart->hitDir = 3;
        kart->field2A8 = 0;
    } else if (GetItemData(kart->currentItemId)->throwType == 0) {
        kart->hitDir = 1;
        kart->field2A8 = 1;
    } else {
        kart->hitDir = 2;
        kart->field2A8 = 0;
    }

    if (GetItemKind(kart->currentItemId) == 9) {
        if (kart->currentItemId == 0x6C) {
            JObj_SetExpressionByIndex(kart, 0);
        } else if (kart->currentItemId == 0x6D) {
            JObj_SetExpressionByIndex(kart, 1);
        } else if (kart->currentItemId == 0x6E) {
            JObj_SetExpressionByIndex(kart, 2);
        } else if (kart->currentItemId == 0x6F) {
            JObj_SetExpressionByIndex(kart, 3);
        }
        kart->field174 = 1;
    }

    kart->field370 = -1;
    if (kart->field35C != 0) {
        if (GetItemKind(kart->currentItemId) == 6) {
            kart->field35C->active = 1;
        }
        if (GetItemKind(kart->currentItemId) == 7) {
            kart->field35C->active = 1;
        }
        if (kart->currentItemId == 0x6F) {
            kart->field35C->active = 1;
        }
    }
    if (kart->field360 != 0) {
        if ((GetItemKind(kart->currentItemId) == 5 || GetItemKind(kart->currentItemId) == 9) &&
            kart->currentItemId != 0x6F && (signed char)effect == -1) {
            kart->field360->active = 1;
        }
    }
    kart->field348 = 0;
    return 1;
}

#pragma exceptions reset
