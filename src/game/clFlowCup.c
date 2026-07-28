/* clFlowCup extab bundle: generated from target assembly. */
/*
 * clFlowCup_Draw   @ 0x801C7360 (0x3CC)
 * clFlowCup_Update @ 0x801C772C (0x11C8)
 * clFlowCup_Dtor   @ 0x801C88F4 (0x1C0)
 * clFlowCup_Init   @ 0x801C8AB4 (0x7D4)
 *
 * Keep fragment order equal to target extab/extabindex and .text order.
 */
#ifdef __cplusplus
extern "C" {
#endif
/* === extracted from auto_clFlowCup_Draw_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void fn_8019FF8C();
extern void fn_801A0004();
extern void fn_801A0DF0();
extern void fn_801A0FD4();
extern void fn_801A10DC();
extern void fn_801A1128();
extern void fn_801A1174();
extern void isJapanese();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D9C88;
extern unsigned int lbl_806D9CA8;
extern unsigned int lbl_806D9CAC;
extern unsigned int lbl_806D9CB0;
extern unsigned int lbl_806D9CB4;
extern unsigned int lbl_806D9CB8;
extern unsigned int lbl_806D9CBC;
extern unsigned int lbl_806D9CC0;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8049AD58[];
extern unsigned int lbl_8049ADE4[];

/* --- function index (1 fns, .text 0x801C7360..0x801C772C) ---
 * [  0] 0x801C7360 size:0x3CC   global clFlowCup_Draw
 */

/* --- forward decls --- */
asm void clFlowCup_Draw(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clFlowCup_Draw[8] = {
    0x20, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowCup_Draw = {
    (void *)&clFlowCup_Draw, 0x000003CC, (void *)extab_clFlowCup_Draw
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clFlowCup_Draw(void) { /* 0x801C7360 size:0x3CC */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stw r31, 0x4c(r1)
    mr r31, r3
    stw r30, 0x48(r1)
    stw r29, 0x44(r1)
    stw r28, 0x40(r1)
    lwz r3, 0xf8(r3)
    cmplwi r3, 0x0
    beq clFlowCup_Draw_L_801C7390
    bl fn_801A0004
    clFlowCup_Draw_L_801C7390:
    lwz r3, 0x18(r31)
    cmplwi r3, 0x0
    beq clFlowCup_Draw_L_801C73A0
    bl fn_801A0004
    clFlowCup_Draw_L_801C73A0:
    lwz r3, 0xb0(r31)
    cmplwi r3, 0x0
    beq clFlowCup_Draw_L_801C73B0
    bl fn_801A0004
    clFlowCup_Draw_L_801C73B0:
    lwz r3, 0xfc(r31)
    cmplwi r3, 0x0
    beq clFlowCup_Draw_L_801C73C0
    bl fn_801A0004
    clFlowCup_Draw_L_801C73C0:
    li r29, 0x0
    mr r30, r31
    clFlowCup_Draw_L_801C73C8:
    lwz r0, 0x4(r31)
    cmpw r29, r0
    beq clFlowCup_Draw_L_801C73E8
    lwz r3, 0x2c(r30)
    cmplwi r3, 0x0
    beq clFlowCup_Draw_L_801C73E8
    beq clFlowCup_Draw_L_801C73E8
    bl fn_801A0004
    clFlowCup_Draw_L_801C73E8:
    addi r29, r29, 0x1
    addi r30, r30, 0x10
    cmpwi r29, 0x9
    blt clFlowCup_Draw_L_801C73C8
    lwz r0, 0xc(r31)
    cmpwi r0, 0x4
    beq clFlowCup_Draw_L_801C7458
    lwz r0, 0x4(r31)
    srwi r3, r0, 31
    clrlwi r0, r0, 31
    xor r0, r0, r3
    subf r0, r3, r0
    cmpwi r0, 0x1
    bne clFlowCup_Draw_L_801C7458
    lwz r3, 0x108(r31)
    cmplwi r3, 0x0
    beq clFlowCup_Draw_L_801C743C
    lbz r0, 0x110(r31)
    cmplwi r0, 0x0
    beq clFlowCup_Draw_L_801C743C
    bl fn_801A0004
    clFlowCup_Draw_L_801C743C:
    lwz r3, 0x10c(r31)
    cmplwi r3, 0x0
    beq clFlowCup_Draw_L_801C7458
    lbz r0, 0x111(r31)
    cmplwi r0, 0x0
    beq clFlowCup_Draw_L_801C7458
    bl fn_801A0004
    clFlowCup_Draw_L_801C7458:
    lwz r0, 0x4(r31)
    slwi r0, r0, 4
    add r3, r31, r0
    lwz r3, 0x2c(r3)
    cmplwi r3, 0x0
    beq clFlowCup_Draw_L_801C7504
    bl fn_801A0004
    lbz r0, 0x118(r31)
    cmplwi r0, 0x1
    bne clFlowCup_Draw_L_801C7504
    lwz r4, 0x4(r31)
    lis r3, lbl_8049AD58@ha
    addi r3, r3, lbl_8049AD58@l
    addi r5, r1, 0x8
    mulli r0, r4, 0xc
    slwi r4, r4, 4
    add r6, r31, r4
    add r4, r3, r0
    lwz r3, 0x2c(r6)
    lha r4, 0x2(r4)
    bl fn_8019FF8C
    li r3, 0x15f4
    li r4, 0x5
    li r5, 0x0
    li r6, 0x0
    li r7, 0x0
    bl fn_801A1174
    lfs f3, 0x8(r1)
    lfs f1, lbl_806D9CA8(r2)
    lfs f2, lbl_806D9CAC(r2)
    lfs f0, 0xc(r1)
    fsubs f1, f3, f1
    fadds f2, f2, f0
    bl fn_801A1128
    lfs f1, lbl_806D9CB0(r2)
    fmr f2, f1
    bl fn_801A10DC
    lfs f1, 0x1c(r1)
    lfs f2, 0x20(r1)
    lfs f3, 0x24(r1)
    lfs f4, 0x28(r1)
    bl fn_801A0FD4
    bl fn_801A0DF0
    clFlowCup_Draw_L_801C7504:
    lwz r0, 0xc(r31)
    cmpwi r0, 0x4
    beq clFlowCup_Draw_L_801C7560
    lwz r0, 0x4(r31)
    srwi r3, r0, 31
    clrlwi r0, r0, 31
    xor r0, r0, r3
    subf. r0, r3, r0
    bne clFlowCup_Draw_L_801C7560
    lwz r3, 0x108(r31)
    cmplwi r3, 0x0
    beq clFlowCup_Draw_L_801C7544
    lbz r0, 0x110(r31)
    cmplwi r0, 0x0
    beq clFlowCup_Draw_L_801C7544
    bl fn_801A0004
    clFlowCup_Draw_L_801C7544:
    lwz r3, 0x10c(r31)
    cmplwi r3, 0x0
    beq clFlowCup_Draw_L_801C7560
    lbz r0, 0x111(r31)
    cmplwi r0, 0x0
    beq clFlowCup_Draw_L_801C7560
    bl fn_801A0004
    clFlowCup_Draw_L_801C7560:
    lwz r0, 0x4(r31)
    lis r3, lbl_8049ADE4@ha
    addi r3, r3, lbl_8049ADE4@l
    li r4, 0x4
    mulli r0, r0, 0xc
    li r5, 0x0
    li r6, 0x0
    li r7, 0x0
    lhax r3, r3, r0
    bl fn_801A1174
    lfs f1, lbl_806D9CB4(r2)
    lfs f2, lbl_806D9CB8(r2)
    bl fn_801A1128
    lfs f1, lbl_806D9C88(r2)
    lfs f4, 0x114(r31)
    fmr f2, f1
    fmr f3, f1
    bl fn_801A0FD4
    bl fn_801A0DF0
    lwz r0, 0x4(r31)
    lis r3, lbl_8049ADE4@ha
    addi r3, r3, lbl_8049ADE4@l
    li r4, 0x4
    mulli r0, r0, 0xc
    li r5, 0x0
    li r6, 0x0
    li r7, 0x0
    add r3, r3, r0
    lha r3, 0x2(r3)
    bl fn_801A1174
    bl isJapanese
    cmpwi r3, 0x0
    bne clFlowCup_Draw_L_801C7608
    lwz r0, 0x4(r31)
    lis r3, lbl_8049ADE4@ha
    addi r3, r3, lbl_8049ADE4@l
    lfs f2, lbl_806D9CB8(r2)
    mulli r0, r0, 0xc
    add r3, r3, r0
    lfs f1, 0x4(r3)
    bl fn_801A1128
    b clFlowCup_Draw_L_801C7628
    clFlowCup_Draw_L_801C7608:
    lwz r0, 0x4(r31)
    lis r3, lbl_8049ADE4@ha
    addi r3, r3, lbl_8049ADE4@l
    lfs f2, lbl_806D9CB8(r2)
    mulli r0, r0, 0xc
    add r3, r3, r0
    lfs f1, 0x8(r3)
    bl fn_801A1128
    clFlowCup_Draw_L_801C7628:
    lfs f1, lbl_806D9C88(r2)
    lfs f4, 0x114(r31)
    fmr f2, f1
    fmr f3, f1
    bl fn_801A0FD4
    bl fn_801A0DF0
    li r3, 0x174c
    li r4, 0x4
    li r5, 0x0
    li r6, 0x0
    li r7, 0x0
    bl fn_801A1174
    lfs f1, lbl_806D9CBC(r2)
    lfs f2, lbl_806D9CC0(r2)
    bl fn_801A1128
    lfs f1, lbl_806D9C88(r2)
    lfs f4, 0x114(r31)
    fmr f2, f1
    fmr f3, f1
    bl fn_801A0FD4
    bl fn_801A0DF0
    mr r30, r31
    mr r29, r31
    li r28, 0x0
    clFlowCup_Draw_L_801C7688:
    lwz r0, 0xc4(r30)
    cmpwi r0, -0x1
    beq clFlowCup_Draw_L_801C76A4
    slwi r3, r0, 2
    addi r0, r3, 0xd8
    lwzx r3, r29, r0
    bl fn_801A0004
    clFlowCup_Draw_L_801C76A4:
    addi r28, r28, 0x1
    addi r29, r29, 0x8
    cmpwi r28, 0x4
    addi r30, r30, 0x4
    blt clFlowCup_Draw_L_801C7688
    lwz r3, 0x1c(r31)
    cmplwi r3, 0x0
    beq clFlowCup_Draw_L_801C76C8
    bl fn_801A0004
    clFlowCup_Draw_L_801C76C8:
    lwz r0, 0xc(r31)
    cmpwi r0, 0x4
    bne clFlowCup_Draw_L_801C770C
    lwz r3, 0x14c(r31)
    bl fn_801A0004
    lwz r3, 0x148(r31)
    bl fn_801A0004
    lwz r3, 0x150(r31)
    bl fn_801A0004
    li r28, 0x0
    mr r29, r31
    clFlowCup_Draw_L_801C76F4:
    lwz r3, 0x124(r29)
    bl fn_801A0004
    addi r28, r28, 0x1
    addi r29, r29, 0x4
    cmpwi r28, 0x9
    blt clFlowCup_Draw_L_801C76F4
    clFlowCup_Draw_L_801C770C:
    lwz r0, 0x54(r1)
    lwz r31, 0x4c(r1)
    lwz r30, 0x48(r1)
    lwz r29, 0x44(r1)
    lwz r28, 0x40(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}



/* === extracted from auto_clFlowCup_Update_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void CupTile_StateChange();
extern void GetInputManager();
extern void InputMgr_GetPlayer();
extern void RumbleUpdate();
extern void SetCourseParams();
extern void SetRumbleMode();
extern void SetScreenBrightness();
extern void Sprite_AdvanceAnim();
extern void Sprite_CreateWithParams();
extern void Sprite_Destroy();
extern void Sprite_InitWithAnim();
extern void Sprite_SetAnimParam();
extern void Sprite_SetupAnim();
extern void fn_801699D8();
extern void fn_8019FF6C();
extern void fn_801A0550();
extern void fn_801B7C64();
extern void fn_801B7CAC();
extern void fn_801B85DC();
extern void fn_801B87D8();
extern void fn_801C64DC();
extern void fn_801C6744();
extern void fn_801D5C88();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_ccClass;
extern unsigned int g_pInputState;
extern unsigned int lbl_806D184C;
extern unsigned int lbl_806D184D;
extern unsigned int lbl_806D9C68;
extern unsigned int lbl_806D9C70;
extern unsigned int lbl_806D9C74;
extern unsigned int lbl_806D9C7C;
extern unsigned int lbl_806D9C80;
extern unsigned int lbl_806D9C88;
extern unsigned int lbl_806D9C90;
extern unsigned int lbl_806D9C94;
extern unsigned int lbl_806D9C98;
extern unsigned int lbl_806D9CA0;
extern unsigned int lbl_806D9CA4;
extern unsigned int lbl_806D9CC4;
extern unsigned int lbl_806D9CC8;
extern unsigned int lbl_806D9CCC;
extern unsigned int lbl_806D9CD0;
extern unsigned int lbl_806D9CD4;
extern unsigned int lbl_806D9CD8;
extern unsigned int lbl_806D9CDC;
extern unsigned int lbl_806D9CE0;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int g_playerData[];
extern unsigned int lbl_8039B228[];
extern unsigned int lbl_8049AD58[];
extern unsigned int lbl_8049ADD0[];

/* --- function index (1 fns, .text 0x801C772C..0x801C88F4) ---
 * [  0] 0x801C772C size:0x11C8  global clFlowCup_Update
 */

/* --- forward decls --- */
asm void clFlowCup_Update(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; void *f11; unsigned int f12; void *f13; unsigned int f14; void *f15; unsigned int f16; void *f17; } extab_clFlowCup_Update = { 0x200A0000, 0x00000228, 0x00000028, 0x00000264, 0x00000030, 0x0000029C, 0x00000038, 0x000002C0, 0x00000040, 0x00000000, 0x8A80001C, (void *)&MemoryManager_TimedFree, 0x8A80001C, (void *)&MemoryManager_TimedFree, 0x8A80001C, (void *)&MemoryManager_TimedFree, 0x8A80001C, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowCup_Update = {
    (void *)&clFlowCup_Update, 0x000011C8, (void *)&extab_clFlowCup_Update
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clFlowCup_Update(void) { /* 0x801C772C size:0x11C8 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stw r31, 0x2c(r1)
    stw r30, 0x28(r1)
    mr r30, r3
    stw r29, 0x24(r1)
    stw r28, 0x20(r1)
    bl RumbleUpdate
    lbz r0, 0x10(r30)
    cmplwi r0, 0x0
    beq clFlowCup_Update_L_801C7770
    lwz r3, 0xc(r30)
    li r0, 0x0
    addi r3, r3, 0x1
    stw r3, 0xc(r30)
    stb r0, 0x10(r30)
    clFlowCup_Update_L_801C7770:
    lwz r3, 0x14(r30)
    addi r0, r3, 0x1
    stw r0, 0x14(r30)
    lwz r0, 0xc(r30)
    cmpwi r0, 0x2
    beq clFlowCup_Update_L_801C82B8
    bge clFlowCup_Update_L_801C779C
    cmpwi r0, 0x0
    beq clFlowCup_Update_L_801C77AC
    bge clFlowCup_Update_L_801C7C70
    b clFlowCup_Update_L_801C86F4
    clFlowCup_Update_L_801C779C:
    cmpwi r0, 0x4
    beq clFlowCup_Update_L_801C8424
    bge clFlowCup_Update_L_801C86F4
    b clFlowCup_Update_L_801C8358
    clFlowCup_Update_L_801C77AC:
    lwz r0, 0x14(r30)
    cmpwi r0, 0x1
    bne clFlowCup_Update_L_801C77C8
    mr r3, r30
    li r4, 0x0
    li r5, 0x1
    bl CupTile_StateChange
    clFlowCup_Update_L_801C77C8:
    lwz r0, 0x14(r30)
    cmpwi r0, 0x6
    bne clFlowCup_Update_L_801C77E4
    mr r3, r30
    li r4, 0x1
    li r5, 0x1
    bl CupTile_StateChange
    clFlowCup_Update_L_801C77E4:
    lwz r0, 0x14(r30)
    cmpwi r0, 0xa
    bne clFlowCup_Update_L_801C7800
    mr r3, r30
    li r4, 0x2
    li r5, 0x1
    bl CupTile_StateChange
    clFlowCup_Update_L_801C7800:
    lwz r0, 0x14(r30)
    cmpwi r0, 0xe
    bne clFlowCup_Update_L_801C781C
    mr r3, r30
    li r4, 0x3
    li r5, 0x1
    bl CupTile_StateChange
    clFlowCup_Update_L_801C781C:
    lwz r0, 0x14(r30)
    cmpwi r0, 0x12
    bne clFlowCup_Update_L_801C7838
    mr r3, r30
    li r4, 0x4
    li r5, 0x1
    bl CupTile_StateChange
    clFlowCup_Update_L_801C7838:
    lwz r0, 0x14(r30)
    cmpwi r0, 0x14
    bne clFlowCup_Update_L_801C7854
    mr r3, r30
    li r4, 0x5
    li r5, 0x1
    bl CupTile_StateChange
    clFlowCup_Update_L_801C7854:
    lwz r0, 0x14(r30)
    cmpwi r0, 0x16
    bne clFlowCup_Update_L_801C7870
    mr r3, r30
    li r4, 0x6
    li r5, 0x1
    bl CupTile_StateChange
    clFlowCup_Update_L_801C7870:
    lwz r0, 0x14(r30)
    cmpwi r0, 0x1a
    bne clFlowCup_Update_L_801C788C
    mr r3, r30
    li r4, 0x7
    li r5, 0x1
    bl CupTile_StateChange
    clFlowCup_Update_L_801C788C:
    lwz r0, 0x14(r30)
    cmpwi r0, 0x1e
    bne clFlowCup_Update_L_801C7908
    lbz r0, 0x118(r30)
    cmplwi r0, 0x1
    bne clFlowCup_Update_L_801C78D0
    lwz r3, 0xf8(r30)
    li r4, 0x18e
    li r5, 0x1
    li r6, 0x0
    bl Sprite_SetupAnim
    lwz r3, 0xfc(r30)
    li r4, 0x1c7
    li r5, 0x1
    li r6, 0x0
    bl Sprite_SetupAnim
    b clFlowCup_Update_L_801C7908
    clFlowCup_Update_L_801C78D0:
    lwz r3, 0xf8(r30)
    li r4, 0x184
    li r5, 0x1
    li r6, 0x0
    bl Sprite_SetupAnim
    lwz r3, 0xfc(r30)
    li r4, 0x1dd
    li r5, 0x1
    li r6, 0x0
    bl Sprite_SetupAnim
    lwz r3, 0xfc(r30)
    li r4, 0x1ad4
    li r5, 0x1ae3
    bl Sprite_SetAnimParam
    clFlowCup_Update_L_801C7908:
    lwz r0, 0x14(r30)
    cmpwi r0, 0x28
    bne clFlowCup_Update_L_801C799C
    lbz r0, 0x118(r30)
    cmplwi r0, 0x1
    bne clFlowCup_Update_L_801C795C
    li r3, 0x30
    bl Alloc
    mr. r28, r3
    beq clFlowCup_Update_L_801C7954
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x18f
    lfs f1, lbl_806D9CC4(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f2, lbl_806D9CC8(r2)
    fmr f6, f3
    lfs f5, lbl_806D9C80(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Update_L_801C7954:
    stw r28, 0x18(r30)
    b clFlowCup_Update_L_801C7994
    clFlowCup_Update_L_801C795C:
    li r3, 0x30
    bl Alloc
    mr. r28, r3
    beq clFlowCup_Update_L_801C7990
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x185
    lfs f1, lbl_806D9CC4(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f2, lbl_806D9CC8(r2)
    fmr f6, f3
    lfs f5, lbl_806D9C80(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Update_L_801C7990:
    stw r28, 0x18(r30)
    clFlowCup_Update_L_801C7994:
    li r0, 0x1
    stb r0, 0xc0(r30)
    clFlowCup_Update_L_801C799C:
    lwz r0, 0x14(r30)
    cmpwi r0, 0x3c
    bne clFlowCup_Update_L_801C7BE0
    li r3, 0x30
    bl Alloc
    mr. r28, r3
    beq clFlowCup_Update_L_801C79C8
    li r4, 0x9c
    li r5, 0x1
    li r6, 0x0
    bl Sprite_InitWithAnim
    clFlowCup_Update_L_801C79C8:
    stw r28, 0x108(r30)
    li r3, 0x30
    bl Alloc
    mr. r28, r3
    beq clFlowCup_Update_L_801C79EC
    li r4, 0x9c
    li r5, 0x1
    li r6, 0x0
    bl Sprite_InitWithAnim
    clFlowCup_Update_L_801C79EC:
    stw r28, 0x10c(r30)
    li r4, 0x1
    lwz r3, 0x108(r30)
    bl fn_8019FF6C
    lwz r3, 0x10c(r30)
    li r4, 0x1
    bl fn_8019FF6C
    lwz r4, 0x4(r30)
    mr r3, r30
    li r5, 0x4
    bl CupTile_StateChange
    lwz r4, 0x4(r30)
    mr r3, r30
    bl fn_801C64DC
    li r0, 0x0
    stb r0, 0x110(r30)
    lwz r5, 0x108(r30)
    cmplwi r5, 0x0
    beq clFlowCup_Update_L_801C7AB0
    lwz r0, 0x4(r30)
    lis r3, lbl_8039B228@ha
    addi r4, r3, lbl_8039B228@l
    lfd f2, lbl_806D9C68(r2)
    mulli r0, r0, 0x18
    lfs f0, lbl_806D9C70(r2)
    lfsx f1, r4, r0
    add r3, r4, r0
    lfs f3, 0x4(r3)
    stfs f1, 0xc(r5)
    stfs f3, 0x10(r5)
    lwz r0, 0x4(r30)
    lwz r3, 0x108(r30)
    mulli r0, r0, 0x18
    add r4, r4, r0
    lfs f1, 0x8(r4)
    fmul f1, f2, f1
    frsp f1, f1
    stfs f1, 0x1c(r3)
    lwz r3, 0x108(r30)
    stfs f0, 0x14(r3)
    stfs f0, 0x18(r3)
    lwz r0, 0x4(r30)
    cmpwi r0, 0x0
    bne clFlowCup_Update_L_801C7AA8
    lbz r0, 0x118(r30)
    cmplwi r0, 0x1
    bne clFlowCup_Update_L_801C7AB0
    clFlowCup_Update_L_801C7AA8:
    li r0, 0x1
    stb r0, 0x110(r30)
    clFlowCup_Update_L_801C7AB0:
    li r0, 0x0
    stb r0, 0x111(r30)
    lwz r5, 0x10c(r30)
    cmplwi r5, 0x0
    beq clFlowCup_Update_L_801C7BB8
    lwz r0, 0x4(r30)
    lis r3, lbl_8039B228@ha
    addi r4, r3, lbl_8039B228@l
    lfd f2, lbl_806D9C68(r2)
    mulli r0, r0, 0x18
    lfs f0, lbl_806D9C70(r2)
    add r3, r4, r0
    lfs f1, 0xc(r3)
    lfs f3, 0x10(r3)
    stfs f1, 0xc(r5)
    stfs f3, 0x10(r5)
    lwz r0, 0x4(r30)
    lwz r3, 0x10c(r30)
    mulli r0, r0, 0x18
    add r4, r4, r0
    lfs f1, 0x14(r4)
    fmul f1, f2, f1
    frsp f1, f1
    stfs f1, 0x1c(r3)
    lwz r3, 0x10c(r30)
    stfs f0, 0x14(r3)
    stfs f0, 0x18(r3)
    lwz r0, 0x4(r30)
    cmpwi r0, 0x7
    beq clFlowCup_Update_L_801C7B30
    li r0, 0x1
    stb r0, 0x111(r30)
    clFlowCup_Update_L_801C7B30:
    lbz r0, 0x118(r30)
    cmplwi r0, 0x0
    bne clFlowCup_Update_L_801C7B60
    lis r3, g_playerData@ha
    lwz r4, g_ccClass(r13)
    addi r3, r3, g_playerData@l
    bl fn_801D5C88
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne clFlowCup_Update_L_801C7B60
    li r0, 0x1
    stb r0, 0x111(r30)
    clFlowCup_Update_L_801C7B60:
    lbz r0, 0x118(r30)
    cmplwi r0, 0x0
    bne clFlowCup_Update_L_801C7B8C
    lwz r0, 0x4(r30)
    cmpwi r0, 0x6
    bne clFlowCup_Update_L_801C7B8C
    lbz r0, 0x154(r30)
    cmplwi r0, 0x0
    bne clFlowCup_Update_L_801C7B8C
    li r0, 0x0
    stb r0, 0x111(r30)
    clFlowCup_Update_L_801C7B8C:
    lbz r0, 0x118(r30)
    cmplwi r0, 0x1
    bne clFlowCup_Update_L_801C7BB8
    lwz r0, 0x4(r30)
    cmpwi r0, 0x6
    bne clFlowCup_Update_L_801C7BB8
    lbz r0, 0x155(r30)
    cmplwi r0, 0x0
    bne clFlowCup_Update_L_801C7BB8
    li r0, 0x0
    stb r0, 0x111(r30)
    clFlowCup_Update_L_801C7BB8:
    lfs f1, 0xd4(r30)
    bl SetScreenBrightness
    li r5, 0x1
    li r0, 0x0
    stb r5, lbl_806D184C(r13)
    li r3, 0x0
    li r4, 0x1
    stb r0, lbl_806D184D(r13)
    stb r5, 0x10(r30)
    bl fn_801699D8
    clFlowCup_Update_L_801C7BE0:
    lwz r0, 0x14(r30)
    cmpwi r0, 0x12
    blt clFlowCup_Update_L_801C86F4
    cmpwi r0, 0x1e
    bgt clFlowCup_Update_L_801C86F4
    xoris r3, r0, 0x8000
    lis r0, 0x4330
    stw r3, 0xc(r1)
    lfd f3, lbl_806D9C98(r2)
    stw r0, 0x8(r1)
    lfs f1, lbl_806D9CCC(r2)
    lfd f2, 0x8(r1)
    lfs f0, lbl_806D9C90(r2)
    fsubs f2, f2, f3
    lwz r3, 0xd8(r30)
    fsubs f1, f2, f1
    fdivs f0, f1, f0
    stfs f0, 0x20(r3)
    lwz r3, 0xdc(r30)
    stfs f0, 0x20(r3)
    lwz r3, 0xe0(r30)
    stfs f0, 0x20(r3)
    lwz r3, 0xe4(r30)
    stfs f0, 0x20(r3)
    lwz r3, 0xe8(r30)
    stfs f0, 0x20(r3)
    lwz r3, 0xec(r30)
    stfs f0, 0x20(r3)
    lwz r3, 0xf0(r30)
    stfs f0, 0x20(r3)
    lwz r3, 0xf4(r30)
    stfs f0, 0x20(r3)
    lwz r3, 0x1c(r30)
    stfs f0, 0x20(r3)
    stfs f0, 0x114(r30)
    b clFlowCup_Update_L_801C86F4
    clFlowCup_Update_L_801C7C70:
    lwz r4, g_pInputState(r13)
    lwz r31, 0x4(r30)
    cmplwi r4, 0x0
    bne clFlowCup_Update_L_801C7C88
    li r0, 0x0
    b clFlowCup_Update_L_801C7C8C
    clFlowCup_Update_L_801C7C88:
    mr r0, r4
    clFlowCup_Update_L_801C7C8C:
    cmplwi r0, 0x0
    beq clFlowCup_Update_L_801C7E18
    cmplwi r4, 0x0
    bne clFlowCup_Update_L_801C7CA0
    li r4, 0x0
    clFlowCup_Update_L_801C7CA0:
    lwz r3, 0x4(r30)
    lwz r0, 0x14(r4)
    add r0, r3, r0
    stw r0, 0x4(r30)
    lwz r0, 0x4(r30)
    cmpwi r0, 0x6
    ble clFlowCup_Update_L_801C7CFC
    lbz r0, 0x118(r30)
    cmplwi r0, 0x0
    bne clFlowCup_Update_L_801C7CDC
    lbz r0, 0x154(r30)
    cmplwi r0, 0x0
    bne clFlowCup_Update_L_801C7CDC
    li r0, 0x6
    stw r0, 0x4(r30)
    clFlowCup_Update_L_801C7CDC:
    lbz r0, 0x118(r30)
    cmplwi r0, 0x1
    bne clFlowCup_Update_L_801C7CFC
    lbz r0, 0x155(r30)
    cmplwi r0, 0x0
    bne clFlowCup_Update_L_801C7CFC
    li r0, 0x6
    stw r0, 0x4(r30)
    clFlowCup_Update_L_801C7CFC:
    lwz r0, 0x4(r30)
    cmpwi r0, 0x7
    ble clFlowCup_Update_L_801C7D90
    li r0, 0x7
    stw r0, 0x4(r30)
    lbz r0, 0x118(r30)
    cmplwi r0, 0x0
    bne clFlowCup_Update_L_801C7D90
    lis r3, g_playerData@ha
    lwz r4, g_ccClass(r13)
    addi r3, r3, g_playerData@l
    bl fn_801D5C88
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne clFlowCup_Update_L_801C7D90
    lwz r3, 0x148(r30)
    li r4, 0x18f
    li r5, 0x1
    li r6, 0x0
    bl Sprite_SetupAnim
    lwz r3, 0x14c(r30)
    li r4, 0x18e
    li r5, 0x1
    li r6, 0x0
    bl Sprite_SetupAnim
    lwz r3, 0x150(r30)
    li r4, 0x1c7
    li r5, 0x1
    li r6, 0x0
    bl Sprite_SetupAnim
    li r0, 0x1
    li r3, 0x0
    stb r0, 0x118(r30)
    li r0, 0x4
    stw r3, 0x4(r30)
    stw r0, 0xc(r30)
    stw r3, 0x14(r30)
    clFlowCup_Update_L_801C7D90:
    lwz r0, 0x4(r30)
    cmpwi r0, 0x0
    bge clFlowCup_Update_L_801C7E18
    li r0, 0x0
    stw r0, 0x4(r30)
    lbz r0, 0x118(r30)
    cmplwi r0, 0x1
    bne clFlowCup_Update_L_801C7E18
    lwz r3, 0x148(r30)
    li r4, 0x185
    li r5, 0x1
    li r6, 0x0
    bl Sprite_SetupAnim
    lwz r3, 0x14c(r30)
    li r4, 0x184
    li r5, 0x1
    li r6, 0x0
    bl Sprite_SetupAnim
    lwz r3, 0x150(r30)
    li r4, 0x1dd
    li r5, 0x1
    li r6, 0x0
    bl Sprite_SetupAnim
    lwz r3, 0x150(r30)
    li r4, 0x1ad4
    li r5, 0x1ae3
    bl Sprite_SetAnimParam
    li r4, 0x0
    li r3, 0x7
    stb r4, 0x118(r30)
    li r0, 0x4
    stw r3, 0x4(r30)
    stw r0, 0xc(r30)
    stw r4, 0x14(r30)
    clFlowCup_Update_L_801C7E18:
    lwz r0, 0x4(r30)
    cmpw r31, r0
    beq clFlowCup_Update_L_801C8050
    mr r3, r30
    mr r4, r31
    li r5, 0x2
    bl CupTile_StateChange
    lwz r4, 0x4(r30)
    mr r3, r30
    li r5, 0x4
    bl CupTile_StateChange
    lwz r0, 0xb0(r30)
    lwz r3, 0x4(r30)
    cmplwi r0, 0x0
    beq clFlowCup_Update_L_801C7EAC
    lwz r0, 0xb4(r30)
    cmpwi r0, 0x1
    bne clFlowCup_Update_L_801C7EAC
    stw r3, 0xbc(r30)
    li r4, 0x183
    li r5, 0x0
    li r6, 0x0
    lwz r3, 0xb0(r30)
    bl Sprite_SetupAnim
    lwz r0, 0xbc(r30)
    lis r3, lbl_8049ADD0@ha
    addi r5, r3, lbl_8049ADD0@l
    lwz r3, 0xb0(r30)
    slwi r0, r0, 1
    li r4, 0x1744
    lhax r5, r5, r0
    bl Sprite_SetAnimParam
    lwz r3, 0xb0(r30)
    bl fn_801A0550
    lwz r3, 0xb0(r30)
    li r4, 0x1
    bl fn_8019FF6C
    clFlowCup_Update_L_801C7EAC:
    lwz r4, 0x4(r30)
    mr r3, r30
    bl fn_801C64DC
    li r0, 0x0
    stb r0, 0x110(r30)
    lwz r5, 0x108(r30)
    cmplwi r5, 0x0
    beq clFlowCup_Update_L_801C7F44
    lwz r0, 0x4(r30)
    lis r3, lbl_8039B228@ha
    addi r4, r3, lbl_8039B228@l
    lfd f2, lbl_806D9C68(r2)
    mulli r0, r0, 0x18
    lfs f0, lbl_806D9C70(r2)
    lfsx f1, r4, r0
    add r3, r4, r0
    lfs f3, 0x4(r3)
    stfs f1, 0xc(r5)
    stfs f3, 0x10(r5)
    lwz r0, 0x4(r30)
    lwz r3, 0x108(r30)
    mulli r0, r0, 0x18
    add r4, r4, r0
    lfs f1, 0x8(r4)
    fmul f1, f2, f1
    frsp f1, f1
    stfs f1, 0x1c(r3)
    lwz r3, 0x108(r30)
    stfs f0, 0x14(r3)
    stfs f0, 0x18(r3)
    lwz r0, 0x4(r30)
    cmpwi r0, 0x0
    bne clFlowCup_Update_L_801C7F3C
    lbz r0, 0x118(r30)
    cmplwi r0, 0x1
    bne clFlowCup_Update_L_801C7F44
    clFlowCup_Update_L_801C7F3C:
    li r0, 0x1
    stb r0, 0x110(r30)
    clFlowCup_Update_L_801C7F44:
    li r0, 0x0
    stb r0, 0x111(r30)
    lwz r5, 0x10c(r30)
    cmplwi r5, 0x0
    beq clFlowCup_Update_L_801C804C
    lwz r0, 0x4(r30)
    lis r3, lbl_8039B228@ha
    addi r4, r3, lbl_8039B228@l
    lfd f2, lbl_806D9C68(r2)
    mulli r0, r0, 0x18
    lfs f0, lbl_806D9C70(r2)
    add r3, r4, r0
    lfs f1, 0xc(r3)
    lfs f3, 0x10(r3)
    stfs f1, 0xc(r5)
    stfs f3, 0x10(r5)
    lwz r0, 0x4(r30)
    lwz r3, 0x10c(r30)
    mulli r0, r0, 0x18
    add r4, r4, r0
    lfs f1, 0x14(r4)
    fmul f1, f2, f1
    frsp f1, f1
    stfs f1, 0x1c(r3)
    lwz r3, 0x10c(r30)
    stfs f0, 0x14(r3)
    stfs f0, 0x18(r3)
    lwz r0, 0x4(r30)
    cmpwi r0, 0x7
    beq clFlowCup_Update_L_801C7FC4
    li r0, 0x1
    stb r0, 0x111(r30)
    clFlowCup_Update_L_801C7FC4:
    lbz r0, 0x118(r30)
    cmplwi r0, 0x0
    bne clFlowCup_Update_L_801C7FF4
    lis r3, g_playerData@ha
    lwz r4, g_ccClass(r13)
    addi r3, r3, g_playerData@l
    bl fn_801D5C88
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne clFlowCup_Update_L_801C7FF4
    li r0, 0x1
    stb r0, 0x111(r30)
    clFlowCup_Update_L_801C7FF4:
    lbz r0, 0x118(r30)
    cmplwi r0, 0x0
    bne clFlowCup_Update_L_801C8020
    lwz r0, 0x4(r30)
    cmpwi r0, 0x6
    bne clFlowCup_Update_L_801C8020
    lbz r0, 0x154(r30)
    cmplwi r0, 0x0
    bne clFlowCup_Update_L_801C8020
    li r0, 0x0
    stb r0, 0x111(r30)
    clFlowCup_Update_L_801C8020:
    lbz r0, 0x118(r30)
    cmplwi r0, 0x1
    bne clFlowCup_Update_L_801C804C
    lwz r0, 0x4(r30)
    cmpwi r0, 0x6
    bne clFlowCup_Update_L_801C804C
    lbz r0, 0x155(r30)
    cmplwi r0, 0x0
    bne clFlowCup_Update_L_801C804C
    li r0, 0x0
    stb r0, 0x111(r30)
    clFlowCup_Update_L_801C804C:
    bl fn_801B7CAC
    clFlowCup_Update_L_801C8050:
    lwz r0, 0x8(r30)
    cmpwi r0, -0x1
    beq clFlowCup_Update_L_801C8060
    b clFlowCup_Update_L_801C8214
    clFlowCup_Update_L_801C8060:
    lfs f1, 0xd4(r30)
    lfs f0, lbl_806D9CA0(r2)
    fsubs f0, f1, f0
    stfs f0, 0xd4(r30)
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r3, g_pInputState(r13)
    cmplwi r3, 0x0
    bne clFlowCup_Update_L_801C808C
    li r3, 0x0
    clFlowCup_Update_L_801C808C:
    lwz r0, 0x18(r3)
    cmpwi r0, 0x1
    beq clFlowCup_Update_L_801C80A8
    lfs f1, 0xd4(r30)
    lfs f0, lbl_806D9C80(r2)
    fcmpo cr0, f1, f0
    bge clFlowCup_Update_L_801C8208
    clFlowCup_Update_L_801C80A8:
    li r3, 0x0
    li r4, 0x1
    li r5, 0x1
    bl SetRumbleMode
    lwz r3, g_pInputState(r13)
    cmplwi r3, 0x0
    bne clFlowCup_Update_L_801C80CC
    li r0, 0x0
    b clFlowCup_Update_L_801C80D0
    clFlowCup_Update_L_801C80CC:
    mr r0, r3
    clFlowCup_Update_L_801C80D0:
    cmplwi r0, 0x0
    beq clFlowCup_Update_L_801C80F4
    cmplwi r3, 0x0
    bne clFlowCup_Update_L_801C80E4
    li r3, 0x0
    clFlowCup_Update_L_801C80E4:
    li r0, 0x0
    stb r0, 0x4(r3)
    stw r0, 0x18(r3)
    stw r0, 0x1c(r3)
    clFlowCup_Update_L_801C80F4:
    lwz r0, 0x4(r30)
    cmpwi r0, 0x0
    bne clFlowCup_Update_L_801C8114
    li r3, 0x7
    li r4, 0x0
    li r5, 0x0
    li r6, 0x0
    bl SetCourseParams
    clFlowCup_Update_L_801C8114:
    lwz r0, 0x4(r30)
    cmpwi r0, 0x1
    bne clFlowCup_Update_L_801C8134
    li r3, 0x1
    li r4, 0x0
    li r5, 0x0
    li r6, 0x0
    bl SetCourseParams
    clFlowCup_Update_L_801C8134:
    lwz r0, 0x4(r30)
    cmpwi r0, 0x2
    bne clFlowCup_Update_L_801C8154
    li r3, 0x8
    li r4, 0x0
    li r5, 0x0
    li r6, 0x0
    bl SetCourseParams
    clFlowCup_Update_L_801C8154:
    lwz r0, 0x4(r30)
    cmpwi r0, 0x3
    bne clFlowCup_Update_L_801C8174
    li r3, 0x2
    li r4, 0x0
    li r5, 0x0
    li r6, 0x0
    bl SetCourseParams
    clFlowCup_Update_L_801C8174:
    lwz r0, 0x4(r30)
    cmpwi r0, 0x4
    bne clFlowCup_Update_L_801C8194
    li r3, 0x3
    li r4, 0x0
    li r5, 0x0
    li r6, 0x0
    bl SetCourseParams
    clFlowCup_Update_L_801C8194:
    lwz r0, 0x4(r30)
    cmpwi r0, 0x5
    bne clFlowCup_Update_L_801C81B4
    li r3, 0x4
    li r4, 0x0
    li r5, 0x0
    li r6, 0x0
    bl SetCourseParams
    clFlowCup_Update_L_801C81B4:
    lwz r0, 0x4(r30)
    cmpwi r0, 0x6
    bne clFlowCup_Update_L_801C81D4
    li r3, 0x5
    li r4, 0x0
    li r5, 0x0
    li r6, 0x0
    bl SetCourseParams
    clFlowCup_Update_L_801C81D4:
    lwz r0, 0x4(r30)
    cmpwi r0, 0x7
    bne clFlowCup_Update_L_801C81F4
    li r3, 0x6
    li r4, 0x0
    li r5, 0x0
    li r6, 0x0
    bl SetCourseParams
    clFlowCup_Update_L_801C81F4:
    li r0, 0x1b
    lfs f0, lbl_806D9CA4(r2)
    stw r0, 0x8(r30)
    stfs f0, 0xd4(r30)
    bl fn_801B7C64
    clFlowCup_Update_L_801C8208:
    lfs f1, 0xd4(r30)
    bl SetScreenBrightness
    lwz r0, 0x8(r30)
    clFlowCup_Update_L_801C8214:
    cmpwi r0, -0x1
    beq clFlowCup_Update_L_801C86F4
    li r29, 0x0
    clFlowCup_Update_L_801C8220:
    lwz r0, 0x4(r30)
    cmpw r29, r0
    bne clFlowCup_Update_L_801C8240
    mr r3, r30
    mr r4, r29
    li r5, 0x5
    bl CupTile_StateChange
    b clFlowCup_Update_L_801C8250
    clFlowCup_Update_L_801C8240:
    mr r3, r30
    mr r4, r29
    li r5, 0x3
    bl CupTile_StateChange
    clFlowCup_Update_L_801C8250:
    addi r29, r29, 0x1
    cmpwi r29, 0x9
    blt clFlowCup_Update_L_801C8220
    lwz r3, 0x18(r30)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x108(r30)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x10c(r30)
    li r4, 0x1
    bl Sprite_Destroy
    li r6, 0x0
    li r4, 0x1
    stw r6, 0x18(r30)
    li r0, -0x1
    li r3, 0x15
    li r5, 0x0
    stw r6, 0x14(r30)
    stw r6, 0x108(r30)
    stw r6, 0x10c(r30)
    stb r4, 0x10(r30)
    stb r0, lbl_806D184C(r13)
    lbz r4, 0x118(r30)
    bl fn_801B85DC
    b clFlowCup_Update_L_801C86F4
    clFlowCup_Update_L_801C82B8:
    lwz r0, 0x14(r30)
    cmpwi r0, 0x3c
    bne clFlowCup_Update_L_801C86F4
    lwz r4, 0x4(r30)
    mr r3, r30
    li r5, 0x6
    bl CupTile_StateChange
    bl fn_801B87D8
    lwz r0, 0xb0(r30)
    cmplwi r0, 0x0
    beq clFlowCup_Update_L_801C8334
    lwz r0, 0xb4(r30)
    cmpwi r0, 0x1
    bne clFlowCup_Update_L_801C8334
    li r0, 0x2
    li r4, 0x35
    stw r0, 0xb4(r30)
    li r5, 0x0
    li r6, 0x0
    lwz r3, 0xb0(r30)
    bl Sprite_SetupAnim
    lwz r0, 0xbc(r30)
    lis r3, lbl_8049ADD0@ha
    addi r5, r3, lbl_8049ADD0@l
    lwz r3, 0xb0(r30)
    slwi r0, r0, 1
    li r4, 0x1744
    lhax r5, r5, r0
    bl Sprite_SetAnimParam
    lwz r3, 0xb0(r30)
    bl fn_801A0550
    clFlowCup_Update_L_801C8334:
    li r5, 0x0
    li r0, 0x1
    stb r5, 0xc0(r30)
    li r3, 0x0
    li r4, 0x0
    stw r5, 0x14(r30)
    stb r0, 0x10(r30)
    bl fn_801699D8
    b clFlowCup_Update_L_801C86F4
    clFlowCup_Update_L_801C8358:
    lwz r3, 0x14(r30)
    cmpwi r3, 0xa
    bgt clFlowCup_Update_L_801C8404
    lis r0, 0x4330
    xoris r3, r3, 0x8000
    stw r3, 0xc(r1)
    lfd f3, lbl_806D9C98(r2)
    stw r0, 0x8(r1)
    lfs f2, lbl_806D9CD0(r2)
    lfd f0, 0x8(r1)
    lfs f4, lbl_806D9C88(r2)
    fsubs f0, f0, f3
    lwz r3, 0xd8(r30)
    stw r0, 0x10(r1)
    lfs f1, lbl_806D9CD4(r2)
    fdivs f0, f0, f2
    fsubs f0, f4, f0
    stfs f0, 0x20(r3)
    lwz r3, 0xdc(r30)
    stfs f0, 0x20(r3)
    lwz r3, 0xe0(r30)
    stfs f0, 0x20(r3)
    lwz r3, 0xe4(r30)
    stfs f0, 0x20(r3)
    lwz r3, 0xe8(r30)
    stfs f0, 0x20(r3)
    lwz r3, 0xec(r30)
    stfs f0, 0x20(r3)
    lwz r3, 0xf0(r30)
    stfs f0, 0x20(r3)
    lwz r3, 0xf4(r30)
    stfs f0, 0x20(r3)
    lwz r3, 0x1c(r30)
    stfs f0, 0x20(r3)
    stfs f0, 0x114(r30)
    lwz r0, 0x14(r30)
    xoris r0, r0, 0x8000
    stw r0, 0x14(r1)
    lfd f0, 0x10(r1)
    fsubs f0, f0, f3
    fdivs f0, f0, f2
    fmuls f0, f1, f0
    stfs f0, 0x11c(r30)
    clFlowCup_Update_L_801C8404:
    lwz r0, 0x14(r30)
    cmpwi r0, 0x16
    blt clFlowCup_Update_L_801C86F4
    lwz r0, 0xb0(r30)
    cmplwi r0, 0x0
    bne clFlowCup_Update_L_801C86F4
    lwz r3, 0x8(r30)
    b clFlowCup_Update_L_801C88D4
    clFlowCup_Update_L_801C8424:
    lbz r0, 0x118(r30)
    cmplwi r0, 0x1
    bne clFlowCup_Update_L_801C8468
    lwz r3, 0x14(r30)
    lis r0, 0x4330
    stw r0, 0x10(r1)
    xoris r0, r3, 0x8000
    lfd f2, lbl_806D9C98(r2)
    stw r0, 0x14(r1)
    lfs f0, lbl_806D9CD8(r2)
    lfd f1, 0x10(r1)
    lfs f3, lbl_806D9CD4(r2)
    fsubs f1, f1, f2
    fdivs f0, f1, f0
    fmuls f0, f3, f0
    stfs f0, 0x120(r30)
    b clFlowCup_Update_L_801C849C
    clFlowCup_Update_L_801C8468:
    lwz r3, 0x14(r30)
    lis r0, 0x4330
    stw r0, 0x10(r1)
    xoris r0, r3, 0x8000
    lfd f2, lbl_806D9C98(r2)
    stw r0, 0x14(r1)
    lfs f0, lbl_806D9CD8(r2)
    lfd f1, 0x10(r1)
    lfs f3, lbl_806D9C94(r2)
    fsubs f1, f1, f2
    fdivs f0, f1, f0
    fmuls f0, f3, f0
    stfs f0, 0x120(r30)
    clFlowCup_Update_L_801C849C:
    lwz r0, 0x14(r30)
    cmpwi r0, 0xa
    bgt clFlowCup_Update_L_801C84D8
    xoris r3, r0, 0x8000
    lis r0, 0x4330
    stw r3, 0x14(r1)
    lfd f2, lbl_806D9C98(r2)
    stw r0, 0x10(r1)
    lfs f0, lbl_806D9CD0(r2)
    lfd f1, 0x10(r1)
    lfs f3, lbl_806D9CD4(r2)
    fsubs f1, f1, f2
    fdivs f0, f1, f0
    fmuls f0, f3, f0
    stfs f0, 0x11c(r30)
    clFlowCup_Update_L_801C84D8:
    lwz r0, 0x14(r30)
    cmpwi r0, 0x14
    blt clFlowCup_Update_L_801C85AC
    lfs f0, lbl_806D9C80(r2)
    li r0, 0x1
    li r3, 0x0
    stfs f0, 0x120(r30)
    stfs f0, 0x11c(r30)
    stw r0, 0xc(r30)
    stw r3, 0x14(r30)
    lbz r0, 0x118(r30)
    cmplwi r0, 0x0
    bne clFlowCup_Update_L_801C856C
    li r0, 0x7
    li r4, 0x185
    stw r0, 0x4(r30)
    li r5, 0x1
    li r6, 0x0
    lwz r3, 0x18(r30)
    bl Sprite_SetupAnim
    lwz r3, 0xf8(r30)
    li r4, 0x184
    li r5, 0x1
    li r6, 0x0
    bl Sprite_SetupAnim
    lwz r3, 0xfc(r30)
    li r4, 0x1dd
    li r5, 0x0
    li r6, 0x0
    bl Sprite_SetupAnim
    lwz r3, 0xfc(r30)
    li r4, 0x1ad4
    li r5, 0x1ae3
    bl Sprite_SetAnimParam
    lwz r3, 0xfc(r30)
    bl fn_801A0550
    b clFlowCup_Update_L_801C85AC
    clFlowCup_Update_L_801C856C:
    stw r3, 0x4(r30)
    li r4, 0x18f
    li r5, 0x1
    li r6, 0x0
    lwz r3, 0x18(r30)
    bl Sprite_SetupAnim
    lwz r3, 0xf8(r30)
    li r4, 0x18e
    li r5, 0x1
    li r6, 0x0
    bl Sprite_SetupAnim
    lwz r3, 0xfc(r30)
    li r4, 0x1c7
    li r5, 0x1
    li r6, 0x0
    bl Sprite_SetupAnim
    clFlowCup_Update_L_801C85AC:
    lbz r0, 0x118(r30)
    lfs f0, lbl_806D9C94(r2)
    lfs f1, 0x120(r30)
    cmplwi r0, 0x0
    fadds f2, f0, f1
    bne clFlowCup_Update_L_801C85CC
    lfs f0, lbl_806D9CD4(r2)
    fadds f2, f0, f1
    clFlowCup_Update_L_801C85CC:
    lis r3, lbl_8049AD58@ha
    li r0, 0x2
    addi r4, r3, lbl_8049AD58@l
    mr r5, r30
    mr r6, r30
    mtctr r0
    clFlowCup_Update_L_801C85E4:
    lfs f1, 0x120(r30)
    lfs f0, 0x4(r4)
    lwz r3, 0x2c(r5)
    fadds f0, f1, f0
    stfs f0, 0xc(r3)
    lfs f0, 0x4(r4)
    lwz r3, 0x124(r6)
    fadds f0, f2, f0
    stfs f0, 0xc(r3)
    lfs f1, 0x120(r30)
    lfs f0, 0x10(r4)
    lwz r3, 0x3c(r5)
    fadds f0, f1, f0
    stfs f0, 0xc(r3)
    lfs f0, 0x10(r4)
    lwz r3, 0x128(r6)
    fadds f0, f2, f0
    stfs f0, 0xc(r3)
    lfs f1, 0x120(r30)
    lfs f0, 0x1c(r4)
    lwz r3, 0x4c(r5)
    fadds f0, f1, f0
    stfs f0, 0xc(r3)
    lfs f0, 0x1c(r4)
    lwz r3, 0x12c(r6)
    fadds f0, f2, f0
    stfs f0, 0xc(r3)
    lwz r3, 0x5c(r5)
    addi r5, r5, 0x40
    lfs f1, 0x120(r30)
    lfs f0, 0x28(r4)
    fadds f0, f1, f0
    stfs f0, 0xc(r3)
    lfs f0, 0x28(r4)
    addi r4, r4, 0x30
    lwz r3, 0x130(r6)
    addi r6, r6, 0x10
    fadds f0, f2, f0
    stfs f0, 0xc(r3)
    bdnz clFlowCup_Update_L_801C85E4
    lfs f0, lbl_806D9CC4(r2)
    lwz r3, 0x148(r30)
    fadds f0, f0, f2
    stfs f0, 0xc(r3)
    lwz r3, 0x14c(r30)
    stfs f0, 0xc(r3)
    lwz r3, 0x14(r30)
    cmpwi r3, 0xa
    blt clFlowCup_Update_L_801C86E8
    subi r3, r3, 0xa
    lis r0, 0x4330
    xoris r3, r3, 0x8000
    stw r0, 0x10(r1)
    lfd f2, lbl_806D9C98(r2)
    stw r3, 0x14(r1)
    lfs f1, lbl_806D9CD0(r2)
    lfd f0, 0x10(r1)
    lfs f3, lbl_806D9C94(r2)
    fsubs f2, f0, f2
    lfs f0, lbl_806D9CDC(r2)
    lwz r3, 0x150(r30)
    fdivs f1, f2, f1
    fmadds f0, f3, f1, f0
    stfs f0, 0xc(r3)
    b clFlowCup_Update_L_801C86F4
    clFlowCup_Update_L_801C86E8:
    lfs f0, lbl_806D9CDC(r2)
    lwz r3, 0x150(r30)
    stfs f0, 0xc(r3)
    clFlowCup_Update_L_801C86F4:
    lwz r3, 0xfc(r30)
    cmplwi r3, 0x0
    beq clFlowCup_Update_L_801C871C
    lfs f2, lbl_806D9CE0(r2)
    lfs f0, 0x11c(r30)
    lfs f1, lbl_806D9C7C(r2)
    fadds f0, f2, f0
    stfs f0, 0xc(r3)
    lwz r3, 0xfc(r30)
    bl Sprite_AdvanceAnim
    clFlowCup_Update_L_801C871C:
    lwz r3, 0xf8(r30)
    cmplwi r3, 0x0
    beq clFlowCup_Update_L_801C8744
    lfs f2, lbl_806D9C74(r2)
    lfs f0, 0x120(r30)
    lfs f1, lbl_806D9C7C(r2)
    fadds f0, f2, f0
    stfs f0, 0xc(r3)
    lwz r3, 0xf8(r30)
    bl Sprite_AdvanceAnim
    clFlowCup_Update_L_801C8744:
    lwz r3, 0x18(r30)
    cmplwi r3, 0x0
    beq clFlowCup_Update_L_801C8774
    lfs f2, lbl_806D9CC4(r2)
    lfs f1, 0x120(r30)
    lfs f0, lbl_806D9CC8(r2)
    fadds f2, f2, f1
    lfs f1, lbl_806D9C7C(r2)
    stfs f2, 0xc(r3)
    stfs f0, 0x10(r3)
    lwz r3, 0x18(r30)
    bl Sprite_AdvanceAnim
    clFlowCup_Update_L_801C8774:
    li r29, 0x0
    clFlowCup_Update_L_801C8778:
    mr r3, r30
    mr r4, r29
    bl fn_801C6744
    addi r29, r29, 0x1
    cmpwi r29, 0x9
    blt clFlowCup_Update_L_801C8778
    lwz r3, 0xb0(r30)
    cmplwi r3, 0x0
    beq clFlowCup_Update_L_801C8854
    lfs f1, lbl_806D9C7C(r2)
    bl Sprite_AdvanceAnim
    clrlwi. r0, r3, 24
    bne clFlowCup_Update_L_801C8854
    lwz r3, 0xb4(r30)
    cmpwi r3, 0x0
    bne clFlowCup_Update_L_801C8828
    addi r0, r3, 0x1
    stw r0, 0xb4(r30)
    lwz r0, 0xb0(r30)
    lwz r3, 0xbc(r30)
    cmplwi r0, 0x0
    beq clFlowCup_Update_L_801C8828
    lwz r0, 0xb4(r30)
    cmpwi r0, 0x1
    bne clFlowCup_Update_L_801C8828
    stw r3, 0xbc(r30)
    li r4, 0x183
    li r5, 0x0
    li r6, 0x0
    lwz r3, 0xb0(r30)
    bl Sprite_SetupAnim
    lwz r0, 0xbc(r30)
    lis r3, lbl_8049ADD0@ha
    addi r5, r3, lbl_8049ADD0@l
    lwz r3, 0xb0(r30)
    slwi r0, r0, 1
    li r4, 0x1744
    lhax r5, r5, r0
    bl Sprite_SetAnimParam
    lwz r3, 0xb0(r30)
    bl fn_801A0550
    lwz r3, 0xb0(r30)
    li r4, 0x1
    bl fn_8019FF6C
    clFlowCup_Update_L_801C8828:
    lwz r0, 0xb4(r30)
    cmpwi r0, 0x2
    bne clFlowCup_Update_L_801C8854
    lwz r3, 0xb0(r30)
    li r4, 0x1
    bl Sprite_Destroy
    li r0, 0x0
    stw r0, 0xb0(r30)
    lwz r3, 0xb4(r30)
    addi r0, r3, 0x1
    stw r0, 0xb4(r30)
    clFlowCup_Update_L_801C8854:
    mr r31, r30
    mr r29, r30
    li r28, 0x0
    clFlowCup_Update_L_801C8860:
    lwz r0, 0xc4(r31)
    cmpwi r0, -0x1
    beq clFlowCup_Update_L_801C8880
    slwi r3, r0, 2
    lfs f1, lbl_806D9C7C(r2)
    addi r0, r3, 0xd8
    lwzx r3, r29, r0
    bl Sprite_AdvanceAnim
    clFlowCup_Update_L_801C8880:
    addi r28, r28, 0x1
    addi r29, r29, 0x8
    cmpwi r28, 0x4
    addi r31, r31, 0x4
    blt clFlowCup_Update_L_801C8860
    lwz r3, 0x1c(r30)
    cmplwi r3, 0x0
    beq clFlowCup_Update_L_801C88A8
    lfs f1, lbl_806D9C7C(r2)
    bl Sprite_AdvanceAnim
    clFlowCup_Update_L_801C88A8:
    lwz r3, 0x108(r30)
    cmplwi r3, 0x0
    beq clFlowCup_Update_L_801C88BC
    lfs f1, lbl_806D9C7C(r2)
    bl Sprite_AdvanceAnim
    clFlowCup_Update_L_801C88BC:
    lwz r3, 0x10c(r30)
    cmplwi r3, 0x0
    beq clFlowCup_Update_L_801C88D0
    lfs f1, lbl_806D9C7C(r2)
    bl Sprite_AdvanceAnim
    clFlowCup_Update_L_801C88D0:
    li r3, -0x1
    clFlowCup_Update_L_801C88D4:
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    lwz r28, 0x20(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}



/* === extracted from auto_clFlowCup_Dtor_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void MemoryManager_TimedFree();
extern void SetScreenBrightness();
extern void Sprite_Destroy();
extern void dtor_801BA14C();
extern void fn_80120A08();
extern void fn_80169C44();
extern void fn_801A1678();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_pInputState;
extern unsigned int g_roundIndex;
extern unsigned int lbl_806D9CA4;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8049ADE4[];
extern unsigned int lbl_8049AE5C[];

/* --- function index (1 fns, .text 0x801C88F4..0x801C8AB4) ---
 * [  0] 0x801C88F4 size:0x1C0   global clFlowCup_Dtor
 */

/* --- forward decls --- */
asm void clFlowCup_Dtor(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clFlowCup_Dtor[8] = {
    0x28, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowCup_Dtor = {
    (void *)&clFlowCup_Dtor, 0x000001C0, (void *)extab_clFlowCup_Dtor
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clFlowCup_Dtor(void) { /* 0x801C88F4 size:0x1C0 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stmw r27, 0xc(r1)
    mr. r30, r3
    mr r31, r4
    beq clFlowCup_Dtor_L_801C8A9C
    lis r3, lbl_8049AE5C@ha
    addi r0, r3, lbl_8049AE5C@l
    stw r0, 0x0(r30)
    bl fn_80169C44
    lbz r0, 0x118(r30)
    li r3, 0x0
    cmplwi r0, 0x1
    bne clFlowCup_Dtor_L_801C8934
    li r3, 0x4
    clFlowCup_Dtor_L_801C8934:
    lwz r4, g_pInputState(r13)
    stw r3, g_roundIndex(r13)
    cmplwi r4, 0x0
    bne clFlowCup_Dtor_L_801C894C
    li r0, 0x0
    b clFlowCup_Dtor_L_801C8950
    clFlowCup_Dtor_L_801C894C:
    mr r0, r4
    clFlowCup_Dtor_L_801C8950:
    cmplwi r0, 0x0
    beq clFlowCup_Dtor_L_801C8974
    cmplwi r4, 0x0
    bne clFlowCup_Dtor_L_801C8964
    li r4, 0x0
    clFlowCup_Dtor_L_801C8964:
    li r0, 0x0
    stb r0, 0x4(r4)
    stw r0, 0x18(r4)
    stw r0, 0x1c(r4)
    clFlowCup_Dtor_L_801C8974:
    lfs f1, lbl_806D9CA4(r2)
    bl SetScreenBrightness
    lis r3, lbl_8049ADE4@ha
    addi r3, r3, lbl_8049ADE4@l
    lha r3, 0x2(r3)
    bl fn_80120A08
    lis r3, lbl_8049ADE4@ha
    addi r3, r3, lbl_8049ADE4@l
    lha r3, 0x0(r3)
    bl fn_80120A08
    lwz r3, 0x108(r30)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x10c(r30)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x18(r30)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0xf8(r30)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0xfc(r30)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x1c(r30)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0xb0(r30)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x148(r30)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x14c(r30)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x150(r30)
    li r4, 0x1
    bl Sprite_Destroy
    mr r29, r30
    mr r28, r30
    li r27, 0x0
    clFlowCup_Dtor_L_801C8A20:
    lwz r3, 0x2c(r29)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x124(r28)
    li r4, 0x1
    bl Sprite_Destroy
    addi r27, r27, 0x1
    addi r28, r28, 0x4
    cmpwi r27, 0x9
    addi r29, r29, 0x10
    blt clFlowCup_Dtor_L_801C8A20
    li r27, 0x0
    mr r28, r30
    clFlowCup_Dtor_L_801C8A54:
    lwz r3, 0xd8(r28)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0xdc(r28)
    li r4, 0x1
    bl Sprite_Destroy
    addi r27, r27, 0x1
    addi r28, r28, 0x8
    cmpwi r27, 0x4
    blt clFlowCup_Dtor_L_801C8A54
    bl fn_801A1678
    mr r3, r30
    li r4, 0x0
    bl dtor_801BA14C
    extsh. r0, r31
    ble clFlowCup_Dtor_L_801C8A9C
    mr r3, r30
    bl MemoryManager_TimedFree
    clFlowCup_Dtor_L_801C8A9C:
    mr r3, r30
    lmw r27, 0xc(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}



/* === extracted from auto_clFlowCup_Init_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void InitBGM();
extern void InitRumbleController();
extern void InitializeFrameSelection();
extern void IsCardValid();
extern void PCBComm_PackAndTriggerCardSnapshot();
extern void PreloadResource();
extern void SetScreenBrightness();
extern void SetSyncTarget();
extern void SetupBgSprites();
extern void SpriteSystem_EnsureInit();
extern void Sprite_CreateWithParams();
extern void Sprite_InitWithAnim();
extern void Sprite_SetAnimParam();
extern void fn_801A0310();
extern void fn_801A0550();
extern void fn_801C64DC();
extern void fn_801D5B8C();
extern void fn_801D5C88();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_ccClass;
extern unsigned int g_pInputState;
extern unsigned int lbl_806D9C70;
extern unsigned int lbl_806D9C74;
extern unsigned int lbl_806D9C78;
extern unsigned int lbl_806D9C80;
extern unsigned int lbl_806D9C88;
extern unsigned int lbl_806D9C94;
extern unsigned int lbl_806D9CA4;
extern unsigned int lbl_806D9CC8;
extern unsigned int lbl_806D9CD8;
extern unsigned int lbl_806D9CDC;
extern unsigned int lbl_806D9CE0;
extern unsigned int lbl_806D9CE4;
extern unsigned int lbl_806D9CE8;
extern unsigned int lbl_806D9CEC;
extern unsigned int lbl_806D9CF0;
extern unsigned int lbl_806D9CF4;
extern unsigned int lbl_806D9CF8;
extern unsigned int lbl_806D9CFC;
extern unsigned int lbl_806D9D00;
extern unsigned int lbl_806D9D04;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int g_playerData[];
extern unsigned int lbl_8049AD58[];

/* --- function index (1 fns, .text 0x801C8AB4..0x801C9288) ---
 * [  0] 0x801C8AB4 size:0x7D4   global clFlowCup_Init
 */

/* --- forward decls --- */
asm void clFlowCup_Init(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();
extern void dtor_801BA14C();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; unsigned int f29; unsigned int f30; unsigned int f31; unsigned int f32; unsigned int f33; unsigned int f34; unsigned int f35; unsigned int f36; unsigned int f37; unsigned int f38; unsigned int f39; unsigned int f40; unsigned int f41; unsigned int f42; unsigned int f43; unsigned int f44; unsigned int f45; unsigned int f46; unsigned int f47; unsigned int f48; unsigned int f49; unsigned int f50; unsigned int f51; unsigned int f52; unsigned int f53; unsigned int f54; unsigned int f55; unsigned int f56; unsigned int f57; unsigned int f58; unsigned int f59; unsigned int f60; unsigned int f61; unsigned int f62; unsigned int f63; unsigned int f64; unsigned int f65; unsigned int f66; unsigned int f67; unsigned int f68; unsigned int f69; unsigned int f70; unsigned int f71; unsigned int f72; unsigned int f73; unsigned int f74; unsigned int f75; unsigned int f76; void *f77; unsigned int f78; unsigned int f79; void *f80; unsigned int f81; void *f82; unsigned int f83; unsigned int f84; void *f85; unsigned int f86; void *f87; unsigned int f88; unsigned int f89; void *f90; unsigned int f91; void *f92; unsigned int f93; unsigned int f94; void *f95; unsigned int f96; void *f97; unsigned int f98; unsigned int f99; void *f100; unsigned int f101; void *f102; unsigned int f103; unsigned int f104; void *f105; unsigned int f106; void *f107; unsigned int f108; unsigned int f109; void *f110; unsigned int f111; void *f112; unsigned int f113; unsigned int f114; void *f115; unsigned int f116; void *f117; unsigned int f118; unsigned int f119; void *f120; unsigned int f121; void *f122; unsigned int f123; unsigned int f124; void *f125; unsigned int f126; void *f127; unsigned int f128; unsigned int f129; void *f130; unsigned int f131; void *f132; unsigned int f133; unsigned int f134; void *f135; unsigned int f136; void *f137; unsigned int f138; unsigned int f139; void *f140; unsigned int f141; void *f142; unsigned int f143; unsigned int f144; void *f145; unsigned int f146; void *f147; unsigned int f148; unsigned int f149; void *f150; unsigned int f151; void *f152; unsigned int f153; unsigned int f154; void *f155; unsigned int f156; void *f157; unsigned int f158; unsigned int f159; void *f160; unsigned int f161; void *f162; unsigned int f163; unsigned int f164; void *f165; } extab_clFlowCup_Init = { 0x308A0000, 0x0000003C, 0x00930138, 0x000002B4, 0x00000130, 0x000002C0, 0x00000138, 0x000002EC, 0x00000144, 0x000002F8, 0x00000138, 0x00000324, 0x00000158, 0x00000330, 0x00000138, 0x0000035C, 0x0000016C, 0x00000368, 0x00000138, 0x00000394, 0x00000180, 0x000003A0, 0x00000138, 0x000003CC, 0x00000194, 0x000003D8, 0x00000138, 0x00000404, 0x000001A8, 0x00000410, 0x00000138, 0x0000043C, 0x000001BC, 0x0000045C, 0x00000138, 0x00000488, 0x000001D0, 0x00000498, 0x000F0138, 0x000004EC, 0x000001E4, 0x00000504, 0x00110138, 0x00000574, 0x000001F8, 0x00000580, 0x00000138, 0x000005AC, 0x0000020C, 0x000005B8, 0x00000138, 0x000005E4, 0x00000220, 0x000005FC, 0x00000138, 0x00000628, 0x00000234, 0x00000634, 0x00000138, 0x00000660, 0x00000248, 0x00000670, 0x00000138, 0x0000069C, 0x0000025C, 0x000006A8, 0x00000138, 0x000006D4, 0x00000270, 0x000006E8, 0x001D0138, 0x00000774, 0x00000284, 0x00000788, 0x00090138, 0x00000000, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowCup_Init = {
    (void *)&clFlowCup_Init, 0x000007D4, (void *)&extab_clFlowCup_Init
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clFlowCup_Init(void) { /* 0x801C8AB4 size:0x7D4 */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stfd f31, 0x30(r1)
    psq_st f31, 0x38(r1), 0, 0
    stfd f30, 0x20(r1)
    psq_st f30, 0x28(r1), 0, 0
    stmw r26, 0x8(r1)
    lis r4, lbl_8049AD58@ha
    mr r31, r3
    addi r30, r4, lbl_8049AD58@l
    bl InitializeFrameSelection
    addi r0, r30, 0x104
    stw r0, 0x0(r31)
    bl SpriteSystem_EnsureInit
    bl PCBComm_PackAndTriggerCardSnapshot
    li r3, 0x15
    bl SetSyncTarget
    lha r3, 0x8c(r30)
    bl PreloadResource
    addi r3, r30, 0x8c
    lha r3, 0x2(r3)
    bl PreloadResource
    li r3, 0x1736
    bl PreloadResource
    li r3, 0x1ae3
    bl PreloadResource
    li r3, 0x1777
    bl PreloadResource
    li r3, 0x178b
    bl PreloadResource
    li r3, 0x194c
    bl PreloadResource
    li r3, 0x195e
    bl PreloadResource
    li r3, 0x196f
    bl PreloadResource
    li r3, 0x197c
    bl PreloadResource
    li r3, 0x1780
    bl PreloadResource
    li r3, 0x1794
    bl PreloadResource
    li r3, 0x1744
    bl PreloadResource
    li r3, 0x175e
    bl PreloadResource
    li r3, 0x1ea2
    bl PreloadResource
    li r3, 0x1eaa
    bl PreloadResource
    li r3, 0x1eb2
    bl PreloadResource
    li r3, 0x1eba
    bl PreloadResource
    li r3, 0x1863
    bl PreloadResource
    li r3, 0x18ba
    bl PreloadResource
    li r0, 0x3
    li r11, 0x0
    mtctr r0
    clFlowCup_Init_L_801C8BAC:
    addi r0, r11, 0x20
    li r10, 0x0
    stwx r10, r31, r0
    addi r4, r11, 0x24
    addi r3, r11, 0x28
    addi r0, r11, 0x2c
    stwx r10, r31, r4
    addi r9, r11, 0x30
    addi r8, r11, 0x34
    addi r7, r11, 0x38
    stwx r10, r31, r3
    addi r6, r11, 0x3c
    addi r5, r11, 0x40
    addi r4, r11, 0x44
    stwx r10, r31, r0
    addi r3, r11, 0x48
    addi r0, r11, 0x4c
    addi r11, r11, 0x30
    stwx r10, r31, r9
    stwx r10, r31, r8
    stwx r10, r31, r7
    stwx r10, r31, r6
    stwx r10, r31, r5
    stwx r10, r31, r4
    stwx r10, r31, r3
    stwx r10, r31, r0
    bdnz clFlowCup_Init_L_801C8BAC
    stw r10, 0x4(r31)
    li r0, -0x1
    lis r3, g_playerData@ha
    lfs f1, lbl_806D9C80(r2)
    stw r0, 0x8(r31)
    addi r3, r3, g_playerData@l
    lfs f0, lbl_806D9CD8(r2)
    stw r10, 0xc(r31)
    stb r10, 0x10(r31)
    stw r10, 0x14(r31)
    stw r10, 0x18(r31)
    stw r10, 0xb0(r31)
    stw r10, 0xb4(r31)
    stw r10, 0x1c(r31)
    stw r10, 0xb8(r31)
    stb r10, 0xc0(r31)
    stfs f1, 0x114(r31)
    stfs f0, 0xd4(r31)
    lwz r4, g_ccClass(r13)
    bl fn_801D5C88
    stb r3, 0x118(r31)
    li r0, 0x0
    lfs f0, lbl_806D9C80(r2)
    addi r3, r13, -0x5A3C  /* lbl_806D12E4 */
    stw r0, 0xf8(r31)
    stw r0, 0xfc(r31)
    stw r0, 0x108(r31)
    stw r0, 0x10c(r31)
    stfs f0, 0x120(r31)
    stfs f0, 0x11c(r31)
    stw r0, 0x100(r31)
    stw r0, 0x104(r31)
    stb r0, 0x154(r31)
    stb r0, 0x155(r31)
    lwz r0, g_ccClass(r13)
    lbzx r0, r3, r0
    stb r0, 0x154(r31)
    lbz r0, 0x118(r31)
    cmplwi r0, 0x1
    bne clFlowCup_Init_L_801C8CC0
    li r0, 0x1
    stb r0, 0x154(r31)
    clFlowCup_Init_L_801C8CC0:
    lis r3, g_playerData@ha
    li r29, 0x0
    addi r0, r3, g_playerData@l
    li r27, 0x1
    mr r28, r0
    clFlowCup_Init_L_801C8CD4:
    lwz r4, g_ccClass(r13)
    mr r3, r28
    mr r5, r27
    li r6, 0x7
    bl fn_801D5B8C
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne clFlowCup_Init_L_801C8CF8
    addi r29, r29, 0x1
    clFlowCup_Init_L_801C8CF8:
    addi r27, r27, 0x1
    cmpwi r27, 0x9
    blt clFlowCup_Init_L_801C8CD4
    li r0, 0x7
    srawi r4, r29, 31
    srwi r3, r0, 31
    subfc r0, r0, r29
    adde r0, r4, r3
    stb r0, 0x155(r31)
    bl IsCardValid
    clrlwi. r0, r3, 24
    bne clFlowCup_Init_L_801C8D34
    li r0, 0x1
    stb r0, 0x155(r31)
    stb r0, 0x154(r31)
    clFlowCup_Init_L_801C8D34:
    li r3, 0x30
    bl Alloc
    mr. r27, r3
    beq clFlowCup_Init_L_801C8D68
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x186
    lfs f5, lbl_806D9C80(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f1, lbl_806D9CE4(r2)
    fmr f6, f5
    lfs f2, lbl_806D9CE8(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C8D68:
    stw r27, 0xd8(r31)
    li r3, 0x30
    bl Alloc
    mr. r27, r3
    beq clFlowCup_Init_L_801C8DA0
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x187
    lfs f5, lbl_806D9C80(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f1, lbl_806D9CC8(r2)
    fmr f6, f5
    lfs f2, lbl_806D9CE8(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C8DA0:
    stw r27, 0xe0(r31)
    li r3, 0x30
    bl Alloc
    mr. r27, r3
    beq clFlowCup_Init_L_801C8DD8
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x188
    lfs f5, lbl_806D9C80(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f1, lbl_806D9CEC(r2)
    fmr f6, f5
    lfs f2, lbl_806D9CE8(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C8DD8:
    stw r27, 0xe8(r31)
    li r3, 0x30
    bl Alloc
    mr. r27, r3
    beq clFlowCup_Init_L_801C8E10
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x189
    lfs f5, lbl_806D9C80(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f1, lbl_806D9CF0(r2)
    fmr f6, f5
    lfs f2, lbl_806D9CE8(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C8E10:
    stw r27, 0xf0(r31)
    li r3, 0x30
    bl Alloc
    mr. r27, r3
    beq clFlowCup_Init_L_801C8E48
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x18a
    lfs f5, lbl_806D9C80(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f1, lbl_806D9CE4(r2)
    fmr f6, f5
    lfs f2, lbl_806D9CE8(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C8E48:
    stw r27, 0xdc(r31)
    li r3, 0x30
    bl Alloc
    mr. r27, r3
    beq clFlowCup_Init_L_801C8E80
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x18b
    lfs f5, lbl_806D9C80(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f1, lbl_806D9CC8(r2)
    fmr f6, f5
    lfs f2, lbl_806D9CE8(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C8E80:
    stw r27, 0xe4(r31)
    li r3, 0x30
    bl Alloc
    mr. r27, r3
    beq clFlowCup_Init_L_801C8EB8
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x18c
    lfs f5, lbl_806D9C80(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f1, lbl_806D9CEC(r2)
    fmr f6, f5
    lfs f2, lbl_806D9CE8(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C8EB8:
    stw r27, 0xec(r31)
    li r3, 0x30
    bl Alloc
    mr. r27, r3
    beq clFlowCup_Init_L_801C8EF0
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x18d
    lfs f5, lbl_806D9C80(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f1, lbl_806D9CF0(r2)
    fmr f6, f5
    lfs f2, lbl_806D9CE8(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C8EF0:
    stw r27, 0xf4(r31)
    li r0, -0x1
    li r3, 0x30
    stw r0, 0xc4(r31)
    stw r0, 0xc8(r31)
    stw r0, 0xcc(r31)
    stw r0, 0xd0(r31)
    bl Alloc
    mr. r27, r3
    beq clFlowCup_Init_L_801C8F3C
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x1de
    lfs f5, lbl_806D9C80(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f1, lbl_806D9CF4(r2)
    fmr f6, f5
    lfs f2, lbl_806D9C78(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C8F3C:
    stw r27, 0x1c(r31)
    li r4, 0x175b
    lwz r3, 0x1c(r31)
    bl fn_801A0310
    stw r3, 0x100(r31)
    li r4, 0x1ea3
    lwz r3, 0x1c(r31)
    bl fn_801A0310
    stw r3, 0x104(r31)
    mr r3, r31
    lwz r4, 0x4(r31)
    bl fn_801C64DC
    lfs f30, lbl_806D9C94(r2)
    addi r28, r30, 0x0
    lfs f31, lbl_806D9C70(r2)
    li r27, 0x0
    li r29, 0x0
    clFlowCup_Init_L_801C8F80:
    li r3, 0x30
    bl Alloc
    mr. r26, r3
    beq clFlowCup_Init_L_801C8FA0
    li r4, 0x180
    li r5, 0x1
    li r6, 0x0
    bl Sprite_InitWithAnim
    clFlowCup_Init_L_801C8FA0:
    addi r0, r29, 0x124
    li r4, 0x1777
    stwx r26, r31, r0
    lwzx r3, r31, r0
    lha r5, 0x0(r28)
    bl Sprite_SetAnimParam
    lfs f0, 0x4(r28)
    addi r0, r29, 0x124
    lfs f1, 0x8(r28)
    addi r27, r27, 0x1
    fadds f0, f30, f0
    lwzx r3, r31, r0
    cmpwi r27, 0x9
    addi r29, r29, 0x4
    addi r28, r28, 0xc
    stfs f0, 0xc(r3)
    stfs f1, 0x10(r3)
    lwzx r3, r31, r0
    stfs f31, 0x14(r3)
    stfs f31, 0x18(r3)
    blt clFlowCup_Init_L_801C8F80
    li r3, 0x30
    bl Alloc
    mr. r26, r3
    beq clFlowCup_Init_L_801C9028
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x18f
    lfs f1, lbl_806D9CF8(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f2, lbl_806D9CC8(r2)
    fmr f6, f3
    lfs f5, lbl_806D9C80(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C9028:
    stw r26, 0x148(r31)
    li r3, 0x30
    bl Alloc
    mr. r26, r3
    beq clFlowCup_Init_L_801C9060
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x18e
    lfs f1, lbl_806D9CFC(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f2, lbl_806D9D00(r2)
    fmr f6, f3
    lfs f5, lbl_806D9C80(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C9060:
    stw r26, 0x14c(r31)
    li r3, 0x30
    bl Alloc
    mr. r26, r3
    beq clFlowCup_Init_L_801C9098
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x1c7
    lfs f1, lbl_806D9CDC(r2)
    li r5, 0x0
    fmr f4, f3
    lfs f2, lbl_806D9D04(r2)
    fmr f6, f3
    lfs f5, lbl_806D9C80(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C9098:
    stw r26, 0x150(r31)
    lbz r0, 0x118(r31)
    cmplwi r0, 0x1
    bne clFlowCup_Init_L_801C911C
    li r3, 0x30
    bl Alloc
    mr. r26, r3
    beq clFlowCup_Init_L_801C90DC
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x3a
    lfs f1, lbl_806D9C74(r2)
    li r5, 0x0
    fmr f4, f3
    lfs f2, lbl_806D9D00(r2)
    fmr f6, f3
    lfs f5, lbl_806D9C80(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C90DC:
    stw r26, 0xf8(r31)
    li r3, 0x30
    bl Alloc
    mr. r26, r3
    beq clFlowCup_Init_L_801C9114
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x1c7
    lfs f1, lbl_806D9CE0(r2)
    li r5, 0x0
    fmr f4, f3
    lfs f2, lbl_806D9D04(r2)
    fmr f6, f3
    lfs f5, lbl_806D9C80(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C9114:
    stw r26, 0xfc(r31)
    b clFlowCup_Init_L_801C919C
    clFlowCup_Init_L_801C911C:
    li r3, 0x30
    bl Alloc
    mr. r26, r3
    beq clFlowCup_Init_L_801C9150
    lfs f3, lbl_806D9C88(r2)
    li r4, 0x38
    lfs f1, lbl_806D9C74(r2)
    li r5, 0x0
    fmr f4, f3
    lfs f2, lbl_806D9D00(r2)
    fmr f6, f3
    lfs f5, lbl_806D9C80(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C9150:
    stw r26, 0xf8(r31)
    li r3, 0x30
    bl Alloc
    mr. r26, r3
    beq clFlowCup_Init_L_801C9188
    lfs f3, lbl_806D9C88(r2)
    li r4, 0xc8
    lfs f1, lbl_806D9CE0(r2)
    li r5, 0x0
    fmr f4, f3
    lfs f2, lbl_806D9D04(r2)
    fmr f6, f3
    lfs f5, lbl_806D9C80(r2)
    bl Sprite_CreateWithParams
    clFlowCup_Init_L_801C9188:
    stw r26, 0xfc(r31)
    li r4, 0x1ad4
    li r5, 0x1ae3
    lwz r3, 0xfc(r31)
    bl Sprite_SetAnimParam
    clFlowCup_Init_L_801C919C:
    lwz r4, g_pInputState(r13)
    cmplwi r4, 0x0
    bne clFlowCup_Init_L_801C91B0
    li r0, 0x0
    b clFlowCup_Init_L_801C91B4
    clFlowCup_Init_L_801C91B0:
    mr r0, r4
    clFlowCup_Init_L_801C91B4:
    cmplwi r0, 0x0
    beq clFlowCup_Init_L_801C91DC
    cmplwi r4, 0x0
    bne clFlowCup_Init_L_801C91C8
    li r4, 0x0
    clFlowCup_Init_L_801C91C8:
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x4(r4)
    stw r0, 0x18(r4)
    stw r0, 0x1c(r4)
    clFlowCup_Init_L_801C91DC:
    bl InitBGM
    lfs f1, lbl_806D9CA4(r2)
    bl SetScreenBrightness
    li r3, 0x1
    bl SetupBgSprites
    lwz r0, 0xb0(r31)
    cmplwi r0, 0x0
    bne clFlowCup_Init_L_801C9258
    li r0, 0x0
    li r3, 0x30
    stw r0, 0xb4(r31)
    stw r0, 0xbc(r31)
    bl Alloc
    mr. r26, r3
    beq clFlowCup_Init_L_801C9228
    li r4, 0x36
    li r5, 0x0
    li r6, 0x0
    bl Sprite_InitWithAnim
    clFlowCup_Init_L_801C9228:
    stw r26, 0xb0(r31)
    li r4, 0x1744
    lwz r3, 0xb0(r31)
    lha r5, 0x78(r30)
    bl Sprite_SetAnimParam
    lwz r3, 0xb0(r31)
    bl fn_801A0550
    lwz r3, 0xb0(r31)
    lfs f1, lbl_806D9C74(r2)
    lfs f0, lbl_806D9C78(r2)
    stfs f1, 0xc(r3)
    stfs f0, 0x10(r3)
    clFlowCup_Init_L_801C9258:
    li r3, 0x1
    bl InitRumbleController
    mr r3, r31
    psq_l f31, 0x38(r1), 0, 0
    lfd f31, 0x30(r1)
    psq_l f30, 0x28(r1), 0, 0
    lfd f30, 0x20(r1)
    lmw r26, 0x8(r1)
    lwz r0, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}

#ifdef __cplusplus
}
#endif

