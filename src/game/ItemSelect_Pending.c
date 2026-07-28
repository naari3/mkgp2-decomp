/*
 * asm_fn bridge for the three pending ItemSelect routines at 0x8006012C.
 *
 * Each target function has an independent 8-byte extab record.  The records
 * are emitted manually and renamed by postprocess_extab_user.py; see the
 * matching entry in tools/extab_user_renames.json.
 */

extern void BattleRoulette_TickAndGetCounter();
extern void KartItem_CancelAndQueueDefault();
extern void KartMovement_GetCurrentItemId();
extern void SoundMgr_PlaySE();
extern void fn_8023E19C();
extern void fn_8023E1E4();

extern unsigned int g_gameMode;
extern unsigned int g_isCommHost;

asm void ItemSelect_OnDropAllCancel(void);
asm void ItemSelect_GiveItemOrQueueDrop(void);
asm void ItemSelect_StartRouletteSpin(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") const unsigned char extab_ItemSelect_OnDropAllCancel[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
__declspec(section ".extab_user") static const unsigned char extab_ItemSelect_GiveItemOrQueueDrop[8] = {
    0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
__declspec(section ".extab_user") static const unsigned char extab_ItemSelect_StartRouletteSpin[8] = {
    0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemSelect_OnDropAllCancel = {
    (void *)&ItemSelect_OnDropAllCancel, 0x00000094, (void *)extab_ItemSelect_OnDropAllCancel
};
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemSelect_GiveItemOrQueueDrop = {
    (void *)&ItemSelect_GiveItemOrQueueDrop, 0x00000110, (void *)extab_ItemSelect_GiveItemOrQueueDrop
};
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemSelect_StartRouletteSpin = {
    (void *)&ItemSelect_StartRouletteSpin, 0x000001EC, (void *)extab_ItemSelect_StartRouletteSpin
};

asm void ItemSelect_OnDropAllCancel(void) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 0x8(r1)
    mr r30, r3
    lwz r0, 0x54(r3)
    cmpwi r0, -0x1
    bne ItemSelect_OnDropAllCancel_L_8006015C
    li r3, 0x0
    b ItemSelect_OnDropAllCancel_L_800601A8
ItemSelect_OnDropAllCancel_L_8006015C:
    li r3, -0x1
    li r0, 0x0
    stw r3, 0x54(r30)
    stw r3, 0x70(r30)
    stw r0, 0x6c(r30)
    stw r0, 0x64(r30)
    lwz r3, 0x78(r30)
    cmplwi r3, 0x0
    beq ItemSelect_OnDropAllCancel_L_8006018C
    li r4, -0x1
    li r5, 0x0
    bl fn_8023E1E4
ItemSelect_OnDropAllCancel_L_8006018C:
    mr r3, r31
    bl KartItem_CancelAndQueueDefault
    li r3, 0x1e
    li r0, 0x1
    stw r3, 0x80(r30)
    li r3, 0x1
    stb r0, 0x84(r30)
ItemSelect_OnDropAllCancel_L_800601A8:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

asm void ItemSelect_GiveItemOrQueueDrop(void) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r6
    stw r30, 0x18(r1)
    mr r30, r5
    stw r29, 0x14(r1)
    mr r29, r4
    stw r28, 0x10(r1)
    mr r28, r3
    mr r3, r29
    bl KartMovement_GetCurrentItemId
    cmpwi r3, -0x1
    beq ItemSelect_GiveItemOrQueueDrop_L_80060204
    li r0, 0x1
    b ItemSelect_GiveItemOrQueueDrop_L_8006021C
ItemSelect_GiveItemOrQueueDrop_L_80060204:
    lwz r0, 0x64(r28)
    cmpwi r0, 0x0
    beq ItemSelect_GiveItemOrQueueDrop_L_80060218
    li r0, 0x1
    b ItemSelect_GiveItemOrQueueDrop_L_8006021C
ItemSelect_GiveItemOrQueueDrop_L_80060218:
    li r0, 0x0
ItemSelect_GiveItemOrQueueDrop_L_8006021C:
    clrlwi r0, r0, 24
    cmplwi r0, 0x1
    bne ItemSelect_GiveItemOrQueueDrop_L_8006026C
    clrlwi r0, r31, 24
    cmplwi r0, 0x1
    bne ItemSelect_GiveItemOrQueueDrop_L_80060264
    lwz r0, 0x70(r28)
    cmpwi r0, -0x1
    bne ItemSelect_GiveItemOrQueueDrop_L_80060264
    mr r3, r29
    bl KartMovement_GetCurrentItemId
    cmpwi r3, 0x7a
    beq ItemSelect_GiveItemOrQueueDrop_L_80060260
    mr r3, r29
    bl KartMovement_GetCurrentItemId
    cmpwi r3, 0xef
    bne ItemSelect_GiveItemOrQueueDrop_L_80060264
ItemSelect_GiveItemOrQueueDrop_L_80060260:
    stw r30, 0x70(r28)
ItemSelect_GiveItemOrQueueDrop_L_80060264:
    li r3, 0x0
    b ItemSelect_GiveItemOrQueueDrop_L_800602B0
ItemSelect_GiveItemOrQueueDrop_L_8006026C:
    stw r30, 0x1c(r28)
    li r0, 0x1
    li r3, 0x3
    stw r0, 0x20(r28)
    stw r3, 0x54(r28)
    stw r3, 0x58(r28)
    stw r0, 0x64(r28)
    stb r0, 0x61(r28)
    stw r0, 0x6c(r28)
    lwz r0, 0x1c(r28)
    cmpwi r0, 0x88
    bge ItemSelect_GiveItemOrQueueDrop_L_800602AC
    cmpwi r0, 0x7b
    bge ItemSelect_GiveItemOrQueueDrop_L_800602A8
    b ItemSelect_GiveItemOrQueueDrop_L_800602AC
ItemSelect_GiveItemOrQueueDrop_L_800602A8:
    stw r3, 0x6c(r28)
ItemSelect_GiveItemOrQueueDrop_L_800602AC:
    li r3, 0x1
ItemSelect_GiveItemOrQueueDrop_L_800602B0:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

asm void ItemSelect_StartRouletteSpin(void) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    stw r30, 0x18(r1)
    mr r30, r6
    stw r29, 0x14(r1)
    mr r29, r4
    lwz r0, 0x70(r3)
    cmpwi r0, -0x1
    beq ItemSelect_StartRouletteSpin_L_80060308
    li r3, -0x1
    b ItemSelect_StartRouletteSpin_L_800604A0
ItemSelect_StartRouletteSpin_L_80060308:
    lwz r0, 0x6c(r31)
    cmpwi r0, 0x0
    beq ItemSelect_StartRouletteSpin_L_8006031C
    li r3, -0x1
    b ItemSelect_StartRouletteSpin_L_800604A0
ItemSelect_StartRouletteSpin_L_8006031C:
    mr r3, r29
    bl KartMovement_GetCurrentItemId
    cmpwi r3, -0x1
    beq ItemSelect_StartRouletteSpin_L_80060334
    li r0, 0x1
    b ItemSelect_StartRouletteSpin_L_8006034C
ItemSelect_StartRouletteSpin_L_80060334:
    lwz r0, 0x64(r31)
    cmpwi r0, 0x0
    beq ItemSelect_StartRouletteSpin_L_80060348
    li r0, 0x1
    b ItemSelect_StartRouletteSpin_L_8006034C
ItemSelect_StartRouletteSpin_L_80060348:
    li r0, 0x0
ItemSelect_StartRouletteSpin_L_8006034C:
    clrlwi r0, r0, 24
    cmplwi r0, 0x1
    bne ItemSelect_StartRouletteSpin_L_80060360
    li r3, -0x1
    b ItemSelect_StartRouletteSpin_L_800604A0
ItemSelect_StartRouletteSpin_L_80060360:
    lbz r0, 0x2b1(r29)
    cmplwi r0, 0x1
    bne ItemSelect_StartRouletteSpin_L_80060374
    li r3, -0x1
    b ItemSelect_StartRouletteSpin_L_800604A0
ItemSelect_StartRouletteSpin_L_80060374:
    lwz r0, g_gameMode(r13)
    cmpwi r0, 0x2
    bne ItemSelect_StartRouletteSpin_L_800603FC
    lbz r0, g_isCommHost(r13)
    cmplwi r0, 0x1
    bne ItemSelect_StartRouletteSpin_L_800603E0
    bl BattleRoulette_TickAndGetCounter
    lis r4, 0x5555
    addi r5, r4, 0x5556
    mulhw r4, r5, r3
    srwi r0, r4, 31
    add r0, r4, r0
    mulli r0, r0, 0x3
    subf r0, r0, r3
    stw r0, 0x54(r31)
    lwz r3, 0x54(r31)
    lwz r0, 0x58(r31)
    cmpw r3, r0
    bne ItemSelect_StartRouletteSpin_L_8006044C
    addi r4, r3, 0x1
    mulhw r3, r5, r4
    srwi r0, r3, 31
    add r0, r3, r0
    mulli r0, r0, 0x3
    subf r0, r0, r4
    stw r0, 0x54(r31)
    b ItemSelect_StartRouletteSpin_L_8006044C
ItemSelect_StartRouletteSpin_L_800603E0:
    cmpwi r30, 0x0
    ble ItemSelect_StartRouletteSpin_L_800603F4
    subi r0, r30, 0x1
    stw r0, 0x54(r31)
    b ItemSelect_StartRouletteSpin_L_8006044C
ItemSelect_StartRouletteSpin_L_800603F4:
    li r3, -0x1
    b ItemSelect_StartRouletteSpin_L_800604A0
ItemSelect_StartRouletteSpin_L_800603FC:
    bl BattleRoulette_TickAndGetCounter
    lis r4, 0x5555
    addi r5, r4, 0x5556
    mulhw r4, r5, r3
    srwi r0, r4, 31
    add r0, r4, r0
    mulli r0, r0, 0x3
    subf r0, r0, r3
    stw r0, 0x54(r31)
    lwz r3, 0x54(r31)
    lwz r0, 0x58(r31)
    cmpw r3, r0
    bne ItemSelect_StartRouletteSpin_L_8006044C
    addi r4, r3, 0x1
    mulhw r3, r5, r4
    srwi r0, r3, 31
    add r0, r3, r0
    mulli r0, r0, 0x3
    subf r0, r0, r4
    stw r0, 0x54(r31)
ItemSelect_StartRouletteSpin_L_8006044C:
    lwz r4, 0x54(r31)
    li r3, -0x1
    li r0, 0x78
    stw r4, 0x58(r31)
    stw r3, 0x5c(r31)
    stw r0, 0x64(r31)
    lwz r3, 0x78(r31)
    cmplwi r3, 0x0
    beq ItemSelect_StartRouletteSpin_L_80060474
    bl fn_8023E19C
ItemSelect_StartRouletteSpin_L_80060474:
    lbz r0, 0x7c(r31)
    cmplwi r0, 0x0
    beq ItemSelect_StartRouletteSpin_L_80060488
    li r3, 0x4d
    bl SoundMgr_PlaySE
ItemSelect_StartRouletteSpin_L_80060488:
    li r3, -0x2
    li r0, 0x1
    stw r3, 0x6c(r31)
    stb r0, 0x61(r31)
    stb r0, 0x60(r31)
    lwz r3, 0x54(r31)
ItemSelect_StartRouletteSpin_L_800604A0:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
