/* === extracted from auto_JumpDistanceMode_Ini_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void Camera_Create();
extern void CarObject_GetKartMovementPtr();
extern void CarObject_GetRenderObj();
extern void CarObject_Init();
extern void CarObject_SetPosition();
extern void ChallengeGoalCamera_Init();
extern void CourseObjectManager_Init();
extern void DMAChannelManager_Init();
extern void DrawManager_GetOrCreate();
extern void GameMode_BaseInit();
extern void GetCourseDataPtr();
extern void GetCourseStartYaw();
extern void GetDisplayBufferIndex();
extern void GetKartModelNameEntry();
extern void GetKartStartSlot();
extern void GetRaceContextPtr();
extern void GetStartPosition();
extern void HUD_Init();
extern void HUD_RegisterOverlay();
extern void InitRumbleController();
extern void InputManager_Init();
extern void ItemObjectManager_Init();
extern void JumpDistanceMode_CopyKartMovement();
extern void JumpDistanceMode_InitTimerDisplay();
extern void KartMovement_EquipItem();
extern void LakituStart_Init();
extern void MiniGame_GetCourseData();
extern void MiniGame_GetTimerValue();
extern void PreloadEffectResources();
extern void ProcessSystemTick();
extern void RankingTable_Init();
extern void RenderTarget_Create();
extern void Scene3D_GetCameraPos();
extern void Scene3D_Init();
extern void Scene3D_SetupProjection();
extern void SetActiveCamera();
extern void SetCourseScene3D();
extern void SetPlayerCarObject();
extern void SetResourceLoadingFlag();
extern void SoundChannels_ClearAll();
extern void SoundDriver_GetOrCreate();
extern void TransitionEffect_GetOrCreate();
extern void Vec3_Normalize();
extern void Vec3_Subtract();
extern void WeatherSystem_Init();
extern void fn_8013D608();
extern void fn_8013D634();
extern void fn_8013D738();
extern void fn_8013D800();
extern void fn_801699D8();
extern void fn_8023E1E4();
extern void fn_8023EA80();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_ccClass;
extern unsigned int g_characterId;
extern unsigned int g_kartStartSlot;
extern unsigned int g_lakituStartAnimDone;
extern unsigned int g_playerRenderObj;
extern unsigned int g_raceCamera;
extern unsigned int g_raceEnded;
extern unsigned int g_raceTimeRemaining;
extern unsigned int g_reverseRoundFlag;
extern unsigned int g_weatherSystem;
extern unsigned int lbl_806D12BC;
extern unsigned int lbl_806DAD70;
extern unsigned int lbl_806DAD7C;
extern unsigned int lbl_806DAD88;
extern unsigned int lbl_806DADA4;
extern unsigned int lbl_806DADDC;
extern unsigned int lbl_806DADE0;
extern unsigned int lbl_806DAE08;
extern unsigned int lbl_806DAE0C;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_803C3858[];
extern unsigned int lbl_8048E144[];
extern unsigned int lbl_804ECC08[];

/* --- function index (1 fns, .text 0x80213210..0x80213A64) ---
 * [  0] 0x80213210 size:0x854   global JumpDistanceMode_Init
 */

