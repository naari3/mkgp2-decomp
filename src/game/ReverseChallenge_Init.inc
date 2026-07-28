/* === extracted from auto_ReverseChallenge_Ini_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void BananaPositionData_Init();
extern void BuildOrientationFromYaw();
extern void Camera_Create();
extern void CarObject_GetRenderObj();
extern void CarObject_Init();
extern void CarObject_ResetPhysics();
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
extern void GetRaceContextPtr();
extern void GetSpawnPosition();
extern void HUD_Init();
extern void HUD_RegisterOverlay();
extern void InputManager_Init();
extern void IsUraCourseFromSubMode();
extern void ItemObjectManager_Init();
extern void LakituStart_Init();
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

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_characterId;
extern unsigned int g_lakituStartAnimDone;
extern unsigned int g_raceCamera;
extern unsigned int g_raceEnded;
extern unsigned int g_raceTimeRemaining;
extern unsigned int g_weatherSystem;
extern unsigned int lbl_806D12BC;
extern unsigned int lbl_806D4F50;
extern unsigned int lbl_806D4F54;
extern unsigned int lbl_806D4F5C;
extern unsigned int lbl_806D4F70;
extern unsigned int lbl_806D4F78;
extern unsigned int lbl_806D4F7C;
extern unsigned int lbl_806D4F80;
extern unsigned int lbl_806D4F84;
extern unsigned int lbl_806D4F88;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80328DD8[];
extern unsigned int lbl_80328E10[];
extern unsigned int lbl_80419E70[];
extern unsigned int lbl_8048E144[];

/* --- function index (1 fns, .text 0x800AD910..0x800ADDA0) ---
 * [  0] 0x800AD910 size:0x490   global ReverseChallenge_Init
 */

