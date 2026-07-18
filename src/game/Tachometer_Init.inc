/* === extracted from auto_Tachometer_Init_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void PreloadResource();
extern void ResCtrl_Init();
extern void SpriteHandle_CreateDefault();
extern void SpriteHandle_RecomputeCull();
extern void SpriteHandle_SetActiveFlag();
extern void Tachometer_UpdateDisplaySpeed();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int FLOAT_806cf25c;
extern unsigned int FLOAT_806d1468;
extern unsigned int FLOAT_806d146c;
extern unsigned int FLOAT_806d1474;
extern unsigned int g_ccClass;
extern unsigned int g_tachometer_coinCount;
extern unsigned int g_tachometer_coinTier;
extern unsigned int g_tachometer_displaySpeed;
extern unsigned int g_tachometer_isInitialized;
extern unsigned int g_tachometer_maxDisplaySpeed;
extern unsigned int lbl_806D1459;
extern unsigned int lbl_806D145C;
extern unsigned int lbl_806D4E68;
extern unsigned int lbl_806D4E78;
extern unsigned int lbl_806D4E7C;
extern unsigned int lbl_806D4E80;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80411E20[];
extern unsigned int lbl_80598A60[];
extern unsigned int lbl_805D3320[];

/* --- function index (1 fns, .text 0x800AB77C..0x800AB958) ---
 * [  0] 0x800AB77C size:0x1DC   global Tachometer_Init
 */

/* --- forward decls --- */
asm void Tachometer_Init(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void dtor_80082960();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; void *f9; unsigned int f10; void *f11; unsigned int f12; void *f13; } extab_Tachometer_Init = { 0x100A0000, 0x00000110, 0x00000020, 0x00000140, 0x00000028, 0x0000017C, 0x00000030, 0x00000000, 0x820000B8, (void *)&dtor_80082960, 0x82000060, (void *)&dtor_80082960, 0x82000008, (void *)&dtor_80082960 };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Tachometer_Init = {
    (void *)&Tachometer_Init, 0x000001DC, (void *)&extab_Tachometer_Init
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void Tachometer_Init(void) { /* 0x800AB77C size:0x1DC */
    nofralloc
    stwu r1, -0x120(r1)
    mflr r0
    stw r0, 0x124(r1)
    stw r31, 0x11c(r1)
    stw r30, 0x118(r1)
    lbz r0, g_tachometer_isInitialized(r13)
    cmplwi r0, 0x1
    bne Tachometer_Init_L_800AB7A4
    li r3, 0x0
    b Tachometer_Init_L_800AB940
    Tachometer_Init_L_800AB7A4:
    lwz r3, g_ccClass(r13)
    li r0, 0x0
    lfs f1, lbl_806D4E68(r2)
    lis r4, lbl_80598A60@ha
    cntlzw r3, r3
    lfs f3, lbl_806D4E78(r2)
    addi r5, r4, lbl_80598A60@l
    lfs f0, lbl_806D4E7C(r2)
    extrwi r4, r3, 1, 26
    lbz r5, 0x26(r5)
    li r6, 0x1
    li r3, 0x6
    neg r4, r4
    stb r6, g_tachometer_isInitialized(r13)
    andc r3, r3, r4
    lfs f2, lbl_806D4E80(r2)
    stb r5, lbl_806D1459(r13)
    stw r3, lbl_806D145C(r13)
    stw r0, g_tachometer_coinTier(r13)
    stw r0, g_tachometer_coinCount(r13)
    stfs f1, FLOAT_806d1468(r13)
    stfs f1, FLOAT_806d146c(r13)
    stfs f3, g_tachometer_maxDisplaySpeed(r13)
    stfs f1, g_tachometer_displaySpeed(r13)
    stfs f1, FLOAT_806d1474(r13)
    stfs f0, FLOAT_806cf25c(r13)
    bl Tachometer_UpdateDisplaySpeed
    lbz r0, lbl_806D1459(r13)
    lis r3, lbl_80411E20@ha
    addi r3, r3, lbl_80411E20@l
    slwi r0, r0, 2
    lwzx r3, r3, r0
    bl PreloadResource
    lbz r0, lbl_806D1459(r13)
    lis r3, lbl_80411E20@ha
    addi r3, r3, lbl_80411E20@l
    addi r30, r3, 0x10
    slwi r0, r0, 2
    lwzx r3, r30, r0
    bl PreloadResource
    lbz r0, lbl_806D1459(r13)
    lis r3, lbl_80411E20@ha
    addi r3, r3, lbl_80411E20@l
    addi r31, r3, 0xe0
    slwi r0, r0, 2
    lwzx r3, r31, r0
    bl PreloadResource
    addi r3, r1, 0xb8
    bl ResCtrl_Init
    lbz r0, lbl_806D1459(r13)
    lis r3, lbl_80411E20@ha
    addi r5, r3, lbl_80411E20@l
    addi r3, r1, 0xb8
    slwi r0, r0, 2
    li r4, 0x4
    lwzx r0, r5, r0
    stw r0, 0xb8(r1)
    bl SpriteHandle_CreateDefault
    lis r4, lbl_805D3320@ha
    addi r4, r4, lbl_805D3320@l
    stw r3, 0x4(r4)
    addi r3, r1, 0x60
    bl ResCtrl_Init
    lbz r0, lbl_806D1459(r13)
    addi r3, r1, 0x60
    li r4, 0x4
    slwi r0, r0, 2
    lwzx r0, r30, r0
    stw r0, 0x60(r1)
    bl SpriteHandle_CreateDefault
    lis r4, lbl_805D3320@ha
    stw r3, lbl_805D3320@l(r4)
    addi r3, r1, 0x8
    bl ResCtrl_Init
    lbz r0, lbl_806D1459(r13)
    lis r3, lbl_805D3320@ha
    addi r3, r3, lbl_805D3320@l
    li r30, 0x2
    slwi r0, r0, 2
    lwzx r0, r31, r0
    addi r31, r3, 0x8
    stw r0, 0x8(r1)
    Tachometer_Init_L_800AB8EC:
    addi r3, r1, 0x8
    li r4, 0x4
    bl SpriteHandle_CreateDefault
    addi r30, r30, 0x1
    stw r3, 0x0(r31)
    cmpwi r30, 0x5
    addi r31, r31, 0x4
    blt Tachometer_Init_L_800AB8EC
    lis r3, lbl_805D3320@ha
    li r30, 0x0
    addi r31, r3, lbl_805D3320@l
    Tachometer_Init_L_800AB918:
    lwz r3, 0x0(r31)
    li r4, 0x0
    bl SpriteHandle_SetActiveFlag
    lwz r3, 0x0(r31)
    bl SpriteHandle_RecomputeCull
    addi r30, r30, 0x1
    addi r31, r31, 0x4
    cmpwi r30, 0x5
    blt Tachometer_Init_L_800AB918
    li r3, 0x1
    Tachometer_Init_L_800AB940:
    lwz r0, 0x124(r1)
    lwz r31, 0x11c(r1)
    lwz r30, 0x118(r1)
    mtlr r0
    addi r1, r1, 0x120
    blr
}

