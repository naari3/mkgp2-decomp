#include "game/singleton.h"
extern "C" { unsigned char fn_8016C360(int); void fn_8016C394(int); }
#include "game/types/arg_order.h"
/* JumpDistanceMode_Init (0x80213210): constructor of the jump-distance
 * minigame mode. Builds the player kart, camera, HUD, goal lines and
 * landing-grid objects. */

#include "game/types/size_t.h"
#include "game/types/Vec3.h"
typedef Vec3 Vec;

void *operator new(size_t size);
void operator delete(void *p) throw();

extern "C" {
/* .rodata 0x803C3858..0x803C3DD8 (owned by this TU so the pool base matches) */
static const unsigned int JumpDistanceMode_Init_rodata_803C3858[0x102] = {
    0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x3F333333, 0x3F666666,
    0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556,
    0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556,
    0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556,
    0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556,
    0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000,
    0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556,
    0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556,
    0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556,
    0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556,
    0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556,
    0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556,
    0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000,
    0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556,
    0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556,
    0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556,
    0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556,
    0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556,
    0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556,
    0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000,
    0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556,
    0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556,
    0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556,
    0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556,
    0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556,
    0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556,
    0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000,
    0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556,
    0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556,
    0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB,
    0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB,
    0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB,
    0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB,
    0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000,
    0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB,
    0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB,
    0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB,
    0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB,
    0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB,
    0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB,
    0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000,
    0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB,
    0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB,
};
static const unsigned int lbl_803C3C60[12] = {
    0x44340000, 0x00000000, 0xC5AFF000, 0x43F00000, 0x00000000, 0xC5AFF000,
    0x43F00000, 0x00000000, 0xC505C000, 0x44340000, 0x00000000, 0xC505C000,
};
static const unsigned int lbl_803C3C90[12] = {
    0x44480000, 0x00000000, 0xC5CB2000, 0x43C80000, 0x00000000, 0xC5CB2000,
    0x43C80000, 0x00000000, 0xC4BB8000, 0x44480000, 0x00000000, 0xC4BB8000,
};
static const unsigned int lbl_803C3CC0[12] = {
    0x44480000, 0x00000000, 0xC5D61000, 0x43C80000, 0x00000000, 0xC5D61000,
    0x43C80000, 0x00000000, 0xC48FC000, 0x44480000, 0x00000000, 0xC48FC000,
};
extern const float JumpDistanceMode_rodata_803C3CF0[14] = {
    330.0f, 63.25f, 318.0f, 79.25f, 358.0f, 79.25f, 399.0f, 79.25f,
    355.0f, 38.25f, 380.0f, 38.25f, 405.0f, 38.25f,
};
static const float s_gridX[5] = { 490.0f, 523.0f, 556.0f, 589.0f, 622.0f };
static const float s_gridY[3] = { 43.0f, 78.0f, 113.0f };
static const Vec s_markerScale = { 0.0f, 0.0f, -5.0f };
extern const float JumpDistanceMode_UpdateGameplay_rodata_803C3D54[4] = { 300.0f, -7500.0f, 1000.0f, -800.0f };
extern const float JumpDistanceMode_HandlePhysics_rodata_803C3D64[7] = { 1900.0f, -7800.0f, 2100.0f, -7400.0f, 0.0f, 0.0f, 0.0f };
extern const unsigned int JumpDistanceMode_rodata_803C3D80[3] = { 0, 0, 0 };


extern char lbl_8048E144[];
extern char JumpDistanceMode_vtable_804ECC08[];
extern int g_ccClass;
extern int g_characterId;
extern int g_kartStartSlot;
extern unsigned char g_lakituStartAnimDone;
extern void *g_playerRenderObj;
extern void *g_raceCamera;
extern unsigned char g_raceEnded;
extern float g_raceTimeRemaining;
extern int g_reverseRoundFlag;
extern struct WeatherSystem *g_weatherSystem;
extern int lbl_806D12BC;
extern const float lbl_806DAD70;
extern const float lbl_806DAD7C;
extern const float lbl_806DAD88;
extern const float lbl_806DADA4;
extern const float lbl_806DADDC;
extern const float lbl_806DAE08;
extern const float lbl_806DAE0C;

void GameMode_BaseInit(void *self);
void DrawManager_GetOrCreate(void);
void SetResourceLoadingFlag(unsigned char on);
void DMAChannelManager_Init(void);
void TransitionEffect_GetOrCreate(void);
void SoundChannels_ClearAll(void);
void ItemObjectManager_Init(void);
void CourseObjectManager_Init(void);
void *GetCourseDataPtr(void);
struct HsdObj *HSD_LObjLoadDesc(void *desc);
void SetActiveCamera(int idx, void *camera);
void ProcessSystemTick(int arg);
void *GetRaceContextPtr(void);
void RankingTable_Init(void *);
void SoundDriver_GetOrCreate(int arg);
int GetDisplayBufferIndex(void);
int GetKartStartSlot(int);
void GetStartPosition(int idx, float *x, float *y, float *z);
float GetCourseStartYaw(void);
void CarObject_SetPosition(void *car, Vec *pos);
struct KartDriver *CarObject_GetRenderObj(struct CarObject *car);
void *CarObject_GetKartMovementPtr(void *car);
void KartMovement_EquipItem(void *obj, int item);
void fn_8023E1E4(void *obj, int item, int arg);
void SetPlayerCarObject(void *car);
int *GetKartModelNameEntry(int chara, int arg);
void Vec3_Subtract(const Vec *a, const Vec *b, Vec *out);
void Vec3_Normalize(Vec *src, Vec *dst);
void Scene3D_GetCameraPos(void *scene, float *a, float *b);
void Scene3D_SetupProjection(void *scene, float a, float b);
void HUD_RegisterOverlay(void *hud, int id, int arg);
void SetCourseScene3D(void *scene);
int MiniGame_GetTimerValue(void);
void PreloadEffectResources(int id);
float *MiniGame_GetCourseData(void);
void fn_8013D738(void *obj, float a, float b);
void fn_8013D608(void *obj, float x, float y, float z);
void fn_8013D634(void *obj, float x, float y, float z);
void InitRumbleController(int arg);
void fn_801699D8(int a, int b);
}

