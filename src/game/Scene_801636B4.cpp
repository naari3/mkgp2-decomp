#include "game/Scene_80164614Private.h"
namespace DeleteView {
#include "game/types/clCSPlayDemoDeleteView.h"
extern "C" LoaderDelete162 *fn_801638B4(LoaderDelete162 *, short);
}
extern "C" int fn_80163EF4(LoaderTick163 *);
extern "C" void fn_80163C68(LoaderDraw *);
#include "game/types/arg_order.h"

// Course demo speed curves, followed by the replay configuration pool.
extern "C" const float Scene_80164614_rodata_80369798[255] = {
    1.0f, 0.699999988f, 0.899999976f, 0.0f, 0.0f, 500.0f, 66.6666718f, 1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f, 1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f, 1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f, 1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f, 1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f, 1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f, 1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f, 1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f, 1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f, 1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f, 1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f, 1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 83.3333359f, 1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
    83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f, 1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
    83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f, 1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
    83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f, 1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
    83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f, 1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
    83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f, 1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
    83.3333359f, 5000.0f, 83.3333359f,
};

extern "C" const char lbl_80369B94[0x13] = "playlog7_short.bin";
extern "C" const char lbl_80369BA8[0x13] = "playlog8_short.bin";
extern "C" const char lbl_80369BBC[0x12] = "playlog7_long.bin";
extern "C" const char lbl_80369BD0[0x12] = "playlog8_long.bin";
static const DemoEntry163 demoEntries[4] = {
    {12, 7, 0, 0, 0, lbl_80369B94},
    {11, 8, 0, 0, 0, lbl_80369BA8},
    {12, 7, 1, 0, 0, lbl_80369BBC},
    {11, 8, 1, 0, 0, lbl_80369BD0},
};
#include "game/types/shared_data.h"
#ifndef __MWERKS__ /* the names other units use (tools/alias_census.py) */
#define demoZero1 Scene_80163EF4_rodata_80369C44
#define demoZero2 Scene_80163EF4_rodata_80369C50
#endif
extern "C" const Vec demoZero1 = {0.0f, 0.0f, 0.0f};
extern "C" const Vec demoZero2 = {0.0f, 0.0f, 0.0f};
extern "C" const char lbl_80369C5C[0x12] = "clCSPartsPlayDemo";
extern "C" const char lbl_80369C70[0x22] = "clCSSceneAttract::clTaskInterface";
extern "C" const char lbl_80369C94[0x38] = "//====================================================\n";
extern "C" const char lbl_80369CCC[0x1a] = "  { %ff, %ff, %ff, %d },\n";
static const char demoSizeFormat[0x18] = "PLAYDEMO    logsize:%d\n";
static const char demoFileSizeFormat[0x1c] = "PLAYDEMO    logfilesize:%d\n";
static const char demoReadFormat[0x19] = "PLAYDEMO    readsize:%d\n";
static const char demoLakituName[0x12] = "jyugemu_start.dat";

static inline void FillDemoItemList() {
    int mode, cup, round;
    round = g_roundIndex;
    cup = g_cupId;
    mode = g_gameMode;
    clEnemyParam_FillItemListIds(GetEnemyParam(), mode, cup, round);
}
static inline int *GetDemoItemList() {
    int mode, cup, round;
    round = g_roundIndex;
    cup = g_cupId;
    mode = g_gameMode;
    return AI_GetItemList(GetEnemyParam(), mode, cup, round, 0);
}

#include "game/types/reg_args.h"

static inline void CapTime(float limit, float &value) { if (value > limit) value = limit; }

/* The scene and loader share one original file; definitions follow target order. */
#include "game/types/clCSScenePlayDemo.h"

/* fakematch: an uncalled diagnostic preserves the pooled base-name order,
 * following clLineManager::PrintLines. */
void clCSScenePlayDemo::PrintClassName() { DebugPrintf("clSceneInterface"); }

void clCSScenePlayDemo::Draw() {
    if (!done && loader) fn_80163C68((LoaderDraw *)loader);
}

void clCSScenePlayDemo::Update() {
    if (!done && loader) {
        if ((unsigned char)fn_80163EF4((LoaderTick163 *)loader) == 1) done = 1;
    }
}

