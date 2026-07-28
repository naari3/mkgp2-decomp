/* === extracted from auto_KartItemAudio_StopSE_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ItemAlias_DestToSource();
extern void SoundMgr_PlaySE();
extern void fn_8016C288();
extern void fn_8016C394();
extern void fn_8016C488();
extern void fn_8016C4CC();

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_802EDD24[];

/* --- function index (1 fns, .text 0x8005A140..0x8005A314) ---
 * [  0] 0x8005A140 size:0x1D4   global KartItemAudio_StopSEByItemId
 */

/* --- forward decls --- */
asm void KartItemAudio_StopSEByItemId(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartItemAudio_StopSEByItemId[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartItemAudio_StopSEByItemId = {
    (void *)&KartItemAudio_StopSEByItemId, 0x000001D4, (void *)extab_KartItemAudio_StopSEByItemId
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartItemAudio_StopSEByItemId(void) { /* 0x8005A140 size:0x1D4 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    cmpwi r4, 0x115
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    bge KartItemAudio_StopSEByItemId_L_8005A16C
    clrlwi r3, r4, 24
    addi r4, r1, 0x8
    bl ItemAlias_DestToSource
    b KartItemAudio_StopSEByItemId_L_8005A170
    KartItemAudio_StopSEByItemId_L_8005A16C:
    mr r3, r4
    KartItemAudio_StopSEByItemId_L_8005A170:
    cmpwi r3, 0x24
    beq KartItemAudio_StopSEByItemId_L_8005A214
    bge KartItemAudio_StopSEByItemId_L_8005A1CC
    cmpwi r3, 0x17
    bge KartItemAudio_StopSEByItemId_L_8005A1A8
    cmpwi r3, 0x10
    beq KartItemAudio_StopSEByItemId_L_8005A214
    bge KartItemAudio_StopSEByItemId_L_8005A19C
    cmpwi r3, 0xe
    beq KartItemAudio_StopSEByItemId_L_8005A214
    b KartItemAudio_StopSEByItemId_L_8005A300
    KartItemAudio_StopSEByItemId_L_8005A19C:
    cmpwi r3, 0x15
    bge KartItemAudio_StopSEByItemId_L_8005A214
    b KartItemAudio_StopSEByItemId_L_8005A300
    KartItemAudio_StopSEByItemId_L_8005A1A8:
    cmpwi r3, 0x1e
    bge KartItemAudio_StopSEByItemId_L_8005A1BC
    cmpwi r3, 0x19
    beq KartItemAudio_StopSEByItemId_L_8005A264
    b KartItemAudio_StopSEByItemId_L_8005A300
    KartItemAudio_StopSEByItemId_L_8005A1BC:
    cmpwi r3, 0x21
    beq KartItemAudio_StopSEByItemId_L_8005A22C
    bge KartItemAudio_StopSEByItemId_L_8005A300
    b KartItemAudio_StopSEByItemId_L_8005A214
    KartItemAudio_StopSEByItemId_L_8005A1CC:
    cmpwi r3, 0x46
    beq KartItemAudio_StopSEByItemId_L_8005A2DC
    bge KartItemAudio_StopSEByItemId_L_8005A1FC
    cmpwi r3, 0x2d
    beq KartItemAudio_StopSEByItemId_L_8005A2DC
    bge KartItemAudio_StopSEByItemId_L_8005A1F0
    cmpwi r3, 0x28
    beq KartItemAudio_StopSEByItemId_L_8005A214
    b KartItemAudio_StopSEByItemId_L_8005A300
    KartItemAudio_StopSEByItemId_L_8005A1F0:
    cmpwi r3, 0x3c
    beq KartItemAudio_StopSEByItemId_L_8005A24C
    b KartItemAudio_StopSEByItemId_L_8005A300
    KartItemAudio_StopSEByItemId_L_8005A1FC:
    cmpwi r3, 0x98
    beq KartItemAudio_StopSEByItemId_L_8005A2F0
    bge KartItemAudio_StopSEByItemId_L_8005A300
    cmpwi r3, 0x5d
    beq KartItemAudio_StopSEByItemId_L_8005A2DC
    b KartItemAudio_StopSEByItemId_L_8005A300
    KartItemAudio_StopSEByItemId_L_8005A214:
    lbz r0, 0x4(r31)
    cmplwi r0, 0x1
    bne KartItemAudio_StopSEByItemId_L_8005A300
    li r3, 0x0
    bl fn_8016C488
    b KartItemAudio_StopSEByItemId_L_8005A300
    KartItemAudio_StopSEByItemId_L_8005A22C:
    lbz r0, 0x4(r31)
    cmplwi r0, 0x1
    bne KartItemAudio_StopSEByItemId_L_8005A300
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0xc5
    bl fn_8016C394
    b KartItemAudio_StopSEByItemId_L_8005A300
    KartItemAudio_StopSEByItemId_L_8005A24C:
    lbz r0, 0x4(r31)
    cmplwi r0, 0x1
    bne KartItemAudio_StopSEByItemId_L_8005A300
    li r3, 0x0
    bl fn_8016C4CC
    b KartItemAudio_StopSEByItemId_L_8005A300
    KartItemAudio_StopSEByItemId_L_8005A264:
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0xa2
    bl SoundMgr_PlaySE
    lbz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne KartItemAudio_StopSEByItemId_L_8005A300
    lwz r7, 0xc(r31)
    cmplwi r7, 0x0
    beq KartItemAudio_StopSEByItemId_L_8005A300
    lis r3, lbl_802EDD24@ha
    addi r4, r1, 0xc
    addi r6, r3, lbl_802EDD24@l
    lwz r5, 0x0(r6)
    lwz r3, 0x4(r6)
    lwz r0, 0x8(r6)
    stw r5, 0xc(r1)
    stw r3, 0x10(r1)
    stw r0, 0x14(r1)
    lfs f0, 0xc(r7)
    stfs f0, 0xc(r1)
    lfs f0, 0x1c(r7)
    stfs f0, 0x10(r1)
    lfs f0, 0x2c(r7)
    stfs f0, 0x14(r1)
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0xa2
    bl fn_8016C288
    b KartItemAudio_StopSEByItemId_L_8005A300
    KartItemAudio_StopSEByItemId_L_8005A2DC:
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0x8a
    bl fn_8016C394
    b KartItemAudio_StopSEByItemId_L_8005A300
    KartItemAudio_StopSEByItemId_L_8005A2F0:
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0xcf
    bl fn_8016C394
    KartItemAudio_StopSEByItemId_L_8005A300:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}


/* === extracted from auto_KartItemAudio_PlayHi_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ItemAlias_DestToSource();
extern void MediaBoard_DMA_Submit();
extern void SoundMgr_PlaySE();
extern void fn_8016C288();
extern void fn_8016C4CC();

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_802EDD24[];

/* --- function index (1 fns, .text 0x8005A314..0x8005A638) ---
 * [  0] 0x8005A314 size:0x324   global KartItemAudio_PlayHitConfirmSE
 */

/* --- forward decls --- */
asm void KartItemAudio_PlayHitConfirmSE(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartItemAudio_PlayHitConfirmSE[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartItemAudio_PlayHitConfirmSE = {
    (void *)&KartItemAudio_PlayHitConfirmSE, 0x00000324, (void *)extab_KartItemAudio_PlayHitConfirmSE
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartItemAudio_PlayHitConfirmSE(void) { /* 0x8005A314 size:0x324 */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    cmpwi r4, 0x115
    stw r0, 0x54(r1)
    stw r31, 0x4c(r1)
    mr r31, r3
    stw r30, 0x48(r1)
    bge KartItemAudio_PlayHitConfirmSE_L_8005A348
    clrlwi r3, r4, 24
    addi r4, r1, 0x8
    bl ItemAlias_DestToSource
    mr r30, r3
    b KartItemAudio_PlayHitConfirmSE_L_8005A34C
    KartItemAudio_PlayHitConfirmSE_L_8005A348:
    mr r30, r4
    KartItemAudio_PlayHitConfirmSE_L_8005A34C:
    mr r3, r31
    mr r4, r30
    bl MediaBoard_DMA_Submit
    cmpwi r30, 0x46
    beq KartItemAudio_PlayHitConfirmSE_L_8005A3B8
    bge KartItemAudio_PlayHitConfirmSE_L_8005A394
    cmpwi r30, 0x3b
    beq KartItemAudio_PlayHitConfirmSE_L_8005A620
    bge KartItemAudio_PlayHitConfirmSE_L_8005A388
    cmpwi r30, 0x2d
    beq KartItemAudio_PlayHitConfirmSE_L_8005A3B8
    blt KartItemAudio_PlayHitConfirmSE_L_8005A620
    cmpwi r30, 0x39
    bge KartItemAudio_PlayHitConfirmSE_L_8005A4A4
    b KartItemAudio_PlayHitConfirmSE_L_8005A620
    KartItemAudio_PlayHitConfirmSE_L_8005A388:
    cmpwi r30, 0x3d
    bge KartItemAudio_PlayHitConfirmSE_L_8005A620
    b KartItemAudio_PlayHitConfirmSE_L_8005A594
    KartItemAudio_PlayHitConfirmSE_L_8005A394:
    cmpwi r30, 0x5d
    beq KartItemAudio_PlayHitConfirmSE_L_8005A3B8
    bge KartItemAudio_PlayHitConfirmSE_L_8005A3AC
    cmpwi r30, 0x50
    beq KartItemAudio_PlayHitConfirmSE_L_8005A51C
    b KartItemAudio_PlayHitConfirmSE_L_8005A620
    KartItemAudio_PlayHitConfirmSE_L_8005A3AC:
    cmpwi r30, 0x98
    beq KartItemAudio_PlayHitConfirmSE_L_8005A5AC
    b KartItemAudio_PlayHitConfirmSE_L_8005A620
    KartItemAudio_PlayHitConfirmSE_L_8005A3B8:
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0x63
    bl SoundMgr_PlaySE
    lbz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne KartItemAudio_PlayHitConfirmSE_L_8005A42C
    lwz r7, 0xc(r31)
    cmplwi r7, 0x0
    beq KartItemAudio_PlayHitConfirmSE_L_8005A42C
    lis r3, lbl_802EDD24@ha
    addi r4, r1, 0x3c
    addi r6, r3, lbl_802EDD24@l
    lwz r5, 0x0(r6)
    lwz r3, 0x4(r6)
    lwz r0, 0x8(r6)
    stw r5, 0x3c(r1)
    stw r3, 0x40(r1)
    stw r0, 0x44(r1)
    lfs f0, 0xc(r7)
    stfs f0, 0x3c(r1)
    lfs f0, 0x1c(r7)
    stfs f0, 0x40(r1)
    lfs f0, 0x2c(r7)
    stfs f0, 0x44(r1)
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0x63
    bl fn_8016C288
    KartItemAudio_PlayHitConfirmSE_L_8005A42C:
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0x8a
    bl SoundMgr_PlaySE
    lbz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne KartItemAudio_PlayHitConfirmSE_L_8005A620
    lwz r7, 0xc(r31)
    cmplwi r7, 0x0
    beq KartItemAudio_PlayHitConfirmSE_L_8005A620
    lis r3, lbl_802EDD24@ha
    addi r4, r1, 0x30
    addi r6, r3, lbl_802EDD24@l
    lwz r5, 0x0(r6)
    lwz r3, 0x4(r6)
    lwz r0, 0x8(r6)
    stw r5, 0x30(r1)
    stw r3, 0x34(r1)
    stw r0, 0x38(r1)
    lfs f0, 0xc(r7)
    stfs f0, 0x30(r1)
    lfs f0, 0x1c(r7)
    stfs f0, 0x34(r1)
    lfs f0, 0x2c(r7)
    stfs f0, 0x38(r1)
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0x8a
    bl fn_8016C288
    b KartItemAudio_PlayHitConfirmSE_L_8005A620
    KartItemAudio_PlayHitConfirmSE_L_8005A4A4:
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0x85
    bl SoundMgr_PlaySE
    lbz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne KartItemAudio_PlayHitConfirmSE_L_8005A620
    lwz r7, 0xc(r31)
    cmplwi r7, 0x0
    beq KartItemAudio_PlayHitConfirmSE_L_8005A620
    lis r3, lbl_802EDD24@ha
    addi r4, r1, 0x24
    addi r6, r3, lbl_802EDD24@l
    lwz r5, 0x0(r6)
    lwz r3, 0x4(r6)
    lwz r0, 0x8(r6)
    stw r5, 0x24(r1)
    stw r3, 0x28(r1)
    stw r0, 0x2c(r1)
    lfs f0, 0xc(r7)
    stfs f0, 0x24(r1)
    lfs f0, 0x1c(r7)
    stfs f0, 0x28(r1)
    lfs f0, 0x2c(r7)
    stfs f0, 0x2c(r1)
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0x85
    bl fn_8016C288
    b KartItemAudio_PlayHitConfirmSE_L_8005A620
    KartItemAudio_PlayHitConfirmSE_L_8005A51C:
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0x84
    bl SoundMgr_PlaySE
    lbz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne KartItemAudio_PlayHitConfirmSE_L_8005A620
    lwz r7, 0xc(r31)
    cmplwi r7, 0x0
    beq KartItemAudio_PlayHitConfirmSE_L_8005A620
    lis r3, lbl_802EDD24@ha
    addi r4, r1, 0x18
    addi r6, r3, lbl_802EDD24@l
    lwz r5, 0x0(r6)
    lwz r3, 0x4(r6)
    lwz r0, 0x8(r6)
    stw r5, 0x18(r1)
    stw r3, 0x1c(r1)
    stw r0, 0x20(r1)
    lfs f0, 0xc(r7)
    stfs f0, 0x18(r1)
    lfs f0, 0x1c(r7)
    stfs f0, 0x1c(r1)
    lfs f0, 0x2c(r7)
    stfs f0, 0x20(r1)
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0x84
    bl fn_8016C288
    b KartItemAudio_PlayHitConfirmSE_L_8005A620
    KartItemAudio_PlayHitConfirmSE_L_8005A594:
    lbz r0, 0x4(r31)
    cmplwi r0, 0x1
    bne KartItemAudio_PlayHitConfirmSE_L_8005A620
    li r3, 0x1
    bl fn_8016C4CC
    b KartItemAudio_PlayHitConfirmSE_L_8005A620
    KartItemAudio_PlayHitConfirmSE_L_8005A5AC:
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0xcf
    bl SoundMgr_PlaySE
    lbz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne KartItemAudio_PlayHitConfirmSE_L_8005A620
    lwz r7, 0xc(r31)
    cmplwi r7, 0x0
    beq KartItemAudio_PlayHitConfirmSE_L_8005A620
    lis r3, lbl_802EDD24@ha
    addi r4, r1, 0xc
    addi r6, r3, lbl_802EDD24@l
    lwz r5, 0x0(r6)
    lwz r3, 0x4(r6)
    lwz r0, 0x8(r6)
    stw r5, 0xc(r1)
    stw r3, 0x10(r1)
    stw r0, 0x14(r1)
    lfs f0, 0xc(r7)
    stfs f0, 0xc(r1)
    lfs f0, 0x1c(r7)
    stfs f0, 0x10(r1)
    lfs f0, 0x2c(r7)
    stfs f0, 0x14(r1)
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0xcf
    bl fn_8016C288
    KartItemAudio_PlayHitConfirmSE_L_8005A620:
    lwz r0, 0x54(r1)
    lwz r31, 0x4c(r1)
    lwz r30, 0x48(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}


/* === extracted from auto_KartItemAudio_PlayTh_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ItemAlias_DestToSource();
extern void SoundMgr_PlaySE();
extern void fn_8016C288();
extern void fn_8016C488();

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int jumptable_803F9968[];
extern unsigned int lbl_802EDD24[];

/* --- function index (1 fns, .text 0x8005A638..0x8005AA04) ---
 * [  0] 0x8005A638 size:0x3CC   global KartItemAudio_PlayThrowConfirmSE
 */

/* --- forward decls --- */
asm void KartItemAudio_PlayThrowConfirmSE(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartItemAudio_PlayThrowConfirmSE[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartItemAudio_PlayThrowConfirmSE = {
    (void *)&KartItemAudio_PlayThrowConfirmSE, 0x000003CC, (void *)extab_KartItemAudio_PlayThrowConfirmSE
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartItemAudio_PlayThrowConfirmSE(void) { /* 0x8005A638 size:0x3CC */
    nofralloc
    stwu r1, -0x70(r1)
    mflr r0
    cmpwi r4, 0x115
    stw r0, 0x74(r1)
    stw r31, 0x6c(r1)
    mr r31, r3
    bge KartItemAudio_PlayThrowConfirmSE_L_8005A664
    clrlwi r3, r4, 24
    addi r4, r1, 0x8
    bl ItemAlias_DestToSource
    b KartItemAudio_PlayThrowConfirmSE_L_8005A668
    KartItemAudio_PlayThrowConfirmSE_L_8005A664:
    mr r3, r4
    KartItemAudio_PlayThrowConfirmSE_L_8005A668:
    subi r0, r3, 0xc
    cmplwi r0, 0x1c
    bgt KartItemAudio_PlayThrowConfirmSE_L_8005A9F0
    lis r3, jumptable_803F9968@ha
    slwi r0, r0, 2
    addi r3, r3, jumptable_803F9968@l
    lwzx r0, r3, r0
    mtctr r0
    bctr
    lbz r0, 0x4(r31)
    cmplwi r0, 0x1
    bne KartItemAudio_PlayThrowConfirmSE_L_8005A9F0
    li r3, 0x1
    bl fn_8016C488
    b KartItemAudio_PlayThrowConfirmSE_L_8005A9F0
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0xc6
    bl SoundMgr_PlaySE
    lbz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne KartItemAudio_PlayThrowConfirmSE_L_8005A9F0
    lwz r7, 0xc(r31)
    cmplwi r7, 0x0
    beq KartItemAudio_PlayThrowConfirmSE_L_8005A9F0
    lis r3, lbl_802EDD24@ha
    addi r4, r1, 0x54
    addi r6, r3, lbl_802EDD24@l
    lwz r5, 0x0(r6)
    lwz r3, 0x4(r6)
    lwz r0, 0x8(r6)
    stw r5, 0x54(r1)
    stw r3, 0x58(r1)
    stw r0, 0x5c(r1)
    lfs f0, 0xc(r7)
    stfs f0, 0x54(r1)
    lfs f0, 0x1c(r7)
    stfs f0, 0x58(r1)
    lfs f0, 0x2c(r7)
    stfs f0, 0x5c(r1)
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0xc6
    bl fn_8016C288
    b KartItemAudio_PlayThrowConfirmSE_L_8005A9F0
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0xa4
    bl SoundMgr_PlaySE
    lbz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne KartItemAudio_PlayThrowConfirmSE_L_8005A9F0
    lwz r7, 0xc(r31)
    cmplwi r7, 0x0
    beq KartItemAudio_PlayThrowConfirmSE_L_8005A9F0
    lis r3, lbl_802EDD24@ha
    addi r4, r1, 0x48
    addi r6, r3, lbl_802EDD24@l
    lwz r5, 0x0(r6)
    lwz r3, 0x4(r6)
    lwz r0, 0x8(r6)
    stw r5, 0x48(r1)
    stw r3, 0x4c(r1)
    stw r0, 0x50(r1)
    lfs f0, 0xc(r7)
    stfs f0, 0x48(r1)
    lfs f0, 0x1c(r7)
    stfs f0, 0x4c(r1)
    lfs f0, 0x2c(r7)
    stfs f0, 0x50(r1)
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0xa4
    bl fn_8016C288
    b KartItemAudio_PlayThrowConfirmSE_L_8005A9F0
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0xc7
    bl SoundMgr_PlaySE
    lbz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne KartItemAudio_PlayThrowConfirmSE_L_8005A9F0
    lwz r7, 0xc(r31)
    cmplwi r7, 0x0
    beq KartItemAudio_PlayThrowConfirmSE_L_8005A9F0
    lis r3, lbl_802EDD24@ha
    addi r4, r1, 0x3c
    addi r6, r3, lbl_802EDD24@l
    lwz r5, 0x0(r6)
    lwz r3, 0x4(r6)
    lwz r0, 0x8(r6)
    stw r5, 0x3c(r1)
    stw r3, 0x40(r1)
    stw r0, 0x44(r1)
    lfs f0, 0xc(r7)
    stfs f0, 0x3c(r1)
    lfs f0, 0x1c(r7)
    stfs f0, 0x40(r1)
    lfs f0, 0x2c(r7)
    stfs f0, 0x44(r1)
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0xc7
    bl fn_8016C288
    b KartItemAudio_PlayThrowConfirmSE_L_8005A9F0
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0xc7
    bl SoundMgr_PlaySE
    lbz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne KartItemAudio_PlayThrowConfirmSE_L_8005A880
    lwz r7, 0xc(r31)
    cmplwi r7, 0x0
    beq KartItemAudio_PlayThrowConfirmSE_L_8005A880
    lis r3, lbl_802EDD24@ha
    addi r4, r1, 0x30
    addi r6, r3, lbl_802EDD24@l
    lwz r5, 0x0(r6)
    lwz r3, 0x4(r6)
    lwz r0, 0x8(r6)
    stw r5, 0x30(r1)
    stw r3, 0x34(r1)
    stw r0, 0x38(r1)
    lfs f0, 0xc(r7)
    stfs f0, 0x30(r1)
    lfs f0, 0x1c(r7)
    stfs f0, 0x34(r1)
    lfs f0, 0x2c(r7)
    stfs f0, 0x38(r1)
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0xc7
    bl fn_8016C288
    KartItemAudio_PlayThrowConfirmSE_L_8005A880:
    lbz r0, 0x4(r31)
    cmplwi r0, 0x1
    bne KartItemAudio_PlayThrowConfirmSE_L_8005A9F0
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0xc5
    bl SoundMgr_PlaySE
    lbz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne KartItemAudio_PlayThrowConfirmSE_L_8005A9F0
    lwz r7, 0xc(r31)
    cmplwi r7, 0x0
    beq KartItemAudio_PlayThrowConfirmSE_L_8005A9F0
    lis r3, lbl_802EDD24@ha
    addi r4, r1, 0x24
    addi r6, r3, lbl_802EDD24@l
    lwz r5, 0x0(r6)
    lwz r3, 0x4(r6)
    lwz r0, 0x8(r6)
    stw r5, 0x24(r1)
    stw r3, 0x28(r1)
    stw r0, 0x2c(r1)
    lfs f0, 0xc(r7)
    stfs f0, 0x24(r1)
    lfs f0, 0x1c(r7)
    stfs f0, 0x28(r1)
    lfs f0, 0x2c(r7)
    stfs f0, 0x2c(r1)
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0xc5
    bl fn_8016C288
    b KartItemAudio_PlayThrowConfirmSE_L_8005A9F0
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0xa1
    bl SoundMgr_PlaySE
    lbz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne KartItemAudio_PlayThrowConfirmSE_L_8005A9F0
    lwz r7, 0xc(r31)
    cmplwi r7, 0x0
    beq KartItemAudio_PlayThrowConfirmSE_L_8005A9F0
    lis r3, lbl_802EDD24@ha
    addi r4, r1, 0x18
    addi r6, r3, lbl_802EDD24@l
    lwz r5, 0x0(r6)
    lwz r3, 0x4(r6)
    lwz r0, 0x8(r6)
    stw r5, 0x18(r1)
    stw r3, 0x1c(r1)
    stw r0, 0x20(r1)
    lfs f0, 0xc(r7)
    stfs f0, 0x18(r1)
    lfs f0, 0x1c(r7)
    stfs f0, 0x1c(r1)
    lfs f0, 0x2c(r7)
    stfs f0, 0x20(r1)
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0xa1
    bl fn_8016C288
    b KartItemAudio_PlayThrowConfirmSE_L_8005A9F0
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0x64
    bl SoundMgr_PlaySE
    lbz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne KartItemAudio_PlayThrowConfirmSE_L_8005A9F0
    lwz r7, 0xc(r31)
    cmplwi r7, 0x0
    beq KartItemAudio_PlayThrowConfirmSE_L_8005A9F0
    lis r3, lbl_802EDD24@ha
    addi r4, r1, 0xc
    addi r6, r3, lbl_802EDD24@l
    lwz r5, 0x0(r6)
    lwz r3, 0x4(r6)
    lwz r0, 0x8(r6)
    stw r5, 0xc(r1)
    stw r3, 0x10(r1)
    stw r0, 0x14(r1)
    lfs f0, 0xc(r7)
    stfs f0, 0xc(r1)
    lfs f0, 0x1c(r7)
    stfs f0, 0x10(r1)
    lfs f0, 0x2c(r7)
    stfs f0, 0x14(r1)
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0x64
    bl fn_8016C288
    KartItemAudio_PlayThrowConfirmSE_L_8005A9F0:
    lwz r0, 0x74(r1)
    lwz r31, 0x6c(r1)
    mtlr r0
    addi r1, r1, 0x70
    blr
}

