/* === extracted from auto_FrameSelection_Init_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void GetCoinMilage();
extern void GetFrameIdxFromVisualIdx();
extern void GetTextureByIdAndLang();
extern void InitBGM();
extern void InitRumbleController();
extern void InitializeFrameSelection();
extern void IsCardValid();
extern void PreloadResource();
extern void ResCtrl_Init();
extern void Scene3D_Init();
extern void SceneModel_Init();
extern void SetCourseParams();
extern void SetScreenBrightness();
extern void SetSyncTarget();
extern void SetupBgSprites();
extern void SpriteSystem_EnsureInit();
extern void Sprite_CreateWithParams();
extern void TexMgr_Apply();
extern void TexMgr_Init();
extern void TexMgr_SetTexture();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int FLOAT_ARROW_LEFT_SCALE_X;
extern unsigned int FLOAT_ARROW_LEFT_X;
extern unsigned int FLOAT_ARROW_RIGHT_OFFSET;
extern unsigned int FLOAT_ARROW_RIGHT_X;
extern unsigned int FLOAT_ARROW_SCALE;
extern unsigned int FLOAT_ARROW_Y;
extern unsigned int FLOAT_BRIGHTNESS_DARK;
extern unsigned int FLOAT_FULL_ALPHA;
extern unsigned int FLOAT_INIT_Z_DEPTH;
extern unsigned int FLOAT_SPRITE_INIT_TIME;
extern unsigned int FLOAT_TEX_POS_X;
extern unsigned int FLOAT_TEX_POS_Y;
extern unsigned int FLOAT_TEX_SCALE;
extern unsigned int g_pInputState;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int g_charaStatTable[];
extern unsigned int g_playerData[];
extern unsigned int lbl_8039AA40[];

/* --- function index (1 fns, .text 0x801C4EA8..0x801C53A0) ---
 * [  0] 0x801C4EA8 size:0x4F8   global FrameSelection_Init
 */