#include "game/types/KartDriver.h"

struct InputManager { char data[0x37C]; InputManager(); ~InputManager(); };
struct Camera { virtual ~Camera(); char data[0x28]; Camera ARGS_ORDER((float,float,int,int,int),(int,int,int,float,float)); };
struct CarObject { virtual void v0(); virtual ~CarObject(); char pad004[0xD4-4]; unsigned char stepping; char tail[0x118-0xD5]; CarObject(int,int,int,int,int,int,int,int,float,float,float); };
static inline int GetCC() { return g_ccClass; }
static inline int GetChara() { return g_characterId; }
struct CtorCar { char data[0x118]; CtorCar(int,int,int,int,int,int,int,int,float,float,float); };
struct PlayerCar : CtorCar {
    PlayerCar(Vec *pos, int chara, int cc)
        : CtorCar(GetDisplayBufferIndex(), chara, cc, 0, 1, 7, 0, 0, pos->x, pos->z, GetCourseStartYaw()) {}
};
struct ItemSlot { char data[0x44]; ItemSlot(int arg); ~ItemSlot(); };
struct LakituStart { char data[0x58]; LakituStart(const void *,int,float,float,float); ~LakituStart(); };
struct Scene3D { virtual ~Scene3D(); virtual unsigned char Ready(); virtual void Render(); char data[0x3080]; Scene3D(int); };
struct ChallengeGoalCamera { char data[8]; ChallengeGoalCamera(); ~ChallengeGoalCamera(); };
struct KartMovement {
    char data[0x324];
    KartMovement(const KartMovement &src);
    ~KartMovement();
};
struct HUD { char data[0x80]; HUD(int); ~HUD(); };
struct SpriteHandle;
extern "C" void SpriteHandle_Destroy(SpriteHandle *);
struct TimerDisplay { char pad00[0x10]; SpriteHandle *digits[7]; TimerDisplay(int); ~TimerDisplay() { for (int i=0;i<7;i++) SpriteHandle_Destroy(digits[i]); } };
struct WeatherSystem { char data[0x1B4]; WeatherSystem(int); ~WeatherSystem(); };
struct LandingMarker { virtual ~LandingMarker(); virtual void Draw(); char data[0x1C]; LandingMarker(const void *, int); };

struct ScenePos {
    int x0;
    void *scene;
    Vec a;
    Vec b;
    float x20;
    ScenePos(void *s) {
        x0 = 0;
        scene = s;
        a.x = a.y = a.z = x20 = lbl_806DAD7C;
        b.x = b.y = b.z = lbl_806DAD7C;
    }
};

struct GoalLinePair {
    Vec fwd[2];
    Vec rev[2];
};

struct GoalLine {
    const Vec *pts;
    Vec normal;
    Vec dir;
    GoalLine(const GoalLinePair *pair) {
        pts = g_reverseRoundFlag == 0 ? pair->fwd : pair->rev;
        Vec3_Subtract(&pts[1], &pts[0], &dir);
        Vec3_Normalize(&dir, &dir);
        normal.x = -dir.z;
        normal.y = dir.y;
        normal.z = dir.x;
    }
};

struct JumpGauge {
    unsigned char start, running, landed;
    int count;
    int div;
    float step;
    float spin;
    float lift;
    float delta[16];
    float mtx[16];
    ~JumpGauge() { if (fn_8016C360(0x42)) fn_8016C394(0x42); }
    void Set(int n) {
        count = n;
        div = n;
        step = lbl_806DAD70 / div;
    }
    JumpGauge() {
        start = 0;
        running = 0;
        landed = 0;
        count = 0;
        div = 1;
        step = lbl_806DAD70;
        spin = lbl_806DAD7C;
        lift = lbl_806DAD7C;
        Set(3);
    }
};

struct GridSlot { int age; float x,y; int pad; };

struct GridCell {
    float x,y,rot,alpha;
    int frame,visible;
    GridSlot slots[5];
};

struct LandingGrid {
    LandingMarker *markers[2];
    int next,pending,delay;
    float spin;
    int sparkle;
    ~LandingGrid() { delete markers[0]; delete markers[1]; }
    GridCell cells[15];
    GridCell cells2[15];
    LandingGrid(const char *m0, const char *m1, const Vec *pos, const float *xs, const float *ys);
};

