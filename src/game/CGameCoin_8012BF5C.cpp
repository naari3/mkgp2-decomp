
/* sdata symbols referenced from asm */
extern char lbl_806D7174[7];
extern char lbl_806D717C[5];
/*
 * 0x8012BF5C..0x801313D0: coin game, boss Koopa, shells and coin particles.
 */
#pragma cplusplus on

struct CoinVObj {
    virtual ~CoinVObj();
};

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
extern void Object_RenderJObjTree(void *, int);
extern void Object_SetAnimBinding();
extern void Object_SetColorAlphaOnly(void *, int, float);
extern void PSMTXConcat(float (*)[4], float (*)[4], float (*)[4]);
extern void PSMTXRotRad(float (*)[4], char, float);
extern void PSMTXScale(float (*)[4], float, float, float);
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
extern CoinVObj *lbl_806D109C;
extern CoinVObj *lbl_806D10AC;
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
extern void *GetInputManager(void);
extern void *GetRaceContextPtr(void);
extern void HSD_JObjSetMtxDirtySub(struct CoinJObj *);
extern void HSD_JObjSetupMatrixSub(struct CoinJObj *);
extern void HUD_FrameUpdate();
extern void InputCmd_GetDetectedFlag();
extern void InputCmd_PushSample();
extern void InputCmd_TickAndDetectAndClear();
extern struct CoinInputPlayer *InputMgr_GetPlayer(void *, int);
extern void Input_IsItemButtonPressed();
extern void IsCardValid();
extern unsigned char IsRaceStarted(void);
extern void ItemEffectBus_ApplyItemEventClear();
extern void ItemEffectBus_ApplyItemEventSet();
extern void ItemEffectBus_SnapshotAndFullReset();
extern void ItemEffectBus_TickTornadoCooldown();
extern void ItemObjectManager_PerFrameUpdate();
extern void ItemObjectManager_Update();
extern float LUT_Sin12Bit(float);
extern void LakituStart_UpdateCountdown();
extern void NokoNokoChallenge_CalcResultText();
extern void NokoNokoChallenge_GetCoinDivisor();
extern void NokoNokoChallenge_SaveResult();
extern void NokoNokoChallenge_TransitionToResult();
extern void Object_SetByte10_Return1();
extern void PSMTXCopy(float (*)[4], float (*)[4]);
extern void PSMTXTrans();
extern void PSVECSquareMag();
extern void RenderObj_ItemStateMachine_Timed();
extern void RumbleUpdate();
extern void SetCoinCount();
extern void SetCourseScene3D(void *);
extern void SetRumbleMode();
extern void Sinf_LUT_Wrap();
extern void SoundMgr_Play(int);
extern void SoundMgr_PlaySE(int);
extern void SoundObj_PlaySE();
extern void SoundObj_PlaySE_Direct();
extern void SoundVolumePan_Update();
extern void TornadoEffect_ApplyItemVisual_Primary();
extern void TornadoEffect_ApplyItemVisual_Secondary();
extern void TornadoEffect_ClearFlagC0AndSetC4();
extern void TornadoEffect_SetFlagC0();
extern void TornadoEffect_Tick();
extern void TransitionEffect_Tick();
extern void Vec3_Normalize(struct CoinVec *, struct CoinVec *);
extern void Vec3_Subtract();
extern void VfxSlotMgr_Update();
extern void __assert(const char *, int, const char *);
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
extern unsigned char fn_8016C360(int);
extern void fn_8016C394(int);
extern void fn_8016C554();
extern void fn_8016DA78();
extern void fn_8016DC90();
extern void fn_8016DEF4();
extern void fn_8016DF50();
extern void fn_8016EC80();
extern void fn_801734B0();
extern void fn_80173500();
extern void fn_8017351C();
extern void fn_80182B50(void *, float, float);
extern void fn_80192688();
extern void fn_80253C40();
extern void fn_80253C74();
extern void fn_80253FD8();
extern unsigned int g_lakituStartAnimDone;
extern unsigned int g_pInputState;
extern unsigned int g_raceEnded;
extern unsigned int g_raceTimeRemaining;
extern void *g_weatherSystem;
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
extern char lbl_80356730[];
extern void HSD_CObjAnim(void *);
extern void HSD_CObjReqAnim(void *, float);
extern void HSD_JObjClearFlagsAll(struct CoinJObj *, int);
extern void HSD_JObjSetFlagsAll(struct CoinJObj *, int);
extern void Object_SetField8_AndDirty(void *, float);
extern float Saturate_Double(float, float, float);
extern void clNormal3D_Exec(void *);
extern int g_characterId;
extern unsigned int lbl_806D720C;
extern unsigned int lbl_806D7210;
extern unsigned int lbl_806D7214;
extern unsigned int lbl_806D7218;
extern unsigned int lbl_806D721C;
extern unsigned int lbl_806D7220;
extern unsigned int lbl_806D7224;
extern unsigned int lbl_806D7228;
extern unsigned int lbl_806D722C;
extern char lbl_80356C58[];
extern unsigned int lbl_806D7134;
extern unsigned int lbl_806D7234;
extern unsigned int lbl_806D7238;
extern unsigned int lbl_806D723C;
extern unsigned int lbl_806D7240;
extern unsigned int lbl_806D7244;
extern unsigned int lbl_806D7248;
extern unsigned int lbl_806D724C;
extern unsigned int lbl_806D7250;
extern float lbl_80495994[];
extern float lbl_80495A94[];
extern void PSMTXMultVec(float (*)[4], struct CoinVec *, struct CoinVec *);
extern float Vec3_Dot(struct CoinVec *, struct CoinVec *);
extern float lbl_806CF578;
extern float lbl_806CF57C;
extern float lbl_806CF580;
extern float lbl_806CF584;
extern float lbl_806CF588;
extern int lbl_806D1510;
extern unsigned int lbl_806D7254;
extern unsigned int lbl_806D7258;
extern unsigned int lbl_806D725C;
extern unsigned char fn_80123480(void *, struct CoinVec *);
extern void fn_80172844(void *);
extern unsigned int lbl_806D7260;
extern unsigned int lbl_806D7264;
extern void AudioChannel_DtorWithSeStop(void *, int);
extern void ClRomTable_PurgeAll(void);
extern void CourseEnvironment_Dtor(void *, int);
extern void InputCmd_Dtor(void *, int);
extern void ItemObjectManager_Reset(void);
extern void KartDriver_Dtor(void *, int);
extern void LakituStart_Dtor(void *, int);
extern void MemoryManager_TimedFree(void *);
extern void Object_DtorWithGXSync(void *, int);
extern void RankingTable_Init(void *);
extern void SceneDrawList_Reset(void);
extern void SetActiveCamera(void *, int);
extern void SetPlayerCarObject(void *);
extern void SetResourceLoadingFlag(unsigned char);
extern void VfxSlotMgr_Shutdown(void);
extern void VisualEffectHolder_Dtor(void *, int);
extern void clRom_PurgeAll(void);
extern void dtor_80122FD8(void *, int);
extern void fn_80123B48(void *, int);
extern void fn_80124C84(void *, int);
extern void fn_8012B394(void *, int);
extern void fn_80169C44(void);
extern void fn_8016C634(void *, int);
extern void fn_8016DFAC(void *, int);
extern void fn_8016EFA8(void *, int);
extern void fn_80173550(void *, int);
extern void fn_80254134(void *, int);
extern void *g_raceCamera;
extern CoinVObj *lbl_806D10D0;
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
extern struct CoinStrPcb *StrPcb_GetInstance(void);
extern void StrPcb_ResetCommands_Neutral(struct CoinStrPcb *, int);
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
extern void HSD_CObjAddAnim(void *, void *);
extern struct CoinJObj *ResolveJointByName(void *, const char *);
extern void clNormal3D_SetScale(void *, int, float, float, float, float);
extern unsigned int lbl_80419EF8[];
extern unsigned long OSGetTick(void);
extern void Object_SetJObjPositionXYZ(void *, float, float, float);
extern float lbl_806CF570;
extern float lbl_806CF574;
extern void PSMTXIdentity(float (*)[4]);
extern void *LinkedNode_GetField10_OrFallback(void *, int);
extern void Object_RenderJObjEx(void *, void *, int);
extern void Object_SetJObjPositionVec(void *, void *);
extern void Object_SetJObjRotationY(void *, float);
extern void Object_SetJObjScaleXYZ(void *, float, float, float);
extern unsigned int lbl_806D7130;
extern unsigned int lbl_806D713C;
extern float fn_80186960(float);
extern unsigned int lbl_806D7230;
extern int Clamp_Int(int, int, int);
extern void StrPcb_ResetCommands_Zero(struct CoinStrPcb *, int);
extern int abs(int);
extern const unsigned int lbl_806D7268;
extern const unsigned int lbl_806D726C;
extern unsigned int lbl_806D7270;
asm void fn_8012BF5C(void);
asm void CGameCoin_Draw(void);
asm void CGameCoin_Update(void);
struct DefeatDemo;
void DefeatDemo_Update(DefeatDemo *self);
struct BossKoopa;
void BossKoopa_UpdateAnim(BossKoopa *self);
struct KoopaFireball;
void KoopaFireball_Update(KoopaFireball *self);
struct CoinShell;
void Shell_UpdateState(CoinShell *self);
struct CGameCoin;
CGameCoin *CGameCoin_Destroy(CGameCoin *self, short flag);
asm void CGameCoin_Init(void);
void CGameCoin_InitDefeatDemo(void);
void BossKoopa_Init(void);
struct CGameCoinFields;
void CGameCoin_InitFields(CGameCoinFields *self);
struct CoinParticleManager;
void CoinParticle_Draw(CoinParticleManager *self);
void CoinParticle_Update(CoinParticleManager *self);
CoinParticleManager *CoinParticleManager_Destroy(CoinParticleManager *self, short flag);
asm void CGameCoin_ProcessInput(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_fn_8012BF5C = { 0x288A0000, 0x000001C4, 0x003B0010, 0x00000000, 0x82000008, (void *)&dtor_8007D9C4 };

__declspec(section ".extab_user") static const unsigned char extab_CGameCoin_Draw[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_CGameCoin_Update[8] = {
    0x38, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; unsigned int f29; unsigned int f30; unsigned int f31; unsigned int f32; unsigned int f33; unsigned int f34; unsigned int f35; unsigned int f36; unsigned int f37; unsigned int f38; unsigned int f39; unsigned int f40; unsigned int f41; unsigned int f42; unsigned int f43; unsigned int f44; unsigned int f45; unsigned int f46; unsigned int f47; unsigned int f48; unsigned int f49; unsigned int f50; unsigned int f51; unsigned int f52; unsigned int f53; unsigned int f54; unsigned int f55; unsigned int f56; unsigned int f57; unsigned int f58; unsigned int f59; unsigned int f60; unsigned int f61; unsigned int f62; unsigned int f63; unsigned int f64; unsigned int f65; unsigned int f66; unsigned int f67; unsigned int f68; unsigned int f69; unsigned int f70; unsigned int f71; unsigned int f72; unsigned int f73; unsigned int f74; unsigned int f75; unsigned int f76; unsigned int f77; unsigned int f78; unsigned int f79; unsigned int f80; unsigned int f81; unsigned int f82; unsigned int f83; unsigned int f84; unsigned int f85; unsigned int f86; unsigned int f87; unsigned int f88; unsigned int f89; unsigned int f90; void *f91; unsigned int f92; unsigned int f93; void *f94; unsigned int f95; void *f96; unsigned int f97; unsigned int f98; void *f99; unsigned int f100; void *f101; unsigned int f102; unsigned int f103; void *f104; unsigned int f105; void *f106; unsigned int f107; unsigned int f108; void *f109; unsigned int f110; void *f111; unsigned int f112; unsigned int f113; void *f114; unsigned int f115; void *f116; unsigned int f117; unsigned int f118; void *f119; unsigned int f120; void *f121; unsigned int f122; unsigned int f123; void *f124; unsigned int f125; void *f126; unsigned int f127; unsigned int f128; void *f129; unsigned int f130; void *f131; unsigned int f132; unsigned int f133; void *f134; unsigned int f135; void *f136; unsigned int f137; unsigned int f138; void *f139; unsigned int f140; void *f141; unsigned int f142; void *f143; unsigned int f144; unsigned int f145; void *f146; unsigned int f147; void *f148; unsigned int f149; unsigned int f150; void *f151; unsigned int f152; unsigned int f153; void *f154; unsigned int f155; unsigned int f156; void *f157; unsigned int f158; void *f159; unsigned int f160; unsigned int f161; void *f162; unsigned int f163; void *f164; unsigned int f165; unsigned int f166; void *f167; unsigned int f168; void *f169; unsigned int f170; unsigned int f171; void *f172; unsigned int f173; void *f174; unsigned int f175; void *f176; unsigned int f177; unsigned int f178; void *f179; unsigned int f180; void *f181; unsigned int f182; unsigned int f183; void *f184; unsigned int f185; unsigned int f186; void *f187; } extab_CGameCoin_Init = { 0x284A0000, 0x00000058, 0x000A0170, 0x0000008C, 0x00000168, 0x000000A8, 0x00020170, 0x000000C0, 0x0000017C, 0x000000C8, 0x000C0170, 0x00000108, 0x00080190, 0x00000140, 0x00000170, 0x00000168, 0x000001A4, 0x0000017C, 0x00060170, 0x000001B4, 0x000001B8, 0x000001C4, 0x00020170, 0x000001E0, 0x000001CC, 0x000001EC, 0x00000170, 0x0000020C, 0x000001E0, 0x00000218, 0x00000170, 0x0000022C, 0x000401F4, 0x00000248, 0x00000170, 0x00000254, 0x00000208, 0x00000260, 0x00020170, 0x00000278, 0x0000021C, 0x0000028C, 0x002A0170, 0x00000388, 0x00000238, 0x00000394, 0x00000230, 0x000003A0, 0x00000238, 0x000003B4, 0x0000024C, 0x000003C8, 0x00040238, 0x000003EC, 0x00000258, 0x000003FC, 0x00000170, 0x00000414, 0x00000264, 0x00000420, 0x00000170, 0x0000042C, 0x00000278, 0x00000438, 0x00000170, 0x00000444, 0x0000028C, 0x00000450, 0x00000170, 0x0000045C, 0x000002A0, 0x0000046C, 0x00130170, 0x000004E8, 0x000002BC, 0x000004FC, 0x000002B4, 0x00000510, 0x000202BC, 0x0000052C, 0x000002D0, 0x00000538, 0x000202BC, 0x00000698, 0x00000170, 0x000006A8, 0x000002DC, 0x000006B4, 0x00250170, 0x00000000, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x01000238, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x01000238, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x010002BC, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8 };

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

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CGameCoin_Init = {
    (void *)&CGameCoin_Init, 0x0000078C, (void *)&extab_CGameCoin_Init
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
    la r3, lbl_806D7174(r2)  /* lbl_806D7174 */
    li r4, 0x47c
    la r5, lbl_806D717C(r2)  /* lbl_806D717C */
    bl __assert
    CGameCoin_Update_L_8012C8F4:
    cmplwi r27, 0x0
    beq CGameCoin_Update_L_8012C93C
    bne CGameCoin_Update_L_8012C910
    la r3, lbl_806D7174(r2)  /* lbl_806D7174 */
    li r4, 0x25d
    la r5, lbl_806D717C(r2)  /* lbl_806D717C */
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
    la r3, lbl_806D7174(r2)  /* lbl_806D7174 */
    li r4, 0x47c
    la r5, lbl_806D717C(r2)  /* lbl_806D717C */
    bl __assert
    CGameCoin_Update_L_8012CB0C:
    cmplwi r27, 0x0
    beq CGameCoin_Update_L_8012CB54
    bne CGameCoin_Update_L_8012CB28
    la r3, lbl_806D7174(r2)  /* lbl_806D7174 */
    li r4, 0x25d
    la r5, lbl_806D717C(r2)  /* lbl_806D717C */
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
    la r3, lbl_806D7174(r2)  /* lbl_806D7174 */
    li r4, 0x2b8
    la r5, lbl_806D717C(r2)  /* lbl_806D717C */
    bl __assert
    CGameCoin_Update_L_8012DA04:
    lwz r0, 0x14(r27)
    rlwinm. r0, r0, 0, 14, 14
    beq CGameCoin_Update_L_8012DA20
    addi r5, r31, 0x528
    la r3, lbl_806D7174(r2)  /* lbl_806D7174 */
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
    la r3, lbl_806D7174(r2)  /* lbl_806D7174 */
    li r4, 0x25d
    la r5, lbl_806D717C(r2)  /* lbl_806D717C */
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
    la r3, lbl_806D7174(r2)  /* lbl_806D7174 */
    li r4, 0x2b8
    la r5, lbl_806D717C(r2)  /* lbl_806D717C */
    bl __assert
    CGameCoin_Update_L_8012DA98:
    lwz r0, 0x14(r27)
    rlwinm. r0, r0, 0, 14, 14
    beq CGameCoin_Update_L_8012DAB4
    addi r5, r31, 0x528
    la r3, lbl_806D7174(r2)  /* lbl_806D7174 */
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
    la r3, lbl_806D7174(r2)  /* lbl_806D7174 */
    li r4, 0x25d
    la r5, lbl_806D717C(r2)  /* lbl_806D717C */
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

struct CoinVec {
    float x;
    float y;
    float z;
};

struct CoinQuat {
    float x;
    float y;
    float z;
    float w;
};

struct CoinJObj {
    unsigned char pad0[0x14];
    unsigned int flags;
    unsigned char pad18[0x4];
    CoinQuat rotate;
    CoinVec scale;
    CoinVec translate;
    float mtx[3][4];
};

struct CoinNormal3D {
    unsigned char opaque[0x5C];
    CoinNormal3D(const char *path, int flags);
};

struct CoinAnimLeaf {
    void *value;
};

struct CoinAnimNode {
    void *opaque;
    CoinAnimLeaf *next;
};

struct CoinAnimDesc {
    void *opaque;
    CoinAnimNode *next;
};

static inline void *CoinAnimLeaf_Value(CoinAnimLeaf *leaf) {
    if (leaf == 0) return 0;
    return leaf->value;
}

static inline void *CoinAnimNode_Value(CoinAnimNode *node) {
    if (node == 0) return 0;
    return CoinAnimLeaf_Value(node->next);
}

static inline void *CoinAnimDesc_Value(CoinAnimDesc *desc) {
    if (desc == 0) return 0;
    return CoinAnimNode_Value(desc->next);
}

struct CoinScene3D : CoinVObj {
    CoinScene3D(const char *path);
    virtual ~CoinScene3D();
    void *cobj;
    unsigned char pad8[0x24];
    CoinAnimDesc *animDesc;
    unsigned char pad30[0x3054];
    unsigned char animFirst;
    float animSpeed;
    float animFrame;
};

struct CoinAnimScene3D : CoinScene3D {
    CoinAnimScene3D(const char *path) : CoinScene3D(path) {
        animSpeed = -1.0f;
        animFrame = 0.0f;
    }
    virtual void key();
    void Start() {
        if (cobj) {
            animFirst = 1;
            animFrame = 0.0f;
            animSpeed = 1.0f;
            HSD_CObjAddAnim(cobj, CoinAnimDesc_Value(animDesc));
            HSD_CObjReqAnim(cobj, animFrame);
            HSD_CObjAnim(cobj);
        }
    }
};

struct DefeatDemo {
    void *body;
    void *hand;
    void *effect;
    CoinScene3D *scene;
    float frame;
    unsigned char first;
    void *spinA;
    void *spinB;
    void *spinC;
    CoinJObj *wheelA;
    CoinJObj *wheelB;
    float wheelAngleA;
    float wheelAngleB;
    CoinJObj *flash;

    DefeatDemo();
};

static inline void CoinJObj_SetMtxDirty(CoinJObj *jobj) {
    unsigned int flags;
    unsigned char dirty;

    if (jobj != 0) {
        if (jobj == 0) {
            __assert(lbl_806D7174, 0x25D, lbl_806D717C);
        }
        flags = jobj->flags;
        dirty = 0;
        if (!(flags & 0x00800000) && (flags & 0x40)) {
            dirty = 1;
        }
        if (!dirty) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

static inline void CoinJObj_SetRotationY(CoinJObj *jobj, float y) {
    if (jobj == 0) {
        __assert(lbl_806D7174, 0x2B8, lbl_806D717C);
    }
    if (jobj->flags & 0x00020000) {
        __assert(lbl_806D7174, 0x2B9, lbl_80356C58);
    }
    jobj->rotate.y = y;
    if (!(jobj->flags & 0x02000000)) {
        CoinJObj_SetMtxDirty(jobj);
    }
}

static inline void CoinJObj_SetScaleX(CoinJObj *jobj, float x) {
    if (jobj == 0) {
        __assert(lbl_806D7174, 0x325, lbl_806D717C);
    }
    jobj->scale.x = x;
    if (!(jobj->flags & 0x02000000)) {
        CoinJObj_SetMtxDirty(jobj);
    }
}

static inline void CoinJObj_SetScaleY(CoinJObj *jobj, float y) {
    if (jobj == 0) {
        __assert(lbl_806D7174, 0x333, lbl_806D717C);
    }
    jobj->scale.y = y;
    if (!(jobj->flags & 0x02000000)) {
        CoinJObj_SetMtxDirty(jobj);
    }
}

static inline void CoinJObj_SetScaleZ(CoinJObj *jobj, float z) {
    if (jobj == 0) {
        __assert(lbl_806D7174, 0x341, lbl_806D717C);
    }
    jobj->scale.z = z;
    if (!(jobj->flags & 0x02000000)) {
        CoinJObj_SetMtxDirty(jobj);
    }
}

static inline void CoinScene3D_SetAnimFrame(CoinScene3D *scene, float frame) {
    if (scene->animFrame < 0.0f || frame < 0.0f) {
        return;
    }
    scene->animFirst = 1;
    scene->animFrame = frame;
}

static inline void CoinScene3D_UpdateAnim(CoinScene3D *scene) {
    if (scene->animSpeed == -1.0f) {
        return;
    }
    if (scene->animFirst) {
        scene->animFirst = 0;
    } else {
        scene->animFrame += scene->animSpeed;
    }
    HSD_CObjReqAnim(scene->cobj, scene->animFrame);
    HSD_CObjAnim(scene->cobj);
}

extern "C" void DefeatDemo_Update(DefeatDemo *self) { /* 0x8012E69C size:0x5A8 */
    float s;

    if (self->first == 1) {
        self->first = 0;
    } else {
        self->frame += 1.0f;
        if (self->frame >= 270.0f) {
            self->frame = 269.0f;
        }
    }
    if (self->frame == 180.0f && g_characterId != 4) {
        SoundMgr_Play(0x13B);
    }
    CoinScene3D_SetAnimFrame(self->scene, self->frame);
    CoinScene3D_UpdateAnim(self->scene);
    Object_SetField8_AndDirty(self->body, self->frame);
    clNormal3D_Exec(self->body);
    Object_SetField8_AndDirty(self->hand, self->frame);
    clNormal3D_Exec(self->hand);
    Object_SetField8_AndDirty(self->effect, self->frame);
    clNormal3D_Exec(self->effect);
    fn_80182B50(self->spinA, 0.0f, 0.002f);
    fn_80182B50(self->spinB, 0.0f, -0.002f);
    fn_80182B50(self->spinC, 0.0f, -0.002f);
    self->wheelAngleA += 0.00087266444f;
    if (self->wheelAngleA >= 6.283184f) {
        self->wheelAngleA -= 6.283184f;
    }
    self->wheelAngleB += 0.0005817763f;
    if (self->wheelAngleB >= 6.283184f) {
        self->wheelAngleB -= 6.283184f;
    }
    CoinJObj_SetRotationY(self->wheelA, self->wheelAngleA);
    CoinJObj_SetRotationY(self->wheelB, self->wheelAngleB);
    if (self->frame < 192.0f || self->frame > 230.0f) {
        HSD_JObjSetFlagsAll(self->flash, 0x10);
    } else {
        HSD_JObjClearFlagsAll(self->flash, 0x10);
        s = Saturate_Double((self->frame - 192.0f) / 3.0f, 0.0f, 1.0f);
        CoinJObj_SetScaleX(self->flash, 0.5f * s + 0.5f);
        CoinJObj_SetScaleZ(self->flash, 0.5f * s + 0.5f);
        if (self->frame < 198.0f) {
            CoinJObj_SetScaleY(self->flash, 8.0f * Saturate_Double((self->frame - 192.0f) / 6.0f, 0.0f, 1.0f) + 1.0f);
        } else {
            CoinJObj_SetScaleY(self->flash, 9.0f - 8.8f * Saturate_Double((self->frame - 198.0f) / 32.0f, 0.0f, 1.0f));
        }
    }
}

struct KoopaFlame {
    float life;
    CoinVec vel;
    CoinVec pos;
    float scale;
    float alpha;
    float grow;
};

struct KoopaFireball {
    void *model;
    CoinJObj *jobj;
    float angle;
    int cooldown;
    unsigned char active;
    int rnd64;
    int rnd48;
    unsigned char first;
    CoinVec dir;
    KoopaFlame flames[64];

    KoopaFireball(const char *modelPath) {
        int i;

        model = 0;
        jobj = 0;
        angle = 0.0f;
        cooldown = 0;
        active = 0;
        first = 1;
        rnd64 = 0;
        rnd48 = 0;
        dir.x = 0.0f;
        dir.y = 0.0f;
        dir.z = 0.0f;
        for (i = 0; i < 64; i++) {
            flames[i].life = -1.0f;
        }
        model = new CoinNormal3D(modelPath, 1);
    }
};

struct BossKoopa {
    void *anims[4];
    int state;
    int reqState;
    float frame;
    unsigned char justChanged;
    float timer;
    int attack;
    KoopaFireball *fireball;
    int wait;
    int waitMin;
    int waitMax;
    int waitRndIdx;
    int attackRndIdx;

    BossKoopa(int waitMin, int waitMax);
};

static inline void KoopaFireball_SetActive(KoopaFireball *fb, unsigned char on) {
    if (fb->active != on) {
        fb->active = on;
        if (fb->active) {
            fb->cooldown = 0;
            fb->first = 1;
        }
    }
}

static inline float BossKoopa_Rand64(BossKoopa *self) {
    if (self->waitRndIdx >= 64) {
        self->waitRndIdx = 0;
    }
    return lbl_80495994[self->waitRndIdx++];
}

static inline float BossKoopa_Rand48(BossKoopa *self) {
    if (self->attackRndIdx >= 48) {
        self->attackRndIdx = 0;
    }
    return lbl_80495A94[self->attackRndIdx++];
}

extern "C" void BossKoopa_UpdateAnim(BossKoopa *self) { /* 0x8012EC44 size:0x438 */
    float r;
    float t;

    if (self->state != self->reqState) {
        self->state = self->reqState;
        self->frame = 0.0f;
        self->justChanged = 1;
        self->timer = 0.0f;
        if (self->state == 0) {
            self->wait = (int)((self->waitMax - self->waitMin) * BossKoopa_Rand64(self) + self->waitMin);
        }
    }
    if (self->state == 4) {
        return;
    }
    if (self->justChanged) {
        self->justChanged = 0;
    } else {
        self->timer += 1.0f;
    }
    switch (self->state) {
    case 0:
        if (self->timer >= 60.0f) {
            self->timer = 0.0f;
        }
        self->frame = self->timer;
        if (IsRaceStarted()) {
            if (self->wait > 0) {
                self->wait--;
            } else {
                self->reqState = 1;
                r = BossKoopa_Rand48(self);
                if (r < 0.5f) {
                    self->attack = 0;
                } else if (r < 0.75f) {
                    self->attack = 1;
                } else {
                    self->attack = 2;
                }
            }
        }
        break;
    case 1:
        switch (self->attack) {
        case 0:
            self->frame = self->timer;
            if (self->timer > 198.0f) {
                self->reqState = 0;
            }
            break;
        case 1:
            self->frame = 1.2f * self->timer;
            if (self->timer > 165.0f) {
                self->reqState = 0;
            }
            break;
        case 2:
            t = self->timer;
            if (t < 60.0f) {
                self->frame = t;
            } else {
                self->frame = 0.75f * (t - 60.0f) + 60.0f;
            }
            if (self->timer > 244.0f) {
                self->reqState = 0;
            }
            break;
        case 3:
            t = self->timer;
            if (t <= 150.0f) {
                self->frame = t;
            } else if (t <= 200.0f) {
                self->frame = 150.0f - (t - 150.0f);
            } else {
                self->frame = t - 100.0f;
            }
            if (self->timer > 298.0f) {
                self->reqState = 0;
            }
            break;
        }
        break;
    case 2:
    case 3:
        self->frame = self->timer;
        if (self->timer >= 69.0f) {
            self->reqState = 1;
            self->attack = 3;
        }
        break;
    }
    Object_SetField8_AndDirty(self->anims[self->state], self->frame);
    clNormal3D_Exec(self->anims[self->state]);
    if (self->state == 1 && self->frame >= 60.0f && self->frame <= 150.0f) {
        KoopaFireball_SetActive(self->fireball, 1);
        if (!fn_8016C360(0x37)) {
            SoundMgr_PlaySE(0x37);
        }
    } else {
        KoopaFireball_SetActive(self->fireball, 0);
        if (fn_8016C360(0x37) == 1) {
            fn_8016C394(0x37);
        }
    }
    KoopaFireball_Update(self->fireball);
}

static inline void CoinJObj_SetupMatrix(CoinJObj *jobj) {
    unsigned int flags;
    unsigned char dirty;

    if (jobj == 0) {
        __assert(lbl_806D7174, 0x47C, lbl_806D717C);
    }
    if (jobj != 0) {
        if (jobj == 0) {
            __assert(lbl_806D7174, 0x25D, lbl_806D717C);
        }
        flags = jobj->flags;
        dirty = 0;
        if (!(flags & 0x00800000) && (flags & 0x40)) {
            dirty = 1;
        }
        if (dirty) {
            HSD_JObjSetupMatrixSub(jobj);
        }
    }
}

static inline float (*CoinJObj_GetMtxPtr(CoinJObj *jobj))[4] {
    CoinJObj_SetupMatrix(jobj);
    return jobj->mtx;
}

static inline float KoopaFireball_Rand64(KoopaFireball *self) {
    if (self->rnd64 >= 64) {
        self->rnd64 = 0;
    }
    return lbl_80495994[self->rnd64++];
}

static inline float KoopaFireball_Rand48(KoopaFireball *self) {
    if (self->rnd48 >= 48) {
        self->rnd48 = 0;
    }
    return lbl_80495A94[self->rnd48++];
}

extern "C" void KoopaFireball_Update(KoopaFireball *self) { /* 0x8012F07C size:0x3E0 */
    float (*mtx)[4];
    int i;
    float m[3][4];
    CoinVec d;
    float dot;

    if (self->jobj == 0) {
        return;
    }
    if (self->cooldown != 0) {
        self->cooldown--;
    }
    if (self->active) {
        mtx = CoinJObj_GetMtxPtr(self->jobj);
        for (i = 0; i < 64; i++) {
            if (self->flames[i].life < 0.0f) {
                self->flames[i].pos.x = mtx[0][3];
                self->flames[i].pos.y = mtx[1][3];
                self->flames[i].pos.z = mtx[2][3];
                self->flames[i].vel.x = mtx[0][2];
                self->flames[i].vel.y = mtx[1][2];
                self->flames[i].vel.z = mtx[2][2];
                PSMTXRotRad(m, 'X', 0.017453292f * self->angle);
                PSMTXMultVec(m, &self->flames[i].vel, &self->flames[i].vel);
                self->flames[i].scale = lbl_806CF57C * KoopaFireball_Rand64(self) + lbl_806CF578;
                self->flames[i].grow = lbl_806CF588 * KoopaFireball_Rand48(self) + lbl_806CF584;
                self->flames[i].alpha = 1.0f - 0.2f * KoopaFireball_Rand48(self);
                if (self->cooldown != 0) {
                    self->flames[i].alpha *= 0.5f;
                }
                self->flames[i].life = 0.0f;
                if (self->cooldown == 0) {
                    if (self->first) {
                        self->cooldown = lbl_806D1510;
                        self->first = 0;
                        self->dir.x = mtx[0][2];
                        self->dir.y = mtx[1][2];
                        self->dir.z = mtx[2][2];
                        Vec3_Normalize(&self->dir, &self->dir);
                    } else {
                        d.x = mtx[0][2];
                        d.y = mtx[1][2];
                        d.z = mtx[2][2];
                        Vec3_Normalize(&d, &d);
                        dot = Vec3_Dot(&d, &self->dir);
                        if (dot < 0.0f) {
                            dot = -dot;
                        }
                        if (dot > 0.999f) {
                            self->cooldown = lbl_806D1510;
                        } else {
                            self->cooldown = 0;
                        }
                        self->dir.x = d.x;
                        self->dir.y = d.y;
                        self->dir.z = d.z;
                    }
                }
                break;
            }
        }
    }
    for (i = 0; i < 64; i++) {
        if (self->flames[i].life >= 0.0f) {
            self->flames[i].pos.x += self->flames[i].vel.x * lbl_806CF580;
            self->flames[i].pos.y += self->flames[i].vel.y * lbl_806CF580;
            self->flames[i].pos.z += self->flames[i].vel.z * lbl_806CF580;
            if (self->flames[i].vel.y < 0.5f) {
                self->flames[i].vel.y += 0.01f;
                if (self->flames[i].vel.y > 0.5f) {
                    self->flames[i].vel.y = 0.5f;
                }
            }
            self->flames[i].scale += self->flames[i].grow;
            if ((self->flames[i].life += 1.0f) >= 64.0f) {
                self->flames[i].life = -1.0f;
            }
        }
    }
}

struct CoinShell {
    void *effect;
    int m4;
    int state;
    float t;
    float mtx[3][4];
    float alpha;
    CoinJObj *joint;
    void *ground;
    unsigned char landed;
    unsigned char pad4D[0xF];
    CoinVec vel;
    float speed;
};

static inline void Shell_AttachToJoint(CoinShell *self) {
    float (*jm)[4];
    float m[3][4];

    if (self->joint != 0) {
        jm = CoinJObj_GetMtxPtr(self->joint);
        PSMTXCopy(jm, self->mtx);
        PSMTXRotRad(m, 'Z', -1.5707964f);
        PSMTXConcat(self->mtx, m, self->mtx);
        PSMTXScale(m, 1.0f, 1.0f, 1.0f);
        PSMTXConcat(self->mtx, m, self->mtx);
        self->mtx[0][3] = 2.5f * self->mtx[0][1] + jm[0][3];
        self->mtx[1][3] = 2.5f * self->mtx[1][1] + jm[1][3];
        self->mtx[2][3] = 2.5f * self->mtx[2][1] + jm[2][3];
    }
}

static inline void Shell_UpdateRolling(CoinShell *self) {
    CoinVec pos;
    float m[3][4];

    self->t += 1.0f;
    pos.x = self->mtx[0][3];
    pos.y = self->mtx[1][3];
    pos.z = self->mtx[2][3];
    PSMTXScale(m, 1.0f, 1.0f, 1.0f);
    PSMTXConcat(self->mtx, m, self->mtx);
    PSMTXRotRad(m, 'Y', 0.5235988f);
    PSMTXConcat(self->mtx, m, self->mtx);
    pos.x = self->vel.x * self->speed + pos.x;
    pos.y = self->vel.y * self->speed + pos.y;
    pos.z = self->vel.z * self->speed + pos.z;
    self->mtx[0][3] = pos.x;
    self->mtx[1][3] = pos.y;
    self->mtx[2][3] = pos.z;
    if (!self->landed) {
        if (fn_80123480(self->ground, &pos) == 1) {
            self->landed = 1;
        }
    } else if (pos.y < -110.0f || !fn_80123480(self->ground, &pos)) {
        self->state = 5;
        self->t = 0.0f;
    }
}

extern "C" void Shell_UpdateState(CoinShell *self) { /* 0x8012F45C size:0x458 */
    if (self->state == 0) {
        return;
    }
    switch (self->state) {
    case 3:
        Shell_AttachToJoint(self);
        if (self->t < 60.0f) {
            self->t += 1.0f;
            self->alpha = Saturate_Double(self->t / 60.0f, 0.0f, 1.0f);
        }
        break;
    case 1:
        self->mtx[1][3] -= 0.2f;
        break;
    case 4:
        Shell_UpdateRolling(self);
        break;
    case 5:
        if (self->t < 30.0f) {
            self->t += 1.0f;
            self->alpha = -self->alpha * (self->t / 30.0f) + self->alpha;
        } else {
            self->state = 0;
            self->t = 0.0f;
            self->alpha = 0.0f;
        }
        break;
    case 6:
        if (self->t < 30.0f) {
            self->t += 1.0f;
            Shell_AttachToJoint(self);
            self->alpha = -self->alpha * (self->t / 30.0f) + self->alpha;
        } else {
            self->state = 0;
            self->t = 0.0f;
            self->alpha = 0.0f;
        }
        break;
    }
    fn_80172844(self->effect);
}

struct CoinHsdClassInfo {
    unsigned char pad0[0x30];
    void (*release)(struct CoinHsdObj *o);
    void (*destroy)(struct CoinHsdObj *o);
};

struct CoinHsdObj {
    CoinHsdClassInfo *info;
    unsigned short ref;
};

static inline int CoinHsdObj_RefDec(CoinHsdObj *o) {
    int ret = o->ref == (unsigned short)-1;
    if (ret) {
        return ret;
    }
    return o->ref-- == 0;
}

static inline void CoinHsdObj_Unref(CoinHsdObj *o) {
    if (o == 0) {
        return;
    }
    if (CoinHsdObj_RefDec(o)) {
        if (o != 0) {
            o->info->release(o);
            o->info->destroy(o);
        }
    }
}

struct CoinShellSet {
    void *model;
    void *jobj;
    unsigned char pad8[0x40];
    void *shells;
};

struct CGameCoin {
    void *vt;
    unsigned char pad4[0x4];
    void *input;
    void *driver;
    void *effects;
    void *audio;
    unsigned char pad18[0x30];
    void *m48;
    CoinShellSet *shellSet;
    void *lakitu;
    void *env;
    CoinVObj *scene;
    void *goalCam;
    CoinVObj *m60;
    CoinHsdObj *lights;
    void *hud;
    BossKoopa *koopa;
    void *m70;
    void *m74;
    DefeatDemo *defeatDemo;
    unsigned char pad7C[0x44];
    CoinVObj *camera;
};

static inline void CoinShellSet_Delete(CoinShellSet *set) {
    if (set != 0) {
        fn_80173550(set->model, 1);
        Object_DtorWithGXSync(set->jobj, 1);
        fn_80123B48(set->shells, 1);
        MemoryManager_TimedFree(set);
    }
}

static inline void KoopaFireball_Delete(KoopaFireball *fireball) {
    if (fireball != 0) {
        Object_DtorWithGXSync(fireball->model, 1);
        MemoryManager_TimedFree(fireball);
    }
}

static inline void BossKoopa_Delete(BossKoopa *koopa) {
    int i;

    if (koopa != 0) {
        KoopaFireball_Delete(koopa->fireball);
        for (i = 0; i < 4; i++) {
            Object_DtorWithGXSync(koopa->anims[i], 1);
        }
        if (fn_8016C360(0x37) == 1) {
            fn_8016C394(0x37);
        }
        MemoryManager_TimedFree(koopa);
    }
}

static inline void DefeatDemo_Delete(DefeatDemo *demo) {
    if (demo != 0) {
        Object_DtorWithGXSync(demo->body, 1);
        Object_DtorWithGXSync(demo->hand, 1);
        Object_DtorWithGXSync(demo->effect, 1);
        delete demo->scene;
        MemoryManager_TimedFree(demo);
    }
}

extern "C" CGameCoin *CGameCoin_Destroy(CGameCoin *self, short flag) { /* 0x8012F8B4 size:0x3A4 */

    if (self) {
        self->vt = vtable;
        delete self->camera;
        fn_80169C44();
        if (g_weatherSystem != 0) {
            fn_8016C634(g_weatherSystem, 1);
            g_weatherSystem = 0;
        }
        SetActiveCamera(0, 0);
        SetCourseScene3D(0);
        delete self->scene;
        LakituStart_Dtor(self->lakitu, 1);
        fn_80124C84(self->goalCam, 1);
        SetPlayerCarObject(0);
        KartDriver_Dtor(self->driver, 1);
        VisualEffectHolder_Dtor(self->effects, 1);
        AudioChannel_DtorWithSeStop(self->audio, 1);
        fn_8012B394(self->m48, 1);
        InputCmd_Dtor(self->input, 1);
        g_raceCamera = 0;
        if (self->m60 != 0) {
            delete self->m60;
        }
        if (self->lights != 0) {
            CoinHsdObj_Unref(self->lights);
        }
        CourseEnvironment_Dtor(self->env, 1);
        fn_80254134(self->hud, 1);
        CoinShellSet_Delete(self->shellSet);
        BossKoopa_Delete(self->koopa);
        fn_8016DFAC(self->m70, 1);
        fn_8016EFA8(self->m74, 1);
        DefeatDemo_Delete(self->defeatDemo);
        ItemObjectManager_Reset();
        VfxSlotMgr_Shutdown();
        ClRomTable_PurgeAll();
        RankingTable_Init(GetRaceContextPtr());
        delete lbl_806D10D0;
        lbl_806D10D0 = 0;
        SceneDrawList_Reset();
        delete lbl_806D109C;
        lbl_806D109C = 0;
        SetResourceLoadingFlag(0);
        clRom_PurgeAll();
        delete lbl_806D10AC;
        lbl_806D10AC = 0;
        dtor_80122FD8(self, 0);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
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

DefeatDemo::DefeatDemo() { /* 0x801303E4 size:0x2A8 */
    const char *pool = lbl_80356730;

    body = 0;
    hand = 0;
    effect = 0;
    scene = 0;
    frame = 0.0f;
    first = 1;
    spinA = 0;
    spinB = 0;
    spinC = 0;
    wheelA = 0;
    wheelB = 0;
    wheelAngleA = 0.0f;
    wheelAngleB = 0.0f;
    flash = 0;
    if (g_characterId == 4) {
        body = new CoinNormal3D(pool + 0x630, 0);
        hand = new CoinNormal3D(pool + 0x64C, 0);
    } else {
        body = new CoinNormal3D(pool + 0x630, 0);
        hand = new CoinNormal3D(pool + 0x664, 0);
    }
    effect = new CoinNormal3D(pool + 0x678, 0);
    clNormal3D_SetScale(body, 0, 0.0f, 1.0f, 0.0f, 0.0f);
    clNormal3D_SetScale(hand, 0, 0.0f, 1.0f, 0.0f, 0.0f);
    clNormal3D_SetScale(effect, 0, 0.0f, 1.0f, 0.0f, 0.0f);
    scene = new CoinAnimScene3D(pool + 0x630);
    ((CoinAnimScene3D *)scene)->Start();
    spinA = ResolveJointByName(body, pool + 0x688);
    spinB = ResolveJointByName(body, pool + 0x6A4);
    spinC = ResolveJointByName(body, pool + 0x6C0);
    wheelA = ResolveJointByName(body, pool + 0x6DC);
    wheelB = ResolveJointByName(body, pool + 0x6FC);
    flash = ResolveJointByName(effect, pool + 0x71C);
}

#define OS_BUS_CLOCK (*(unsigned long *)0x800000F8)
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)
#define OSTicksToSeconds(ticks) ((ticks) / OS_TIMER_CLOCK)

BossKoopa::BossKoopa(int waitMin, int waitMax) { /* 0x8013068C size:0x3FC */
    const char *pool = lbl_80356730;

    anims[0] = 0;
    anims[1] = 0;
    anims[2] = 0;
    anims[3] = 0;
    state = 0;
    reqState = 0;
    frame = 0.0f;
    justChanged = 1;
    timer = 0.0f;
    wait = 60;
    attack = 0;
    fireball = 0;
    waitRndIdx = OSTicksToSeconds(OSGetTick()) % 64;
    attackRndIdx = OSTicksToSeconds(OSGetTick()) % 48;
    this->waitMin = waitMin;
    this->waitMax = waitMax;
    fireball = new KoopaFireball(pool + 0x744);
    if (g_characterId == 4) {
        anims[0] = new CoinNormal3D(pool + 0x754, 0);
        anims[1] = new CoinNormal3D(pool + 0x770, 0);
        anims[2] = new CoinNormal3D(pool + 0x78C, 0);
        anims[3] = new CoinNormal3D(pool + 0x7AC, 0);
        fireball->jobj = ResolveJointByName(anims[1], pool + 0x7CC);
        fireball->angle = lbl_806CF574;
    } else {
        anims[0] = new CoinNormal3D(pool + 0x7F4, 0);
        anims[1] = new CoinNormal3D(pool + 0x808, 0);
        anims[2] = new CoinNormal3D(pool + 0x820, 0);
        anims[3] = new CoinNormal3D(pool + 0x838, 0);
        fireball->jobj = ResolveJointByName(anims[1], pool + 0x850);
        fireball->angle = lbl_806CF570;
    }
    clNormal3D_SetScale(anims[0], 0, 0.0f, 1.0f, 0.0f, 0.0f);
    Object_SetJObjPositionXYZ(anims[0], 0.0f, 15.0f, 40.0f);
    clNormal3D_SetScale(anims[1], 0, 0.0f, 1.0f, 0.0f, 0.0f);
    Object_SetJObjPositionXYZ(anims[1], 0.0f, 15.0f, 40.0f);
    clNormal3D_SetScale(anims[2], 0, 0.0f, 1.0f, 0.0f, 0.0f);
    Object_SetJObjPositionXYZ(anims[2], 0.0f, 15.0f, 40.0f);
    clNormal3D_SetScale(anims[3], 0, 0.0f, 1.0f, 0.0f, 0.0f);
    Object_SetJObjPositionXYZ(anims[3], 0.0f, 15.0f, 40.0f);
}

struct CGameCoinFields {
    unsigned char pad0[0x8];
    int m8;
    int mC;
    int m10;
    int m14;
    float mtx[3][4];
    int m48;
    int m4C;
    int m50[11];
    unsigned char m7C;
    unsigned char m7D;
    unsigned char m7E;
    unsigned char m7F;
    int m80;
    int m84;
    int m88;
    int m8C;
    int m90;
    float m94;
    float m98;
    int m9C;
    float mA0;
    int mA4;
    int mA8;
    int mAC;
    int mB0;
    int mB4;
    float mB8;
    float mBC;
};

extern "C" void CGameCoin_InitFields(CGameCoinFields *self) { /* 0x80130A88 size:0xD4 */
    self->m8 = 0;
    self->mC = 0;
    self->m10 = 0;
    self->m14 = 0;
    PSMTXIdentity(self->mtx);
    self->m48 = 0;
    self->m4C = 0;
    self->m94 = -1.0f;
    self->m98 = -1.0f;
    self->m84 = 0;
    self->m9C = 0;
    self->mA0 = 0.0f;
    self->m88 = 2;
    self->m8C = 2;
    self->m50[0] = 0;
    self->m50[1] = 0;
    self->m50[2] = 0;
    self->m50[3] = 0;
    self->m50[4] = 0;
    self->m50[5] = 0;
    self->m50[6] = 0;
    self->m50[7] = 0;
    self->m50[8] = 0;
    self->m50[9] = 0;
    self->m50[10] = 0;
    self->m7C = 0;
    self->m7D = 0;
    self->m7E = 0;
    self->m7F = 0;
    self->m80 = 0;
    self->mA4 = 0;
    self->mA8 = 0;
    self->mAC = 0;
    self->mB0 = 0;
    self->mB4 = 0;
    self->mB8 = 0.0f;
    self->mBC = 0.0f;
}

struct CoinTrail {
    int t;
    float pos[3];
};

struct CoinParticle {
    int active;
    int m4;
    int timer;
    float pos[3];
    float vel[3];
    float rotY;
    float alpha;
    CoinTrail trail[20];
};

struct CoinParticleManager {
    void *vtbl;
    void *jobj;
    void *trailJobj;
    int sinIdx;
    int heightIdx;
    CoinParticle particles[6];
    int trailCount;
};

extern "C" void CoinParticle_Draw(CoinParticleManager *self) { /* 0x80130B5C size:0x1D0 */
    int i;
    int j;
    void *node;
    float t;
    float scale;

    for (i = 0; i < 6; i++) {
        if (self->particles[i].active != 0) {
            Object_SetJObjPositionVec(self->jobj, self->particles[i].pos);
            Object_SetJObjRotationY(self->jobj, 0.017453289f * self->particles[i].rotY);
            Object_SetJObjScaleXYZ(self->jobj, 1.2f, 1.2f, 1.2f);
            Object_SetColorAlphaOnly(self->jobj, 0, self->particles[i].alpha);
            Object_RenderJObjEx(self->jobj, LinkedNode_GetField10_OrFallback(self->jobj, 0), 7);
            node = LinkedNode_GetField10_OrFallback(self->jobj, 0);
            Object_RenderJObjEx(self->jobj, node == 0 ? 0 : *(void **)((char *)node + 8), 7);
            for (j = 0; j < self->trailCount; j++) {
                t = self->particles[i].trail[j].t / 10.0f;
                scale = 2.0f - t;
                Object_SetJObjPositionVec(self->trailJobj, self->particles[i].trail[j].pos);
                Object_SetJObjScaleXYZ(self->trailJobj, scale, scale, scale);
                Object_SetColorAlphaOnly(self->trailJobj, 0, (1.0f - t) * self->particles[i].alpha);
                Object_RenderJObjTree(self->trailJobj, 7);
            }
        }
    }
}

static inline unsigned char CoinTrail_Spawn(CoinTrail *tr, float angle, float height) {
    if (tr->t >= 0) {
        return 0;
    }
    tr->t = 0;
    angle = 360.0f * angle;
    tr->pos[0] = 5.0f * LUT_Sin12Bit(angle);
    tr->pos[1] = 10.0f * height;
    tr->pos[2] = 5.0f * fn_80186960(angle);
    return 1;
}

extern "C" void CoinParticle_Update(CoinParticleManager *self) { /* 0x80130D2C size:0x2B0 */
    CoinTrail *trail;
    int i;
    int j;

    for (i = 0; i < 6; i++) {
        if (self->particles[i].active != 0) {
            trail = self->particles[i].trail;
            self->particles[i].pos[0] += self->particles[i].vel[0];
            self->particles[i].pos[1] += self->particles[i].vel[1];
            self->particles[i].pos[2] += self->particles[i].vel[2];
            self->particles[i].vel[1] -= 0.1f;
            self->particles[i].rotY += 5.0f;
            if (self->particles[i].rotY > 360.0f) {
                self->particles[i].rotY -= 360.0f;
            }
            self->particles[i].alpha = 1.0f - self->particles[i].timer / 100.0f;
            for (j = 0; j < self->trailCount; j++) {
                if (trail[j].t >= 0) {
                    trail[j].pos[1] -= 2.0f;
                    if (++trail[j].t > 10) {
                        trail[j].t = -1;
                    }
                }
            }
            if ((self->particles[i].timer & 3) == 0) {
                for (j = 0; j < self->trailCount; j++) {
                    if (CoinTrail_Spawn(&trail[j], lbl_80495994[self->sinIdx], lbl_80495A94[self->heightIdx]) == 1) {
                        trail[j].pos[0] += self->particles[i].pos[0];
                        trail[j].pos[1] += self->particles[i].pos[1];
                        trail[j].pos[2] += self->particles[i].pos[2];
                        break;
                    }
                }
                if (++self->sinIdx >= 64) {
                    self->sinIdx = 0;
                }
                if (++self->heightIdx >= 48) {
                    self->heightIdx = 0;
                }
            }
            if (++self->particles[i].timer >= 100) {
                self->particles[i].active = 0;
            }
        }
    }
}

static inline void CoinParticleManagerBase_Dtor(CoinParticleManager *self) {
    if (self != 0) {
        self->vtbl = lbl_8048E34C;
        Object_DtorWithGXSync(self->jobj, 1);
        Object_DtorWithGXSync(self->trailJobj, 1);
    }
}

extern "C" CoinParticleManager *CoinParticleManager_Destroy(CoinParticleManager *self, short flag) { /* 0x80130FDC size:0x80 */
    if (self != 0) {
        self->vtbl = lbl_8048E3C0;
        CoinParticleManagerBase_Dtor(self);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
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

