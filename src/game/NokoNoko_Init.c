/* === extracted from auto_NokoNoko_Init_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void IsSpawnTableTerminator();
extern void MemoryManager_TimedFree();
extern void NokoNoko_InitEntity();
extern void OSGetTick();
extern void Object_DtorWithGXSync();
extern void Object_SetJObjScaleXYZ();
extern void clNormal3D_Construct();
extern void clNormal3D_SetScale();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_nokonokoEnable;
extern unsigned int g_nokonokoHead;
extern unsigned int lbl_806CFBD8;
extern unsigned int lbl_806D1684;
extern unsigned int lbl_806D168C;
extern unsigned int lbl_806D931C;
extern unsigned int lbl_806D9324;
extern unsigned int lbl_806D9354;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80495C28[];
extern unsigned int lbl_80495D34[];
extern unsigned int lbl_80677EC8[];
extern unsigned int lbl_80677ED8[];

/* --- function index (1 fns, .text 0x80188E9C..0x801891C4) ---
 * [  0] 0x80188E9C size:0x328   global NokoNoko_Init
 */

/* --- forward decls --- */
asm void NokoNoko_Init(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; void *f13; unsigned int f14; void *f15; unsigned int f16; void *f17; unsigned int f18; void *f19; unsigned int f20; void *f21; } extab_NokoNoko_Init = { 0x204A0000, 0x0000011C, 0x00000030, 0x00000180, 0x00000038, 0x000001D8, 0x00000040, 0x00000230, 0x00000048, 0x000002A8, 0x00000050, 0x00000000, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001C, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_NokoNoko_Init = {
    (void *)&NokoNoko_Init, 0x00000328, (void *)&extab_NokoNoko_Init
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void NokoNoko_Init(void) { /* 0x80188E9C size:0x328 */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stfd f31, 0x30(r1)
    psq_st f31, 0x38(r1), 0, 0
    stw r31, 0x2c(r1)
    stw r30, 0x28(r1)
    stw r29, 0x24(r1)
    stw r28, 0x20(r1)
    lbz r0, g_nokonokoEnable(r13)
    fmr f31, f1
    cmplwi r0, 0x0
    beq NokoNoko_Init_L_80188F24
    b NokoNoko_Init_L_80188EE8
    NokoNoko_Init_L_80188ED4:
    lwz r0, 0x0(r3)
    cmplwi r3, 0x0
    stw r0, g_nokonokoHead(r13)
    beq NokoNoko_Init_L_80188EE8
    bl MemoryManager_TimedFree
    NokoNoko_Init_L_80188EE8:
    lwz r3, g_nokonokoHead(r13)
    cmplwi r3, 0x0
    bne NokoNoko_Init_L_80188ED4
    lis r3, lbl_80677EC8@ha
    li r30, 0x0
    addi r31, r3, lbl_80677EC8@l
    NokoNoko_Init_L_80188F00:
    lwz r3, 0x0(r31)
    cmplwi r3, 0x0
    beq NokoNoko_Init_L_80188F14
    li r4, 0x1
    bl Object_DtorWithGXSync
    NokoNoko_Init_L_80188F14:
    addi r30, r30, 0x1
    addi r31, r31, 0x4
    cmpwi r30, 0x4
    blt NokoNoko_Init_L_80188F00
    NokoNoko_Init_L_80188F24:
    lis r3, lbl_80677EC8@ha
    li r0, 0x0
    addi r30, r3, lbl_80677EC8@l
    stw r0, g_nokonokoHead(r13)
    stw r0, 0x0(r30)
    stw r0, 0x4(r30)
    stw r0, 0x8(r30)
    stw r0, 0xc(r30)
    bl OSGetTick
    lis r5, 0x8000
    lis r4, lbl_80677ED8@ha
    lwz r5, 0xf8(r5)
    li r0, 0x0
    lfs f0, lbl_806D9324(r2)
    addi r31, r4, lbl_80677ED8@l
    srwi r4, r5, 2
    stb r0, g_nokonokoEnable(r13)
    divwu r4, r3, r4
    li r3, 0x5c
    stfs f0, 0x0(r31)
    stfs f0, 0x4(r31)
    stfs f0, 0x8(r31)
    stfs f0, lbl_806D168C(r13)
    slwi r0, r4, 26
    srwi r4, r4, 31
    subf r0, r4, r0
    rotlwi r0, r0, 6
    add r0, r0, r4
    stw r0, lbl_806D1684(r13)
    bl Alloc
    mr. r29, r3
    beq NokoNoko_Init_L_80188FB8
    lis r4, lbl_80495D34@ha
    li r5, 0x0
    addi r4, r4, lbl_80495D34@l
    lwz r4, 0x0(r4)
    bl clNormal3D_Construct
    NokoNoko_Init_L_80188FB8:
    lfs f1, lbl_806D9324(r2)
    lis r3, lbl_80677EC8@ha
    stw r29, lbl_80677EC8@l(r3)
    mr r3, r29
    fmr f3, f1
    lfs f2, lbl_806D931C(r2)
    fmr f4, f1
    li r4, 0x0
    bl clNormal3D_SetScale
    lfs f1, lbl_806D9354(r2)
    lis r3, lbl_80677EC8@ha
    addi r3, r3, lbl_80677EC8@l
    fmr f2, f1
    lwz r3, 0x0(r3)
    fmr f3, f1
    bl Object_SetJObjScaleXYZ
    li r3, 0x5c
    bl Alloc
    mr. r29, r3
    beq NokoNoko_Init_L_8018901C
    lis r4, lbl_80495D34@ha
    li r5, 0x0
    addi r4, r4, lbl_80495D34@l
    lwz r4, 0x4(r4)
    bl clNormal3D_Construct
    NokoNoko_Init_L_8018901C:
    lfs f1, lbl_806D9324(r2)
    mr r3, r29
    stw r29, 0x4(r30)
    li r4, 0x0
    fmr f3, f1
    lfs f2, lbl_806D931C(r2)
    fmr f4, f1
    bl clNormal3D_SetScale
    lfs f1, lbl_806D9354(r2)
    lwz r3, 0x4(r30)
    fmr f2, f1
    fmr f3, f1
    bl Object_SetJObjScaleXYZ
    li r3, 0x5c
    bl Alloc
    mr. r29, r3
    beq NokoNoko_Init_L_80189074
    lis r4, lbl_80495D34@ha
    li r5, 0x0
    addi r4, r4, lbl_80495D34@l
    lwz r4, 0x8(r4)
    bl clNormal3D_Construct
    NokoNoko_Init_L_80189074:
    lfs f1, lbl_806D9324(r2)
    mr r3, r29
    stw r29, 0x8(r30)
    li r4, 0x0
    fmr f3, f1
    lfs f2, lbl_806D931C(r2)
    fmr f4, f1
    bl clNormal3D_SetScale
    lfs f1, lbl_806D9354(r2)
    lwz r3, 0x8(r30)
    fmr f2, f1
    fmr f3, f1
    bl Object_SetJObjScaleXYZ
    li r3, 0x5c
    bl Alloc
    mr. r29, r3
    beq NokoNoko_Init_L_801890CC
    lis r4, lbl_80495D34@ha
    li r5, 0x1
    addi r4, r4, lbl_80495D34@l
    lwz r4, 0xc(r4)
    bl clNormal3D_Construct
    NokoNoko_Init_L_801890CC:
    lfs f1, lbl_806D9324(r2)
    mr r3, r29
    stw r29, 0xc(r30)
    li r4, 0x0
    fmr f3, f1
    lfs f2, lbl_806D931C(r2)
    fmr f4, f1
    bl clNormal3D_SetScale
    lfs f1, lbl_806D9354(r2)
    lwz r3, 0xc(r30)
    fmr f2, f1
    fmr f3, f1
    bl Object_SetJObjScaleXYZ
    lis r3, lbl_80495C28@ha
    li r30, 0x0
    addi r0, r3, lbl_80495C28@l
    mr r29, r0
    b NokoNoko_Init_L_80189168
    NokoNoko_Init_L_80189114:
    lfs f2, 0x0(r29)
    li r3, 0x40
    lfs f1, 0x4(r29)
    lfs f0, 0x8(r29)
    stfs f2, 0x8(r1)
    stfs f1, 0xc(r1)
    stfs f0, 0x10(r1)
    bl Alloc
    mr. r28, r3
    beq NokoNoko_Init_L_80189144
    addi r4, r1, 0x8
    bl NokoNoko_InitEntity
    NokoNoko_Init_L_80189144:
    cmplwi r28, 0x0
    beq NokoNoko_Init_L_80189164
    cmplwi r30, 0x0
    beq NokoNoko_Init_L_8018915C
    stw r28, 0x0(r30)
    b NokoNoko_Init_L_80189160
    NokoNoko_Init_L_8018915C:
    stw r28, g_nokonokoHead(r13)
    NokoNoko_Init_L_80189160:
    mr r30, r28
    NokoNoko_Init_L_80189164:
    addi r29, r29, 0x10
    NokoNoko_Init_L_80189168:
    mr r3, r29
    bl IsSpawnTableTerminator
    clrlwi. r0, r3, 24
    beq NokoNoko_Init_L_80189114
    lfs f0, lbl_806D9324(r2)
    lis r3, lbl_80677ED8@ha
    li r0, 0x1
    stfs f31, lbl_806CFBD8(r13)
    stfs f0, lbl_80677ED8@l(r3)
    stfs f0, 0x4(r31)
    stfs f0, 0x8(r31)
    stfs f0, lbl_806D168C(r13)
    stb r0, g_nokonokoEnable(r13)
    psq_l f31, 0x38(r1), 0, 0
    lwz r0, 0x44(r1)
    lfd f31, 0x30(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    lwz r28, 0x20(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}

