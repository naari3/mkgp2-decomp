#include "game/types/arg_order.h"

#include "game/types/size_t.h"
#include "game/singleton.h"
/* sdata symbols referenced from asm */
extern unsigned char lbl_806D7084[7];
extern unsigned char lbl_806D708C[5];
/*
 * 0x801287F8..0x8012A5AC: Noko Noko challenge and time trial scene.
 */
#pragma cplusplus on

typedef struct { float x, y, z; } Vec;
void *operator new(size_t size);
void operator delete(void *p);

#include "game/types/Vec3.h"
#include "game/types/LNode.h"
#include "game/types/Trail.h"
#include "game/types/Shot.h"
#include "game/types/ShotSet.h"
#include "game/types/ShotOwner.h"

#include "game/types/ModelPair.h"

struct VObj {
    virtual ~VObj();
    virtual unsigned char IsReady();
    virtual void Draw();
};

struct VObjSub {
    virtual void Update();
    virtual ~VObjSub();
};

struct HsdClassInfo {
    char pad[0x30];
    void (*release)(struct HsdObj *o);
    void (*destroy)(struct HsdObj *o);
};

struct HsdObj {
    HsdClassInfo *info;
    unsigned short ref;
};

struct TimeTrialMode {
    void **vt;
    char pad4[4];
    VObjSub *car;
    void *lakitu;
    void *env;
    VObj *scene;
    void *goalCam;
    VObj *camera;
    HsdObj *lights;
    char pad24[4];
    void *hud;
    void *icons;
    VObj *x30;
    unsigned char x34;
    char pad35[0x44 - 0x35];
    VObj *x44;
};


#include "game/types/clJobRunner.h"
extern "C" const float lbl_806D7070;
struct CarObject; struct LakituStart; struct InputManager; struct Scene3D; struct ChallengeGoalCamera; struct Camera; struct HUD; struct IconSet; struct MapWaterEffect; struct clCGameDKCoin;
struct clCGame : clJobRunner {
    float x4;
    clCGame() {
        x4 = lbl_806D7070;
    }
    virtual ~clCGame();
};


struct clCGameDK : clCGame {
    virtual int Update();
    virtual void Draw();
    virtual ~clCGameDK();
    CarObject *car;
    LakituStart *lakitu;
    void *input;
    Scene3D *scene;
    ChallengeGoalCamera *goalCam;
    Camera *camera;
    int renderTarget;
    int x24;
    HUD *hud;
    IconSet *icons;
    MapWaterEffect *water;
    unsigned char x34, x35, x36;
    int x38, x3C;
    int count;
    clCGameDKCoin *shots;
    clCGameDK();
    static clCGameDK *CheckType(clJobRunner *);
};


/* TOP-END */

