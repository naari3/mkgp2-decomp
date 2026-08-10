/* AnimState pool management, 0x800AF240..0x800AF4F8. */

extern void Alloc(void);
extern void AnimState_Init(void);
extern void MemoryManager_TimedFree(void);

extern unsigned int lbl_805DF350[];
extern float lbl_806D4FC8;
extern float lbl_806D4FCC;

asm void AnimStatePool_Free(void);
asm void AnimStatePool_Alloc(void);
asm void AnimStatePool_FreeAll(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_AnimStatePool_Free[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
__declspec(section ".extab_user") static const struct {
    unsigned int f0, f1, f2, f3, f4;
    void *f5;
} extab_AnimStatePool_Alloc = {
    0x180A0000, 0x00000108, 0x00000010, 0x00000000, 0x8A80001D,
    (void *)&MemoryManager_TimedFree
};
__declspec(section ".extab_user") static const unsigned char extab_AnimStatePool_FreeAll[8] = {
    0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int size; void *extab; } extabindex_AnimStatePool_Free = {
    (void *)&AnimStatePool_Free, 0x78, (void *)&extab_AnimStatePool_Free
};
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int size; void *extab; } extabindex_AnimStatePool_Alloc = {
    (void *)&AnimStatePool_Alloc, 0x14C, (void *)&extab_AnimStatePool_Alloc
};
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int size; void *extab; } extabindex_AnimStatePool_FreeAll = {
    (void *)&AnimStatePool_FreeAll, 0x68, (void *)&extab_AnimStatePool_FreeAll
};

asm void AnimStatePool_Free(void) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r4, lbl_805DF350@ha
    li r5, 0
    stw r0, 0x14(r1)
    li r0, 0x20
    addi r4, r4, lbl_805DF350@l
    stw r31, 0xc(r1)
    stw r30, 8(r1)
    mtctr r0
AnimStatePool_Free_L_800AF268:
    lwz r0, 0(r4)
    cmplw r0, r3
    bne AnimStatePool_Free_L_800AF294
    lis r3, lbl_805DF350@ha
    slwi r30, r5, 2
    addi r31, r3, lbl_805DF350@l
    lwzx r3, r31, r30
    bl MemoryManager_TimedFree
    li r0, 0
    stwx r0, r31, r30
    b AnimStatePool_Free_L_800AF2A0
AnimStatePool_Free_L_800AF294:
    addi r4, r4, 4
    addi r5, r5, 1
    bdnz AnimStatePool_Free_L_800AF268
AnimStatePool_Free_L_800AF2A0:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

asm void AnimStatePool_Alloc(void) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    lis r4, lbl_805DF350@ha
    stw r0, 0x24(r1)
    li r0, 0x20
    addi r4, r4, lbl_805DF350@l
    stw r31, 0x1c(r1)
    li r31, 0
    stw r30, 0x18(r1)
    mr r30, r3
    stw r29, 0x14(r1)
    mtctr r0
