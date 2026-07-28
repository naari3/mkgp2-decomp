/* === extracted from auto_clFlowItemSelect_Ini_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void InitBGM();
extern void InitRumbleController();
extern void InitializeFrameSelection();
extern void ItemDisplay_GetOrCreate();
extern void ItemDisplay_Start();
extern void Item_GetDescriptorField0();
extern void Item_GetDescriptorField8();
extern void Item_GetDescriptorFieldC();
extern void Item_GetLocalizedAsset();
extern void OSGetTick();
extern void PlayerData_ResolveUnlockedIdByIndex();
extern void PreloadResource();
extern void Rand15();
extern void Rand_SetSeedDebug();
extern void ResCtrl_Init();
extern void SetSyncTarget();
extern void SetupBgSprites();
extern void SpriteAnimParamBlock_SetAnimParamCached();
extern void SpriteGroup_CreateOrInit();
extern void SpriteHandle_CreateDefault();
extern void TexMgr_Apply();
extern void TexMgr_Init();
extern void TexMgr_SetTexture();
extern void fn_80121E10();
extern void fn_801F8E90();
extern void fn_8023CCF8();
extern void fn_8023CD3C();
extern void fn_8023D080();
extern void fn_8023D844();
extern void fn_8023DAA8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_characterId;
extern unsigned int g_pInputState;
extern unsigned int lbl_806D9DC0;
extern unsigned int lbl_806D9DD8;
extern unsigned int lbl_806D9DE4;
extern unsigned int lbl_806D9DF8;
extern unsigned int lbl_806D9E04;
extern unsigned int lbl_806D9E08;
extern unsigned int lbl_806D9E0C;
extern unsigned int lbl_806D9E10;
extern unsigned int lbl_806D9E14;
extern unsigned int lbl_806D9E18;
extern unsigned int lbl_806D9E1C;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int g_playerData[];
extern unsigned int lbl_8039B3C8[];
extern unsigned int lbl_8049B130[];
extern unsigned int lbl_8049B148[];

/* --- function index (1 fns, .text 0x801CC2EC..0x801CCA30) ---
 * [  0] 0x801CC2EC size:0x744   global clFlowItemSelect_Init
 */

