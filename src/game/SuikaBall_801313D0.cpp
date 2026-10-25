
/* sdata symbols referenced from asm */
extern unsigned char lbl_806D7280[7];
extern unsigned char lbl_806D7288[5];
/*
 * 0x801313D0..0x801341E4: Suika ball minigame.
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
extern void GXBegin();
extern void GXClearVtxDesc();
extern void GXLoadPosMtxImm();
extern void GXSetBlendMode();
extern void GXSetChanCtrl();
extern void GXSetCullMode();
extern void GXSetCurrentMtx();
extern void GXSetNumChans();
extern void GXSetNumTevStages();
extern void GXSetNumTexGens();
extern void GXSetTevOp();
extern void GXSetTevOrder();
extern void GXSetVtxAttrFmt();
extern void GXSetVtxDesc();
extern void GXSetZMode();
extern void HSD_CObjGetCurrent();
extern void HSD_CObjGetViewingMtxPtr();
extern void HSD_JObjSetMtxDirtySub();
extern void HSD_StateInvalidate();
extern void IsCardValid();
extern void ItemObjectManager_Render();
extern void KartItem_RenderPipelinedWithEffects();
void Object_RenderJObjEx(void *o, void *node, int mask);
extern void Object_RenderJObjIfWithinRange();
extern void Subsystem36c_DispatchPass2_Timed();
extern void Subsystem36c_DispatchPass4_Timed();
extern void SuikaBallObj_Render();
extern void TransitionEffect_RenderPass();
extern void TransparentDraw_SortAndDispatch();
extern void __assert();
extern void clDrawMan_Buckets_Dispatch();
extern void clDrawMan_Buckets_Reset();
extern void clDrawMan_EndFrame_NoOp();
extern void fn_8016B0C4();
extern void fn_80253448();
extern void fn_802535D4();
extern unsigned int lbl_806D109C;
extern unsigned int lbl_806D10AC;
extern unsigned int lbl_806D7290;
extern unsigned int lbl_806D7294;
extern unsigned int lbl_806DC190;
extern unsigned int lbl_806DC1B0;
extern unsigned int lbl_806DC1B8;
extern unsigned int lbl_803579F4[];
extern void CObj_ApplyScissor();
extern void CObj_LoadProjMatrix();
extern void CarObject_ApplyInput();
extern void CarObject_CalcSpeedRatio();
extern void CarObject_FrameUpdate();
extern void CarObject_GetRenderObj();
extern void ChallengeGoalCamera_Update();
extern void CourseEnvironment_UpdateAndCullZones_Timed();
extern void DebugPrintf();
extern void Fog_UpdateFromCourseScene3D();
extern void GetInputManager();
extern void GetRaceContextPtr();
extern void HUD_FrameUpdate();
extern void InputMgr_GetPlayer();
extern void IsRaceStarted();
extern void ItemObjectManager_PerFrameUpdate();
extern void ItemObjectManager_Update();
extern void KartDriver_GetKartRootMtx();
extern void KartItem_GetCurrentSpeedWithBonus();
extern void KartItem_UpdateShadowBillboardAndViewport();
extern void KartMovement_ResetOnGoal();
extern void KartMovement_ResetOnTimeout();
extern void KartMovement_SetSpeedScale();
extern void KartReaction_Rear();
extern void LUT_Cosine();
extern void LUT_Sine();
extern void LakituStart_UpdateCountdown();
extern void NokoNokoChallenge_CalcResultText();
extern void NokoNokoChallenge_HandleBrakeInput();
extern void NokoNokoChallenge_SaveResult();
extern void NokoNokoChallenge_TransitionToResult();
extern void Object_SetByte10_Return1();
extern void SetCoinCount();
extern void SoundMgr_Play();
extern void SoundMgr_PlaySE();
extern void SuikaBallObj_UpdatePhysics();
extern void TransitionEffect_Tick();
extern void Vec3_Dot();
extern void Vec3_Subtract();
extern void VfxSlotMgr_Update();
extern void atan2();
extern void clNormal3D_Exec();
extern void fn_8016B32C();
extern void fn_8016C360();
extern void fn_8016C394();
extern void fn_80192688();
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
extern const float lbl_806D72A4;
extern unsigned int lbl_806D72B0;
extern unsigned int lbl_806D72B4;
extern unsigned int lbl_806D72B8;
extern unsigned int lbl_806D72BC;
extern unsigned int lbl_806D72C0;
extern unsigned int lbl_806D72C4;
extern unsigned int lbl_806D72C8;
extern unsigned int lbl_806D72CC;
extern unsigned int lbl_806D72D0;
extern unsigned int lbl_806D72D4;
extern unsigned int lbl_806D72D8;
extern unsigned int lbl_806D72DC;
extern unsigned int lbl_806D72E0;
extern unsigned int lbl_806D72E4;
extern unsigned int lbl_806D72E8;
extern unsigned int lbl_80357A6C[];
extern unsigned int lbl_80357A88[];
extern unsigned int lbl_80677C70[];
extern unsigned int lbl_80677C7C[];
extern void ClRomTable_PurgeAll();
extern void CourseEnvironment_Dtor();
extern void ItemObjectManager_Reset();
extern void LakituStart_Dtor();
void MemoryManager_Free(void *p);
void MemoryManager_TimedFree(void *p);
void Object_DtorWithGXSync(void *o, int flag);
extern void RankingTable_Init();
extern void SceneDrawList_Reset();
extern void SetActiveCamera();
extern void SetPlayerCarObject();
extern void SetResourceLoadingFlag();
extern void VfxSlotMgr_Shutdown();
extern void clRom_PurgeAll();
extern void dtor_80122FD8();
extern void fn_8012491C();
extern void fn_80124C84();
extern void fn_8016C634();
extern void fn_80254134();
extern unsigned int g_raceCamera;
extern unsigned int lbl_806D10D0;
extern unsigned int lbl_8048E3F8[];
extern void Alloc();
extern void Archive_GetRootJObj();
extern void Camera_Create();
extern void CarObject_Init();
extern void CarObject_SetPosition();
extern void ChallengeGoalCamera_Init();
extern void CourseObjectManager_Init();
extern void DMAChannelManager_Init();
extern void DrawManager_GetOrCreate();
extern void FUN_8003b120();
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
extern void LakituStart_Init();
extern void MiniGame_GetCourseData();
extern void MiniGame_GetTimerValue();
extern void PreloadEffectResources();
extern void ProcessSystemTick();
extern void ResolveJointByName();
extern void Scene3D_GetCameraPos();
extern void Scene3D_Init();
extern void Scene3D_SetupProjection();
extern void SceneRender_CmdB_8aa20();
extern void SetCourseScene3D();
extern void SoundChannels_ClearAll();
extern void SoundDriver_GetOrCreate();
extern void SuikaBallObj_Init();
extern void TransitionEffect_GetOrCreate();
extern void Vec3_Normalize();
extern void WeatherSystem_Init();
extern void clNormal3D_Construct();
extern void clNormal3D_SetFlags();
extern void clNormal3D_SetScale();
extern void fn_8018F614();
extern void fn_8018FEAC();
extern unsigned int g_characterId;
extern unsigned int lbl_806D12BC;
extern const float lbl_806D729C;
extern unsigned int lbl_806D72A8;
extern unsigned int lbl_806D72F8;
extern unsigned int lbl_806D72FC;
extern unsigned int lbl_806D7300;
extern unsigned int lbl_806D7304;
extern unsigned int lbl_806D7308;
extern unsigned int lbl_806D730C;
extern unsigned int lbl_806D7310;
extern unsigned int lbl_806D7314;
extern unsigned int lbl_80357008[];
extern unsigned int lbl_8048E144[];
extern void *lbl_8048E34C[];
extern void *lbl_8048E418[];
struct LNode *LinkedNode_GetField10_OrFallback(void *o, int idx);
void Object_RenderJObjTree(void *o, int mask);
void Object_SetColorAlphaOnly(void *o, int idx, float a);
void Object_SetJObjPositionVec(void *o, struct Vec3 *v);
void Object_SetJObjRotationY(void *o, float r);
void Object_SetJObjScaleXYZ(void *o, float x, float y, float z);
extern const float lbl_806D7298;
extern const float lbl_806D72A0;
extern void LUT_Sin12Bit();
extern void Terrain_GetGroundHeightWithPenetration();
extern void fn_80186960();
extern unsigned int lbl_806D72EC;
extern unsigned int lbl_806D72F0;
extern unsigned int lbl_806D72F4;
extern unsigned int lbl_80495994[];
extern unsigned int lbl_80495A94[];
asm void SuikaBall_Render(void);
asm void SuikaBall_Update(void);
asm void fn_80133008(void);
asm void SuikaBall_Init(void);
void fn_80133CA8(ShotOwner *self);
asm void fn_80133E64(void);
ModelPair *fn_80134164(ModelPair *self, short flag);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_SuikaBall_Render[8] = {
    0x41, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_SuikaBall_Update[8] = {
    0x20, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_80133008[8] = {
    0x28, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; unsigned int f29; unsigned int f30; unsigned int f31; unsigned int f32; unsigned int f33; unsigned int f34; unsigned int f35; unsigned int f36; unsigned int f37; unsigned int f38; unsigned int f39; unsigned int f40; unsigned int f41; unsigned int f42; unsigned int f43; unsigned int f44; unsigned int f45; unsigned int f46; unsigned int f47; unsigned int f48; unsigned int f49; unsigned int f50; unsigned int f51; unsigned int f52; unsigned int f53; unsigned int f54; unsigned int f55; unsigned int f56; unsigned int f57; unsigned int f58; unsigned int f59; unsigned int f60; unsigned int f61; unsigned int f62; unsigned int f63; unsigned int f64; unsigned int f65; unsigned int f66; unsigned int f67; unsigned int f68; unsigned int f69; unsigned int f70; unsigned int f71; unsigned int f72; unsigned int f73; unsigned int f74; unsigned int f75; unsigned int f76; unsigned int f77; unsigned int f78; void *f79; unsigned int f80; unsigned int f81; void *f82; unsigned int f83; void *f84; unsigned int f85; unsigned int f86; void *f87; unsigned int f88; void *f89; unsigned int f90; unsigned int f91; void *f92; unsigned int f93; void *f94; unsigned int f95; unsigned int f96; void *f97; unsigned int f98; void *f99; unsigned int f100; unsigned int f101; void *f102; unsigned int f103; void *f104; unsigned int f105; unsigned int f106; void *f107; unsigned int f108; void *f109; unsigned int f110; unsigned int f111; void *f112; unsigned int f113; void *f114; unsigned int f115; unsigned int f116; void *f117; unsigned int f118; void *f119; unsigned int f120; unsigned int f121; void *f122; unsigned int f123; void *f124; unsigned int f125; unsigned int f126; void *f127; unsigned int f128; void *f129; unsigned int f130; unsigned int f131; void *f132; unsigned int f133; void *f134; unsigned int f135; unsigned int f136; void *f137; unsigned int f138; void *f139; unsigned int f140; unsigned int f141; void *f142; unsigned int f143; void *f144; unsigned int f145; void *f146; unsigned int f147; unsigned int f148; void *f149; unsigned int f150; void *f151; unsigned int f152; unsigned int f153; void *f154; unsigned int f155; void *f156; unsigned int f157; unsigned int f158; void *f159; unsigned int f160; void *f161; unsigned int f162; unsigned int f163; void *f164; } extab_SuikaBall_Init = { 0x504A0000, 0x00000054, 0x000B0140, 0x0000008C, 0x00000138, 0x00000094, 0x00040140, 0x000000C4, 0x0000014C, 0x000000D4, 0x00110140, 0x00000128, 0x00100160, 0x00000178, 0x00080140, 0x000001B8, 0x00000174, 0x000001C4, 0x00000140, 0x000001D8, 0x00040188, 0x000001F4, 0x00000140, 0x00000200, 0x0000019C, 0x0000020C, 0x000D0140, 0x00000250, 0x000001B0, 0x00000264, 0x002F0140, 0x00000330, 0x000001C4, 0x00000378, 0x00150140, 0x000003D8, 0x000001D8, 0x000003E4, 0x00000140, 0x000003F0, 0x000001EC, 0x000003FC, 0x00000140, 0x000004A0, 0x00030200, 0x000004D4, 0x00080140, 0x00000508, 0x00000214, 0x00000528, 0x00020140, 0x00000544, 0x00000228, 0x00000564, 0x00290140, 0x00000638, 0x00000244, 0x0000064C, 0x0000023C, 0x00000660, 0x00020244, 0x0000067C, 0x00000258, 0x00000688, 0x00020244, 0x000007DC, 0x00000140, 0x000007FC, 0x0000026C, 0x00000874, 0x00030264, 0x000008D4, 0x00000140, 0x000008E4, 0x00000280, 0x000008F0, 0x00000140, 0x00000000, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x01000244, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A800016, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8 };


__declspec(section ".extab_user") static const unsigned char extab_fn_80133E64[8] = {
    0x40, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SuikaBall_Render = {
    (void *)&SuikaBall_Render, 0x0000060C, (void *)extab_SuikaBall_Render
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SuikaBall_Update = {
    (void *)&SuikaBall_Update, 0x0000162C, (void *)extab_SuikaBall_Update
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80133008 = {
    (void *)&fn_80133008, 0x00000390, (void *)extab_fn_80133008
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SuikaBall_Init = {
    (void *)&SuikaBall_Init, 0x00000910, (void *)&extab_SuikaBall_Init
};


__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80133E64 = {
    (void *)&fn_80133E64, 0x00000300, (void *)extab_fn_80133E64
};


}





extern "C" asm void SuikaBall_Render(void) { /* 0x801313D0 size:0x60C */
    nofralloc
    stwu r1, -0x70(r1)
    mflr r0
    stw r0, 0x74(r1)
    stfd f31, 0x60(r1)
    psq_st f31, 0x68(r1), 0, 0
    stfd f30, 0x50(r1)
    psq_st f30, 0x58(r1), 0, 0
    stfd f29, 0x40(r1)
    psq_st f29, 0x48(r1), 0, 0
    stfd f28, 0x30(r1)
    psq_st f28, 0x38(r1), 0, 0
    stmw r24, 0x10(r1)
    mr r26, r3
    lbz r0, 0x30(r3)
    cmplwi r0, 0x0
    beq SuikaBall_Render_L_801319A8
    lwz r3, 0x18(r26)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne SuikaBall_Render_L_80131974
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne SuikaBall_Render_L_80131440
    li r3, 0x0
    SuikaBall_Render_L_80131440:
    bl clDrawMan_Buckets_Reset
    bl TransparentDraw_SortAndDispatch
    lwz r3, 0x18(r26)
    bl CObj_DebugVizPathFlush
    bl fn_8016B0C4
    lwz r3, 0xc(r26)
    li r4, 0x0
    bl KartItem_RenderPipelinedWithEffects
    lwz r3, 0x10(r26)
    bl Object_RenderJObjIfWithinRange
    lwz r3, 0x14(r26)
    bl CourseEnvironment_RenderObjects_Timed
    lwz r3, 0x14(r26)
    bl Subsystem36c_DispatchPass2_Timed
    bl ItemObjectManager_Render
    lwz r3, 0x3c(r26)
    bl SuikaBallObj_Render
    lwz r3, 0x44(r26)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lwz r3, 0x48(r26)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    li r29, 0x0
    li r30, 0x0
    SuikaBall_Render_L_801314B4:
    lwz r0, 0x5c(r26)
    li r27, 0x0
    li r31, 0x0
    add r28, r0, r30
    b SuikaBall_Render_L_80131708
    SuikaBall_Render_L_801314C8:
    lwz r3, 0xc(r28)
    lwzx r24, r3, r31
    cmplwi r24, 0x0
    beq SuikaBall_Render_L_80131700
    lwz r3, 0x8(r28)
    lwzx r0, r3, r31
    cmplwi r0, 0x0
    beq SuikaBall_Render_L_80131700
    cmplwi r24, 0x0
    bne SuikaBall_Render_L_80131500
    la r3, lbl_806D7280(r2)  /* lbl_806D7280 */
    li r4, 0x3e4
    la r5, lbl_806D7288(r2)  /* lbl_806D7288 */
    bl __assert
    SuikaBall_Render_L_80131500:
    lwz r3, 0x8(r28)
    lfs f30, 0x38(r24)
    lwzx r25, r3, r31
    lfs f31, 0x3c(r24)
    cmplwi r25, 0x0
    lfs f29, 0x40(r24)
    bne SuikaBall_Render_L_8013152C
    la r3, lbl_806D7280(r2)  /* lbl_806D7280 */
    li r4, 0x3a9
    la r5, lbl_806D7288(r2)  /* lbl_806D7288 */
    bl __assert
    SuikaBall_Render_L_8013152C:
    stfs f30, 0x38(r25)
    stfs f31, 0x3c(r25)
    stfs f29, 0x40(r25)
    lwz r0, 0x14(r25)
    rlwinm. r0, r0, 0, 6, 6
    bne SuikaBall_Render_L_8013158C
    cmplwi r25, 0x0
    beq SuikaBall_Render_L_8013158C
    bne SuikaBall_Render_L_80131560
    la r3, lbl_806D7280(r2)  /* lbl_806D7280 */
    li r4, 0x25d
    la r5, lbl_806D7288(r2)  /* lbl_806D7288 */
    bl __assert
    SuikaBall_Render_L_80131560:
    lwz r4, 0x14(r25)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne SuikaBall_Render_L_8013157C
    rlwinm. r0, r4, 0, 25, 25
    beq SuikaBall_Render_L_8013157C
    li r3, 0x1
    SuikaBall_Render_L_8013157C:
    clrlwi. r0, r3, 24
    bne SuikaBall_Render_L_8013158C
    mr r3, r25
    bl HSD_JObjSetMtxDirtySub
    SuikaBall_Render_L_8013158C:
    lwz r3, 0xc(r28)
    lwzx r25, r3, r31
    cmplwi r25, 0x0
    bne SuikaBall_Render_L_801315AC
    la r3, lbl_806D7280(r2)  /* lbl_806D7280 */
    li r4, 0x2dd
    la r5, lbl_806D7288(r2)  /* lbl_806D7288 */
    bl __assert
    SuikaBall_Render_L_801315AC:
    lwz r3, 0x8(r28)
    lfs f29, 0x1c(r25)
    lwzx r24, r3, r31
    lfs f30, 0x20(r25)
    cmplwi r24, 0x0
    lfs f31, 0x24(r25)
    lfs f28, 0x28(r25)
    bne SuikaBall_Render_L_801315DC
    la r3, lbl_806D7280(r2)  /* lbl_806D7280 */
    li r4, 0x290
    la r5, lbl_806D7288(r2)  /* lbl_806D7288 */
    bl __assert
    SuikaBall_Render_L_801315DC:
    stfs f29, 0x1c(r24)
    stfs f30, 0x20(r24)
    stfs f31, 0x24(r24)
    stfs f28, 0x28(r24)
    lwz r0, 0x14(r24)
    rlwinm. r0, r0, 0, 6, 6
    bne SuikaBall_Render_L_80131640
    cmplwi r24, 0x0
    beq SuikaBall_Render_L_80131640
    bne SuikaBall_Render_L_80131614
    la r3, lbl_806D7280(r2)  /* lbl_806D7280 */
    li r4, 0x25d
    la r5, lbl_806D7288(r2)  /* lbl_806D7288 */
    bl __assert
    SuikaBall_Render_L_80131614:
    lwz r4, 0x14(r24)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne SuikaBall_Render_L_80131630
    rlwinm. r0, r4, 0, 25, 25
    beq SuikaBall_Render_L_80131630
    li r3, 0x1
    SuikaBall_Render_L_80131630:
    clrlwi. r0, r3, 24
    bne SuikaBall_Render_L_80131640
    mr r3, r24
    bl HSD_JObjSetMtxDirtySub
    SuikaBall_Render_L_80131640:
    lwz r3, 0xc(r28)
    lwzx r24, r3, r31
    cmplwi r24, 0x0
    bne SuikaBall_Render_L_80131660
    la r3, lbl_806D7280(r2)  /* lbl_806D7280 */
    li r4, 0x351
    la r5, lbl_806D7288(r2)  /* lbl_806D7288 */
    bl __assert
    SuikaBall_Render_L_80131660:
    lwz r3, 0x8(r28)
    lfs f28, 0x2c(r24)
    lwzx r25, r3, r31
    lfs f29, 0x30(r24)
    cmplwi r25, 0x0
    lfs f30, 0x34(r24)
    bne SuikaBall_Render_L_8013168C
    la r3, lbl_806D7280(r2)  /* lbl_806D7280 */
    li r4, 0x316
    la r5, lbl_806D7288(r2)  /* lbl_806D7288 */
    bl __assert
    SuikaBall_Render_L_8013168C:
    stfs f28, 0x2c(r25)
    stfs f29, 0x30(r25)
    stfs f30, 0x34(r25)
    lwz r0, 0x14(r25)
    rlwinm. r0, r0, 0, 6, 6
    bne SuikaBall_Render_L_801316EC
    cmplwi r25, 0x0
    beq SuikaBall_Render_L_801316EC
    bne SuikaBall_Render_L_801316C0
    la r3, lbl_806D7280(r2)  /* lbl_806D7280 */
    li r4, 0x25d
    la r5, lbl_806D7288(r2)  /* lbl_806D7288 */
    bl __assert
    SuikaBall_Render_L_801316C0:
    lwz r4, 0x14(r25)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne SuikaBall_Render_L_801316DC
    rlwinm. r0, r4, 0, 25, 25
    beq SuikaBall_Render_L_801316DC
    li r3, 0x1
    SuikaBall_Render_L_801316DC:
    clrlwi. r0, r3, 24
    bne SuikaBall_Render_L_801316EC
    mr r3, r25
    bl HSD_JObjSetMtxDirtySub
    SuikaBall_Render_L_801316EC:
    lwz r4, 0x8(r28)
    li r5, 0x7
    lwz r3, 0x0(r28)
    lwzx r4, r4, r31
    bl Object_RenderJObjEx
    SuikaBall_Render_L_80131700:
    addi r31, r31, 0x4
    addi r27, r27, 0x1
    SuikaBall_Render_L_80131708:
    lwz r0, 0x10(r28)
    cmpw r27, r0
    blt SuikaBall_Render_L_801314C8
    addi r29, r29, 0x1
    addi r30, r30, 0x14
    cmplwi r29, 0x3
    blt SuikaBall_Render_L_801314B4
    lwz r3, 0x2c(r26)
    lwz r4, lbl_806DC190(r2)
    bl fn_80253448
    bl DrawEffect_TickAndCull
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq SuikaBall_Render_L_801318D8
    bl GXClearVtxDesc
    li r3, 0x9
    li r4, 0x1
    bl GXSetVtxDesc
    li r3, 0x0
    li r4, 0x9
    li r5, 0x1
    li r6, 0x4
    li r7, 0x0
    bl GXSetVtxAttrFmt
    li r3, 0xb
    li r4, 0x1
    bl GXSetVtxDesc
    li r3, 0x0
    li r4, 0xb
    li r5, 0x1
    li r6, 0x5
    li r7, 0x0
    bl GXSetVtxAttrFmt
    li r3, 0x1
    bl GXSetNumChans
    li r3, 0x4
    li r4, 0x0
    li r5, 0x1
    li r6, 0x1
    li r7, 0x0
    li r8, 0x0
    li r9, 0x2
    bl GXSetChanCtrl
    li r3, 0x0
    bl GXSetNumTexGens
    li r3, 0x1
    bl GXSetNumTevStages
    li r3, 0x0
    li r4, 0xff
    li r5, 0xff
    li r6, 0x4
    bl GXSetTevOrder
    li r3, 0x0
    li r4, 0x4
    bl GXSetTevOp
    li r3, 0x1
    li r4, 0x3
    li r5, 0x1
    bl GXSetZMode
    li r3, 0x1
    li r4, 0x4
    li r5, 0x5
    li r6, 0x0
    bl GXSetBlendMode
    bl HSD_CObjGetCurrent
    mr. r24, r3
    beq SuikaBall_Render_L_80131834
    li r3, 0x0
    bl GXSetCurrentMtx
    mr r3, r24
    bl HSD_CObjGetViewingMtxPtr
    li r4, 0x0
    bl GXLoadPosMtxImm
    li r3, 0x0
    bl GXSetCullMode
    SuikaBall_Render_L_80131834:
    lis r3, 0xe020
    lis r4, lbl_803579F4@ha
    lfs f30, lbl_806D7290(r2)
    addi r25, r4, lbl_803579F4@l
    lfs f31, lbl_806D7294(r2)
    addi r28, r3, 0x2000
    addi r27, r3, 0x2080
    li r24, 0x0
    lis r29, 0xcc01
    SuikaBall_Render_L_80131858:
    li r3, 0x80
    li r4, 0x0
    li r5, 0x4
    bl GXBegin
    lfs f3, 0xc(r25)
    addi r24, r24, 0x1
    lfs f2, 0x14(r25)
    cmpwi r24, 0x4
    stfs f3, -0x8000(r29)
    lfs f1, 0x0(r25)
    stfs f30, -0x8000(r29)
    lfs f0, 0x8(r25)
    addi r25, r25, 0x18
    stfs f2, -0x8000(r29)
    stw r28, -0x8000(r29)
    stfs f1, -0x8000(r29)
    stfs f30, -0x8000(r29)
    stfs f0, -0x8000(r29)
    stw r28, -0x8000(r29)
    stfs f1, -0x8000(r29)
    stfs f31, -0x8000(r29)
    stfs f0, -0x8000(r29)
    stw r27, -0x8000(r29)
    stfs f3, -0x8000(r29)
    stfs f31, -0x8000(r29)
    stfs f2, -0x8000(r29)
    stw r27, -0x8000(r29)
    blt SuikaBall_Render_L_80131858
    li r3, 0x2
    bl GXSetCullMode
    li r3, 0x7e
    bl HSD_StateInvalidate
    SuikaBall_Render_L_801318D8:
    lwz r3, 0x60(r26)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne SuikaBall_Render_L_801318FC
    li r3, 0x0
    SuikaBall_Render_L_801318FC:
    bl clDrawMan_EndFrame_NoOp
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne SuikaBall_Render_L_80131910
    li r3, 0x0
    SuikaBall_Render_L_80131910:
    bl clDrawMan_Buckets_Dispatch
    lwz r3, 0x14(r26)
    bl Subsystem36c_DispatchPass4_Timed
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne SuikaBall_Render_L_8013192C
    li r3, 0x0
    SuikaBall_Render_L_8013192C:
    li r4, 0x2
    bl TransitionEffect_RenderPass
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne SuikaBall_Render_L_80131944
    li r3, 0x0
    SuikaBall_Render_L_80131944:
    li r4, 0x4
    bl TransitionEffect_RenderPass
    lwz r4, lbl_806DC1B0(r2)
    lwz r0, lbl_806DC190(r2)
    lwz r3, 0x2c(r26)
    or r4, r4, r0
    bl fn_80253448
    lwz r3, 0x18(r26)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    SuikaBall_Render_L_80131974:
    lwz r3, 0x2c(r26)
    lwz r4, lbl_806DC1B8(r2)
    bl fn_80253448
    lwz r3, 0x2c(r26)
    bl fn_802535D4
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne SuikaBall_Render_L_80131998
    li r3, 0x0
    SuikaBall_Render_L_80131998:
    li r4, 0x1
    bl TransitionEffect_RenderPass
    li r3, 0x7f
    bl HSD_StateInvalidate
    SuikaBall_Render_L_801319A8:
    psq_l f31, 0x68(r1), 0, 0
    lfd f31, 0x60(r1)
    psq_l f30, 0x58(r1), 0, 0
    lfd f30, 0x50(r1)
    psq_l f29, 0x48(r1), 0, 0
    lfd f29, 0x40(r1)
    psq_l f28, 0x38(r1), 0, 0
    lfd f28, 0x30(r1)
    lmw r24, 0x10(r1)
    lwz r0, 0x74(r1)
    mtlr r0
    addi r1, r1, 0x70
    blr
}

