#ifndef TAMODE_FRAMEUPDATE_PRIVATE_H
#define TAMODE_FRAMEUPDATE_PRIVATE_H
#include "game/singleton.h"
struct TaRender {
    unsigned char pad0[0x23c];
    int position;
    unsigned char pad240[0x2b8-0x240];
    unsigned char effectActive;
    unsigned char pad2b9[0x2cc-0x2b9];
    int coins;
    unsigned char pad2d0[0x304-0x2d0];
    void *itemBus;
};
struct TaGhostFrame {
    float accel, steer, brake;
    signed char started, item, coins, pad;
};
#include "game/types/Vec.h"

struct InputPlayer {
    virtual void v0();
    virtual void v1();
    virtual float Accel();
    virtual void v3();
    virtual float Steer();
    virtual float Brake();
    virtual unsigned char Pressed(int mask);
    virtual void v7();
    virtual unsigned int Held(int mask);
};

struct RaceScene {
    void *vtable;
    void *lakitu;          /* 0x04 */
    void *jyugemuFlag;     /* 0x08 */
    void *jyugemuReverse;  /* 0x0C */
    void *lapBanner;       /* 0x10 */
    void *environment;     /* 0x14 */
    void *pad18;
    void *scene;           /* 0x1C */
    void *pad20[3];
    void *hud;             /* 0x2C */
    void *pad30;
    int finishFrames;       /* 0x34 */
    unsigned char demoCamera; /* 0x38 */
    unsigned char pad39[3];
    void *overlay;         /* 0x3C */
};

extern "C" {
extern int g_sceneTransitionTimer;
extern void *lbl_806D10A0;
extern void *lbl_806D109C;
extern void *lbl_806D10D0;
extern unsigned char g_raceEnded;
extern int g_ccClass;
#ifdef __MWERKS__
extern void *g_carObjects[];
#else /* this namespace sees g_carObjects with another type: a view of the same object */
static void * *const g_carObjects = (void * *)::g_carObjects;
#endif
extern unsigned char g_playerData[];
extern unsigned char g_rendererGateFlag;
extern float g_raceTimeRemaining;
extern int g_currentLap;
extern int g_totalLaps;
extern float g_currentLapTime;
extern float g_bestLapTime;
extern float g_totalRaceTime;
extern int g_finalRacePosition;
extern unsigned char g_finalLapBannerShown;
extern int g_raceResultCode;
extern unsigned char g_finalLapCoinJumpEnabled;
extern void *g_playerRenderObj;
extern int g_cupId;
extern unsigned char g_lakituStartAnimDone;
extern unsigned char g_lapChangePending;
#ifdef __MWERKS__
extern void *g_weatherSystem;
#else /* this namespace sees g_weatherSystem with another type: a view of the same object */
static void * &g_weatherSystem = *(void * *)&::g_weatherSystem;
#endif
extern unsigned char lbl_806D0051;

void SetSyncTarget(int target);
void *GetInputManager(void);
InputPlayer *InputMgr_GetPlayer(void *mgr, int index);
void *GetRaceContextPtr(void);
void ItemObjectManager_PerFrameUpdate(void *ctx);
long long OSGetTime(void);
unsigned char IsRaceStarted(void);
#ifdef __MWERKS__
TaRender *CarObject_GetRenderObj(void *car);
#else /* this namespace declares CarObject_GetRenderObj with other types: a view of the same object */
static inline TaRender * CarObject_GetRenderObj(void * a0) { return ((TaRender * (*)(void *))&::CarObject_GetRenderObj)(a0); }
#endif
float CalcSoundDirection(void *render, void *path, float *steer, int flag);
void CarObject_ApplyInput(void *car, float accel, float steer, float brake, unsigned char started);
void CarObject_FrameUpdate(void *car, unsigned int held);
int GetCoinMilage(unsigned char *playerData);
void CoinJumpFlasher_Toggle(void *car);
int GetDisplayBufferIndex(void);
void KartItem_UpdateShadowBillboardAndViewport(void *car, void *scene, int flag);
void Fog_UpdateFromCourseScene3D(void);
void PathManager_UpdateAll(void *path);
unsigned char LakituStart_UpdateCountdown(void *lakitu);
void Jyugemu_Flag_Tick(void *flag);
void Jyugemu_ReverseFlag_Tick(void *flag);
void LapBannerScene_UpdateAndDriveAnim(void *banner);
void CourseEnvironment_UpdateAndCullZones_Timed(void *env);
void CObj_LoadProjMatrix(void *scene, Vec *v);
void CObj_ApplyScissor(void *scene, Vec *v);
void ItemObjectManager_Update(void);
void VfxSlotMgr_Update(Vec a, Vec b);
void fn_80253BE4(void *hud);
void fn_8016C554(int flag);
void Tachometer_RenderDigits(void);
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
int GetKartSlotCharId(int slot);
void fn_80253D00(void *hud);
void Object_SetByte10_Return1(void *scene, int v);
void Jyugemu_Flag_SetKartDriver(void *flag, void *render);
void RankLog_SetRaceResult(void *stats, int display, int pos, int time);
void fn_8016C598(void);
void LapBannerScene_TriggerBannerAnim(void *banner);
void fn_8016C5CC(void);
void TitleTracker_ResetPerRound(void *stats, int display, int lap);
void HUD_FrameUpdate(void *hud);
void clItemBoxManager_Update(void *mgr);
void fn_8013A534(void);
void fn_8016B32C(void *weather);
}

static inline void *TitleStats(void)
{
    return SINGLETON_INSTANCE(lbl_806D10A0);
}

static inline void *Transition(void)
{
    return SINGLETON_INSTANCE(lbl_806D109C);
}

static inline void *ItemBoxMgr(void)
{
    return SINGLETON_INSTANCE(lbl_806D10D0);
}