extern "C" {

extern const float lbl_806D7050;
extern const float lbl_806D7058;
extern const float lbl_806D7068;
extern const float lbl_806D706C;
extern const float lbl_806D7070;
extern const float lbl_806D70B0;
extern const float lbl_806D70BC;
extern const float lbl_806D70C0;
extern const float lbl_806D70C4;
extern int g_characterId;
extern unsigned char g_lakituStartAnimDone;
extern void *g_raceCamera;
extern unsigned char g_raceEnded;
extern float g_raceTimeRemaining;
extern void *g_weatherSystem;
extern int lbl_806D12BC;

void DrawManager_GetOrCreate(void);
void SetResourceLoadingFlag(int on);
void DMAChannelManager_Init(void);
void TransitionEffect_GetOrCreate(void);
void SoundChannels_ClearAll(void);
void ItemObjectManager_Init(void);
void CourseObjectManager_Init(void);
void *GetCourseDataPtr(void);
int HSD_LObjLoadDesc(void *desc);
void SetActiveCamera(int idx, void *camera);
void ProcessSystemTick(int arg);
void *GetRaceContextPtr(void);
void RankingTable_Init(void *ctx);
void SoundDriver_GetOrCreate(int arg);
int GetDisplayBufferIndex(void);
void GetStartPosition(int idx, float *x, float *y, float *z);
float GetCourseStartYaw(void);
struct KartDriver *CarObject_GetRenderObj(void *car);
void KartMovement_EquipItem(void *obj, int item);
void SetPlayerCarObject(void *car);
int *GetKartModelNameEntry(int chara, int arg);
void Scene3D_GetCameraPos(void *scene, float *a, float *b);
void Scene3D_SetupProjection(void *scene, float a, float b);
void HUD_RegisterOverlay(void *hud, int id, int arg);
void SetCourseScene3D(void *scene);
int MiniGame_GetTimerValue(void);
void PreloadEffectResources(int id);
float *MiniGame_GetCourseData(void);
void NokoNoko_Init(float speed);
void PreloadResource(int id);
void clNormal3D_SetFlags(void *o, unsigned int flags, int arg);
void *Archive_GetRootJObj(void *o);
void HSD_JObjSetFlags(void *jobj, unsigned int flags);
void Object_SetJObjScaleXYZ(void *o, float x, float y, float z);

void CObj_DebugVizPathFlush(void *scene);
void CourseEnvironment_RenderObjects_Timed(void *env);
void DrawEffect_TickAndCull(void);
void HSD_StateInvalidate(int mask);
void ItemObjectManager_Render(void);
void KartItem_RenderPipelinedWithEffects(void *car, int arg);
void NokoNoko_Render(void);
void Object_RenderJObjIfWithinRange(void *o);
void Subsystem36c_DispatchPass2_Timed(void *env);
void Subsystem36c_DispatchPass4_Timed(void *env);
void TransitionEffect_RenderPass(void *te, int pass);
void TransparentDraw_SortAndDispatch(void);
void clDrawMan_Buckets_Dispatch(void *dm);
void clDrawMan_Buckets_Reset(void *dm);
void clDrawMan_EndFrame_NoOp(void *dm);
void clDrawMan_SetMaxClipZ(void *dm, float z);
void clItemBoxManager_Draw(void *m);
void fn_8011F994(int arg);
void fn_8016B0C4(void);
void fn_80253448(void *hud, unsigned int mask);
void fn_802535D4(void *hud);
extern VObj *lbl_806D109C;
extern VObj *lbl_806D10AC;
extern VObj *lbl_806D10D0;
extern const float lbl_806D7048;
extern unsigned int lbl_806DC190;
extern unsigned int lbl_806DC1B0;
extern unsigned int lbl_806DC1B8;
extern const float lbl_806D7054;
extern const unsigned int NokoNoko_801287F8_rodata_803561E8[0x10C];
extern void dtor_80036E40();
void ClRomTable_PurgeAll(void);
void CourseEnvironment_Dtor(void *env, int del);
void ItemObjectManager_Reset(void);
void LakituStart_Dtor(void *l, int del);
void MemoryManager_TimedFree(void *p);
void SceneDrawList_Reset(void);
void VfxSlotMgr_Shutdown(void);
void __destroy_arr(void *block, void *dtor, unsigned long size, unsigned long count);
void clRom_PurgeAll(void);
void dtor_80122FD8(void *self, int del);
void fn_80121210(void);
void fn_80124C84(void *cam, int del);
void fn_8016C634(void *w, int del);
void fn_80188DA8(void);
void fn_80254134(void *hud, int del);
void dtor_80082960(void);
extern void *NokoNokoChallenge_vtable_8048E338[];
extern void Alloc();
extern void Camera_Create();
extern void CarObject_Init();
extern void ChallengeGoalCamera_Init();
extern void GameMode_BaseInit();
extern void HUD_Init();
extern void InputManager_Init();
extern void LakituStart_Init();
extern void MapWaterEffect_Init();
extern void Scene3D_Init();
extern void WeatherSystem_Init();
extern void __construct_array();
extern void clNormal3D_Construct();
extern unsigned int lbl_806D7060;
extern unsigned int ResCtrl_Init[];
extern unsigned int lbl_8048E144[];
extern void *CoinShotBase_vtable_8048E34C[];
extern void *CoinShots_vtable_8048E36C[];
extern void dtor_8012A5AC();
struct LNode *LinkedNode_GetField10_OrFallback(void *o, int idx);
void Object_RenderJObjEx(void *o, void *node, int mask);
void Object_RenderJObjTree(void *o, int mask);
void Object_SetColorAlphaOnly(void *o, int idx, float a);
void Object_SetJObjPositionVec(void *o, struct Vec3 *v);
void Object_SetJObjRotationY(void *o, float r);
extern const float lbl_806D704C;
float LUT_Sin12Bit(float x);
unsigned char Terrain_GetGroundHeightWithPenetration(Vec3 *pos, float *out, int a, int b, float c);
float fn_80186960(float x);
extern const float lbl_806D70AC;
extern const float lbl_806D70B4;
extern const float lbl_806D70B8;
extern float lbl_80495994[];
extern float lbl_80495A94[];
void Object_DtorWithGXSync(void *o, int flag);
void TimeTrial_Render(TimeTrialMode *self);
TimeTrialMode *TimeTrial_Destroy(TimeTrialMode *self, short flag);
void fn_8012A070(ShotOwner *self);
void fn_8012A22C(ShotOwner *self);
ModelPair *fn_8012A52C(ModelPair *self, short flag);

#pragma section R ".extab_user"







#pragma section R ".extabindex_user"







}





/* .rodata 0x803561E8..0x80356708, owned by this TU (pool base of the mode ctor). */
struct IconPos { float x, y; };

extern "C" const unsigned int NokoNoko_801287F8_rodata_803561E8[0x10C] = {
    0x3F800000, 0x3F333333, 0x3F666666, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000,
    0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000,
    0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000,
    0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000,
    0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000,
    0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000,
    0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000,
    0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000,
    0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000,
    0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x00000000,
    0x000014BA, 0x000014BB, 0x000014BC, 0x000014BD, 0x000014BE, 0x000014BF,
    0x000014C0, 0x000014C1, 0x000014C2, 0x000014C3,
};
static const IconPos s_iconPos[8] = {
    { 520.0f, 421.25f }, { 450.0f, 419.25f }, { 485.0f, 421.25f }, { 515.0f, 419.25f },
    { 545.0f, 419.25f }, { 565.0f, 426.25f }, { 580.0f, 433.25f }, { 598.0f, 433.25f },
};
/* Fakematch: an uncalled diagnostic retains the original RTTI-name pool order. */
extern "C" void DebugPrintf(const char *, ...);
clCGameDK *clCGameDK::CheckType(clJobRunner *p) { return dynamic_cast<clCGameDK *>(p); }
static const char NkCoinStartFormat[] = "Start to DKCoin.  %s - %d\n";
static const char NkCoinHeaderName[] = "CGameCoin.hpp";
static const char NkCourseHeaderName[] = "item_center_joint";





#pragma exceptions on
#pragma readonly_strings on
/* NokoNokoChallenge_Update (0x801289B8): per-frame update of the Noko Noko
 * challenge. Same frame shape as MiniGame_CoinChallenge_Update; adds the
 * DK-coin shots fired at hit shells (CGameCoin.hpp inline), the defeated
 * counter icons and the nearest-shell arrow. */
