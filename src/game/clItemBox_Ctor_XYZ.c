/* === extracted from auto_clItemBox_Ctor_XYZ_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void fn_80270D6C();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D29A8;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int clItemBoxResponder_DebrisParticle_Dtor[];
extern unsigned int fn_8005E788[];
extern unsigned int lbl_803F9C6C[];

/* --- function index (1 fns, .text 0x8005EF38..0x8005F050) ---
 * [  0] 0x8005EF38 size:0x118   global clItemBox_Ctor_XYZ
 */

/* --- forward decls --- */
asm void clItemBox_Ctor_XYZ(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();
extern void dtor_80036E40();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; void *f7; unsigned int f8; unsigned int f9; void *f10; } extab_clItemBox_Ctor_XYZ = { 0x100A0000, 0x00000088, 0x00000020, 0x000000B0, 0x00000018, 0x00000000, 0x0A80001E, (void *)&MemoryManager_TimedFree, 0x8780001F, 0x00000008, (void *)&dtor_80036E40 };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clItemBox_Ctor_XYZ = {
    (void *)&clItemBox_Ctor_XYZ, 0x00000118, (void *)&extab_clItemBox_Ctor_XYZ
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clItemBox_Ctor_XYZ(void) { /* 0x8005EF38 size:0x118 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lfs f0, lbl_806D29A8(r2)
    li r5, 0x0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lis r3, lbl_803F9C6C@ha
    stw r30, 0x8(r1)
    addi r4, r3, lbl_803F9C6C@l
    stfs f0, 0x0(r31)
    stw r5, 0x4(r31)
    stfs f1, 0x8(r31)
    stfs f2, 0xc(r31)
    stfs f3, 0x10(r31)
    stfs f0, 0x14(r31)
    lwz r3, 0x0(r4)
    lwz r0, 0x4(r4)
    stw r3, 0x18(r31)
    stw r0, 0x1c(r31)
    lwz r0, 0x8(r4)
    stw r0, 0x20(r31)
    stw r5, 0x24(r31)
    stfs f0, 0x28(r31)
    stfs f0, 0x2c(r31)
    stfs f0, 0x30(r31)
    stw r5, 0x24(r31)
    lfs f0, 0xc(r31)
    stfs f0, 0x0(r31)
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne clItemBox_Ctor_XYZ_L_8005F034
    li r3, 0x298
    bl Alloc
    mr. r30, r3
    beq clItemBox_Ctor_XYZ_L_8005F030
    lis r3, fn_8005E788@ha
    lis r5, clItemBoxResponder_DebrisParticle_Dtor@ha
    addi r4, r3, fn_8005E788@l
    li r6, 0x2c
    addi r3, r30, 0x4
    addi r5, r5, clItemBoxResponder_DebrisParticle_Dtor@l
    li r7, 0xf
    bl fn_80270D6C
    li r0, 0x0
    lfs f0, lbl_806D29A8(r2)
    stb r0, 0x0(r30)
    stfs f0, 0x20(r30)
    stfs f0, 0x4c(r30)
    stfs f0, 0x78(r30)
    stfs f0, 0xa4(r30)
    stfs f0, 0xd0(r30)
    stfs f0, 0xfc(r30)
    stfs f0, 0x128(r30)
    stfs f0, 0x154(r30)
    stfs f0, 0x180(r30)
    stfs f0, 0x1ac(r30)
    stfs f0, 0x1d8(r30)
    stfs f0, 0x204(r30)
    stfs f0, 0x230(r30)
    stfs f0, 0x25c(r30)
    stfs f0, 0x288(r30)
    clItemBox_Ctor_XYZ_L_8005F030:
    stw r30, 0x4(r31)
    clItemBox_Ctor_XYZ_L_8005F034:
    lwz r0, 0x14(r1)
    mr r3, r31
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

