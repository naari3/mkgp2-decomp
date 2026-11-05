#include "game/Scene_80164614Private.h"

extern "C" LoaderInit163 *fn_80164614(LoaderInit163 *s, int index, int record) {
    DemoRodata163 *data = (DemoRodata163 *)lbl_80369798;
    fn_80121210();
    DrawManager_GetOrCreate();
    fn_801E93A0();
    ReplayRandCursor_Reset();
    ProcessSystemTick(0);
    unsigned int *seed = HSD_RandSeedPtr;
    HSD_RandSeedPtr = (unsigned int *)s;
    s->seed = (unsigned int)seed;
    srand(1);
    Rand_SetSeedDebug(1);
    *HSD_RandSeedPtr = 1;
    s->random = RandSeedDebug_SetEnable(0);
    SetTimerModeEnabled(1);
    g_gameMode = 0;
    g_ccClass = 0;
    g_cupId = data->entries[index].cup;
    g_longRoundFlag = data->entries[index].round;
    SetReverseRoundFlag(data->entries[index].reverse);
    g_courseVariantIdx = data->entries[index].variant;
    g_roundIndex = 0;
    lbl_806D1264[0] = 0x3d;
    lbl_806D1264[1] = 0x2b;
    lbl_806D1264[2] = 0x32;
    s->recording = record;
    ProcessSystemTick(0);
    DebugPrintf(data->sizeFormat, 43200);
    s->inputs = (TraceInput163 *)FUN_8003b120(43200);
    memset(s->inputs, 0, 43200);
    if (!s->recording) {
        DVDFile163 file;
        if (DVDOpen(data->entries[index].file, &file)) {
            int size = file.length;
            DebugPrintf(data->fileSizeFormat, size);
            if (size > 0) {
                size = (size + 31) & ~31;
                void *buffer = OSAllocFromHeap(lbl_806CF010, size);
                if (buffer) {
                    int end = file.start + file.length - 1;
                    DVDLoad_WaitIfSamePage();
                    int count = DVDReadPrio(&file, buffer, size, 0, 2);
                    DVDLoad_RecordOpStart(end);
                    DebugPrintf(data->readFormat, count);
                    if (count > 43200) count = 43200;
                    count -= (unsigned int)count % 16;
                    if (count > 0) memcpy(s->inputs, buffer, count);
                    OSFreeToHeap(lbl_806CF010, buffer);
                }
            }
            DVDClose(&file);
        }
    }
    s->inputIndex = 0;
    ProcessSystemTick(0);
    RaceSlot_ResetAll();
    RaceSlot_InitSlot(VSMode_SeedRandomItemSequence(0, data->entries[index].character, 5), 0, data->entries[index].character, 1, 0);
    g_characterId = data->entries[index].character;
    HSD_FObjForceLinearInterp(1);
    lbl_806CF110 = 1;
    SetLocalPcbRole(0);
    g_isCommHost = 0;
    g_spawnedKartCount = 6;
    ItemUse_ResetAllKartUseSlots();
    lbl_806D1050 = 0;
    RaceScene_ClearPlayerSlotPointers();
    SetResourceLoadingFlag(0);
    DMAChannelManager_Init();
    ProcessSystemTick(0);
    TransitionEffect_GetOrCreate();
    SoundChannels_ClearAll();
    ProcessSystemTick(0);
    ItemObjectManager_Init();
    ProcessSystemTick(0);
    CourseObjectManager_Init();
    ProcessSystemTick(0);
    s->environment = new Env163;
    ProcessSystemTick(0);
    CourseData_GetOrCreate(g_cupId, g_longRoundFlag, g_reverseRoundFlag);
    s->resource = HSD_LObjLoadDesc(GetCourseDataPtr());
    s->child = new Camera163(512, 512, lbl_806D8908, lbl_806D890C, s->resource);
    SetActiveCamera(0, (int)s->child);
    g_raceCamera = s->child;
    RankingTable_Init(GetRaceContextPtr());
    ProcessSystemTick(0);
    if (g_cupId == 6 && g_roundIndex == 0) SoundDriver_GetOrCreate(0);
    else SoundDriver_GetOrCreate(GetCourseBgmEntry());
    ProcessSystemTick(0);
    CoinSystem_Init(0, 2);
    ProcessSystemTick(0);
    s->slot = GetKartStartSlot(0);
    g_kartStartSlot = s->slot;
    float x, z;
    GetStartPosition(s->slot, &x, 0, &z);
    if (s->recording == 1)
        g_carObjects[0] = new Car163(0, GetKartSlotCharId(s->slot), x, z, GetCourseStartYaw(), 0, 0, 1, -1, 0, 0);
    else
        g_carObjects[0] = new Car163(0, GetKartSlotCharId(s->slot), x, z, GetCourseStartYaw(), 0, 0, 0, -1, 0, 1);
    *(int *)((char *)CarObject_GetRenderObj(g_carObjects[0]) + 0x238) = 1;
    KartItem_SetShortArray34a(CarObject_GetRenderObj(g_carObjects[0]), g_playerData);
    g_playerRenderObj = CarObject_GetRenderObj(g_carObjects[0]);
    SetPlayerCarObject(g_carObjects[0]);
    ProcessSystemTick(0);
    char *matrix = CarObject_GetTransformMatrix(g_carObjects[0]);
    SceneFlow_SetFlag1048(1);
    s->paths = new Path163(CourseData_GetDefaultPathKey_Safe(), g_carObjects[0], CarObject_GetRenderObj(g_carObjects[0]), matrix + 0x30, matrix + 0x34, matrix + 0x38);
    s->scene = (DemoSceneBase *)new Scene163(*GetKartModelNameEntry(GetKartSlotCharId(s->slot), -1));
    float nearPlane, farPlane;
    Scene3D_GetCameraPos(s->scene, &nearPlane, &farPlane);
    Scene3D_SetupProjection(s->scene, lbl_806D8910 + nearPlane, farPlane);
    CObj_UpdatePerspParam(s->scene, RaceScene_GetPerspFovyForCup());
    SetCourseScene3D(s->scene);
    ProcessSystemTick(0);
    s->object = new Lakitu163(data->lakituName, s->slot, lbl_806D88F0, lbl_806D88F0, lbl_806D88F0);
    LakituStart_SetCountdownHoldFrames(s->object, 320);
    s->flag = new Flag163(s->scene);
    s->reverseFlag = new Reverse163(CarObject_GetRenderObj(g_carObjects[0]));
    s->banner = new Banner163(CarObject_GetRenderObj(g_carObjects[0]));
    ProcessSystemTick(0);
    g_lakituStartAnimDone = 0;
    s->system = new Collision163;
    g_objCollChecker = s->system;
    ProcessSystemTick(0);
    s->ai = new AI163(s->paths, s->system, 0);
    ProcessSystemTick(0);
    g_itemSelects[0] = 0;
    g_sceneTransitionTimer = -1;
    g_itemSelects[1] = 0;
    g_itemSelects[2] = 0;
    g_itemSelects[3] = 0;
    *((char *)GetKartSlotKartVariant(s->slot) + 0x2d0) = 1;
    void *select = new Select163(s->slot, 0);
    g_itemSelects[0] = select;
    *(void **)((char *)g_carObjects[0] + 0x104) = select;
    *(void **)((char *)CarObject_GetRenderObj(g_carObjects[0]) + 0x364) = g_itemSelects[0];
    if (lbl_806CF110 == 1) {
        ItemSelect_AddSlotItem(g_itemSelects[0], lbl_806D1264[0], 1);
        ItemSelect_AddSlotItem(g_itemSelects[0], lbl_806D1264[1], 1);
        ItemSelect_AddSlotItem(g_itemSelects[0], lbl_806D1264[2], 1);
    } else {
        ItemSelect_AddSlotItem(g_itemSelects[0], 0x3d, 1);
        ItemSelect_AddSlotItem(g_itemSelects[0], 0x2b, 1);
        ItemSelect_AddSlotItem(g_itemSelects[0], 0x32, 1);
    }
    g_raceEnded = 0;
    g_finalRacePosition = 6;
    g_bestLapTime = lbl_806D88F0;
    g_currentLapTime = lbl_806D88F0;
    g_totalRaceTime = lbl_806D88F0;
    g_currentLap = 1;
    g_raceResultCode = -2;
    g_finalLapBannerShown = 0;
    g_lapChangePending = 0;
    g_totalLaps = DEMO[g_cupId][g_longRoundFlag - 4].laps;
    g_raceTimeRemaining = DEMO[g_cupId][g_longRoundFlag - 4].time;
    g_lapBonusTimeDelta = DEMO[g_cupId][g_longRoundFlag - 4].bonus;
    CourseBgm_Load();
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
    ProcessSystemTick(0);
    PreloadEffectResources(9);
    PreloadEffectResources(10);
    ProcessSystemTick(0);
    for (int i = 0; i < (lbl_806CF110 == 1 ? 3 : 5); i++) {
        unsigned char id = ItemSelect_GetSlotItemId(g_itemSelects[0], i);
        if (id) PreloadItemResources(id);
    }
    ProcessSystemTick(0);
    int round = g_roundIndex;
    int cup = g_cupId;
    int mode = g_gameMode;
    clEnemyParam_FillItemListIds(GetEnemyParam(), mode, cup, round);
    round = g_roundIndex;
    cup = g_cupId;
    mode = g_gameMode;
    int *items = AI_GetItemList(GetEnemyParam(), mode, cup, round, 0);
    for (; *items != -1; items++) PreloadItemResources(*items);
    ProcessSystemTick(0);
    s->done = 0;
    s->ready = 0;
    s->time = lbl_806D8904;
    s->fade = lbl_806D88F0;
    s->heldItemFrames = 0;
    s->field58 = 0;
    return s;
}