struct NkVec { float x, y, z; };
/* empty out-of-line dtor is dtor_80036E40 (renamed in extab_user_renames.json) */
struct NkVelVec { float x, y, z; ~NkVelVec() {} };
struct NkInput {
    virtual void slot08();
    virtual void slot0c();
    virtual float steering();
    virtual void slot14();
    virtual float accelerator();
    virtual float brake();
};
struct NkVObj {
    virtual void slot08();
    virtual void Update();
};
struct NkRender { char pad[0x290]; int x290; float x294; };
struct NkJObj { char pad[0x14]; unsigned int flags; char pad18[0x2C]; float mtx[3][4]; };
struct NkModel { char pad[0x18]; void *model; };
struct NkSlot { char pad[0x18]; NkModel *obj; };
struct NkIcon {
    int id;
    char pad4[0xC];
    unsigned char x10;
    char pad11[3];
    float x14, x18, x1C;
    char pad20[0x38];
    void Set(float x, float y) { x10 = 1; x14 = x; x18 = y; x1C = lbl_806D7058; }
};
struct NkIcons {
    NkIcon icons[8];
    unsigned char exiting;
    float slide;
};
struct NkShot {
    int active;
    int x4;
    int timer;
    NkVec pos;
    NkVec vel;
    float rot;
    float alpha;
    char trail[0x140];
};
struct NkShots : NkVObj {
    char pad4[0x10];
    NkShot shots[6];
};
struct NkView {
    void *vptr;
    int x4;
    void *car;
    void *lakitu;
    void *env;
    void *camera;
    void *goalCam;
    char pad1c[0xC];
    void *hud;
    NkIcons *icons;
    NkVObj *water;
    unsigned char active, x35, won;
    int endDelay, resultFrames, count;
    NkShots *shots;
};

extern "C" {
extern unsigned char lbl_806D1290;
extern const float lbl_806D7074, lbl_806D7078, lbl_806D707C, lbl_806D7080, lbl_806D7094;
extern const float lbl_806D7098, lbl_806D709C, lbl_806D70A0, lbl_806D70A4, lbl_806D70A8;
extern Vec3 NokoNokoChallenge_Update_bss_80677C58, NokoNokoChallenge_Update_bss_80677C64;
void ItemObjectManager_PerFrameUpdate(void *);
void *GetInputManager();
NkInput *InputMgr_GetPlayer(void *, int);
unsigned char IsRaceStarted();
unsigned char NokoNokoChallenge_HandleBrakeInput(void *, int);
#ifdef __MWERKS__
void CarObject_ApplyInput(void *, float, float, float, unsigned char);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void CarObject_ApplyInput(void *, unsigned char, float, float, float);
static inline void CarObject_ApplyInput_Reordered(void * a0, float a1, float a2, float a3, unsigned char a4) { CarObject_ApplyInput(a0, a4, a1, a2, a3); }
#define CarObject_ApplyInput CarObject_ApplyInput_Reordered
#endif
void CarObject_FrameUpdate(void *, int);
void KartItem_UpdateShadowBillboardAndViewport(void *, void *, int);
void KartMovement_SetSpeedScale(void *, float);
float (*KartDriver_GetKartRootMtx(void *))[4];
void ChallengeGoalCamera_Update(void *, void *, void *);
unsigned char KartMovement_CanReceiveItem(void *, int);
void RenderObj_UseItem(void *, int, int);
void Fog_UpdateFromCourseScene3D();
void LakituStart_UpdateCountdown(void *);
void CourseEnvironment_UpdateAndCullZones_Timed(void *);
unsigned char NokoNoko_CheckHitAndKill(NkVec *pos, NkVec *hit, float radius);
void KartItem_GetCarVelocityVec3(void *car, NkVelVec *out);
void Vec3_Normalize(void *in, void *out);
unsigned char IsCardValid();
void DebugPrintf(const char *fmt, ...);
unsigned char fn_8016C360(int);
void fn_8016C394(int);
void SoundMgr_PlaySE(int);
NkSlot *KartItem_GetCurrentISESlot(void *);
NkJObj *ResolveJointByName(void *model, const char *name);
void __assert(const char *file, int line, const char *expr);
void HSD_JObjSetupMatrixSub(NkJObj *);
void NokoNoko_UpdateAll();
int NokoNoko_CountDefeated();
int Clamp_Int(int, int, int);
void fn_80121E10(NkIcon *);
void NokoNoko_StopAllAlive();
unsigned char NokoNoko_FindNearest(NkVec *pos, NkVec *out);
void Vec3_Subtract(NkVec *a, NkVec *b, NkVec *out);
float Vec3_Dot(NkVec *a, NkVec *b);
int CObj_LoadProjMatrix(void *, Vec3 *);
int CObj_ApplyScissor(void *, Vec3 *);
void ItemObjectManager_Update();
#ifdef __MWERKS__
void VfxSlotMgr_Update(Vec3, Vec3);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void VfxSlotMgr_Update(Vec3 *, Vec3 *);
static inline void VfxSlotMgr_Update_ByValue(Vec3 a0, Vec3 a1) { VfxSlotMgr_Update(&a0, &a1); }
#define VfxSlotMgr_Update VfxSlotMgr_Update_ByValue
#endif
void fn_80253FD8(void *, float);
float CarObject_CalcSpeedRatio(void *);
void fn_80253EBC(void *, float);
float KartItem_GetCurrentSpeedWithBonus(void *);
void fn_80253EC0(void *, float);
void HUD_FrameUpdate(void *);
void fn_8011FAFC(NkIcon *, int);
void TransitionEffect_Tick(void *);
int *NokoNokoChallenge_GetCoinDivisor();
void SetCoinCount(int);
int NokoNokoChallenge_CalcResultText(void *, int, int);
void fn_80253C74(void *, int, int, int);
void KartMovement_ResetOnGoal(void *);
void KartMovement_ResetOnTimeout(void *);
void NokoNokoChallenge_SaveResult(void *, int, unsigned char);
int Object_SetByte10_Return1(void *, int);
unsigned char fn_80253C40(void *);
int NokoNokoChallenge_TransitionToResult(void *);
void fn_8016B32C(void *);
}

