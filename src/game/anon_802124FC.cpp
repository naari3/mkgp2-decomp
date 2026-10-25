/*
 * 0x802124FC..0x80213210: JumpDistanceMode helpers: the landing grid
 * animation, the kart launch stepper and the mode destructor.
 */

#include "game/JumpDistanceMode.h"

extern "C" {
void *memcpy(void *dst, const void *src, unsigned long n);
unsigned char IsCardValid(void);
float Cosf_LUT_Wrap(float x);
float LUT_Sin12Bit(float x);
void fn_8016C3C8(int se, int a);
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
        g->spin += lbl_806DAD70;
        if (g->spin > lbl_806DADB4) {
            g->spin -= lbl_806DADB4;
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

/* ---- kart launch stepper ---- */

struct KartRender {
    char pad000[0x20];
    void *jobj;
    char pad024[0x1CC - 0x24];
    float scale1CC;
    char pad1D0[0x1D8 - 0x1D0];
    float speed;
    char pad1DC[0x320 - 0x1DC];
    float lift;
    char pad324[0x37C - 0x324];
    float scale37C;
};

struct CarObject {
    virtual void v0();
    virtual ~CarObject();
    char pad004[0xD4 - 0x4];
    unsigned char stepping;
};

/* Kart root position (dtor dtor_80036E40). */
struct KartPos {
    float x, y, z;
    KartPos(float px, float py, float pz) : x(px), y(py), z(pz) {}
    ~KartPos() {}
};

extern "C" {
KartRender *CarObject_GetRenderObj(CarObject *car);
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

static inline void AddLift(CarObject *car, float lift) {
    CarObject_GetRenderObj(car)->lift += lift;
}

extern "C" void fn_802128F4(JumpGauge *g, CarObject *car) {
    if ((g->running || g->start) && car != 0) {
        float *m = KartDriver_GetKartRootMtx(CarObject_GetRenderObj(car));
        KartPos pos(m[3], m[7], m[11]);
        if (g->start == 1) {
            g->start = 0;
            if (!g->running && !g->landed) {
                g->running = 1;
                CarObject_GetRenderObj(car)->scale37C = g->step;
                CarObject_GetRenderObj(car)->scale1CC = g->step;
                CarObject_GetRenderObj(car)->speed = g->step * CarObject_GetRenderObj(car)->speed;
                g->lift = -(lbl_806DAE04 * (lbl_806DAD70 - g->step));
            }
        }
        if (g->running == 1 && g->landed == 1) {
            g->start = 0;
            g->running = 0;
            g->landed = 0;
            car->stepping = 1;
            CarObject_GetRenderObj(car)->scale37C = lbl_806DAD70;
            CarObject_GetRenderObj(car)->scale1CC = lbl_806DAD70;
            CarObject_GetRenderObj(car)->speed = g->div * CarObject_GetRenderObj(car)->speed;
            if (CarObject_GetRenderObj(car)->jobj != 0) {
                Object_SetField14_IfValid(CarObject_GetRenderObj(car)->jobj, lbl_806DAD70);
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
            m = KartDriver_GetKartRootMtx(CarObject_GetRenderObj(car));
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
            CarObject_GetRenderObj(car)->lift += g->lift;
            if (CarObject_GetRenderObj(car)->jobj != 0) {
                Object_SetField14_IfValid(CarObject_GetRenderObj(car)->jobj, g->step);
            }
        }
        CarObject_GetRenderObj(car)->lift += g->lift;
        g->mtx[12] = pos.x;
        g->mtx[13] = pos.y;
        g->mtx[14] = pos.z;
        for (int i = 0; i < 16; i++) {
            g->mtx[i] += g->delta[i];
        }
        KartItem_ForwardToCarMovement_8019a4e0(car, g->mtx);
        KartDriver_TickAction_79244(CarObject_GetRenderObj(car), g->spin * g->count);
    }
}

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
struct GoalLine {
    char pad[0x1C];
};
struct ScenePos {
    char pad[0x24];
};

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
