/* === extracted from auto_TornadoEffect_Ctor_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void TornadoEffect_InitDetails();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D28E0;

/* --- function index (1 fns, .text 0x80056EC0..0x80056F1C) ---
 * [  0] 0x80056EC0 size:0x5C    global TornadoEffect_Ctor
 */

/* --- forward decls --- */
asm void TornadoEffect_Ctor(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void dtor_80036E40();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; void *f6; unsigned int f7; unsigned int f8; void *f9; unsigned int f10; unsigned int f11; void *f12; } extab_TornadoEffect_Ctor = { 0x080A0000, 0x00000044, 0x00000010, 0x00000000, 0x0780001F, 0x000000EC, (void *)&dtor_80036E40, 0x0780001F, 0x000000E0, (void *)&dtor_80036E40, 0x8780001F, 0x0000005C, (void *)&dtor_80036E40 };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TornadoEffect_Ctor = {
    (void *)&TornadoEffect_Ctor, 0x0000005C, (void *)&extab_TornadoEffect_Ctor
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void TornadoEffect_Ctor(void) { /* 0x80056EC0 size:0x5C */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lfs f0, lbl_806D28E0(r2)
    stw r0, 0x14(r1)
    li r0, 0x0
    stw r31, 0xc(r1)
    mr r31, r3
    stb r4, 0x0(r3)
    mr r4, r5
    stw r6, 0x4(r3)
    stb r7, 0x8(r3)
    stw r5, 0xc(r3)
    stw r0, 0x10(r3)
    stw r0, 0x14(r3)
    stfs f0, 0x18(r3)
    stw r0, 0xa8(r3)
    bl TornadoEffect_InitDetails
    lwz r0, 0x14(r1)
    mr r3, r31
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

