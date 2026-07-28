/* === extracted from auto_NokoNoko_Render_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Archive_GetRootJObj();
extern void ObjectTree_BlendOrCopy_Timed();
extern void Object_RenderJObjTree();
extern void Object_SetColorAlphaOnly();
extern void Object_SetField8_AndDirty();
extern void Object_SetJObjPositionVec();
extern void Object_SetJObjRotationY();
extern void clNormal3D_Exec();
extern void fn_801379F0();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_nokonokoEnable;
extern unsigned int g_nokonokoHead;
extern unsigned int lbl_806D9318;
extern unsigned int lbl_806D931C;
extern unsigned int lbl_806D9320;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80677EC8[];

/* --- function index (1 fns, .text 0x80188B24..0x80188D0C) ---
 * [  0] 0x80188B24 size:0x1E8   global NokoNoko_Render
 */

/* --- forward decls --- */
asm void NokoNoko_Render(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_NokoNoko_Render[8] = {
    0x18, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_NokoNoko_Render = {
    (void *)&NokoNoko_Render, 0x000001E8, (void *)extab_NokoNoko_Render
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void NokoNoko_Render(void) { /* 0x80188B24 size:0x1E8 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    lbz r0, g_nokonokoEnable(r13)
    cmplwi r0, 0x0
    beq NokoNoko_Render_L_80188CF0
    lwz r31, g_nokonokoHead(r13)
    b NokoNoko_Render_L_80188CE8
    NokoNoko_Render_L_80188B50:
    lwz r0, 0x10(r31)
    cmpwi r0, -0x1
    beq NokoNoko_Render_L_80188CE4
    lfs f1, lbl_806D9318(r2)
    addi r3, r31, 0x1c
    bl fn_801379F0
    clrlwi. r0, r3, 24
    beq NokoNoko_Render_L_80188CE4
    lwz r0, 0x10(r31)
    lis r3, lbl_80677EC8@ha
    addi r3, r3, lbl_80677EC8@l
    lfs f1, 0x14(r31)
    slwi r0, r0, 2
    lwzx r3, r3, r0
    bl Object_SetField8_AndDirty
    lwz r0, 0x10(r31)
    lis r3, lbl_80677EC8@ha
    addi r3, r3, lbl_80677EC8@l
    slwi r0, r0, 2
    lwzx r3, r3, r0
    bl clNormal3D_Exec
    lwz r0, 0x34(r31)
    cmpwi r0, -0x1
    beq NokoNoko_Render_L_80188C58
    lis r3, lbl_80677EC8@ha
    slwi r0, r0, 2
    addi r3, r3, lbl_80677EC8@l
    lfs f1, 0x3c(r31)
    lwzx r3, r3, r0
    bl Object_SetField8_AndDirty
    lwz r0, 0x34(r31)
    lis r3, lbl_80677EC8@ha
    addi r3, r3, lbl_80677EC8@l
    slwi r0, r0, 2
    lwzx r3, r3, r0
    bl clNormal3D_Exec
    lwz r0, 0x10(r31)
    lis r3, lbl_80677EC8@ha
    addi r3, r3, lbl_80677EC8@l
    slwi r0, r0, 2
    lwzx r3, r3, r0
    bl Archive_GetRootJObj
    lwz r0, 0x10(r31)
    lis r4, lbl_80677EC8@ha
    addi r4, r4, lbl_80677EC8@l
    mr r29, r3
    slwi r0, r0, 2
    lwzx r3, r4, r0
    bl Archive_GetRootJObj
    lwz r0, 0x34(r31)
    lis r4, lbl_80677EC8@ha
    addi r4, r4, lbl_80677EC8@l
    mr r30, r3
    slwi r0, r0, 2
    lwzx r3, r4, r0
    bl Archive_GetRootJObj
    lwz r0, 0x10(r31)
    lis r5, lbl_80677EC8@ha
    mr r4, r3
    lfs f1, 0x38(r31)
    addi r3, r5, lbl_80677EC8@l
    slwi r0, r0, 2
    lwzx r3, r3, r0
    mr r5, r30
    mr r6, r29
    bl ObjectTree_BlendOrCopy_Timed
    NokoNoko_Render_L_80188C58:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x3
    bne NokoNoko_Render_L_80188C90
    lfs f1, 0x14(r31)
    lis r3, lbl_80677EC8@ha
    lfs f0, lbl_806D9320(r2)
    slwi r0, r0, 2
    addi r3, r3, lbl_80677EC8@l
    lfs f2, lbl_806D931C(r2)
    fdivs f0, f1, f0
    lwzx r3, r3, r0
    li r4, 0x0
    fsubs f1, f2, f0
    bl Object_SetColorAlphaOnly
    NokoNoko_Render_L_80188C90:
    lwz r0, 0x10(r31)
    lis r3, lbl_80677EC8@ha
    addi r3, r3, lbl_80677EC8@l
    addi r4, r31, 0x1c
    slwi r0, r0, 2
    lwzx r3, r3, r0
    bl Object_SetJObjPositionVec
    lwz r0, 0x10(r31)
    lis r3, lbl_80677EC8@ha
    addi r3, r3, lbl_80677EC8@l
    lfs f1, 0x28(r31)
    slwi r0, r0, 2
    lwzx r3, r3, r0
    bl Object_SetJObjRotationY
    lwz r0, 0x10(r31)
    lis r3, lbl_80677EC8@ha
    addi r3, r3, lbl_80677EC8@l
    li r4, 0x7
    slwi r0, r0, 2
    lwzx r3, r3, r0
    bl Object_RenderJObjTree
    NokoNoko_Render_L_80188CE4:
    lwz r31, 0x0(r31)
    NokoNoko_Render_L_80188CE8:
    cmplwi r31, 0x0
    bne NokoNoko_Render_L_80188B50
    NokoNoko_Render_L_80188CF0:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

