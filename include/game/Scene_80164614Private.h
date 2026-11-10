#ifndef GAME_SCENE_80164614_PRIVATE_H
#define GAME_SCENE_80164614_PRIVATE_H
#include "game/types/arg_order.h"
#include "game/Scene_80163EF4Private.h"
struct Env163 { char opaque[0x37c]; Env163(); };
struct Camera163 { char opaque[0x2c]; Camera163 ARGS_ORDER((int, int, float, float, void *), (int, int, void *, float, float)); };
struct Car163 { char opaque[0x118]; Car163 ARGS_ORDER((int, int, float, float, float, int, int, int, int, int, int), (int, int, int, int, int, int, int, int, float, float, float)); };
struct Path163 { char opaque[0x4e8]; Path163(void *, void *, void *, void *, void *, void *); };
struct Scene163 { char opaque[0x3084]; Scene163(const char *); };
struct Lakitu163 { char opaque[0x58]; Lakitu163(const char *, int, float, float, float); };
struct Flag163 { char opaque[0xc]; Flag163(DemoSceneBase *); };
struct Reverse163 { char opaque[0x14]; Reverse163(void *); };
struct Banner163 { char opaque[0x10]; Banner163(void *); };
struct Collision163 { char opaque[0x18]; Collision163(); };
struct AI163 { char opaque[0x4]; AI163(void *, void *, int); };
struct Select163 { char opaque[0x88]; Select163(int, int); };
struct LoaderInit163 : LoaderTick163 { int field58; };
struct DVDFile163 { char pad0[0x30]; unsigned int start, length; char pad38[4]; };
struct DemoEntry163 { int character, cup, round, variant, reverse; const char *file; };
struct DemoRodata163 {
    char pad0[0x44c];
    DemoEntry163 entries[4];
    char pad4ac[0xa4];
    char sizeFormat[0x18];
    char fileSizeFormat[0x1c];
    char readFormat[0x1c];
    char lakituName[1];
};
#include "game/types/RaceLimits163.h"
extern "C" {
extern const float Scene_80164614_rodata_80369798[255];
extern unsigned int *HSD_RandSeedPtr;
extern int g_gameMode, g_ccClass, g_cupId, g_longRoundFlag, g_courseVariantIdx, g_roundIndex, g_reverseRoundFlag;
extern unsigned char lbl_806D1264[3], g_isCommHost;
extern int lbl_806CF010, lbl_806CF110, g_spawnedKartCount, lbl_806D1050, g_kartStartSlot, g_sceneTransitionTimer;
extern void *g_objCollChecker;
extern char g_playerData[];
extern const float lbl_806D8908, lbl_806D890C, lbl_806D8910;
extern RaceLimits163 DEMO[6][6];
extern float g_currentLapTime, g_lapBonusTimeDelta;
void fn_80121210();
#include "game/types/reg_args.h"
void fn_801E93A0();
void ReplayRandCursor_Reset(REG_ARGS1(void *)); /* the callee ignores its parameter */
void srand(unsigned int);
void Rand_SetSeedDebug(int);
unsigned char RandSeedDebug_SetEnable(unsigned char);
void SetTimerModeEnabled(int);
void SetReverseRoundFlag(int);
void DebugPrintf(const char *, ...);
void *FUN_8003b120(unsigned long);
void *memset(void *, int, unsigned long);
void *memcpy(void *, const void *, unsigned long);
int DVDOpen(const char *, DVDFile163 *);
void *OSAllocFromHeap(int, unsigned long);
int DVDLoad_WaitIfSamePage(unsigned int);
int DVDReadPrio(DVDFile163 *, void *, int, int, int);
void DVDLoad_RecordOpStart(unsigned int);
void OSFreeToHeap(int, void *);
void DVDClose(DVDFile163 *);
void RaceSlot_ResetAll();
int VSMode_SeedRandomItemSequence(int, int, int);
void RaceSlot_InitSlot(int, int, int, int, int);
void HSD_FObjForceLinearInterp(int);
void SetLocalPcbRole(int);
void ItemUse_ResetAllKartUseSlots();
void RaceScene_ClearPlayerSlotPointers();
void TransitionEffect_GetOrCreate();
void CourseData_GetOrCreate(int, int, int);
void *GetCourseDataPtr();
void *HSD_LObjLoadDesc(void *);
void RankingTable_Init(void *);
int GetCourseBgmEntry();
void SoundDriver_GetOrCreate(int);
void CoinSystem_Init(int, int);
int GetKartStartSlot(int);
void GetStartPosition(int, float *, int, float *);
float GetCourseStartYaw();
void KartItem_SetShortArray34a(void *, void *);
char *CarObject_GetTransformMatrix(void *);
void SceneFlow_SetFlag1048(unsigned char);
void *CourseData_GetDefaultPathKey_Safe();
const char **GetKartModelNameEntry(int, int);
void Scene3D_GetCameraPos(DemoSceneBase *, float *, float *);
void Scene3D_SetupProjection(DemoSceneBase *, float, float);
float RaceScene_GetPerspFovyForCup();
void CObj_UpdatePerspParam(DemoSceneBase *, float);
void LakituStart_SetCountdownHoldFrames(void *, int);
void ItemSelect_AddSlotItem(void *, int, int);
void CourseBgm_Load();
void PreloadEffectResources(int);
int ItemSelect_GetSlotItemId(void *, int);
void PreloadItemResources(int);
void *GetEnemyParam();
void clEnemyParam_FillItemListIds(void *, int, int, int);
int *AI_GetItemList(void *, int, int, int, int);
}
#endif
