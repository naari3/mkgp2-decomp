/*
 * 0x8012BF5C..0x801313D0: coin game, boss Koopa, shells and coin particles.
 */
#pragma cplusplus on

extern "C" {
extern void Archive_GetRootJObj();
extern void CObj_DebugVizPathFlush();
extern void CObj_GetProjMatrix_Cached();
extern void CourseEnvironment_RenderObjects_Timed();
extern void DrawEffect_TickAndCull();
extern void GXChannel_Init();
extern void GXChannel_PushTransform();
extern void GetCourseScene3D();
extern void HSD_JObjGetDObj();
extern void ItemObjectManager_Render();
extern void KartItem_DispatchEffectRenderByState();
extern void KartItem_FlushPendingRender_v2();
extern void Object_DriveAnimMatrix();
extern void Object_RenderJObjIfWithinRange();
extern void Object_RenderJObjTree();
extern void Object_SetAnimBinding();
extern void Object_SetColorAlphaOnly();
extern void PSMTXConcat();
extern void PSMTXRotRad();
extern void PSMTXScale();
extern void Subsystem36c_DispatchPass2_Timed();
extern void Subsystem36c_DispatchPass4_Timed();
extern void TransitionEffect_RenderPass();
extern void TransparentDraw_SortAndDispatch();
extern void clDrawMan_Buckets_Dispatch();
extern void clDrawMan_Buckets_Reset();
extern void clDrawMan_EndFrame_NoOp();
extern void dtor_8007D9C4();
extern void fn_8012A61C();
extern void fn_8016B0C4();
extern void fn_8016DA30();
extern void fn_8016EACC();
extern void fn_8017218C();
extern unsigned int lbl_806CF58C;
extern unsigned int lbl_806CF590;
extern unsigned int lbl_806CF594;
extern unsigned int lbl_806CF598;
extern unsigned int lbl_806D109C;
extern unsigned int lbl_806D10AC;
extern unsigned int lbl_806D7138;
extern unsigned int lbl_806D7140;
extern unsigned int lbl_806D7150;
extern unsigned int lbl_806D7154;
extern unsigned int lbl_806D7158;
extern void HSD_StateInvalidate();
extern void fn_80253448();
extern void fn_802535D4();
extern unsigned int lbl_806DC1B8;
extern void CObj_ApplyScissor();
extern void CObj_ApplyViewport();
extern void CObj_LoadIntoGX();
extern void CObj_LoadProjMatrix();
extern void ChallengeGoalCamera_Update();
extern void Cosf_LUT_Wrap();
extern void CourseEnvironment_UpdateAndCullZones_Timed();
extern void DebugPrintf();
extern void Fog_UpdateFromCourseScene3D();
extern void GetDisplayBufferIndex();
extern void GetInputManager();
extern void GetRaceContextPtr();
extern void HSD_JObjSetMtxDirtySub();
extern void HSD_JObjSetupMatrixSub();
extern void HUD_FrameUpdate();
extern void InputCmd_GetDetectedFlag();
extern void InputCmd_PushSample();
extern void InputCmd_TickAndDetectAndClear();
extern void InputMgr_GetPlayer();
extern void Input_IsItemButtonPressed();
extern void IsCardValid();
extern void IsRaceStarted();
extern void ItemEffectBus_ApplyItemEventClear();
extern void ItemEffectBus_ApplyItemEventSet();
extern void ItemEffectBus_SnapshotAndFullReset();
extern void ItemEffectBus_TickTornadoCooldown();
extern void ItemObjectManager_PerFrameUpdate();
extern void ItemObjectManager_Update();
extern void LUT_Sin12Bit();
extern void LakituStart_UpdateCountdown();
extern void NokoNokoChallenge_CalcResultText();
extern void NokoNokoChallenge_GetCoinDivisor();
extern void NokoNokoChallenge_SaveResult();
extern void NokoNokoChallenge_TransitionToResult();
extern void Object_SetByte10_Return1();
extern void PSMTXCopy();
extern void PSMTXTrans();
extern void PSVECSquareMag();
extern void RenderObj_ItemStateMachine_Timed();
extern void RumbleUpdate();
extern void SetCoinCount();
extern void SetCourseScene3D();
extern void SetRumbleMode();
extern void Sinf_LUT_Wrap();
extern void SoundMgr_Play();
extern void SoundMgr_PlaySE();
extern void SoundObj_PlaySE();
extern void SoundObj_PlaySE_Direct();
extern void SoundVolumePan_Update();
extern void TornadoEffect_ApplyItemVisual_Primary();
extern void TornadoEffect_ApplyItemVisual_Secondary();
extern void TornadoEffect_ClearFlagC0AndSetC4();
extern void TornadoEffect_SetFlagC0();
extern void TornadoEffect_Tick();
extern void TransitionEffect_Tick();
extern void Vec3_Normalize();
extern void Vec3_Subtract();
extern void VfxSlotMgr_Update();
extern void __assert();
extern void fn_8012A71C();
extern void fn_8012B924();
extern void fn_8012B9AC();
extern void fn_8012BA38();
extern void fn_8012BAC4();
extern void fn_8012BB58();
extern void fn_8012BD2C();
extern void fn_8012BDA4();
extern void fn_801699D8();
extern void fn_8016B32C();
extern void fn_8016C360();
extern void fn_8016C394();
extern void fn_8016C554();
extern void fn_8016DA78();
extern void fn_8016DC90();
extern void fn_8016DEF4();
extern void fn_8016DF50();
extern void fn_8016EC80();
extern void fn_801734B0();
extern void fn_80173500();
extern void fn_8017351C();
extern void fn_80182B50();
extern void fn_80192688();
extern void fn_80253C40();
extern void fn_80253C74();
extern void fn_80253FD8();
extern unsigned int g_lakituStartAnimDone;
extern unsigned int g_pInputState;
extern unsigned int g_raceEnded;
extern unsigned int g_raceTimeRemaining;
extern unsigned int g_weatherSystem;
extern unsigned int lbl_806D7148;
extern unsigned int lbl_806D715C;
extern unsigned int lbl_806D7160;
extern unsigned int lbl_806D7164;
extern unsigned int lbl_806D7168;
extern unsigned int lbl_806D716C;
extern unsigned int lbl_806D7170;
extern unsigned int lbl_806D7184;
extern unsigned int lbl_806D7188;
extern unsigned int lbl_806D718C;
extern unsigned int lbl_806D7190;
extern unsigned int lbl_806D7194;
extern unsigned int lbl_806D7198;
extern unsigned int lbl_806D719C;
extern unsigned int lbl_806D71A0;
extern unsigned int lbl_806D71A4;
extern unsigned int lbl_806D71A8;
extern unsigned int lbl_806D71AC;
extern unsigned int lbl_806D71B0;
extern unsigned int lbl_806D71B4;
extern unsigned int lbl_806D71B8;
extern unsigned int lbl_806D71BC;
extern unsigned int lbl_806D71C0;
extern unsigned int lbl_806D71C4;
extern unsigned int lbl_806D71C8;
extern unsigned int lbl_806D71CC;
extern unsigned int lbl_806D71D0;
extern unsigned int lbl_806D71D4;
extern unsigned int lbl_806D71D8;
extern unsigned int lbl_806D71DC;
extern unsigned int lbl_806D71E0;
extern unsigned int lbl_806D71E4;
extern unsigned int lbl_806D71E8;
extern unsigned int lbl_806D71EC;
extern unsigned int lbl_806D71F0;
extern unsigned int lbl_806D71F4;
extern unsigned int lbl_806D71F8;
extern unsigned int lbl_806D71FC;
extern unsigned int lbl_806D7200;
extern unsigned int lbl_806D7204;
extern unsigned int lbl_806D7208;
extern unsigned int lbl_80356730[];
extern void HSD_CObjAnim();
extern void HSD_CObjReqAnim();
extern void HSD_JObjClearFlagsAll();
extern void HSD_JObjSetFlagsAll();
extern void Object_SetField8_AndDirty();
extern void Saturate_Double();
extern void clNormal3D_Exec();
extern unsigned int g_characterId;
extern unsigned int lbl_806D720C;
extern unsigned int lbl_806D7210;
extern unsigned int lbl_806D7214;
extern unsigned int lbl_806D7218;
extern unsigned int lbl_806D721C;
extern unsigned int lbl_806D7220;
extern unsigned int lbl_806D7224;
extern unsigned int lbl_806D7228;
extern unsigned int lbl_806D722C;
extern unsigned int lbl_80356C58[];
extern unsigned int lbl_806D7134;
extern unsigned int lbl_806D7234;
extern unsigned int lbl_806D7238;
extern unsigned int lbl_806D723C;
extern unsigned int lbl_806D7240;
extern unsigned int lbl_806D7244;
extern unsigned int lbl_806D7248;
extern unsigned int lbl_806D724C;
extern unsigned int lbl_806D7250;
extern unsigned int lbl_80495994[];
extern unsigned int lbl_80495A94[];
extern void PSMTXMultVec();
extern void Vec3_Dot();
extern unsigned int lbl_806CF578;
extern unsigned int lbl_806CF57C;
extern unsigned int lbl_806CF580;
extern unsigned int lbl_806CF584;
extern unsigned int lbl_806CF588;
extern unsigned int lbl_806D1510;
extern unsigned int lbl_806D7254;
extern unsigned int lbl_806D7258;
extern unsigned int lbl_806D725C;
extern void fn_80123480();
extern void fn_80172844();
extern unsigned int lbl_806D7260;
extern unsigned int lbl_806D7264;
extern void AudioChannel_DtorWithSeStop();
extern void ClRomTable_PurgeAll();
extern void CourseEnvironment_Dtor();
extern void InputCmd_Dtor();
extern void ItemObjectManager_Reset();
extern void KartDriver_Dtor();
extern void LakituStart_Dtor();
extern void MemoryManager_TimedFree();
extern void Object_DtorWithGXSync();
extern void RankingTable_Init();
extern void SceneDrawList_Reset();
extern void SetActiveCamera();
extern void SetPlayerCarObject();
extern void SetResourceLoadingFlag();
extern void VfxSlotMgr_Shutdown();
extern void VisualEffectHolder_Dtor();
extern void clRom_PurgeAll();
extern void dtor_80122FD8();
extern void fn_80123B48();
extern void fn_80124C84();
extern void fn_8012B394();
extern void fn_80169C44();
extern void fn_8016C634();
extern void fn_8016DFAC();
extern void fn_8016EFA8();
extern void fn_80173550();
extern void fn_80254134();
extern unsigned int g_raceCamera;
extern unsigned int lbl_806D10D0;
extern unsigned int vtable[];
extern void Alloc();
extern void ChallengeGoalCamera_Init();
extern void CourseEnvironment_ResolveJointInSlot0();
extern void CourseObjectManager_Init();
extern void DMAChannelManager_Init();
extern void DrawManager_GetOrCreate();
extern void GameMode_BaseInit();
extern void GetKartModelNameEntry();
extern void GetStartPosition();
extern void HSD_JObjSetFlags();
extern void HUD_Init();
extern void HUD_RegisterOverlay();
extern void InitRumbleController();
extern void InputCmd_Init();
extern void InputManager_Init();
extern void ItemObjectManager_Init();
extern void KartAudioChannel_Init();
extern void KartAudioChannel_ResetSEsAndSetFlag();
extern void KartDriver_New_Full();
extern void LakituStart_Init();
extern void MiniGame_GetCourseData();
extern void MiniGame_GetTimerValue();
extern void PreloadEffectResources();
extern void ProcessSystemTick();
extern void Scene3D_Init();
extern void SoundChannels_ClearAll();
extern void SoundDriver_GetOrCreate();
extern void StrPcb_ForceRun_Neutral();
extern void StrPcb_GetInstance();
extern void StrPcb_ResetCommands_Neutral();
extern void TireEffect_ResetSpin();
extern void TornadoEffect_Ctor();
extern void TornadoEffect_SetColorPairC8CC();
extern void TransitionEffect_GetOrCreate();
extern void WeatherSystem_Init();
extern void clNormal3D_Construct();
extern void clNormal3D_SetFlags();
extern void fn_80123BB4();
extern void fn_8012B48C();
extern void fn_8016E064();
extern void fn_8016F010();
extern void fn_8017363C();
extern unsigned int lbl_806D12BC;
extern unsigned int lbl_803FDF28[];
extern unsigned int lbl_803FDF40[];
extern unsigned int lbl_8048E144[];
extern unsigned int lbl_8048E34C[];
extern unsigned int lbl_8048E3C0[];
extern void HSD_CObjAddAnim();
extern void ResolveJointByName();
extern void clNormal3D_SetScale();
extern unsigned int lbl_80419EF8[];
extern void OSGetTick();
extern void Object_SetJObjPositionXYZ();
extern unsigned int lbl_806CF570;
extern unsigned int lbl_806CF574;
extern void PSMTXIdentity();
extern void LinkedNode_GetField10_OrFallback();
extern void Object_RenderJObjEx();
extern void Object_SetJObjPositionVec();
extern void Object_SetJObjRotationY();
extern void Object_SetJObjScaleXYZ();
extern unsigned int lbl_806D7130;
extern unsigned int lbl_806D713C;
extern void fn_80186960();
extern unsigned int lbl_806D7230;
extern void Clamp_Int();
extern void StrPcb_ResetCommands_Zero();
extern void abs();
extern unsigned int lbl_806D7268;
extern unsigned int lbl_806D726C;
extern unsigned int lbl_806D7270;
asm void fn_8012BF5C(void);
asm void CGameCoin_Draw(void);
asm void CGameCoin_Update(void);
asm void DefeatDemo_Update(void);
asm void BossKoopa_UpdateAnim(void);
asm void KoopaFireball_Update(void);
asm void Shell_UpdateState(void);
asm void CGameCoin_Destroy(void);
asm void CGameCoin_Init(void);
asm void CGameCoin_InitDefeatDemo(void);
asm void BossKoopa_Init(void);
asm void CGameCoin_InitFields(void);
asm void CoinParticle_Draw(void);
asm void CoinParticle_Update(void);
asm void CoinParticleManager_Destroy(void);
asm void CGameCoin_ProcessInput(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_fn_8012BF5C = { 0x288A0000, 0x000001C4, 0x003B0010, 0x00000000, 0x82000008, (void *)&dtor_8007D9C4 };

__declspec(section ".extab_user") static const unsigned char extab_CGameCoin_Draw[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_CGameCoin_Update[8] = {
    0x38, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_DefeatDemo_Update[8] = {
    0x10, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_BossKoopa_UpdateAnim[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_KoopaFireball_Update[8] = {
    0x18, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_Shell_UpdateState[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_CGameCoin_Destroy[8] = {
    0x28, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; unsigned int f29; unsigned int f30; unsigned int f31; unsigned int f32; unsigned int f33; unsigned int f34; unsigned int f35; unsigned int f36; unsigned int f37; unsigned int f38; unsigned int f39; unsigned int f40; unsigned int f41; unsigned int f42; unsigned int f43; unsigned int f44; unsigned int f45; unsigned int f46; unsigned int f47; unsigned int f48; unsigned int f49; unsigned int f50; unsigned int f51; unsigned int f52; unsigned int f53; unsigned int f54; unsigned int f55; unsigned int f56; unsigned int f57; unsigned int f58; unsigned int f59; unsigned int f60; unsigned int f61; unsigned int f62; unsigned int f63; unsigned int f64; unsigned int f65; unsigned int f66; unsigned int f67; unsigned int f68; unsigned int f69; unsigned int f70; unsigned int f71; unsigned int f72; unsigned int f73; unsigned int f74; unsigned int f75; unsigned int f76; unsigned int f77; unsigned int f78; unsigned int f79; unsigned int f80; unsigned int f81; unsigned int f82; unsigned int f83; unsigned int f84; unsigned int f85; unsigned int f86; unsigned int f87; unsigned int f88; unsigned int f89; unsigned int f90; void *f91; unsigned int f92; unsigned int f93; void *f94; unsigned int f95; void *f96; unsigned int f97; unsigned int f98; void *f99; unsigned int f100; void *f101; unsigned int f102; unsigned int f103; void *f104; unsigned int f105; void *f106; unsigned int f107; unsigned int f108; void *f109; unsigned int f110; void *f111; unsigned int f112; unsigned int f113; void *f114; unsigned int f115; void *f116; unsigned int f117; unsigned int f118; void *f119; unsigned int f120; void *f121; unsigned int f122; unsigned int f123; void *f124; unsigned int f125; void *f126; unsigned int f127; unsigned int f128; void *f129; unsigned int f130; void *f131; unsigned int f132; unsigned int f133; void *f134; unsigned int f135; void *f136; unsigned int f137; unsigned int f138; void *f139; unsigned int f140; void *f141; unsigned int f142; void *f143; unsigned int f144; unsigned int f145; void *f146; unsigned int f147; void *f148; unsigned int f149; unsigned int f150; void *f151; unsigned int f152; unsigned int f153; void *f154; unsigned int f155; unsigned int f156; void *f157; unsigned int f158; void *f159; unsigned int f160; unsigned int f161; void *f162; unsigned int f163; void *f164; unsigned int f165; unsigned int f166; void *f167; unsigned int f168; void *f169; unsigned int f170; unsigned int f171; void *f172; unsigned int f173; void *f174; unsigned int f175; void *f176; unsigned int f177; unsigned int f178; void *f179; unsigned int f180; void *f181; unsigned int f182; unsigned int f183; void *f184; unsigned int f185; unsigned int f186; void *f187; } extab_CGameCoin_Init = { 0x284A0000, 0x00000058, 0x000A0170, 0x0000008C, 0x00000168, 0x000000A8, 0x00020170, 0x000000C0, 0x0000017C, 0x000000C8, 0x000C0170, 0x00000108, 0x00080190, 0x00000140, 0x00000170, 0x00000168, 0x000001A4, 0x0000017C, 0x00060170, 0x000001B4, 0x000001B8, 0x000001C4, 0x00020170, 0x000001E0, 0x000001CC, 0x000001EC, 0x00000170, 0x0000020C, 0x000001E0, 0x00000218, 0x00000170, 0x0000022C, 0x000401F4, 0x00000248, 0x00000170, 0x00000254, 0x00000208, 0x00000260, 0x00020170, 0x00000278, 0x0000021C, 0x0000028C, 0x002A0170, 0x00000388, 0x00000238, 0x00000394, 0x00000230, 0x000003A0, 0x00000238, 0x000003B4, 0x0000024C, 0x000003C8, 0x00040238, 0x000003EC, 0x00000258, 0x000003FC, 0x00000170, 0x00000414, 0x00000264, 0x00000420, 0x00000170, 0x0000042C, 0x00000278, 0x00000438, 0x00000170, 0x00000444, 0x0000028C, 0x00000450, 0x00000170, 0x0000045C, 0x000002A0, 0x0000046C, 0x00130170, 0x000004E8, 0x000002BC, 0x000004FC, 0x000002B4, 0x00000510, 0x000202BC, 0x0000052C, 0x000002D0, 0x00000538, 0x000202BC, 0x00000698, 0x00000170, 0x000006A8, 0x000002DC, 0x000006B4, 0x00250170, 0x00000000, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x01000238, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x01000238, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x010002BC, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8 };

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; void *f15; unsigned int f16; void *f17; unsigned int f18; void *f19; unsigned int f20; void *f21; unsigned int f22; void *f23; unsigned int f24; void *f25; } extab_CGameCoin_InitDefeatDemo = { 0x180A0000, 0x00000090, 0x00000038, 0x000000B0, 0x00000040, 0x000000D4, 0x00000048, 0x000000F4, 0x00000050, 0x00000114, 0x00000058, 0x00000184, 0x00000060, 0x00000000, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree };

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; void *f23; unsigned int f24; void *f25; unsigned int f26; void *f27; unsigned int f28; void *f29; unsigned int f30; void *f31; unsigned int f32; void *f33; unsigned int f34; void *f35; unsigned int f36; void *f37; unsigned int f38; void *f39; unsigned int f40; void *f41; } extab_BossKoopa_Init = { 0x200A0000, 0x000001AC, 0x00000060, 0x000001C0, 0x00000058, 0x000001F0, 0x00000068, 0x00000210, 0x00000070, 0x00000230, 0x00000078, 0x00000250, 0x00000080, 0x00000294, 0x00000088, 0x000002B4, 0x00000090, 0x000002D4, 0x00000098, 0x000002F4, 0x000000A0, 0x00000000, 0x0A80001E, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree };

__declspec(section ".extab_user") static const unsigned char extab_CGameCoin_InitFields[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_CoinParticle_Draw[8] = {
    0x31, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_CoinParticle_Update[8] = {
    0x40, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_CoinParticleManager_Destroy[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_CGameCoin_ProcessInput[8] = {
    0x38, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8012BF5C = {
    (void *)&fn_8012BF5C, 0x00000370, (void *)&extab_fn_8012BF5C
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CGameCoin_Draw = {
    (void *)&CGameCoin_Draw, 0x0000026C, (void *)extab_CGameCoin_Draw
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CGameCoin_Update = {
    (void *)&CGameCoin_Update, 0x00002164, (void *)extab_CGameCoin_Update
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_DefeatDemo_Update = {
    (void *)&DefeatDemo_Update, 0x000005A8, (void *)extab_DefeatDemo_Update
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_BossKoopa_UpdateAnim = {
    (void *)&BossKoopa_UpdateAnim, 0x00000438, (void *)extab_BossKoopa_UpdateAnim
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KoopaFireball_Update = {
    (void *)&KoopaFireball_Update, 0x000003E0, (void *)extab_KoopaFireball_Update
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Shell_UpdateState = {
    (void *)&Shell_UpdateState, 0x00000458, (void *)extab_Shell_UpdateState
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CGameCoin_Destroy = {
    (void *)&CGameCoin_Destroy, 0x000003A4, (void *)extab_CGameCoin_Destroy
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CGameCoin_Init = {
    (void *)&CGameCoin_Init, 0x0000078C, (void *)&extab_CGameCoin_Init
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CGameCoin_InitDefeatDemo = {
    (void *)&CGameCoin_InitDefeatDemo, 0x000002A8, (void *)&extab_CGameCoin_InitDefeatDemo
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_BossKoopa_Init = {
    (void *)&BossKoopa_Init, 0x000003FC, (void *)&extab_BossKoopa_Init
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CGameCoin_InitFields = {
    (void *)&CGameCoin_InitFields, 0x000000D4, (void *)extab_CGameCoin_InitFields
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CoinParticle_Draw = {
    (void *)&CoinParticle_Draw, 0x000001D0, (void *)extab_CoinParticle_Draw
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CoinParticle_Update = {
    (void *)&CoinParticle_Update, 0x000002B0, (void *)extab_CoinParticle_Update
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CoinParticleManager_Destroy = {
    (void *)&CoinParticleManager_Destroy, 0x00000080, (void *)extab_CoinParticleManager_Destroy
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CGameCoin_ProcessInput = {
    (void *)&CGameCoin_ProcessInput, 0x00000374, (void *)extab_CGameCoin_ProcessInput
};

}


extern "C" asm void fn_8012BF5C(void) { /* 0x8012BF5C size:0x370 */
    nofralloc
    stwu r1, -0xc0(r1)
    mflr r0
    stw r0, 0xc4(r1)
    stfd f31, 0xb0(r1)
    psq_st f31, 0xb8(r1), 0, 0
    stfd f30, 0xa0(r1)
    psq_st f30, 0xa8(r1), 0, 0
    stmw r27, 0x8c(r1)
    mr r31, r3
    lwz r3, 0x58(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne fn_8012BF5C_L_8012C2A8
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne fn_8012BF5C_L_8012BFB0
    li r3, 0x0
    fn_8012BF5C_L_8012BFB0:
    bl clDrawMan_Buckets_Reset
    bl TransparentDraw_SortAndDispatch
    lwz r3, 0x58(r31)
    bl CObj_DebugVizPathFlush
    bl fn_8016B0C4
    lwz r3, 0x10(r31)
    bl KartItem_DispatchEffectRenderByState
    lwz r3, 0x48(r31)
    bl fn_8012A61C
    lwz r3, 0x10(r31)
    bl KartItem_FlushPendingRender_v2
    lwz r3, 0x50(r31)
    bl Object_RenderJObjIfWithinRange
    lwz r3, 0x54(r31)
    bl CourseEnvironment_RenderObjects_Timed
    lwz r3, 0x70(r31)
    bl fn_8016DA30
    lwz r3, 0x54(r31)
    bl Subsystem36c_DispatchPass2_Timed
    lwz r3, 0xc0(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lwz r30, 0x4c(r31)
    lwz r0, 0x8(r30)
    cmpwi r0, 0x0
    beq fn_8012BF5C_L_8012C070
    lfs f1, 0x40(r30)
    lfs f0, lbl_806D7150(r2)
    fcmpo cr0, f1, f0
    cror eq, lt, eq
    beq fn_8012BF5C_L_8012C070
    lwz r3, 0x4(r30)
    addi r4, r30, 0x10
    li r5, 0x0
    bl Object_SetAnimBinding
    lwz r3, 0x4(r30)
    bl Object_DriveAnimMatrix
    lwz r3, 0x4(r30)
    li r4, 0x0
    lfs f1, 0x40(r30)
    bl Object_SetColorAlphaOnly
    lwz r3, 0x4(r30)
    li r4, 0x7
    bl Object_RenderJObjTree
    lwz r3, 0x0(r30)
    bl fn_8017218C
    fn_8012BF5C_L_8012C070:
    bl ItemObjectManager_Render
    lwz r30, 0x6c(r31)
    lwz r0, 0x10(r30)
    cmpwi r0, 0x4
    bge fn_8012BF5C_L_8012C228
    slwi r0, r0, 2
    li r4, 0x7
    lwzx r3, r30, r0
    bl Object_RenderJObjTree
    lwz r28, 0x28(r30)
    lwz r0, 0x4(r28)
    cmplwi r0, 0x0
    beq fn_8012BF5C_L_8012C228
    bl GetCourseScene3D
    bl CObj_GetProjMatrix_Cached
    mr r29, r3
    lwz r3, 0x0(r28)
    bl Archive_GetRootJObj
    bl HSD_JObjGetDObj
    mr r30, r3
    lwz r3, 0x0(r28)
    bl Archive_GetRootJObj
    mr r4, r3
    mr r5, r30
    addi r3, r1, 0x8
    lis r6, 0x4000
    li r7, 0x1
    bl GXChannel_Init
    lfs f31, lbl_806D7150(r2)
    mr r27, r28
    li r30, 0x0
    fn_8012BF5C_L_8012C0EC:
    lfs f0, 0x2c(r27)
    fcmpo cr0, f0, f31
    blt fn_8012BF5C_L_8012C20C
    lfs f1, 0x48(r27)
    addi r3, r1, 0x1c
    lfs f0, lbl_806CF58C(r13)
    lfs f2, 0x4c(r27)
    fmuls f1, f1, f0
    lfs f0, lbl_806CF590(r13)
    lfs f3, lbl_806D7140(r2)
    fmuls f30, f2, f0
    fmr f2, f1
    bl PSMTXScale
    addi r3, r1, 0x1c
    mr r4, r29
    mr r5, r3
    bl PSMTXConcat
    lfs f1, lbl_806D7154(r2)
    addi r3, r1, 0x4c
    li r4, 0x58
    bl PSMTXRotRad
    addi r3, r1, 0x1c
    addi r4, r1, 0x4c
    mr r5, r3
    bl PSMTXConcat
    lfs f0, 0x3c(r27)
    fmr f1, f30
    li r4, 0x0
    stfs f0, 0x28(r1)
    lfs f0, 0x40(r27)
    stfs f0, 0x38(r1)
    lfs f0, 0x44(r27)
    stfs f0, 0x48(r1)
    lwz r3, 0x0(r28)
    bl Object_SetColorAlphaOnly
    addi r3, r1, 0x8
    addi r4, r1, 0x1c
    bl GXChannel_PushTransform
    lfs f1, 0x48(r27)
    lfs f0, lbl_806CF594(r13)
    lfs f3, 0x4c(r27)
    lfs f2, lbl_806CF598(r13)
    fmuls f1, f1, f0
    lfs f4, 0x2c(r27)
    lfs f0, lbl_806D7138(r2)
    fmuls f30, f3, f2
    fcmpo cr0, f4, f0
    bge fn_8012BF5C_L_8012C1B8
    lfs f0, lbl_806D7158(r2)
    fmuls f0, f0, f4
    fmuls f30, f30, f0
    fn_8012BF5C_L_8012C1B8:
    fmr f2, f1
    lfs f3, lbl_806D7140(r2)
    addi r3, r1, 0x1c
    bl PSMTXScale
    addi r3, r1, 0x1c
    mr r4, r29
    mr r5, r3
    bl PSMTXConcat
    lfs f0, 0x3c(r27)
    fmr f1, f30
    li r4, 0x0
    stfs f0, 0x28(r1)
    lfs f0, 0x40(r27)
    stfs f0, 0x38(r1)
    lfs f0, 0x44(r27)
    stfs f0, 0x48(r1)
    lwz r3, 0x0(r28)
    bl Object_SetColorAlphaOnly
    addi r3, r1, 0x8
    addi r4, r1, 0x1c
    bl GXChannel_PushTransform
    fn_8012BF5C_L_8012C20C:
    addi r30, r30, 0x1
    addi r27, r27, 0x28
    cmpwi r30, 0x40
    blt fn_8012BF5C_L_8012C0EC
    addi r3, r1, 0x8
    li r4, -0x1
    bl dtor_8007D9C4
    fn_8012BF5C_L_8012C228:
    bl DrawEffect_TickAndCull
    lwz r3, 0x74(r31)
    bl fn_8016EACC
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne fn_8012BF5C_L_8012C244
    li r3, 0x0
    fn_8012BF5C_L_8012C244:
    bl clDrawMan_EndFrame_NoOp
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne fn_8012BF5C_L_8012C258
    li r3, 0x0
    fn_8012BF5C_L_8012C258:
    bl clDrawMan_Buckets_Dispatch
    lwz r3, 0x54(r31)
    bl Subsystem36c_DispatchPass4_Timed
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne fn_8012BF5C_L_8012C274
    li r3, 0x0
    fn_8012BF5C_L_8012C274:
    li r4, 0x2
    bl TransitionEffect_RenderPass
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne fn_8012BF5C_L_8012C28C
    li r3, 0x0
    fn_8012BF5C_L_8012C28C:
    li r4, 0x4
    bl TransitionEffect_RenderPass
    lwz r3, 0x58(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    fn_8012BF5C_L_8012C2A8:
    psq_l f31, 0xb8(r1), 0, 0
    lfd f31, 0xb0(r1)
    psq_l f30, 0xa8(r1), 0, 0
    lfd f30, 0xa0(r1)
    lmw r27, 0x8c(r1)
    lwz r0, 0xc4(r1)
    mtlr r0
    addi r1, r1, 0xc0
    blr
}

extern "C" asm void CGameCoin_Draw(void) { /* 0x8012C2CC size:0x26C */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    stw r30, 0x8(r1)
    lbz r0, 0x7c(r3)
    cmplwi r0, 0x0
    beq CGameCoin_Draw_L_8012C520
    lbz r0, 0x7e(r31)
    cmplwi r0, 0x0
    bne CGameCoin_Draw_L_8012C304
    bl fn_8012BF5C
    b CGameCoin_Draw_L_8012C4EC
    CGameCoin_Draw_L_8012C304:
    lbz r0, 0x7f(r31)
    cmplwi r0, 0x0
    beq CGameCoin_Draw_L_8012C414
    lwz r3, 0x78(r31)
    lwz r3, 0xc(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CGameCoin_Draw_L_8012C4EC
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne CGameCoin_Draw_L_8012C344
    li r3, 0x0
    CGameCoin_Draw_L_8012C344:
    bl clDrawMan_Buckets_Reset
    bl TransparentDraw_SortAndDispatch
    lwz r3, 0x78(r31)
    lwz r3, 0xc(r3)
    bl CObj_DebugVizPathFlush
    bl fn_8016B0C4
    lwz r30, 0x78(r31)
    li r4, 0x7
    lwz r3, 0x0(r30)
    bl Object_RenderJObjTree
    lwz r3, 0x4(r30)
    li r4, 0x7
    bl Object_RenderJObjTree
    lwz r3, 0x8(r30)
    li r4, 0x7
    bl Object_RenderJObjTree
    lwz r3, 0x74(r31)
    bl fn_8016EACC
    lwz r3, 0xc0(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne CGameCoin_Draw_L_8012C3B0
    li r3, 0x0
    CGameCoin_Draw_L_8012C3B0:
    bl clDrawMan_EndFrame_NoOp
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne CGameCoin_Draw_L_8012C3C4
    li r3, 0x0
    CGameCoin_Draw_L_8012C3C4:
    bl clDrawMan_Buckets_Dispatch
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne CGameCoin_Draw_L_8012C3D8
    li r3, 0x0
    CGameCoin_Draw_L_8012C3D8:
    li r4, 0x2
    bl TransitionEffect_RenderPass
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne CGameCoin_Draw_L_8012C3F0
    li r3, 0x0
    CGameCoin_Draw_L_8012C3F0:
    li r4, 0x4
    bl TransitionEffect_RenderPass
    lwz r3, 0x78(r31)
    lwz r3, 0xc(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    b CGameCoin_Draw_L_8012C4EC
    CGameCoin_Draw_L_8012C414:
    lwz r3, 0x58(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CGameCoin_Draw_L_8012C4EC
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne CGameCoin_Draw_L_8012C444
    li r3, 0x0
    CGameCoin_Draw_L_8012C444:
    bl clDrawMan_Buckets_Reset
    bl TransparentDraw_SortAndDispatch
    lwz r3, 0x58(r31)
    bl CObj_DebugVizPathFlush
    bl fn_8016B0C4
    lwz r3, 0x48(r31)
    bl fn_8012A61C
    lwz r3, 0x50(r31)
    bl Object_RenderJObjIfWithinRange
    lwz r3, 0x54(r31)
    bl CourseEnvironment_RenderObjects_Timed
    lwz r3, 0x54(r31)
    bl Subsystem36c_DispatchPass2_Timed
    lwz r3, 0x74(r31)
    bl fn_8016EACC
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne CGameCoin_Draw_L_8012C490
    li r3, 0x0
    CGameCoin_Draw_L_8012C490:
    bl clDrawMan_EndFrame_NoOp
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne CGameCoin_Draw_L_8012C4A4
    li r3, 0x0
    CGameCoin_Draw_L_8012C4A4:
    bl clDrawMan_Buckets_Dispatch
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne CGameCoin_Draw_L_8012C4B8
    li r3, 0x0
    CGameCoin_Draw_L_8012C4B8:
    li r4, 0x2
    bl TransitionEffect_RenderPass
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne CGameCoin_Draw_L_8012C4D0
    li r3, 0x0
    CGameCoin_Draw_L_8012C4D0:
    li r4, 0x4
    bl TransitionEffect_RenderPass
    lwz r3, 0x58(r31)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    CGameCoin_Draw_L_8012C4EC:
    lwz r3, 0x68(r31)
    lwz r4, lbl_806DC1B8(r2)
    bl fn_80253448
    lwz r3, 0x68(r31)
    bl fn_802535D4
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne CGameCoin_Draw_L_8012C510
    li r3, 0x0
    CGameCoin_Draw_L_8012C510:
    li r4, 0x1
    bl TransitionEffect_RenderPass
    li r3, 0x7f
    bl HSD_StateInvalidate
    CGameCoin_Draw_L_8012C520:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void CGameCoin_Update(void) { /* 0x8012C538 size:0x2164 */
    nofralloc
    stwu r1, -0x1c0(r1)
    mflr r0
    stw r0, 0x1c4(r1)
    stfd f31, 0x1b0(r1)
    psq_st f31, 0x1b8(r1), 0, 0
    stfd f30, 0x1a0(r1)
    psq_st f30, 0x1a8(r1), 0, 0
    stfd f29, 0x190(r1)
    psq_st f29, 0x198(r1), 0, 0
    stmw r25, 0x174(r1)
    mr r28, r3
    lis r3, lbl_80356730@ha
    lbz r0, 0x7c(r28)
    addi r31, r3, lbl_80356730@l
    cmplwi r0, 0x0
    bne CGameCoin_Update_L_8012C580
    li r0, 0x1
    stb r0, 0x7c(r28)
    CGameCoin_Update_L_8012C580:
    bl IsRaceStarted
    clrlwi. r0, r3, 24
    bne CGameCoin_Update_L_8012C5AC
    lbz r0, 0x7d(r28)
    cmplwi r0, 0x0
    bne CGameCoin_Update_L_8012C5CC
    li r3, 0x33
    bl SoundMgr_Play
    li r0, 0x1
    stb r0, 0x7d(r28)
    b CGameCoin_Update_L_8012C5CC
    CGameCoin_Update_L_8012C5AC:
    lbz r0, 0x7d(r28)
    cmplwi r0, 0x1
    bne CGameCoin_Update_L_8012C5CC
    li r3, 0x33
    li r4, 0x1
    bl fn_80192688
    li r0, 0x0
    stb r0, 0x7d(r28)
    CGameCoin_Update_L_8012C5CC:
    lwz r3, g_pInputState(r13)
    cmplwi r3, 0x0
    bne CGameCoin_Update_L_8012C5DC
    li r3, 0x0
    CGameCoin_Update_L_8012C5DC:
    bl CGameCoin_ProcessInput
    bl GetRaceContextPtr
    bl ItemObjectManager_PerFrameUpdate
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lfs f1, lbl_806D7150(r2)
    mr r30, r3
    lfs f0, lbl_806D715C(r2)
    stfs f1, 0x74(r1)
    stfs f1, 0x78(r1)
    stfs f0, 0x7c(r1)
    lbz r0, 0x7e(r28)
    cmplwi r0, 0x0
    bne CGameCoin_Update_L_8012D880
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lwz r3, 0xc(r28)
    fmr f31, f1
    lwz r3, 0x304(r3)
    bl ItemEffectBus_SnapshotAndFullReset
    bl IsRaceStarted
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012D3BC
    lfs f0, 0x94(r28)
    li r29, 0x0
    lfs f1, lbl_806D7150(r2)
    fcmpo cr0, f0, f1
    cror eq, gt, eq
    beq CGameCoin_Update_L_8012C67C
    lfs f0, 0x98(r28)
    fcmpo cr0, f0, f1
    cror eq, gt, eq
    beq CGameCoin_Update_L_8012C67C
    lwz r3, 0x88(r28)
    lwz r0, 0x8c(r28)
    cmpw r3, r0
    beq CGameCoin_Update_L_8012C680
    CGameCoin_Update_L_8012C67C:
    li r29, 0x1
    CGameCoin_Update_L_8012C680:
    mr r3, r30
    lwz r12, 0x0(r30)
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl
    mr r3, r30
    fmr f29, f1
    lwz r12, 0x0(r30)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    mr r3, r30
    fmr f30, f1
    lwz r12, 0x0(r30)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lfs f5, lbl_806D7160(r2)
    lis r0, 0x4330
    stw r0, 0x148(r1)
    li r4, 0x0
    fmuls f2, f5, f1
    lfd f4, lbl_806D7148(r2)
    fmuls f1, f5, f30
    stw r0, 0x158(r1)
    fmuls f0, f5, f29
    lwz r3, 0x8(r28)
    fctiwz f2, f2
    stw r0, 0x168(r1)
    fctiwz f1, f1
    fctiwz f0, f0
    stfd f2, 0x140(r1)
    stfd f1, 0x150(r1)
    lwz r0, 0x144(r1)
    stfd f0, 0x160(r1)
    lwz r5, 0x154(r1)
    xoris r6, r0, 0x8000
    lwz r0, 0x164(r1)
    xoris r5, r5, 0x8000
    stw r6, 0x14c(r1)
    xoris r0, r0, 0x8000
    stw r5, 0x15c(r1)
    lfd f0, 0x148(r1)
    stw r0, 0x16c(r1)
    lfd f1, 0x158(r1)
    fsubs f3, f0, f4
    lfd f0, 0x168(r1)
    fsubs f2, f1, f4
    fsubs f0, f0, f4
    fdivs f1, f3, f5
    fdivs f2, f2, f5
    fdivs f3, f0, f5
    bl InputCmd_PushSample
    lwz r3, 0x8(r28)
    bl InputCmd_TickAndDetectAndClear
    lwz r3, 0x4c(r28)
    bl Shell_UpdateState
    lwz r27, 0x4c(r28)
    lwz r4, 0x8(r27)
    cmpwi r4, 0x2
    beq CGameCoin_Update_L_8012C864
    bge CGameCoin_Update_L_8012C788
    cmpwi r4, 0x0
    beq CGameCoin_Update_L_8012C798
    bge CGameCoin_Update_L_8012C82C
    b CGameCoin_Update_L_8012D28C
    CGameCoin_Update_L_8012C788:
    cmpwi r4, 0x4
    beq CGameCoin_Update_L_8012CC00
    bge CGameCoin_Update_L_8012D28C
    b CGameCoin_Update_L_8012C9EC
    CGameCoin_Update_L_8012C798:
    lwz r3, 0x9c(r28)
    cmpwi r3, 0x0
    ble CGameCoin_Update_L_8012C7B0
    subi r0, r3, 0x1
    stw r0, 0x9c(r28)
    b CGameCoin_Update_L_8012D28C
    CGameCoin_Update_L_8012C7B0:
    cmpwi r4, 0x0
    bne CGameCoin_Update_L_8012D28C
    li r0, 0x1
    lfs f1, lbl_806D7150(r2)
    stw r0, 0x8(r27)
    addi r3, r27, 0x10
    lfs f0, lbl_806D7140(r2)
    li r4, 0x59
    stfs f1, 0xc(r27)
    lfs f1, lbl_806D7164(r2)
    stfs f0, 0x40(r27)
    bl PSMTXRotRad
    lfs f1, lbl_806D7168(r2)
    addi r3, r1, 0xe0
    fmr f2, f1
    fmr f3, f1
    bl PSMTXScale
    addi r3, r27, 0x10
    addi r4, r1, 0xe0
    mr r5, r3
    bl PSMTXConcat
    addi r3, r31, 0x454
    lfs f2, 0x454(r31)
    lfs f1, lbl_806D716C(r2)
    lfs f0, 0x4(r3)
    stfs f2, 0x1c(r27)
    fadds f1, f1, f0
    lfs f0, 0x8(r3)
    stfs f1, 0x2c(r27)
    stfs f0, 0x3c(r27)
    b CGameCoin_Update_L_8012D28C
    CGameCoin_Update_L_8012C82C:
    lfs f1, lbl_806D7170(r2)
    lfs f0, 0x34(r28)
    lfs f2, 0x2c(r27)
    fadds f0, f1, f0
    fcmpo cr0, f2, f0
    bge CGameCoin_Update_L_8012D28C
    cmpwi r4, 0x1
    bne CGameCoin_Update_L_8012D28C
    li r0, 0x2
    lfs f0, lbl_806D7150(r2)
    stw r0, 0x8(r27)
    stfs f0, 0xc(r27)
    stfs f0, 0x40(r27)
    b CGameCoin_Update_L_8012D28C
    CGameCoin_Update_L_8012C864:
    lwz r3, 0x48(r28)
    bl fn_8012BA38
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012D28C
    lwz r30, 0x4c(r28)
    addi r5, r31, 0x460
    lwz r3, 0x8c(r28)
    lwz r0, 0x8(r30)
    mulli r3, r3, 0xc
    cmpwi r0, 0x2
    add r5, r5, r3
    bne CGameCoin_Update_L_8012C9C4
    lfs f0, 0x0(r5)
    addi r4, r30, 0x50
    lfs f1, 0x4(r5)
    stfs f0, 0x50(r30)
    lfs f0, 0x8(r5)
    stfs f1, 0x54(r30)
    stfs f0, 0x58(r30)
    lwz r3, 0x0(r30)
    bl fn_801734B0
    lwz r3, 0x0(r30)
    bl fn_8017351C
    li r0, 0x3
    lfs f0, lbl_806D7150(r2)
    stw r0, 0x8(r30)
    stfs f0, 0xc(r30)
    stfs f0, 0x40(r30)
    lwz r27, 0x44(r30)
    cmplwi r27, 0x0
    beq CGameCoin_Update_L_8012C9C4
    bne CGameCoin_Update_L_8012C8F4
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x47c
    addi r5, r2, -0x30E4  /* lbl_806D717C */
    bl __assert
    CGameCoin_Update_L_8012C8F4:
    cmplwi r27, 0x0
    beq CGameCoin_Update_L_8012C93C
    bne CGameCoin_Update_L_8012C910
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x25d
    addi r5, r2, -0x30E4  /* lbl_806D717C */
    bl __assert
    CGameCoin_Update_L_8012C910:
    lwz r4, 0x14(r27)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne CGameCoin_Update_L_8012C92C
    rlwinm. r0, r4, 0, 25, 25
    beq CGameCoin_Update_L_8012C92C
    li r3, 0x1
    CGameCoin_Update_L_8012C92C:
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012C93C
    mr r3, r27
    bl HSD_JObjSetupMatrixSub
    CGameCoin_Update_L_8012C93C:
    addi r27, r27, 0x44
    addi r4, r30, 0x10
    mr r3, r27
    bl PSMTXCopy
    lfs f1, lbl_806D7164(r2)
    addi r3, r1, 0xb0
    li r4, 0x5a
    bl PSMTXRotRad
    addi r3, r30, 0x10
    addi r4, r1, 0xb0
    mr r5, r3
    bl PSMTXConcat
    lfs f1, lbl_806D7140(r2)
    addi r3, r1, 0xb0
    fmr f2, f1
    fmr f3, f1
    bl PSMTXScale
    addi r3, r30, 0x10
    addi r4, r1, 0xb0
    mr r5, r3
    bl PSMTXConcat
    lfs f2, lbl_806D7184(r2)
    lfs f1, 0x14(r30)
    lfs f0, 0xc(r27)
    fmadds f0, f2, f1, f0
    stfs f0, 0x1c(r30)
    lfs f1, 0x24(r30)
    lfs f0, 0x1c(r27)
    fmadds f0, f2, f1, f0
    stfs f0, 0x2c(r30)
    lfs f1, 0x34(r30)
    lfs f0, 0x2c(r27)
    fmadds f0, f2, f1, f0
    stfs f0, 0x3c(r30)
    CGameCoin_Update_L_8012C9C4:
    lwz r5, 0x84(r28)
    li r3, 0x0
    li r4, 0x1
    lwz r0, 0x0(r5)
    stw r0, 0x9c(r28)
    bl fn_801699D8
    li r3, 0x1
    li r4, 0x1
    bl fn_801699D8
    b CGameCoin_Update_L_8012D28C
    CGameCoin_Update_L_8012C9EC:
    clrlwi. r0, r29, 24
    bne CGameCoin_Update_L_8012D28C
    cmpwi r4, 0x3
    bne CGameCoin_Update_L_8012CA18
    lfs f1, 0xc(r27)
    lfs f0, lbl_806D7188(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne CGameCoin_Update_L_8012CA18
    li r0, 0x1
    b CGameCoin_Update_L_8012CA1C
    CGameCoin_Update_L_8012CA18:
    li r0, 0x0
    CGameCoin_Update_L_8012CA1C:
    clrlwi. r0, r0, 24
    beq CGameCoin_Update_L_8012D28C
    mr r3, r30
    lis r4, 0x1
    lwz r12, 0x0(r30)
    subi r4, r4, 0x1c01
    lwz r12, 0x28(r12)
    mtctr r12
    bctrl
    bl Input_IsItemButtonPressed
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012D28C
    lwz r3, 0x48(r28)
    bl fn_8012B9AC
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012D28C
    li r3, 0x0
    li r4, 0x0
    bl fn_801699D8
    li r3, 0x1
    li r4, 0x0
    bl fn_801699D8
    li r3, 0x0
    li r4, 0x4
    li r5, 0x1e
    bl SetRumbleMode
    li r3, 0x68
    bl SoundMgr_PlaySE
    lwz r29, 0x4c(r28)
    lwz r0, 0x8(r29)
    cmpwi r0, 0x3
    bne CGameCoin_Update_L_8012CAB8
    lfs f1, 0xc(r29)
    lfs f0, lbl_806D7188(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne CGameCoin_Update_L_8012CAB8
    li r0, 0x1
    b CGameCoin_Update_L_8012CABC
    CGameCoin_Update_L_8012CAB8:
    li r0, 0x0
    CGameCoin_Update_L_8012CABC:
    clrlwi. r0, r0, 24
    beq CGameCoin_Update_L_8012CBF8
    lwz r3, 0x0(r29)
    bl fn_80173500
    li r0, 0x4
    lfs f1, lbl_806D7150(r2)
    stw r0, 0x8(r29)
    li r0, 0x0
    lfs f0, lbl_806D7140(r2)
    stfs f1, 0xc(r29)
    stfs f0, 0x40(r29)
    stb r0, 0x4c(r29)
    lwz r27, 0x44(r29)
    cmplwi r27, 0x0
    beq CGameCoin_Update_L_8012CBF8
    bne CGameCoin_Update_L_8012CB0C
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x47c
    addi r5, r2, -0x30E4  /* lbl_806D717C */
    bl __assert
    CGameCoin_Update_L_8012CB0C:
    cmplwi r27, 0x0
    beq CGameCoin_Update_L_8012CB54
    bne CGameCoin_Update_L_8012CB28
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x25d
    addi r5, r2, -0x30E4  /* lbl_806D717C */
    bl __assert
    CGameCoin_Update_L_8012CB28:
    lwz r4, 0x14(r27)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne CGameCoin_Update_L_8012CB44
    rlwinm. r0, r4, 0, 25, 25
    beq CGameCoin_Update_L_8012CB44
    li r3, 0x1
    CGameCoin_Update_L_8012CB44:
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012CB54
    mr r3, r27
    bl HSD_JObjSetupMatrixSub
    CGameCoin_Update_L_8012CB54:
    lfs f1, lbl_806D718C(r2)
    addi r3, r29, 0x10
    li r4, 0x59
    bl PSMTXRotRad
    lfs f1, lbl_806D7140(r2)
    addi r3, r1, 0x80
    fmr f2, f1
    fmr f3, f1
    bl PSMTXScale
    addi r3, r29, 0x10
    addi r4, r1, 0x80
    mr r5, r3
    bl PSMTXConcat
    lfs f2, lbl_806D7184(r2)
    addi r3, r29, 0x5c
    lfs f1, 0x14(r29)
    mr r4, r3
    lfs f0, 0x50(r27)
    fmadds f0, f2, f1, f0
    stfs f0, 0x1c(r29)
    lfs f1, 0x24(r29)
    lfs f0, 0x60(r27)
    fmadds f0, f2, f1, f0
    stfs f0, 0x2c(r29)
    lfs f1, 0x34(r29)
    lfs f0, 0x70(r27)
    fmadds f0, f2, f1, f0
    stfs f0, 0x3c(r29)
    lfs f1, 0x50(r29)
    lfs f0, 0x1c(r29)
    fsubs f0, f1, f0
    stfs f0, 0x5c(r29)
    lfs f1, 0x54(r29)
    lfs f0, 0x2c(r29)
    fsubs f0, f1, f0
    stfs f0, 0x60(r29)
    lfs f1, 0x58(r29)
    lfs f0, 0x3c(r29)
    fsubs f0, f1, f0
    stfs f0, 0x64(r29)
    bl Vec3_Normalize
    CGameCoin_Update_L_8012CBF8:
    li r29, 0x1
    b CGameCoin_Update_L_8012D28C
    CGameCoin_Update_L_8012CC00:
    lfs f0, 0x1c(r27)
    addi r4, r1, 0x38
    lfs f1, lbl_806D7190(r2)
    stfs f0, 0x38(r1)
    lfs f0, 0x2c(r27)
    stfs f0, 0x3c(r1)
    lfs f0, 0x3c(r27)
    stfs f0, 0x40(r1)
    lwz r3, 0x70(r28)
    bl fn_8016DC90
    mr. r25, r3
    blt CGameCoin_Update_L_8012D28C
    lwz r4, 0x4c(r28)
    lwz r0, 0x8(r4)
    cmpwi r0, 0x4
    bne CGameCoin_Update_L_8012CC60
    li r0, 0x5
    lfs f1, lbl_806D7150(r2)
    stw r0, 0x8(r4)
    li r3, 0xc9
    lfs f0, lbl_806D7140(r2)
    stfs f1, 0xc(r4)
    stfs f0, 0x40(r4)
    bl SoundMgr_PlaySE
    CGameCoin_Update_L_8012CC60:
    cmpwi r25, 0x0
    beq CGameCoin_Update_L_8012CC70
    cmpwi r25, 0x3
    bne CGameCoin_Update_L_8012CC7C
    CGameCoin_Update_L_8012CC70:
    lwz r3, 0x6c(r28)
    li r0, 0x2
    stw r0, 0x14(r3)
    CGameCoin_Update_L_8012CC7C:
    cmpwi r25, 0x1
    beq CGameCoin_Update_L_8012CC8C
    cmpwi r25, 0x2
    bne CGameCoin_Update_L_8012CC98
    CGameCoin_Update_L_8012CC8C:
    lwz r3, 0x6c(r28)
    li r0, 0x3
    stw r0, 0x14(r3)
    CGameCoin_Update_L_8012CC98:
    lwz r3, 0x14(r28)
    li r4, 0xb
    bl SoundObj_PlaySE
    lwz r3, 0x48(r28)
    bl fn_8012BAC4
    lwz r3, 0x70(r28)
    bl fn_8016DEF4
    cmpwi r3, 0x4
    bge CGameCoin_Update_L_8012D28C
    mr r4, r25
    addi r3, r31, 0x4dc
    crxor 6, 6, 6
    bl DebugPrintf
    subfic r0, r25, 0x1
    li r4, 0x1
    orc r3, r4, r25
    srwi r0, r0, 1
    subf r0, r0, r3
    srwi. r0, r0, 31
    bne CGameCoin_Update_L_8012CCEC
    li r4, 0x0
    CGameCoin_Update_L_8012CCEC:
    clrlwi r3, r4, 24
    lwz r27, 0xc0(r28)
    neg r0, r3
    or r0, r0, r3
    srwi r30, r0, 31
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012CED8
    mr r4, r30
    addi r3, r31, 0x4ec
    addi r5, r31, 0x518
    li r6, 0x1f2
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CGameCoin_Update_L_8012CD40
    li r3, 0xab
    bl fn_8016C394
    CGameCoin_Update_L_8012CD40:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r27)
    li r3, 0x0
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012CD60
    li r3, 0x0
    b CGameCoin_Update_L_8012CDC0
    CGameCoin_Update_L_8012CD60:
    lwz r0, 0x180(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012CD74
    li r3, 0x1
    b CGameCoin_Update_L_8012CDC0
    CGameCoin_Update_L_8012CD74:
    lwz r0, 0x2ec(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012CD88
    li r3, 0x2
    b CGameCoin_Update_L_8012CDC0
    CGameCoin_Update_L_8012CD88:
    lwz r0, 0x458(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012CD9C
    li r3, 0x3
    b CGameCoin_Update_L_8012CDC0
    CGameCoin_Update_L_8012CD9C:
    lwz r0, 0x5c4(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012CDB0
    li r3, 0x4
    b CGameCoin_Update_L_8012CDC0
    CGameCoin_Update_L_8012CDB0:
    lwz r0, 0x730(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012CDC0
    li r3, 0x5
    CGameCoin_Update_L_8012CDC0:
    mulli r26, r3, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D7150(r2)
    lfs f1, lbl_806D7198(r2)
    add r3, r27, r26
    stw r4, 0x14(r3)
    stw r0, 0x1c(r3)
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x38(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x3c(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x40(r1)
    stfs f0, 0x28(r3)
    bl Cosf_LUT_Wrap
    lfs f2, lbl_806D7194(r2)
    add r25, r27, r26
    fmuls f0, f2, f1
    lfs f1, lbl_806D7198(r2)
    stfs f0, 0x2c(r25)
    stfs f2, 0x30(r25)
    bl Sinf_LUT_Wrap
    lfs f0, lbl_806D7194(r2)
    cmpwi r30, 0x1
    mr r3, r25
    fmuls f0, f0, f1
    stfs f0, 0x34(r25)
    beq CGameCoin_Update_L_8012CE74
    bge CGameCoin_Update_L_8012CE48
    cmpwi r30, 0x0
    bge CGameCoin_Update_L_8012CE54
    b CGameCoin_Update_L_8012CED8
    CGameCoin_Update_L_8012CE48:
    cmpwi r30, 0x3
    bge CGameCoin_Update_L_8012CED8
    b CGameCoin_Update_L_8012CEA4
    CGameCoin_Update_L_8012CE54:
    lfs f0, 0x2c(r25)
    lfs f1, lbl_806D719C(r2)
    fmuls f0, f0, f1
    stfs f0, 0x2c(r25)
    lfs f0, 0x34(r3)
    fmuls f0, f0, f1
    stfs f0, 0x34(r3)
    b CGameCoin_Update_L_8012CED8
    CGameCoin_Update_L_8012CE74:
    lfs f1, 0x2c(r25)
    lfs f2, lbl_806D71A0(r2)
    lfs f0, lbl_806D71A4(r2)
    fmuls f1, f1, f2
    stfs f1, 0x2c(r25)
    lfs f1, 0x34(r3)
    fmuls f1, f1, f2
    stfs f1, 0x34(r3)
    lfs f1, 0x30(r25)
    fmuls f0, f1, f0
    stfs f0, 0x30(r25)
    b CGameCoin_Update_L_8012CED8
    CGameCoin_Update_L_8012CEA4:
    lfs f1, 0x2c(r25)
    li r0, 0xa
    lfs f2, lbl_806D719C(r2)
    lfs f0, lbl_806D71A8(r2)
    fmuls f1, f1, f2
    stfs f1, 0x2c(r25)
    lfs f1, 0x34(r3)
    fmuls f1, f1, f2
    stfs f1, 0x34(r3)
    lfs f1, 0x30(r25)
    fmuls f0, f1, f0
    stfs f0, 0x30(r25)
    stw r0, 0x89c(r27)
    CGameCoin_Update_L_8012CED8:
    lwz r27, 0xc0(r28)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012D0B0
    mr r4, r30
    addi r3, r31, 0x4ec
    addi r5, r31, 0x518
    li r6, 0x1f2
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CGameCoin_Update_L_8012CF1C
    li r3, 0xab
    bl fn_8016C394
    CGameCoin_Update_L_8012CF1C:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r27)
    li r3, 0x0
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012CF3C
    li r3, 0x0
    b CGameCoin_Update_L_8012CF9C
    CGameCoin_Update_L_8012CF3C:
    lwz r0, 0x180(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012CF50
    li r3, 0x1
    b CGameCoin_Update_L_8012CF9C
    CGameCoin_Update_L_8012CF50:
    lwz r0, 0x2ec(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012CF64
    li r3, 0x2
    b CGameCoin_Update_L_8012CF9C
    CGameCoin_Update_L_8012CF64:
    lwz r0, 0x458(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012CF78
    li r3, 0x3
    b CGameCoin_Update_L_8012CF9C
    CGameCoin_Update_L_8012CF78:
    lwz r0, 0x5c4(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012CF8C
    li r3, 0x4
    b CGameCoin_Update_L_8012CF9C
    CGameCoin_Update_L_8012CF8C:
    lwz r0, 0x730(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012CF9C
    li r3, 0x5
    CGameCoin_Update_L_8012CF9C:
    mulli r25, r3, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f1, lbl_806D7150(r2)
    add r3, r27, r25
    stw r4, 0x14(r3)
    stw r0, 0x1c(r3)
    stfs f1, 0x3c(r3)
    stfs f1, 0x38(r3)
    lfs f0, 0x38(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x3c(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x40(r1)
    stfs f0, 0x28(r3)
    bl Cosf_LUT_Wrap
    lfs f2, lbl_806D7194(r2)
    add r26, r27, r25
    fmuls f0, f2, f1
    lfs f1, lbl_806D7150(r2)
    stfs f0, 0x2c(r26)
    stfs f2, 0x30(r26)
    bl Sinf_LUT_Wrap
    lfs f0, lbl_806D7194(r2)
    cmpwi r30, 0x1
    mr r3, r26
    fmuls f0, f0, f1
    stfs f0, 0x34(r26)
    beq CGameCoin_Update_L_8012D04C
    bge CGameCoin_Update_L_8012D020
    cmpwi r30, 0x0
    bge CGameCoin_Update_L_8012D02C
    b CGameCoin_Update_L_8012D0B0
    CGameCoin_Update_L_8012D020:
    cmpwi r30, 0x3
    bge CGameCoin_Update_L_8012D0B0
    b CGameCoin_Update_L_8012D07C
    CGameCoin_Update_L_8012D02C:
    lfs f0, 0x2c(r26)
    lfs f1, lbl_806D719C(r2)
    fmuls f0, f0, f1
    stfs f0, 0x2c(r26)
    lfs f0, 0x34(r3)
    fmuls f0, f0, f1
    stfs f0, 0x34(r3)
    b CGameCoin_Update_L_8012D0B0
    CGameCoin_Update_L_8012D04C:
    lfs f1, 0x2c(r26)
    lfs f2, lbl_806D71A0(r2)
    lfs f0, lbl_806D71A4(r2)
    fmuls f1, f1, f2
    stfs f1, 0x2c(r26)
    lfs f1, 0x34(r3)
    fmuls f1, f1, f2
    stfs f1, 0x34(r3)
    lfs f1, 0x30(r26)
    fmuls f0, f1, f0
    stfs f0, 0x30(r26)
    b CGameCoin_Update_L_8012D0B0
    CGameCoin_Update_L_8012D07C:
    lfs f1, 0x2c(r26)
    li r0, 0xa
    lfs f2, lbl_806D719C(r2)
    lfs f0, lbl_806D71A8(r2)
    fmuls f1, f1, f2
    stfs f1, 0x2c(r26)
    lfs f1, 0x34(r3)
    fmuls f1, f1, f2
    stfs f1, 0x34(r3)
    lfs f1, 0x30(r26)
    fmuls f0, f1, f0
    stfs f0, 0x30(r26)
    stw r0, 0x89c(r27)
    CGameCoin_Update_L_8012D0B0:
    lwz r27, 0xc0(r28)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012D28C
    mr r4, r30
    addi r3, r31, 0x4ec
    addi r5, r31, 0x518
    li r6, 0x1f2
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CGameCoin_Update_L_8012D0F4
    li r3, 0xab
    bl fn_8016C394
    CGameCoin_Update_L_8012D0F4:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r27)
    li r3, 0x0
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012D114
    li r3, 0x0
    b CGameCoin_Update_L_8012D174
    CGameCoin_Update_L_8012D114:
    lwz r0, 0x180(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012D128
    li r3, 0x1
    b CGameCoin_Update_L_8012D174
    CGameCoin_Update_L_8012D128:
    lwz r0, 0x2ec(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012D13C
    li r3, 0x2
    b CGameCoin_Update_L_8012D174
    CGameCoin_Update_L_8012D13C:
    lwz r0, 0x458(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012D150
    li r3, 0x3
    b CGameCoin_Update_L_8012D174
    CGameCoin_Update_L_8012D150:
    lwz r0, 0x5c4(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012D164
    li r3, 0x4
    b CGameCoin_Update_L_8012D174
    CGameCoin_Update_L_8012D164:
    lwz r0, 0x730(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012D174
    li r3, 0x5
    CGameCoin_Update_L_8012D174:
    mulli r25, r3, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D7150(r2)
    lfs f1, lbl_806D71AC(r2)
    add r3, r27, r25
    stw r4, 0x14(r3)
    stw r0, 0x1c(r3)
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x38(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x3c(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x40(r1)
    stfs f0, 0x28(r3)
    bl Cosf_LUT_Wrap
    lfs f2, lbl_806D7194(r2)
    add r26, r27, r25
    fmuls f0, f2, f1
    lfs f1, lbl_806D71AC(r2)
    stfs f0, 0x2c(r26)
    stfs f2, 0x30(r26)
    bl Sinf_LUT_Wrap
    lfs f0, lbl_806D7194(r2)
    cmpwi r30, 0x1
    mr r3, r26
    fmuls f0, f0, f1
    stfs f0, 0x34(r26)
    beq CGameCoin_Update_L_8012D228
    bge CGameCoin_Update_L_8012D1FC
    cmpwi r30, 0x0
    bge CGameCoin_Update_L_8012D208
    b CGameCoin_Update_L_8012D28C
    CGameCoin_Update_L_8012D1FC:
    cmpwi r30, 0x3
    bge CGameCoin_Update_L_8012D28C
    b CGameCoin_Update_L_8012D258
    CGameCoin_Update_L_8012D208:
    lfs f0, 0x2c(r26)
    lfs f1, lbl_806D719C(r2)
    fmuls f0, f0, f1
    stfs f0, 0x2c(r26)
    lfs f0, 0x34(r3)
    fmuls f0, f0, f1
    stfs f0, 0x34(r3)
    b CGameCoin_Update_L_8012D28C
    CGameCoin_Update_L_8012D228:
    lfs f1, 0x2c(r26)
    lfs f2, lbl_806D71A0(r2)
    lfs f0, lbl_806D71A4(r2)
    fmuls f1, f1, f2
    stfs f1, 0x2c(r26)
    lfs f1, 0x34(r3)
    fmuls f1, f1, f2
    stfs f1, 0x34(r3)
    lfs f1, 0x30(r26)
    fmuls f0, f1, f0
    stfs f0, 0x30(r26)
    b CGameCoin_Update_L_8012D28C
    CGameCoin_Update_L_8012D258:
    lfs f1, 0x2c(r26)
    li r0, 0xa
    lfs f2, lbl_806D719C(r2)
    lfs f0, lbl_806D71A8(r2)
    fmuls f1, f1, f2
    stfs f1, 0x2c(r26)
    lfs f1, 0x34(r3)
    fmuls f1, f1, f2
    stfs f1, 0x34(r3)
    lfs f1, 0x30(r26)
    fmuls f0, f1, f0
    stfs f0, 0x30(r26)
    stw r0, 0x89c(r27)
    CGameCoin_Update_L_8012D28C:
    clrlwi. r0, r29, 24
    bne CGameCoin_Update_L_8012D2CC
    lwz r3, 0x8(r28)
    bl InputCmd_GetDetectedFlag
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012D2CC
    lfs f0, lbl_806D7150(r2)
    stfs f0, 0x94(r28)
    lwz r3, 0x10(r28)
    bl TornadoEffect_SetFlagC0
    lwz r3, 0x14(r28)
    li r4, 0x56
    bl SoundObj_PlaySE_Direct
    lwz r3, 0x48(r28)
    bl fn_8012BB58
    li r29, 0x1
    CGameCoin_Update_L_8012D2CC:
    clrlwi. r0, r29, 24
    bne CGameCoin_Update_L_8012D3BC
    lwz r3, g_pInputState(r13)
    cmplwi r3, 0x0
    bne CGameCoin_Update_L_8012D2E8
    li r0, 0x0
    b CGameCoin_Update_L_8012D2EC
    CGameCoin_Update_L_8012D2E8:
    mr r0, r3
    CGameCoin_Update_L_8012D2EC:
    cmplwi r0, 0x0
    beq CGameCoin_Update_L_8012D3BC
    cmplwi r3, 0x0
    bne CGameCoin_Update_L_8012D300
    li r3, 0x0
    CGameCoin_Update_L_8012D300:
    lwz r0, 0x14(r3)
    cmpwi r0, 0x1
    bne CGameCoin_Update_L_8012D32C
    lwz r3, 0x88(r28)
    cmpwi r3, 0x4
    bge CGameCoin_Update_L_8012D350
    addi r0, r3, 0x1
    lfs f0, lbl_806D7150(r2)
    stw r0, 0x8c(r28)
    stfs f0, 0x90(r28)
    b CGameCoin_Update_L_8012D350
    CGameCoin_Update_L_8012D32C:
    cmpwi r0, -0x1
    bne CGameCoin_Update_L_8012D350
    lwz r3, 0x88(r28)
    cmpwi r3, 0x0
    ble CGameCoin_Update_L_8012D350
    subi r0, r3, 0x1
    lfs f0, lbl_806D7150(r2)
    stw r0, 0x8c(r28)
    stfs f0, 0x90(r28)
    CGameCoin_Update_L_8012D350:
    lwz r0, 0x88(r28)
    lwz r3, 0x8c(r28)
    cmpw r0, r3
    beq CGameCoin_Update_L_8012D3BC
    lwz r5, 0x4c(r28)
    mulli r3, r3, 0xc
    addi r6, r31, 0x460
    lwz r0, 0x8(r5)
    add r6, r6, r3
    cmpwi r0, 0x3
    bne CGameCoin_Update_L_8012D3A0
    lfs f0, 0x0(r6)
    addi r4, r5, 0x50
    lfs f1, 0x4(r6)
    stfs f0, 0x50(r5)
    lfs f0, 0x8(r6)
    stfs f1, 0x54(r5)
    stfs f0, 0x58(r5)
    lwz r3, 0x0(r5)
    bl fn_801734B0
    CGameCoin_Update_L_8012D3A0:
    lwz r3, 0x10(r28)
    bl TornadoEffect_SetFlagC0
    lwz r3, 0x14(r28)
    li r4, 0x56
    bl SoundObj_PlaySE_Direct
    lwz r3, 0x48(r28)
    bl fn_8012BB58
    CGameCoin_Update_L_8012D3BC:
    lfs f2, 0x94(r28)
    lfs f0, lbl_806D7150(r2)
    fcmpo cr0, f2, f0
    cror eq, gt, eq
    bne CGameCoin_Update_L_8012D454
    lbz r0, 0x7e(r28)
    cmplwi r0, 0x0
    bne CGameCoin_Update_L_8012D454
    lfs f1, lbl_806D7140(r2)
    lfs f0, lbl_806D7198(r2)
    fadds f1, f2, f1
    stfs f1, 0x94(r28)
    lfs f1, 0x94(r28)
    fcmpo cr0, f1, f0
    bge CGameCoin_Update_L_8012D414
    lfs f0, lbl_806D71B0(r2)
    fmuls f1, f0, f1
    bl LUT_Sin12Bit
    lfs f2, lbl_806D7138(r2)
    lfs f0, 0x78(r1)
    fmadds f0, f2, f1, f0
    stfs f0, 0x78(r1)
    CGameCoin_Update_L_8012D414:
    lfs f0, lbl_806D7198(r2)
    lfs f1, 0x94(r28)
    fcmpu cr0, f0, f1
    bne CGameCoin_Update_L_8012D440
    lwz r3, 0x10(r28)
    lfs f1, lbl_806D71B4(r2)
    bl TornadoEffect_ClearFlagC0AndSetC4
    lwz r3, 0x14(r28)
    li r4, 0x57
    bl SoundObj_PlaySE_Direct
    b CGameCoin_Update_L_8012D454
    CGameCoin_Update_L_8012D440:
    lfs f0, lbl_806D71B8(r2)
    fcmpo cr0, f1, f0
    ble CGameCoin_Update_L_8012D454
    lfs f0, lbl_806D71BC(r2)
    stfs f0, 0x94(r28)
    CGameCoin_Update_L_8012D454:
    lwz r3, 0x88(r28)
    lwz r0, 0x8c(r28)
    cmpw r3, r0
    beq CGameCoin_Update_L_8012D52C
    lfs f1, 0x90(r28)
    lfs f0, lbl_806D7140(r2)
    lfs f2, lbl_806D71C0(r2)
    fadds f0, f1, f0
    stfs f0, 0x90(r28)
    lfs f3, 0x90(r28)
    fcmpo cr0, f3, f2
    bge CGameCoin_Update_L_8012D4D8
    lwz r4, 0x88(r28)
    addi r3, r31, 0x49c
    lwz r0, 0x8c(r28)
    slwi r4, r4, 2
    lfs f1, lbl_806D7170(r2)
    slwi r0, r0, 2
    lfsx f4, r3, r4
    lfsx f0, r3, r0
    fsubs f0, f0, f4
    fmuls f0, f3, f0
    fdivs f0, f0, f2
    fadds f0, f4, f0
    stfs f0, 0xa0(r28)
    lfs f0, 0x90(r28)
    fmuls f1, f1, f0
    bl LUT_Sin12Bit
    lfs f2, lbl_806D7190(r2)
    lfs f0, 0x78(r1)
    fmadds f0, f2, f1, f0
    stfs f0, 0x78(r1)
    b CGameCoin_Update_L_8012D4EC
    CGameCoin_Update_L_8012D4D8:
    lwz r0, 0x8c(r28)
    addi r3, r31, 0x49c
    slwi r0, r0, 2
    lfsx f0, r3, r0
    stfs f0, 0xa0(r28)
    CGameCoin_Update_L_8012D4EC:
    lfs f0, lbl_806D71C0(r2)
    lfs f1, 0x90(r28)
    fcmpu cr0, f0, f1
    bne CGameCoin_Update_L_8012D518
    lwz r3, 0x10(r28)
    lfs f1, lbl_806D71C4(r2)
    bl TornadoEffect_ClearFlagC0AndSetC4
    lwz r3, 0x14(r28)
    li r4, 0x57
    bl SoundObj_PlaySE_Direct
    b CGameCoin_Update_L_8012D52C
    CGameCoin_Update_L_8012D518:
    lfs f0, lbl_806D71C8(r2)
    fcmpo cr0, f1, f0
    ble CGameCoin_Update_L_8012D52C
    lwz r0, 0x8c(r28)
    stw r0, 0x88(r28)
    CGameCoin_Update_L_8012D52C:
    lfs f1, lbl_806D7140(r2)
    addi r3, r28, 0x18
    fmr f2, f1
    fmr f3, f1
    bl PSMTXScale
    lfs f1, lbl_806D71D0(r2)
    addi r3, r1, 0x110
    lfs f0, 0xa0(r28)
    li r4, 0x59
    lfs f2, lbl_806D71CC(r2)
    fadds f0, f1, f0
    fmuls f1, f2, f0
    bl PSMTXRotRad
    addi r4, r28, 0x18
    addi r3, r1, 0x110
    mr r5, r4
    bl PSMTXConcat
    lfs f1, 0x74(r1)
    addi r3, r1, 0x110
    lfs f2, 0x78(r1)
    lfs f3, 0x7c(r1)
    bl PSMTXTrans
    addi r4, r28, 0x18
    addi r3, r1, 0x110
    mr r5, r4
    bl PSMTXConcat
    lwz r3, 0x6c(r28)
    bl BossKoopa_UpdateAnim
    lwz r3, 0x6c(r28)
    li r27, 0x0
    lfs f30, lbl_806D7150(r2)
    lwz r29, 0x28(r3)
    CGameCoin_Update_L_8012D5AC:
    lfs f0, 0x2c(r29)
    fcmpo cr0, f0, f30
    blt CGameCoin_Update_L_8012D614
    addi r3, r1, 0x74
    addi r4, r29, 0x3c
    addi r5, r1, 0x8
    bl Vec3_Subtract
    lfs f0, lbl_806D7150(r2)
    addi r3, r1, 0x8
    stfs f0, 0xc(r1)
    bl PSVECSquareMag
    lfs f0, lbl_806D71D4(r2)
    fcmpo cr0, f1, f0
    bge CGameCoin_Update_L_8012D614
    lfs f2, 0x78(r1)
    lfs f1, 0xc(r1)
    lfs f0, lbl_806D7150(r2)
    fsubs f1, f2, f1
    fcmpo cr0, f1, f0
    bge CGameCoin_Update_L_8012D600
    fneg f1, f1
    CGameCoin_Update_L_8012D600:
    lfs f0, lbl_806D7190(r2)
    fcmpo cr0, f1, f0
    bge CGameCoin_Update_L_8012D614
    li r0, 0x1
    b CGameCoin_Update_L_8012D628
    CGameCoin_Update_L_8012D614:
    addi r27, r27, 0x1
    addi r29, r29, 0x28
    cmpwi r27, 0x40
    blt CGameCoin_Update_L_8012D5AC
    li r0, 0x0
    CGameCoin_Update_L_8012D628:
    clrlwi. r0, r0, 24
    beq CGameCoin_Update_L_8012D718
    lwz r3, 0x4c(r28)
    lwz r0, 0x8(r3)
    cmpwi r0, 0x3
    bne CGameCoin_Update_L_8012D698
    lwz r3, 0x84(r28)
    lbz r0, 0x10(r3)
    cmplwi r0, 0x0
    beq CGameCoin_Update_L_8012D698
    li r3, 0x0
    li r4, 0x0
    bl fn_801699D8
    li r3, 0x1
    li r4, 0x0
    bl fn_801699D8
    lwz r3, 0x4c(r28)
    lwz r0, 0x8(r3)
    cmpwi r0, 0x3
    bne CGameCoin_Update_L_8012D690
    li r0, 0x6
    lfs f0, lbl_806D7150(r2)
    stw r0, 0x8(r3)
    stfs f0, 0xc(r3)
    lwz r3, 0x0(r3)
    bl fn_80173500
    CGameCoin_Update_L_8012D690:
    lwz r3, 0x48(r28)
    bl fn_8012B924
    CGameCoin_Update_L_8012D698:
    lwz r4, 0x4c(r28)
    lwz r3, 0x8(r4)
    subfic r0, r3, 0x4
    cntlzw r0, r0
    extrwi. r0, r0, 8, 19
    beq CGameCoin_Update_L_8012D6D8
    cmpwi r3, 0x4
    bne CGameCoin_Update_L_8012D6D8
    li r0, 0x5
    lfs f1, lbl_806D7150(r2)
    stw r0, 0x8(r4)
    li r3, 0xc9
    lfs f0, lbl_806D7140(r2)
    stfs f1, 0xc(r4)
    stfs f0, 0x40(r4)
    bl SoundMgr_PlaySE
    CGameCoin_Update_L_8012D6D8:
    lwz r3, 0xc(r28)
    li r4, 0x5f
    li r5, 0x1
    lwz r3, 0x304(r3)
    bl ItemEffectBus_ApplyItemEventSet
    lwz r3, 0x10(r28)
    li r4, 0x5f
    li r5, 0x1
    bl TornadoEffect_ApplyItemVisual_Secondary
    lwz r3, 0x14(r28)
    li r4, 0xc
    bl SoundObj_PlaySE
    lwz r3, 0x48(r28)
    bl fn_8012BD2C
    lfs f0, lbl_806D7150(r2)
    stfs f0, 0x98(r28)
    CGameCoin_Update_L_8012D718:
    lfs f2, 0x98(r28)
    lfs f0, lbl_806D7150(r2)
    fcmpo cr0, f2, f0
    cror eq, gt, eq
    bne CGameCoin_Update_L_8012D768
    lfs f1, lbl_806D7140(r2)
    lfs f0, lbl_806D7188(r2)
    fadds f1, f2, f1
    fcmpo cr0, f1, f0
    stfs f1, 0x98(r28)
    ble CGameCoin_Update_L_8012D768
    lwz r3, 0xc(r28)
    li r4, 0x5f
    lwz r3, 0x304(r3)
    bl ItemEffectBus_ApplyItemEventClear
    lwz r3, 0x10(r28)
    li r4, 0x5f
    bl TornadoEffect_ApplyItemVisual_Primary
    lfs f0, lbl_806D71BC(r2)
    stfs f0, 0x98(r28)
    CGameCoin_Update_L_8012D768:
    lfs f1, lbl_806D7150(r2)
    li r4, 0x0
    lwz r3, 0xc(r28)
    fmr f2, f1
    bl RenderObj_ItemStateMachine_Timed
    bl GetDisplayBufferIndex
    mr r4, r3
    lwz r3, 0x10(r28)
    bl TornadoEffect_Tick
    lwz r3, 0x14(r28)
    bl SoundVolumePan_Update
    fneg f1, f31
    lwz r3, 0x48(r28)
    bl fn_8012A71C
    lwz r3, 0xc(r28)
    lwz r3, 0x304(r3)
    bl ItemEffectBus_TickTornadoCooldown
    lfs f1, lbl_806D7150(r2)
    addi r3, r1, 0x68
    lfs f0, lbl_806D715C(r2)
    mr r4, r3
    stfs f1, 0x50(r1)
    stfs f1, 0x44(r1)
    stfs f1, 0x54(r1)
    stfs f1, 0x48(r1)
    stfs f0, 0x58(r1)
    stfs f0, 0x4c(r1)
    lfs f0, 0x1c(r28)
    stfs f0, 0x68(r1)
    lfs f0, 0x2c(r28)
    stfs f0, 0x6c(r1)
    lfs f0, 0x3c(r28)
    stfs f0, 0x70(r1)
    lfs f0, 0x20(r28)
    stfs f0, 0x5c(r1)
    lfs f0, 0x30(r28)
    stfs f0, 0x60(r1)
    lfs f0, 0x40(r28)
    stfs f0, 0x64(r1)
    bl Vec3_Normalize
    addi r3, r1, 0x5c
    mr r4, r3
    bl Vec3_Normalize
    lfs f7, lbl_806D71D8(r2)
    addi r4, r1, 0x50
    lfs f1, 0x60(r1)
    lfs f0, 0x54(r1)
    lfs f2, 0x5c(r1)
    fnmsubs f5, f7, f1, f0
    lfs f1, 0x50(r1)
    lfs f0, lbl_806D71DC(r2)
    fnmsubs f6, f7, f2, f1
    lfs f4, 0x64(r1)
    lfs f3, 0x58(r1)
    lfs f1, 0x48(r1)
    fadds f2, f5, f0
    lfs f0, lbl_806D71E0(r2)
    fnmsubs f3, f7, f4, f3
    stfs f5, 0x54(r1)
    fadds f0, f1, f0
    stfs f6, 0x50(r1)
    stfs f3, 0x58(r1)
    stfs f2, 0x54(r1)
    stfs f0, 0x48(r1)
    lwz r3, 0x58(r28)
    bl CObj_LoadIntoGX
    lwz r3, 0x58(r28)
    addi r4, r1, 0x44
    bl CObj_ApplyViewport
    b CGameCoin_Update_L_8012D924
    CGameCoin_Update_L_8012D880:
    lbz r0, 0x7f(r28)
    cmplwi r0, 0x0
    bne CGameCoin_Update_L_8012D924
    lfs f1, lbl_806D7140(r2)
    addi r3, r28, 0x18
    fmr f2, f1
    fmr f3, f1
    bl PSMTXScale
    lfs f1, lbl_806D718C(r2)
    addi r3, r1, 0x110
    li r4, 0x59
    bl PSMTXRotRad
    addi r4, r28, 0x18
    addi r3, r1, 0x110
    mr r5, r4
    bl PSMTXConcat
    lfs f1, 0x74(r1)
    addi r3, r1, 0x110
    lfs f2, 0x78(r1)
    lfs f3, 0x7c(r1)
    bl PSMTXTrans
    addi r4, r28, 0x18
    addi r3, r1, 0x110
    mr r5, r4
    bl PSMTXConcat
    lfs f1, lbl_806D7150(r2)
    li r4, 0x0
    lwz r3, 0xc(r28)
    fmr f2, f1
    bl RenderObj_ItemStateMachine_Timed
    bl GetDisplayBufferIndex
    mr r4, r3
    lwz r3, 0x10(r28)
    bl TornadoEffect_Tick
    lwz r3, 0x48(r28)
    lfs f1, lbl_806D7150(r2)
    bl fn_8012A71C
    lwz r3, 0x5c(r28)
    addi r5, r28, 0x18
    lwz r4, 0x58(r28)
    bl ChallengeGoalCamera_Update
    CGameCoin_Update_L_8012D924:
    bl Fog_UpdateFromCourseScene3D
    lwz r3, 0x50(r28)
    bl LakituStart_UpdateCountdown
    lwz r3, 0x54(r28)
    bl CourseEnvironment_UpdateAndCullZones_Timed
    lwz r3, 0xc0(r28)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    lwz r3, 0x70(r28)
    bl fn_8016DA78
    lwz r3, 0x74(r28)
    bl fn_8016EC80
    lwz r3, 0xa4(r28)
    lfs f1, lbl_806D7150(r2)
    lfs f2, lbl_806D71E4(r2)
    bl fn_80182B50
    lwz r3, 0xa8(r28)
    lfs f1, lbl_806D7150(r2)
    lfs f2, lbl_806D71E8(r2)
    bl fn_80182B50
    lwz r3, 0xac(r28)
    lfs f1, lbl_806D7150(r2)
    lfs f2, lbl_806D71E8(r2)
    bl fn_80182B50
    lfs f2, 0xb8(r28)
    lfs f1, lbl_806D71EC(r2)
    lfs f0, lbl_806D71F0(r2)
    fadds f1, f2, f1
    stfs f1, 0xb8(r28)
    lfs f1, 0xb8(r28)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne CGameCoin_Update_L_8012D9B8
    fsubs f0, f1, f0
    stfs f0, 0xb8(r28)
    CGameCoin_Update_L_8012D9B8:
    lfs f2, 0xbc(r28)
    lfs f1, lbl_806D71F4(r2)
    lfs f0, lbl_806D71F0(r2)
    fadds f1, f2, f1
    stfs f1, 0xbc(r28)
    lfs f1, 0xbc(r28)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne CGameCoin_Update_L_8012D9E4
    fsubs f0, f1, f0
    stfs f0, 0xbc(r28)
    CGameCoin_Update_L_8012D9E4:
    lwz r27, 0xb0(r28)
    lfs f29, 0xb8(r28)
    cmplwi r27, 0x0
    bne CGameCoin_Update_L_8012DA04
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x2b8
    addi r5, r2, -0x30E4  /* lbl_806D717C */
    bl __assert
    CGameCoin_Update_L_8012DA04:
    lwz r0, 0x14(r27)
    rlwinm. r0, r0, 0, 14, 14
    beq CGameCoin_Update_L_8012DA20
    addi r5, r31, 0x528
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x2b9
    bl __assert
    CGameCoin_Update_L_8012DA20:
    stfs f29, 0x20(r27)
    lwz r0, 0x14(r27)
    rlwinm. r0, r0, 0, 6, 6
    bne CGameCoin_Update_L_8012DA78
    cmplwi r27, 0x0
    beq CGameCoin_Update_L_8012DA78
    bne CGameCoin_Update_L_8012DA4C
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x25d
    addi r5, r2, -0x30E4  /* lbl_806D717C */
    bl __assert
    CGameCoin_Update_L_8012DA4C:
    lwz r4, 0x14(r27)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne CGameCoin_Update_L_8012DA68
    rlwinm. r0, r4, 0, 25, 25
    beq CGameCoin_Update_L_8012DA68
    li r3, 0x1
    CGameCoin_Update_L_8012DA68:
    clrlwi. r0, r3, 24
    bne CGameCoin_Update_L_8012DA78
    mr r3, r27
    bl HSD_JObjSetMtxDirtySub
    CGameCoin_Update_L_8012DA78:
    lwz r27, 0xb4(r28)
    lfs f29, 0xbc(r28)
    cmplwi r27, 0x0
    bne CGameCoin_Update_L_8012DA98
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x2b8
    addi r5, r2, -0x30E4  /* lbl_806D717C */
    bl __assert
    CGameCoin_Update_L_8012DA98:
    lwz r0, 0x14(r27)
    rlwinm. r0, r0, 0, 14, 14
    beq CGameCoin_Update_L_8012DAB4
    addi r5, r31, 0x528
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x2b9
    bl __assert
    CGameCoin_Update_L_8012DAB4:
    stfs f29, 0x20(r27)
    lwz r0, 0x14(r27)
    rlwinm. r0, r0, 0, 6, 6
    bne CGameCoin_Update_L_8012DB0C
    cmplwi r27, 0x0
    beq CGameCoin_Update_L_8012DB0C
    bne CGameCoin_Update_L_8012DAE0
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x25d
    addi r5, r2, -0x30E4  /* lbl_806D717C */
    bl __assert
    CGameCoin_Update_L_8012DAE0:
    lwz r4, 0x14(r27)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne CGameCoin_Update_L_8012DAFC
    rlwinm. r0, r4, 0, 25, 25
    beq CGameCoin_Update_L_8012DAFC
    li r3, 0x1
    CGameCoin_Update_L_8012DAFC:
    clrlwi. r0, r3, 24
    bne CGameCoin_Update_L_8012DB0C
    mr r3, r27
    bl HSD_JObjSetMtxDirtySub
    CGameCoin_Update_L_8012DB0C:
    bl IsRaceStarted
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012DBA8
    lbz r0, 0x7e(r28)
    cmplwi r0, 0x0
    bne CGameCoin_Update_L_8012DBA8
    lwz r3, 0x70(r28)
    bl fn_8016DF50
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012DB5C
    li r0, 0x1
    li r3, 0x0
    stb r0, 0x7e(r28)
    li r4, 0x0
    stb r0, 0x7f(r28)
    bl fn_801699D8
    li r3, 0x1
    li r4, 0x0
    bl fn_801699D8
    b CGameCoin_Update_L_8012DBA8
    CGameCoin_Update_L_8012DB5C:
    lfs f2, g_raceTimeRemaining(r13)
    lfs f1, lbl_806D7150(r2)
    fcmpo cr0, f2, f1
    cror eq, gt, eq
    bne CGameCoin_Update_L_8012DBA8
    lfs f0, lbl_806D71F8(r2)
    fsubs f0, f2, f0
    fcmpo cr0, f0, f1
    stfs f0, g_raceTimeRemaining(r13)
    bge CGameCoin_Update_L_8012DBA8
    stfs f1, g_raceTimeRemaining(r13)
    li r0, 0x1
    li r3, 0x0
    li r4, 0x0
    stb r0, 0x7e(r28)
    bl fn_801699D8
    li r3, 0x1
    li r4, 0x0
    bl fn_801699D8
    CGameCoin_Update_L_8012DBA8:
    lwz r3, 0x68(r28)
    lfs f1, g_raceTimeRemaining(r13)
    bl fn_80253FD8
    lwz r3, 0x68(r28)
    bl HUD_FrameUpdate
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne CGameCoin_Update_L_8012DBCC
    li r3, 0x0
    CGameCoin_Update_L_8012DBCC:
    bl TransitionEffect_Tick
    lbz r0, 0x7e(r28)
    cmplwi r0, 0x0
    beq CGameCoin_Update_L_8012E600
    lwz r0, 0x80(r28)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012DD44
    lwz r3, 0x70(r28)
    li r29, 0x0
    bl fn_8016DEF4
    mr r30, r3
    bl NokoNokoChallenge_GetCoinDivisor
    cmplwi r3, 0x0
    beq CGameCoin_Update_L_8012DC30
    cmpwi r30, 0x0
    ble CGameCoin_Update_L_8012DC24
    cmpwi r30, 0x4
    bgt CGameCoin_Update_L_8012DC24
    slwi r0, r30, 2
    add r3, r3, r0
    lwz r29, -0x4(r3)
    b CGameCoin_Update_L_8012DC28
    CGameCoin_Update_L_8012DC24:
    li r29, 0x0
    CGameCoin_Update_L_8012DC28:
    mr r3, r29
    bl SetCoinCount
    CGameCoin_Update_L_8012DC30:
    lbz r0, 0x7f(r28)
    cmplwi r0, 0x0
    beq CGameCoin_Update_L_8012DCB4
    lwz r4, 0x6c(r28)
    li r0, 0x4
    li r3, 0x37
    stw r0, 0x14(r4)
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CGameCoin_Update_L_8012DC64
    li r3, 0x37
    bl fn_8016C394
    CGameCoin_Update_L_8012DC64:
    lwz r3, 0x70(r28)
    bl fn_8016DEF4
    mr r30, r3
    mr r3, r28
    li r4, 0x1
    li r5, 0x0
    bl NokoNokoChallenge_CalcResultText
    mr r5, r3
    lwz r3, 0x68(r28)
    mr r6, r30
    li r4, 0x1
    bl fn_80253C74
    lwz r3, 0x78(r28)
    lwz r3, 0xc(r3)
    bl SetCourseScene3D
    li r3, 0x1
    li r0, 0x0
    stb r3, g_raceEnded(r13)
    stb r0, g_lakituStartAnimDone(r13)
    b CGameCoin_Update_L_8012DD30
    CGameCoin_Update_L_8012DCB4:
    lwz r4, 0x6c(r28)
    li r0, 0x4
    li r3, 0x37
    stw r0, 0x14(r4)
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CGameCoin_Update_L_8012DCDC
    li r3, 0x37
    bl fn_8016C394
    CGameCoin_Update_L_8012DCDC:
    lwz r3, 0x48(r28)
    bl fn_8012BDA4
    lwz r3, 0x70(r28)
    bl fn_8016DEF4
    mr r30, r3
    mr r3, r28
    li r4, 0x0
    li r5, 0x0
    bl NokoNokoChallenge_CalcResultText
    mr r5, r3
    lwz r3, 0x68(r28)
    mr r6, r30
    li r4, 0x0
    bl fn_80253C74
    lwz r3, 0x58(r28)
    li r4, 0x1
    bl Object_SetByte10_Return1
    li r3, 0x0
    bl fn_8016C554
    li r0, 0x0
    stb r0, g_lakituStartAnimDone(r13)
    CGameCoin_Update_L_8012DD30:
    lbz r5, 0x7f(r28)
    mr r3, r28
    mr r4, r29
    bl NokoNokoChallenge_SaveResult
    b CGameCoin_Update_L_8012DD58
    CGameCoin_Update_L_8012DD44:
    lbz r0, 0x7f(r28)
    cmplwi r0, 0x0
    beq CGameCoin_Update_L_8012DD58
    lwz r3, 0x78(r28)
    bl DefeatDemo_Update
    CGameCoin_Update_L_8012DD58:
    lwz r3, 0x80(r28)
    addi r0, r3, 0x1
    stw r0, 0x80(r28)
    lwz r0, 0x80(r28)
    cmpwi r0, 0xc8
    bne CGameCoin_Update_L_8012E5E4
    lbz r0, 0x7f(r28)
    cmplwi r0, 0x1
    bne CGameCoin_Update_L_8012E5E4
    lwz r3, 0x78(r28)
    addi r4, r1, 0x2c
    lwz r3, 0xc(r3)
    bl CObj_ApplyScissor
    lwz r27, 0xc0(r28)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012DEF0
    addi r3, r31, 0x4ec
    addi r5, r31, 0x518
    li r4, 0x2
    li r6, 0x1f2
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CGameCoin_Update_L_8012DDD0
    li r3, 0xab
    bl fn_8016C394
    CGameCoin_Update_L_8012DDD0:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r27)
    li r3, 0x0
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012DDF0
    li r3, 0x0
    b CGameCoin_Update_L_8012DE50
    CGameCoin_Update_L_8012DDF0:
    lwz r0, 0x180(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012DE04
    li r3, 0x1
    b CGameCoin_Update_L_8012DE50
    CGameCoin_Update_L_8012DE04:
    lwz r0, 0x2ec(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012DE18
    li r3, 0x2
    b CGameCoin_Update_L_8012DE50
    CGameCoin_Update_L_8012DE18:
    lwz r0, 0x458(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012DE2C
    li r3, 0x3
    b CGameCoin_Update_L_8012DE50
    CGameCoin_Update_L_8012DE2C:
    lwz r0, 0x5c4(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012DE40
    li r3, 0x4
    b CGameCoin_Update_L_8012DE50
    CGameCoin_Update_L_8012DE40:
    lwz r0, 0x730(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012DE50
    li r3, 0x5
    CGameCoin_Update_L_8012DE50:
    mulli r25, r3, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D7150(r2)
    lfs f1, lbl_806D7138(r2)
    add r3, r27, r25
    stw r4, 0x14(r3)
    stw r0, 0x1c(r3)
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x2c(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x30(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x34(r1)
    stfs f0, 0x28(r3)
    bl Cosf_LUT_Wrap
    lfs f2, lbl_806D7194(r2)
    add r26, r27, r25
    fmuls f0, f2, f1
    lfs f1, lbl_806D7138(r2)
    stfs f0, 0x2c(r26)
    stfs f2, 0x30(r26)
    bl Sinf_LUT_Wrap
    lfs f0, lbl_806D7194(r2)
    li r0, 0xa
    lfs f2, lbl_806D719C(r2)
    fmuls f1, f0, f1
    lfs f0, lbl_806D71A8(r2)
    stfs f1, 0x34(r26)
    lfs f1, 0x2c(r26)
    fmuls f1, f1, f2
    stfs f1, 0x2c(r26)
    lfs f1, 0x34(r26)
    fmuls f1, f1, f2
    stfs f1, 0x34(r26)
    lfs f1, 0x30(r26)
    fmuls f0, f1, f0
    stfs f0, 0x30(r26)
    stw r0, 0x89c(r27)
    CGameCoin_Update_L_8012DEF0:
    lwz r27, 0xc0(r28)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012E054
    addi r3, r31, 0x4ec
    addi r5, r31, 0x518
    li r4, 0x2
    li r6, 0x1f2
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CGameCoin_Update_L_8012DF34
    li r3, 0xab
    bl fn_8016C394
    CGameCoin_Update_L_8012DF34:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r27)
    li r3, 0x0
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012DF54
    li r3, 0x0
    b CGameCoin_Update_L_8012DFB4
    CGameCoin_Update_L_8012DF54:
    lwz r0, 0x180(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012DF68
    li r3, 0x1
    b CGameCoin_Update_L_8012DFB4
    CGameCoin_Update_L_8012DF68:
    lwz r0, 0x2ec(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012DF7C
    li r3, 0x2
    b CGameCoin_Update_L_8012DFB4
    CGameCoin_Update_L_8012DF7C:
    lwz r0, 0x458(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012DF90
    li r3, 0x3
    b CGameCoin_Update_L_8012DFB4
    CGameCoin_Update_L_8012DF90:
    lwz r0, 0x5c4(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012DFA4
    li r3, 0x4
    b CGameCoin_Update_L_8012DFB4
    CGameCoin_Update_L_8012DFA4:
    lwz r0, 0x730(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012DFB4
    li r3, 0x5
    CGameCoin_Update_L_8012DFB4:
    mulli r25, r3, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D7150(r2)
    lfs f1, lbl_806D71FC(r2)
    add r3, r27, r25
    stw r4, 0x14(r3)
    stw r0, 0x1c(r3)
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x2c(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x30(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x34(r1)
    stfs f0, 0x28(r3)
    bl Cosf_LUT_Wrap
    lfs f2, lbl_806D7194(r2)
    add r26, r27, r25
    fmuls f0, f2, f1
    lfs f1, lbl_806D71FC(r2)
    stfs f0, 0x2c(r26)
    stfs f2, 0x30(r26)
    bl Sinf_LUT_Wrap
    lfs f0, lbl_806D7194(r2)
    li r0, 0xa
    lfs f2, lbl_806D719C(r2)
    fmuls f1, f0, f1
    lfs f0, lbl_806D71A8(r2)
    stfs f1, 0x34(r26)
    lfs f1, 0x2c(r26)
    fmuls f1, f1, f2
    stfs f1, 0x2c(r26)
    lfs f1, 0x34(r26)
    fmuls f1, f1, f2
    stfs f1, 0x34(r26)
    lfs f1, 0x30(r26)
    fmuls f0, f1, f0
    stfs f0, 0x30(r26)
    stw r0, 0x89c(r27)
    CGameCoin_Update_L_8012E054:
    lwz r27, 0xc0(r28)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012E1B8
    addi r3, r31, 0x4ec
    addi r5, r31, 0x518
    li r4, 0x2
    li r6, 0x1f2
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CGameCoin_Update_L_8012E098
    li r3, 0xab
    bl fn_8016C394
    CGameCoin_Update_L_8012E098:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r27)
    li r3, 0x0
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E0B8
    li r3, 0x0
    b CGameCoin_Update_L_8012E118
    CGameCoin_Update_L_8012E0B8:
    lwz r0, 0x180(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E0CC
    li r3, 0x1
    b CGameCoin_Update_L_8012E118
    CGameCoin_Update_L_8012E0CC:
    lwz r0, 0x2ec(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E0E0
    li r3, 0x2
    b CGameCoin_Update_L_8012E118
    CGameCoin_Update_L_8012E0E0:
    lwz r0, 0x458(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E0F4
    li r3, 0x3
    b CGameCoin_Update_L_8012E118
    CGameCoin_Update_L_8012E0F4:
    lwz r0, 0x5c4(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E108
    li r3, 0x4
    b CGameCoin_Update_L_8012E118
    CGameCoin_Update_L_8012E108:
    lwz r0, 0x730(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E118
    li r3, 0x5
    CGameCoin_Update_L_8012E118:
    mulli r25, r3, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D7150(r2)
    lfs f1, lbl_806D716C(r2)
    add r3, r27, r25
    stw r4, 0x14(r3)
    stw r0, 0x1c(r3)
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x2c(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x30(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x34(r1)
    stfs f0, 0x28(r3)
    bl Cosf_LUT_Wrap
    lfs f2, lbl_806D7194(r2)
    add r26, r27, r25
    fmuls f0, f2, f1
    lfs f1, lbl_806D716C(r2)
    stfs f0, 0x2c(r26)
    stfs f2, 0x30(r26)
    bl Sinf_LUT_Wrap
    lfs f0, lbl_806D7194(r2)
    li r0, 0xa
    lfs f2, lbl_806D719C(r2)
    fmuls f1, f0, f1
    lfs f0, lbl_806D71A8(r2)
    stfs f1, 0x34(r26)
    lfs f1, 0x2c(r26)
    fmuls f1, f1, f2
    stfs f1, 0x2c(r26)
    lfs f1, 0x34(r26)
    fmuls f1, f1, f2
    stfs f1, 0x34(r26)
    lfs f1, 0x30(r26)
    fmuls f0, f1, f0
    stfs f0, 0x30(r26)
    stw r0, 0x89c(r27)
    CGameCoin_Update_L_8012E1B8:
    lwz r27, 0xc0(r28)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012E31C
    addi r3, r31, 0x4ec
    addi r5, r31, 0x518
    li r4, 0x2
    li r6, 0x1f2
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CGameCoin_Update_L_8012E1FC
    li r3, 0xab
    bl fn_8016C394
    CGameCoin_Update_L_8012E1FC:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r27)
    li r3, 0x0
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E21C
    li r3, 0x0
    b CGameCoin_Update_L_8012E27C
    CGameCoin_Update_L_8012E21C:
    lwz r0, 0x180(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E230
    li r3, 0x1
    b CGameCoin_Update_L_8012E27C
    CGameCoin_Update_L_8012E230:
    lwz r0, 0x2ec(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E244
    li r3, 0x2
    b CGameCoin_Update_L_8012E27C
    CGameCoin_Update_L_8012E244:
    lwz r0, 0x458(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E258
    li r3, 0x3
    b CGameCoin_Update_L_8012E27C
    CGameCoin_Update_L_8012E258:
    lwz r0, 0x5c4(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E26C
    li r3, 0x4
    b CGameCoin_Update_L_8012E27C
    CGameCoin_Update_L_8012E26C:
    lwz r0, 0x730(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E27C
    li r3, 0x5
    CGameCoin_Update_L_8012E27C:
    mulli r25, r3, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D7150(r2)
    lfs f1, lbl_806D7200(r2)
    add r3, r27, r25
    stw r4, 0x14(r3)
    stw r0, 0x1c(r3)
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x2c(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x30(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x34(r1)
    stfs f0, 0x28(r3)
    bl Cosf_LUT_Wrap
    lfs f2, lbl_806D7194(r2)
    add r26, r27, r25
    fmuls f0, f2, f1
    lfs f1, lbl_806D7200(r2)
    stfs f0, 0x2c(r26)
    stfs f2, 0x30(r26)
    bl Sinf_LUT_Wrap
    lfs f0, lbl_806D7194(r2)
    li r0, 0xa
    lfs f2, lbl_806D719C(r2)
    fmuls f1, f0, f1
    lfs f0, lbl_806D71A8(r2)
    stfs f1, 0x34(r26)
    lfs f1, 0x2c(r26)
    fmuls f1, f1, f2
    stfs f1, 0x2c(r26)
    lfs f1, 0x34(r26)
    fmuls f1, f1, f2
    stfs f1, 0x34(r26)
    lfs f1, 0x30(r26)
    fmuls f0, f1, f0
    stfs f0, 0x30(r26)
    stw r0, 0x89c(r27)
    CGameCoin_Update_L_8012E31C:
    lwz r27, 0xc0(r28)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012E480
    addi r3, r31, 0x4ec
    addi r5, r31, 0x518
    li r4, 0x2
    li r6, 0x1f2
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CGameCoin_Update_L_8012E360
    li r3, 0xab
    bl fn_8016C394
    CGameCoin_Update_L_8012E360:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r27)
    li r3, 0x0
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E380
    li r3, 0x0
    b CGameCoin_Update_L_8012E3E0
    CGameCoin_Update_L_8012E380:
    lwz r0, 0x180(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E394
    li r3, 0x1
    b CGameCoin_Update_L_8012E3E0
    CGameCoin_Update_L_8012E394:
    lwz r0, 0x2ec(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E3A8
    li r3, 0x2
    b CGameCoin_Update_L_8012E3E0
    CGameCoin_Update_L_8012E3A8:
    lwz r0, 0x458(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E3BC
    li r3, 0x3
    b CGameCoin_Update_L_8012E3E0
    CGameCoin_Update_L_8012E3BC:
    lwz r0, 0x5c4(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E3D0
    li r3, 0x4
    b CGameCoin_Update_L_8012E3E0
    CGameCoin_Update_L_8012E3D0:
    lwz r0, 0x730(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E3E0
    li r3, 0x5
    CGameCoin_Update_L_8012E3E0:
    mulli r25, r3, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D7150(r2)
    lfs f1, lbl_806D7204(r2)
    add r3, r27, r25
    stw r4, 0x14(r3)
    stw r0, 0x1c(r3)
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x2c(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x30(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x34(r1)
    stfs f0, 0x28(r3)
    bl Cosf_LUT_Wrap
    lfs f2, lbl_806D7194(r2)
    add r26, r27, r25
    fmuls f0, f2, f1
    lfs f1, lbl_806D7204(r2)
    stfs f0, 0x2c(r26)
    stfs f2, 0x30(r26)
    bl Sinf_LUT_Wrap
    lfs f0, lbl_806D7194(r2)
    li r0, 0xa
    lfs f2, lbl_806D719C(r2)
    fmuls f1, f0, f1
    lfs f0, lbl_806D71A8(r2)
    stfs f1, 0x34(r26)
    lfs f1, 0x2c(r26)
    fmuls f1, f1, f2
    stfs f1, 0x2c(r26)
    lfs f1, 0x34(r26)
    fmuls f1, f1, f2
    stfs f1, 0x34(r26)
    lfs f1, 0x30(r26)
    fmuls f0, f1, f0
    stfs f0, 0x30(r26)
    stw r0, 0x89c(r27)
    CGameCoin_Update_L_8012E480:
    lwz r27, 0xc0(r28)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012E5E4
    addi r3, r31, 0x4ec
    addi r5, r31, 0x518
    li r4, 0x2
    li r6, 0x1f2
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CGameCoin_Update_L_8012E4C4
    li r3, 0xab
    bl fn_8016C394
    CGameCoin_Update_L_8012E4C4:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r27)
    li r3, 0x0
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E4E4
    li r3, 0x0
    b CGameCoin_Update_L_8012E544
    CGameCoin_Update_L_8012E4E4:
    lwz r0, 0x180(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E4F8
    li r3, 0x1
    b CGameCoin_Update_L_8012E544
    CGameCoin_Update_L_8012E4F8:
    lwz r0, 0x2ec(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E50C
    li r3, 0x2
    b CGameCoin_Update_L_8012E544
    CGameCoin_Update_L_8012E50C:
    lwz r0, 0x458(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E520
    li r3, 0x3
    b CGameCoin_Update_L_8012E544
    CGameCoin_Update_L_8012E520:
    lwz r0, 0x5c4(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E534
    li r3, 0x4
    b CGameCoin_Update_L_8012E544
    CGameCoin_Update_L_8012E534:
    lwz r0, 0x730(r27)
    cmpwi r0, 0x0
    bne CGameCoin_Update_L_8012E544
    li r3, 0x5
    CGameCoin_Update_L_8012E544:
    mulli r25, r3, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D7150(r2)
    lfs f1, lbl_806D7208(r2)
    add r3, r27, r25
    stw r4, 0x14(r3)
    stw r0, 0x1c(r3)
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x2c(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x30(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x34(r1)
    stfs f0, 0x28(r3)
    bl Cosf_LUT_Wrap
    lfs f2, lbl_806D7194(r2)
    add r26, r27, r25
    fmuls f0, f2, f1
    lfs f1, lbl_806D7208(r2)
    stfs f0, 0x2c(r26)
    stfs f2, 0x30(r26)
    bl Sinf_LUT_Wrap
    lfs f0, lbl_806D7194(r2)
    li r0, 0xa
    lfs f2, lbl_806D719C(r2)
    fmuls f1, f0, f1
    lfs f0, lbl_806D71A8(r2)
    stfs f1, 0x34(r26)
    lfs f1, 0x2c(r26)
    fmuls f1, f1, f2
    stfs f1, 0x2c(r26)
    lfs f1, 0x34(r26)
    fmuls f1, f1, f2
    stfs f1, 0x34(r26)
    lfs f1, 0x30(r26)
    fmuls f0, f1, f0
    stfs f0, 0x30(r26)
    stw r0, 0x89c(r27)
    CGameCoin_Update_L_8012E5E4:
    lwz r3, 0x68(r28)
    bl fn_80253C40
    clrlwi. r0, r3, 24
    beq CGameCoin_Update_L_8012E658
    mr r3, r28
    bl NokoNokoChallenge_TransitionToResult
    b CGameCoin_Update_L_8012E670
    CGameCoin_Update_L_8012E600:
    lwz r3, 0x58(r28)
    addi r4, r1, 0x50
    bl CObj_LoadProjMatrix
    lwz r3, 0x58(r28)
    addi r4, r1, 0x44
    bl CObj_ApplyScissor
    bl ItemObjectManager_Update
    lwz r9, 0x44(r1)
    addi r3, r1, 0x20
    lwz r8, 0x48(r1)
    addi r4, r1, 0x14
    lwz r7, 0x4c(r1)
    lwz r6, 0x50(r1)
    lwz r5, 0x54(r1)
    lwz r0, 0x58(r1)
    stw r9, 0x14(r1)
    stw r8, 0x18(r1)
    stw r7, 0x1c(r1)
    stw r6, 0x20(r1)
    stw r5, 0x24(r1)
    stw r0, 0x28(r1)
    bl VfxSlotMgr_Update
    CGameCoin_Update_L_8012E658:
    lwz r3, g_weatherSystem(r13)
    cmplwi r3, 0x0
    beq CGameCoin_Update_L_8012E668
    bl fn_8016B32C
    CGameCoin_Update_L_8012E668:
    bl RumbleUpdate
    li r3, -0x2
    CGameCoin_Update_L_8012E670:
    psq_l f31, 0x1b8(r1), 0, 0
    lfd f31, 0x1b0(r1)
    psq_l f30, 0x1a8(r1), 0, 0
    lfd f30, 0x1a0(r1)
    psq_l f29, 0x198(r1), 0, 0
    lfd f29, 0x190(r1)
    lmw r25, 0x174(r1)
    lwz r0, 0x1c4(r1)
    mtlr r0
    addi r1, r1, 0x1c0
    blr
}

extern "C" asm void DefeatDemo_Update(void) { /* 0x8012E69C size:0x5A8 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stfd f31, 0x10(r1)
    psq_st f31, 0x18(r1), 0, 0
    stw r31, 0xc(r1)
    stw r30, 0x8(r1)
    mr r31, r3
    lbz r0, 0x14(r3)
    cmplwi r0, 0x1
    bne DefeatDemo_Update_L_8012E6D4
    li r0, 0x0
    stb r0, 0x14(r31)
    b DefeatDemo_Update_L_8012E700
    DefeatDemo_Update_L_8012E6D4:
    lfs f2, 0x10(r31)
    lfs f1, lbl_806D7140(r2)
    lfs f0, lbl_806D720C(r2)
    fadds f1, f2, f1
    stfs f1, 0x10(r31)
    lfs f1, 0x10(r31)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne DefeatDemo_Update_L_8012E700
    lfs f0, lbl_806D7210(r2)
    stfs f0, 0x10(r31)
    DefeatDemo_Update_L_8012E700:
    lfs f1, lbl_806D71D0(r2)
    lfs f0, 0x10(r31)
    fcmpu cr0, f1, f0
    bne DefeatDemo_Update_L_8012E724
    lwz r0, g_characterId(r13)
    cmpwi r0, 0x4
    beq DefeatDemo_Update_L_8012E724
    li r3, 0x13b
    bl SoundMgr_Play
    DefeatDemo_Update_L_8012E724:
    lwz r3, 0xc(r31)
    lfs f0, lbl_806D7150(r2)
    lfs f1, 0x308c(r3)
    lfs f2, 0x10(r31)
    fcmpo cr0, f1, f0
    blt DefeatDemo_Update_L_8012E750
    fcmpo cr0, f2, f0
    blt DefeatDemo_Update_L_8012E750
    li r0, 0x1
    stb r0, 0x3084(r3)
    stfs f2, 0x308c(r3)
    DefeatDemo_Update_L_8012E750:
    lwz r30, 0xc(r31)
    lfs f0, lbl_806D71BC(r2)
    lfs f1, 0x3088(r30)
    fcmpu cr0, f0, f1
    beq DefeatDemo_Update_L_8012E79C
    lbz r0, 0x3084(r30)
    cmplwi r0, 0x0
    beq DefeatDemo_Update_L_8012E77C
    li r0, 0x0
    stb r0, 0x3084(r30)
    b DefeatDemo_Update_L_8012E788
    DefeatDemo_Update_L_8012E77C:
    lfs f0, 0x308c(r30)
    fadds f0, f0, f1
    stfs f0, 0x308c(r30)
    DefeatDemo_Update_L_8012E788:
    lwz r3, 0x4(r30)
    lfs f1, 0x308c(r30)
    bl HSD_CObjReqAnim
    lwz r3, 0x4(r30)
    bl HSD_CObjAnim
    DefeatDemo_Update_L_8012E79C:
    lwz r3, 0x0(r31)
    lfs f1, 0x10(r31)
    bl Object_SetField8_AndDirty
    lwz r3, 0x0(r31)
    bl clNormal3D_Exec
    lwz r3, 0x4(r31)
    lfs f1, 0x10(r31)
    bl Object_SetField8_AndDirty
    lwz r3, 0x4(r31)
    bl clNormal3D_Exec
    lwz r3, 0x8(r31)
    lfs f1, 0x10(r31)
    bl Object_SetField8_AndDirty
    lwz r3, 0x8(r31)
    bl clNormal3D_Exec
    lwz r3, 0x18(r31)
    lfs f1, lbl_806D7150(r2)
    lfs f2, lbl_806D71E4(r2)
    bl fn_80182B50
    lwz r3, 0x1c(r31)
    lfs f1, lbl_806D7150(r2)
    lfs f2, lbl_806D71E8(r2)
    bl fn_80182B50
    lwz r3, 0x20(r31)
    lfs f1, lbl_806D7150(r2)
    lfs f2, lbl_806D71E8(r2)
    bl fn_80182B50
    lfs f2, 0x2c(r31)
    lfs f1, lbl_806D71EC(r2)
    lfs f0, lbl_806D71F0(r2)
    fadds f1, f2, f1
    stfs f1, 0x2c(r31)
    lfs f1, 0x2c(r31)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne DefeatDemo_Update_L_8012E834
    fsubs f0, f1, f0
    stfs f0, 0x2c(r31)
    DefeatDemo_Update_L_8012E834:
    lfs f2, 0x30(r31)
    lfs f1, lbl_806D71F4(r2)
    lfs f0, lbl_806D71F0(r2)
    fadds f1, f2, f1
    stfs f1, 0x30(r31)
    lfs f1, 0x30(r31)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne DefeatDemo_Update_L_8012E860
    fsubs f0, f1, f0
    stfs f0, 0x30(r31)
    DefeatDemo_Update_L_8012E860:
    lwz r30, 0x24(r31)
    lfs f31, 0x2c(r31)
    cmplwi r30, 0x0
    bne DefeatDemo_Update_L_8012E880
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x2b8
    addi r5, r2, -0x30E4  /* lbl_806D717C */
    bl __assert
    DefeatDemo_Update_L_8012E880:
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 14, 14
    beq DefeatDemo_Update_L_8012E8A0
    lis r4, lbl_80356C58@ha
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    addi r5, r4, lbl_80356C58@l
    li r4, 0x2b9
    bl __assert
    DefeatDemo_Update_L_8012E8A0:
    stfs f31, 0x20(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne DefeatDemo_Update_L_8012E8F8
    cmplwi r30, 0x0
    beq DefeatDemo_Update_L_8012E8F8
    bne DefeatDemo_Update_L_8012E8CC
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x25d
    addi r5, r2, -0x30E4  /* lbl_806D717C */
    bl __assert
    DefeatDemo_Update_L_8012E8CC:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne DefeatDemo_Update_L_8012E8E8
    rlwinm. r0, r4, 0, 25, 25
    beq DefeatDemo_Update_L_8012E8E8
    li r3, 0x1
    DefeatDemo_Update_L_8012E8E8:
    clrlwi. r0, r3, 24
    bne DefeatDemo_Update_L_8012E8F8
    mr r3, r30
    bl HSD_JObjSetMtxDirtySub
    DefeatDemo_Update_L_8012E8F8:
    lwz r30, 0x28(r31)
    lfs f31, 0x30(r31)
    cmplwi r30, 0x0
    bne DefeatDemo_Update_L_8012E918
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x2b8
    addi r5, r2, -0x30E4  /* lbl_806D717C */
    bl __assert
    DefeatDemo_Update_L_8012E918:
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 14, 14
    beq DefeatDemo_Update_L_8012E938
    lis r4, lbl_80356C58@ha
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    addi r5, r4, lbl_80356C58@l
    li r4, 0x2b9
    bl __assert
    DefeatDemo_Update_L_8012E938:
    stfs f31, 0x20(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne DefeatDemo_Update_L_8012E990
    cmplwi r30, 0x0
    beq DefeatDemo_Update_L_8012E990
    bne DefeatDemo_Update_L_8012E964
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x25d
    addi r5, r2, -0x30E4  /* lbl_806D717C */
    bl __assert
    DefeatDemo_Update_L_8012E964:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne DefeatDemo_Update_L_8012E980
    rlwinm. r0, r4, 0, 25, 25
    beq DefeatDemo_Update_L_8012E980
    li r3, 0x1
    DefeatDemo_Update_L_8012E980:
    clrlwi. r0, r3, 24
    bne DefeatDemo_Update_L_8012E990
    mr r3, r30
    bl HSD_JObjSetMtxDirtySub
    DefeatDemo_Update_L_8012E990:
    lfs f1, 0x10(r31)
    lfs f0, lbl_806D7214(r2)
    fcmpo cr0, f1, f0
    blt DefeatDemo_Update_L_8012E9AC
    lfs f0, lbl_806D7218(r2)
    fcmpo cr0, f1, f0
    ble DefeatDemo_Update_L_8012E9BC
    DefeatDemo_Update_L_8012E9AC:
    lwz r3, 0x34(r31)
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    b DefeatDemo_Update_L_8012EC24
    DefeatDemo_Update_L_8012E9BC:
    lwz r3, 0x34(r31)
    li r4, 0x10
    bl HSD_JObjClearFlagsAll
    lfs f2, 0x10(r31)
    lfs f1, lbl_806D7214(r2)
    lfs f0, lbl_806D7194(r2)
    fsubs f1, f2, f1
    lfs f2, lbl_806D7150(r2)
    lfs f3, lbl_806D7140(r2)
    fdivs f1, f1, f0
    bl Saturate_Double
    lwz r30, 0x34(r31)
    fmr f31, f1
    cmplwi r30, 0x0
    bne DefeatDemo_Update_L_8012EA08
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x325
    addi r5, r2, -0x30E4  /* lbl_806D717C */
    bl __assert
    DefeatDemo_Update_L_8012EA08:
    lfs f0, lbl_806D71B4(r2)
    fmadds f31, f0, f31, f0
    stfs f31, 0x2c(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne DefeatDemo_Update_L_8012EA68
    cmplwi r30, 0x0
    beq DefeatDemo_Update_L_8012EA68
    bne DefeatDemo_Update_L_8012EA3C
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x25d
    addi r5, r2, -0x30E4  /* lbl_806D717C */
    bl __assert
    DefeatDemo_Update_L_8012EA3C:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne DefeatDemo_Update_L_8012EA58
    rlwinm. r0, r4, 0, 25, 25
    beq DefeatDemo_Update_L_8012EA58
    li r3, 0x1
    DefeatDemo_Update_L_8012EA58:
    clrlwi. r0, r3, 24
    bne DefeatDemo_Update_L_8012EA68
    mr r3, r30
    bl HSD_JObjSetMtxDirtySub
    DefeatDemo_Update_L_8012EA68:
    lwz r30, 0x34(r31)
    cmplwi r30, 0x0
    bne DefeatDemo_Update_L_8012EA84
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x341
    addi r5, r2, -0x30E4  /* lbl_806D717C */
    bl __assert
    DefeatDemo_Update_L_8012EA84:
    stfs f31, 0x34(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne DefeatDemo_Update_L_8012EADC
    cmplwi r30, 0x0
    beq DefeatDemo_Update_L_8012EADC
    bne DefeatDemo_Update_L_8012EAB0
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x25d
    addi r5, r2, -0x30E4  /* lbl_806D717C */
    bl __assert
    DefeatDemo_Update_L_8012EAB0:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne DefeatDemo_Update_L_8012EACC
    rlwinm. r0, r4, 0, 25, 25
    beq DefeatDemo_Update_L_8012EACC
    li r3, 0x1
    DefeatDemo_Update_L_8012EACC:
    clrlwi. r0, r3, 24
    bne DefeatDemo_Update_L_8012EADC
    mr r3, r30
    bl HSD_JObjSetMtxDirtySub
    DefeatDemo_Update_L_8012EADC:
    lfs f2, 0x10(r31)
    lfs f0, lbl_806D721C(r2)
    fcmpo cr0, f2, f0
    bge DefeatDemo_Update_L_8012EB8C
    lfs f1, lbl_806D7214(r2)
    lfs f0, lbl_806D71B0(r2)
    fsubs f1, f2, f1
    lfs f2, lbl_806D7150(r2)
    lfs f3, lbl_806D7140(r2)
    fdivs f1, f1, f0
    bl Saturate_Double
    lwz r30, 0x34(r31)
    lfs f2, lbl_806D7220(r2)
    lfs f0, lbl_806D7140(r2)
    cmplwi r30, 0x0
    fmadds f31, f2, f1, f0
    bne DefeatDemo_Update_L_8012EB30
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x333
    addi r5, r2, -0x30E4  /* lbl_806D717C */
    bl __assert
    DefeatDemo_Update_L_8012EB30:
    stfs f31, 0x30(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne DefeatDemo_Update_L_8012EC24
    cmplwi r30, 0x0
    beq DefeatDemo_Update_L_8012EC24
    bne DefeatDemo_Update_L_8012EB5C
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x25d
    addi r5, r2, -0x30E4  /* lbl_806D717C */
    bl __assert
    DefeatDemo_Update_L_8012EB5C:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne DefeatDemo_Update_L_8012EB78
    rlwinm. r0, r4, 0, 25, 25
    beq DefeatDemo_Update_L_8012EB78
    li r3, 0x1
    DefeatDemo_Update_L_8012EB78:
    clrlwi. r0, r3, 24
    bne DefeatDemo_Update_L_8012EC24
    mr r3, r30
    bl HSD_JObjSetMtxDirtySub
    b DefeatDemo_Update_L_8012EC24
    DefeatDemo_Update_L_8012EB8C:
    fsubs f1, f2, f0
    lfs f0, lbl_806D722C(r2)
    lfs f2, lbl_806D7150(r2)
    lfs f3, lbl_806D7140(r2)
    fmuls f1, f1, f0
    bl Saturate_Double
    lwz r30, 0x34(r31)
    lfs f2, lbl_806D7228(r2)
    lfs f0, lbl_806D7224(r2)
    cmplwi r30, 0x0
    fnmsubs f31, f2, f1, f0
    bne DefeatDemo_Update_L_8012EBCC
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x333
    addi r5, r2, -0x30E4  /* lbl_806D717C */
    bl __assert
    DefeatDemo_Update_L_8012EBCC:
    stfs f31, 0x30(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne DefeatDemo_Update_L_8012EC24
    cmplwi r30, 0x0
    beq DefeatDemo_Update_L_8012EC24
    bne DefeatDemo_Update_L_8012EBF8
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x25d
    addi r5, r2, -0x30E4  /* lbl_806D717C */
    bl __assert
    DefeatDemo_Update_L_8012EBF8:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne DefeatDemo_Update_L_8012EC14
    rlwinm. r0, r4, 0, 25, 25
    beq DefeatDemo_Update_L_8012EC14
    li r3, 0x1
    DefeatDemo_Update_L_8012EC14:
    clrlwi. r0, r3, 24
    bne DefeatDemo_Update_L_8012EC24
    mr r3, r30
    bl HSD_JObjSetMtxDirtySub
    DefeatDemo_Update_L_8012EC24:
    psq_l f31, 0x18(r1), 0, 0
    lwz r0, 0x24(r1)
    lfd f31, 0x10(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void BossKoopa_UpdateAnim(void) { /* 0x8012EC44 size:0x438 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stw r31, 0x2c(r1)
    mr r31, r3
    lwz r0, 0x10(r3)
    lwz r3, 0x14(r3)
    cmpw r0, r3
    beq BossKoopa_UpdateAnim_L_8012ED0C
    stw r3, 0x10(r31)
    li r0, 0x1
    lfs f0, lbl_806D7150(r2)
    stfs f0, 0x18(r31)
    stb r0, 0x1c(r31)
    stfs f0, 0x20(r31)
    lwz r0, 0x10(r31)
    cmpwi r0, 0x0
    bne BossKoopa_UpdateAnim_L_8012ED0C
    lwz r0, 0x38(r31)
    cmpwi r0, 0x40
    blt BossKoopa_UpdateAnim_L_8012ECA0
    li r0, 0x0
    stw r0, 0x38(r31)
    BossKoopa_UpdateAnim_L_8012ECA0:
    lwz r5, 0x38(r31)
    lis r3, 0x4330
    lis r4, lbl_80495994@ha
    stw r3, 0x8(r1)
    addi r0, r5, 0x1
    lfd f2, lbl_806D7148(r2)
    stw r0, 0x38(r31)
    slwi r6, r5, 2
    addi r5, r4, lbl_80495994@l
    lwz r7, 0x30(r31)
    lwz r4, 0x34(r31)
    xoris r0, r7, 0x8000
    stw r3, 0x10(r1)
    subf r3, r7, r4
    lfsx f3, r5, r6
    xoris r3, r3, 0x8000
    stw r0, 0x14(r1)
    stw r3, 0xc(r1)
    lfd f0, 0x10(r1)
    lfd f1, 0x8(r1)
    fsubs f0, f0, f2
    fsubs f1, f1, f2
    fmadds f0, f1, f3, f0
    fctiwz f0, f0
    stfd f0, 0x18(r1)
    lwz r0, 0x1c(r1)
    stw r0, 0x2c(r31)
    BossKoopa_UpdateAnim_L_8012ED0C:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x4
    beq BossKoopa_UpdateAnim_L_8012F068
    lbz r0, 0x1c(r31)
    cmplwi r0, 0x0
    beq BossKoopa_UpdateAnim_L_8012ED30
    li r0, 0x0
    stb r0, 0x1c(r31)
    b BossKoopa_UpdateAnim_L_8012ED40
    BossKoopa_UpdateAnim_L_8012ED30:
    lfs f1, 0x20(r31)
    lfs f0, lbl_806D7140(r2)
    fadds f0, f1, f0
    stfs f0, 0x20(r31)
    BossKoopa_UpdateAnim_L_8012ED40:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x1
    beq BossKoopa_UpdateAnim_L_8012EE24
    bge BossKoopa_UpdateAnim_L_8012ED5C
    cmpwi r0, 0x0
    bge BossKoopa_UpdateAnim_L_8012ED68
    b BossKoopa_UpdateAnim_L_8012EF74
    BossKoopa_UpdateAnim_L_8012ED5C:
    cmpwi r0, 0x4
    bge BossKoopa_UpdateAnim_L_8012EF74
    b BossKoopa_UpdateAnim_L_8012EF48
    BossKoopa_UpdateAnim_L_8012ED68:
    lfs f1, 0x20(r31)
    lfs f0, lbl_806D7188(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne BossKoopa_UpdateAnim_L_8012ED84
    lfs f0, lbl_806D7150(r2)
    stfs f0, 0x20(r31)
    BossKoopa_UpdateAnim_L_8012ED84:
    lfs f0, 0x20(r31)
    stfs f0, 0x18(r31)
    bl IsRaceStarted
    clrlwi. r0, r3, 24
    beq BossKoopa_UpdateAnim_L_8012EF74
    lwz r3, 0x2c(r31)
    cmpwi r3, 0x0
    ble BossKoopa_UpdateAnim_L_8012EDB0
    subi r0, r3, 0x1
    stw r0, 0x2c(r31)
    b BossKoopa_UpdateAnim_L_8012EF74
    BossKoopa_UpdateAnim_L_8012EDB0:
    li r0, 0x1
    stw r0, 0x14(r31)
    lwz r0, 0x3c(r31)
    cmpwi r0, 0x30
    blt BossKoopa_UpdateAnim_L_8012EDCC
    li r0, 0x0
    stw r0, 0x3c(r31)
    BossKoopa_UpdateAnim_L_8012EDCC:
    lwz r5, 0x3c(r31)
    lis r3, lbl_80495A94@ha
    addi r3, r3, lbl_80495A94@l
    lfs f0, lbl_806D71B4(r2)
    addi r4, r5, 0x1
    slwi r0, r5, 2
    stw r4, 0x3c(r31)
    lfsx f1, r3, r0
    fcmpo cr0, f1, f0
    bge BossKoopa_UpdateAnim_L_8012EE00
    li r0, 0x0
    stw r0, 0x24(r31)
    b BossKoopa_UpdateAnim_L_8012EF74
    BossKoopa_UpdateAnim_L_8012EE00:
    lfs f0, lbl_806D7238(r2)
    fcmpo cr0, f1, f0
    bge BossKoopa_UpdateAnim_L_8012EE18
    li r0, 0x1
    stw r0, 0x24(r31)
    b BossKoopa_UpdateAnim_L_8012EF74
    BossKoopa_UpdateAnim_L_8012EE18:
    li r0, 0x2
    stw r0, 0x24(r31)
    b BossKoopa_UpdateAnim_L_8012EF74
    BossKoopa_UpdateAnim_L_8012EE24:
    lwz r0, 0x24(r31)
    cmpwi r0, 0x2
    beq BossKoopa_UpdateAnim_L_8012EEA0
    bge BossKoopa_UpdateAnim_L_8012EE44
    cmpwi r0, 0x0
    beq BossKoopa_UpdateAnim_L_8012EE50
    bge BossKoopa_UpdateAnim_L_8012EE74
    b BossKoopa_UpdateAnim_L_8012EF74
    BossKoopa_UpdateAnim_L_8012EE44:
    cmpwi r0, 0x4
    bge BossKoopa_UpdateAnim_L_8012EF74
    b BossKoopa_UpdateAnim_L_8012EEE4
    BossKoopa_UpdateAnim_L_8012EE50:
    lfs f1, 0x20(r31)
    lfs f0, lbl_806D721C(r2)
    stfs f1, 0x18(r31)
    lfs f1, 0x20(r31)
    fcmpo cr0, f1, f0
    ble BossKoopa_UpdateAnim_L_8012EF74
    li r0, 0x0
    stw r0, 0x14(r31)
    b BossKoopa_UpdateAnim_L_8012EF74
    BossKoopa_UpdateAnim_L_8012EE74:
    lfs f2, lbl_806D7134(r2)
    lfs f1, 0x20(r31)
    lfs f0, lbl_806D723C(r2)
    fmuls f1, f2, f1
    stfs f1, 0x18(r31)
    lfs f1, 0x20(r31)
    fcmpo cr0, f1, f0
    ble BossKoopa_UpdateAnim_L_8012EF74
    li r0, 0x0
    stw r0, 0x14(r31)
    b BossKoopa_UpdateAnim_L_8012EF74
    BossKoopa_UpdateAnim_L_8012EEA0:
    lfs f0, 0x20(r31)
    lfs f2, lbl_806D7188(r2)
    fcmpo cr0, f0, f2
    bge BossKoopa_UpdateAnim_L_8012EEB8
    stfs f0, 0x18(r31)
    b BossKoopa_UpdateAnim_L_8012EEC8
    BossKoopa_UpdateAnim_L_8012EEB8:
    fsubs f0, f0, f2
    lfs f1, lbl_806D7238(r2)
    fmadds f0, f1, f0, f2
    stfs f0, 0x18(r31)
    BossKoopa_UpdateAnim_L_8012EEC8:
    lfs f1, 0x20(r31)
    lfs f0, lbl_806D7240(r2)
    fcmpo cr0, f1, f0
    ble BossKoopa_UpdateAnim_L_8012EF74
    li r0, 0x0
    stw r0, 0x14(r31)
    b BossKoopa_UpdateAnim_L_8012EF74
    BossKoopa_UpdateAnim_L_8012EEE4:
    lfs f2, 0x20(r31)
    lfs f1, lbl_806D7244(r2)
    fcmpo cr0, f2, f1
    cror eq, lt, eq
    bne BossKoopa_UpdateAnim_L_8012EF00
    stfs f2, 0x18(r31)
    b BossKoopa_UpdateAnim_L_8012EF2C
    BossKoopa_UpdateAnim_L_8012EF00:
    lfs f0, lbl_806D7248(r2)
    fcmpo cr0, f2, f0
    cror eq, lt, eq
    bne BossKoopa_UpdateAnim_L_8012EF20
    fsubs f0, f2, f1
    fsubs f0, f1, f0
    stfs f0, 0x18(r31)
    b BossKoopa_UpdateAnim_L_8012EF2C
    BossKoopa_UpdateAnim_L_8012EF20:
    lfs f0, lbl_806D7234(r2)
    fsubs f0, f2, f0
    stfs f0, 0x18(r31)
    BossKoopa_UpdateAnim_L_8012EF2C:
    lfs f1, 0x20(r31)
    lfs f0, lbl_806D724C(r2)
    fcmpo cr0, f1, f0
    ble BossKoopa_UpdateAnim_L_8012EF74
    li r0, 0x0
    stw r0, 0x14(r31)
    b BossKoopa_UpdateAnim_L_8012EF74
    BossKoopa_UpdateAnim_L_8012EF48:
    lfs f1, 0x20(r31)
    lfs f0, lbl_806D7250(r2)
    stfs f1, 0x18(r31)
    lfs f1, 0x20(r31)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne BossKoopa_UpdateAnim_L_8012EF74
    li r3, 0x1
    li r0, 0x3
    stw r3, 0x14(r31)
    stw r0, 0x24(r31)
    BossKoopa_UpdateAnim_L_8012EF74:
    lwz r0, 0x10(r31)
    lfs f1, 0x18(r31)
    slwi r0, r0, 2
    lwzx r3, r31, r0
    bl Object_SetField8_AndDirty
    lwz r0, 0x10(r31)
    slwi r0, r0, 2
    lwzx r3, r31, r0
    bl clNormal3D_Exec
    lwz r0, 0x10(r31)
    cmpwi r0, 0x1
    bne BossKoopa_UpdateAnim_L_8012F014
    lfs f1, 0x18(r31)
    lfs f0, lbl_806D7188(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne BossKoopa_UpdateAnim_L_8012F014
    lfs f0, lbl_806D7244(r2)
    fcmpo cr0, f1, f0
    cror eq, lt, eq
    bne BossKoopa_UpdateAnim_L_8012F014
    lwz r4, 0x28(r31)
    lbz r0, 0x10(r4)
    cmplwi r0, 0x1
    beq BossKoopa_UpdateAnim_L_8012EFF8
    li r3, 0x1
    stb r3, 0x10(r4)
    lbz r0, 0x10(r4)
    cmplwi r0, 0x0
    beq BossKoopa_UpdateAnim_L_8012EFF8
    li r0, 0x0
    stw r0, 0xc(r4)
    stb r3, 0x1c(r4)
    BossKoopa_UpdateAnim_L_8012EFF8:
    li r3, 0x37
    bl fn_8016C360
    clrlwi. r0, r3, 24
    bne BossKoopa_UpdateAnim_L_8012F060
    li r3, 0x37
    bl SoundMgr_PlaySE
    b BossKoopa_UpdateAnim_L_8012F060
    BossKoopa_UpdateAnim_L_8012F014:
    lwz r4, 0x28(r31)
    lbz r0, 0x10(r4)
    cmplwi r0, 0x0
    beq BossKoopa_UpdateAnim_L_8012F044
    li r3, 0x0
    stb r3, 0x10(r4)
    lbz r0, 0x10(r4)
    cmplwi r0, 0x0
    beq BossKoopa_UpdateAnim_L_8012F044
    stw r3, 0xc(r4)
    li r0, 0x1
    stb r0, 0x1c(r4)
    BossKoopa_UpdateAnim_L_8012F044:
    li r3, 0x37
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne BossKoopa_UpdateAnim_L_8012F060
    li r3, 0x37
    bl fn_8016C394
    BossKoopa_UpdateAnim_L_8012F060:
    lwz r3, 0x28(r31)
    bl KoopaFireball_Update
    BossKoopa_UpdateAnim_L_8012F068:
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

extern "C" asm void KoopaFireball_Update(void) { /* 0x8012F07C size:0x3E0 */
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    stw r31, 0x5c(r1)
    stw r30, 0x58(r1)
    stw r29, 0x54(r1)
    mr r29, r3
    lwz r0, 0x4(r3)
    cmplwi r0, 0x0
    beq KoopaFireball_Update_L_8012F440
    lwz r3, 0xc(r29)
    cmpwi r3, 0x0
    beq KoopaFireball_Update_L_8012F0B8
    subi r0, r3, 0x1
    stw r0, 0xc(r29)
    KoopaFireball_Update_L_8012F0B8:
    lbz r0, 0x10(r29)
    cmplwi r0, 0x0
    beq KoopaFireball_Update_L_8012F378
    lwz r31, 0x4(r29)
    cmplwi r31, 0x0
    bne KoopaFireball_Update_L_8012F0E0
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x47c
    addi r5, r2, -0x30E4  /* lbl_806D717C */
    bl __assert
    KoopaFireball_Update_L_8012F0E0:
    cmplwi r31, 0x0
    beq KoopaFireball_Update_L_8012F128
    bne KoopaFireball_Update_L_8012F0FC
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x25d
    addi r5, r2, -0x30E4  /* lbl_806D717C */
    bl __assert
    KoopaFireball_Update_L_8012F0FC:
    lwz r4, 0x14(r31)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KoopaFireball_Update_L_8012F118
    rlwinm. r0, r4, 0, 25, 25
    beq KoopaFireball_Update_L_8012F118
    li r3, 0x1
    KoopaFireball_Update_L_8012F118:
    clrlwi. r0, r3, 24
    beq KoopaFireball_Update_L_8012F128
    mr r3, r31
    bl HSD_JObjSetupMatrixSub
    KoopaFireball_Update_L_8012F128:
    li r0, 0x40
    mr r3, r29
    lfs f0, lbl_806D7150(r2)
    li r4, 0x0
    mtctr r0
    KoopaFireball_Update_L_8012F13C:
    lfs f1, 0x2c(r3)
    fcmpo cr0, f1, f0
    bge KoopaFireball_Update_L_8012F36C
    mulli r30, r4, 0x28
    lfs f0, 0x50(r31)
    lfs f1, lbl_806D71CC(r2)
    addi r3, r1, 0x14
    li r4, 0x58
    add r5, r29, r30
    stfs f0, 0x3c(r5)
    lfs f0, 0x60(r31)
    stfs f0, 0x40(r5)
    lfs f0, 0x70(r31)
    stfs f0, 0x44(r5)
    lfs f0, 0x4c(r31)
    stfs f0, 0x30(r5)
    lfs f0, 0x5c(r31)
    stfs f0, 0x34(r5)
    lfs f0, 0x6c(r31)
    stfs f0, 0x38(r5)
    lfs f0, 0x8(r29)
    fmuls f1, f1, f0
    bl PSMTXRotRad
    addi r4, r30, 0x30
    addi r3, r1, 0x14
    add r4, r29, r4
    mr r5, r4
    bl PSMTXMultVec
    lwz r0, 0x14(r29)
    cmpwi r0, 0x40
    blt KoopaFireball_Update_L_8012F1C0
    li r0, 0x0
    stw r0, 0x14(r29)
    KoopaFireball_Update_L_8012F1C0:
    lwz r6, 0x14(r29)
    lis r3, lbl_80495994@ha
    addi r4, r3, lbl_80495994@l
    add r3, r29, r30
    addi r5, r6, 0x1
    slwi r0, r6, 2
    stw r5, 0x14(r29)
    lfsx f2, r4, r0
    lfs f1, lbl_806CF57C(r13)
    lfs f0, lbl_806CF578(r13)
    fmadds f0, f1, f2, f0
    stfs f0, 0x48(r3)
    lwz r0, 0x18(r29)
    cmpwi r0, 0x30
    blt KoopaFireball_Update_L_8012F204
    li r0, 0x0
    stw r0, 0x18(r29)
    KoopaFireball_Update_L_8012F204:
    lwz r6, 0x18(r29)
    lis r3, lbl_80495A94@ha
    addi r4, r3, lbl_80495A94@l
    add r3, r29, r30
    addi r5, r6, 0x1
    slwi r0, r6, 2
    stw r5, 0x18(r29)
    lfsx f2, r4, r0
    lfs f1, lbl_806CF588(r13)
    lfs f0, lbl_806CF584(r13)
    fmadds f0, f1, f2, f0
    stfs f0, 0x50(r3)
    lwz r0, 0x18(r29)
    cmpwi r0, 0x30
    blt KoopaFireball_Update_L_8012F248
    li r0, 0x0
    stw r0, 0x18(r29)
    KoopaFireball_Update_L_8012F248:
    lwz r5, 0x18(r29)
    lis r3, lbl_80495A94@ha
    addi r3, r3, lbl_80495A94@l
    lfs f1, lbl_806D71C4(r2)
    addi r4, r5, 0x1
    slwi r0, r5, 2
    stw r4, 0x18(r29)
    add r4, r29, r30
    lfs f0, lbl_806D7140(r2)
    lfsx f2, r3, r0
    fnmsubs f0, f1, f2, f0
    stfs f0, 0x4c(r4)
    lwz r0, 0xc(r29)
    cmpwi r0, 0x0
    beq KoopaFireball_Update_L_8012F294
    lfs f1, 0x4c(r4)
    lfs f0, lbl_806D71B4(r2)
    fmuls f0, f1, f0
    stfs f0, 0x4c(r4)
    KoopaFireball_Update_L_8012F294:
    lfs f0, lbl_806D7150(r2)
    add r3, r29, r30
    stfs f0, 0x2c(r3)
    lwz r0, 0xc(r29)
    cmpwi r0, 0x0
    bne KoopaFireball_Update_L_8012F378
    lbz r0, 0x1c(r29)
    cmplwi r0, 0x0
    beq KoopaFireball_Update_L_8012F2F0
    lwz r4, lbl_806D1510(r13)
    addi r3, r29, 0x20
    li r0, 0x0
    stw r4, 0xc(r29)
    mr r4, r3
    stb r0, 0x1c(r29)
    lfs f0, 0x4c(r31)
    stfs f0, 0x20(r29)
    lfs f0, 0x5c(r31)
    stfs f0, 0x24(r29)
    lfs f0, 0x6c(r31)
    stfs f0, 0x28(r29)
    bl Vec3_Normalize
    b KoopaFireball_Update_L_8012F378
    KoopaFireball_Update_L_8012F2F0:
    lfs f0, 0x4c(r31)
    addi r3, r1, 0x8
    mr r4, r3
    stfs f0, 0x8(r1)
    lfs f0, 0x5c(r31)
    stfs f0, 0xc(r1)
    lfs f0, 0x6c(r31)
    stfs f0, 0x10(r1)
    bl Vec3_Normalize
    addi r3, r1, 0x8
    addi r4, r29, 0x20
    bl Vec3_Dot
    lfs f0, lbl_806D7150(r2)
    fcmpo cr0, f1, f0
    bge KoopaFireball_Update_L_8012F330
    fneg f1, f1
    KoopaFireball_Update_L_8012F330:
    lfs f0, lbl_806D7254(r2)
    fcmpo cr0, f1, f0
    ble KoopaFireball_Update_L_8012F348
    lwz r0, lbl_806D1510(r13)
    stw r0, 0xc(r29)
    b KoopaFireball_Update_L_8012F350
    KoopaFireball_Update_L_8012F348:
    li r0, 0x0
    stw r0, 0xc(r29)
    KoopaFireball_Update_L_8012F350:
    lfs f0, 0x8(r1)
    stfs f0, 0x20(r29)
    lfs f0, 0xc(r1)
    stfs f0, 0x24(r29)
    lfs f0, 0x10(r1)
    stfs f0, 0x28(r29)
    b KoopaFireball_Update_L_8012F378
    KoopaFireball_Update_L_8012F36C:
    addi r3, r3, 0x28
    addi r4, r4, 0x1
    bdnz KoopaFireball_Update_L_8012F13C
    KoopaFireball_Update_L_8012F378:
    li r0, 0x40
    mr r3, r29
    lfs f4, lbl_806D7150(r2)
    mtctr r0
    KoopaFireball_Update_L_8012F388:
    lfs f0, 0x2c(r3)
    fcmpo cr0, f0, f4
    cror eq, gt, eq
    bne KoopaFireball_Update_L_8012F438
    lfs f3, 0x30(r3)
    lfs f2, lbl_806CF580(r13)
    lfs f0, 0x3c(r3)
    lfs f1, lbl_806D71B4(r2)
    fmadds f0, f3, f2, f0
    stfs f0, 0x3c(r3)
    lfs f3, 0x34(r3)
    lfs f2, lbl_806CF580(r13)
    lfs f0, 0x40(r3)
    fmadds f0, f3, f2, f0
    stfs f0, 0x40(r3)
    lfs f3, 0x38(r3)
    lfs f2, lbl_806CF580(r13)
    lfs f0, 0x44(r3)
    fmadds f0, f3, f2, f0
    stfs f0, 0x44(r3)
    lfs f2, 0x34(r3)
    fcmpo cr0, f2, f1
    bge KoopaFireball_Update_L_8012F400
    lfs f0, lbl_806D7258(r2)
    fadds f0, f2, f0
    stfs f0, 0x34(r3)
    lfs f0, 0x34(r3)
    fcmpo cr0, f0, f1
    ble KoopaFireball_Update_L_8012F400
    stfs f1, 0x34(r3)
    KoopaFireball_Update_L_8012F400:
    lfs f2, 0x48(r3)
    lfs f0, 0x50(r3)
    lfs f1, lbl_806D7140(r2)
    fadds f2, f2, f0
    lfs f0, lbl_806D725C(r2)
    stfs f2, 0x48(r3)
    lfs f2, 0x2c(r3)
    fadds f1, f2, f1
    fcmpo cr0, f1, f0
    stfs f1, 0x2c(r3)
    cror eq, gt, eq
    bne KoopaFireball_Update_L_8012F438
    lfs f0, lbl_806D71BC(r2)
    stfs f0, 0x2c(r3)
    KoopaFireball_Update_L_8012F438:
    addi r3, r3, 0x28
    bdnz KoopaFireball_Update_L_8012F388
    KoopaFireball_Update_L_8012F440:
    lwz r0, 0x64(r1)
    lwz r31, 0x5c(r1)
    lwz r30, 0x58(r1)
    lwz r29, 0x54(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
}

extern "C" asm void Shell_UpdateState(void) { /* 0x8012F45C size:0x458 */
    nofralloc
    stwu r1, -0xb0(r1)
    mflr r0
    stw r0, 0xb4(r1)
    stw r31, 0xac(r1)
    mr r31, r3
    stw r30, 0xa8(r1)
    lwz r0, 0x8(r3)
    cmpwi r0, 0x0
    beq Shell_UpdateState_L_8012F89C
    cmpwi r0, 0x4
    beq Shell_UpdateState_L_8012F5EC
    bge Shell_UpdateState_L_8012F4A4
    cmpwi r0, 0x2
    beq Shell_UpdateState_L_8012F894
    bge Shell_UpdateState_L_8012F4B4
    cmpwi r0, 0x1
    bge Shell_UpdateState_L_8012F5D8
    b Shell_UpdateState_L_8012F894
    Shell_UpdateState_L_8012F4A4:
    cmpwi r0, 0x6
    beq Shell_UpdateState_L_8012F754
    bge Shell_UpdateState_L_8012F894
    b Shell_UpdateState_L_8012F704
    Shell_UpdateState_L_8012F4B4:
    lwz r30, 0x44(r31)
    cmplwi r30, 0x0
    beq Shell_UpdateState_L_8012F5A4
    bne Shell_UpdateState_L_8012F4D4
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x47c
    addi r5, r2, -0x30E4  /* lbl_806D717C */
    bl __assert
    Shell_UpdateState_L_8012F4D4:
    cmplwi r30, 0x0
    beq Shell_UpdateState_L_8012F51C
    bne Shell_UpdateState_L_8012F4F0
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x25d
    addi r5, r2, -0x30E4  /* lbl_806D717C */
    bl __assert
    Shell_UpdateState_L_8012F4F0:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne Shell_UpdateState_L_8012F50C
    rlwinm. r0, r4, 0, 25, 25
    beq Shell_UpdateState_L_8012F50C
    li r3, 0x1
    Shell_UpdateState_L_8012F50C:
    clrlwi. r0, r3, 24
    beq Shell_UpdateState_L_8012F51C
    mr r3, r30
    bl HSD_JObjSetupMatrixSub
    Shell_UpdateState_L_8012F51C:
    addi r30, r30, 0x44
    addi r4, r31, 0x10
    mr r3, r30
    bl PSMTXCopy
    lfs f1, lbl_806D7164(r2)
    addi r3, r1, 0x74
    li r4, 0x5a
    bl PSMTXRotRad
    addi r3, r31, 0x10
    addi r4, r1, 0x74
    mr r5, r3
    bl PSMTXConcat
    lfs f1, lbl_806D7140(r2)
    addi r3, r1, 0x74
    fmr f2, f1
    fmr f3, f1
    bl PSMTXScale
    addi r3, r31, 0x10
    addi r4, r1, 0x74
    mr r5, r3
    bl PSMTXConcat
    lfs f2, lbl_806D7184(r2)
    lfs f1, 0x14(r31)
    lfs f0, 0xc(r30)
    fmadds f0, f2, f1, f0
    stfs f0, 0x1c(r31)
    lfs f1, 0x24(r31)
    lfs f0, 0x1c(r30)
    fmadds f0, f2, f1, f0
    stfs f0, 0x2c(r31)
    lfs f1, 0x34(r31)
    lfs f0, 0x2c(r30)
    fmadds f0, f2, f1, f0
    stfs f0, 0x3c(r31)
    Shell_UpdateState_L_8012F5A4:
    lfs f0, 0xc(r31)
    lfs f1, lbl_806D7188(r2)
    fcmpo cr0, f0, f1
    bge Shell_UpdateState_L_8012F894
    lfs f3, lbl_806D7140(r2)
    lfs f2, lbl_806D7150(r2)
    fadds f0, f0, f3
    stfs f0, 0xc(r31)
    lfs f0, 0xc(r31)
    fdivs f1, f0, f1
    bl Saturate_Double
    stfs f1, 0x40(r31)
    b Shell_UpdateState_L_8012F894
    Shell_UpdateState_L_8012F5D8:
    lfs f1, 0x2c(r31)
    lfs f0, lbl_806D71C4(r2)
    fsubs f0, f1, f0
    stfs f0, 0x2c(r31)
    b Shell_UpdateState_L_8012F894
    Shell_UpdateState_L_8012F5EC:
    lfs f1, lbl_806D7140(r2)
    addi r3, r1, 0x44
    lfs f0, 0xc(r31)
    fmr f2, f1
    fadds f0, f0, f1
    fmr f3, f1
    stfs f0, 0xc(r31)
    lfs f0, 0x1c(r31)
    stfs f0, 0x8(r1)
    lfs f0, 0x2c(r31)
    stfs f0, 0xc(r1)
    lfs f0, 0x3c(r31)
    stfs f0, 0x10(r1)
    bl PSMTXScale
    addi r3, r31, 0x10
    addi r4, r1, 0x44
    mr r5, r3
    bl PSMTXConcat
    lfs f1, lbl_806D7260(r2)
    addi r3, r1, 0x44
    li r4, 0x59
    bl PSMTXRotRad
    addi r3, r31, 0x10
    addi r4, r1, 0x44
    mr r5, r3
    bl PSMTXConcat
    lfs f2, 0x5c(r31)
    lfs f4, 0x68(r31)
    lfs f0, 0x8(r1)
    lfs f1, 0xc(r1)
    fmadds f3, f2, f4, f0
    lfs f0, 0x10(r1)
    stfs f3, 0x8(r1)
    lfs f2, 0x60(r31)
    fmadds f1, f2, f4, f1
    stfs f1, 0xc(r1)
    lfs f1, 0x64(r31)
    fmadds f0, f1, f4, f0
    stfs f0, 0x10(r1)
    stfs f3, 0x1c(r31)
    lfs f0, 0xc(r1)
    stfs f0, 0x2c(r31)
    lfs f0, 0x10(r1)
    stfs f0, 0x3c(r31)
    lbz r0, 0x4c(r31)
    cmplwi r0, 0x0
    bne Shell_UpdateState_L_8012F6CC
    lwz r3, 0x48(r31)
    addi r4, r1, 0x8
    bl fn_80123480
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne Shell_UpdateState_L_8012F894
    li r0, 0x1
    stb r0, 0x4c(r31)
    b Shell_UpdateState_L_8012F894
    Shell_UpdateState_L_8012F6CC:
    lfs f1, 0xc(r1)
    lfs f0, lbl_806D7264(r2)
    fcmpo cr0, f1, f0
    blt Shell_UpdateState_L_8012F6F0
    lwz r3, 0x48(r31)
    addi r4, r1, 0x8
    bl fn_80123480
    clrlwi. r0, r3, 24
    bne Shell_UpdateState_L_8012F894
    Shell_UpdateState_L_8012F6F0:
    li r0, 0x5
    lfs f0, lbl_806D7150(r2)
    stw r0, 0x8(r31)
    stfs f0, 0xc(r31)
    b Shell_UpdateState_L_8012F894
    Shell_UpdateState_L_8012F704:
    lfs f2, 0xc(r31)
    lfs f1, lbl_806D7198(r2)
    fcmpo cr0, f2, f1
    bge Shell_UpdateState_L_8012F73C
    lfs f0, lbl_806D7140(r2)
    fadds f0, f2, f0
    stfs f0, 0xc(r31)
    lfs f0, 0xc(r31)
    lfs f2, 0x40(r31)
    fdivs f0, f0, f1
    fneg f1, f2
    fmadds f0, f1, f0, f2
    stfs f0, 0x40(r31)
    b Shell_UpdateState_L_8012F894
    Shell_UpdateState_L_8012F73C:
    li r0, 0x0
    lfs f0, lbl_806D7150(r2)
    stw r0, 0x8(r31)
    stfs f0, 0xc(r31)
    stfs f0, 0x40(r31)
    b Shell_UpdateState_L_8012F894
    Shell_UpdateState_L_8012F754:
    lfs f1, 0xc(r31)
    lfs f0, lbl_806D7198(r2)
    fcmpo cr0, f1, f0
    bge Shell_UpdateState_L_8012F880
    lfs f0, lbl_806D7140(r2)
    fadds f0, f1, f0
    stfs f0, 0xc(r31)
    lwz r30, 0x44(r31)
    cmplwi r30, 0x0
    beq Shell_UpdateState_L_8012F860
    bne Shell_UpdateState_L_8012F790
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x47c
    addi r5, r2, -0x30E4  /* lbl_806D717C */
    bl __assert
    Shell_UpdateState_L_8012F790:
    cmplwi r30, 0x0
    beq Shell_UpdateState_L_8012F7D8
    bne Shell_UpdateState_L_8012F7AC
    addi r3, r2, -0x30EC  /* lbl_806D7174 */
    li r4, 0x25d
    addi r5, r2, -0x30E4  /* lbl_806D717C */
    bl __assert
    Shell_UpdateState_L_8012F7AC:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne Shell_UpdateState_L_8012F7C8
    rlwinm. r0, r4, 0, 25, 25
    beq Shell_UpdateState_L_8012F7C8
    li r3, 0x1
    Shell_UpdateState_L_8012F7C8:
    clrlwi. r0, r3, 24
    beq Shell_UpdateState_L_8012F7D8
    mr r3, r30
    bl HSD_JObjSetupMatrixSub
    Shell_UpdateState_L_8012F7D8:
    addi r30, r30, 0x44
    addi r4, r31, 0x10
    mr r3, r30
    bl PSMTXCopy
    lfs f1, lbl_806D7164(r2)
    addi r3, r1, 0x14
    li r4, 0x5a
    bl PSMTXRotRad
    addi r3, r31, 0x10
    addi r4, r1, 0x14
    mr r5, r3
    bl PSMTXConcat
    lfs f1, lbl_806D7140(r2)
    addi r3, r1, 0x14
    fmr f2, f1
    fmr f3, f1
    bl PSMTXScale
    addi r3, r31, 0x10
    addi r4, r1, 0x14
    mr r5, r3
    bl PSMTXConcat
    lfs f2, lbl_806D7184(r2)
    lfs f1, 0x14(r31)
    lfs f0, 0xc(r30)
    fmadds f0, f2, f1, f0
    stfs f0, 0x1c(r31)
    lfs f1, 0x24(r31)
    lfs f0, 0x1c(r30)
    fmadds f0, f2, f1, f0
    stfs f0, 0x2c(r31)
    lfs f1, 0x34(r31)
    lfs f0, 0x2c(r30)
    fmadds f0, f2, f1, f0
    stfs f0, 0x3c(r31)
    Shell_UpdateState_L_8012F860:
    lfs f1, 0xc(r31)
    lfs f0, lbl_806D7198(r2)
    lfs f2, 0x40(r31)
    fdivs f0, f1, f0
    fneg f1, f2
    fmadds f0, f1, f0, f2
    stfs f0, 0x40(r31)
    b Shell_UpdateState_L_8012F894
    Shell_UpdateState_L_8012F880:
    li r0, 0x0
    lfs f0, lbl_806D7150(r2)
    stw r0, 0x8(r31)
    stfs f0, 0xc(r31)
    stfs f0, 0x40(r31)
    Shell_UpdateState_L_8012F894:
    lwz r3, 0x0(r31)
    bl fn_80172844
    Shell_UpdateState_L_8012F89C:
    lwz r0, 0xb4(r1)
    lwz r31, 0xac(r1)
    lwz r30, 0xa8(r1)
    mtlr r0
    addi r1, r1, 0xb0
    blr
}

extern "C" asm void CGameCoin_Destroy(void) { /* 0x8012F8B4 size:0x3A4 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stmw r27, 0xc(r1)
    mr. r30, r3
    mr r31, r4
    beq CGameCoin_Destroy_L_8012FC40
    lis r3, vtable@ha
    addi r0, r3, vtable@l
    stw r0, 0x0(r30)
    lwz r3, 0xc0(r30)
    cmplwi r3, 0x0
    beq CGameCoin_Destroy_L_8012F8FC
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    CGameCoin_Destroy_L_8012F8FC:
    bl fn_80169C44
    lwz r3, g_weatherSystem(r13)
    cmplwi r3, 0x0
    beq CGameCoin_Destroy_L_8012F91C
    li r4, 0x1
    bl fn_8016C634
    li r0, 0x0
    stw r0, g_weatherSystem(r13)
    CGameCoin_Destroy_L_8012F91C:
    li r3, 0x0
    li r4, 0x0
    bl SetActiveCamera
    li r3, 0x0
    bl SetCourseScene3D
    lwz r3, 0x58(r30)
    cmplwi r3, 0x0
    beq CGameCoin_Destroy_L_8012F950
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    CGameCoin_Destroy_L_8012F950:
    lwz r3, 0x50(r30)
    li r4, 0x1
    bl LakituStart_Dtor
    lwz r3, 0x5c(r30)
    li r4, 0x1
    bl fn_80124C84
    li r3, 0x0
    bl SetPlayerCarObject
    lwz r3, 0xc(r30)
    li r4, 0x1
    bl KartDriver_Dtor
    lwz r3, 0x10(r30)
    li r4, 0x1
    bl VisualEffectHolder_Dtor
    lwz r3, 0x14(r30)
    li r4, 0x1
    bl AudioChannel_DtorWithSeStop
    lwz r3, 0x48(r30)
    li r4, 0x1
    bl fn_8012B394
    lwz r3, 0x8(r30)
    li r4, 0x1
    bl InputCmd_Dtor
    li r0, 0x0
    stw r0, g_raceCamera(r13)
    lwz r3, 0x60(r30)
    cmplwi r3, 0x0
    beq CGameCoin_Destroy_L_8012F9D8
    beq CGameCoin_Destroy_L_8012F9D8
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    CGameCoin_Destroy_L_8012F9D8:
    lwz r27, 0x64(r30)
    cmplwi r27, 0x0
    beq CGameCoin_Destroy_L_8012FA54
    beq CGameCoin_Destroy_L_8012FA54
    lis r3, 0x1
    lhz r4, 0x4(r27)
    subi r0, r3, 0x1
    clrlwi r0, r0, 16
    subf r0, r4, r0
    cntlzw r0, r0
    extrwi. r0, r0, 8, 19
    beq CGameCoin_Destroy_L_8012FA0C
    b CGameCoin_Destroy_L_8012FA1C
    CGameCoin_Destroy_L_8012FA0C:
    subi r3, r4, 0x1
    cntlzw r0, r4
    sth r3, 0x4(r27)
    extrwi r0, r0, 8, 19
    CGameCoin_Destroy_L_8012FA1C:
    cmpwi r0, 0x0
    beq CGameCoin_Destroy_L_8012FA54
    cmplwi r27, 0x0
    beq CGameCoin_Destroy_L_8012FA54
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
    CGameCoin_Destroy_L_8012FA54:
    lwz r3, 0x54(r30)
    li r4, 0x1
    bl CourseEnvironment_Dtor
    lwz r3, 0x68(r30)
    li r4, 0x1
    bl fn_80254134
    lwz r29, 0x4c(r30)
    cmplwi r29, 0x0
    beq CGameCoin_Destroy_L_8012FAA4
    lwz r3, 0x0(r29)
    li r4, 0x1
    bl fn_80173550
    lwz r3, 0x4(r29)
    li r4, 0x1
    bl Object_DtorWithGXSync
    lwz r3, 0x48(r29)
    li r4, 0x1
    bl fn_80123B48
    mr r3, r29
    bl MemoryManager_TimedFree
    CGameCoin_Destroy_L_8012FAA4:
    lwz r28, 0x6c(r30)
    cmplwi r28, 0x0
    beq CGameCoin_Destroy_L_8012FB18
    lwz r29, 0x28(r28)
    cmplwi r29, 0x0
    beq CGameCoin_Destroy_L_8012FAD0
    lwz r3, 0x0(r29)
    li r4, 0x1
    bl Object_DtorWithGXSync
    mr r3, r29
    bl MemoryManager_TimedFree
    CGameCoin_Destroy_L_8012FAD0:
    li r29, 0x0
    mr r27, r28
    CGameCoin_Destroy_L_8012FAD8:
    lwz r3, 0x0(r27)
    li r4, 0x1
    bl Object_DtorWithGXSync
    addi r29, r29, 0x1
    addi r27, r27, 0x4
    cmpwi r29, 0x4
    blt CGameCoin_Destroy_L_8012FAD8
    li r3, 0x37
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CGameCoin_Destroy_L_8012FB10
    li r3, 0x37
    bl fn_8016C394
    CGameCoin_Destroy_L_8012FB10:
    mr r3, r28
    bl MemoryManager_TimedFree
    CGameCoin_Destroy_L_8012FB18:
    lwz r3, 0x70(r30)
    li r4, 0x1
    bl fn_8016DFAC
    lwz r3, 0x74(r30)
    li r4, 0x1
    bl fn_8016EFA8
    lwz r28, 0x78(r30)
    cmplwi r28, 0x0
    beq CGameCoin_Destroy_L_8012FB88
    lwz r3, 0x0(r28)
    li r4, 0x1
    bl Object_DtorWithGXSync
    lwz r3, 0x4(r28)
    li r4, 0x1
    bl Object_DtorWithGXSync
    lwz r3, 0x8(r28)
    li r4, 0x1
    bl Object_DtorWithGXSync
    lwz r3, 0xc(r28)
    cmplwi r3, 0x0
    beq CGameCoin_Destroy_L_8012FB80
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    CGameCoin_Destroy_L_8012FB80:
    mr r3, r28
    bl MemoryManager_TimedFree
    CGameCoin_Destroy_L_8012FB88:
    bl ItemObjectManager_Reset
    bl VfxSlotMgr_Shutdown
    bl ClRomTable_PurgeAll
    bl GetRaceContextPtr
    bl RankingTable_Init
    lwz r3, lbl_806D10D0(r13)
    cmplwi r3, 0x0
    beq CGameCoin_Destroy_L_8012FBBC
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    CGameCoin_Destroy_L_8012FBBC:
    li r0, 0x0
    stw r0, lbl_806D10D0(r13)
    bl SceneDrawList_Reset
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    beq CGameCoin_Destroy_L_8012FBE8
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    CGameCoin_Destroy_L_8012FBE8:
    li r0, 0x0
    li r3, 0x0
    stw r0, lbl_806D109C(r13)
    bl SetResourceLoadingFlag
    bl clRom_PurgeAll
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    beq CGameCoin_Destroy_L_8012FC1C
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    CGameCoin_Destroy_L_8012FC1C:
    li r0, 0x0
    mr r3, r30
    stw r0, lbl_806D10AC(r13)
    li r4, 0x0
    bl dtor_80122FD8
    extsh. r0, r31
    ble CGameCoin_Destroy_L_8012FC40
    mr r3, r30
    bl MemoryManager_TimedFree
    CGameCoin_Destroy_L_8012FC40:
    mr r3, r30
    lmw r27, 0xc(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void CGameCoin_Init(void) { /* 0x8012FC58 size:0x78C */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stfd f31, 0x40(r1)
    psq_st f31, 0x48(r1), 0, 0
    stmw r27, 0x2c(r1)
    mr r31, r3
    lis r4, lbl_80356730@ha
    mr r0, r31
    mr r29, r0
    addi r30, r4, lbl_80356730@l
    bl GameMode_BaseInit
    lis r4, lbl_8048E144@ha
    lis r3, vtable@ha
    addi r0, r4, lbl_8048E144@l
    lfs f0, lbl_806D7150(r2)
    stw r0, 0x0(r29)
    addi r0, r3, vtable@l
    mr r3, r31
    stfs f0, 0x4(r29)
    stw r0, 0x0(r31)
    bl CGameCoin_InitFields
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
    mr. r29, r3
    beq CGameCoin_Init_L_8012FCE4
    bl InputManager_Init
    CGameCoin_Init_L_8012FCE4:
    stw r29, 0x54(r31)
    li r0, 0x0
    li r3, 0x0
    stw r0, 0x60(r31)
    stw r0, 0x64(r31)
    stw r0, g_raceCamera(r13)
    bl ProcessSystemTick
    li r3, 0x30
    bl Alloc
    mr. r29, r3
    beq CGameCoin_Init_L_8012FD18
    li r4, 0x3c
    bl InputCmd_Init
    CGameCoin_Init_L_8012FD18:
    stw r29, 0x8(r31)
    bl GetRaceContextPtr
    bl RankingTable_Init
    li r0, 0x0
    li r3, 0x0
    stw r0, lbl_806D12BC(r13)
    bl SoundDriver_GetOrCreate
    addi r4, r1, 0x10
    addi r5, r1, 0xc
    addi r6, r1, 0x8
    li r3, 0x0
    bl GetStartPosition
    li r3, 0x384
    bl Alloc
    mr. r28, r3
    beq CGameCoin_Init_L_8012FD80
    lwz r29, g_characterId(r13)
    bl GetDisplayBufferIndex
    mr r4, r3
    mr r3, r28
    mr r5, r29
    addi r6, r31, 0x18
    li r7, 0x0
    li r8, 0x0
    li r9, 0x0
    bl KartDriver_New_Full
    CGameCoin_Init_L_8012FD80:
    stw r28, 0xc(r31)
    li r0, 0x1
    li r3, 0x154
    lwz r4, 0xc(r31)
    stw r0, 0x238(r4)
    bl Alloc
    mr. r28, r3
    beq CGameCoin_Init_L_8012FDC0
    lfs f1, lbl_806D7150(r2)
    li r4, 0x1
    lwz r5, 0xc(r31)
    li r7, 0x1
    fmr f2, f1
    lwz r6, g_characterId(r13)
    fmr f3, f1
    bl TornadoEffect_Ctor
    CGameCoin_Init_L_8012FDC0:
    stw r28, 0x10(r31)
    lfs f1, lbl_806D7150(r2)
    lwz r3, 0x10(r31)
    lfs f2, lbl_806D7140(r2)
    bl TireEffect_ResetSpin
    lwz r3, 0x10(r31)
    li r4, 0x1
    li r5, 0x1
    bl TornadoEffect_SetColorPairC8CC
    li r3, 0x38
    bl Alloc
    mr. r28, r3
    beq CGameCoin_Init_L_8012FE0C
    lwz r4, g_characterId(r13)
    li r5, 0x1
    li r6, 0x1
    li r7, 0x0
    li r8, 0x0
    bl KartAudioChannel_Init
    CGameCoin_Init_L_8012FE0C:
    stw r28, 0x14(r31)
    li r4, 0x1
    lwz r3, 0x14(r31)
    bl KartAudioChannel_ResetSEsAndSetFlag
    li r3, 0x168
    bl Alloc
    mr. r28, r3
    beq CGameCoin_Init_L_8012FE38
    lwz r4, g_characterId(r13)
    addi r5, r31, 0x18
    bl fn_8012B48C
    CGameCoin_Init_L_8012FE38:
    stw r28, 0x48(r31)
    li r3, 0x58
    bl Alloc
    mr. r28, r3
    beq CGameCoin_Init_L_8012FE64
    lfs f1, lbl_806D7150(r2)
    addi r4, r30, 0x550
    li r5, 0x0
    fmr f2, f1
    fmr f3, f1
    bl LakituStart_Init
    CGameCoin_Init_L_8012FE64:
    stw r28, 0x50(r31)
    li r3, 0x3084
    bl Alloc
    mr. r28, r3
    beq CGameCoin_Init_L_8012FE94
    lwz r3, g_characterId(r13)
    li r4, -0x1
    bl GetKartModelNameEntry
    mr r4, r3
    mr r3, r28
    lwz r4, 0x0(r4)
    bl Scene3D_Init
    CGameCoin_Init_L_8012FE94:
    stw r28, 0x58(r31)
    li r3, 0x8
    bl Alloc
    mr. r28, r3
    beq CGameCoin_Init_L_8012FEAC
    bl ChallengeGoalCamera_Init
    CGameCoin_Init_L_8012FEAC:
    stw r28, 0x5c(r31)
    li r3, 0x0
    bl ProcessSystemTick
    li r3, 0x80
    bl Alloc
    mr. r28, r3
    beq CGameCoin_Init_L_8012FED0
    li r4, 0x0
    bl HUD_Init
    CGameCoin_Init_L_8012FED0:
    stw r28, 0x68(r31)
    li r4, 0x6
    li r5, 0x0
    lwz r3, 0x68(r31)
    bl HUD_RegisterOverlay
    lwz r3, 0x68(r31)
    li r4, 0x11
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x68(r31)
    li r4, 0x12
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x68(r31)
    li r4, 0xe
    li r5, 0x0
    bl HUD_RegisterOverlay
    li r0, 0x0
    stb r0, g_lakituStartAnimDone(r13)
    lwz r3, 0x58(r31)
    bl SetCourseScene3D
    li r0, 0x0
    stb r0, g_raceEnded(r13)
    bl MiniGame_GetTimerValue
    xoris r3, r3, 0x8000
    lis r0, 0x4330
    stw r3, 0x1c(r1)
    li r3, 0x5
    lfd f1, lbl_806D7148(r2)
    stw r0, 0x18(r1)
    lfd f0, 0x18(r1)
    fsubs f0, f0, f1
    stfs f0, g_raceTimeRemaining(r13)
    bl PreloadEffectResources
    li r3, 0x9
    bl PreloadEffectResources
    li r3, 0xa
    bl PreloadEffectResources
    bl MiniGame_GetCourseData
    stw r3, 0x84(r31)
    lwz r0, 0x84(r31)
    cmplwi r0, 0x0
    bne CGameCoin_Init_L_8012FF84
    addi r0, r30, 0x4b0
    stw r0, 0x84(r31)
    CGameCoin_Init_L_8012FF84:
    li r3, 0x6c
    bl Alloc
    mr. r28, r3
    beq CGameCoin_Init_L_80130048
    lwz r5, 0x84(r31)
    li r0, 0x0
    lwz r4, 0x48(r31)
    li r3, 0x20
    lfs f31, 0x4(r5)
    lwz r29, 0x164(r4)
    lfs f0, lbl_806D7150(r2)
    stw r0, 0x0(r28)
    stw r0, 0x4(r28)
    stw r0, 0x8(r28)
    stfs f0, 0xc(r28)
    stfs f0, 0x40(r28)
    stw r0, 0x44(r28)
    stw r0, 0x48(r28)
    stb r0, 0x4c(r28)
    stfs f0, 0x50(r28)
    stfs f0, 0x54(r28)
    stfs f0, 0x58(r28)
    bl Alloc
    mr. r27, r3
    beq CGameCoin_Init_L_8012FFEC
    bl fn_8017363C
    CGameCoin_Init_L_8012FFEC:
    stw r27, 0x0(r28)
    li r3, 0x5c
    bl Alloc
    mr. r27, r3
    beq CGameCoin_Init_L_8013000C
    addi r4, r30, 0x564
    li r5, 0x1
    bl clNormal3D_Construct
    CGameCoin_Init_L_8013000C:
    stw r27, 0x4(r28)
    lis r4, 0x4000
    li r5, 0x0
    lwz r3, 0x4(r28)
    bl clNormal3D_SetFlags
    stw r29, 0x44(r28)
    li r3, 0x4
    stfs f31, 0x68(r28)
    bl Alloc
    mr. r27, r3
    beq CGameCoin_Init_L_80130044
    addi r4, r30, 0x418
    li r5, 0x1
    bl fn_80123BB4
    CGameCoin_Init_L_80130044:
    stw r27, 0x48(r28)
    CGameCoin_Init_L_80130048:
    stw r28, 0x4c(r31)
    li r3, 0x40
    bl Alloc
    mr. r27, r3
    beq CGameCoin_Init_L_8013006C
    lwz r5, 0x84(r31)
    lwz r4, 0x8(r5)
    lwz r5, 0xc(r5)
    bl BossKoopa_Init
    CGameCoin_Init_L_8013006C:
    stw r27, 0x6c(r31)
    li r3, 0x10
    bl Alloc
    mr. r27, r3
    beq CGameCoin_Init_L_80130084
    bl fn_8016E064
    CGameCoin_Init_L_80130084:
    stw r27, 0x70(r31)
    li r3, 0x898
    bl Alloc
    mr. r27, r3
    beq CGameCoin_Init_L_8013009C
    bl fn_8016F010
    CGameCoin_Init_L_8013009C:
    stw r27, 0x74(r31)
    li r3, 0x38
    bl Alloc
    mr. r27, r3
    beq CGameCoin_Init_L_801300B4
    bl CGameCoin_InitDefeatDemo
    CGameCoin_Init_L_801300B4:
    stw r27, 0x78(r31)
    addi r4, r30, 0x57c
    lwz r3, 0x54(r31)
    bl CourseEnvironment_ResolveJointInSlot0
    stw r3, 0xa4(r31)
    addi r4, r30, 0x598
    lwz r3, 0x54(r31)
    bl CourseEnvironment_ResolveJointInSlot0
    stw r3, 0xa8(r31)
    addi r4, r30, 0x5b4
    lwz r3, 0x54(r31)
    bl CourseEnvironment_ResolveJointInSlot0
    stw r3, 0xac(r31)
    addi r4, r30, 0x5d0
    lwz r3, 0x54(r31)
    bl CourseEnvironment_ResolveJointInSlot0
    stw r3, 0xb0(r31)
    addi r4, r30, 0x5f0
    lwz r3, 0x54(r31)
    bl CourseEnvironment_ResolveJointInSlot0
    stw r3, 0xb4(r31)
    li r3, 0x8a0
    bl Alloc
    mr. r27, r3
    beq CGameCoin_Init_L_801302D8
    lis r3, lbl_8048E34C@ha
    li r4, 0x0
    addi r3, r3, lbl_8048E34C@l
    li r0, 0x7
    stw r3, 0x0(r27)
    li r3, 0x5c
    stw r4, 0xc(r27)
    stw r4, 0x10(r27)
    stw r0, 0x89c(r27)
    bl Alloc
    mr. r28, r3
    beq CGameCoin_Init_L_80130154
    addi r4, r30, 0x610
    li r5, 0x1
    bl clNormal3D_Construct
    CGameCoin_Init_L_80130154:
    stw r28, 0x4(r27)
    lis r4, 0x4000
    li r5, 0x0
    lwz r3, 0x4(r27)
    bl clNormal3D_SetFlags
    li r3, 0x5c
    bl Alloc
    mr. r28, r3
    beq CGameCoin_Init_L_80130184
    addi r4, r30, 0x620
    li r5, 0x1
    bl clNormal3D_Construct
    CGameCoin_Init_L_80130184:
    stw r28, 0x8(r27)
    lwz r3, 0x8(r27)
    bl Archive_GetRootJObj
    li r4, 0x200
    bl HSD_JObjSetFlags
    li r0, 0x3
    mr r5, r27
    lfs f0, lbl_806D7150(r2)
    li r4, 0x0
    mtctr r0
    CGameCoin_Init_L_801301AC:
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
    bdnz CGameCoin_Init_L_801301AC
    lwz r0, 0x89c(r27)
    cmpwi r0, 0x14
    blt CGameCoin_Init_L_801302CC
    li r0, 0x13
    stw r0, 0x89c(r27)
    CGameCoin_Init_L_801302CC:
    lis r3, lbl_8048E3C0@ha
    addi r0, r3, lbl_8048E3C0@l
    stw r0, 0x0(r27)
    CGameCoin_Init_L_801302D8:
    stw r27, 0xc0(r31)
    lwz r0, g_weatherSystem(r13)
    cmplwi r0, 0x0
    bne CGameCoin_Init_L_80130304
    li r3, 0x1b4
    bl Alloc
    mr. r27, r3
    beq CGameCoin_Init_L_80130300
    li r4, 0x1
    bl WeatherSystem_Init
    CGameCoin_Init_L_80130300:
    stw r27, g_weatherSystem(r13)
    CGameCoin_Init_L_80130304:
    li r3, 0x0
    bl InitRumbleController
    li r3, 0x1
    bl SetResourceLoadingFlag
    lwz r0, g_pInputState(r13)
    cmplwi r0, 0x0
    bne CGameCoin_Init_L_80130324
    li r0, 0x0
    CGameCoin_Init_L_80130324:
    cmplwi r0, 0x0
    bne CGameCoin_Init_L_8013038C
    li r3, 0x28
    bl Alloc
    cmplwi r3, 0x0
    beq CGameCoin_Init_L_8013038C
    lis r4, lbl_803FDF28@ha
    lis r5, lbl_803FDF40@ha
    addi r0, r4, lbl_803FDF28@l
    li r4, 0x0
    stw r0, 0x0(r3)
    addi r5, r5, lbl_803FDF40@l
    li r0, 0x1
    stw r3, g_pInputState(r13)
    stw r5, 0x0(r3)
    stb r4, 0x4(r3)
    stb r0, 0x5(r3)
    stb r0, 0x6(r3)
    stw r4, 0x8(r3)
    stw r4, 0xc(r3)
    stw r4, 0x10(r3)
    stw r4, 0x14(r3)
    stw r4, 0x18(r3)
    stw r4, 0x1c(r3)
    stw r4, 0x20(r3)
    stw r4, 0x24(r3)
    CGameCoin_Init_L_8013038C:
    bl StrPcb_GetInstance
    bl StrPcb_ForceRun_Neutral
    bl StrPcb_GetInstance
    li r4, 0x1
    bl StrPcb_ResetCommands_Neutral
    lwz r4, g_pInputState(r13)
    cmplwi r4, 0x0
    bne CGameCoin_Init_L_801303B0
    li r4, 0x0
    CGameCoin_Init_L_801303B0:
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x4(r4)
    mr r3, r31
    stw r0, 0x18(r4)
    stw r0, 0x1c(r4)
    psq_l f31, 0x48(r1), 0, 0
    lfd f31, 0x40(r1)
    lmw r27, 0x2c(r1)
    lwz r0, 0x54(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}

extern "C" asm void CGameCoin_InitDefeatDemo(void) { /* 0x801303E4 size:0x2A8 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    lfs f0, lbl_806D7150(r2)
    lis r4, lbl_80356730@ha
    stw r0, 0x24(r1)
    li r0, 0x1
    stw r31, 0x1c(r1)
    mr r31, r3
    li r3, 0x0
    stw r30, 0x18(r1)
    addi r30, r4, lbl_80356730@l
    stw r29, 0x14(r1)
    stw r3, 0x0(r31)
    stw r3, 0x4(r31)
    stw r3, 0x8(r31)
    stw r3, 0xc(r31)
    stfs f0, 0x10(r31)
    stb r0, 0x14(r31)
    stw r3, 0x18(r31)
    stw r3, 0x1c(r31)
    stw r3, 0x20(r31)
    stw r3, 0x24(r31)
    stw r3, 0x28(r31)
    stfs f0, 0x2c(r31)
    stfs f0, 0x30(r31)
    stw r3, 0x34(r31)
    lwz r0, g_characterId(r13)
    cmpwi r0, 0x4
    bne CGameCoin_InitDefeatDemo_L_8013049C
    li r3, 0x5c
    bl Alloc
    mr. r29, r3
    beq CGameCoin_InitDefeatDemo_L_80130474
    addi r4, r30, 0x630
    li r5, 0x0
    bl clNormal3D_Construct
    CGameCoin_InitDefeatDemo_L_80130474:
    stw r29, 0x0(r31)
    li r3, 0x5c
    bl Alloc
    mr. r29, r3
    beq CGameCoin_InitDefeatDemo_L_80130494
    addi r4, r30, 0x64c
    li r5, 0x0
    bl clNormal3D_Construct
    CGameCoin_InitDefeatDemo_L_80130494:
    stw r29, 0x4(r31)
    b CGameCoin_InitDefeatDemo_L_801304DC
    CGameCoin_InitDefeatDemo_L_8013049C:
    li r3, 0x5c
    bl Alloc
    mr. r29, r3
    beq CGameCoin_InitDefeatDemo_L_801304B8
    addi r4, r30, 0x630
    li r5, 0x0
    bl clNormal3D_Construct
    CGameCoin_InitDefeatDemo_L_801304B8:
    stw r29, 0x0(r31)
    li r3, 0x5c
    bl Alloc
    mr. r29, r3
    beq CGameCoin_InitDefeatDemo_L_801304D8
    addi r4, r30, 0x664
    li r5, 0x0
    bl clNormal3D_Construct
    CGameCoin_InitDefeatDemo_L_801304D8:
    stw r29, 0x4(r31)
    CGameCoin_InitDefeatDemo_L_801304DC:
    li r3, 0x5c
    bl Alloc
    mr. r29, r3
    beq CGameCoin_InitDefeatDemo_L_801304F8
    addi r4, r30, 0x678
    li r5, 0x0
    bl clNormal3D_Construct
    CGameCoin_InitDefeatDemo_L_801304F8:
    lfs f1, lbl_806D7150(r2)
    li r4, 0x0
    stw r29, 0x8(r31)
    fmr f3, f1
    lfs f2, lbl_806D7140(r2)
    fmr f4, f1
    lwz r3, 0x0(r31)
    bl clNormal3D_SetScale
    lfs f1, lbl_806D7150(r2)
    li r4, 0x0
    lwz r3, 0x4(r31)
    fmr f3, f1
    lfs f2, lbl_806D7140(r2)
    fmr f4, f1
    bl clNormal3D_SetScale
    lfs f1, lbl_806D7150(r2)
    li r4, 0x0
    lwz r3, 0x8(r31)
    fmr f3, f1
    lfs f2, lbl_806D7140(r2)
    fmr f4, f1
    bl clNormal3D_SetScale
    li r3, 0x3090
    bl Alloc
    mr. r29, r3
    beq CGameCoin_InitDefeatDemo_L_80130584
    addi r4, r30, 0x630
    bl Scene3D_Init
    lis r3, lbl_80419EF8@ha
    lfs f1, lbl_806D71BC(r2)
    addi r0, r3, lbl_80419EF8@l
    lfs f0, lbl_806D7150(r2)
    stw r0, 0x0(r29)
    stfs f1, 0x3088(r29)
    stfs f0, 0x308c(r29)
    CGameCoin_InitDefeatDemo_L_80130584:
    stw r29, 0xc(r31)
    lwz r29, 0xc(r31)
    lwz r0, 0x4(r29)
    cmplwi r0, 0x0
    beq CGameCoin_InitDefeatDemo_L_8013060C
    li r0, 0x1
    lfs f1, lbl_806D7150(r2)
    stb r0, 0x3084(r29)
    lfs f0, lbl_806D7140(r2)
    stfs f1, 0x308c(r29)
    stfs f0, 0x3088(r29)
    lwz r3, 0x2c(r29)
    cmplwi r3, 0x0
    bne CGameCoin_InitDefeatDemo_L_801305C4
    li r4, 0x0
    b CGameCoin_InitDefeatDemo_L_801305F0
    CGameCoin_InitDefeatDemo_L_801305C4:
    lwz r3, 0x4(r3)
    cmplwi r3, 0x0
    bne CGameCoin_InitDefeatDemo_L_801305D8
    li r4, 0x0
    b CGameCoin_InitDefeatDemo_L_801305F0
    CGameCoin_InitDefeatDemo_L_801305D8:
    lwz r3, 0x4(r3)
    cmplwi r3, 0x0
    bne CGameCoin_InitDefeatDemo_L_801305EC
    li r4, 0x0
    b CGameCoin_InitDefeatDemo_L_801305F0
    CGameCoin_InitDefeatDemo_L_801305EC:
    lwz r4, 0x0(r3)
    CGameCoin_InitDefeatDemo_L_801305F0:
    lwz r3, 0x4(r29)
    bl HSD_CObjAddAnim
    lwz r3, 0x4(r29)
    lfs f1, 0x308c(r29)
    bl HSD_CObjReqAnim
    lwz r3, 0x4(r29)
    bl HSD_CObjAnim
    CGameCoin_InitDefeatDemo_L_8013060C:
    lwz r3, 0x0(r31)
    addi r4, r30, 0x688
    bl ResolveJointByName
    stw r3, 0x18(r31)
    addi r4, r30, 0x6a4
    lwz r3, 0x0(r31)
    bl ResolveJointByName
    stw r3, 0x1c(r31)
    addi r4, r30, 0x6c0
    lwz r3, 0x0(r31)
    bl ResolveJointByName
    stw r3, 0x20(r31)
    addi r4, r30, 0x6dc
    lwz r3, 0x0(r31)
    bl ResolveJointByName
    stw r3, 0x24(r31)
    addi r4, r30, 0x6fc
    lwz r3, 0x0(r31)
    bl ResolveJointByName
    stw r3, 0x28(r31)
    addi r4, r30, 0x71c
    lwz r3, 0x8(r31)
    bl ResolveJointByName
    stw r3, 0x34(r31)
    mr r3, r31
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void BossKoopa_Init(void) { /* 0x8013068C size:0x3FC */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    li r6, 0x0
    lfs f0, lbl_806D7150(r2)
    stw r0, 0x24(r1)
    li r0, 0x3c
    lis r7, lbl_80356730@ha
    stw r31, 0x1c(r1)
    addi r31, r7, lbl_80356730@l
    stw r30, 0x18(r1)
    mr r30, r5
    stw r29, 0x14(r1)
    mr r29, r4
    stw r28, 0x10(r1)
    mr r28, r3
    stw r6, 0x0(r3)
    li r3, 0x1
    stw r6, 0x4(r28)
    stw r6, 0x8(r28)
    stw r6, 0xc(r28)
    stw r6, 0x10(r28)
    stw r6, 0x14(r28)
    stfs f0, 0x18(r28)
    stb r3, 0x1c(r28)
    stfs f0, 0x20(r28)
    stw r0, 0x2c(r28)
    stw r6, 0x24(r28)
    stw r6, 0x28(r28)
    bl OSGetTick
    lis r4, 0x8000
    lwz r0, 0xf8(r4)
    srwi r0, r0, 2
    divwu r0, r3, r0
    clrlwi r0, r0, 26
    stw r0, 0x38(r28)
    bl OSGetTick
    lis r5, 0x8000
    lis r4, 0xaaab
    lwz r5, 0xf8(r5)
    subi r0, r4, 0x5555
    srwi r4, r5, 2
    divwu r4, r3, r4
    li r3, 0xa2c
    mulhwu r0, r0, r4
    srwi r0, r0, 5
    mulli r0, r0, 0x30
    subf r0, r0, r4
    stw r0, 0x3c(r28)
    stw r29, 0x30(r28)
    stw r30, 0x34(r28)
    bl Alloc
    mr. r29, r3
    beq BossKoopa_Init_L_80130850
    li r4, 0x0
    lfs f1, lbl_806D7150(r2)
    stw r4, 0x0(r29)
    li r3, 0x1
    li r0, 0x2
    mr r5, r29
    stw r4, 0x4(r29)
    lfs f0, lbl_806D71BC(r2)
    stfs f1, 0x8(r29)
    stw r4, 0xc(r29)
    stb r4, 0x10(r29)
    stb r3, 0x1c(r29)
    stw r4, 0x14(r29)
    stw r4, 0x18(r29)
    stfs f1, 0x20(r29)
    stfs f1, 0x24(r29)
    stfs f1, 0x28(r29)
    mtctr r0
    BossKoopa_Init_L_801307A8:
    stfs f0, 0x2c(r5)
    stfs f0, 0x54(r5)
    stfs f0, 0x7c(r5)
    stfs f0, 0xa4(r5)
    stfs f0, 0xcc(r5)
    stfs f0, 0xf4(r5)
    stfs f0, 0x11c(r5)
    stfs f0, 0x144(r5)
    stfs f0, 0x16c(r5)
    stfs f0, 0x194(r5)
    stfs f0, 0x1bc(r5)
    stfs f0, 0x1e4(r5)
    stfs f0, 0x20c(r5)
    stfs f0, 0x234(r5)
    stfs f0, 0x25c(r5)
    stfs f0, 0x284(r5)
    stfs f0, 0x2ac(r5)
    stfs f0, 0x2d4(r5)
    stfs f0, 0x2fc(r5)
    stfs f0, 0x324(r5)
    stfs f0, 0x34c(r5)
    stfs f0, 0x374(r5)
    stfs f0, 0x39c(r5)
    stfs f0, 0x3c4(r5)
    stfs f0, 0x3ec(r5)
    stfs f0, 0x414(r5)
    stfs f0, 0x43c(r5)
    stfs f0, 0x464(r5)
    stfs f0, 0x48c(r5)
    stfs f0, 0x4b4(r5)
    stfs f0, 0x4dc(r5)
    stfs f0, 0x504(r5)
    addi r5, r5, 0x500
    bdnz BossKoopa_Init_L_801307A8
    li r3, 0x5c
    bl Alloc
    mr. r30, r3
    beq BossKoopa_Init_L_8013084C
    addi r4, r31, 0x744
    li r5, 0x1
    bl clNormal3D_Construct
    BossKoopa_Init_L_8013084C:
    stw r30, 0x0(r29)
    BossKoopa_Init_L_80130850:
    stw r29, 0x28(r28)
    lwz r0, g_characterId(r13)
    cmpwi r0, 0x4
    bne BossKoopa_Init_L_80130904
    li r3, 0x5c
    bl Alloc
    mr. r29, r3
    beq BossKoopa_Init_L_8013087C
    addi r4, r31, 0x754
    li r5, 0x0
    bl clNormal3D_Construct
    BossKoopa_Init_L_8013087C:
    stw r29, 0x0(r28)
    li r3, 0x5c
    bl Alloc
    mr. r29, r3
    beq BossKoopa_Init_L_8013089C
    addi r4, r31, 0x770
    li r5, 0x0
    bl clNormal3D_Construct
    BossKoopa_Init_L_8013089C:
    stw r29, 0x4(r28)
    li r3, 0x5c
    bl Alloc
    mr. r29, r3
    beq BossKoopa_Init_L_801308BC
    addi r4, r31, 0x78c
    li r5, 0x0
    bl clNormal3D_Construct
    BossKoopa_Init_L_801308BC:
    stw r29, 0x8(r28)
    li r3, 0x5c
    bl Alloc
    mr. r29, r3
    beq BossKoopa_Init_L_801308DC
    addi r4, r31, 0x7ac
    li r5, 0x0
    bl clNormal3D_Construct
    BossKoopa_Init_L_801308DC:
    stw r29, 0xc(r28)
    addi r4, r31, 0x7cc
    lwz r3, 0x4(r28)
    bl ResolveJointByName
    lwz r4, 0x28(r28)
    stw r3, 0x4(r4)
    lfs f0, lbl_806CF574(r13)
    lwz r3, 0x28(r28)
    stfs f0, 0x8(r3)
    b BossKoopa_Init_L_801309A4
    BossKoopa_Init_L_80130904:
    li r3, 0x5c
    bl Alloc
    mr. r29, r3
    beq BossKoopa_Init_L_80130920
    addi r4, r31, 0x7f4
    li r5, 0x0
    bl clNormal3D_Construct
    BossKoopa_Init_L_80130920:
    stw r29, 0x0(r28)
    li r3, 0x5c
    bl Alloc
    mr. r29, r3
    beq BossKoopa_Init_L_80130940
    addi r4, r31, 0x808
    li r5, 0x0
    bl clNormal3D_Construct
    BossKoopa_Init_L_80130940:
    stw r29, 0x4(r28)
    li r3, 0x5c
    bl Alloc
    mr. r29, r3
    beq BossKoopa_Init_L_80130960
    addi r4, r31, 0x820
    li r5, 0x0
    bl clNormal3D_Construct
    BossKoopa_Init_L_80130960:
    stw r29, 0x8(r28)
    li r3, 0x5c
    bl Alloc
    mr. r29, r3
    beq BossKoopa_Init_L_80130980
    addi r4, r31, 0x838
    li r5, 0x0
    bl clNormal3D_Construct
    BossKoopa_Init_L_80130980:
    stw r29, 0xc(r28)
    addi r4, r31, 0x850
    lwz r3, 0x4(r28)
    bl ResolveJointByName
    lwz r4, 0x28(r28)
    stw r3, 0x4(r4)
    lfs f0, lbl_806CF570(r13)
    lwz r3, 0x28(r28)
    stfs f0, 0x8(r3)
    BossKoopa_Init_L_801309A4:
    lfs f1, lbl_806D7150(r2)
    li r4, 0x0
    lwz r3, 0x0(r28)
    fmr f3, f1
    lfs f2, lbl_806D7140(r2)
    fmr f4, f1
    bl clNormal3D_SetScale
    lwz r3, 0x0(r28)
    lfs f1, lbl_806D7150(r2)
    lfs f2, lbl_806D71C0(r2)
    lfs f3, lbl_806D71D8(r2)
    bl Object_SetJObjPositionXYZ
    lfs f1, lbl_806D7150(r2)
    li r4, 0x0
    lwz r3, 0x4(r28)
    fmr f3, f1
    lfs f2, lbl_806D7140(r2)
    fmr f4, f1
    bl clNormal3D_SetScale
    lwz r3, 0x4(r28)
    lfs f1, lbl_806D7150(r2)
    lfs f2, lbl_806D71C0(r2)
    lfs f3, lbl_806D71D8(r2)
    bl Object_SetJObjPositionXYZ
    lfs f1, lbl_806D7150(r2)
    li r4, 0x0
    lwz r3, 0x8(r28)
    fmr f3, f1
    lfs f2, lbl_806D7140(r2)
    fmr f4, f1
    bl clNormal3D_SetScale
    lwz r3, 0x8(r28)
    lfs f1, lbl_806D7150(r2)
    lfs f2, lbl_806D71C0(r2)
    lfs f3, lbl_806D71D8(r2)
    bl Object_SetJObjPositionXYZ
    lfs f1, lbl_806D7150(r2)
    li r4, 0x0
    lwz r3, 0xc(r28)
    fmr f3, f1
    lfs f2, lbl_806D7140(r2)
    fmr f4, f1
    bl clNormal3D_SetScale
    lwz r3, 0xc(r28)
    lfs f1, lbl_806D7150(r2)
    lfs f2, lbl_806D71C0(r2)
    lfs f3, lbl_806D71D8(r2)
    bl Object_SetJObjPositionXYZ
    lwz r0, 0x24(r1)
    mr r3, r28
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm void CGameCoin_InitFields(void) { /* 0x80130A88 size:0xD4 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    li r0, 0x0
    stw r31, 0xc(r1)
    mr r31, r3
    stw r0, 0x8(r3)
    addi r3, r31, 0x18
    stw r0, 0xc(r31)
    stw r0, 0x10(r31)
    stw r0, 0x14(r31)
    bl PSMTXIdentity
    li r3, 0x0
    lfs f1, lbl_806D71BC(r2)
    stw r3, 0x48(r31)
    li r0, 0x2
    lfs f0, lbl_806D7150(r2)
    stw r3, 0x4c(r31)
    stfs f1, 0x94(r31)
    stfs f1, 0x98(r31)
    stw r3, 0x84(r31)
    stw r3, 0x9c(r31)
    stfs f0, 0xa0(r31)
    stw r0, 0x88(r31)
    stw r0, 0x8c(r31)
    stw r3, 0x50(r31)
    stw r3, 0x54(r31)
    stw r3, 0x58(r31)
    stw r3, 0x5c(r31)
    stw r3, 0x60(r31)
    stw r3, 0x64(r31)
    stw r3, 0x68(r31)
    stw r3, 0x6c(r31)
    stw r3, 0x70(r31)
    stw r3, 0x74(r31)
    stw r3, 0x78(r31)
    stb r3, 0x7c(r31)
    stb r3, 0x7d(r31)
    stb r3, 0x7e(r31)
    stb r3, 0x7f(r31)
    stw r3, 0x80(r31)
    stw r3, 0xa4(r31)
    stw r3, 0xa8(r31)
    stw r3, 0xac(r31)
    stw r3, 0xb0(r31)
    stw r3, 0xb4(r31)
    stfs f0, 0xb8(r31)
    stfs f0, 0xbc(r31)
    lwz r31, 0xc(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void CoinParticle_Draw(void) { /* 0x80130B5C size:0x1D0 */
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
    stfd f28, 0x50(r1)
    psq_st f28, 0x58(r1), 0, 0
    stfd f27, 0x40(r1)
    psq_st f27, 0x48(r1), 0, 0
    stfd f26, 0x30(r1)
    psq_st f26, 0x38(r1), 0, 0
    stmw r26, 0x18(r1)
    mr r26, r3
    li r28, 0x0
    mr r29, r26
    CoinParticle_Draw_L_80130BA8:
    lwz r0, 0x14(r29)
    cmpwi r0, 0x0
    beq CoinParticle_Draw_L_80130CD8
    lwz r3, 0x4(r26)
    addi r4, r29, 0x20
    bl Object_SetJObjPositionVec
    lfs f1, lbl_806D7130(r2)
    lfs f0, 0x38(r29)
    lwz r3, 0x4(r26)
    fmuls f1, f1, f0
    bl Object_SetJObjRotationY
    lfs f1, lbl_806D7134(r2)
    lwz r3, 0x4(r26)
    fmr f2, f1
    fmr f3, f1
    bl Object_SetJObjScaleXYZ
    lwz r3, 0x4(r26)
    li r4, 0x0
    lfs f1, 0x3c(r29)
    bl Object_SetColorAlphaOnly
    lwz r3, 0x4(r26)
    li r4, 0x0
    bl LinkedNode_GetField10_OrFallback
    mr r4, r3
    lwz r3, 0x4(r26)
    li r5, 0x7
    bl Object_RenderJObjEx
    lwz r3, 0x4(r26)
    li r4, 0x0
    bl LinkedNode_GetField10_OrFallback
    mr. r4, r3
    lwz r3, 0x4(r26)
    bne CoinParticle_Draw_L_80130C34
    li r4, 0x0
    b CoinParticle_Draw_L_80130C38
    CoinParticle_Draw_L_80130C34:
    lwz r4, 0x8(r4)
    CoinParticle_Draw_L_80130C38:
    li r5, 0x7
    bl Object_RenderJObjEx
    lfd f28, lbl_806D7148(r2)
    mr r30, r29
    lfs f29, lbl_806D7138(r2)
    li r27, 0x0
    lfs f30, lbl_806D713C(r2)
    lis r31, 0x4330
    lfs f31, lbl_806D7140(r2)
    b CoinParticle_Draw_L_80130CCC
    CoinParticle_Draw_L_80130C60:
    lwz r0, 0x40(r30)
    addi r4, r30, 0x44
    stw r31, 0x8(r1)
    xoris r0, r0, 0x8000
    lwz r3, 0x8(r26)
    stw r0, 0xc(r1)
    lfd f0, 0x8(r1)
    fsubs f0, f0, f28
    fdivs f27, f0, f29
    fsubs f26, f30, f27
    bl Object_SetJObjPositionVec
    fmr f1, f26
    lwz r3, 0x8(r26)
    fmr f2, f26
    fmr f3, f26
    bl Object_SetJObjScaleXYZ
    fsubs f1, f31, f27
    lfs f0, 0x3c(r29)
    lwz r3, 0x8(r26)
    li r4, 0x0
    fmuls f1, f1, f0
    bl Object_SetColorAlphaOnly
    lwz r3, 0x8(r26)
    li r4, 0x7
    bl Object_RenderJObjTree
    addi r30, r30, 0x10
    addi r27, r27, 0x1
    CoinParticle_Draw_L_80130CCC:
    lwz r0, 0x89c(r26)
    cmpw r27, r0
    blt CoinParticle_Draw_L_80130C60
    CoinParticle_Draw_L_80130CD8:
    addi r28, r28, 0x1
    addi r29, r29, 0x16c
    cmpwi r28, 0x6
    blt CoinParticle_Draw_L_80130BA8
    psq_l f31, 0x88(r1), 0, 0
    lfd f31, 0x80(r1)
    psq_l f30, 0x78(r1), 0, 0
    lfd f30, 0x70(r1)
    psq_l f29, 0x68(r1), 0, 0
    lfd f29, 0x60(r1)
    psq_l f28, 0x58(r1), 0, 0
    lfd f28, 0x50(r1)
    psq_l f27, 0x48(r1), 0, 0
    lfd f27, 0x40(r1)
    psq_l f26, 0x38(r1), 0, 0
    lfd f26, 0x30(r1)
    lmw r26, 0x18(r1)
    lwz r0, 0x94(r1)
    mtlr r0
    addi r1, r1, 0x90
    blr
}

extern "C" asm void CoinParticle_Update(void) { /* 0x80130D2C size:0x2B0 */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stfd f31, 0x40(r1)
    psq_st f31, 0x48(r1), 0, 0
    stfd f30, 0x30(r1)
    psq_st f30, 0x38(r1), 0, 0
    stmw r24, 0x10(r1)
    mr r26, r3
    li r27, 0x0
    mr r30, r26
    CoinParticle_Update_L_80130D58:
    lwz r0, 0x14(r30)
    cmpwi r0, 0x0
    beq CoinParticle_Update_L_80130FA8
    lfs f1, 0x20(r30)
    addi r28, r30, 0x40
    lfs f0, 0x2c(r30)
    lfs f2, lbl_806D7158(r2)
    fadds f3, f1, f0
    lfs f1, lbl_806D7190(r2)
    lfs f0, lbl_806D7230(r2)
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
    lfs f2, 0x38(r30)
    fadds f1, f2, f1
    stfs f1, 0x38(r30)
    lfs f1, 0x38(r30)
    fcmpo cr0, f1, f0
    ble CoinParticle_Update_L_80130DD0
    fsubs f0, f1, f0
    stfs f0, 0x38(r30)
    CoinParticle_Update_L_80130DD0:
    lwz r3, 0x1c(r30)
    lis r0, 0x4330
    stw r0, 0x8(r1)
    mr r5, r28
    xoris r0, r3, 0x8000
    lfd f2, lbl_806D7148(r2)
    stw r0, 0xc(r1)
    li r6, 0x0
    lfs f0, lbl_806D7234(r2)
    li r3, -0x1
    lfd f1, 0x8(r1)
    lfs f3, lbl_806D7140(r2)
    fsubs f2, f1, f2
    lfs f1, lbl_806D713C(r2)
    fdivs f0, f2, f0
    fsubs f0, f3, f0
    stfs f0, 0x3c(r30)
    b CoinParticle_Update_L_80130E50
    CoinParticle_Update_L_80130E18:
    lwz r0, 0x0(r5)
    cmpwi r0, 0x0
    blt CoinParticle_Update_L_80130E48
    lfs f0, 0x8(r5)
    fsubs f0, f0, f1
    stfs f0, 0x8(r5)
    lwz r4, 0x0(r5)
    addi r0, r4, 0x1
    cmpwi r0, 0xa
    stw r0, 0x0(r5)
    ble CoinParticle_Update_L_80130E48
    stw r3, 0x0(r5)
    CoinParticle_Update_L_80130E48:
    addi r5, r5, 0x10
    addi r6, r6, 0x1
    CoinParticle_Update_L_80130E50:
    lwz r0, 0x89c(r26)
    cmpw r6, r0
    blt CoinParticle_Update_L_80130E18
    lwz r0, 0x1c(r30)
    clrlwi. r0, r0, 30
    bne CoinParticle_Update_L_80130F8C
    lis r4, lbl_80495A94@ha
    lis r3, lbl_80495994@ha
    mr r31, r28
    li r29, 0x0
    addi r24, r4, lbl_80495A94@l
    addi r25, r3, lbl_80495994@l
    b CoinParticle_Update_L_80130F48
    CoinParticle_Update_L_80130E84:
    lwz r4, 0x10(r26)
    lwz r3, 0xc(r26)
    lwz r0, 0x0(r31)
    slwi r4, r4, 2
    slwi r3, r3, 2
    lfsx f31, r24, r4
    cmpwi r0, 0x0
    lfsx f1, r25, r3
    blt CoinParticle_Update_L_80130EB0
    li r0, 0x0
    b CoinParticle_Update_L_80130EF8
    CoinParticle_Update_L_80130EB0:
    lfs f0, lbl_806D7230(r2)
    li r0, 0x0
    stw r0, 0x0(r31)
    fmuls f30, f0, f1
    fmr f1, f30
    bl LUT_Sin12Bit
    lfs f2, lbl_806D7190(r2)
    lfs f0, lbl_806D7138(r2)
    fmuls f2, f2, f1
    fmuls f0, f0, f31
    fmr f1, f30
    stfs f2, 0x4(r31)
    stfs f0, 0x8(r31)
    bl fn_80186960
    lfs f0, lbl_806D7190(r2)
    li r0, 0x1
    fmuls f0, f0, f1
    stfs f0, 0xc(r31)
    CoinParticle_Update_L_80130EF8:
    clrlwi r0, r0, 24
    cmplwi r0, 0x1
    bne CoinParticle_Update_L_80130F40
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
    b CoinParticle_Update_L_80130F54
    CoinParticle_Update_L_80130F40:
    addi r31, r31, 0x10
    addi r29, r29, 0x1
    CoinParticle_Update_L_80130F48:
    lwz r0, 0x89c(r26)
    cmpw r29, r0
    blt CoinParticle_Update_L_80130E84
    CoinParticle_Update_L_80130F54:
    lwz r3, 0xc(r26)
    addi r0, r3, 0x1
    cmpwi r0, 0x40
    stw r0, 0xc(r26)
    blt CoinParticle_Update_L_80130F70
    li r0, 0x0
    stw r0, 0xc(r26)
    CoinParticle_Update_L_80130F70:
    lwz r3, 0x10(r26)
    addi r0, r3, 0x1
    cmpwi r0, 0x30
    stw r0, 0x10(r26)
    blt CoinParticle_Update_L_80130F8C
    li r0, 0x0
    stw r0, 0x10(r26)
    CoinParticle_Update_L_80130F8C:
    lwz r3, 0x1c(r30)
    addi r0, r3, 0x1
    cmpwi r0, 0x64
    stw r0, 0x1c(r30)
    blt CoinParticle_Update_L_80130FA8
    li r0, 0x0
    stw r0, 0x14(r30)
    CoinParticle_Update_L_80130FA8:
    addi r27, r27, 0x1
    addi r30, r30, 0x16c
    cmpwi r27, 0x6
    blt CoinParticle_Update_L_80130D58
    psq_l f31, 0x48(r1), 0, 0
    lfd f31, 0x40(r1)
    psq_l f30, 0x38(r1), 0, 0
    lfd f30, 0x30(r1)
    lmw r24, 0x10(r1)
    lwz r0, 0x54(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}

extern "C" asm void CoinParticleManager_Destroy(void) { /* 0x80130FDC size:0x80 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 0x8(r1)
    mr. r30, r3
    beq CoinParticleManager_Destroy_L_80131040
    lis r3, lbl_8048E3C0@ha
    addi r0, r3, lbl_8048E3C0@l
    stw r0, 0x0(r30)
    beq CoinParticleManager_Destroy_L_80131030
    lis r3, lbl_8048E34C@ha
    li r4, 0x1
    addi r0, r3, lbl_8048E34C@l
    stw r0, 0x0(r30)
    lwz r3, 0x4(r30)
    bl Object_DtorWithGXSync
    lwz r3, 0x8(r30)
    li r4, 0x1
    bl Object_DtorWithGXSync
    CoinParticleManager_Destroy_L_80131030:
    extsh. r0, r31
    ble CoinParticleManager_Destroy_L_80131040
    mr r3, r30
    bl MemoryManager_TimedFree
    CoinParticleManager_Destroy_L_80131040:
    lwz r0, 0x14(r1)
    mr r3, r30
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void CGameCoin_ProcessInput(void) { /* 0x8013105C size:0x374 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stmw r25, 0x14(r1)
    mr r27, r3
    bl StrPcb_GetInstance
    lfs f1, 0x48(r3)
    lfs f0, lbl_806D7140(r2)
    fcmpo cr0, f1, f0
    blt CGameCoin_ProcessInput_L_801310A8
    lwz r3, 0xc(r27)
    subic. r0, r3, 0x1
    stw r0, 0xc(r27)
    bgt CGameCoin_ProcessInput_L_801310A8
    bl StrPcb_GetInstance
    cmplwi r3, 0x0
    beq CGameCoin_ProcessInput_L_801310A8
    li r4, 0x0
    bl StrPcb_ResetCommands_Neutral
    CGameCoin_ProcessInput_L_801310A8:
    lbz r0, 0x4(r27)
    cmplwi r0, 0x0
    beq CGameCoin_ProcessInput_L_801313BC
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    li r0, 0x0
    mr r30, r3
    stw r0, 0x14(r27)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    lfs f0, lbl_806D7194(r2)
    li r4, -0x3
    li r5, 0x3
    fmuls f0, f0, f1
    fctiwz f0, f0
    stfd f0, 0x8(r1)
    lwz r3, 0xc(r1)
    bl Clamp_Int
    lwz r28, 0x8(r27)
    mr r31, r3
    li r25, 0x0
    li r29, 0x0
    CGameCoin_ProcessInput_L_8013110C:
    cmpw r28, r31
    ble CGameCoin_ProcessInput_L_8013111C
    subi r28, r28, 0x1
    b CGameCoin_ProcessInput_L_80131124
    CGameCoin_ProcessInput_L_8013111C:
    bge CGameCoin_ProcessInput_L_80131124
    addi r28, r28, 0x1
    CGameCoin_ProcessInput_L_80131124:
    lwz r3, 0x8(r27)
    bl abs
    mr r26, r3
    mr r3, r28
    bl abs
    cmpwi r3, 0x3
    bge CGameCoin_ProcessInput_L_80131150
    cmpwi r3, 0x0
    beq CGameCoin_ProcessInput_L_8013115C
    bge CGameCoin_ProcessInput_L_80131170
    b CGameCoin_ProcessInput_L_8013122C
    CGameCoin_ProcessInput_L_80131150:
    cmpwi r3, 0x5
    bge CGameCoin_ProcessInput_L_8013122C
    b CGameCoin_ProcessInput_L_801311D4
    CGameCoin_ProcessInput_L_8013115C:
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x6(r27)
    stw r0, 0x10(r27)
    b CGameCoin_ProcessInput_L_8013122C
    CGameCoin_ProcessInput_L_80131170:
    cmpwi r26, 0x0
    bgt CGameCoin_ProcessInput_L_8013118C
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x6(r27)
    stw r0, 0x10(r27)
    b CGameCoin_ProcessInput_L_8013122C
    CGameCoin_ProcessInput_L_8013118C:
    cmpwi r26, 0x2
    bgt CGameCoin_ProcessInput_L_8013122C
    lwz r0, 0x10(r27)
    cmpwi r0, 0x0
    bgt CGameCoin_ProcessInput_L_8013122C
    lbz r0, 0x6(r27)
    cmplwi r0, 0x1
    bne CGameCoin_ProcessInput_L_801311C4
    li r3, 0x0
    li r0, 0x28
    stb r3, 0x6(r27)
    li r29, 0x1
    stw r0, 0x10(r27)
    b CGameCoin_ProcessInput_L_801311CC
    CGameCoin_ProcessInput_L_801311C4:
    li r0, 0xa
    stw r0, 0x10(r27)
    CGameCoin_ProcessInput_L_801311CC:
    li r25, 0x1
    b CGameCoin_ProcessInput_L_8013122C
    CGameCoin_ProcessInput_L_801311D4:
    cmpwi r26, 0x2
    bgt CGameCoin_ProcessInput_L_801311F0
    li r3, 0x1
    li r0, 0x8
    stb r3, 0x6(r27)
    stw r0, 0x10(r27)
    b CGameCoin_ProcessInput_L_8013122C
    CGameCoin_ProcessInput_L_801311F0:
    lwz r0, 0x10(r27)
    cmpwi r0, 0x0
    bgt CGameCoin_ProcessInput_L_8013122C
    lbz r0, 0x6(r27)
    cmplwi r0, 0x1
    bne CGameCoin_ProcessInput_L_80131220
    li r3, 0x0
    li r0, 0x6
    stb r3, 0x6(r27)
    li r29, 0x1
    stw r0, 0x10(r27)
    b CGameCoin_ProcessInput_L_80131228
    CGameCoin_ProcessInput_L_80131220:
    li r0, 0x6
    stw r0, 0x10(r27)
    CGameCoin_ProcessInput_L_80131228:
    li r25, 0x1
    CGameCoin_ProcessInput_L_8013122C:
    cmpw r28, r31
    stw r28, 0x8(r27)
    bne CGameCoin_ProcessInput_L_8013110C
    lwz r3, 0x10(r27)
    cmpwi r3, 0x0
    ble CGameCoin_ProcessInput_L_8013124C
    subi r0, r3, 0x1
    stw r0, 0x10(r27)
    CGameCoin_ProcessInput_L_8013124C:
    clrlwi r0, r25, 24
    cmplwi r0, 0x1
    bne CGameCoin_ProcessInput_L_80131278
    cmpwi r31, 0x0
    ble CGameCoin_ProcessInput_L_8013126C
    li r0, 0x1
    stw r0, 0x14(r27)
    b CGameCoin_ProcessInput_L_80131278
    CGameCoin_ProcessInput_L_8013126C:
    bge CGameCoin_ProcessInput_L_80131278
    li r0, -0x1
    stw r0, 0x14(r27)
    CGameCoin_ProcessInput_L_80131278:
    clrlwi r0, r29, 24
    cmplwi r0, 0x1
    bne CGameCoin_ProcessInput_L_801312BC
    li r0, 0x0
    stw r0, 0xc(r27)
    bl StrPcb_GetInstance
    lfs f1, 0x48(r3)
    lfs f0, lbl_806D7140(r2)
    fcmpo cr0, f1, f0
    blt CGameCoin_ProcessInput_L_801312BC
    li r0, 0x2
    stw r0, 0xc(r27)
    bl StrPcb_GetInstance
    cmplwi r3, 0x0
    beq CGameCoin_ProcessInput_L_801312BC
    li r4, 0x0
    bl StrPcb_ResetCommands_Zero
    CGameCoin_ProcessInput_L_801312BC:
    li r0, 0x0
    mr r3, r30
    stw r0, 0x20(r27)
    li r25, 0x0
    li r4, 0x2000
    lwz r12, 0x0(r30)
    lwz r12, 0x2c(r12)
    mtctr r12
    bctrl
    cmplwi r3, 0x0
    beq CGameCoin_ProcessInput_L_801312F8
    lwz r3, 0x20(r27)
    lwz r0, lbl_806D7268(r2)
    or r0, r3, r0
    stw r0, 0x20(r27)
    CGameCoin_ProcessInput_L_801312F8:
    mr r3, r30
    lwz r12, 0x0(r30)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    lfs f0, lbl_806D7270(r2)
    fcmpo cr0, f1, f0
    ble CGameCoin_ProcessInput_L_80131328
    lwz r3, 0x20(r27)
    lwz r0, lbl_806D726C(r2)
    or r0, r3, r0
    stw r0, 0x20(r27)
    CGameCoin_ProcessInput_L_80131328:
    lwz r3, 0x20(r27)
    lwz r0, 0x24(r27)
    andc. r0, r3, r0
    beq CGameCoin_ProcessInput_L_80131340
    li r25, 0x1
    b CGameCoin_ProcessInput_L_8013138C
    CGameCoin_ProcessInput_L_80131340:
    mr r3, r30
    lwz r12, 0x0(r30)
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl
    lfs f0, lbl_806D7270(r2)
    fcmpo cr0, f1, f0
    ble CGameCoin_ProcessInput_L_80131368
    li r25, 0x2
    b CGameCoin_ProcessInput_L_8013138C
    CGameCoin_ProcessInput_L_80131368:
    mr r3, r30
    li r4, 0x400
    lwz r12, 0x0(r30)
    lwz r12, 0x2c(r12)
    mtctr r12
    bctrl
    cmplwi r3, 0x0
    beq CGameCoin_ProcessInput_L_8013138C
    li r25, 0x3
    CGameCoin_ProcessInput_L_8013138C:
    lwz r0, 0x1c(r27)
    cmpw r25, r0
    bne CGameCoin_ProcessInput_L_801313AC
    cmpwi r25, 0x1
    stw r25, 0x1c(r27)
    beq CGameCoin_ProcessInput_L_801313B0
    li r25, 0x0
    b CGameCoin_ProcessInput_L_801313B0
    CGameCoin_ProcessInput_L_801313AC:
    stw r25, 0x1c(r27)
    CGameCoin_ProcessInput_L_801313B0:
    lwz r0, 0x20(r27)
    stw r0, 0x24(r27)
    stw r25, 0x18(r27)
    CGameCoin_ProcessInput_L_801313BC:
    lmw r25, 0x14(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

