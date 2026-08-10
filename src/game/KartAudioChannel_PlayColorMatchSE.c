/* === extracted from auto_KartAudioChannel_Pla_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void SoundMgr_PlaySE();
extern void Terrain_ApplyCup2FlagPatch();
extern void fn_8016C288();
extern void fn_8016C394();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D2940;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_802EDCBC[];
extern unsigned int lbl_802EDD24[];

/* --- function index (1 fns, .text 0x8005967C..0x8005982C) ---
 * [  0] 0x8005967C size:0x1B0   global KartAudioChannel_PlayColorMatchSE
 */

/* --- forward decls --- */
asm void KartAudioChannel_PlayColorMatchSE(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartAudioChannel_PlayColorMatchSE[8] = {
    0x18, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartAudioChannel_PlayColorMatchSE = {
    (void *)&KartAudioChannel_PlayColorMatchSE, 0x000001B0, (void *)extab_KartAudioChannel_PlayColorMatchSE
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartAudioChannel_PlayColorMatchSE(void) { /* 0x8005967C size:0x1B0 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stw r31, 0x2c(r1)
    mr r31, r3
    stw r30, 0x28(r1)
    stw r29, 0x24(r1)
    mr r29, r5
    lbz r0, 0x5(r3)
    cmplwi r0, 0x0
    beq KartAudioChannel_PlayColorMatchSE_L_80059810
    lfs f0, lbl_806D2940(r2)
    fcmpo cr0, f1, f0
    cror eq, lt, eq
    bne KartAudioChannel_PlayColorMatchSE_L_800596C0
    li r4, 0x0
    li r29, 0x0
    KartAudioChannel_PlayColorMatchSE_L_800596C0:
    mr r3, r4
    bl Terrain_ApplyCup2FlagPatch
    mr r30, r3
    mr r3, r29
    bl Terrain_ApplyCup2FlagPatch
    lis r4, lbl_802EDCBC@ha
    li r0, 0xd
    addi r5, r4, lbl_802EDCBC@l
    li r6, 0xc
    li r7, 0xc
    li r8, 0x0
    mr r4, r5
    mtctr r0
    KartAudioChannel_PlayColorMatchSE_L_800596F4:
    lwz r0, 0x0(r4)
    cmplw r30, r0
    bne KartAudioChannel_PlayColorMatchSE_L_80059708
    mr r6, r8
    b KartAudioChannel_PlayColorMatchSE_L_80059714
    KartAudioChannel_PlayColorMatchSE_L_80059708:
    addi r4, r4, 0x8
    addi r8, r8, 0x1
    bdnz KartAudioChannel_PlayColorMatchSE_L_800596F4
    KartAudioChannel_PlayColorMatchSE_L_80059714:
    li r0, 0xd
    li r4, 0x0
    mtctr r0
    KartAudioChannel_PlayColorMatchSE_L_80059720:
    lwz r0, 0x0(r5)
    cmplw r3, r0
    bne KartAudioChannel_PlayColorMatchSE_L_80059734
    mr r7, r4
    b KartAudioChannel_PlayColorMatchSE_L_80059740
    KartAudioChannel_PlayColorMatchSE_L_80059734:
    addi r5, r5, 0x8
    addi r4, r4, 0x1
    bdnz KartAudioChannel_PlayColorMatchSE_L_80059720
    KartAudioChannel_PlayColorMatchSE_L_80059740:
    cmpw r6, r7
    mr r0, r7
    bge KartAudioChannel_PlayColorMatchSE_L_80059750
    mr r0, r6
    KartAudioChannel_PlayColorMatchSE_L_80059750:
    lis r3, lbl_802EDCBC@ha
    slwi r0, r0, 3
    addi r3, r3, lbl_802EDCBC@l
    lwz r4, 0x34(r31)
    add r30, r3, r0
    lwzu r0, 0x4(r30)
    cmpw r4, r0
    beq KartAudioChannel_PlayColorMatchSE_L_80059810
    cmpwi r4, 0x0
    blt KartAudioChannel_PlayColorMatchSE_L_80059788
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    or r3, r4, r0
    bl fn_8016C394
    KartAudioChannel_PlayColorMatchSE_L_80059788:
    lwz r0, 0x0(r30)
    stw r0, 0x34(r31)
    lwz r30, 0x34(r31)
    cmpwi r30, 0x0
    blt KartAudioChannel_PlayColorMatchSE_L_80059810
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    or r3, r30, r0
    bl SoundMgr_PlaySE
    lbz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne KartAudioChannel_PlayColorMatchSE_L_80059810
    lwz r7, 0xc(r31)
    cmplwi r7, 0x0
    beq KartAudioChannel_PlayColorMatchSE_L_80059810
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
    lwz r0, 0x8(r31)
    clrlslwi r0, r0, 28, 27
    or r3, r30, r0
    bl fn_8016C288
    KartAudioChannel_PlayColorMatchSE_L_80059810:
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}
