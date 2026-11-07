
#include "game/singleton.h"
/* sdata symbols referenced from asm */
extern unsigned char lbl_806D7084[7];
extern unsigned char lbl_806D708C[5];
/*
 * 0x801287F8..0x8012A5AC: Noko Noko challenge and time trial scene.
 */
#pragma cplusplus on

typedef struct { float x, y, z; } Vec;
void *operator new(unsigned long size);
void operator delete(void *p);

struct Vec3 { float x, y, z; };
struct LNode { char pad[8]; void *f8; };
struct Trail { int age; Vec3 pos; };
struct Shot {
    char pad0[0x14];
    int active;
    char pad18[4];
    int timer;
    Vec3 pos;
    Vec3 vel;
    float rot;
    float alpha;
    Trail trail[18];
    char pad160[0xc];
};
struct ShotSet {
    Shot shots[6];
};
struct ShotOwner {
    char pad0[4];
    void *model;
    void *trailModel;
    int phaseA;
    int phaseB;
    char pad14[0x89c - 0x14];
    int trailCount;
};

struct ModelPair {
    void **vt;
    void *a;
    void *b;
};

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
void GetCourseDataPtr(void);
int HSD_LObjLoadDesc(void);
void SetActiveCamera(int idx, void *camera);
void ProcessSystemTick(int arg);
void *GetRaceContextPtr(void);
void RankingTable_Init(void *ctx);
void SoundDriver_GetOrCreate(int arg);
int GetDisplayBufferIndex(void);
void GetStartPosition(int idx, float *x, float *y, float *z);
float GetCourseStartYaw(void);
struct RenderObj *CarObject_GetRenderObj(void *car);
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
extern void CObj_ApplyScissor();
extern void CObj_LoadProjMatrix();
extern void CarObject_ApplyInput();
extern void CarObject_CalcSpeedRatio();
extern void CarObject_FrameUpdate();
extern void ChallengeGoalCamera_Update();
extern void Clamp_Int();
extern void CourseEnvironment_UpdateAndCullZones_Timed();
extern void DebugPrintf();
extern void Fog_UpdateFromCourseScene3D();
extern void GetInputManager();
extern void HSD_JObjSetupMatrixSub();
extern void HUD_FrameUpdate();
extern void InputMgr_GetPlayer();
extern void IsCardValid();
extern void IsRaceStarted();
extern void ItemObjectManager_PerFrameUpdate();
extern void ItemObjectManager_Update();
extern void KartDriver_GetKartRootMtx();
extern void KartItem_GetCarVelocityVec3();
extern void KartItem_GetCurrentISESlot();
extern void KartItem_GetCurrentSpeedWithBonus();
extern void KartItem_UpdateShadowBillboardAndViewport();
extern void KartMovement_CanReceiveItem();
extern void KartMovement_ResetOnGoal();
extern void KartMovement_ResetOnTimeout();
extern void KartMovement_SetSpeedScale();
extern void LakituStart_UpdateCountdown();
extern void NokoNokoChallenge_CalcResultText();
extern void NokoNokoChallenge_GetCoinDivisor();
extern void NokoNokoChallenge_HandleBrakeInput();
extern void NokoNokoChallenge_SaveResult();
extern void NokoNokoChallenge_TransitionToResult();
extern void NokoNoko_CheckHitAndKill();
extern void NokoNoko_CountDefeated();
extern void NokoNoko_FindNearest();
extern void NokoNoko_StopAllAlive();
extern void NokoNoko_UpdateAll();
extern void Object_SetByte10_Return1();
extern void RenderObj_UseItem();
extern void ResolveJointByName();
extern void SetCoinCount();
extern void SoundMgr_PlaySE();
extern void TransitionEffect_Tick();
extern void Vec3_Dot();
extern void Vec3_Normalize();
extern void Vec3_Subtract();
extern void VfxSlotMgr_Update();
extern void __assert();
extern void fn_8011FAFC();
extern void fn_80121E10();
extern void fn_8016B32C();
extern void fn_8016C360();
extern void fn_8016C394();
extern void fn_80253C40();
extern void fn_80253C74();
extern void fn_80253EBC();
extern void fn_80253EC0();
extern void fn_80253FD8();
extern unsigned int lbl_806D1290;
extern const float lbl_806D7054;
extern unsigned int lbl_806D7074;
extern unsigned int lbl_806D7078;
extern unsigned int lbl_806D707C;
extern unsigned int lbl_806D7080;
extern unsigned int lbl_806D7094;
extern unsigned int lbl_806D7098;
extern unsigned int lbl_806D709C;
extern unsigned int lbl_806D70A0;
extern unsigned int lbl_806D70A4;
extern unsigned int lbl_806D70A8;
extern const unsigned int lbl_803561E8[0x10C];
extern unsigned int lbl_80677C58[];
extern unsigned int lbl_80677C64[];
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
extern void *lbl_8048E338[];
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
extern void *lbl_8048E34C[];
extern void *lbl_8048E36C[];
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
asm void NokoNokoChallenge_Update(void);
TimeTrialMode *TimeTrial_Destroy(TimeTrialMode *self, short flag);
void fn_8012A070(ShotOwner *self);
void fn_8012A22C(ShotOwner *self);
ModelPair *fn_8012A52C(ModelPair *self, short flag);

#pragma section R ".extab_user"

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_NokoNokoChallenge_Update = { 0x308A0000, 0x00000258, 0x028F0010, 0x00000000, 0x8200002C, (void *)&dtor_80036E40 };






#pragma section R ".extabindex_user"

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_NokoNokoChallenge_Update = {
    (void *)&NokoNokoChallenge_Update, 0x00000CBC, (void *)&extab_NokoNokoChallenge_Update
};






}





