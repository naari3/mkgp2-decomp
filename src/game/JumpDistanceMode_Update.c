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
extern void *g_weatherSystem, *lbl_806D109C;
extern const float lbl_806DAD70, lbl_806DAD74, lbl_806DAD7C, lbl_806DAD88, lbl_806DADA4;
extern const float lbl_806DADB0, lbl_806DADD8, lbl_806DADE8, lbl_806DADEC, lbl_806DADF4;
extern const float JumpDistanceMode_rodata_803C3CF0[14];
void *GetRaceContextPtr();
void ItemObjectManager_PerFrameUpdate(void *);
void fn_802128F4(JDLanding *, void *);
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
void VfxSlotMgr_Update(Vec3, Vec3);
unsigned char IsRaceStarted();
void fn_802124FC(JDCoins *);
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
void *CarObject_GetRenderObj(void *);
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
    void *p = lbl_806D109C;
    if (!p) p = 0;
    return p;
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

extern "C" int JumpDistanceMode_Update(JDMode *self) {
    int i;
    Vec3 projection, scissor;

    if (self->active == 0) {
        self->active = 1;
    }
    ItemObjectManager_PerFrameUpdate(GetRaceContextPtr());
    fn_802128F4(self->landing, self->car);
    fn_8023E324(self->x1C, self->active);
    JumpDistanceMode_HandlePhysics(self);
    Fog_UpdateFromCourseScene3D();
    UpdateIntroCamera(self->introCamera);
    LakituStart_UpdateCountdown(self->lakitu);
    CourseEnvironment_UpdateAndCullZones_Timed(self->environment);
    if (g_raceEnded == 0) {
        JumpDistanceMode_UpdateGameplay(self);
    }
    CObj_LoadProjMatrix(self->camera, &projection);
    CObj_ApplyScissor(self->camera, &scissor);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(projection, scissor);
    if (IsRaceStarted() == 1 && g_raceEnded != 1 && self->state < 2 && g_raceTimeRemaining >= 0.0f) {
        if (self->landing->slowed == 0) {
            g_raceTimeRemaining = g_raceTimeRemaining - lbl_806DAD74;
        } else {
            g_raceTimeRemaining = g_raceTimeRemaining - lbl_806DAD74 * self->landing->scale;
        }
        if (g_raceTimeRemaining < 0.0f) {
            g_raceTimeRemaining = 0.0f;
            g_raceEnded = 1;
        }
    }
    fn_802124FC(self->coins);
    fn_80253FD8(self->hud, g_raceTimeRemaining);
    fn_80253EBC(self->hud, lbl_806DADA4 * CarObject_CalcSpeedRatio(self->car));
    fn_80253EC0(self->hud, KartItem_GetCurrentSpeedWithBonus(self->car));
    HUD_FrameUpdate(self->hud);
    UpdateTimer(self->display);
    RumbleUpdate();
    TransitionEffect_Tick(getTransition());
    if (g_raceEnded == 1) {
        if (self->endDelay > 0) {
            self->endDelay--;
        } else {
            if (self->resultFrames == 0) {
                float distance;
                int ok;

                if (self->coinCount > 15) {
                    self->coinCount = 15;
                }
                self->coins->earned = self->coinCount - self->coins->base;
                SetCoinCount(self->coinCount);
                ok = fn_801231AC();
                distance = self->distance;
                ok = distance >= (float)ok;
                if (self->reached != 0) {
                    fn_80253C74(self->hud, 1, NokoNokoChallenge_CalcResultText(self, 1, ok), (int)distance);
                    KartMovement_ResetOnGoal(CarObject_GetRenderObj(self->car));
                } else {
                    fn_80253C74(self->hud, 0, NokoNokoChallenge_CalcResultText(self, 0, ok), (int)distance);
                    KartMovement_ResetOnTimeout(CarObject_GetRenderObj(self->car));
                }
                NokoNokoChallenge_SaveResult(self, self->coinCount, self->reached);
                {
                    JDTimer *t = self->display;
                    t->slide = lbl_806DAD7C;
                    t->exiting = 1;
                }
                Object_SetByte10_Return1(self->camera, 1);
                g_lakituStartAnimDone = 0;
            } else if (fn_80253C40(self->hud)) {
                return NokoNokoChallenge_TransitionToResult(self);
            }
            self->resultFrames++;
        }
    }
    if (g_weatherSystem) {
        fn_8016B32C(g_weatherSystem);
    }
    return -2;
}
