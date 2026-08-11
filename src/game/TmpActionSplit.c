asm void ActionSplit_Reset(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ActionSplit_Reset[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ActionSplit_Reset = {
    (void *)&ActionSplit_Reset, 0x00000050, (void *)extab_ActionSplit_Reset
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ActionSplit_Reset(void) { /* 0x8005BAB0 size:0x50 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    stw r30, 0x8(r1)
    mr r30, r3
    lwz r31, 0x4(r3)
    lwz r3, 0x0(r31)
    bl KartItem_ResetStrPcbToIdle
    lfs f0, lbl_806D297C(r2)
    li r0, 0x0
    stfs f0, 0x48(r31)
    stw r0, 0xc(r30)
    stw r0, 0x10(r30)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

