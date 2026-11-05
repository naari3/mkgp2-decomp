/* Time-attack scene constructor; native C++ draft, retained NonMatching. */
#include "game/TaModeInitPrivate.h"

static inline int CcClass_Get() { return g_ccClass; }
static inline int KartVariant_Get() { return g_kartVariant; }
static inline void Render_SetReady(void *p) { *(int *)((char *)p + 0x238) = 1; }

TaMode::TaMode() {
    const char *log = lbl_80321980;
    const char *data = BATTLE;
    float startX, startY;
    HSD_RandSeedPtr = &lbl_806D13CC;
    *HSD_RandSeedPtr = lbl_806D1110;
    g_gameMode = 1;
    SetSyncTarget(0x2a);
    g_isCommHost = 0;
    ItemUse_ResetAllKartUseSlots();
    RaceScene_ClearPlayerSlotPointers();
    RaceSlot_ResetAll();
    g_spawnedKartCount = 1;
    int character = g_characterId;
    lbl_806D1050 = 0;
    RaceSlot_InitSlot(0, GetDisplayBufferIndex(), character, 1, 0);
    g_finalLapCoinJumpEnabled = 0;
    ProcessSystemTick(log + 0x68c);
    SetResourceLoadingFlag(0);
    DMAChannelManager_Init();
    TransitionEffect_GetOrCreate();
    SoundChannels_ClearAll();
    ItemObjectManager_Init();
    CourseObjectManager_Init();
    ProcessSystemTick(log + 0x6a4);
    environment = new EnvironmentMgr;
    CourseData_GetOrCreate(g_cupId, g_longRoundFlag, g_reverseRoundFlag);
    lbl_806D13C8 = HSD_LObjLoadDesc(GetCourseDataPtr());
    camera = new RaceCamera(lbl_806D483C, 0x200, lbl_806D4838, 0x200, lbl_806D13C8);
    SetActiveCamera(0, camera);
    g_raceCamera = camera;
    ProcessSystemTick(log + 0x6c8);
    RankingTable_Init(GetRaceContextPtr());
    SoundDriver_GetOrCreate(0);
    CoinSystem_Init(0, 2);
    lbl_806D13A8 = GetKartStartSlot(GetDisplayBufferIndex());
    g_kartStartSlot = lbl_806D13A8;
    GetStartPosition(lbl_806D13A8, &startX, 0, &startY);
    g_carObjects[0] = new CarObject(GetDisplayBufferIndex(), GetKartSlotCharId(lbl_806D13A8), startX, startY, GetCourseStartYaw(), CcClass_Get(), KartVariant_Get(), 1, -1, 0, 0);
    Render_SetReady(CarObject_GetRenderObj(g_carObjects[0]));
    KartItem_SetShortArray34a(CarObject_GetRenderObj(g_carObjects[0]), g_playerData);
    if (GetVBlankFlag() && !g_playerData[0x19d]) KartItem_SetField358(CarObject_GetRenderObj(g_carObjects[0]), 0);
    g_playerRenderObj = CarObject_GetRenderObj(g_carObjects[0]);
    ProcessSystemTick(log + 0x6d4);
    SetPlayerCarObject(g_carObjects[0]);
    {
    float *matrix = CarObject_GetTransformMatrix(g_carObjects[0]);
    lbl_806D13A4 = new PathManager(CourseData_GetDefaultPathKey_Safe(), g_carObjects[0], CarObject_GetRenderObj(g_carObjects[0]), matrix + 12, matrix + 13, matrix + 14);
    }
    int cup = g_cupId - 1;
    int reverse = g_reverseRoundFlag;
    int cc = g_ccClass;
    int round = g_longRoundFlag;
    int index = round + (cup * 4 + reverse * 2);
    if (cc == 2) {
        if (g_playerData[0x48 + index] == 1) lbl_806D13A0 = 1;
        else lbl_806D13A0 = 0;
    }
    lbl_806D1394 = 0;
    if (cc == 2 && lbl_806D13A0) {
        const TaGhostSource *ghost = (const TaGhostSource *)(data + 0x540 + cup * 32 + round * 16);
        if (!reverse) ghost = (const TaGhostSource *)(data + 0x340 + cup * 32 + round * 16);
        lbl_806D1398 = new CarObject(4, ghost->character, startX, startY, GetCourseStartYaw(), 2, 3, 0, -1, 0, 0);
        float *matrix = CarObject_GetTransformMatrix(lbl_806D1398);
        void *render = CarObject_GetRenderObj(lbl_806D1398);
        lbl_806D139C = PathManager_RegisterCarObject(lbl_806D13A4, matrix + 12, matrix + 13, matrix + 14, lbl_806D1398, render, 1);
        lbl_806CF198 = 3;
        lbl_806D1390 = DVDFile_LoadSync(ghost->file);
        lbl_806D1388 = lbl_806D1390;
        lbl_806D138C = ghost->size;
        if (lbl_806D1398) {
            KartMovement_EquipItem(CarObject_GetRenderObj(lbl_806D1398), 0x17);
            ItemEffectBus_OrMask(*(void **)((char *)CarObject_GetRenderObj(lbl_806D1398) + 0x304), 0x8000000000ULL);
        }
    } else { lbl_806D1398 = 0; lbl_806D1390 = 0; }
    ProcessSystemTick(log + 0x6e4);
    lakitu = new LakituStart(log + 0x6f0, lbl_806D13A8, lbl_806D4830, lbl_806D4830, lbl_806D4830);
    scene = new Scene3D(*GetKartModelNameEntry(GetKartSlotCharId(lbl_806D13A8), -1));
    jyugemuFlag = new JyugemuFlag(scene);
    jyugemuReverse = new JyugemuReverseFlag(CarObject_GetRenderObj(g_carObjects[0]));
    lapBanner = new FinalLapBanner(CarObject_GetRenderObj(g_carObjects[0]));
    ProcessSystemTick(log + 0x704);
    float cameraX, cameraY;
    Scene3D_GetCameraPos(scene, &cameraX, &cameraY);
    cameraX += lbl_806D4860;
    Scene3D_SetupProjection(scene, cameraX, cameraY);
    Tachometer_Init();
    hud = new RaceHud(lbl_806D13A4);
    g_raceHud = hud;
    HUD_RegisterOverlay(hud, 6, 0);
    HUD_RegisterOverlay(hud, 3, 0);
    HUD_RegisterOverlay(hud, 5, 0);
    HUD_RegisterOverlay(hud, 1, 0);
    HUD_RegisterOverlay(hud, 2, 0);
    HUD_RegisterOverlay(hud, 10, 0);
    HUD_RegisterOverlay(hud, 11, 0);
    HUD_RegisterOverlay(hud, 7, 0);
    HUD_RegisterOverlay(hud, 15, 0);
    HUD_RegisterOverlay(hud, 16, 0);
    HUD_RegisterOverlay(hud, 14, 0);
    if (IsTimerModeEnabled() == 1) HUD_RegisterOverlay(hud, 4, 0);
    HUD_RegisterOverlay(hud, 13, 0);
    fn_80253EB8(hud, lbl_806D484C);
    HUD_RegisterOverlay(hud, 8, 0);
    HUD_RegisterOverlay(hud, 9, 0);
    HUD_RegisterOverlay(hud, 21, 0);
    ProcessSystemTick(log + 0x718);
    g_sceneTransitionTimer = -1;
    g_lakituStartAnimDone = 0;
    SetCourseScene3D(scene);
    g_raceEnded = 0;
    ai = 0;
    flag38 = 0;
    const RaceParams *params = &((const RaceParams (*)[3][2])data)[g_cupId - 1][g_ccClass][g_longRoundFlag];
    g_bestLapTime = lbl_806D4830;
    g_currentLapTime = lbl_806D4830;
    g_totalRaceTime = lbl_806D4830;
    lbl_806D13A1 = 0;
    g_finalRacePosition = 0;
    int laps = params->laps;
    float time = params->timeLimit;
    float bonus = params->lapBonus;
    g_currentLap = 1;
    g_raceResultCode = -2;
    g_finalLapBannerShown = 0;
    g_lapChangePending = 0;
    g_totalLaps = laps;
    g_raceTimeRemaining = time;
    g_lapBonusTimeDelta = bonus;
    lbl_806CF19C = lbl_806D4834;
    HUD_SetTotalLaps(hud, g_totalLaps);
    ProcessSystemTick(log + 0x72c);
    CourseBgm_Load();
    if (!g_weatherSystem) g_weatherSystem = new WeatherSystem(1);
    lbl_806D13B0 = 0;
    lbl_806D13AC = 3;
    PreloadItemResources(0x17);
    KartMovement_EquipItem(CarObject_GetRenderObj(g_carObjects[0]), 0x17);
    lbl_806D13B4 = new TaSound(0);
    if (lbl_806D13B4) fn_8023E1E4(lbl_806D13B4, 0x117, 0);
    StrPcb_SetStatusBits(StrPcb_GetInstance(), 4, 0);
    StrPcb_SetStatusBits(StrPcb_GetInstance(), 8, 0);
    ProcessSystemTick(log + 0x740);
    SetResourceLoadingFlag(1);
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
    }
    PreloadEffectResources(9);
    PreloadEffectResources(10);
    ProcessSystemTick(log + 0x75c);
    lbl_806D13B8 = 0;
    long long timestamp = OSGetTime();
    lbl_806D13C0 = (unsigned long)(timestamp >> 32);
    lbl_806D13C4 = (unsigned long)timestamp;
    SetSyncTarget(0x2c);
    PlayStats_IncTaPlay();
    DebugPrintf(log + 0x76c);
}