static inline NkRender *NkGetRender(NkView *self) {
    return (NkRender *)CarObject_GetRenderObj(self->car);
}

/* HSD joint accessors keep their own assertions when inlined by callers. */
static inline unsigned int NkGetJointFlags(NkJObj *jobj) {
    if (jobj == 0) {
        __assert((const char *)lbl_806D7084, 0x25D, (const char *)lbl_806D708C);
    }
    return jobj->flags;
}

static inline void NkSetupMatrix(NkJObj *jobj) {
    if (jobj == 0) {
        __assert((const char *)lbl_806D7084, 0x47C, (const char *)lbl_806D708C);
    }
    if (jobj != 0) {
        unsigned int flags = NkGetJointFlags(jobj);
        unsigned char dirty = 0;
        if (!(flags & 0x00800000) && (flags & 0x40)) {
            dirty = 1;
        }
        if (dirty) {
            HSD_JObjSetupMatrixSub(jobj);
        }
    }
}

static inline int NkFindFreeShot(NkShots *s) {
    int idx = 0;
    for (int i = 0; i < 6; i++) {
        if (s->shots[i].active == 0) {
            idx = i;
            break;
        }
    }
    return idx;
}

static inline void NkFireShot(NkShots *s, NkVec *pos, NkVec *dir) {
    if (IsCardValid()) {
        DebugPrintf(NkCoinStartFormat, NkCoinHeaderName, 0x386);
        if (fn_8016C360(0xab) == 1) {
            fn_8016C394(0xab);
        }
        SoundMgr_PlaySE(0xab);
        int i = NkFindFreeShot(s);
        s->shots[i].active = 1;
        s->shots[i].timer = 0;
        s->shots[i].alpha = lbl_806D7070;
        s->shots[i].rot = lbl_806D7070;
        s->shots[i].pos.x = pos->x;
        s->shots[i].pos.y = pos->y;
        s->shots[i].pos.z = pos->z;
        s->shots[i].vel.x = dir->x;
        s->shots[i].vel.z = dir->z;
        s->shots[i].vel.y = dir->y;
    }
}

static inline void NkCheckHit(NkView *self, NkVec *pos, float radius, NkVec &hit, NkVec &dir, NkVelVec &vel) {
    if (NokoNoko_CheckHitAndKill(pos, &hit, radius) == 1) {
        KartItem_GetCarVelocityVec3(self->car, &vel);
        dir.x = hit.x - pos->x;
        dir.y = lbl_806D7070;
        dir.z = hit.z - pos->z;
        Vec3_Normalize(&dir, &dir);
        dir.x = lbl_806D707C * (lbl_806D7080 * vel.x + dir.x);
        dir.z = lbl_806D707C * (lbl_806D7080 * vel.z + dir.z);
        dir.y = lbl_806D7054;
        NkShots *shots = self->shots;
        NkFireShot(shots, &hit, &dir);
    }
}

static inline void NkSetCounter(NkIcons *icons, int shown) {
    if (shown > 99) shown = 99;
    int ones = shown % 10;
    int tens = (shown - ones) / 10;
    fn_80121E10(&icons->icons[3]);
    fn_80121E10(&icons->icons[4]);
    icons->icons[3].id = tens != 0 ? tens + 0x14BA : 0x1ECD;
    icons->icons[4].id = ones + 0x14BA;
    icons->icons[3].Set(s_iconPos[3].x, s_iconPos[3].y);
    icons->icons[4].Set(s_iconPos[4].x, s_iconPos[4].y);
}

static inline void NkUpdateIcons(NkIcons *icons) {
    int i;
    if (icons->exiting != 0) {
        if (icons->slide >= lbl_806D7058) goto done;
        icons->slide += lbl_806D706C;
        for (i = 0; i < 8; i++) {
            icons->icons[i].Set(lbl_806D70A8 * icons->slide + s_iconPos[i].x, s_iconPos[i].y);
        }
    }
    for (i = 0; i < 8; i++) {
        fn_8011FAFC(&icons->icons[i], 0);
    }
done:
    return;
}

static inline int NkShouldHoldBrake(float accel, float brake) {
    int holding = 0;
    if (accel < lbl_806D706C && brake < lbl_806D706C && IsRaceStarted()) {
        holding = 1;
    }
    return holding;
}


static const char s_lakituFile[20] = "jyugemu_start.dat";
static const char s_coinFile[16] = "mario_coin.dat";
static const char s_kiraFile[16] = "k_kira13.dat";
#pragma exceptions reset

static inline int RefDec(HsdObj *o)
{
    int ret = o->ref == (unsigned short)-1;
    if (ret) {
        return ret;
    }
    return o->ref-- == 0;
}

static inline void ObjUnref(HsdObj *o)
{
    if (o == 0) {
        return;
    }
    if (RefDec(o)) {
        if (o != 0) {
            o->info->release(o);
            o->info->destroy(o);
        }
    }
}



/* NokoNokoChallenge_Init (0x80129938): constructor of the Noko Noko
 * challenge mode, the same minigame-ctor shape as JumpDistanceMode_Init.
 * The TU owns .rodata 0x803561E8..0x80356708, so the icon table and the
 * model file names are addressed off one pool base (r30). Mangled names
 * are mapped in tools/extab_user_renames.json. */
