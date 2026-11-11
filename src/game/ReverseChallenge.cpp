/* Reverse-run minigame: real clCGameWC and compiler-emitted RTTI. */
#include "game/singleton.h"
#include "game/types/clJobRunner.h"
struct clCGame : clJobRunner {
    float phase;
    clCGame() { phase = 0.0f; }
    virtual ~clCGame();
};
extern "C" {
/* === extracted from auto_ReverseChallenge_Dto_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ClRomTable_PurgeAll();
extern void CourseEnvironment_Dtor(void *, int);
extern void *GetRaceContextPtr();
extern void ItemObjectManager_Reset();
extern void LakituStart_Dtor(void *, int);
extern void MemoryManager_TimedFree(void *);
extern void RankingTable_Init(void *);
extern void SceneDrawList_Reset();
extern void SetActiveCamera(int, void *);
extern void SetPlayerCarObject(void *);
extern void SetResourceLoadingFlag(int);
extern void VfxSlotMgr_Shutdown();
extern void clRom_PurgeAll();
extern void dtor_80122FD8(void *, int);
extern void fn_80124C84(void *, int);
extern void fn_8016C634(void *, int);
extern void fn_80254134(void *, int);

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_raceCamera;
extern unsigned int g_weatherSystem;
extern unsigned int lbl_806D109C;
extern unsigned int lbl_806D10AC;
extern unsigned int lbl_806D10D0;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int ReverseChallenge_vtable_80419E70[];

/* --- function index (1 fns, .text 0x800ACD60..0x800ACFC0) ---
 * [  0] 0x800ACD60 size:0x260   global ReverseChallenge_Dtor
 */

}
/* --- native C++ island (deleting-destructor shape, see RivalRun.c) --- */
struct RCVirtual {
    virtual ~RCVirtual();
};
struct RCCarVirtual {
    virtual void key();
    virtual ~RCCarVirtual();
};
struct RCLight;
struct RCLightInfo {
    unsigned char pad0[0x30];
    void (*release)(RCLight *);
    void (*destroy)(RCLight *);
};
struct RCLight {
    RCLightInfo *info;
    unsigned short references;
};

static inline int RCLightRefDec(RCLight *obj)
{
    unsigned char unreferenced;
    if ((unreferenced = (obj->references == (unsigned short)0xFFFF)))
        return unreferenced;
    return obj->references-- == 0;
}
static inline void RCLightDelete(RCLight *obj)
{
    if (obj) {
        obj->info->release(obj);
        obj->info->destroy(obj);
    }
}
static inline void RCLightUnref(RCLight *obj)
{
    if (obj && RCLightRefDec(obj))
        RCLightDelete(obj);
}
static inline void RCCameraRelease(RCVirtual *camera)
{
    if (camera)
        delete camera;
}

/* === extracted from auto_ReverseChallenge_Ren_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls --- */
struct RevScene {
    virtual void Slot8();
    virtual unsigned char IsRenderReady();
    virtual void RenderTail();
};

extern "C" {
extern const unsigned int lbl_806DC1B0;
extern const unsigned int lbl_806DC190;
extern const unsigned int lbl_806DC1B8;
void clDrawMan_Buckets_Reset(void *);
void TransparentDraw_SortAndDispatch(void);
void CObj_DebugVizPathFlush(void *);
void fn_8016B0C4(void);
void KartItem_RenderPipelinedWithEffects(void *, int);
void Object_RenderJObjIfWithinRange(void *);
void CourseEnvironment_RenderObjects_Timed(void *);
void Subsystem36c_DispatchPass2_Timed(void *);
void ItemObjectManager_Render(void);
void BananaField_Render(void *);
void DrawEffect_TickAndCull(void);
void clDrawMan_EndFrame_NoOp(void *);
void clDrawMan_Buckets_Dispatch(void *);
void Subsystem36c_DispatchPass4_Timed(void *);
void TransitionEffect_RenderPass(void *, int);
void fn_80253448(void *, unsigned int);
void fn_802535D4(void *);
void HSD_StateInvalidate(int);
}



