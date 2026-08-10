/* === extracted from auto_SpriteSlot_TickAnim_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Object_DriveAnimMatrix();
extern void Object_SetField14_IfValid();
extern void Object_SetField8_10_14();
extern void clNormal3D_Exec();
extern void clNormal3D_SetScale();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5960;
extern unsigned int lbl_806D5964;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8041AC24[];

/* --- function index (1 fns, .text 0x800D6F64..0x800D717C) ---
 * [  0] 0x800D6F64 size:0x218   global SpriteSlot_TickAnim
 */

/* --- forward decls --- */
asm void SpriteSlot_TickAnim(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_SpriteSlot_TickAnim[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SpriteSlot_TickAnim = {
    (void *)&SpriteSlot_TickAnim, 0x00000218, (void *)extab_SpriteSlot_TickAnim
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void SpriteSlot_TickAnim(void) { /* 0x800D6F64 size:0x218 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    stw r30, 0x8(r1)
    mr r30, r3
    lwz r6, 0x4(r3)
    cmplwi r6, 0x0
    beq SpriteSlot_TickAnim_L_800D7164
    beq SpriteSlot_TickAnim_L_800D7150
    lbz r3, 0x8(r30)
    lis r4, lbl_8041AC24@ha
    lbz r7, 0x9(r30)
    addi r5, r4, lbl_8041AC24@l
    lbz r0, 0xa(r30)
    mulli r4, r3, 0x14
    extsb r3, r7
    addi r5, r5, 0x4
    extsb r0, r0
    lwzx r4, r5, r4
    mulli r3, r3, 0xc
    cmpwi r0, 0x1
    add r31, r4, r3
    beq SpriteSlot_TickAnim_L_800D7120
    bge SpriteSlot_TickAnim_L_800D6FD4
    cmpwi r0, 0x0
    bge SpriteSlot_TickAnim_L_800D6FE0
    b SpriteSlot_TickAnim_L_800D7120
    SpriteSlot_TickAnim_L_800D6FD4:
    cmpwi r0, 0x3
    bge SpriteSlot_TickAnim_L_800D7120
    b SpriteSlot_TickAnim_L_800D7060
    SpriteSlot_TickAnim_L_800D6FE0:
    lfs f2, 0xc(r30)
    lfs f1, 0x10(r30)
    lfs f0, lbl_806D5960(r2)
    fadds f1, f2, f1
    stfs f1, 0xc(r30)
    lfs f1, 0xc(r30)
    lfs f3, 0x8(r31)
    lfs f2, 0x4(r31)
    fcmpo cr0, f1, f0
    fsubs f2, f3, f2
    bge SpriteSlot_TickAnim_L_800D7028
    lbz r0, 0x0(r31)
    extsb. r0, r0
    bne SpriteSlot_TickAnim_L_800D7024
    fadds f0, f1, f2
    stfs f0, 0xc(r30)
    b SpriteSlot_TickAnim_L_800D7028
    SpriteSlot_TickAnim_L_800D7024:
    stfs f0, 0xc(r30)
    SpriteSlot_TickAnim_L_800D7028:
    lfs f0, 0xc(r30)
    fcmpo cr0, f2, f0
    cror eq, lt, eq
    bne SpriteSlot_TickAnim_L_800D7120
    stfs f2, 0xc(r30)
    lbz r0, 0x0(r31)
    extsb. r0, r0
    bne SpriteSlot_TickAnim_L_800D7054
    li r0, 0x2
    stb r0, 0xa(r30)
    b SpriteSlot_TickAnim_L_800D7120
    SpriteSlot_TickAnim_L_800D7054:
    li r0, 0x1
    stb r0, 0xa(r30)
    b SpriteSlot_TickAnim_L_800D7120
    SpriteSlot_TickAnim_L_800D7060:
    cmplwi r6, 0x0
    beq SpriteSlot_TickAnim_L_800D7120
    stb r7, 0x9(r30)
    lfs f1, lbl_806D5960(r2)
    lbz r3, 0x8(r30)
    lbz r0, 0x9(r30)
    mulli r3, r3, 0x14
    extsb r0, r0
    mulli r0, r0, 0xc
    lwzx r3, r5, r3
    add r3, r3, r0
    lfs f0, 0x4(r3)
    lfs f2, 0x8(r3)
    fadds f1, f1, f0
    fcmpo cr0, f2, f1
    bge SpriteSlot_TickAnim_L_800D70A4
    fmr f1, f2
    SpriteSlot_TickAnim_L_800D70A4:
    li r0, 0x0
    lfs f3, lbl_806D5960(r2)
    stb r0, 0xa(r30)
    li r4, 0x0
    fmr f4, f3
    lfs f2, lbl_806D5964(r2)
    lbz r3, 0x8(r30)
    lbz r0, 0x9(r30)
    mulli r3, r3, 0x14
    extsb r0, r0
    mulli r0, r0, 0xc
    lwzx r3, r5, r3
    add r3, r3, r0
    lfs f0, 0x4(r3)
    fsubs f0, f1, f0
    stfs f0, 0xc(r30)
    lbz r3, 0x8(r30)
    lbz r0, 0x9(r30)
    mulli r7, r3, 0x14
    lfs f0, 0xc(r30)
    extsb r0, r0
    lwz r3, 0x4(r30)
    mulli r6, r0, 0xc
    lwzx r5, r5, r7
    addi r0, r6, 0x4
    lfsx f1, r5, r0
    fadds f1, f1, f0
    bl clNormal3D_SetScale
    lwz r3, 0x4(r30)
    lfs f1, lbl_806D5960(r2)
    bl Object_SetField14_IfValid
    SpriteSlot_TickAnim_L_800D7120:
    lbz r0, 0x14(r30)
    extsb. r0, r0
    beq SpriteSlot_TickAnim_L_800D7150
    lfs f1, 0x4(r31)
    lfs f0, 0xc(r30)
    lwz r3, 0x4(r30)
    fadds f1, f1, f0
    lfs f2, lbl_806D5960(r2)
    fmr f3, f1
    bl Object_SetField8_10_14
    lwz r3, 0x4(r30)
    bl clNormal3D_Exec
    SpriteSlot_TickAnim_L_800D7150:
    lbz r0, 0x14(r30)
    extsb. r0, r0
    beq SpriteSlot_TickAnim_L_800D7164
    lwz r3, 0x4(r30)
    bl Object_DriveAnimMatrix
    SpriteSlot_TickAnim_L_800D7164:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
