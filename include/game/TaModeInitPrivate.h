#ifndef GAME_TA_MODE_INIT_PRIVATE_H
#define GAME_TA_MODE_INIT_PRIVATE_H
void *operator new(unsigned long);
void operator delete(void *);
#include "game/types/RaceParams.h"

struct GameModeBase {
    GameModeBase() {}
    virtual ~GameModeBase() {}
    virtual int FrameUpdate() = 0;
    virtual void Render() = 0;
};

#include "game/types/EnvironmentMgr.h"

#include "game/types/RaceCamera.h"

struct CarObject {
    unsigned char data[0x118];
    CarObject(int displayIdx, int charId, float x, float y, float yaw, int ccClass, int variant, int human,
              int team, int local, int ghost);
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

struct WeatherSystem {
    unsigned char data[0x1B4];
    WeatherSystem(int flag);
};

#include "game/types/RaceHud.h"

#include "game/types/SceneOverlay.h"

struct TaMode : GameModeBase {
    LakituStart *lakitu;           /* 0x04 */
    JyugemuFlag *jyugemuFlag;      /* 0x08 */
    JyugemuReverseFlag *jyugemuReverse; /* 0x0C */
    FinalLapBanner *lapBanner;     /* 0x10 */
    EnvironmentMgr *environment;   /* 0x14 */
    void *pad18;
    Scene3D *scene;                /* 0x1C */
    void *pad20[2];
    RaceCamera *camera;            /* 0x28 */
    RaceHud *hud;                  /* 0x2C */
    void *pad30;
    AISystem *ai;                  /* 0x34 */
    unsigned char flag38;          /* 0x38 */
    SceneOverlay *overlay;         /* 0x3C */

    TaMode();
    virtual ~TaMode();
    virtual int FrameUpdate();
    virtual void Render();
};

extern "C" {
extern char RaceScene_rodata_803211D8[];
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

extern const char TaMode_FrameUpdate_rodata_80321980[];
extern const float lbl_806D4830, lbl_806D4834, lbl_806D4838, lbl_806D483C, lbl_806D484C, lbl_806D4860;

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
extern void *g_raceRenderTarget;
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
void *HSD_LObjLoadDesc(void *desc);
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
unsigned char ItemSelect_GetSlotItemId(ItemSelect *sel, int slot);
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
}


struct TaSound { char data[0x44]; TaSound(int); };
struct TaGhostSource { int character; const char *file; unsigned long size; int unused; };
extern "C" {
extern int TaMode_Init_bss_806D13CC, g_characterId, TaMode_FrameUpdate_bss_806D13A8, TaMode_FrameUpdate_bss_806D1394, TaMode_FrameUpdate_bss_806D139C, TaMode_FrameUpdate_data_806CF198, TaMode_FrameUpdate_bss_806D13AC, TaMode_FrameUpdate_bss_806D13B0;
extern unsigned char TaMode_FrameUpdate_bss_806D13A0, lbl_806D13A1, TaMode_FrameUpdate_bss_806D13B8;
extern CarObject *lbl_806D1398;
extern PathManager *TaMode_FrameUpdate_bss_806D13A4;
extern void *TaMode_FrameUpdate_bss_806D1390, *TaMode_FrameUpdate_bss_806D1388, *TaMode_FrameUpdate_bss_806D13C8;
extern unsigned long TaMode_FrameUpdate_bss_806D138C;
extern TaSound *lbl_806D13B4;
extern float TaMode_FrameUpdate_data_806CF19C;
extern unsigned long TaMode_FrameUpdate_bss_806D13C0, TaMode_FrameUpdate_bss_806D13C4;
void RaceSlot_ResetAll();
void RaceSlot_InitSlot(int, int, int, int, int);
unsigned char GetVBlankFlag();
void *DVDFile_LoadSync(const char *);
int PathManager_RegisterCarObject(PathManager *, float *, float *, float *, CarObject *, void *, int);
void KartMovement_EquipItem(void *, int);
void ItemEffectBus_OrMask(void *, unsigned long long);
void fn_8023E1E4(TaSound *, int, int);
void *StrPcb_GetInstance();
void StrPcb_SetStatusBits(void *, int, int);
int IsTimerModeEnabled();
void PlayStats_IncTaPlay();
}
#endif
