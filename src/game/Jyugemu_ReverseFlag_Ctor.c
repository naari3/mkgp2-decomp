/* === extracted from auto_Jyugemu_ReverseFlag_text_2 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void Archive_GetRootJObj();
extern void __assert();
extern void clNormal3D_Construct();
extern void clNormal3D_SetScale();
extern void fn_8016C510();
extern void fn_802D20AC();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806CEFC0;
extern unsigned int lbl_806D3078;
extern unsigned int lbl_806D307C;
extern unsigned int lbl_806D30A4;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80311DF0[];
extern unsigned int lbl_80311E24[];

/* --- function index (1 fns, .text 0x8008100C..0x8008117C) ---
 * [  0] 0x8008100C size:0x170   global Jyugemu_ReverseFlag_Ctor
 */

/* --- forward decls --- */
asm void Jyugemu_ReverseFlag_Ctor(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_Jyugemu_ReverseFlag_Ctor = { 0x180A0000, 0x00000070, 0x00000010, 0x00000000, 0x8A80001D, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Jyugemu_ReverseFlag_Ctor = {
    (void *)&Jyugemu_ReverseFlag_Ctor, 0x00000170, (void *)&extab_Jyugemu_ReverseFlag_Ctor
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void Jyugemu_ReverseFlag_Ctor(void) { /* 0x8008100C size:0x170 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    lfs f0, lbl_806D3078(r2)
    stw r0, 0x34(r1)
    li r0, 0x1
    stw r31, 0x2c(r1)
    mr r31, r4
    stw r30, 0x28(r1)
    mr r30, r3
    li r3, 0x0
    stw r29, 0x24(r1)
    stb r0, lbl_806CEFC0(r13)
    li r0, 0xb4
    stw r3, 0x0(r30)
    li r3, 0x0
    stfs f0, 0x10(r30)
    stw r0, 0xc(r30)
    bl fn_8016C510
    li r0, 0x0
    li r3, 0x5c
    stb r0, 0x8(r30)
    bl Alloc
    mr. r29, r3
    beq Jyugemu_ReverseFlag_Ctor_L_8008107C
    lis r4, lbl_80311E24@ha
    li r5, 0x0
    addi r4, r4, lbl_80311E24@l
    bl clNormal3D_Construct
    Jyugemu_ReverseFlag_Ctor_L_8008107C:
    stw r29, 0x0(r30)
    lwz r3, 0x0(r30)
    cmplwi r3, 0x0
    bne Jyugemu_ReverseFlag_Ctor_L_80081094
    mr r3, r30
    b Jyugemu_ReverseFlag_Ctor_L_80081160
    Jyugemu_ReverseFlag_Ctor_L_80081094:
    lfs f1, lbl_806D307C(r2)
    li r4, 0x0
    lfs f2, lbl_806D3078(r2)
    fmr f3, f1
    lfs f4, lbl_806D30A4(r2)
    bl clNormal3D_SetScale
    lis r4, lbl_80311DF0@ha
    lwz r3, 0x0(r30)
    addi r6, r4, lbl_80311DF0@l
    lwz r5, 0x0(r6)
    lwz r4, 0x4(r6)
    lwz r0, 0x8(r6)
    stw r5, 0x8(r1)
    stw r4, 0xc(r1)
    stw r0, 0x10(r1)
    bl Archive_GetRootJObj
    mr. r29, r3
    bne Jyugemu_ReverseFlag_Ctor_L_800810EC
    addi r3, r2, -0x71D4  /* lbl_806D308C */
    li r4, 0x316
    addi r5, r2, -0x71CC  /* lbl_806D3094 */
    bl __assert
    Jyugemu_ReverseFlag_Ctor_L_800810EC:
    lfs f0, 0x8(r1)
    lfs f1, 0xc(r1)
    stfs f0, 0x2c(r29)
    lfs f0, 0x10(r1)
    stfs f1, 0x30(r29)
    stfs f0, 0x34(r29)
    lwz r0, 0x14(r29)
    rlwinm. r0, r0, 0, 6, 6
    bne Jyugemu_ReverseFlag_Ctor_L_80081158
    cmplwi r29, 0x0
    beq Jyugemu_ReverseFlag_Ctor_L_80081158
    bne Jyugemu_ReverseFlag_Ctor_L_8008112C
    addi r3, r2, -0x71D4  /* lbl_806D308C */
    li r4, 0x25d
    addi r5, r2, -0x71CC  /* lbl_806D3094 */
    bl __assert
    Jyugemu_ReverseFlag_Ctor_L_8008112C:
    lwz r4, 0x14(r29)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne Jyugemu_ReverseFlag_Ctor_L_80081148
    rlwinm. r0, r4, 0, 25, 25
    beq Jyugemu_ReverseFlag_Ctor_L_80081148
    li r3, 0x1
    Jyugemu_ReverseFlag_Ctor_L_80081148:
    clrlwi. r0, r3, 24
    bne Jyugemu_ReverseFlag_Ctor_L_80081158
    mr r3, r29
    bl fn_802D20AC
    Jyugemu_ReverseFlag_Ctor_L_80081158:
    stw r31, 0x4(r30)
    mr r3, r30
    Jyugemu_ReverseFlag_Ctor_L_80081160:
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

