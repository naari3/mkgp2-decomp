/*
 * 0x80214B3C..0x80214DB8: coin challenge mode destructor (vtable
 * lbl_804EDA98). Layout follows src/game/CoinChallengeInit.cpp.
 */

#include "game/JumpDistanceMode.h"

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
void fn_8016C634(VObj *w, int del);
void SetActiveCamera(int a, void *cam);
void SetPlayerCarObject(void *car);
void SpriteHandle_Destroy(SpriteHandle *h);
void fn_8013A6F8(void);
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
struct LakituStart {
    ~LakituStart();
};
struct CourseEnvironment {
    ~CourseEnvironment();
};
struct ChallengeGoalCamera {
    ~ChallengeGoalCamera();
};
struct HUD {
    ~HUD();
};
struct CoinCar {
    virtual void Update();
    virtual ~CoinCar();
};
struct CoinIcons {
    SpriteHandle *icons[9];
    ~CoinIcons() {
        for (int i = 0; i < 9; i++) {
            SpriteHandle_Destroy(icons[i]);
        }
        fn_80121210();
    }
};

extern "C" WeatherSystem *g_weatherSystem;

struct CoinChallengeMode : ModeBase {
    CoinCar *car;
    LakituStart *lakitu;
    CourseEnvironment *env;
    VObj *scene;
    ChallengeGoalCamera *goalCam;
    VObj *camera;
    HsdObj *lights;
    int x24;
    HUD *hud;
    CoinIcons *icons;
    virtual ~CoinChallengeMode();
};

CoinChallengeMode::~CoinChallengeMode() {
    if (g_weatherSystem != 0) {
        delete g_weatherSystem;
        g_weatherSystem = 0;
    }
    SetActiveCamera(0, 0);
    delete scene;
    delete lakitu;
    delete goalCam;
    SetPlayerCarObject(0);
    delete car;
    g_raceCamera = 0;
    if (camera != 0) {
        delete camera;
    }
    if (lights != 0) {
        ObjUnref(lights);
    }
    delete env;
    delete icons;
    delete hud;
    fn_8013A6F8();
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
