/*
 * Use the held item: statistics, throw animation and item timers,
 * 0x8003F77C..0x8003FFD0.
 */

typedef struct ItemData {
    unsigned char pad0[5];
    unsigned char kind; /* 0x5 */
    signed char throwable; /* 0x6 */
    signed char throwType; /* 0x7 */
    unsigned char effect; /* 0x8 */
} ItemData;

typedef struct UseStats {
    unsigned char pad00[4];
    int count04;
    int count08;
    int count0C;
    int count10;
    unsigned char used; /* 0x14 */
    unsigned char pad15[3];
    int itemId; /* 0x18 */
} UseStats;

typedef struct UseKart {
    unsigned char pad000[0x178];
    int field178;
    unsigned char pad17C[0x1F0 - 0x17C];
    int currentState; /* 0x1F0 */
    unsigned char pad1F4[0x205 - 0x1F4];
    unsigned char flag205;
    unsigned char pad206[0x248 - 0x206];
    void *field248;
    unsigned char pad24C[0x290 - 0x24C];
    int field290;
    unsigned char pad294[0x2A4 - 0x294];
    int hitDir; /* 0x2A4 */
    unsigned char pad2A8[0x2B0 - 0x2A8];
    unsigned char field2B0;
    unsigned char field2B1;
    unsigned char pad2B2[0x2C0 - 0x2B2];
    int currentItemId; /* 0x2C0 */
    signed char field2C4;
    unsigned char pad2C5[3];
    int currentISESlot; /* 0x2C8 */
    unsigned char pad2CC[0x2DC - 0x2CC];
    void *iseSlots[10]; /* 0x2DC */
    unsigned char pad304[0x310 - 0x304];
    float field310;
    unsigned char field314;
    unsigned char pad315[0x344 - 0x315];
    UseStats *field344;
    unsigned char field348;
    unsigned char pad349[0x36C - 0x349];
    float field36C;
    int field370;
} UseKart;

extern const float lbl_806D2540;
extern const float lbl_806D2570;
extern const float lbl_806D25AC;
extern const float lbl_806D25B8;
extern const float lbl_806D25BC;
extern const float lbl_806D25C0;
extern const float lbl_806D25C4;
extern const float lbl_806D25C8;
extern const float lbl_806D25CC;
extern float lbl_806CF08C;
extern float lbl_806CF090;
extern float lbl_806CF094;
extern float lbl_806CF098;
extern float lbl_806CF09C;
extern float lbl_806CF0A0;
extern float lbl_806CF0A4;
extern float lbl_806CF0A8;
extern float lbl_806CF0AC;
extern float lbl_806CF0B0;
extern float lbl_806CF0B4;
extern float lbl_806CF0B8;
extern float lbl_806CF0BC;
extern float lbl_806CF0C0;
extern float lbl_806CF0C4;
extern float lbl_806CF0C8;

ItemData *GetItemDataEntry(int id);
int ISESlot_StopEffect(void *self, int idx, unsigned char value);
void fn_801B4548(void *p, int item);
void SetAnimState(UseKart *self, int anim_id, ItemData *data, int trigger_flag,
                  float f1, float f2, float f3, float f4);

static inline ItemData *GetItemData(int id) {
    if (id >= 0x115) {
        return 0;
    }
    return GetItemDataEntry(id);
}

static inline int ItemKind(ItemData *data) {
    return data->kind;
}

#pragma exceptions on

