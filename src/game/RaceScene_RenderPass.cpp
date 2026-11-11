/* clGameSingle (0x800A0BE8..0x800A28D4): the race scene. The compiler emits
 * its vtable, base list and RTTI; deferred generation reverses method order. */
#include "game/types/arg_order.h"
/* RaceScene_Init (0x800A1D80): constructor of the race scene. Builds the
 * course, camera, player kart, path manager, Lakitu, HUD and the per-race
 * managers, logging the heap use after each step, then preloads the
 * effect and item resources the race can need.
 * The slot getter returns an int; the preload loop narrows it to a byte. */

#include "game/types/RaceParams.h"



#include "game/types/EnvironmentMgr.h"

#include "game/types/RaceCamera.h"

struct CarObject {
    unsigned char data[0x118];
    CarObject ARGS_ORDER((int displayIdx, int charId, float x, float y, float yaw, int ccClass, int variant, int human, int team, int local, int ghost), (int displayIdx, int charId, int ccClass, int variant, int human, int team, int local, int ghost, float x, float y, float yaw));
};

#include "game/types/PathManager.h"

struct LakituStart {
    unsigned char data[0x58];
    LakituStart(const char *name, int slot, float x, float y, float z);
};

struct Scene3D {
    unsigned char data[0x3084];
    Scene3D(const char *modelName);
};

struct JyugemuFlag {
    unsigned char data[0xC];
    JyugemuFlag(Scene3D *scene);
};

#include "game/types/JyugemuReverseFlag.h"

#include "game/types/FinalLapBanner.h"

#include "game/types/ObjCollChecker.h"

#include "game/types/AISystem.h"

#include "game/types/ItemSelect.h"

#include "game/types/WeatherSystem.h"

#include "game/types/RaceHud.h"

#include "game/types/SceneOverlay.h"




#include "game/types/SceneCamera.h"
#include "game/types/Vec.h"
#include "game/types/reg_args.h"
#include "game/singleton.h"
struct Deletable { virtual ~Deletable(); };
struct CarDeletable { virtual void v0(); virtual void Destroy(int); };
struct HsdClass {
    unsigned char pad0[0x30];
    void (*release)(void *obj);
    void (*destroy)(void *obj);
};
#include "game/types/HsdRefObj.h"
struct InputPlayer {
    virtual void v0(); virtual void v1(); virtual float Accel();
    virtual void v3(); virtual float Steer(); virtual float Brake();
    virtual unsigned char Pressed(int mask); virtual void v7();
    virtual unsigned int Held(int mask);
};
extern "C" {
extern const float RaceScene_rodata_803211D8[255] = {
    1.0f, 0.7f, 0.9f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f,
    66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f,
    66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f,
    66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f,
    0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f,
    66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f,
    66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f,
    66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f,
    66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f,
    66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f,
    0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f,
    66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f,
    66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f,
    66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f,
    66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f,
    66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f,
    0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f,
    66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f,
    66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f,
    83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f,
    83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f,
    83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f,
    0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f,
    83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f,
    83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f,
    83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f,
    83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f,
    83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f,
    83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f
};
extern const Vec RaceScene_FrameUpdate_rodata_803215D4 = { 0.0f, 0.0f, 0.0f };
extern const Vec RaceScene_FrameUpdate_rodata_803215E0 = { 0.0f, 0.0f, 0.0f };

}

struct clGameWorld {
    clGameWorld() {}
    virtual ~clGameWorld() {}
};
class clGameSingle : public clGameWorld {
public:
    clGameSingle();
    virtual ~clGameSingle();
    virtual int Update();
    virtual void Draw();
    LakituStart *lakitu;
    JyugemuFlag *jyugemuFlag;
    JyugemuReverseFlag *jyugemuReverse;
    FinalLapBanner *lapBanner;
    EnvironmentMgr *environment;
    void *pad18;
    Scene3D *scene;
    void *pad20[2];
    RaceCamera *camera;
    RaceHud *hud;
    void *pad30;
    AISystem *ai;
    ObjCollChecker *coll;
    SceneOverlay *overlay;
};