inline LandingGrid::LandingGrid(const char *m0, const char *m1, const Vec *pos, const float *xs, const float *ys) {
    int i;

    markers[0] = 0;
    next = 0;
    pending = 0;
    delay = 0;
    spin = lbl_806DAD7C;
    sparkle = 0;
    markers[0] = new LandingMarker(m0, 1);
    fn_8013D738(markers[0], lbl_806DAD7C, lbl_806DAD70);
    fn_8013D608(markers[0], lbl_806DAE0C, lbl_806DAE0C, lbl_806DAE0C);
    fn_8013D634(markers[0], pos->x, pos->y, pos->z);
    markers[1] = new LandingMarker(m1, 1);
    fn_8013D738(markers[1], lbl_806DAD7C, lbl_806DAD70);
    fn_8013D608(markers[1], lbl_806DAE0C, lbl_806DAE0C, lbl_806DAE0C);
    fn_8013D634(markers[1], pos->x, pos->y, pos->z);
    for (i = 0; i < 15; i++) {
        cells[i].x = cells2[i].x = xs[i % 5];
        cells[i].y = cells2[i].y = ys[i / 5];
        cells[i].rot = cells2[i].rot = lbl_806DAD7C;
        cells[i].alpha = cells2[i].alpha = lbl_806DAD7C;
        cells[i].frame = cells2[i].frame = 0;
        cells[i].visible = cells2[i].visible = 0;
        cells[i].slots[0].age = cells2[i].slots[0].age = -1;
        cells[i].slots[1].age = cells2[i].slots[1].age = -1;
        cells[i].slots[2].age = cells2[i].slots[2].age = -1;
        cells[i].slots[3].age = cells2[i].slots[3].age = -1;
        cells[i].slots[4].age = cells2[i].slots[4].age = -1;
    }
}


#include "game/types/VObj.h"
struct HsdObj;

