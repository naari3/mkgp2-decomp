/* === extracted from auto_clItemBox_Draw_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void GXChannel_PushTransform();
extern void Object_GetJObjLocalMatrix();
extern void Object_SetColorAlphaOnly();
extern void Object_SetJObjPositionXYZ();
extern void Object_SetJObjRotationY();
extern void clItemBoxResponder_DrawDebris();
extern void fn_80137718();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806CEEA0;
extern unsigned int lbl_806D10B0;
extern unsigned int lbl_806D10B4;
extern unsigned int lbl_806D10BC;
extern unsigned int lbl_806D29E0;
extern unsigned int lbl_806D29F0;
extern unsigned int lbl_806D2A04;
extern unsigned int lbl_806D2A08;
extern unsigned int lbl_806D2A0C;

/* --- function index (1 fns, .text 0x8005ED18..0x8005EE24) ---
 * [  0] 0x8005ED18 size:0x10C   global clItemBox_Draw
 */

/* --- forward decls --- */
asm void clItemBox_Draw(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clItemBox_Draw[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clItemBox_Draw = {
    (void *)&clItemBox_Draw, 0x0000010C, (void *)extab_clItemBox_Draw
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clItemBox_Draw(void) { /* 0x8005ED18 size:0x10C */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    lwz r0, 0x24(r3)
    cmpwi r0, 0x3
    beq clItemBox_Draw_L_8005EE10
    lwz r0, lbl_806CEEA0(r13)
    cmpwi r0, 0x2
    bne clItemBox_Draw_L_8005ED50
    lwz r3, 0x4(r31)
    bl clItemBoxResponder_DrawDebris
    b clItemBox_Draw_L_8005EE10
    clItemBox_Draw_L_8005ED50:
    lwz r3, 0x4(r31)
    lbz r0, 0x0(r3)
    cmplwi r0, 0x1
    beq clItemBox_Draw_L_8005EE10
    lfs f1, lbl_806D2A04(r2)
    addi r3, r31, 0x8
    addi r4, r1, 0x8
    bl fn_80137718
    clrlwi. r0, r3, 24
    beq clItemBox_Draw_L_8005EE10
    lfs f1, 0x10(r1)
    lfs f0, lbl_806D2A08(r2)
    fcmpo cr0, f1, f0
    bge clItemBox_Draw_L_8005ED8C
    b clItemBox_Draw_L_8005EE10
    clItemBox_Draw_L_8005ED8C:
    lwz r3, lbl_806D10BC(r13)
    li r4, 0x0
    lfs f1, 0x30(r31)
    bl Object_SetColorAlphaOnly
    lfs f1, lbl_806D2A0C(r2)
    lfs f0, 0xc(r31)
    lwz r3, lbl_806D10BC(r13)
    fadds f2, f1, f0
    lfs f1, 0x8(r31)
    lfs f3, 0x10(r31)
    bl Object_SetJObjPositionXYZ
    lfs f1, lbl_806D29E0(r2)
    lfs f0, 0x14(r31)
    lfd f2, lbl_806D29F0(r2)
    fmuls f0, f1, f0
    lwz r3, lbl_806D10BC(r13)
    fmul f1, f2, f0
    frsp f1, f1
    bl Object_SetJObjRotationY
    lwz r0, lbl_806CEEA0(r13)
    cmpwi r0, 0x0
    bne clItemBox_Draw_L_8005EDFC
    lwz r3, lbl_806D10BC(r13)
    bl Object_GetJObjLocalMatrix
    mr r4, r3
    lwz r3, lbl_806D10B4(r13)
    bl GXChannel_PushTransform
    b clItemBox_Draw_L_8005EE10
    clItemBox_Draw_L_8005EDFC:
    lwz r3, lbl_806D10BC(r13)
    bl Object_GetJObjLocalMatrix
    mr r4, r3
    lwz r3, lbl_806D10B0(r13)
    bl GXChannel_PushTransform
    clItemBox_Draw_L_8005EE10:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