extern "C" {

extern const char lbl_806D4800[4];  /* "map" */
extern const char lbl_806D4804[6];  /* "light" */
extern const char lbl_806D480C[8];  /* "itembox" */
extern const char lbl_806D4814[5];  /* "coin" */
extern const char lbl_806D481C[7];  /* "center" */
extern const char lbl_806D4828[8];  /* "sprite2" */
extern const float lbl_806D47DC;
extern const float lbl_806D47E0;
extern const float lbl_806D47EC;
extern const float lbl_806D47F4;
extern const float lbl_806D4824;
extern RaceParams kRaceParamsTable[][3][2];

extern int *HSD_RandSeedPtr;
extern int g_raceSceneContextSwitch;
extern int lbl_806D1110;
extern int g_gameMode;
extern unsigned char g_isCommHost;
extern int g_spawnedKartCount;
extern unsigned char g_finalLapCoinJumpEnabled;
extern int lbl_806D1050;
extern int g_cupId;
extern int g_longRoundFlag;
extern int g_reverseRoundFlag;
extern int g_ccClass;
extern int g_kartVariant;
extern int g_playerKartSlot;
extern int g_kartStartSlot;
extern HsdRefObj *g_raceRenderTarget;
extern RaceCamera *g_raceCamera;
extern CarObject *g_carObjects[4];
extern ItemSelect *g_itemSelects[4];
extern unsigned char g_playerData[];
extern unsigned char g_namCamFlag;
extern void *g_playerRenderObj;
extern PathManager *g_pathManager;
extern unsigned char g_lakituDropOrderIssued;
extern unsigned char g_lakituStartAnimDone;
extern ObjCollChecker *g_objCollChecker;
extern int g_sceneTransitionTimer;
extern int lbl_806CF110;
extern unsigned char lbl_806D1264[3];
extern unsigned char g_raceEnded;
extern int g_raceEndExitTimer;
extern unsigned char g_rendererActivated;
extern int g_finalRacePosition;
extern float g_bestLapTime;
extern float g_currentLapTime;
extern float g_totalRaceTime;
extern int g_currentLap;
extern int g_raceResultCode;
extern unsigned char g_finalLapBannerShown;
extern unsigned char g_lapChangePending;
extern int g_totalLaps;
extern float g_raceTimeRemaining;
extern float g_lapBonusTimeDelta;
extern WeatherSystem *g_weatherSystem;
extern int g_raceFrameCounterLo2digits;
extern int g_roundIndex;
extern RaceHud *g_raceHud;
extern unsigned char g_fullThrottleHoldFlag;
extern unsigned int g_prevFrameTimestampLo;
extern unsigned int g_prevFrameTimestampHi;
extern int g_humanPlayerCount;
extern PathManager *g_raceRankingPathObject;

void SetSyncTarget(int target);
void ItemUse_ResetAllKartUseSlots(void);
void RaceScene_ClearPlayerSlotPointers(void);
void ProcessSystemTick(const char *msg);
void VoiceSystem_Init(void);
void SetResourceLoadingFlag(int flag);
void DMAChannelManager_Init(void);
int HeapStats_DumpForTag(const char *tag, int prev);
void TransitionEffect_GetOrCreate(void);
void SoundChannels_ClearAll(void);
void ItemObjectManager_Init(void);
void CourseObjectManager_Init(void);
void *CourseData_GetOrCreate(int cup, int longRound, int reverse);
void *GetCourseDataPtr(void);
HsdRefObj *HSD_LObjLoadDesc(void *desc);
void SetActiveCamera(int index, RaceCamera *cam);
void *GetRaceContextPtr(void);
void RankingTable_Init(void *ctx);
void *GetCourseBgmEntry(void);
void SoundDriver_GetOrCreate(void *entry);
void CoinSystem_Init(int a, int b);
int GetDisplayBufferIndex(void);
int GetKartStartSlot(int displayIdx);
void GetStartPosition(int slot, float *x, int flag, float *y);
float GetCourseStartYaw(void);
int GetKartSlotCharId(int slot);
void *CarObject_GetRenderObj(CarObject *car);
void KartItem_SetShortArray34a(void *renderObj, unsigned char *playerData);
void VoiceSystem_BindKartCarObject(int slot, CarObject *car);
void KartItem_SetField358(void *renderObj, int displayIdx);
void SetPlayerCarObject(CarObject *car);
float *CarObject_GetTransformMatrix(CarObject *car);
void *CourseData_GetDefaultPathKey_Safe(void);
void LakituStart_SetCountdownHoldFrames(LakituStart *lakitu, int frames);
const char **GetKartModelNameEntry(int charId, int variant);
void Scene3D_GetCameraPos(Scene3D *scene, float *x, float *y);
void Scene3D_SetupProjection(Scene3D *scene, float x, float y);
float RaceScene_GetPerspFovyForCup(void);
void CObj_UpdatePerspParam(Scene3D *scene, float fovy);
unsigned char *GetKartSlotKartVariant(int slot);
void ItemSelect_AddSlotItem(ItemSelect *sel, int item, int flag);
void SetCourseScene3D(Scene3D *scene);
void CourseBgm_Load(void);
void PreloadEffectResources(int set);
int ItemSelect_GetSlotItemId(ItemSelect *sel, int slot);
void PreloadItemResources(int item);
int fn_8023DBEC(int item);
void PreloadResource(int id);
void *GetEnemyParam(void);
void clEnemyParam_FillItemListIds(void *param, int mode, int cup, int round);
int *AI_GetItemList(void *param, int mode, int cup, int round, int index);
void PlayStats_OnRaceSceneInit_Stub(void);
void DebugPrintf(const char *fmt, ...);
void Tachometer_Init(void);
void HitMessageOverlay_Init(void);
void HUD_RegisterOverlay(RaceHud *hud, int id, int flag);
void fn_80253EB8(RaceHud *hud, float scale);
void HUD_SetTotalLaps(RaceHud *hud, int laps);
long long OSGetTime(void);
int TEXPalette_GetTotalLoadedSize(void);
int fn_80209A84(void);
void VoiceSystem_SetCheckpointsForTotalLaps(int laps);
void VoiceQueue_Clear(int flag);

extern int g_currentSceneState;
extern void *lbl_806D10A0;
extern Deletable *lbl_806D109C;
extern Deletable *lbl_806D10D0;
extern Vec RaceScene_FrameUpdate_bss_805D2B10;
extern Vec RaceScene_FrameUpdate_bss_805D2B1C;
extern unsigned char g_rendererGateFlag;
extern unsigned char g_nonFirstFinishFlag;
extern unsigned char lbl_806CF270;
extern unsigned char lbl_806D0051;

void Race_PerFrameTickAndAudio(void);
unsigned char Live_IsConnectReady(void);
unsigned char fn_8020B07C(void *overlay);
void fn_8020AF08(void *overlay, int flag);
int rand(void);
void PathManager_RefreshFinishPositions(void *path);
void TitleStats_FinalizeRace_WithRankSnapshot(void *stats);
void *GetInputManager(void);
InputPlayer *InputMgr_GetPlayer(void *mgr, int index);
void ItemObjectManager_PerFrameUpdate(void *ctx);
unsigned char IsRaceStarted(void);
float CalcSoundDirection(void *render, void *path, float *steer, int flag);
#ifdef __MWERKS__
void CarObject_ApplyInput(void *car, float accel, float steer, float brake, unsigned char started);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void CarObject_ApplyInput(void *, unsigned char, float, float, float);
static inline void CarObject_ApplyInput_Reordered(void * a0, float a1, float a2, float a3, unsigned char a4) { CarObject_ApplyInput(a0, a4, a1, a2, a3); }
#define CarObject_ApplyInput CarObject_ApplyInput_Reordered
#endif
void CarObject_FrameUpdate(void *car, unsigned int held);
void ItemBox_ProcessPickup(void *sel, void *car, int a, unsigned int held, int b, float steer);
int GetCoinMilage(unsigned char *playerData);
void CoinJumpFlasher_Toggle(void *car);
void RankingMgr_UpdatePositions(void *ai);
float *Path_LookupCheckpointOffset(void *path, int a, int b);
unsigned char JObj_IsForwardDotBelowThreshold(void *render, Vec *a, Vec *b);
void Jyugemu_ReverseFlag_SetState(void *flag, int state);
void fn_801B3BC8(void *p);
void fn_801B3B7C(void *p);
void TitleStats_AccumDistanceCounter(void *stats, int display, int reverse);
void fn_80208E30(void *coll);
void KartItem_UpdateShadowBillboardAndViewport(void *car, void *scene, int flag);
void Fog_UpdateFromCourseScene3D(void);
void PathManager_UpdateAll(void *path);
unsigned char LakituStart_UpdateCountdown(void *lakitu);
void LakituStart_Dtor(void *lakitu, int flag);
void Jyugemu_Flag_Tick(void *flag);
void Jyugemu_ReverseFlag_Tick(void *flag);
void LapBannerScene_UpdateAndDriveAnim(void *banner);
void CourseEnvironment_UpdateAndCullZones_Timed(void *env);
void CObj_LoadProjMatrix(void *scene, Vec *v);
void CObj_ApplyScissor(void *scene, Vec *v);
void ItemObjectManager_Update(void);
#ifdef __MWERKS__
void VfxSlotMgr_Update(Vec a, Vec b);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void VfxSlotMgr_Update(Vec *, Vec *);
static inline void VfxSlotMgr_Update_ByValue(Vec a, Vec b) { VfxSlotMgr_Update(&a, &b); }
#define VfxSlotMgr_Update VfxSlotMgr_Update_ByValue
#endif
void fn_80253BE4(void *hud);
void fn_8016C554(int flag);
void fn_801B12A0(void);
void Tachometer_RenderDigits(void);
void HitMessageOverlay_FrameUpdate(void);
void HUD_SetCurrentLap(void *hud, int lap);
void fn_80253FD8(void *hud, float time);
float CarObject_CalcSpeedRatio(void *car);
void fn_80253EBC(void *hud, float v);
float KartItem_GetCurrentSpeedWithBonus(void *car);
void fn_80253EC0(void *hud, float v);
void fn_80253EC4(void *hud, float v);
void fn_80253F2C(void *hud, float v);
void HUD_SetRacePosition(void *hud, int pos);
void fn_80253E18(void *hud, int v);
void TransitionEffect_Tick(void *fx);
void fn_80253DF0(void *hud);
void KartItem_OnFallOffOrDeath(void *car);
void CoinJumpFlasher_SetArmed(void *car, int armed);
void ItemSelect_Reset(void *sel, int flag);
void RaceResult_StoreLatest(int charId, int pos, float best, float total);
int RaceResult_InsertSortedRank(int charId, int pos, float best, float total);
void SetRaceResultLatestPtr(REG_ARGS1(void *p));
void fn_801D680C(unsigned char *playerData, int cup, int round, int win);
void fn_801D67F4(unsigned char *playerData);
void fn_80253D00(void *hud);
void Object_SetByte10_Return1(void *scene, int v);
void Jyugemu_Flag_SetKartDriver(void *flag, void *render);
void PlayStats_OnRace1stPlace_Stub(void);
void CoinEvent_PlayResultSE(void *car, int pos);
void RankLog_SetRaceResult(void *stats, int display, int pos, int time);
void fn_8016C598(void);
void LapBannerScene_TriggerBannerAnim(void *banner);
void fn_8016C5CC(void);
void TitleTracker_ResetPerRound(void *stats, int display, int lap);
void HUD_FrameUpdate(void *hud);
void clItemBoxManager_Update(void *mgr);
void fn_8013A534(void);
void fn_8016B32C(void *weather);

extern void *lbl_806D10AC;
extern unsigned int lbl_806DC178;
extern unsigned int lbl_806DC17C;
extern unsigned int lbl_806DC180;
extern unsigned int lbl_806DC184;
extern unsigned int lbl_806DC188;
extern unsigned int lbl_806DC18C;
extern unsigned int lbl_806DC190;
extern unsigned int lbl_806DC194;
extern unsigned int lbl_806DC198;
extern unsigned int lbl_806DC19C;
extern unsigned int lbl_806DC1A0;
extern unsigned int lbl_806DC1A4;
extern unsigned int lbl_806DC1A8;
extern unsigned int lbl_806DC1AC;
extern unsigned int lbl_806DC1B0;
extern unsigned int lbl_806DC1B4;
extern unsigned int lbl_806DC1B8;

void clDrawMan_Buckets_Reset(void *mgr);
void TransparentDraw_SortAndDispatch(void);
void CObj_DebugVizPathFlush(SceneCamera *cam);
void fn_8016B0C4(void);
void IsTimerModeEnabled(void);
void Stub_NoOp_80030aec(SceneCamera *cam);
void Object_RenderJObjIfWithinRange(void *obj);
void Jyugemu_Flag_Render(void *p);
void Jyugemu_ReverseFlag_Render(void *p);
void LapBannerScene_RenderIfActive(void *p);
void CourseEnvironment_RenderObjects_Timed(void *p);
void Subsystem36c_DispatchPass2_Timed(void *p);
void Subsystem36c_DispatchPass4_Timed(void *p);
void fn_801EB91C(void *p, int flag);
void fn_80208E2C(void *p);
void NoopRenderHook_Pending_80064d28(void);
void ItemObjectManager_Render(void);
void DrawEffect_TickAndCull(void);
void KartItem_TriggerStateAction(void *kart);
void KartItem_IsAtStartSlot(void *kart);
void KartItem_RenderPipelinedWithEffects(void *car, int flag);
void fn_80139810(void);
void clItemBoxManager_Draw(void *mgr);
void clDrawMan_EndFrame_NoOp(void *mgr);
void clDrawMan_Buckets_Dispatch(void *mgr);
void TransitionEffect_RenderPass(void *fx, int pass);
void fn_80253448(void *hud, unsigned int layers);
void ItemSelect_DrawUIHelperIfActive(void *sel);
void fn_8020AFD4(void *p);
void HSD_StateInvalidate(int mask);

extern Deletable *g_courseData;

void fn_801B6B94(void);
void fn_8016C634(void *p, int flag);
void AI_SystemDtor(void *p, int flag);
void fn_80208FE4(void *p, int flag);
void ItemSelect_Dtor(void *p, int flag);
void Tachometer_Destroy(void);
void HitMessageOverlay_Destroy(void);
void fn_80254134(void *p, int flag);
void Jyugemu_Flag_Dtor(void *p, int flag);
void Jyugemu_ReverseFlag_Dtor(void *p, int flag);
void LapBannerScene_Dtor(void *p, int flag);
void PathParticipantArray_Dtor(void *p, int flag);
void CourseEnvironment_Dtor(void *p, int flag);
void ItemObjectManager_Reset(void);
void VfxSlotMgr_Shutdown(void);
void ClRomTable_PurgeAll(void);
void fn_8013A6F8(void);
void CourseBgm_Free(void);
void SceneDrawList_Reset(void);
void clRom_PurgeAll(void);
void MemoryManager_TimedFree(void *p);
}
#ifndef __MWERKS__
extern "C" {
extern const float lbl_806D47DC = 0.1f;
extern const float lbl_806D47E0 = 1000.0f;
extern const float lbl_806D47EC = 0.0f;
extern const float lbl_806D47F4 = 100.0f;
}
#endif

