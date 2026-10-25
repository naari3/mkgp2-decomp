/*
 * Kart reset on timeout/goal and wall/spin hit animations,
 * 0x80040608..0x80040C24.
 */

typedef struct CharacterEntry {
    unsigned char pad00[0x20];
    unsigned char goalAnim; /* 0x20 */
    unsigned char pad21[7];
    unsigned char timeoutAnim; /* 0x28 */
} CharacterEntry;

typedef struct ResetFlag {
    unsigned char pad0[4];
    unsigned char active; /* 0x4 */
} ResetFlag;

typedef struct ResetKart {
    unsigned char pad000[0xC];
    void *character; /* 0x00C */
    unsigned char pad010[0x158 - 0x010];
    void *joint158;
    void *joint15C;
    void *joint160;
    unsigned char pad164[0x174 - 0x164];
    unsigned char field174;
    unsigned char pad175[0x1B8 - 0x175];
    int wallHitTimer; /* 0x1B8 */
    unsigned char pad1BC[0x1CC - 0x1BC];
    float field1CC;
    unsigned char pad1D0[0x1E0 - 0x1D0];
    float field1E0;
    unsigned char pad1E4[0x1F0 - 0x1E4];
    int currentState; /* 0x1F0 */
    unsigned char pad1F4[4];
    int characterId; /* 0x1F8 */
    unsigned char pad1FC[0x204 - 0x1FC];
    unsigned char flag204;
    unsigned char flag205;
    unsigned char pad206[0x29C - 0x206];
    void *field29C;
    unsigned char pad2A0[4];
    int hitDir; /* 0x2A4 */
    unsigned char field2A8;
    unsigned char pad2A9[0x2B0 - 0x2A9];
    unsigned char field2B0;
    unsigned char pad2B1[2];
    unsigned char iseActive; /* 0x2B3 */
    int field2B4;
    unsigned char pad2B8[0x2C0 - 0x2B8];
    int currentItemId; /* 0x2C0 */
    unsigned char pad2C4;
    unsigned char field2C5;
    unsigned char pad2C6[2];
    int currentISESlot; /* 0x2C8 */
    unsigned char pad2CC[0x2DC - 0x2CC];
    void *iseSlots[20]; /* 0x2DC */
    void *field32C;
    unsigned char pad330[0x35C - 0x330];
    ResetFlag *field35C;
    ResetFlag *field360;
} ResetKart;

extern const float lbl_806D2540;
extern const float lbl_806D2570;
extern const float lbl_806D2574;
extern float lbl_806CF04C;
extern float lbl_806CF050;
extern float lbl_806CF054;
extern float lbl_806CF058;
extern float lbl_806CF05C;
extern float lbl_806CF060;
extern float lbl_806CF064;
extern float lbl_806CF068;
extern float lbl_806CF06C;
extern float lbl_806CF070;
extern float lbl_806CF074;
extern float lbl_806CF078;

void ISESlot_Deactivate(void *slot);
void ItemEffectState_Init(void *state, int id);
void fn_80173B68(void *p, int v);
void fn_80173BE8(void *p);
CharacterEntry *GetCharacterDataEntry(int id);
void JObj_Hide(void *character, void *joint, unsigned int flags);
void JObj_Show(void *character, void *joint, unsigned int flags);
void SetAnimState(ResetKart *self, int anim_id, int unk_zero, int trigger_flag,
                  float f1, float f2, float f3, float f4);

#pragma exceptions on

void KartMovement_ResetOnTimeout(ResetKart *kart) {
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
    kart->currentState = 0x2B;
    kart->field1E0 = lbl_806D2540;
    kart->field1CC = lbl_806D2570;
    kart->field2C5 = 1;
    kart->field2A8 = GetCharacterDataEntry(kart->characterId)->timeoutAnim;
    if (kart->joint158 != 0) {
        JObj_Hide(kart->character, kart->joint158, 0x10);
    }
    if (kart->joint15C != 0) {
        JObj_Hide(kart->character, kart->joint15C, 0x10);
    }
    if (kart->joint160 != 0) {
        JObj_Show(kart->character, kart->joint160, 0x10);
    }
}

