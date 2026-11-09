/* VS/Battle mode unit: .text 0x8009E0D4..0x800A0688, .rodata 0x80320960..0x80321178.
 * Merged from the per-function files (VSMode_FrameUpdate, BtMode_Dtor, VSMode_Init,
 * BtMode_Init) so the TU owns its .rodata pool. Each part keeps its own
 * declarations, renamed with `_pN` (tools/extab_user_renames.json maps them back). */
extern const unsigned int lbl_80320960[];
extern const char lbl_80320D8C[];
extern const unsigned int lbl_80320D9C[];

/* ==== VSMode_FrameUpdate ==== */
#define CObj_ApplyScissor CObj_ApplyScissor_p0
#define CObj_LoadProjMatrix CObj_LoadProjMatrix_p0
#define CalcSoundDirection CalcSoundDirection_p0
#define CarObject_ApplyInput_AI CarObject_ApplyInput_AI_p0
#define CarObject_CalcSpeedRatio CarObject_CalcSpeedRatio_p0
#define CarObject_FrameUpdate CarObject_FrameUpdate_p0
#define CarObject_GetRenderObj CarObject_GetRenderObj_p0
#define CarObject_GetTransformMatrix CarObject_GetTransformMatrix_p0
#define CarObject_SetPosition CarObject_SetPosition_p0
#define CoinEvent_PlayResultSE CoinEvent_PlayResultSE_p0
#define CoinJumpFlasher_SetArmed CoinJumpFlasher_SetArmed_p0
#define CoinJumpFlasher_Toggle CoinJumpFlasher_Toggle_p0
#define CommBroadcast_ClearTable CommBroadcast_ClearTable_p0
#define CommBroadcast_ScanForMySyncMatch CommBroadcast_ScanForMySyncMatch_p0
#define CountPeersWithRole CountPeersWithRole_p0
#define CourseEnvironment_UpdateAndCullZones_Timed CourseEnvironment_UpdateAndCullZones_Timed_p0
#define DebugPrintf DebugPrintf_p0
#define Fog_UpdateFromCourseScene3D Fog_UpdateFromCourseScene3D_p0
#define Frame_UpdatePerFrameState Frame_UpdatePerFrameState_p0
#define GetCoinMilage GetCoinMilage_p0
#define GetDisplayBufferIndex GetDisplayBufferIndex_p0
#define GetInputManager GetInputManager_p0
#define GetKartSlotCharId GetKartSlotCharId_p0
#define GetPlayerCarObject GetPlayerCarObject_p0
#define GetRaceContextPtr GetRaceContextPtr_p0
#define HSD_RandSeedPtr HSD_RandSeedPtr_p0
#define HUD_FrameUpdate HUD_FrameUpdate_p0
#define HUD_SetCurrentLap HUD_SetCurrentLap_p0
#define HUD_SetRacePosition HUD_SetRacePosition_p0
#define HitMessageOverlay_FrameUpdate HitMessageOverlay_FrameUpdate_p0
#define InputMgr_GetPlayer InputMgr_GetPlayer_p0
#define IsRaceStarted IsRaceStarted_p0
#define IsSyncReached IsSyncReached_p0
#define ItemBox_ProcessPickup ItemBox_ProcessPickup_p0
#define ItemObjectManager_PerFrameUpdate ItemObjectManager_PerFrameUpdate_p0
#define ItemObjectManager_Update ItemObjectManager_Update_p0
#define ItemSelect_Reset ItemSelect_Reset_p0
#define ItemSelect_StartRouletteSpin ItemSelect_StartRouletteSpin_p0
#define JObj_IsForwardDotBelowThreshold JObj_IsForwardDotBelowThreshold_p0
#define Jyugemu_Flag_SetKartDriver Jyugemu_Flag_SetKartDriver_p0
#define Jyugemu_Flag_Tick Jyugemu_Flag_Tick_p0
#define Jyugemu_ReverseFlag_SetState Jyugemu_ReverseFlag_SetState_p0
#define Jyugemu_ReverseFlag_Tick Jyugemu_ReverseFlag_Tick_p0
#define KartItem_GetCurrentSpeedWithBonus KartItem_GetCurrentSpeedWithBonus_p0
#define KartItem_OnFallOffOrDeath KartItem_OnFallOffOrDeath_p0
#define KartItem_SetCarObjectField1c8Float KartItem_SetCarObjectField1c8Float_p0
#define KartItem_UpdateShadowBillboardAndViewport KartItem_UpdateShadowBillboardAndViewport_p0
#define LakituStart_Dtor LakituStart_Dtor_p0
#define LakituStart_SetCountdownHoldFrames LakituStart_SetCountdownHoldFrames_p0
#define LakituStart_UpdateCountdown LakituStart_UpdateCountdown_p0
#define LapBannerScene_TriggerBannerAnim LapBannerScene_TriggerBannerAnim_p0
#define LapBannerScene_UpdateAndDriveAnim LapBannerScene_UpdateAndDriveAnim_p0
#define Live_IsConnectReady Live_IsConnectReady_p0
#define OSGetTime OSGetTime_p0
#define Object_SetByte10_Return1 Object_SetByte10_Return1_p0
#define PCBComm_Process PCBComm_Process_p0
#define PathManager_RefreshFinishPositions PathManager_RefreshFinishPositions_p0
#define PathManager_UpdateAll PathManager_UpdateAll_p0
#define Path_LookupCheckpointOffset Path_LookupCheckpointOffset_p0
#define PcbSlot_ResetScratchAreas PcbSlot_ResetScratchAreas_p0
#define PlayStats_IncVsPeerCount PlayStats_IncVsPeerCount_p0
#define PlayStats_IncVsPlay PlayStats_IncVsPlay_p0
#define RaceResult_InsertSortedRank RaceResult_InsertSortedRank_p0
#define RaceResult_StoreLatest RaceResult_StoreLatest_p0
#define RaceSlot_GetDriverId RaceSlot_GetDriverId_p0
#define Race_CompareKartProgress Race_CompareKartProgress_p0
#define Race_PerFrameTickAndAudio Race_PerFrameTickAndAudio_p0
#define Rand_SetSeedDebug Rand_SetSeedDebug_p0
#define RankLog_SetRaceResult RankLog_SetRaceResult_p0
#define RankingMgr_UpdatePositions RankingMgr_UpdatePositions_p0
#define ReplayRandCursor_Reset ReplayRandCursor_Reset_p0
#define RingBuffer_GetEntryHead RingBuffer_GetEntryHead_p0
#define RingBuffer_GetKartSlot RingBuffer_GetKartSlot_p0
#define RingBuffer_GetRankSlot RingBuffer_GetRankSlot_p0
#define SetRaceResultLatestPtr SetRaceResultLatestPtr_p0
#define SetSyncTarget SetSyncTarget_p0
#define SyncSlot_ApplyCourseChoice SyncSlot_ApplyCourseChoice_p0
#define SyncSlot_GetHostSend SyncSlot_GetHostSend_p0
#define SyncSlot_GetRecv SyncSlot_GetRecv_p0
#define Tachometer_RenderDigits Tachometer_RenderDigits_p0
#define Timer_Decrement Timer_Decrement_p0
#define TitleStats_AccumDistanceCounter TitleStats_AccumDistanceCounter_p0
#define TitleTracker_ResetPerRound TitleTracker_ResetPerRound_p0
#define TransitionEffect_Tick TransitionEffect_Tick_p0
#define VIWaitForRetrace VIWaitForRetrace_p0
#define VfxSlotMgr_Update VfxSlotMgr_Update_p0
#define VoiceQueue_Clear VoiceQueue_Clear_p0
#define __cvt_sll_flt __cvt_sll_flt_p0
#define __div2i __div2i_p0
#define clItemBoxManager_Update clItemBoxManager_Update_p0
#define fn_8013A534 fn_8013A534_p0
#define fn_8016B32C fn_8016B32C_p0
#define fn_8016C554 fn_8016C554_p0
#define fn_8016C598 fn_8016C598_p0
#define fn_8016C5CC fn_8016C5CC_p0
#define fn_8016C600 fn_8016C600_p0
#define fn_801B12A0 fn_801B12A0_p0
#define fn_801B3B7C fn_801B3B7C_p0
#define fn_801B3BC8 fn_801B3BC8_p0
#define fn_801B5C98 fn_801B5C98_p0
#define fn_801DC69C fn_801DC69C_p0
#define fn_801DC6B4 fn_801DC6B4_p0
#define fn_801DC6CC fn_801DC6CC_p0
#define fn_801DC6E4 fn_801DC6E4_p0
#define fn_801DC6FC fn_801DC6FC_p0
#define fn_801DC714 fn_801DC714_p0
#define fn_801DC72C fn_801DC72C_p0
#define fn_801DC740 fn_801DC740_p0
#define fn_80208E30 fn_80208E30_p0
#define fn_8020AF08 fn_8020AF08_p0
#define fn_8020B07C fn_8020B07C_p0
#define fn_80253BE4 fn_80253BE4_p0
#define fn_80253D00 fn_80253D00_p0
#define fn_80253DF0 fn_80253DF0_p0
#define fn_80253E18 fn_80253E18_p0
#define fn_80253EBC fn_80253EBC_p0
#define fn_80253EC0 fn_80253EC0_p0
#define fn_80253EC4 fn_80253EC4_p0
#define fn_80253F2C fn_80253F2C_p0
#define fn_80253FD8 fn_80253FD8_p0
#define g_bestLapTime g_bestLapTime_p0
#define g_carObjects g_carObjects_p0
#define g_ccClass g_ccClass_p0
#define g_currentLap g_currentLap_p0
#define g_currentLapTime g_currentLapTime_p0
#define g_currentSceneState g_currentSceneState_p0
#define g_finalLapBannerShown g_finalLapBannerShown_p0
#define g_finalLapCoinJumpEnabled g_finalLapCoinJumpEnabled_p0
#define g_finalRacePosition g_finalRacePosition_p0
#define g_isCommHost g_isCommHost_p0
#define g_itemSelects g_itemSelects_p0
#define g_lakituStartAnimDone g_lakituStartAnimDone_p0
#define g_lapChangePending g_lapChangePending_p0
#define g_playerData g_playerData_p0
#define g_playerRenderObj g_playerRenderObj_p0
#define g_raceEnded g_raceEnded_p0
#define g_raceResultCode g_raceResultCode_p0
#define g_raceTimeRemaining g_raceTimeRemaining_p0
#define g_rendererGateFlag g_rendererGateFlag_p0
#define g_sceneTransitionTimer g_sceneTransitionTimer_p0
#define g_totalLaps g_totalLaps_p0
#define g_totalRaceTime g_totalRaceTime_p0
#define g_weatherSystem g_weatherSystem_p0
#define lbl_805D2AA8 lbl_805D2AA8_p0
#define lbl_805D2B00 lbl_805D2B00_p0
#define lbl_806792D8 lbl_806792D8_p0
#define lbl_806CF140 lbl_806CF140_p0
#define lbl_806CF148 lbl_806CF148_p0
#define lbl_806CF270 lbl_806CF270_p0
#define lbl_806D0051 lbl_806D0051_p0
#define lbl_806D109C lbl_806D109C_p0
#define lbl_806D10A0 lbl_806D10A0_p0
#define lbl_806D10D0 lbl_806D10D0_p0
#define lbl_806D1191 lbl_806D1191_p0
#define lbl_806D12E8 lbl_806D12E8_p0
#define lbl_806D12EC lbl_806D12EC_p0
#define lbl_806D12F0 lbl_806D12F0_p0
#define lbl_806D12F4 lbl_806D12F4_p0
#define lbl_806D12FC lbl_806D12FC_p0
#define lbl_806D1300 lbl_806D1300_p0
#define lbl_806D1310 lbl_806D1310_p0
#define lbl_806D1314 lbl_806D1314_p0
#define lbl_806D1318 lbl_806D1318_p0
#define lbl_806D1319 lbl_806D1319_p0
#define lbl_806D131C lbl_806D131C_p0
#define lbl_806D134C lbl_806D134C_p0
#define lbl_806D1350 lbl_806D1350_p0
#define lbl_806D47A0 lbl_806D47A0_p0
#define lbl_806D47A4 lbl_806D47A4_p0
#define lbl_806D47A8 lbl_806D47A8_p0
#define lbl_806D47AC lbl_806D47AC_p0
#define lbl_806D47B0 lbl_806D47B0_p0
#define lbl_806D47B4 lbl_806D47B4_p0
#define lbl_806D47B8 lbl_806D47B8_p0
#define lbl_806D47BC lbl_806D47BC_p0
#define lbl_806D47C0 lbl_806D47C0_p0
#define lbl_806D47C8 lbl_806D47C8_p0
#define memset memset_p0
#define race_result_handler race_result_handler_p0

/* sdata symbols referenced from asm */
extern unsigned char lbl_806D12F0[4];
extern unsigned char lbl_806D131C[1];
/* === extracted from auto_VSMode_FrameUpdate_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CObj_ApplyScissor();
extern void CObj_LoadProjMatrix();
extern void CalcSoundDirection();
extern void CarObject_ApplyInput_AI();
extern void CarObject_CalcSpeedRatio();
extern void CarObject_FrameUpdate();
extern void CarObject_GetRenderObj();
extern void CarObject_GetTransformMatrix();
extern void CarObject_SetPosition();
extern void CoinEvent_PlayResultSE();
extern void CoinJumpFlasher_SetArmed();
extern void CoinJumpFlasher_Toggle();
extern void CommBroadcast_ClearTable();
extern void CommBroadcast_ScanForMySyncMatch();
extern void CountPeersWithRole();
extern void CourseEnvironment_UpdateAndCullZones_Timed();
extern void DebugPrintf();
extern void Fog_UpdateFromCourseScene3D();
extern void Frame_UpdatePerFrameState();
extern void GetCoinMilage();
extern void GetDisplayBufferIndex();
extern void GetInputManager();
extern void GetKartSlotCharId();
extern void GetPlayerCarObject();
extern void GetRaceContextPtr();
extern void HUD_FrameUpdate();
extern void HUD_SetCurrentLap();
extern void HUD_SetRacePosition();
extern void HitMessageOverlay_FrameUpdate();
extern void InputMgr_GetPlayer();
extern void IsRaceStarted();
extern void IsSyncReached();
extern void ItemBox_ProcessPickup();
extern void ItemObjectManager_PerFrameUpdate();
extern void ItemObjectManager_Update();
extern void ItemSelect_Reset();
extern void ItemSelect_StartRouletteSpin();
extern void JObj_IsForwardDotBelowThreshold();
extern void Jyugemu_Flag_SetKartDriver();
extern void Jyugemu_Flag_Tick();
extern void Jyugemu_ReverseFlag_SetState();
extern void Jyugemu_ReverseFlag_Tick();
extern void KartItem_GetCurrentSpeedWithBonus();
extern void KartItem_OnFallOffOrDeath();
extern void KartItem_SetCarObjectField1c8Float();
extern void KartItem_UpdateShadowBillboardAndViewport();
extern void LakituStart_Dtor();
extern void LakituStart_SetCountdownHoldFrames();
extern void LakituStart_UpdateCountdown();
extern void LapBannerScene_TriggerBannerAnim();
extern void LapBannerScene_UpdateAndDriveAnim();
extern void Live_IsConnectReady();
extern void OSGetTime();
extern void Object_SetByte10_Return1();
extern void PCBComm_Process();
extern void PathManager_RefreshFinishPositions();
extern void PathManager_UpdateAll();
extern void Path_LookupCheckpointOffset();
extern void PcbSlot_ResetScratchAreas();
extern void PlayStats_IncVsPeerCount();
extern void PlayStats_IncVsPlay();
extern void RaceResult_InsertSortedRank();
extern void RaceResult_StoreLatest();
extern void RaceSlot_GetDriverId();
extern void Race_CompareKartProgress();
extern void Race_PerFrameTickAndAudio();
extern void Rand_SetSeedDebug();
extern void RankLog_SetRaceResult();
extern void RankingMgr_UpdatePositions();
extern void ReplayRandCursor_Reset();
extern void RingBuffer_GetEntryHead();
extern void RingBuffer_GetKartSlot();
extern void RingBuffer_GetRankSlot();
extern void SetRaceResultLatestPtr();
extern void SetSyncTarget();
extern void SyncSlot_ApplyCourseChoice();
extern void SyncSlot_GetHostSend();
extern void SyncSlot_GetRecv();
extern void Tachometer_RenderDigits();
extern void Timer_Decrement();
extern void TitleStats_AccumDistanceCounter();
extern void TitleTracker_ResetPerRound();
extern void TransitionEffect_Tick();
extern void VSMode_Init(void *);
extern void VfxSlotMgr_Update();
extern void VoiceQueue_Clear();
extern void __cvt_sll_flt();
extern void clItemBoxManager_Update();
extern void fn_8013A534();
extern void fn_8016B32C();
extern void fn_8016C554();
extern void fn_8016C598();
extern void fn_8016C5CC();
extern void fn_8016C600();
extern void fn_801B12A0();
extern void fn_801B3B7C();
extern void fn_801B3BC8();
extern void fn_801B5C98();
extern void fn_801DC69C();
extern void fn_801DC6B4();
extern void fn_801DC6CC();
extern void fn_801DC6E4();
extern void fn_801DC6FC();
extern void fn_801DC714();
extern void fn_801DC72C();
extern void fn_801DC740();
extern void fn_80208E30();
extern void fn_8020AF08();
extern void fn_8020B07C();
extern void fn_80253BE4();
extern void fn_80253D00();
extern void fn_80253DF0();
extern void fn_80253E18();
extern void fn_80253EBC();
extern void fn_80253EC0();
extern void fn_80253EC4();
extern void fn_80253F2C();
extern void fn_80253FD8();
extern void VIWaitForRetrace();
extern void __div2i();
extern void memset();
extern void race_result_handler();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_bestLapTime;
extern unsigned int g_ccClass;
extern unsigned int g_currentLap;
extern unsigned int g_currentLapTime;
extern unsigned int g_currentSceneState;
extern unsigned int g_finalLapBannerShown;
extern unsigned int g_finalLapCoinJumpEnabled;
extern unsigned int g_finalRacePosition;
extern unsigned int g_isCommHost;
extern unsigned int g_lakituStartAnimDone;
extern unsigned int g_lapChangePending;
extern unsigned int g_playerRenderObj;
extern unsigned int g_raceEnded;
extern unsigned int g_raceResultCode;
extern unsigned int g_raceTimeRemaining;
extern unsigned int g_rendererGateFlag;
extern unsigned int g_sceneTransitionTimer;
extern unsigned int g_totalLaps;
extern unsigned int g_totalRaceTime;
extern unsigned int g_weatherSystem;
extern unsigned int lbl_806CF140;
extern unsigned int lbl_806CF148;
extern unsigned int lbl_806CF270;
extern unsigned int lbl_806D0051;
extern unsigned int HSD_RandSeedPtr;
extern unsigned int lbl_806D109C;
extern unsigned int lbl_806D10A0;
extern unsigned int lbl_806D10D0;
extern unsigned int lbl_806D1191;
extern unsigned int lbl_806D12E8;
extern unsigned int lbl_806D12EC;
extern unsigned int lbl_806D12F4;
extern unsigned int lbl_806D12FC;
extern unsigned int lbl_806D1300;
extern unsigned int lbl_806D1310;
extern unsigned int lbl_806D1314;
extern unsigned int lbl_806D1318;
extern unsigned int lbl_806D1319;
extern unsigned int lbl_806D134C;
extern unsigned int lbl_806D1350;
extern unsigned int lbl_806D47A0;
extern unsigned int lbl_806D47A4;
extern unsigned int lbl_806D47A8;
extern unsigned int lbl_806D47AC;
extern unsigned int lbl_806D47B0;
extern unsigned int lbl_806D47B4;
extern unsigned int lbl_806D47B8;
extern unsigned int lbl_806D47BC;
extern unsigned int lbl_806D47C0;
extern unsigned int lbl_806D47C8;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int g_carObjects[];
extern unsigned int g_itemSelects[];
extern unsigned int g_playerData[];

extern unsigned int lbl_805D2AA8[];
extern unsigned int lbl_805D2B00[];
extern unsigned int lbl_806792D8[];

/* --- function index (1 fns, .text 0x8009E0D4..0x8009F47C) ---
 * [  0] 0x8009E0D4 size:0x13A8  global VSMode_FrameUpdate
 */