#pragma exceptions on

#include "game/types/KartDriver.h"

#include "game/types/InputManager.h"
#include "game/types/Camera.h"
#include "game/types/CarObject.h"
static inline int GetChara() { return g_characterId; }
struct PlayerCar : CarObject {
    PlayerCar(const float *x, const float *z, int chara)
        : CarObject(GetDisplayBufferIndex(), chara, 0, 0, 1, 1, 0, 0, *x, *z, GetCourseStartYaw()) {}
};
#include "game/types/LakituStart.h"
#include "game/types/Scene3D.h"
#include "game/types/ChallengeGoalCamera.h"
struct MapWaterEffect { char data[0x10]; MapWaterEffect(); };
#include "game/types/HUD.h"
#include "game/types/WeatherSystem.h"
#include "game/types/clNormal3D.h"

struct ResCtrl {
    int id;
    char pad4[0xC];
    unsigned char x10;
    char pad11[3];
    float x14, x18, x1C;
    char pad20[0xC];
    float x2C, x30;
    char pad34[0x24];
    ResCtrl();
    void Set(float x, float y) { x10 = 1; x14 = x; x18 = y; x1C = lbl_806D7058; }
    ~ResCtrl();
};


struct IconSet {
    ResCtrl icons[8];
    unsigned char x2C0;
    float x2C4;
    IconSet(int count, const IconPos *pos) {
        PreloadResource(0x14B9);
        PreloadResource(0x14C4);
        PreloadResource(0x14BA);
        icons[0].id = 0x14B9;
        icons[1].id = 0x14C7;
        icons[2].id = 0x14C5;
        icons[3].id = 0x1ECD;
        icons[4].id = 0x14BA;
        icons[5].id = 0x14C4;
        icons[6].id = count / 10 + 0x14BA;
        icons[7].id = count % 10 + 0x14BA;
        icons[5].x2C = lbl_806D7068;
        icons[5].x30 = lbl_806D7068;
        icons[6].x2C = lbl_806D70C0;
        icons[6].x30 = lbl_806D70C0;
        icons[7].x2C = lbl_806D70C0;
        icons[7].x30 = lbl_806D70C0;
        for (int i = 0; i < 8; i++) {
            icons[i].Set(pos[i].x, pos[i].y);
        }
        x2C0 = 0;
        x2C4 = lbl_806D7070;
    }
};

struct ShotVec {
    float x, y, z;
    void Zero() { x = y = z = lbl_806D7070; }
};
struct CoinShotTrail { int age; ShotVec pos; };
struct CoinShot {
    int active;
    int x4;
    int timer;
    ShotVec pos;
    ShotVec vel;
    float rot;
    float alpha;
    CoinShotTrail trail[20];
};

#include "game/types/clCGameCoinBase.h"


/* Fakematch: parse-time RTTI diagnostic preserves the original name pool. */
clCGameCoinBase *clCGameCoinBase::CheckType(clJobRunner *p) { return dynamic_cast<clCGameCoinBase *>(p); }
inline clCGameCoinBase::clCGameCoinBase(const char *modelFile, const char *trailFile) {
    xC = 0;
    x10 = 0;
    trailCount = 5;
    model = new clNormal3D(modelFile, 1);
    clNormal3D_SetFlags(model, 0x40000000, 0);
    trailModel = new clNormal3D(trailFile, 1);
    HSD_JObjSetFlags(Archive_GetRootJObj(trailModel), 0x200);
    for (int i = 0; i < 6; i++) {
        shots[i].active = 0;
        shots[i].timer = 0;
        shots[i].rot = lbl_806D7070;
        shots[i].alpha = lbl_806D7070;
        shots[i].x4 = 0;
        shots[i].pos.Zero();
        shots[i].vel.Zero();
        for (int j = 0; j < 20; j++) {
            shots[i].trail[j].age = -1;
        }
    }
    if (trailCount >= 20) {
        trailCount = 19;
    }
}



inline clCGameCoinBase::~clCGameCoinBase() {
    Object_DtorWithGXSync(model, 1);
    Object_DtorWithGXSync(trailModel, 1);
}

struct clCGameDKCoin : clCGameCoinBase {
    clCGameDKCoin(const char *modelFile, const char *trailFile) : clCGameCoinBase(modelFile, trailFile) {
        Object_SetJObjScaleXYZ(model, lbl_806D70C4, lbl_806D70C4, lbl_806D70C4);
    }
    virtual ~clCGameDKCoin();
    virtual void Update();
    virtual void Draw();
};







static inline bool Trail_Spawn(Trail *t, float a, float b)
{
    if (t->age >= 0) {
        return false;
    }
    t->age = 0;
    t->pos.x = 5.0f * LUT_Sin12Bit(360.0f * a);
    t->pos.y = 10.0f * b;
    t->pos.z = 5.0f * fn_80186960(360.0f * a);
    return true;
}






clCGameDKCoin::~clCGameDKCoin() {}

