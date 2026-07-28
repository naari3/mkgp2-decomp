/* === extracted from auto_Tornado_HomingChildT_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Item_AdvanceTrackedHomingState();
extern void KartDriver_GetKartRootMtx();
extern void Mtx44_GetTranslation_RowMajor();
extern void SpriteSlot_Container_Free();
extern void Vec3_Add_DestFirst();
extern void Vec3_Copy();
extern void Vec3_Subtract_DestFirst();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D6260;

/* --- function index (1 fns, .text 0x800F8FD8..0x800F9148) ---
 * [  0] 0x800F8FD8 size:0x170   global Tornado_HomingChildTick
 */

/* --- forward decls --- */
asm void Tornado_HomingChildTick(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_Tornado_HomingChildTick[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Tornado_HomingChildTick = {
    (void *)&Tornado_HomingChildTick, 0x00000170, (void *)extab_Tornado_HomingChildTick
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void Tornado_HomingChildTick(void) { /* 0x800F8FD8 size:0x170 */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stw r31, 0x4c(r1)
    mr r31, r3
    stw r30, 0x48(r1)
    lbz r0, 0xc8(r3)
    extsb r0, r0
    cmpwi r0, 0x1
    beq Tornado_HomingChildTick_L_800F905C
    bge Tornado_HomingChildTick_L_800F905C
    cmpwi r0, 0x0
    bge Tornado_HomingChildTick_L_800F9010
    b Tornado_HomingChildTick_L_800F905C
    Tornado_HomingChildTick_L_800F9010:
    lwz r3, 0x184(r31)
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r1, 0x38
    bl Mtx44_GetTranslation_RowMajor
    lwz r5, 0x148(r31)
    addi r3, r31, 0x120
    addi r4, r1, 0x38
    addi r5, r5, 0xa0
    bl Vec3_Subtract_DestFirst
    lwz r4, 0x148(r31)
    addi r3, r31, 0x12c
    addi r4, r4, 0xa0
    bl Vec3_Copy
    li r0, 0x0
    stb r0, 0xec(r31)
    lbz r3, 0xc8(r31)
    addi r0, r3, 0x1
    stb r0, 0xc8(r31)
    Tornado_HomingChildTick_L_800F905C:
    lwz r3, 0x184(r31)
    li r4, 0x0
    lis r0, 0x100
    lwz r30, 0x304(r3)
    lwz r3, 0x10(r30)
    lwz r5, 0x14(r30)
    and r0, r3, r0
    and r3, r5, r4
    xor r3, r3, r4
    xor r0, r0, r4
    or. r0, r3, r0
    bne Tornado_HomingChildTick_L_800F9094
    li r0, 0x1
    stb r0, 0xec(r31)
    Tornado_HomingChildTick_L_800F9094:
    addi r3, r1, 0x2c
    addi r4, r31, 0x120
    bl Vec3_Copy
    lwz r3, 0x148(r31)
    addi r4, r31, 0x120
    lfs f1, lbl_806D6260(r2)
    bl Item_AdvanceTrackedHomingState
    cmpwi r3, 0x0
    beq Tornado_HomingChildTick_L_800F90C0
    li r0, 0x1
    stb r0, 0xec(r31)
    Tornado_HomingChildTick_L_800F90C0:
    addi r3, r1, 0x20
    addi r4, r31, 0x120
    addi r5, r1, 0x2c
    bl Vec3_Subtract_DestFirst
    lwz r4, 0x148(r31)
    addi r3, r1, 0x14
    addi r5, r31, 0x12c
    addi r4, r4, 0xa0
    bl Vec3_Subtract_DestFirst
    addi r3, r1, 0x8
    addi r4, r1, 0x20
    addi r5, r1, 0x14
    bl Vec3_Add_DestFirst
    lfs f2, 0x10(r1)
    addi r3, r31, 0x12c
    lfs f1, 0xc(r1)
    lfs f0, 0x8(r1)
    stfs f0, 0x30(r30)
    stfs f1, 0x34(r30)
    stfs f2, 0x38(r30)
    lwz r4, 0x148(r31)
    addi r4, r4, 0xa0
    bl Vec3_Copy
    lbz r0, 0xec(r31)
    cmplwi r0, 0x0
    beq Tornado_HomingChildTick_L_800F9130
    mr r3, r31
    bl SpriteSlot_Container_Free
    Tornado_HomingChildTick_L_800F9130:
    lwz r0, 0x54(r1)
    lwz r31, 0x4c(r1)
    lwz r30, 0x48(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}