static inline void *DrawMan() { return SINGLETON_INSTANCE(lbl_806D10AC); }

static inline void *ItemBoxMgr() { return SINGLETON_INSTANCE(lbl_806D10D0); }

static inline void *Transition() { return SINGLETON_INSTANCE(lbl_806D109C); }

static inline void *TitleStats(void)
{
    return SINGLETON_INSTANCE(lbl_806D10A0);
}

static inline float QuantizeInput(float v)
{
    return (float)(int)(10000.0f * v) / 10000.0f;
}

static inline int HsdRef_Dec(HsdRefObj *o)
{
    int done = o->ref == (unsigned short)-1;
    if (done) {
        return done;
    }
    return o->ref-- == 0;
}

static inline void HsdRef_Unref(HsdRefObj *o)
{
    if (o == 0) {
        return;
    }
    if (HsdRef_Dec(o)) {
        if (o != 0) {
            o->klass->release(o);
            o->klass->destroy(o);
        }
    }
}

static inline int CcClass_Get(void)
{
    return g_ccClass;
}

static inline int KartVariant_Get(void)
{
    return g_kartVariant;
}

static inline int GameMode_Get(void)
{
    return g_gameMode;
}

static inline int CupId_Get(void)
{
    return g_cupId;
}

static inline int RoundIndex_Get(void)
{
    return g_roundIndex;
}

