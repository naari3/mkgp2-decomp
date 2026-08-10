extern unsigned char g_ringBufferBase[0x3700];
extern int g_ringReadIdx;
extern int lbl_806D11A0;
extern void *memset(void *, int, unsigned long);

asm void CommBroadcast_ClearTable(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_CommBroadcast_ClearTable[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_CommBroadcast_ClearTable = {
    (void *)&CommBroadcast_ClearTable, 0x68, (void *)extab_CommBroadcast_ClearTable
};

asm void CommBroadcast_ClearTable(void) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r4, 1
    lis r3, g_ringBufferBase@ha
    stw r0, 0x14(r1)
    li r0, 0
    stw r31, 0xc(r1)
    addi r31, r3, g_ringBufferBase@l
    stw r30, 0x8(r1)
    li r30, 0
    stw r4, lbl_806D11A0(r13)
    stw r0, g_ringReadIdx(r13)
CommBroadcast_ClearTable_Loop:
    mr r3, r31
    li r4, 0
    li r5, 0xdc
    bl memset
    addi r30, r30, 1
    addi r31, r31, 0xdc
    cmpwi r30, 0x40
    blt CommBroadcast_ClearTable_Loop
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
