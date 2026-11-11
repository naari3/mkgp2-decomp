#include "game/types/arg_order.h"

/* sdata symbols referenced from asm */
extern unsigned char lbl_806D7280[7];
extern unsigned char lbl_806D7288[5];
/*
 * 0x801313D0..0x801341E4: Suika ball minigame.
 */
#pragma cplusplus on

#include "game/types/Vec3.h"
#include "game/types/LNode.h"
#include "game/types/Trail.h"
#include "game/types/Shot.h"
#include "game/types/ShotSet.h"
#include "game/types/ShotOwner.h"

#include "game/types/ModelPair.h"

struct Deletable {
    virtual ~Deletable();
    virtual unsigned char Begin();
    virtual void End();
};

struct Destroyable {
    virtual void v0();
    virtual void Destroy(int flag);
};

struct HsdClass {
    unsigned char pad0[0x30];
    void (*release)(void *obj);
    void (*destroy)(void *obj);
};

#include "game/types/HsdRefObj.h"

#include "game/types/Quat.h"

#include "game/types/HSD_JObj.h"

#include "game/types/InputPlayer.h"

struct SuikaBallObj {
    void *archive;          /* 0x00 */
    char pad4[0x34];
    Vec3 pos;               /* 0x38 */
    char pad44[0x60 - 0x44];
    unsigned char hit;      /* 0x60 */
    unsigned char goal;     /* 0x61 */
    char pad62[2];
    float x64, x68, x6C, x70, x74, x78;
    SuikaBallObj(const char *file);
    void SetPos(float x, float y, float z) { pos.x = x; pos.y = y; pos.z = z; }
    void SetParams(float a, float b, float c, float d, float e, float f) { x64 = a; x68 = b; x6C = c; x70 = d; x74 = e; x78 = f; }
};

struct Gate {
    Vec3 pos;
    char padC[0x24 - 0xC];
    Vec3 normal;            /* 0x24 */
};

struct GateList {
    Gate *gates[4];
    int next;               /* 0x10 */
};

struct SuikaSlot {
    void *objA;
    void *objB;
    HSD_JObj **bufA;
    HSD_JObj **bufB;
    int count;
};

#include "game/types/clJobRunner.h"
extern "C" const float lbl_806D72B8;
struct clCGame : clJobRunner {
    float phase;
    clCGame() { phase = lbl_806D72B8; }
    virtual ~clCGame();
};
struct clCGameMR : clCGame {
    virtual int Update();
    virtual void Draw();
    virtual ~clCGameMR();
    float *courseData;
    Destroyable *car;
    void *lakitu;
    void *environment;
    Deletable *m18;
    void *m1C;
    Deletable *m20;
    HsdRefObj *m24;
    int x28;
    void *hud;
    unsigned char active, bgmOn, finished, goalReached;
    int state, x38;
    SuikaBallObj *m3C;
    Gate *m40;
    Deletable *m44, *m48;
    float speedScale;
    Vec3 prevPos;
    SuikaSlot *slots;
    Deletable *m60;
    GateList *bufs;
    int coins;
    clCGameMR();
    void AddBallToCamera(void *cam);
    void PrintTypeNames();
};
typedef clCGameMR SuikaBall;

/* TOP-END */