#include "game/types/clJobRunner.h"
struct clCGame : clJobRunner {
    float x4;
    clCGame() { x4 = lbl_806DAD7C; }
    virtual ~clCGame();
};
struct clCGameDN : clCGame {
    CarObject *car;
    LakituStart *lakitu;
    InputManager *env;
    Scene3D *scene;
    ChallengeGoalCamera *goalCam;
    ItemSlot *itemSlot;
    Camera *camera;
    HsdObj *lights;
    HUD *hud;
    TimerDisplay *timer;
    GoalLine *lines[3];
    JumpGauge *gauge;
    ScenePos *scenePos;
    unsigned char ready;
    unsigned char x45;
    int x48, x4C, x50;
    float x54, x58, x5C, x60, x64, x68;
    unsigned char x6C, x6D;
    KartMovement *movement;
    float x74;
    unsigned char x78;
    LandingGrid *grid;
    int x80, x84;
    unsigned char x88;
    virtual int Update();
    clCGameDN();
    virtual void Draw();
    virtual ~clCGameDN();
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

static inline int RefDec(HsdObj *o) {
    int ret = o->ref == (unsigned short)-1;
    if (ret) {
        return ret;
    }
    return o->ref-- == 0;
}

static inline void ObjUnref(HsdObj *o) {
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

extern "C" {
extern void *g_raceCamera;
extern VObj *lbl_806D10D0;
extern VObj *lbl_806D109C;
extern VObj *lbl_806D10AC;
void fn_801699D8(int a, int b);
void fn_80169C44(void);
void fn_8016C634(VObj *w, int del);
void SetActiveCamera(int a, void *cam);
void SetPlayerCarObject(void *car);
void SpriteHandle_Destroy(SpriteHandle *h);
void ItemObjectManager_Reset(void);
void VfxSlotMgr_Shutdown(void);
void ClRomTable_PurgeAll(void);
void *GetRaceContextPtr(void);
void RankingTable_Init(void *ctx);
void SceneDrawList_Reset(void);
void fn_80121210(void);
void SetResourceLoadingFlag(unsigned char on);
void clRom_PurgeAll(void);
}


clCGameDN::clCGameDN() {
    Vec pos;
    float camA, camB;
    float *course;

    car = 0;
    lakitu = 0;
    env = 0;
    scene = 0;
    goalCam = 0;
    itemSlot = 0;
    camera = 0;
    lights = 0;
    hud = 0;
    timer = 0;
    lines[0] = 0;
    lines[1] = 0;
    lines[2] = 0;
    gauge = 0;
    scenePos = 0;
    ready = 0;
    x45 = 0;
    x48 = 0;
    x4C = 0;
    x50 = 0;
    x54 = lbl_806DADA4;
    x58 = lbl_806DAD7C;
    x68 = lbl_806DAD7C;
    x6C = 0;
    x6D = 0;
    movement = 0;
    x74 = lbl_806DAD7C;
    x78 = 0;
    x88 = 0;
    DrawManager_GetOrCreate();
    SetResourceLoadingFlag(0);
    DMAChannelManager_Init();
    TransitionEffect_GetOrCreate();
    SoundChannels_ClearAll();
    ItemObjectManager_Init();
    CourseObjectManager_Init();
    env = new InputManager;
    lights = HSD_LObjLoadDesc(GetCourseDataPtr());
    camera = new Camera ARGS_ORDER((lbl_806DAE08, lbl_806DAD88, 0x100, 0x100, (int)lights), (0x100, 0x100, (int)lights, lbl_806DAE08, lbl_806DAD88));
    SetActiveCamera(0, camera);
    g_raceCamera = camera;
    ProcessSystemTick(0);
    RankingTable_Init(GetRaceContextPtr());
    lbl_806D12BC = 0;
    SoundDriver_GetOrCreate(0);
    g_kartStartSlot = GetKartStartSlot(GetDisplayBufferIndex());
    GetStartPosition(0, &pos.x, &pos.y, &pos.z);
    car = (CarObject *)new PlayerCar(&pos, GetChara(), GetCC());
    CarObject_SetPosition(car, &pos);
    {
        KartDriver *r = CarObject_GetRenderObj(car);
        r->visible_238 = 1;
    }
    {
        KartDriver *r = CarObject_GetRenderObj(car);
        r->forceDraw = 1;
    }
    KartMovement_EquipItem(CarObject_GetRenderObj(car), 0x17);
    itemSlot = new ItemSlot(0);
    fn_8023E1E4(itemSlot, 0x17, 0);
    SetPlayerCarObject(car);
    g_playerRenderObj = CarObject_GetRenderObj(car);
    lakitu = new LakituStart("jyugemu_start.dat", 0, lbl_806DAD7C, lbl_806DAD7C, lbl_806DAD7C);
    scene = new Scene3D(*GetKartModelNameEntry(g_characterId, -1));
    goalCam = new ChallengeGoalCamera;
    movement = new KartMovement(*(KartMovement *)CarObject_GetKartMovementPtr(car));
    scenePos = new ScenePos(scene);
    lines[0] = new GoalLine((const GoalLinePair *)lbl_803C3C60);
    lines[1] = new GoalLine((const GoalLinePair *)lbl_803C3C90);
    lines[2] = new GoalLine((const GoalLinePair *)lbl_803C3CC0);
    ProcessSystemTick(0);
    Scene3D_GetCameraPos(scene, &camA, &camB);
    camA += lbl_806DADDC;
    Scene3D_SetupProjection(scene, camA, camB);
    hud = new HUD(0);
    HUD_RegisterOverlay(hud, 6, 0);
    HUD_RegisterOverlay(hud, 0x11, 0);
    HUD_RegisterOverlay(hud, 0x12, 0);
    HUD_RegisterOverlay(hud, 0xE, 0);
    g_lakituStartAnimDone = 0;
    SetCourseScene3D(scene);
    g_raceEnded = 0;
    g_raceTimeRemaining = MiniGame_GetTimerValue();
    x5C = x60 = x64 = lbl_806DAD7C;
    PreloadEffectResources(1);
    PreloadEffectResources(9);
    PreloadEffectResources(0xA);
    course = MiniGame_GetCourseData();
    if (course != 0) {
        x54 = *course;
    }
    timer = new TimerDisplay(x54);
    gauge = new JumpGauge;
    grid = new LandingGrid("mario_coin.dat", "k_kira13.dat", &s_markerScale, s_gridX, s_gridY);
    x80 = 0;
    x84 = 0;
    if (g_weatherSystem == 0) {
        g_weatherSystem = new WeatherSystem(1);
    }
    SetResourceLoadingFlag(1);
    InitRumbleController(0);
    fn_801699D8(0, 1);
    fn_801699D8(1, 1);
}

clCGameDN::~clCGameDN() {
    fn_801699D8(0, 0);
    fn_801699D8(1, 0);
    fn_80169C44();
    if (g_weatherSystem != 0) {
        delete g_weatherSystem;
        g_weatherSystem = 0;
    }
    SetActiveCamera(0, 0);
    delete grid;
    delete movement;
    if (scenePos != 0) {
        delete scenePos;
    }
    delete scene;
    delete lakitu;
    delete goalCam;
    SetPlayerCarObject(0);
    delete car;
    delete itemSlot;
    g_raceCamera = 0;
    if (camera != 0) {
        delete camera;
    }
    if (lights != 0) {
        ObjUnref(lights);
    }
    delete env;
    delete gauge;
    delete timer;
    delete hud;
    if (lines[2] != 0) {
        delete lines[2];
    }
    if (lines[1] != 0) {
        delete lines[1];
    }
    if (lines[0] != 0) {
        delete lines[0];
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
    fn_80121210();
    SetResourceLoadingFlag(0);
    clRom_PurgeAll();
    delete lbl_806D10AC;
    lbl_806D10AC = 0;
}

struct KartRender {
    char pad000[0x20];
    void *jobj;
    char pad024[0x1CC - 0x24];
    float scale1CC;
    char pad1D0[0x1D8 - 0x1D0];
    float speed;
    float GetSpeed() const { return speed; }
    char pad1DC[0x320 - 0x1DC];
    float lift;
    char pad324[0x37C - 0x324];
    float scale37C;
};



/* Kart root position (dtor dtor_80036E40). */
struct KartPos {
    float x, y, z;
    KartPos() {}
    void Set(float px, float py, float pz) { x = px; y = py; z = pz; }
    ~KartPos() {}
};

extern "C" {

float *KartDriver_GetKartRootMtx(KartRender *r);
float *CarObject_GetTransformMatrix(CarObject *car);
void *KartItem_GetCarObjectSoundCh(CarObject *car);
float TornadoEffect_GetField114(void *t);
void CarObject_FrameUpdate(CarObject *car, int a);
unsigned char CarObject_IsAirborne(CarObject *car);
void KartItem_ForwardToCarMovement_8019a4e0(CarObject *car, float *mtx);
void KartDriver_TickAction_79244(KartRender *r, float t);
void Object_SetField14_IfValid(void *jobj, float v);
}


extern "C" { void *memcpy(void *,const void *,unsigned long); int fn_8016C3C8(int,int); extern const float lbl_806DAE04; }
static inline float MultiplySpeed(float factor, float speed) {
    return factor * speed;
}

static inline void AddLift(CarObject *car, float lift) {
    ((KartRender *)CarObject_GetRenderObj(car))->lift += lift;
}

extern "C" void fn_802128F4(JumpGauge *g, CarObject *car) {
    if ((g->running || g->start) && car != 0) {
        KartPos pos;
        float *m = KartDriver_GetKartRootMtx(((KartRender *)CarObject_GetRenderObj(car)));
        pos.Set(m[3], m[7], m[11]);
        if (g->start == 1) {
            g->start = 0;
            if (!g->running && !g->landed) {
                g->running = 1;
                ((KartRender *)CarObject_GetRenderObj(car))->scale37C = g->step;
                ((KartRender *)CarObject_GetRenderObj(car))->scale1CC = g->step;
                {
                    float speed = ((KartRender *)CarObject_GetRenderObj(car))->GetSpeed();
                    float factor = g->step;
                    factor = MultiplySpeed(factor, speed);
                    ((KartRender *)CarObject_GetRenderObj(car))->speed = factor;
                }
                g->lift = -(lbl_806DAE04 * (lbl_806DAD70 - g->step));
            }
        }
        if (g->running == 1 && g->landed == 1) {
            g->start = 0;
            g->running = 0;
            g->landed = 0;
            car->stepping = 1;
            { KartRender *r = ((KartRender *)CarObject_GetRenderObj(car)); r->scale37C = lbl_806DAD70; }
            { KartRender *r = ((KartRender *)CarObject_GetRenderObj(car)); r->scale1CC = lbl_806DAD70; }
            {
                float speed = ((KartRender *)CarObject_GetRenderObj(car))->GetSpeed();
                float factor = g->div;
                factor = MultiplySpeed(factor, speed);
                ((KartRender *)CarObject_GetRenderObj(car))->speed = factor;
            }
            if (((KartRender *)CarObject_GetRenderObj(car))->jobj != 0) {
                Object_SetField14_IfValid(((KartRender *)CarObject_GetRenderObj(car))->jobj, lbl_806DAD70);
            }
            return;
        }
        if (++g->count >= g->div) {
            g->count = 0;
            float h = TornadoEffect_GetField114(KartItem_GetCarObjectSoundCh(car));
            memcpy(g->mtx, CarObject_GetTransformMatrix(car), 0x40);
            car->stepping = 1;
            CarObject_FrameUpdate(car, 0);
            car->stepping = 0;
            if (!CarObject_IsAirborne(car)) {
                if (fn_8016C360(0x42) == 1) {
                    fn_8016C3C8(0x42, 1);
                }
                g->landed = 1;
            }
            m = KartDriver_GetKartRootMtx(((KartRender *)CarObject_GetRenderObj(car)));
            float x = m[3];
            float y = m[7];
            float z = m[11];
            float cur[16];
            memcpy(cur, CarObject_GetTransformMatrix(car), 0x40);
            for (int i = 0; i < 16; i++) {
                g->delta[i] = g->step * (cur[i] - g->mtx[i]);
            }
            g->delta[12] = g->step * (x - pos.x);
            g->delta[13] = g->step * (y - pos.y);
            g->delta[14] = g->step * (z - pos.z);
            g->spin = g->step * (TornadoEffect_GetField114(KartItem_GetCarObjectSoundCh(car)) - h);
            {
                float lift = g->lift;
                KartRender *r = ((KartRender *)CarObject_GetRenderObj(car));
                r->lift += lift;
            }
            if (((KartRender *)CarObject_GetRenderObj(car))->jobj != 0) {
                Object_SetField14_IfValid(((KartRender *)CarObject_GetRenderObj(car))->jobj, g->step);
            }
        }
        float lift = g->lift;
        KartRender *r = ((KartRender *)CarObject_GetRenderObj(car));
        r->lift += lift;
        g->mtx[12] = pos.x;
        g->mtx[13] = pos.y;
        g->mtx[14] = pos.z;
        for (int i = 0; i < 16; i++) {
            g->mtx[i] += g->delta[i];
        }
        KartItem_ForwardToCarMovement_8019a4e0(car, g->mtx);
        KartDriver_TickAction_79244(((KartRender *)CarObject_GetRenderObj(car)), g->spin * g->count);
    }
}

extern "C" {
void *memcpy(void *dst, const void *src, unsigned long n);
unsigned char IsCardValid(void);
float Cosf_LUT_Wrap(float x);
float LUT_Sin12Bit(float x);
int fn_8016C3C8(int se, int a);
void SoundMgr_PlaySE(int se);
extern const float lbl_80495994[64];
extern const float lbl_806DAD70;
extern const float lbl_806DAD84;
extern const float lbl_806DAD8C;
extern const float lbl_806DADB4;
extern const float lbl_806DADDC;
extern const float lbl_806DADF8;
extern const float lbl_806DADFC;
extern const float lbl_806DAE00;
extern const float lbl_806DAE04;
}

static inline void TickSlot(GridSlot *s, float rise) {
    if (s->age >= 0) {
        s->y += rise;
        if (++s->age >= 10) {
            s->age = -1;
        }
    }
}

extern "C" void fn_802124FC(LandingGrid *g) {
    if (IsCardValid()) {
        float rise = lbl_806DADF8;
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 5; j++) {
                TickSlot(&g->cells[i].slots[j], rise);
            }
            if (g->cells[i].visible > 0) {
                g->cells[i].y -= lbl_806DAD8C * Cosf_LUT_Wrap(lbl_806DADFC * g->cells[i].frame);
                g->cells[i].rot += lbl_806DADDC;
                g->cells[i].alpha = lbl_806DAD70 - g->cells[i].frame / lbl_806DAE00;
                if ((g->cells[i].frame & 3) == 0) {
                    for (int j = 0; j < 5; j++) {
                        if (g->cells[i].slots[j].age < 0) {
                            g->cells[i].slots[j].age = 0;
                            g->cells[i].slots[j].x = lbl_806DADDC * LUT_Sin12Bit(lbl_806DADB4 * lbl_80495994[g->sparkle]) + g->cells[i].x;
                            g->cells[i].slots[j].y = lbl_806DAD84 * LUT_Sin12Bit(lbl_806DADB4 * lbl_80495994[g->sparkle]) + g->cells[i].y;
                            if (++g->sparkle >= 64) {
                                g->sparkle = 0;
                            }
                            break;
                        }
                    }
                }
                if (g->cells[i].frame >= 50) {
                    g->cells2[i].visible = 1;
                    g->cells[i].visible = 0;
                }
                if (g->cells[i].frame < 300) {
                    g->cells[i].frame++;
                }
            }
            if (g->cells2[i].visible > 0) {
                if (g->cells2[i].frame < 40) {
                    g->cells2[i].alpha = g->cells2[i].frame / lbl_806DAE00;
                }
                g->cells2[i].rot = g->spin;
                if (g->cells2[i].frame < 300) {
                    g->cells2[i].frame++;
                }
            }
        }
        g->spin += 1.0f;
        if (g->spin > 360.0f) {
            g->spin -= 360.0f;
        }
        if (g->pending > 0 && g->delay <= 0) {
            g->cells[g->next].visible = 1;
            g->next++;
            g->pending--;
            g->delay = 10;
            if (fn_8016C360(0xAB) == 1) {
                fn_8016C394(0xAB);
            }
            SoundMgr_PlaySE(0xAB);
        }
        if (g->delay > 0) {
            g->delay--;
        }
    }
}

#include "game/types/Vec3.h"

struct JDCamera {
    int state;
    void *cobj;
    Vec3 pos;
    Vec3 vel;
    float t;
};

struct JDTimer {
    int value;
    int pad4;
    unsigned char exiting;
    char pad9[3];
    float slide;
    void *sprite[7];
};

#include "game/types/JDLanding.h"
#include "game/types/JDCoins.h"

#include "game/types/JDMode.h"

extern "C" {
extern unsigned char g_raceEnded, g_lakituStartAnimDone;
extern float g_raceTimeRemaining;
extern WeatherSystem *g_weatherSystem;
extern VObj *lbl_806D109C;
extern const float lbl_806DAD70, lbl_806DAD74, lbl_806DAD7C, lbl_806DAD88, lbl_806DADA4;
extern const float lbl_806DADB0, lbl_806DADD8, lbl_806DADE8, lbl_806DADEC, lbl_806DADF4;
extern const float JumpDistanceMode_rodata_803C3CF0[14];
void *GetRaceContextPtr();
void ItemObjectManager_PerFrameUpdate(void *);

void fn_8023E324(void *, unsigned char);
void JumpDistanceMode_HandlePhysics(JDMode *);
void JumpDistanceMode_UpdateGameplay(JDMode *);
void Fog_UpdateFromCourseScene3D();
int CObj_ApplyScissor(void *, Vec3 *);
int CObj_LoadProjMatrix(void *, Vec3 *);
int CObj_LoadIntoGX(void *, Vec3 *);
void Vec3_Subtract(const Vec3 *, const Vec3 *, Vec3 *);
float LUT_Cosine(float);
float LUT_Sine(float);
unsigned char Terrain_RaycastWall(Vec3 *, Vec3 *, Vec3 *, Vec3 *);
void LakituStart_UpdateCountdown(void *);
void CourseEnvironment_UpdateAndCullZones_Timed(void *);
void ItemObjectManager_Update();
#ifdef __MWERKS__
void VfxSlotMgr_Update(Vec3, Vec3);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void VfxSlotMgr_Update(Vec3 *, Vec3 *);
static inline void VfxSlotMgr_Update_ByValue(Vec3 a0, Vec3 a1) { VfxSlotMgr_Update(&a0, &a1); }
#define VfxSlotMgr_Update VfxSlotMgr_Update_ByValue
#endif
unsigned char IsRaceStarted();

void fn_80253FD8(void *, float);
float CarObject_CalcSpeedRatio(void *);
void fn_80253EBC(void *, float);
float KartItem_GetCurrentSpeedWithBonus(void *);
void fn_80253EC0(void *, float);
void HUD_FrameUpdate(void *);
void fn_8011F804(void *, float, float);
void SpriteLayer_SetResource(void *, int);
void SpriteHandle_RecomputeCull(void *);
void RumbleUpdate();
void TransitionEffect_Tick(void *);
void SetCoinCount(int);
int fn_801231AC();
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

static inline float JD_sqrtf(float x) {
    volatile float y;
    if (x > 0.0f) {
        double guess = __frsqrte(x);
        guess = 0.5 * guess * (3.0 - x * (guess * guess));
        guess = 0.5 * guess * (3.0 - x * (guess * guess));
        guess = 0.5 * guess * (3.0 - x * (guess * guess));
        y = (float)(x * guess);
        return y;
    }
    return x;
}

static inline void *getTransition() {
    return SINGLETON_INSTANCE(lbl_806D109C);
}

static inline float Wave(const JDCamera *c) {
    return LUT_Sine(lbl_806DADD8 * c->t);
}

/* Multiplying through an inline keeps the two squares from fusing into fmadds. */
static inline float JD_mul(float a, float b) { return a * b; }

static inline void UpdateIntroCamera(JDCamera *cam) {
    Vec3 eye, at, pos, d;
    Vec3 save, hit, normal;
    switch (cam->state) {
    case 0:
        break;
    case 1: {
        float len;
        float r;

        CObj_ApplyScissor(cam->cobj, &eye);
        CObj_LoadProjMatrix(cam->cobj, &at);
        Vec3_Subtract(&eye, &at, &d);
        len = JD_sqrtf(JD_mul(d.x, d.x) + JD_mul(d.z, d.z));
        r = lbl_806DADE8 * len;
        pos.x = r * LUT_Cosine(lbl_806DADEC) + eye.x;
        pos.z = r * LUT_Sine(lbl_806DADEC) + eye.z;
        pos.y = eye.y;
        CObj_LoadIntoGX(cam->cobj, &pos);
        break;
    }
    case 2:
        cam->state = 3;
        break;
    case 3:
        CObj_LoadIntoGX(cam->cobj, &cam->pos);
        break;
    case 4:
        if (cam->t < 90.0f) {
            float s;

            save = cam->pos;
            s = Wave(cam);
            cam->pos.x += cam->vel.x * s;
            cam->pos.y += cam->vel.y * s;
            cam->pos.z += cam->vel.z * s;
            cam->t += lbl_806DADB0;
            if (Terrain_RaycastWall(&save, &cam->pos, &hit, &normal) == 1) {
                cam->pos = save;
                cam->t = 90.0f;
            }
        }
        CObj_LoadIntoGX(cam->cobj, &cam->pos);
        break;
    }
}

static inline void UpdateTimer(JDTimer *timer) {
    int i;
    if (timer->exiting == 1) {
        float k;

        if (timer->slide >= lbl_806DAD70) return;
        k = lbl_806DADF4;
        timer->slide += lbl_806DAD88;
        for (i = 0; i < 7; i++) {
            fn_8011F804(timer->sprite[i], k * timer->slide + JumpDistanceMode_rodata_803C3CF0[i * 2], JumpDistanceMode_rodata_803C3CF0[i * 2 + 1]);
        }
    }
    {
        int value = timer->value;
        int hundreds = value / 100 % 10;
        int tens = value / 10 % 10;
        int ones = value % 10;
        int hundredsRes = 0x1ECD;
        int tensRes = hundredsRes;

        if (hundreds != 0) {
            hundredsRes = hundreds + 0x1B73;
            tensRes = tens + 0x1B73;
        } else if (tens != 0) {
            tensRes = tens + 0x1B73;
        }
        SpriteLayer_SetResource(timer->sprite[1], hundredsRes);
        SpriteLayer_SetResource(timer->sprite[2], tensRes);
        SpriteLayer_SetResource(timer->sprite[3], ones + 0x1B73);
    }
    {
        int j;
        for (j = 0; j < 7; j++, timer = (JDTimer *)((char *)timer + 4)) {
            SpriteHandle_RecomputeCull(timer->sprite[0]);
        }
    }
}

int clCGameDN::Update() {
    int i;
    Vec3 projection, scissor;

    if (ready == 0) {
        ready = 1;
    }
    ItemObjectManager_PerFrameUpdate(GetRaceContextPtr());
    fn_802128F4((JumpGauge *)((JDLanding *)gauge), car);
    fn_8023E324(itemSlot, ready);
    JumpDistanceMode_HandlePhysics((JDMode *)this);
    Fog_UpdateFromCourseScene3D();
    UpdateIntroCamera(((JDCamera *)scenePos));
    LakituStart_UpdateCountdown(lakitu);
    CourseEnvironment_UpdateAndCullZones_Timed(env);
    if (g_raceEnded == 0) {
        JumpDistanceMode_UpdateGameplay((JDMode *)this);
    }
    CObj_LoadProjMatrix(scene, &projection);
    CObj_ApplyScissor(scene, &scissor);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(projection, scissor);
    if (IsRaceStarted() == 1 && g_raceEnded != 1 && x50 < 2 && g_raceTimeRemaining >= 0.0f) {
        if (((JDLanding *)gauge)->slowed == 0) {
            g_raceTimeRemaining = g_raceTimeRemaining - lbl_806DAD74;
        } else {
            g_raceTimeRemaining = g_raceTimeRemaining - lbl_806DAD74 * ((JDLanding *)gauge)->scale;
        }
        if (g_raceTimeRemaining < 0.0f) {
            g_raceTimeRemaining = 0.0f;
            g_raceEnded = 1;
        }
    }
    fn_802124FC((LandingGrid *)((JDCoins *)grid));
    fn_80253FD8(hud, g_raceTimeRemaining);
    fn_80253EBC(hud, lbl_806DADA4 * CarObject_CalcSpeedRatio(car));
    fn_80253EC0(hud, KartItem_GetCurrentSpeedWithBonus(car));
    HUD_FrameUpdate(hud);
    UpdateTimer(((JDTimer *)timer));
    RumbleUpdate();
    TransitionEffect_Tick(getTransition());
    if (g_raceEnded == 1) {
        if (x48 > 0) {
            x48--;
        } else {
            if (x4C == 0) {
                float distance;
                int ok;

                if (x84 > 15) {
                    x84 = 15;
                }
                ((JDCoins *)grid)->earned = x84 - ((JDCoins *)grid)->base;
                SetCoinCount(x84);
                ok = fn_801231AC();
                distance = x58;
                ok = distance >= (float)ok;
                if (x45 != 0) {
                    fn_80253C74(hud, 1, NokoNokoChallenge_CalcResultText(this, 1, ok), (int)distance);
                    KartMovement_ResetOnGoal(CarObject_GetRenderObj(car));
                } else {
                    fn_80253C74(hud, 0, NokoNokoChallenge_CalcResultText(this, 0, ok), (int)distance);
                    KartMovement_ResetOnTimeout(CarObject_GetRenderObj(car));
                }
                NokoNokoChallenge_SaveResult(this, x84, x45);
                {
                    JDTimer *t = ((JDTimer *)timer);
                    t->slide = lbl_806DAD7C;
                    t->exiting = 1;
                }
                Object_SetByte10_Return1(scene, 1);
                g_lakituStartAnimDone = 0;
            } else if (fn_80253C40(hud)) {
                return NokoNokoChallenge_TransitionToResult(this);
            }
            x4C++;
        }
    }
    if (g_weatherSystem) {
        fn_8016B32C(g_weatherSystem);
    }
    return -2;
}

struct DrawMan;
struct TransitionEffect;
struct ItemBoxManager;

extern "C" {
extern VObj *lbl_806D10AC;
extern VObj *lbl_806D109C;
extern VObj *lbl_806D10D0;
extern const float lbl_806DAD70;
extern const float lbl_806DADD4;
extern const float lbl_806DADD8;
extern const float lbl_806DADDC;
extern const unsigned int lbl_806DC190;
extern const unsigned int lbl_806DC1B0;
extern const unsigned int lbl_806DC1B8;
void clDrawMan_Buckets_Reset(VObj *dm);
void clDrawMan_SetMaxClipZ(VObj *dm, float z);
void clDrawMan_EndFrame_NoOp(VObj *dm);
void clDrawMan_Buckets_Dispatch(VObj *dm);
void TransparentDraw_SortAndDispatch(void);
void CObj_DebugVizPathFlush(Scene3D *scene);
void fn_8016B0C4(void);
void KartItem_RenderPipelinedWithEffects(void *kart, int a);
void Object_RenderJObjIfWithinRange(void *obj);
void CourseEnvironment_RenderObjects_Timed(void *env);
void Subsystem36c_DispatchPass2_Timed(void *env);
void Subsystem36c_DispatchPass4_Timed(void *env);
void fn_8023E2F8(void *p);
void clItemBoxManager_Draw(VObj *m);
void ItemObjectManager_Render(void);
void DrawEffect_TickAndCull(void);
void TransitionEffect_RenderPass(VObj *t, int pass);
void fn_80253448(void *p, unsigned int color);
void fn_802535D4(void *p);
unsigned char IsCardValid(void);
void HSD_StateInvalidate(int state);
}

static inline VObj *GetDrawMan() {
    return SINGLETON_INSTANCE(lbl_806D10AC);
}

static inline VObj *GetTransition() {
    return SINGLETON_INSTANCE(lbl_806D109C);
}

static inline VObj *GetItemBoxMan() {
    return SINGLETON_INSTANCE(lbl_806D10D0);
}

extern "C" { void fn_8013D660(LandingMarker *,float,float); void fn_8013D570(LandingMarker *,float); void fn_8013D4B0(LandingMarker *,float); }
static inline void DrawDigit(LandingGrid *d, GridCell *g) {
    GridCell *h = g;
    fn_8013D660(d->markers[0], h->x, g->y);
    fn_8013D570(d->markers[0], lbl_806DADD8 * h->rot);
    fn_8013D4B0(d->markers[0], h->alpha);
    d->markers[0]->Draw();
    for (int i = 0; i < 5; i++) {
        GridSlot *t = &h->slots[i];
        if (t->age >= 0) {
            fn_8013D660(d->markers[1], t->x, t->y);
            fn_8013D4B0(d->markers[1], lbl_806DAD70 - (float)t->age / lbl_806DADDC);
            d->markers[1]->Draw();
        }
    }
}

void clCGameDN::Draw() {
    if (ready) {
        if (scene->Ready() == 1) {
            clDrawMan_Buckets_Reset(GetDrawMan());
            clDrawMan_SetMaxClipZ(GetDrawMan(), lbl_806DADD4);
            TransparentDraw_SortAndDispatch();
            CObj_DebugVizPathFlush(scene);
            fn_8016B0C4();
            KartItem_RenderPipelinedWithEffects(car, 0);
            Object_RenderJObjIfWithinRange(lakitu);
            CourseEnvironment_RenderObjects_Timed(env);
            fn_8023E2F8(itemSlot);
            clItemBoxManager_Draw(GetItemBoxMan());
            Subsystem36c_DispatchPass2_Timed(env);
            ItemObjectManager_Render();
            DrawEffect_TickAndCull();
            clDrawMan_EndFrame_NoOp(GetDrawMan());
            clDrawMan_Buckets_Dispatch(GetDrawMan());
            Subsystem36c_DispatchPass4_Timed(env);
            TransitionEffect_RenderPass(GetTransition(), 2);
            TransitionEffect_RenderPass(GetTransition(), 4);
            fn_80253448(hud, lbl_806DC1B0 | lbl_806DC190);
            scene->Render();
        }
        int i;
        LandingGrid *d = grid;
        if (IsCardValid()) {
            for (i = 0; i < 15; i++) {
                if (d->cells[i].visible) {
                    DrawDigit(d, &d->cells[i]);
                }
                if (d->cells2[i].visible) {
                    DrawDigit(d, &d->cells2[i]);
                }
            }
        }
        fn_80253448(hud, lbl_806DC1B8);
        fn_802535D4(hud);
        TransitionEffect_RenderPass(GetTransition(), 1);
        HSD_StateInvalidate(0x7F);
    }
}
