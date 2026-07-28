/* === extracted from auto_clFlowItemSelect_Com_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Item_GetDescriptorField0();
extern void Item_GetDescriptorField8();
extern void Item_GetDescriptorFieldC();
extern void SpriteAnimParamBlock_Reload();
extern void SpriteAnimParamBlock_SetAnimParamCached();
extern void SpriteAnimParamBlock_SetKey();
extern void Sprite_SetAnimTime();
extern void fn_8019FEBC();
extern void fn_8019FED8();
extern void fn_8019FF8C();
extern void fn_801A0550();
extern void fn_801F93EC();

/* --- function index (1 fns, .text 0x801CB620..0x801CB818) ---
 * [  0] 0x801CB620 size:0x1F8   global clFlowItemSelect_CommitSlotAnim
 */

/* --- forward decls --- */
asm void clFlowItemSelect_CommitSlotAnim(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clFlowItemSelect_CommitSlotAnim[8] = {
    0x28, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowItemSelect_CommitSlotAnim = {
    (void *)&clFlowItemSelect_CommitSlotAnim, 0x000001F8, (void *)extab_clFlowItemSelect_CommitSlotAnim
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clFlowItemSelect_CommitSlotAnim(void) { /* 0x801CB620 size:0x1F8 */
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    stfd f31, 0x50(r1)
    psq_st f31, 0x58(r1), 0, 0
    stmw r27, 0x3c(r1)
    mr r28, r4
    mr r29, r3
    slwi r0, r4, 2
    mr r27, r5
    add r31, r29, r0
    li r4, 0x53
    lwz r3, 0x80(r31)
    bl SpriteAnimParamBlock_Reload
    lwz r3, 0x80(r31)
    lwz r3, 0x0(r3)
    bl fn_801A0550
    mr r3, r27
    li r4, 0x0
    bl Item_GetDescriptorField0
    mr r5, r3
    lwz r3, 0x80(r31)
    li r4, 0x13b9
    bl SpriteAnimParamBlock_SetKey
    mr r3, r27
    bl Item_GetDescriptorFieldC
    mr. r6, r3
    lwz r3, 0x80(r31)
    li r4, 0x1e1d
    li r5, -0x1
    blt clFlowItemSelect_CommitSlotAnim_L_801CB6A0
    addi r5, r6, 0x1e1d
    clFlowItemSelect_CommitSlotAnim_L_801CB6A0:
    bl SpriteAnimParamBlock_SetKey
    mr r3, r27
    bl Item_GetDescriptorField8
    mr. r6, r3
    lwz r3, 0x80(r31)
    li r4, 0x17a4
    li r5, -0x1
    blt clFlowItemSelect_CommitSlotAnim_L_801CB6C4
    addi r5, r6, 0x17a3
    clFlowItemSelect_CommitSlotAnim_L_801CB6C4:
    bl SpriteAnimParamBlock_SetKey
    slwi r30, r28, 4
    lis r3, 0xe020
    add r28, r29, r30
    li r5, -0x100
    lwz r4, 0x98(r28)
    addi r0, r3, 0x2000
    stw r5, 0x20(r4)
    lwz r3, 0x9c(r28)
    stw r5, 0x20(r3)
    lwz r3, 0xa0(r28)
    stw r5, 0x20(r3)
    lwz r3, 0xa4(r28)
    stw r5, 0x20(r3)
    lwz r3, 0x98(r28)
    stw r0, 0x20(r3)
    lwz r3, 0x80(r31)
    lwz r3, 0x0(r3)
    bl fn_8019FED8
    lwz r3, 0x80(r31)
    fmr f31, f1
    lwz r27, 0x0(r3)
    mr r3, r27
    bl fn_8019FEBC
    mr r3, r27
    bl Sprite_SetAnimTime
    lwz r3, 0x80(r31)
    addi r5, r1, 0x8
    li r4, 0x1ecd
    lwz r3, 0x0(r3)
    bl fn_8019FF8C
    lwz r3, 0x98(r28)
    lfs f1, 0x8(r1)
    lfs f2, 0xc(r1)
    bl fn_801F93EC
    lwz r3, 0x80(r31)
    addi r5, r1, 0x8
    li r4, 0x1ecf
    lwz r3, 0x0(r3)
    bl fn_8019FF8C
    lfs f1, 0x8(r1)
    lwz r3, 0x9c(r28)
    lfs f2, 0xc(r1)
    bl fn_801F93EC
    lwz r3, 0x80(r31)
    addi r5, r1, 0x8
    li r4, 0x1ed1
    lwz r3, 0x0(r3)
    bl fn_8019FF8C
    lfs f1, 0x8(r1)
    lwz r3, 0xa0(r28)
    lfs f2, 0xc(r1)
    bl fn_801F93EC
    lwz r3, 0x80(r31)
    addi r5, r1, 0x8
    li r4, 0x1ed3
    lwz r3, 0x0(r3)
    bl fn_8019FF8C
    lfs f1, 0x8(r1)
    lwz r3, 0xa4(r28)
    lfs f2, 0xc(r1)
    bl fn_801F93EC
    lwz r3, 0x80(r31)
    fmr f1, f31
    lwz r3, 0x0(r3)
    bl Sprite_SetAnimTime
    lwz r3, 0x80(r31)
    li r4, 0x1ecf
    li r5, 0x1ecd
    bl SpriteAnimParamBlock_SetAnimParamCached
    lwz r3, 0x80(r31)
    li r4, 0x1ed1
    li r5, 0x1ecd
    bl SpriteAnimParamBlock_SetAnimParamCached
    lwz r3, 0x80(r31)
    li r4, 0x1ed3
    li r5, 0x1ecd
    bl SpriteAnimParamBlock_SetAnimParamCached
    psq_l f31, 0x58(r1), 0, 0
    lfd f31, 0x50(r1)
    lmw r27, 0x3c(r1)
    lwz r0, 0x64(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
}