static inline void PreloadItem(int item)
{
    PreloadItemResources(item);
    PreloadResource(fn_8023DBEC(item));
}

static inline void KartRender_SetItemSelect(void *render, ItemSelect *sel)
{
    *(ItemSelect **)((char *)render + 0x364) = sel;
}

clGameSingle::clGameSingle()
{
    int heap;
    float startX;
    float startY;
    int i;

    HSD_RandSeedPtr = &g_raceSceneContextSwitch;
    *HSD_RandSeedPtr = lbl_806D1110;
    g_gameMode = 0;
    SetSyncTarget(0x2A);
    g_isCommHost = 0;
    g_spawnedKartCount = 6;
    ItemUse_ResetAllKartUseSlots();
    g_finalLapCoinJumpEnabled = 0;
    lbl_806D1050 = 0;
    RaceScene_ClearPlayerSlotPointers();
    ProcessSystemTick("OK clGame::setting()");
    VoiceSystem_Init();
    ProcessSystemTick("OK clLiveInit()");
    SetResourceLoadingFlag(0);
    DMAChannelManager_Init();
    heap = HeapStats_DumpForTag("clLightManager::init()", 0);
    TransitionEffect_GetOrCreate();
    SoundChannels_ClearAll();
    heap = HeapStats_DumpForTag("clScreenEffect() & clEffectManager()", heap);
    ProcessSystemTick("OK ObjectWorkInit & EffectWorkInit");
    ItemObjectManager_Init();
    heap = HeapStats_DumpForTag("ObjectWorkInit()", heap);
    CourseObjectManager_Init();
    heap = HeapStats_DumpForTag("EffectWorkInit()", heap);
    environment = new EnvironmentMgr;
    heap = HeapStats_DumpForTag(lbl_806D4800, heap);
    CourseData_GetOrCreate(g_cupId, g_longRoundFlag, g_reverseRoundFlag);
    heap = HeapStats_DumpForTag("map manager", heap);
    g_raceRenderTarget = HSD_LObjLoadDesc(GetCourseDataPtr());
    heap = HeapStats_DumpForTag(lbl_806D4804, heap);
    camera = new RaceCamera ARGS_ORDER((lbl_806D47E0, 0x200, lbl_806D47DC, 0x200, g_raceRenderTarget), (0x200, 0x200, g_raceRenderTarget, lbl_806D47E0, lbl_806D47DC));
    SetActiveCamera(0, camera);
    g_raceCamera = camera;
    heap = HeapStats_DumpForTag("clGame::shadow()", heap);
    ProcessSystemTick("OK shadow!");
    RankingTable_Init(GetRaceContextPtr());
    SoundDriver_GetOrCreate(GetCourseBgmEntry());
    heap = HeapStats_DumpForTag(lbl_806D480C, heap);
    CoinSystem_Init(0, 2);
    heap = HeapStats_DumpForTag(lbl_806D4814, heap);
    g_playerKartSlot = GetKartStartSlot(GetDisplayBufferIndex());
    g_kartStartSlot = g_playerKartSlot;
    GetStartPosition(g_playerKartSlot, &startX, 0, &startY);
    g_carObjects[0] = new CarObject ARGS_ORDER((GetDisplayBufferIndex(), GetKartSlotCharId(g_playerKartSlot), startX, startY, GetCourseStartYaw(), CcClass_Get(), KartVariant_Get(), 1, -1, 1, 0), (GetDisplayBufferIndex(), GetKartSlotCharId(g_playerKartSlot), CcClass_Get(), KartVariant_Get(), 1, -1, 1, 0, startX, startY, GetCourseStartYaw()));
    {
        char *render = (char *)CarObject_GetRenderObj(g_carObjects[0]);
        *(int *)(render + 0x238) = 1;
    }
    KartItem_SetShortArray34a(CarObject_GetRenderObj(g_carObjects[0]), g_playerData);
    VoiceSystem_BindKartCarObject(g_playerKartSlot, g_carObjects[0]);
    if (g_namCamFlag) {
        KartItem_SetField358(CarObject_GetRenderObj(g_carObjects[0]), GetDisplayBufferIndex());
    }
    g_playerRenderObj = CarObject_GetRenderObj(g_carObjects[0]);
    heap = HeapStats_DumpForTag("player car", heap);
    ProcessSystemTick("OK Player car");
    SetPlayerCarObject(g_carObjects[0]);
    {
        float *m = CarObject_GetTransformMatrix(g_carObjects[0]);
        g_pathManager = new PathManager(CourseData_GetDefaultPathKey_Safe(), g_carObjects[0],
                                        CarObject_GetRenderObj(g_carObjects[0]), &m[12], &m[13], &m[14]);
    }
    heap = HeapStats_DumpForTag(lbl_806D481C, heap);
    lakitu = new LakituStart("jyugemu_start.dat", g_playerKartSlot, lbl_806D47EC, lbl_806D47EC, lbl_806D47EC);
    LakituStart_SetCountdownHoldFrames(lakitu, 10000);
    scene = new Scene3D(*GetKartModelNameEntry(GetKartSlotCharId(g_playerKartSlot), -1));
    jyugemuFlag = new JyugemuFlag(scene);
    jyugemuReverse = new JyugemuReverseFlag(CarObject_GetRenderObj(g_carObjects[0]));
    lapBanner = new FinalLapBanner(CarObject_GetRenderObj(g_carObjects[0]));
    heap = HeapStats_DumpForTag("jugemu camera", heap);
    g_lakituDropOrderIssued = 0;
    ProcessSystemTick("OK jugemu & etc!!");
    {
        float x;
        float y;
        Scene3D_GetCameraPos(scene, &x, &y);
        x += lbl_806D4824;
        Scene3D_SetupProjection(scene, x, y);
    }
    CObj_UpdatePerspParam(scene, RaceScene_GetPerspFovyForCup());
    g_lakituStartAnimDone = 0;
    coll = new ObjCollChecker;
    heap = HeapStats_DumpForTag("clObjCollChecker", heap);
    g_objCollChecker = coll;
    ai = new AISystem(g_pathManager, coll, 0);
    heap = HeapStats_DumpForTag("clEnemyThinkManager", heap);
    ProcessSystemTick("OK clEnemyThinkManager()!");
    g_sceneTransitionTimer = -1;
    heap = HeapStats_DumpForTag(lbl_806D4828, heap);
    g_itemSelects[0] = 0;
    g_itemSelects[1] = 0;
    g_itemSelects[2] = 0;
    g_itemSelects[3] = 0;
    {
        unsigned char *variant = GetKartSlotKartVariant(g_playerKartSlot);
        variant[0x2D0] = 1;
    }
    g_itemSelects[0] = new ItemSelect(g_playerKartSlot, 1);
    heap = HeapStats_DumpForTag("itemSelect", heap);
    *(ItemSelect **)((char *)g_carObjects[0] + 0x104) = g_itemSelects[0];
    KartRender_SetItemSelect(CarObject_GetRenderObj(g_carObjects[0]), g_itemSelects[0]);
    if (lbl_806CF110 == 1) {
        ItemSelect_AddSlotItem(g_itemSelects[0], lbl_806D1264[0], 1);
        ItemSelect_AddSlotItem(g_itemSelects[0], lbl_806D1264[1], 1);
        ItemSelect_AddSlotItem(g_itemSelects[0], lbl_806D1264[2], 1);
    } else {
        ItemSelect_AddSlotItem(g_itemSelects[0], lbl_806D1264[0], 1);
        ItemSelect_AddSlotItem(g_itemSelects[0], 0x3D, 1);
        ItemSelect_AddSlotItem(g_itemSelects[0], 0x2B, 1);
        ItemSelect_AddSlotItem(g_itemSelects[0], 0x17, 1);
        ItemSelect_AddSlotItem(g_itemSelects[0], 0x32, 1);
    }
    ProcessSystemTick("OK sprite item!");
    SetCourseScene3D(scene);
    {
        g_raceEnded = 0;
        g_raceEndExitTimer = 0;
        g_rendererActivated = 0;
        g_finalRacePosition = 6;
        g_bestLapTime = lbl_806D47EC;
        g_currentLapTime = lbl_806D47EC;
        g_totalRaceTime = lbl_806D47EC;
        g_currentLap = 1;
        g_raceResultCode = -2;
        g_finalLapBannerShown = 0;
        g_lapChangePending = 0;
        g_totalLaps = kRaceParamsTable[g_cupId - 1][g_ccClass][g_longRoundFlag].laps;
        g_raceTimeRemaining = kRaceParamsTable[g_cupId - 1][g_ccClass][g_longRoundFlag].timeLimit;
        g_lapBonusTimeDelta = kRaceParamsTable[g_cupId - 1][g_ccClass][g_longRoundFlag].lapBonus;
    }
    ProcessSystemTick("OK TIME setting!");
    CourseBgm_Load();
    if (g_weatherSystem == 0) {
        g_weatherSystem = new WeatherSystem(1);
    }
    SetResourceLoadingFlag(1);
    g_raceFrameCounterLo2digits = 0;
    switch (g_cupId) {
    case 1:
        PreloadEffectResources(1);
        break;
    case 2:
        PreloadEffectResources(2);
        break;
    case 3:
        PreloadEffectResources(3);
        break;
    case 4:
        PreloadEffectResources(4);
        break;
    case 5:
        PreloadEffectResources(5);
        break;
    case 6:
        PreloadEffectResources(6);
        break;
    case 7:
        PreloadEffectResources(7);
        break;
    case 8:
        PreloadEffectResources(8);
        break;
    }
    ProcessSystemTick("OK etc course effect file load!");
    PreloadEffectResources(9);
    ProcessSystemTick("OK effect_LoadData(EF_KART);");
    PreloadEffectResources(10);
    ProcessSystemTick("OK effect_LoadData(EF_ITEM);");
    for (i = 0; i < (lbl_806CF110 == 1 ? 3 : 5); i++) {
        unsigned char item = ItemSelect_GetSlotItemId(g_itemSelects[0], i);
        if (item != 0) {
            PreloadItemResources(item);
            PreloadResource(fn_8023DBEC(item));
        }
    }
    ProcessSystemTick("OK Player Item Model load!");
    clEnemyParam_FillItemListIds(GetEnemyParam(), GameMode_Get(), CupId_Get(), RoundIndex_Get());
    for (i = 0; i < 6; i++) {
        int *list = AI_GetItemList(GetEnemyParam(), GameMode_Get(), CupId_Get(), RoundIndex_Get(), i);
        while (*list != -1) {
            PreloadItemResources(*list);
            PreloadResource(fn_8023DBEC(*list));
            list++;
        }
    }
    ProcessSystemTick("OK ENEMY Item Model load!");
    SetSyncTarget(0x2C);
    PlayStats_OnRaceSceneInit_Stub();
    DebugPrintf("---LOAD SPRITE ---------------------------------\n");
    Tachometer_Init();
    HitMessageOverlay_Init();
    hud = new RaceHud(g_pathManager);
    g_raceHud = hud;
    HUD_RegisterOverlay(hud, 6, 0);
    HUD_RegisterOverlay(hud, 3, 0);
    HUD_RegisterOverlay(hud, 5, 0);
    HUD_RegisterOverlay(hud, 1, 0);
    HUD_RegisterOverlay(hud, 2, 0);
    HUD_RegisterOverlay(hud, 0xA, 0);
    HUD_RegisterOverlay(hud, 0xC, 0);
    HUD_RegisterOverlay(hud, 0xB, 0);
    HUD_RegisterOverlay(hud, 7, 0);
    HUD_RegisterOverlay(hud, 0, 0);
    HUD_RegisterOverlay(hud, 0xF, 0);
    HUD_RegisterOverlay(hud, 0x10, 0);
    HUD_RegisterOverlay(hud, 0xE, 0);
    HUD_RegisterOverlay(hud, 4, 0);
    HUD_RegisterOverlay(hud, 0xD, 0);
    fn_80253EB8(hud, lbl_806D47F4);
    HUD_RegisterOverlay(hud, 8, 0);
    HUD_RegisterOverlay(hud, 9, 0);
    HUD_SetTotalLaps(hud, g_totalLaps);
    HUD_RegisterOverlay(hud, 0x15, 0);
    ProcessSystemTick("OK sprite cdisp()");
    DebugPrintf("---RACE ----------------------------------------\n");
    g_fullThrottleHoldFlag = 0;
    {
        long long t = OSGetTime();
        g_prevFrameTimestampLo = (unsigned int)t;
        g_prevFrameTimestampHi = (unsigned int)(t >> 32);
    }
    {
        int texSize = TEXPalette_GetTotalLoadedSize();
        DebugPrintf("spr size is %d\n", texSize);
    }
    ProcessSystemTick("OK live setting");
    g_humanPlayerCount = fn_80209A84();
    overlay = new SceneOverlay(0x168);
    VoiceSystem_SetCheckpointsForTotalLaps(g_totalLaps);
    g_raceRankingPathObject = g_pathManager;
    VoiceQueue_Clear(0);
}