extern "C" {
extern void CObj_DebugVizPathFlush(void *cobj);
extern void CourseEnvironment_RenderObjects_Timed(void *env);
extern void DrawEffect_TickAndCull(void);
extern void GXBegin(int type, int fmt, unsigned short n);
extern void GXClearVtxDesc(void);
extern void GXLoadPosMtxImm(void *mtx, unsigned int id);
extern void GXSetBlendMode(int type, int src, int dst, int op);
extern void GXSetChanCtrl(int chan, unsigned char enable, int amb, int mat, unsigned int lights, int diff, int attn);
extern void GXSetCullMode(int mode);
extern void GXSetCurrentMtx(unsigned int id);
extern void GXSetNumChans(unsigned char n);
extern void GXSetNumTevStages(unsigned char n);
extern void GXSetNumTexGens(unsigned char n);
extern void GXSetTevOp(int stage, int mode);
extern void GXSetTevOrder(int stage, int coord, int map, int color);
extern void GXSetVtxAttrFmt(int fmt, int attr, int cnt, int type, unsigned char frac);
extern void GXSetVtxDesc(int attr, int type);
extern void GXSetZMode(unsigned char compare, int func, unsigned char update);
extern void *HSD_CObjGetCurrent(void);
extern void *HSD_CObjGetViewingMtxPtr(void *cobj);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *jobj);
extern void HSD_StateInvalidate(int state);
extern unsigned char IsCardValid(void);
extern void ItemObjectManager_Render(void);
extern void KartItem_RenderPipelinedWithEffects(void *car, int flag);
void Object_RenderJObjEx(void *o, void *node, int mask);
extern void Object_RenderJObjIfWithinRange(void *o);
extern void Subsystem36c_DispatchPass2_Timed(void *env);
extern void Subsystem36c_DispatchPass4_Timed(void *env);
extern void SuikaBallObj_Render(void *o);
extern void TransitionEffect_RenderPass(void *te, int pass);
extern void TransparentDraw_SortAndDispatch(void);
extern void __assert(const char *file, int line, const char *cond);
extern void clDrawMan_Buckets_Dispatch(void *dm);
extern void clDrawMan_Buckets_Reset(void *dm);
extern void clDrawMan_EndFrame_NoOp(void *dm);
extern void fn_8016B0C4(void);
extern void fn_80253448(void *hud, unsigned int flags);
extern void fn_802535D4(void *hud);
extern Deletable *lbl_806D109C;
extern Deletable *lbl_806D10AC;
extern unsigned int lbl_806D7290;
extern unsigned int lbl_806D7294;
extern const unsigned int lbl_806DC190;
extern const unsigned int lbl_806DC1B0;
extern const unsigned int lbl_806DC1B8;
extern const Vec3 SuikaBall_Render_rodata_803579F4[4][2];
extern void CObj_ApplyScissor(void *cobj, Vec3 *v);
extern void CObj_LoadProjMatrix(void *cobj, Vec3 *v);
#ifdef __MWERKS__
extern void CarObject_ApplyInput(void *car, float steer, float accel, float brake, unsigned char started);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void CarObject_ApplyInput(void *, unsigned char, float, float, float);
static inline void CarObject_ApplyInput_Reordered(void * a0, float a1, float a2, float a3, unsigned char a4) { CarObject_ApplyInput(a0, a4, a1, a2, a3); }
#define CarObject_ApplyInput CarObject_ApplyInput_Reordered
#endif
extern float CarObject_CalcSpeedRatio(void *car);
extern void CarObject_FrameUpdate(void *car, int flag);
extern void *CarObject_GetRenderObj(void *car);
extern void ChallengeGoalCamera_Update(void *cam, void *cobj, float (*mtx)[4]);
extern void CourseEnvironment_UpdateAndCullZones_Timed(void *env);
extern void DebugPrintf(const char *fmt, ...);
extern void Fog_UpdateFromCourseScene3D(void);
extern void *GetInputManager(void);
void *GetRaceContextPtr(void);
extern void HUD_FrameUpdate(void *hud);
extern InputPlayer *InputMgr_GetPlayer(void *mgr, int index);
extern unsigned char IsRaceStarted(void);
extern void ItemObjectManager_PerFrameUpdate(void *);
extern void ItemObjectManager_Update(void);
extern float (*KartDriver_GetKartRootMtx(void *drv))[4];
extern float KartItem_GetCurrentSpeedWithBonus(void *car);
extern void KartItem_UpdateShadowBillboardAndViewport(void *car, void *cobj, int flag);
extern void KartMovement_ResetOnGoal(void *drv);
extern void KartMovement_ResetOnTimeout(void *drv);
extern void KartMovement_SetSpeedScale(void *car, float scale);
extern void KartReaction_Rear(void *drv);
extern float LUT_Cosine(float a);
extern float LUT_Sine(float a);
extern void LakituStart_UpdateCountdown(void *lakitu);
extern int NokoNokoChallenge_CalcResultText(void *self, int goal, int flag);
extern unsigned char NokoNokoChallenge_HandleBrakeInput(void *self, unsigned char brake);
extern void NokoNokoChallenge_SaveResult(void *self, int coins, unsigned char goal);
extern int NokoNokoChallenge_TransitionToResult(void *self);
extern void Object_SetByte10_Return1(void *o, int v);
extern void SetCoinCount(int n);
extern void SoundMgr_Play(int id);
extern void SoundMgr_PlaySE(int id);
extern void SuikaBallObj_UpdatePhysics(SuikaBallObj *ball, float (*mtx)[4], Vec3 *delta, float radius);
extern void TransitionEffect_Tick(void *te);
extern float Vec3_Dot(Vec3 *a, Vec3 *b);
extern void Vec3_Subtract(Vec3 *a, Vec3 *b, Vec3 *out);
#ifdef __MWERKS__
extern void VfxSlotMgr_Update(Vec3 eye, Vec3 at);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void VfxSlotMgr_Update(Vec3 *, Vec3 *);
static inline void VfxSlotMgr_Update_ByValue(Vec3 eye, Vec3 at) { VfxSlotMgr_Update(&eye, &at); }
#define VfxSlotMgr_Update VfxSlotMgr_Update_ByValue
#endif
extern double atan2(double y, double x);
extern void clNormal3D_Exec(void *o);
extern void fn_8016B32C(void *ws);
extern unsigned char fn_8016C360(int id);
void fn_8016C394(int n);
extern void fn_80192688(int id, int mode);
extern unsigned char fn_80253C40(void *hud);
extern void fn_80253C74(void *hud, int goal, int text, int flag);
extern void fn_80253EBC(void *hud, float v);
extern void fn_80253EC0(void *hud, float v);
extern void fn_80253FD8(void *hud, float t);
extern unsigned char g_lakituStartAnimDone;
extern unsigned char g_raceEnded;
extern float g_raceTimeRemaining;
extern void *g_weatherSystem;
extern unsigned char lbl_806D1290;
extern const float lbl_806D72A4;
extern const float lbl_806D72B0;
extern const float lbl_806D72B4;
extern const float lbl_806D72B8;
extern unsigned int lbl_806D72BC;
extern unsigned int lbl_806D72C0;
extern unsigned int lbl_806D72C4;
extern unsigned int lbl_806D72C8;
extern unsigned int lbl_806D72CC;
extern unsigned int lbl_806D72D0;
extern unsigned int lbl_806D72D4;
extern unsigned int lbl_806D72D8;
extern unsigned int lbl_806D72DC;
extern unsigned int lbl_806D72E0;
extern unsigned int lbl_806D72E4;
extern unsigned int lbl_806D72E8;
extern Vec3 SuikaBall_Update_bss_80677C70;
extern Vec3 SuikaBall_Update_bss_80677C7C;
extern void ClRomTable_PurgeAll();
void CourseEnvironment_Dtor(void *p, int flag);
extern void ItemObjectManager_Reset();
void LakituStart_Dtor(void *p, int flag);
void MemoryManager_Free(void *p);
void MemoryManager_TimedFree(void *p);
void Object_DtorWithGXSync(void *o, int flag);
void RankingTable_Init(void *ctx);
extern void SceneDrawList_Reset();
void SetActiveCamera(int idx, void *cam);
void SetPlayerCarObject(void *car);
void SetResourceLoadingFlag(int flag);
extern void VfxSlotMgr_Shutdown();
extern void clRom_PurgeAll();
void dtor_80122FD8(void *p, int flag);
void fn_8012491C(void *p, int flag);
void fn_80124C84(void *p, int flag);
void fn_8016C634(void *p, int flag);
void fn_80254134(void *p, int flag);
extern void *g_raceCamera;
extern Deletable *lbl_806D10D0;
extern char SuikaBallMode_vtable_8048E3F8[];
extern const float lbl_806D72FC;
extern const float lbl_806D72F8;
extern const float lbl_806D7300;
extern const float lbl_806D7304;
extern int g_characterId;
extern int lbl_806D12BC;
void DrawManager_GetOrCreate(void);
void DMAChannelManager_Init(void);
void TransitionEffect_GetOrCreate(void);
void SoundChannels_ClearAll(void);
void ItemObjectManager_Init(void);
void CourseObjectManager_Init(void);
void *GetCourseDataPtr(void);
int HSD_LObjLoadDesc(void *desc);
void ProcessSystemTick(int arg);
void SoundDriver_GetOrCreate(int arg);
int GetDisplayBufferIndex(void);
void GetStartPosition(int idx, float *x, float *y, float *z);
float GetCourseStartYaw(void);
int *GetKartModelNameEntry(int chara, int arg);
void Scene3D_GetCameraPos(void *scene, float *a, float *b);
void Scene3D_SetupProjection(void *scene, float a, float b);
void HUD_RegisterOverlay(void *hud, int id, int arg);
void SetCourseScene3D(void *scene);
int MiniGame_GetTimerValue(void);
void PreloadEffectResources(int id);
float *MiniGame_GetCourseData(void);
void clNormal3D_SetFlags(void *o, unsigned int flags, int arg);
void *Archive_GetRootJObj(void *o);
void HSD_JObjSetFlags(void *jobj, unsigned int flags);
extern const float lbl_806D7308;
extern const float lbl_806D730C;
extern const float lbl_806D7310;
extern const float lbl_806D7314;
void CarObject_SetPosition(void *car, Vec3 *pos);
void clNormal3D_SetScale(void *obj, int arg, float a, float b, float c, float d);
void *FUN_8003b120(unsigned long size);
void *ResolveJointByName(void *obj, const char *name);
void SceneRender_CmdB_8aa20(void *cam, void *jobj);
void Vec3_Normalize(Vec3 *src, Vec3 *dst);
extern const float lbl_806D729C;
extern void *CoinShotBase_vtable_8048E34C[];
extern void *SuikaCoinShots_vtable_8048E418[];
struct LNode *LinkedNode_GetField10_OrFallback(void *o, int idx);
void Object_RenderJObjTree(void *o, int mask);
void Object_SetColorAlphaOnly(void *o, int idx, float a);
void Object_SetJObjPositionVec(void *o, struct Vec3 *v);
void Object_SetJObjRotationY(void *o, float r);
void Object_SetJObjScaleXYZ(void *o, float x, float y, float z);
extern const float lbl_806D7298;
extern const float lbl_806D72A0;
float LUT_Sin12Bit(float x);
unsigned char Terrain_GetGroundHeightWithPenetration(Vec3 *pos, float *height, void *a, void *b, float r);
float fn_80186960(float x);
extern const float lbl_806D72EC;
extern const float lbl_806D72F0;
extern const float lbl_806D72F4;
extern float lbl_80495994[];
extern float lbl_80495A94[];



