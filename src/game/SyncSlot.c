/*
 * msg_type 4 sync slot helpers.
 *
 * Two 0x1C-byte slots sit back-to-back at lbl_805AC258 (recv) and
 * lbl_805AC258 + 0x1C (host send).
 *
 * SyncSlot_Reset is asm_fn: CW132 cannot reproduce the prologue scheduling
 * `stw r31, 0xc(r1) ; addi r31, r3, lbl@l` (target inlines r31 init right
 * after r31 save), instead emitting `addi r0 ; stw r31 ; mr r31, r0` via a
 * temporary (+4 bytes). Held as asm_fn with manually emitted extab so the
 * other two functions stay matched.
 */

extern unsigned char g_isCommHost;
extern int g_localPcbRole;
extern unsigned char lbl_805AC258[0x38];

extern void memset();

asm void SyncSlot_Reset(void);

/* --- extab (manual emit, .extab_user -> extab via postprocess_extab_user) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_SyncSlot_Reset[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via postprocess) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_SyncSlot_Reset = {
    (void *)&SyncSlot_Reset, 0x00000058, (void *)extab_SyncSlot_Reset
};

void *SyncSlot_GetHostSend(void) {
    unsigned char *p;
    if (g_isCommHost == 0) return (void *)0;
    p = &lbl_805AC258[0x1c];
    if (g_localPcbRole != 0) return p;
    return (void *)0;
}

void *SyncSlot_GetRecv(void) {
    return lbl_805AC258;
}

asm void SyncSlot_Reset(void) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r3, lbl_805AC258@ha
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    addi r31, r3, lbl_805AC258@l
    stw r30, 0x8(r1)
    li r30, 0x0
SyncSlot_Reset_L_8008511C:
    mr r3, r31
    li r4, 0x0
    li r5, 0x1c
    bl memset
    addi r30, r30, 0x1
    addi r31, r31, 0x1c
    cmpwi r30, 0x2
    blt SyncSlot_Reset_L_8008511C
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