/* --- function index (1 fns, .text 0x800ACFC0..0x800AD134) ---
 * [  0] 0x800ACFC0 size:0x174   global ReverseChallenge_Render
 */

/* ReverseChallenge_Update (0x800AD134..0x800AD910): per-frame update of the
 * reverse-run challenge (drive the course backwards inside the start quad,
 * reach the goal plane before the timer runs out). Same frame as
 * MiniGame_CoinChallenge_Update. */

typedef struct RCVec3 { float x, y, z; } RCVec3;
#include "game/types/RCQuadPtsC.h"

struct RCInput {
    virtual void slot08();
    virtual void slot0c();
    virtual float steering();
    virtual void slot14();
    virtual float accelerator();
    virtual float brake();
};
extern "C" {

typedef struct RCCarData { char pad0[0x1c8]; float yaw; } RCCarData;
typedef struct RCCar { char pad0[0x28]; RCCarData *data; } RCCar;
typedef struct RCGoal { RCVec3 pos; char padC[0x18]; RCVec3 normal; } RCGoal;
typedef struct RCBanana { char pad0[0xc]; unsigned char hit; } RCBanana;
typedef struct RCHitInfo {
    char pad0[8];
    int kind;
    char padC[0x94];
    RCVec3 pos;
    char padAC[0x1ec - 0xac];
} RCHitInfo;
typedef struct RCCoinTier { int limit; int coins; } RCCoinTier;


extern void *CarObject_GetRenderObj(void *car);
extern void BananaField_CheckCollision(RCBanana *field, void *mtx, RCVec3 *delta);
extern void CObj_ApplyScissor(void *cam, void *out);
extern void CObj_ApplyViewport(void *cam, void *in);
extern void CObj_LoadIntoGX(void *cam, void *in);
extern void CObj_LoadProjMatrix(void *cam, void *out);
#ifdef __MWERKS__
extern void CarObject_ApplyInput(RCCar *car, float steer, float accel, float brake, unsigned char started);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void CarObject_ApplyInput(RCCar *, unsigned char, float, float, float);
static inline void CarObject_ApplyInput_Reordered(RCCar * a0, float a1, float a2, float a3, unsigned char a4) { CarObject_ApplyInput(a0, a4, a1, a2, a3); }
#define CarObject_ApplyInput CarObject_ApplyInput_Reordered
#endif
extern float CarObject_CalcSpeedRatio(RCCar *car);
extern void CarObject_FrameUpdate(RCCar *car, int arg);
extern void CarObject_HandleObstacleHit(RCCar *car, RCHitInfo *info);
extern void ChallengeGoalCamera_Update(void *goalCam, void *cam, void *mtx);
extern void CourseEnvironment_UpdateAndCullZones_Timed(void *env);
extern void Fog_UpdateFromCourseScene3D(void);
extern void *GetInputManager(void);
extern void HUD_FrameUpdate(void *hud);
extern RCInput *InputMgr_GetPlayer(void *mgr, int index);
extern unsigned char IsRaceStarted(void);
extern void ItemObjectManager_PerFrameUpdate(void *ctx);
extern void ItemObjectManager_Update(void);
extern float (*KartDriver_GetKartRootMtx(void *obj))[4];
extern float KartItem_GetCurrentSpeedWithBonus(RCCar *car);
extern void KartItem_UpdateShadowBillboardAndViewport(RCCar *car, void *cam, int arg);
extern void KartMovement_ResetOnGoal(void *obj);
extern void KartMovement_ResetOnTimeout(void *obj);
extern void KartMovement_SetSpeedScale(RCCar *car, float scale);
extern void LakituStart_UpdateCountdown(void *lakitu);
extern int MiniGame_GetTimerValue(void);
extern void Mtx44_GetTranslation_RowMajor(RCVec3 *out, void *mtx);
extern int NokoNokoChallenge_CalcResultText(void *self, int won, int arg);
extern RCCoinTier **NokoNokoChallenge_GetCoinDivisor(void);
extern unsigned char NokoNokoChallenge_HandleBrakeInput(void *self, int holding);
extern void NokoNokoChallenge_SaveResult(void *self, int coins, unsigned char won);
extern int NokoNokoChallenge_TransitionToResult(void *self);
extern int Object_SetByte10_Return1(void *obj, int value);
extern void SetCoinCount(int coins);
extern void TransitionEffect_Tick(void *fx);
extern void Vec2_RotateY(RCVec3 *out, RCVec3 *in, float angle);
extern void Vec3_Add_DestFirst(RCVec3 *out, RCVec3 *a, RCVec3 *b);
extern float Vec3_Dot(RCVec3 *a, RCVec3 *b);
extern void Vec3_Subtract(void *a, void *b, void *out);
extern void Vec3_Subtract_DestFirst(RCVec3 *out, RCVec3 *a, RCVec3 *b);
#ifdef __MWERKS__
extern void VfxSlotMgr_Update(RCVec3 proj, RCVec3 scissor);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void VfxSlotMgr_Update(RCVec3 *, RCVec3 *);
static inline void VfxSlotMgr_Update_ByValue(RCVec3 proj, RCVec3 scissor) { VfxSlotMgr_Update(&proj, &scissor); }
#define VfxSlotMgr_Update VfxSlotMgr_Update_ByValue
#endif
extern void fn_8016B32C(void *weather);
extern unsigned char fn_80253C40(void *hud);
extern void fn_80253C74(void *hud, int won, int text, int time);
extern void fn_80253EBC(void *hud, float v);
extern void fn_80253EC0(void *hud, float v);
extern void fn_80253FD8(void *hud, float v);
extern void *memset(void *p, int c, unsigned long n);

extern unsigned int g_lakituStartAnimDone;
extern unsigned int g_raceEnded;
extern unsigned int g_raceTimeRemaining;
extern unsigned int g_weatherSystem;
extern unsigned int lbl_806D109C;
extern unsigned char lbl_806D1290;
extern unsigned int lbl_806D4F48;
extern unsigned int lbl_806D4F4C;
extern unsigned int lbl_806D4F50;
extern unsigned int lbl_806D4F54;
extern unsigned int lbl_806D4F58;
extern unsigned int lbl_806D4F5C;
extern unsigned int lbl_806D4F60;
extern unsigned int lbl_806D4F64;
extern unsigned int lbl_806D4F68;

extern const RCQuadPtsC ReverseChallenge_rodata_80328DD8 = {
    { {1045.0f,-340.0f}, {913.4f,250.0f}, {650.0f,330.9f}, {650.0f,-150.0f} }
};
extern RCVec3 ReverseChallenge_Update_bss_805DF338;
extern RCVec3 ReverseChallenge_Update_bss_805DF344;

#define RCF(x) (*(const float *)&(x))
#define RC_ENDED (*(unsigned char *)&g_raceEnded)
#define RC_TIME (*(float *)&g_raceTimeRemaining)

static inline unsigned char RC_InsideStartQuad(RCVec3 *p, float *n)
{
    float dx = p->x - ReverseChallenge_rodata_80328DD8.p[1][0];
    float dz = -(p->z - ReverseChallenge_rodata_80328DD8.p[1][1]);
    float zero = RCF(lbl_806D4F54);
    if (dz * n[0] + dx * n[1] > zero) {
        return 0;
    }
    if (dz * n[2] + dx * n[3] > zero) {
        return 0;
    }
    dx = p->x - ReverseChallenge_rodata_80328DD8.p[3][0];
    dz = -(p->z - ReverseChallenge_rodata_80328DD8.p[3][1]);
    if (dz * n[4] + dx * n[5] > zero) {
        return 0;
    }
    if (dz * n[6] + dx * n[7] > zero) {
        return 0;
    }
    return 1;
}

static inline int RC_PastGoal(RCVec3 *p, RCGoal *goal)
{
    RCVec3 v;
    Vec3_Subtract(p, goal, &v);
    return Vec3_Dot(&v, &goal->normal) > RCF(lbl_806D4F54);
}

/* --- function index (1 fns, .text 0x800AD134..0x800AD910) ---
 * [  0] 0x800AD134 size:0x7DC   global ReverseChallenge_Update
 */
}
extern "C" {
#include "game/types/arg_order.h"
/* === extracted from auto_ReverseChallenge_Ini_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
#include "game/types/size_t.h"
extern float BuildOrientationFromYaw(float yaw);
extern void *CarObject_GetRenderObj(void *car);
extern void CarObject_ResetPhysics(void *car, int arg);
extern void CarObject_SetPosition(void *car, void *pos);
extern void CourseObjectManager_Init();
extern void DMAChannelManager_Init();
extern void DrawManager_GetOrCreate();
extern void *GetCourseDataPtr(void);
extern float GetCourseStartYaw(void);
extern int GetDisplayBufferIndex(void);
extern int *GetKartModelNameEntry(int chara, int arg);
extern void *GetRaceContextPtr();
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern void HUD_RegisterOverlay(void *hud, int id, int arg);
extern int IsUraCourseFromSubMode(void);
extern void ItemObjectManager_Init();
extern int MiniGame_GetTimerValue(void);
extern void PreloadEffectResources(int id);
extern void ProcessSystemTick(int arg);
extern void RankingTable_Init(void *);
extern int HSD_LObjLoadDesc(void *desc);
extern void Scene3D_GetCameraPos(void *scene, float *a, float *b);
extern void Scene3D_SetupProjection(void *scene, float a, float b);
extern void SetActiveCamera(int, void *);
extern void SetCourseScene3D(void *scene);
extern void SetPlayerCarObject(void *);
extern void SetResourceLoadingFlag(int);
extern void SoundChannels_ClearAll();
extern void SoundDriver_GetOrCreate(int arg);
extern void TransitionEffect_GetOrCreate();
extern void Vec3_Normalize(void *src, void *dst);
extern void Vec3_Subtract(void *a, void *b, void *out);

/* --- extern decls: sda21-referenced data --- */
extern int g_characterId;
extern unsigned int g_lakituStartAnimDone;
extern unsigned int g_raceCamera;
extern unsigned int g_raceEnded;
extern unsigned int g_raceTimeRemaining;
extern unsigned int g_weatherSystem;
extern int lbl_806D12BC;
extern unsigned int lbl_806D4F50;
extern unsigned int lbl_806D4F54;
extern unsigned int lbl_806D4F5C;
extern unsigned int lbl_806D4F70;
extern unsigned int lbl_806D4F78;
extern unsigned int lbl_806D4F7C;
extern unsigned int lbl_806D4F80;
extern unsigned int lbl_806D4F84;
extern unsigned int lbl_806D4F88;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */

extern unsigned int ReverseChallenge_vtable_80419E70[];
extern unsigned int lbl_8048E144[];

/* --- function index (1 fns, .text 0x800AD910..0x800ADDA0) ---
 * [  0] 0x800AD910 size:0x490   global ReverseChallenge_Init
 */

/* --- native C++ ctor (same shape as JumpDistanceMode_Init.c) --- */
} 
void *operator new(size_t size);
void operator delete(void *p);

