#include "game/types/reg_args.h"
#ifndef GAME_SCENE_80163EF4_PRIVATE_H
#define GAME_SCENE_80163EF4_PRIVATE_H

#include "game/Scene_80163C68Private.h"

struct TraceInput163 { float steer, pedal, brake; int buttons; };
struct LoaderTick163 {
    int pad0, seed;
    unsigned char random, recording;
    char padA[2];
    TraceInput163 *inputs;
    int inputIndex;
    void *environment, *resource, *child;
    int slot;
    void *paths, *object, *flag, *reverseFlag, *banner, *system, *ai;
    unsigned char done, ready;
    char pad42[2];
    float time, fade;
    DemoSceneBase *scene;
    int pad50, heldItemFrames;
};
struct RecordedPlayer163 {
    virtual void V08();
    virtual void V0C();
    virtual float Steering();
    virtual void V14();
    virtual float Pedal();
    virtual float Brake();
    virtual void V20();
    virtual void V24();
    virtual int Buttons(int);
};
struct Checkpoint163 { int pad0; float x, y, z; };
struct ResultKart163 { char pad0[0x23c]; int position; };

extern "C" {
extern int g_raceFrameCounterLo2digits, g_finalRacePosition, g_raceResultCode;
extern unsigned char g_raceEnded, g_rendererGateFlag, g_finalLapBannerShown, g_lapChangePending;
extern float g_raceTimeRemaining, g_bestLapTime, g_totalRaceTime;
extern void *g_weatherSystem;
extern const float lbl_806D88FC, lbl_806D8900, lbl_806D8904, lbl_806D8060;
extern const Vec Scene_80163EF4_rodata_80369C44, Scene_80163EF4_rodata_80369C50;
extern Vec Scene_80163EF4_bss_80677CE8, Scene_80163EF4_bss_80677CF4;
int BattleRoulette_TickAndGetCounter();
void *GetRaceContextPtr();
void ItemObjectManager_PerFrameUpdate(void *);
void *CarObject_GetRenderObj(void *);
float CalcSoundDirection(void *, void *, float *, int);
int KartMovement_GetCurrentItemId(void *);
int IsRaceStarted();
void CarObject_ApplyInput(void *, int, float, float, float);
void CarObject_FrameUpdate(void *, int);
void ItemBox_ProcessPickup(void *, void *, int, int, int, float);
void RankingMgr_UpdatePositions(void *);
Checkpoint163 *Path_LookupCheckpointOffset(void *, int, int);
unsigned char JObj_IsForwardDotBelowThreshold(void *, Vec *, Vec *);
void Jyugemu_ReverseFlag_SetState(void *, int);
void fn_80208E30(void *);
void KartItem_UpdateShadowBillboardAndViewport(void *, DemoSceneBase *, int);
void Fog_UpdateFromCourseScene3D();
void PathManager_UpdateAll(void *);
void LakituStart_UpdateCountdown(void *);
void Jyugemu_Flag_Tick(void *);
void Jyugemu_ReverseFlag_Tick(void *);
void LapBannerScene_UpdateAndDriveAnim(void *);
void CourseEnvironment_UpdateAndCullZones_Timed(void *);
void TransitionEffect_Tick(void *);
void KartItem_OnFallOffOrDeath(void *);
void CoinJumpFlasher_SetArmed(void *, int);
void ItemSelect_Reset(void *, int);
int GetKartSlotCharId(int);
void RaceResult_StoreLatest(int, int, float, float);
int RaceResult_InsertSortedRank(int, int, float, float);
void SetRaceResultLatestPtr(REG_ARGS1(void *p));
void Object_SetByte10_Return1(DemoSceneBase *, int);
void Jyugemu_Flag_SetKartDriver(void *, void *);
void KartMovement_ResetOnGoal(void *);
void KartMovement_ResetOnTimeout(void *);
void fn_8016C554(int);
void fn_8016C598();
void LapBannerScene_TriggerBannerAnim(void *);
void fn_8016C5CC();
void clItemBoxManager_Update(void *);
void fn_8013A534();
void fn_8016B32C(void *);
float Saturate_Double(float, float, float);
}
#endif