int RenderObj_UseItem(UseKart *kart, unsigned char force, unsigned char throwBack) {
    ItemData *data;
    UseStats *stats;

    if (!force) {
        if (kart->currentState == 0x18) {
            return 0;
        }
        if (kart->currentState == 0x19) {
            return 0;
        }
        if (kart->currentState == 0x1A) {
            return 0;
        }
        if (kart->currentState == 0x1B) {
            return 0;
        }
        if (kart->hitDir == 0) {
            return 0;
        }
        if (kart->currentISESlot == -1) {
            return 0;
        }
    }

    data = GetItemData(kart->currentItemId);
    stats = kart->field344;
    stats->used = 1;
    switch ((signed char)GetItemData(stats->itemId)->kind) {
    case 1:
        stats->count08++;
        break;
    case 2:
    case 3:
    case 4:
    case 10:
    case 11:
        stats->count04++;
        break;
    case 5:
    case 6:
    case 8:
        stats->count0C++;
        break;
    case 7:
    case 9:
        stats->count10++;
        break;
    }

    if (throwBack == 1 && data->throwable == 0) {
        throwBack = 0;
    }
    if (throwBack == 1) {
        kart->field2C4 = -1;
    } else if (kart->currentItemId == 0x6C) {
        kart->field2C4 = 6;
    } else if (kart->currentItemId == 0x6D) {
        kart->field2C4 = 6;
    } else if (kart->currentItemId == 0x6E) {
        kart->field2C4 = 6;
    } else {
        kart->field2C4 = data->effect;
    }

    if (kart->currentItemId == 0xB) {
        SetAnimState(kart, 0x2D, data, 0, lbl_806D2570, lbl_806D25B8, lbl_806D25B8, lbl_806D25BC);
    } else if (kart->currentItemId == 0xD) {
        SetAnimState(kart, 0x2E, data, 0, lbl_806D2570, lbl_806D25B8, lbl_806D25B8, lbl_806D25C0);
    } else if (kart->currentItemId == 0x51) {
        SetAnimState(kart, 0x2F, data, 0, lbl_806D2570, lbl_806D25B8, lbl_806D25B8, lbl_806D25C0);
    } else if (kart->currentItemId == 0x15) {
        SetAnimState(kart, 0x2D, data, 0, lbl_806D2570, lbl_806D25B8, lbl_806D25B8, lbl_806D25C0);
    } else if (kart->currentItemId == 0x14) {
        SetAnimState(kart, 0x2D, data, 0, lbl_806D2570, lbl_806D25B8, lbl_806D25B8, lbl_806D25C0);
    } else if (kart->currentItemId == 0x6F) {
        SetAnimState(kart, 0x2E, data, 0, lbl_806D2570, lbl_806D25B8, lbl_806D25B8, lbl_806D25C4);
    } else if (kart->currentItemId == 0x12) {
        SetAnimState(kart, 0x2F, data, 0, lbl_806D2570, lbl_806D25B8, lbl_806D25B8, lbl_806D25AC);
    } else if (kart->currentItemId == 0x13) {
        SetAnimState(kart, 0x2F, data, 0, lbl_806D2570, lbl_806D25B8, lbl_806D25B8, lbl_806D25C0);
    } else if (kart->currentItemId == 0x2A) {
        SetAnimState(kart, 0x30, data, 0, lbl_806D2570, lbl_806D25B8, lbl_806D25B8, lbl_806D25C8);
    } else if (kart->currentItemId == 0xF) {
        SetAnimState(kart, 0x2D, data, 0, lbl_806D2570, lbl_806D25B8, lbl_806D25B8, lbl_806D25C0);
    } else if (kart->currentItemId == 0x7A) {
        SetAnimState(kart, 0x2D, data, 0, lbl_806D2570, lbl_806D25B8, lbl_806D25B8, lbl_806D25BC);
    } else if (throwBack == 1) {
        SetAnimState(kart, 0x1C, data, 0, lbl_806CF08C, lbl_806CF090, lbl_806CF094, lbl_806CF098);
    } else if (kart->currentItemId == 0x37) {
        SetAnimState(kart, 0x2D, data, 0, lbl_806D2570, lbl_806D25B8, lbl_806D25B8, lbl_806D25C0);
    } else if ((signed char)data->kind == 5) {
        SetAnimState(kart, 0x17, data, 0, lbl_806CF08C, lbl_806CF090, lbl_806CF094, lbl_806CF098);
    } else if ((signed char)data->kind == 6) {
        SetAnimState(kart, 0x1C, data, 0, lbl_806CF08C, lbl_806CF090, lbl_806CF094, lbl_806CF098);
    } else if ((signed char)data->kind == 7) {
        SetAnimState(kart, 0x1C, data, 0, lbl_806CF08C, lbl_806CF090, lbl_806CF094, lbl_806CF098);
    } else if ((signed char)data->kind == 0xB) {
        SetAnimState(kart, 0x1D, data, 0, lbl_806CF09C, lbl_806CF0A0, lbl_806CF0A4, lbl_806CF0A8);
    } else if ((signed char)data->kind == 1) {
        SetAnimState(kart, 0x28, data, 0, lbl_806CF0AC, lbl_806CF0B0, lbl_806CF0B4, lbl_806CF0B8);
    } else if ((signed char)data->kind == 3) {
        SetAnimState(kart, 0x26, data, 0, lbl_806CF08C, lbl_806CF090, lbl_806CF094, lbl_806CF098);
    } else if ((signed char)data->kind == 9) {
        SetAnimState(kart, 0x27, data, 0, lbl_806CF0BC, lbl_806CF0C0, lbl_806CF0C4, lbl_806CF0C8);
    } else {
        SetAnimState(kart, 0x17, data, 0, lbl_806CF08C, lbl_806CF090, lbl_806CF094, lbl_806CF098);
    }

    if (kart->currentItemId == 0x2C) {
        if (kart->field314 == 1) {
            kart->field314 = 0;
            kart->field310 = lbl_806D25CC;
        }
        kart->field290 = 0x2716;
    } else {
        kart->hitDir = 0;
    }

    if (kart->currentItemId == 0x1) {
        kart->field290 = 20;
    } else if (kart->currentItemId == 0x2) {
        kart->field290 = 20;
    } else if (kart->currentItemId == 0x3) {
        kart->field290 = 20;
    } else if (kart->currentItemId == 0x4) {
        kart->field290 = 20;
    } else if (kart->currentItemId == 0x5) {
        kart->field290 = 20;
    } else if (kart->currentItemId == 0x6) {
        kart->field290 = 20;
    } else if (kart->currentItemId == 0x7) {
        kart->field290 = 20;
    } else if (kart->currentItemId == 0x9) {
        kart->field290 = 20;
    } else if (kart->currentItemId == 0xB) {
        kart->field290 = 20;
    } else if (kart->currentItemId == 0x7A) {
        kart->field290 = 20;
    } else if (kart->currentItemId == 0x8) {
        kart->field290 = 20;
    } else if (kart->currentItemId == 0xA) {
        kart->field290 = 20;
    } else if (kart->currentItemId == 0x2A) {
        kart->field290 = 2;
    } else if (kart->currentItemId == 0x12) {
        kart->field290 = 3;
    } else if (kart->currentItemId == 0x8F) {
        kart->field290 = 10;
    } else if (kart->currentItemId == 0x89) {
        kart->field290 = 10;
    }

    kart->field36C = lbl_806D2540;
    if (kart->currentItemId == 0x6F) {
        kart->field370 = 0;
    } else {
        kart->field370 = -1;
    }
    if (kart->currentItemId == 8) {
        ISESlot_StopEffect(kart->iseSlots[kart->currentISESlot], 1, 1);
    }
    if (ItemKind(data) == 9) {
        kart->field178 = 0x2C;
    }
    if (ItemKind(data) == 5) {
        kart->field348 = 1;
    }
    if (throwBack == 1) {
        kart->flag205 = 1;
    } else {
        kart->flag205 = 0;
    }
    if (kart->currentItemId == 0x54) {
        kart->field2B1 = 1;
    } else if (kart->currentItemId == 0x42) {
        kart->field2B1 = 1;
    } else if (kart->currentItemId == 0x1A) {
        kart->field2B1 = 1;
    } else if (kart->currentItemId == 0x23) {
        kart->field2B1 = 1;
    } else {
        kart->field2B1 = 0;
    }
    kart->field2B0 = 1;
    fn_801B4548(kart->field248, kart->currentItemId);
    return 1;
}

#pragma exceptions reset
