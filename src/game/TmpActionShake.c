asm void ActionShake_Reset(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ActionShake_Reset[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ActionShake_Reset = {
    (void *)&ActionShake_Reset, 0x0000004C, (void *)extab_ActionShake_Reset
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ActionShake_Reset(void) { /* 0x8005B880 size:0x4C */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lfs f0, lbl_806D297C(r2)
    stw r0, 0x14(r1)
    li r0, 0x0
    stw r31, 0xc(r1)
    stfs f0, 0x8(r3)
    stw r0, 0xc(r3)
    stfs f0, 0x24(r3)
    lwz r31, 0x4(r3)
    lwz r3, 0x0(r31)
    bl KartItem_ResetStrPcbToIdle
    lfs f0, lbl_806D297C(r2)
    stfs f0, 0x48(r31)
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