typedef struct RCVec { float x, y, z; } RCVec;
struct RCInputManager { char data[0x37C]; RCInputManager(); };
struct RCCamera { char data[0x2C]; RCCamera ARGS_ORDER((float a, float b, int w, int h, int target), (int w, int h, int target, float a, float b)); };
struct RCCarObject {
    char data[0x118];
    RCCarObject(int disp, int chara, int a, int b, int c, int d, int e, int f, float x, float z, float yaw);
};
struct RCPlayerCar : RCCarObject {
    RCPlayerCar(RCVec *pos, int chara)
        : RCCarObject(GetDisplayBufferIndex(), chara, 0, 0, 1, 0, 0, 0, pos->x, pos->z,
                      BuildOrientationFromYaw(GetCourseStartYaw() + 3.141592f)) {}
};
struct RCRenderObj { char pad0[0x238]; int x238; };
struct RCLakituStart { char data[0x58]; RCLakituStart(const void *data, int arg, float x, float y, float z); };
struct RCScene3D { char data[0x3084]; RCScene3D(int name); };
struct RCGoalCamera { char data[8]; RCGoalCamera(); };
struct RCHUD { char data[0x80]; RCHUD(int arg); };
struct RCBananaData { char data[0x10]; RCBananaData(int ura); };
struct RCWeatherSystem { char data[0x1B4]; RCWeatherSystem(int arg); };