void fn_80133CA8(ShotOwner *self);
void fn_80133E64(ShotOwner *self);
ModelPair *fn_80134164(ModelPair *self, short flag);

#pragma section R ".extab_user"






#pragma section R ".extabindex_user"






}





/* .rodata pool 0x80357008..0x80357B00, defined before its first use */
struct JointSetDesc {
    const char *model;
    const char *setModel;
    const char *const *joints;
    int count;
};
extern "C" const unsigned int suikaCourseParameters[0x102] = {
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
};
extern "C" const char lbl_80357410[] = "MH_challenge_kino_a_joint";
extern "C" const char lbl_8035742C[] = "MH_challenge_kino_set_a1_joint";
extern "C" const char lbl_8035744C[] = "MH_challenge_kino_set_a2_joint";
extern "C" const char lbl_8035746C[] = "MH_challenge_kino_set_a3_joint";
extern "C" const char lbl_8035748C[] = "MH_challenge_kino_b_joint";
extern "C" const char lbl_803574A8[] = "MH_challenge_kino_set_b1_joint";
extern "C" const char lbl_803574C8[] = "MH_challenge_kino_set_b2_joint";
extern "C" const char lbl_803574E8[] = "MH_challenge_kino_set_b3_joint";
extern "C" const char lbl_80357508[] = "MH_challenge_kino_c_joint";
extern "C" const char lbl_80357524[] = "MH_challenge_kino_set_c1_joint";
extern "C" const char lbl_80357544[] = "MH_challenge_kino_set_c2_joint";
extern "C" const char lbl_80357564[] = "MH_challenge_kino_d_joint";
extern "C" const char lbl_80357580[] = "MH_challenge_kino_set_d1_joint";
extern "C" const char lbl_803575A0[] = "MH_challenge_kino_set_d2_joint";
extern "C" const char *const SuikaBall_801313D0_rodata_803575C0[20] = {
    lbl_80357410, lbl_8035742C, lbl_80357410, lbl_8035744C, lbl_80357410, lbl_8035746C, lbl_8035748C, lbl_803574A8, lbl_8035748C, lbl_803574C8, lbl_8035748C, lbl_803574E8, lbl_80357508, lbl_80357524, lbl_80357508, lbl_80357544, lbl_80357564, lbl_80357580, lbl_80357564, lbl_803575A0,
};
extern "C" const char lbl_80357610[] = "MH_challenge_monte_a_joint";
extern "C" const char lbl_8035762C[] = "MH_challenge_monte_set_a1_joint";
extern "C" const char lbl_8035764C[] = "MH_challenge_monte_set_a2_joint";
extern "C" const char lbl_8035766C[] = "MH_challenge_monte_set_a3_joint";
extern "C" const char lbl_8035768C[] = "MH_challenge_monte_b_joint";
extern "C" const char lbl_803576A8[] = "MH_challenge_monte_set_b1_joint";
extern "C" const char lbl_803576C8[] = "MH_challenge_monte_set_b2_joint";
extern "C" const char lbl_803576E8[] = "MH_challenge_monte_set_b3_joint";
extern "C" const char *const SuikaBall_801313D0_rodata_80357708[12] = {
    lbl_80357610, lbl_8035762C, lbl_80357610, lbl_8035764C, lbl_80357610, lbl_8035766C, lbl_8035768C, lbl_803576A8, lbl_8035768C, lbl_803576C8, lbl_8035768C, lbl_803576E8,
};
extern "C" const char lbl_80357738[] = "MH_challenge_poihana_a_joint";
extern "C" const char lbl_80357758[] = "MH_challenge_poihana_set_a1_joint";
extern "C" const char lbl_8035777C[] = "MH_challenge_poihana_set_a2_joint";
extern "C" const char lbl_803577A0[] = "MH_challenge_poihana_set_a3_joint";
extern "C" const char lbl_803577C4[] = "MH_challenge_poihana_b_joint";
extern "C" const char lbl_803577E4[] = "MH_challenge_poihana_set_b1_joint";
extern "C" const char lbl_80357808[] = "MH_challenge_poihana_c_joint";
extern "C" const char lbl_80357828[] = "MH_challenge_poihana_set_c1_joint";
extern "C" const char lbl_8035784C[] = "MH_challenge_poihana_d_joint";
extern "C" const char lbl_8035786C[] = "MH_challenge_poihana_set_d1_joint";
extern "C" const char lbl_80357890[] = "MH_challenge_poihana_set_d2_joint";
extern "C" const char lbl_803578B4[] = "MH_challenge_poihana_set_d3_joint";
extern "C" const char *const SuikaBall_801313D0_rodata_803578D8[16] = {
    lbl_80357738, lbl_80357758, lbl_80357738, lbl_8035777C, lbl_80357738, lbl_803577A0, lbl_803577C4, lbl_803577E4, lbl_80357808, lbl_80357828, lbl_8035784C, lbl_8035786C, lbl_8035784C, lbl_80357890, lbl_8035784C, lbl_803578B4,
};
extern "C" const char lbl_80357918[] = "MH_challenge_kinopio.dat";
extern "C" const char lbl_80357934[] = "MH_challenge_kinopio_set.dat";
extern "C" const char lbl_80357954[] = "MH_challenge_monte.dat";
extern "C" const char lbl_8035796C[] = "MH_challenge_monte_set.dat";
extern "C" const char lbl_80357988[] = "MH_challenge_poihana.dat";
extern "C" const char lbl_803579A4[] = "MH_challenge_poihana_set.dat";
static const JointSetDesc s_jointSets[3] = {
    { lbl_80357918, lbl_80357934, SuikaBall_801313D0_rodata_803575C0, 10 },
    { lbl_80357954, lbl_8035796C, SuikaBall_801313D0_rodata_80357708, 6 },
    { lbl_80357988, lbl_803579A4, SuikaBall_801313D0_rodata_803578D8, 8 },
};
extern "C" const Vec3 SuikaBall_Render_rodata_803579F4[4][2] = {
    { { 1603.87f, 0.0f, 875.05f }, { 1659.19f, 0.0f, 958.76f } },
    { { 1166.56f, 0.0f, 949.29f }, { 1142.48f, 0.0f, 1045.98f } },
    { { 648.89f, 0.0f, 991.32f }, { 684.98f, 0.0f, 1083.0f } },
    { { 313.91f, 0.0f, 960.16f }, { 260.2f, 0.0f, 1042.56f } },
};











