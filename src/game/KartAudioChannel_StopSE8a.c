/* === extracted from auto_KartAudioChannel_Sto_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void fn_8016C394();

/* --- function index (1 fns, .text 0x80059F70..0x80059FD4) ---
 * [  0] 0x80059F70 size:0x64    global KartAudioChannel_StopSE8a
 */

/* --- forward decls --- */
asm void KartAudioChannel_StopSE8a(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartAudioChannel_StopSE8a[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartAudioChannel_StopSE8a = {
    (void *)&KartAudioChannel_StopSE8a, 0x00000064, (void *)extab_KartAudioChannel_StopSE8a
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartAudioChannel_StopSE8a(void) { /* 0x80059F70 size:0x64 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 0x8(r1)
    mr r30, r3
    lwz r0, 0x30(r3)
    cmpwi r0, -0x1
    beq KartAudioChannel_StopSE8a_L_80059FBC
    lwz r0, 0x8(r30)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0x8a
    bl fn_8016C394
    clrlwi r0, r31, 24
    cmplwi r0, 0x1
    bne KartAudioChannel_StopSE8a_L_80059FBC
    li r0, -0x1
    stw r0, 0x30(r30)
    KartAudioChannel_StopSE8a_L_80059FBC:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}


