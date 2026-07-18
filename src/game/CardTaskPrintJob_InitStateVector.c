extern unsigned int lbl_803F1C68[];

asm void CardTaskPrintJob_InitStateVector(void) {
    nofralloc
    lis r4, lbl_803F1C68@ha
    li r0, 0
    addi r6, r4, lbl_803F1C68@l
    lwz r5, 0(r6)
    lwz r4, 4(r6)
    stw r5, 0(r3)
    stw r4, 4(r3)
    lwz r4, 8(r6)
    stw r4, 8(r3)
    stw r0, 0xc(r3)
    stw r0, 0x10(r3)
    blr
}