/* --- forward decls --- */
asm void VSMode_FrameUpdate(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_VSMode_FrameUpdate[8] = {
    0x90, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_VSMode_FrameUpdate = {
    (void *)&VSMode_FrameUpdate, 0x000013A8, (void *)extab_VSMode_FrameUpdate
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void VSMode_FrameUpdate(void) { /* 0x8009E0D4 size:0x13A8 */
    nofralloc
    stwu r1, -0xf0(r1)
    mflr r0
    stw r0, 0xf4(r1)
    stfd f31, 0xe0(r1)
    psq_st f31, 0xe8(r1), 0, 0
    stfd f30, 0xd0(r1)
    psq_st f30, 0xd8(r1), 0, 0
    stmw r14, 0x88(r1)
    lwz r6, g_currentSceneState(r13)
    lis r5, lbl_805D2AA8@ha
    addi r0, r5, lbl_805D2AA8@l
    lis r4, lbl_80320960@ha
    cmpwi r6, 0x2a
    stw r0, 0x7c(r1)
    mr r15, r3
    addi r27, r4, lbl_80320960@l
    bne VSMode_FrameUpdate_L_8009E14C
    bl IsSyncReached
    clrlwi. r0, r3, 24
    beq VSMode_FrameUpdate_L_8009E144
    bl SyncSlot_ApplyCourseChoice
    mr r3, r15
    bl VSMode_Init
    li r3, 0x2b
    bl SetSyncTarget
    addi r3, r27, 0x448
    crxor 6, 6, 6
    bl DebugPrintf
    VSMode_FrameUpdate_L_8009E144:
    li r3, -0x2
    b VSMode_FrameUpdate_L_8009F458
    VSMode_FrameUpdate_L_8009E14C:
    cmpwi r6, 0x2b
    bne VSMode_FrameUpdate_L_8009E208
    bl IsSyncReached
    clrlwi. r0, r3, 24
    beq VSMode_FrameUpdate_L_8009E200
    la r3, lbl_806D12F0(r13)  /* lbl_806D12F0 */
    li r4, 0x0
    li r5, 0x4
    bl memset
    la r0, lbl_806D12F0(r13)  /* lbl_806D12F0 */
    stw r0, HSD_RandSeedPtr(r13)
    bl SyncSlot_GetRecv
    lbz r0, 0x1b(r3)
    lwz r3, HSD_RandSeedPtr(r13)
    stw r0, 0x0(r3)
    bl SyncSlot_GetRecv
    lbz r3, 0x1b(r3)
    bl Rand_SetSeedDebug
    bl SyncSlot_GetRecv
    lbz r0, 0x1b(r3)
    stw r0, lbl_806D134C(r13)
    bl SyncSlot_GetRecv
    lbz r0, 0x1b(r3)
    stw r0, lbl_806D1350(r13)
    bl ReplayRandCursor_Reset
    bl PcbSlot_ResetScratchAreas
    bl CommBroadcast_ClearTable
    li r3, 0x2c
    bl SetSyncTarget
    bl PlayStats_IncVsPlay
    bl PlayStats_IncVsPeerCount
    li r3, 0x0
    bl VoiceQueue_Clear
    lbz r5, g_isCommHost(r13)
    li r3, 0x7
    li r0, 0x2
    stw r3, lbl_806D1310(r13)
    neg r4, r5
    addi r3, r27, 0x47c
    or r4, r4, r5
    srawi r4, r4, 31
    andc r0, r0, r4
    stw r0, lbl_806D1314(r13)
    crxor 6, 6, 6
    bl DebugPrintf
    VSMode_FrameUpdate_L_8009E200:
    li r3, -0x2
    b VSMode_FrameUpdate_L_8009F458
    VSMode_FrameUpdate_L_8009E208:
    lwz r3, lbl_806D1314(r13)
    cmpwi r3, 0x0
    beq VSMode_FrameUpdate_L_8009E278
    subic. r0, r3, 0x1
    stw r0, lbl_806D1314(r13)
    bne VSMode_FrameUpdate_L_8009E270
    la r3, lbl_806D12F0(r13)  /* lbl_806D12F0 */
    li r4, 0x0
    li r5, 0x4
    bl memset
    la r0, lbl_806D12F0(r13)  /* lbl_806D12F0 */
    stw r0, HSD_RandSeedPtr(r13)
    bl SyncSlot_GetRecv
    lbz r0, 0x1b(r3)
    lwz r3, HSD_RandSeedPtr(r13)
    stw r0, 0x0(r3)
    bl SyncSlot_GetRecv
    lbz r3, 0x1b(r3)
    bl Rand_SetSeedDebug
    bl SyncSlot_GetRecv
    lbz r0, 0x1b(r3)
    stw r0, lbl_806D134C(r13)
    bl SyncSlot_GetRecv
    lbz r0, 0x1b(r3)
    stw r0, lbl_806D1350(r13)
    bl ReplayRandCursor_Reset
    VSMode_FrameUpdate_L_8009E270:
    li r3, -0x2
    b VSMode_FrameUpdate_L_8009F458
    VSMode_FrameUpdate_L_8009E278:
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lbz r0, g_raceEnded(r13)
    stw r3, 0x78(r1)
    cmplwi r0, 0x0
    bne VSMode_FrameUpdate_L_8009E2CC
    lwz r12, 0x0(r3)
    li r4, 0x400
    lwz r12, 0x28(r12)
    mtctr r12
    bctrl
    cmplwi r3, 0x0
    beq VSMode_FrameUpdate_L_8009E2CC
    lis r3, g_playerData@ha
    addi r3, r3, g_playerData@l
    bl GetCoinMilage
    cmpwi r3, 0xfa0
    blt VSMode_FrameUpdate_L_8009E2CC
    bl GetPlayerCarObject
    bl CoinJumpFlasher_Toggle
    VSMode_FrameUpdate_L_8009E2CC:
    lbz r0, g_isCommHost(r13)
    li r3, 0x0
    stw r3, 0x54(r1)
    addi r21, r1, 0x54
    cmplwi r0, 0x1
    stw r3, 0x58(r1)
    stw r3, 0x5c(r1)
    stw r3, 0x60(r1)
    bne VSMode_FrameUpdate_L_8009E39C
    lis r3, g_carObjects@ha
    li r18, 0x0
    addi r14, r3, g_carObjects@l
    VSMode_FrameUpdate_L_8009E2FC:
    mr r16, r14
    mr r17, r21
    li r19, 0x0
    li r20, 0x0
    VSMode_FrameUpdate_L_8009E30C:
    lwz r0, 0x0(r16)
    cmplwi r0, 0x0
    beq VSMode_FrameUpdate_L_8009E344
    mr r3, r20
    bl RingBuffer_GetKartSlot
    lwz r5, 0x0(r17)
    clrlwi r0, r19, 24
    lwz r4, 0xc(r3)
    lbz r6, 0x22(r3)
    or r3, r5, r4
    cmplw r6, r0
    stw r3, 0x0(r17)
    ble VSMode_FrameUpdate_L_8009E344
    mr r19, r6
    VSMode_FrameUpdate_L_8009E344:
    addi r20, r20, 0x1
    addi r17, r17, 0x4
    cmpwi r20, 0x4
    addi r16, r16, 0x4
    blt VSMode_FrameUpdate_L_8009E30C
    clrlwi r0, r19, 24
    cmplwi r0, 0x2
    blt VSMode_FrameUpdate_L_8009E3E4
    addi r18, r18, 0x1
    cmpwi r18, 0x4
    bgt VSMode_FrameUpdate_L_8009E3E4
    bl VIWaitForRetrace
    bl Frame_UpdatePerFrameState
    bl Timer_Decrement
    li r3, 0x1
    li r4, 0x0
    bl PCBComm_Process
    lbz r0, lbl_806D1191(r13)
    cmplwi r0, 0x1
    bne VSMode_FrameUpdate_L_8009E2FC
    li r3, -0x2
    b VSMode_FrameUpdate_L_8009F458
    VSMode_FrameUpdate_L_8009E39C:
    bl CommBroadcast_ScanForMySyncMatch
    clrlwi. r0, r3, 24
    bne VSMode_FrameUpdate_L_8009E3E4
    VSMode_FrameUpdate_L_8009E3A8:
    bl VIWaitForRetrace
    bl Frame_UpdatePerFrameState
    bl Timer_Decrement
    li r3, 0x0
    li r4, 0x1
    bl PCBComm_Process
    bl CommBroadcast_ScanForMySyncMatch
    lbz r0, lbl_806D1191(r13)
    cmplwi r0, 0x1
    bne VSMode_FrameUpdate_L_8009E3D8
    li r3, -0x2
    b VSMode_FrameUpdate_L_8009F458
    VSMode_FrameUpdate_L_8009E3D8:
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    ble VSMode_FrameUpdate_L_8009E3A8
    VSMode_FrameUpdate_L_8009E3E4:
    lis r3, g_carObjects@ha
    mr r16, r21
    addi r20, r3, g_carObjects@l
    li r17, 0x0
    mr r14, r20
    VSMode_FrameUpdate_L_8009E3F8:
    lwz r0, 0x0(r14)
    cmplwi r0, 0x0
    beq VSMode_FrameUpdate_L_8009E41C
    mr r3, r17
    bl RingBuffer_GetKartSlot
    lwz r3, 0xc(r3)
    lwz r0, 0x0(r16)
    or r0, r0, r3
    stw r0, 0x0(r16)
    VSMode_FrameUpdate_L_8009E41C:
    addi r17, r17, 0x1
    addi r16, r16, 0x4
    cmpwi r17, 0x4
    addi r14, r14, 0x4
    blt VSMode_FrameUpdate_L_8009E3F8
    bl fn_801B5C98
    bl SyncSlot_GetHostSend
    cmplwi r3, 0x0
    beq VSMode_FrameUpdate_L_8009E444
    bl Race_PerFrameTickAndAudio
    VSMode_FrameUpdate_L_8009E444:
    lbz r0, lbl_806D1318(r13)
    cmplwi r0, 0x0
    bne VSMode_FrameUpdate_L_8009E484
    bl Live_IsConnectReady
    clrlwi. r0, r3, 24
    beq VSMode_FrameUpdate_L_8009E484
    li r0, 0x1
    stb r0, lbl_806D1318(r13)
    bl SyncSlot_GetHostSend
    cmplwi r3, 0x0
    beq VSMode_FrameUpdate_L_8009E484
    li r14, 0x1
    bl SyncSlot_GetHostSend
    lbz r0, 0x2(r3)
    rlwimi r0, r14, 7, 24, 24
    stb r0, 0x2(r3)
    VSMode_FrameUpdate_L_8009E484:
    lbz r0, lbl_806D1319(r13)
    cmplwi r0, 0x0
    beq VSMode_FrameUpdate_L_8009E4C0
    bl SyncSlot_GetRecv
    lbz r0, 0x2(r3)
    extrwi r0, r0, 1, 24
    cmplwi r0, 0x1
    bne VSMode_FrameUpdate_L_8009E4C0
    lwz r3, 0x4(r15)
    cmplwi r3, 0x0
    beq VSMode_FrameUpdate_L_8009E4B8
    li r4, -0x1
    bl LakituStart_SetCountdownHoldFrames
    VSMode_FrameUpdate_L_8009E4B8:
    li r0, 0x0
    stb r0, lbl_806D1319(r13)
    VSMode_FrameUpdate_L_8009E4C0:
    lwz r3, 0x34(r15)
    cmplwi r3, 0x0
    beq VSMode_FrameUpdate_L_8009E4EC
    bl fn_8020B07C
    clrlwi. r0, r3, 24
    beq VSMode_FrameUpdate_L_8009E4EC
    lwz r3, 0x34(r15)
    li r4, 0x1
    bl fn_8020AF08
    li r0, 0x0
    stw r0, 0x34(r15)
    VSMode_FrameUpdate_L_8009E4EC:
    lwz r0, g_currentSceneState(r13)
    cmpwi r0, 0x2d
    bne VSMode_FrameUpdate_L_8009E554
    bl IsSyncReached
    clrlwi. r0, r3, 24
    beq VSMode_FrameUpdate_L_8009E62C
    addi r3, r27, 0x4b0
    crxor 6, 6, 6
    bl DebugPrintf
    lwz r3, lbl_806D10A0(r13)
    cmplwi r3, 0x0
    bne VSMode_FrameUpdate_L_8009E520
    li r3, 0x0
    VSMode_FrameUpdate_L_8009E520:
    cmplwi r3, 0x0
    beq VSMode_FrameUpdate_L_8009E54C
    lbz r0, g_raceEnded(r13)
    lwz r4, g_finalRacePosition(r13)
    cmplwi r0, 0x0
    bne VSMode_FrameUpdate_L_8009E544
    li r5, 0x1
    bl race_result_handler
    b VSMode_FrameUpdate_L_8009E54C
    VSMode_FrameUpdate_L_8009E544:
    li r5, 0x0
    bl race_result_handler
    VSMode_FrameUpdate_L_8009E54C:
    li r3, 0xd
    b VSMode_FrameUpdate_L_8009F458
    VSMode_FrameUpdate_L_8009E554:
    lwz r0, g_sceneTransitionTimer(r13)
    cmpwi r0, 0x0
    ble VSMode_FrameUpdate_L_8009E59C
    bl Live_IsConnectReady
    clrlwi. r0, r3, 24
    beq VSMode_FrameUpdate_L_8009E590
    lwz r3, g_sceneTransitionTimer(r13)
    subic. r0, r3, 0x1
    stw r0, g_sceneTransitionTimer(r13)
    bne VSMode_FrameUpdate_L_8009E62C
    lwz r3, lbl_806D12F4(r13)
    bl PathManager_RefreshFinishPositions
    li r3, 0x2d
    bl SetSyncTarget
    b VSMode_FrameUpdate_L_8009E62C
    VSMode_FrameUpdate_L_8009E590:
    li r0, 0xb4
    stw r0, g_sceneTransitionTimer(r13)
    b VSMode_FrameUpdate_L_8009E62C
    VSMode_FrameUpdate_L_8009E59C:
    li r17, 0x0
    li r3, -0x1
    bl CountPeersWithRole
    mr r14, r3
    mr r16, r20
    li r18, 0x0
    VSMode_FrameUpdate_L_8009E5B4:
    lwz r3, 0x0(r16)
    cmplwi r3, 0x0
    beq VSMode_FrameUpdate_L_8009E5D4
    bl CarObject_GetRenderObj
    lbz r0, 0x2b8(r3)
    cmplwi r0, 0x0
    beq VSMode_FrameUpdate_L_8009E5D4
    addi r17, r17, 0x1
    VSMode_FrameUpdate_L_8009E5D4:
    addi r18, r18, 0x1
    addi r16, r16, 0x4
    cmpwi r18, 0x4
    blt VSMode_FrameUpdate_L_8009E5B4
    cmpwi r14, 0x0
    beq VSMode_FrameUpdate_L_8009E5FC
    cmpw r14, r17
    bne VSMode_FrameUpdate_L_8009E5FC
    li r0, 0xb4
    stw r0, g_sceneTransitionTimer(r13)
    VSMode_FrameUpdate_L_8009E5FC:
    cmpwi r17, 0x0
    beq VSMode_FrameUpdate_L_8009E62C
    lbz r0, lbl_806CF148(r13)
    cmplwi r0, 0x0
    beq VSMode_FrameUpdate_L_8009E62C
    lfs f1, g_raceTimeRemaining(r13)
    li r0, 0x0
    lfs f0, lbl_806D47A0(r2)
    stb r0, lbl_806CF148(r13)
    fcmpo cr0, f1, f0
    ble VSMode_FrameUpdate_L_8009E62C
    stfs f0, g_raceTimeRemaining(r13)
    VSMode_FrameUpdate_L_8009E62C:
    bl SyncSlot_GetRecv
    lbz r3, 0x0(r3)
    lwz r0, lbl_806D12FC(r13)
    extrwi r14, r3, 5, 24
    cmpw r14, r0
    beq VSMode_FrameUpdate_L_8009E660
    cmpwi r14, 0x3
    stw r14, lbl_806D12FC(r13)
    bne VSMode_FrameUpdate_L_8009E654
    bl fn_8016C600
    VSMode_FrameUpdate_L_8009E654:
    cmpwi r14, 0x4
    bne VSMode_FrameUpdate_L_8009E660
    bl fn_8016C598
    VSMode_FrameUpdate_L_8009E660:
    lbz r0, g_isCommHost(r13)
    cmplwi r0, 0x0
    bne VSMode_FrameUpdate_L_8009E6F8
    lis r3, lbl_806792D8@ha
    li r16, 0x0
    addi r14, r3, lbl_806792D8@l
    li r17, 0x0
    VSMode_FrameUpdate_L_8009E67C:
    mr r3, r17
    bl RaceSlot_GetDriverId
    cmpwi r3, 0x6
    bne VSMode_FrameUpdate_L_8009E6E8
    mr r3, r16
    addi r16, r16, 0x1
    bl RingBuffer_GetRankSlot
    mr r0, r3
    mr r3, r17
    mr r18, r0
    mr r4, r18
    bl fn_801DC740
    lfs f0, 0xc(r18)
    mr r3, r17
    stfs f0, 0xc(r14)
    lfs f0, 0x10(r18)
    stfs f0, 0x10(r14)
    lha r4, 0x14(r18)
    bl fn_801DC714
    lbz r4, 0x16(r18)
    mr r3, r17
    extsb r4, r4
    bl fn_801DC6E4
    lbz r4, 0x17(r18)
    mr r3, r17
    extsb r4, r4
    bl fn_801DC6B4
    VSMode_FrameUpdate_L_8009E6E8:
    addi r17, r17, 0x1
    addi r14, r14, 0x20
    cmpwi r17, 0x8
    blt VSMode_FrameUpdate_L_8009E67C
    VSMode_FrameUpdate_L_8009E6F8:
    bl GetRaceContextPtr
    bl ItemObjectManager_PerFrameUpdate
    lwz r3, 0x2c(r15)
    bl RankingMgr_UpdatePositions
    lwz r3, 0x30(r15)
    bl fn_80208E30
    lbz r0, g_isCommHost(r13)
    cmplwi r0, 0x1
    bne VSMode_FrameUpdate_L_8009E7B0
    lis r3, lbl_806792D8@ha
    li r17, 0x0
    addi r16, r3, lbl_806792D8@l
    li r18, 0x0
    VSMode_FrameUpdate_L_8009E72C:
    mr r3, r18
    bl RaceSlot_GetDriverId
    cmpwi r3, 0x6
    bne VSMode_FrameUpdate_L_8009E7A0
    mr r3, r17
    addi r17, r17, 0x1
    bl RingBuffer_GetRankSlot
    mr r14, r3
    mr r3, r18
    bl fn_801DC72C
    lfs f0, 0x0(r3)
    stfs f0, 0x0(r14)
    lfs f0, 0x4(r3)
    stfs f0, 0x4(r14)
    lfs f0, 0x8(r3)
    mr r3, r18
    stfs f0, 0x8(r14)
    lfs f0, 0xc(r16)
    stfs f0, 0xc(r14)
    lfs f0, 0x10(r16)
    stfs f0, 0x10(r14)
    bl fn_801DC6FC
    sth r3, 0x14(r14)
    mr r3, r18
    bl fn_801DC6CC
    stb r3, 0x16(r14)
    mr r3, r18
    bl fn_801DC69C
    stb r3, 0x17(r14)
    VSMode_FrameUpdate_L_8009E7A0:
    addi r18, r18, 0x1
    addi r16, r16, 0x20
    cmpwi r18, 0x8
    blt VSMode_FrameUpdate_L_8009E72C
    VSMode_FrameUpdate_L_8009E7B0:
    bl SyncSlot_GetHostSend
    mr r28, r3
    bl OSGetTime
    lis r6, lbl_805D2B00@ha
    lis r5, g_itemSelects@ha
    mr r30, r3
    lwz r3, 0x7c(r1)
    addi r14, r6, lbl_805D2B00@l
    addi r19, r5, g_itemSelects@l
    mr r29, r4
    mr r26, r20
    mr r25, r14
    mr r22, r19
    addi r24, r3, 0x0
    li r18, 0x0
    la r23, lbl_806D131C(r13)  /* lbl_806D131C */
    VSMode_FrameUpdate_L_8009E7F0:
    mr r3, r18
    bl RingBuffer_GetKartSlot
    lwz r0, 0x0(r26)
    mr r31, r3
    cmplwi r0, 0x0
    beq VSMode_FrameUpdate_L_8009EB14
    lwz r3, lbl_806D1310(r13)
    cmpwi r3, 0x0
    ble VSMode_FrameUpdate_L_8009E840
    subi r0, r3, 0x1
    lfs f30, lbl_806D47A4(r2)
    stw r0, lbl_806D1310(r13)
    li r17, 0x0
    fmr f31, f30
    li r16, 0x0
    stfs f30, 0x0(r31)
    stfs f30, 0x8(r1)
    stfs f30, 0x4(r31)
    stfs f30, 0x8(r31)
    b VSMode_FrameUpdate_L_8009E980
    VSMode_FrameUpdate_L_8009E840:
    mr r3, r0
    bl CarObject_GetRenderObj
    lbz r0, 0x2b8(r3)
    cmplwi r0, 0x1
    bne VSMode_FrameUpdate_L_8009E880
    lwz r3, 0x0(r26)
    bl CarObject_GetRenderObj
    lwz r4, lbl_806D12F4(r13)
    addi r5, r1, 0x8
    lwz r6, 0x0(r25)
    bl CalcSoundDirection
    fmr f30, f1
    lfs f31, lbl_806D47A4(r2)
    li r17, 0x1
    li r16, 0x0
    b VSMode_FrameUpdate_L_8009E980
    VSMode_FrameUpdate_L_8009E880:
    lfs f30, 0x0(r31)
    lfs f0, 0x4(r31)
    lwz r0, g_ccClass(r13)
    stfs f0, 0x8(r1)
    cmpwi r0, 0x2
    lfs f31, 0x8(r31)
    beq VSMode_FrameUpdate_L_8009E958
    bl IsRaceStarted
    clrlwi. r0, r3, 24
    bne VSMode_FrameUpdate_L_8009E8B4
    stw r29, 0x4(r24)
    stw r30, 0x0(r24)
    b VSMode_FrameUpdate_L_8009E958
    VSMode_FrameUpdate_L_8009E8B4:
    lfs f1, 0x8(r1)
    lfs f0, lbl_806D47A8(r2)
    fcmpo cr0, f1, f0
    bge VSMode_FrameUpdate_L_8009E948
    fcmpo cr0, f31, f0
    bge VSMode_FrameUpdate_L_8009E948
    lbz r0, 0x0(r23)
    cmplwi r0, 0x0
    bne VSMode_FrameUpdate_L_8009E930
    lis r4, 0x8000
    lis r3, 0x1062
    lwz r0, 0xf8(r4)
    addi r3, r3, 0x4dd3
    lwz r4, 0x4(r24)
    li r5, 0x0
    srwi r0, r0, 2
    lwz r6, 0x0(r24)
    mulhwu r0, r3, r0
    subfc r4, r4, r29
    subfe r3, r6, r30
    srwi r6, r0, 6
    bl __div2i
    bl __cvt_sll_flt
    lfs f2, lbl_806D47AC(r2)
    lfs f0, lbl_806D47B0(r2)
    fdivs f1, f1, f2
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne VSMode_FrameUpdate_L_8009E930
    li r0, 0x1
    stb r0, 0x0(r23)
    VSMode_FrameUpdate_L_8009E930:
    lbz r0, 0x0(r23)
    cmplwi r0, 0x0
    beq VSMode_FrameUpdate_L_8009E958
    lfs f0, lbl_806D47B4(r2)
    stfs f0, 0x8(r1)
    b VSMode_FrameUpdate_L_8009E958
    VSMode_FrameUpdate_L_8009E948:
    stw r29, 0x4(r24)
    li r0, 0x0
    stb r0, 0x0(r23)
    stw r30, 0x0(r24)
    VSMode_FrameUpdate_L_8009E958:
    lfs f31, 0x8(r31)
    bl IsRaceStarted
    lbz r0, g_isCommHost(r13)
    mr r17, r3
    lwz r16, 0x0(r21)
    cmplwi r0, 0x0
    bne VSMode_FrameUpdate_L_8009E980
    lha r0, 0x24(r31)
    lwz r3, 0x0(r22)
    stw r0, 0x5c(r3)
    VSMode_FrameUpdate_L_8009E980:
    lbz r0, g_isCommHost(r13)
    cmplwi r0, 0x1
    bne VSMode_FrameUpdate_L_8009E9C4
    lwz r3, 0x0(r26)
    bl CarObject_GetTransformMatrix
    stw r16, 0xc(r31)
    lfs f0, 0x30(r3)
    stfs f0, 0x10(r31)
    lfs f0, 0x34(r3)
    stfs f0, 0x14(r31)
    lfs f0, 0x38(r3)
    stfs f0, 0x18(r31)
    lwz r3, 0x0(r26)
    lwz r3, 0x28(r3)
    lfs f0, 0x1c8(r3)
    stfs f0, 0x1c(r31)
    b VSMode_FrameUpdate_L_8009E9DC
    VSMode_FrameUpdate_L_8009E9C4:
    lwz r3, 0x0(r26)
    addi r4, r31, 0x10
    bl CarObject_SetPosition
    lwz r3, 0x0(r26)
    lfs f1, 0x1c(r31)
    bl KartItem_SetCarObjectField1c8Float
    VSMode_FrameUpdate_L_8009E9DC:
    lwz r0, lbl_806CF140(r13)
    cmpw r18, r0
    bne VSMode_FrameUpdate_L_8009EA50
    lwz r3, 0x78(r1)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    fmr f0, f1
    lfs f5, lbl_806D47B8(r2)
    lis r0, 0x4330
    lfd f2, lbl_806D47C8(r2)
    stw r0, 0x70(r1)
    fmr f1, f30
    fmuls f0, f5, f0
    lwz r3, 0x0(r26)
    fmr f4, f31
    lfs f3, 0x8(r1)
    mr r4, r17
    fctiwz f0, f0
    stfd f0, 0x68(r1)
    lwz r0, 0x6c(r1)
    xoris r0, r0, 0x8000
    stw r0, 0x74(r1)
    lfd f0, 0x70(r1)
    fsubs f0, f0, f2
    fdivs f2, f0, f5
    bl CarObject_ApplyInput_AI
    b VSMode_FrameUpdate_L_8009EA6C
    VSMode_FrameUpdate_L_8009EA50:
    fmr f1, f30
    lwz r3, 0x0(r26)
    fmr f2, f30
    lfs f3, 0x8(r1)
    fmr f4, f31
    mr r4, r17
    bl CarObject_ApplyInput_AI
    VSMode_FrameUpdate_L_8009EA6C:
    lwz r3, 0x0(r26)
    mr r4, r16
    bl CarObject_FrameUpdate
    lwz r0, lbl_806CF140(r13)
    cmpw r18, r0
    bne VSMode_FrameUpdate_L_8009EAA4
    lwz r3, 0x0(r22)
    mr r6, r16
    lwz r4, 0x0(r26)
    li r5, 0x0
    lfs f1, 0x8(r1)
    li r7, 0x1
    bl ItemBox_ProcessPickup
    b VSMode_FrameUpdate_L_8009EAC0
    VSMode_FrameUpdate_L_8009EAA4:
    lwz r3, 0x0(r22)
    mr r6, r16
    lwz r4, 0x0(r26)
    li r5, 0x0
    lfs f1, 0x8(r1)
    li r7, 0x0
    bl ItemBox_ProcessPickup
    VSMode_FrameUpdate_L_8009EAC0:
    lbz r0, g_isCommHost(r13)
    cmplwi r0, 0x1
    bne VSMode_FrameUpdate_L_8009EAD8
    lwz r3, 0x0(r22)
    lwz r0, 0x5c(r3)
    sth r0, 0x24(r31)
    VSMode_FrameUpdate_L_8009EAD8:
    cmplwi r28, 0x0
    beq VSMode_FrameUpdate_L_8009EB14
    lbz r0, 0x0(r28)
    extrwi r0, r0, 5, 24
    cmplwi r0, 0x4
    bge VSMode_FrameUpdate_L_8009EB14
    lwz r3, 0x0(r26)
    bl CarObject_GetRenderObj
    lwz r0, 0x240(r3)
    cmpwi r0, 0x1
    bne VSMode_FrameUpdate_L_8009EB14
    lbz r0, 0x0(r28)
    li r3, 0x4
    rlwimi r0, r3, 3, 24, 28
    stb r0, 0x0(r28)
    VSMode_FrameUpdate_L_8009EB14:
    addi r18, r18, 0x1
    addi r25, r25, 0x4
    cmpwi r18, 0x4
    addi r24, r24, 0x8
    addi r23, r23, 0x1
    addi r21, r21, 0x4
    addi r22, r22, 0x4
    addi r26, r26, 0x4
    blt VSMode_FrameUpdate_L_8009E7F0
    lbz r0, g_isCommHost(r13)
    cmplwi r0, 0x0
    bne VSMode_FrameUpdate_L_8009EBA8
    mr r17, r20
    mr r18, r19
    li r21, 0x0
    VSMode_FrameUpdate_L_8009EB50:
    lwz r3, 0x0(r17)
    cmplwi r3, 0x0
    beq VSMode_FrameUpdate_L_8009EB94
    bl CarObject_GetRenderObj
    lbz r0, 0x2b8(r3)
    cmplwi r0, 0x0
    bne VSMode_FrameUpdate_L_8009EB94
    mr r3, r21
    bl RingBuffer_GetKartSlot
    lhz r16, 0x20(r3)
    lwz r3, 0x0(r17)
    bl CarObject_GetRenderObj
    mr r4, r3
    lwz r3, 0x0(r18)
    mr r6, r16
    li r5, 0x0
    bl ItemSelect_StartRouletteSpin
    VSMode_FrameUpdate_L_8009EB94:
    addi r21, r21, 0x1
    addi r18, r18, 0x4
    cmpwi r21, 0x4
    addi r17, r17, 0x4
    blt VSMode_FrameUpdate_L_8009EB50
    VSMode_FrameUpdate_L_8009EBA8:
    bl IsRaceStarted
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne VSMode_FrameUpdate_L_8009EDC4
    lwz r0, lbl_806CF140(r13)
    lis r3, lbl_805D2B00@ha
    addi r4, r3, lbl_805D2B00@l
    lwz r3, lbl_806D12F4(r13)
    slwi r0, r0, 2
    li r5, 0x0
    lwzx r4, r4, r0
    bl Path_LookupCheckpointOffset
    lwz r0, lbl_806CF140(r13)
    lis r4, lbl_805D2B00@ha
    mr r16, r3
    lwz r3, lbl_806D12F4(r13)
    slwi r0, r0, 2
    addi r4, r4, lbl_805D2B00@l
    lwzx r4, r4, r0
    li r5, 0x1
    bl Path_LookupCheckpointOffset
    lwz r7, 0x3fc(r27)
    addi r4, r1, 0x48
    lwz r6, 0x400(r27)
    addi r5, r1, 0x3c
    lwz r0, 0x404(r27)
    stw r7, 0x48(r1)
    lwz r7, 0x408(r27)
    stw r6, 0x4c(r1)
    lwz r6, 0x40c(r27)
    stw r0, 0x50(r1)
    lwz r0, 0x410(r27)
    lfs f0, 0x4(r16)
    stfs f0, 0x48(r1)
    lfs f0, 0xc(r16)
    stfs f0, 0x50(r1)
    stw r7, 0x3c(r1)
    stw r6, 0x40(r1)
    stw r0, 0x44(r1)
    lfs f0, 0x4(r3)
    stfs f0, 0x3c(r1)
    lfs f0, 0xc(r3)
    lwz r3, g_playerRenderObj(r13)
    stfs f0, 0x44(r1)
    bl JObj_IsForwardDotBelowThreshold
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne VSMode_FrameUpdate_L_8009ECA4
    lwz r3, 0xc(r15)
    li r4, 0x1
    bl Jyugemu_ReverseFlag_SetState
    lwz r16, lbl_806D10A0(r13)
    cmplwi r16, 0x0
    bne VSMode_FrameUpdate_L_8009EC84
    li r16, 0x0
    VSMode_FrameUpdate_L_8009EC84:
    cmplwi r16, 0x0
    beq VSMode_FrameUpdate_L_8009ECDC
    bl GetDisplayBufferIndex
    mr r4, r3
    mr r3, r16
    li r5, 0x1
    bl TitleStats_AccumDistanceCounter
    b VSMode_FrameUpdate_L_8009ECDC
    VSMode_FrameUpdate_L_8009ECA4:
    lwz r3, 0xc(r15)
    li r4, 0x0
    bl Jyugemu_ReverseFlag_SetState
    lwz r16, lbl_806D10A0(r13)
    cmplwi r16, 0x0
    bne VSMode_FrameUpdate_L_8009ECC0
    li r16, 0x0
    VSMode_FrameUpdate_L_8009ECC0:
    cmplwi r16, 0x0
    beq VSMode_FrameUpdate_L_8009ECDC
    bl GetDisplayBufferIndex
    mr r4, r3
    mr r3, r16
    li r5, 0x0
    bl TitleStats_AccumDistanceCounter
    VSMode_FrameUpdate_L_8009ECDC:
    lbz r0, g_isCommHost(r13)
    cmplwi r0, 0x1
    bne VSMode_FrameUpdate_L_8009EDC4
    mr r17, r20
    mr r18, r14
    li r21, 0x0
    VSMode_FrameUpdate_L_8009ECF4:
    lwz r3, 0x0(r17)
    cmplwi r3, 0x0
    beq VSMode_FrameUpdate_L_8009EDB0
    bl CarObject_GetRenderObj
    mr r0, r3
    lwz r3, lbl_806D12F4(r13)
    lwz r4, 0x0(r18)
    mr r22, r0
    li r5, 0x0
    bl Path_LookupCheckpointOffset
    mr r16, r3
    lwz r3, lbl_806D12F4(r13)
    lwz r4, 0x0(r18)
    li r5, 0x1
    bl Path_LookupCheckpointOffset
    lwz r7, 0x414(r27)
    addi r4, r1, 0x30
    lwz r6, 0x418(r27)
    addi r5, r1, 0x24
    lwz r0, 0x41c(r27)
    stw r7, 0x30(r1)
    lwz r7, 0x420(r27)
    stw r6, 0x34(r1)
    lwz r6, 0x424(r27)
    stw r0, 0x38(r1)
    lwz r0, 0x428(r27)
    lfs f0, 0x4(r16)
    stfs f0, 0x30(r1)
    lfs f0, 0xc(r16)
    stfs f0, 0x38(r1)
    stw r7, 0x24(r1)
    stw r6, 0x28(r1)
    stw r0, 0x2c(r1)
    lfs f0, 0x4(r3)
    stfs f0, 0x24(r1)
    lfs f0, 0xc(r3)
    mr r3, r22
    stfs f0, 0x2c(r1)
    bl JObj_IsForwardDotBelowThreshold
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne VSMode_FrameUpdate_L_8009EDA8
    lwz r3, 0x248(r22)
    bl fn_801B3BC8
    b VSMode_FrameUpdate_L_8009EDB0
    VSMode_FrameUpdate_L_8009EDA8:
    lwz r3, 0x248(r22)
    bl fn_801B3B7C
    VSMode_FrameUpdate_L_8009EDB0:
    addi r21, r21, 0x1
    addi r18, r18, 0x4
    cmpwi r21, 0x4
    addi r17, r17, 0x4
    blt VSMode_FrameUpdate_L_8009ECF4
    VSMode_FrameUpdate_L_8009EDC4:
    li r0, 0x0
    stw r0, 0x1c(r15)
    bl GetPlayerCarObject
    lwz r4, 0x18(r15)
    lwz r5, 0x1c(r15)
    bl KartItem_UpdateShadowBillboardAndViewport
    lbz r0, lbl_806D12E8(r13)
    cmplwi r0, 0x0
    bne VSMode_FrameUpdate_L_8009EDF0
    li r0, 0x1
    stb r0, lbl_806D12E8(r13)
    VSMode_FrameUpdate_L_8009EDF0:
    bl Fog_UpdateFromCourseScene3D
    lwz r3, lbl_806D12F4(r13)
    bl PathManager_UpdateAll
    lwz r3, 0x4(r15)
    cmplwi r3, 0x0
    beq VSMode_FrameUpdate_L_8009EE28
    bl LakituStart_UpdateCountdown
    clrlwi. r0, r3, 24
    bne VSMode_FrameUpdate_L_8009EE28
    lwz r3, 0x4(r15)
    li r4, 0x1
    bl LakituStart_Dtor
    li r0, 0x0
    stw r0, 0x4(r15)
    VSMode_FrameUpdate_L_8009EE28:
    lwz r3, 0x8(r15)
    bl Jyugemu_Flag_Tick
    lwz r3, 0xc(r15)
    bl Jyugemu_ReverseFlag_Tick
    lwz r3, 0x10(r15)
    bl LapBannerScene_UpdateAndDriveAnim
    lwz r3, 0x14(r15)
    bl CourseEnvironment_UpdateAndCullZones_Timed
    li r21, 0x0
    mr r18, r20
    VSMode_FrameUpdate_L_8009EE50:
    lwz r3, 0x0(r18)
    cmplwi r3, 0x0
    beq VSMode_FrameUpdate_L_8009EEB0
    bl CarObject_GetRenderObj
    mr r16, r3
    mr r17, r20
    li r22, 0x0
    li r23, 0x0
    VSMode_FrameUpdate_L_8009EE70:
    cmpw r21, r23
    beq VSMode_FrameUpdate_L_8009EE9C
    lwz r3, 0x0(r17)
    cmplwi r3, 0x0
    beq VSMode_FrameUpdate_L_8009EE9C
    bl CarObject_GetRenderObj
    lwz r3, 0x23c(r3)
    lwz r0, 0x23c(r16)
    cmpw r3, r0
    bge VSMode_FrameUpdate_L_8009EE9C
    addi r22, r22, 0x1
    VSMode_FrameUpdate_L_8009EE9C:
    addi r23, r23, 0x1
    addi r17, r17, 0x4
    cmpwi r23, 0x4
    blt VSMode_FrameUpdate_L_8009EE70
    stw r22, 0x1bc(r16)
    VSMode_FrameUpdate_L_8009EEB0:
    addi r21, r21, 0x1
    addi r18, r18, 0x4
    cmpwi r21, 0x4
    blt VSMode_FrameUpdate_L_8009EE50
    mr r16, r20
    mr r17, r14
    li r18, 0x0
    VSMode_FrameUpdate_L_8009EECC:
    lwz r3, 0x0(r16)
    cmplwi r3, 0x0
    beq VSMode_FrameUpdate_L_8009EFA0
    bl CarObject_GetRenderObj
    mr r21, r3
    lwz r0, 0x1bc(r3)
    cmpwi r0, 0x0
    bne VSMode_FrameUpdate_L_8009EF48
    li r0, -0x1
    mr r22, r20
    stw r0, 0x1b4(r21)
    mr r23, r14
    li r24, 0x0
    stw r0, 0x1b0(r21)
    VSMode_FrameUpdate_L_8009EF04:
    lwz r0, 0x0(r22)
    cmplwi r0, 0x0
    beq VSMode_FrameUpdate_L_8009EF30
    lwz r3, lbl_806D12F4(r13)
    lwz r4, 0x0(r17)
    lwz r5, 0x0(r23)
    bl Race_CompareKartProgress
    mr r21, r3
    lwz r3, 0x0(r22)
    bl CarObject_GetRenderObj
    stw r21, 0x1b4(r3)
    VSMode_FrameUpdate_L_8009EF30:
    addi r24, r24, 0x1
    addi r23, r23, 0x4
    cmpwi r24, 0x4
    addi r22, r22, 0x4
    blt VSMode_FrameUpdate_L_8009EF04
    b VSMode_FrameUpdate_L_8009EFA0
    VSMode_FrameUpdate_L_8009EF48:
    mr r23, r20
    mr r24, r14
    li r25, 0x0
    VSMode_FrameUpdate_L_8009EF54:
    lwz r3, 0x0(r23)
    cmplwi r3, 0x0
    beq VSMode_FrameUpdate_L_8009EF8C
    lwz r22, 0x1bc(r21)
    bl CarObject_GetRenderObj
    lwz r3, 0x1bc(r3)
    subi r0, r22, 0x1
    cmpw r3, r0
    bne VSMode_FrameUpdate_L_8009EF8C
    lwz r3, lbl_806D12F4(r13)
    lwz r4, 0x0(r24)
    lwz r5, 0x0(r17)
    bl Race_CompareKartProgress
    stw r3, 0x1b0(r21)
    VSMode_FrameUpdate_L_8009EF8C:
    addi r25, r25, 0x1
    addi r24, r24, 0x4
    cmpwi r25, 0x4
    addi r23, r23, 0x4
    blt VSMode_FrameUpdate_L_8009EF54
    VSMode_FrameUpdate_L_8009EFA0:
    addi r18, r18, 0x1
    addi r17, r17, 0x4
    cmpwi r18, 0x4
    addi r16, r16, 0x4
    blt VSMode_FrameUpdate_L_8009EECC
    lwz r4, 0x7c(r1)
    lwz r3, 0x18(r15)
    addi r4, r4, 0x20
    bl CObj_LoadProjMatrix
    lwz r4, 0x7c(r1)
    lwz r3, 0x18(r15)
    addi r4, r4, 0x2c
    bl CObj_ApplyScissor
    bl ItemObjectManager_Update
    lwz r5, 0x7c(r1)
    lwz r3, 0x7c(r1)
    lwz r4, 0x7c(r1)
    lwz r10, 0x2c(r3)
    addi r3, r1, 0x18
    lwz r9, 0x30(r4)
    addi r4, r1, 0xc
    lwz r8, 0x34(r5)
    lwz r7, 0x20(r5)
    lwz r6, 0x24(r5)
    lwz r0, 0x28(r5)
    stw r10, 0xc(r1)
    stw r9, 0x10(r1)
    stw r8, 0x14(r1)
    stw r7, 0x18(r1)
    stw r6, 0x1c(r1)
    stw r0, 0x20(r1)
    bl VfxSlotMgr_Update
    lbz r0, g_rendererGateFlag(r13)
    cmplwi r0, 0x1
    bne VSMode_FrameUpdate_L_8009F0B8
    bl IsRaceStarted
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne VSMode_FrameUpdate_L_8009F0B8
    lfs f1, g_raceTimeRemaining(r13)
    lfs f0, lbl_806D47A4(r2)
    fcmpo cr0, f1, f0
    ble VSMode_FrameUpdate_L_8009F0B8
    lbz r0, g_isCommHost(r13)
    cmplwi r0, 0x1
    bne VSMode_FrameUpdate_L_8009F064
    lfs f0, lbl_806D47BC(r2)
    fsubs f2, f1, f0
    b VSMode_FrameUpdate_L_8009F06C
    VSMode_FrameUpdate_L_8009F064:
    bl RingBuffer_GetEntryHead
    lfs f2, 0xd0(r3)
    VSMode_FrameUpdate_L_8009F06C:
    frsp f1, f2
    lfs f0, lbl_806D47A4(r2)
    stfs f2, g_raceTimeRemaining(r13)
    fcmpo cr0, f1, f0
    cror eq, lt, eq
    bne VSMode_FrameUpdate_L_8009F0B8
    lwz r3, g_playerRenderObj(r13)
    lbz r0, 0x2b8(r3)
    cmplwi r0, 0x0
    bne VSMode_FrameUpdate_L_8009F09C
    lwz r3, 0x24(r15)
    bl fn_80253BE4
    VSMode_FrameUpdate_L_8009F09C:
    lfs f0, lbl_806D47A4(r2)
    li r0, 0xb4
    stw r0, g_sceneTransitionTimer(r13)
    li r3, 0x0
    stfs f0, g_raceTimeRemaining(r13)
    bl fn_8016C554
    bl fn_801B12A0
    VSMode_FrameUpdate_L_8009F0B8:
    lbz r0, g_isCommHost(r13)
    cmplwi r0, 0x1
    bne VSMode_FrameUpdate_L_8009F0D0
    lfs f31, g_raceTimeRemaining(r13)
    bl RingBuffer_GetEntryHead
    stfs f31, 0xd0(r3)
    VSMode_FrameUpdate_L_8009F0D0:
    bl Tachometer_RenderDigits
    bl HitMessageOverlay_FrameUpdate
    lwz r3, 0x24(r15)
    lwz r4, g_currentLap(r13)
    bl HUD_SetCurrentLap
    lwz r3, 0x24(r15)
    lfs f1, g_raceTimeRemaining(r13)
    bl fn_80253FD8
    bl GetPlayerCarObject
    bl CarObject_CalcSpeedRatio
    lfs f0, lbl_806D47C0(r2)
    lwz r3, 0x24(r15)
    fmuls f1, f0, f1
    bl fn_80253EBC
    bl GetPlayerCarObject
    bl KartItem_GetCurrentSpeedWithBonus
    lwz r3, 0x24(r15)
    bl fn_80253EC0
    lwz r3, 0x24(r15)
    lfs f1, g_currentLapTime(r13)
    bl fn_80253EC4
    lwz r3, 0x24(r15)
    lfs f1, g_bestLapTime(r13)
    bl fn_80253F2C
    lwz r3, 0x24(r15)
    lwz r4, g_finalRacePosition(r13)
    bl HUD_SetRacePosition
    lwz r4, g_playerRenderObj(r13)
    lwz r3, 0x24(r15)
    lwz r4, 0x2cc(r4)
    bl fn_80253E18
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne VSMode_FrameUpdate_L_8009F15C
    li r3, 0x0
    VSMode_FrameUpdate_L_8009F15C:
    bl TransitionEffect_Tick
    lbz r0, g_finalLapBannerShown(r13)
    cmplwi r0, 0x0
    bne VSMode_FrameUpdate_L_8009F18C
    lwz r3, g_currentLap(r13)
    lwz r0, g_totalLaps(r13)
    cmpw r3, r0
    blt VSMode_FrameUpdate_L_8009F18C
    li r0, 0x1
    stb r0, g_finalLapBannerShown(r13)
    lwz r3, 0x24(r15)
    bl fn_80253DF0
    VSMode_FrameUpdate_L_8009F18C:
    lfs f1, lbl_806D47A4(r2)
    lfs f0, g_raceTimeRemaining(r13)
    fcmpu cr0, f1, f0
    beq VSMode_FrameUpdate_L_8009F38C
    lwz r0, g_raceResultCode(r13)
    cmpwi r0, -0x2
    bne VSMode_FrameUpdate_L_8009F38C
    lwz r3, g_totalLaps(r13)
    lwz r4, g_currentLap(r13)
    addi r0, r3, 0x1
    cmpw r4, r0
    blt VSMode_FrameUpdate_L_8009F328
    lbz r0, g_finalLapCoinJumpEnabled(r13)
    cmplwi r0, 0x1
    bne VSMode_FrameUpdate_L_8009F1D0
    bl GetPlayerCarObject
    bl CoinJumpFlasher_Toggle
    VSMode_FrameUpdate_L_8009F1D0:
    lwz r0, lbl_806CF140(r13)
    lis r3, g_carObjects@ha
    li r4, 0x0
    slwi r0, r0, 2
    addi r3, r3, g_carObjects@l
    stb r4, lbl_806CF270(r13)
    lwzx r3, r3, r0
    bl KartItem_OnFallOffOrDeath
    lwz r0, lbl_806CF140(r13)
    lis r3, g_carObjects@ha
    addi r3, r3, g_carObjects@l
    li r4, 0x0
    slwi r0, r0, 2
    lwzx r3, r3, r0
    bl CoinJumpFlasher_SetArmed
    lwz r0, lbl_806CF140(r13)
    lis r3, g_itemSelects@ha
    addi r3, r3, g_itemSelects@l
    li r4, 0x0
    slwi r0, r0, 2
    lwzx r3, r3, r0
    bl ItemSelect_Reset
    lwz r4, g_playerRenderObj(r13)
    lwz r3, lbl_806D12EC(r13)
    lwz r0, 0x23c(r4)
    stw r0, g_finalRacePosition(r13)
    bl GetKartSlotCharId
    lwz r4, g_finalRacePosition(r13)
    lfs f1, g_bestLapTime(r13)
    lfs f2, g_totalRaceTime(r13)
    bl RaceResult_StoreLatest
    lwz r3, lbl_806D12EC(r13)
    bl GetKartSlotCharId
    lwz r4, g_finalRacePosition(r13)
    lfs f1, g_bestLapTime(r13)
    lfs f2, g_totalRaceTime(r13)
    bl RaceResult_InsertSortedRank
    stw r3, g_raceResultCode(r13)
    bl SetRaceResultLatestPtr
    lwz r3, 0x24(r15)
    bl fn_80253D00
    lwz r3, 0x18(r15)
    li r4, 0x1
    bl Object_SetByte10_Return1
    lwz r0, g_finalRacePosition(r13)
    cmpwi r0, 0x0
    bne VSMode_FrameUpdate_L_8009F2A4
    lwz r3, 0x8(r15)
    lwz r4, g_playerRenderObj(r13)
    bl Jyugemu_Flag_SetKartDriver
    li r3, 0x1
    bl fn_8016C554
    b VSMode_FrameUpdate_L_8009F2AC
    VSMode_FrameUpdate_L_8009F2A4:
    li r3, 0x0
    bl fn_8016C554
    VSMode_FrameUpdate_L_8009F2AC:
    lwz r0, lbl_806CF140(r13)
    lis r3, g_carObjects@ha
    addi r3, r3, g_carObjects@l
    lwz r4, g_finalRacePosition(r13)
    slwi r0, r0, 2
    lwzx r3, r3, r0
    bl CoinEvent_PlayResultSE
    lwz r3, lbl_806D1300(r13)
    li r4, 0x1
    lwz r5, lbl_806D10A0(r13)
    li r14, 0x0
    addi r0, r3, 0x1
    stb r4, g_raceEnded(r13)
    cmplwi r5, 0x0
    stb r14, g_lakituStartAnimDone(r13)
    stw r0, lbl_806D1300(r13)
    bne VSMode_FrameUpdate_L_8009F2F4
    b VSMode_FrameUpdate_L_8009F2F8
    VSMode_FrameUpdate_L_8009F2F4:
    mr r14, r5
    VSMode_FrameUpdate_L_8009F2F8:
    cmplwi r14, 0x0
    beq VSMode_FrameUpdate_L_8009F3A0
    bl GetDisplayBufferIndex
    lfs f0, g_raceTimeRemaining(r13)
    mr r4, r3
    lwz r5, g_finalRacePosition(r13)
    mr r3, r14
    fctiwz f0, f0
    stfd f0, 0x70(r1)
    lwz r6, 0x74(r1)
    bl RankLog_SetRaceResult
    b VSMode_FrameUpdate_L_8009F3A0
    VSMode_FrameUpdate_L_8009F328:
    lbz r0, g_lapChangePending(r13)
    cmplwi r0, 0x0
    beq VSMode_FrameUpdate_L_8009F3A0
    lbz r0, g_finalLapBannerShown(r13)
    cmplwi r0, 0x0
    beq VSMode_FrameUpdate_L_8009F34C
    lwz r3, 0x10(r15)
    bl LapBannerScene_TriggerBannerAnim
    b VSMode_FrameUpdate_L_8009F350
    VSMode_FrameUpdate_L_8009F34C:
    bl fn_8016C5CC
    VSMode_FrameUpdate_L_8009F350:
    lwz r14, lbl_806D10A0(r13)
    cmplwi r14, 0x0
    bne VSMode_FrameUpdate_L_8009F360
    li r14, 0x0
    VSMode_FrameUpdate_L_8009F360:
    cmplwi r14, 0x0
    beq VSMode_FrameUpdate_L_8009F380
    bl GetDisplayBufferIndex
    lwz r5, g_currentLap(r13)
    mr r4, r3
    mr r3, r14
    subi r5, r5, 0x1
    bl TitleTracker_ResetPerRound
    VSMode_FrameUpdate_L_8009F380:
    li r0, 0x0
    stb r0, g_lapChangePending(r13)
    b VSMode_FrameUpdate_L_8009F3A0
    VSMode_FrameUpdate_L_8009F38C:
    lwz r3, lbl_806D1300(r13)
    cmpwi r3, 0x0
    beq VSMode_FrameUpdate_L_8009F3A0
    addi r0, r3, 0x1
    stw r0, lbl_806D1300(r13)
    VSMode_FrameUpdate_L_8009F3A0:
    lwz r3, 0x24(r15)
    bl HUD_FrameUpdate
    lwz r3, lbl_806D10D0(r13)
    cmplwi r3, 0x0
    bne VSMode_FrameUpdate_L_8009F3B8
    li r3, 0x0
    VSMode_FrameUpdate_L_8009F3B8:
    bl clItemBoxManager_Update
    bl fn_8013A534
    lwz r3, g_weatherSystem(r13)
    cmplwi r3, 0x0
    beq VSMode_FrameUpdate_L_8009F3D0
    bl fn_8016B32C
    VSMode_FrameUpdate_L_8009F3D0:
    lbz r0, g_isCommHost(r13)
    cmplwi r0, 0x0
    beq VSMode_FrameUpdate_L_8009F41C
    li r15, 0x0
    VSMode_FrameUpdate_L_8009F3E0:
    lwz r0, 0x0(r20)
    cmplwi r0, 0x0
    beq VSMode_FrameUpdate_L_8009F408
    lwz r4, 0x0(r19)
    mr r3, r15
    lwz r4, 0x54(r4)
    addi r0, r4, 0x1
    clrlwi r14, r0, 16
    bl RingBuffer_GetKartSlot
    sth r14, 0x20(r3)
    VSMode_FrameUpdate_L_8009F408:
    addi r15, r15, 0x1
    addi r19, r19, 0x4
    cmpwi r15, 0x4
    addi r20, r20, 0x4
    blt VSMode_FrameUpdate_L_8009F3E0
    VSMode_FrameUpdate_L_8009F41C:
    lbz r0, lbl_806D0051(r13)
    cmplwi r0, 0x0
    bne VSMode_FrameUpdate_L_8009F454
    lwz r3, 0x78(r1)
    li r4, 0x400
    lwz r12, 0x0(r3)
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne VSMode_FrameUpdate_L_8009F454
    li r3, 0x4
    b VSMode_FrameUpdate_L_8009F458
    VSMode_FrameUpdate_L_8009F454:
    li r3, -0x2
    VSMode_FrameUpdate_L_8009F458:
    psq_l f31, 0xe8(r1), 0, 0
    lfd f31, 0xe0(r1)
    psq_l f30, 0xd8(r1), 0, 0
    lfd f30, 0xd0(r1)
    lmw r14, 0x88(r1)
    lwz r0, 0xf4(r1)
    mtlr r0
    addi r1, r1, 0xf0
    blr
}
#undef CObj_ApplyScissor
#undef CObj_LoadProjMatrix
#undef CalcSoundDirection
#undef CarObject_ApplyInput_AI
#undef CarObject_CalcSpeedRatio
#undef CarObject_FrameUpdate
#undef CarObject_GetRenderObj
#undef CarObject_GetTransformMatrix
#undef CarObject_SetPosition
#undef CoinEvent_PlayResultSE
#undef CoinJumpFlasher_SetArmed
#undef CoinJumpFlasher_Toggle
#undef CommBroadcast_ClearTable
#undef CommBroadcast_ScanForMySyncMatch
#undef CountPeersWithRole
#undef CourseEnvironment_UpdateAndCullZones_Timed
#undef DebugPrintf
#undef Fog_UpdateFromCourseScene3D
#undef Frame_UpdatePerFrameState
#undef GetCoinMilage
#undef GetDisplayBufferIndex
#undef GetInputManager
#undef GetKartSlotCharId
#undef GetPlayerCarObject
#undef GetRaceContextPtr
#undef HSD_RandSeedPtr
#undef HUD_FrameUpdate
#undef HUD_SetCurrentLap
#undef HUD_SetRacePosition
#undef HitMessageOverlay_FrameUpdate
#undef InputMgr_GetPlayer
#undef IsRaceStarted
#undef IsSyncReached
#undef ItemBox_ProcessPickup
#undef ItemObjectManager_PerFrameUpdate
#undef ItemObjectManager_Update
#undef ItemSelect_Reset
#undef ItemSelect_StartRouletteSpin
#undef JObj_IsForwardDotBelowThreshold
#undef Jyugemu_Flag_SetKartDriver
#undef Jyugemu_Flag_Tick
#undef Jyugemu_ReverseFlag_SetState
#undef Jyugemu_ReverseFlag_Tick
#undef KartItem_GetCurrentSpeedWithBonus
#undef KartItem_OnFallOffOrDeath
#undef KartItem_SetCarObjectField1c8Float
#undef KartItem_UpdateShadowBillboardAndViewport
#undef LakituStart_Dtor
#undef LakituStart_SetCountdownHoldFrames
#undef LakituStart_UpdateCountdown
#undef LapBannerScene_TriggerBannerAnim
#undef LapBannerScene_UpdateAndDriveAnim
#undef Live_IsConnectReady
#undef OSGetTime
#undef Object_SetByte10_Return1
#undef PCBComm_Process
#undef PathManager_RefreshFinishPositions
#undef PathManager_UpdateAll
#undef Path_LookupCheckpointOffset
#undef PcbSlot_ResetScratchAreas
#undef PlayStats_IncVsPeerCount
#undef PlayStats_IncVsPlay
#undef RaceResult_InsertSortedRank
#undef RaceResult_StoreLatest
#undef RaceSlot_GetDriverId
#undef Race_CompareKartProgress
#undef Race_PerFrameTickAndAudio
#undef Rand_SetSeedDebug
#undef RankLog_SetRaceResult
#undef RankingMgr_UpdatePositions
#undef ReplayRandCursor_Reset
#undef RingBuffer_GetEntryHead
#undef RingBuffer_GetKartSlot
#undef RingBuffer_GetRankSlot
#undef SetRaceResultLatestPtr
#undef SetSyncTarget
#undef SyncSlot_ApplyCourseChoice
#undef SyncSlot_GetHostSend
#undef SyncSlot_GetRecv
#undef Tachometer_RenderDigits
#undef Timer_Decrement
#undef TitleStats_AccumDistanceCounter
#undef TitleTracker_ResetPerRound
#undef TransitionEffect_Tick
#undef VIWaitForRetrace
#undef VfxSlotMgr_Update
#undef VoiceQueue_Clear
#undef __cvt_sll_flt
#undef __div2i
#undef clItemBoxManager_Update
#undef fn_8013A534
#undef fn_8016B32C
#undef fn_8016C554
#undef fn_8016C598
#undef fn_8016C5CC
#undef fn_8016C600
#undef fn_801B12A0
#undef fn_801B3B7C
#undef fn_801B3BC8
#undef fn_801B5C98
#undef fn_801DC69C
#undef fn_801DC6B4
#undef fn_801DC6CC
#undef fn_801DC6E4
#undef fn_801DC6FC
#undef fn_801DC714
#undef fn_801DC72C
#undef fn_801DC740
#undef fn_80208E30
#undef fn_8020AF08
#undef fn_8020B07C
#undef fn_80253BE4
#undef fn_80253D00
#undef fn_80253DF0
#undef fn_80253E18
#undef fn_80253EBC
#undef fn_80253EC0
#undef fn_80253EC4
#undef fn_80253F2C
#undef fn_80253FD8
#undef g_bestLapTime
#undef g_carObjects
#undef g_ccClass
#undef g_currentLap
#undef g_currentLapTime
#undef g_currentSceneState
#undef g_finalLapBannerShown
#undef g_finalLapCoinJumpEnabled
#undef g_finalRacePosition
#undef g_isCommHost
#undef g_itemSelects
#undef g_lakituStartAnimDone
#undef g_lapChangePending
#undef g_playerData
#undef g_playerRenderObj
#undef g_raceEnded
#undef g_raceResultCode
#undef g_raceTimeRemaining
#undef g_rendererGateFlag
#undef g_sceneTransitionTimer
#undef g_totalLaps
#undef g_totalRaceTime
#undef g_weatherSystem
#undef lbl_805D2AA8
#undef lbl_805D2B00
#undef lbl_806792D8
#undef lbl_806CF140
#undef lbl_806CF148
#undef lbl_806CF270
#undef lbl_806D0051
#undef lbl_806D109C
#undef lbl_806D10A0
#undef lbl_806D10D0
#undef lbl_806D1191
#undef lbl_806D12E8
#undef lbl_806D12EC
#undef lbl_806D12F0
#undef lbl_806D12F4
#undef lbl_806D12FC
#undef lbl_806D1300
#undef lbl_806D1310
#undef lbl_806D1314
#undef lbl_806D1318
#undef lbl_806D1319
#undef lbl_806D131C
#undef lbl_806D134C
#undef lbl_806D1350
#undef lbl_806D47A0
#undef lbl_806D47A4
#undef lbl_806D47A8
#undef lbl_806D47AC
#undef lbl_806D47B0
#undef lbl_806D47B4
#undef lbl_806D47B8
#undef lbl_806D47BC
#undef lbl_806D47C0
#undef lbl_806D47C8
#undef memset
#undef race_result_handler

/* ==== BtMode_Dtor ==== */
#pragma cplusplus on
#define AI_SystemDtor AI_SystemDtor_p1
#define ClRomTable_PurgeAll ClRomTable_PurgeAll_p1
#define CourseBgm_Free CourseBgm_Free_p1
#define CourseEnvironment_Dtor CourseEnvironment_Dtor_p1
#define HitMessageOverlay_Destroy HitMessageOverlay_Destroy_p1
#define ItemObjectManager_Reset ItemObjectManager_Reset_p1
#define Jyugemu_Flag_Dtor Jyugemu_Flag_Dtor_p1
#define Jyugemu_ReverseFlag_Dtor Jyugemu_ReverseFlag_Dtor_p1
#define LakituStart_Dtor LakituStart_Dtor_p1
#define LapBannerScene_Dtor LapBannerScene_Dtor_p1
#define PathParticipantArray_Dtor PathParticipantArray_Dtor_p1
#define Release Release_p1
#define SceneDrawList_Reset SceneDrawList_Reset_p1
#define SetActiveCamera SetActiveCamera_p1
#define SetCourseScene3D SetCourseScene3D_p1
#define SetPlayerCarObject SetPlayerCarObject_p1
#define SetResourceLoadingFlag SetResourceLoadingFlag_p1
#define Tachometer_Destroy Tachometer_Destroy_p1
#define VfxSlotMgr_Shutdown VfxSlotMgr_Shutdown_p1
#define clRom_PurgeAll clRom_PurgeAll_p1
#define fn_8013A6F8 fn_8013A6F8_p1
#define fn_8016C634 fn_8016C634_p1
#define fn_801B6B94 fn_801B6B94_p1
#define fn_80208FE4 fn_80208FE4_p1
#define fn_8020AF08 fn_8020AF08_p1
#define fn_80254134 fn_80254134_p1
#define g_currentSceneState g_currentSceneState_p1
#define g_weatherSystem g_weatherSystem_p1
#define lbl_8040E734 lbl_8040E734_p1
#define lbl_8040E76C lbl_8040E76C_p1
#define lbl_806D129C lbl_806D129C_p1
#define lbl_806D12F4 lbl_806D12F4_p1
#define lbl_806D12F8 lbl_806D12F8_p1
#define lbl_80320960 ((const char *)lbl_80320960)
#include "game/BtMode_DtorPrivate.h"
extern "C" {
extern void *g_weatherSystem;
extern int g_currentSceneState, lbl_806D129C;
extern void *lbl_806D12F4;
extern RefObject162 *lbl_806D12F8;

extern int lbl_8040E734[], lbl_8040E76C[];
void fn_801B6B94();
void fn_8016C634(void *, int);
void fn_8020AF08(void *, int);
void fn_80254134(void *, int);

void Tachometer_Destroy();
void HitMessageOverlay_Destroy();





}
static inline void baseDtor(BtModeView *p) {
    if (p) p->vt = lbl_8040E76C;
}
#pragma use_lmw_stmw on
extern "C" BtModeView *BtMode_Dtor(BtModeView *self, short deleting) {
    const char *messages = lbl_80320960;
    if (self) {
        self->vt = lbl_8040E734;
        fn_801B6B94();
        lbl_806D129C = 0;
        if (g_currentSceneState != 0x2a) {
            if (g_weatherSystem) {
                fn_8016C634(g_weatherSystem, 1);
                g_weatherSystem = 0;
            }
            SetActiveCamera(0, 0);
            if (self->field34) {
                fn_8020AF08(self->field34, 1);
                self->field34 = 0;
            }
            ProcessSystemTick((int)messages + 0x4e4);
            AI_SystemDtor(self->ai, 1);
            fn_80208FE4(self->system, 1);
            ProcessSystemTick((int)messages + 0x4f4);
            for (int i=0; i<4; ++i) {
                if (g_itemSelects[i]) ItemSelect_Dtor(g_itemSelects[i], 1);
                g_itemSelects[i] = 0;
            }
            Tachometer_Destroy();
            HitMessageOverlay_Destroy();
            ProcessSystemTick((int)messages + 0x500);
            fn_80254134(self->field24, 1);
            delete self->child;
            LakituStart_Dtor(self->start, 1);
            Jyugemu_Flag_Dtor(self->flag, 1);
            Jyugemu_ReverseFlag_Dtor(self->reverseFlag, 1);
            LapBannerScene_Dtor(self->banner, 1);
            PathParticipantArray_Dtor(lbl_806D12F4, 1);
            ProcessSystemTick((int)messages + 0x524);
            for (int i=0; i<4; ++i) {
                if (g_carObjects[i]) delete g_carObjects[i];
                g_carObjects[i] = 0;
            }
            if (self->child20) delete self->child20;
            CourseEnvironment_Dtor(self->environment, 1);
            ProcessSystemTick((int)messages + 0x548);
            if (lbl_806D12F8) {
                Release(lbl_806D12F8);
                lbl_806D12F8 = 0;
            }
            ItemObjectManager_Reset();
            VfxSlotMgr_Shutdown();
            RankingTable_Init(GetRaceContextPtr());
            ClRomTable_PurgeAll();
            self->start = 0;
            self->flag = 0;
            self->reverseFlag = 0;
            self->banner = 0;
            lbl_806D12F4 = 0;
            self->child = 0;
            self->environment = 0;
            SetPlayerCarObject(0);
            delete lbl_806D10D0;
            lbl_806D10D0 = 0;
            fn_8013A6F8();
            g_raceCamera = 0;
            delete lbl_806D109C;
            lbl_806D109C = 0;
            CourseBgm_Free();
            SceneDrawList_Reset();
            ProcessSystemTick((int)messages + 0x55c);
            delete g_courseData[0];
            g_courseData[0] = 0;
            SetResourceLoadingFlag(0);
            clRom_PurgeAll();
            SetCourseScene3D(0);
            ProcessSystemTick((int)messages + 0x578);
        }
        baseDtor(self);
        if (deleting > 0) MemoryManager_TimedFree(self);
    }
    return self;
}
#pragma use_lmw_stmw reset
#undef AI_SystemDtor
#undef ClRomTable_PurgeAll
#undef CourseBgm_Free
#undef CourseEnvironment_Dtor
#undef HitMessageOverlay_Destroy
#undef ItemObjectManager_Reset
#undef Jyugemu_Flag_Dtor
#undef Jyugemu_ReverseFlag_Dtor
#undef LakituStart_Dtor
#undef LapBannerScene_Dtor
#undef PathParticipantArray_Dtor
#undef Release
#undef SceneDrawList_Reset
#undef SetActiveCamera
#undef SetCourseScene3D
#undef SetPlayerCarObject
#undef SetResourceLoadingFlag
#undef Tachometer_Destroy
#undef VfxSlotMgr_Shutdown
#undef clRom_PurgeAll
#undef fn_8013A6F8
#undef fn_8016C634
#undef fn_801B6B94
#undef fn_80208FE4
#undef fn_8020AF08
#undef fn_80254134
#undef g_currentSceneState
#undef g_weatherSystem
#undef lbl_8040E734
#undef lbl_8040E76C
#undef lbl_806D129C
#undef lbl_806D12F4
#undef lbl_806D12F8
#undef lbl_80320960
#pragma cplusplus off

/* ==== VSMode_Init ==== */
#define AI_GetItemList AI_GetItemList_p2
#define AI_SystemInit AI_SystemInit_p2
#define Alloc Alloc_p2
#define CObj_UpdatePerspParam CObj_UpdatePerspParam_p2
#define Camera_Create Camera_Create_p2
#define CarObject_GetRenderObj CarObject_GetRenderObj_p2
#define CarObject_GetTransformMatrix CarObject_GetTransformMatrix_p2
#define CarObject_Init CarObject_Init_p2
#define CoinSystem_Init CoinSystem_Init_p2
#define CommBroadcast_SetKartRankNibble CommBroadcast_SetKartRankNibble_p2
#define CourseBgm_Load CourseBgm_Load_p2
#define CourseData_GetDefaultPathKey_Safe CourseData_GetDefaultPathKey_Safe_p2
#define CourseData_GetOrCreate CourseData_GetOrCreate_p2
#define CourseObjectManager_Init CourseObjectManager_Init_p2
#define DMAChannelManager_Init DMAChannelManager_Init_p2
#define DebugPrintf DebugPrintf_p2
#define FinalLapBanner_Init FinalLapBanner_Init_p2
#define GetCourseBgmEntry GetCourseBgmEntry_p2
#define GetCourseDataPtr GetCourseDataPtr_p2
#define GetCourseStartYaw GetCourseStartYaw_p2
#define GetEnemyParam GetEnemyParam_p2
#define GetKartModelNameEntry GetKartModelNameEntry_p2
#define GetKartSlotCharId GetKartSlotCharId_p2
#define GetRaceContextPtr GetRaceContextPtr_p2
#define GetStartPosition GetStartPosition_p2
#define HSD_LObjLoadDesc HSD_LObjLoadDesc_p2
#define HSD_RandSeedPtr HSD_RandSeedPtr_p2
#define HUD_Init HUD_Init_p2
#define HUD_RegisterOverlay HUD_RegisterOverlay_p2
#define HUD_SetTotalLaps HUD_SetTotalLaps_p2
#define HitMessageOverlay_Init HitMessageOverlay_Init_p2
#define InputManager_Init InputManager_Init_p2
#define IsTimerModeEnabled IsTimerModeEnabled_p2
#define ItemObjectManager_Init ItemObjectManager_Init_p2
#define ItemSelect_AddSlotItem ItemSelect_AddSlotItem_p2
#define ItemSelect_GetSlotItemId ItemSelect_GetSlotItemId_p2
#define ItemSelect_Init ItemSelect_Init_p2
#define Jyugemu_Flag_Ctor Jyugemu_Flag_Ctor_p2
#define Jyugemu_ReverseFlag_Ctor Jyugemu_ReverseFlag_Ctor_p2
#define KartItem_SetField358 KartItem_SetField358_p2
#define KartItem_SetShortArray34a KartItem_SetShortArray34a_p2
#define LakituStart_Init LakituStart_Init_p2
#define LakituStart_SetCountdownHoldFrames LakituStart_SetCountdownHoldFrames_p2
#define MemoryManager_TimedFree MemoryManager_TimedFree_p2
#define OSGetTime OSGetTime_p2
#define PathManager_Init PathManager_Init_p2
#define PathManager_RegisterCarObject PathManager_RegisterCarObject_p2
#define PreloadEffectResources PreloadEffectResources_p2
#define PreloadItemResources PreloadItemResources_p2
#define PreloadResource PreloadResource_p2
#define ProcessSystemTick ProcessSystemTick_p2
#define RaceScene_GetPerspFovyForCup RaceScene_GetPerspFovyForCup_p2
#define RaceSlot_InitSlot RaceSlot_InitSlot_p2
#define RankingTable_Init RankingTable_Init_p2
#define Scene3D_GetCameraPos Scene3D_GetCameraPos_p2
#define Scene3D_Init Scene3D_Init_p2
#define Scene3D_SetupProjection Scene3D_SetupProjection_p2
#define SetActiveCamera SetActiveCamera_p2
#define SetCourseScene3D SetCourseScene3D_p2
#define SetPlayerCarObject SetPlayerCarObject_p2
#define SetResourceLoadingFlag SetResourceLoadingFlag_p2
#define SoundChannels_ClearAll SoundChannels_ClearAll_p2
#define SoundDriver_GetOrCreate SoundDriver_GetOrCreate_p2
#define SyncSlot_GetHostSend SyncSlot_GetHostSend_p2
#define SyncSlot_GetRecv SyncSlot_GetRecv_p2
#define Tachometer_Init Tachometer_Init_p2
#define TitleTracker_OnRaceStart_Stub TitleTracker_OnRaceStart_Stub_p2
#define TransitionEffect_GetOrCreate TransitionEffect_GetOrCreate_p2
#define VSAI VSAI_p2
#define VSCamera VSCamera_p2
#define VSCar VSCar_p2
#define VSCollision VSCollision_p2
#define VSFinalLap VSFinalLap_p2
#define VSFinalObject VSFinalObject_p2
#define VSFlag VSFlag_p2
#define VSHud VSHud_p2
#define VSInput VSInput_p2
#define VSItems VSItems_p2
#define VSLakitu VSLakitu_p2
#define VSOwner VSOwner_p2
#define VSPath VSPath_p2
#define VSPeer VSPeer_p2
#define VSRaceRow VSRaceRow_p2
#define VSReverse VSReverse_p2
#define VSScene VSScene_p2
#define VSWeather VSWeather_p2
#define VS_MODE VS_MODE_p2
#define VoiceSystem_BindKartCarObject VoiceSystem_BindKartCarObject_p2
#define VoiceSystem_SetCheckpointsForTotalLaps VoiceSystem_SetCheckpointsForTotalLaps_p2
#define WeatherSystem_Init WeatherSystem_Init_p2
#define clEnemyParam_FillItemListIds clEnemyParam_FillItemListIds_p2
#define fn_802090A8 fn_802090A8_p2
#define fn_8020B234 fn_8020B234_p2
#define fn_8023DBEC fn_8023DBEC_p2
#define fn_80253EB8 fn_80253EB8_p2
#define g_bestLapTime g_bestLapTime_p2
#define g_carObjects g_carObjects_p2
#define g_ccClass g_ccClass_p2
#define g_cupId g_cupId_p2
#define g_currentLap g_currentLap_p2
#define g_currentLapTime g_currentLapTime_p2
#define g_finalLapBannerShown g_finalLapBannerShown_p2
#define g_finalRacePosition g_finalRacePosition_p2
#define g_gameMode g_gameMode_p2
#define g_humanPlayerCount g_humanPlayerCount_p2
#define g_isCommHost g_isCommHost_p2
#define g_itemSelects g_itemSelects_p2
#define g_kartStartSlot g_kartStartSlot_p2
#define g_lakituStartAnimDone g_lakituStartAnimDone_p2
#define g_lapBonusTimeDelta g_lapBonusTimeDelta_p2
#define g_lapChangePending g_lapChangePending_p2
#define g_localPcbRole g_localPcbRole_p2
#define g_longRoundFlag g_longRoundFlag_p2
#define g_namCamFlag g_namCamFlag_p2
#define g_objCollChecker g_objCollChecker_p2
#define g_playerRenderObj g_playerRenderObj_p2
#define g_raceCamera g_raceCamera_p2
#define g_raceEnded g_raceEnded_p2
#define g_raceFrameCounterLo2digits g_raceFrameCounterLo2digits_p2
#define g_raceHud g_raceHud_p2
#define g_raceRankingPathObject g_raceRankingPathObject_p2
#define g_raceResultCode g_raceResultCode_p2
#define g_raceTimeRemaining g_raceTimeRemaining_p2
#define g_reverseRoundFlag g_reverseRoundFlag_p2
#define g_roundIndex g_roundIndex_p2
#define g_sceneTransitionTimer g_sceneTransitionTimer_p2
#define g_totalLaps g_totalLaps_p2
#define g_totalRaceTime g_totalRaceTime_p2
#define g_weatherSystem g_weatherSystem_p2
#define jumptable_8040E748 jumptable_8040E748_p2
#define lbl_80598A60 lbl_80598A60_p2
#define lbl_805A6154 lbl_805A6154_p2
#define lbl_805D2AA8 lbl_805D2AA8_p2
#define lbl_805D2B00 lbl_805D2B00_p2
#define lbl_806CF110 lbl_806CF110_p2
#define lbl_806CF140 lbl_806CF140_p2
#define lbl_806CF144 lbl_806CF144_p2
#define lbl_806CF148 lbl_806CF148_p2
#define lbl_806D1050 lbl_806D1050_p2
#define lbl_806D10A0 lbl_806D10A0_p2
#define lbl_806D1264 lbl_806D1264_p2
#define lbl_806D129C lbl_806D129C_p2
#define lbl_806D12E8 lbl_806D12E8_p2
#define lbl_806D12EC lbl_806D12EC_p2
#define lbl_806D12F0 lbl_806D12F0_p2
#define lbl_806D12F4 lbl_806D12F4_p2
#define lbl_806D12F8 lbl_806D12F8_p2
#define lbl_806D12FC lbl_806D12FC_p2
#define lbl_806D1300 lbl_806D1300_p2
#define lbl_806D1304 lbl_806D1304_p2
#define lbl_806D1308 lbl_806D1308_p2
#define lbl_806D1318 lbl_806D1318_p2
#define lbl_806D1319 lbl_806D1319_p2
#define lbl_806D131C lbl_806D131C_p2
#define lbl_806D47A4 lbl_806D47A4_p2
#define lbl_806D47A8 lbl_806D47A8_p2
#define lbl_806D47AC lbl_806D47AC_p2
#define lbl_806D47C0 lbl_806D47C0_p2
#define lbl_806D47D0 lbl_806D47D0_p2
/*
 * Bounded whole-body C++ reconstruction (cycle_retrofit_vsmode_cpp).
 * Disabled best approach B: natural constructor ABI/size was checked against
 * full direct constructor bodies. Non-constructor ABI audit remains incomplete.
 * Three approaches: A 85.35609%, B 92.18771%, C 84.78043% (see HANDOFF).
 * B emits 3520B text / 264B automatic EH; target is 3516B / 264B.
 * External constructor mangled bridges must be restored before re-enabling.
 * This is NOT a genuine matched implementation; the original fallback below is
 * untouched. Layouts describe only bytes observed by this caller.
 */
#if 1
#pragma cplusplus on
void* operator new(unsigned long);
void operator delete(void*);

struct VSInput { unsigned char bytes[0x37C]; VSInput(); };
struct VSCamera { unsigned char bytes[0x2C]; VSCamera(int, int, void*, float, float); };
struct VSCar {
    unsigned char prefix[0x104]; void* itemSelect; unsigned char suffix[0x10];
    VSCar(int, int, int, int, unsigned char, int, int, unsigned char, float, float, float);
};
struct VSPath {
    unsigned char bytes[0x4E8];
    VSPath(void*, VSCar*, void*, float*, float*, float*);
};
struct VSLakitu {
    unsigned char bytes[0x58];
    VSLakitu(void*, int, float, float, float);
};
struct VSScene { unsigned char bytes[0x3084]; VSScene(void*); };
struct VSFlag { unsigned char bytes[0xC]; VSFlag(VSScene*); };
struct VSReverse { unsigned char bytes[0x14]; VSReverse(void*); };
struct VSFinalLap { unsigned char bytes[0x10]; VSFinalLap(void*); };
struct VSCollision { unsigned char bytes[0x18]; VSCollision(); };
struct VSAI { unsigned char bytes[4]; VSAI(VSPath*, VSCollision*, int); };
struct VSHud { unsigned char bytes[0x80]; VSHud(VSPath*); };
struct VSItems { unsigned char bytes[0x88]; VSItems(int, unsigned char); };
struct VSWeather { unsigned char bytes[0x1B4]; VSWeather(unsigned char); };
struct VSFinalObject { unsigned char bytes[0x24]; VSFinalObject(int); };
struct VSOwner {
    void* unseen0;
    VSLakitu* lakitu;
    VSFlag* flag;
    VSReverse* reverse;
    VSFinalLap* finalLap;
    VSInput* input;
    VSScene* scene;
    void* unseen1C;
    VSCamera* camera;
    VSHud* hud;
    void* unseen28;
    VSAI* ai;
    VSCollision* collision;
    VSFinalObject* finalObject;
};
struct VSPeer {
    unsigned char teamTop : 1, teamId : 3, teamLow : 4;
    unsigned char unknown1, unknown2, cameraFlags;
    unsigned char charId : 4, charLow : 4;
    unsigned char unknown5, tuning;
    unsigned char unknown7[9];
    unsigned short items[3];
    unsigned short shorts16[3];
    unsigned char remainder[0xA3C - 0x1C];
};
struct VSHostFlags { unsigned char ready : 1, rest : 7; };
struct VSRaceRow { signed char laps; unsigned char pad[3]; float remaining, bonus; };

extern "C" {

extern unsigned char lbl_80598A60[];
extern VSPeer lbl_805A6154[];
extern VSCar* g_carObjects[];
extern VSItems* g_itemSelects[];
extern int lbl_805D2B00[];
extern unsigned long long lbl_805D2AA8[];
extern unsigned char VS_MODE[];
extern const float lbl_806D47A4, lbl_806D47A8, lbl_806D47AC, lbl_806D47C0, lbl_806D47D0;
extern int g_cupId, g_longRoundFlag, g_reverseRoundFlag, g_localPcbRole, g_ccClass;
extern int lbl_806CF110, lbl_806CF140, lbl_806CF144, lbl_806D129C, lbl_806D12F0;
extern int lbl_806D12EC, lbl_806D12FC, lbl_806D1050, g_kartStartSlot;
extern int g_sceneTransitionTimer, g_finalRacePosition, g_currentLap, g_raceResultCode;
extern int lbl_806D1304, lbl_806D1308, lbl_806D1300, g_totalLaps;
extern int g_raceFrameCounterLo2digits, g_roundIndex, g_gameMode, g_humanPlayerCount;
extern unsigned char g_isCommHost, g_namCamFlag, g_lakituStartAnimDone, g_raceEnded;
extern unsigned char g_finalLapBannerShown, g_lapChangePending, lbl_806CF148, lbl_806D12E8;
extern unsigned char lbl_806D1318, lbl_806D1319, lbl_806D131C[4], lbl_806D1264[3];
extern float g_bestLapTime, g_currentLapTime, g_totalRaceTime, g_raceTimeRemaining, g_lapBonusTimeDelta;
extern int* HSD_RandSeedPtr;
extern void* lbl_806D10A0;
extern void* lbl_806D12F8;
extern void* g_playerRenderObj;
extern VSCamera* g_raceCamera;
extern VSCollision* g_objCollChecker;
extern VSHud* g_raceHud;
extern VSWeather* g_weatherSystem;
extern VSPath* lbl_806D12F4;
extern VSPath* g_raceRankingPathObject;

void ProcessSystemTick(const char*);
unsigned char* SyncSlot_GetRecv();
unsigned char* SyncSlot_GetHostSend();
void SetResourceLoadingFlag(int);
void DMAChannelManager_Init();
void TransitionEffect_GetOrCreate();
void CourseData_GetOrCreate(int, int, int);
void* GetCourseDataPtr();
void* HSD_LObjLoadDesc(void*);
void SetActiveCamera(int, VSCamera*);
void SoundChannels_ClearAll();
void ItemObjectManager_Init();
void CourseObjectManager_Init();
void* GetRaceContextPtr();
void RankingTable_Init(void*);
void* GetCourseBgmEntry();
void SoundDriver_GetOrCreate(void*);
void CoinSystem_Init(int, int);
void TitleTracker_OnRaceStart_Stub(void*);
void DebugPrintf(const char*, ...);
void RaceSlot_InitSlot(int, int, int, int, int);
int GetStartPosition(int, float*, float*, float*);
float GetCourseStartYaw();
int GetKartSlotCharId(int);
void* CarObject_GetRenderObj(VSCar*);
float* CarObject_GetTransformMatrix(VSCar*);
void KartItem_SetShortArray34a(void*, unsigned short*);
void KartItem_SetField358(void*, int);
void VoiceSystem_BindKartCarObject(int, VSCar*);
void SetPlayerCarObject(VSCar*);
void* CourseData_GetDefaultPathKey_Safe();
int PathManager_RegisterCarObject(VSPath*, float*, float*, float*, VSCar*, void*, int);
void LakituStart_SetCountdownHoldFrames(VSLakitu*, int);
void** GetKartModelNameEntry(int, int);
void Scene3D_GetCameraPos(VSScene*, float*, float*);
void Scene3D_SetupProjection(VSScene*, float, float);
float RaceScene_GetPerspFovyForCup();
void CObj_UpdatePerspParam(VSScene*, float);
void CommBroadcast_SetKartRankNibble(int, int);
void Tachometer_Init();
void HitMessageOverlay_Init();
void HUD_RegisterOverlay(VSHud*, int, int);
int IsTimerModeEnabled();
void fn_80253EB8(VSHud*, float);
void ItemSelect_AddSlotItem(VSItems*, int, int);
unsigned char ItemSelect_GetSlotItemId(VSItems*, int);
void SetCourseScene3D(VSScene*);
void HUD_SetTotalLaps(VSHud*, int);
void CourseBgm_Load();
void PreloadEffectResources(int);
void PreloadItemResources(int);
int fn_8023DBEC(int);
void PreloadResource(int);
void* GetEnemyParam();
void clEnemyParam_FillItemListIds(void*, int, int, int);
int* AI_GetItemList(void*, int, int, int, int);
unsigned long long OSGetTime();
void VoiceSystem_SetCheckpointsForTotalLaps(int);

#pragma use_lmw_stmw on
void VSMode_Init(void* self_)
{
    VSOwner* self = (VSOwner*)self_;
    char* pool = (char*)lbl_80320960;
    ProcessSystemTick(pool + 0x588);
    HSD_RandSeedPtr = &lbl_806D12F0;
    *HSD_RandSeedPtr = SyncSlot_GetRecv()[0x1B];
    lbl_806D129C = 0;
    SetResourceLoadingFlag(0);
    DMAChannelManager_Init();
    TransitionEffect_GetOrCreate();
    ProcessSystemTick(pool + 0x59C);
    self->input = new VSInput;
    ProcessSystemTick(pool + 0x5B8);
    CourseData_GetOrCreate(g_cupId, g_longRoundFlag, g_reverseRoundFlag);
    lbl_806D12F8 = HSD_LObjLoadDesc(GetCourseDataPtr());
    self->camera = new VSCamera(0x100, 0x100, lbl_806D12F8, lbl_806D47AC, lbl_806D47A8);
    SetActiveCamera(0, self->camera);
    g_raceCamera = self->camera;
    ProcessSystemTick(pool + 0x5C4);
    SoundChannels_ClearAll();
    ItemObjectManager_Init();
    CourseObjectManager_Init();
    ProcessSystemTick(pool + 0x5D0);
    RankingTable_Init(GetRaceContextPtr());
    SoundDriver_GetOrCreate(GetCourseBgmEntry());
    CoinSystem_Init(0, 2);

    VSPeer* table = lbl_805A6154;
    lbl_806D12FC = 0;
    lbl_806CF140 = (signed char)lbl_80598A60[0x21] - 1;
    lbl_806CF144 = g_localPcbRole - 2;
    int peers = 0;
    int i;
    int slot;
    for (i = 0; i < 4; ++i)
        if (table[i].teamId ==
            table[lbl_806CF140].teamId)
            ++peers;
    if (peers == 4 && g_isCommHost == 1)
        TitleTracker_OnRaceStart_Stub(lbl_806D10A0 == 0 ? 0 : lbl_806D10A0);
    ProcessSystemTick(pool + 0x5F4);
    DebugPrintf(pool + 0x608, lbl_806CF140, lbl_806CF144, peers);
    unsigned char* packet = SyncSlot_GetRecv();
    int cpus = 4 - peers;
    for (i = 0; i < cpus; ++i)
        RaceSlot_InitSlot(i, 6, (signed char)packet[i + 0x15], 1, 0);
    for (i = 0; i < 4; ++i)
        if (table[i].teamId ==
            table[lbl_806CF140].teamId && i == lbl_806CF140)
            lbl_806D12EC = (signed char)packet[i + 9];
    g_kartStartSlot = lbl_806D12EC;
    ProcessSystemTick(pool + 0x62C);

    for (i = 0; i < 4; ++i) {
        VSPeer* peer = &table[i];
        if (peer->teamId == table[lbl_806CF140].teamId) {
            int lap = (signed char)packet[i + 0x11];
            slot = (signed char)packet[i + 9];
            int cameraPeer = -1;
            unsigned char human = 0;
            if (i == lbl_806CF140) human = 1;
            if ((peer->cameraFlags >> 5) & 1) cameraPeer = i;
            lbl_806D1050 = lap;
            RaceSlot_InitSlot(slot, i, peer->charId, 1, 0);
            DebugPrintf(pool + 0x638, i, slot, i, peer->charId);
            float x, z;
            GetStartPosition(slot, &x, 0, &z);
            int cc;
            g_carObjects[i] = new VSCar(i, GetKartSlotCharId(slot), (cc = g_ccClass, cc),
                (peer->tuning >> 1) & 3, human, -1, 1, 0, x, z, GetCourseStartYaw());
            KartItem_SetShortArray34a(CarObject_GetRenderObj(g_carObjects[i]), peer->shorts16);
            if (g_namCamFlag)
                KartItem_SetField358(CarObject_GetRenderObj(g_carObjects[i]), cameraPeer);
            VoiceSystem_BindKartCarObject(slot, g_carObjects[i]);
        } else {
            g_carObjects[i] = 0;
        }
    }
    ProcessSystemTick(pool + 0x65C);
    g_playerRenderObj = CarObject_GetRenderObj(g_carObjects[lbl_806CF140]);
    SetPlayerCarObject(g_carObjects[lbl_806CF140]);
    *(int*)((unsigned char*)g_playerRenderObj + 0x238) = 1;

    for (i = 0; i < 4; ++i) {
        if (g_carObjects[i]) {
            float* matrix = CarObject_GetTransformMatrix(g_carObjects[i]);
            if (!lbl_806D12F4) {
                lbl_806D12F4 = new VSPath(CourseData_GetDefaultPathKey_Safe(),
                    g_carObjects[i], CarObject_GetRenderObj(g_carObjects[i]),
                    matrix + 12, matrix + 13, matrix + 14);
                lbl_805D2B00[i] = 0;
            } else {
                lbl_805D2B00[i] = PathManager_RegisterCarObject(lbl_806D12F4,
                    matrix + 12, matrix + 13, matrix + 14, g_carObjects[i],
                    CarObject_GetRenderObj(g_carObjects[i]), -1);
            }
        }
    }
    ProcessSystemTick(pool + 0x66C);
    if (SyncSlot_GetHostSend())
        ((VSHostFlags*)(SyncSlot_GetHostSend() + 2))->ready = 0;
    self->lakitu = new VSLakitu(pool + 0x684, lbl_806D12EC,
        lbl_806D47A4, lbl_806D47A4, lbl_806D47A4);
    LakituStart_SetCountdownHoldFrames(self->lakitu, 0x4E20);
    self->scene = new VSScene(*GetKartModelNameEntry(GetKartSlotCharId(lbl_806D12EC), -1));
    self->flag = new VSFlag(self->scene);
    self->reverse = new VSReverse(g_playerRenderObj);
    self->finalLap = new VSFinalLap(g_playerRenderObj);
    float projectionX, projectionZ;
    Scene3D_GetCameraPos(self->scene, &projectionX, &projectionZ);
    projectionX += lbl_806D47D0;
    Scene3D_SetupProjection(self->scene, projectionX, projectionZ);
    CObj_UpdatePerspParam(self->scene, RaceScene_GetPerspFovyForCup());
    ProcessSystemTick(pool + 0x698);
    self->collision = new VSCollision;
    g_objCollChecker = self->collision;
    self->ai = new VSAI(lbl_806D12F4, self->collision, 0);
    ProcessSystemTick(pool + 0x6AC);
    g_sceneTransitionTimer = -1;
    if (g_isCommHost)
        for (int i = 0; i < 4; ++i) CommBroadcast_SetKartRankNibble(i, i);
    ProcessSystemTick(pool + 0x6C8);
    Tachometer_Init();
    HitMessageOverlay_Init();
    self->hud = new VSHud(lbl_806D12F4);
    g_raceHud = self->hud;
    HUD_RegisterOverlay(self->hud, 6, 0);
    HUD_RegisterOverlay(self->hud, 3, 0);
    HUD_RegisterOverlay(self->hud, 5, 0);
    HUD_RegisterOverlay(self->hud, 1, 0);
    HUD_RegisterOverlay(self->hud, 2, 0);
    HUD_RegisterOverlay(self->hud, 10, 0);
    HUD_RegisterOverlay(self->hud, 12, 0);
    HUD_RegisterOverlay(self->hud, 11, 0);
    HUD_RegisterOverlay(self->hud, 7, 0);
    HUD_RegisterOverlay(self->hud, 0, 0);
    HUD_RegisterOverlay(self->hud, 15, 0);
    HUD_RegisterOverlay(self->hud, 16, 0);
    HUD_RegisterOverlay(self->hud, 14, 0);
    if (IsTimerModeEnabled() == 1) HUD_RegisterOverlay(self->hud, 4, 0);
    HUD_RegisterOverlay(self->hud, 13, 0);
    fn_80253EB8(self->hud, lbl_806D47C0);
    HUD_RegisterOverlay(self->hud, 8, 0);
    HUD_RegisterOverlay(self->hud, 9, 0);
    HUD_RegisterOverlay(self->hud, 21, 0);
    HUD_RegisterOverlay(self->hud, 22, 0);
    ProcessSystemTick(pool + 0x6D4);

    for (int i = 0; i < 4; ++i) {
        VSPeer* peer = &table[i];
        if (i == lbl_806CF140 ||
            peer->teamId == table[lbl_806CF140].teamId) {
            slot = (signed char)packet[i + 9];
            if (i == lbl_806CF140) g_itemSelects[i] = new VSItems(slot, 1);
            else g_itemSelects[i] = new VSItems(slot, 0);
            g_carObjects[i]->itemSelect = g_itemSelects[i];
            VSItems* select = g_itemSelects[i];
            *(VSItems**)((unsigned char*)CarObject_GetRenderObj(g_carObjects[i]) + 0x364) = select;
            if (lbl_806CF110 == 1) {
                ItemSelect_AddSlotItem(g_itemSelects[i], peer->items[0], 1);
                ItemSelect_AddSlotItem(g_itemSelects[i], peer->items[1], 1);
                ItemSelect_AddSlotItem(g_itemSelects[i], peer->items[2], 1);
                if (i == lbl_806CF140) {
                    lbl_806D1264[0] = peer->items[0];
                    lbl_806D1264[1] = peer->items[1];
                    lbl_806D1264[2] = peer->items[2];
                }
            } else {
                ItemSelect_AddSlotItem(g_itemSelects[i], peer->items[0], 1);
                ItemSelect_AddSlotItem(g_itemSelects[i], 0x3D, 1);
                ItemSelect_AddSlotItem(g_itemSelects[i], 0x2B, 1);
                ItemSelect_AddSlotItem(g_itemSelects[i], 0x17, 1);
                ItemSelect_AddSlotItem(g_itemSelects[i], 0x32, 1);
            }
        } else {
            g_itemSelects[i] = 0;
        }
    }
    ProcessSystemTick(pool + 0x6E8);
    g_lakituStartAnimDone = 0;
    SetCourseScene3D(self->scene);
    VSRaceRow (*row)[3][2] = (VSRaceRow (*)[3][2])VS_MODE + g_cupId;
    g_raceEnded = 0;
    g_finalRacePosition = 0;
    g_bestLapTime = lbl_806D47A4;
    g_currentLapTime = lbl_806D47A4;
    g_totalRaceTime = lbl_806D47A4;
    g_currentLap = 1;
    g_raceResultCode = -2;
    g_finalLapBannerShown = 0;
    g_lapChangePending = 0;
    lbl_806D1304 = 0;
    lbl_806D1308 = 0;
    lbl_806CF148 = 1;
    lbl_806D12E8 = 0;
    lbl_806D1300 = 0;
    g_totalLaps = row[-1][g_ccClass][g_longRoundFlag].laps;
    g_raceTimeRemaining = row[-1][g_ccClass][g_longRoundFlag].remaining;
    g_lapBonusTimeDelta = row[-1][g_ccClass][g_longRoundFlag].bonus;
    ProcessSystemTick(pool + 0x6F8);
    HUD_SetTotalLaps(self->hud, g_totalLaps);
    CourseBgm_Load();
    if (!g_weatherSystem) g_weatherSystem = new VSWeather(1);
    SetResourceLoadingFlag(1);
    lbl_806D129C = 1;
    g_raceFrameCounterLo2digits = 0;
    switch (g_cupId) {
    case 1: PreloadEffectResources(1); break;
    case 2: PreloadEffectResources(2); break;
    case 3: PreloadEffectResources(3); break;
    case 4: PreloadEffectResources(4); break;
    case 5: PreloadEffectResources(5); break;
    case 6: PreloadEffectResources(6); break;
    case 7: PreloadEffectResources(7); break;
    case 8: PreloadEffectResources(8); break;
    default: break;
    }
    ProcessSystemTick(pool + 0x70C);
    PreloadEffectResources(9);
    ProcessSystemTick(pool + 0x72C);
    PreloadEffectResources(10);
    ProcessSystemTick(pool + 0x74C);
    for (int i = 0; i < 4; ++i) {
        if (g_itemSelects[i])
            for (int slot = 0; slot < (lbl_806CF110 == 1 ? 3 : 5); ++slot) {
                unsigned char item = ItemSelect_GetSlotItemId(g_itemSelects[i], slot);
                if (item) {
                    PreloadItemResources(item);
                    PreloadResource(fn_8023DBEC(item));
                }
            }
    }
    ProcessSystemTick(pool + 0x76C);
    {
        int round = g_roundIndex, cup = g_cupId, mode = g_gameMode;
        clEnemyParam_FillItemListIds(GetEnemyParam(), mode, cup, round);
    }
    for (i = 0; i < 4; ++i) {
        int round = g_roundIndex, cup = g_cupId, mode = g_gameMode;
        int* list = AI_GetItemList(GetEnemyParam(), mode, cup, round, i);
        while (*list != -1) {
            PreloadItemResources(*list);
            PreloadResource(fn_8023DBEC(*list));
            ++list;
        }
    }
    ProcessSystemTick(pool + 0x788);
    lbl_806D1318 = 0;
    lbl_806D1319 = 1;
    unsigned long long time = OSGetTime();
    for (i = 0; i < 4; ++i) {
        lbl_806D131C[i] = 0;
        lbl_805D2AA8[i] = time;
    }
    ProcessSystemTick(pool + 0x7A4);
    g_humanPlayerCount = *(int*)(SyncSlot_GetRecv() + 4);
    self->finalObject = new VSFinalObject(0x168);
    VoiceSystem_SetCheckpointsForTotalLaps(g_totalLaps);
    g_raceRankingPathObject = lbl_806D12F4;
}
#pragma use_lmw_stmw reset
}
#pragma cplusplus off
#else

/* === extracted from auto_VSMode_Init_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void AI_GetItemList();
extern void AI_SystemInit();
extern void Alloc();
extern void CObj_UpdatePerspParam();
extern void Camera_Create();
extern void CarObject_GetRenderObj();
extern void CarObject_GetTransformMatrix();
extern void CarObject_Init();
extern void CoinSystem_Init();
extern void CommBroadcast_SetKartRankNibble();
extern void CourseBgm_Load();
extern void CourseData_GetDefaultPathKey_Safe();
extern void CourseData_GetOrCreate();
extern void CourseObjectManager_Init();
extern void DMAChannelManager_Init();
extern void DebugPrintf();
extern void FinalLapBanner_Init();
extern void GetCourseBgmEntry();
extern void GetCourseDataPtr();
extern void GetCourseStartYaw();
extern void GetEnemyParam();
extern void GetKartModelNameEntry();
extern void GetKartSlotCharId();
extern void GetRaceContextPtr();
extern void GetStartPosition();
extern void HUD_Init();
extern void HUD_RegisterOverlay();
extern void HUD_SetTotalLaps();
extern void HitMessageOverlay_Init();
extern void InputManager_Init();
extern void IsTimerModeEnabled();
extern void ItemObjectManager_Init();
extern void ItemSelect_AddSlotItem();
extern void ItemSelect_GetSlotItemId();
extern void ItemSelect_Init();
extern void Jyugemu_Flag_Ctor();
extern void Jyugemu_ReverseFlag_Ctor();
extern void KartItem_SetField358();
extern void KartItem_SetShortArray34a();
extern void LakituStart_Init();
extern void LakituStart_SetCountdownHoldFrames();
extern void OSGetTime();
extern void PathManager_Init();
extern void PathManager_RegisterCarObject();
extern void PreloadEffectResources();
extern void PreloadItemResources();
extern void PreloadResource();
extern void ProcessSystemTick();
extern void RaceScene_GetPerspFovyForCup();
extern void RaceSlot_InitSlot();
extern void RankingTable_Init();
extern void HSD_LObjLoadDesc();
extern void Scene3D_GetCameraPos();
extern void Scene3D_Init();
extern void Scene3D_SetupProjection();
extern void SetActiveCamera();
extern void SetCourseScene3D();
extern void SetPlayerCarObject();
extern void SetResourceLoadingFlag();
extern void SoundChannels_ClearAll();
extern void SoundDriver_GetOrCreate();
extern void SyncSlot_GetHostSend();
extern void SyncSlot_GetRecv();
extern void Tachometer_Init();
extern void TitleTracker_OnRaceStart_Stub();
extern void TransitionEffect_GetOrCreate();
extern void VoiceSystem_BindKartCarObject();
extern void VoiceSystem_SetCheckpointsForTotalLaps();
extern void WeatherSystem_Init();
extern void clEnemyParam_FillItemListIds();
extern void fn_802090A8();
extern void fn_8020B234();
extern void fn_8023DBEC();
extern void fn_80253EB8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_bestLapTime;
extern unsigned int g_ccClass;
extern unsigned int g_cupId;
extern unsigned int g_currentLap;
extern unsigned int g_currentLapTime;
extern unsigned int g_finalLapBannerShown;
extern unsigned int g_finalRacePosition;
extern unsigned int g_gameMode;
extern unsigned int g_humanPlayerCount;
extern unsigned int g_isCommHost;
extern unsigned int g_kartStartSlot;
extern unsigned int g_lakituStartAnimDone;
extern unsigned int g_lapBonusTimeDelta;
extern unsigned int g_lapChangePending;
extern unsigned int g_localPcbRole;
extern unsigned int g_longRoundFlag;
extern unsigned int g_namCamFlag;
extern unsigned int g_objCollChecker;
extern unsigned int g_playerRenderObj;
extern unsigned int g_raceCamera;
extern unsigned int g_raceEnded;
extern unsigned int g_raceFrameCounterLo2digits;
extern unsigned int g_raceHud;
extern unsigned int g_raceRankingPathObject;
extern unsigned int g_raceResultCode;
extern unsigned int g_raceTimeRemaining;
extern unsigned int g_reverseRoundFlag;
extern unsigned int g_roundIndex;
extern unsigned int g_sceneTransitionTimer;
extern unsigned int g_totalLaps;
extern unsigned int g_totalRaceTime;
extern unsigned int g_weatherSystem;
extern unsigned int lbl_806CF110;
extern unsigned int lbl_806CF140;
extern unsigned int lbl_806CF144;
extern unsigned int lbl_806CF148;
extern unsigned int HSD_RandSeedPtr;
extern unsigned int lbl_806D1050;
extern unsigned int lbl_806D10A0;
extern unsigned int lbl_806D1264;
extern unsigned int lbl_806D129C;
extern unsigned int lbl_806D12E8;
extern unsigned int lbl_806D12EC;
extern unsigned int lbl_806D12F0;
extern unsigned int lbl_806D12F4;
extern unsigned int lbl_806D12F8;
extern unsigned int lbl_806D12FC;
extern unsigned int lbl_806D1300;
extern unsigned int lbl_806D1304;
extern unsigned int lbl_806D1308;
extern unsigned int lbl_806D1318;
extern unsigned int lbl_806D1319;
extern unsigned int lbl_806D131C;
extern unsigned int lbl_806D47A4;
extern unsigned int lbl_806D47A8;
extern unsigned int lbl_806D47AC;
extern unsigned int lbl_806D47C0;
extern unsigned int lbl_806D47D0;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int VS_MODE[];
extern unsigned int g_carObjects[];
extern unsigned int g_itemSelects[];
extern unsigned int jumptable_8040E748[];

extern unsigned int lbl_80598A60[];
extern unsigned int lbl_805A6154[];
extern unsigned int lbl_805D2AA8[];
extern unsigned int lbl_805D2B00[];

/* --- function index (1 fns, .text 0x8009F814..0x800A05D0) ---
 * [  0] 0x8009F814 size:0xDBC   global VSMode_Init
 */

/* --- forward decls --- */
asm void VSMode_Init(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; unsigned int f29; unsigned int f30; unsigned int f31; unsigned int f32; unsigned int f33; unsigned int f34; void *f35; unsigned int f36; void *f37; unsigned int f38; void *f39; unsigned int f40; void *f41; unsigned int f42; void *f43; unsigned int f44; void *f45; unsigned int f46; void *f47; unsigned int f48; void *f49; unsigned int f50; void *f51; unsigned int f52; void *f53; unsigned int f54; void *f55; unsigned int f56; void *f57; unsigned int f58; void *f59; unsigned int f60; void *f61; unsigned int f62; void *f63; unsigned int f64; void *f65; } extab_VSMode_Init = { 0x684A0000, 0x00000078, 0x00000088, 0x000000C8, 0x00000090, 0x00000408, 0x00120098, 0x0000053C, 0x000A00A0, 0x00000604, 0x000000A8, 0x0000062C, 0x000600B0, 0x00000660, 0x000000B8, 0x0000067C, 0x000000C0, 0x00000698, 0x000000C8, 0x000006F0, 0x000000D0, 0x0000071C, 0x000000D8, 0x00000780, 0x000000E0, 0x0000094C, 0x000000E8, 0x00000970, 0x000000F0, 0x00000B4C, 0x000000F8, 0x00000D8C, 0x00000100, 0x00000000, 0x8A800014, (void *)&MemoryManager_TimedFree, 0x8A800014, (void *)&MemoryManager_TimedFree, 0x8A800013, (void *)&MemoryManager_TimedFree, 0x8A800013, (void *)&MemoryManager_TimedFree, 0x8A800013, (void *)&MemoryManager_TimedFree, 0x8A800013, (void *)&MemoryManager_TimedFree, 0x8A800013, (void *)&MemoryManager_TimedFree, 0x8A800013, (void *)&MemoryManager_TimedFree, 0x8A800013, (void *)&MemoryManager_TimedFree, 0x8A800013, (void *)&MemoryManager_TimedFree, 0x8A800013, (void *)&MemoryManager_TimedFree, 0x8A800013, (void *)&MemoryManager_TimedFree, 0x8A800013, (void *)&MemoryManager_TimedFree, 0x8A800013, (void *)&MemoryManager_TimedFree, 0x8A800013, (void *)&MemoryManager_TimedFree, 0x8A800013, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_VSMode_Init = {
    (void *)&VSMode_Init, 0x00000DBC, (void *)&extab_VSMode_Init
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void VSMode_Init(void) { /* 0x8009F814 size:0xDBC */
    nofralloc
    stwu r1, -0x70(r1)
    mflr r0
    stw r0, 0x74(r1)
    stfd f31, 0x60(r1)
    psq_st f31, 0x68(r1), 0, 0
    stmw r19, 0x2c(r1)
    lis r4, lbl_80320960@ha
    mr r29, r3
    addi r27, r4, lbl_80320960@l
    addi r3, r27, 0x588
    bl ProcessSystemTick
    la r0, lbl_806D12F0(r13)
    stw r0, HSD_RandSeedPtr(r13)
    bl SyncSlot_GetRecv
    lbz r5, 0x1b(r3)
    li r0, 0x0
    lwz r4, HSD_RandSeedPtr(r13)
    li r3, 0x0
    stw r5, 0x0(r4)
    stw r0, lbl_806D129C(r13)
    bl SetResourceLoadingFlag
    bl DMAChannelManager_Init
    bl TransitionEffect_GetOrCreate
    addi r3, r27, 0x59c
    bl ProcessSystemTick
    li r3, 0x37c
    bl Alloc
    mr. r20, r3
    beq VSMode_Init_L_8009F88C
    bl InputManager_Init
    VSMode_Init_L_8009F88C:
    stw r20, 0x14(r29)
    addi r3, r27, 0x5b8
    bl ProcessSystemTick
    lwz r3, g_cupId(r13)
    lwz r4, g_longRoundFlag(r13)
    lwz r5, g_reverseRoundFlag(r13)
    bl CourseData_GetOrCreate
    bl GetCourseDataPtr
    bl HSD_LObjLoadDesc
    stw r3, lbl_806D12F8(r13)
    li r3, 0x2c
    bl Alloc
    mr. r20, r3
    beq VSMode_Init_L_8009F8DC
    lfs f1, lbl_806D47AC(r2)
    li r4, 0x100
    lfs f2, lbl_806D47A8(r2)
    li r5, 0x100
    lwz r6, lbl_806D12F8(r13)
    bl Camera_Create
    VSMode_Init_L_8009F8DC:
    stw r20, 0x20(r29)
    li r3, 0x0
    lwz r4, 0x20(r29)
    bl SetActiveCamera
    lwz r0, 0x20(r29)
    addi r3, r27, 0x5c4
    stw r0, g_raceCamera(r13)
    bl ProcessSystemTick
    bl SoundChannels_ClearAll
    bl ItemObjectManager_Init
    bl CourseObjectManager_Init
    addi r3, r27, 0x5d0
    bl ProcessSystemTick
    bl GetRaceContextPtr
    bl RankingTable_Init
    bl GetCourseBgmEntry
    bl SoundDriver_GetOrCreate
    li r3, 0x0
    li r4, 0x2
    bl CoinSystem_Init
    lis r3, lbl_80598A60@ha
    lis r5, lbl_805A6154@ha
    addi r3, r3, lbl_80598A60@l
    lwz r4, g_localPcbRole(r13)
    lbz r0, 0x21(r3)
    addi r7, r5, lbl_805A6154@l
    lbz r3, 0x0(r7)
    subi r5, r4, 0x2
    extsb r4, r0
    li r6, 0x0
    subi r0, r4, 0x1
    extrwi r3, r3, 3, 25
    mulli r4, r0, 0xa3c
    stw r6, lbl_806D12FC(r13)
    mr r30, r7
    stw r0, lbl_806CF140(r13)
    li r20, 0x0
    lbzx r0, r7, r4
    stw r5, lbl_806CF144(r13)
    extrwi r0, r0, 3, 25
    cmplw r3, r0
    bne VSMode_Init_L_8009F988
    li r20, 0x1
    VSMode_Init_L_8009F988:
    addi r5, r7, 0xa3c
    lbzx r0, r7, r4
    lbz r3, 0xa3c(r7)
    extrwi r0, r0, 3, 25
    extrwi r3, r3, 3, 25
    cmplw r3, r0
    bne VSMode_Init_L_8009F9A8
    addi r20, r20, 0x1
    VSMode_Init_L_8009F9A8:
    lbzx r0, r7, r4
    lbzu r3, 0xa3c(r5)
    extrwi r0, r0, 3, 25
    extrwi r3, r3, 3, 25
    cmplw r3, r0
    bne VSMode_Init_L_8009F9C4
    addi r20, r20, 0x1
    VSMode_Init_L_8009F9C4:
    lbzx r0, r7, r4
    lbz r3, 0xa3c(r5)
    extrwi r0, r0, 3, 25
    extrwi r3, r3, 3, 25
    cmplw r3, r0
    bne VSMode_Init_L_8009F9E0
    addi r20, r20, 0x1
    VSMode_Init_L_8009F9E0:
    cmpwi r20, 0x4
    bne VSMode_Init_L_8009FA08
    lbz r0, g_isCommHost(r13)
    cmplwi r0, 0x1
    bne VSMode_Init_L_8009FA08
    lwz r3, lbl_806D10A0(r13)
    cmplwi r3, 0x0
    bne VSMode_Init_L_8009FA04
    li r3, 0x0
    VSMode_Init_L_8009FA04:
    bl TitleTracker_OnRaceStart_Stub
    VSMode_Init_L_8009FA08:
    addi r3, r27, 0x5f4
    bl ProcessSystemTick
    lwz r4, lbl_806CF140(r13)
    mr r6, r20
    lwz r5, lbl_806CF144(r13)
    addi r3, r27, 0x608
    crxor 6, 6, 6
    bl DebugPrintf
    bl SyncSlot_GetRecv
    mr r31, r3
    subfic r20, r20, 0x4
    li r21, 0x0
    b VSMode_Init_L_8009FA60
    VSMode_Init_L_8009FA3C:
    addi r0, r21, 0x15
    mr r3, r21
    lbzx r5, r31, r0
    li r4, 0x6
    li r6, 0x1
    li r7, 0x0
    extsb r5, r5
    bl RaceSlot_InitSlot
    addi r21, r21, 0x1
    VSMode_Init_L_8009FA60:
    cmpw r21, r20
    blt VSMode_Init_L_8009FA3C
    lwz r6, lbl_806CF140(r13)
    li r7, 0x0
    lbz r3, 0x0(r30)
    mulli r4, r6, 0xa3c
    extrwi r3, r3, 3, 25
    lbzx r0, r30, r4
    extrwi r0, r0, 3, 25
    cmplw r3, r0
    bne VSMode_Init_L_8009FAA0
    cmpw r7, r6
    bne VSMode_Init_L_8009FAA0
    lbz r0, 0x9(r31)
    extsb r0, r0
    stw r0, lbl_806D12EC(r13)
    VSMode_Init_L_8009FAA0:
    addi r5, r30, 0xa3c
    lbzx r0, r30, r4
    lbz r3, 0xa3c(r30)
    li r7, 0x1
    extrwi r0, r0, 3, 25
    extrwi r3, r3, 3, 25
    cmplw r3, r0
    bne VSMode_Init_L_8009FAD4
    cmpw r7, r6
    bne VSMode_Init_L_8009FAD4
    lbz r0, 0xa(r31)
    extsb r0, r0
    stw r0, lbl_806D12EC(r13)
    VSMode_Init_L_8009FAD4:
    lbzx r0, r30, r4
    li r7, 0x2
    lbzu r3, 0xa3c(r5)
    extrwi r0, r0, 3, 25
    extrwi r3, r3, 3, 25
    cmplw r3, r0
    bne VSMode_Init_L_8009FB04
    cmpw r7, r6
    bne VSMode_Init_L_8009FB04
    lbz r0, 0xb(r31)
    extsb r0, r0
    stw r0, lbl_806D12EC(r13)
    VSMode_Init_L_8009FB04:
    lbzx r0, r30, r4
    li r7, 0x3
    lbz r3, 0xa3c(r5)
    extrwi r0, r0, 3, 25
    extrwi r3, r3, 3, 25
    cmplw r3, r0
    bne VSMode_Init_L_8009FB34
    cmpw r7, r6
    bne VSMode_Init_L_8009FB34
    lbz r0, 0xc(r31)
    extsb r0, r0
    stw r0, lbl_806D12EC(r13)
    VSMode_Init_L_8009FB34:
    lwz r0, lbl_806D12EC(r13)
    addi r3, r27, 0x62c
    stw r0, g_kartStartSlot(r13)
    bl ProcessSystemTick
    lis r3, g_carObjects@ha
    mr r26, r30
    addi r28, r3, g_carObjects@l
    li r23, 0x0
    mr r25, r28
    VSMode_Init_L_8009FB58:
    lwz r4, lbl_806CF140(r13)
    lbz r3, 0x0(r26)
    mulli r0, r4, 0xa3c
    extrwi r3, r3, 3, 25
    lbzx r0, r30, r0
    extrwi r0, r0, 3, 25
    cmplw r3, r0
    bne VSMode_Init_L_8009FCA4
    add r3, r31, r23
    cmpw r23, r4
    lbz r21, 0x9(r3)
    li r24, 0x0
    lbz r4, 0x11(r3)
    li r22, -0x1
    extsb r21, r21
    extsb r4, r4
    bne VSMode_Init_L_8009FBA0
    li r24, 0x1
    VSMode_Init_L_8009FBA0:
    lbz r0, 0x3(r26)
    extrwi. r0, r0, 1, 26
    beq VSMode_Init_L_8009FBB0
    mr r22, r23
    VSMode_Init_L_8009FBB0:
    lbz r0, 0x4(r26)
    mr r3, r21
    stw r4, lbl_806D1050(r13)
    mr r4, r23
    extrwi r5, r0, 4, 24
    li r6, 0x1
    li r7, 0x0
    bl RaceSlot_InitSlot
    lbz r0, 0x4(r26)
    mr r4, r23
    mr r5, r21
    mr r6, r23
    addi r3, r27, 0x638
    extrwi r7, r0, 4, 24
    crxor 6, 6, 6
    bl DebugPrintf
    mr r3, r21
    addi r4, r1, 0x1c
    addi r6, r1, 0x18
    li r5, 0x0
    bl GetStartPosition
    li r3, 0x118
    bl Alloc
    mr. r19, r3
    beq VSMode_Init_L_8009FC64
    lwz r20, g_ccClass(r13)
    bl GetCourseStartYaw
    fmr f31, f1
    mr r3, r21
    bl GetKartSlotCharId
    li r0, 0x0
    mr r5, r3
    stw r0, 0x8(r1)
    fmr f3, f31
    mr r3, r19
    mr r4, r23
    lbz r0, 0x6(r26)
    mr r6, r20
    lfs f1, 0x1c(r1)
    lfs f2, 0x18(r1)
    mr r8, r24
    extrwi r7, r0, 2, 29
    li r9, -0x1
    li r10, 0x1
    bl CarObject_Init
    VSMode_Init_L_8009FC64:
    stw r19, 0x0(r25)
    lwz r3, 0x0(r25)
    bl CarObject_GetRenderObj
    addi r4, r26, 0x16
    bl KartItem_SetShortArray34a
    lbz r0, g_namCamFlag(r13)
    cmplwi r0, 0x0
    beq VSMode_Init_L_8009FC94
    lwz r3, 0x0(r25)
    bl CarObject_GetRenderObj
    mr r4, r22
    bl KartItem_SetField358
    VSMode_Init_L_8009FC94:
    lwz r4, 0x0(r25)
    mr r3, r21
    bl VoiceSystem_BindKartCarObject
    b VSMode_Init_L_8009FCAC
    VSMode_Init_L_8009FCA4:
    li r0, 0x0
    stw r0, 0x0(r25)
    VSMode_Init_L_8009FCAC:
    addi r23, r23, 0x1
    addi r25, r25, 0x4
    cmpwi r23, 0x4
    addi r26, r26, 0xa3c
    blt VSMode_Init_L_8009FB58
    addi r3, r27, 0x65c
    bl ProcessSystemTick
    lwz r0, lbl_806CF140(r13)
    lis r3, g_carObjects@ha
    addi r3, r3, g_carObjects@l
    slwi r0, r0, 2
    lwzx r3, r3, r0
    bl CarObject_GetRenderObj
    lwz r0, lbl_806CF140(r13)
    lis r4, g_carObjects@ha
    addi r4, r4, g_carObjects@l
    stw r3, g_playerRenderObj(r13)
    slwi r0, r0, 2
    lwzx r3, r4, r0
    bl SetPlayerCarObject
    lwz r4, g_playerRenderObj(r13)
    li r0, 0x1
    lis r3, lbl_805D2B00@ha
    mr r25, r28
    stw r0, 0x238(r4)
    addi r20, r3, lbl_805D2B00@l
    li r23, 0x0
    VSMode_Init_L_8009FD18:
    lwz r3, 0x0(r25)
    cmplwi r3, 0x0
    beq VSMode_Init_L_8009FDB4
    bl CarObject_GetTransformMatrix
    lwz r0, lbl_806D12F4(r13)
    mr r22, r3
    cmplwi r0, 0x0
    bne VSMode_Init_L_8009FD88
    li r3, 0x4e8
    bl Alloc
    mr. r19, r3
    beq VSMode_Init_L_8009FD78
    lwz r3, 0x0(r25)
    bl CarObject_GetRenderObj
    mr r21, r3
    bl CourseData_GetDefaultPathKey_Safe
    lwz r5, 0x0(r25)
    mr r4, r3
    mr r3, r19
    mr r6, r21
    addi r7, r22, 0x30
    addi r8, r22, 0x34
    addi r9, r22, 0x38
    bl PathManager_Init
    VSMode_Init_L_8009FD78:
    li r0, 0x0
    stw r19, lbl_806D12F4(r13)
    stw r0, 0x0(r20)
    b VSMode_Init_L_8009FDB4
    VSMode_Init_L_8009FD88:
    lwz r3, 0x0(r25)
    bl CarObject_GetRenderObj
    mr r8, r3
    lwz r3, lbl_806D12F4(r13)
    lwz r7, 0x0(r25)
    addi r4, r22, 0x30
    addi r5, r22, 0x34
    addi r6, r22, 0x38
    li r9, -0x1
    bl PathManager_RegisterCarObject
    stw r3, 0x0(r20)
    VSMode_Init_L_8009FDB4:
    addi r23, r23, 0x1
    addi r20, r20, 0x4
    cmpwi r23, 0x4
    addi r25, r25, 0x4
    blt VSMode_Init_L_8009FD18
    addi r3, r27, 0x66c
    bl ProcessSystemTick
    bl SyncSlot_GetHostSend
    cmplwi r3, 0x0
    beq VSMode_Init_L_8009FDF0
    li r21, 0x0
    bl SyncSlot_GetHostSend
    lbz r0, 0x2(r3)
    rlwimi r0, r21, 7, 24, 24
    stb r0, 0x2(r3)
    VSMode_Init_L_8009FDF0:
    li r3, 0x58
    bl Alloc
    mr. r19, r3
    beq VSMode_Init_L_8009FE18
    lfs f1, lbl_806D47A4(r2)
    addi r4, r27, 0x684
    lwz r5, lbl_806D12EC(r13)
    fmr f2, f1
    fmr f3, f1
    bl LakituStart_Init
    VSMode_Init_L_8009FE18:
    stw r19, 0x4(r29)
    li r4, 0x4e20
    lwz r3, 0x4(r29)
    bl LakituStart_SetCountdownHoldFrames
    li r3, 0x3084
    bl Alloc
    mr. r19, r3
    beq VSMode_Init_L_8009FE58
    lwz r3, lbl_806D12EC(r13)
    bl GetKartSlotCharId
    li r4, -0x1
    bl GetKartModelNameEntry
    mr r4, r3
    mr r3, r19
    lwz r4, 0x0(r4)
    bl Scene3D_Init
    VSMode_Init_L_8009FE58:
    stw r19, 0x18(r29)
    li r3, 0xc
    bl Alloc
    mr. r19, r3
    beq VSMode_Init_L_8009FE74
    lwz r4, 0x18(r29)
    bl Jyugemu_Flag_Ctor
    VSMode_Init_L_8009FE74:
    stw r19, 0x8(r29)
    li r3, 0x14
    bl Alloc
    mr. r19, r3
    beq VSMode_Init_L_8009FE90
    lwz r4, g_playerRenderObj(r13)
    bl Jyugemu_ReverseFlag_Ctor
    VSMode_Init_L_8009FE90:
    stw r19, 0xc(r29)
    li r3, 0x10
    bl Alloc
    mr. r19, r3
    beq VSMode_Init_L_8009FEAC
    lwz r4, g_playerRenderObj(r13)
    bl FinalLapBanner_Init
    VSMode_Init_L_8009FEAC:
    stw r19, 0x10(r29)
    addi r4, r1, 0x14
    addi r5, r1, 0x10
    lwz r3, 0x18(r29)
    bl Scene3D_GetCameraPos
    lfs f1, 0x14(r1)
    lfs f0, lbl_806D47D0(r2)
    lfs f2, 0x10(r1)
    fadds f1, f1, f0
    stfs f1, 0x14(r1)
    lwz r3, 0x18(r29)
    bl Scene3D_SetupProjection
    bl RaceScene_GetPerspFovyForCup
    lwz r3, 0x18(r29)
    bl CObj_UpdatePerspParam
    addi r3, r27, 0x698
    bl ProcessSystemTick
    li r3, 0x18
    bl Alloc
    mr. r19, r3
    beq VSMode_Init_L_8009FF04
    bl fn_802090A8
    VSMode_Init_L_8009FF04:
    stw r19, 0x30(r29)
    li r3, 0x4
    lwz r0, 0x30(r29)
    stw r0, g_objCollChecker(r13)
    bl Alloc
    mr. r19, r3
    beq VSMode_Init_L_8009FF30
    lwz r4, lbl_806D12F4(r13)
    li r6, 0x0
    lwz r5, 0x30(r29)
    bl AI_SystemInit
    VSMode_Init_L_8009FF30:
    stw r19, 0x2c(r29)
    addi r3, r27, 0x6ac
    bl ProcessSystemTick
    lbz r0, g_isCommHost(r13)
    li r3, -0x1
    stw r3, g_sceneTransitionTimer(r13)
    cmplwi r0, 0x0
    beq VSMode_Init_L_8009FF6C
    li r20, 0x0
    VSMode_Init_L_8009FF54:
    mr r3, r20
    mr r4, r20
    bl CommBroadcast_SetKartRankNibble
    addi r20, r20, 0x1
    cmpwi r20, 0x4
    blt VSMode_Init_L_8009FF54
    VSMode_Init_L_8009FF6C:
    addi r3, r27, 0x6c8
    bl ProcessSystemTick
    bl Tachometer_Init
    bl HitMessageOverlay_Init
    li r3, 0x80
    bl Alloc
    mr. r19, r3
    beq VSMode_Init_L_8009FF94
    lwz r4, lbl_806D12F4(r13)
    bl HUD_Init
    VSMode_Init_L_8009FF94:
    stw r19, 0x24(r29)
    li r4, 0x6
    li r5, 0x0
    lwz r0, 0x24(r29)
    stw r0, g_raceHud(r13)
    lwz r3, 0x24(r29)
    bl HUD_RegisterOverlay
    lwz r3, 0x24(r29)
    li r4, 0x3
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x24(r29)
    li r4, 0x5
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x24(r29)
    li r4, 0x1
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x24(r29)
    li r4, 0x2
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x24(r29)
    li r4, 0xa
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x24(r29)
    li r4, 0xc
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x24(r29)
    li r4, 0xb
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x24(r29)
    li r4, 0x7
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x24(r29)
    li r4, 0x0
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x24(r29)
    li r4, 0xf
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x24(r29)
    li r4, 0x10
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x24(r29)
    li r4, 0xe
    li r5, 0x0
    bl HUD_RegisterOverlay
    bl IsTimerModeEnabled
    cmpwi r3, 0x1
    bne VSMode_Init_L_800A008C
    lwz r3, 0x24(r29)
    li r4, 0x4
    li r5, 0x0
    bl HUD_RegisterOverlay
    VSMode_Init_L_800A008C:
    lwz r3, 0x24(r29)
    li r4, 0xd
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x24(r29)
    lfs f1, lbl_806D47C0(r2)
    bl fn_80253EB8
    lwz r3, 0x24(r29)
    li r4, 0x8
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x24(r29)
    li r4, 0x9
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x24(r29)
    li r4, 0x15
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x24(r29)
    li r4, 0x16
    li r5, 0x0
    bl HUD_RegisterOverlay
    addi r3, r27, 0x6d4
    bl ProcessSystemTick
    lis r3, g_itemSelects@ha
    mr r25, r30
    addi r23, r3, g_itemSelects@l
    li r21, 0x0
    mr r26, r23
    la r24, lbl_806D1264(r13)
    VSMode_Init_L_800A0108:
    lwz r4, lbl_806CF140(r13)
    cmpw r21, r4
    beq VSMode_Init_L_800A0130
    mulli r0, r4, 0xa3c
    lbz r3, 0x0(r25)
    extrwi r3, r3, 3, 25
    lbzx r0, r30, r0
    extrwi r0, r0, 3, 25
    cmplw r3, r0
    bne VSMode_Init_L_800A025C
    VSMode_Init_L_800A0130:
    addi r0, r21, 0x9
    cmpw r21, r4
    lbzx r20, r31, r0
    extsb r20, r20
    bne VSMode_Init_L_800A0168
    li r3, 0x88
    bl Alloc
    mr. r19, r3
    beq VSMode_Init_L_800A0160
    mr r4, r20
    li r5, 0x1
    bl ItemSelect_Init
    VSMode_Init_L_800A0160:
    stw r19, 0x0(r26)
    b VSMode_Init_L_800A0188
    VSMode_Init_L_800A0168:
    li r3, 0x88
    bl Alloc
    mr. r19, r3
    beq VSMode_Init_L_800A0184
    mr r4, r20
    li r5, 0x0
    bl ItemSelect_Init
    VSMode_Init_L_800A0184:
    stw r19, 0x0(r26)
    VSMode_Init_L_800A0188:
    lwz r0, 0x0(r26)
    lwz r3, 0x0(r28)
    stw r0, 0x104(r3)
    lwz r22, 0x0(r26)
    lwz r3, 0x0(r28)
    bl CarObject_GetRenderObj
    stw r22, 0x364(r3)
    lwz r0, lbl_806CF110(r13)
    cmpwi r0, 0x1
    bne VSMode_Init_L_800A0208
    lwz r3, 0x0(r26)
    li r5, 0x1
    lhz r4, 0x10(r25)
    bl ItemSelect_AddSlotItem
    lwz r3, 0x0(r26)
    li r5, 0x1
    lhz r4, 0x12(r25)
    bl ItemSelect_AddSlotItem
    lwz r3, 0x0(r26)
    li r5, 0x1
    lhz r4, 0x14(r25)
    bl ItemSelect_AddSlotItem
    lwz r0, lbl_806CF140(r13)
    cmpw r21, r0
    bne VSMode_Init_L_800A0264
    lhz r4, 0x10(r25)
    lhz r3, 0x12(r25)
    lhz r0, 0x14(r25)
    stb r4, lbl_806D1264(r13)
    stb r3, 0x1(r24)
    stb r0, 0x2(r24)
    b VSMode_Init_L_800A0264
    VSMode_Init_L_800A0208:
    lwz r3, 0x0(r26)
    li r5, 0x1
    lhz r4, 0x10(r25)
    bl ItemSelect_AddSlotItem
    lwz r3, 0x0(r26)
    li r4, 0x3d
    li r5, 0x1
    bl ItemSelect_AddSlotItem
    lwz r3, 0x0(r26)
    li r4, 0x2b
    li r5, 0x1
    bl ItemSelect_AddSlotItem
    lwz r3, 0x0(r26)
    li r4, 0x17
    li r5, 0x1
    bl ItemSelect_AddSlotItem
    lwz r3, 0x0(r26)
    li r4, 0x32
    li r5, 0x1
    bl ItemSelect_AddSlotItem
    b VSMode_Init_L_800A0264
    VSMode_Init_L_800A025C:
    li r0, 0x0
    stw r0, 0x0(r26)
    VSMode_Init_L_800A0264:
    addi r21, r21, 0x1
    addi r26, r26, 0x4
    cmpwi r21, 0x4
    addi r28, r28, 0x4
    addi r25, r25, 0xa3c
    blt VSMode_Init_L_800A0108
    addi r3, r27, 0x6e8
    bl ProcessSystemTick
    li r0, 0x0
    stb r0, g_lakituStartAnimDone(r13)
    lwz r3, 0x18(r29)
    bl SetCourseScene3D
    lwz r4, g_cupId(r13)
    li r7, 0x0
    lwz r3, g_ccClass(r13)
    li r6, 0x1
    lwz r0, g_longRoundFlag(r13)
    mulli r8, r4, 0x48
    lis r4, VS_MODE@ha
    lfs f0, lbl_806D47A4(r2)
    li r5, -0x2
    stb r7, g_raceEnded(r13)
    addi r4, r4, VS_MODE@l
    mulli r9, r3, 0x18
    stw r7, g_finalRacePosition(r13)
    add r4, r4, r8
    stfs f0, g_bestLapTime(r13)
    addi r3, r27, 0x6f8
    mulli r8, r0, 0xc
    add r0, r4, r9
    stfs f0, g_currentLapTime(r13)
    add r4, r0, r8
    stfs f0, g_totalRaceTime(r13)
    lbz r0, -0x48(r4)
    lfs f1, -0x44(r4)
    lfs f0, -0x40(r4)
    extsb r0, r0
    stw r6, g_currentLap(r13)
    stw r5, g_raceResultCode(r13)
    stb r7, g_finalLapBannerShown(r13)
    stb r7, g_lapChangePending(r13)
    stw r7, lbl_806D1304(r13)
    stw r7, lbl_806D1308(r13)
    stb r6, lbl_806CF148(r13)
    stb r7, lbl_806D12E8(r13)
    stw r7, lbl_806D1300(r13)
    stw r0, g_totalLaps(r13)
    stfs f1, g_raceTimeRemaining(r13)
    stfs f0, g_lapBonusTimeDelta(r13)
    bl ProcessSystemTick
    lwz r3, 0x24(r29)
    lwz r4, g_totalLaps(r13)
    bl HUD_SetTotalLaps
    bl CourseBgm_Load
    lwz r0, g_weatherSystem(r13)
    cmplwi r0, 0x0
    bne VSMode_Init_L_800A0364
    li r3, 0x1b4
    bl Alloc
    mr. r19, r3
    beq VSMode_Init_L_800A0360
    li r4, 0x1
    bl WeatherSystem_Init
    VSMode_Init_L_800A0360:
    stw r19, g_weatherSystem(r13)
    VSMode_Init_L_800A0364:
    li r3, 0x1
    bl SetResourceLoadingFlag
    lwz r0, g_cupId(r13)
    li r4, 0x1
    li r3, 0x0
    stw r4, lbl_806D129C(r13)
    cmplwi r0, 0x8
    stw r3, g_raceFrameCounterLo2digits(r13)
    bgt VSMode_Init_L_800A03FC
    lis r3, jumptable_8040E748@ha
    slwi r0, r0, 2
    addi r3, r3, jumptable_8040E748@l
    lwzx r0, r3, r0
    mtctr r0
    bctr
    li r3, 0x1
    bl PreloadEffectResources
    b VSMode_Init_L_800A03FC
    li r3, 0x2
    bl PreloadEffectResources
    b VSMode_Init_L_800A03FC
    li r3, 0x3
    bl PreloadEffectResources
    b VSMode_Init_L_800A03FC
    li r3, 0x4
    bl PreloadEffectResources
    b VSMode_Init_L_800A03FC
    li r3, 0x5
    bl PreloadEffectResources
    b VSMode_Init_L_800A03FC
    li r3, 0x6
    bl PreloadEffectResources
    b VSMode_Init_L_800A03FC
    li r3, 0x7
    bl PreloadEffectResources
    b VSMode_Init_L_800A03FC
    li r3, 0x8
    bl PreloadEffectResources
    VSMode_Init_L_800A03FC:
    addi r3, r27, 0x70c
    bl ProcessSystemTick
    li r3, 0x9
    bl PreloadEffectResources
    addi r3, r27, 0x72c
    bl ProcessSystemTick
    li r3, 0xa
    bl PreloadEffectResources
    addi r3, r27, 0x74c
    bl ProcessSystemTick
    li r21, 0x0
    VSMode_Init_L_800A0428:
    lwz r0, 0x0(r23)
    cmplwi r0, 0x0
    beq VSMode_Init_L_800A0484
    li r22, 0x0
    b VSMode_Init_L_800A0468
    VSMode_Init_L_800A043C:
    lwz r3, 0x0(r23)
    mr r4, r22
    bl ItemSelect_GetSlotItemId
    clrlwi. r3, r3, 24
    beq VSMode_Init_L_800A0464
    mr r20, r3
    bl PreloadItemResources
    mr r3, r20
    bl fn_8023DBEC
    bl PreloadResource
    VSMode_Init_L_800A0464:
    addi r22, r22, 0x1
    VSMode_Init_L_800A0468:
    lwz r0, lbl_806CF110(r13)
    li r3, 0x5
    cmpwi r0, 0x1
    bne VSMode_Init_L_800A047C
    li r3, 0x3
    VSMode_Init_L_800A047C:
    cmpw r22, r3
    blt VSMode_Init_L_800A043C
    VSMode_Init_L_800A0484:
    addi r21, r21, 0x1
    addi r23, r23, 0x4
    cmpwi r21, 0x4
    blt VSMode_Init_L_800A0428
    addi r3, r27, 0x76c
    bl ProcessSystemTick
    lwz r20, g_roundIndex(r13)
    lwz r21, g_cupId(r13)
    lwz r22, g_gameMode(r13)
    bl GetEnemyParam
    mr r4, r22
    mr r5, r21
    mr r6, r20
    bl clEnemyParam_FillItemListIds
    li r23, 0x0
    VSMode_Init_L_800A04C0:
    lwz r20, g_roundIndex(r13)
    lwz r21, g_cupId(r13)
    lwz r22, g_gameMode(r13)
    bl GetEnemyParam
    mr r4, r22
    mr r5, r21
    mr r6, r20
    mr r7, r23
    bl AI_GetItemList
    mr r20, r3
    b VSMode_Init_L_800A0500
    VSMode_Init_L_800A04EC:
    bl PreloadItemResources
    lwz r3, 0x0(r20)
    bl fn_8023DBEC
    bl PreloadResource
    addi r20, r20, 0x4
    VSMode_Init_L_800A0500:
    lwz r3, 0x0(r20)
    cmpwi r3, -0x1
    bne VSMode_Init_L_800A04EC
    addi r23, r23, 0x1
    cmpwi r23, 0x4
    blt VSMode_Init_L_800A04C0
    addi r3, r27, 0x788
    bl ProcessSystemTick
    li r3, 0x0
    li r0, 0x1
    stb r3, lbl_806D1318(r13)
    stb r0, lbl_806D1319(r13)
    bl OSGetTime
    lis r5, lbl_805D2AA8@ha
    li r0, 0x0
    addi r6, r5, lbl_805D2AA8@l
    la r5, lbl_806D131C(r13)
    stb r0, lbl_806D131C(r13)
    stw r4, 0x4(r6)
    stw r3, 0x0(r6)
    stb r0, 0x1(r5)
    stw r4, 0xc(r6)
    stw r3, 0x8(r6)
    stb r0, 0x2(r5)
    stw r4, 0x14(r6)
    stw r3, 0x10(r6)
    stw r3, 0x18(r6)
    addi r3, r27, 0x7a4
    stb r0, 0x3(r5)
    stw r4, 0x1c(r6)
    bl ProcessSystemTick
    bl SyncSlot_GetRecv
    lwz r0, 0x4(r3)
    li r3, 0x24
    stw r0, g_humanPlayerCount(r13)
    bl Alloc
    mr. r19, r3
    beq VSMode_Init_L_800A05A0
    li r4, 0x168
    bl fn_8020B234
    VSMode_Init_L_800A05A0:
    stw r19, 0x34(r29)
    lwz r3, g_totalLaps(r13)
    bl VoiceSystem_SetCheckpointsForTotalLaps
    lwz r0, lbl_806D12F4(r13)
    stw r0, g_raceRankingPathObject(r13)
    psq_l f31, 0x68(r1), 0, 0
    lfd f31, 0x60(r1)
    lmw r19, 0x2c(r1)
    lwz r0, 0x74(r1)
    mtlr r0
    addi r1, r1, 0x70
    blr
}
#endif
#undef AI_GetItemList
#undef AI_SystemInit
#undef Alloc
#undef CObj_UpdatePerspParam
#undef Camera_Create
#undef CarObject_GetRenderObj
#undef CarObject_GetTransformMatrix
#undef CarObject_Init
#undef CoinSystem_Init
#undef CommBroadcast_SetKartRankNibble
#undef CourseBgm_Load
#undef CourseData_GetDefaultPathKey_Safe
#undef CourseData_GetOrCreate
#undef CourseObjectManager_Init
#undef DMAChannelManager_Init
#undef DebugPrintf
#undef FinalLapBanner_Init
#undef GetCourseBgmEntry
#undef GetCourseDataPtr
#undef GetCourseStartYaw
#undef GetEnemyParam
#undef GetKartModelNameEntry
#undef GetKartSlotCharId
#undef GetRaceContextPtr
#undef GetStartPosition
#undef HSD_LObjLoadDesc
#undef HSD_RandSeedPtr
#undef HUD_Init
#undef HUD_RegisterOverlay
#undef HUD_SetTotalLaps
#undef HitMessageOverlay_Init
#undef InputManager_Init
#undef IsTimerModeEnabled
#undef ItemObjectManager_Init
#undef ItemSelect_AddSlotItem
#undef ItemSelect_GetSlotItemId
#undef ItemSelect_Init
#undef Jyugemu_Flag_Ctor
#undef Jyugemu_ReverseFlag_Ctor
#undef KartItem_SetField358
#undef KartItem_SetShortArray34a
#undef LakituStart_Init
#undef LakituStart_SetCountdownHoldFrames
#undef MemoryManager_TimedFree
#undef OSGetTime
#undef PathManager_Init
#undef PathManager_RegisterCarObject
#undef PreloadEffectResources
#undef PreloadItemResources
#undef PreloadResource
#undef ProcessSystemTick
#undef RaceScene_GetPerspFovyForCup
#undef RaceSlot_InitSlot
#undef RankingTable_Init
#undef Scene3D_GetCameraPos
#undef Scene3D_Init
#undef Scene3D_SetupProjection
#undef SetActiveCamera
#undef SetCourseScene3D
#undef SetPlayerCarObject
#undef SetResourceLoadingFlag
#undef SoundChannels_ClearAll
#undef SoundDriver_GetOrCreate
#undef SyncSlot_GetHostSend
#undef SyncSlot_GetRecv
#undef Tachometer_Init
#undef TitleTracker_OnRaceStart_Stub
#undef TransitionEffect_GetOrCreate
#undef VSAI
#undef VSCamera
#undef VSCar
#undef VSCollision
#undef VSFinalLap
#undef VSFinalObject
#undef VSFlag
#undef VSHud
#undef VSInput
#undef VSItems
#undef VSLakitu
#undef VSOwner
#undef VSPath
#undef VSPeer
#undef VSRaceRow
#undef VSReverse
#undef VSScene
#undef VSWeather
#undef VS_MODE
#undef VoiceSystem_BindKartCarObject
#undef VoiceSystem_SetCheckpointsForTotalLaps
#undef WeatherSystem_Init
#undef clEnemyParam_FillItemListIds
#undef delete
#undef fn_802090A8
#undef fn_8020B234
#undef fn_8023DBEC
#undef fn_80253EB8
#undef g_bestLapTime
#undef g_carObjects
#undef g_ccClass
#undef g_cupId
#undef g_currentLap
#undef g_currentLapTime
#undef g_finalLapBannerShown
#undef g_finalRacePosition
#undef g_gameMode
#undef g_humanPlayerCount
#undef g_isCommHost
#undef g_itemSelects
#undef g_kartStartSlot
#undef g_lakituStartAnimDone
#undef g_lapBonusTimeDelta
#undef g_lapChangePending
#undef g_localPcbRole
#undef g_longRoundFlag
#undef g_namCamFlag
#undef g_objCollChecker
#undef g_playerRenderObj
#undef g_raceCamera
#undef g_raceEnded
#undef g_raceFrameCounterLo2digits
#undef g_raceHud
#undef g_raceRankingPathObject
#undef g_raceResultCode
#undef g_raceTimeRemaining
#undef g_reverseRoundFlag
#undef g_roundIndex
#undef g_sceneTransitionTimer
#undef g_totalLaps
#undef g_totalRaceTime
#undef g_weatherSystem
#undef jumptable_8040E748
#undef lbl_80598A60
#undef lbl_805A6154
#undef lbl_805D2AA8
#undef lbl_805D2B00
#undef lbl_806CF110
#undef lbl_806CF140
#undef lbl_806CF144
#undef lbl_806CF148
#undef lbl_806D1050
#undef lbl_806D10A0
#undef lbl_806D1264
#undef lbl_806D129C
#undef lbl_806D12E8
#undef lbl_806D12EC
#undef lbl_806D12F0
#undef lbl_806D12F4
#undef lbl_806D12F8
#undef lbl_806D12FC
#undef lbl_806D1300
#undef lbl_806D1304
#undef lbl_806D1308
#undef lbl_806D1318
#undef lbl_806D1319
#undef lbl_806D131C
#undef lbl_806D47A4
#undef lbl_806D47A8
#undef lbl_806D47AC
#undef lbl_806D47C0
#undef lbl_806D47D0
#undef new

/* ==== BtMode_Init ==== */
#pragma exceptions off
#define DebugPrintf DebugPrintf_p3
#define ItemUse_ResetAllKartUseSlots ItemUse_ResetAllKartUseSlots_p3
#define ProcessSystemTick ProcessSystemTick_p3
#define RaceScene_ClearPlayerSlotPointers RaceScene_ClearPlayerSlotPointers_p3
#define RaceSlot_ResetAll RaceSlot_ResetAll_p3
#define SetSyncTarget SetSyncTarget_p3
#define VoiceSystem_Init VoiceSystem_Init_p3
#define dtor_800A0688 dtor_800A0688_p3
#define g_finalLapCoinJumpEnabled g_finalLapCoinJumpEnabled_p3
#define g_gameMode g_gameMode_p3
#define g_spawnedKartCount g_spawnedKartCount_p3
#define lbl_8040E734 lbl_8040E734_p3
#define lbl_8040E76C lbl_8040E76C_p3
#define lbl_806CF14C lbl_806CF14C_p3
#define lbl_806D1050 lbl_806D1050_p3
#define lbl_806D130C lbl_806D130C_p3
/* === extracted from auto_BtMode_Init_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DebugPrintf(const char *fmt, ...);
extern void ItemUse_ResetAllKartUseSlots();
extern void ProcessSystemTick(const char *name);
extern void RaceScene_ClearPlayerSlotPointers();
extern void RaceSlot_ResetAll();
extern void SetSyncTarget();
extern void VoiceSystem_Init();

/* --- extern decls: sda21-referenced data --- */
extern unsigned char g_finalLapCoinJumpEnabled;
extern unsigned int g_gameMode;
extern unsigned int g_spawnedKartCount;
extern int lbl_806CF14C;
extern unsigned int lbl_806D1050;
extern unsigned char lbl_806D130C;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */

extern unsigned int lbl_8040E734[];
extern unsigned int lbl_8040E76C[];

/* --- function index (1 fns, .text 0x800A05D0..0x800A0688) ---
 * [  0] 0x800A05D0 size:0xB8    global BtMode_Init
 */

/* --- forward decls --- */
void *BtMode_Init(void **self);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void dtor_800A0688();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; void *f6; } extab_BtMode_Init = { 0x10080000, 0x00000048, 0x00110010, 0x00000000, 0x8680001E, 0x00000000, (void *)&dtor_800A0688 };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_BtMode_Init = {
    (void *)&BtMode_Init, 0x000000B8, (void *)&extab_BtMode_Init
};

/* BtMode_Init @ 0x800A05D0: battle-mode scene constructor. Sets game mode 2
 * (battle), resets the race slots for four karts and starts the voice
 * system, logging each step. Written in C with explicit vtable stores
 * (base lbl_8040E76C, then derived lbl_8040E734): the C++ ctor form loads
 * the string-pool base after the derived vtable store instead of between
 * the two. The extab (base dtor cleanup) stays a manual emit above. */
void *BtMode_Init(void **self)
{
    const char *log;

    *self = lbl_8040E76C;
    log = (const char *)lbl_80320960;
    *self = lbl_8040E734;
    g_gameMode = 2;
    SetSyncTarget(0x2a);
    RaceSlot_ResetAll();
    g_spawnedKartCount = 4;
    ItemUse_ResetAllKartUseSlots();
    g_finalLapCoinJumpEnabled = 0;
    RaceScene_ClearPlayerSlotPointers();
    lbl_806D1050 = 0;
    ProcessSystemTick(log + 0x7b4);
    VoiceSystem_Init();
    ProcessSystemTick(log + 0x7cc);
    DebugPrintf(log + 0x7e0);
    lbl_806CF14C = -1;
    lbl_806D130C = 0;
    return self;
}
#undef DebugPrintf
#undef ItemUse_ResetAllKartUseSlots
#undef ProcessSystemTick
#undef RaceScene_ClearPlayerSlotPointers
#undef RaceSlot_ResetAll
#undef SetSyncTarget
#undef VoiceSystem_Init
#undef dtor_800A0688
#undef g_finalLapCoinJumpEnabled
#undef g_gameMode
#undef g_spawnedKartCount
#undef lbl_8040E734
#undef lbl_8040E76C
#undef lbl_806CF14C
#undef lbl_806D1050
#undef lbl_806D130C

#pragma exceptions reset
__declspec(section ".rodata") const unsigned int lbl_80320960[267] = { 0x3F800000, 0x3F333333, 0x3F666666, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
__declspec(section ".rodata") const char lbl_80320D8C[] = "clGameBattle";
__declspec(section ".rodata") const unsigned int lbl_80320D9C[247] = { 0x636C4761, 0x6D65576F, 0x726C6400, 0x2D2D2D52, 0x41434520, 0x57414954, 0x202D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x0A000000, 0x2D2D2D52, 0x41434520, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x0A000000, 0x2D2D2D52, 0x414E4B49, 0x4E47202D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x0A000000, 0x4F4B2050, 0x72697A65, 0x20667265, 0x65210000, 0x636F6C6C, 0x20667265, 0x65210000, 0x63697465, 0x6D73656C, 0x20746163, 0x686F6D65, 0x74657220, 0x68697466, 0x61636520, 0x66726565, 0x21000000, 0x63646973, 0x70206361, 0x6D657261, 0x206A7567, 0x656D7520, 0x63656E74, 0x65722066, 0x72656521, 0x00000000, 0x63617220, 0x73686164, 0x6F772066, 0x72656521, 0x00000000, 0x65666665, 0x63742061, 0x75746F72, 0x756E206C, 0x69676874, 0x20667265, 0x65210000, 0x616C6C20, 0x726F6D20, 0x66726565, 0x21000000, 0x73746172, 0x74206261, 0x74746C65, 0x206C6F61, 0x64210000, 0x636C5363, 0x7265656E, 0x45666665, 0x63743A3A, 0x63726561, 0x74652829, 0x00000000, 0x4F4B2063, 0x6C4D6170, 0x28290000, 0x4F4B2073, 0x6861646F, 0x77210000, 0x4F4B204F, 0x626A6563, 0x74576F72, 0x6B496E69, 0x74202620, 0x45666665, 0x6374576F, 0x726B496E, 0x69740000, 0x4F4B206D, 0x61737465, 0x72206F72, 0x20736C61, 0x76650000, 0x4D595F50, 0x43422025, 0x64206D61, 0x73746572, 0x20256420, 0x454E454D, 0x59204D41, 0x58202564, 0x0A000000, 0x4F4B2073, 0x65747469, 0x6E672100, 0x50434225, 0x64203A20, 0x67726964, 0x2025642C, 0x20702025, 0x642C2063, 0x68617261, 0x2025640A, 0x00000000, 0x4F4B2050, 0x6C617965, 0x72206361, 0x72000000, 0x4F4B2050, 0x6C617965, 0x72206361, 0x72206365, 0x6E746572, 0x21000000, 0x6A797567, 0x656D755F, 0x73746172, 0x742E6461, 0x74000000, 0x4F4B206A, 0x7567656D, 0x75202620, 0x65746321, 0x21000000, 0x4F4B2063, 0x6C456E65, 0x6D795468, 0x696E6B4D, 0x616E6167, 0x65722829, 0x21000000, 0x4F4B2052, 0x616E6B69, 0x6E672100, 0x4F4B2073, 0x70726974, 0x65206364, 0x69737028, 0x29000000, 0x4F4B2073, 0x70726974, 0x65206974, 0x656D2100, 0x4F4B2054, 0x494D4520, 0x73657474, 0x696E6721, 0x00000000, 0x4F4B2065, 0x74632063, 0x6F757273, 0x65206566, 0x66656374, 0x2066696C, 0x65206C6F, 0x61642100, 0x4F4B2065, 0x66666563, 0x745F4C6F, 0x61644461, 0x74612845, 0x465F4B41, 0x5254293B, 0x00000000, 0x4F4B2065, 0x66666563, 0x745F4C6F, 0x61644461, 0x74612845, 0x465F4954, 0x454D293B, 0x00000000, 0x4F4B2050, 0x6C617965, 0x72204974, 0x656D204D, 0x6F64656C, 0x206C6F61, 0x64210000, 0x4F4B2045, 0x4E454D59, 0x20497465, 0x6D204D6F, 0x64656C20, 0x6C6F6164, 0x21000000, 0x4F4B206C, 0x69766520, 0x73657474, 0x696E6700, 0x4F4B2063, 0x6C47616D, 0x653A3A73, 0x65747469, 0x6E672829, 0x00000000, 0x4F4B2063, 0x6C47616D, 0x653A3A63, 0x6C4C6976, 0x65282900, 0x2D2D2D4C, 0x4F414420, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x0A000000, 0x00000000 };

