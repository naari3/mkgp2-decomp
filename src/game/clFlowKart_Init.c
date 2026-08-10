/* === extracted from auto_clFlowKart_Init_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void CObj_ApplyViewport();
extern void CObj_LoadIntoGX();
extern void GetCoinMilage();
extern void GetTextureByIdAndLang();
extern void InitRumbleController();
extern void InitializeFrameSelection();
extern void KartDriver_New_Full();
extern void MTXIdentity();
extern void PSMTXConcat();
extern void PSMTXScale();
extern void PSMTXTrans();
extern void PreloadResource();
extern void RenderObj_ItemStateMachine_Timed();
extern void ResCtrl_Init();
extern void Scene3D_Init();
extern void SceneModel_Init();
extern void SetScreenBrightness();
extern void SetSyncTarget();
extern void TexMgr_Init();
extern void TexMgr_SetTexture();
extern void fn_801B8918();
extern void fn_801F93EC();
extern void fn_8025D770();
extern void isJapanese();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_characterId;
extern unsigned int g_pInputState;
extern unsigned int lbl_806DA130;
extern unsigned int lbl_806DA134;
extern unsigned int lbl_806DA138;
extern unsigned int lbl_806DA13C;
extern unsigned int lbl_806DA144;
extern unsigned int lbl_806DA14C;
extern unsigned int lbl_806DA154;
extern unsigned int lbl_806DA15C;
extern unsigned int lbl_806DA174;
extern unsigned int lbl_806DA178;
extern unsigned int lbl_806DA17C;
extern unsigned int lbl_806DA180;
extern unsigned int lbl_806DA184;
extern unsigned int lbl_806DA188;
extern unsigned int lbl_806DA18C;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int g_playerData[];
extern unsigned int lbl_8039E508[];
extern unsigned int lbl_8049BBD0[];

/* --- function index (1 fns, .text 0x801D83D4..0x801D878C) ---
 * [  0] 0x801D83D4 size:0x3B8   global clFlowKart_Init
 */