#include "game/singleton.h"

union GXFifoPipe {
    unsigned char u8;
    unsigned short u16;
    unsigned int u32;
    float f32;
};
#include "game/types/at_address.h"
volatile GXFifoPipe GXWGFifo AT_ADDRESS(0xCC008000);

static inline void GXPosition3f32(float x, float y, float z)
{
    GXWGFifo.f32 = x;
    GXWGFifo.f32 = y;
    GXWGFifo.f32 = z;
}

static inline void GXColor1u32(unsigned int c)
{
    GXWGFifo.u32 = c;
}

static inline int HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    unsigned char result;
    if (!jobj) {
        __assert((const char *)lbl_806D7280, 0x25d, (const char *)lbl_806D7288);
    }
    result = 0;
    if (!(jobj->flags & 0x00800000) && (jobj->flags & 0x40)) {
        result = 1;
    }
    return result;
}

static inline void HSD_JObjSetMtxDirty(HSD_JObj *jobj)
{
    if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj)) {
        HSD_JObjSetMtxDirtySub(jobj);
    }
}

static inline void HSD_JObjGetTranslation(HSD_JObj *jobj, Vec3 *t)
{
    if (!jobj) {
        __assert((const char *)lbl_806D7280, 0x3e4, (const char *)lbl_806D7288);
    }
    t->x = jobj->translate.x;
    t->y = jobj->translate.y;
    t->z = jobj->translate.z;
}