extern "C" asm void SuikaBall_Update(void) { /* 0x801319DC size:0x162C */
    nofralloc
    stwu r1, -0x90(r1)
    mflr r0
    stw r0, 0x94(r1)
    stfd f31, 0x80(r1)
    psq_st f31, 0x88(r1), 0, 0
    stfd f30, 0x70(r1)
    psq_st f30, 0x78(r1), 0, 0
    stfd f29, 0x60(r1)
    psq_st f29, 0x68(r1), 0, 0
    stw r31, 0x5c(r1)
    stw r30, 0x58(r1)
    stw r29, 0x54(r1)
    stw r28, 0x50(r1)
    mr r31, r3
    lbz r0, 0x30(r3)
    cmplwi r0, 0x0
    bne SuikaBall_Update_L_80131A28
    li r0, 0x1
    stb r0, 0x30(r31)
    SuikaBall_Update_L_80131A28:
    bl IsRaceStarted
    clrlwi. r0, r3, 24
    bne SuikaBall_Update_L_80131A5C
    lbz r0, 0x31(r31)
    cmplwi r0, 0x0
    bne SuikaBall_Update_L_80131A88
    li r3, 0x24
    bl SoundMgr_Play
    li r3, 0xd5
    bl SoundMgr_Play
    li r0, 0x1
    stb r0, 0x31(r31)
    b SuikaBall_Update_L_80131A88
    SuikaBall_Update_L_80131A5C:
    lbz r0, 0x31(r31)
    cmplwi r0, 0x1
    bne SuikaBall_Update_L_80131A88
    li r3, 0x24
    li r4, 0x1
    bl fn_80192688
    li r3, 0xd5
    li r4, 0x1
    bl fn_80192688
    li r0, 0x0
    stb r0, 0x31(r31)
    SuikaBall_Update_L_80131A88:
    bl GetRaceContextPtr
    bl ItemObjectManager_PerFrameUpdate
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lbz r0, g_raceEnded(r13)
    mr r29, r3
    cmplwi r0, 0x1
    beq SuikaBall_Update_L_80131B90
    lwz r0, 0x34(r31)
    cmpwi r0, 0x0
    blt SuikaBall_Update_L_80131B90
    lbz r0, lbl_806D1290(r13)
    cmplwi r0, 0x0
    bne SuikaBall_Update_L_80131ADC
    lwz r12, 0x0(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    fmr f30, f1
    b SuikaBall_Update_L_80131AE0
    SuikaBall_Update_L_80131ADC:
    lfs f30, lbl_806D72B0(r2)
    SuikaBall_Update_L_80131AE0:
    mr r3, r29
    fmr f29, f30
    lwz r12, 0x0(r29)
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl
    lfs f0, lbl_806D72B4(r2)
    li r30, 0x0
    fcmpo cr0, f30, f0
    fmr f30, f1
    bge SuikaBall_Update_L_80131B24
    fcmpo cr0, f30, f0
    bge SuikaBall_Update_L_80131B24
    bl IsRaceStarted
    clrlwi. r0, r3, 24
    beq SuikaBall_Update_L_80131B24
    li r30, 0x1
    SuikaBall_Update_L_80131B24:
    mr r3, r31
    mr r4, r30
    bl NokoNokoChallenge_HandleBrakeInput
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne SuikaBall_Update_L_80131B40
    lfs f29, lbl_806D72A4(r2)
    SuikaBall_Update_L_80131B40:
    bl IsRaceStarted
    mr r30, r3
    mr r3, r29
    lwz r12, 0x0(r29)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    fmr f2, f29
    lwz r3, 0xc(r31)
    fmr f3, f30
    mr r4, r30
    bl CarObject_ApplyInput
    lwz r3, 0xc(r31)
    li r4, 0x0
    bl CarObject_FrameUpdate
    lwz r3, 0xc(r31)
    li r5, 0x0
    lwz r4, 0x18(r31)
    bl KartItem_UpdateShadowBillboardAndViewport
    b SuikaBall_Update_L_80131C2C
    SuikaBall_Update_L_80131B90:
    lwz r0, 0x34(r31)
    cmpwi r0, 0x0
    bge SuikaBall_Update_L_80131BE0
    lfs f1, lbl_806D72B8(r2)
    li r4, 0x1
    lwz r3, 0xc(r31)
    fmr f2, f1
    fmr f3, f1
    bl CarObject_ApplyInput
    lwz r3, 0xc(r31)
    lfs f1, lbl_806D72BC(r2)
    bl KartMovement_SetSpeedScale
    lwz r3, 0xc(r31)
    li r4, 0x0
    bl CarObject_FrameUpdate
    lwz r3, 0xc(r31)
    li r5, 0x0
    lwz r4, 0x18(r31)
    bl KartItem_UpdateShadowBillboardAndViewport
    b SuikaBall_Update_L_80131C2C
    SuikaBall_Update_L_80131BE0:
    lfs f1, lbl_806D72B8(r2)
    li r4, 0x1
    lwz r3, 0xc(r31)
    fmr f2, f1
    fmr f3, f1
    bl CarObject_ApplyInput
    lwz r3, 0xc(r31)
    lfs f1, lbl_806D72BC(r2)
    bl KartMovement_SetSpeedScale
    lwz r3, 0xc(r31)
    li r4, 0x0
    bl CarObject_FrameUpdate
    lwz r3, 0xc(r31)
    bl CarObject_GetRenderObj
    bl KartDriver_GetKartRootMtx
    mr r5, r3
    lwz r3, 0x1c(r31)
    lwz r4, 0x18(r31)
    bl ChallengeGoalCamera_Update
    SuikaBall_Update_L_80131C2C:
    bl Fog_UpdateFromCourseScene3D
    lwz r3, 0x10(r31)
    bl LakituStart_UpdateCountdown
    lwz r3, 0x14(r31)
    bl CourseEnvironment_UpdateAndCullZones_Timed
    lwz r3, 0xc(r31)
    bl CarObject_GetRenderObj
    bl KartDriver_GetKartRootMtx
    mr r0, r3
    addi r3, r1, 0x38
    mr r29, r0
    addi r4, r31, 0x50
    lfs f0, 0xc(r29)
    addi r5, r1, 0x44
    stfs f0, 0x38(r1)
    lfs f0, 0x1c(r29)
    stfs f0, 0x3c(r1)
    lfs f0, 0x2c(r29)
    stfs f0, 0x40(r1)
    bl Vec3_Subtract
    lfs f0, 0x38(r1)
    mr r4, r29
    lfs f1, lbl_806D72C0(r2)
    addi r5, r1, 0x44
    stfs f0, 0x50(r31)
    lfs f0, 0x3c(r1)
    stfs f0, 0x54(r31)
    lfs f0, 0x40(r1)
    stfs f0, 0x58(r31)
    lwz r3, 0x3c(r31)
    bl SuikaBallObj_UpdatePhysics
    lwz r3, 0x3c(r31)
    lbz r0, 0x60(r3)
    cmplwi r0, 0x0
    beq SuikaBall_Update_L_80131CD8
    lwz r3, 0xc(r31)
    bl CarObject_GetRenderObj
    bl KartReaction_Rear
    li r3, 0x5d
    bl SoundMgr_PlaySE
    lfs f0, lbl_806D72C4(r2)
    stfs f0, 0x4c(r31)
    b SuikaBall_Update_L_80131CFC
    SuikaBall_Update_L_80131CD8:
    lfs f2, 0x4c(r31)
    lfs f1, lbl_806D72C8(r2)
    lfs f0, lbl_806D72A4(r2)
    fadds f1, f2, f1
    stfs f1, 0x4c(r31)
    lfs f1, 0x4c(r31)
    fcmpo cr0, f1, f0
    ble SuikaBall_Update_L_80131CFC
    stfs f0, 0x4c(r31)
    SuikaBall_Update_L_80131CFC:
    lwz r3, 0xc(r31)
    lfs f1, 0x4c(r31)
    bl KartMovement_SetSpeedScale
    lwz r3, 0x44(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    lwz r3, 0x48(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    lbz r0, 0x32(r31)
    cmplwi r0, 0x0
    bne SuikaBall_Update_L_80132D60
    lwz r3, 0xc(r31)
    bl CarObject_GetRenderObj
    bl KartDriver_GetKartRootMtx
    lwz r4, 0x3c(r31)
    addi r5, r1, 0x14
    lfs f31, 0xc(r3)
    lfs f30, 0x2c(r3)
    addi r3, r1, 0x38
    lfs f0, 0x38(r4)
    stfs f0, 0x38(r1)
    lfs f0, 0x3c(r4)
    stfs f0, 0x3c(r1)
    lfs f0, 0x40(r4)
    stfs f0, 0x40(r1)
    lwz r30, 0x40(r31)
    mr r4, r30
    bl Vec3_Subtract
    addi r3, r1, 0x14
    addi r4, r30, 0x24
    bl Vec3_Dot
    lfs f0, lbl_806D72B8(r2)
    fcmpo cr0, f1, f0
    ble SuikaBall_Update_L_80132488
    lwz r3, 0x3c(r31)
    li r4, 0x1
    li r0, -0x32
    stb r4, 0x61(r3)
    stb r4, 0x33(r31)
    stb r4, 0x32(r31)
    stw r0, 0x34(r31)
    lwz r3, 0x68(r31)
    addi r0, r3, 0x5
    stw r0, 0x68(r31)
    lwz r29, 0x60(r31)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq SuikaBall_Update_L_80131F18
    lis r3, lbl_80357A6C@ha
    lis r4, lbl_80357A88@ha
    addi r3, r3, lbl_80357A6C@l
    li r5, 0x2d8
    addi r4, r4, lbl_80357A88@l
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne SuikaBall_Update_L_80131E08
    li r3, 0xab
    bl fn_8016C394
    SuikaBall_Update_L_80131E08:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r29)
    li r30, 0x0
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80131E28
    li r30, 0x0
    b SuikaBall_Update_L_80131E88
    SuikaBall_Update_L_80131E28:
    lwz r0, 0x180(r29)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80131E3C
    li r30, 0x1
    b SuikaBall_Update_L_80131E88
    SuikaBall_Update_L_80131E3C:
    lwz r0, 0x2ec(r29)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80131E50
    li r30, 0x2
    b SuikaBall_Update_L_80131E88
    SuikaBall_Update_L_80131E50:
    lwz r0, 0x458(r29)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80131E64
    li r30, 0x3
    b SuikaBall_Update_L_80131E88
    SuikaBall_Update_L_80131E64:
    lwz r0, 0x5c4(r29)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80131E78
    li r30, 0x4
    b SuikaBall_Update_L_80131E88
    SuikaBall_Update_L_80131E78:
    lwz r0, 0x730(r29)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80131E88
    li r30, 0x5
    SuikaBall_Update_L_80131E88:
    lfs f1, 0x38(r1)
    lfs f0, 0x40(r1)
    fsubs f1, f31, f1
    fsubs f2, f30, f0
    bl atan2
    mulli r30, r30, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D72B8(r2)
    frsp f1, f1
    add r3, r29, r30
    stw r4, 0x14(r3)
    fadds f29, f1, f0
    stw r0, 0x1c(r3)
    stfs f0, 0x3c(r3)
    fmr f1, f29
    stfs f0, 0x38(r3)
    lfs f0, 0x38(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x3c(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x40(r1)
    stfs f0, 0x28(r3)
    bl LUT_Cosine
    lfs f0, lbl_806D72CC(r2)
    add r3, r29, r30
    fmuls f0, f0, f1
    fmr f1, f29
    stfs f0, 0x2c(r3)
    bl LUT_Sine
    lfs f2, lbl_806D72CC(r2)
    add r3, r29, r30
    lfs f0, lbl_806D72D0(r2)
    fmuls f1, f2, f1
    stfs f1, 0x34(r3)
    stfs f0, 0x30(r3)
    SuikaBall_Update_L_80131F18:
    lwz r30, 0x60(r31)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq SuikaBall_Update_L_80132074
    lis r3, lbl_80357A6C@ha
    lis r4, lbl_80357A88@ha
    addi r3, r3, lbl_80357A6C@l
    li r5, 0x2d8
    addi r4, r4, lbl_80357A88@l
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne SuikaBall_Update_L_80131F60
    li r3, 0xab
    bl fn_8016C394
    SuikaBall_Update_L_80131F60:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r30)
    li r29, 0x0
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80131F80
    li r29, 0x0
    b SuikaBall_Update_L_80131FE0
    SuikaBall_Update_L_80131F80:
    lwz r0, 0x180(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80131F94
    li r29, 0x1
    b SuikaBall_Update_L_80131FE0
    SuikaBall_Update_L_80131F94:
    lwz r0, 0x2ec(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80131FA8
    li r29, 0x2
    b SuikaBall_Update_L_80131FE0
    SuikaBall_Update_L_80131FA8:
    lwz r0, 0x458(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80131FBC
    li r29, 0x3
    b SuikaBall_Update_L_80131FE0
    SuikaBall_Update_L_80131FBC:
    lwz r0, 0x5c4(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80131FD0
    li r29, 0x4
    b SuikaBall_Update_L_80131FE0
    SuikaBall_Update_L_80131FD0:
    lwz r0, 0x730(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80131FE0
    li r29, 0x5
    SuikaBall_Update_L_80131FE0:
    lfs f1, 0x38(r1)
    lfs f0, 0x40(r1)
    fsubs f1, f31, f1
    fsubs f2, f30, f0
    bl atan2
    mulli r29, r29, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D72B8(r2)
    frsp f2, f1
    lfs f1, lbl_806D72D4(r2)
    add r3, r30, r29
    stw r4, 0x14(r3)
    fadds f29, f2, f1
    stw r0, 0x1c(r3)
    fmr f1, f29
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x38(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x3c(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x40(r1)
    stfs f0, 0x28(r3)
    bl LUT_Cosine
    lfs f0, lbl_806D72CC(r2)
    add r3, r30, r29
    fmuls f0, f0, f1
    fmr f1, f29
    stfs f0, 0x2c(r3)
    bl LUT_Sine
    lfs f2, lbl_806D72CC(r2)
    add r3, r30, r29
    lfs f0, lbl_806D72D0(r2)
    fmuls f1, f2, f1
    stfs f1, 0x34(r3)
    stfs f0, 0x30(r3)
    SuikaBall_Update_L_80132074:
    lwz r30, 0x60(r31)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq SuikaBall_Update_L_801321D0
    lis r3, lbl_80357A6C@ha
    lis r4, lbl_80357A88@ha
    addi r3, r3, lbl_80357A6C@l
    li r5, 0x2d8
    addi r4, r4, lbl_80357A88@l
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne SuikaBall_Update_L_801320BC
    li r3, 0xab
    bl fn_8016C394
    SuikaBall_Update_L_801320BC:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r30)
    li r29, 0x0
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_801320DC
    li r29, 0x0
    b SuikaBall_Update_L_8013213C
    SuikaBall_Update_L_801320DC:
    lwz r0, 0x180(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_801320F0
    li r29, 0x1
    b SuikaBall_Update_L_8013213C
    SuikaBall_Update_L_801320F0:
    lwz r0, 0x2ec(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132104
    li r29, 0x2
    b SuikaBall_Update_L_8013213C
    SuikaBall_Update_L_80132104:
    lwz r0, 0x458(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132118
    li r29, 0x3
    b SuikaBall_Update_L_8013213C
    SuikaBall_Update_L_80132118:
    lwz r0, 0x5c4(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_8013212C
    li r29, 0x4
    b SuikaBall_Update_L_8013213C
    SuikaBall_Update_L_8013212C:
    lwz r0, 0x730(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_8013213C
    li r29, 0x5
    SuikaBall_Update_L_8013213C:
    lfs f1, 0x38(r1)
    lfs f0, 0x40(r1)
    fsubs f1, f31, f1
    fsubs f2, f30, f0
    bl atan2
    mulli r29, r29, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D72B8(r2)
    frsp f2, f1
    lfs f1, lbl_806D72D8(r2)
    add r3, r30, r29
    stw r4, 0x14(r3)
    fadds f29, f2, f1
    stw r0, 0x1c(r3)
    fmr f1, f29
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x38(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x3c(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x40(r1)
    stfs f0, 0x28(r3)
    bl LUT_Cosine
    lfs f0, lbl_806D72CC(r2)
    add r3, r30, r29
    fmuls f0, f0, f1
    fmr f1, f29
    stfs f0, 0x2c(r3)
    bl LUT_Sine
    lfs f2, lbl_806D72CC(r2)
    add r3, r30, r29
    lfs f0, lbl_806D72D0(r2)
    fmuls f1, f2, f1
    stfs f1, 0x34(r3)
    stfs f0, 0x30(r3)
    SuikaBall_Update_L_801321D0:
    lwz r30, 0x60(r31)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq SuikaBall_Update_L_8013232C
    lis r3, lbl_80357A6C@ha
    lis r4, lbl_80357A88@ha
    addi r3, r3, lbl_80357A6C@l
    li r5, 0x2d8
    addi r4, r4, lbl_80357A88@l
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne SuikaBall_Update_L_80132218
    li r3, 0xab
    bl fn_8016C394
    SuikaBall_Update_L_80132218:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r30)
    li r29, 0x0
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132238
    li r29, 0x0
    b SuikaBall_Update_L_80132298
    SuikaBall_Update_L_80132238:
    lwz r0, 0x180(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_8013224C
    li r29, 0x1
    b SuikaBall_Update_L_80132298
    SuikaBall_Update_L_8013224C:
    lwz r0, 0x2ec(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132260
    li r29, 0x2
    b SuikaBall_Update_L_80132298
    SuikaBall_Update_L_80132260:
    lwz r0, 0x458(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132274
    li r29, 0x3
    b SuikaBall_Update_L_80132298
    SuikaBall_Update_L_80132274:
    lwz r0, 0x5c4(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132288
    li r29, 0x4
    b SuikaBall_Update_L_80132298
    SuikaBall_Update_L_80132288:
    lwz r0, 0x730(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132298
    li r29, 0x5
    SuikaBall_Update_L_80132298:
    lfs f1, 0x38(r1)
    lfs f0, 0x40(r1)
    fsubs f1, f31, f1
    fsubs f2, f30, f0
    bl atan2
    mulli r29, r29, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D72B8(r2)
    frsp f2, f1
    lfs f1, lbl_806D72DC(r2)
    add r3, r30, r29
    stw r4, 0x14(r3)
    fadds f29, f2, f1
    stw r0, 0x1c(r3)
    fmr f1, f29
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x38(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x3c(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x40(r1)
    stfs f0, 0x28(r3)
    bl LUT_Cosine
    lfs f0, lbl_806D72CC(r2)
    add r3, r30, r29
    fmuls f0, f0, f1
    fmr f1, f29
    stfs f0, 0x2c(r3)
    bl LUT_Sine
    lfs f2, lbl_806D72CC(r2)
    add r3, r30, r29
    lfs f0, lbl_806D72D0(r2)
    fmuls f1, f2, f1
    stfs f1, 0x34(r3)
    stfs f0, 0x30(r3)
    SuikaBall_Update_L_8013232C:
    lwz r30, 0x60(r31)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq SuikaBall_Update_L_80132488
    lis r3, lbl_80357A6C@ha
    lis r4, lbl_80357A88@ha
    addi r3, r3, lbl_80357A6C@l
    li r5, 0x2d8
    addi r4, r4, lbl_80357A88@l
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne SuikaBall_Update_L_80132374
    li r3, 0xab
    bl fn_8016C394
    SuikaBall_Update_L_80132374:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r30)
    li r29, 0x0
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132394
    li r29, 0x0
    b SuikaBall_Update_L_801323F4
    SuikaBall_Update_L_80132394:
    lwz r0, 0x180(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_801323A8
    li r29, 0x1
    b SuikaBall_Update_L_801323F4
    SuikaBall_Update_L_801323A8:
    lwz r0, 0x2ec(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_801323BC
    li r29, 0x2
    b SuikaBall_Update_L_801323F4
    SuikaBall_Update_L_801323BC:
    lwz r0, 0x458(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_801323D0
    li r29, 0x3
    b SuikaBall_Update_L_801323F4
    SuikaBall_Update_L_801323D0:
    lwz r0, 0x5c4(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_801323E4
    li r29, 0x4
    b SuikaBall_Update_L_801323F4
    SuikaBall_Update_L_801323E4:
    lwz r0, 0x730(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_801323F4
    li r29, 0x5
    SuikaBall_Update_L_801323F4:
    lfs f1, 0x38(r1)
    lfs f0, 0x40(r1)
    fsubs f1, f31, f1
    fsubs f2, f30, f0
    bl atan2
    mulli r29, r29, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D72B8(r2)
    frsp f2, f1
    lfs f1, lbl_806D72E0(r2)
    add r3, r30, r29
    stw r4, 0x14(r3)
    fadds f29, f2, f1
    stw r0, 0x1c(r3)
    fmr f1, f29
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x38(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x3c(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x40(r1)
    stfs f0, 0x28(r3)
    bl LUT_Cosine
    lfs f0, lbl_806D72CC(r2)
    add r3, r30, r29
    fmuls f0, f0, f1
    fmr f1, f29
    stfs f0, 0x2c(r3)
    bl LUT_Sine
    lfs f2, lbl_806D72CC(r2)
    add r3, r30, r29
    lfs f0, lbl_806D72D0(r2)
    fmuls f1, f2, f1
    stfs f1, 0x34(r3)
    stfs f0, 0x30(r3)
    SuikaBall_Update_L_80132488:
    lwz r29, 0x64(r31)
    lwz r0, 0x10(r29)
    cmpwi r0, 0x4
    blt SuikaBall_Update_L_801324A0
    li r4, 0x0
    b SuikaBall_Update_L_80132500
    SuikaBall_Update_L_801324A0:
    slwi r0, r0, 2
    addi r3, r1, 0x38
    lwzx r30, r29, r0
    addi r5, r1, 0x8
    mr r4, r30
    bl Vec3_Subtract
    addi r3, r1, 0x8
    addi r4, r30, 0x24
    bl Vec3_Dot
    lfs f0, lbl_806D72B8(r2)
    fcmpo cr0, f1, f0
    ble SuikaBall_Update_L_801324D8
    li r0, 0x1
    b SuikaBall_Update_L_801324DC
    SuikaBall_Update_L_801324D8:
    li r0, 0x0
    SuikaBall_Update_L_801324DC:
    clrlwi r0, r0, 24
    cmplwi r0, 0x1
    bne SuikaBall_Update_L_801324FC
    lwz r3, 0x10(r29)
    li r4, 0x1
    addi r0, r3, 0x1
    stw r0, 0x10(r29)
    b SuikaBall_Update_L_80132500
    SuikaBall_Update_L_801324FC:
    li r4, 0x0
    SuikaBall_Update_L_80132500:
    clrlwi r0, r4, 24
    cmplwi r0, 0x1
    bne SuikaBall_Update_L_80132D60
    lwz r3, 0x64(r31)
    lwz r0, 0x10(r3)
    cmpwi r0, 0x3
    bgt SuikaBall_Update_L_801327E4
    lwz r30, 0x60(r31)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq SuikaBall_Update_L_80132678
    lis r3, lbl_80357A6C@ha
    lis r4, lbl_80357A88@ha
    addi r3, r3, lbl_80357A6C@l
    li r5, 0x2d8
    addi r4, r4, lbl_80357A88@l
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne SuikaBall_Update_L_80132564
    li r3, 0xab
    bl fn_8016C394
    SuikaBall_Update_L_80132564:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r30)
    li r29, 0x0
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132584
    li r29, 0x0
    b SuikaBall_Update_L_801325E4
    SuikaBall_Update_L_80132584:
    lwz r0, 0x180(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132598
    li r29, 0x1
    b SuikaBall_Update_L_801325E4
    SuikaBall_Update_L_80132598:
    lwz r0, 0x2ec(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_801325AC
    li r29, 0x2
    b SuikaBall_Update_L_801325E4
    SuikaBall_Update_L_801325AC:
    lwz r0, 0x458(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_801325C0
    li r29, 0x3
    b SuikaBall_Update_L_801325E4
    SuikaBall_Update_L_801325C0:
    lwz r0, 0x5c4(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_801325D4
    li r29, 0x4
    b SuikaBall_Update_L_801325E4
    SuikaBall_Update_L_801325D4:
    lwz r0, 0x730(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_801325E4
    li r29, 0x5
    SuikaBall_Update_L_801325E4:
    lfs f1, 0x38(r1)
    lfs f0, 0x40(r1)
    fsubs f1, f31, f1
    fsubs f2, f30, f0
    bl atan2
    mulli r29, r29, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D72B8(r2)
    frsp f2, f1
    lfs f1, lbl_806D72D4(r2)
    add r3, r30, r29
    stw r4, 0x14(r3)
    fadds f29, f2, f1
    stw r0, 0x1c(r3)
    fmr f1, f29
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x38(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x3c(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x40(r1)
    stfs f0, 0x28(r3)
    bl LUT_Cosine
    lfs f0, lbl_806D72CC(r2)
    add r3, r30, r29
    fmuls f0, f0, f1
    fmr f1, f29
    stfs f0, 0x2c(r3)
    bl LUT_Sine
    lfs f2, lbl_806D72CC(r2)
    add r3, r30, r29
    lfs f0, lbl_806D72D0(r2)
    fmuls f1, f2, f1
    stfs f1, 0x34(r3)
    stfs f0, 0x30(r3)
    SuikaBall_Update_L_80132678:
    lwz r30, 0x60(r31)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq SuikaBall_Update_L_801327D4
    lis r3, lbl_80357A6C@ha
    lis r4, lbl_80357A88@ha
    addi r3, r3, lbl_80357A6C@l
    li r5, 0x2d8
    addi r4, r4, lbl_80357A88@l
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne SuikaBall_Update_L_801326C0
    li r3, 0xab
    bl fn_8016C394
    SuikaBall_Update_L_801326C0:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r30)
    li r29, 0x0
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_801326E0
    li r29, 0x0
    b SuikaBall_Update_L_80132740
    SuikaBall_Update_L_801326E0:
    lwz r0, 0x180(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_801326F4
    li r29, 0x1
    b SuikaBall_Update_L_80132740
    SuikaBall_Update_L_801326F4:
    lwz r0, 0x2ec(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132708
    li r29, 0x2
    b SuikaBall_Update_L_80132740
    SuikaBall_Update_L_80132708:
    lwz r0, 0x458(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_8013271C
    li r29, 0x3
    b SuikaBall_Update_L_80132740
    SuikaBall_Update_L_8013271C:
    lwz r0, 0x5c4(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132730
    li r29, 0x4
    b SuikaBall_Update_L_80132740
    SuikaBall_Update_L_80132730:
    lwz r0, 0x730(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132740
    li r29, 0x5
    SuikaBall_Update_L_80132740:
    lfs f1, 0x38(r1)
    lfs f0, 0x40(r1)
    fsubs f1, f31, f1
    fsubs f2, f30, f0
    bl atan2
    mulli r29, r29, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D72B8(r2)
    frsp f2, f1
    lfs f1, lbl_806D72D8(r2)
    add r3, r30, r29
    stw r4, 0x14(r3)
    fadds f29, f2, f1
    stw r0, 0x1c(r3)
    fmr f1, f29
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x38(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x3c(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x40(r1)
    stfs f0, 0x28(r3)
    bl LUT_Cosine
    lfs f0, lbl_806D72CC(r2)
    add r3, r30, r29
    fmuls f0, f0, f1
    fmr f1, f29
    stfs f0, 0x2c(r3)
    bl LUT_Sine
    lfs f2, lbl_806D72CC(r2)
    add r3, r30, r29
    lfs f0, lbl_806D72D0(r2)
    fmuls f1, f2, f1
    stfs f1, 0x34(r3)
    stfs f0, 0x30(r3)
    SuikaBall_Update_L_801327D4:
    lwz r3, 0x68(r31)
    addi r0, r3, 0x2
    stw r0, 0x68(r31)
    b SuikaBall_Update_L_80132D60
    SuikaBall_Update_L_801327E4:
    lwz r30, 0x60(r31)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq SuikaBall_Update_L_80132940
    lis r3, lbl_80357A6C@ha
    lis r4, lbl_80357A88@ha
    addi r3, r3, lbl_80357A6C@l
    li r5, 0x2d8
    addi r4, r4, lbl_80357A88@l
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne SuikaBall_Update_L_8013282C
    li r3, 0xab
    bl fn_8016C394
    SuikaBall_Update_L_8013282C:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r30)
    li r29, 0x0
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_8013284C
    li r29, 0x0
    b SuikaBall_Update_L_801328AC
    SuikaBall_Update_L_8013284C:
    lwz r0, 0x180(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132860
    li r29, 0x1
    b SuikaBall_Update_L_801328AC
    SuikaBall_Update_L_80132860:
    lwz r0, 0x2ec(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132874
    li r29, 0x2
    b SuikaBall_Update_L_801328AC
    SuikaBall_Update_L_80132874:
    lwz r0, 0x458(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132888
    li r29, 0x3
    b SuikaBall_Update_L_801328AC
    SuikaBall_Update_L_80132888:
    lwz r0, 0x5c4(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_8013289C
    li r29, 0x4
    b SuikaBall_Update_L_801328AC
    SuikaBall_Update_L_8013289C:
    lwz r0, 0x730(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_801328AC
    li r29, 0x5
    SuikaBall_Update_L_801328AC:
    lfs f1, 0x38(r1)
    lfs f0, 0x40(r1)
    fsubs f1, f31, f1
    fsubs f2, f30, f0
    bl atan2
    mulli r29, r29, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D72B8(r2)
    frsp f2, f1
    lfs f1, lbl_806D72D4(r2)
    add r3, r30, r29
    stw r4, 0x14(r3)
    fadds f29, f2, f1
    stw r0, 0x1c(r3)
    fmr f1, f29
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x38(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x3c(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x40(r1)
    stfs f0, 0x28(r3)
    bl LUT_Cosine
    lfs f0, lbl_806D72CC(r2)
    add r3, r30, r29
    fmuls f0, f0, f1
    fmr f1, f29
    stfs f0, 0x2c(r3)
    bl LUT_Sine
    lfs f2, lbl_806D72CC(r2)
    add r3, r30, r29
    lfs f0, lbl_806D72D0(r2)
    fmuls f1, f2, f1
    stfs f1, 0x34(r3)
    stfs f0, 0x30(r3)
    SuikaBall_Update_L_80132940:
    lwz r30, 0x60(r31)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq SuikaBall_Update_L_80132A9C
    lis r3, lbl_80357A6C@ha
    lis r4, lbl_80357A88@ha
    addi r3, r3, lbl_80357A6C@l
    li r5, 0x2d8
    addi r4, r4, lbl_80357A88@l
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne SuikaBall_Update_L_80132988
    li r3, 0xab
    bl fn_8016C394
    SuikaBall_Update_L_80132988:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r30)
    li r29, 0x0
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_801329A8
    li r29, 0x0
    b SuikaBall_Update_L_80132A08
    SuikaBall_Update_L_801329A8:
    lwz r0, 0x180(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_801329BC
    li r29, 0x1
    b SuikaBall_Update_L_80132A08
    SuikaBall_Update_L_801329BC:
    lwz r0, 0x2ec(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_801329D0
    li r29, 0x2
    b SuikaBall_Update_L_80132A08
    SuikaBall_Update_L_801329D0:
    lwz r0, 0x458(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_801329E4
    li r29, 0x3
    b SuikaBall_Update_L_80132A08
    SuikaBall_Update_L_801329E4:
    lwz r0, 0x5c4(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_801329F8
    li r29, 0x4
    b SuikaBall_Update_L_80132A08
    SuikaBall_Update_L_801329F8:
    lwz r0, 0x730(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132A08
    li r29, 0x5
    SuikaBall_Update_L_80132A08:
    lfs f1, 0x38(r1)
    lfs f0, 0x40(r1)
    fsubs f1, f31, f1
    fsubs f2, f30, f0
    bl atan2
    mulli r29, r29, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D72B8(r2)
    frsp f2, f1
    lfs f1, lbl_806D72D8(r2)
    add r3, r30, r29
    stw r4, 0x14(r3)
    fadds f29, f2, f1
    stw r0, 0x1c(r3)
    fmr f1, f29
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x38(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x3c(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x40(r1)
    stfs f0, 0x28(r3)
    bl LUT_Cosine
    lfs f0, lbl_806D72CC(r2)
    add r3, r30, r29
    fmuls f0, f0, f1
    fmr f1, f29
    stfs f0, 0x2c(r3)
    bl LUT_Sine
    lfs f2, lbl_806D72CC(r2)
    add r3, r30, r29
    lfs f0, lbl_806D72D0(r2)
    fmuls f1, f2, f1
    stfs f1, 0x34(r3)
    stfs f0, 0x30(r3)
    SuikaBall_Update_L_80132A9C:
    lwz r30, 0x60(r31)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq SuikaBall_Update_L_80132BF8
    lis r3, lbl_80357A6C@ha
    lis r4, lbl_80357A88@ha
    addi r3, r3, lbl_80357A6C@l
    li r5, 0x2d8
    addi r4, r4, lbl_80357A88@l
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne SuikaBall_Update_L_80132AE4
    li r3, 0xab
    bl fn_8016C394
    SuikaBall_Update_L_80132AE4:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r30)
    li r29, 0x0
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132B04
    li r29, 0x0
    b SuikaBall_Update_L_80132B64
    SuikaBall_Update_L_80132B04:
    lwz r0, 0x180(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132B18
    li r29, 0x1
    b SuikaBall_Update_L_80132B64
    SuikaBall_Update_L_80132B18:
    lwz r0, 0x2ec(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132B2C
    li r29, 0x2
    b SuikaBall_Update_L_80132B64
    SuikaBall_Update_L_80132B2C:
    lwz r0, 0x458(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132B40
    li r29, 0x3
    b SuikaBall_Update_L_80132B64
    SuikaBall_Update_L_80132B40:
    lwz r0, 0x5c4(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132B54
    li r29, 0x4
    b SuikaBall_Update_L_80132B64
    SuikaBall_Update_L_80132B54:
    lwz r0, 0x730(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132B64
    li r29, 0x5
    SuikaBall_Update_L_80132B64:
    lfs f1, 0x38(r1)
    lfs f0, 0x40(r1)
    fsubs f1, f31, f1
    fsubs f2, f30, f0
    bl atan2
    mulli r29, r29, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D72B8(r2)
    frsp f2, f1
    lfs f1, lbl_806D72DC(r2)
    add r3, r30, r29
    stw r4, 0x14(r3)
    fadds f29, f2, f1
    stw r0, 0x1c(r3)
    fmr f1, f29
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x38(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x3c(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x40(r1)
    stfs f0, 0x28(r3)
    bl LUT_Cosine
    lfs f0, lbl_806D72CC(r2)
    add r3, r30, r29
    fmuls f0, f0, f1
    fmr f1, f29
    stfs f0, 0x2c(r3)
    bl LUT_Sine
    lfs f2, lbl_806D72CC(r2)
    add r3, r30, r29
    lfs f0, lbl_806D72D0(r2)
    fmuls f1, f2, f1
    stfs f1, 0x34(r3)
    stfs f0, 0x30(r3)
    SuikaBall_Update_L_80132BF8:
    lwz r30, 0x60(r31)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq SuikaBall_Update_L_80132D54
    lis r3, lbl_80357A6C@ha
    lis r4, lbl_80357A88@ha
    addi r3, r3, lbl_80357A6C@l
    li r5, 0x2d8
    addi r4, r4, lbl_80357A88@l
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne SuikaBall_Update_L_80132C40
    li r3, 0xab
    bl fn_8016C394
    SuikaBall_Update_L_80132C40:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r30)
    li r29, 0x0
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132C60
    li r29, 0x0
    b SuikaBall_Update_L_80132CC0
    SuikaBall_Update_L_80132C60:
    lwz r0, 0x180(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132C74
    li r29, 0x1
    b SuikaBall_Update_L_80132CC0
    SuikaBall_Update_L_80132C74:
    lwz r0, 0x2ec(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132C88
    li r29, 0x2
    b SuikaBall_Update_L_80132CC0
    SuikaBall_Update_L_80132C88:
    lwz r0, 0x458(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132C9C
    li r29, 0x3
    b SuikaBall_Update_L_80132CC0
    SuikaBall_Update_L_80132C9C:
    lwz r0, 0x5c4(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132CB0
    li r29, 0x4
    b SuikaBall_Update_L_80132CC0
    SuikaBall_Update_L_80132CB0:
    lwz r0, 0x730(r30)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132CC0
    li r29, 0x5
    SuikaBall_Update_L_80132CC0:
    lfs f1, 0x38(r1)
    lfs f0, 0x40(r1)
    fsubs f1, f31, f1
    fsubs f2, f30, f0
    bl atan2
    mulli r29, r29, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D72B8(r2)
    frsp f2, f1
    lfs f1, lbl_806D72E0(r2)
    add r3, r30, r29
    stw r4, 0x14(r3)
    fadds f29, f2, f1
    stw r0, 0x1c(r3)
    fmr f1, f29
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x38(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x3c(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x40(r1)
    stfs f0, 0x28(r3)
    bl LUT_Cosine
    lfs f0, lbl_806D72CC(r2)
    add r3, r30, r29
    fmuls f0, f0, f1
    fmr f1, f29
    stfs f0, 0x2c(r3)
    bl LUT_Sine
    lfs f2, lbl_806D72CC(r2)
    add r3, r30, r29
    lfs f0, lbl_806D72D0(r2)
    fmuls f1, f2, f1
    stfs f1, 0x34(r3)
    stfs f0, 0x30(r3)
    SuikaBall_Update_L_80132D54:
    lwz r3, 0x68(r31)
    addi r0, r3, 0x4
    stw r0, 0x68(r31)
    SuikaBall_Update_L_80132D60:
    li r30, 0x0
    li r29, 0x0
    SuikaBall_Update_L_80132D68:
    lwz r0, 0x5c(r31)
    add r28, r0, r29
    lwz r3, 0x0(r28)
    bl clNormal3D_Exec
    lwz r3, 0x4(r28)
    bl clNormal3D_Exec
    addi r30, r30, 0x1
    addi r29, r29, 0x14
    cmplwi r30, 0x3
    blt SuikaBall_Update_L_80132D68
    lwz r3, 0x60(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    lis r4, lbl_80677C70@ha
    lwz r3, 0x18(r31)
    addi r4, r4, lbl_80677C70@l
    bl CObj_LoadProjMatrix
    lis r4, lbl_80677C7C@ha
    lwz r3, 0x18(r31)
    addi r4, r4, lbl_80677C7C@l
    bl CObj_ApplyScissor
    bl ItemObjectManager_Update
    lis r3, lbl_80677C7C@ha
    lis r4, lbl_80677C70@ha
    addi r5, r3, lbl_80677C7C@l
    addi r3, r1, 0x2c
    addi r7, r4, lbl_80677C70@l
    lwz r10, 0x0(r5)
    lwz r9, 0x4(r5)
    addi r4, r1, 0x20
    lwz r8, 0x8(r5)
    lwz r6, 0x0(r7)
    lwz r5, 0x4(r7)
    lwz r0, 0x8(r7)
    stw r10, 0x20(r1)
    stw r9, 0x24(r1)
    stw r8, 0x28(r1)
    stw r6, 0x2c(r1)
    stw r5, 0x30(r1)
    stw r0, 0x34(r1)
    bl VfxSlotMgr_Update
    bl IsRaceStarted
    clrlwi. r0, r3, 24
    beq SuikaBall_Update_L_80132E6C
    lbz r0, 0x32(r31)
    cmplwi r0, 0x0
    bne SuikaBall_Update_L_80132E6C
    lfs f2, g_raceTimeRemaining(r13)
    lfs f1, lbl_806D72B8(r2)
    fcmpo cr0, f2, f1
    cror eq, gt, eq
    bne SuikaBall_Update_L_80132E6C
    lfs f0, lbl_806D72E4(r2)
    fsubs f0, f2, f0
    fcmpo cr0, f0, f1
    stfs f0, g_raceTimeRemaining(r13)
    bge SuikaBall_Update_L_80132E6C
    stfs f1, g_raceTimeRemaining(r13)
    li r0, 0x1
    stb r0, 0x32(r31)
    lwz r3, 0xc(r31)
    bl CarObject_GetRenderObj
    bl KartMovement_ResetOnTimeout
    SuikaBall_Update_L_80132E6C:
    lwz r3, 0x2c(r31)
    lfs f1, g_raceTimeRemaining(r13)
    bl fn_80253FD8
    lwz r3, 0xc(r31)
    bl CarObject_CalcSpeedRatio
    lfs f0, lbl_806D72E8(r2)
    lwz r3, 0x2c(r31)
    fmuls f1, f0, f1
    bl fn_80253EBC
    lwz r3, 0xc(r31)
    bl KartItem_GetCurrentSpeedWithBonus
    lwz r3, 0x2c(r31)
    bl fn_80253EC0
    lwz r3, 0x2c(r31)
    bl HUD_FrameUpdate
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne SuikaBall_Update_L_80132EB8
    li r3, 0x0
    SuikaBall_Update_L_80132EB8:
    bl TransitionEffect_Tick
    lbz r0, 0x32(r31)
    cmplwi r0, 0x0
    beq SuikaBall_Update_L_80132FBC
    lwz r0, 0x34(r31)
    cmpwi r0, 0x0
    bne SuikaBall_Update_L_80132F90
    lwz r3, 0x68(r31)
    bl SetCoinCount
    li r3, 0xd5
    li r4, 0x2
    bl fn_80192688
    lbz r0, 0x33(r31)
    cmplwi r0, 0x0
    beq SuikaBall_Update_L_80132F3C
    lwz r3, 0xc(r31)
    bl CarObject_GetRenderObj
    bl KartMovement_ResetOnGoal
    mr r3, r31
    li r4, 0x1
    li r5, 0x0
    bl NokoNokoChallenge_CalcResultText
    mr r5, r3
    lwz r3, 0x2c(r31)
    li r4, 0x1
    li r6, 0x0
    bl fn_80253C74
    lwz r3, 0x18(r31)
    li r4, 0x1
    bl Object_SetByte10_Return1
    li r3, 0xd6
    bl SoundMgr_Play
    b SuikaBall_Update_L_80132F6C
    SuikaBall_Update_L_80132F3C:
    mr r3, r31
    li r4, 0x0
    li r5, 0x0
    bl NokoNokoChallenge_CalcResultText
    mr r5, r3
    lwz r3, 0x2c(r31)
    li r4, 0x0
    li r6, 0x0
    bl fn_80253C74
    lwz r3, 0x18(r31)
    li r4, 0x1
    bl Object_SetByte10_Return1
    SuikaBall_Update_L_80132F6C:
    lwz r4, 0x68(r31)
    mr r3, r31
    lbz r5, 0x33(r31)
    bl NokoNokoChallenge_SaveResult
    li r3, 0x1
    li r0, 0x0
    stb r3, g_raceEnded(r13)
    stb r0, g_lakituStartAnimDone(r13)
    b SuikaBall_Update_L_80132FB0
    SuikaBall_Update_L_80132F90:
    ble SuikaBall_Update_L_80132FB0
    lwz r3, 0x2c(r31)
    bl fn_80253C40
    clrlwi. r0, r3, 24
    beq SuikaBall_Update_L_80132FB0
    mr r3, r31
    bl NokoNokoChallenge_TransitionToResult
    b SuikaBall_Update_L_80132FD0
    SuikaBall_Update_L_80132FB0:
    lwz r3, 0x34(r31)
    addi r0, r3, 0x1
    stw r0, 0x34(r31)
    SuikaBall_Update_L_80132FBC:
    lwz r3, g_weatherSystem(r13)
    cmplwi r3, 0x0
    beq SuikaBall_Update_L_80132FCC
    bl fn_8016B32C
    SuikaBall_Update_L_80132FCC:
    li r3, -0x2
    SuikaBall_Update_L_80132FD0:
    psq_l f31, 0x88(r1), 0, 0
    lfd f31, 0x80(r1)
    psq_l f30, 0x78(r1), 0, 0
    lfd f30, 0x70(r1)
    psq_l f29, 0x68(r1), 0, 0
    lfd f29, 0x60(r1)
    lwz r31, 0x5c(r1)
    lwz r30, 0x58(r1)
    lwz r29, 0x54(r1)
    lwz r0, 0x94(r1)
    lwz r28, 0x50(r1)
    mtlr r0
    addi r1, r1, 0x90
    blr
}

extern "C" asm void fn_80133008(void) { /* 0x80133008 size:0x390 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stmw r27, 0xc(r1)
    mr. r31, r3
    mr r30, r4
    beq fn_80133008_L_80133380
    lis r3, lbl_8048E3F8@ha
    addi r0, r3, lbl_8048E3F8@l
    stw r0, 0x0(r31)
    lwz r3, 0x60(r31)
    cmplwi r3, 0x0
    beq fn_80133008_L_80133050
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_80133008_L_80133050:
    lwz r28, 0x64(r31)
    cmplwi r28, 0x0
    beq fn_80133008_L_8013308C
    li r29, 0x0
    mr r27, r28
    fn_80133008_L_80133064:
    lwz r3, 0x0(r27)
    cmplwi r3, 0x0
    beq fn_80133008_L_80133074
    bl MemoryManager_TimedFree
    fn_80133008_L_80133074:
    addi r29, r29, 0x1
    addi r27, r27, 0x4
    cmpwi r29, 0x4
    blt fn_80133008_L_80133064
    mr r3, r28
    bl MemoryManager_TimedFree
    fn_80133008_L_8013308C:
    li r3, 0x24
    bl fn_8016C394
    lwz r3, g_weatherSystem(r13)
    cmplwi r3, 0x0
    beq fn_80133008_L_801330B0
    li r4, 0x1
    bl fn_8016C634
    li r0, 0x0
    stw r0, g_weatherSystem(r13)
    fn_80133008_L_801330B0:
    li r3, 0x0
    li r4, 0x0
    bl SetActiveCamera
    lwz r3, 0x18(r31)
    cmplwi r3, 0x0
    beq fn_80133008_L_801330DC
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_80133008_L_801330DC:
    lwz r3, 0x10(r31)
    li r4, 0x1
    bl LakituStart_Dtor
    lwz r3, 0x1c(r31)
    li r4, 0x1
    bl fn_80124C84
    li r3, 0x0
    bl SetPlayerCarObject
    lwz r3, 0xc(r31)
    cmplwi r3, 0x0
    beq fn_80133008_L_8013311C
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    fn_80133008_L_8013311C:
    li r0, 0x0
    stw r0, g_raceCamera(r13)
    lwz r3, 0x20(r31)
    cmplwi r3, 0x0
    beq fn_80133008_L_80133148
    beq fn_80133008_L_80133148
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_80133008_L_80133148:
    lwz r27, 0x24(r31)
    cmplwi r27, 0x0
    beq fn_80133008_L_801331C4
    beq fn_80133008_L_801331C4
    lis r3, 0x1
    lhz r4, 0x4(r27)
    subi r0, r3, 0x1
    clrlwi r0, r0, 16
    subf r0, r4, r0
    cntlzw r0, r0
    extrwi. r0, r0, 8, 19
    beq fn_80133008_L_8013317C
    b fn_80133008_L_8013318C
    fn_80133008_L_8013317C:
    subi r3, r4, 0x1
    cntlzw r0, r4
    sth r3, 0x4(r27)
    extrwi r0, r0, 8, 19
    fn_80133008_L_8013318C:
    cmpwi r0, 0x0
    beq fn_80133008_L_801331C4
    cmplwi r27, 0x0
    beq fn_80133008_L_801331C4
    lwz r4, 0x0(r27)
    mr r3, r27
    lwz r12, 0x30(r4)
    mtctr r12
    bctrl
    lwz r4, 0x0(r27)
    mr r3, r27
    lwz r12, 0x34(r4)
    mtctr r12
    bctrl
    fn_80133008_L_801331C4:
    lwz r3, 0x14(r31)
    li r4, 0x1
    bl CourseEnvironment_Dtor
    lwz r3, 0x2c(r31)
    li r4, 0x1
    bl fn_80254134
    lwz r3, 0x3c(r31)
    li r4, 0x1
    bl fn_8012491C
    lwz r3, 0x40(r31)
    cmplwi r3, 0x0
    beq fn_80133008_L_801331F8
    bl MemoryManager_TimedFree
    fn_80133008_L_801331F8:
    lwz r3, 0x44(r31)
    cmplwi r3, 0x0
    beq fn_80133008_L_80133218
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_80133008_L_80133218:
    lwz r3, 0x48(r31)
    cmplwi r3, 0x0
    beq fn_80133008_L_80133238
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_80133008_L_80133238:
    lwz r0, 0x5c(r31)
    cmplwi r0, 0x0
    beq fn_80133008_L_801332C8
    li r28, 0x0
    li r27, 0x0
    fn_80133008_L_8013324C:
    lwz r3, 0x5c(r31)
    addi r0, r27, 0x8
    lwzx r3, r3, r0
    cmplwi r3, 0x0
    beq fn_80133008_L_80133264
    bl MemoryManager_Free
    fn_80133008_L_80133264:
    lwz r3, 0x5c(r31)
    addi r0, r27, 0xc
    lwzx r3, r3, r0
    cmplwi r3, 0x0
    beq fn_80133008_L_8013327C
    bl MemoryManager_Free
    fn_80133008_L_8013327C:
    lwz r3, 0x5c(r31)
    lwzx r3, r3, r27
    cmplwi r3, 0x0
    beq fn_80133008_L_80133294
    li r4, 0x1
    bl Object_DtorWithGXSync
    fn_80133008_L_80133294:
    lwz r3, 0x5c(r31)
    addi r0, r27, 0x4
    lwzx r3, r3, r0
    cmplwi r3, 0x0
    beq fn_80133008_L_801332B0
    li r4, 0x1
    bl Object_DtorWithGXSync
    fn_80133008_L_801332B0:
    addi r28, r28, 0x1
    addi r27, r27, 0x14
    cmplwi r28, 0x3
    blt fn_80133008_L_8013324C
    lwz r3, 0x5c(r31)
    bl MemoryManager_Free
    fn_80133008_L_801332C8:
    bl ItemObjectManager_Reset
    bl VfxSlotMgr_Shutdown
    bl ClRomTable_PurgeAll
    bl GetRaceContextPtr
    bl RankingTable_Init
    lwz r3, lbl_806D10D0(r13)
    cmplwi r3, 0x0
    beq fn_80133008_L_801332FC
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_80133008_L_801332FC:
    li r0, 0x0
    stw r0, lbl_806D10D0(r13)
    bl SceneDrawList_Reset
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    beq fn_80133008_L_80133328
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_80133008_L_80133328:
    li r0, 0x0
    li r3, 0x0
    stw r0, lbl_806D109C(r13)
    bl SetResourceLoadingFlag
    bl clRom_PurgeAll
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    beq fn_80133008_L_8013335C
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_80133008_L_8013335C:
    li r0, 0x0
    mr r3, r31
    stw r0, lbl_806D10AC(r13)
    li r4, 0x0
    bl dtor_80122FD8
    extsh. r0, r30
    ble fn_80133008_L_80133380
    mr r3, r31
    bl MemoryManager_TimedFree
    fn_80133008_L_80133380:
    mr r3, r31
    lmw r27, 0xc(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void SuikaBall_Init(void) { /* 0x80133398 size:0x910 */
    nofralloc
    stwu r1, -0xb0(r1)
    mflr r0
    stw r0, 0xb4(r1)
    stfd f31, 0xa0(r1)
    psq_st f31, 0xa8(r1), 0, 0
    stmw r22, 0x78(r1)
    mr r31, r3
    lis r4, lbl_80357008@ha
    mr r0, r31
    mr r22, r0
    addi r30, r4, lbl_80357008@l
    bl GameMode_BaseInit
    lis r4, lbl_8048E144@ha
    lis r3, lbl_8048E3F8@ha
    addi r0, r4, lbl_8048E144@l
    lfs f0, lbl_806D72B8(r2)
    stw r0, 0x0(r22)
    addi r0, r3, lbl_8048E3F8@l
    stfs f0, 0x4(r22)
    stw r0, 0x0(r31)
    bl MiniGame_GetCourseData
    stw r3, 0x8(r31)
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
    mr. r22, r3
    beq SuikaBall_Init_L_80133424
    bl InputManager_Init
    SuikaBall_Init_L_80133424:
    stw r22, 0x14(r31)
    bl GetCourseDataPtr
    bl HSD_LObjLoadDesc
    stw r3, 0x24(r31)
    li r3, 0x2c
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_8013345C
    lfs f1, lbl_806D72F8(r2)
    li r4, 0x100
    lfs f2, lbl_806D72B4(r2)
    li r5, 0x100
    lwz r6, 0x24(r31)
    bl Camera_Create
    SuikaBall_Init_L_8013345C:
    stw r22, 0x20(r31)
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
    addi r6, r1, 0x68
    addi r4, r1, 0x60
    addi r5, r1, 0x64
    li r3, 0x0
    bl GetStartPosition
    li r3, 0x118
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_80133500
    lwz r26, g_characterId(r13)
    bl GetCourseStartYaw
    fmr f31, f1
    bl GetDisplayBufferIndex
    li r0, 0x0
    mr r4, r3
    stw r0, 0x8(r1)
    fmr f3, f31
    mr r3, r22
    mr r5, r26
    lfs f1, 0x60(r1)
    li r6, 0x0
    lfs f2, 0x68(r1)
    li r7, 0x0
    li r8, 0x1
    li r9, 0x0
    li r10, 0x0
    bl CarObject_Init
    SuikaBall_Init_L_80133500:
    stw r22, 0xc(r31)
    addi r4, r1, 0x60
    lwz r3, 0xc(r31)
    bl CarObject_SetPosition
    lwz r3, 0xc(r31)
    bl CarObject_GetRenderObj
    li r0, 0x1
    stw r0, 0x238(r3)
    lwz r3, 0xc(r31)
    bl SetPlayerCarObject
    li r3, 0x58
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_80133550
    lfs f1, lbl_806D72B8(r2)
    addi r4, r30, 0xa90
    li r5, 0x0
    fmr f2, f1
    fmr f3, f1
    bl LakituStart_Init
    SuikaBall_Init_L_80133550:
    stw r22, 0x10(r31)
    li r3, 0x3084
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_80133580
    lwz r3, g_characterId(r13)
    li r4, -0x1
    bl GetKartModelNameEntry
    mr r4, r3
    mr r3, r22
    lwz r4, 0x0(r4)
    bl Scene3D_Init
    SuikaBall_Init_L_80133580:
    stw r22, 0x18(r31)
    li r3, 0x8
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_80133598
    bl ChallengeGoalCamera_Init
    SuikaBall_Init_L_80133598:
    stw r22, 0x1c(r31)
    li r3, 0x0
    bl ProcessSystemTick
    lwz r3, 0x18(r31)
    addi r4, r1, 0x14
    addi r5, r1, 0x10
    bl Scene3D_GetCameraPos
    lfs f1, 0x14(r1)
    lfs f0, lbl_806D729C(r2)
    lfs f2, 0x10(r1)
    fadds f1, f1, f0
    stfs f1, 0x14(r1)
    lwz r3, 0x18(r31)
    bl Scene3D_SetupProjection
    li r3, 0x80
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_801335E8
    li r4, 0x0
    bl HUD_Init
    SuikaBall_Init_L_801335E8:
    stw r22, 0x2c(r31)
    li r4, 0x6
    li r5, 0x0
    lwz r3, 0x2c(r31)
    bl HUD_RegisterOverlay
    lwz r3, 0x2c(r31)
    li r4, 0x11
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x2c(r31)
    li r4, 0x12
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x2c(r31)
    li r4, 0xe
    li r5, 0x0
    bl HUD_RegisterOverlay
    li r0, 0x0
    stb r0, g_lakituStartAnimDone(r13)
    lwz r3, 0x18(r31)
    bl SetCourseScene3D
    li r0, 0x0
    stb r0, g_raceEnded(r13)
    bl MiniGame_GetTimerValue
    xoris r3, r3, 0x8000
    lis r0, 0x4330
    stw r3, 0x74(r1)
    li r3, 0x1
    lfd f1, lbl_806D72A8(r2)
    stw r0, 0x70(r1)
    lfd f0, 0x70(r1)
    fsubs f0, f0, f1
    stfs f0, g_raceTimeRemaining(r13)
    bl PreloadEffectResources
    li r3, 0x9
    bl PreloadEffectResources
    li r3, 0xa
    bl PreloadEffectResources
    li r0, 0x0
    lfs f1, lbl_806D72A4(r2)
    stb r0, 0x30(r31)
    li r3, 0x7c
    lfs f0, lbl_806D72B8(r2)
    stb r0, 0x32(r31)
    stb r0, 0x33(r31)
    stw r0, 0x34(r31)
    stb r0, 0x31(r31)
    stfs f1, 0x4c(r31)
    stfs f0, 0x50(r31)
    stfs f0, 0x54(r31)
    stfs f0, 0x58(r31)
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_801336C8
    addi r4, r30, 0xaa4
    bl SuikaBallObj_Init
    SuikaBall_Init_L_801336C8:
    cmplwi r22, 0x0
    stw r22, 0x3c(r31)
    beq SuikaBall_Init_L_8013375C
    lwz r3, 0x3c(r31)
    lfs f0, lbl_806D72FC(r2)
    lfs f1, lbl_806D7300(r2)
    stfs f0, 0x38(r3)
    lfs f0, lbl_806D7304(r2)
    stfs f1, 0x3c(r3)
    stfs f0, 0x40(r3)
    lwz r23, g_raceCamera(r13)
    cmplwi r23, 0x0
    beq SuikaBall_Init_L_8013371C
    lwz r3, 0x3c(r31)
    lwz r3, 0x0(r3)
    cmplwi r3, 0x0
    beq SuikaBall_Init_L_8013371C
    bl Archive_GetRootJObj
    mr r4, r3
    mr r3, r23
    bl SceneRender_CmdB_8aa20
    SuikaBall_Init_L_8013371C:
    lwz r4, 0x8(r31)
    cmplwi r4, 0x0
    beq SuikaBall_Init_L_8013375C
    lfs f5, 0x14(r4)
    lfs f4, 0x10(r4)
    lfs f3, 0xc(r4)
    lfs f2, 0x8(r4)
    lfs f1, 0x4(r4)
    lwz r3, 0x3c(r31)
    lfs f0, 0x0(r4)
    stfs f0, 0x64(r3)
    stfs f1, 0x68(r3)
    stfs f2, 0x6c(r3)
    stfs f3, 0x70(r3)
    stfs f4, 0x74(r3)
    stfs f5, 0x78(r3)
    SuikaBall_Init_L_8013375C:
    li r3, 0xc
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_80133770
    bl fn_8018FEAC
    SuikaBall_Init_L_80133770:
    stw r22, 0x44(r31)
    li r3, 0x10
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_80133788
    bl fn_8018F614
    SuikaBall_Init_L_80133788:
    stw r22, 0x48(r31)
    li r3, 0x30
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_80133860
    lfs f0, lbl_806D7308(r2)
    mr r4, r22
    lfs f2, lbl_806D7300(r2)
    addi r3, r22, 0xc
    stfs f0, 0x30(r1)
    addi r5, r22, 0x18
    lfs f0, lbl_806D730C(r2)
    stfs f2, 0x34(r1)
    lwz r0, 0x30(r1)
    stfs f0, 0x38(r1)
    lfs f0, lbl_806D7310(r2)
    stw r0, 0x48(r1)
    lwz r6, 0x34(r1)
    stfs f0, 0x3c(r1)
    lwz r0, 0x38(r1)
    stw r6, 0x4c(r1)
    lfs f1, 0x48(r1)
    stfs f2, 0x40(r1)
    lfs f0, lbl_806D7314(r2)
    stw r0, 0x50(r1)
    lwz r0, 0x3c(r1)
    stfs f0, 0x44(r1)
    lwz r6, 0x40(r1)
    stw r0, 0x54(r1)
    lwz r0, 0x44(r1)
    stw r6, 0x58(r1)
    lfs f0, 0x4c(r1)
    stfs f1, 0x0(r22)
    lfs f1, 0x50(r1)
    stfs f0, 0x4(r22)
    lfs f0, 0x54(r1)
    stfs f1, 0x8(r22)
    lfs f1, 0x58(r1)
    stw r0, 0x5c(r1)
    stfs f0, 0xc(r22)
    lfs f0, 0x5c(r1)
    stfs f1, 0x10(r22)
    stfs f0, 0x14(r22)
    bl Vec3_Subtract
    addi r3, r22, 0x18
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0x20(r22)
    fneg f0, f0
    stfs f0, 0x24(r22)
    lfs f0, 0x1c(r22)
    stfs f0, 0x28(r22)
    lfs f0, 0x18(r22)
    stfs f0, 0x2c(r22)
    SuikaBall_Init_L_80133860:
    stw r22, 0x40(r31)
    li r3, 0x3c
    bl FUN_8003b120
    stw r3, 0x5c(r31)
    addi r28, r30, 0x9bc
    li r27, 0x0
    li r29, 0x0
    SuikaBall_Init_L_8013387C:
    lwz r0, 0x5c(r31)
    li r3, 0x5c
    add r26, r0, r29
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_801338A0
    lwz r4, 0x0(r28)
    li r5, 0x0
    bl clNormal3D_Construct
    SuikaBall_Init_L_801338A0:
    lfs f1, lbl_806D72B8(r2)
    li r4, 0x0
    stw r22, 0x0(r26)
    fmr f3, f1
    lfs f2, lbl_806D72A4(r2)
    fmr f4, f1
    lwz r3, 0x0(r26)
    bl clNormal3D_SetScale
    li r3, 0x5c
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_801338DC
    lwz r4, 0x4(r28)
    li r5, 0x0
    bl clNormal3D_Construct
    SuikaBall_Init_L_801338DC:
    lfs f1, lbl_806D72B8(r2)
    li r4, 0x0
    stw r22, 0x4(r26)
    fmr f3, f1
    lfs f2, lbl_806D72A4(r2)
    fmr f4, f1
    lwz r3, 0x4(r26)
    bl clNormal3D_SetScale
    lwz r0, 0xc(r28)
    stw r0, 0x10(r26)
    lwz r0, 0x10(r26)
    slwi r3, r0, 2
    bl FUN_8003b120
    stw r3, 0x8(r26)
    lwz r0, 0x10(r26)
    slwi r3, r0, 2
    bl FUN_8003b120
    li r25, 0x0
    stw r3, 0xc(r26)
    mr r24, r25
    addi r23, r28, 0x8
    li r22, 0x0
    b SuikaBall_Init_L_80133978
    SuikaBall_Init_L_80133938:
    lwz r4, 0x0(r23)
    lwz r3, 0x0(r26)
    lwzx r4, r4, r25
    bl ResolveJointByName
    lwz r5, 0x8(r26)
    addi r0, r25, 0x4
    lwz r4, 0x0(r23)
    stwx r3, r5, r24
    lwz r3, 0x4(r26)
    lwzx r4, r4, r0
    bl ResolveJointByName
    lwz r4, 0xc(r26)
    addi r25, r25, 0x8
    addi r22, r22, 0x1
    stwx r3, r4, r24
    addi r24, r24, 0x4
    SuikaBall_Init_L_80133978:
    lwz r0, 0x10(r26)
    cmpw r22, r0
    blt SuikaBall_Init_L_80133938
    addi r27, r27, 0x1
    addi r28, r28, 0x10
    cmplwi r27, 0x3
    addi r29, r29, 0x14
    blt SuikaBall_Init_L_8013387C
    li r3, 0x8a0
    bl Alloc
    mr. r26, r3
    beq SuikaBall_Init_L_80133B68
    lis r3, lbl_8048E34C@ha
    li r4, 0x0
    addi r3, r3, lbl_8048E34C@l
    li r0, 0x5
    stw r3, 0x0(r26)
    li r3, 0x5c
    stw r4, 0xc(r26)
    stw r4, 0x10(r26)
    stw r0, 0x89c(r26)
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_801339E4
    addi r4, r30, 0xab8
    li r5, 0x1
    bl clNormal3D_Construct
    SuikaBall_Init_L_801339E4:
    stw r22, 0x4(r26)
    lis r4, 0x4000
    li r5, 0x0
    lwz r3, 0x4(r26)
    bl clNormal3D_SetFlags
    li r3, 0x5c
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_80133A14
    addi r4, r30, 0xac8
    li r5, 0x1
    bl clNormal3D_Construct
    SuikaBall_Init_L_80133A14:
    stw r22, 0x8(r26)
    lwz r3, 0x8(r26)
    bl Archive_GetRootJObj
    li r4, 0x200
    bl HSD_JObjSetFlags
    li r0, 0x3
    mr r5, r26
    lfs f0, lbl_806D72B8(r2)
    li r4, 0x0
    mtctr r0
    SuikaBall_Init_L_80133A3C:
    li r3, 0x0
    li r0, -0x1
    stw r3, 0x14(r5)
    stw r3, 0x1c(r5)
    stfs f0, 0x38(r5)
    stfs f0, 0x3c(r5)
    stw r3, 0x18(r5)
    stfs f0, 0x28(r5)
    stfs f0, 0x24(r5)
    stfs f0, 0x20(r5)
    stfs f0, 0x34(r5)
    stfs f0, 0x30(r5)
    stfs f0, 0x2c(r5)
    stw r0, 0x40(r5)
    stw r0, 0x50(r5)
    stw r0, 0x60(r5)
    stw r0, 0x70(r5)
    stw r0, 0x80(r5)
    stw r0, 0x90(r5)
    stw r0, 0xa0(r5)
    stw r0, 0xb0(r5)
    stw r0, 0xc0(r5)
    stw r0, 0xd0(r5)
    stw r0, 0xe0(r5)
    stw r0, 0xf0(r5)
    stw r0, 0x100(r5)
    stw r0, 0x110(r5)
    stw r0, 0x120(r5)
    stw r0, 0x130(r5)
    stw r0, 0x140(r5)
    stw r0, 0x150(r5)
    stw r0, 0x160(r5)
    stw r0, 0x170(r5)
    stw r3, 0x180(r5)
    stw r3, 0x188(r5)
    stfs f0, 0x1a4(r5)
    stfs f0, 0x1a8(r5)
    stw r3, 0x184(r5)
    stfs f0, 0x194(r5)
    stfs f0, 0x190(r5)
    stfs f0, 0x18c(r5)
    stfs f0, 0x1a0(r5)
    stfs f0, 0x19c(r5)
    stfs f0, 0x198(r5)
    stw r0, 0x1ac(r5)
    addi r4, r4, 0x1
    stw r0, 0x1bc(r5)
    stw r0, 0x1cc(r5)
    stw r0, 0x1dc(r5)
    stw r0, 0x1ec(r5)
    stw r0, 0x1fc(r5)
    stw r0, 0x20c(r5)
    stw r0, 0x21c(r5)
    stw r0, 0x22c(r5)
    stw r0, 0x23c(r5)
    stw r0, 0x24c(r5)
    stw r0, 0x25c(r5)
    stw r0, 0x26c(r5)
    stw r0, 0x27c(r5)
    stw r0, 0x28c(r5)
    stw r0, 0x29c(r5)
    stw r0, 0x2ac(r5)
    stw r0, 0x2bc(r5)
    stw r0, 0x2cc(r5)
    stw r0, 0x2dc(r5)
    addi r5, r5, 0x2d8
    bdnz SuikaBall_Init_L_80133A3C
    lwz r0, 0x89c(r26)
    cmpwi r0, 0x14
    blt SuikaBall_Init_L_80133B5C
    li r0, 0x13
    stw r0, 0x89c(r26)
    SuikaBall_Init_L_80133B5C:
    lis r3, lbl_8048E418@ha
    addi r0, r3, lbl_8048E418@l
    stw r0, 0x0(r26)
    SuikaBall_Init_L_80133B68:
    stw r26, 0x60(r31)
    li r3, 0x14
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_80133C4C
    li r26, 0x0
    mr r24, r22
    stw r26, 0x10(r22)
    addi r23, r30, 0x9ec
    SuikaBall_Init_L_80133B8C:
    li r3, 0x30
    bl Alloc
    mr. r25, r3
    beq SuikaBall_Init_L_80133C34
    lwz r0, 0x0(r23)
    mr r4, r25
    lwz r6, 0x4(r23)
    addi r3, r25, 0xc
    stw r0, 0x18(r1)
    addi r5, r25, 0x18
    lwz r0, 0x8(r23)
    stw r6, 0x1c(r1)
    lfs f1, 0x18(r1)
    stw r0, 0x20(r1)
    lwz r0, 0xc(r23)
    lwz r6, 0x10(r23)
    stw r0, 0x24(r1)
    lwz r0, 0x14(r23)
    stw r6, 0x28(r1)
    lfs f0, 0x1c(r1)
    stfs f1, 0x0(r25)
    lfs f1, 0x20(r1)
    stfs f0, 0x4(r25)
    lfs f0, 0x24(r1)
    stfs f1, 0x8(r25)
    lfs f1, 0x28(r1)
    stw r0, 0x2c(r1)
    stfs f0, 0xc(r25)
    lfs f0, 0x2c(r1)
    stfs f1, 0x10(r25)
    stfs f0, 0x14(r25)
    bl Vec3_Subtract
    addi r3, r25, 0x18
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0x20(r25)
    fneg f0, f0
    stfs f0, 0x24(r25)
    lfs f0, 0x1c(r25)
    stfs f0, 0x28(r25)
    lfs f0, 0x18(r25)
    stfs f0, 0x2c(r25)
    SuikaBall_Init_L_80133C34:
    addi r26, r26, 0x1
    stw r25, 0x0(r24)
    cmpwi r26, 0x4
    addi r23, r23, 0x18
    addi r24, r24, 0x4
    blt SuikaBall_Init_L_80133B8C
    SuikaBall_Init_L_80133C4C:
    stw r22, 0x64(r31)
    li r0, 0x0
    stw r0, 0x68(r31)
    lwz r0, g_weatherSystem(r13)
    cmplwi r0, 0x0
    bne SuikaBall_Init_L_80133C80
    li r3, 0x1b4
    bl Alloc
    mr. r22, r3
    beq SuikaBall_Init_L_80133C7C
    li r4, 0x1
    bl WeatherSystem_Init
    SuikaBall_Init_L_80133C7C:
    stw r22, g_weatherSystem(r13)
    SuikaBall_Init_L_80133C80:
    li r3, 0x1
    bl SetResourceLoadingFlag
    mr r3, r31
    psq_l f31, 0xa8(r1), 0, 0
    lfd f31, 0xa0(r1)
    lmw r22, 0x78(r1)
    lwz r0, 0xb4(r1)
    mtlr r0
    addi r1, r1, 0xb0
    blr
}

extern "C" void fn_80133CA8(ShotOwner *self)
{
    for (int i = 0; i < 6; i++) {
        if (((ShotSet *)self)->shots[i].active) {
            Object_SetJObjPositionVec(self->model, &((ShotSet *)self)->shots[i].pos);
            Object_SetJObjRotationY(self->model, lbl_806D7298 * ((ShotSet *)self)->shots[i].rot);
            Object_SetColorAlphaOnly(self->model, 0, ((ShotSet *)self)->shots[i].alpha);
            Object_RenderJObjEx(self->model, LinkedNode_GetField10_OrFallback(self->model, 0), 7);
            LNode *n = LinkedNode_GetField10_OrFallback(self->model, 0);
            Object_RenderJObjEx(self->model, n == 0 ? 0 : n->f8, 7);
            for (int j = 0; j < self->trailCount; j++) {
                float f = ((ShotSet *)self)->shots[i].trail[j].age / lbl_806D729C;
                float sc = lbl_806D72A0 - f;
                Object_SetJObjPositionVec(self->trailModel, &((ShotSet *)self)->shots[i].trail[j].pos);
                Object_SetJObjScaleXYZ(self->trailModel, sc, sc, sc);
                Object_SetColorAlphaOnly(self->trailModel, 0, (lbl_806D72A4 - f) * ((ShotSet *)self)->shots[i].alpha);
                Object_RenderJObjTree(self->trailModel, 7);
            }
        }
    }
}

extern "C" asm void fn_80133E64(void) { /* 0x80133E64 size:0x300 */
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
    fn_80133E64_L_80133E90:
    lwz r0, 0x14(r30)
    cmpwi r0, 0x0
    beq fn_80133E64_L_80134130
    lfs f1, 0x20(r30)
    addi r28, r30, 0x40
    lfs f0, 0x2c(r30)
    addi r3, r30, 0x20
    lfs f2, lbl_806D72B4(r2)
    addi r4, r1, 0x8
    fadds f3, f1, f0
    lfs f0, lbl_806D72B8(r2)
    lfs f1, lbl_806D729C(r2)
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
    bne fn_80133E64_L_80133F30
    lfs f1, 0x24(r30)
    lfs f0, 0x8(r1)
    fcmpo cr0, f1, f0
    bge fn_80133E64_L_80133F30
    lfs f0, 0x30(r30)
    lfs f1, lbl_806D72B0(r2)
    fneg f0, f0
    fmuls f0, f1, f0
    stfs f0, 0x30(r30)
    fn_80133E64_L_80133F30:
    lfs f2, 0x38(r30)
    lfs f1, lbl_806D72EC(r2)
    lfs f0, lbl_806D72F0(r2)
    fadds f1, f2, f1
    stfs f1, 0x38(r30)
    lfs f1, 0x38(r30)
    fcmpo cr0, f1, f0
    ble fn_80133E64_L_80133F58
    fsubs f0, f1, f0
    stfs f0, 0x38(r30)
    fn_80133E64_L_80133F58:
    lwz r3, 0x1c(r30)
    lis r0, 0x4330
    stw r0, 0x10(r1)
    mr r5, r28
    xoris r0, r3, 0x8000
    lfd f2, lbl_806D72A8(r2)
    stw r0, 0x14(r1)
    li r6, 0x0
    lfs f0, lbl_806D72F4(r2)
    li r3, -0x1
    lfd f1, 0x10(r1)
    lfs f3, lbl_806D72A4(r2)
    fsubs f2, f1, f2
    lfs f1, lbl_806D72A0(r2)
    fdivs f0, f2, f0
    fsubs f0, f3, f0
    stfs f0, 0x3c(r30)
    b fn_80133E64_L_80133FD8
    fn_80133E64_L_80133FA0:
    lwz r0, 0x0(r5)
    cmpwi r0, 0x0
    blt fn_80133E64_L_80133FD0
    lfs f0, 0x8(r5)
    fsubs f0, f0, f1
    stfs f0, 0x8(r5)
    lwz r4, 0x0(r5)
    addi r0, r4, 0x1
    cmpwi r0, 0xa
    stw r0, 0x0(r5)
    ble fn_80133E64_L_80133FD0
    stw r3, 0x0(r5)
    fn_80133E64_L_80133FD0:
    addi r5, r5, 0x10
    addi r6, r6, 0x1
    fn_80133E64_L_80133FD8:
    lwz r0, 0x89c(r26)
    cmpw r6, r0
    blt fn_80133E64_L_80133FA0
    lwz r0, 0x1c(r30)
    clrlwi. r0, r0, 30
    bne fn_80133E64_L_80134114
    lis r4, lbl_80495A94@ha
    lis r3, lbl_80495994@ha
    mr r31, r28
    li r29, 0x0
    addi r24, r4, lbl_80495A94@l
    addi r25, r3, lbl_80495994@l
    b fn_80133E64_L_801340D0
    fn_80133E64_L_8013400C:
    lwz r4, 0x10(r26)
    lwz r3, 0xc(r26)
    lwz r0, 0x0(r31)
    slwi r4, r4, 2
    slwi r3, r3, 2
    lfsx f31, r24, r4
    cmpwi r0, 0x0
    lfsx f1, r25, r3
    blt fn_80133E64_L_80134038
    li r0, 0x0
    b fn_80133E64_L_80134080
    fn_80133E64_L_80134038:
    lfs f0, lbl_806D72F0(r2)
    li r0, 0x0
    stw r0, 0x0(r31)
    fmuls f30, f0, f1
    fmr f1, f30
    bl LUT_Sin12Bit
    lfs f2, lbl_806D72EC(r2)
    lfs f0, lbl_806D729C(r2)
    fmuls f2, f2, f1
    fmuls f0, f0, f31
    fmr f1, f30
    stfs f2, 0x4(r31)
    stfs f0, 0x8(r31)
    bl fn_80186960
    lfs f0, lbl_806D72EC(r2)
    li r0, 0x1
    fmuls f0, f0, f1
    stfs f0, 0xc(r31)
    fn_80133E64_L_80134080:
    clrlwi r0, r0, 24
    cmplwi r0, 0x1
    bne fn_80133E64_L_801340C8
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
    b fn_80133E64_L_801340DC
    fn_80133E64_L_801340C8:
    addi r31, r31, 0x10
    addi r29, r29, 0x1
    fn_80133E64_L_801340D0:
    lwz r0, 0x89c(r26)
    cmpw r29, r0
    blt fn_80133E64_L_8013400C
    fn_80133E64_L_801340DC:
    lwz r3, 0xc(r26)
    addi r0, r3, 0x1
    cmpwi r0, 0x40
    stw r0, 0xc(r26)
    blt fn_80133E64_L_801340F8
    li r0, 0x0
    stw r0, 0xc(r26)
    fn_80133E64_L_801340F8:
    lwz r3, 0x10(r26)
    addi r0, r3, 0x1
    cmpwi r0, 0x30
    stw r0, 0x10(r26)
    blt fn_80133E64_L_80134114
    li r0, 0x0
    stw r0, 0x10(r26)
    fn_80133E64_L_80134114:
    lwz r3, 0x1c(r30)
    addi r0, r3, 0x1
    cmpwi r0, 0x46
    stw r0, 0x1c(r30)
    blt fn_80133E64_L_80134130
    li r0, 0x0
    stw r0, 0x14(r30)
    fn_80133E64_L_80134130:
    addi r27, r27, 0x1
    addi r30, r30, 0x16c
    cmpwi r27, 0x6
    blt fn_80133E64_L_80133E90
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

extern "C" ModelPair *fn_80134164(ModelPair *self, short flag)
{
    if (self) {
        self->vt = lbl_8048E418;
        if (self) {
            self->vt = lbl_8048E34C;
            Object_DtorWithGXSync(self->a, 1);
            Object_DtorWithGXSync(self->b, 1);
        }
        if (flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}

