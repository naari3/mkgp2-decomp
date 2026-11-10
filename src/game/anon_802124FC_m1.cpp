#define JUMPDISTANCEMODE_EXTERNAL_VTABLE
#include "game/JumpDistanceMode.h"

struct CarObject {
    virtual void v0();
    virtual ~CarObject();
    char pad004[0xD4 - 0x4];
    unsigned char stepping;
};

/* ---- destructor ---- */

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

struct SpriteHandle;

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

struct WeatherSystem {
    ~WeatherSystem();
};
struct KartMovement {
    ~KartMovement();
};
struct LakituStart {
    ~LakituStart();
};
struct CourseEnvironment {
    ~CourseEnvironment();
};
struct ChallengeGoalCamera {
    ~ChallengeGoalCamera();
};
struct ItemSlot {
    ~ItemSlot();
};
struct HUD {
    ~HUD();
};
struct TimerDisplay {
    char pad00[0x10];
    SpriteHandle *digits[7];
    ~TimerDisplay() {
        for (int i = 0; i < 7; i++) {
            SpriteHandle_Destroy(digits[i]);
        }
    }
};
#include "game/types/GoalLine.h"
#include "game/types/ScenePos.h"

extern "C" WeatherSystem *g_weatherSystem;

JumpDistanceMode::~JumpDistanceMode() {
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
