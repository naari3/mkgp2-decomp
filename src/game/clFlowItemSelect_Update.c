/* === extracted from auto_clFlowItemSelect_Upd_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ItemDisplay_GetOrCreate();
extern void ItemDisplay_Update();
extern void Item_GetDescriptorField0();
extern void Item_GetDescriptorField8();
extern void Item_GetDescriptorFieldC();
extern void Rand15();
extern void RumbleUpdate();
extern void SetScreenBrightness();
extern void SpriteAnimParamBlock_Reload();
extern void SpriteAnimParamBlock_SetKey();
extern void SpriteGroup_CreateOrInit();
extern void SpriteHandle_RecomputeCull();
extern void SpriteHandle_SetActiveFlag();
extern void SpriteHandle_SetCornerAlpha();
extern void Sprite_AdvanceAnim();
extern void UI_PlaySeDecide();
extern void fn_801699D8();
extern void fn_8019FF6C();
extern void fn_801B7EF8();
extern void fn_801CB818();
extern void fn_8023CDA8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D9DB0;
extern unsigned int lbl_806D9DBC;
extern unsigned int lbl_806D9DC8;
extern unsigned int lbl_806D9DD0;
extern unsigned int lbl_806D9DD4;
extern unsigned int lbl_806D9DD8;
extern unsigned int lbl_806D9DDC;
extern unsigned int lbl_806D9DE0;
extern unsigned int lbl_806D9DE4;
extern unsigned int lbl_806D9DE8;
extern unsigned int lbl_806D9DEC;
extern unsigned int lbl_806D9DF0;
extern unsigned int lbl_806D9DF4;
extern unsigned int lbl_806D9DF8;

/* --- function index (1 fns, .text 0x801CBD58..0x801CC104) ---
 * [  0] 0x801CBD58 size:0x3AC   global clFlowItemSelect_Update
 */