struct RCDirLine {
    RCVec a;
    RCVec b;
    RCVec dir;
    RCVec normal;
    RCDirLine() {
        a.x = 150.0f;
        a.y = 0.0f;
        a.z = -3100.0f;
        b.x = -150.0f;
        b.y = 0.0f;
        b.z = -3100.0f;
        Vec3_Subtract(&b, &a, &dir);
        Vec3_Normalize(&dir, &dir);
        normal.x = -dir.z;
        normal.y = dir.y;
        normal.z = dir.x;
    }
};

struct RCQuadPts { float p[4][2]; };
struct RCQuadEdges {
    float e[4][2];
    RCQuadEdges() {
        e[0][0] = ReverseChallenge_rodata_80328DD8.p[1][0] - ReverseChallenge_rodata_80328DD8.p[0][0];
        e[0][1] = ReverseChallenge_rodata_80328DD8.p[1][1] - ReverseChallenge_rodata_80328DD8.p[0][1];
        e[1][0] = ReverseChallenge_rodata_80328DD8.p[2][0] - ReverseChallenge_rodata_80328DD8.p[1][0];
        e[1][1] = ReverseChallenge_rodata_80328DD8.p[2][1] - ReverseChallenge_rodata_80328DD8.p[1][1];
        e[2][0] = ReverseChallenge_rodata_80328DD8.p[3][0] - ReverseChallenge_rodata_80328DD8.p[2][0];
        e[2][1] = ReverseChallenge_rodata_80328DD8.p[3][1] - ReverseChallenge_rodata_80328DD8.p[2][1];
        e[3][0] = ReverseChallenge_rodata_80328DD8.p[0][0] - ReverseChallenge_rodata_80328DD8.p[3][0];
        e[3][1] = ReverseChallenge_rodata_80328DD8.p[0][1] - ReverseChallenge_rodata_80328DD8.p[3][1];
    }
};


