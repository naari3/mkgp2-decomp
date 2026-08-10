/* === extracted from auto_KartAudioChannel_Pla_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void SoundMgr_PlaySE();
extern void fn_8016C288();

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_802EDD24[];

/* --- function index (1 fns, .text 0x80059FD4..0x8005A0BC) ---
 * [  0] 0x80059FD4 size:0xE8    global KartAudioChannel_PlayJumpSE
 */

/* --- forward decls --- */
asm void KartAudioChannel_PlayJumpSE(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartAudioChannel_PlayJumpSE[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartAudioChannel_PlayJumpSE = {
    (void *)&KartAudioChannel_PlayJumpSE, 0x000000E8, (void *)extab_KartAudioChannel_PlayJumpSE
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartAudioChannel_PlayJumpSE(void) { /* 0x80059FD4 size:0xE8 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    cmpwi r4, 0x1
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r30, r3
    beq KartAudioChannel_PlayJumpSE_L_8005A018
    bge KartAudioChannel_PlayJumpSE_L_8005A004
    cmpwi r4, 0x0
    bge KartAudioChannel_PlayJumpSE_L_8005A010
    b KartAudioChannel_PlayJumpSE_L_8005A0A4
    KartAudioChannel_PlayJumpSE_L_8005A004:
    cmpwi r4, 0x3
    bge KartAudioChannel_PlayJumpSE_L_8005A0A4
    b KartAudioChannel_PlayJumpSE_L_8005A020
    KartAudioChannel_PlayJumpSE_L_8005A010:
    li r31, 0x8b
    b KartAudioChannel_PlayJumpSE_L_8005A02C
    KartAudioChannel_PlayJumpSE_L_8005A018:
    li r31, 0x8c
    b KartAudioChannel_PlayJumpSE_L_8005A02C
    KartAudioChannel_PlayJumpSE_L_8005A020:
    li r31, 0x8a
    b KartAudioChannel_PlayJumpSE_L_8005A02C
    b KartAudioChannel_PlayJumpSE_L_8005A0A4
    KartAudioChannel_PlayJumpSE_L_8005A02C:
    stw r4, 0x30(r30)
    lwz r0, 0x8(r30)
    clrlslwi r0, r0, 28, 27
    or r3, r31, r0
    bl SoundMgr_PlaySE
    lbz r0, 0x4(r30)
    cmplwi r0, 0x0
    bne KartAudioChannel_PlayJumpSE_L_8005A0A4
    lwz r7, 0xc(r30)
    cmplwi r7, 0x0
    beq KartAudioChannel_PlayJumpSE_L_8005A0A4
    lis r3, lbl_802EDD24@ha
    addi r4, r1, 0x8
    addi r6, r3, lbl_802EDD24@l
    lwz r5, 0x0(r6)
    lwz r3, 0x4(r6)
    lwz r0, 0x8(r6)
    stw r5, 0x8(r1)
    stw r3, 0xc(r1)
    stw r0, 0x10(r1)
    lfs f0, 0xc(r7)
    stfs f0, 0x8(r1)
    lfs f0, 0x1c(r7)
    stfs f0, 0xc(r1)
    lfs f0, 0x2c(r7)
    stfs f0, 0x10(r1)
    lwz r0, 0x8(r30)
    clrlslwi r0, r0, 28, 27
    or r3, r31, r0
    bl fn_8016C288
    KartAudioChannel_PlayJumpSE_L_8005A0A4:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