/* --- forward decls --- */
asm void clFlowItemSelect_Update(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clFlowItemSelect_Update[8] = {
    0x20, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowItemSelect_Update = {
    (void *)&clFlowItemSelect_Update, 0x000003AC, (void *)extab_clFlowItemSelect_Update
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clFlowItemSelect_Update(void) { /* 0x801CBD58 size:0x3AC */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stw r31, 0x2c(r1)
    stw r30, 0x28(r1)
    stw r29, 0x24(r1)
    mr r29, r3
    stw r28, 0x20(r1)
    bl RumbleUpdate
    lwz r3, 0x18(r29)
    addi r0, r3, 0x1
    stw r0, 0x18(r29)
    lwz r3, 0x10(r29)
    cmpwi r3, 0xf
    bgt clFlowItemSelect_Update_L_801CBF1C
    addi r0, r3, 0x1
    cmpwi r0, 0x9
    stw r0, 0x10(r29)
    blt clFlowItemSelect_Update_L_801CBE00
    lwz r3, 0x94(r29)
    li r4, 0x1
    bl SpriteHandle_SetActiveFlag
    lwz r3, 0x10(r29)
    lis r0, 0x4330
    stw r0, 0x8(r1)
    xoris r0, r3, 0x8000
    lfd f3, lbl_806D9DC8(r2)
    stw r0, 0xc(r1)
    lfs f1, lbl_806D9DD0(r2)
    lfd f2, 0x8(r1)
    lfs f0, lbl_806D9DD4(r2)
    fsubs f2, f2, f3
    lfs f3, lbl_806D9DBC(r2)
    lwz r3, 0x94(r29)
    fsubs f1, f2, f1
    fdivs f0, f1, f0
    fmuls f0, f3, f0
    fctiwz f0, f0
    stfd f0, 0x10(r1)
    lwz r4, 0x14(r1)
    bl SpriteHandle_SetCornerAlpha
    b clFlowItemSelect_Update_L_801CBEA0
    clFlowItemSelect_Update_L_801CBE00:
    bl UI_PlaySeDecide
    lwz r4, 0x10(r29)
    lis r0, 0x4330
    lwz r3, 0x80(r29)
    srawi r4, r4, 3
    stw r0, 0x10(r1)
    addze r4, r4
    lfd f3, lbl_806D9DC8(r2)
    xoris r4, r4, 0x8000
    lfs f4, lbl_806D9DDC(r2)
    stw r4, 0x14(r1)
    lfs f1, lbl_806D9DD8(r2)
    lfd f0, 0x10(r1)
    lwz r3, 0x0(r3)
    fsubs f2, f0, f3
    stw r0, 0x8(r1)
    lfs f0, lbl_806D9DE0(r2)
    fmadds f1, f4, f2, f1
    stfs f1, 0x10(r3)
    lwz r3, 0x84(r29)
    lwz r3, 0x0(r3)
    stfs f1, 0x10(r3)
    lwz r3, 0x88(r29)
    lwz r3, 0x0(r3)
    stfs f1, 0x10(r3)
    lwz r0, 0x10(r29)
    lwz r3, 0x80(r29)
    xoris r0, r0, 0x8000
    stw r0, 0xc(r1)
    lwz r3, 0x0(r3)
    lfd f1, 0x8(r1)
    fsubs f1, f1, f3
    fmuls f0, f1, f0
    stfs f0, 0x20(r3)
    lwz r3, 0x84(r29)
    lwz r3, 0x0(r3)
    stfs f0, 0x20(r3)
    lwz r3, 0x88(r29)
    lwz r3, 0x0(r3)
    stfs f0, 0x20(r3)
    clFlowItemSelect_Update_L_801CBEA0:
    lwz r0, 0x10(r29)
    cmpwi r0, 0x10
    bne clFlowItemSelect_Update_L_801CBF1C
    lwz r3, 0x8c(r29)
    li r4, 0x46
    bl SpriteAnimParamBlock_Reload
    lwz r3, 0x8c(r29)
    li r4, 0x1
    lwz r3, 0x0(r3)
    bl fn_8019FF6C
    lwz r0, 0x1c(r29)
    cmpwi r0, 0x0
    bne clFlowItemSelect_Update_L_801CBEFC
    lfs f1, lbl_806D9DE4(r2)
    addi r3, r29, 0x90
    lfs f2, lbl_806D9DE8(r2)
    addi r4, r13, -0x6F08  /* lbl_806CFE18 */
    li r5, 0x1
    bl SpriteGroup_CreateOrInit
    lwz r3, 0x90(r29)
    li r0, 0x6
    lwz r3, 0x0(r3)
    stw r0, 0x4(r3)
    clFlowItemSelect_Update_L_801CBEFC:
    lwz r3, 0x94(r29)
    li r4, 0xff
    bl SpriteHandle_SetCornerAlpha
    lfs f0, lbl_806D9DEC(r2)
    li r3, 0x0
    li r4, 0x1
    stfs f0, 0x20(r29)
    bl fn_801699D8
    clFlowItemSelect_Update_L_801CBF1C:
    li r30, 0x0
    mr r31, r29
    clFlowItemSelect_Update_L_801CBF24:
    lwz r28, 0xdc(r31)
    lwz r3, 0xc(r28)
    subic. r0, r3, 0x1
    stw r0, 0xc(r28)
    bne clFlowItemSelect_Update_L_801CBFCC
    lbz r0, 0x0(r28)
    cmplwi r0, 0x1
    beq clFlowItemSelect_Update_L_801CBFCC
    clFlowItemSelect_Update_L_801CBF44:
    bl Rand15
    lwz r5, 0x14(r28)
    lwz r4, 0x10(r28)
    divw r0, r3, r5
    mullw r0, r0, r5
    subf r0, r0, r3
    slwi r0, r0, 3
    lwzx r3, r4, r0
    cmpwi r3, -0x4
    beq clFlowItemSelect_Update_L_801CBFA0
    bge clFlowItemSelect_Update_L_801CBF80
    cmpwi r3, -0x6
    beq clFlowItemSelect_Update_L_801CBFB0
    bge clFlowItemSelect_Update_L_801CBFA8
    b clFlowItemSelect_Update_L_801CBFB4
    clFlowItemSelect_Update_L_801CBF80:
    cmpwi r3, -0x2
    beq clFlowItemSelect_Update_L_801CBF90
    bge clFlowItemSelect_Update_L_801CBFB4
    b clFlowItemSelect_Update_L_801CBF98
    clFlowItemSelect_Update_L_801CBF90:
    lwz r3, 0x1c(r28)
    b clFlowItemSelect_Update_L_801CBFB4
    clFlowItemSelect_Update_L_801CBF98:
    lwz r3, 0x20(r28)
    b clFlowItemSelect_Update_L_801CBFB4
    clFlowItemSelect_Update_L_801CBFA0:
    lwz r3, 0x18(r28)
    b clFlowItemSelect_Update_L_801CBFB4
    clFlowItemSelect_Update_L_801CBFA8:
    lwz r3, 0x24(r28)
    b clFlowItemSelect_Update_L_801CBFB4
    clFlowItemSelect_Update_L_801CBFB0:
    lwz r3, 0x28(r28)
    clFlowItemSelect_Update_L_801CBFB4:
    lwz r0, 0x8(r28)
    cmpw r3, r0
    beq clFlowItemSelect_Update_L_801CBF44
    stw r3, 0x8(r28)
    li r0, 0x6
    stw r0, 0xc(r28)
    clFlowItemSelect_Update_L_801CBFCC:
    lwz r3, 0xdc(r31)
    li r4, 0x0
    lwz r28, 0x8(r3)
    mr r3, r28
    bl Item_GetDescriptorField0
    mr r5, r3
    lwz r3, 0x80(r31)
    li r4, 0x13b9
    bl SpriteAnimParamBlock_SetKey
    mr r3, r28
    bl Item_GetDescriptorFieldC
    mr. r6, r3
    lwz r3, 0x80(r31)
    li r4, 0x1e1d
    li r5, -0x1
    blt clFlowItemSelect_Update_L_801CC010
    addi r5, r6, 0x1e1d
    clFlowItemSelect_Update_L_801CC010:
    bl SpriteAnimParamBlock_SetKey
    mr r3, r28
    bl Item_GetDescriptorField8
    mr. r6, r3
    lwz r3, 0x80(r31)
    li r4, 0x17a4
    li r5, -0x1
    blt clFlowItemSelect_Update_L_801CC034
    addi r5, r6, 0x17a3
    clFlowItemSelect_Update_L_801CC034:
    bl SpriteAnimParamBlock_SetKey
    addi r30, r30, 0x1
    addi r31, r31, 0x4
    cmpwi r30, 0x3
    blt clFlowItemSelect_Update_L_801CBF24
    li r30, 0x0
    mr r28, r29
    clFlowItemSelect_Update_L_801CC050:
    lwz r3, 0x80(r28)
    cmplwi r3, 0x0
    beq clFlowItemSelect_Update_L_801CC068
    lwz r3, 0x0(r3)
    lfs f1, lbl_806D9DF0(r2)
    bl Sprite_AdvanceAnim
    clFlowItemSelect_Update_L_801CC068:
    addi r30, r30, 0x1
    addi r28, r28, 0x4
    cmpwi r30, 0x5
    blt clFlowItemSelect_Update_L_801CC050
    lwz r3, 0x94(r29)
    bl SpriteHandle_RecomputeCull
    lwz r3, 0xe8(r29)
    bl fn_8023CDA8
    lwz r0, 0x1c(r29)
    cmpwi r0, 0x1
    bgt clFlowItemSelect_Update_L_801CC0C0
    lfs f2, 0x20(r29)
    lfs f1, lbl_806D9DF4(r2)
    lfs f0, lbl_806D9DB0(r2)
    fsubs f1, f2, f1
    stfs f1, 0x20(r29)
    lfs f1, 0x20(r29)
    fcmpo cr0, f1, f0
    bge clFlowItemSelect_Update_L_801CC0C8
    lfs f0, lbl_806D9DF8(r2)
    stfs f0, 0x20(r29)
    b clFlowItemSelect_Update_L_801CC0C8
    clFlowItemSelect_Update_L_801CC0C0:
    lfs f0, lbl_806D9DF8(r2)
    stfs f0, 0x20(r29)
    clFlowItemSelect_Update_L_801CC0C8:
    lfs f1, 0x20(r29)
    bl SetScreenBrightness
    bl fn_801B7EF8
    bl ItemDisplay_GetOrCreate
    bl ItemDisplay_Update
    mr r3, r29
    bl fn_801CB818
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    lwz r28, 0x20(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