struct clCGameWC : clCGame {
    virtual int Update();
    virtual void Draw();
    virtual ~clCGameWC();
    RCInputManager *environment;
    RCCamera *camera;
    int renderTarget;
    RCCarObject *car;
    RCLakituStart *lakitu;
    RCScene3D *scene;
    RCGoalCamera *goalCam;
    RCHUD *hud;
    RCDirLine *dirLine;
    RCQuadEdges *edges;
    RCBananaData *banana;
    float x34, x38, x3C;
    unsigned char x40, x41, x42, pad43;
    int x44;
    unsigned char x48, pad49[3];
    clCGameWC();
};

clCGameWC::clCGameWC() {
    RCVec pos;
    float camA, camB;

    DrawManager_GetOrCreate();
    SetResourceLoadingFlag(0);
    DMAChannelManager_Init();
    TransitionEffect_GetOrCreate();
    SoundChannels_ClearAll();
    ItemObjectManager_Init();
    CourseObjectManager_Init();
    environment = new RCInputManager;
    renderTarget = HSD_LObjLoadDesc(GetCourseDataPtr());
    camera = new RCCamera ARGS_ORDER((1000.0f, 0.1f, 0x100, 0x100, renderTarget), (0x100, 0x100, renderTarget, 1000.0f, 0.1f));
    SetActiveCamera(0, camera);
    *(RCCamera **)&g_raceCamera = camera;
    ProcessSystemTick(0);
    RankingTable_Init(GetRaceContextPtr());
    lbl_806D12BC = 0;
    SoundDriver_GetOrCreate(0);
    GetSpawnPosition(&pos, 0.0f, 0.0f, 0.0f);
    car = new RCPlayerCar(&pos, g_characterId);
    CarObject_SetPosition(car, &pos);
    {
        RCRenderObj *r = (RCRenderObj *)CarObject_GetRenderObj(car);
        r->x238 = 1;
    }
    SetPlayerCarObject(car);
    lakitu = new RCLakituStart("jyugemu_start.dat", 0, 0.0f, 0.0f, 0.0f);
    scene = new RCScene3D(*GetKartModelNameEntry(g_characterId, -1));
    goalCam = new RCGoalCamera;
    ProcessSystemTick(0);
    Scene3D_GetCameraPos(scene, &camA, &camB);
    camA += 10.0f;
    Scene3D_SetupProjection(scene, camA, camB);
    hud = new RCHUD(0);
    HUD_RegisterOverlay(hud, 6, 0);
    HUD_RegisterOverlay(hud, 0x11, 0);
    HUD_RegisterOverlay(hud, 0x12, 0);
    HUD_RegisterOverlay(hud, 0xE, 0);
    *(unsigned char *)&g_lakituStartAnimDone = 0;
    SetCourseScene3D(scene);
    *(unsigned char *)&g_raceEnded = 0;
    *(float *)&g_raceTimeRemaining = MiniGame_GetTimerValue();
    PreloadEffectResources(1);
    PreloadEffectResources(9);
    PreloadEffectResources(0xA);
    x40 = 0;
    x41 = 0;
    x42 = 0;
    x44 = 0;
    x48 = 0;
    banana = new RCBananaData(IsUraCourseFromSubMode());
    x34 = 0.0f;
    x38 = 0.0f;
    x3C = 0.0f;
    CarObject_ResetPhysics(car, 1);
    dirLine = new RCDirLine;
    edges = new RCQuadEdges;
    if (*(void **)&g_weatherSystem == 0) {
        *(void **)&g_weatherSystem = new RCWeatherSystem(1);
    }
    SetResourceLoadingFlag(1);
}