void clCGameDKCoin::Update()
{
    Shot *s;
    Trail *trails;
    int i;
    int j;

    for (i = 0; i < 6; i++) {
        s = &((ShotSet *)this)->shots[i];
        if (s->active) {
            trails = s->trail;
            s->pos.x += s->vel.x;
            s->pos.y += s->vel.y;
            s->pos.z += s->vel.z;
            s->vel.y -= 0.1f;
            float ground = 0.0f;
            if (Terrain_GetGroundHeightWithPenetration(&s->pos, &ground, 0, 0, 10.0f) == 1 && s->pos.y < ground) {
                s->vel.y = 0.85f * -s->vel.y;
            }
            s->rot += 5.0f;
            if (s->rot > 360.0f) {
                s->rot -= 360.0f;
            }
            s->alpha = 1.0f - s->timer / 90.0f;
            for (j = 0; j < trailCount; j++) {
                if (trails[j].age >= 0) {
                    trails[j].pos.y -= 2.0f;
                    if (++trails[j].age > 10) {
                        trails[j].age = -1;
                    }
                }
            }
            if ((s->timer & 3) == 0) {
                for (j = 0; j < trailCount; j++) {
                    if (Trail_Spawn(&trails[j], lbl_80495994[xC], lbl_80495A94[x10]) == 1) {
                        trails[j].pos.x += s->pos.x;
                        trails[j].pos.y += s->pos.y;
                        trails[j].pos.z += s->pos.z;
                        break;
                    }
                }
                if (++xC >= 0x40) {
                    xC = 0;
                }
                if (++x10 >= 0x30) {
                    x10 = 0;
                }
            }
            if (++s->timer >= 0x5a) {
                s->active = 0;
            }
        }
    }
}

void clCGameDKCoin::Draw()
{
    for (int i = 0; i < 6; i++) {
        if (((ShotSet *)this)->shots[i].active) {
            Object_SetJObjPositionVec(model, &((ShotSet *)this)->shots[i].pos);
            Object_SetJObjRotationY(model, lbl_806D704C * ((ShotSet *)this)->shots[i].rot);
            Object_SetColorAlphaOnly(model, 0, ((ShotSet *)this)->shots[i].alpha);
            Object_RenderJObjEx(model, LinkedNode_GetField10_OrFallback(model, 0), 7);
            LNode *n = LinkedNode_GetField10_OrFallback(model, 0);
            Object_RenderJObjEx(model, n == 0 ? 0 : n->f8, 7);
            for (int j = 0; j < trailCount; j++) {
                float f = ((ShotSet *)this)->shots[i].trail[j].age / lbl_806D7050;
                float sc = lbl_806D7054 - f;
                Object_SetJObjPositionVec(trailModel, &((ShotSet *)this)->shots[i].trail[j].pos);
                Object_SetJObjScaleXYZ(trailModel, sc, sc, sc);
                Object_SetColorAlphaOnly(trailModel, 0, (lbl_806D7058 - f) * ((ShotSet *)this)->shots[i].alpha);
                Object_RenderJObjTree(trailModel, 7);
            }
        }
    }
}

clCGameDK::clCGameDK() {
    float x, z;
    float camA, camB;
    float *course;
    float speed;

    DrawManager_GetOrCreate();
    SetResourceLoadingFlag(0);
    DMAChannelManager_Init();
    TransitionEffect_GetOrCreate();
    SoundChannels_ClearAll();
    ItemObjectManager_Init();
    CourseObjectManager_Init();
    input = new InputManager;
    renderTarget = HSD_LObjLoadDesc(GetCourseDataPtr());
    camera = new Camera ARGS_ORDER((lbl_806D70BC, lbl_806D706C, 0x100, 0x100, renderTarget), (0x100, 0x100, renderTarget, lbl_806D70BC, lbl_806D706C));
    SetActiveCamera(0, camera);
    g_raceCamera = camera;
    ProcessSystemTick(0);
    RankingTable_Init(GetRaceContextPtr());
    lbl_806D12BC = 0;
    SoundDriver_GetOrCreate(0);
    GetStartPosition(0, &x, 0, &z);
    car = new PlayerCar(&x, &z, GetChara());
    {
        KartDriver *r = CarObject_GetRenderObj(car);
        r->visible_238 = 1;
    }
    {
        KartDriver *r = CarObject_GetRenderObj(car);
        r->forceDraw = 1;
    }
    SetPlayerCarObject(car);
    KartMovement_EquipItem(CarObject_GetRenderObj(car), 6);
    lakitu = new LakituStart(s_lakituFile, 0, lbl_806D70B0, lbl_806D7070, lbl_806D7070);
    scene = new Scene3D(*GetKartModelNameEntry(g_characterId, -1));
    goalCam = new ChallengeGoalCamera;
    water = new MapWaterEffect;
    ProcessSystemTick(0);
    Scene3D_GetCameraPos(scene, &camA, &camB);
    camA += lbl_806D7050;
    Scene3D_SetupProjection(scene, camA, camB);
    hud = new HUD(0);
    HUD_RegisterOverlay(hud, 6, 0);
    HUD_RegisterOverlay(hud, 0x11, 0);
    HUD_RegisterOverlay(hud, 0x12, 0);
    HUD_RegisterOverlay(hud, 0xE, 0);
    g_lakituStartAnimDone = 0;
    SetCourseScene3D(scene);
    g_raceEnded = 0;
    x34 = 0;
    x36 = 0;
    x38 = 0;
    x3C = 0;
    g_raceTimeRemaining = MiniGame_GetTimerValue();
    PreloadEffectResources(2);
    PreloadEffectResources(9);
    PreloadEffectResources(0xA);
    course = MiniGame_GetCourseData();
    count = 15;
    speed = lbl_806D7058;
    if (course != 0) {
        speed = course[0];
        count = ((int *)course)[1];
    }
    NokoNoko_Init(speed);
    icons = new IconSet(count, s_iconPos);
    shots = new clCGameDKCoin(s_coinFile, s_kiraFile);
    if (g_weatherSystem == 0) {
        g_weatherSystem = new WeatherSystem(1);
    }
    SetResourceLoadingFlag(1);
}

