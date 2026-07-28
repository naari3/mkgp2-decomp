/* === extracted from auto_NokoNoko_InitEntity_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Atan2();
extern void Terrain_GetGroundHeight();
extern void Vec3_Dot();
extern void Vec3_Normalize();
extern void Vec3_Subtract();
extern void fn_8025E30C();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D1684;
extern unsigned int lbl_806D9324;
extern unsigned int lbl_806D9350;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80377450[];
extern unsigned int lbl_80495994[];
extern unsigned int lbl_80495D28[];

/* --- function index (1 fns, .text 0x801884E8..0x801887BC) ---
 * [  0] 0x801884E8 size:0x2D4   global NokoNoko_InitEntity
 */

/* --- forward decls --- */
asm void NokoNoko_InitEntity(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_NokoNoko_InitEntity[8] = {
    0x20, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_NokoNoko_InitEntity = {
    (void *)&NokoNoko_InitEntity, 0x000002D4, (void *)extab_NokoNoko_InitEntity
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void NokoNoko_InitEntity(void) { /* 0x801884E8 size:0x2D4 */
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    stfd f31, 0x50(r1)
    psq_st f31, 0x58(r1), 0, 0
    stw r31, 0x4c(r1)
    stw r30, 0x48(r1)
    stw r29, 0x44(r1)
    stw r28, 0x40(r1)
    mr r29, r3
    li r3, 0x0
    stw r3, 0x0(r29)
    li r0, -0x1
    lfs f0, lbl_806D9324(r2)
    lfs f1, 0x0(r4)
    stfs f1, 0x1c(r29)
    lfs f1, 0x4(r4)
    stfs f1, 0x20(r29)
    lfs f1, 0x8(r4)
    stfs f1, 0x24(r29)
    stw r0, 0x34(r29)
    stfs f0, 0x38(r29)
    stfs f0, 0x3c(r29)
    lwz r0, lbl_806D1684(r13)
    cmpwi r0, 0x40
    blt NokoNoko_InitEntity_L_80188554
    stw r3, lbl_806D1684(r13)
    NokoNoko_InitEntity_L_80188554:
    lwz r6, lbl_806D1684(r13)
    lis r5, lbl_80495994@ha
    lis r3, lbl_80495D28@ha
    lis r4, lbl_80377450@ha
    slwi r0, r6, 2
    addi r5, r5, lbl_80495994@l
    lfsx f1, r5, r0
    addi r5, r6, 0x1
    lfs f0, lbl_806D9350(r2)
    li r0, 0x0
    stw r5, lbl_806D1684(r13)
    addi r3, r3, lbl_80495D28@l
    fmuls f1, f0, f1
    lfs f0, lbl_806D9324(r2)
    addi r28, r4, lbl_80377450@l
    li r31, 0x0
    fctiwz f1, f1
    stfd f1, 0x30(r1)
    lwz r4, 0x34(r1)
    stw r4, 0x4(r29)
    stw r0, 0x8(r29)
    lwz r4, 0x4(r29)
    lwz r0, 0x8(r29)
    slwi r4, r4, 2
    mulli r0, r0, 0x14
    lwzx r4, r3, r4
    lwzx r0, r4, r0
    stw r0, 0xc(r29)
    lwz r4, 0x4(r29)
    lwz r0, 0x8(r29)
    slwi r4, r4, 2
    mulli r0, r0, 0x14
    lwzx r4, r3, r4
    add r4, r4, r0
    lwz r0, 0x4(r4)
    stw r0, 0x10(r29)
    lwz r4, 0x4(r29)
    lwz r0, 0x8(r29)
    slwi r4, r4, 2
    mulli r0, r0, 0x14
    lwzx r4, r3, r4
    add r4, r4, r0
    lwz r0, 0x8(r4)
    stw r0, 0x18(r29)
    lwz r4, 0x4(r29)
    lwz r0, 0x8(r29)
    slwi r4, r4, 2
    mulli r0, r0, 0x14
    lwzx r4, r3, r4
    add r4, r4, r0
    lfs f1, 0xc(r4)
    stfs f1, 0x2c(r29)
    lwz r4, 0x4(r29)
    lwz r0, 0x8(r29)
    slwi r4, r4, 2
    mulli r0, r0, 0x14
    lwzx r3, r3, r4
    add r3, r3, r0
    lfs f1, 0x10(r3)
    stfs f1, 0x30(r29)
    stfs f0, 0x14(r29)
    NokoNoko_InitEntity_L_80188648:
    mr r3, r28
    addi r4, r29, 0x1c
    addi r5, r1, 0x24
    bl Vec3_Subtract
    addi r3, r1, 0x24
    bl fn_8025E30C
    cmpwi r31, 0x0
    beq NokoNoko_InitEntity_L_80188670
    fcmpo cr0, f1, f31
    bge NokoNoko_InitEntity_L_80188678
    NokoNoko_InitEntity_L_80188670:
    mr r30, r31
    fmr f31, f1
    NokoNoko_InitEntity_L_80188678:
    addi r31, r31, 0x1
    cmplwi r31, 0x15
    blt NokoNoko_InitEntity_L_80188648
    mulli r4, r30, 0xc
    lis r3, lbl_80377450@ha
    addi r5, r30, 0x1
    addi r0, r3, lbl_80377450@l
    add r4, r0, r4
    cmplwi r5, 0x15
    lfs f2, 0x0(r4)
    lfs f1, 0x4(r4)
    lfs f0, 0x8(r4)
    stfs f2, 0xc(r1)
    stfs f1, 0x10(r1)
    stfs f0, 0x14(r1)
    bne NokoNoko_InitEntity_L_801886BC
    li r5, 0x0
    NokoNoko_InitEntity_L_801886BC:
    mulli r5, r5, 0xc
    lis r3, lbl_80377450@ha
    addi r0, r3, lbl_80377450@l
    add r3, r0, r5
    addi r5, r1, 0x24
    bl Vec3_Subtract
    addi r3, r1, 0x24
    mr r4, r3
    bl Vec3_Normalize
    addi r3, r29, 0x1c
    addi r4, r1, 0xc
    addi r5, r1, 0x18
    bl Vec3_Subtract
    addi r3, r1, 0x18
    addi r4, r1, 0x24
    bl Vec3_Dot
    lfs f2, 0x24(r1)
    addi r3, r1, 0x18
    lfs f0, 0xc(r1)
    mr r4, r3
    lfs f4, 0x28(r1)
    lfs f3, 0x10(r1)
    fmadds f5, f2, f1, f0
    lfs f2, 0x2c(r1)
    lfs f0, 0x14(r1)
    fmadds f3, f4, f1, f3
    stfs f5, 0xc(r1)
    fmadds f2, f2, f1, f0
    lfs f0, lbl_806D9324(r2)
    stfs f3, 0x10(r1)
    stfs f2, 0x14(r1)
    lfs f1, 0x1c(r29)
    fsubs f1, f5, f1
    stfs f0, 0x1c(r1)
    stfs f1, 0x18(r1)
    lfs f0, 0x24(r29)
    fsubs f0, f2, f0
    stfs f0, 0x20(r1)
    bl Vec3_Normalize
    lfs f1, 0x18(r1)
    lfs f2, 0x20(r1)
    bl Atan2
    frsp f0, f1
    addi r3, r29, 0x1c
    addi r4, r1, 0x8
    li r5, 0x0
    li r6, 0x0
    stfs f0, 0x28(r29)
    bl Terrain_GetGroundHeight
    clrlwi. r0, r3, 24
    beq NokoNoko_InitEntity_L_80188790
    lfs f0, 0x8(r1)
    stfs f0, 0x20(r29)
    NokoNoko_InitEntity_L_80188790:
    mr r3, r29
    psq_l f31, 0x58(r1), 0, 0
    lwz r0, 0x64(r1)
    lfd f31, 0x50(r1)
    lwz r31, 0x4c(r1)
    lwz r30, 0x48(r1)
    lwz r29, 0x44(r1)
    lwz r28, 0x40(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
}

