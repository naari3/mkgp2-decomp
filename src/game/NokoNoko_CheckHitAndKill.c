/* === extracted from auto_NokoNoko_CheckHitAnd_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Atan2();
extern void DrawEffect_SpawnWithDescriptor();
extern void SoundMgr_PlaySE();
extern void Vec3_Magnitude();
extern void Vec3_Normalize();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_nokonokoEnable;
extern unsigned int g_nokonokoHead;
extern unsigned int lbl_806D168C;
extern unsigned int lbl_806D9324;
extern unsigned int lbl_806D933C;
extern unsigned int lbl_806D934C;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80677ED8[];

/* --- function index (1 fns, .text 0x801888B8..0x80188AE4) ---
 * [  0] 0x801888B8 size:0x22C   global NokoNoko_CheckHitAndKill
 */

/* --- forward decls --- */
asm void NokoNoko_CheckHitAndKill(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_NokoNoko_CheckHitAndKill[8] = {
    0x20, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_NokoNoko_CheckHitAndKill = {
    (void *)&NokoNoko_CheckHitAndKill, 0x0000022C, (void *)extab_NokoNoko_CheckHitAndKill
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void NokoNoko_CheckHitAndKill(void) { /* 0x801888B8 size:0x22C */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stfd f31, 0x30(r1)
    psq_st f31, 0x38(r1), 0, 0
    stw r31, 0x2c(r1)
    stw r30, 0x28(r1)
    stw r29, 0x24(r1)
    stw r28, 0x20(r1)
    lbz r0, g_nokonokoEnable(r13)
    mr r28, r3
    mr r29, r4
    cmplwi r0, 0x0
    beq NokoNoko_CheckHitAndKill_L_80188ABC
    cmplwi r28, 0x0
    beq NokoNoko_CheckHitAndKill_L_80188ABC
    lfs f0, lbl_806D9324(r2)
    fcmpo cr0, f1, f0
    cror eq, lt, eq
    bne NokoNoko_CheckHitAndKill_L_8018890C
    b NokoNoko_CheckHitAndKill_L_80188ABC
    NokoNoko_CheckHitAndKill_L_8018890C:
    lfs f2, 0x0(r28)
    lis r3, lbl_80677ED8@ha
    lfs f0, lbl_806D933C(r2)
    li r31, 0x0
    stfsu f2, lbl_80677ED8@l(r3)
    fadds f31, f0, f1
    lwz r30, g_nokonokoHead(r13)
    lfs f0, 0x4(r28)
    stfs f0, 0x4(r3)
    lfs f0, 0x8(r28)
    stfs f0, 0x8(r3)
    stfs f1, lbl_806D168C(r13)
    b NokoNoko_CheckHitAndKill_L_80188AB0
    NokoNoko_CheckHitAndKill_L_80188940:
    lwz r0, 0xc(r30)
    cmpwi r0, 0x4
    blt NokoNoko_CheckHitAndKill_L_80188954
    li r0, 0x0
    b NokoNoko_CheckHitAndKill_L_80188A9C
    NokoNoko_CheckHitAndKill_L_80188954:
    lfs f2, 0x0(r28)
    addi r3, r1, 0x8
    lfs f0, 0x1c(r30)
    lfs f1, lbl_806D933C(r2)
    fsubs f0, f2, f0
    stfs f0, 0x8(r1)
    lfs f0, 0x20(r30)
    lfs f2, 0x4(r28)
    fadds f0, f1, f0
    fsubs f0, f2, f0
    stfs f0, 0xc(r1)
    lfs f1, 0x8(r28)
    lfs f0, 0x24(r30)
    fsubs f0, f1, f0
    stfs f0, 0x10(r1)
    bl Vec3_Magnitude
    fcmpo cr0, f1, f31
    bge NokoNoko_CheckHitAndKill_L_80188A98
    addi r3, r1, 0x8
    mr r4, r3
    bl Vec3_Normalize
    lfs f1, 0x8(r1)
    lfs f0, 0x0(r28)
    fnmsubs f0, f1, f31, f0
    stfs f0, 0x1c(r30)
    lfs f1, 0xc(r1)
    lfs f0, 0x4(r28)
    fnmsubs f0, f1, f31, f0
    stfs f0, 0x20(r30)
    lfs f1, 0x10(r1)
    lfs f0, 0x8(r28)
    fnmsubs f0, f1, f31, f0
    stfs f0, 0x24(r30)
    lfs f1, 0x8(r1)
    lfs f2, 0x10(r1)
    bl Atan2
    frsp f0, f1
    li r3, 0xcb
    stfs f0, 0x28(r30)
    bl SoundMgr_PlaySE
    lfs f1, 0x1c(r30)
    addi r4, r1, 0x14
    lfs f0, lbl_806D934C(r2)
    li r3, 0x2
    stfs f1, 0x8(r1)
    lfs f1, 0x20(r30)
    lwz r6, 0x8(r1)
    stfs f1, 0xc(r1)
    fadds f0, f1, f0
    lfs f1, 0x24(r30)
    stfs f1, 0x10(r1)
    stfs f0, 0xc(r1)
    lwz r0, 0x10(r1)
    lwz r5, 0xc(r1)
    stw r6, 0x14(r1)
    stw r5, 0x18(r1)
    stw r0, 0x1c(r1)
    bl DrawEffect_SpawnWithDescriptor
    li r3, 0x4
    li r0, 0x3
    stw r3, 0xc(r30)
    cmplwi r29, 0x0
    lfs f0, lbl_806D9324(r2)
    stw r0, 0x10(r30)
    stfs f0, 0x14(r30)
    stfs f0, 0x2c(r30)
    stfs f0, 0x30(r30)
    lwz r0, 0x10(r30)
    stw r0, 0x34(r30)
    stfs f0, 0x38(r30)
    lfs f0, 0x14(r30)
    stfs f0, 0x3c(r30)
    beq NokoNoko_CheckHitAndKill_L_80188A90
    lfs f0, 0x8(r1)
    stfs f0, 0x0(r29)
    lfs f0, 0xc(r1)
    stfs f0, 0x4(r29)
    lfs f0, 0x10(r1)
    stfs f0, 0x8(r29)
    NokoNoko_CheckHitAndKill_L_80188A90:
    li r0, 0x1
    b NokoNoko_CheckHitAndKill_L_80188A9C
    NokoNoko_CheckHitAndKill_L_80188A98:
    li r0, 0x0
    NokoNoko_CheckHitAndKill_L_80188A9C:
    clrlwi r0, r0, 24
    cmplwi r0, 0x1
    bne NokoNoko_CheckHitAndKill_L_80188AAC
    li r31, 0x1
    NokoNoko_CheckHitAndKill_L_80188AAC:
    lwz r30, 0x0(r30)
    NokoNoko_CheckHitAndKill_L_80188AB0:
    cmplwi r30, 0x0
    bne NokoNoko_CheckHitAndKill_L_80188940
    mr r3, r31
    NokoNoko_CheckHitAndKill_L_80188ABC:
    psq_l f31, 0x38(r1), 0, 0
    lwz r0, 0x44(r1)
    lfd f31, 0x30(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    lwz r28, 0x20(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}

