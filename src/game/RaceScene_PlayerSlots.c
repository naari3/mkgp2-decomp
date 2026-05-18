extern void *g_carObjects[4];

void *GetPlayerCarBySlot(int slot) {
    if (slot < 0 || slot >= 4) {
        return 0;
    }
    return g_carObjects[slot];
}

asm void RaceScene_ClearPlayerSlotPointers(void) {
    nofralloc
    lis r3, g_carObjects@ha
    li r0, 0x0
    addi r6, r3, g_carObjects@l
    addi r5, r6, 0x0
    stw r0, 0x0(r6)
    addi r4, r6, 0x10
    addi r3, r6, 0x20
    stw r0, 0x10(r6)
    stw r0, 0x20(r6)
    stw r0, 0x4(r5)
    stw r0, 0x4(r4)
    stw r0, 0x4(r3)
    stw r0, 0x8(r5)
    stw r0, 0x8(r4)
    stw r0, 0x8(r3)
    stw r0, 0xc(r5)
    stw r0, 0xc(r4)
    stw r0, 0xc(r3)
    blr
}