clCSScenePlayDemo::~clCSScenePlayDemo() {
    SetCourseScene3D(0);
    if (loader) DeleteView::fn_801638B4((DeleteView::LoaderDelete162 *)loader, 1);
}

void clCSScenePlayDemo::Destroy() { delete this; }

extern "C" clCSScenePlayDemo *fn_80163804(void *desc, void *arg) {
    return new clCSScenePlayDemo(desc, arg);
}

namespace DeleteView {
extern "C" LoaderDelete162 *fn_801638B4(LoaderDelete162 *s, short flag) {
    if (s) {
        if (s->trace == 1 && s->traceTime <= lbl_806D88F0) {
            DebugPrintf(lbl_80369C94);
            for (int i = 0; i < 2700; i++) {
                Trace162 *p = &s->positions[i];
                DebugPrintf(lbl_80369CCC, p->x, p->y, p->z, p->n);
            }
            DebugPrintf(lbl_80369C94);
        }
        MemoryManager_Free(s->positions);
        ProcessSystemTick(0);
        SetActiveCamera(0, 0);
        AI_SystemDtor(s->ai, 1);
        fn_80208FE4(s->system, 1);
        ItemSelect_Dtor(g_itemSelects[0], 1);
        SetCourseScene3D(0);
        delete s->scene;
        LakituStart_Dtor(s->object, 1);
        Jyugemu_Flag_Dtor(s->flag, 1);
        Jyugemu_ReverseFlag_Dtor(s->reverseFlag, 1);
        LapBannerScene_Dtor(s->banner, 1);
        PathParticipantArray_Dtor(s->paths, 1);
        SceneFlow_SetFlag1048(0);
        ProcessSystemTick(0);
        delete (DeleteCar162 *)g_carObjects[0];
        if (s->child) delete s->child;
        CourseEnvironment_Dtor(s->environment, 1);
        ProcessSystemTick(0);
        if (s->resource) {
            Release(s->resource);
            s->resource = 0;
        }
        ItemObjectManager_Reset();
        VfxSlotMgr_Shutdown();
        RankingTable_Init(GetRaceContextPtr());
        ClRomTable_PurgeAll();
        ProcessSystemTick(0);
        s->object = 0;
        s->flag = 0;
        s->reverseFlag = 0;
        s->banner = 0;
        g_carObjects[0] = 0;
        s->paths = 0;
        s->scene = 0;
        s->environment = 0;
        SetPlayerCarObject(0);
        delete (DeleteObject162 *)lbl_806D10D0;
        lbl_806D10D0 = 0;
        fn_8013A6F8();
        g_raceCamera = 0;
        ProcessSystemTick(0);
        CourseBgm_Free();
        SceneDrawList_Reset();
        delete (DeleteObject162 *)lbl_806D109C;
        lbl_806D109C = 0;
        delete g_courseData[0];
        g_courseData[0] = 0;
        ProcessSystemTick(0);
        SetResourceLoadingFlag(0);
        HSD_FObjForceLinearInterp(0);
        HSD_RandSeedPtr = (unsigned int *)s->seed;
        RandSeedDebug_SetEnable(s->randDebug);
        ProcessSystemTick(0);
        delete lbl_806D10AC;
        lbl_806D10AC = 0;
        fn_80121210();
        clRom_PurgeAll();
        ProcessSystemTick(0);
        if (flag > 0) MemoryManager_TimedFree(s);
    }
    return s;
}
}

