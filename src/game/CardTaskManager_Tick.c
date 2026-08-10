extern void ServiceButtonExtra_Set();

asm void CardTaskManager_Tick(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_CardTaskManager_Tick[8] = {
    0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CardTaskManager_Tick = {
    (void *)&CardTaskManager_Tick, 0x00000124, (void *)extab_CardTaskManager_Tick
};

asm void CardTaskManager_Tick(void) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    mr r29, r3
    lwz r3, 0xc(r3)
    addi r0, r3, 0x1
    stw r0, 0xc(r29)
    lwz r4, 0x8(r29)
    lwz r0, 0x4(r29)
    cmpw r4, r0
    blt CardTaskManager_Tick_L_80089ED8
    lwz r3, 0x10(r29)
    li r0, 0x2
    subi r3, r3, 0x1
    stw r3, 0x10(r29)
    lwz r4, 0x10(r29)
    neg r3, r4
    orc r3, r4, r3
    srawi r3, r3, 31
    andc r3, r0, r3
    b CardTaskManager_Tick_L_80089F80
CardTaskManager_Tick_L_80089ED8:
    lwz r3, 0x0(r29)
    slwi r0, r4, 3
    lwzx r30, r3, r0
    mr r3, r30
    lwz r12, 0x0(r30)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    stw r3, 0x4(r30)
    lwz r31, 0x4(r30)
    cmpwi r31, 0x2
    beq CardTaskManager_Tick_L_80089F18
    cmpwi r31, 0x4
    beq CardTaskManager_Tick_L_80089F18
    cmpwi r31, 0x5
    bne CardTaskManager_Tick_L_80089F7C
CardTaskManager_Tick_L_80089F18:
    mr r3, r30
    lwz r12, 0x0(r30)
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl
    li r3, 0x0
    bl ServiceButtonExtra_Set
    cmpwi r31, 0x5
    bne CardTaskManager_Tick_L_80089F44
    li r3, 0x3
    b CardTaskManager_Tick_L_80089F80
CardTaskManager_Tick_L_80089F44:
    lwz r3, 0x8(r29)
    addi r0, r3, 0x1
    stw r0, 0x8(r29)
    lwz r4, 0x8(r29)
    lwz r0, 0x4(r29)
    cmpw r4, r0
    bge CardTaskManager_Tick_L_80089F7C
    lwz r3, 0x0(r29)
    slwi r0, r4, 3
    lwzx r3, r3, r0
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
CardTaskManager_Tick_L_80089F7C:
    li r3, 0x2
CardTaskManager_Tick_L_80089F80:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