/* .rodata 0x803561E8..0x80356708, owned by this TU (pool base of the mode ctor). */
struct IconPos { float x, y; };

extern "C" const unsigned int lbl_803561E8[0x10C] = {
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
extern "C" const char lbl_80356658[] = "clCGameDK";
extern "C" const char lbl_80356664[] = "clJobRunner";
extern "C" const char lbl_80356670[] = "Start to DKCoin.  %s - %d\n";
extern "C" const char lbl_8035668C[] = "CGameCoin.hpp";
extern "C" const char lbl_8035669C[] = "item_center_joint";
static const char s_lakituFile[20] = "jyugemu_start.dat";
static const char s_coinFile[16] = "mario_coin.dat";
static const char s_kiraFile[16] = "k_kira13.dat";
extern "C" const char lbl_803566E4[] = "clCGameCoinBase";
extern "C" const char lbl_803566F4[] = "clCGameDKCoin";

extern "C" void TimeTrial_Render(TimeTrialMode *self)
{
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

extern "C" asm void NokoNokoChallenge_Update(void) { /* 0x801289B8 size:0xCBC */
    nofralloc
    stwu r1, -0xa0(r1)
    mflr r0
    stw r0, 0xa4(r1)
    stfd f31, 0x90(r1)
    psq_st f31, 0x98(r1), 0, 0
    stfd f30, 0x80(r1)
    psq_st f30, 0x88(r1), 0, 0
    stmw r26, 0x68(r1)
    mr r28, r3
    lis r3, lbl_803561E8@ha
    lbz r0, 0x34(r28)
    addi r30, r3, lbl_803561E8@l
    cmplwi r0, 0x0
    bne NokoNokoChallenge_Update_L_801289F8
    li r0, 0x1
    stb r0, 0x34(r28)
    NokoNokoChallenge_Update_L_801289F8:
    bl GetRaceContextPtr
    bl ItemObjectManager_PerFrameUpdate
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lbz r0, g_raceEnded(r13)
    mr r26, r3
    cmplwi r0, 0x1
    beq NokoNokoChallenge_Update_L_80128AF0
    lbz r0, lbl_806D1290(r13)
    cmplwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80128A40
    lwz r12, 0x0(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    fmr f31, f1
    b NokoNokoChallenge_Update_L_80128A44
    NokoNokoChallenge_Update_L_80128A40:
    lfs f31, lbl_806D7068(r2)
    NokoNokoChallenge_Update_L_80128A44:
    lwz r12, 0x0(r26)
    mr r3, r26
    lwz r12, 0x1c(r12)
    mtctr r12
    bctrl
    lfs f0, lbl_806D706C(r2)
    fmr f30, f1
    li r29, 0x0
    fcmpo cr0, f31, f0
    bge NokoNokoChallenge_Update_L_80128A84
    fcmpo cr0, f30, f0
    bge NokoNokoChallenge_Update_L_80128A84
    bl IsRaceStarted
    clrlwi. r0, r3, 24
    beq NokoNokoChallenge_Update_L_80128A84
    li r29, 0x1
    NokoNokoChallenge_Update_L_80128A84:
    mr r3, r28
    mr r4, r29
    bl NokoNokoChallenge_HandleBrakeInput
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne NokoNokoChallenge_Update_L_80128AA0
    lfs f31, lbl_806D7058(r2)
    NokoNokoChallenge_Update_L_80128AA0:
    bl IsRaceStarted
    mr r29, r3
    mr r3, r26
    lwz r12, 0x0(r26)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    fmr f2, f31
    lwz r3, 0x8(r28)
    fmr f3, f30
    mr r4, r29
    bl CarObject_ApplyInput
    lwz r3, 0x8(r28)
    li r4, 0x0
    bl CarObject_FrameUpdate
    lwz r3, 0x8(r28)
    li r5, 0x0
    lwz r4, 0x14(r28)
    bl KartItem_UpdateShadowBillboardAndViewport
    b NokoNokoChallenge_Update_L_80128B5C
    NokoNokoChallenge_Update_L_80128AF0:
    lfs f1, lbl_806D7070(r2)
    li r4, 0x1
    lwz r3, 0x8(r28)
    fmr f2, f1
    fmr f3, f1
    bl CarObject_ApplyInput
    lwz r3, 0x8(r28)
    lfs f1, lbl_806D7074(r2)
    bl KartMovement_SetSpeedScale
    lwz r3, 0x8(r28)
    li r4, 0x0
    bl CarObject_FrameUpdate
    lwz r0, 0x38(r28)
    cmpwi r0, 0x0
    ble NokoNokoChallenge_Update_L_80128B40
    lwz r3, 0x8(r28)
    li r5, 0x0
    lwz r4, 0x14(r28)
    bl KartItem_UpdateShadowBillboardAndViewport
    b NokoNokoChallenge_Update_L_80128B5C
    NokoNokoChallenge_Update_L_80128B40:
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    bl KartDriver_GetKartRootMtx
    mr r5, r3
    lwz r3, 0x18(r28)
    lwz r4, 0x14(r28)
    bl ChallengeGoalCamera_Update
    NokoNokoChallenge_Update_L_80128B5C:
    bl IsRaceStarted
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne NokoNokoChallenge_Update_L_80128BB4
    lbz r0, g_raceEnded(r13)
    cmplwi r0, 0x1
    beq NokoNokoChallenge_Update_L_80128BB4
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    li r4, 0x1
    bl KartMovement_CanReceiveItem
    clrlwi. r0, r3, 24
    beq NokoNokoChallenge_Update_L_80128BB4
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    li r4, 0x0
    li r5, 0x0
    bl RenderObj_UseItem
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    li r0, -0x1
    stw r0, 0x290(r3)
    NokoNokoChallenge_Update_L_80128BB4:
    bl Fog_UpdateFromCourseScene3D
    lwz r3, 0xc(r28)
    bl LakituStart_UpdateCountdown
    lwz r3, 0x10(r28)
    bl CourseEnvironment_UpdateAndCullZones_Timed
    lwz r3, 0x30(r28)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    bl KartDriver_GetKartRootMtx
    lfs f0, 0xc(r3)
    addi r4, r1, 0x44
    lfs f1, lbl_806D7078(r2)
    stfs f0, 0x50(r1)
    lfs f0, 0x1c(r3)
    stfs f0, 0x54(r1)
    lfs f0, 0x2c(r3)
    addi r3, r1, 0x50
    stfs f0, 0x58(r1)
    bl NokoNoko_CheckHitAndKill
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne NokoNokoChallenge_Update_L_80128DA8
    lwz r3, 0x8(r28)
    addi r4, r1, 0x2c
    bl KartItem_GetCarVelocityVec3
    lfs f3, 0x44(r1)
    addi r3, r1, 0x38
    lfs f2, 0x50(r1)
    mr r4, r3
    lfs f1, 0x4c(r1)
    lfs f0, 0x58(r1)
    fsubs f3, f3, f2
    lfs f2, lbl_806D7070(r2)
    fsubs f0, f1, f0
    stfs f3, 0x38(r1)
    stfs f2, 0x3c(r1)
    stfs f0, 0x40(r1)
    bl Vec3_Normalize
    lfs f4, lbl_806D7080(r2)
    lfs f3, 0x2c(r1)
    lfs f2, 0x38(r1)
    lfs f1, 0x34(r1)
    lfs f0, 0x40(r1)
    fmadds f2, f4, f3, f2
    lfs f3, lbl_806D707C(r2)
    fmadds f1, f4, f1, f0
    lfs f0, lbl_806D7054(r2)
    fmuls f2, f3, f2
    stfs f0, 0x3c(r1)
    fmuls f0, f3, f1
    stfs f2, 0x38(r1)
    stfs f0, 0x40(r1)
    lwz r29, 0x44(r28)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq NokoNokoChallenge_Update_L_80128DA8
    addi r3, r30, 0x488
    addi r4, r30, 0x4a4
    li r5, 0x386
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne NokoNokoChallenge_Update_L_80128CD4
    li r3, 0xab
    bl fn_8016C394
    NokoNokoChallenge_Update_L_80128CD4:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r29)
    li r3, 0x0
    cmpwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80128CF4
    li r3, 0x0
    b NokoNokoChallenge_Update_L_80128D54
    NokoNokoChallenge_Update_L_80128CF4:
    lwz r0, 0x180(r29)
    cmpwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80128D08
    li r3, 0x1
    b NokoNokoChallenge_Update_L_80128D54
    NokoNokoChallenge_Update_L_80128D08:
    lwz r0, 0x2ec(r29)
    cmpwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80128D1C
    li r3, 0x2
    b NokoNokoChallenge_Update_L_80128D54
    NokoNokoChallenge_Update_L_80128D1C:
    lwz r0, 0x458(r29)
    cmpwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80128D30
    li r3, 0x3
    b NokoNokoChallenge_Update_L_80128D54
    NokoNokoChallenge_Update_L_80128D30:
    lwz r0, 0x5c4(r29)
    cmpwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80128D44
    li r3, 0x4
    b NokoNokoChallenge_Update_L_80128D54
    NokoNokoChallenge_Update_L_80128D44:
    lwz r0, 0x730(r29)
    cmpwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80128D54
    li r3, 0x5
    NokoNokoChallenge_Update_L_80128D54:
    mulli r3, r3, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D7070(r2)
    add r3, r29, r3
    stw r4, 0x14(r3)
    stw r0, 0x1c(r3)
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x44(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x48(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x4c(r1)
    stfs f0, 0x28(r3)
    lfs f0, 0x38(r1)
    stfs f0, 0x2c(r3)
    lfs f0, 0x40(r1)
    stfs f0, 0x34(r3)
    lfs f0, 0x3c(r1)
    stfs f0, 0x30(r3)
    NokoNokoChallenge_Update_L_80128DA8:
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    bl KartItem_GetCurrentISESlot
    cmplwi r3, 0x0
    beq NokoNokoChallenge_Update_L_80128DC4
    lwz r3, 0x18(r3)
    b NokoNokoChallenge_Update_L_80128DC8
    NokoNokoChallenge_Update_L_80128DC4:
    li r3, 0x0
    NokoNokoChallenge_Update_L_80128DC8:
    cmplwi r3, 0x0
    beq NokoNokoChallenge_Update_L_80129008
    lwz r3, 0x18(r3)
    cmplwi r3, 0x0
    beq NokoNokoChallenge_Update_L_80129008
    addi r4, r30, 0x4b4
    bl ResolveJointByName
    mr. r26, r3
    beq NokoNokoChallenge_Update_L_80129008
    bne NokoNokoChallenge_Update_L_80128E00
    la r3, lbl_806D7084(r2)  /* lbl_806D7084 */
    li r4, 0x47c
    la r5, lbl_806D708C(r2)  /* lbl_806D708C */
    bl __assert
    NokoNokoChallenge_Update_L_80128E00:
    cmplwi r26, 0x0
    beq NokoNokoChallenge_Update_L_80128E48
    bne NokoNokoChallenge_Update_L_80128E1C
    la r3, lbl_806D7084(r2)  /* lbl_806D7084 */
    li r4, 0x25d
    la r5, lbl_806D708C(r2)  /* lbl_806D708C */
    bl __assert
    NokoNokoChallenge_Update_L_80128E1C:
    lwz r4, 0x14(r26)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne NokoNokoChallenge_Update_L_80128E38
    rlwinm. r0, r4, 0, 25, 25
    beq NokoNokoChallenge_Update_L_80128E38
    li r3, 0x1
    NokoNokoChallenge_Update_L_80128E38:
    clrlwi. r0, r3, 24
    beq NokoNokoChallenge_Update_L_80128E48
    mr r3, r26
    bl HSD_JObjSetupMatrixSub
    NokoNokoChallenge_Update_L_80128E48:
    lfs f0, 0x50(r26)
    addi r3, r1, 0x50
    lfs f1, lbl_806D7094(r2)
    addi r4, r1, 0x44
    stfs f0, 0x50(r1)
    lfs f0, 0x60(r26)
    stfs f0, 0x54(r1)
    lfs f0, 0x70(r26)
    stfs f0, 0x58(r1)
    bl NokoNoko_CheckHitAndKill
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne NokoNokoChallenge_Update_L_80129008
    lwz r3, 0x8(r28)
    addi r4, r1, 0x2c
    bl KartItem_GetCarVelocityVec3
    lfs f3, 0x44(r1)
    addi r3, r1, 0x38
    lfs f2, 0x50(r1)
    mr r4, r3
    lfs f1, 0x4c(r1)
    lfs f0, 0x58(r1)
    fsubs f3, f3, f2
    lfs f2, lbl_806D7070(r2)
    fsubs f0, f1, f0
    stfs f3, 0x38(r1)
    stfs f2, 0x3c(r1)
    stfs f0, 0x40(r1)
    bl Vec3_Normalize
    lfs f4, lbl_806D7080(r2)
    lfs f3, 0x2c(r1)
    lfs f2, 0x38(r1)
    lfs f1, 0x34(r1)
    lfs f0, 0x40(r1)
    fmadds f2, f4, f3, f2
    lfs f3, lbl_806D707C(r2)
    fmadds f1, f4, f1, f0
    lfs f0, lbl_806D7054(r2)
    fmuls f2, f3, f2
    stfs f0, 0x3c(r1)
    fmuls f0, f3, f1
    stfs f2, 0x38(r1)
    stfs f0, 0x40(r1)
    lwz r29, 0x44(r28)
    bl IsCardValid
    clrlwi. r0, r3, 24
    beq NokoNokoChallenge_Update_L_80129008
    addi r3, r30, 0x488
    addi r4, r30, 0x4a4
    li r5, 0x386
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0xab
    bl fn_8016C360
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne NokoNokoChallenge_Update_L_80128F34
    li r3, 0xab
    bl fn_8016C394
    NokoNokoChallenge_Update_L_80128F34:
    li r3, 0xab
    bl SoundMgr_PlaySE
    lwz r0, 0x14(r29)
    li r3, 0x0
    cmpwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80128F54
    li r3, 0x0
    b NokoNokoChallenge_Update_L_80128FB4
    NokoNokoChallenge_Update_L_80128F54:
    lwz r0, 0x180(r29)
    cmpwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80128F68
    li r3, 0x1
    b NokoNokoChallenge_Update_L_80128FB4
    NokoNokoChallenge_Update_L_80128F68:
    lwz r0, 0x2ec(r29)
    cmpwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80128F7C
    li r3, 0x2
    b NokoNokoChallenge_Update_L_80128FB4
    NokoNokoChallenge_Update_L_80128F7C:
    lwz r0, 0x458(r29)
    cmpwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80128F90
    li r3, 0x3
    b NokoNokoChallenge_Update_L_80128FB4
    NokoNokoChallenge_Update_L_80128F90:
    lwz r0, 0x5c4(r29)
    cmpwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80128FA4
    li r3, 0x4
    b NokoNokoChallenge_Update_L_80128FB4
    NokoNokoChallenge_Update_L_80128FA4:
    lwz r0, 0x730(r29)
    cmpwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80128FB4
    li r3, 0x5
    NokoNokoChallenge_Update_L_80128FB4:
    mulli r3, r3, 0x16c
    li r4, 0x1
    li r0, 0x0
    lfs f0, lbl_806D7070(r2)
    add r3, r29, r3
    stw r4, 0x14(r3)
    stw r0, 0x1c(r3)
    stfs f0, 0x3c(r3)
    stfs f0, 0x38(r3)
    lfs f0, 0x44(r1)
    stfs f0, 0x20(r3)
    lfs f0, 0x48(r1)
    stfs f0, 0x24(r3)
    lfs f0, 0x4c(r1)
    stfs f0, 0x28(r3)
    lfs f0, 0x38(r1)
    stfs f0, 0x2c(r3)
    lfs f0, 0x40(r1)
    stfs f0, 0x34(r3)
    lfs f0, 0x3c(r1)
    stfs f0, 0x30(r3)
    NokoNokoChallenge_Update_L_80129008:
    bl NokoNoko_UpdateAll
    lbz r0, g_raceEnded(r13)
    cmplwi r0, 0x1
    beq NokoNokoChallenge_Update_L_80129240
    bl NokoNoko_CountDefeated
    lwz r5, 0x40(r28)
    mr r31, r3
    li r4, 0x0
    bl Clamp_Int
    mr r6, r3
    lwz r29, 0x2c(r28)
    cmpwi r6, 0x63
    ble NokoNokoChallenge_Update_L_80129040
    li r6, 0x63
    NokoNokoChallenge_Update_L_80129040:
    lis r4, 0x6666
    addi r3, r29, 0x108
    addi r5, r4, 0x6667
    mulhw r0, r5, r6
    srawi r0, r0, 2
    srwi r4, r0, 31
    add r0, r0, r4
    mulli r0, r0, 0xa
    subf r26, r0, r6
    subf r0, r26, r6
    mulhw r0, r5, r0
    srawi r0, r0, 2
    srwi r4, r0, 31
    add r27, r0, r4
    bl fn_80121E10
    addi r3, r29, 0x160
    bl fn_80121E10
    cmpwi r27, 0x0
    li r0, 0x1ecd
    beq NokoNokoChallenge_Update_L_80129094
    addi r0, r27, 0x14ba
    NokoNokoChallenge_Update_L_80129094:
    stw r0, 0x108(r29)
    addi r3, r30, 0x430
    addi r4, r26, 0x14ba
    li r0, 0x1
    stw r4, 0x160(r29)
    lfs f0, 0x18(r3)
    stb r0, 0x118(r29)
    lfs f1, 0x1c(r3)
    stfs f0, 0x11c(r29)
    lfs f0, lbl_806D7058(r2)
    stfs f1, 0x120(r29)
    lfs f1, 0x20(r3)
    stfs f0, 0x124(r29)
    lfs f2, 0x24(r3)
    stb r0, 0x170(r29)
    stfs f1, 0x174(r29)
    stfs f2, 0x178(r29)
    stfs f0, 0x17c(r29)
    lwz r0, 0x40(r28)
    cmpw r31, r0
    blt NokoNokoChallenge_Update_L_80129118
    bl NokoNoko_StopAllAlive
    li r3, 0x1
    li r0, 0x1e
    stb r3, 0x36(r28)
    stw r0, 0x38(r28)
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    li r4, 0x0
    li r0, 0x1
    stw r4, 0x290(r3)
    stb r0, g_raceEnded(r13)
    b NokoNokoChallenge_Update_L_80129240
    NokoNokoChallenge_Update_L_80129118:
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    bl KartDriver_GetKartRootMtx
    mr r29, r3
    addi r3, r1, 0x50
    lfs f0, 0xc(r29)
    addi r4, r1, 0x20
    stfs f0, 0x50(r1)
    lfs f0, 0x1c(r29)
    stfs f0, 0x54(r1)
    lfs f0, 0x2c(r29)
    stfs f0, 0x58(r1)
    bl NokoNoko_FindNearest
    clrlwi. r0, r3, 24
    beq NokoNokoChallenge_Update_L_80129240
    addi r3, r1, 0x20
    addi r4, r1, 0x50
    mr r5, r3
    bl Vec3_Subtract
    addi r3, r1, 0x20
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0x8(r29)
    addi r3, r1, 0x50
    mr r4, r3
    stfs f0, 0x50(r1)
    lfs f0, 0x18(r29)
    stfs f0, 0x54(r1)
    lfs f0, 0x28(r29)
    stfs f0, 0x58(r1)
    bl Vec3_Normalize
    addi r3, r1, 0x20
    addi r4, r1, 0x50
    bl Vec3_Dot
    lfs f0, lbl_806D7098(r2)
    fcmpo cr0, f1, f0
    ble NokoNokoChallenge_Update_L_801291C0
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    lfs f0, lbl_806D7070(r2)
    stfs f0, 0x294(r3)
    b NokoNokoChallenge_Update_L_80129240
    NokoNokoChallenge_Update_L_801291C0:
    lfs f0, lbl_806D709C(r2)
    fcmpo cr0, f1, f0
    ble NokoNokoChallenge_Update_L_80129230
    lfs f0, 0x0(r29)
    addi r3, r1, 0x50
    mr r4, r3
    stfs f0, 0x50(r1)
    lfs f0, 0x10(r29)
    stfs f0, 0x54(r1)
    lfs f0, 0x20(r29)
    stfs f0, 0x58(r1)
    bl Vec3_Normalize
    addi r3, r1, 0x20
    addi r4, r1, 0x50
    bl Vec3_Dot
    lfs f0, lbl_806D7070(r2)
    fcmpo cr0, f1, f0
    ble NokoNokoChallenge_Update_L_8012921C
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    lfs f0, lbl_806D7058(r2)
    stfs f0, 0x294(r3)
    b NokoNokoChallenge_Update_L_80129240
    NokoNokoChallenge_Update_L_8012921C:
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    lfs f0, lbl_806D7054(r2)
    stfs f0, 0x294(r3)
    b NokoNokoChallenge_Update_L_80129240
    NokoNokoChallenge_Update_L_80129230:
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    lfs f0, lbl_806D7070(r2)
    stfs f0, 0x294(r3)
    NokoNokoChallenge_Update_L_80129240:
    lwz r3, 0x44(r28)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    lis r4, lbl_80677C58@ha
    lwz r3, 0x14(r28)
    addi r4, r4, lbl_80677C58@l
    bl CObj_LoadProjMatrix
    lis r4, lbl_80677C64@ha
    lwz r3, 0x14(r28)
    addi r4, r4, lbl_80677C64@l
    bl CObj_ApplyScissor
    bl ItemObjectManager_Update
    lis r3, lbl_80677C64@ha
    lis r4, lbl_80677C58@ha
    addi r5, r3, lbl_80677C64@l
    addi r3, r1, 0x14
    addi r7, r4, lbl_80677C58@l
    lwz r10, 0x0(r5)
    lwz r9, 0x4(r5)
    addi r4, r1, 0x8
    lwz r8, 0x8(r5)
    lwz r6, 0x0(r7)
    lwz r5, 0x4(r7)
    lwz r0, 0x8(r7)
    stw r10, 0x8(r1)
    stw r9, 0xc(r1)
    stw r8, 0x10(r1)
    stw r6, 0x14(r1)
    stw r5, 0x18(r1)
    stw r0, 0x1c(r1)
    bl VfxSlotMgr_Update
    bl IsRaceStarted
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne NokoNokoChallenge_Update_L_80129328
    lbz r0, g_raceEnded(r13)
    cmplwi r0, 0x1
    beq NokoNokoChallenge_Update_L_80129328
    lfs f2, g_raceTimeRemaining(r13)
    lfs f1, lbl_806D7070(r2)
    fcmpo cr0, f2, f1
    cror eq, gt, eq
    bne NokoNokoChallenge_Update_L_80129328
    lfs f0, lbl_806D70A0(r2)
    fsubs f0, f2, f0
    fcmpo cr0, f0, f1
    stfs f0, g_raceTimeRemaining(r13)
    bge NokoNokoChallenge_Update_L_80129328
    stfs f1, g_raceTimeRemaining(r13)
    bl NokoNoko_StopAllAlive
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    li r4, 0x0
    li r0, 0x1
    stw r4, 0x290(r3)
    stb r0, g_raceEnded(r13)
    NokoNokoChallenge_Update_L_80129328:
    lwz r3, 0x28(r28)
    lfs f1, g_raceTimeRemaining(r13)
    bl fn_80253FD8
    lwz r3, 0x8(r28)
    bl CarObject_CalcSpeedRatio
    lfs f0, lbl_806D70A4(r2)
    lwz r3, 0x28(r28)
    fmuls f1, f0, f1
    bl fn_80253EBC
    lwz r3, 0x8(r28)
    bl KartItem_GetCurrentSpeedWithBonus
    lwz r3, 0x28(r28)
    bl fn_80253EC0
    lwz r3, 0x28(r28)
    bl HUD_FrameUpdate
    lwz r27, 0x2c(r28)
    lbz r0, 0x2c0(r27)
    cmplwi r0, 0x0
    beq NokoNokoChallenge_Update_L_801294A0
    lfs f1, 0x2c4(r27)
    lfs f8, lbl_806D7058(r2)
    fcmpo cr0, f1, f8
    cror eq, gt, eq
    beq NokoNokoChallenge_Update_L_801294C0
    lfs f0, lbl_806D706C(r2)
    addi r3, r30, 0x430
    lfs f7, lbl_806D70A8(r2)
    li r0, 0x1
    fadds f2, f1, f0
    lfs f1, 0x430(r30)
    lfs f3, 0x4(r3)
    lfs f0, 0x8(r3)
    stfs f2, 0x2c4(r27)
    lfs f6, 0xc(r3)
    lfs f2, 0x2c4(r27)
    lfs f5, 0x10(r3)
    fmadds f1, f7, f2, f1
    stb r0, 0x10(r27)
    lfs f31, 0x14(r3)
    lfs f4, 0x18(r3)
    stfs f1, 0x14(r27)
    lfs f13, 0x1c(r3)
    stfs f3, 0x18(r27)
    lfs f3, 0x20(r3)
    stfs f8, 0x1c(r27)
    lfs f12, 0x24(r3)
    lfs f1, 0x2c4(r27)
    lfs f2, 0x28(r3)
    fmadds f0, f7, f1, f0
    stb r0, 0x68(r27)
    lfs f11, 0x2c(r3)
    lfs f1, 0x30(r3)
    stfs f0, 0x6c(r27)
    lfs f10, 0x34(r3)
    stfs f6, 0x70(r27)
    lfs f0, 0x38(r3)
    stfs f8, 0x74(r27)
    lfs f9, 0x3c(r3)
    lfs f6, 0x2c4(r27)
    fmadds f5, f7, f6, f5
    stb r0, 0xc0(r27)
    stfs f5, 0xc4(r27)
    stfs f31, 0xc8(r27)
    stfs f8, 0xcc(r27)
    lfs f5, 0x2c4(r27)
    fmadds f4, f7, f5, f4
    stb r0, 0x118(r27)
    stfs f4, 0x11c(r27)
    stfs f13, 0x120(r27)
    stfs f8, 0x124(r27)
    lfs f4, 0x2c4(r27)
    fmadds f3, f7, f4, f3
    stb r0, 0x170(r27)
    stfs f3, 0x174(r27)
    stfs f12, 0x178(r27)
    stfs f8, 0x17c(r27)
    lfs f3, 0x2c4(r27)
    fmadds f2, f7, f3, f2
    stb r0, 0x1c8(r27)
    stfs f2, 0x1cc(r27)
    stfs f11, 0x1d0(r27)
    stfs f8, 0x1d4(r27)
    lfs f2, 0x2c4(r27)
    fmadds f1, f7, f2, f1
    stb r0, 0x220(r27)
    stfs f1, 0x224(r27)
    stfs f10, 0x228(r27)
    stfs f8, 0x22c(r27)
    lfs f1, 0x2c4(r27)
    fmadds f0, f7, f1, f0
    stb r0, 0x278(r27)
    stfs f0, 0x27c(r27)
    stfs f9, 0x280(r27)
    stfs f8, 0x284(r27)
    NokoNokoChallenge_Update_L_801294A0:
    li r26, 0x0
    NokoNokoChallenge_Update_L_801294A4:
    mr r3, r27
    li r4, 0x0
    bl fn_8011FAFC
    addi r26, r26, 0x1
    addi r27, r27, 0x58
    cmpwi r26, 0x8
    blt NokoNokoChallenge_Update_L_801294A4
    NokoNokoChallenge_Update_L_801294C0:
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne NokoNokoChallenge_Update_L_801294D0
    li r3, 0x0
    NokoNokoChallenge_Update_L_801294D0:
    bl TransitionEffect_Tick
    lbz r0, g_raceEnded(r13)
    cmplwi r0, 0x1
    bne NokoNokoChallenge_Update_L_8012963C
    lwz r3, 0x38(r28)
    cmpwi r3, 0x0
    ble NokoNokoChallenge_Update_L_801294F8
    subi r0, r3, 0x1
    stw r0, 0x38(r28)
    b NokoNokoChallenge_Update_L_8012963C
    NokoNokoChallenge_Update_L_801294F8:
    lwz r0, 0x3c(r28)
    cmpwi r0, 0x0
    bne NokoNokoChallenge_Update_L_80129614
    li r26, 0x0
    bl NokoNokoChallenge_GetCoinDivisor
    mr. r29, r3
    beq NokoNokoChallenge_Update_L_8012953C
    bl NokoNoko_CountDefeated
    lwz r0, 0x40(r28)
    mr r26, r3
    cmpw r26, r0
    ble NokoNokoChallenge_Update_L_8012952C
    mr r26, r0
    NokoNokoChallenge_Update_L_8012952C:
    lwz r0, 0x0(r29)
    divw r26, r26, r0
    mr r3, r26
    bl SetCoinCount
    NokoNokoChallenge_Update_L_8012953C:
    lbz r0, 0x36(r28)
    cmplwi r0, 0x0
    beq NokoNokoChallenge_Update_L_8012959C
    bl NokoNoko_CountDefeated
    lwz r5, 0x40(r28)
    li r4, 0x0
    bl Clamp_Int
    mr r29, r3
    mr r3, r28
    li r4, 0x1
    li r5, 0x0
    bl NokoNokoChallenge_CalcResultText
    mr r5, r3
    lwz r3, 0x28(r28)
    mr r6, r29
    li r4, 0x1
    bl fn_80253C74
    lwz r3, 0x2c(r28)
    li r0, 0x1
    stb r0, 0x2c0(r3)
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    bl KartMovement_ResetOnGoal
    b NokoNokoChallenge_Update_L_801295EC
    NokoNokoChallenge_Update_L_8012959C:
    bl NokoNoko_CountDefeated
    lwz r5, 0x40(r28)
    li r4, 0x0
    bl Clamp_Int
    mr r29, r3
    mr r3, r28
    li r4, 0x0
    li r5, 0x0
    bl NokoNokoChallenge_CalcResultText
    mr r5, r3
    lwz r3, 0x28(r28)
    mr r6, r29
    li r4, 0x0
    bl fn_80253C74
    lwz r3, 0x2c(r28)
    li r0, 0x1
    stb r0, 0x2c0(r3)
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    bl KartMovement_ResetOnTimeout
    NokoNokoChallenge_Update_L_801295EC:
    lbz r5, 0x36(r28)
    mr r3, r28
    mr r4, r26
    bl NokoNokoChallenge_SaveResult
    lwz r3, 0x14(r28)
    li r4, 0x1
    bl Object_SetByte10_Return1
    li r0, 0x0
    stb r0, g_lakituStartAnimDone(r13)
    b NokoNokoChallenge_Update_L_80129630
    NokoNokoChallenge_Update_L_80129614:
    lwz r3, 0x28(r28)
    bl fn_80253C40
    clrlwi. r0, r3, 24
    beq NokoNokoChallenge_Update_L_80129630
    mr r3, r28
    bl NokoNokoChallenge_TransitionToResult
    b NokoNokoChallenge_Update_L_80129650
    NokoNokoChallenge_Update_L_80129630:
    lwz r3, 0x3c(r28)
    addi r0, r3, 0x1
    stw r0, 0x3c(r28)
    NokoNokoChallenge_Update_L_8012963C:
    lwz r3, g_weatherSystem(r13)
    cmplwi r3, 0x0
    beq NokoNokoChallenge_Update_L_8012964C
    bl fn_8016B32C
    NokoNokoChallenge_Update_L_8012964C:
    li r3, -0x2
    NokoNokoChallenge_Update_L_80129650:
    psq_l f31, 0x98(r1), 0, 0
    lfd f31, 0x90(r1)
    psq_l f30, 0x88(r1), 0, 0
    lfd f30, 0x80(r1)
    lmw r26, 0x68(r1)
    lwz r0, 0xa4(r1)
    mtlr r0
    addi r1, r1, 0xa0
    blr
}

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

extern "C" TimeTrialMode *TimeTrial_Destroy(TimeTrialMode *self, short flag)
{
    if (self) {
        self->vt = lbl_8048E338;
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
        dtor_80122FD8(self, 0);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

/* NokoNokoChallenge_Init (0x80129938): constructor of the Noko Noko
 * challenge mode, the same minigame-ctor shape as JumpDistanceMode_Init.
 * The TU owns .rodata 0x803561E8..0x80356708, so the icon table and the
 * model file names are addressed off one pool base (r30). Mangled names
 * are mapped in tools/extab_user_renames.json. */
#pragma exceptions on

struct RenderObj {
    char pad0[0x238];
    int x238;
    char pad23C[0x94];
    unsigned char x2D0;
};

struct InputManager { char data[0x37C]; InputManager(); };
struct Camera { char data[0x2C]; Camera(float a, float b, int w, int h, int target); };
struct CarObject {
    char data[0x118];
    CarObject(int disp, int chara, int cc, int a, int b, int c, int d, int e, float x, float z, float yaw);
};
static inline int GetChara() { return g_characterId; }
struct PlayerCar : CarObject {
    PlayerCar(const float *x, const float *z, int chara)
        : CarObject(GetDisplayBufferIndex(), chara, 0, 0, 1, 1, 0, 0, *x, *z, GetCourseStartYaw()) {}
};
struct LakituStart { char data[0x58]; LakituStart(const void *data, int arg, float x, float y, float z); };
struct Scene3D { char data[0x3084]; Scene3D(int name); };
struct ChallengeGoalCamera { char data[8]; ChallengeGoalCamera(); };
struct MapWaterEffect { char data[0x10]; MapWaterEffect(); };
struct HUD { char data[0x80]; HUD(int arg); };
struct WeatherSystem { char data[0x1B4]; WeatherSystem(int arg); };
struct clNormal3D { char data[0x5C]; clNormal3D(const char *file, int arg); };

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

struct CoinShotBase {
    virtual ~CoinShotBase();
    clNormal3D *model;
    clNormal3D *trailModel;
    int xC;
    int x10;
    CoinShot shots[6];
    int trailCount;
    CoinShotBase(const char *modelFile, const char *trailFile);
};

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

struct CoinShots : CoinShotBase {
    CoinShots(const char *modelFile, const char *trailFile) : CoinShotBase(modelFile, trailFile) {
        Object_SetJObjScaleXYZ(model, lbl_806D70C4, lbl_806D70C4, lbl_806D70C4);
    }
    virtual ~CoinShots();
};

struct GameModeBase {
    virtual void _key();
    virtual ~GameModeBase();
    GameModeBase();
};

struct ModeBase : GameModeBase {
    float x4;
    ModeBase() {
        x4 = lbl_806D7070;
    }
    virtual void _key2();
    virtual ~ModeBase();
};


struct NokoNokoChallenge : ModeBase {
    virtual void _key3();
    CarObject *car;
    LakituStart *lakitu;
    InputManager *input;
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
    CoinShots *shots;
    NokoNokoChallenge();
};

NokoNokoChallenge::NokoNokoChallenge() {
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
    GetCourseDataPtr();
    renderTarget = HSD_LObjLoadDesc();
    camera = new Camera(lbl_806D70BC, lbl_806D706C, 0x100, 0x100, renderTarget);
    SetActiveCamera(0, camera);
    g_raceCamera = camera;
    ProcessSystemTick(0);
    RankingTable_Init(GetRaceContextPtr());
    lbl_806D12BC = 0;
    SoundDriver_GetOrCreate(0);
    GetStartPosition(0, &x, 0, &z);
    car = new PlayerCar(&x, &z, GetChara());
    {
        RenderObj *r = CarObject_GetRenderObj(car);
        r->x238 = 1;
    }
    {
        RenderObj *r = CarObject_GetRenderObj(car);
        r->x2D0 = 1;
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
    shots = new CoinShots(s_coinFile, s_kiraFile);
    if (g_weatherSystem == 0) {
        g_weatherSystem = new WeatherSystem(1);
    }
    SetResourceLoadingFlag(1);
}

extern "C" void fn_8012A070(ShotOwner *self)
{
    for (int i = 0; i < 6; i++) {
        if (((ShotSet *)self)->shots[i].active) {
            Object_SetJObjPositionVec(self->model, &((ShotSet *)self)->shots[i].pos);
            Object_SetJObjRotationY(self->model, lbl_806D704C * ((ShotSet *)self)->shots[i].rot);
            Object_SetColorAlphaOnly(self->model, 0, ((ShotSet *)self)->shots[i].alpha);
            Object_RenderJObjEx(self->model, LinkedNode_GetField10_OrFallback(self->model, 0), 7);
            LNode *n = LinkedNode_GetField10_OrFallback(self->model, 0);
            Object_RenderJObjEx(self->model, n == 0 ? 0 : n->f8, 7);
            for (int j = 0; j < self->trailCount; j++) {
                float f = ((ShotSet *)self)->shots[i].trail[j].age / lbl_806D7050;
                float sc = lbl_806D7054 - f;
                Object_SetJObjPositionVec(self->trailModel, &((ShotSet *)self)->shots[i].trail[j].pos);
                Object_SetJObjScaleXYZ(self->trailModel, sc, sc, sc);
                Object_SetColorAlphaOnly(self->trailModel, 0, (lbl_806D7058 - f) * ((ShotSet *)self)->shots[i].alpha);
                Object_RenderJObjTree(self->trailModel, 7);
            }
        }
    }
}

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

extern "C" void fn_8012A22C(ShotOwner *self)
{
    Shot *s;
    Trail *trails;
    int i;
    int j;

    for (i = 0; i < 6; i++) {
        s = &((ShotSet *)self)->shots[i];
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
            for (j = 0; j < self->trailCount; j++) {
                if (trails[j].age >= 0) {
                    trails[j].pos.y -= 2.0f;
                    if (++trails[j].age > 10) {
                        trails[j].age = -1;
                    }
                }
            }
            if ((s->timer & 3) == 0) {
                for (j = 0; j < self->trailCount; j++) {
                    if (Trail_Spawn(&trails[j], lbl_80495994[self->phaseA], lbl_80495A94[self->phaseB]) == 1) {
                        trails[j].pos.x += s->pos.x;
                        trails[j].pos.y += s->pos.y;
                        trails[j].pos.z += s->pos.z;
                        break;
                    }
                }
                if (++self->phaseA >= 0x40) {
                    self->phaseA = 0;
                }
                if (++self->phaseB >= 0x30) {
                    self->phaseB = 0;
                }
            }
            if (++s->timer >= 0x5a) {
                s->active = 0;
            }
        }
    }
}

extern "C" ModelPair *fn_8012A52C(ModelPair *self, short flag)
{
    if (self) {
        self->vt = lbl_8048E36C;
        if (self) {
            self->vt = lbl_8048E34C;
            Object_DtorWithGXSync(self->a, 1);
            Object_DtorWithGXSync(self->b, 1);
        }
        if (flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}

