/* === extracted from auto_ReverseChallenge_Ini_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern float BuildOrientationFromYaw(float yaw);
extern void *CarObject_GetRenderObj(void *car);
extern void CarObject_ResetPhysics(void *car, int arg);
extern void CarObject_SetPosition(void *car, void *pos);
extern void CourseObjectManager_Init();
extern void DMAChannelManager_Init();
extern void DrawManager_GetOrCreate();
extern void GetCourseDataPtr();
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
extern void RankingTable_Init();
extern int HSD_LObjLoadDesc(void);
extern void Scene3D_GetCameraPos(void *scene, float *a, float *b);
extern void Scene3D_SetupProjection(void *scene, float a, float b);
extern void SetActiveCamera();
extern void SetCourseScene3D(void *scene);
extern void SetPlayerCarObject();
extern void SetResourceLoadingFlag();
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
extern unsigned int lbl_80328E10[];
extern unsigned int ReverseChallenge_vtable_80419E70[];
extern unsigned int lbl_8048E144[];

/* --- function index (1 fns, .text 0x800AD910..0x800ADDA0) ---
 * [  0] 0x800AD910 size:0x490   global ReverseChallenge_Init
 */

/* --- native C++ ctor (same shape as JumpDistanceMode_Init.c) --- */
#pragma cplusplus on
void *operator new(unsigned long size);
void operator delete(void *p);

typedef struct RCVec { float x, y, z; } RCVec;
struct RCInputManager { char data[0x37C]; RCInputManager(); };
struct RCCamera { char data[0x2C]; RCCamera(float a, float b, int w, int h, int target); };
struct RCCarObject {
    char data[0x118];
    RCCarObject(int disp, int chara, int a, int b, int c, int d, int e, int f, float x, float z, float yaw);
};
struct RCPlayerCar : RCCarObject {
    RCPlayerCar(RCVec *pos, int chara)
        : RCCarObject(GetDisplayBufferIndex(), chara, 0, 0, 1, 0, 0, 0, pos->x, pos->z,
                      BuildOrientationFromYaw(GetCourseStartYaw() + 3.1415925f)) {}
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

#include "game/types/GameModeBase.h"

#include "game/types/ModeBase.h"

struct ReverseChallenge : ModeBase {
    virtual void _key3();
    RCInputManager *input;
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
    unsigned char x40, x41, x42;
    int x44;
    unsigned char x48;
    ReverseChallenge();
};

#pragma exceptions on
ReverseChallenge::ReverseChallenge() {
    RCVec pos;
    float camA, camB;

    DrawManager_GetOrCreate();
    SetResourceLoadingFlag(0);
    DMAChannelManager_Init();
    TransitionEffect_GetOrCreate();
    SoundChannels_ClearAll();
    ItemObjectManager_Init();
    CourseObjectManager_Init();
    input = new RCInputManager;
    GetCourseDataPtr();
    renderTarget = HSD_LObjLoadDesc();
    camera = new RCCamera(1000.0f, 0.1f, 0x100, 0x100, renderTarget);
    SetActiveCamera(0, camera);
    *(RCCamera **)&g_raceCamera = camera;
    ProcessSystemTick(0);
    GetRaceContextPtr();
    RankingTable_Init();
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
    lakitu = new RCLakituStart(lbl_80328E10, 0, 0.0f, 0.0f, 0.0f);
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
#pragma exceptions reset
#pragma cplusplus reset