AnimStatePool_Alloc_L_800AF2E8:
    lwz r0, 0(r4)
    cmplwi r0, 0
    bne AnimStatePool_Alloc_L_800AF3D8
    li r3, 0xe8
    bl Alloc
    mr. r29, r3
    beq AnimStatePool_Alloc_L_800AF3C0
    li r0, -1
    lfs f1, -0x5298(r2)
    stw r0, 0x44(r29)
    mr r4, r30
    lfs f0, -0x5294(r2)
    stfs f1, 0x48(r29)
    stfs f1, 0x4c(r29)
    stfs f1, 0x50(r29)
    stfs f1, 0x78(r29)
    stfs f1, 0x7c(r29)
    stfs f1, 0x80(r29)
    stfs f0, 0xa8(r29)
    stfs f0, 0xac(r29)
    stfs f0, 0xb0(r29)
    stfs f0, 0xd8(r29)
    stfs f1, 0x54(r29)
    stfs f1, 0x58(r29)
    stfs f1, 0x5c(r29)
    stfs f1, 0x84(r29)
    stfs f1, 0x88(r29)
    stfs f1, 0x8c(r29)
    stfs f0, 0xb4(r29)
    stfs f0, 0xb8(r29)
    stfs f0, 0xbc(r29)
    stfs f0, 0xdc(r29)
    stfs f1, 0x60(r29)
    stfs f1, 0x64(r29)
    stfs f1, 0x68(r29)
    stfs f1, 0x90(r29)
    stfs f1, 0x94(r29)
    stfs f1, 0x98(r29)
    stfs f0, 0xc0(r29)
    stfs f0, 0xc4(r29)
    stfs f0, 0xc8(r29)
    stfs f0, 0xe0(r29)
    stfs f1, 0x6c(r29)
    stfs f1, 0x70(r29)
    stfs f1, 0x74(r29)
    stfs f1, 0x9c(r29)
    stfs f1, 0xa0(r29)
    stfs f1, 0xa4(r29)
    stfs f0, 0xcc(r29)
    stfs f0, 0xd0(r29)
    stfs f0, 0xd4(r29)
    stfs f0, 0xe4(r29)
    stfs f0, 0x28(r29)
    bl AnimState_Init
AnimStatePool_Alloc_L_800AF3C0:
    lis r3, lbl_805DF350@ha
    slwi r0, r31, 2
    addi r3, r3, lbl_805DF350@l
    stwx r29, r3, r0
    lwzx r3, r3, r0
    b AnimStatePool_Alloc_L_800AF3E8
AnimStatePool_Alloc_L_800AF3D8:
    addi r4, r4, 4
    addi r31, r31, 1
    bdnz AnimStatePool_Alloc_L_800AF2E8
    li r3, 0
AnimStatePool_Alloc_L_800AF3E8:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

asm void AnimStatePool_FreeAll(void) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    lis r3, lbl_805DF350@ha
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    li r31, 0
    stw r30, 0x18(r1)
    addi r30, r3, lbl_805DF350@l
    stw r29, 0x14(r1)
    li r29, 0
AnimStatePool_FreeAll_L_800AF42C:
    lwz r3, 0(r30)
    cmplwi r3, 0
    beq AnimStatePool_FreeAll_L_800AF440
    bl MemoryManager_TimedFree
    stw r31, 0(r30)
AnimStatePool_FreeAll_L_800AF440:
    addi r29, r29, 1
    addi r30, r30, 4
    cmpwi r29, 0x20
    blt AnimStatePool_FreeAll_L_800AF42C
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

void AnimStatePool_ZeroInit(void) {
    lbl_805DF350[0] = 0;
    lbl_805DF350[1] = 0;
    lbl_805DF350[2] = 0;
    lbl_805DF350[3] = 0;
    lbl_805DF350[4] = 0;
    lbl_805DF350[5] = 0;
    lbl_805DF350[6] = 0;
    lbl_805DF350[7] = 0;
    lbl_805DF350[8] = 0;
    lbl_805DF350[9] = 0;
    lbl_805DF350[10] = 0;
    lbl_805DF350[11] = 0;
    lbl_805DF350[12] = 0;
    lbl_805DF350[13] = 0;
    lbl_805DF350[14] = 0;
    lbl_805DF350[15] = 0;
    lbl_805DF350[16] = 0;
    lbl_805DF350[17] = 0;
    lbl_805DF350[18] = 0;
    lbl_805DF350[19] = 0;
    lbl_805DF350[20] = 0;
    lbl_805DF350[21] = 0;
    lbl_805DF350[22] = 0;
    lbl_805DF350[23] = 0;
    lbl_805DF350[24] = 0;
    lbl_805DF350[25] = 0;
    lbl_805DF350[26] = 0;
    lbl_805DF350[27] = 0;
    lbl_805DF350[28] = 0;
    lbl_805DF350[29] = 0;
    lbl_805DF350[30] = 0;
    lbl_805DF350[31] = 0;
}
