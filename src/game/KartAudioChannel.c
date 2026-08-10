extern unsigned int lbl_806D2940;
extern void fn_8016C394();

asm void KartAudioChannel_Init(void);
asm void KartAudioChannel_ResetSEsAndSetFlag(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartAudioChannel_ResetSEsAndSetFlag[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartAudioChannel_ResetSEsAndSetFlag = {
    (void *)&KartAudioChannel_ResetSEsAndSetFlag, 0x00000068, (void *)extab_KartAudioChannel_ResetSEsAndSetFlag
};

asm void KartAudioChannel_Init(void) {
    nofralloc
    stw r4, 0x0(r3)
    li r4, 0x0
    lfs f0, lbl_806D2940(r2)
    li r0, -0x1
    stb r5, 0x5(r3)
    stb r5, 0x4(r3)
    stb r6, 0x6(r3)
    stw r7, 0x8(r3)
    stw r8, 0xc(r3)
    stfs f0, 0x10(r3)
    stfs f0, 0x14(r3)
    stb r4, 0x18(r3)
    stfs f0, 0x1c(r3)
    stfs f0, 0x20(r3)
    stw r4, 0x24(r3)
    stw r0, 0x28(r3)
    stw r4, 0x2c(r3)
    stw r0, 0x34(r3)
    stw r0, 0x30(r3)
    blr
}

asm void KartAudioChannel_ResetSEsAndSetFlag(void) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 0x8(r1)
    mr r30, r3
    lwz r0, 0x8(r3)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0x52
    bl fn_8016C394
    lwz r0, 0x8(r30)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0x51
    bl fn_8016C394
    lwz r0, 0x8(r30)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0x50
    bl fn_8016C394
    stb r31, 0x4(r30)
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