clGameSingle::~clGameSingle()
{

        fn_801B6B94();
        if (g_weatherSystem != 0) {
            fn_8016C634(g_weatherSystem, 1);
            g_weatherSystem = 0;
        }
        SetActiveCamera(0, 0);
        if (this->overlay != 0) {
            fn_8020AF08(this->overlay, 1);
            this->overlay = 0;
        }
        ProcessSystemTick("OK Prize free!");
        AI_SystemDtor(this->ai, 1);
        fn_80208FE4(this->coll, 1);
        ProcessSystemTick("coll free!");
        ItemSelect_Dtor(g_itemSelects[0], 1);
        Tachometer_Destroy();
        HitMessageOverlay_Destroy();
        ProcessSystemTick("citemsel tachometer hitface free!");
        fn_80254134(this->hud, 1);
        delete (Deletable *)this->scene;
        LakituStart_Dtor(this->lakitu, 1);
        Jyugemu_Flag_Dtor(this->jyugemuFlag, 1);
        Jyugemu_ReverseFlag_Dtor(this->jyugemuReverse, 1);
        LapBannerScene_Dtor(this->lapBanner, 1);
        PathParticipantArray_Dtor(g_pathManager, 1);
        ProcessSystemTick("car shadow free!");
        if (g_carObjects[0] != 0) {
            ((CarDeletable *)g_carObjects[0])->Destroy(1);
        }
        if (this->camera != 0) {
            delete (Deletable *)this->camera;
        }
        CourseEnvironment_Dtor(this->environment, 1);
        ProcessSystemTick("car shadow map free!");
        if (g_raceRenderTarget != 0) {
            HsdRef_Unref(g_raceRenderTarget);
            g_raceRenderTarget = 0;
        }
        ItemObjectManager_Reset();
        VfxSlotMgr_Shutdown();
        RankingTable_Init(GetRaceContextPtr());
        ClRomTable_PurgeAll();
        this->lakitu = 0;
        this->jyugemuFlag = 0;
        this->jyugemuReverse = 0;
        this->lapBanner = 0;
        g_carObjects[0] = 0;
        g_pathManager = 0;
        this->scene = 0;
        this->environment = 0;
        SetPlayerCarObject(0);
        delete lbl_806D10D0;
        lbl_806D10D0 = 0;
        fn_8013A6F8();
        g_raceCamera = 0;
        CourseBgm_Free();
        SceneDrawList_Reset();
        delete lbl_806D109C;
        lbl_806D109C = 0;
        delete g_courseData;
        g_courseData = 0;
        ProcessSystemTick("effect autorun light free!");
        SetResourceLoadingFlag(0);
        clRom_PurgeAll();
        SetCourseScene3D(0);
        ProcessSystemTick("all rom free!");
}

