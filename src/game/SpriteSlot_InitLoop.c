/* === extracted from auto_SpriteSlot_InitLoop_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void GetSpawnPosition();
extern void Object_JObjUpdate_870();
extern void Object_SetField14_IfValid();
extern void clNormal3D_Construct();
extern void clNormal3D_SetScale();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5960;
extern unsigned int lbl_806D5964;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8041AC24[];

/* --- function index (1 fns, .text 0x800D717C..0x800D7308) ---
 * [  0] 0x800D717C size:0x18C   global SpriteSlot_InitLoop
 */

/* --- forward decls --- */
asm void SpriteSlot_InitLoop(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_SpriteSlot_InitLoop = { 0x180A0000, 0x0000005C, 0x00000010, 0x00000000, 0x8A80001D, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SpriteSlot_InitLoop = {
    (void *)&SpriteSlot_InitLoop, 0x0000018C, (void *)&extab_SpriteSlot_InitLoop
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void SpriteSlot_InitLoop(void) { /* 0x800D717C size:0x18C */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    li r0, 0x0
    stw r31, 0x1c(r1)
    mr r31, r3
    stw r30, 0x18(r1)
    mr r30, r4
    stw r29, 0x14(r1)
    stb r0, 0x0(r3)
    li r3, 0x5c
    stb r0, 0x1(r31)
    stb r30, 0x8(r31)
    bl Alloc
    mr. r29, r3
    beq SpriteSlot_InitLoop_L_800D71D8
    clrlwi r0, r30, 24
    lis r4, lbl_8041AC24@ha
    mulli r0, r0, 0x14
    li r5, 0x1
    addi r4, r4, lbl_8041AC24@l
    lwzx r4, r4, r0
    bl clNormal3D_Construct
    SpriteSlot_InitLoop_L_800D71D8:
    stw r29, 0x4(r31)
    li r4, 0x800
    lwz r3, 0x4(r31)
    bl Object_JObjUpdate_870
    lwz r3, 0x4(r31)
    lfs f1, lbl_806D5960(r2)
    bl Object_SetField14_IfValid
    lfs f1, lbl_806D5964(r2)
    li r0, 0x1
    addi r3, r31, 0x1c
    stfs f1, 0x10(r31)
    fmr f2, f1
    fmr f3, f1
    stb r0, 0x14(r31)
    stfs f1, 0x18(r31)
    bl GetSpawnPosition
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    beq SpriteSlot_InitLoop_L_800D72EC
    li r0, 0x0
    lis r3, lbl_8041AC24@ha
    stb r0, 0x9(r31)
    addi r3, r3, lbl_8041AC24@l
    addi r7, r3, 0x4
    lfs f1, lbl_806D5960(r2)
    lbz r3, 0x8(r31)
    lbz r0, 0x9(r31)
    mulli r3, r3, 0x14
    extsb r0, r0
    mulli r0, r0, 0xc
    lwzx r3, r7, r3
    add r3, r3, r0
    lfs f0, 0x4(r3)
    lfs f2, 0x8(r3)
    fadds f1, f1, f0
    fcmpo cr0, f2, f1
    bge SpriteSlot_InitLoop_L_800D7270
    fmr f1, f2
    SpriteSlot_InitLoop_L_800D7270:
    li r0, 0x0
    lfs f3, lbl_806D5960(r2)
    stb r0, 0xa(r31)
    li r4, 0x0
    fmr f4, f3
    lfs f2, lbl_806D5964(r2)
    lbz r3, 0x8(r31)
    lbz r0, 0x9(r31)
    mulli r3, r3, 0x14
    extsb r0, r0
    mulli r0, r0, 0xc
    lwzx r3, r7, r3
    add r3, r3, r0
    lfs f0, 0x4(r3)
    fsubs f0, f1, f0
    stfs f0, 0xc(r31)
    lbz r3, 0x8(r31)
    lbz r0, 0x9(r31)
    mulli r6, r3, 0x14
    lfs f0, 0xc(r31)
    extsb r0, r0
    lwz r3, 0x4(r31)
    mulli r5, r0, 0xc
    lwzx r6, r7, r6
    addi r0, r5, 0x4
    lfsx f1, r6, r0
    fadds f1, f1, f0
    bl clNormal3D_SetScale
    lwz r3, 0x4(r31)
    lfs f1, lbl_806D5960(r2)
    bl Object_SetField14_IfValid
    SpriteSlot_InitLoop_L_800D72EC:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