/* --- forward decls --- */
asm void clFlowItemSelect_Init(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();
extern void dtor_80082960();
extern void dtor_801BA14C();
extern void dtor_801CCA30();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; void *f21; unsigned int f22; unsigned int f23; void *f24; unsigned int f25; unsigned int f26; void *f27; unsigned int f28; void *f29; unsigned int f30; unsigned int f31; void *f32; unsigned int f33; unsigned int f34; void *f35; unsigned int f36; void *f37; unsigned int f38; } extab_clFlowItemSelect_Init = { 0x504A0000, 0x0000003C, 0x00000064, 0x00000044, 0x00000058, 0x00000064, 0x00000050, 0x00000070, 0x00130078, 0x000000C8, 0x00000070, 0x000000E4, 0x007A0078, 0x000002D4, 0x00400090, 0x00000430, 0x00000088, 0x000004C4, 0x00980090, 0x00000000, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x0780001F, 0x00000024, (void *)&dtor_80082960, 0x8680001F, 0x00000000, (void *)&dtor_801BA14C, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x0780001F, 0x000000E8, (void *)&dtor_801CCA30, 0x01000058, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x02000008, (void *)&dtor_80082960, 0x01000078 };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowItemSelect_Init = {
    (void *)&clFlowItemSelect_Init, 0x00000744, (void *)&extab_clFlowItemSelect_Init
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clFlowItemSelect_Init(void) { /* 0x801CC2EC size:0x744 */
    nofralloc
    stwu r1, -0xa0(r1)
    mflr r0
    stw r0, 0xa4(r1)
    stfd f31, 0x90(r1)
    psq_st f31, 0x98(r1), 0, 0
    stmw r22, 0x68(r1)
    mr r31, r3
    bl InitializeFrameSelection
    lis r3, lbl_8049B148@ha
    lfs f0, lbl_806D9DF8(r2)
    addi r0, r3, lbl_8049B148@l
    addi r3, r31, 0x24
    stw r0, 0x0(r31)
    stfs f0, 0x20(r31)
    bl ResCtrl_Init
    li r3, 0x20
    bl Alloc
    mr. r22, r3
    beq clFlowItemSelect_Init_L_801CC350
    li r4, 0x74
    li r5, -0x1
    li r6, 0x1875
    li r7, -0x1
    li r8, 0x5
    bl fn_8023D080
    clFlowItemSelect_Init_L_801CC350:
    stw r22, 0xe8(r31)
    li r3, 0x22
    bl SetSyncTarget
    li r24, 0x0
    lfs f31, lbl_806D9DF8(r2)
    stw r24, 0x98(r31)
    mr r23, r24
    stw r24, 0x9c(r31)
    stw r24, 0xa0(r31)
    stw r24, 0xa4(r31)
    stw r24, 0xa8(r31)
    stw r24, 0xac(r31)
    stw r24, 0xb0(r31)
    stw r24, 0xb4(r31)
    stw r24, 0xb8(r31)
    stw r24, 0xbc(r31)
    stw r24, 0xc0(r31)
    stw r24, 0xc4(r31)
    clFlowItemSelect_Init_L_801CC398:
    li r25, 0x0
    li r22, 0x0
    clFlowItemSelect_Init_L_801CC3A0:
    li r3, 0x230
    bl Alloc
    mr. r26, r3
    beq clFlowItemSelect_Init_L_801CC3B4
    bl TexMgr_Init
    clFlowItemSelect_Init_L_801CC3B4:
    add r3, r31, r22
    addi r4, r2, -0x464  /* lbl_806D9DFC */
    addi r0, r3, 0x98
    stwx r26, r23, r0
    lwzx r3, r23, r0
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    addi r25, r25, 0x1
    addi r22, r22, 0x4
    cmpwi r25, 0x4
    blt clFlowItemSelect_Init_L_801CC3A0
    addi r0, r23, 0x9c
    addi r24, r24, 0x1
    lwzx r4, r31, r0
    addi r3, r23, 0xa0
    addi r0, r23, 0xa4
    cmpwi r24, 0x3
    stfs f31, 0x22c(r4)
    addi r23, r23, 0x10
    lwzx r3, r31, r3
    stfs f31, 0x22c(r3)
    lwzx r3, r31, r0
    stfs f31, 0x22c(r3)
    blt clFlowItemSelect_Init_L_801CC398
    lwz r4, g_pInputState(r13)
    cmplwi r4, 0x0
    bne clFlowItemSelect_Init_L_801CC428
    li r0, 0x0
    b clFlowItemSelect_Init_L_801CC42C
    clFlowItemSelect_Init_L_801CC428:
    mr r0, r4
    clFlowItemSelect_Init_L_801CC42C:
    cmplwi r0, 0x0
    beq clFlowItemSelect_Init_L_801CC454
    cmplwi r4, 0x0
    bne clFlowItemSelect_Init_L_801CC440
    li r4, 0x0
    clFlowItemSelect_Init_L_801CC440:
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x4(r4)
    stw r0, 0x18(r4)
    stw r0, 0x1c(r4)
    clFlowItemSelect_Init_L_801CC454:
    bl InitBGM
    li r3, 0x1
    bl SetupBgSprites
    bl ItemDisplay_GetOrCreate
    bl ItemDisplay_GetOrCreate
    li r4, 0x1ae7
    bl ItemDisplay_Start
    li r3, 0x17ab
    bl PreloadResource
    li r8, 0x0
    li r5, -0x1
    stw r8, 0x18(r31)
    li r7, 0x2b
    li r6, 0x3d
    li r0, 0x32
    stw r8, 0x1c(r31)
    addi r3, r31, 0x80
    lfs f1, lbl_806D9E04(r2)
    addi r4, r13, -0x6F18  /* lbl_806CFE08 */
    stw r5, 0x7c(r31)
    li r5, 0x0
    lfs f2, lbl_806D9DD8(r2)
    stw r8, 0x10(r31)
    stw r8, 0x14(r31)
    stw r7, 0x4(r31)
    stw r6, 0x8(r31)
    stw r0, 0xc(r31)
    stw r8, 0x80(r31)
    stw r8, 0x84(r31)
    stw r8, 0x88(r31)
    stw r8, 0x8c(r31)
    stw r8, 0x90(r31)
    bl SpriteGroup_CreateOrInit
    lfs f1, lbl_806D9DE4(r2)
    addi r3, r31, 0x84
    lfs f2, lbl_806D9DD8(r2)
    addi r4, r13, -0x6F14  /* lbl_806CFE0C */
    li r5, 0x0
    bl SpriteGroup_CreateOrInit
    lfs f1, lbl_806D9E08(r2)
    addi r3, r31, 0x88
    lfs f2, lbl_806D9DD8(r2)
    addi r4, r13, -0x6F10  /* lbl_806CFE10 */
    li r5, 0x0
    bl SpriteGroup_CreateOrInit
    lfs f1, lbl_806D9DE4(r2)
    addi r3, r31, 0x8c
    lfs f2, lbl_806D9E0C(r2)
    addi r4, r13, -0x6F0C  /* lbl_806CFE14 */
    li r5, 0x0
    bl SpriteGroup_CreateOrInit
    li r26, 0x0
    mr r24, r26
    mr r25, r26
    clFlowItemSelect_Init_L_801CC52C:
    addi r0, r24, 0x80
    li r4, 0x1ecf
    lwzx r3, r31, r0
    li r5, 0x1ecd
    bl SpriteAnimParamBlock_SetAnimParamCached
    addi r0, r24, 0x80
    li r4, 0x1ed1
    lwzx r3, r31, r0
    li r5, 0x1ecd
    bl SpriteAnimParamBlock_SetAnimParamCached
    addi r0, r24, 0x80
    li r4, 0x1ed3
    lwzx r3, r31, r0
    li r5, 0x1ecd
    bl SpriteAnimParamBlock_SetAnimParamCached
    li r27, 0x0
    li r23, 0x0
    li r22, -0x100
    clFlowItemSelect_Init_L_801CC574:
    add r3, r31, r23
    addi r0, r3, 0x98
    lwzx r3, r25, r0
    stw r22, 0x20(r3)
    lwzx r3, r25, r0
    bl fn_801F8E90
    addi r27, r27, 0x1
    addi r23, r23, 0x4
    cmpwi r27, 0x4
    blt clFlowItemSelect_Init_L_801CC574
    addi r26, r26, 0x1
    addi r25, r25, 0x10
    cmpwi r26, 0x3
    addi r24, r24, 0x4
    blt clFlowItemSelect_Init_L_801CC52C
    addi r3, r1, 0x8
    bl ResCtrl_Init
    addi r3, r1, 0x8
    bl fn_80121E10
    lfs f2, lbl_806D9DE4(r2)
    li r4, 0x17ab
    lfs f1, lbl_806D9E0C(r2)
    li r0, 0x1
    lfs f0, lbl_806D9DC0(r2)
    addi r3, r1, 0x8
    stw r4, 0x8(r1)
    li r4, 0x5
    stb r0, 0x18(r1)
    stfs f2, 0x1c(r1)
    stfs f1, 0x20(r1)
    stfs f0, 0x24(r1)
    bl SpriteHandle_CreateDefault
    stw r3, 0x94(r31)
    lwz r24, g_characterId(r13)
    cmpwi r24, 0x0
    blt clFlowItemSelect_Init_L_801CC60C
    cmpwi r24, 0xd
    blt clFlowItemSelect_Init_L_801CC610
    clFlowItemSelect_Init_L_801CC60C:
    li r24, 0x0
    clFlowItemSelect_Init_L_801CC610:
    lis r3, g_playerData@ha
    li r23, 0x0
    addi r0, r3, g_playerData@l
    mr r25, r0
    mr r22, r23
    clFlowItemSelect_Init_L_801CC624:
    mr r3, r24
    addi r4, r23, 0x1
    bl fn_8023D844
    mr r4, r3
    mr r3, r25
    bl PlayerData_ResolveUnlockedIdByIndex
    addi r23, r23, 0x1
    addi r0, r22, 0xc8
    cmpwi r23, 0x5
    stwx r3, r31, r0
    addi r22, r22, 0x4
    blt clFlowItemSelect_Init_L_801CC624
    lwz r3, 0xe8(r31)
    lfs f1, lbl_806D9E10(r2)
    lfs f2, lbl_806D9E14(r2)
    bl fn_8023CD3C
    lwz r3, 0xe8(r31)
    lfs f1, lbl_806D9E18(r2)
    lfs f2, lbl_806D9E1C(r2)
    bl fn_8023CCF8
    addi r3, r31, 0x24
    bl fn_80121E10
    li r0, 0x17a3
    stw r0, 0x24(r31)
    bl OSGetTick
    clrlwi r3, r3, 24
    bl Rand_SetSeedDebug
    lis r4, lbl_8039B3C8@ha
    lis r3, lbl_8049B130@ha
    addi r26, r3, lbl_8049B130@l
    li r24, 0x0
    addi r25, r4, lbl_8039B3C8@l
    lis r3, 0x51ec
    mr r29, r25
    mr r28, r26
    mr r27, r24
    subi r30, r3, 0x7ae1
    clFlowItemSelect_Init_L_801CC6B8:
    li r3, 0x2c
    bl Alloc
    mr. r22, r3
    beq clFlowItemSelect_Init_L_801CC7A0
    lwz r3, 0x0(r28)
    li r0, 0x0
    lwz r4, 0x0(r29)
    stb r0, 0x0(r22)
    stw r0, 0xc(r22)
    stw r3, 0x10(r22)
    stw r4, 0x14(r22)
    lwz r0, 0xc8(r31)
    stw r0, 0x18(r22)
    lwz r0, 0xcc(r31)
    stw r0, 0x1c(r22)
    lwz r0, 0xd0(r31)
    stw r0, 0x20(r22)
    lwz r0, 0xd4(r31)
    stw r0, 0x24(r22)
    lwz r0, 0xd8(r31)
    stw r0, 0x28(r22)
    lbz r0, 0x0(r22)
    cmplwi r0, 0x1
    beq clFlowItemSelect_Init_L_801CC7A0
    clFlowItemSelect_Init_L_801CC718:
    bl Rand15
    lwz r5, 0x14(r22)
    lwz r4, 0x10(r22)
    divw r0, r3, r5
    mullw r0, r0, r5
    subf r0, r0, r3
    slwi r0, r0, 3
    lwzx r3, r4, r0
    cmpwi r3, -0x4
    beq clFlowItemSelect_Init_L_801CC774
    bge clFlowItemSelect_Init_L_801CC754
    cmpwi r3, -0x6
    beq clFlowItemSelect_Init_L_801CC784
    bge clFlowItemSelect_Init_L_801CC77C
    b clFlowItemSelect_Init_L_801CC788
    clFlowItemSelect_Init_L_801CC754:
    cmpwi r3, -0x2
    beq clFlowItemSelect_Init_L_801CC764
    bge clFlowItemSelect_Init_L_801CC788
    b clFlowItemSelect_Init_L_801CC76C
    clFlowItemSelect_Init_L_801CC764:
    lwz r3, 0x1c(r22)
    b clFlowItemSelect_Init_L_801CC788
    clFlowItemSelect_Init_L_801CC76C:
    lwz r3, 0x20(r22)
    b clFlowItemSelect_Init_L_801CC788
    clFlowItemSelect_Init_L_801CC774:
    lwz r3, 0x18(r22)
    b clFlowItemSelect_Init_L_801CC788
    clFlowItemSelect_Init_L_801CC77C:
    lwz r3, 0x24(r22)
    b clFlowItemSelect_Init_L_801CC788
    clFlowItemSelect_Init_L_801CC784:
    lwz r3, 0x28(r22)
    clFlowItemSelect_Init_L_801CC788:
    lwz r0, 0x8(r22)
    cmpw r3, r0
    beq clFlowItemSelect_Init_L_801CC718
    stw r3, 0x8(r22)
    li r0, 0x6
    stw r0, 0xc(r22)
    clFlowItemSelect_Init_L_801CC7A0:
    addi r0, r27, 0xdc
    li r23, 0x0
    stwx r22, r31, r0
    bl Rand15
    mulhw r0, r30, r3
    li r5, 0x0
    li r4, 0x0
    srawi r0, r0, 5
    srwi r6, r0, 31
    add r0, r0, r6
    mulli r0, r0, 0x64
    subf r3, r0, r3
    addi r6, r3, 0x1
    b clFlowItemSelect_Init_L_801CC898
    clFlowItemSelect_Init_L_801CC7D8:
    lwz r0, 0x0(r28)
    add r3, r0, r4
    lwz r0, 0x4(r3)
    add r23, r23, r0
    cmpw r6, r23
    bgt clFlowItemSelect_Init_L_801CC890
    lwz r0, 0x0(r3)
    addi r3, r31, 0x4
    stwx r0, r27, r3
    lwzx r0, r27, r3
    cmpwi r0, -0x4
    beq clFlowItemSelect_Init_L_801CC844
    bge clFlowItemSelect_Init_L_801CC81C
    cmpwi r0, -0x6
    beq clFlowItemSelect_Init_L_801CC85C
    bge clFlowItemSelect_Init_L_801CC850
    b clFlowItemSelect_Init_L_801CC864
    clFlowItemSelect_Init_L_801CC81C:
    cmpwi r0, -0x2
    beq clFlowItemSelect_Init_L_801CC82C
    bge clFlowItemSelect_Init_L_801CC864
    b clFlowItemSelect_Init_L_801CC838
    clFlowItemSelect_Init_L_801CC82C:
    lwz r0, 0xcc(r31)
    stwx r0, r27, r3
    b clFlowItemSelect_Init_L_801CC864
    clFlowItemSelect_Init_L_801CC838:
    lwz r0, 0xd0(r31)
    stwx r0, r27, r3
    b clFlowItemSelect_Init_L_801CC864
    clFlowItemSelect_Init_L_801CC844:
    lwz r0, 0xc8(r31)
    stwx r0, r27, r3
    b clFlowItemSelect_Init_L_801CC864
    clFlowItemSelect_Init_L_801CC850:
    lwz r0, 0xd4(r31)
    stwx r0, r27, r3
    b clFlowItemSelect_Init_L_801CC864
    clFlowItemSelect_Init_L_801CC85C:
    lwz r0, 0xd8(r31)
    stwx r0, r27, r3
    clFlowItemSelect_Init_L_801CC864:
    addi r0, r31, 0x4
    lwzx r0, r27, r0
    cmpwi r0, 0x0
    blt clFlowItemSelect_Init_L_801CC890
    cmpwi r0, 0x115
    bge clFlowItemSelect_Init_L_801CC890
    add r3, r31, r27
    lwz r0, 0x4(r3)
    lwz r3, 0xdc(r3)
    stw r0, 0x4(r3)
    b clFlowItemSelect_Init_L_801CC8A4
    clFlowItemSelect_Init_L_801CC890:
    addi r4, r4, 0x8
    addi r5, r5, 0x1
    clFlowItemSelect_Init_L_801CC898:
    lwz r0, 0x0(r29)
    cmpw r5, r0
    blt clFlowItemSelect_Init_L_801CC7D8
    clFlowItemSelect_Init_L_801CC8A4:
    addi r24, r24, 0x1
    addi r28, r28, 0x4
    cmpwi r24, 0x3
    addi r27, r27, 0x4
    addi r29, r29, 0x4
    blt clFlowItemSelect_Init_L_801CC6B8
    li r29, 0x0
    mr r27, r29
    mr r28, r29
    clFlowItemSelect_Init_L_801CC8C8:
    addi r0, r27, 0x4
    lwzx r3, r31, r0
    bl fn_8023DAA8
    addi r0, r28, 0x98
    mr r4, r3
    lwzx r3, r31, r0
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    addi r0, r27, 0x4
    li r4, 0x0
    lwzx r3, r31, r0
    bl Item_GetLocalizedAsset
    addi r0, r28, 0x9c
    mr r4, r3
    lwzx r3, r31, r0
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    addi r0, r27, 0x4
    li r4, 0x1
    lwzx r3, r31, r0
    bl Item_GetLocalizedAsset
    addi r0, r28, 0xa0
    mr r4, r3
    lwzx r3, r31, r0
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    addi r0, r27, 0x4
    li r4, 0x2
    lwzx r3, r31, r0
    bl Item_GetLocalizedAsset
    addi r0, r28, 0xa4
    mr r4, r3
    lwzx r3, r31, r0
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    li r23, 0x0
    li r22, 0x0
    clFlowItemSelect_Init_L_801CC95C:
    add r3, r31, r22
    addi r0, r3, 0x98
    lwzx r3, r28, r0
    bl TexMgr_Apply
    addi r23, r23, 0x1
    addi r22, r22, 0x4
    cmpwi r23, 0x4
    blt clFlowItemSelect_Init_L_801CC95C
    addi r29, r29, 0x1
    addi r28, r28, 0x10
    cmpwi r29, 0x3
    addi r27, r27, 0x4
    blt clFlowItemSelect_Init_L_801CC8C8
    li r23, 0x0
    clFlowItemSelect_Init_L_801CC994:
    li r24, 0x0
    li r22, 0x0
    b clFlowItemSelect_Init_L_801CC9E0
    clFlowItemSelect_Init_L_801CC9A0:
    lwz r3, 0x0(r26)
    li r4, 0x0
    lwzx r27, r3, r22
    mr r3, r27
    bl Item_GetDescriptorField0
    bl PreloadResource
    mr r3, r27
    bl Item_GetDescriptorFieldC
    addi r3, r3, 0x1e1d
    bl PreloadResource
    mr r3, r27
    bl Item_GetDescriptorField8
    addi r3, r3, 0x17a3
    bl PreloadResource
    addi r22, r22, 0x8
    addi r24, r24, 0x1
    clFlowItemSelect_Init_L_801CC9E0:
    lwz r0, 0x0(r25)
    cmpw r24, r0
    blt clFlowItemSelect_Init_L_801CC9A0
    addi r23, r23, 0x1
    addi r25, r25, 0x4
    cmpwi r23, 0x3
    addi r26, r26, 0x4
    blt clFlowItemSelect_Init_L_801CC994
    li r3, 0x17ab
    bl PreloadResource
    li r3, 0x1
    bl InitRumbleController
    mr r3, r31
    psq_l f31, 0x98(r1), 0, 0
    lfd f31, 0x90(r1)
    lmw r22, 0x68(r1)
    lwz r0, 0xa4(r1)
    mtlr r0
    addi r1, r1, 0xa0
    blr
}