/* --- forward decls --- */
asm void JumpDistanceMode_Init(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();
extern void dtor_80122FD8();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; unsigned int f29; unsigned int f30; unsigned int f31; unsigned int f32; unsigned int f33; unsigned int f34; unsigned int f35; unsigned int f36; unsigned int f37; unsigned int f38; unsigned int f39; unsigned int f40; unsigned int f41; unsigned int f42; unsigned int f43; unsigned int f44; unsigned int f45; unsigned int f46; unsigned int f47; unsigned int f48; unsigned int f49; unsigned int f50; unsigned int f51; unsigned int f52; unsigned int f53; unsigned int f54; unsigned int f55; unsigned int f56; unsigned int f57; unsigned int f58; unsigned int f59; unsigned int f60; unsigned int f61; unsigned int f62; unsigned int f63; unsigned int f64; unsigned int f65; unsigned int f66; unsigned int f67; unsigned int f68; unsigned int f69; unsigned int f70; unsigned int f71; unsigned int f72; void *f73; unsigned int f74; unsigned int f75; void *f76; unsigned int f77; void *f78; unsigned int f79; unsigned int f80; void *f81; unsigned int f82; void *f83; unsigned int f84; unsigned int f85; void *f86; unsigned int f87; void *f88; unsigned int f89; unsigned int f90; void *f91; unsigned int f92; void *f93; unsigned int f94; unsigned int f95; void *f96; unsigned int f97; void *f98; unsigned int f99; unsigned int f100; void *f101; unsigned int f102; void *f103; unsigned int f104; unsigned int f105; void *f106; unsigned int f107; void *f108; unsigned int f109; unsigned int f110; void *f111; unsigned int f112; void *f113; unsigned int f114; unsigned int f115; void *f116; unsigned int f117; void *f118; unsigned int f119; unsigned int f120; void *f121; unsigned int f122; void *f123; unsigned int f124; unsigned int f125; void *f126; unsigned int f127; void *f128; unsigned int f129; unsigned int f130; void *f131; unsigned int f132; void *f133; unsigned int f134; unsigned int f135; void *f136; unsigned int f137; void *f138; unsigned int f139; void *f140; unsigned int f141; unsigned int f142; void *f143; unsigned int f144; void *f145; unsigned int f146; unsigned int f147; void *f148; unsigned int f149; unsigned int f150; void *f151; } extab_JumpDistanceMode_Init = { 0x284A0000, 0x000000D0, 0x00090128, 0x00000100, 0x00000120, 0x00000108, 0x00040128, 0x00000138, 0x00000134, 0x00000148, 0x00140128, 0x000001AC, 0x00100148, 0x000001FC, 0x000E0128, 0x00000244, 0x0000015C, 0x00000258, 0x00070128, 0x00000294, 0x00000170, 0x000002A0, 0x00000128, 0x000002B4, 0x00040184, 0x000002D0, 0x00000128, 0x000002DC, 0x00000198, 0x000002E8, 0x00000128, 0x000002F8, 0x000301AC, 0x00000310, 0x00110128, 0x00000388, 0x000301C0, 0x000003BC, 0x00000128, 0x000003F0, 0x000301D4, 0x00000424, 0x00000128, 0x00000458, 0x000301E8, 0x0000048C, 0x000D0128, 0x000004D0, 0x000001FC, 0x000004E4, 0x002C0128, 0x000005B0, 0x00000210, 0x000005BC, 0x001E0128, 0x00000664, 0x0000022C, 0x00000678, 0x00000224, 0x0000068C, 0x000D022C, 0x000006D4, 0x00000240, 0x000006E8, 0x000A022C, 0x000007F8, 0x00000128, 0x00000808, 0x0000024C, 0x00000814, 0x00080128, 0x00000000, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x0100022C, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8 };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_JumpDistanceMode_Init = {
    (void *)&JumpDistanceMode_Init, 0x00000854, (void *)&extab_JumpDistanceMode_Init
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void JumpDistanceMode_Init(void) { /* 0x80213210 size:0x854 */
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    stfd f31, 0x50(r1)
    psq_st f31, 0x58(r1), 0, 0
    stmw r27, 0x3c(r1)
    mr r31, r3
    lis r4, lbl_803C3858@ha
    mr r0, r31
    mr r28, r0
    addi r30, r4, lbl_803C3858@l
    bl GameMode_BaseInit
    lis r4, lbl_8048E144@ha
    lis r3, lbl_804ECC08@ha
    addi r0, r4, lbl_8048E144@l
    lfs f1, lbl_806DAD7C(r2)
    stw r0, 0x0(r28)
    addi r3, r3, lbl_804ECC08@l
    li r0, 0x0
    lfs f0, lbl_806DADA4(r2)
    stfs f1, 0x4(r28)
    stw r3, 0x0(r31)
    stw r0, 0x8(r31)
    stw r0, 0xc(r31)
    stw r0, 0x10(r31)
    stw r0, 0x14(r31)
    stw r0, 0x18(r31)
    stw r0, 0x1c(r31)
    stw r0, 0x20(r31)
    stw r0, 0x24(r31)
    stw r0, 0x28(r31)
    stw r0, 0x2c(r31)
    stw r0, 0x30(r31)
    stw r0, 0x34(r31)
    stw r0, 0x38(r31)
    stw r0, 0x3c(r31)
    stw r0, 0x40(r31)
    stb r0, 0x44(r31)
    stb r0, 0x45(r31)
    stw r0, 0x48(r31)
    stw r0, 0x4c(r31)
    stw r0, 0x50(r31)
    stfs f0, 0x54(r31)
    stfs f1, 0x58(r31)
    stfs f1, 0x68(r31)
    stb r0, 0x6c(r31)
    stb r0, 0x6d(r31)
    stw r0, 0x70(r31)
    stfs f1, 0x74(r31)
    stb r0, 0x78(r31)
    stb r0, 0x88(r31)
    bl DrawManager_GetOrCreate
    li r3, 0x0
    bl SetResourceLoadingFlag
    bl DMAChannelManager_Init
    bl TransitionEffect_GetOrCreate
    bl SoundChannels_ClearAll
    bl ItemObjectManager_Init
    bl CourseObjectManager_Init
    li r3, 0x37c
    bl Alloc
    mr. r28, r3
    beq JumpDistanceMode_Init_L_80213310
    bl InputManager_Init
    JumpDistanceMode_Init_L_80213310:
    stw r28, 0x10(r31)
    bl GetCourseDataPtr
    bl RenderTarget_Create
    stw r3, 0x24(r31)
    li r3, 0x2c
    bl Alloc
    mr. r28, r3
    beq JumpDistanceMode_Init_L_80213348
    lfs f1, lbl_806DAE08(r2)
    li r4, 0x100
    lfs f2, lbl_806DAD88(r2)
    li r5, 0x100
    lwz r6, 0x24(r31)
    bl Camera_Create
    JumpDistanceMode_Init_L_80213348:
    stw r28, 0x20(r31)
    li r3, 0x0
    lwz r4, 0x20(r31)
    bl SetActiveCamera
    lwz r0, 0x20(r31)
    li r3, 0x0
    stw r0, g_raceCamera(r13)
    bl ProcessSystemTick
    bl GetRaceContextPtr
    bl RankingTable_Init
    li r0, 0x0
    li r3, 0x0
    stw r0, lbl_806D12BC(r13)
    bl SoundDriver_GetOrCreate
    bl GetDisplayBufferIndex
    bl GetKartStartSlot
    stw r3, g_kartStartSlot(r13)
    addi r6, r1, 0x20
    addi r4, r1, 0x18
    addi r5, r1, 0x1c
    li r3, 0x0
    bl GetStartPosition
    li r3, 0x118
    bl Alloc
    mr. r27, r3
    beq JumpDistanceMode_Init_L_802133FC
    lwz r29, g_ccClass(r13)
    lwz r28, g_characterId(r13)
    bl GetCourseStartYaw
    fmr f31, f1
    bl GetDisplayBufferIndex
    li r0, 0x0
    mr r4, r3
    stw r0, 0x8(r1)
    fmr f3, f31
    mr r3, r27
    mr r5, r28
    lfs f1, 0x18(r1)
    mr r6, r29
    lfs f2, 0x20(r1)
    li r7, 0x0
    li r8, 0x1
    li r9, 0x7
    li r10, 0x0
    bl CarObject_Init
    JumpDistanceMode_Init_L_802133FC:
    stw r27, 0x8(r31)
    addi r4, r1, 0x18
    lwz r3, 0x8(r31)
    bl CarObject_SetPosition
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    li r0, 0x1
    stw r0, 0x238(r3)
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    li r0, 0x1
    stb r0, 0x2d0(r3)
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    li r4, 0x17
    bl KartMovement_EquipItem
    li r3, 0x44
    bl Alloc
    mr. r27, r3
    beq JumpDistanceMode_Init_L_80213454
    li r4, 0x0
    bl fn_8023EA80
    JumpDistanceMode_Init_L_80213454:
    stw r27, 0x1c(r31)
    li r4, 0x17
    li r5, 0x0
    lwz r3, 0x1c(r31)
    bl fn_8023E1E4
    lwz r3, 0x8(r31)
    bl SetPlayerCarObject
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    stw r3, g_playerRenderObj(r13)
    li r3, 0x58
    bl Alloc
    mr. r27, r3
    beq JumpDistanceMode_Init_L_802134A4
    lfs f1, lbl_806DAD7C(r2)
    addi r4, r30, 0x54c
    li r5, 0x0
    fmr f2, f1
    fmr f3, f1
    bl LakituStart_Init
    JumpDistanceMode_Init_L_802134A4:
    stw r27, 0xc(r31)
    li r3, 0x3084
    bl Alloc
    mr. r27, r3
    beq JumpDistanceMode_Init_L_802134D4
    lwz r3, g_characterId(r13)
    li r4, -0x1
    bl GetKartModelNameEntry
    mr r4, r3
    mr r3, r27
    lwz r4, 0x0(r4)
    bl Scene3D_Init
    JumpDistanceMode_Init_L_802134D4:
    stw r27, 0x14(r31)
    li r3, 0x8
    bl Alloc
    mr. r27, r3
    beq JumpDistanceMode_Init_L_802134EC
    bl ChallengeGoalCamera_Init
    JumpDistanceMode_Init_L_802134EC:
    stw r27, 0x18(r31)
    li r3, 0x324
    bl Alloc
    mr. r27, r3
    beq JumpDistanceMode_Init_L_80213514
    lwz r3, 0x8(r31)
    bl CarObject_GetKartMovementPtr
    mr r4, r3
    mr r3, r27
    bl JumpDistanceMode_CopyKartMovement
    JumpDistanceMode_Init_L_80213514:
    stw r27, 0x70(r31)
    li r3, 0x24
    bl Alloc
    cmplwi r3, 0x0
    beq JumpDistanceMode_Init_L_80213558
    lwz r4, 0x14(r31)
    li r0, 0x0
    lfs f0, lbl_806DAD7C(r2)
    stw r0, 0x0(r3)
    stw r4, 0x4(r3)
    stfs f0, 0x20(r3)
    stfs f0, 0x10(r3)
    stfs f0, 0xc(r3)
    stfs f0, 0x8(r3)
    stfs f0, 0x1c(r3)
    stfs f0, 0x18(r3)
    stfs f0, 0x14(r3)
    JumpDistanceMode_Init_L_80213558:
    stw r3, 0x40(r31)
    li r3, 0x1c
    bl Alloc
    mr. r27, r3
    beq JumpDistanceMode_Init_L_802135C0
    lwz r0, g_reverseRoundFlag(r13)
    addi r3, r30, 0x408
    addi r3, r3, 0x18
    cmpwi r0, 0x0
    bne JumpDistanceMode_Init_L_80213584
    addi r3, r30, 0x408
    JumpDistanceMode_Init_L_80213584:
    stw r3, 0x0(r27)
    addi r5, r27, 0x10
    lwz r4, 0x0(r27)
    addi r3, r4, 0xc
    bl Vec3_Subtract
    addi r3, r27, 0x10
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0x18(r27)
    fneg f0, f0
    stfs f0, 0x4(r27)
    lfs f0, 0x14(r27)
    stfs f0, 0x8(r27)
    lfs f0, 0x10(r27)
    stfs f0, 0xc(r27)
    JumpDistanceMode_Init_L_802135C0:
    stw r27, 0x30(r31)
    li r3, 0x1c
    bl Alloc
    mr. r27, r3
    beq JumpDistanceMode_Init_L_80213628
    lwz r0, g_reverseRoundFlag(r13)
    addi r3, r30, 0x438
    addi r3, r3, 0x18
    cmpwi r0, 0x0
    bne JumpDistanceMode_Init_L_802135EC
    addi r3, r30, 0x438
    JumpDistanceMode_Init_L_802135EC:
    stw r3, 0x0(r27)
    addi r5, r27, 0x10
    lwz r4, 0x0(r27)
    addi r3, r4, 0xc
    bl Vec3_Subtract
    addi r3, r27, 0x10
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0x18(r27)
    fneg f0, f0
    stfs f0, 0x4(r27)
    lfs f0, 0x14(r27)
    stfs f0, 0x8(r27)
    lfs f0, 0x10(r27)
    stfs f0, 0xc(r27)
    JumpDistanceMode_Init_L_80213628:
    stw r27, 0x34(r31)
    li r3, 0x1c
    bl Alloc
    mr. r27, r3
    beq JumpDistanceMode_Init_L_80213690
    lwz r0, g_reverseRoundFlag(r13)
    addi r3, r30, 0x468
    addi r3, r3, 0x18
    cmpwi r0, 0x0
    bne JumpDistanceMode_Init_L_80213654
    addi r3, r30, 0x468
    JumpDistanceMode_Init_L_80213654:
    stw r3, 0x0(r27)
    addi r5, r27, 0x10
    lwz r4, 0x0(r27)
    addi r3, r4, 0xc
    bl Vec3_Subtract
    addi r3, r27, 0x10
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0x18(r27)
    fneg f0, f0
    stfs f0, 0x4(r27)
    lfs f0, 0x14(r27)
    stfs f0, 0x8(r27)
    lfs f0, 0x10(r27)
    stfs f0, 0xc(r27)
    JumpDistanceMode_Init_L_80213690:
    stw r27, 0x38(r31)
    li r3, 0x0
    bl ProcessSystemTick
    lwz r3, 0x14(r31)
    addi r4, r1, 0x14
    addi r5, r1, 0x10
    bl Scene3D_GetCameraPos
    lfs f1, 0x14(r1)
    lfs f0, lbl_806DADDC(r2)
    lfs f2, 0x10(r1)
    fadds f1, f1, f0
    stfs f1, 0x14(r1)
    lwz r3, 0x14(r31)
    bl Scene3D_SetupProjection
    li r3, 0x80
    bl Alloc
    mr. r27, r3
    beq JumpDistanceMode_Init_L_802136E0
    li r4, 0x0
    bl HUD_Init
    JumpDistanceMode_Init_L_802136E0:
    stw r27, 0x28(r31)
    li r4, 0x6
    li r5, 0x0
    lwz r3, 0x28(r31)
    bl HUD_RegisterOverlay
    lwz r3, 0x28(r31)
    li r4, 0x11
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x28(r31)
    li r4, 0x12
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x28(r31)
    li r4, 0xe
    li r5, 0x0
    bl HUD_RegisterOverlay
    li r0, 0x0
    stb r0, g_lakituStartAnimDone(r13)
    lwz r3, 0x14(r31)
    bl SetCourseScene3D
    li r0, 0x0
    stb r0, g_raceEnded(r13)
    bl MiniGame_GetTimerValue
    xoris r3, r3, 0x8000
    lis r0, 0x4330
    stw r3, 0x2c(r1)
    li r3, 0x1
    lfd f2, lbl_806DADE0(r2)
    stw r0, 0x28(r1)
    lfs f0, lbl_806DAD7C(r2)
    lfd f1, 0x28(r1)
    fsubs f1, f1, f2
    stfs f1, g_raceTimeRemaining(r13)
    stfs f0, 0x64(r31)
    stfs f0, 0x60(r31)
    stfs f0, 0x5c(r31)
    bl PreloadEffectResources
    li r3, 0x9
    bl PreloadEffectResources
    li r3, 0xa
    bl PreloadEffectResources
    bl MiniGame_GetCourseData
    cmplwi r3, 0x0
    beq JumpDistanceMode_Init_L_8021379C
    lfs f0, 0x0(r3)
    stfs f0, 0x54(r31)
    JumpDistanceMode_Init_L_8021379C:
    li r3, 0x2c
    bl Alloc
    mr. r27, r3
    beq JumpDistanceMode_Init_L_802137C0
    lfs f0, 0x54(r31)
    fctiwz f0, f0
    stfd f0, 0x28(r1)
    lwz r4, 0x2c(r1)
    bl JumpDistanceMode_InitTimerDisplay
    JumpDistanceMode_Init_L_802137C0:
    stw r27, 0x2c(r31)
    li r3, 0x98
    bl Alloc
    cmplwi r3, 0x0
    beq JumpDistanceMode_Init_L_80213838
    li r6, 0x0
    lis r0, 0x4330
    stb r6, 0x0(r3)
    li r5, 0x1
    lfs f2, lbl_806DAD70(r2)
    li r4, 0x3
    stb r6, 0x1(r3)
    lfs f0, lbl_806DAD7C(r2)
    stb r6, 0x2(r3)
    lfd f1, lbl_806DADE0(r2)
    stw r6, 0x4(r3)
    stw r5, 0x8(r3)
    stfs f2, 0xc(r3)
    stfs f0, 0x10(r3)
    stfs f0, 0x14(r3)
    stw r4, 0x4(r3)
    stw r4, 0x8(r3)
    lwz r4, 0x8(r3)
    stw r0, 0x28(r1)
    xoris r0, r4, 0x8000
    stw r0, 0x2c(r1)
    lfd f0, 0x28(r1)
    fsubs f0, f0, f1
    fdivs f0, f2, f0
    stfs f0, 0xc(r3)
    JumpDistanceMode_Init_L_80213838:
    stw r3, 0x3c(r31)
    li r3, 0xc4c
    bl Alloc
    mr. r29, r3
    beq JumpDistanceMode_Init_L_802139E4
    li r0, 0x0
    lfs f0, lbl_806DAD7C(r2)
    stw r0, 0x0(r29)
    li r3, 0x20
    stw r0, 0x8(r29)
    stw r0, 0xc(r29)
    stw r0, 0x10(r29)
    stfs f0, 0x14(r29)
    stw r0, 0x18(r29)
    bl Alloc
    mr. r27, r3
    beq JumpDistanceMode_Init_L_80213888
    addi r4, r30, 0x560
    li r5, 0x1
    bl fn_8013D800
    JumpDistanceMode_Init_L_80213888:
    stw r27, 0x0(r29)
    lfs f1, lbl_806DAD7C(r2)
    lwz r3, 0x0(r29)
    lfs f2, lbl_806DAD70(r2)
    bl fn_8013D738
    lfs f1, lbl_806DAE0C(r2)
    lwz r3, 0x0(r29)
    fmr f2, f1
    fmr f3, f1
    bl fn_8013D608
    addi r28, r30, 0x4f0
    lwz r3, 0x0(r29)
    lfs f1, 0x4f0(r30)
    lfs f2, 0x4(r28)
    lfs f3, 0x8(r28)
    bl fn_8013D634
    li r3, 0x20
    bl Alloc
    mr. r27, r3
    beq JumpDistanceMode_Init_L_802138E4
    addi r4, r30, 0x570
    li r5, 0x1
    bl fn_8013D800
    JumpDistanceMode_Init_L_802138E4:
    stw r27, 0x4(r29)
    lfs f1, lbl_806DAD7C(r2)
    lwz r3, 0x4(r29)
    lfs f2, lbl_806DAD70(r2)
    bl fn_8013D738
    lfs f1, lbl_806DAE0C(r2)
    lwz r3, 0x4(r29)
    fmr f2, f1
    fmr f3, f1
    bl fn_8013D608
    lwz r3, 0x4(r29)
    lfs f1, 0x4f0(r30)
    lfs f2, 0x4(r28)
    lfs f3, 0x8(r28)
    bl fn_8013D634
    lis r3, 0x6666
    li r0, 0xf
    mr r11, r29
    addi r7, r30, 0x4d0
    addi r9, r3, 0x6667
    addi r4, r30, 0x4e4
    lfs f0, lbl_806DAD7C(r2)
    li r10, 0x0
    mtctr r0
    JumpDistanceMode_Init_L_80213944:
    mulhw r5, r9, r10
    li r3, 0x0
    li r0, -0x1
    srawi r6, r5, 1
    srwi r8, r6, 31
    srawi r5, r5, 1
    add r6, r6, r8
    mulli r8, r6, 0x5
    srwi r6, r5, 31
    add r5, r5, r6
    subf r6, r8, r10
    addi r10, r10, 0x1
    slwi r6, r6, 2
    slwi r5, r5, 2
    lfsx f2, r7, r6
    lfsx f1, r4, r5
    stfs f2, 0x634(r11)
    stfs f2, 0x1c(r11)
    stfs f1, 0x638(r11)
    stfs f1, 0x20(r11)
    stfs f0, 0x63c(r11)
    stfs f0, 0x24(r11)
    stfs f0, 0x640(r11)
    stfs f0, 0x28(r11)
    stw r3, 0x644(r11)
    stw r3, 0x2c(r11)
    stw r3, 0x648(r11)
    stw r3, 0x30(r11)
    stw r0, 0x64c(r11)
    stw r0, 0x34(r11)
    stw r0, 0x65c(r11)
    stw r0, 0x44(r11)
    stw r0, 0x66c(r11)
    stw r0, 0x54(r11)
    stw r0, 0x67c(r11)
    stw r0, 0x64(r11)
    stw r0, 0x68c(r11)
    stw r0, 0x74(r11)
    addi r11, r11, 0x68
    bdnz JumpDistanceMode_Init_L_80213944
    JumpDistanceMode_Init_L_802139E4:
    stw r29, 0x7c(r31)
    li r0, 0x0
    stw r0, 0x80(r31)
    stw r0, 0x84(r31)
    lwz r0, g_weatherSystem(r13)
    cmplwi r0, 0x0
    bne JumpDistanceMode_Init_L_80213A1C
    li r3, 0x1b4
    bl Alloc
    mr. r27, r3
    beq JumpDistanceMode_Init_L_80213A18
    li r4, 0x1
    bl WeatherSystem_Init
    JumpDistanceMode_Init_L_80213A18:
    stw r27, g_weatherSystem(r13)
    JumpDistanceMode_Init_L_80213A1C:
    li r3, 0x1
    bl SetResourceLoadingFlag
    li r3, 0x0
    bl InitRumbleController
    li r3, 0x0
    li r4, 0x1
    bl fn_801699D8
    li r3, 0x1
    li r4, 0x1
    bl fn_801699D8
    mr r3, r31
    psq_l f31, 0x58(r1), 0, 0
    lfd f31, 0x50(r1)
    lmw r27, 0x3c(r1)
    lwz r0, 0x64(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
}

/* Bounded genuine C++ draft: 75.47467% text; not linked.
 * Three structural approaches exhausted. Natural Grid construction remains
 * out-of-line (496B), violating the immutable singleton and EH boundaries.
 * The exact original fallback above is unchanged; genuine matched gain is zero.
 * Enable only together with the documented TU-local constructor bridges.
 */
#if 0
/* Natural constructor retrofit probe A; observed layouts only. */
#pragma cplusplus on
void* operator new(unsigned long);
void operator delete(void*);
struct JDInput; struct JDCamera; struct JDCar; struct JDScene; struct JDHud;
struct JDItem; struct JDEffect; struct JDWeather; struct JDKartCopy;
struct JDVec { float x, y, z; };
extern "C" {
extern const float lbl_806DAD70, lbl_806DAD7C, lbl_806DAD88, lbl_806DADA4;
extern const float lbl_806DADDC, lbl_806DAE08, lbl_806DAE0C;
extern const unsigned char lbl_803C3858[];
extern int g_ccClass, g_characterId, g_kartStartSlot, g_reverseRoundFlag;
extern int lbl_806D12BC;
extern unsigned char g_lakituStartAnimDone, g_raceEnded;
extern void* g_raceCamera; extern void* g_playerRenderObj;
extern float g_raceTimeRemaining;
extern JDWeather* g_weatherSystem;
void* DrawManager_GetOrCreate();
void SetResourceLoadingFlag(unsigned char);
void DMAChannelManager_Init(); void* TransitionEffect_GetOrCreate();
void SoundChannels_ClearAll(); void ItemObjectManager_Init();
void CourseObjectManager_Init(); void* GetCourseDataPtr();
void* RenderTarget_Create(void*);
void SetActiveCamera(int, JDCamera*);
void ProcessSystemTick(int); void* GetRaceContextPtr();
void RankingTable_Init(void*); void* SoundDriver_GetOrCreate(void*);
int GetDisplayBufferIndex(); int GetKartStartSlot(int);
int GetStartPosition(int,float*,float*,float*);
float GetCourseStartYaw();
const char** GetKartModelNameEntry(int,int);
void CarObject_Init(JDCar*,int,int,int,int,unsigned char,int,int,unsigned char,float,float,float);
void CarObject_SetPosition(JDCar*,const JDVec*);
void* CarObject_GetRenderObj(JDCar*);
void* CarObject_GetKartMovementPtr(JDCar*);
int KartMovement_EquipItem(void*,int);
void fn_8023E1E4(JDItem*,int,unsigned char);
void SetPlayerCarObject(JDCar*);
void Scene3D_Init(JDScene*,const char*);
void JumpDistanceMode_CopyKartMovement(JDKartCopy*,void*);
void Vec3_Subtract(const JDVec*,const JDVec*,JDVec*);
void Vec3_Normalize(const JDVec*,JDVec*);
void Scene3D_GetCameraPos(JDScene*,float*,float*);
int Scene3D_SetupProjection(JDScene*,float,float);
void HUD_RegisterOverlay(JDHud*,int,int);
void SetCourseScene3D(JDScene*);
int MiniGame_GetTimerValue(); const float* MiniGame_GetCourseData();
void PreloadEffectResources(int);
int InitRumbleController(unsigned char);
void fn_801699D8(unsigned int,unsigned char);
void fn_8013D738(JDEffect*,float,float);
void fn_8013D608(JDEffect*,float,float,float);
void fn_8013D634(JDEffect*,float,float,float);
}
struct JDRoot { JDRoot(); virtual ~JDRoot(); virtual void identity(); };
struct JDBase : JDRoot {
    float phase;
    JDBase() { phase = lbl_806DAD7C; }
    virtual ~JDBase();
    virtual void identity();
};
struct JDInput { unsigned char opaque[0x37C]; JDInput(); };
struct JDCamera { unsigned char opaque[0x2C]; JDCamera(int,int,void*,float,float); };
struct JDCar {
    unsigned char opaque[0x118];
    JDCar(const JDVec* p) {
        int cc = g_ccClass;
        int character = g_characterId;
        float yaw = GetCourseStartYaw();
        int display = GetDisplayBufferIndex();
        CarObject_Init(this,display,character,cc,0,1,7,0,0,p->x,p->z,yaw);
    }
};
struct JDItem { unsigned char opaque[0x44]; JDItem(unsigned char); };
struct JDLakitu { unsigned char opaque[0x58]; JDLakitu(const char*,int,float,float,float); };
struct JDScene {
    unsigned char opaque[0x3084];
    JDScene() { Scene3D_Init(this,*GetKartModelNameEntry(g_characterId,-1)); }
};
struct JDGoal { unsigned char opaque[8]; JDGoal(); };
struct JDKartCopy {
    unsigned char opaque[0x324];
    JDKartCopy(JDCar* car) { JumpDistanceMode_CopyKartMovement(this,CarObject_GetKartMovementPtr(car)); }
};
struct JDHelper {
    int state; JDScene* scene; JDVec position, rotation; float phase;
    JDHelper(JDScene* p) {
        state=0; scene=p; phase=lbl_806DAD7C;
        position.z=position.y=position.x=lbl_806DAD7C;
        rotation.z=rotation.y=rotation.x=lbl_806DAD7C;
    }
};
struct JDGate {
    const JDVec* row; JDVec normal, direction;
    JDGate(const JDVec* base) {
        row = g_reverseRoundFlag ? base+2 : base;
        Vec3_Subtract(row+1,row,&direction);
        Vec3_Normalize(&direction,&direction);
        normal.x=-direction.z; normal.y=direction.y; normal.z=direction.x;
    }
};
struct JDHud { unsigned char opaque[0x80]; JDHud(int); };
struct JDTimer { unsigned char opaque[0x2C]; JDTimer(int); };
struct JDScoreBase {
    unsigned char b0,b1,b2,pad; int state, count; float scale,x,y;
    unsigned char opaque[0x80];
    JDScoreBase() {
        b0=b1=b2=0; state=0; count=1; scale=lbl_806DAD70;
        x=lbl_806DAD7C; y=lbl_806DAD7C;
    }
};
struct JDScore : JDScoreBase {
    JDScore() { state=3; count=3; scale=lbl_806DAD70/(float)count; }
};
struct JDEffect { unsigned char opaque[0x20]; JDEffect(const char*,unsigned char); };
struct JDSubRow { int value; unsigned char opaque[12]; };
struct JDRow {
    float x,y,z,phase; int state, count; JDSubRow entries[5];
};
struct JDGridBase {
    JDEffect* first; JDEffect* second; int a,b,c; float phase; int state;
    JDGridBase() {
        first=0; a=0; b=0; c=0; phase=lbl_806DAD7C; state=0;
        first=new JDEffect((const char*)lbl_803C3858+0x560,1);
        fn_8013D738(first,lbl_806DAD7C,lbl_806DAD70);
        fn_8013D608(first,lbl_806DAE0C,lbl_806DAE0C,lbl_806DAE0C);
        const float* coords=(const float*)(lbl_803C3858+0x4F0);
        fn_8013D634(first,coords[0],coords[1],coords[2]);
        second=new JDEffect((const char*)lbl_803C3858+0x570,1);
        fn_8013D738(second,lbl_806DAD7C,lbl_806DAD70);
        fn_8013D608(second,lbl_806DAE0C,lbl_806DAE0C,lbl_806DAE0C);
        fn_8013D634(second,coords[0],coords[1],coords[2]);
    }
};
struct JDGrid : JDGridBase {
    JDRow banks[2][15];
    JDGrid() {
        for(int i=0;i<15;i++) {
            float x=((const float*)(lbl_803C3858+0x4D0))[i%5];
            float y=((const float*)(lbl_803C3858+0x4E4))[i/5];
            banks[1][i].x=x; banks[0][i].x=x;
            banks[1][i].y=y; banks[0][i].y=y;
            banks[0][i].z=lbl_806DAD7C; banks[1][i].z=lbl_806DAD7C;
            banks[0][i].phase=lbl_806DAD7C; banks[1][i].phase=lbl_806DAD7C;
            banks[0][i].state=0; banks[1][i].state=0;
            banks[0][i].count=0; banks[1][i].count=0;
            banks[0][i].entries[0].value=-1; banks[1][i].entries[0].value=-1;
            banks[0][i].entries[1].value=-1; banks[1][i].entries[1].value=-1;
            banks[0][i].entries[2].value=-1; banks[1][i].entries[2].value=-1;
            banks[0][i].entries[3].value=-1; banks[1][i].entries[3].value=-1;
            banks[0][i].entries[4].value=-1; banks[1][i].entries[4].value=-1;
        }
    }
};
struct JDWeather { unsigned char opaque[0x1B4]; JDWeather(unsigned char); };
struct JDOwner : JDBase {
    JDCar* car; JDLakitu* lakitu; JDInput* input; JDScene* scene;
    JDGoal* goal; JDItem* item; JDCamera* camera; void* renderTarget;
    JDHud* hud; JDTimer* timer; JDGate* gate1; JDGate* gate2; JDGate* gate3;
    JDScore* score; JDHelper* helper;
    unsigned char b44,b45,pad46[2]; int w48,w4C,w50;
    float duration, f58, f5C,f60,f64,f68;
    unsigned char b6C,b6D,pad6E[2]; JDKartCopy* copy; float f74;
    unsigned char b78,pad79[3]; JDGrid* grid; int w80,w84;
    unsigned char b88;
    JDOwner(); virtual void identity();
};
JDOwner::JDOwner() {
    car=0; lakitu=0; input=0; scene=0; goal=0; item=0; camera=0;
    renderTarget=0; hud=0; timer=0; gate1=0; gate2=0; gate3=0; score=0; helper=0;
    b44=0; b45=0; w48=0; w4C=0; w50=0;
    duration=lbl_806DADA4; f58=lbl_806DAD7C; f68=lbl_806DAD7C;
    b6C=0; b6D=0; copy=0; f74=lbl_806DAD7C; b78=0; b88=0;
    DrawManager_GetOrCreate(); SetResourceLoadingFlag(0); DMAChannelManager_Init();
    TransitionEffect_GetOrCreate(); SoundChannels_ClearAll(); ItemObjectManager_Init();
    CourseObjectManager_Init();
    input=new JDInput;
    renderTarget=RenderTarget_Create(GetCourseDataPtr());
    camera=new JDCamera(256,256,renderTarget,lbl_806DAE08,lbl_806DAD88);
    SetActiveCamera(0,camera); g_raceCamera=camera; ProcessSystemTick(0);
    RankingTable_Init(GetRaceContextPtr()); lbl_806D12BC=0; SoundDriver_GetOrCreate(0);
    g_kartStartSlot=GetKartStartSlot(GetDisplayBufferIndex());
    JDVec start; GetStartPosition(0,&start.x,&start.y,&start.z);
    car=new JDCar(&start); CarObject_SetPosition(car,&start);
    *(int*)((unsigned char*)CarObject_GetRenderObj(car)+0x238)=1;
    *((unsigned char*)CarObject_GetRenderObj(car)+0x2D0)=1;
    KartMovement_EquipItem(CarObject_GetRenderObj(car),0x17);
    item=new JDItem(0); fn_8023E1E4(item,0x17,0);
    SetPlayerCarObject(car); g_playerRenderObj=CarObject_GetRenderObj(car);
    lakitu=new JDLakitu((const char*)lbl_803C3858+0x54C,0,lbl_806DAD7C,lbl_806DAD7C,lbl_806DAD7C);
    scene=new JDScene; goal=new JDGoal; copy=new JDKartCopy(car);
    helper=new JDHelper(scene);
    gate1=new JDGate((const JDVec*)(lbl_803C3858+0x408));
    gate2=new JDGate((const JDVec*)(lbl_803C3858+0x438));
    gate3=new JDGate((const JDVec*)(lbl_803C3858+0x468));
    ProcessSystemTick(0);
    float projection1,projection2;
    Scene3D_GetCameraPos(scene,&projection1,&projection2);
    projection1+=lbl_806DADDC; Scene3D_SetupProjection(scene,projection1,projection2);
    hud=new JDHud(0);
    HUD_RegisterOverlay(hud,6,0); HUD_RegisterOverlay(hud,17,0);
    HUD_RegisterOverlay(hud,18,0); HUD_RegisterOverlay(hud,14,0);
    g_lakituStartAnimDone=0; SetCourseScene3D(scene); g_raceEnded=0;
    g_raceTimeRemaining=(float)MiniGame_GetTimerValue();
    f64=lbl_806DAD7C; f60=lbl_806DAD7C; f5C=lbl_806DAD7C;
    PreloadEffectResources(1); PreloadEffectResources(9); PreloadEffectResources(10);
    const float* course=MiniGame_GetCourseData(); if(course) duration=*course;
    timer=new JDTimer((int)duration);
    score=new JDScore;
    grid=new JDGrid; w80=0; w84=0;
    if(!g_weatherSystem) g_weatherSystem=new JDWeather(1);
    SetResourceLoadingFlag(1); InitRumbleController(0);
    fn_801699D8(0,1); fn_801699D8(1,1);
}
#pragma cplusplus off
#endif