int clCGameWC::Update()
{
    RCHitInfo info;
    RCVec3 pos;
    RCVec3 eye;
    RCVec3 at;
    RCVec3 dir;
    RCVec3 kartPos;
    RCVec3 off;
    RCVec3 delta;
    RCVec3 cur;
    RCVec3 p;
    RCInput *input;
    float accel;
    float brake;
    float steer;
    float a;
    int holding;

    if (x40 == 0) {
        x40 = 1;
    }
    ItemObjectManager_PerFrameUpdate(GetRaceContextPtr());
    input = InputMgr_GetPlayer(GetInputManager(), 0);
    if (RC_ENDED != 1) {
        if (lbl_806D1290 == 0) {
            a = input->accelerator();
        } else {
            a = RCF(lbl_806D4F48);
        }
        accel = a;
        brake = input->brake();
        steer = input->steering();
        holding = 0;
        if (a < RCF(lbl_806D4F50) && brake < RCF(lbl_806D4F50) && IsRaceStarted()) {
            holding = 1;
        }
        if (NokoNokoChallenge_HandleBrakeInput(this, holding) == 1) {
            accel = RCF(lbl_806D4F4C);
        }
        Mtx44_GetTranslation_RowMajor(&pos, KartDriver_GetKartRootMtx(CarObject_GetRenderObj(((RCCar *)car))));
        if (RC_InsideStartQuad(&pos, (float *)edges) == 1) {
            int yaw = ((RCCar *)car)->data->yaw;
            if (yaw < 0) {
                yaw = -yaw % 360 - 360;
            } else {
                yaw = yaw % 360;
            }
            if (yaw >= 0 && yaw < 170) {
                steer = RCF(lbl_806D4F4C);
            }
            if (yaw > 190 && yaw < 360) {
                steer = RCF(lbl_806D4F58);
            }
            accel = RCF(lbl_806D4F4C);
        }
        CarObject_ApplyInput(((RCCar *)car), steer, accel, brake, IsRaceStarted());
        CarObject_FrameUpdate(((RCCar *)car), 0);
        KartItem_UpdateShadowBillboardAndViewport(((RCCar *)car), scene, 0);
        CObj_LoadProjMatrix(scene, &eye);
        CObj_ApplyScissor(scene, &at);
        Vec3_Subtract_DestFirst(&dir, &at, &eye);
        Mtx44_GetTranslation_RowMajor(&kartPos, KartDriver_GetKartRootMtx(CarObject_GetRenderObj(((RCCar *)car))));
        Vec3_Subtract_DestFirst(&off, &eye, &kartPos);
        Vec2_RotateY(&off, &off, RCF(lbl_806D4F5C));
        Vec3_Add_DestFirst(&eye, &kartPos, &off);
        Vec2_RotateY(&dir, &dir, RCF(lbl_806D4F5C));
        Vec3_Add_DestFirst(&at, &eye, &dir);
        CObj_LoadIntoGX(scene, &eye);
        CObj_ApplyViewport(scene, &at);
    } else {
        CarObject_ApplyInput(((RCCar *)car), RCF(lbl_806D4F54), RCF(lbl_806D4F54), RCF(lbl_806D4F54), 1);
        KartMovement_SetSpeedScale(((RCCar *)car), RCF(lbl_806D4F60));
        CarObject_FrameUpdate(((RCCar *)car), 0);
        ChallengeGoalCamera_Update(goalCam, scene,
                                   KartDriver_GetKartRootMtx(CarObject_GetRenderObj(((RCCar *)car))));
    }
    Fog_UpdateFromCourseScene3D();
    LakituStart_UpdateCountdown(lakitu);
    CourseEnvironment_UpdateAndCullZones_Timed(environment);
    {
        float (*m)[4] = KartDriver_GetKartRootMtx(CarObject_GetRenderObj(((RCCar *)car)));
        cur.x = m[0][3];
        cur.y = m[1][3];
        cur.z = m[2][3];
        Vec3_Subtract(&cur, &(*(RCVec3 *)&x34), &delta);
        (*(RCVec3 *)&x34).x = cur.x;
        (*(RCVec3 *)&x34).y = cur.y;
        (*(RCVec3 *)&x34).z = cur.z;
        BananaField_CheckCollision(((RCBanana *)banana), m, &delta);
        if (((RCBanana *)banana)->hit) {
            memset(&info, 0, sizeof(info));
            info.pos.x = cur.x;
            info.pos.y = cur.y;
            info.pos.z = cur.z;
            info.kind = 0x32;
            CarObject_HandleObstacleHit(((RCCar *)car), &info);
        }
    }
    if (x41 == 0) {
        RCGoal *goal;
        Mtx44_GetTranslation_RowMajor(&p, KartDriver_GetKartRootMtx(CarObject_GetRenderObj(((RCCar *)car))));
        goal = ((RCGoal *)dirLine);
        if (RC_PastGoal(&p, goal)) {
            x42 = 1;
            x41 = 1;
            KartMovement_ResetOnGoal(CarObject_GetRenderObj(((RCCar *)car)));
        }
    }
    CObj_LoadProjMatrix(scene, &ReverseChallenge_Update_bss_805DF338);
    CObj_ApplyScissor(scene, &ReverseChallenge_Update_bss_805DF344);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(ReverseChallenge_Update_bss_805DF338, ReverseChallenge_Update_bss_805DF344);
    if (IsRaceStarted() && x41 == 0) {
        float t;
        float zero;
        zero = RCF(lbl_806D4F54);
        t = RC_TIME;
        if (zero <= t) {
            RC_TIME = t - RCF(lbl_806D4F64);
            if (RC_TIME < zero) {
                RC_TIME = zero;
                x41 = 1;
                KartMovement_ResetOnTimeout(CarObject_GetRenderObj(((RCCar *)car)));
            }
        }
    }
    fn_80253FD8(hud, RC_TIME);
    fn_80253EBC(hud, RCF(lbl_806D4F68) * CarObject_CalcSpeedRatio(((RCCar *)car)));
    fn_80253EC0(hud, KartItem_GetCurrentSpeedWithBonus(((RCCar *)car)));
    HUD_FrameUpdate(hud);
    TransitionEffect_Tick(SINGLETON_INSTANCE(*(void **)&lbl_806D109C));
    if (x41) {
        if (x44 == 0) {
            int t;
            int coins;
            t = (float)MiniGame_GetTimerValue() - RC_TIME;
            coins = 0;
            RCCoinTier **tbl = NokoNokoChallenge_GetCoinDivisor();
            if (tbl != 0 && x42 == 1) {
                int i;
                for (i = 0; (*tbl)[i].coins > 0; i++) {
                    if (t <= (*tbl)[i].limit) {
                        coins = (*tbl)[i].coins;
                        break;
                    }
                }
            }
            SetCoinCount(coins);
            if (x42) {
                fn_80253C74(hud, 1, NokoNokoChallenge_CalcResultText(this, 1, 0), (int)RC_TIME);
                Object_SetByte10_Return1(scene, 1);
            } else {
                fn_80253C74(hud, 0, NokoNokoChallenge_CalcResultText(this, 0, 0), (int)RC_TIME);
                Object_SetByte10_Return1(scene, 1);
            }
            NokoNokoChallenge_SaveResult(this, coins, x42);
            RC_ENDED = 1;
            *(unsigned char *)&g_lakituStartAnimDone = 0;
        } else if (fn_80253C40(hud)) {
            return NokoNokoChallenge_TransitionToResult(this);
        }
        x44++;
    }
    if (*(void **)&g_weatherSystem != 0) {
        fn_8016B32C(*(void **)&g_weatherSystem);
    }
    return -2;
}

