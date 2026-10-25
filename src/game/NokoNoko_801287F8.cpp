
/* sdata symbols referenced from asm */
extern unsigned char lbl_806D7084[7];
extern unsigned char lbl_806D708C[5];
/*
 * 0x801287F8..0x8012A5AC: Noko Noko challenge and time trial scene.
 */
#pragma cplusplus on

struct Vec3 { float x, y, z; };
struct LNode { char pad[8]; void *f8; };
struct Trail { int age; Vec3 pos; };
struct Shot {
    char pad0[0x14];
    int active;
    char pad18[8];
    Vec3 pos;
    char pad2C[0xc];
    float rot;
    float alpha;
    Trail trail[18];
    char pad160[0xc];
};
struct ShotSet {
    Shot shots[6];
};
struct ShotOwner {
    char pad0[4];
    void *model;
    void *trailModel;
    char padC[0x89c - 0xc];
    int trailCount;
};

struct ModelPair {
    void **vt;
    void *a;
    void *b;
};

/* TOP-END */

extern "C" {
extern void CObj_DebugVizPathFlush();
extern void CourseEnvironment_RenderObjects_Timed();
extern void DrawEffect_TickAndCull();
extern void HSD_StateInvalidate();
extern void ItemObjectManager_Render();
extern void KartItem_RenderPipelinedWithEffects();
extern void NokoNoko_Render();
extern void Object_RenderJObjIfWithinRange();
extern void Subsystem36c_DispatchPass2_Timed();
extern void Subsystem36c_DispatchPass4_Timed();
extern void TransitionEffect_RenderPass();
extern void TransparentDraw_SortAndDispatch();
extern void clDrawMan_Buckets_Dispatch();
extern void clDrawMan_Buckets_Reset();
extern void clDrawMan_EndFrame_NoOp();
extern void clDrawMan_SetMaxClipZ();
extern void clItemBoxManager_Draw();
extern void fn_8011F994();
extern void fn_8016B0C4();
extern void fn_80253448();
extern void fn_802535D4();
extern unsigned int lbl_806D109C;
extern unsigned int lbl_806D10AC;
extern unsigned int lbl_806D10D0;
extern unsigned int lbl_806D7048;
extern unsigned int lbl_806DC190;
extern unsigned int lbl_806DC1B0;
extern unsigned int lbl_806DC1B8;
extern void CObj_ApplyScissor();
extern void CObj_LoadProjMatrix();
extern void CarObject_ApplyInput();
extern void CarObject_CalcSpeedRatio();
extern void CarObject_FrameUpdate();
extern void CarObject_GetRenderObj();
extern void ChallengeGoalCamera_Update();
extern void Clamp_Int();
extern void CourseEnvironment_UpdateAndCullZones_Timed();
extern void DebugPrintf();
extern void Fog_UpdateFromCourseScene3D();
extern void GetInputManager();
extern void GetRaceContextPtr();
extern void HSD_JObjSetupMatrixSub();
extern void HUD_FrameUpdate();
extern void InputMgr_GetPlayer();
extern void IsCardValid();
extern void IsRaceStarted();
extern void ItemObjectManager_PerFrameUpdate();
extern void ItemObjectManager_Update();
extern void KartDriver_GetKartRootMtx();
extern void KartItem_GetCarVelocityVec3();
extern void KartItem_GetCurrentISESlot();
extern void KartItem_GetCurrentSpeedWithBonus();
extern void KartItem_UpdateShadowBillboardAndViewport();
extern void KartMovement_CanReceiveItem();
extern void KartMovement_ResetOnGoal();
extern void KartMovement_ResetOnTimeout();
extern void KartMovement_SetSpeedScale();
extern void LakituStart_UpdateCountdown();
extern void NokoNokoChallenge_CalcResultText();
extern void NokoNokoChallenge_GetCoinDivisor();
extern void NokoNokoChallenge_HandleBrakeInput();
extern void NokoNokoChallenge_SaveResult();
extern void NokoNokoChallenge_TransitionToResult();
extern void NokoNoko_CheckHitAndKill();
extern void NokoNoko_CountDefeated();
extern void NokoNoko_FindNearest();
extern void NokoNoko_StopAllAlive();
extern void NokoNoko_UpdateAll();
extern void Object_SetByte10_Return1();
extern void RenderObj_UseItem();
extern void ResolveJointByName();
extern void SetCoinCount();
extern void SoundMgr_PlaySE();
extern void TransitionEffect_Tick();
extern void Vec3_Dot();
extern void Vec3_Normalize();
extern void Vec3_Subtract();
extern void VfxSlotMgr_Update();
extern void __assert();
extern void fn_8011FAFC();
extern void fn_80121E10();
extern void fn_8016B32C();
extern void fn_8016C360();
extern void fn_8016C394();
extern void fn_80253C40();
extern void fn_80253C74();
extern void fn_80253EBC();
extern void fn_80253EC0();
extern void fn_80253FD8();
extern unsigned int g_lakituStartAnimDone;
extern unsigned int g_raceEnded;
extern unsigned int g_raceTimeRemaining;
extern unsigned int g_weatherSystem;
extern unsigned int lbl_806D1290;
extern const float lbl_806D7054;
extern const float lbl_806D7058;
extern unsigned int lbl_806D7068;
extern unsigned int lbl_806D706C;
extern unsigned int lbl_806D7070;
extern unsigned int lbl_806D7074;
extern unsigned int lbl_806D7078;
extern unsigned int lbl_806D707C;
extern unsigned int lbl_806D7080;
extern unsigned int lbl_806D7094;
extern unsigned int lbl_806D7098;
extern unsigned int lbl_806D709C;
extern unsigned int lbl_806D70A0;
extern unsigned int lbl_806D70A4;
extern unsigned int lbl_806D70A8;
extern unsigned int lbl_803561E8[];
extern unsigned int lbl_80677C58[];
extern unsigned int lbl_80677C64[];
extern void dtor_80036E40();
extern void ClRomTable_PurgeAll();
extern void CourseEnvironment_Dtor();
extern void ItemObjectManager_Reset();
extern void LakituStart_Dtor();
void MemoryManager_TimedFree(void *p);
extern void RankingTable_Init();
extern void SceneDrawList_Reset();
extern void SetActiveCamera();
extern void SetPlayerCarObject();
extern void SetResourceLoadingFlag();
extern void VfxSlotMgr_Shutdown();
extern void __destroy_arr();
extern void clRom_PurgeAll();
extern void dtor_80122FD8();
extern void fn_80121210();
extern void fn_80124C84();
extern void fn_8016C634();
extern void fn_80188DA8();
extern void fn_80254134();
extern unsigned int g_raceCamera;
extern unsigned int dtor_80082960[];
extern unsigned int lbl_8048E338[];
extern void Alloc();
extern void Archive_GetRootJObj();
extern void Camera_Create();
extern void CarObject_Init();
extern void ChallengeGoalCamera_Init();
extern void CourseObjectManager_Init();
extern void DMAChannelManager_Init();
extern void DrawManager_GetOrCreate();
extern void GameMode_BaseInit();
extern void GetCourseDataPtr();
extern void GetCourseStartYaw();
extern void GetDisplayBufferIndex();
extern void GetKartModelNameEntry();
extern void GetStartPosition();
extern void HSD_JObjSetFlags();
extern void HSD_LObjLoadDesc();
extern void HUD_Init();
extern void HUD_RegisterOverlay();
extern void InputManager_Init();
extern void ItemObjectManager_Init();
extern void KartMovement_EquipItem();
extern void LakituStart_Init();
extern void MapWaterEffect_Init();
extern void MiniGame_GetCourseData();
extern void MiniGame_GetTimerValue();
extern void NokoNoko_Init();
void Object_SetJObjScaleXYZ(void *o, float x, float y, float z);
extern void PreloadEffectResources();
extern void PreloadResource();
extern void ProcessSystemTick();
extern void Scene3D_GetCameraPos();
extern void Scene3D_Init();
extern void Scene3D_SetupProjection();
extern void SetCourseScene3D();
extern void SoundChannels_ClearAll();
extern void SoundDriver_GetOrCreate();
extern void TransitionEffect_GetOrCreate();
extern void WeatherSystem_Init();
extern void __construct_array();
extern void clNormal3D_Construct();
extern void clNormal3D_SetFlags();
extern unsigned int g_characterId;
extern unsigned int lbl_806D12BC;
extern const float lbl_806D7050;
extern unsigned int lbl_806D7060;
extern unsigned int lbl_806D70B0;
extern unsigned int lbl_806D70BC;
extern unsigned int lbl_806D70C0;
extern unsigned int lbl_806D70C4;
extern unsigned int ResCtrl_Init[];
extern unsigned int lbl_8048E144[];
extern void *lbl_8048E34C[];
extern void *lbl_8048E36C[];
extern void dtor_8012A5AC();
struct LNode *LinkedNode_GetField10_OrFallback(void *o, int idx);
void Object_RenderJObjEx(void *o, void *node, int mask);
void Object_RenderJObjTree(void *o, int mask);
void Object_SetColorAlphaOnly(void *o, int idx, float a);
void Object_SetJObjPositionVec(void *o, struct Vec3 *v);
void Object_SetJObjRotationY(void *o, float r);
extern const float lbl_806D704C;
extern void LUT_Sin12Bit();
extern void Terrain_GetGroundHeightWithPenetration();
extern void fn_80186960();
extern unsigned int lbl_806D70AC;
extern unsigned int lbl_806D70B4;
extern unsigned int lbl_806D70B8;
extern unsigned int lbl_80495994[];
extern unsigned int lbl_80495A94[];
void Object_DtorWithGXSync(void *o, int flag);
asm void TimeTrial_Render(void);
asm void NokoNokoChallenge_Update(void);
asm void TimeTrial_Destroy(void);
asm void NokoNokoChallenge_Init(void);
void fn_8012A070(ShotOwner *self);
asm void fn_8012A22C(void);
ModelPair *fn_8012A52C(ModelPair *self, short flag);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TimeTrial_Render[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_NokoNokoChallenge_Update = { 0x308A0000, 0x00000258, 0x028F0010, 0x00000000, 0x8200002C, (void *)&dtor_80036E40 };

__declspec(section ".extab_user") static const unsigned char extab_TimeTrial_Destroy[8] = {
    0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; unsigned int f29; unsigned int f30; unsigned int f31; unsigned int f32; unsigned int f33; unsigned int f34; unsigned int f35; unsigned int f36; unsigned int f37; unsigned int f38; unsigned int f39; unsigned int f40; unsigned int f41; unsigned int f42; unsigned int f43; unsigned int f44; unsigned int f45; unsigned int f46; unsigned int f47; unsigned int f48; unsigned int f49; unsigned int f50; unsigned int f51; unsigned int f52; unsigned int f53; unsigned int f54; unsigned int f55; unsigned int f56; unsigned int f57; unsigned int f58; unsigned int f59; unsigned int f60; void *f61; unsigned int f62; unsigned int f63; void *f64; unsigned int f65; void *f66; unsigned int f67; unsigned int f68; void *f69; unsigned int f70; void *f71; unsigned int f72; unsigned int f73; void *f74; unsigned int f75; void *f76; unsigned int f77; unsigned int f78; void *f79; unsigned int f80; void *f81; unsigned int f82; unsigned int f83; void *f84; unsigned int f85; void *f86; unsigned int f87; unsigned int f88; void *f89; unsigned int f90; void *f91; unsigned int f92; unsigned int f93; void *f94; unsigned int f95; void *f96; unsigned int f97; unsigned int f98; void *f99; unsigned int f100; unsigned int f101; unsigned int f102; unsigned int f103; void *f104; unsigned int f105; void *f106; unsigned int f107; unsigned int f108; void *f109; unsigned int f110; void *f111; unsigned int f112; void *f113; unsigned int f114; unsigned int f115; void *f116; unsigned int f117; void *f118; unsigned int f119; unsigned int f120; unsigned int f121; void *f122; unsigned int f123; unsigned int f124; void *f125; unsigned int f126; unsigned int f127; void *f128; } extab_NokoNokoChallenge_Init = { 0x204A0000, 0x00000060, 0x000900F8, 0x00000090, 0x000000F0, 0x00000098, 0x000400F8, 0x000000C8, 0x00000104, 0x000000D8, 0x001100F8, 0x0000012C, 0x00100118, 0x00000178, 0x000E00F8, 0x000001D0, 0x0000012C, 0x000001DC, 0x000000F8, 0x000001F0, 0x00040140, 0x0000020C, 0x000000F8, 0x00000218, 0x00000154, 0x00000224, 0x000000F8, 0x00000230, 0x00000168, 0x0000023C, 0x000D00F8, 0x00000280, 0x0000017C, 0x00000294, 0x003100F8, 0x00000380, 0x000001A4, 0x00000388, 0x00040190, 0x0000050C, 0x000000F8, 0x0000053C, 0x000001C0, 0x00000550, 0x000001B8, 0x00000564, 0x000201C0, 0x00000580, 0x000001D4, 0x0000058C, 0x000201C0, 0x000006D8, 0x000001E0, 0x000006F0, 0x000000F8, 0x00000700, 0x000001F0, 0x0000070C, 0x000000F8, 0x00000000, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0980001C, 0x00000000, 0x00000008, 0x00000058, (void *)&dtor_80082960, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x010001C0, 0x0680001C, 0x00000000, (void *)&dtor_8012A5AC, 0x010001C0, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8 };


__declspec(section ".extab_user") static const unsigned char extab_fn_8012A22C[8] = {
    0x40, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TimeTrial_Render = {
    (void *)&TimeTrial_Render, 0x000001C0, (void *)extab_TimeTrial_Render
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_NokoNokoChallenge_Update = {
    (void *)&NokoNokoChallenge_Update, 0x00000CBC, (void *)&extab_NokoNokoChallenge_Update
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TimeTrial_Destroy = {
    (void *)&TimeTrial_Destroy, 0x000002C4, (void *)extab_TimeTrial_Destroy
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_NokoNokoChallenge_Init = {
    (void *)&NokoNokoChallenge_Init, 0x00000738, (void *)&extab_NokoNokoChallenge_Init
};


__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8012A22C = {
    (void *)&fn_8012A22C, 0x00000300, (void *)extab_fn_8012A22C
};


}





extern "C" asm void TimeTrial_Render(void) { /* 0x801287F8 size:0x1C0 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lbz r0, 0x34(r3)
    cmplwi r0, 0x0
    beq TimeTrial_Render_L_801289A4
    lwz r3, 0x14(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne TimeTrial_Render_L_80128970
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne TimeTrial_Render_L_80128848
    li r3, 0x0
    TimeTrial_Render_L_80128848:
    bl clDrawMan_Buckets_Reset
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne TimeTrial_Render_L_8012885C
    li r3, 0x0
    TimeTrial_Render_L_8012885C:
    lfs f1, lbl_806D7048(r2)
    bl clDrawMan_SetMaxClipZ
    bl TransparentDraw_SortAndDispatch
    lwz r3, 0x14(r31)
    bl CObj_DebugVizPathFlush
    bl fn_8016B0C4
    lwz r3, 0x8(r31)
    li r4, 0x0
    bl KartItem_RenderPipelinedWithEffects
    lwz r3, 0xc(r31)
    bl Object_RenderJObjIfWithinRange
    lwz r3, 0x10(r31)
    bl CourseEnvironment_RenderObjects_Timed
    bl NokoNoko_Render
    lwz r3, 0x44(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lwz r3, lbl_806D10D0(r13)
    cmplwi r3, 0x0
    bne TimeTrial_Render_L_801288B8
    li r3, 0x0
    TimeTrial_Render_L_801288B8:
    bl clItemBoxManager_Draw
    lwz r3, 0x10(r31)
    bl Subsystem36c_DispatchPass2_Timed
    bl ItemObjectManager_Render
    lwz r3, 0x30(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    bl DrawEffect_TickAndCull
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne TimeTrial_Render_L_801288F0
    li r3, 0x0
    TimeTrial_Render_L_801288F0:
    bl clDrawMan_EndFrame_NoOp
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne TimeTrial_Render_L_80128904
    li r3, 0x0
    TimeTrial_Render_L_80128904:
    bl clDrawMan_Buckets_Dispatch
    lwz r3, 0x10(r31)
    bl Subsystem36c_DispatchPass4_Timed
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne TimeTrial_Render_L_80128920
    li r3, 0x0
    TimeTrial_Render_L_80128920:
    li r4, 0x2
    bl TransitionEffect_RenderPass
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne TimeTrial_Render_L_80128938
    li r3, 0x0
    TimeTrial_Render_L_80128938:
    li r4, 0x4
    bl TransitionEffect_RenderPass
    lwz r4, lbl_806DC1B0(r2)
    lwz r0, lbl_806DC190(r2)
    lwz r3, 0x28(r31)
    or r4, r4, r0
    bl fn_80253448
    li r3, 0x1
    bl fn_8011F994
    lwz r3, 0x14(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    TimeTrial_Render_L_80128970:
    lwz r3, 0x28(r31)
    lwz r4, lbl_806DC1B8(r2)
    bl fn_80253448
    lwz r3, 0x28(r31)
    bl fn_802535D4
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne TimeTrial_Render_L_80128994
    li r3, 0x0
    TimeTrial_Render_L_80128994:
    li r4, 0x1
    bl TransitionEffect_RenderPass
    li r3, 0x7f
    bl HSD_StateInvalidate
    TimeTrial_Render_L_801289A4:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void NokoNokoChallenge_Update(void) { /* 0x801289B8 size:0xCBC */
    nofralloc
    stwu r1, -0xa0(r1)
    mflr r0
    stw r0, 0xa4(r1)
    stfd f31, 0x90(r1)
    psq_st f31, 0x98(r1), 0, 0
    stfd f30, 0x80(r1)
    psq_st f30, 0x88(r1), 0, 0
    stmw r26, 0x68(r1)
    mr r28, r3
    lis r3, lbl_803561E8@ha
    lbz r0, 0x34(r28)
    addi r30, r3, lbl_803561E8@l
    cmplwi r0, 0x0
    bne NokoNokoChallenge_Update_L_801289F8
    li r0, 0x1
    stb r0, 0x34(r28)
    NokoNokoChallenge_Update_L_801289F8:
    bl GetRaceContextPtr
    bl ItemObjectManager_PerFrameUpdate
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lbz r0, g_raceEnded(r13)
    mr r26, r3
    cmplwi r0, 0x1
    beq NokoNokoChallenge_Update_L_80128AF0
    lbz r0, lbl_806D1290(r13)
    cmplwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80128A40
    lwz r12, 0x0(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    fmr f31, f1
    b NokoNokoChallenge_Update_L_80128A44
    NokoNokoChallenge_Update_L_80128A40:
    lfs f31, lbl_806D7068(r2)
    NokoNokoChallenge_Update_L_80128A44:
    lwz r12, 0x0(r26)
    mr r3, r26
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl
    lfs f0, lbl_806D706C(r2)
    fmr f30, f1
    li r29, 0x0
    fcmpo cr0, f31, f0
    bge NokoNokoChallenge_Update_L_80128A84
    fcmpo cr0, f30, f0
    bge NokoNokoChallenge_Update_L_80128A84
    bl IsRaceStarted
    clrlwi. r0, r3, 24
    beq NokoNokoChallenge_Update_L_80128A84
    li r29, 0x1
    NokoNokoChallenge_Update_L_80128A84:
    mr r3, r28
    mr r4, r29
    bl NokoNokoChallenge_HandleBrakeInput
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne NokoNokoChallenge_Update_L_80128AA0
    lfs f31, lbl_806D7058(r2)
    NokoNokoChallenge_Update_L_80128AA0:
    bl IsRaceStarted
    mr r29, r3
    mr r3, r26
    lwz r12, 0x0(r26)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    fmr f2, f31
    lwz r3, 0x8(r28)
    fmr f3, f30
    mr r4, r29
    bl CarObject_ApplyInput
    lwz r3, 0x8(r28)
    li r4, 0x0
    bl CarObject_FrameUpdate
    lwz r3, 0x8(r28)
    li r5, 0x0
    lwz r4, 0x14(r28)
    bl KartItem_UpdateShadowBillboardAndViewport
    b NokoNokoChallenge_Update_L_80128B5C
    NokoNokoChallenge_Update_L_80128AF0:
    lfs f1, lbl_806D7070(r2)
    li r4, 0x1
    lwz r3, 0x8(r28)
    fmr f2, f1
    fmr f3, f1
    bl CarObject_ApplyInput
    lwz r3, 0x8(r28)
    lfs f1, lbl_806D7074(r2)
    bl KartMovement_SetSpeedScale
    lwz r3, 0x8(r28)
    li r4, 0x0
    bl CarObject_FrameUpdate
    lwz r0, 0x38(r28)
    cmpwi r0, 0x0
    ble NokoNokoChallenge_Update_L_80128B40
    lwz r3, 0x8(r28)
    li r5, 0x0
    lwz r4, 0x14(r28)
    bl KartItem_UpdateShadowBillboardAndViewport
    b NokoNokoChallenge_Update_L_80128B5C
    NokoNokoChallenge_Update_L_80128B40:
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    bl KartDriver_GetKartRootMtx
    mr r5, r3
    lwz r3, 0x18(r28)
    lwz r4, 0x14(r28)
    bl ChallengeGoalCamera_Update
    NokoNokoChallenge_Update_L_80128B5C:
    bl IsRaceStarted
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne NokoNokoChallenge_Update_L_80128BB4
    lbz r0, g_raceEnded(r13)
    cmplwi r0, 0x1
    beq NokoNokoChallenge_Update_L_80128BB4
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    li r4, 0x1
    bl KartMovement_CanReceiveItem
    clrlwi. r0, r3, 24
    beq NokoNokoChallenge_Update_L_80128BB4
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    li r4, 0x0
    li r5, 0x0
    bl RenderObj_UseItem
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    li r0, -0x1
    stw r0, 0x290(r3)
    NokoNokoChallenge_Update_L_80128BB4:
    bl Fog_UpdateFromCourseScene3D
    lwz r3, 0xc(r28)
    bl LakituStart_UpdateCountdown
    lwz r3, 0x10(r28)
    bl CourseEnvironment_UpdateAndCullZones_Timed
    lwz r3, 0x30(r28)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    bl KartDriver_GetKartRootMtx
    lfs f0, 0xc(r3)
    addi r4, r1, 0x44
    lfs f1, lbl_806D7078(r2)
    stfs f0, 0x50(r1)
    lfs f0, 0x1c(r3)
    stfs f0, 0x54(r1)
    lfs f0, 0x2c(r3)
    addi r3, r1, 0x50
    stfs f0, 0x58(r1)
    bl NokoNoko_CheckHitAndKill
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne NokoNokoChallenge_Update_L_80128DA8
    lwz r3, 0x8(r28)
    addi r4, r1, 0x2c
    bl KartItem_GetCarVelocityVec3
    lfs f3, 0x44(r1)
    addi r3, r1, 0x38
    lfs f2, 0x50(r1)
    mr r4, r3
    lfs f1, 0x4c(r1)
    lfs f0, 0x58(r1)
    fsubs f3, f3, f2
    lfs f2, lbl_806D7070(r2)
    fsubs f0, f1, f0
    stfs f3, 0x38(r1)
    stfs f2, 0x3c(r1)
    stfs f0, 0x40(r1)
    bl Vec3_Normalize
    lfs f4, lbl_806D7080(r2)
    lfs f3, 0x2c(r1)
    lfs f2, 0x38(r1)
    lfs f1, 0x34(r1)
    lfs f0, 0x40(r1)
    fmadds f2, f4, f3, f2
    lfs f3, lbl_806D707C(r2)
    fmadds f1, f4, f1, f0
    lfs f0, lbl_806D7054(r2)
    fmuls f2, f3, f2
    stfs f0, 0x3c(r1)
    fmuls f0, f3, f1
    stfs f2, 0x38(r1)
    stfs f0, 0x40(r1)
    lwz r29, 0x44(r28)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq NokoNokoChallenge_Update_L_80128DA8
    addi r3, r30, 0x488
    addi r4, r30, 0x4a4
    li r5, 0x386
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne NokoNokoChallenge_Update_L_80128CD4
    li r3, 0xab
    bl fn_8016C394
    NokoNokoChallenge_Update_L_80128CD4:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r29)
    li r3, 0x0
    cmpwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80128CF4
    li r3, 0x0
    b NokoNokoChallenge_Update_L_80128D54
    NokoNokoChallenge_Update_L_80128CF4:
    lwz r0, 0x180(r29)
    cmpwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80128D08
    li r3, 0x1
    b NokoNokoChallenge_Update_L_80128D54
    NokoNokoChallenge_Update_L_80128D08:
    lwz r0, 0x2ec(r29)
    cmpwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80128D1C
    li r3, 0x2
    b NokoNokoChallenge_Update_L_80128D54
    NokoNokoChallenge_Update_L_80128D1C:
    lwz r0, 0x458(r29)
    cmpwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80128D30
    li r3, 0x3
    b NokoNokoChallenge_Update_L_80128D54
    NokoNokoChallenge_Update_L_80128D30:
    lwz r0, 0x5c4(r29)
    cmpwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80128D44
    li r3, 0x4
    b NokoNokoChallenge_Update_L_80128D54
    NokoNokoChallenge_Update_L_80128D44:
    lwz r0, 0x730(r29)
    cmpwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80128D54
    li r3, 0x5
    NokoNokoChallenge_Update_L_80128D54:
    mulli r3, r3, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D7070(r2)
    add r3, r29, r3
    stw r4, 0x14(r3)
    stw r0, 0x1c(r3)
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x44(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x48(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x4c(r1)
    stfs f0, 0x28(r3)
    lfs f0, 0x38(r1)
    stfs f0, 0x2c(r3)
    lfs f0, 0x40(r1)
    stfs f0, 0x34(r3)
    lfs f0, 0x3c(r1)
    stfs f0, 0x30(r3)
    NokoNokoChallenge_Update_L_80128DA8:
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    bl KartItem_GetCurrentISESlot
    cmplwi r3, 0x0
    beq NokoNokoChallenge_Update_L_80128DC4
    lwz r3, 0x18(r3)
    b NokoNokoChallenge_Update_L_80128DC8
    NokoNokoChallenge_Update_L_80128DC4:
    li r3, 0x0
    NokoNokoChallenge_Update_L_80128DC8:
    cmplwi r3, 0x0
    beq NokoNokoChallenge_Update_L_80129008
    lwz r3, 0x18(r3)
    cmplwi r3, 0x0
    beq NokoNokoChallenge_Update_L_80129008
    addi r4, r30, 0x4b4
    bl ResolveJointByName
    mr. r26, r3
    beq NokoNokoChallenge_Update_L_80129008
    bne NokoNokoChallenge_Update_L_80128E00
    la r3, lbl_806D7084(r2)  /* lbl_806D7084 */
    li r4, 0x47c
    la r5, lbl_806D708C(r2)  /* lbl_806D708C */
    bl __assert
    NokoNokoChallenge_Update_L_80128E00:
    cmplwi r26, 0x0
    beq NokoNokoChallenge_Update_L_80128E48
    bne NokoNokoChallenge_Update_L_80128E1C
    la r3, lbl_806D7084(r2)  /* lbl_806D7084 */
    li r4, 0x25d
    la r5, lbl_806D708C(r2)  /* lbl_806D708C */
    bl __assert
    NokoNokoChallenge_Update_L_80128E1C:
    lwz r4, 0x14(r26)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne NokoNokoChallenge_Update_L_80128E38
    rlwinm. r0, r4, 0, 25, 25
    beq NokoNokoChallenge_Update_L_80128E38
    li r3, 0x1
    NokoNokoChallenge_Update_L_80128E38:
    clrlwi. r0, r3, 24
    beq NokoNokoChallenge_Update_L_80128E48
    mr r3, r26
    bl HSD_JObjSetupMatrixSub
    NokoNokoChallenge_Update_L_80128E48:
    lfs f0, 0x50(r26)
    addi r3, r1, 0x50
    lfs f1, lbl_806D7094(r2)
    addi r4, r1, 0x44
    stfs f0, 0x50(r1)
    lfs f0, 0x60(r26)
    stfs f0, 0x54(r1)
    lfs f0, 0x70(r26)
    stfs f0, 0x58(r1)
    bl NokoNoko_CheckHitAndKill
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne NokoNokoChallenge_Update_L_80129008
    lwz r3, 0x8(r28)
    addi r4, r1, 0x2c
    bl KartItem_GetCarVelocityVec3
    lfs f3, 0x44(r1)
    addi r3, r1, 0x38
    lfs f2, 0x50(r1)
    mr r4, r3
    lfs f1, 0x4c(r1)
    lfs f0, 0x58(r1)
    fsubs f3, f3, f2
    lfs f2, lbl_806D7070(r2)
    fsubs f0, f1, f0
    stfs f3, 0x38(r1)
    stfs f2, 0x3c(r1)
    stfs f0, 0x40(r1)
    bl Vec3_Normalize
    lfs f4, lbl_806D7080(r2)
    lfs f3, 0x2c(r1)
    lfs f2, 0x38(r1)
    lfs f1, 0x34(r1)
    lfs f0, 0x40(r1)
    fmadds f2, f4, f3, f2
    lfs f3, lbl_806D707C(r2)
    fmadds f1, f4, f1, f0
    lfs f0, lbl_806D7054(r2)
    fmuls f2, f3, f2
    stfs f0, 0x3c(r1)
    fmuls f0, f3, f1
    stfs f2, 0x38(r1)
    stfs f0, 0x40(r1)
    lwz r29, 0x44(r28)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq NokoNokoChallenge_Update_L_80129008
    addi r3, r30, 0x488
    addi r4, r30, 0x4a4
    li r5, 0x386
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne NokoNokoChallenge_Update_L_80128F34
    li r3, 0xab
    bl fn_8016C394
    NokoNokoChallenge_Update_L_80128F34:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r29)
    li r3, 0x0
    cmpwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80128F54
    li r3, 0x0
    b NokoNokoChallenge_Update_L_80128FB4
    NokoNokoChallenge_Update_L_80128F54:
    lwz r0, 0x180(r29)
    cmpwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80128F68
    li r3, 0x1
    b NokoNokoChallenge_Update_L_80128FB4
    NokoNokoChallenge_Update_L_80128F68:
    lwz r0, 0x2ec(r29)
    cmpwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80128F7C
    li r3, 0x2
    b NokoNokoChallenge_Update_L_80128FB4
    NokoNokoChallenge_Update_L_80128F7C:
    lwz r0, 0x458(r29)
    cmpwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80128F90
    li r3, 0x3
    b NokoNokoChallenge_Update_L_80128FB4
    NokoNokoChallenge_Update_L_80128F90:
    lwz r0, 0x5c4(r29)
    cmpwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80128FA4
    li r3, 0x4
    b NokoNokoChallenge_Update_L_80128FB4
    NokoNokoChallenge_Update_L_80128FA4:
    lwz r0, 0x730(r29)
    cmpwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80128FB4
    li r3, 0x5
    NokoNokoChallenge_Update_L_80128FB4:
    mulli r3, r3, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D7070(r2)
    add r3, r29, r3
    stw r4, 0x14(r3)
    stw r0, 0x1c(r3)
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x44(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x48(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x4c(r1)
    stfs f0, 0x28(r3)
    lfs f0, 0x38(r1)
    stfs f0, 0x2c(r3)
    lfs f0, 0x40(r1)
    stfs f0, 0x34(r3)
    lfs f0, 0x3c(r1)
    stfs f0, 0x30(r3)
    NokoNokoChallenge_Update_L_80129008:
    bl NokoNoko_UpdateAll
    lbz r0, g_raceEnded(r13)
    cmplwi r0, 0x1
    beq NokoNokoChallenge_Update_L_80129240
    bl NokoNoko_CountDefeated
    lwz r5, 0x40(r28)
    mr r31, r3
    li r4, 0x0
    bl Clamp_Int
    mr r6, r3
    lwz r29, 0x2c(r28)
    cmpwi r6, 0x63
    ble NokoNokoChallenge_Update_L_80129040
    li r6, 0x63
    NokoNokoChallenge_Update_L_80129040:
    lis r4, 0x6666
    addi r3, r29, 0x108
    addi r5, r4, 0x6667
    mulhw r0, r5, r6
    srawi r0, r0, 2
    srwi r4, r0, 31
    add r0, r0, r4
    mulli r0, r0, 0xa
    subf r26, r0, r6
    subf r0, r26, r6
    mulhw r0, r5, r0
    srawi r0, r0, 2
    srwi r4, r0, 31
    add r27, r0, r4
    bl fn_80121E10
    addi r3, r29, 0x160
    bl fn_80121E10
    cmpwi r27, 0x0
    li r0, 0x1ecd
    beq NokoNokoChallenge_Update_L_80129094
    addi r0, r27, 0x14ba
    NokoNokoChallenge_Update_L_80129094:
    stw r0, 0x108(r29)
    addi r3, r30, 0x430
    addi r4, r26, 0x14ba
    li r0, 0x1
    stw r4, 0x160(r29)
    lfs f0, 0x18(r3)
    stb r0, 0x118(r29)
    lfs f1, 0x1c(r3)
    stfs f0, 0x11c(r29)
    lfs f0, lbl_806D7058(r2)
    stfs f1, 0x120(r29)
    lfs f1, 0x20(r3)
    stfs f0, 0x124(r29)
    lfs f2, 0x24(r3)
    stb r0, 0x170(r29)
    stfs f1, 0x174(r29)
    stfs f2, 0x178(r29)
    stfs f0, 0x17c(r29)
    lwz r0, 0x40(r28)
    cmpw r31, r0
    blt NokoNokoChallenge_Update_L_80129118
    bl NokoNoko_StopAllAlive
    li r3, 0x1
    li r0, 0x1e
    stb r3, 0x36(r28)
    stw r0, 0x38(r28)
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    li r4, 0x0
    li r0, 0x1
    stw r4, 0x290(r3)
    stb r0, g_raceEnded(r13)
    b NokoNokoChallenge_Update_L_80129240
    NokoNokoChallenge_Update_L_80129118:
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    bl KartDriver_GetKartRootMtx
    mr r29, r3
    addi r3, r1, 0x50
    lfs f0, 0xc(r29)
    addi r4, r1, 0x20
    stfs f0, 0x50(r1)
    lfs f0, 0x1c(r29)
    stfs f0, 0x54(r1)
    lfs f0, 0x2c(r29)
    stfs f0, 0x58(r1)
    bl NokoNoko_FindNearest
    clrlwi. r0, r3, 24
    beq NokoNokoChallenge_Update_L_80129240
    addi r3, r1, 0x20
    addi r4, r1, 0x50
    mr r5, r3
    bl Vec3_Subtract
    addi r3, r1, 0x20
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0x8(r29)
    addi r3, r1, 0x50
    mr r4, r3
    stfs f0, 0x50(r1)
    lfs f0, 0x18(r29)
    stfs f0, 0x54(r1)
    lfs f0, 0x28(r29)
    stfs f0, 0x58(r1)
    bl Vec3_Normalize
    addi r3, r1, 0x20
    addi r4, r1, 0x50
    bl Vec3_Dot
    lfs f0, lbl_806D7098(r2)
    fcmpo cr0, f1, f0
    ble NokoNokoChallenge_Update_L_801291C0
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    lfs f0, lbl_806D7070(r2)
    stfs f0, 0x294(r3)
    b NokoNokoChallenge_Update_L_80129240
    NokoNokoChallenge_Update_L_801291C0:
    lfs f0, lbl_806D709C(r2)
    fcmpo cr0, f1, f0
    ble NokoNokoChallenge_Update_L_80129230
    lfs f0, 0x0(r29)
    addi r3, r1, 0x50
    mr r4, r3
    stfs f0, 0x50(r1)
    lfs f0, 0x10(r29)
    stfs f0, 0x54(r1)
    lfs f0, 0x20(r29)
    stfs f0, 0x58(r1)
    bl Vec3_Normalize
    addi r3, r1, 0x20
    addi r4, r1, 0x50
    bl Vec3_Dot
    lfs f0, lbl_806D7070(r2)
    fcmpo cr0, f1, f0
    ble NokoNokoChallenge_Update_L_8012921C
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    lfs f0, lbl_806D7058(r2)
    stfs f0, 0x294(r3)
    b NokoNokoChallenge_Update_L_80129240
    NokoNokoChallenge_Update_L_8012921C:
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    lfs f0, lbl_806D7054(r2)
    stfs f0, 0x294(r3)
    b NokoNokoChallenge_Update_L_80129240
    NokoNokoChallenge_Update_L_80129230:
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    lfs f0, lbl_806D7070(r2)
    stfs f0, 0x294(r3)
    NokoNokoChallenge_Update_L_80129240:
    lwz r3, 0x44(r28)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    lis r4, lbl_80677C58@ha
    lwz r3, 0x14(r28)
    addi r4, r4, lbl_80677C58@l
    bl CObj_LoadProjMatrix
    lis r4, lbl_80677C64@ha
    lwz r3, 0x14(r28)
    addi r4, r4, lbl_80677C64@l
    bl CObj_ApplyScissor
    bl ItemObjectManager_Update
    lis r3, lbl_80677C64@ha
    lis r4, lbl_80677C58@ha
    addi r5, r3, lbl_80677C64@l
    addi r3, r1, 0x14
    addi r7, r4, lbl_80677C58@l
    lwz r10, 0x0(r5)
    lwz r9, 0x4(r5)
    addi r4, r1, 0x8
    lwz r8, 0x8(r5)
    lwz r6, 0x0(r7)
    lwz r5, 0x4(r7)
    lwz r0, 0x8(r7)
    stw r10, 0x8(r1)
    stw r9, 0xc(r1)
    stw r8, 0x10(r1)
    stw r6, 0x14(r1)
    stw r5, 0x18(r1)
    stw r0, 0x1c(r1)
    bl VfxSlotMgr_Update
    bl IsRaceStarted
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne NokoNokoChallenge_Update_L_80129328
    lbz r0, g_raceEnded(r13)
    cmplwi r0, 0x1
    beq NokoNokoChallenge_Update_L_80129328
    lfs f2, g_raceTimeRemaining(r13)
    lfs f1, lbl_806D7070(r2)
    fcmpo cr0, f2, f1
    cror eq, gt, eq
    bne NokoNokoChallenge_Update_L_80129328
    lfs f0, lbl_806D70A0(r2)
    fsubs f0, f2, f0
    fcmpo cr0, f0, f1
    stfs f0, g_raceTimeRemaining(r13)
    bge NokoNokoChallenge_Update_L_80129328
    stfs f1, g_raceTimeRemaining(r13)
    bl NokoNoko_StopAllAlive
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    li r4, 0x0
    li r0, 0x1
    stw r4, 0x290(r3)
    stb r0, g_raceEnded(r13)
    NokoNokoChallenge_Update_L_80129328:
    lwz r3, 0x28(r28)
    lfs f1, g_raceTimeRemaining(r13)
    bl fn_80253FD8
    lwz r3, 0x8(r28)
    bl CarObject_CalcSpeedRatio
    lfs f0, lbl_806D70A4(r2)
    lwz r3, 0x28(r28)
    fmuls f1, f0, f1
    bl fn_80253EBC
    lwz r3, 0x8(r28)
    bl KartItem_GetCurrentSpeedWithBonus
    lwz r3, 0x28(r28)
    bl fn_80253EC0
    lwz r3, 0x28(r28)
    bl HUD_FrameUpdate
    lwz r27, 0x2c(r28)
    lbz r0, 0x2c0(r27)
    cmplwi r0, 0x0
    beq NokoNokoChallenge_Update_L_801294A0
    lfs f1, 0x2c4(r27)
    lfs f8, lbl_806D7058(r2)
    fcmpo cr0, f1, f8
    cror eq, gt, eq
    beq NokoNokoChallenge_Update_L_801294C0
    lfs f0, lbl_806D706C(r2)
    addi r3, r30, 0x430
    lfs f7, lbl_806D70A8(r2)
    li r0, 0x1
    fadds f2, f1, f0
    lfs f1, 0x430(r30)
    lfs f3, 0x4(r3)
    lfs f0, 0x8(r3)
    stfs f2, 0x2c4(r27)
    lfs f6, 0xc(r3)
    lfs f2, 0x2c4(r27)
    lfs f5, 0x10(r3)
    fmadds f1, f7, f2, f1
    stb r0, 0x10(r27)
    lfs f31, 0x14(r3)
    lfs f4, 0x18(r3)
    stfs f1, 0x14(r27)
    lfs f13, 0x1c(r3)
    stfs f3, 0x18(r27)
    lfs f3, 0x20(r3)
    stfs f8, 0x1c(r27)
    lfs f12, 0x24(r3)
    lfs f1, 0x2c4(r27)
    lfs f2, 0x28(r3)
    fmadds f0, f7, f1, f0
    stb r0, 0x68(r27)
    lfs f11, 0x2c(r3)
    lfs f1, 0x30(r3)
    stfs f0, 0x6c(r27)
    lfs f10, 0x34(r3)
    stfs f6, 0x70(r27)
    lfs f0, 0x38(r3)
    stfs f8, 0x74(r27)
    lfs f9, 0x3c(r3)
    lfs f6, 0x2c4(r27)
    fmadds f5, f7, f6, f5
    stb r0, 0xc0(r27)
    stfs f5, 0xc4(r27)
    stfs f31, 0xc8(r27)
    stfs f8, 0xcc(r27)
    lfs f5, 0x2c4(r27)
    fmadds f4, f7, f5, f4
    stb r0, 0x118(r27)
    stfs f4, 0x11c(r27)
    stfs f13, 0x120(r27)
    stfs f8, 0x124(r27)
    lfs f4, 0x2c4(r27)
    fmadds f3, f7, f4, f3
    stb r0, 0x170(r27)
    stfs f3, 0x174(r27)
    stfs f12, 0x178(r27)
    stfs f8, 0x17c(r27)
    lfs f3, 0x2c4(r27)
    fmadds f2, f7, f3, f2
    stb r0, 0x1c8(r27)
    stfs f2, 0x1cc(r27)
    stfs f11, 0x1d0(r27)
    stfs f8, 0x1d4(r27)
    lfs f2, 0x2c4(r27)
    fmadds f1, f7, f2, f1
    stb r0, 0x220(r27)
    stfs f1, 0x224(r27)
    stfs f10, 0x228(r27)
    stfs f8, 0x22c(r27)
    lfs f1, 0x2c4(r27)
    fmadds f0, f7, f1, f0
    stb r0, 0x278(r27)
    stfs f0, 0x27c(r27)
    stfs f9, 0x280(r27)
    stfs f8, 0x284(r27)
    NokoNokoChallenge_Update_L_801294A0:
    li r26, 0x0
    NokoNokoChallenge_Update_L_801294A4:
    mr r3, r27
    li r4, 0x0
    bl fn_8011FAFC
    addi r26, r26, 0x1
    addi r27, r27, 0x58
    cmpwi r26, 0x8
    blt NokoNokoChallenge_Update_L_801294A4
    NokoNokoChallenge_Update_L_801294C0:
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne NokoNokoChallenge_Update_L_801294D0
    li r3, 0x0
    NokoNokoChallenge_Update_L_801294D0:
    bl TransitionEffect_Tick
    lbz r0, g_raceEnded(r13)
    cmplwi r0, 0x1
    bne NokoNokoChallenge_Update_L_8012963C
    lwz r3, 0x38(r28)
    cmpwi r3, 0x0
    ble NokoNokoChallenge_Update_L_801294F8
    subi r0, r3, 0x1
    stw r0, 0x38(r28)
    b NokoNokoChallenge_Update_L_8012963C
    NokoNokoChallenge_Update_L_801294F8:
    lwz r0, 0x3c(r28)
    cmpwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80129614
    li r26, 0x0
    bl NokoNokoChallenge_GetCoinDivisor
    mr. r29, r3
    beq NokoNokoChallenge_Update_L_8012953C
    bl NokoNoko_CountDefeated
    lwz r0, 0x40(r28)
    mr r26, r3
    cmpw r26, r0
    ble NokoNokoChallenge_Update_L_8012952C
    mr r26, r0
    NokoNokoChallenge_Update_L_8012952C:
    lwz r0, 0x0(r29)
    divw r26, r26, r0
    mr r3, r26
    bl SetCoinCount
    NokoNokoChallenge_Update_L_8012953C:
    lbz r0, 0x36(r28)
    cmplwi r0, 0x0
    beq NokoNokoChallenge_Update_L_8012959C
    bl NokoNoko_CountDefeated
    lwz r5, 0x40(r28)
    li r4, 0x0
    bl Clamp_Int
    mr r29, r3
    mr r3, r28
    li r4, 0x1
    li r5, 0x0
    bl NokoNokoChallenge_CalcResultText
    mr r5, r3
    lwz r3, 0x28(r28)
    mr r6, r29
    li r4, 0x1
    bl fn_80253C74
    lwz r3, 0x2c(r28)
    li r0, 0x1
    stb r0, 0x2c0(r3)
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    bl KartMovement_ResetOnGoal
    b NokoNokoChallenge_Update_L_801295EC
    NokoNokoChallenge_Update_L_8012959C:
    bl NokoNoko_CountDefeated
    lwz r5, 0x40(r28)
    li r4, 0x0
    bl Clamp_Int
    mr r29, r3
    mr r3, r28
    li r4, 0x0
    li r5, 0x0
    bl NokoNokoChallenge_CalcResultText
    mr r5, r3
    lwz r3, 0x28(r28)
    mr r6, r29
    li r4, 0x0
    bl fn_80253C74
    lwz r3, 0x2c(r28)
    li r0, 0x1
    stb r0, 0x2c0(r3)
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    bl KartMovement_ResetOnTimeout
    NokoNokoChallenge_Update_L_801295EC:
    lbz r5, 0x36(r28)
    mr r3, r28
    mr r4, r26
    bl NokoNokoChallenge_SaveResult
    lwz r3, 0x14(r28)
    li r4, 0x1
    bl Object_SetByte10_Return1
    li r0, 0x0
    stb r0, g_lakituStartAnimDone(r13)
    b NokoNokoChallenge_Update_L_80129630
    NokoNokoChallenge_Update_L_80129614:
    lwz r3, 0x28(r28)
    bl fn_80253C40
    clrlwi. r0, r3, 24
    beq NokoNokoChallenge_Update_L_80129630
    mr r3, r28
    bl NokoNokoChallenge_TransitionToResult
    b NokoNokoChallenge_Update_L_80129650
    NokoNokoChallenge_Update_L_80129630:
    lwz r3, 0x3c(r28)
    addi r0, r3, 0x1
    stw r0, 0x3c(r28)
    NokoNokoChallenge_Update_L_8012963C:
    lwz r3, g_weatherSystem(r13)
    cmplwi r3, 0x0
    beq NokoNokoChallenge_Update_L_8012964C
    bl fn_8016B32C
    NokoNokoChallenge_Update_L_8012964C:
    li r3, -0x2
    NokoNokoChallenge_Update_L_80129650:
    psq_l f31, 0x98(r1), 0, 0
    lfd f31, 0x90(r1)
    psq_l f30, 0x88(r1), 0, 0
    lfd f30, 0x80(r1)
    lmw r26, 0x68(r1)
    lwz r0, 0xa4(r1)
    mtlr r0
    addi r1, r1, 0xa0
    blr
}

extern "C" asm void TimeTrial_Destroy(void) { /* 0x80129674 size:0x2C4 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r4
    stw r30, 0x18(r1)
    mr. r30, r3
    stw r29, 0x14(r1)
    beq TimeTrial_Destroy_L_80129918
    lis r3, lbl_8048E338@ha
    addi r0, r3, lbl_8048E338@l
    stw r0, 0x0(r30)
    lwz r3, g_weatherSystem(r13)
    cmplwi r3, 0x0
    beq TimeTrial_Destroy_L_801296C0
    li r4, 0x1
    bl fn_8016C634
    li r0, 0x0
    stw r0, g_weatherSystem(r13)
    TimeTrial_Destroy_L_801296C0:
    li r3, 0x0
    li r4, 0x0
    bl SetActiveCamera
    lwz r3, 0x44(r30)
    cmplwi r3, 0x0
    beq TimeTrial_Destroy_L_801296EC
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    TimeTrial_Destroy_L_801296EC:
    lwz r3, 0x14(r30)
    cmplwi r3, 0x0
    beq TimeTrial_Destroy_L_8012970C
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    TimeTrial_Destroy_L_8012970C:
    lwz r3, 0xc(r30)
    li r4, 0x1
    bl LakituStart_Dtor
    lwz r3, 0x18(r30)
    li r4, 0x1
    bl fn_80124C84
    lwz r3, 0x30(r30)
    cmplwi r3, 0x0
    beq TimeTrial_Destroy_L_80129744
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    TimeTrial_Destroy_L_80129744:
    li r3, 0x0
    bl SetPlayerCarObject
    lwz r3, 0x8(r30)
    cmplwi r3, 0x0
    beq TimeTrial_Destroy_L_8012976C
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    TimeTrial_Destroy_L_8012976C:
    li r0, 0x0
    stw r0, g_raceCamera(r13)
    lwz r3, 0x1c(r30)
    cmplwi r3, 0x0
    beq TimeTrial_Destroy_L_80129798
    beq TimeTrial_Destroy_L_80129798
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    TimeTrial_Destroy_L_80129798:
    lwz r29, 0x20(r30)
    cmplwi r29, 0x0
    beq TimeTrial_Destroy_L_80129814
    beq TimeTrial_Destroy_L_80129814
    lis r3, 0x1
    lhz r4, 0x4(r29)
    subi r0, r3, 0x1
    clrlwi r0, r0, 16
    subf r0, r4, r0
    cntlzw r0, r0
    extrwi. r0, r0, 8, 19
    beq TimeTrial_Destroy_L_801297CC
    b TimeTrial_Destroy_L_801297DC
    TimeTrial_Destroy_L_801297CC:
    subi r3, r4, 0x1
    cntlzw r0, r4
    sth r3, 0x4(r29)
    extrwi r0, r0, 8, 19
    TimeTrial_Destroy_L_801297DC:
    cmpwi r0, 0x0
    beq TimeTrial_Destroy_L_80129814
    cmplwi r29, 0x0
    beq TimeTrial_Destroy_L_80129814
    lwz r4, 0x0(r29)
    mr r3, r29
    lwz r12, 0x30(r4)
    mtctr r12
    bctrl
    lwz r4, 0x0(r29)
    mr r3, r29
    lwz r12, 0x34(r4)
    mtctr r12
    bctrl
    TimeTrial_Destroy_L_80129814:
    lwz r3, 0x10(r30)
    li r4, 0x1
    bl CourseEnvironment_Dtor
    lwz r29, 0x2c(r30)
    cmplwi r29, 0x0
    beq TimeTrial_Destroy_L_80129850
    bl fn_80121210
    lis r4, dtor_80082960@ha
    mr r3, r29
    addi r4, r4, dtor_80082960@l
    li r5, 0x58
    li r6, 0x8
    bl __destroy_arr
    mr r3, r29
    bl MemoryManager_TimedFree
    TimeTrial_Destroy_L_80129850:
    lwz r3, 0x28(r30)
    li r4, 0x1
    bl fn_80254134
    bl fn_80188DA8
    bl ItemObjectManager_Reset
    bl VfxSlotMgr_Shutdown
    bl ClRomTable_PurgeAll
    bl GetRaceContextPtr
    bl RankingTable_Init
    lwz r3, lbl_806D10D0(r13)
    cmplwi r3, 0x0
    beq TimeTrial_Destroy_L_80129894
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    TimeTrial_Destroy_L_80129894:
    li r0, 0x0
    stw r0, lbl_806D10D0(r13)
    bl SceneDrawList_Reset
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    beq TimeTrial_Destroy_L_801298C0
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    TimeTrial_Destroy_L_801298C0:
    li r0, 0x0
    li r3, 0x0
    stw r0, lbl_806D109C(r13)
    bl SetResourceLoadingFlag
    bl clRom_PurgeAll
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    beq TimeTrial_Destroy_L_801298F4
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    TimeTrial_Destroy_L_801298F4:
    li r0, 0x0
    mr r3, r30
    stw r0, lbl_806D10AC(r13)
    li r4, 0x0
    bl dtor_80122FD8
    extsh. r0, r31
    ble TimeTrial_Destroy_L_80129918
    mr r3, r30
    bl MemoryManager_TimedFree
    TimeTrial_Destroy_L_80129918:
    lwz r0, 0x24(r1)
    mr r3, r30
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void NokoNokoChallenge_Init(void) { /* 0x80129938 size:0x738 */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stfd f31, 0x40(r1)
    psq_st f31, 0x48(r1), 0, 0
    stw r31, 0x3c(r1)
    stw r30, 0x38(r1)
    stw r29, 0x34(r1)
    stw r28, 0x30(r1)
    mr r31, r3
    lis r4, lbl_803561E8@ha
    mr r0, r31
    mr r28, r0
    addi r30, r4, lbl_803561E8@l
    bl GameMode_BaseInit
    lis r4, lbl_8048E144@ha
    lis r3, lbl_8048E338@ha
    addi r0, r4, lbl_8048E144@l
    lfs f0, lbl_806D7070(r2)
    stw r0, 0x0(r28)
    addi r0, r3, lbl_8048E338@l
    stfs f0, 0x4(r28)
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
    mr. r28, r3
    beq NokoNokoChallenge_Init_L_801299C8
    bl InputManager_Init
    NokoNokoChallenge_Init_L_801299C8:
    stw r28, 0x10(r31)
    bl GetCourseDataPtr
    bl HSD_LObjLoadDesc
    stw r3, 0x20(r31)
    li r3, 0x2c
    bl Alloc
    mr. r28, r3
    beq NokoNokoChallenge_Init_L_80129A00
    lfs f1, lbl_806D70BC(r2)
    li r4, 0x100
    lfs f2, lbl_806D706C(r2)
    li r5, 0x100
    lwz r6, 0x20(r31)
    bl Camera_Create
    NokoNokoChallenge_Init_L_80129A00:
    stw r28, 0x1c(r31)
    li r3, 0x0
    lwz r4, 0x1c(r31)
    bl SetActiveCamera
    lwz r0, 0x1c(r31)
    li r3, 0x0
    stw r0, g_raceCamera(r13)
    bl ProcessSystemTick
    bl GetRaceContextPtr
    bl RankingTable_Init
    li r0, 0x0
    li r3, 0x0
    stw r0, lbl_806D12BC(r13)
    bl SoundDriver_GetOrCreate
    addi r4, r1, 0x1c
    addi r6, r1, 0x18
    li r3, 0x0
    li r5, 0x0
    bl GetStartPosition
    li r3, 0x118
    bl Alloc
    mr. r29, r3
    beq NokoNokoChallenge_Init_L_80129AA4
    lwz r28, g_characterId(r13)
    bl GetCourseStartYaw
    fmr f31, f1
    bl GetDisplayBufferIndex
    li r0, 0x0
    mr r4, r3
    stw r0, 0x8(r1)
    fmr f3, f31
    mr r3, r29
    mr r5, r28
    lfs f1, 0x1c(r1)
    li r6, 0x0
    lfs f2, 0x18(r1)
    li r7, 0x0
    li r8, 0x1
    li r9, 0x1
    li r10, 0x0
    bl CarObject_Init
    NokoNokoChallenge_Init_L_80129AA4:
    stw r29, 0x8(r31)
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    li r0, 0x1
    stw r0, 0x238(r3)
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    li r0, 0x1
    stb r0, 0x2d0(r3)
    lwz r3, 0x8(r31)
    bl SetPlayerCarObject
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    li r4, 0x6
    bl KartMovement_EquipItem
    li r3, 0x58
    bl Alloc
    mr. r28, r3
    beq NokoNokoChallenge_Init_L_80129B08
    lfs f2, lbl_806D7070(r2)
    addi r4, r30, 0x4c8
    lfs f1, lbl_806D70B0(r2)
    li r5, 0x0
    fmr f3, f2
    bl LakituStart_Init
    NokoNokoChallenge_Init_L_80129B08:
    stw r28, 0xc(r31)
    li r3, 0x3084
    bl Alloc
    mr. r28, r3
    beq NokoNokoChallenge_Init_L_80129B38
    lwz r3, g_characterId(r13)
    li r4, -0x1
    bl GetKartModelNameEntry
    mr r4, r3
    mr r3, r28
    lwz r4, 0x0(r4)
    bl Scene3D_Init
    NokoNokoChallenge_Init_L_80129B38:
    stw r28, 0x14(r31)
    li r3, 0x8
    bl Alloc
    mr. r28, r3
    beq NokoNokoChallenge_Init_L_80129B50
    bl ChallengeGoalCamera_Init
    NokoNokoChallenge_Init_L_80129B50:
    stw r28, 0x18(r31)
    li r3, 0x10
    bl Alloc
    mr. r28, r3
    beq NokoNokoChallenge_Init_L_80129B68
    bl MapWaterEffect_Init
    NokoNokoChallenge_Init_L_80129B68:
    stw r28, 0x30(r31)
    li r3, 0x0
    bl ProcessSystemTick
    lwz r3, 0x14(r31)
    addi r4, r1, 0x14
    addi r5, r1, 0x10
    bl Scene3D_GetCameraPos
    lfs f1, 0x14(r1)
    lfs f0, lbl_806D7050(r2)
    lfs f2, 0x10(r1)
    fadds f1, f1, f0
    stfs f1, 0x14(r1)
    lwz r3, 0x14(r31)
    bl Scene3D_SetupProjection
    li r3, 0x80
    bl Alloc
    mr. r28, r3
    beq NokoNokoChallenge_Init_L_80129BB8
    li r4, 0x0
    bl HUD_Init
    NokoNokoChallenge_Init_L_80129BB8:
    stw r28, 0x28(r31)
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
    stb r0, 0x34(r31)
    stb r0, 0x36(r31)
    stw r0, 0x38(r31)
    stw r0, 0x3c(r31)
    bl MiniGame_GetTimerValue
    xoris r3, r3, 0x8000
    lis r0, 0x4330
    stw r3, 0x24(r1)
    li r3, 0x2
    lfd f1, lbl_806D7060(r2)
    stw r0, 0x20(r1)
    lfd f0, 0x20(r1)
    fsubs f0, f0, f1
    stfs f0, g_raceTimeRemaining(r13)
    bl PreloadEffectResources
    li r3, 0x9
    bl PreloadEffectResources
    li r3, 0xa
    bl PreloadEffectResources
    bl MiniGame_GetCourseData
    li r0, 0xf
    cmplwi r3, 0x0
    stw r0, 0x40(r31)
    lfs f1, lbl_806D7058(r2)
    beq NokoNokoChallenge_Init_L_80129C84
    lfs f1, 0x0(r3)
    lwz r0, 0x4(r3)
    stw r0, 0x40(r31)
    NokoNokoChallenge_Init_L_80129C84:
    bl NokoNoko_Init
    li r3, 0x2c8
    bl Alloc
    mr. r28, r3
    beq NokoNokoChallenge_Init_L_80129E38
    lis r4, ResCtrl_Init@ha
    lis r5, dtor_80082960@ha
    lwz r29, 0x40(r31)
    addi r4, r4, ResCtrl_Init@l
    addi r5, r5, dtor_80082960@l
    li r6, 0x58
    li r7, 0x8
    bl __construct_array
    li r3, 0x14b9
    bl PreloadResource
    li r3, 0x14c4
    bl PreloadResource
    li r3, 0x14ba
    bl PreloadResource
    lis r3, 0x6666
    addi r4, r30, 0x430
    addi r0, r3, 0x6667
    li r3, 0x14b9
    mulhw r0, r0, r29
    stw r3, 0x0(r28)
    li r3, 0x14c7
    lfs f2, lbl_806D7068(r2)
    stw r3, 0x58(r28)
    li r3, 0x14c5
    srawi r5, r0, 2
    stw r3, 0xb0(r28)
    li r6, 0x1ecd
    srawi r0, r0, 2
    srwi r3, r0, 31
    stw r6, 0x108(r28)
    li r7, 0x14ba
    srwi r6, r5, 31
    add r0, r0, r3
    stw r7, 0x160(r28)
    mulli r0, r0, 0xa
    li r3, 0x14c4
    add r5, r5, r6
    stw r3, 0x1b8(r28)
    lfs f0, lbl_806D70C0(r2)
    li r3, 0x1
    addi r6, r5, 0x14ba
    subf r5, r0, r29
    stw r6, 0x210(r28)
    addi r5, r5, 0x14ba
    lfs f3, 0x430(r30)
    li r0, 0x0
    stw r5, 0x268(r28)
    lfs f4, 0x4(r4)
    stfs f2, 0x1e4(r28)
    lfs f1, lbl_806D7058(r2)
    stfs f2, 0x1e8(r28)
    lfs f8, 0x8(r4)
    stfs f0, 0x23c(r28)
    lfs f2, 0xc(r4)
    stfs f0, 0x240(r28)
    lfs f13, 0x10(r4)
    stfs f0, 0x294(r28)
    lfs f7, 0x14(r4)
    stfs f0, 0x298(r28)
    lfs f12, 0x18(r4)
    stb r3, 0x10(r28)
    lfs f6, 0x1c(r4)
    stfs f3, 0x14(r28)
    lfs f11, 0x20(r4)
    stfs f4, 0x18(r28)
    lfs f5, 0x24(r4)
    stfs f1, 0x1c(r28)
    lfs f10, 0x28(r4)
    stb r3, 0x68(r28)
    lfs f4, 0x2c(r4)
    stfs f8, 0x6c(r28)
    lfs f9, 0x30(r4)
    stfs f2, 0x70(r28)
    lfs f3, 0x34(r4)
    stfs f1, 0x74(r28)
    lfs f8, 0x38(r4)
    stb r3, 0xc0(r28)
    lfs f2, 0x3c(r4)
    stfs f13, 0xc4(r28)
    lfs f0, lbl_806D7070(r2)
    stfs f7, 0xc8(r28)
    stfs f1, 0xcc(r28)
    stb r3, 0x118(r28)
    stfs f12, 0x11c(r28)
    stfs f6, 0x120(r28)
    stfs f1, 0x124(r28)
    stb r3, 0x170(r28)
    stfs f11, 0x174(r28)
    stfs f5, 0x178(r28)
    stfs f1, 0x17c(r28)
    stb r3, 0x1c8(r28)
    stfs f10, 0x1cc(r28)
    stfs f4, 0x1d0(r28)
    stfs f1, 0x1d4(r28)
    stb r3, 0x220(r28)
    stfs f9, 0x224(r28)
    stfs f3, 0x228(r28)
    stfs f1, 0x22c(r28)
    stb r3, 0x278(r28)
    stfs f8, 0x27c(r28)
    stfs f2, 0x280(r28)
    stfs f1, 0x284(r28)
    stb r0, 0x2c0(r28)
    stfs f0, 0x2c4(r28)
    NokoNokoChallenge_Init_L_80129E38:
    stw r28, 0x2c(r31)
    li r3, 0x8a0
    bl Alloc
    mr. r28, r3
    beq NokoNokoChallenge_Init_L_8012A010
    lis r3, lbl_8048E34C@ha
    li r4, 0x0
    addi r0, r3, lbl_8048E34C@l
    stw r0, 0x0(r28)
    li r0, 0x5
    li r3, 0x5c
    stw r4, 0xc(r28)
    stw r4, 0x10(r28)
    stw r0, 0x89c(r28)
    bl Alloc
    mr. r29, r3
    beq NokoNokoChallenge_Init_L_80129E88
    addi r4, r30, 0x4dc
    li r5, 0x1
    bl clNormal3D_Construct
    NokoNokoChallenge_Init_L_80129E88:
    stw r29, 0x4(r28)
    lis r4, 0x4000
    li r5, 0x0
    lwz r3, 0x4(r28)
    bl clNormal3D_SetFlags
    li r3, 0x5c
    bl Alloc
    mr. r29, r3
    beq NokoNokoChallenge_Init_L_80129EB8
    addi r4, r30, 0x4ec
    li r5, 0x1
    bl clNormal3D_Construct
    NokoNokoChallenge_Init_L_80129EB8:
    stw r29, 0x8(r28)
    lwz r3, 0x8(r28)
    bl Archive_GetRootJObj
    li r4, 0x200
    bl HSD_JObjSetFlags
    li r0, 0x6
    lfs f0, lbl_806D7070(r2)
    li r11, 0x0
    mtctr r0
    NokoNokoChallenge_Init_L_80129EDC:
    addi r0, r11, 0x14
    li r8, 0x0
    stwx r8, r28, r0
    addi r0, r11, 0x1c
    addi r9, r11, 0x20
    addi r10, r11, 0x2c
    stwx r8, r28, r0
    addi r4, r11, 0x38
    addi r3, r11, 0x3c
    addi r0, r11, 0x18
    stfsx f0, r28, r4
    add r9, r28, r9
    add r10, r28, r10
    addi r6, r28, 0x40
    stfsx f0, r28, r3
    li r7, -0x1
    addi r5, r28, 0x50
    addi r4, r28, 0x60
    stwx r8, r28, r0
    addi r3, r28, 0x70
    addi r0, r28, 0x80
    stfs f0, 0x8(r9)
    stfs f0, 0x4(r9)
    stfs f0, 0x0(r9)
    stfs f0, 0x8(r10)
    stfs f0, 0x4(r10)
    stfs f0, 0x0(r10)
    stwx r7, r11, r6
    addi r6, r28, 0x90
    stwx r7, r11, r5
    addi r5, r28, 0xa0
    stwx r7, r11, r4
    addi r4, r28, 0xb0
    stwx r7, r11, r3
    addi r3, r28, 0xc0
    stwx r7, r11, r0
    addi r0, r28, 0xd0
    stwx r7, r11, r6
    addi r6, r28, 0xe0
    stwx r7, r11, r5
    addi r5, r28, 0xf0
    stwx r7, r11, r4
    addi r4, r28, 0x100
    stwx r7, r11, r3
    addi r3, r28, 0x110
    stwx r7, r11, r0
    addi r0, r28, 0x120
    stwx r7, r11, r6
    addi r6, r28, 0x130
    stwx r7, r11, r5
    addi r5, r28, 0x140
    stwx r7, r11, r4
    addi r4, r28, 0x150
    stwx r7, r11, r3
    addi r3, r28, 0x160
    stwx r7, r11, r0
    addi r0, r28, 0x170
    stwx r7, r11, r6
    stwx r7, r11, r5
    stwx r7, r11, r4
    stwx r7, r11, r3
    stwx r7, r11, r0
    addi r11, r11, 0x16c
    bdnz NokoNokoChallenge_Init_L_80129EDC
    lwz r0, 0x89c(r28)
    cmpwi r0, 0x14
    blt NokoNokoChallenge_Init_L_80129FF0
    li r0, 0x13
    stw r0, 0x89c(r28)
    NokoNokoChallenge_Init_L_80129FF0:
    lis r3, lbl_8048E36C@ha
    lfs f1, lbl_806D70C4(r2)
    addi r0, r3, lbl_8048E36C@l
    stw r0, 0x0(r28)
    fmr f2, f1
    fmr f3, f1
    lwz r3, 0x4(r28)
    bl Object_SetJObjScaleXYZ
    NokoNokoChallenge_Init_L_8012A010:
    stw r28, 0x44(r31)
    lwz r0, g_weatherSystem(r13)
    cmplwi r0, 0x0
    bne NokoNokoChallenge_Init_L_8012A03C
    li r3, 0x1b4
    bl Alloc
    mr. r28, r3
    beq NokoNokoChallenge_Init_L_8012A038
    li r4, 0x1
    bl WeatherSystem_Init
    NokoNokoChallenge_Init_L_8012A038:
    stw r28, g_weatherSystem(r13)
    NokoNokoChallenge_Init_L_8012A03C:
    li r3, 0x1
    bl SetResourceLoadingFlag
    mr r3, r31
    psq_l f31, 0x48(r1), 0, 0
    lwz r0, 0x54(r1)
    lfd f31, 0x40(r1)
    lwz r31, 0x3c(r1)
    lwz r30, 0x38(r1)
    lwz r29, 0x34(r1)
    lwz r28, 0x30(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}

extern "C" void fn_8012A070(ShotOwner *self)
{
    for (int i = 0; i < 6; i++) {
        if (((ShotSet *)self)->shots[i].active) {
            Object_SetJObjPositionVec(self->model, &((ShotSet *)self)->shots[i].pos);
            Object_SetJObjRotationY(self->model, lbl_806D704C * ((ShotSet *)self)->shots[i].rot);
            Object_SetColorAlphaOnly(self->model, 0, ((ShotSet *)self)->shots[i].alpha);
            Object_RenderJObjEx(self->model, LinkedNode_GetField10_OrFallback(self->model, 0), 7);
            LNode *n = LinkedNode_GetField10_OrFallback(self->model, 0);
            Object_RenderJObjEx(self->model, n == 0 ? 0 : n->f8, 7);
            for (int j = 0; j < self->trailCount; j++) {
                float f = ((ShotSet *)self)->shots[i].trail[j].age / lbl_806D7050;
                float sc = lbl_806D7054 - f;
                Object_SetJObjPositionVec(self->trailModel, &((ShotSet *)self)->shots[i].trail[j].pos);
                Object_SetJObjScaleXYZ(self->trailModel, sc, sc, sc);
                Object_SetColorAlphaOnly(self->trailModel, 0, (lbl_806D7058 - f) * ((ShotSet *)self)->shots[i].alpha);
                Object_RenderJObjTree(self->trailModel, 7);
            }
        }
    }
}

extern "C" asm void fn_8012A22C(void) { /* 0x8012A22C size:0x300 */
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    stfd f31, 0x50(r1)
    psq_st f31, 0x58(r1), 0, 0
    stfd f30, 0x40(r1)
    psq_st f30, 0x48(r1), 0, 0
    stmw r24, 0x20(r1)
    mr r26, r3
    li r27, 0x0
    mr r30, r26
    fn_8012A22C_L_8012A258:
    lwz r0, 0x14(r30)
    cmpwi r0, 0x0
    beq fn_8012A22C_L_8012A4F8
    lfs f1, 0x20(r30)
    addi r28, r30, 0x40
    lfs f0, 0x2c(r30)
    addi r3, r30, 0x20
    lfs f2, lbl_806D706C(r2)
    addi r4, r1, 0x8
    fadds f3, f1, f0
    lfs f0, lbl_806D7070(r2)
    lfs f1, lbl_806D7050(r2)
    li r5, 0x0
    li r6, 0x0
    stfs f3, 0x20(r30)
    lfs f4, 0x24(r30)
    lfs f3, 0x30(r30)
    fadds f3, f4, f3
    stfs f3, 0x24(r30)
    lfs f4, 0x28(r30)
    lfs f3, 0x34(r30)
    fadds f3, f4, f3
    stfs f3, 0x28(r30)
    lfs f3, 0x30(r30)
    fsubs f2, f3, f2
    stfs f2, 0x30(r30)
    stfs f0, 0x8(r1)
    bl Terrain_GetGroundHeightWithPenetration
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne fn_8012A22C_L_8012A2F8
    lfs f1, 0x24(r30)
    lfs f0, 0x8(r1)
    fcmpo cr0, f1, f0
    bge fn_8012A22C_L_8012A2F8
    lfs f0, 0x30(r30)
    lfs f1, lbl_806D70AC(r2)
    fneg f0, f0
    fmuls f0, f1, f0
    stfs f0, 0x30(r30)
    fn_8012A22C_L_8012A2F8:
    lfs f2, 0x38(r30)
    lfs f1, lbl_806D70B0(r2)
    lfs f0, lbl_806D70B4(r2)
    fadds f1, f2, f1
    stfs f1, 0x38(r30)
    lfs f1, 0x38(r30)
    fcmpo cr0, f1, f0
    ble fn_8012A22C_L_8012A320
    fsubs f0, f1, f0
    stfs f0, 0x38(r30)
    fn_8012A22C_L_8012A320:
    lwz r3, 0x1c(r30)
    lis r0, 0x4330
    stw r0, 0x10(r1)
    mr r5, r28
    xoris r0, r3, 0x8000
    lfd f2, lbl_806D7060(r2)
    stw r0, 0x14(r1)
    li r6, 0x0
    lfs f0, lbl_806D70B8(r2)
    li r3, -0x1
    lfd f1, 0x10(r1)
    lfs f3, lbl_806D7058(r2)
    fsubs f2, f1, f2
    lfs f1, lbl_806D7054(r2)
    fdivs f0, f2, f0
    fsubs f0, f3, f0
    stfs f0, 0x3c(r30)
    b fn_8012A22C_L_8012A3A0
    fn_8012A22C_L_8012A368:
    lwz r0, 0x0(r5)
    cmpwi r0, 0x0
    blt fn_8012A22C_L_8012A398
    lfs f0, 0x8(r5)
    fsubs f0, f0, f1
    stfs f0, 0x8(r5)
    lwz r4, 0x0(r5)
    addi r0, r4, 0x1
    cmpwi r0, 0xa
    stw r0, 0x0(r5)
    ble fn_8012A22C_L_8012A398
    stw r3, 0x0(r5)
    fn_8012A22C_L_8012A398:
    addi r5, r5, 0x10
    addi r6, r6, 0x1
    fn_8012A22C_L_8012A3A0:
    lwz r0, 0x89c(r26)
    cmpw r6, r0
    blt fn_8012A22C_L_8012A368
    lwz r0, 0x1c(r30)
    clrlwi. r0, r0, 30
    bne fn_8012A22C_L_8012A4DC
    lis r4, lbl_80495A94@ha
    lis r3, lbl_80495994@ha
    mr r31, r28
    li r29, 0x0
    addi r24, r4, lbl_80495A94@l
    addi r25, r3, lbl_80495994@l
    b fn_8012A22C_L_8012A498
    fn_8012A22C_L_8012A3D4:
    lwz r4, 0x10(r26)
    lwz r3, 0xc(r26)
    lwz r0, 0x0(r31)
    slwi r4, r4, 2
    slwi r3, r3, 2
    lfsx f31, r24, r4
    cmpwi r0, 0x0
    lfsx f1, r25, r3
    blt fn_8012A22C_L_8012A400
    li r0, 0x0
    b fn_8012A22C_L_8012A448
    fn_8012A22C_L_8012A400:
    lfs f0, lbl_806D70B4(r2)
    li r0, 0x0
    stw r0, 0x0(r31)
    fmuls f30, f0, f1
    fmr f1, f30
    bl LUT_Sin12Bit
    lfs f2, lbl_806D70B0(r2)
    lfs f0, lbl_806D7050(r2)
    fmuls f2, f2, f1
    fmuls f0, f0, f31
    fmr f1, f30
    stfs f2, 0x4(r31)
    stfs f0, 0x8(r31)
    bl fn_80186960
    lfs f0, lbl_806D70B0(r2)
    li r0, 0x1
    fmuls f0, f0, f1
    stfs f0, 0xc(r31)
    fn_8012A22C_L_8012A448:
    clrlwi r0, r0, 24
    cmplwi r0, 0x1
    bne fn_8012A22C_L_8012A490
    slwi r0, r29, 4
    lfs f0, 0x20(r30)
    add r3, r28, r0
    lfs f1, 0x4(r3)
    fadds f0, f1, f0
    stfs f0, 0x4(r3)
    lfs f1, 0x8(r3)
    lfs f0, 0x24(r30)
    fadds f0, f1, f0
    stfs f0, 0x8(r3)
    lfs f1, 0xc(r3)
    lfs f0, 0x28(r30)
    fadds f0, f1, f0
    stfs f0, 0xc(r3)
    b fn_8012A22C_L_8012A4A4
    fn_8012A22C_L_8012A490:
    addi r31, r31, 0x10
    addi r29, r29, 0x1
    fn_8012A22C_L_8012A498:
    lwz r0, 0x89c(r26)
    cmpw r29, r0
    blt fn_8012A22C_L_8012A3D4
    fn_8012A22C_L_8012A4A4:
    lwz r3, 0xc(r26)
    addi r0, r3, 0x1
    cmpwi r0, 0x40
    stw r0, 0xc(r26)
    blt fn_8012A22C_L_8012A4C0
    li r0, 0x0
    stw r0, 0xc(r26)
    fn_8012A22C_L_8012A4C0:
    lwz r3, 0x10(r26)
    addi r0, r3, 0x1
    cmpwi r0, 0x30
    stw r0, 0x10(r26)
    blt fn_8012A22C_L_8012A4DC
    li r0, 0x0
    stw r0, 0x10(r26)
    fn_8012A22C_L_8012A4DC:
    lwz r3, 0x1c(r30)
    addi r0, r3, 0x1
    cmpwi r0, 0x5a
    stw r0, 0x1c(r30)
    blt fn_8012A22C_L_8012A4F8
    li r0, 0x0
    stw r0, 0x14(r30)
    fn_8012A22C_L_8012A4F8:
    addi r27, r27, 0x1
    addi r30, r30, 0x16c
    cmpwi r27, 0x6
    blt fn_8012A22C_L_8012A258
    psq_l f31, 0x58(r1), 0, 0
    lfd f31, 0x50(r1)
    psq_l f30, 0x48(r1), 0, 0
    lfd f30, 0x40(r1)
    lmw r24, 0x20(r1)
    lwz r0, 0x64(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
}

extern "C" ModelPair *fn_8012A52C(ModelPair *self, short flag)
{
    if (self) {
        self->vt = lbl_8048E36C;
        if (self) {
            self->vt = lbl_8048E34C;
            Object_DtorWithGXSync(self->a, 1);
            Object_DtorWithGXSync(self->b, 1);
        }
        if (flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}

