/* === extracted from auto_Jyugemu_Flag_Tick_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Archive_GetRootJObj();
extern void KartDriver_GetKartRootMtx();
extern void Object_DriveAnimMatrix();
extern void __assert();
extern void clNormal3D_Exec();
extern void fn_802D20AC();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D3070;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80311DB0[];

/* --- function index (1 fns, .text 0x80080748..0x80080A14) ---
 * [  0] 0x80080748 size:0x2CC   global Jyugemu_Flag_Tick
 */

/* --- forward decls --- */
asm void Jyugemu_Flag_Tick(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_Jyugemu_Flag_Tick[8] = {
    0x20, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Jyugemu_Flag_Tick = {
    (void *)&Jyugemu_Flag_Tick, 0x000002CC, (void *)extab_Jyugemu_Flag_Tick
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void Jyugemu_Flag_Tick(void) { /* 0x80080748 size:0x2CC */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stfd f31, 0x20(r1)
    psq_st f31, 0x28(r1), 0, 0
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    stw r28, 0x10(r1)
    mr r31, r3
    lwz r0, 0x0(r3)
    cmplwi r0, 0x0
    bne Jyugemu_Flag_Tick_L_80080784
    li r3, 0x0
    b Jyugemu_Flag_Tick_L_800809EC
    Jyugemu_Flag_Tick_L_80080784:
    lwz r3, 0x8(r31)
    cmplwi r3, 0x0
    bne Jyugemu_Flag_Tick_L_80080798
    li r3, 0x0
    b Jyugemu_Flag_Tick_L_800809EC
    Jyugemu_Flag_Tick_L_80080798:
    lwz r29, 0x4(r31)
    bl KartDriver_GetKartRootMtx
    mr r30, r3
    lfs f1, 0x14(r29)
    lfs f0, 0xc(r3)
    lwz r3, 0x0(r31)
    fadds f31, f1, f0
    bl Archive_GetRootJObj
    mr. r28, r3
    bne Jyugemu_Flag_Tick_L_800807D0
    addi r3, r2, -0x7200  /* lbl_806D3060 */
    li r4, 0x3b8
    addi r5, r2, -0x71F8  /* lbl_806D3068 */
    bl __assert
    Jyugemu_Flag_Tick_L_800807D0:
    stfs f31, 0x38(r28)
    lwz r0, 0x14(r28)
    rlwinm. r0, r0, 0, 6, 6
    bne Jyugemu_Flag_Tick_L_80080828
    cmplwi r28, 0x0
    beq Jyugemu_Flag_Tick_L_80080828
    bne Jyugemu_Flag_Tick_L_800807FC
    addi r3, r2, -0x7200  /* lbl_806D3060 */
    li r4, 0x25d
    addi r5, r2, -0x71F8  /* lbl_806D3068 */
    bl __assert
    Jyugemu_Flag_Tick_L_800807FC:
    lwz r4, 0x14(r28)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne Jyugemu_Flag_Tick_L_80080818
    rlwinm. r0, r4, 0, 25, 25
    beq Jyugemu_Flag_Tick_L_80080818
    li r3, 0x1
    Jyugemu_Flag_Tick_L_80080818:
    clrlwi. r0, r3, 24
    bne Jyugemu_Flag_Tick_L_80080828
    mr r3, r28
    bl fn_802D20AC
    Jyugemu_Flag_Tick_L_80080828:
    lfs f1, 0x18(r29)
    lfs f0, 0x1c(r30)
    lwz r3, 0x0(r31)
    fadds f31, f1, f0
    bl Archive_GetRootJObj
    mr. r28, r3
    bne Jyugemu_Flag_Tick_L_80080854
    addi r3, r2, -0x7200  /* lbl_806D3060 */
    li r4, 0x3c6
    addi r5, r2, -0x71F8  /* lbl_806D3068 */
    bl __assert
    Jyugemu_Flag_Tick_L_80080854:
    stfs f31, 0x3c(r28)
    lwz r0, 0x14(r28)
    rlwinm. r0, r0, 0, 6, 6
    bne Jyugemu_Flag_Tick_L_800808AC
    cmplwi r28, 0x0
    beq Jyugemu_Flag_Tick_L_800808AC
    bne Jyugemu_Flag_Tick_L_80080880
    addi r3, r2, -0x7200  /* lbl_806D3060 */
    li r4, 0x25d
    addi r5, r2, -0x71F8  /* lbl_806D3068 */
    bl __assert
    Jyugemu_Flag_Tick_L_80080880:
    lwz r4, 0x14(r28)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne Jyugemu_Flag_Tick_L_8008089C
    rlwinm. r0, r4, 0, 25, 25
    beq Jyugemu_Flag_Tick_L_8008089C
    li r3, 0x1
    Jyugemu_Flag_Tick_L_8008089C:
    clrlwi. r0, r3, 24
    bne Jyugemu_Flag_Tick_L_800808AC
    mr r3, r28
    bl fn_802D20AC
    Jyugemu_Flag_Tick_L_800808AC:
    lfs f1, 0x1c(r29)
    lfs f0, 0x2c(r30)
    lwz r3, 0x0(r31)
    fadds f31, f1, f0
    bl Archive_GetRootJObj
    mr. r28, r3
    bne Jyugemu_Flag_Tick_L_800808D8
    addi r3, r2, -0x7200  /* lbl_806D3060 */
    li r4, 0x3d4
    addi r5, r2, -0x71F8  /* lbl_806D3068 */
    bl __assert
    Jyugemu_Flag_Tick_L_800808D8:
    stfs f31, 0x40(r28)
    lwz r0, 0x14(r28)
    rlwinm. r0, r0, 0, 6, 6
    bne Jyugemu_Flag_Tick_L_80080930
    cmplwi r28, 0x0
    beq Jyugemu_Flag_Tick_L_80080930
    bne Jyugemu_Flag_Tick_L_80080904
    addi r3, r2, -0x7200  /* lbl_806D3060 */
    li r4, 0x25d
    addi r5, r2, -0x71F8  /* lbl_806D3068 */
    bl __assert
    Jyugemu_Flag_Tick_L_80080904:
    lwz r4, 0x14(r28)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne Jyugemu_Flag_Tick_L_80080920
    rlwinm. r0, r4, 0, 25, 25
    beq Jyugemu_Flag_Tick_L_80080920
    li r3, 0x1
    Jyugemu_Flag_Tick_L_80080920:
    clrlwi. r0, r3, 24
    bne Jyugemu_Flag_Tick_L_80080930
    mr r3, r28
    bl fn_802D20AC
    Jyugemu_Flag_Tick_L_80080930:
    lwz r3, 0x4(r31)
    lfs f1, lbl_806D3070(r2)
    lfs f0, 0x20(r3)
    lwz r3, 0x0(r31)
    fmuls f31, f1, f0
    bl Archive_GetRootJObj
    mr. r28, r3
    bne Jyugemu_Flag_Tick_L_80080960
    addi r3, r2, -0x7200  /* lbl_806D3060 */
    li r4, 0x2b8
    addi r5, r2, -0x71F8  /* lbl_806D3068 */
    bl __assert
    Jyugemu_Flag_Tick_L_80080960:
    lwz r0, 0x14(r28)
    rlwinm. r0, r0, 0, 14, 14
    beq Jyugemu_Flag_Tick_L_80080980
    lis r4, lbl_80311DB0@ha
    addi r3, r2, -0x7200  /* lbl_806D3060 */
    addi r5, r4, lbl_80311DB0@l
    li r4, 0x2b9
    bl __assert
    Jyugemu_Flag_Tick_L_80080980:
    stfs f31, 0x20(r28)
    lwz r0, 0x14(r28)
    rlwinm. r0, r0, 0, 6, 6
    bne Jyugemu_Flag_Tick_L_800809D8
    cmplwi r28, 0x0
    beq Jyugemu_Flag_Tick_L_800809D8
    bne Jyugemu_Flag_Tick_L_800809AC
    addi r3, r2, -0x7200  /* lbl_806D3060 */
    li r4, 0x25d
    addi r5, r2, -0x71F8  /* lbl_806D3068 */
    bl __assert
    Jyugemu_Flag_Tick_L_800809AC:
    lwz r4, 0x14(r28)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne Jyugemu_Flag_Tick_L_800809C8
    rlwinm. r0, r4, 0, 25, 25
    beq Jyugemu_Flag_Tick_L_800809C8
    li r3, 0x1
    Jyugemu_Flag_Tick_L_800809C8:
    clrlwi. r0, r3, 24
    bne Jyugemu_Flag_Tick_L_800809D8
    mr r3, r28
    bl fn_802D20AC
    Jyugemu_Flag_Tick_L_800809D8:
    lwz r3, 0x0(r31)
    bl clNormal3D_Exec
    lwz r3, 0x0(r31)
    bl Object_DriveAnimMatrix
    li r3, 0x1
    Jyugemu_Flag_Tick_L_800809EC:
    psq_l f31, 0x28(r1), 0, 0
    lwz r0, 0x34(r1)
    lfd f31, 0x20(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