extern "C" void fn_80163C68(LoaderDraw *s) {
    if (s->done != 1 && s->ready) {
        if (s->scene->Ready() == 1) {
            clDrawMan_Buckets_Reset(GetDrawMan());
            TransparentDraw_SortAndDispatch();
            CObj_DebugVizPathFlush(s->scene);
            fn_8016B0C4();
            Stub_NoOp_80030aec(s->scene);
            Object_RenderJObjIfWithinRange(s->object);
            Jyugemu_Flag_Render(s->flag);
            Jyugemu_ReverseFlag_Render(s->reverseFlag);
            LapBannerScene_RenderIfActive(s->banner);
            CourseEnvironment_RenderObjects_Timed(s->environment);
            Subsystem36c_DispatchPass2_Timed(s->environment);
            fn_801EB91C(s->ai, 1);
            fn_80208E2C(s->system);
            NoopRenderHook_Pending_80064d28();
            ItemObjectManager_Render();
            DrawEffect_TickAndCull();
            for (int i = 0; i < 8; i++) {
                void *kart = GetKartSlotKartVariant(i);
                if (kart) {
                    KartItem_TriggerStateAction(kart);
                    KartItem_IsAtStartSlot(kart);
                }
            }
            KartItem_RenderPipelinedWithEffects(g_carObjects[0], 0);
            fn_80139810();
            clItemBoxManager_Draw(BoxManager());
            clDrawMan_EndFrame_NoOp(GetDrawMan());
            clDrawMan_Buckets_Dispatch(GetDrawMan());
            Subsystem36c_DispatchPass4_Timed(s->environment);
            TransitionEffect_RenderPass(Transition(), 5);
            TransitionEffect_RenderPass(Transition(), 3);
            if (g_currentLap < g_totalLaps + 1) ItemSelect_DrawUIHelperIfActive(g_itemSelects[0]);
            TransitionEffect_RenderPass(Transition(), 2);
            TransitionEffect_RenderPass(Transition(), 4);
            TransitionEffect_RenderPass(Transition(), 6);
            s->scene->Render();
            HSD_LObjDeleteCurrentAll(0);
        }
        TransitionEffect_RenderPass(Transition(), 1);
        if (s->fade > lbl_806D88F0) {
            fn_80181790(s->scene, 0, lbl_806D88F8, 0, 0, (int)(lbl_806D88F4 * s->fade), 0);
        }
        HSD_StateInvalidate(0x7f);
    }
}

