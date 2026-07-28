/* === extracted from auto_FrameSelection_Draw_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void FlashFadeOverlay_Draw();
extern void fn_8011FAB8();
extern void fn_801A0004();
extern void fn_801A0DF0();
extern void fn_801A1128();
extern void fn_801A1174();
extern void fn_801A1280();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int DOUBLE_INT2FLOAT_MAGIC;
extern unsigned int lbl_806D9C10;
extern unsigned int lbl_806D9C14;
extern unsigned int lbl_806D9C18;
extern unsigned int lbl_806D9C1C;
extern unsigned int lbl_806D9C20;
extern unsigned int lbl_806D9C24;
extern unsigned int lbl_806D9C28;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80598A60[];

/* --- function index (1 fns, .text 0x801C569C..0x801C5890) ---
 * [  0] 0x801C569C size:0x1F4   global FrameSelection_Draw
 */

/* --- forward decls --- */
asm void FrameSelection_Draw(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_FrameSelection_Draw[8] = {
    0x18, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_FrameSelection_Draw = {
    (void *)&FrameSelection_Draw, 0x000001F4, (void *)extab_FrameSelection_Draw
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void FrameSelection_Draw(void) { /* 0x801C569C size:0x1F4 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stw r31, 0x2c(r1)
    mr r31, r3
    stw r30, 0x28(r1)
    stw r29, 0x24(r1)
    lwz r3, 0x30(r3)
    bl fn_801A0004
    bl fn_8011FAB8
    bl fn_801A1280
    lis r3, lbl_80598A60@ha
    lis r4, 0x4330
    addi r3, r3, lbl_80598A60@l
    lbz r0, 0x18(r31)
    lwz r5, 0x4c(r3)
    lwz r3, 0x48(r3)
    cmplwi r0, 0x0
    xoris r5, r5, 0x8000
    stw r4, 0x8(r1)
    xoris r0, r3, 0x8000
    lfd f1, DOUBLE_INT2FLOAT_MAGIC(r2)
    stw r5, 0xc(r1)
    lfd f0, 0x8(r1)
    stw r0, 0x14(r1)
    fsubs f5, f0, f1
    stw r4, 0x10(r1)
    lfd f0, 0x10(r1)
    fsubs f6, f0, f1
    bne FrameSelection_Draw_L_801C572C
    lwz r3, 0xac(r31)
    lfs f1, lbl_806D9C10(r2)
    lfs f2, lbl_806D9C14(r2)
    lfs f3, lbl_806D9C18(r2)
    lfs f4, lbl_806D9C1C(r2)
    bl FlashFadeOverlay_Draw
    FrameSelection_Draw_L_801C572C:
    li r29, 0x0
    mr r30, r31
    FrameSelection_Draw_L_801C5734:
    lwz r0, 0x4(r31)
    cmpw r29, r0
    beq FrameSelection_Draw_L_801C5748
    lwz r3, 0x50(r30)
    bl fn_801A0004
    FrameSelection_Draw_L_801C5748:
    addi r29, r29, 0x1
    addi r30, r30, 0x4
    cmpwi r29, 0xb
    blt FrameSelection_Draw_L_801C5734
    lwz r3, 0x34(r31)
    bl fn_801A0004
    lwz r0, 0x4(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x7c(r3)
    bl fn_801A0004
    lwz r0, 0x4(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x50(r3)
    bl fn_801A0004
    li r3, 0x18dd
    li r4, 0x5
    li r5, 0x0
    li r6, 0x0
    li r7, 0x0
    bl fn_801A1174
    lfs f1, lbl_806D9C20(r2)
    lfs f2, lbl_806D9C24(r2)
    bl fn_801A1128
    bl fn_801A0DF0
    lwz r0, 0x24(r31)
    cmpwi r0, 0x0
    bne FrameSelection_Draw_L_801C5824
    lbz r0, 0xc(r31)
    cmplwi r0, 0x0
    bne FrameSelection_Draw_L_801C5824
    lwz r0, 0x20(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x40(r3)
    cmplwi r3, 0x0
    beq FrameSelection_Draw_L_801C57E4
    bl fn_801A0004
    FrameSelection_Draw_L_801C57E4:
    lwz r3, 0x38(r31)
    cmplwi r3, 0x0
    beq FrameSelection_Draw_L_801C57F4
    bl fn_801A0004
    FrameSelection_Draw_L_801C57F4:
    lwz r3, 0x3c(r31)
    cmplwi r3, 0x0
    beq FrameSelection_Draw_L_801C5804
    bl fn_801A0004
    FrameSelection_Draw_L_801C5804:
    lwz r3, 0x48(r31)
    cmplwi r3, 0x0
    beq FrameSelection_Draw_L_801C5814
    bl fn_801A0004
    FrameSelection_Draw_L_801C5814:
    lwz r3, 0x4c(r31)
    cmplwi r3, 0x0
    beq FrameSelection_Draw_L_801C5824
    bl fn_801A0004
    FrameSelection_Draw_L_801C5824:
    lwz r0, 0x24(r31)
    cmpwi r0, 0x0
    beq FrameSelection_Draw_L_801C5840
    lwz r3, 0xa8(r31)
    cmplwi r3, 0x0
    beq FrameSelection_Draw_L_801C5840
    bl fn_801A0004
    FrameSelection_Draw_L_801C5840:
    lbz r0, 0x18(r31)
    cmplwi r0, 0x0
    beq FrameSelection_Draw_L_801C5874
    li r3, 0x50d
    li r4, 0x5
    li r5, 0x0
    li r6, 0x0
    li r7, 0x0
    bl fn_801A1174
    lfs f1, lbl_806D9C20(r2)
    lfs f2, lbl_806D9C28(r2)
    bl fn_801A1128
    bl fn_801A0DF0
    FrameSelection_Draw_L_801C5874:
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}
