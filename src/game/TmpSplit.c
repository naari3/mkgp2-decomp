asm void EffectSteering_InitForSplit(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_EffectSteering_InitForSplit[8] = {
    0x18, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_EffectSteering_InitForSplit = {
    (void *)&EffectSteering_InitForSplit, 0x000001E4, (void *)extab_EffectSteering_InitForSplit
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void EffectSteering_InitForSplit(void) { /* 0x8005B8CC size:0x1E4 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stfd f31, 0x20(r1)
    psq_st f31, 0x28(r1), 0, 0
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    mr r30, r3
    fmr f31, f1
    lwz r0, 0x1c(r3)
    mr r31, r4
    cmpwi r0, 0x0
    beq EffectSteering_InitForSplit_L_8005B918
    lwz r3, 0x20(r30)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    EffectSteering_InitForSplit_L_8005B918:
    li r0, 0x5
    stw r0, 0x1c(r30)
    lwz r0, 0x14(r30)
    cmpwi r0, 0x0
    ble EffectSteering_InitForSplit_L_8005B940
    lwz r3, 0xc(r30)
    lwz r0, 0x8(r30)
    cmpw r3, r0
    bge EffectSteering_InitForSplit_L_8005B950
    b EffectSteering_InitForSplit_L_8005B984
    EffectSteering_InitForSplit_L_8005B940:
    lwz r3, 0xc(r30)
    lwz r0, 0x8(r30)
    cmpw r3, r0
    bgt EffectSteering_InitForSplit_L_8005B984
    EffectSteering_InitForSplit_L_8005B950:
    lfs f0, lbl_806D2978(r2)
    li r0, 0x0
    stw r0, 0x8(r30)
    li r0, 0x1
    fmuls f0, f0, f31
    lwz r3, 0x8(r30)
    fctiwz f0, f0
    stw r3, 0x10(r30)
    stfd f0, 0x8(r1)
    lwz r3, 0xc(r1)
    stw r3, 0xc(r30)
    stw r0, 0x14(r30)
    stb r0, 0x18(r30)
    EffectSteering_InitForSplit_L_8005B984:
    lwz r0, 0x1c(r30)
    cmplwi r0, 0x9
    bgt EffectSteering_InitForSplit_L_8005BA08
    lis r3, jumptable_803F9A58@ha
    slwi r0, r0, 2
    addi r3, r3, jumptable_803F9A58@l
    lwzx r0, r3, r0
    mtctr r0
    bctr
    lwz r0, 0x24(r30)
    stw r0, 0x20(r30)
    b EffectSteering_InitForSplit_L_8005BA20
    lwz r0, 0x28(r30)
    stw r0, 0x20(r30)
    b EffectSteering_InitForSplit_L_8005BA20
    lwz r0, 0x2c(r30)
    stw r0, 0x20(r30)
    b EffectSteering_InitForSplit_L_8005BA20
    lwz r0, 0x30(r30)
    stw r0, 0x20(r30)
    b EffectSteering_InitForSplit_L_8005BA20
    lwz r0, 0x34(r30)
    stw r0, 0x20(r30)
    b EffectSteering_InitForSplit_L_8005BA20
    lwz r0, 0x38(r30)
    stw r0, 0x20(r30)
    b EffectSteering_InitForSplit_L_8005BA20
    lwz r0, 0x3c(r30)
    stw r0, 0x20(r30)
    b EffectSteering_InitForSplit_L_8005BA20
    lwz r0, 0x40(r30)
    stw r0, 0x20(r30)
    b EffectSteering_InitForSplit_L_8005BA20
    EffectSteering_InitForSplit_L_8005BA08:
    lis r3, lbl_802EDD98@ha
    addi r3, r3, lbl_802EDD98@l
    crxor 6, 6, 6
    bl DebugPrintf
    li r0, 0x0
    b EffectSteering_InitForSplit_L_8005BA24
    EffectSteering_InitForSplit_L_8005BA20:
    li r0, 0x1
    EffectSteering_InitForSplit_L_8005BA24:
    clrlwi. r0, r0, 24
    bne EffectSteering_InitForSplit_L_8005BA34
    li r3, 0x0
    b EffectSteering_InitForSplit_L_8005BA8C
    EffectSteering_InitForSplit_L_8005BA34:
    lwz r29, 0x30(r30)
    mr r3, r29
    lwz r12, 0x0(r29)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    stw r31, 0x8(r29)
    lwz r30, 0x4(r29)
    bl StrPcb_GetInstance
    bl StrPcb_GetIntensityScale
    lfs f0, lbl_806D2984(r2)
    lwz r3, 0x0(r30)
    fmuls f1, f0, f1
    bl KartItem_SetStrPcbCmd2dFromFloat
    lwz r30, 0x4(r29)
    bl StrPcb_GetInstance
    bl StrPcb_GetIntensityScale
    lfs f0, lbl_806D2988(r2)
    lwz r3, 0x0(r30)
    fmuls f1, f0, f1
    bl KartItem_SetStrPcbCmd2eFromFloat
    li r3, 0x1
    EffectSteering_InitForSplit_L_8005BA8C:
    psq_l f31, 0x28(r1), 0, 0
    lwz r0, 0x34(r1)
    lfd f31, 0x20(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