extern "C" int fn_80163EF4(LoaderTick163 *s) {
    if (s->done || s->time <= 0.0f) {
        s->done = 1;
        return 1;
    }
    g_raceFrameCounterLo2digits = (BattleRoulette_TickAndGetCounter() * 3 + 1) % 100;
    ItemObjectManager_PerFrameUpdate(GetRaceContextPtr());
    float pedal;
    CalcSoundDirection(CarObject_GetRenderObj(g_carObjects[0]), s->paths, &pedal, 0);
    pedal = 1.0f;
    if (KartMovement_GetCurrentItemId(CarObject_GetRenderObj(g_carObjects[0])) != -1)
        s->heldItemFrames++;
    else s->heldItemFrames = 0;
    if (s->recording == 1) {
        RecordedPlayer163 *p = (RecordedPlayer163 *)InputMgr_GetPlayer(GetInputManager(), 0);
        s->inputs[s->inputIndex].steer = p->Steering();
        s->inputs[s->inputIndex].pedal = p->Pedal();
        s->inputs[s->inputIndex].brake = p->Brake();
        s->inputs[s->inputIndex].buttons = p->Buttons(0xe3ff);
    }
    float steer = s->inputs[s->inputIndex].steer;
    pedal = s->inputs[s->inputIndex].pedal;
    float brake = s->inputs[s->inputIndex].brake;
    int buttons = s->inputs[s->inputIndex].buttons;
    if (s->inputIndex < 2699) s->inputIndex++;
    if (g_raceEnded) {
        steer = CalcSoundDirection(CarObject_GetRenderObj(g_carObjects[0]), s->paths, &pedal, 0);
        brake = 0.0f;
        buttons = 0;
    }
    CarObject_ApplyInput(g_carObjects[0], IsRaceStarted(), steer, pedal, brake);
    CarObject_FrameUpdate(g_carObjects[0], 0);
    ItemBox_ProcessPickup(g_itemSelects[0], g_carObjects[0], 0, buttons, 0, brake);
    RankingMgr_UpdatePositions(s->ai);
    if ((unsigned char)IsRaceStarted() == 1) {
        Checkpoint163 *a = Path_LookupCheckpointOffset(s->paths, 0, 0);
        Checkpoint163 *b = Path_LookupCheckpointOffset(s->paths, 0, 1);
        Vec v = Scene_80163EF4_rodata_80369C44;
        v.x = a->x;
        v.z = a->z;
        Vec w = Scene_80163EF4_rodata_80369C50;
        w.x = b->x;
        w.z = b->z;
        if (JObj_IsForwardDotBelowThreshold(CarObject_GetRenderObj(g_carObjects[0]), &v, &w) == 1)
            Jyugemu_ReverseFlag_SetState(s->reverseFlag, 1);
        else Jyugemu_ReverseFlag_SetState(s->reverseFlag, 0);
    }
    fn_80208E30(s->system);
    if (!s->ready) s->ready = 1;
    KartItem_UpdateShadowBillboardAndViewport(g_carObjects[0], s->scene, 0);
    Fog_UpdateFromCourseScene3D();
    PathManager_UpdateAll(s->paths);
    LakituStart_UpdateCountdown(s->object);
    Jyugemu_Flag_Tick(s->flag);
    Jyugemu_ReverseFlag_Tick(s->reverseFlag);
    LapBannerScene_UpdateAndDriveAnim(s->banner);
    CourseEnvironment_UpdateAndCullZones_Timed(s->environment);
    CObj_LoadProjMatrix(s->scene, &Scene_80163EF4_bss_80677CE8);
    CObj_ApplyScissor(s->scene, &Scene_80163EF4_bss_80677CF4);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(Scene_80163EF4_bss_80677CE8, Scene_80163EF4_bss_80677CF4);
    if (g_rendererGateFlag == 1 && (unsigned char)IsRaceStarted() == 1 && !g_raceEnded) {
        float zero = 0.0f;
        float raceTime = g_raceTimeRemaining;
        if (raceTime > zero) {
            g_raceTimeRemaining -= (1.0f / 60.0f);
            if (g_raceTimeRemaining < 0.0f) {
                g_raceTimeRemaining = 0.0f;
                CapTime(60.0f, s->time);
            }
        }
    }
    TransitionEffect_Tick(Transition());
    if (!g_finalLapBannerShown && g_currentLap >= g_totalLaps) g_finalLapBannerShown = 1;
    if (0.0f != g_raceTimeRemaining && g_raceResultCode == -2) {
        if (g_currentLap >= g_totalLaps + 1) {
            KartItem_OnFallOffOrDeath(g_carObjects[0]);
            CoinJumpFlasher_SetArmed(g_carObjects[0], 0);
            ItemSelect_Reset(g_itemSelects[0], 0);
            g_finalRacePosition = ((ResultKart163 *)g_playerRenderObj)->position;
            RaceResult_StoreLatest(GetKartSlotCharId(s->slot), g_finalRacePosition, g_bestLapTime, g_totalRaceTime);
            g_raceResultCode = RaceResult_InsertSortedRank(GetKartSlotCharId(s->slot), g_finalRacePosition, g_bestLapTime, g_totalRaceTime);
            SetRaceResultLatestPtr(REG_ARGS1((void *)g_raceResultCode)); /* r3 still holds the rank just stored */
            Object_SetByte10_Return1(s->scene, 1);
            if (g_finalRacePosition == 0) {
                Jyugemu_Flag_SetKartDriver(s->flag, CarObject_GetRenderObj(g_carObjects[0]));
                KartMovement_ResetOnGoal(CarObject_GetRenderObj(g_carObjects[0]));
                fn_8016C554(1);
            } else {
                KartMovement_ResetOnTimeout(CarObject_GetRenderObj(g_carObjects[0]));
                fn_8016C554(0);
            }
            g_raceEnded = 1;
            g_lakituStartAnimDone = 0;
            CapTime(60.0f, s->time);
        } else if (g_lapChangePending) {
            if (g_finalLapBannerShown) {
                fn_8016C598();
                LapBannerScene_TriggerBannerAnim(s->banner);
            } else fn_8016C5CC();
            g_lapChangePending = 0;
        }
    }
    clItemBoxManager_Update(BoxManager());
    fn_8013A534();
    if (g_weatherSystem) fn_8016B32C(g_weatherSystem);
    if (s->time > 0.0f) s->time -= 1.0f;
    float duration = lbl_806D8060;
    float threshold = lbl_806D8904 - duration;
    float remaining = s->time;
    if (remaining > threshold)
        s->fade = Saturate_Double((remaining - threshold) / duration, 0.0f, 1.0f);
    else if (remaining < duration)
        s->fade = Saturate_Double(1.0f - remaining / duration, 0.0f, 1.0f);
    else s->fade = 0.0f;
    return 0;
}

