extern void clItemBoxManager_RegisterResponder();
extern unsigned int lbl_806D10D0;
extern unsigned int lbl_803F9D00[];
asm void clItemBoxResponder_Ctor(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clItemBoxResponder_Ctor[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clItemBoxResponder_Ctor = {
    (void *)&clItemBoxResponder_Ctor, 0x0000007C, (void *)extab_clItemBoxResponder_Ctor
};

asm void clItemBoxResponder_Ctor(void) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r5, lbl_803F9D00@ha
    stw r0, 0x14(r1)
    addi r0, r5, lbl_803F9D00@l
    li r5, 0x0
    stw r31, 0xc(r1)
    mr r31, r3
    stw r0, 0x0(r3)
    stw r4, 0x4(r3)
    stw r5, 0x8(r3)
    lwz r3, lbl_806D10D0(r13)
    cmplwi r3, 0x0
    bne clItemBoxResponder_Ctor_L_800600EC
    b clItemBoxResponder_Ctor_L_800600F0
clItemBoxResponder_Ctor_L_800600EC:
    mr r5, r3
clItemBoxResponder_Ctor_L_800600F0:
    cmplwi r5, 0x0
    bne clItemBoxResponder_Ctor_L_80060100
    mr r3, r31
    b clItemBoxResponder_Ctor_L_80060118
clItemBoxResponder_Ctor_L_80060100:
    cmplwi r3, 0x0
    bne clItemBoxResponder_Ctor_L_8006010C
    li r3, 0x0
clItemBoxResponder_Ctor_L_8006010C:
    mr r4, r31
    bl clItemBoxManager_RegisterResponder
    mr r3, r31
clItemBoxResponder_Ctor_L_80060118:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