/* --- forward decls --- */
asm void ReverseChallenge_Init(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();
extern void dtor_80122FD8();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; unsigned int f29; unsigned int f30; unsigned int f31; unsigned int f32; unsigned int f33; unsigned int f34; unsigned int f35; unsigned int f36; unsigned int f37; unsigned int f38; unsigned int f39; unsigned int f40; unsigned int f41; unsigned int f42; unsigned int f43; unsigned int f44; void *f45; unsigned int f46; unsigned int f47; void *f48; unsigned int f49; void *f50; unsigned int f51; unsigned int f52; void *f53; unsigned int f54; void *f55; unsigned int f56; unsigned int f57; void *f58; unsigned int f59; void *f60; unsigned int f61; unsigned int f62; void *f63; unsigned int f64; void *f65; unsigned int f66; unsigned int f67; void *f68; unsigned int f69; void *f70; unsigned int f71; unsigned int f72; void *f73; unsigned int f74; void *f75; unsigned int f76; unsigned int f77; void *f78; unsigned int f79; void *f80; unsigned int f81; unsigned int f82; void *f83; unsigned int f84; void *f85; unsigned int f86; unsigned int f87; void *f88; unsigned int f89; void *f90; unsigned int f91; unsigned int f92; void *f93; } extab_ReverseChallenge_Init = { 0x184A0000, 0x00000054, 0x000900B8, 0x00000084, 0x000000B0, 0x0000008C, 0x000400B8, 0x000000BC, 0x000000C4, 0x000000CC, 0x001100B8, 0x00000120, 0x001300D8, 0x0000017C, 0x000800B8, 0x000001C0, 0x000000EC, 0x000001CC, 0x000000B8, 0x000001E0, 0x00040100, 0x000001FC, 0x000000B8, 0x00000208, 0x00000114, 0x00000214, 0x000D00B8, 0x00000258, 0x00000128, 0x0000026C, 0x002900B8, 0x0000031C, 0x0003013C, 0x00000348, 0x000200B8, 0x00000390, 0x00030150, 0x000003C4, 0x002200B8, 0x0000045C, 0x00000164, 0x00000468, 0x000000B8, 0x00000000, 0x0A80001E, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001E, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8 };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ReverseChallenge_Init = {
    (void *)&ReverseChallenge_Init, 0x00000490, (void *)&extab_ReverseChallenge_Init
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ReverseChallenge_Init(void) { /* 0x800AD910 size:0x490 */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stfd f31, 0x40(r1)
    psq_st f31, 0x48(r1), 0, 0
    stw r31, 0x3c(r1)
    stw r30, 0x38(r1)
    stw r29, 0x34(r1)
    mr r31, r3
    mr r0, r31
    mr r30, r0
    bl GameMode_BaseInit
    lis r4, lbl_8048E144@ha
    lis r3, lbl_80419E70@ha
    addi r0, r4, lbl_8048E144@l
    lfs f0, lbl_806D4F54(r2)
    stw r0, 0x0(r30)
    addi r0, r3, lbl_80419E70@l
    stfs f0, 0x4(r30)
    stw r0, 0x0(r31)
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
    mr. r30, r3
    beq ReverseChallenge_Init_L_800AD994
    bl InputManager_Init
    ReverseChallenge_Init_L_800AD994:
    stw r30, 0x8(r31)
    bl GetCourseDataPtr
    bl RenderTarget_Create
    stw r3, 0x10(r31)
    li r3, 0x2c
    bl Alloc
    mr. r30, r3
    beq ReverseChallenge_Init_L_800AD9CC
    lfs f1, lbl_806D4F78(r2)
    li r4, 0x100
    lfs f2, lbl_806D4F50(r2)
    li r5, 0x100
    lwz r6, 0x10(r31)
    bl Camera_Create
    ReverseChallenge_Init_L_800AD9CC:
    stw r30, 0xc(r31)
    li r3, 0x0
    lwz r4, 0xc(r31)
    bl SetActiveCamera
    lwz r0, 0xc(r31)
    li r3, 0x0
    stw r0, g_raceCamera(r13)
    bl ProcessSystemTick
    bl GetRaceContextPtr
    bl RankingTable_Init
    li r0, 0x0
    li r3, 0x0
    stw r0, lbl_806D12BC(r13)
    bl SoundDriver_GetOrCreate
    lfs f1, lbl_806D4F54(r2)
    addi r3, r1, 0x18
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    li r3, 0x118
    bl Alloc
    mr. r29, r3
    beq ReverseChallenge_Init_L_800ADA7C
    lwz r30, g_characterId(r13)
    bl GetCourseStartYaw
    lfs f0, lbl_806D4F5C(r2)
    fadds f1, f0, f1
    bl BuildOrientationFromYaw
    fmr f31, f1
    bl GetDisplayBufferIndex
    li r0, 0x0
    mr r4, r3
    stw r0, 0x8(r1)
    fmr f3, f31
    mr r3, r29
    mr r5, r30
    lfs f1, 0x18(r1)
    li r6, 0x0
    lfs f2, 0x20(r1)
    li r7, 0x0
    li r8, 0x1
    li r9, 0x0
    li r10, 0x0
    bl CarObject_Init
    ReverseChallenge_Init_L_800ADA7C:
    stw r29, 0x14(r31)
    addi r4, r1, 0x18
    lwz r3, 0x14(r31)
    bl CarObject_SetPosition
    lwz r3, 0x14(r31)
    bl CarObject_GetRenderObj
    li r0, 0x1
    stw r0, 0x238(r3)
    lwz r3, 0x14(r31)
    bl SetPlayerCarObject
    li r3, 0x58
    bl Alloc
    mr. r29, r3
    beq ReverseChallenge_Init_L_800ADAD0
    lfs f1, lbl_806D4F54(r2)
    lis r4, lbl_80328E10@ha
    addi r4, r4, lbl_80328E10@l
    li r5, 0x0
    fmr f2, f1
    fmr f3, f1
    bl LakituStart_Init
    ReverseChallenge_Init_L_800ADAD0:
    stw r29, 0x18(r31)
    li r3, 0x3084
    bl Alloc
    mr. r29, r3
    beq ReverseChallenge_Init_L_800ADB00
    lwz r3, g_characterId(r13)
    li r4, -0x1
    bl GetKartModelNameEntry
    mr r4, r3
    mr r3, r29
    lwz r4, 0x0(r4)
    bl Scene3D_Init
    ReverseChallenge_Init_L_800ADB00:
    stw r29, 0x1c(r31)
    li r3, 0x8
    bl Alloc
    mr. r29, r3
    beq ReverseChallenge_Init_L_800ADB18
    bl ChallengeGoalCamera_Init
    ReverseChallenge_Init_L_800ADB18:
    stw r29, 0x20(r31)
    li r3, 0x0
    bl ProcessSystemTick
    lwz r3, 0x1c(r31)
    addi r4, r1, 0x14
    addi r5, r1, 0x10
    bl Scene3D_GetCameraPos
    lfs f1, 0x14(r1)
    lfs f0, lbl_806D4F7C(r2)
    lfs f2, 0x10(r1)
    fadds f1, f1, f0
    stfs f1, 0x14(r1)
    lwz r3, 0x1c(r31)
    bl Scene3D_SetupProjection
    li r3, 0x80
    bl Alloc
    mr. r29, r3
    beq ReverseChallenge_Init_L_800ADB68
    li r4, 0x0
    bl HUD_Init
    ReverseChallenge_Init_L_800ADB68:
    stw r29, 0x24(r31)
    li r4, 0x6
    li r5, 0x0
    lwz r3, 0x24(r31)
    bl HUD_RegisterOverlay
    lwz r3, 0x24(r31)
    li r4, 0x11
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x24(r31)
    li r4, 0x12
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x24(r31)
    li r4, 0xe
    li r5, 0x0
    bl HUD_RegisterOverlay
    li r0, 0x0
    stb r0, g_lakituStartAnimDone(r13)
    lwz r3, 0x1c(r31)
    bl SetCourseScene3D
    li r0, 0x0
    stb r0, g_raceEnded(r13)
    bl MiniGame_GetTimerValue
    xoris r3, r3, 0x8000
    lis r0, 0x4330
    stw r3, 0x2c(r1)
    li r3, 0x1
    lfd f1, lbl_806D4F70(r2)
    stw r0, 0x28(r1)
    lfd f0, 0x28(r1)
    fsubs f0, f0, f1
    stfs f0, g_raceTimeRemaining(r13)
    bl PreloadEffectResources
    li r3, 0x9
    bl PreloadEffectResources
    li r3, 0xa
    bl PreloadEffectResources
    li r0, 0x0
    li r3, 0x10
    stb r0, 0x40(r31)
    stb r0, 0x41(r31)
    stb r0, 0x42(r31)
    stw r0, 0x44(r31)
    stb r0, 0x48(r31)
    bl Alloc
    mr. r29, r3
    beq ReverseChallenge_Init_L_800ADC38
    bl IsUraCourseFromSubMode
    mr r4, r3
    mr r3, r29
    bl BananaPositionData_Init
    ReverseChallenge_Init_L_800ADC38:
    stw r29, 0x30(r31)
    li r4, 0x1
    lfs f0, lbl_806D4F54(r2)
    stfs f0, 0x34(r31)
    stfs f0, 0x38(r31)
    stfs f0, 0x3c(r31)
    lwz r3, 0x14(r31)
    bl CarObject_ResetPhysics
    li r3, 0x30
    bl Alloc
    mr. r29, r3
    beq ReverseChallenge_Init_L_800ADCC8
    lfs f0, lbl_806D4F80(r2)
    mr r4, r29
    lfs f2, lbl_806D4F54(r2)
    addi r3, r29, 0xc
    stfs f0, 0x0(r29)
    addi r5, r29, 0x18
    lfs f1, lbl_806D4F84(r2)
    stfs f2, 0x4(r29)
    lfs f0, lbl_806D4F88(r2)
    stfs f1, 0x8(r29)
    stfs f0, 0xc(r29)
    stfs f2, 0x10(r29)
    stfs f1, 0x14(r29)
    bl Vec3_Subtract
    addi r3, r29, 0x18
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0x20(r29)
    fneg f0, f0
    stfs f0, 0x24(r29)
    lfs f0, 0x1c(r29)
    stfs f0, 0x28(r29)
    lfs f0, 0x18(r29)
    stfs f0, 0x2c(r29)
    ReverseChallenge_Init_L_800ADCC8:
    stw r29, 0x28(r31)
    li r3, 0x20
    bl Alloc
    cmplwi r3, 0x0
    beq ReverseChallenge_Init_L_800ADD44
    lis r4, lbl_80328DD8@ha
    addi r4, r4, lbl_80328DD8@l
    lfs f3, 0x8(r4)
    lfs f7, 0x0(r4)
    lfs f4, 0xc(r4)
    fsubs f2, f3, f7
    lfs f6, 0x4(r4)
    lfs f5, 0x10(r4)
    fsubs f0, f4, f6
    lfs f1, 0x18(r4)
    stfs f2, 0x0(r3)
    lfs f2, 0x14(r4)
    fsubs f3, f5, f3
    stfs f0, 0x4(r3)
    fsubs f4, f2, f4
    lfs f0, 0x1c(r4)
    stfs f3, 0x8(r3)
    fsubs f3, f1, f5
    fsubs f2, f0, f2
    stfs f4, 0xc(r3)
    fsubs f1, f7, f1
    stfs f3, 0x10(r3)
    fsubs f0, f6, f0
    stfs f2, 0x14(r3)
    stfs f1, 0x18(r3)
    stfs f0, 0x1c(r3)
    ReverseChallenge_Init_L_800ADD44:
    stw r3, 0x2c(r31)
    lwz r0, g_weatherSystem(r13)
    cmplwi r0, 0x0
    bne ReverseChallenge_Init_L_800ADD70
    li r3, 0x1b4
    bl Alloc
    mr. r29, r3
    beq ReverseChallenge_Init_L_800ADD6C
    li r4, 0x1
    bl WeatherSystem_Init
    ReverseChallenge_Init_L_800ADD6C:
    stw r29, g_weatherSystem(r13)
    ReverseChallenge_Init_L_800ADD70:
    li r3, 0x1
    bl SetResourceLoadingFlag
    mr r3, r31
    psq_l f31, 0x48(r1), 0, 0
    lwz r0, 0x54(r1)
    lfd f31, 0x40(r1)
    lwz r31, 0x3c(r1)
    lwz r30, 0x38(r1)
    lwz r29, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}