extern "C" LoaderInit163 *fn_80164614(LoaderInit163 *s, int index, int record) {
    fn_80121210();
    DrawManager_GetOrCreate();
    fn_801E93A0();
    ReplayRandCursor_Reset(REG_ARGS1(0));
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
    g_cupId = demoEntries[index].cup;
    g_longRoundFlag = demoEntries[index].round;
    SetReverseRoundFlag(demoEntries[index].reverse);
    g_courseVariantIdx = demoEntries[index].variant;
    g_roundIndex = 0;
    lbl_806D1264[0] = 0x3d;
    lbl_806D1264[1] = 0x2b;
    lbl_806D1264[2] = 0x32;
    s->recording = record;
    ProcessSystemTick(0);
    DebugPrintf(demoSizeFormat, 43200);
    s->inputs = (TraceInput163 *)FUN_8003b120(43200);
    memset(s->inputs, 0, 43200);
    if (!s->recording) {
        DVDFile163 file;
        if (DVDOpen(demoEntries[index].file, &file)) {
            int size = file.length;
            DebugPrintf(demoFileSizeFormat, size);
            if (size > 0) {
                size = (size + 31) & ~31;
                void *buffer = OSAllocFromHeap(lbl_806CF010, size);
                if (buffer) {
                    int end = file.start + file.length - 1;
                    DVDLoad_WaitIfSamePage(file.start);
                    int count = DVDReadPrio(&file, buffer, size, 0, 2);
                    DVDLoad_RecordOpStart(end);
                    DebugPrintf(demoReadFormat, count);
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
    /* fakematch: the volatile reads reproduce the target reloading demoEntries[index].character
     * three times (natural code: plain demoEntries[index].character). */
    RaceSlot_InitSlot(VSMode_SeedRandomItemSequence(0, ((volatile const DemoEntry163 *)demoEntries)[index].character, 5), 0, ((volatile const DemoEntry163 *)demoEntries)[index].character, 1, 0);
    g_characterId = ((volatile const DemoEntry163 *)demoEntries)[index].character;
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
    s->child = new Camera163 ARGS_ORDER((512, 512, lbl_806D8908, lbl_806D890C, s->resource), (512, 512, s->resource, lbl_806D8908, lbl_806D890C));
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
        g_carObjects[0] = new Car163 ARGS_ORDER((0, GetKartSlotCharId(s->slot), x, z, GetCourseStartYaw(), 0, 0, 1, -1, 0, 0), (0, GetKartSlotCharId(s->slot), 0, 0, 1, -1, 0, 0, x, z, GetCourseStartYaw()));
    else
        g_carObjects[0] = new Car163 ARGS_ORDER((0, GetKartSlotCharId(s->slot), x, z, GetCourseStartYaw(), 0, 0, 0, -1, 0, 1), (0, GetKartSlotCharId(s->slot), 0, 0, 0, -1, 0, 1, x, z, GetCourseStartYaw()));
    char *render = (char *)CarObject_GetRenderObj(g_carObjects[0]);
    *(int *)(render + 0x238) = 1;
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
    s->object = new Lakitu163(demoLakituName, s->slot, lbl_806D88F0, lbl_806D88F0, lbl_806D88F0);
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
    g_sceneTransitionTimer = -1;
    g_itemSelects[0] = 0;
    g_itemSelects[1] = 0;
    g_itemSelects[2] = 0;
    g_itemSelects[3] = 0;
    char *variant = (char *)GetKartSlotKartVariant(s->slot);
    variant[0x2d0] = 1;
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
    FillDemoItemList();
    int *items = GetDemoItemList();
    for (int i = 0; items[i] != -1; i++) PreloadItemResources(items[i]);
    ProcessSystemTick(0);
    s->done = 0;
    s->ready = 0;
    s->time = lbl_806D8904;
    s->fade = lbl_806D88F0;
    s->heldItemFrames = 0;
    s->field58 = 0;
    return s;
}