void KartMovement_ResetOnGoal(ResetKart *kart) {
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
    kart->currentState = 0x2A;
    kart->flag204 = 0;
    kart->field1E0 = lbl_806D2540;
    kart->field1CC = lbl_806D2570;
    kart->field2C5 = 1;
    kart->field2A8 = GetCharacterDataEntry(kart->characterId)->goalAnim;
    if (kart->joint158 != 0) {
        JObj_Show(kart->character, kart->joint158, 0x10);
    }
    if (kart->joint15C != 0) {
        JObj_Hide(kart->character, kart->joint15C, 0x10);
    }
    if (kart->joint160 != 0) {
        JObj_Hide(kart->character, kart->joint160, 0x10);
    }
}

int ItemHit_CommonKnockdown(ResetKart *kart) {
    if (kart->currentState != 0) {
        return 0;
    }
    if (kart->hitDir != 0) {
        return 0;
    }
    SetAnimState(kart, 0x25, 0, 1, lbl_806CF06C, lbl_806CF070, lbl_806CF074, lbl_806CF078);
    return 1;
}

int SetAnimWallHitA(ResetKart *kart) {
    if (kart->currentState != 0) {
        return 0;
    }
    if (kart->wallHitTimer != 0) {
        return 0;
    }
    if (kart->currentItemId == 0x51) {
        return 0;
    }
    if (kart->hitDir == 0) {
        SetAnimState(kart, 0x21, 0, 1, lbl_806CF05C, lbl_806CF060, lbl_806CF064, lbl_806D2574 + lbl_806CF068);
    } else if (kart->hitDir == 3) {
        SetAnimState(kart, 0x23, 0, 1, lbl_806CF05C, lbl_806CF060, lbl_806CF064, lbl_806CF068);
    } else if (kart->hitDir == 4) {
        SetAnimState(kart, 0x24, 0, 1, lbl_806CF05C, lbl_806CF060, lbl_806CF064, lbl_806CF068);
    } else {
        SetAnimState(kart, 0x22, 0, 1, lbl_806CF05C, lbl_806CF060, lbl_806CF064, lbl_806D2574 + lbl_806CF068);
    }
    kart->field1E0 = lbl_806D2574;
    kart->wallHitTimer = 0x3C;
    return 1;
}

int SetAnimWallHitB(ResetKart *kart) {
    if (kart->currentState != 0) {
        return 0;
    }
    if (kart->wallHitTimer != 0) {
        return 0;
    }
    if (kart->currentItemId == 0x51) {
        return 0;
    }
    if (kart->hitDir == 0) {
        SetAnimState(kart, 0x21, 0, 1, lbl_806CF05C, lbl_806CF060, lbl_806CF064, lbl_806CF068);
    } else if (kart->hitDir == 3) {
        SetAnimState(kart, 0x23, 0, 1, lbl_806CF05C, lbl_806CF060, lbl_806CF064, lbl_806CF068);
    } else if (kart->hitDir == 4) {
        SetAnimState(kart, 0x24, 0, 1, lbl_806CF05C, lbl_806CF060, lbl_806CF064, lbl_806CF068);
    } else {
        SetAnimState(kart, 0x22, 0, 1, lbl_806CF05C, lbl_806CF060, lbl_806CF064, lbl_806CF068);
    }
    kart->field1E0 = lbl_806D2540;
    kart->wallHitTimer = 0x3C;
    return 1;
}

int SetAnimSpin(ResetKart *kart) {
    if (kart->currentState != 0) {
        return 0;
    }
    if (kart->hitDir == 0) {
        SetAnimState(kart, 0x18, 0, 1, lbl_806CF04C, lbl_806CF050, lbl_806CF054, lbl_806CF058);
    } else if (kart->hitDir == 3) {
        SetAnimState(kart, 0x1A, 0, 1, lbl_806CF04C, lbl_806CF050, lbl_806CF054, lbl_806CF058);
    } else if (kart->hitDir == 4) {
        SetAnimState(kart, 0x1B, 0, 1, lbl_806CF04C, lbl_806CF050, lbl_806CF054, lbl_806CF058);
    } else {
        SetAnimState(kart, 0x19, 0, 1, lbl_806CF04C, lbl_806CF050, lbl_806CF054, lbl_806CF058);
    }
    return 1;
}

#pragma exceptions reset