void clCGameWC::Draw()
{
    if (x40) {
        if (((RevScene *)scene)->IsRenderReady() == 1) {
            clDrawMan_Buckets_Reset(SINGLETON_INSTANCE(*(void **)&lbl_806D10AC));
            TransparentDraw_SortAndDispatch();
            CObj_DebugVizPathFlush(((RevScene *)scene));
            fn_8016B0C4();
            KartItem_RenderPipelinedWithEffects(car, 0);
            Object_RenderJObjIfWithinRange(lakitu);
            CourseEnvironment_RenderObjects_Timed(environment);
            Subsystem36c_DispatchPass2_Timed(environment);
            ItemObjectManager_Render();
            BananaField_Render(banana);
            fn_80253448(hud, lbl_806DC190);
            DrawEffect_TickAndCull();
            clDrawMan_EndFrame_NoOp(SINGLETON_INSTANCE(*(void **)&lbl_806D10AC));
            clDrawMan_Buckets_Dispatch(SINGLETON_INSTANCE(*(void **)&lbl_806D10AC));
            Subsystem36c_DispatchPass4_Timed(environment);
            TransitionEffect_RenderPass(SINGLETON_INSTANCE(*(void **)&lbl_806D109C), 2);
            TransitionEffect_RenderPass(SINGLETON_INSTANCE(*(void **)&lbl_806D109C), 4);
            fn_80253448(hud, lbl_806DC1B0 | lbl_806DC190);
            ((RevScene *)scene)->RenderTail();
        }
        fn_80253448(hud, lbl_806DC1B8);
        fn_802535D4(hud);
        TransitionEffect_RenderPass(SINGLETON_INSTANCE(*(void **)&lbl_806D109C), 1);
        HSD_StateInvalidate(0x7f);
    }
}

