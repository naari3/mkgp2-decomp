/* === extracted from auto_GXChannel_PushTransf_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void GXChannel_PushChannelColors();
extern void GXLoadTexMtxImm();
extern void GX_CallDisplayList();
extern void GX_LoadPosMtxImm();
extern void GX_SetCurrentMtx();
extern void fn_8025D1B8();
extern void fn_8025D6A8();
extern void fn_8026A354();
extern void fn_802BE120();
extern void fn_802C457C();
extern void fn_802D377C();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D2FB4;

/* --- function index (1 fns, .text 0x8007D11C..0x8007D2AC) ---
 * [  0] 0x8007D11C size:0x190   global GXChannel_PushTransform
 */

/* --- forward decls --- */
asm void GXChannel_PushTransform(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_GXChannel_PushTransform[8] = {
    0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_GXChannel_PushTransform = {
    (void *)&GXChannel_PushTransform, 0x00000190, (void *)extab_GXChannel_PushTransform
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void GXChannel_PushTransform(void) { /* 0x8007D11C size:0x190 */
    nofralloc
    stwu r1, -0x80(r1)
    mflr r0
    stw r0, 0x84(r1)
    stw r31, 0x7c(r1)
    stw r30, 0x78(r1)
    stw r29, 0x74(r1)
    mr r29, r3
    lbz r0, 0xc(r3)
    cmplwi r0, 0x0
    bne GXChannel_PushTransform_L_8007D14C
    li r3, 0x0
    b GXChannel_PushTransform_L_8007D290
    GXChannel_PushTransform_L_8007D14C:
    lwz r5, 0x0(r29)
    mr r3, r4
    addi r4, r5, 0x44
    bl fn_8025D1B8
    lwz r3, 0x0(r29)
    addi r5, r1, 0x38
    lwz r4, 0x10(r29)
    bl fn_802D377C
    lwz r31, 0x0(r29)
    lwz r0, 0x14(r31)
    rlwinm. r0, r0, 0, 15, 15
    beq GXChannel_PushTransform_L_8007D184
    addi r3, r1, 0x38
    bl fn_802C457C
    GXChannel_PushTransform_L_8007D184:
    li r3, 0x0
    bl GX_SetCurrentMtx
    addi r3, r1, 0x38
    li r4, 0x0
    bl GX_LoadPosMtxImm
    lwz r0, 0x14(r31)
    li r30, 0x0
    rlwinm. r0, r0, 0, 24, 24
    beq GXChannel_PushTransform_L_8007D1AC
    lwz r30, lbl_806D2FB4(r2)
    GXChannel_PushTransform_L_8007D1AC:
    li r3, 0x0
    li r4, 0x1
    bl fn_802BE120
    cmplwi r3, 0x0
    beq GXChannel_PushTransform_L_8007D1C4
    ori r30, r30, 0x3
    GXChannel_PushTransform_L_8007D1C4:
    li r3, 0x0
    li r4, 0x2
    bl fn_802BE120
    cmplwi r3, 0x0
    beq GXChannel_PushTransform_L_8007D1DC
    ori r30, r30, 0x5
    GXChannel_PushTransform_L_8007D1DC:
    clrlwi. r0, r30, 31
    beq GXChannel_PushTransform_L_8007D234
    addi r3, r1, 0x38
    addi r4, r1, 0x8
    bl fn_8025D6A8
    cmplwi r3, 0x0
    bne GXChannel_PushTransform_L_8007D204
    addi r3, r1, 0x38
    addi r4, r1, 0x8
    bl fn_8025D1B8
    GXChannel_PushTransform_L_8007D204:
    lwz r0, 0x14(r31)
    rlwinm. r0, r0, 0, 24, 24
    beq GXChannel_PushTransform_L_8007D21C
    addi r3, r1, 0x8
    li r4, 0x0
    bl fn_8026A354
    GXChannel_PushTransform_L_8007D21C:
    rlwinm. r0, r30, 0, 29, 30
    beq GXChannel_PushTransform_L_8007D234
    addi r3, r1, 0x8
    li r4, 0x1e
    li r5, 0x0
    bl GXLoadTexMtxImm
    GXChannel_PushTransform_L_8007D234:
    lwz r3, 0x4(r29)
    lwz r3, 0x8(r3)
    lwz r3, 0x1c(r3)
    bl GXChannel_PushChannelColors
    lwz r30, 0x4(r29)
    b GXChannel_PushTransform_L_8007D288
    GXChannel_PushTransform_L_8007D24C:
    lwz r31, 0xc(r30)
    b GXChannel_PushTransform_L_8007D268
    GXChannel_PushTransform_L_8007D254:
    lhz r0, 0xe(r31)
    lwz r3, 0x10(r31)
    slwi r4, r0, 5
    bl GX_CallDisplayList
    lwz r31, 0x4(r31)
    GXChannel_PushTransform_L_8007D268:
    cmplwi r31, 0x0
    bne GXChannel_PushTransform_L_8007D254
    cmplwi r30, 0x0
    beq GXChannel_PushTransform_L_8007D280
    lwz r0, 0x4(r30)
    b GXChannel_PushTransform_L_8007D284
    GXChannel_PushTransform_L_8007D280:
    li r0, 0x0
    GXChannel_PushTransform_L_8007D284:
    mr r30, r0
    GXChannel_PushTransform_L_8007D288:
    cmplwi r30, 0x0
    bne GXChannel_PushTransform_L_8007D24C
    GXChannel_PushTransform_L_8007D290:
    lwz r0, 0x84(r1)
    lwz r31, 0x7c(r1)
    lwz r30, 0x78(r1)
    lwz r29, 0x74(r1)
    mtlr r0
    addi r1, r1, 0x80
    blr
}