static inline void HSD_JObjSetTranslate(HSD_JObj *jobj, Vec3 *t)
{
    if (!jobj) {
        __assert((const char *)lbl_806D7280, 0x3a9, (const char *)lbl_806D7288);
    }
    jobj->translate.x = t->x;
    jobj->translate.y = t->y;
    jobj->translate.z = t->z;
    if (!(jobj->flags & 0x02000000)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjGetRotation(HSD_JObj *jobj, Quat *q)
{
    if (!jobj) {
        __assert((const char *)lbl_806D7280, 0x2dd, (const char *)lbl_806D7288);
    }
    q->x = jobj->rotate.x;
    q->y = jobj->rotate.y;
    q->z = jobj->rotate.z;
    q->w = jobj->rotate.w;
}

static inline void HSD_JObjSetRotation(HSD_JObj *jobj, Quat *q)
{
    if (!jobj) {
        __assert((const char *)lbl_806D7280, 0x290, (const char *)lbl_806D7288);
    }
    jobj->rotate.x = q->x;
    jobj->rotate.y = q->y;
    jobj->rotate.z = q->z;
    jobj->rotate.w = q->w;
    if (!(jobj->flags & 0x02000000)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjGetScale(HSD_JObj *jobj, Vec3 *s)
{
    if (!jobj) {
        __assert((const char *)lbl_806D7280, 0x351, (const char *)lbl_806D7288);
    }
    s->x = jobj->scale.x;
    s->y = jobj->scale.y;
    s->z = jobj->scale.z;
}

static inline void HSD_JObjSetScale(HSD_JObj *jobj, Vec3 *s)
{
    if (!jobj) {
        __assert((const char *)lbl_806D7280, 0x316, (const char *)lbl_806D7288);
    }
    jobj->scale.x = s->x;
    jobj->scale.y = s->y;
    jobj->scale.z = s->z;
    if (!(jobj->flags & 0x02000000)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void DrawCardWalls(void)
{
    void *cobj;
    float top;
    float bottom;
    int i;

    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxDesc(0xb, 1);
    GXSetVtxAttrFmt(0, 0xb, 1, 5, 0);
    GXSetNumChans(1);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOrder(0, 0xff, 0xff, 4);
    GXSetTevOp(0, 4);
    GXSetZMode(1, 3, 1);
    GXSetBlendMode(1, 4, 5, 0);
    cobj = HSD_CObjGetCurrent();
    if (cobj != 0) {
        GXSetCurrentMtx(0);
        GXLoadPosMtxImm(HSD_CObjGetViewingMtxPtr(cobj), 0);
        GXSetCullMode(0);
    }
    top = -180.0f;
    bottom = -200.0f;
    for (i = 0; i < 4; i++) {
        GXBegin(0x80, 0, 4);
        GXPosition3f32(SuikaBall_Render_rodata_803579F4[i][1].x, top, SuikaBall_Render_rodata_803579F4[i][1].z);
        GXColor1u32(0xE0202000);
        GXPosition3f32(SuikaBall_Render_rodata_803579F4[i][0].x, top, SuikaBall_Render_rodata_803579F4[i][0].z);
        GXColor1u32(0xE0202000);
        GXPosition3f32(SuikaBall_Render_rodata_803579F4[i][0].x, bottom, SuikaBall_Render_rodata_803579F4[i][0].z);
        GXColor1u32(0xE0202080);
        GXPosition3f32(SuikaBall_Render_rodata_803579F4[i][1].x, bottom, SuikaBall_Render_rodata_803579F4[i][1].z);
        GXColor1u32(0xE0202080);
    }
    GXSetCullMode(2);
    HSD_StateInvalidate(0x7e);
}



static inline void Fireworks_Launch(ShotSet *fw, Vec3 *pos, float kx, float kz, float spread)
{
    if (IsCardValid()) {
        int i;
        float heading;
        float angle;
        DebugPrintf("Start to MRCoin.  %s - %d\n", "CGameCoin.hpp", 0x2d8);
        if (fn_8016C360(0xab) == 1) {
            fn_8016C394(0xab);
        }
        SoundMgr_PlaySE(0xab);
        i = 0;
        for (int k = 0; k < 6; k++) {
            if (fw->shots[k].active == 0) {
                i = k;
                break;
            }
        }
        heading = atan2(kx - pos->x, kz - pos->z);
        angle = heading + spread;
        fw->shots[i].active = 1;
        fw->shots[i].timer = 0;
        fw->shots[i].alpha = 0.0f;
        fw->shots[i].rot = 0.0f;
        fw->shots[i].pos.x = pos->x;
        fw->shots[i].pos.y = pos->y;
        fw->shots[i].pos.z = pos->z;
        fw->shots[i].vel.x = 0.7f * LUT_Cosine(angle);
        fw->shots[i].vel.z = 0.7f * LUT_Sine(angle);
        fw->shots[i].vel.y = 1.82f;
    }
}

static inline float Gate_Side(Gate *gate, Vec3 *pos)
{
    Vec3 rel;
    Vec3_Subtract(pos, &gate->pos, &rel);
    return Vec3_Dot(&rel, &gate->normal);
}

static inline bool Gate_IsPassed(Gate *gate, Vec3 *pos)
{
    if (Gate_Side(gate, pos) > 0.0f) {
        return true;
    }
    return false;
}

static inline bool GateList_Update(GateList *list, Vec3 *pos)
{
    if (list->next >= 4) {
        return false;
    }
    if (Gate_IsPassed(list->gates[list->next], pos) == true) {
        list->next++;
        return true;
    }
    return false;
}



static inline int HsdRef_Dec(HsdRefObj *o)
{
    int done = o->ref == (unsigned short)-1;
    if (done) {
        return done;
    }
    return o->ref-- == 0;
}

static inline void HsdObj_Destroy(HsdRefObj *o)
{
    if (o != 0) {
        o->klass->release(o);
        o->klass->destroy(o);
    }
}

static inline void HsdRef_Unref(HsdRefObj *o)
{
    if (o != 0 && HsdRef_Dec(o)) {
        HsdObj_Destroy(o);
    }
}

static inline void FreeBufs(SuikaBall *self)
{
    GateList *bufs = self->bufs;
    if (bufs != 0) {
        for (int i = 0; i < 4; i++) {
            if (bufs->gates[i] != 0) {
                MemoryManager_TimedFree(bufs->gates[i]);
            }
        }
        MemoryManager_TimedFree(bufs);
    }
}



#include "game/types/KartDriver.h"

#include "game/types/InputManager.h"
#include "game/types/Camera.h"
#include "game/types/CarObject.h"
static inline int GetChara() { return g_characterId; }
struct PlayerCar : CarObject {
    PlayerCar(const float *x, const float *z, int chara)
        : CarObject(GetDisplayBufferIndex(), chara, 0, 0, 1, 0, 0, 0, *x, *z, GetCourseStartYaw()) {}
};
#include "game/types/LakituStart.h"
#include "game/types/Scene3D.h"
#include "game/types/ChallengeGoalCamera.h"
#include "game/types/HUD.h"
#include "game/types/WeatherSystem.h"
#include "game/types/clNormal3D.h"

struct ShotVec {
    float x, y, z;
    void Zero() { x = y = z = lbl_806D72B8; }
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

#include "game/types/CoinShotBase.h"

inline CoinShotBase::CoinShotBase(const char *modelFile, const char *trailFile) {
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
        shots[i].rot = lbl_806D72B8;
        shots[i].alpha = lbl_806D72B8;
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

struct SuikaCoinShots : CoinShotBase {
    SuikaCoinShots(const char *modelFile, const char *trailFile) : CoinShotBase(modelFile, trailFile) {}
    virtual ~SuikaCoinShots();
};

struct GVec { float x, y, z; };
static inline GVec MkVec(float x, float y, float z) { GVec v; v.x = x; v.y = y; v.z = z; return v; }
struct GoalLine {
    Vec3 p0, p1, dir, normal;
    GoalLine(GVec a, GVec b) { Set(a, b); }
    void Set(GVec a, GVec b) {
        p0.x = a.x; p0.y = a.y; p0.z = a.z;
        p1.x = b.x; p1.y = b.y; p1.z = b.z;
        Vec3_Subtract(&p1, &p0, &dir);
        Vec3_Normalize(&dir, &dir);
        normal.x = -dir.z; normal.y = dir.y; normal.z = dir.x;
    }
};
struct GoalLineSet {
    GoalLine *lines[4];
    int next;
    GoalLineSet(const Vec3 (*tbl)[2]) {
        next = 0;
        for (int i = 0; i < 4; i++) {
            lines[i] = new GoalLine(*(const GVec *)&tbl[i][0], *(const GVec *)&tbl[i][1]);
        }
    }
};
struct JointSet {
    clNormal3D *a;
    clNormal3D *b;
    void **ja;
    void **jb;
    int count;
};
struct SuikaUnk44 { char data[0xC]; SuikaUnk44(); };
struct SuikaUnk48 { char data[0x10]; SuikaUnk48(); };

/*
 * SuikaBall_Init: the mode's constructor. The goal-line constructor takes
 * its two end points by value and forwards them to Set() by value; that
 * extra copy (and MkVec's local) is what gives the target's stack layout.
 * Float literals in the joint-set loop keep 0.0f from being hoisted into f31.
 */
inline void clCGameMR::AddBallToCamera(void *cam) {
    if (cam != 0 && m3C->archive != 0) {
        SceneRender_CmdB_8aa20(cam, Archive_GetRootJObj(m3C->archive));
    }
}





static inline bool Trail_Spawn(Trail *t, float c, float s)
{
    if (t->age >= 0) {
        return false;
    }
    t->age = 0;
    t->pos.x = 5.0f * LUT_Sin12Bit(360.0f * c);
    t->pos.y = 10.0f * s;
    t->pos.z = 5.0f * fn_80186960(360.0f * c);
    return true;
}







/* Uncalled diagnostic preserves the trailing pooled type names, as in
 * clLineManager::PrintLines (body inferred; pool-order fakematch). */
void clCGameMR::PrintTypeNames() {
    DebugPrintf("clCGameCoinBase");
    DebugPrintf("clCGameMRCoin");
}

/* Deferred code generation emits these in target address order. */
extern "C" ModelPair *fn_80134164(ModelPair *self, short flag)
{
    if (self) {
        self->vt = SuikaCoinShots_vtable_8048E418;
        if (self) {
            self->vt = CoinShotBase_vtable_8048E34C;
            Object_DtorWithGXSync(self->a, 1);
            Object_DtorWithGXSync(self->b, 1);
        }
        if (flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}

extern "C" void fn_80133E64(ShotOwner *self)
{
    Trail *tr;
    int i;
    for (i = 0; i < 6; i++) {
        Shot *s = &((ShotSet *)self)->shots[i];
        if (s->active) {
            tr = s->trail;
            s->pos.x += s->vel.x;
            s->pos.y += s->vel.y;
            s->pos.z += s->vel.z;
            s->vel.y -= 0.1f;
            float h = 0.0f;
            if (Terrain_GetGroundHeightWithPenetration(&s->pos, &h, 0, 0, 10.0f) == 1 && s->pos.y < h) {
                s->vel.y = 0.8f * -s->vel.y;
            }
            s->rot += 5.0f;
            if (s->rot > 360.0f) {
                s->rot -= 360.0f;
            }
            s->alpha = 1.0f - s->timer / 70.0f;
            int j;
            for (j = 0; j < self->trailCount; j++) {
                Trail *t = &tr[j];
                if (t->age >= 0) {
                    t->pos.y -= 2.0f;
                    if (++t->age > 10) {
                        t->age = -1;
                    }
                }
            }
            if ((s->timer & 3) == 0) {
                for (j = 0; j < self->trailCount; j++) {
                    if (Trail_Spawn(&tr[j], lbl_80495994[self->sinIdx], lbl_80495A94[self->cosIdx]) == true) {
                        tr[j].pos.x += s->pos.x;
                        tr[j].pos.y += s->pos.y;
                        tr[j].pos.z += s->pos.z;
                        break;
                    }
                }
                if (++self->sinIdx >= 0x40) {
                    self->sinIdx = 0;
                }
                if (++self->cosIdx >= 0x30) {
                    self->cosIdx = 0;
                }
            }
            if (++s->timer >= 0x46) {
                s->active = 0;
            }
        }
    }
}

extern "C" void fn_80133CA8(ShotOwner *self)
{
    for (int i = 0; i < 6; i++) {
        if (((ShotSet *)self)->shots[i].active) {
            Object_SetJObjPositionVec(self->model, &((ShotSet *)self)->shots[i].pos);
            Object_SetJObjRotationY(self->model, lbl_806D7298 * ((ShotSet *)self)->shots[i].rot);
            Object_SetColorAlphaOnly(self->model, 0, ((ShotSet *)self)->shots[i].alpha);
            Object_RenderJObjEx(self->model, LinkedNode_GetField10_OrFallback(self->model, 0), 7);
            LNode *n = LinkedNode_GetField10_OrFallback(self->model, 0);
            Object_RenderJObjEx(self->model, n == 0 ? 0 : n->f8, 7);
            for (int j = 0; j < self->trailCount; j++) {
                float f = ((ShotSet *)self)->shots[i].trail[j].age / lbl_806D729C;
                float sc = lbl_806D72A0 - f;
                Object_SetJObjPositionVec(self->trailModel, &((ShotSet *)self)->shots[i].trail[j].pos);
                Object_SetJObjScaleXYZ(self->trailModel, sc, sc, sc);
                Object_SetColorAlphaOnly(self->trailModel, 0, (lbl_806D72A4 - f) * ((ShotSet *)self)->shots[i].alpha);
                Object_RenderJObjTree(self->trailModel, 7);
            }
        }
    }
}

clCGameMR::clCGameMR() {
    Vec3 pos;
    float camA, camB;

    courseData = MiniGame_GetCourseData();
    DrawManager_GetOrCreate();
    SetResourceLoadingFlag(0);
    DMAChannelManager_Init();
    TransitionEffect_GetOrCreate();
    SoundChannels_ClearAll();
    ItemObjectManager_Init();
    CourseObjectManager_Init();
    environment = new InputManager;
    m24 = (HsdRefObj *)HSD_LObjLoadDesc(GetCourseDataPtr());
    m20 = (Deletable *)new Camera ARGS_ORDER((lbl_806D72F8, lbl_806D72B4, 0x100, 0x100, (int)m24), (0x100, 0x100, (int)m24, lbl_806D72F8, lbl_806D72B4));
    SetActiveCamera(0, m20);
    g_raceCamera = m20;
    ProcessSystemTick(0);
    RankingTable_Init(GetRaceContextPtr());
    lbl_806D12BC = 0;
    SoundDriver_GetOrCreate(0);
    GetStartPosition(0, &pos.x, &pos.y, &pos.z);
    car = (Destroyable *)new PlayerCar(&pos.x, &pos.z, GetChara());
    CarObject_SetPosition(car, &pos);
    {
        KartDriver *r = (KartDriver *)CarObject_GetRenderObj(car);
        r->visible_238 = 1;
    }
    SetPlayerCarObject(car);
    lakitu = new LakituStart("jyugemu_start.dat", 0, lbl_806D72B8, lbl_806D72B8, lbl_806D72B8);
    m18 = (Deletable *)new Scene3D(*GetKartModelNameEntry(g_characterId, -1));
    m1C = new ChallengeGoalCamera;
    ProcessSystemTick(0);
    Scene3D_GetCameraPos(m18, &camA, &camB);
    camA += lbl_806D729C;
    Scene3D_SetupProjection(m18, camA, camB);
    hud = new HUD(0);
    HUD_RegisterOverlay(hud, 6, 0);
    HUD_RegisterOverlay(hud, 0x11, 0);
    HUD_RegisterOverlay(hud, 0x12, 0);
    HUD_RegisterOverlay(hud, 0xE, 0);
    g_lakituStartAnimDone = 0;
    SetCourseScene3D(m18);
    g_raceEnded = 0;
    g_raceTimeRemaining = MiniGame_GetTimerValue();
    PreloadEffectResources(1);
    PreloadEffectResources(9);
    PreloadEffectResources(0xA);
    active = 0;
    finished = 0;
    goalReached = 0;
    state = 0;
    bgmOn = 0;
    speedScale = lbl_806D72A4;
    prevPos.x = lbl_806D72B8;
    prevPos.y = lbl_806D72B8;
    prevPos.z = lbl_806D72B8;
    if ((m3C = new SuikaBallObj("MRO_suikaball.dat")) != 0) {
        m3C->SetPos(lbl_806D72FC, lbl_806D7300, lbl_806D7304);
        AddBallToCamera(g_raceCamera);
        if (courseData != 0) {
            m3C->SetParams(courseData[0], courseData[1], courseData[2], courseData[3], courseData[4], courseData[5]);
        }
    }
    m44 = (Deletable *)new SuikaUnk44;
    m48 = (Deletable *)new SuikaUnk48;
    m40 = (Gate *)new GoalLine(MkVec(lbl_806D7308, lbl_806D7300, lbl_806D730C), MkVec(lbl_806D7310, lbl_806D7300, lbl_806D7314));
    slots = (SuikaSlot *)FUN_8003b120(sizeof(JointSet) * 3);
    for (unsigned int i = 0; i < 3; i++) {
        JointSet *s = (JointSet *)&slots[i];
        s->a = new clNormal3D(s_jointSets[i].model, 0);
        clNormal3D_SetScale(s->a, 0, 0.0f, 1.0f, 0.0f, 0.0f);
        s->b = new clNormal3D(s_jointSets[i].setModel, 0);
        clNormal3D_SetScale(s->b, 0, 0.0f, 1.0f, 0.0f, 0.0f);
        s->count = s_jointSets[i].count;
        s->ja = (void **)FUN_8003b120(s->count * 4);
        s->jb = (void **)FUN_8003b120(s->count * 4);
        for (int j = 0; j < s->count; j++) {
            s->ja[j] = ResolveJointByName(s->a, s_jointSets[i].joints[j * 2]);
            s->jb[j] = ResolveJointByName(s->b, s_jointSets[i].joints[j * 2 + 1]);
        }
    }
    m60 = (Deletable *)new SuikaCoinShots("mario_coin.dat", "k_kira13.dat");
    bufs = (GateList *)new GoalLineSet(SuikaBall_Render_rodata_803579F4);
    coins = 0;
    if (g_weatherSystem == 0) {
        g_weatherSystem = new WeatherSystem(1);
    }
    SetResourceLoadingFlag(1);
}

clCGameMR::~clCGameMR()
{
    clCGameMR *self = this;
        delete self->m60;
        FreeBufs(self);
        fn_8016C394(0x24);
        if (g_weatherSystem != 0) {
            fn_8016C634(g_weatherSystem, 1);
            g_weatherSystem = 0;
        }
        SetActiveCamera(0, 0);
        delete self->m18;
        LakituStart_Dtor(self->lakitu, 1);
        fn_80124C84(self->m1C, 1);
        SetPlayerCarObject(0);
        if (self->car != 0) {
            self->car->Destroy(1);
        }
        g_raceCamera = 0;
        if (self->m20 != 0) {
            delete self->m20;
        }
        if (self->m24 != 0) {
            HsdRef_Unref(self->m24);
        }
        CourseEnvironment_Dtor(self->environment, 1);
        fn_80254134(self->hud, 1);
        fn_8012491C(self->m3C, 1);
        if (self->m40 != 0) {
            MemoryManager_TimedFree(self->m40);
        }
        delete self->m44;
        delete self->m48;
        if (self->slots != 0) {
            for (unsigned int i = 0; i < 3; i++) {
                if (self->slots[i].bufA != 0) {
                    MemoryManager_Free(self->slots[i].bufA);
                }
                if (self->slots[i].bufB != 0) {
                    MemoryManager_Free(self->slots[i].bufB);
                }
                if (self->slots[i].objA != 0) {
                    Object_DtorWithGXSync(self->slots[i].objA, 1);
                }
                if (self->slots[i].objB != 0) {
                    Object_DtorWithGXSync(self->slots[i].objB, 1);
                }
            }
            MemoryManager_Free(self->slots);
        }
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

int clCGameMR::Update()
{
    clCGameMR *self = this;
    InputPlayer *pad;
    float (*mtx)[4];
    Vec3 delta;
    Vec3 pos;

    if (self->active == 0) {
        self->active = 1;
    }
    if (!IsRaceStarted()) {
        if (self->bgmOn == 0) {
            SoundMgr_Play(0x24);
            SoundMgr_Play(0xd5);
            self->bgmOn = 1;
        }
    } else if (self->bgmOn == 1) {
        fn_80192688(0x24, 1);
        fn_80192688(0xd5, 1);
        self->bgmOn = 0;
    }
    ItemObjectManager_PerFrameUpdate(GetRaceContextPtr());
    pad = InputMgr_GetPlayer(GetInputManager(), 0);
    if (g_raceEnded != 1 && self->state >= 0) {
        float accel;
        float brake;
        unsigned char braking;
        if (lbl_806D1290 == 0) {
            accel = pad->StickRight();
        } else {
            accel = 0.8f;
        }
        brake = pad->StickLeft();
        braking = 0;
        if (accel < 0.1f && brake < 0.1f && IsRaceStarted()) {
            braking = 1;
        }
        if (NokoNokoChallenge_HandleBrakeInput(self, braking) == 1) {
            accel = 1.0f;
        }
        CarObject_ApplyInput(self->car, pad->v2(), accel, brake, IsRaceStarted());
        CarObject_FrameUpdate(self->car, 0);
        KartItem_UpdateShadowBillboardAndViewport(self->car, self->m18, 0);
    } else if (self->state < 0) {
        CarObject_ApplyInput(self->car, 0.0f, 0.0f, 0.0f, 1);
        KartMovement_SetSpeedScale(self->car, 0.5f);
        CarObject_FrameUpdate(self->car, 0);
        KartItem_UpdateShadowBillboardAndViewport(self->car, self->m18, 0);
    } else {
        CarObject_ApplyInput(self->car, 0.0f, 0.0f, 0.0f, 1);
        KartMovement_SetSpeedScale(self->car, 0.5f);
        CarObject_FrameUpdate(self->car, 0);
        ChallengeGoalCamera_Update(self->m1C, self->m18, KartDriver_GetKartRootMtx(CarObject_GetRenderObj(self->car)));
    }
    Fog_UpdateFromCourseScene3D();
    LakituStart_UpdateCountdown(self->lakitu);
    CourseEnvironment_UpdateAndCullZones_Timed(self->environment);

    mtx = KartDriver_GetKartRootMtx(CarObject_GetRenderObj(self->car));
    pos.x = mtx[0][3];
    pos.y = mtx[1][3];
    pos.z = mtx[2][3];
    Vec3_Subtract(&pos, &self->prevPos, &delta);
    self->prevPos.x = pos.x;
    self->prevPos.y = pos.y;
    self->prevPos.z = pos.z;
    SuikaBallObj_UpdatePhysics(self->m3C, mtx, &delta, 12.0f);
    if (self->m3C->hit) {
        KartReaction_Rear(CarObject_GetRenderObj(self->car));
        SoundMgr_PlaySE(0x5d);
        self->speedScale = 0.3f;
    } else {
        self->speedScale += 0.01f;
        if (self->speedScale > 1.0f) {
            self->speedScale = 1.0f;
        }
    }
    KartMovement_SetSpeedScale(self->car, self->speedScale);
    self->m44->Begin();
    self->m48->Begin();

    if (self->finished == 0) {
        float kx;
        float kz;

        mtx = KartDriver_GetKartRootMtx(CarObject_GetRenderObj(self->car));
        kx = mtx[0][3];
        kz = mtx[2][3];
        pos.x = self->m3C->pos.x;
        pos.y = self->m3C->pos.y;
        pos.z = self->m3C->pos.z;
        if (Gate_Side(self->m40, &pos) > 0.0f) {
            self->m3C->goal = 1;
            self->goalReached = 1;
            self->finished = 1;
            self->state = -50;
            self->coins += 5;
            Fireworks_Launch((ShotSet *)self->m60, &pos, kx, kz, 0.0f);
            Fireworks_Launch((ShotSet *)self->m60, &pos, kx, kz, 0.5235987f);
            Fireworks_Launch((ShotSet *)self->m60, &pos, kx, kz, -0.5235987f);
            Fireworks_Launch((ShotSet *)self->m60, &pos, kx, kz, 1.570796f);
            Fireworks_Launch((ShotSet *)self->m60, &pos, kx, kz, -1.570796f);
        }
        if (GateList_Update(self->bufs, &pos) == true) {
            if (self->bufs->next <= 3) {
                Fireworks_Launch((ShotSet *)self->m60, &pos, kx, kz, 0.5235987f);
                Fireworks_Launch((ShotSet *)self->m60, &pos, kx, kz, -0.5235987f);
                self->coins += 2;
            } else {
                Fireworks_Launch((ShotSet *)self->m60, &pos, kx, kz, 0.5235987f);
                Fireworks_Launch((ShotSet *)self->m60, &pos, kx, kz, -0.5235987f);
                Fireworks_Launch((ShotSet *)self->m60, &pos, kx, kz, 1.570796f);
                Fireworks_Launch((ShotSet *)self->m60, &pos, kx, kz, -1.570796f);
                self->coins += 4;
            }
        }
    }

    for (unsigned int i = 0; i < 3; i++) {
        SuikaSlot *slot = &self->slots[i];
        clNormal3D_Exec(slot->objA);
        clNormal3D_Exec(slot->objB);
    }
    self->m60->Begin();
    CObj_LoadProjMatrix(self->m18, &SuikaBall_Update_bss_80677C70);
    CObj_ApplyScissor(self->m18, &SuikaBall_Update_bss_80677C7C);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(SuikaBall_Update_bss_80677C70, SuikaBall_Update_bss_80677C7C);
    if (IsRaceStarted() && self->finished == 0 && g_raceTimeRemaining >= 0.0f) {
        g_raceTimeRemaining -= 0.016666668f;
        if (g_raceTimeRemaining < 0.0f) {
            g_raceTimeRemaining = 0.0f;
            self->finished = 1;
            KartMovement_ResetOnTimeout(CarObject_GetRenderObj(self->car));
        }
    }
    fn_80253FD8(self->hud, g_raceTimeRemaining);
    fn_80253EBC(self->hud, 100.0f * CarObject_CalcSpeedRatio(self->car));
    fn_80253EC0(self->hud, KartItem_GetCurrentSpeedWithBonus(self->car));
    HUD_FrameUpdate(self->hud);
    TransitionEffect_Tick(SINGLETON_INSTANCE(lbl_806D109C));
    if (self->finished != 0) {
        if (self->state == 0) {
            SetCoinCount(self->coins);
            fn_80192688(0xd5, 2);
            if (self->goalReached != 0) {
                KartMovement_ResetOnGoal(CarObject_GetRenderObj(self->car));
                fn_80253C74(self->hud, 1, NokoNokoChallenge_CalcResultText(self, 1, 0), 0);
                Object_SetByte10_Return1(self->m18, 1);
                SoundMgr_Play(0xd6);
            } else {
                fn_80253C74(self->hud, 0, NokoNokoChallenge_CalcResultText(self, 0, 0), 0);
                Object_SetByte10_Return1(self->m18, 1);
            }
            NokoNokoChallenge_SaveResult(self, self->coins, self->goalReached);
            g_raceEnded = 1;
            g_lakituStartAnimDone = 0;
        } else if (self->state > 0 && fn_80253C40(self->hud)) {
            return NokoNokoChallenge_TransitionToResult(self);
        }
        self->state++;
    }
    if (g_weatherSystem != 0) {
        fn_8016B32C(g_weatherSystem);
    }
    return -2;
}

void clCGameMR::Draw()
{
    clCGameMR *self = this;
    if (self->active == 0) {
        return;
    }
    if (self->m18->Begin() == 1) {
        clDrawMan_Buckets_Reset(SINGLETON_INSTANCE(lbl_806D10AC));
        TransparentDraw_SortAndDispatch();
        CObj_DebugVizPathFlush(self->m18);
        fn_8016B0C4();
        KartItem_RenderPipelinedWithEffects(self->car, 0);
        Object_RenderJObjIfWithinRange(self->lakitu);
        CourseEnvironment_RenderObjects_Timed(self->environment);
        Subsystem36c_DispatchPass2_Timed(self->environment);
        ItemObjectManager_Render();
        SuikaBallObj_Render(self->m3C);
        self->m44->End();
        self->m48->End();
        for (unsigned int i = 0; i < 3; i++) {
            SuikaSlot *slot = &self->slots[i];
            for (int j = 0; j < slot->count; j++) {
                if (slot->bufB[j] != 0 && slot->bufA[j] != 0) {
                    Vec3 v;
                    Quat q;
                    HSD_JObjGetTranslation(slot->bufB[j], &v);
                    HSD_JObjSetTranslate(slot->bufA[j], &v);
                    HSD_JObjGetRotation(slot->bufB[j], &q);
                    HSD_JObjSetRotation(slot->bufA[j], &q);
                    HSD_JObjGetScale(slot->bufB[j], &v);
                    HSD_JObjSetScale(slot->bufA[j], &v);
                    Object_RenderJObjEx(slot->objA, slot->bufA[j], 7);
                }
            }
        }
        fn_80253448(self->hud, lbl_806DC190);
        DrawEffect_TickAndCull();
        if (IsCardValid()) {
            DrawCardWalls();
        }
        self->m60->End();
        clDrawMan_EndFrame_NoOp(SINGLETON_INSTANCE(lbl_806D10AC));
        clDrawMan_Buckets_Dispatch(SINGLETON_INSTANCE(lbl_806D10AC));
        Subsystem36c_DispatchPass4_Timed(self->environment);
        TransitionEffect_RenderPass(SINGLETON_INSTANCE(lbl_806D109C), 2);
        TransitionEffect_RenderPass(SINGLETON_INSTANCE(lbl_806D109C), 4);
        fn_80253448(self->hud, lbl_806DC1B0 | lbl_806DC190);
        self->m18->End();
    }
    fn_80253448(self->hud, lbl_806DC1B8);
    fn_802535D4(self->hud);
    TransitionEffect_RenderPass(SINGLETON_INSTANCE(lbl_806D109C), 1);
    HSD_StateInvalidate(0x7f);
}