clCGameWC::~clCGameWC()
{
        if (g_weatherSystem) {
            fn_8016C634((void *)g_weatherSystem, 1);
            g_weatherSystem = 0;
        }
        SetActiveCamera(0, 0);
        delete (RCVirtual *)scene;
        LakituStart_Dtor(lakitu, 1);
        fn_80124C84(goalCam, 1);
        SetPlayerCarObject(0);
        delete (RCCarVirtual *)car;
        g_raceCamera = 0;
        RCCameraRelease((RCVirtual *)camera);
        if ((RCLight *)renderTarget)
            RCLightUnref((RCLight *)renderTarget);
        CourseEnvironment_Dtor(environment, 1);
        fn_80254134(hud, 1);
        if (dirLine)
            MemoryManager_TimedFree(dirLine);
        ItemObjectManager_Reset();
        VfxSlotMgr_Shutdown();
        ClRomTable_PurgeAll();
        RankingTable_Init(GetRaceContextPtr());
        delete (RCVirtual *)lbl_806D10D0;
        lbl_806D10D0 = 0;
        SceneDrawList_Reset();
        delete (RCVirtual *)lbl_806D109C;
        lbl_806D109C = 0;
        SetResourceLoadingFlag(0);
        clRom_PurgeAll();
        delete (RCVirtual *)lbl_806D10AC;
        lbl_806D10AC = 0;
}