int clGameSingle::Update()
{
    InputPlayer *pad;
    float steer;
    float accel;
    float brake;
    unsigned int held;
    unsigned char started;

    Race_PerFrameTickAndAudio();
    if (!g_lakituDropOrderIssued && Live_IsConnectReady()) {
        g_lakituDropOrderIssued = 1;
        if (this->lakitu != 0) {
            LakituStart_SetCountdownHoldFrames(this->lakitu, -1);
        }
    }
    if (this->overlay != 0 && fn_8020B07C(this->overlay)) {
        fn_8020AF08(this->overlay, 1);
        this->overlay = 0;
    }

    g_raceFrameCounterLo2digits = rand() % 100;
    if (g_currentSceneState == 0x2D) {
        if (Live_IsConnectReady()) {
            if (--g_sceneTransitionTimer <= 0) {
                PathManager_RefreshFinishPositions(g_pathManager);
                void *stats = TitleStats();
                if (stats != 0) {
                    TitleStats_FinalizeRace_WithRankSnapshot(stats);
                }
                return 0xD;
            }
        } else {
            g_sceneTransitionTimer = 0xB4;
        }
    }
    if (g_currentSceneState != 0x2D && g_sceneTransitionTimer > 0) {
        if (--g_sceneTransitionTimer <= 0) {
            g_sceneTransitionTimer = 0xB4;
            SetSyncTarget(0x2D);
        }
    }

    pad = InputMgr_GetPlayer(GetInputManager(), 0);
    ItemObjectManager_PerFrameUpdate(GetRaceContextPtr());
    if (g_raceEnded != 1) {
        unsigned long long now = OSGetTime();

        steer = QuantizeInput(pad->Steer());
        brake = QuantizeInput(pad->Brake());
        if (g_ccClass != 2) {
            if (!IsRaceStarted()) {
                g_prevFrameTimestampLo = (unsigned int)now;
                g_prevFrameTimestampHi = (unsigned int)(now >> 32);
            } else if (steer < 0.1f && brake < 0.1f) {
                if (!g_fullThrottleHoldFlag) {
                    long long prev = ((long long)g_prevFrameTimestampHi << 32) | g_prevFrameTimestampLo;
                    long long ms = (long long)(now - prev) / ((*(unsigned int *)0x800000F8 / 4) / 1000);
                    if ((float)ms / 1000.0f >= 4.0f) {
                        g_fullThrottleHoldFlag = 1;
                    }
                }
                if (g_fullThrottleHoldFlag) {
                    steer = 1.0f;
                }
            } else {
                g_prevFrameTimestampLo = (unsigned int)now;
                g_fullThrottleHoldFlag = 0;
                g_prevFrameTimestampHi = (unsigned int)(now >> 32);
            }
        }
        accel = QuantizeInput(pad->Accel());
        started = IsRaceStarted();
        held = pad->Held(0xE7FF);
    } else {
        accel = CalcSoundDirection(CarObject_GetRenderObj(g_carObjects[0]), g_pathManager, &steer, 0);
        brake = 0.0f;
        started = 1;
        held = 0;
    }
    CarObject_ApplyInput(g_carObjects[0], accel, steer, brake, started);
    CarObject_FrameUpdate(g_carObjects[0], held);
    ItemBox_ProcessPickup(g_itemSelects[0], g_carObjects[0], 0, held, 1, steer);
    if (!g_raceEnded && pad->Held(0x400) && GetCoinMilage(g_playerData) >= 4000) {
        CoinJumpFlasher_Toggle(g_carObjects[0]);
    }
    RankingMgr_UpdatePositions(this->ai);

    if (IsRaceStarted() == 1) {
        float *cp0 = Path_LookupCheckpointOffset(g_pathManager, 0, 0);
        float *cp1 = Path_LookupCheckpointOffset(g_pathManager, 0, 1);
        Vec a = RaceScene_FrameUpdate_rodata_803215D4;
        a.x = cp0[1];
        a.z = cp0[3];
        Vec b = RaceScene_FrameUpdate_rodata_803215E0;
        b.x = cp1[1];
        b.z = cp1[3];
        if (JObj_IsForwardDotBelowThreshold(CarObject_GetRenderObj(g_carObjects[0]), &a, &b) == 1) {
            Jyugemu_ReverseFlag_SetState(this->jyugemuReverse, 1);
            fn_801B3BC8(*(void **)((char *)CarObject_GetRenderObj(g_carObjects[0]) + 0x248));
            void *stats = TitleStats();
            if (stats != 0) {
                TitleStats_AccumDistanceCounter(stats, GetDisplayBufferIndex(), 1);
            }
        } else {
            Jyugemu_ReverseFlag_SetState(this->jyugemuReverse, 0);
            fn_801B3B7C(*(void **)((char *)CarObject_GetRenderObj(g_carObjects[0]) + 0x248));
            void *stats = TitleStats();
            if (stats != 0) {
                TitleStats_AccumDistanceCounter(stats, GetDisplayBufferIndex(), 0);
            }
        }
    }

    fn_80208E30(this->coll);
    if (!g_rendererActivated) {
        g_rendererActivated = 1;
    }
    KartItem_UpdateShadowBillboardAndViewport(g_carObjects[0], this->scene, 0);
    Fog_UpdateFromCourseScene3D();
    PathManager_UpdateAll(g_pathManager);
    if (this->lakitu != 0 && !LakituStart_UpdateCountdown(this->lakitu)) {
        LakituStart_Dtor(this->lakitu, 1);
        this->lakitu = 0;
    }
    Jyugemu_Flag_Tick(this->jyugemuFlag);
    Jyugemu_ReverseFlag_Tick(this->jyugemuReverse);
    LapBannerScene_UpdateAndDriveAnim(this->lapBanner);
    CourseEnvironment_UpdateAndCullZones_Timed(this->environment);
    CObj_LoadProjMatrix(this->scene, &RaceScene_FrameUpdate_bss_805D2B10);
    CObj_ApplyScissor(this->scene, &RaceScene_FrameUpdate_bss_805D2B1C);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(RaceScene_FrameUpdate_bss_805D2B10, RaceScene_FrameUpdate_bss_805D2B1C);

    if (g_currentSceneState != 0x2D && g_rendererGateFlag == 1 && IsRaceStarted() == 1 &&
        g_raceTimeRemaining > 0.0f) {
        g_raceTimeRemaining -= 0.016666668f;
        if (g_raceTimeRemaining < 0.0f) {
            g_raceTimeRemaining = 0.0f;
            if (!g_raceEnded) {
                fn_80253BE4(this->hud);
                g_sceneTransitionTimer = 0x3C;
                fn_8016C554(0);
                fn_801B12A0();
                g_nonFirstFinishFlag = 1;
            }
        }
    }

    Tachometer_RenderDigits();
    HitMessageOverlay_FrameUpdate();
    HUD_SetCurrentLap(this->hud, g_currentLap);
    fn_80253FD8(this->hud, g_raceTimeRemaining);
    fn_80253EBC(this->hud, 100.0f * CarObject_CalcSpeedRatio(g_carObjects[0]));
    fn_80253EC0(this->hud, KartItem_GetCurrentSpeedWithBonus(g_carObjects[0]));
    fn_80253EC4(this->hud, g_currentLapTime);
    fn_80253F2C(this->hud, g_bestLapTime);
    HUD_SetRacePosition(this->hud, g_finalRacePosition);
    fn_80253E18(this->hud, *(int *)((char *)CarObject_GetRenderObj(g_carObjects[0]) + 0x2CC));
    TransitionEffect_Tick(Transition());
    if (!g_finalLapBannerShown && g_currentLap >= g_totalLaps) {
        g_finalLapBannerShown = 1;
        fn_80253DF0(this->hud);
    }

    if (0.0f != g_raceTimeRemaining && g_raceResultCode == -2) {
        if (g_currentLap >= g_totalLaps + 1) {
            void *stats;

            if (g_finalLapCoinJumpEnabled == 1) {
                CoinJumpFlasher_Toggle(g_carObjects[0]);
            }
            lbl_806CF270 = 0;
            KartItem_OnFallOffOrDeath(g_carObjects[0]);
            CoinJumpFlasher_SetArmed(g_carObjects[0], 0);
            ItemSelect_Reset(g_itemSelects[0], 0);
            g_finalRacePosition = *(int *)((char *)g_playerRenderObj + 0x23C);
            RaceResult_StoreLatest(GetKartSlotCharId(g_playerKartSlot), g_finalRacePosition, g_bestLapTime,
                                   g_totalRaceTime);
            g_raceResultCode = RaceResult_InsertSortedRank(GetKartSlotCharId(g_playerKartSlot),
                                                           g_finalRacePosition, g_bestLapTime, g_totalRaceTime);
            SetRaceResultLatestPtr(REG_ARGS1((void *)g_raceResultCode)); /* r3 still holds the rank just stored */
            if (g_finalRacePosition == 0) {
                fn_801D680C(g_playerData, g_cupId - 1, g_roundIndex, 1);
            } else {
                fn_801D680C(g_playerData, g_cupId - 1, g_roundIndex, 0);
                fn_801D67F4(g_playerData);
            }
            fn_80253D00(this->hud);
            Object_SetByte10_Return1(this->scene, 1);
            if (g_finalRacePosition == 0) {
                Jyugemu_Flag_SetKartDriver(this->jyugemuFlag, CarObject_GetRenderObj(g_carObjects[0]));
                fn_8016C554(1);
                PlayStats_OnRace1stPlace_Stub();
                g_nonFirstFinishFlag = 0;
            } else {
                fn_8016C554(0);
                g_nonFirstFinishFlag = 1;
            }
            CoinEvent_PlayResultSE(g_carObjects[0], g_finalRacePosition);
            g_raceEnded = 1;
            g_lakituStartAnimDone = 0;
            g_raceEndExitTimer++;
            stats = TitleStats();
            if (stats != 0) {
                RankLog_SetRaceResult(stats, GetDisplayBufferIndex(), g_finalRacePosition, (int)g_raceTimeRemaining);
            }
        } else if (g_lapChangePending) {
            if (g_finalLapBannerShown) {
                fn_8016C598();
                LapBannerScene_TriggerBannerAnim(this->lapBanner);
            } else {
                fn_8016C5CC();
            }
            void *stats = TitleStats();
            if (stats != 0) {
                TitleTracker_ResetPerRound(stats, GetDisplayBufferIndex(), g_currentLap - 1);
            }
            g_lapChangePending = 0;
        }
    } else if (g_raceEndExitTimer != 0 && g_currentSceneState != 0x2D) {
        if (++g_raceEndExitTimer >= 0x3C) {
            g_sceneTransitionTimer = 0xB4;
            SetSyncTarget(0x2D);
        }
    }

    HUD_FrameUpdate(this->hud);
    clItemBoxManager_Update(ItemBoxMgr());
    fn_8013A534();
    if (g_weatherSystem != 0) {
        fn_8016B32C(g_weatherSystem);
    }
    if (!lbl_806D0051 && pad->Pressed(0x400) == 1) {
        return 2;
    }
    return -2;
}