/* --- forward decls --- */
asm void FrameSelection_Init(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();
extern void dtor_80082960();
extern void dtor_800869D0();
extern void dtor_801BA14C();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; void *f29; unsigned int f30; unsigned int f31; void *f32; unsigned int f33; unsigned int f34; void *f35; unsigned int f36; void *f37; unsigned int f38; unsigned int f39; void *f40; unsigned int f41; unsigned int f42; void *f43; unsigned int f44; unsigned int f45; void *f46; unsigned int f47; unsigned int f48; void *f49; unsigned int f50; } extab_FrameSelection_Init = { 0x380A0000, 0x00000038, 0x00000084, 0x0000003C, 0x00660078, 0x00000200, 0x00000070, 0x0000020C, 0x00000078, 0x00000238, 0x00000090, 0x00000254, 0x00000078, 0x00000260, 0x0000009C, 0x0000027C, 0x00570078, 0x000003E8, 0x000000A8, 0x000003F4, 0x00000078, 0x00000408, 0x000000B4, 0x00000414, 0x00000078, 0x00000420, 0x003000C0, 0x00000000, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x0780001A, 0x0000017C, (void *)&dtor_80082960, 0x8680001A, 0x00000000, (void *)&dtor_801BA14C, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x01000078, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x01000078, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x01000078, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x01000078, 0x02000008, (void *)&dtor_800869D0, 0x01000078 };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_FrameSelection_Init = {
    (void *)&FrameSelection_Init, 0x000004F8, (void *)&extab_FrameSelection_Init
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void FrameSelection_Init(void) { /* 0x801C4EA8 size:0x4F8 */
    nofralloc
    stwu r1, -0x260(r1)
    mflr r0
    lis r5, g_charaStatTable@ha
    lis r4, lbl_8039AA40@ha
    stw r0, 0x264(r1)
    stmw r25, 0x244(r1)
    mr r26, r3
    addi r30, r5, g_charaStatTable@l
    addi r29, r4, lbl_8039AA40@l
    bl InitializeFrameSelection
    addi r0, r30, 0x224
    addi r3, r26, 0x17c
    stw r0, 0x0(r26)
    bl ResCtrl_Init
    bl SpriteSystem_EnsureInit
    li r3, 0xd
    bl SetSyncTarget
    li r3, 0x7
    li r4, 0x0
    li r5, 0x0
    li r6, 0x0
    bl SetCourseParams
    li r3, 0x167f
    bl PreloadResource
    li r3, 0x169b
    bl PreloadResource
    li r3, 0x16ac
    bl PreloadResource
    li r3, 0x16ae
    bl PreloadResource
    li r3, 0x16ad
    bl PreloadResource
    li r3, 0x16af
    bl PreloadResource
    addi r28, r30, 0x78
    li r25, 0x0
    mr r27, r28
    FrameSelection_Init_L_801C4F3C:
    lha r3, 0x0(r27)
    bl PreloadResource
    lha r3, 0x2(r27)
    bl PreloadResource
    addi r25, r25, 0x1
    addi r27, r27, 0x18
    cmpwi r25, 0xd
    blt FrameSelection_Init_L_801C4F3C
    li r3, 0x16af
    bl PreloadResource
    li r3, 0x16a8
    bl PreloadResource
    li r3, 0x1d55
    bl PreloadResource
    li r3, 0x1d3e
    bl PreloadResource
    li r3, 0x186c
    bl PreloadResource
    li r3, 0x16b0
    bl PreloadResource
    li r3, 0x16cc
    bl PreloadResource
    li r3, 0x1d5c
    bl PreloadResource
    li r4, 0x0
    li r8, 0xc
    stw r4, 0x14(r26)
    mulli r3, r8, 0x18
    addi r7, r30, 0x78
    stw r4, 0x8(r28)
    subfic r0, r8, 0xd
    slwi r6, r8, 2
    stw r4, 0x18(r26)
    add r7, r7, r3
    stw r4, 0x20(r28)
    stw r4, 0x1c(r26)
    stw r4, 0x38(r28)
    stw r4, 0x20(r26)
    stw r4, 0x50(r28)
    stw r4, 0x24(r26)
    stw r4, 0x68(r28)
    stw r4, 0x28(r26)
    stw r4, 0x80(r28)
    stw r4, 0x2c(r26)
    stw r4, 0x98(r28)
    stw r4, 0x30(r26)
    stw r4, 0xb0(r28)
    stw r4, 0x34(r26)
    stw r4, 0xc8(r28)
    stw r4, 0x38(r26)
    stw r4, 0xe0(r28)
    stw r4, 0x3c(r26)
    stw r4, 0xf8(r28)
    stw r4, 0x40(r26)
    stw r4, 0x110(r28)
    mtctr r0
    cmpwi r8, 0xd
    bge FrameSelection_Init_L_801C503C
    FrameSelection_Init_L_801C5024:
    addi r0, r6, 0x14
    addi r6, r6, 0x4
    stwx r4, r26, r0
    stw r4, 0x8(r7)
    addi r7, r7, 0x18
    bdnz FrameSelection_Init_L_801C5024
    FrameSelection_Init_L_801C503C:
    li r4, 0x0
    li r0, -0x1
    stw r4, 0x4(r26)
    li r3, 0x30
    lfs f0, FLOAT_INIT_Z_DEPTH(r2)
    stw r0, 0x60(r26)
    stw r4, 0x8(r26)
    stb r4, 0xc(r26)
    stw r4, 0x10(r26)
    stw r4, 0x5c(r26)
    stw r4, 0x70(r26)
    stw r4, 0x74(r26)
    stfs f0, 0x6c(r26)
    stb r4, 0x64(r26)
    stb r4, 0x65(r26)
    bl Alloc
    mr. r25, r3
    beq FrameSelection_Init_L_801C50A8
    lfs f1, FLOAT_ARROW_LEFT_X(r2)
    li r4, 0x9c
    lfs f2, FLOAT_ARROW_Y(r2)
    li r5, 0x1
    lfs f3, FLOAT_ARROW_LEFT_SCALE_X(r2)
    lfs f4, FLOAT_ARROW_SCALE(r2)
    lfs f5, FLOAT_SPRITE_INIT_TIME(r2)
    lfs f6, FLOAT_FULL_ALPHA(r2)
    bl Sprite_CreateWithParams
    FrameSelection_Init_L_801C50A8:
    stw r25, 0x48(r26)
    li r3, 0x30
    bl Alloc
    mr. r25, r3
    beq FrameSelection_Init_L_801C50E0
    lfs f3, FLOAT_ARROW_SCALE(r2)
    li r4, 0x9c
    lfs f1, FLOAT_ARROW_RIGHT_X(r2)
    li r5, 0x1
    fmr f4, f3
    lfs f2, FLOAT_ARROW_Y(r2)
    lfs f5, FLOAT_SPRITE_INIT_TIME(r2)
    lfs f6, FLOAT_FULL_ALPHA(r2)
    bl Sprite_CreateWithParams
    FrameSelection_Init_L_801C50E0:
    stw r25, 0x4c(r26)
    li r0, 0x0
    li r3, 0x230
    stw r0, 0x50(r26)
    stw r0, 0x54(r26)
    stw r0, 0x58(r26)
    bl Alloc
    mr. r25, r3
    beq FrameSelection_Init_L_801C5108
    bl TexMgr_Init
    FrameSelection_Init_L_801C5108:
    lis r3, g_playerData@ha
    stw r25, 0x178(r26)
    addi r27, r3, g_playerData@l
    li r25, 0x0
    FrameSelection_Init_L_801C5118:
    mr r3, r26
    mr r4, r25
    bl GetFrameIdxFromVisualIdx
    lbz r0, 0x1b8(r27)
    extsb r0, r0
    cmpw r3, r0
    bne FrameSelection_Init_L_801C513C
    stw r25, 0x4(r26)
    b FrameSelection_Init_L_801C5148
    FrameSelection_Init_L_801C513C:
    addi r25, r25, 0x1
    cmpwi r25, 0xd
    blt FrameSelection_Init_L_801C5118
    FrameSelection_Init_L_801C5148:
    lwz r5, 0x48(r26)
    cmplwi r5, 0x0
    beq FrameSelection_Init_L_801C5180
    lwz r3, 0x4(r26)
    addi r4, r30, 0x1b0
    li r0, 0x5
    slwi r6, r3, 3
    add r3, r4, r6
    lfsx f0, r4, r6
    lfs f1, 0x4(r3)
    stfs f0, 0xc(r5)
    stfs f1, 0x10(r5)
    lwz r3, 0x48(r26)
    stw r0, 0x4(r3)
    FrameSelection_Init_L_801C5180:
    lwz r5, 0x4c(r26)
    cmplwi r5, 0x0
    beq FrameSelection_Init_L_801C51C0
    lwz r3, 0x4(r26)
    addi r4, r30, 0x1b0
    lfs f1, FLOAT_ARROW_RIGHT_OFFSET(r2)
    li r0, 0x5
    slwi r3, r3, 3
    lfsx f0, r4, r3
    add r3, r4, r3
    lfs f2, 0x4(r3)
    fadds f0, f1, f0
    stfs f0, 0xc(r5)
    stfs f2, 0x10(r5)
    lwz r3, 0x4c(r26)
    stw r0, 0x4(r3)
    FrameSelection_Init_L_801C51C0:
    lis r3, g_playerData@ha
    addi r3, r3, g_playerData@l
    bl GetCoinMilage
    mr r30, r3
    addi r31, r29, 0x430
    li r27, 0x0
    li r28, 0x0
    FrameSelection_Init_L_801C51DC:
    addi r0, r28, 0xdc
    li r5, 0x0
    stwx r5, r26, r0
    addi r4, r28, 0x110
    addi r0, r28, 0x144
    mr r3, r26
    stwx r5, r26, r4
    mr r4, r27
    stwx r5, r26, r0
    bl GetFrameIdxFromVisualIdx
    slwi r25, r3, 2
    lwzx r0, r31, r25
    cmpw r30, r0
    blt FrameSelection_Init_L_801C5224
    addi r0, r25, 0xa8
    li r3, 0x2
    stwx r3, r26, r0
    b FrameSelection_Init_L_801C5250
    FrameSelection_Init_L_801C5224:
    addi r3, r29, 0x3fc
    lwzx r0, r3, r25
    cmpw r30, r0
    blt FrameSelection_Init_L_801C5244
    addi r0, r25, 0xa8
    li r3, 0x1
    stwx r3, r26, r0
    b FrameSelection_Init_L_801C5250
    FrameSelection_Init_L_801C5244:
    addi r0, r25, 0xa8
    li r3, 0x0
    stwx r3, r26, r0
    FrameSelection_Init_L_801C5250:
    bl IsCardValid
    clrlwi. r0, r3, 24
    bne FrameSelection_Init_L_801C5268
    addi r0, r25, 0xa8
    li r3, 0x1
    stwx r3, r26, r0
    FrameSelection_Init_L_801C5268:
    addi r27, r27, 0x1
    addi r28, r28, 0x4
    cmpwi r27, 0xd
    blt FrameSelection_Init_L_801C51DC
    li r3, 0x3084
    bl Alloc
    mr. r25, r3
    beq FrameSelection_Init_L_801C5290
    addi r4, r29, 0x608
    bl Scene3D_Init
    FrameSelection_Init_L_801C5290:
    stw r25, 0x70(r26)
    li r3, 0x28
    bl Alloc
    mr. r25, r3
    beq FrameSelection_Init_L_801C52B0
    addi r4, r29, 0x608
    li r5, 0x1
    bl SceneModel_Init
    FrameSelection_Init_L_801C52B0:
    stw r25, 0x74(r26)
    addi r3, r1, 0x8
    bl TexMgr_Init
    lwz r4, 0x4(r26)
    mr r3, r26
    bl GetFrameIdxFromVisualIdx
    slwi r0, r3, 2
    addi r3, r29, 0x464
    lwzx r3, r3, r0
    li r4, -0x1
    addi r3, r3, 0x95
    bl GetTextureByIdAndLang
    mr r4, r3
    addi r3, r1, 0x8
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    addi r3, r1, 0x8
    bl TexMgr_Apply
    li r0, 0x1d5c
    lfs f0, FLOAT_TEX_SCALE(r2)
    stw r0, 0x17c(r26)
    li r0, 0x1
    lfs f2, FLOAT_TEX_POS_Y(r2)
    stfs f0, 0x1a8(r26)
    lfs f1, FLOAT_TEX_POS_X(r2)
    stfs f0, 0x1ac(r26)
    lfs f0, FLOAT_FULL_ALPHA(r2)
    stb r0, 0x18c(r26)
    stfs f2, 0x190(r26)
    stfs f1, 0x194(r26)
    stfs f0, 0x198(r26)
    lwz r4, g_pInputState(r13)
    cmplwi r4, 0x0
    bne FrameSelection_Init_L_801C5340
    li r0, 0x0
    b FrameSelection_Init_L_801C5344
    FrameSelection_Init_L_801C5340:
    mr r0, r4
    FrameSelection_Init_L_801C5344:
    cmplwi r0, 0x0
    beq FrameSelection_Init_L_801C536C
    cmplwi r4, 0x0
    bne FrameSelection_Init_L_801C5358
    li r4, 0x0
    FrameSelection_Init_L_801C5358:
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x4(r4)
    stw r0, 0x18(r4)
    stw r0, 0x1c(r4)
    FrameSelection_Init_L_801C536C:
    lfs f1, FLOAT_BRIGHTNESS_DARK(r2)
    bl SetScreenBrightness
    bl InitBGM
    li r3, 0x1
    bl SetupBgSprites
    li r3, 0x1
    bl InitRumbleController
    mr r3, r26
    lmw r25, 0x244(r1)
    lwz r0, 0x264(r1)
    mtlr r0
    addi r1, r1, 0x260
    blr
}