/* --- forward decls --- */
asm void clFlowKart_Init(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();
extern void dtor_80082960();
extern void dtor_801BA14C();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; void *f27; unsigned int f28; unsigned int f29; void *f30; unsigned int f31; unsigned int f32; void *f33; unsigned int f34; void *f35; unsigned int f36; unsigned int f37; void *f38; unsigned int f39; unsigned int f40; void *f41; unsigned int f42; unsigned int f43; void *f44; unsigned int f45; } extab_clFlowKart_Init = { 0x200A0000, 0x00000040, 0x0000007C, 0x00000048, 0x000D0070, 0x0000008C, 0x00000068, 0x00000098, 0x00000070, 0x000000AC, 0x00000088, 0x000000F8, 0x00350070, 0x000001F0, 0x00000094, 0x000001FC, 0x00000070, 0x00000220, 0x000000A0, 0x00000240, 0x001D0070, 0x000002C0, 0x000000AC, 0x000002E0, 0x002D0070, 0x00000000, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x0780001E, 0x00000084, (void *)&dtor_80082960, 0x8680001E, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x01000070, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x01000070, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x01000070, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x01000070 };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowKart_Init = {
    (void *)&clFlowKart_Init, 0x000003B8, (void *)&extab_clFlowKart_Init
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clFlowKart_Init(void) { /* 0x801D83D4 size:0x3B8 */
    nofralloc
    stwu r1, -0xc0(r1)
    mflr r0
    lis r4, lbl_8039E508@ha
    stw r0, 0xc4(r1)
    stw r31, 0xbc(r1)
    addi r31, r4, lbl_8039E508@l
    stw r30, 0xb8(r1)
    mr r30, r3
    stw r29, 0xb4(r1)
    stw r28, 0xb0(r1)
    bl InitializeFrameSelection
    lis r4, lbl_8049BBD0@ha
    addi r3, r30, 0x84
    addi r0, r4, lbl_8049BBD0@l
    stw r0, 0x0(r30)
    bl ResCtrl_Init
    li r3, 0xf
    bl SetSyncTarget
    li r3, 0x167f
    bl PreloadResource
    li r0, 0x1
    li r4, -0x1
    stw r0, 0x4(r30)
    li r0, 0x0
    li r3, 0x3084
    stw r4, 0x8(r30)
    stw r0, 0xc(r30)
    stb r0, 0x10(r30)
    stw r0, 0x24(r30)
    stw r0, 0x28(r30)
    bl Alloc
    mr. r29, r3
    beq clFlowKart_Init_L_801D8460
    addi r4, r31, 0x4e0
    bl Scene3D_Init
    clFlowKart_Init_L_801D8460:
    stw r29, 0x1c(r30)
    li r3, 0x28
    bl Alloc
    mr. r29, r3
    beq clFlowKart_Init_L_801D8480
    addi r4, r31, 0x4e0
    li r5, 0x0
    bl SceneModel_Init
    clFlowKart_Init_L_801D8480:
    stw r29, 0x20(r30)
    li r0, 0x0
    lfs f2, lbl_806DA174(r2)
    addi r4, r1, 0x8
    stw r0, 0x68(r30)
    lfs f1, lbl_806DA13C(r2)
    stw r0, 0x6c(r30)
    lfs f0, lbl_806DA178(r2)
    stw r0, 0x70(r30)
    stfs f2, 0x18(r30)
    stw r0, 0x14(r30)
    stw r0, 0x74(r30)
    stw r0, 0x78(r30)
    stw r0, 0x7c(r30)
    stfs f1, 0x8(r1)
    stfs f1, 0xc(r1)
    stfs f0, 0x10(r1)
    lwz r3, 0x1c(r30)
    bl CObj_LoadIntoGX
    lfs f0, lbl_806DA13C(r2)
    addi r4, r1, 0x8
    stfs f0, 0x8(r1)
    stfs f0, 0xc(r1)
    stfs f0, 0x10(r1)
    lwz r3, 0x1c(r30)
    bl CObj_ApplyViewport
    lfs f1, lbl_806DA130(r2)
    addi r3, r1, 0x14
    lwz r29, g_characterId(r13)
    fmr f2, f1
    fmr f3, f1
    bl PSMTXScale
    lfs f0, 0x4a4(r31)
    addi r4, r31, 0x4a4
    lfs f1, 0x4(r4)
    addi r3, r1, 0x74
    stfs f0, 0x5c(r30)
    lfs f0, 0x8(r4)
    stfs f1, 0x60(r30)
    stfs f0, 0x64(r30)
    lfs f1, 0x5c(r30)
    lfs f2, 0x60(r30)
    lfs f3, 0x64(r30)
    bl PSMTXTrans
    addi r3, r30, 0x2c
    bl MTXIdentity
    addi r4, r30, 0x2c
    addi r3, r1, 0x14
    mr r5, r4
    bl PSMTXConcat
    lfs f1, lbl_806DA134(r2)
    addi r3, r1, 0x44
    li r4, 0x78
    bl fn_8025D770
    addi r4, r30, 0x2c
    addi r3, r1, 0x44
    mr r5, r4
    bl PSMTXConcat
    lfs f1, lbl_806DA138(r2)
    addi r3, r1, 0x44
    li r4, 0x79
    bl fn_8025D770
    addi r4, r30, 0x2c
    addi r3, r1, 0x44
    mr r5, r4
    bl PSMTXConcat
    addi r4, r30, 0x2c
    addi r3, r1, 0x74
    mr r5, r4
    bl PSMTXConcat
    li r3, 0x384
    bl Alloc
    mr. r28, r3
    beq clFlowKart_Init_L_801D85C4
    mr r5, r29
    addi r6, r30, 0x2c
    li r4, 0x6
    li r7, 0x0
    li r8, 0x0
    li r9, 0x0
    bl KartDriver_New_Full
    clFlowKart_Init_L_801D85C4:
    stw r28, 0x24(r30)
    li r3, 0x384
    bl Alloc
    mr. r28, r3
    beq clFlowKart_Init_L_801D85F4
    mr r5, r29
    addi r6, r30, 0x2c
    li r4, 0x6
    li r7, 0x0
    li r8, 0x0
    li r9, 0x2
    bl KartDriver_New_Full
    clFlowKart_Init_L_801D85F4:
    stw r28, 0x28(r30)
    lwz r3, 0x24(r30)
    cmplwi r3, 0x0
    beq clFlowKart_Init_L_801D8614
    lfs f1, lbl_806DA13C(r2)
    li r4, 0x0
    fmr f2, f1
    bl RenderObj_ItemStateMachine_Timed
    clFlowKart_Init_L_801D8614:
    lwz r3, 0x28(r30)
    cmplwi r3, 0x0
    beq clFlowKart_Init_L_801D8630
    lfs f1, lbl_806DA13C(r2)
    li r4, 0x0
    fmr f2, f1
    bl RenderObj_ItemStateMachine_Timed
    clFlowKart_Init_L_801D8630:
    lwz r4, g_pInputState(r13)
    cmplwi r4, 0x0
    bne clFlowKart_Init_L_801D8644
    li r0, 0x0
    b clFlowKart_Init_L_801D8648
    clFlowKart_Init_L_801D8644:
    mr r0, r4
    clFlowKart_Init_L_801D8648:
    cmplwi r0, 0x0
    beq clFlowKart_Init_L_801D8670
    cmplwi r4, 0x0
    bne clFlowKart_Init_L_801D865C
    li r4, 0x0
    clFlowKart_Init_L_801D865C:
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x4(r4)
    stw r0, 0x18(r4)
    stw r0, 0x1c(r4)
    clFlowKart_Init_L_801D8670:
    lfs f1, lbl_806DA144(r2)
    bl SetScreenBrightness
    li r3, 0x1ae2
    bl fn_801B8918
    li r3, 0x230
    bl Alloc
    mr. r28, r3
    beq clFlowKart_Init_L_801D8694
    bl TexMgr_Init
    clFlowKart_Init_L_801D8694:
    stw r28, 0x80(r30)
    addi r3, r31, 0x464
    li r4, -0x1
    lwz r0, g_characterId(r13)
    slwi r0, r0, 2
    lwzx r3, r3, r0
    addi r3, r3, 0x95
    bl GetTextureByIdAndLang
    mr r4, r3
    lwz r3, 0x80(r30)
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    lwz r3, 0x80(r30)
    lfs f1, lbl_806DA17C(r2)
    lfs f2, lbl_806DA14C(r2)
    bl fn_801F93EC
    bl isJapanese
    cmpwi r3, 0x0
    bne clFlowKart_Init_L_801D86E8
    lfs f0, lbl_806DA180(r2)
    b clFlowKart_Init_L_801D86EC
    clFlowKart_Init_L_801D86E8:
    lfs f0, lbl_806DA184(r2)
    clFlowKart_Init_L_801D86EC:
    lwz r5, 0x80(r30)
    lis r3, g_playerData@ha
    li r4, 0x1d5c
    li r0, 0x1
    stfs f0, 0x22c(r5)
    addi r3, r3, g_playerData@l
    lfs f0, lbl_806DA188(r2)
    stw r4, 0x84(r30)
    lfs f2, lbl_806DA18C(r2)
    stfs f0, 0xb0(r30)
    lfs f1, lbl_806DA154(r2)
    stfs f0, 0xb4(r30)
    lfs f0, lbl_806DA15C(r2)
    stb r0, 0x94(r30)
    stfs f2, 0x98(r30)
    stfs f1, 0x9c(r30)
    stfs f0, 0xa0(r30)
    lwz r29, g_characterId(r13)
    bl GetCoinMilage
    slwi r0, r29, 2
    addi r4, r31, 0x430
    lwzx r0, r4, r0
    cmpw r3, r0
    bge clFlowKart_Init_L_801D8760
    li r0, -0x100
    stw r0, 0xb8(r30)
    stw r0, 0xbc(r30)
    stw r0, 0xc0(r30)
    stw r0, 0xc4(r30)
    clFlowKart_Init_L_801D8760:
    li r3, 0x1
    bl InitRumbleController
    lwz r0, 0xc4(r1)
    mr r3, r30
    lwz r31, 0xbc(r1)
    lwz r30, 0xb8(r1)
    lwz r29, 0xb4(r1)
    lwz r28, 0xb0(r1)
    mtlr r0
    addi r1, r1, 0xc0
    blr
}


