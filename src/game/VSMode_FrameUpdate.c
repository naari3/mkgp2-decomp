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
extern void VSMode_Init();
extern void VfxSlotMgr_Update();
extern void VoiceQueue_Clear();
extern void __cvt_ll2flt();
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
extern void fn_8025EF58();
extern void fn_80271884();
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
extern unsigned int lbl_806D0F14;
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
extern unsigned int lbl_80320960[];
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
    addi r3, r13, -0x5A30  /* lbl_806D12F0 */
    li r4, 0x0
    li r5, 0x4
    bl memset
    addi r0, r13, -0x5A30  /* lbl_806D12F0 */
    stw r0, lbl_806D0F14(r13)
    bl SyncSlot_GetRecv
    lbz r0, 0x1b(r3)
    lwz r3, lbl_806D0F14(r13)
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
    addi r3, r13, -0x5A30  /* lbl_806D12F0 */
    li r4, 0x0
    li r5, 0x4
    bl memset
    addi r0, r13, -0x5A30  /* lbl_806D12F0 */
    stw r0, lbl_806D0F14(r13)
    bl SyncSlot_GetRecv
    lbz r0, 0x1b(r3)
    lwz r3, lbl_806D0F14(r13)
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
    bl fn_8025EF58
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
    bl fn_8025EF58
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
    addi r23, r13, -0x5A04  /* lbl_806D131C */
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
    bl fn_80271884
    bl __cvt_ll2flt
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