clCGameDK::~clCGameDK()
{
        TimeTrialMode *self = (TimeTrialMode *)this;
        if (g_weatherSystem != 0) {
            fn_8016C634(g_weatherSystem, 1);
            g_weatherSystem = 0;
        }
        SetActiveCamera(0, 0);
        delete self->x44;
        delete self->scene;
        LakituStart_Dtor(self->lakitu, 1);
        fn_80124C84(self->goalCam, 1);
        delete self->x30;
        SetPlayerCarObject(0);
        delete self->car;
        g_raceCamera = 0;
        if (self->camera != 0) {
            delete self->camera;
        }
        if (self->lights != 0) {
            ObjUnref(self->lights);
        }
        CourseEnvironment_Dtor(self->env, 1);
        void *icons = self->icons;
        if (icons != 0) {
            fn_80121210();
            __destroy_arr(icons, (void *)dtor_80082960, 0x58, 8);
            MemoryManager_TimedFree(icons);
        }
        fn_80254134(self->hud, 1);
        fn_80188DA8();
        ItemObjectManager_Reset();
        VfxSlotMgr_Shutdown();
        ClRomTable_PurgeAll();
        RankingTable_Init(GetRaceContextPtr());
        delete lbl_806D10D0;
        lbl_806D10D0 = 0;
        SceneDrawList_Reset();
        delete lbl_806D109C;
        lbl_806D109C = 0;
        SetResourceLoadingFlag(0);
        clRom_PurgeAll();
        delete lbl_806D10AC;
        lbl_806D10AC = 0;
}

int clCGameDK::Update()
{
    NkInput *input;
    float accel, brake;
    float (*mtx)[4];
    NkVec pos;
    NkVec hit;
    NkVec dir;
    int defeated;

    if (x34 == 0) {
        x34 = 1;
    }
    ItemObjectManager_PerFrameUpdate(GetRaceContextPtr());
    input = InputMgr_GetPlayer(GetInputManager(), 0);
    if (g_raceEnded != 1) {
        if (lbl_806D1290 == 0) {
            accel = input->accelerator();
        } else {
            accel = lbl_806D7068;
        }
        brake = input->brake();
        int holding = NkShouldHoldBrake(accel, brake);
        if (NokoNokoChallenge_HandleBrakeInput(((NkView *)this), holding) == 1) {
            accel = lbl_806D7058;
        }
        CarObject_ApplyInput(car, input->steering(), accel, brake, IsRaceStarted());
        CarObject_FrameUpdate(car, 0);
        KartItem_UpdateShadowBillboardAndViewport(car, scene, 0);
    } else {
        CarObject_ApplyInput(car, lbl_806D7070, lbl_806D7070, lbl_806D7070, 1);
        KartMovement_SetSpeedScale(car, lbl_806D7074);
        CarObject_FrameUpdate(car, 0);
        if (x38 > 0) {
            KartItem_UpdateShadowBillboardAndViewport(car, scene, 0);
        } else {
            ChallengeGoalCamera_Update(goalCam, scene, KartDriver_GetKartRootMtx(CarObject_GetRenderObj(car)));
        }
    }
    if (IsRaceStarted() == 1 && g_raceEnded != 1 && KartMovement_CanReceiveItem(CarObject_GetRenderObj(car), 1)) {
        RenderObj_UseItem(CarObject_GetRenderObj(car), 0, 0);
        NkGetRender(((NkView *)this))->x290 = -1;
    }
    Fog_UpdateFromCourseScene3D();
    LakituStart_UpdateCountdown(lakitu);
    CourseEnvironment_UpdateAndCullZones_Timed(this->input);
    ((NkVObj *)water)->Update();

    mtx = KartDriver_GetKartRootMtx(CarObject_GetRenderObj(car));
    pos.x = mtx[0][3];
    pos.y = mtx[1][3];
    pos.z = mtx[2][3];
    NkVelVec vel;
    NkVec target;
    NkCheckHit(((NkView *)this), &pos, lbl_806D7078, hit, dir, vel);

    {
        NkSlot *slot = KartItem_GetCurrentISESlot(CarObject_GetRenderObj(car));
        NkModel *obj = slot != 0 ? slot->obj : 0;
        if (obj != 0 && obj->model != 0) {
            NkJObj *joint = ResolveJointByName(obj->model, NkCourseHeaderName);
            if (joint != 0) {
                NkSetupMatrix(joint);
                pos.x = joint->mtx[0][3];
                pos.y = joint->mtx[1][3];
                pos.z = joint->mtx[2][3];
                NkCheckHit(((NkView *)this), &pos, lbl_806D7094, hit, dir, vel);
            }
        }
    }

    NokoNoko_UpdateAll();
    if (g_raceEnded != 1) {
        defeated = NokoNoko_CountDefeated();
        NkSetCounter(((NkIcons *)icons), Clamp_Int(defeated, 0, count));
        if (defeated >= count) {
            NokoNoko_StopAllAlive();
            x36 = 1;
            x38 = 30;
            NkGetRender(((NkView *)this))->x290 = 0;
            g_raceEnded = 1;
        } else {
            mtx = KartDriver_GetKartRootMtx(CarObject_GetRenderObj(car));
            pos.x = mtx[0][3];
            pos.y = mtx[1][3];
            pos.z = mtx[2][3];
            if (NokoNoko_FindNearest(&pos, &target)) {
                Vec3_Subtract(&target, &pos, &target);
                Vec3_Normalize(&target, &target);
                pos.x = mtx[0][2];
                pos.y = mtx[1][2];
                pos.z = mtx[2][2];
                Vec3_Normalize(&pos, &pos);
                float dot = Vec3_Dot(&target, &pos);
                if (dot > lbl_806D7098) {
                    NkGetRender(((NkView *)this))->x294 = lbl_806D7070;
                } else if (dot > lbl_806D709C) {
                    pos.x = mtx[0][0];
                    pos.y = mtx[1][0];
                    pos.z = mtx[2][0];
                    Vec3_Normalize(&pos, &pos);
                    if (Vec3_Dot(&target, &pos) > lbl_806D7070) {
                        NkGetRender(((NkView *)this))->x294 = lbl_806D7058;
                    } else {
                        NkGetRender(((NkView *)this))->x294 = lbl_806D7054;
                    }
                } else {
                    NkGetRender(((NkView *)this))->x294 = lbl_806D7070;
                }
            }
        }
    }
    ((NkShots *)shots)->Update();
    CObj_LoadProjMatrix(scene, &NokoNokoChallenge_Update_bss_80677C58);
    CObj_ApplyScissor(scene, &NokoNokoChallenge_Update_bss_80677C64);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(NokoNokoChallenge_Update_bss_80677C58, NokoNokoChallenge_Update_bss_80677C64);
    if (IsRaceStarted() == 1 && g_raceEnded != 1) {
        if (g_raceTimeRemaining >= 0.0f) {
            g_raceTimeRemaining -= lbl_806D70A0;
            if (g_raceTimeRemaining < 0.0f) {
                g_raceTimeRemaining = 0.0f;
                NokoNoko_StopAllAlive();
                NkGetRender(((NkView *)this))->x290 = 0;
                g_raceEnded = 1;
            }
        }
    }
    fn_80253FD8(hud, g_raceTimeRemaining);
    fn_80253EBC(hud, lbl_806D70A4 * CarObject_CalcSpeedRatio(car));
    fn_80253EC0(hud, KartItem_GetCurrentSpeedWithBonus(car));
    HUD_FrameUpdate(hud);
    NkUpdateIcons(((NkIcons *)icons));
    TransitionEffect_Tick(SINGLETON_INSTANCE(lbl_806D109C));
    if (g_raceEnded == 1) {
        if (x38 > 0) {
            x38--;
        } else {
            if (x3C == 0) {
                int coins = 0;
                int *divisor = NokoNokoChallenge_GetCoinDivisor();
                if (divisor != 0) {
                    coins = NokoNoko_CountDefeated();
                    if (coins > count) {
                        coins = count;
                    }
                    coins /= *divisor;
                    SetCoinCount(coins);
                }
                if (x36 != 0) {
                    fn_80253C74(hud, 1, NokoNokoChallenge_CalcResultText(((NkView *)this), 1, 0), Clamp_Int(NokoNoko_CountDefeated(), 0, count));
                    ((NkIcons *)icons)->exiting = 1;
                    KartMovement_ResetOnGoal(CarObject_GetRenderObj(car));
                } else {
                    fn_80253C74(hud, 0, NokoNokoChallenge_CalcResultText(((NkView *)this), 0, 0), Clamp_Int(NokoNoko_CountDefeated(), 0, count));
                    ((NkIcons *)icons)->exiting = 1;
                    KartMovement_ResetOnTimeout(CarObject_GetRenderObj(car));
                }
                NokoNokoChallenge_SaveResult(((NkView *)this), coins, x36);
                Object_SetByte10_Return1(scene, 1);
                g_lakituStartAnimDone = 0;
            } else if (fn_80253C40(hud)) {
                return NokoNokoChallenge_TransitionToResult(((NkView *)this));
            }
            x3C++;
        }
    }
    if (g_weatherSystem != 0) {
        fn_8016B32C(g_weatherSystem);
    }
    return -2;
}

