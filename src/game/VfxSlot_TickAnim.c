/* === extracted from auto_VfxSlot_TickAnim_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void cLNormal3DWrap_Slot_AdvanceAnimFrame();
extern void cLNormal3DWrap_Slot_SetAnimFrame();
extern void cLNormal3DWrap_Slot_SetAnimSpeed();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D4FF8;
extern unsigned int lbl_806D5000;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8041BC00[];

/* --- function index (1 fns, .text 0x800B013C..0x800B02CC) ---
 * [  0] 0x800B013C size:0x190   global VfxSlot_TickAnim
 */

/* --- forward decls --- */
asm void VfxSlot_TickAnim(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_VfxSlot_TickAnim[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_VfxSlot_TickAnim = {
    (void *)&VfxSlot_TickAnim, 0x00000190, (void *)extab_VfxSlot_TickAnim
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void VfxSlot_TickAnim(void) { /* 0x800B013C size:0x190 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    lwz r7, 0x4(r3)
    cmplwi r7, 0x0
    beq VfxSlot_TickAnim_L_800B02B8
    lbz r0, 0x8(r3)
    lis r5, lbl_8041BC00@ha
    addi r6, r5, lbl_8041BC00@l
    mulli r0, r0, 0x14
    add r5, r6, r0
    lbz r0, 0x4(r5)
    extsb r0, r0
    cmpwi r0, 0x1
    beq VfxSlot_TickAnim_L_800B01AC
    bge VfxSlot_TickAnim_L_800B02B8
    cmpwi r0, 0x0
    bge VfxSlot_TickAnim_L_800B018C
    b VfxSlot_TickAnim_L_800B02B8
    VfxSlot_TickAnim_L_800B018C:
    cmpwi r4, 0x0
    beq VfxSlot_TickAnim_L_800B02B8
    lbz r0, 0x14(r3)
    extsb. r0, r0
    beq VfxSlot_TickAnim_L_800B02B8
    mr r3, r7
    bl cLNormal3DWrap_Slot_AdvanceAnimFrame
    b VfxSlot_TickAnim_L_800B02B8
    VfxSlot_TickAnim_L_800B01AC:
    lbz r0, 0xa(r3)
    extsb r0, r0
    cmpwi r0, 0x1
    beq VfxSlot_TickAnim_L_800B0280
    bge VfxSlot_TickAnim_L_800B01CC
    cmpwi r0, 0x0
    bge VfxSlot_TickAnim_L_800B01D8
    b VfxSlot_TickAnim_L_800B0280
    VfxSlot_TickAnim_L_800B01CC:
    cmpwi r0, 0x3
    bge VfxSlot_TickAnim_L_800B0280
    b VfxSlot_TickAnim_L_800B0268
    VfxSlot_TickAnim_L_800B01D8:
    lfs f1, 0xc(r3)
    lis r0, 0x4330
    lfs f0, 0x10(r3)
    stw r0, 0x8(r1)
    fadds f0, f1, f0
    lfd f2, lbl_806D5000(r2)
    stfs f0, 0xc(r3)
    lbz r5, 0x8(r3)
    lfs f0, 0xc(r3)
    mulli r5, r5, 0x14
    add r5, r6, r5
    lwz r5, 0x8(r5)
    xoris r5, r5, 0x8000
    stw r5, 0xc(r1)
    lfd f1, 0x8(r1)
    fsubs f1, f1, f2
    fcmpo cr0, f1, f0
    cror eq, lt, eq
    bne VfxSlot_TickAnim_L_800B0280
    stw r5, 0xc(r1)
    stw r0, 0x8(r1)
    lfd f0, 0x8(r1)
    fsubs f0, f0, f2
    stfs f0, 0xc(r3)
    lbz r0, 0x8(r3)
    mulli r0, r0, 0x14
    add r5, r6, r0
    lbz r0, 0xc(r5)
    extsb. r0, r0
    beq VfxSlot_TickAnim_L_800B025C
    li r0, 0x2
    stb r0, 0xa(r3)
    b VfxSlot_TickAnim_L_800B0280
    VfxSlot_TickAnim_L_800B025C:
    li r0, 0x1
    stb r0, 0xa(r3)
    b VfxSlot_TickAnim_L_800B0280
    VfxSlot_TickAnim_L_800B0268:
    cmplwi r7, 0x0
    beq VfxSlot_TickAnim_L_800B0280
    li r0, 0x0
    lfs f0, lbl_806D4FF8(r2)
    stb r0, 0xa(r3)
    stfs f0, 0xc(r3)
    VfxSlot_TickAnim_L_800B0280:
    cmpwi r4, 0x0
    beq VfxSlot_TickAnim_L_800B02B8
    lbz r0, 0x14(r3)
    extsb. r0, r0
    beq VfxSlot_TickAnim_L_800B02B8
    lwz r31, 0x4(r3)
    lfs f1, 0xc(r3)
    mr r3, r31
    bl cLNormal3DWrap_Slot_SetAnimFrame
    lfs f1, lbl_806D4FF8(r2)
    mr r3, r31
    bl cLNormal3DWrap_Slot_SetAnimSpeed
    mr r3, r31
    bl cLNormal3DWrap_Slot_AdvanceAnimFrame
    VfxSlot_TickAnim_L_800B02B8:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
