/* === extracted from auto_NokoNoko_FindNearest_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Vec3_Subtract();
extern void fn_8025E30C();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_nokonokoHead;

/* --- function index (1 fns, .text 0x801887BC..0x801888B8) ---
 * [  0] 0x801887BC size:0xFC    global NokoNoko_FindNearest
 */

/* --- forward decls --- */
asm void NokoNoko_FindNearest(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_NokoNoko_FindNearest[8] = {
    0x20, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_NokoNoko_FindNearest = {
    (void *)&NokoNoko_FindNearest, 0x000000FC, (void *)extab_NokoNoko_FindNearest
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void NokoNoko_FindNearest(void) { /* 0x801887BC size:0xFC */
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
    mr. r28, r3
    mr r29, r4
    beq NokoNoko_FindNearest_L_801887F4
    cmplwi r29, 0x0
    bne NokoNoko_FindNearest_L_801887FC
    NokoNoko_FindNearest_L_801887F4:
    li r3, 0x0
    b NokoNoko_FindNearest_L_80188890
    NokoNoko_FindNearest_L_801887FC:
    lwz r30, g_nokonokoHead(r13)
    li r31, 0x0
    b NokoNoko_FindNearest_L_8018885C
    NokoNoko_FindNearest_L_80188808:
    lwz r0, 0xc(r30)
    cmpwi r0, 0x4
    bge NokoNoko_FindNearest_L_80188858
    mr r3, r28
    addi r4, r30, 0x1c
    addi r5, r1, 0x8
    bl Vec3_Subtract
    cmplwi r31, 0x0
    bne NokoNoko_FindNearest_L_80188840
    mr r31, r30
    addi r3, r1, 0x8
    bl fn_8025E30C
    fmr f31, f1
    b NokoNoko_FindNearest_L_80188858
    NokoNoko_FindNearest_L_80188840:
    addi r3, r1, 0x8
    bl fn_8025E30C
    fcmpo cr0, f1, f31
    bge NokoNoko_FindNearest_L_80188858
    mr r31, r30
    fmr f31, f1
    NokoNoko_FindNearest_L_80188858:
    lwz r30, 0x0(r30)
    NokoNoko_FindNearest_L_8018885C:
    cmplwi r30, 0x0
    bne NokoNoko_FindNearest_L_80188808
    cmplwi r31, 0x0
    beq NokoNoko_FindNearest_L_8018888C
    lfs f0, 0x1c(r31)
    li r3, 0x1
    stfs f0, 0x0(r29)
    lfs f0, 0x20(r31)
    stfs f0, 0x4(r29)
    lfs f0, 0x24(r31)
    stfs f0, 0x8(r29)
    b NokoNoko_FindNearest_L_80188890
    NokoNoko_FindNearest_L_8018888C:
    li r3, 0x0
    NokoNoko_FindNearest_L_80188890:
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