void clCGameDK::Draw()
{
    TimeTrialMode *self = (TimeTrialMode *)this;
    if (self->x34 == 0) {
        return;
    }
    if (self->scene->IsReady() == 1) {
        clDrawMan_Buckets_Reset(SINGLETON_INSTANCE(lbl_806D10AC));
        clDrawMan_SetMaxClipZ(SINGLETON_INSTANCE(lbl_806D10AC), lbl_806D7048);
        TransparentDraw_SortAndDispatch();
        CObj_DebugVizPathFlush(self->scene);
        fn_8016B0C4();
        KartItem_RenderPipelinedWithEffects(self->car, 0);
        Object_RenderJObjIfWithinRange(self->lakitu);
        CourseEnvironment_RenderObjects_Timed(self->env);
        NokoNoko_Render();
        self->x44->Draw();
        clItemBoxManager_Draw(SINGLETON_INSTANCE(lbl_806D10D0));
        Subsystem36c_DispatchPass2_Timed(self->env);
        ItemObjectManager_Render();
        self->x30->Draw();
        DrawEffect_TickAndCull();
        clDrawMan_EndFrame_NoOp(SINGLETON_INSTANCE(lbl_806D10AC));
        clDrawMan_Buckets_Dispatch(SINGLETON_INSTANCE(lbl_806D10AC));
        Subsystem36c_DispatchPass4_Timed(self->env);
        TransitionEffect_RenderPass(SINGLETON_INSTANCE(lbl_806D109C), 2);
        TransitionEffect_RenderPass(SINGLETON_INSTANCE(lbl_806D109C), 4);
        fn_80253448(self->hud, lbl_806DC1B0 | lbl_806DC190);
        fn_8011F994(1);
        self->scene->Draw();
    }
    fn_80253448(self->hud, lbl_806DC1B8);
    fn_802535D4(self->hud);
    TransitionEffect_RenderPass(SINGLETON_INSTANCE(lbl_806D109C), 1);
    HSD_StateInvalidate(0x7f);
}
