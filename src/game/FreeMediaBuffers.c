/*
 * FreeMediaBuffers: walks the 6-entry g_mediaBuffers table (stride 8, flag at
 * +0 / ptr at +4) and frees each slot's pointer via MemoryManager_Free,
 * zeroing both fields.
 *
 * Held as asm_fn: CW132 cannot reproduce the prologue scheduling
 * `stw r30, 0x18(r1) ; addi r30, r3, g_mediaBuffers@l` (target inlines the
 * pointer init directly into r30 after the callee-save), instead emitting
 * `addi r0, r3, @l ; stw r30 ; mr r30, r0` via a temporary (+4 bytes / +1 mr).
 * Same idiom as SyncSlot_Reset (src/game/SyncSlot.c).
 */

extern void MemoryManager_Free(void *p);

extern unsigned char g_mediaBuffers[0x30];

asm void FreeMediaBuffers(void);

/* --- extab (manual emit, .extab_user -> extab via postprocess_extab_user) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_FreeMediaBuffers[8] = {
    0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via postprocess) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_FreeMediaBuffers = {
    (void *)&FreeMediaBuffers, 0x00000064, (void *)extab_FreeMediaBuffers
};

asm void FreeMediaBuffers(void) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    lis r3, g_mediaBuffers@ha
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    li r31, 0x0
    stw r30, 0x18(r1)
    addi r30, r3, g_mediaBuffers@l
    stw r29, 0x14(r1)
    li r29, 0x0
FreeMediaBuffers_L_80087A94:
    lwz r3, 0x4(r30)
    bl MemoryManager_Free
    stb r31, 0x0(r30)
    addi r29, r29, 0x1
    cmpwi r29, 0x6
    stw r31, 0x4(r30)
    addi r30, r30, 0x8
    blt FreeMediaBuffers_L_80087A94
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
