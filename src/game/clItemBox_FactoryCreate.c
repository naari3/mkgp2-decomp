/* === extracted from auto_clItemBox_FactoryCre_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void clItemBox_Ctor_GroundSnap();
extern void clItemBox_Ctor_XYZ();

/* --- function index (1 fns, .text 0x8005F5D8..0x8005F65C) ---
 * [  0] 0x8005F5D8 size:0x84    global clItemBox_FactoryCreate
 */

/* --- forward decls --- */
asm void clItemBox_FactoryCreate(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; void *f7; unsigned int f8; void *f9; } extab_clItemBox_FactoryCreate = { 0x100A0000, 0x00000040, 0x00000018, 0x00000068, 0x00000020, 0x00000000, 0x8A80001E, (void *)&MemoryManager_TimedFree, 0x8A80001E, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clItemBox_FactoryCreate = {
    (void *)&clItemBox_FactoryCreate, 0x00000084, (void *)&extab_clItemBox_FactoryCreate
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clItemBox_FactoryCreate(void) { /* 0x8005F5D8 size:0x84 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    lwz r0, 0xc(r3)
    stw r31, 0xc(r1)
    mr r31, r3
    clrlwi. r0, r0, 31
    stw r30, 0x8(r1)
    beq clItemBox_FactoryCreate_L_8005F620
    li r3, 0x34
    bl Alloc
    mr. r30, r3
    beq clItemBox_FactoryCreate_L_8005F618
    lfs f1, 0x0(r31)
    lfs f2, 0x8(r31)
    bl clItemBox_Ctor_GroundSnap
    clItemBox_FactoryCreate_L_8005F618:
    mr r3, r30
    b clItemBox_FactoryCreate_L_8005F644
    clItemBox_FactoryCreate_L_8005F620:
    li r3, 0x34
    bl Alloc
    mr. r30, r3
    beq clItemBox_FactoryCreate_L_8005F640
    lfs f1, 0x0(r31)
    lfs f2, 0x4(r31)
    lfs f3, 0x8(r31)
    bl clItemBox_Ctor_XYZ
    clItemBox_FactoryCreate_L_8005F640:
    mr r3, r30
    clItemBox_FactoryCreate_L_8005F644:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