void clGameSingle::Draw()
{
    int i;

    if (g_rendererActivated != 1) {
        return;
    }
    if (((SceneCamera *)this->scene)->Begin() == 1) {
        clDrawMan_Buckets_Reset(DrawMan());
        TransparentDraw_SortAndDispatch();
        CObj_DebugVizPathFlush(((SceneCamera *)this->scene));
        fn_8016B0C4();
        if (g_cupId == 0) {
            IsTimerModeEnabled();
        }
        Stub_NoOp_80030aec(((SceneCamera *)this->scene));
        if (this->lakitu != 0) {
            Object_RenderJObjIfWithinRange(this->lakitu);
        }
        Jyugemu_Flag_Render(this->jyugemuFlag);
        Jyugemu_ReverseFlag_Render(this->jyugemuReverse);
        LapBannerScene_RenderIfActive(this->lapBanner);
        CourseEnvironment_RenderObjects_Timed(this->environment);
        Subsystem36c_DispatchPass2_Timed(this->environment);
        fn_801EB91C(this->ai, 1);
        fn_80208E2C(this->coll);
        NoopRenderHook_Pending_80064d28();
        ItemObjectManager_Render();
        DrawEffect_TickAndCull();
        for (i = 0; i < 8; i++) {
            void *kart = GetKartSlotKartVariant(i);
            if (kart != 0) {
                KartItem_TriggerStateAction(kart);
                KartItem_IsAtStartSlot(kart);
            }
        }
        KartItem_RenderPipelinedWithEffects(g_carObjects[0], 0);
        fn_80139810();
        clItemBoxManager_Draw(ItemBoxMgr());
        clDrawMan_EndFrame_NoOp(DrawMan());
        clDrawMan_Buckets_Dispatch(DrawMan());
        Subsystem36c_DispatchPass4_Timed(this->environment);
        TransitionEffect_RenderPass(Transition(), 5);
        TransitionEffect_RenderPass(Transition(), 3);
        if (IsRaceStarted() == 1) {
            fn_80253448(this->hud, lbl_806DC178);
        }
        fn_80253448(this->hud, lbl_806DC190 | lbl_806DC188 | lbl_806DC18C | lbl_806DC184 | lbl_806DC198 | lbl_806DC19C);
        if (g_currentLap < g_totalLaps + 1) {
            ItemSelect_DrawUIHelperIfActive(g_itemSelects[0]);
        }
        fn_80253448(this->hud, lbl_806DC180 | lbl_806DC17C | lbl_806DC1A0 | lbl_806DC1A4 | lbl_806DC1AC |
                                   lbl_806DC194 | lbl_806DC1B0 | lbl_806DC1B4);
        fn_80253448(this->hud, lbl_806DC1A8);
        TransitionEffect_RenderPass(Transition(), 2);
        TransitionEffect_RenderPass(Transition(), 4);
        TransitionEffect_RenderPass(Transition(), 6);
        ((SceneCamera *)this->scene)->End();
    }
    fn_80253448(this->hud, lbl_806DC1B8);
    TransitionEffect_RenderPass(Transition(), 1);
    if (this->overlay != 0) {
        fn_8020AFD4(this->overlay);
    }
    HSD_StateInvalidate(0x7F);
}