static inline float QuantizeInput(float v)
{
    return (float)(int)(10000.0f * v) / 10000.0f;
}


struct TaBookend { Vec eye, target; };
extern "C" {
struct TaRecord { int character; const char *name; int score; float time; };
extern Vec TaMode_FrameUpdate_bss_805D2B28, TaMode_FrameUpdate_bss_805D2B34;
#ifdef __MWERKS__
extern void *g_taSound, *TaMode_FrameUpdate_bss_806D13A4, *g_taGhostCar;
#else /* this namespace sees them with another type: views of the same objects */
static void * &g_taSound = *(void * *)&::g_taSound;
static void * &TaMode_FrameUpdate_bss_806D13A4 = *(void * *)&::TaMode_FrameUpdate_bss_806D13A4;
static void * &g_taGhostCar = *(void * *)&::g_taGhostCar;
#endif
#ifdef __MWERKS__
extern void *g_raceCamera;
#else /* this namespace sees g_raceCamera with another type: a view of the same object */
static void * &g_raceCamera = *(void * *)&::g_raceCamera;
#endif
#ifdef __MWERKS__
extern TaGhostFrame *TaMode_FrameUpdate_bss_806D1388;
#else /* this namespace sees TaMode_FrameUpdate_bss_806D1388 with another type: a view of the same object */
static TaGhostFrame * &TaMode_FrameUpdate_bss_806D1388 = *(TaGhostFrame * *)&::TaMode_FrameUpdate_bss_806D1388;
#endif
#ifdef __MWERKS__
extern unsigned int TaMode_FrameUpdate_bss_806D138C, TaMode_FrameUpdate_bss_806D1394;
#else /* this namespace sees them with another type: views of the same objects */
static unsigned int &TaMode_FrameUpdate_bss_806D138C = *(unsigned int *)&::TaMode_FrameUpdate_bss_806D138C;
static unsigned int &TaMode_FrameUpdate_bss_806D1394 = *(unsigned int *)&::TaMode_FrameUpdate_bss_806D1394;
#endif
extern int TaMode_FrameUpdate_bss_806D139C, TaMode_FrameUpdate_data_806CF198, TaMode_FrameUpdate_bss_806D13AC, TaMode_FrameUpdate_bss_806D13B0, TaMode_FrameUpdate_bss_806D13A8;
extern unsigned char TaMode_FrameUpdate_bss_806D13A0, lbl_806D13A1, TaMode_FrameUpdate_bss_806D13B8;
#ifdef __MWERKS__
extern unsigned int TaMode_FrameUpdate_bss_806D13C0, TaMode_FrameUpdate_bss_806D13C4;
#else /* this namespace sees them with another type: views of the same objects */
static unsigned int &TaMode_FrameUpdate_bss_806D13C0 = *(unsigned int *)&::TaMode_FrameUpdate_bss_806D13C0;
static unsigned int &TaMode_FrameUpdate_bss_806D13C4 = *(unsigned int *)&::TaMode_FrameUpdate_bss_806D13C4;
#endif
extern int g_longRoundFlag, g_reverseRoundFlag;
extern float TaMode_FrameUpdate_data_806CF19C;
int __ptmf_test(const void *);
void fn_8023E324(void *, int);
int KartMovement_GetCurrentItemId(TaRender *);
unsigned char KartItem_GetByte_f4(void *);
unsigned char Input_IsItemButtonPressed(int buttons);
unsigned char RenderObj_UseItem(TaRender *, int, int);
void RankLog_OnPlayerVictory(void *, int, int);
void CarObject_ApplyDriftBoost(void *, int, float);
#ifdef __MWERKS__
void fn_8023E1E4(void *, int, int);
#else /* this namespace declares fn_8023E1E4 with other types: a view of the same object */
static inline void fn_8023E1E4(void * a0, int a1, int a2) { ((void (*)(void *, int, int))&::fn_8023E1E4)(a0, a1, a2); }
#endif
#ifdef __MWERKS__
void KartMovement_EquipItem(TaRender *, int);
#else /* this namespace declares KartMovement_EquipItem with other types: a view of the same object */
static inline void KartMovement_EquipItem(TaRender * a0, int a1) { ((void (*)(TaRender *, int))&::KartMovement_EquipItem)(a0, a1); }
#endif
void ItemEffectBus_ClearMask(void *, unsigned long long);
void ItemEffectBus_OrMask(void *, unsigned long long);
void *StrPcb_GetInstance(void);
void StrPcb_SetStatusBits(void *, int, int);
void StrPcb_ClearStatusBits(void *, int);
TaBookend *TaMode_GetDemoCameraBookend(void);
void Vec3_Subtract(const Vec *, const Vec *, Vec *);
void Vec3_Normalize(const Vec *, Vec *);
void CObj_LoadIntoGX(void *, Vec *);
void CObj_ApplyViewport(void *, Vec *);
#ifdef __MWERKS__
float *CarObject_GetTransformMatrix(void *);
#else /* this namespace declares CarObject_GetTransformMatrix with other types: a view of the same object */
static inline float * CarObject_GetTransformMatrix(void * a0) { return ((float * (*)(void *))&::CarObject_GetTransformMatrix)(a0); }
#endif
void SceneRender_SetViewportRect(void *, float, float, float, float, float, float);
int TaRecord_InsertResult(unsigned char *, int, int, int, int, float);
void fn_801D670C(unsigned char *);
void fn_801D676C(unsigned char *);
void fn_801D597C(unsigned char *);
void PlayStats_IncTaBestRecord(void);
void TitleStats_CaptureRoundContext(void *, int, float);
void TitleStats_FinalizeRace_PlayCountThenTitle(void *);
unsigned char fn_80253C40(void *);
}
#endif
