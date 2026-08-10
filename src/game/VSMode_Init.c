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
extern unsigned int lbl_806D0F14;
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
extern unsigned int lbl_80320960[];
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
    stw r0, lbl_806D0F14(r13)
    bl SyncSlot_GetRecv
    lbz r5, 0x1b(r3)
    li r0, 0x0
    lwz r4, lbl_806D0F14(r13)
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
    bl RenderTarget_Create
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
