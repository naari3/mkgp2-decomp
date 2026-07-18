/* === extracted from auto_Jyugemu_Flag_Ctor_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void clNormal3D_Construct();
extern void clNormal3D_SetScale();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806CEFB8;
extern unsigned int lbl_806CEFBC;
extern unsigned int lbl_806D3074;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80311DD8[];

/* --- function index (1 fns, .text 0x80080A74..0x80080B20) ---
 * [  0] 0x80080A74 size:0xAC    global Jyugemu_Flag_Ctor
 */

/* --- forward decls --- */
asm void Jyugemu_Flag_Ctor(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_Jyugemu_Flag_Ctor = { 0x180A0000, 0x00000050, 0x00000010, 0x00000000, 0x8A80001D, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Jyugemu_Flag_Ctor = {
    (void *)&Jyugemu_Flag_Ctor, 0x000000AC, (void *)&extab_Jyugemu_Flag_Ctor
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void Jyugemu_Flag_Ctor(void) { /* 0x80080A74 size:0xAC */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    li r0, 0x0
    stw r31, 0x1c(r1)
    mr. r31, r4
    stw r30, 0x18(r1)
    mr r30, r3
    stw r29, 0x14(r1)
    stw r0, 0x0(r3)
    bne Jyugemu_Flag_Ctor_L_80080AA4
    b Jyugemu_Flag_Ctor_L_80080B04
    Jyugemu_Flag_Ctor_L_80080AA4:
    li r3, 0x5c
    bl Alloc
    mr. r29, r3
    beq Jyugemu_Flag_Ctor_L_80080AC4
    lis r4, lbl_80311DD8@ha
    li r5, 0x0
    addi r4, r4, lbl_80311DD8@l
    bl clNormal3D_Construct
    Jyugemu_Flag_Ctor_L_80080AC4:
    stw r29, 0x0(r30)
    lwz r3, 0x0(r30)
    cmplwi r3, 0x0
    bne Jyugemu_Flag_Ctor_L_80080ADC
    mr r3, r30
    b Jyugemu_Flag_Ctor_L_80080B04
    Jyugemu_Flag_Ctor_L_80080ADC:
    lfs f1, lbl_806D3074(r2)
    li r4, 0x0
    lfs f2, lbl_806CEFB8(r13)
    fmr f3, f1
    lfs f4, lbl_806CEFBC(r13)
    bl clNormal3D_SetScale
    stw r31, 0x4(r30)
    li r0, 0x0
    mr r3, r30
    stw r0, 0x8(r30)
    Jyugemu_Flag_Ctor_L_80080B04:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

