#include "game/BiribiriLand_private.h"

/* BiribiriLand: Render/Update/UpdateObstacles/Destroy native; Init retains its original asm. */

/* === extracted from auto_BiribiriLand_Render_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

#include "game/singleton.h"

void CObj_DebugVizPathFlush(void *scene);
void CourseEnvironment_RenderObjects_Timed(void *env);
void DrawEffect_TickAndCull(void);
void ItemObjectManager_Render(void);
void KartItem_RenderPipelinedWithEffects(void *car, int arg);
void Object_RenderJObjIfWithinRange(void *o);
void Object_RenderJObjTree(void *o, int mask);
void Object_SetJObjField40(void *o, float v);
void Object_SetJObjPositionVec(void *o, Vec *v);
void Object_SetJObjPositionX(void *o, float v);
void Object_SetJObjPositionY(void *o, float v);
void Object_SetJObjRotationY(void *o, float r);
void Subsystem36c_DispatchPass2_Timed(void *env);
void Subsystem36c_DispatchPass4_Timed(void *env);
void TransitionEffect_RenderPass(void *te, int pass);
void TransparentDraw_SortAndDispatch(void);
void clDrawMan_Buckets_Dispatch(void *dm);
void clDrawMan_Buckets_Reset(void *dm);
void clDrawMan_EndFrame_NoOp(void *dm);
void fn_8016B0C4(void);
void fn_80253448(void *hud, unsigned int mask);
void fn_802535D4(void *hud);
void HSD_StateInvalidate(int mask);

extern float lbl_806CF5F0;
extern void *lbl_806D109C;
extern void *lbl_806D10AC;
extern const float lbl_806D7320;
extern unsigned int lbl_806DC1B8;

typedef struct BiribiriObstacleDesc {
    Vec a;
    Vec b;
    float yaw;
    int model;
    unsigned char glow;
} BiribiriObstacleDesc;

/* --- .rodata of this scene (0x80357B00..0x803580F8) --- */
/* Table at the start of this scene's .rodata (0x80357B00); no code reference. */
const float lbl_80357B00[255] = {
    1.0f, 0.7f, 0.9f,
    0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f,
    0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f,
    0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f,
    0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f,
    0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f,
    0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f,
    0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f,
    0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f,
    0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f,
    0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f,
    0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f,
    0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f,
    0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f,
    0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f,
    0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f,
    0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f,
    0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f,
    0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f,
};

/* Model archives (referenced from the scene's .data table). */
const char lbl_80357EFC[] = "obj_red.dat";
const char lbl_80357F08[] = "obj_blue.dat";
const char lbl_80357F18[] = "obj_yellow.dat";
const char lbl_80357F28[] = "obj_pink.dat";
const char lbl_80357F38[] = "obj_purple.dat";
const char lbl_80357F48[] = "obj_UFO.dat";
const char lbl_80357F54[] = "packland_biribiri.dat";

/* Obstacle gates: two posts, gate yaw, post model, electric pole flag. */
const BiribiriObstacleDesc lbl_80357F6C[9] = {
    {{113.0f, 0.0f, -1700.0f}, {-113.0f, 0.0f, -1700.0f}, 0.0f, 0, 0},
    {{113.0f, 0.0f, -3900.0f}, {-113.0f, 0.0f, -3900.0f}, 0.0f, 1, 0},
    {{113.0f, 0.0f, -5800.0f}, {-113.0f, 0.0f, -5800.0f}, 0.0f, 2, 0},
    {{113.0f, 0.0f, -7400.0f}, {-113.0f, 0.0f, -7400.0f}, 0.0f, 3, 0},
    {{1450.0f, 0.0f, -8724.0f}, {1450.0f, 0.0f, -8950.0f}, -1.5707964f, 2, 0},
    {{2735.0f, 0.0f, -8724.0f}, {2735.0f, 0.0f, -8950.0f}, -1.5707964f, 0, 1},
    {{4035.0f, 0.0f, -8724.0f}, {4035.0f, 0.0f, -8950.0f}, -1.5707964f, 1, 0},
    {{5100.0f, 0.0f, -8724.0f}, {5100.0f, 0.0f, -8950.0f}, -1.5707964f, 3, 1},
    {{6000.0f, 0.0f, -8724.0f}, {6000.0f, 0.0f, -8950.0f}, -1.5707964f, 0, 1},
};

#pragma cplusplus on
struct BiribiriScene {
    virtual ~BiribiriScene();
    virtual unsigned char IsReady();
    virtual void Draw();
};
#pragma cplusplus reset

static inline void BiribiriDrawObstacles(BiribiriObstacles *obs)
{
    unsigned int i;

    for (i = 0; i < 9; i++) {
        int model = lbl_80357F6C[i].model;
        float yaw = lbl_80357F6C[i].yaw;
        if (model != 0) {
            yaw += lbl_806D7320;
        }
        Object_SetJObjPositionVec(obs->model[model], &obs->obstacles[i].a);
        Object_SetJObjRotationY(obs->model[model], yaw);
        Object_RenderJObjTree(obs->model[model], 7);
        if (lbl_80357F6C[i].glow) {
            Object_SetJObjPositionX(obs->model[5], obs->obstacles[i].a.x);
            Object_SetJObjPositionY(obs->model[5], obs->obstacles[i].a.y + lbl_806CF5F0);
            Object_SetJObjField40(obs->model[5], obs->obstacles[i].a.z);
            Object_SetJObjRotationY(obs->model[5], yaw);
            Object_RenderJObjTree(obs->model[5], 7);
        }
        Object_SetJObjPositionVec(obs->model[model], &obs->obstacles[i].b);
        Object_SetJObjRotationY(obs->model[model], yaw);
        Object_RenderJObjTree(obs->model[model], 7);
        if (lbl_80357F6C[i].glow) {
            Object_SetJObjPositionX(obs->model[5], obs->obstacles[i].b.x);
            Object_SetJObjPositionY(obs->model[5], obs->obstacles[i].b.y + lbl_806CF5F0);
            Object_SetJObjField40(obs->model[5], obs->obstacles[i].b.z);
            Object_SetJObjRotationY(obs->model[5], yaw);
            Object_RenderJObjTree(obs->model[5], 7);
        }
        if (obs->obstacles[i].hit == 0) {
            Object_SetJObjPositionVec(obs->model[6], &obs->obstacles[i].center);
            Object_SetJObjRotationY(obs->model[6], yaw);
            Object_RenderJObjTree(obs->model[6], 7);
        }
    }
}

#pragma exceptions on
#pragma use_lmw_stmw on
void BiribiriLand_Render(BiribiriState *self)
{
    if (self->visible == 0) {
        return;
    }
    if (((struct BiribiriScene *)self->scene)->IsReady() == 1) {
        clDrawMan_Buckets_Reset(SINGLETON_INSTANCE(lbl_806D10AC));
        TransparentDraw_SortAndDispatch();
        CObj_DebugVizPathFlush(self->scene);
        fn_8016B0C4();
        KartItem_RenderPipelinedWithEffects(self->car, 0);
        Object_RenderJObjIfWithinRange(self->lakitu);
        CourseEnvironment_RenderObjects_Timed(self->environment);
        Subsystem36c_DispatchPass2_Timed(self->environment);
        BiribiriDrawObstacles(self->obstacles);
        ItemObjectManager_Render();
        DrawEffect_TickAndCull();
        clDrawMan_EndFrame_NoOp(SINGLETON_INSTANCE(lbl_806D10AC));
        clDrawMan_Buckets_Dispatch(SINGLETON_INSTANCE(lbl_806D10AC));
        Subsystem36c_DispatchPass4_Timed(self->environment);
        TransitionEffect_RenderPass(SINGLETON_INSTANCE(lbl_806D109C), 2);
        TransitionEffect_RenderPass(SINGLETON_INSTANCE(lbl_806D109C), 4);
        ((struct BiribiriScene *)self->scene)->Draw();
    }
    fn_80253448(self->hud, lbl_806DC1B8);
    fn_802535D4(self->hud);
    TransitionEffect_RenderPass(SINGLETON_INSTANCE(lbl_806D109C), 1);
    HSD_StateInvalidate(0x7f);
}
#pragma use_lmw_stmw reset
#pragma exceptions reset


/* === BiribiriLand_Update === */
extern void BiribiriLand_UpdateObstacles();
#pragma cplusplus on
struct BiribiriInput {
    virtual void slot08();
    virtual void slot0c();
    virtual float steering();
    virtual void slot14();
    virtual float accelerator();
    virtual float brake();
};

typedef struct BiribiriGoal {
    Vec pos;
    char padC[0x18];
    Vec normal;
} BiribiriGoal;

typedef struct BiribiriHitInfo {
    char pad0[8];
    int type;
    char padC[0x94];
    Vec pos;
    char padAC[0x140];
} BiribiriHitInfo;

typedef struct BiribiriCoinRank {
    int time;
    int coins;
} BiribiriCoinRank;

typedef float BiribiriMtx[3][4];

extern "C" {
void CObj_ApplyScissor(void *scene, Vec *v);
void CObj_LoadProjMatrix(void *scene, Vec *v);
void CarObject_ApplyInput(void *car, float steering, float accelerator, float brake, unsigned char started);
float CarObject_CalcSpeedRatio(void *car);
void CarObject_FrameUpdate(void *car, int arg);
void *CarObject_GetRenderObj(void *car);
void CarObject_HandleObstacleHit(void *car, BiribiriHitInfo *info);
void ChallengeGoalCamera_Update(void *cam, void *scene, void *mtx);
void CourseEnvironment_UpdateAndCullZones_Timed(void *env);
void Fog_UpdateFromCourseScene3D(void);
void *GetInputManager(void);
void GetRaceContextPtr();
void HUD_FrameUpdate(void *hud);
BiribiriInput *InputMgr_GetPlayer(void *mgr, int idx);
unsigned char IsRaceStarted(void);
void ItemObjectManager_PerFrameUpdate();
void ItemObjectManager_Update(void);
BiribiriMtx *KartDriver_GetKartRootMtx(void *obj);
void KartItem_CancelActiveEffect(void *car);
float KartItem_GetCurrentSpeedWithBonus(void *car);
void KartItem_UpdateShadowBillboardAndViewport(void *car, void *scene, int arg);
void KartMovement_ResetOnGoal(void *obj);
void KartMovement_ResetOnTimeout(void *obj);
void KartMovement_SetSpeedScale(void *car, float scale);
void KartReaction_Rear(void *obj);
void LakituStart_UpdateCountdown(void *lakitu);
int MiniGame_GetTimerValue(void);
int NokoNokoChallenge_CalcResultText(void *self, int success, int arg);
BiribiriCoinRank **NokoNokoChallenge_GetCoinDivisor(void);
unsigned char NokoNokoChallenge_HandleBrakeInput(void *self, bool brake);
void NokoNokoChallenge_SaveResult(void *self, int coins, unsigned char success);
int NokoNokoChallenge_TransitionToResult(void *self);
int Object_SetByte10_Return1(void *o, int v);
void SetCoinCount(int coins);
void SoundMgr_PlaySE(int id);
void TransitionEffect_Tick(void *te);
float Vec3_Dot(Vec *a, Vec *b);
void Vec3_Subtract(Vec *a, Vec *b, Vec *out);
void VfxSlotMgr_Update(Vec a, Vec b);
void fn_8016B32C(void *w);
unsigned char fn_80253C40(void *hud);
void fn_80253C74(void *hud, int success, int text, int time);
void fn_80253EBC(void *hud, float v);
void fn_80253EC0(void *hud, float v);
void fn_80253FD8(void *hud, float v);
void *memset(void *p, int c, unsigned long n);

extern unsigned int g_weatherSystem;
extern unsigned char g_lakituStartAnimDone;
extern unsigned char g_raceEnded;
extern float g_raceTimeRemaining;
extern unsigned char lbl_806D1290;
extern const float lbl_806D7324;
extern const float lbl_806D7328;
extern const float lbl_806D732C;
extern const float lbl_806D7330;
extern const float lbl_806D7334;
extern const float lbl_806D7338;
extern const float lbl_806D733C;
extern const float lbl_806D7340;
extern const float lbl_806D7344;
extern Vec lbl_80677C88;
extern Vec lbl_80677C94;
}

static inline unsigned char BiribiriCheckObstacleHit(BiribiriObstacles *obs, Vec *pos)
{
    unsigned int i;
    Vec d;

    for (i = 0; i < 9; i++) {
        if (obs->obstacles[i].hit == 0) {
            float dot;
            Vec3_Subtract(pos, &obs->obstacles[i].a, &d);
            dot = Vec3_Dot(&d, &obs->obstacles[i].direction);
            if (dot < lbl_806D7338 && dot > lbl_806D733C && pos->y < obs->obstacles[i].center.y) {
                obs->obstacles[i].hit = 1;
                SoundMgr_PlaySE(0x90);
                return 1;
            }
        }
    }
    return 0;
}

static inline unsigned char BiribiriCheckGoal(BiribiriGoal *goal, Vec *pos)
{
    Vec d;

    Vec3_Subtract(pos, &goal->pos, &d);
    return Vec3_Dot(&d, &goal->normal) > lbl_806D7330;
}

#pragma exceptions on
extern "C" int BiribiriLand_Update(BiribiriState *self)
{
    BiribiriInput *input;

    if (self->visible == 0) {
        self->visible = 1;
    }
    GetRaceContextPtr();
    ItemObjectManager_PerFrameUpdate();
    input = InputMgr_GetPlayer(GetInputManager(), 0);
    if (g_raceEnded != 1) {
        float accelerator;
        float brake;
        if (lbl_806D1290 == 0) {
            accelerator = input->accelerator();
        } else {
            accelerator = lbl_806D7324;
        }
        brake = input->brake();
        if (NokoNokoChallenge_HandleBrakeInput(self, accelerator < lbl_806D732C && brake < lbl_806D732C && IsRaceStarted()) == 1) {
            accelerator = lbl_806D7328;
        }
        CarObject_ApplyInput(self->car, input->steering(), accelerator, brake, IsRaceStarted());
        CarObject_FrameUpdate(self->car, 0);
        KartItem_UpdateShadowBillboardAndViewport(self->car, self->scene, 0);
    } else {
        CarObject_ApplyInput(self->car, lbl_806D7330, lbl_806D7330, lbl_806D7330, 1);
        KartMovement_SetSpeedScale(self->car, lbl_806D7334);
        CarObject_FrameUpdate(self->car, 0);
        ChallengeGoalCamera_Update(self->goalCamera, self->scene, KartDriver_GetKartRootMtx(CarObject_GetRenderObj(self->car)));
    }
    Fog_UpdateFromCourseScene3D();
    LakituStart_UpdateCountdown(self->lakitu);
    CourseEnvironment_UpdateAndCullZones_Timed(self->environment);
    BiribiriLand_UpdateObstacles(self->obstacles);
    if (self->finished == 0) {
        Vec pos;
        BiribiriMtx *mtx = KartDriver_GetKartRootMtx(CarObject_GetRenderObj(self->car));
        pos.x = (*mtx)[0][3];
        pos.y = (*mtx)[1][3];
        pos.z = (*mtx)[2][3];
        if (BiribiriCheckObstacleHit(self->obstacles, &pos)) {
            BiribiriHitInfo info;
            KartReaction_Rear(CarObject_GetRenderObj(self->car));
            memset(&info, 0, sizeof(info));
            info.pos.x = pos.x;
            info.pos.y = pos.y;
            info.pos.z = pos.z;
            info.type = 8;
            CarObject_HandleObstacleHit(self->car, &info);
        }
        if (BiribiriCheckGoal((BiribiriGoal *)self->goal, &pos)) {
            self->success = 1;
            self->finished = 1;
            KartItem_CancelActiveEffect(self->car);
            KartMovement_ResetOnGoal(CarObject_GetRenderObj(self->car));
        }
    }
    CObj_LoadProjMatrix(self->scene, &lbl_80677C88);
    CObj_ApplyScissor(self->scene, &lbl_80677C94);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(lbl_80677C88, lbl_80677C94);
    if (IsRaceStarted() && self->finished == 0 && g_raceTimeRemaining >= 0.0f) {
        g_raceTimeRemaining -= 0.016666668f;
        if (g_raceTimeRemaining < 0.0f) {
            g_raceTimeRemaining = 0.0f;
            self->finished = 1;
            KartItem_CancelActiveEffect(self->car);
            KartMovement_ResetOnTimeout(CarObject_GetRenderObj(self->car));
        }
    }
    fn_80253FD8(self->hud, g_raceTimeRemaining);
    fn_80253EBC(self->hud, lbl_806D7344 * CarObject_CalcSpeedRatio(self->car));
    fn_80253EC0(self->hud, KartItem_GetCurrentSpeedWithBonus(self->car));
    HUD_FrameUpdate(self->hud);
    TransitionEffect_Tick(SINGLETON_INSTANCE(lbl_806D109C));
    if (self->finished) {
        if (self->resultTimer == 0) {
            int time;
            int coins;
            time = (int)(MiniGame_GetTimerValue() - g_raceTimeRemaining);
            coins = 0;
            BiribiriCoinRank **ranks = NokoNokoChallenge_GetCoinDivisor();
            if (ranks != 0 && self->success == 1) {
                int i;
                for (i = 0; (*ranks)[i].coins > 0; i++) {
                    if (time <= (*ranks)[i].time) {
                        coins = (*ranks)[i].coins;
                        break;
                    }
                }
            }
            SetCoinCount(coins);
            if (self->success) {
                fn_80253C74(self->hud, 1, NokoNokoChallenge_CalcResultText(self, 1, 0), (int)g_raceTimeRemaining);
                Object_SetByte10_Return1(self->scene, 1);
            } else {
                fn_80253C74(self->hud, 0, NokoNokoChallenge_CalcResultText(self, 0, 0), (int)g_raceTimeRemaining);
                Object_SetByte10_Return1(self->scene, 1);
            }
            NokoNokoChallenge_SaveResult(self, coins, self->success);
            g_raceEnded = 1;
            g_lakituStartAnimDone = 0;
        } else if (fn_80253C40(self->hud)) {
            return NokoNokoChallenge_TransitionToResult(self);
        }
        self->resultTimer++;
    }
    if (g_weatherSystem) {
        fn_8016B32C((void *)g_weatherSystem);
    }
    return -2;
}
#pragma exceptions reset
#pragma cplusplus reset


/* === BiribiriLand_UpdateObstacles === */
void *GetCourseScene3D(void);
float LUT_Sin12Bit(float x);
void clNormal3D_Exec(void *o);
void fn_8016C288(int id, Vec *pos);
unsigned char fn_8016C360(int id);
void fn_8016C394(int id);
float PSVECSquareMag(Vec *v);
extern const float lbl_806D7350;
extern const float lbl_806D7354;
extern const float lbl_806D7358;
extern const float lbl_806D735C;
extern const float lbl_806D7360;

#pragma exceptions on
void BiribiriLand_UpdateObstacles(BiribiriObstacles *obs)
{
    Vec nearest = {0.0f, 0.0f, 0.0f};
    Vec camera = {0.0f, 0.0f, 0.0f};
    Vec d;
    float best = lbl_806D7350;
    float dist;
    unsigned int i;

    if (GetCourseScene3D() != 0) {
        CObj_LoadProjMatrix(GetCourseScene3D(), &camera);
    }
    for (i = 0; i < 9; i++) {
        float lift;
        obs->obstacles[i].phase += lbl_806D7328;
        if (obs->obstacles[i].phase >= lbl_806D7354) {
            obs->obstacles[i].phase = lbl_806D7330;
        }
        lift = lbl_806D7330;
        if (lbl_80357F6C[i].glow) {
            lift = 5.0f * LUT_Sin12Bit(lbl_806D735C * obs->obstacles[i].phase) + 5.0f;
        }
        obs->obstacles[i].a.x = lbl_80357F6C[i].a.x;
        obs->obstacles[i].a.y = lbl_80357F6C[i].a.y;
        obs->obstacles[i].a.z = lbl_80357F6C[i].a.z;
        obs->obstacles[i].b.x = lbl_80357F6C[i].b.x;
        obs->obstacles[i].b.y = lbl_80357F6C[i].b.y;
        obs->obstacles[i].b.z = lbl_80357F6C[i].b.z;
        obs->obstacles[i].a.y += lift;
        obs->obstacles[i].b.y += lift;
        obs->obstacles[i].center.x = lbl_806D7334 * (obs->obstacles[i].a.x + obs->obstacles[i].b.x);
        obs->obstacles[i].center.y = lbl_806D7334 * (obs->obstacles[i].a.y + obs->obstacles[i].b.y) + lbl_806D7360;
        obs->obstacles[i].center.z = lbl_806D7334 * (obs->obstacles[i].a.z + obs->obstacles[i].b.z);
        if (obs->obstacles[i].hit == 0) {
            if (best < lbl_806D7330) {
                nearest.x = obs->obstacles[i].center.x;
                nearest.y = obs->obstacles[i].center.y;
                nearest.z = obs->obstacles[i].center.z;
                Vec3_Subtract(&nearest, &camera, &d);
                best = PSVECSquareMag(&d);
            } else {
                Vec3_Subtract(&obs->obstacles[i].center, &camera, &d);
                dist = PSVECSquareMag(&d);
                if (dist < best) {
                    best = dist;
                    nearest.x = obs->obstacles[i].center.x;
                    nearest.y = obs->obstacles[i].center.y;
                    nearest.z = obs->obstacles[i].center.z;
                }
            }
        }
    }
    clNormal3D_Exec(obs->model[6]);
    if (dist >= lbl_806D7330) {
        if (!fn_8016C360(0x91)) {
            SoundMgr_PlaySE(0x91);
        }
        fn_8016C288(0x91, &nearest);
    } else if (fn_8016C360(0x91)) {
        fn_8016C394(0x91);
    }
}
#pragma exceptions reset

/* --- class-name strings and Lakitu archive (tail of the scene's .rodata) --- */
const char lbl_803580C8[] = "clCGamePC";
const char lbl_803580D4[] = "clJobRunner";
const char lbl_803580E0[] = "jyugemu_start.dat";



/* === extracted from auto_BiribiriLand_Destroy_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ClRomTable_PurgeAll();
extern void CourseEnvironment_Dtor();
extern void GetRaceContextPtr();
extern void ItemObjectManager_Reset();
extern void LakituStart_Dtor();
extern void MemoryManager_TimedFree();
extern void Object_DtorWithGXSync();
extern void RankingTable_Init();
extern void SceneDrawList_Reset();
extern void SetActiveCamera();
extern void SetPlayerCarObject();
extern void SetResourceLoadingFlag();
extern void VfxSlotMgr_Shutdown();
extern void clRom_PurgeAll();
extern void dtor_80122FD8();
extern void fn_80124C84();
extern void fn_8016C634();
extern void fn_80254134();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_raceCamera;
extern unsigned int g_weatherSystem;
extern unsigned int lbl_806D10D0;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8048E46C[];

/* --- function index (1 fns, .text 0x80134D68..0x80134FF0) ---
 * [  0] 0x80134D68 size:0x288   global BiribiriLand_Destroy
 */

/* --- forward decls --- */
void *BiribiriLand_Destroy(BiribiriState *, short);

#pragma cplusplus on
struct BiribiriVirtual {
    virtual ~BiribiriVirtual();
};
struct BiribiriCarVirtual {
    virtual void key();
    virtual ~BiribiriCarVirtual();
};
void operator delete(void *);

/* ref_DEC follows the canonical HSD object.h inline. */
static inline int BiribiriRefDec(BiribiriLight *obj)
{
    unsigned char unreferenced;
    if ((unreferenced = (obj->references == (unsigned short)0xFFFF)))
        return unreferenced;
    return obj->references-- == 0;
}
static inline void BiribiriLightDelete(BiribiriLight *obj)
{
    if (obj) {
        obj->info->release(obj);
        obj->info->destroy(obj);
    }
}
static inline void BiribiriLightUnref(BiribiriLight *obj)
{
    if (obj && BiribiriRefDec(obj))
        BiribiriLightDelete(obj);
}
static inline void BiribiriCameraRelease(BiribiriVirtual *camera)
{
    if (camera)
        delete camera;
}

static inline void BiribiriDestroyObstacles(BiribiriObstacles *obstacles)
{
    if (obstacles) {
        int i;
        for (i = 0; i < 7; i++)
            Object_DtorWithGXSync(obstacles->model[i], 1);
        MemoryManager_TimedFree(obstacles);
    }
}

#pragma exceptions on
#pragma use_lmw_stmw on
extern "C" void *BiribiriLand_Destroy(BiribiriState *self, short freeMemory)
{
    if (self) {
        self->vtable = lbl_8048E46C;
        if (g_weatherSystem) {
            fn_8016C634((void *)g_weatherSystem, 1);
            g_weatherSystem = 0;
        }
        SetActiveCamera(0, 0);
        delete (BiribiriVirtual *)self->scene;
        LakituStart_Dtor(self->lakitu, 1);
        fn_80124C84(self->goalCamera, 1);
        SetPlayerCarObject(0);
        delete (BiribiriCarVirtual *)self->car;
        g_raceCamera = 0;
        BiribiriCameraRelease((BiribiriVirtual *)self->camera);
        if (self->lights)
            BiribiriLightUnref(self->lights);
        CourseEnvironment_Dtor(self->environment, 1);
        fn_80254134(self->hud, 1);
        BiribiriDestroyObstacles(self->obstacles);
        if (self->goal)
            MemoryManager_TimedFree(self->goal);
        ItemObjectManager_Reset();
        VfxSlotMgr_Shutdown();
        ClRomTable_PurgeAll();
        GetRaceContextPtr();
        RankingTable_Init();
        delete (BiribiriVirtual *)lbl_806D10D0;
        lbl_806D10D0 = 0;
        SceneDrawList_Reset();
        delete (BiribiriVirtual *)lbl_806D109C;
        lbl_806D109C = 0;
        SetResourceLoadingFlag(0);
        clRom_PurgeAll();
        delete (BiribiriVirtual *)lbl_806D10AC;
        lbl_806D10AC = 0;
        dtor_80122FD8(self, 0);
        if (freeMemory > 0)
            MemoryManager_TimedFree(self);
    }
    return self;
}
#pragma use_lmw_stmw reset
#pragma exceptions reset
#pragma cplusplus reset


/* === extracted from auto_BiribiriLand_Init_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void Camera_Create();
extern void CarObject_Init();
extern void CarObject_SetPosition();
extern void ChallengeGoalCamera_Init();
extern void CourseObjectManager_Init();
extern void DMAChannelManager_Init();
extern void DrawManager_GetOrCreate();
extern void GameMode_BaseInit();
extern void GetCourseDataPtr();
extern void GetCourseStartYaw();
extern void GetDisplayBufferIndex();
extern void GetKartModelNameEntry();
extern void GetRaceContextPtr();
extern void GetStartPosition();
extern void HUD_Init();
extern void HUD_RegisterOverlay();
extern void InputManager_Init();
extern void ItemObjectManager_Init();
extern void LakituStart_Init();
extern void Object_SetJObjScaleXYZ();
extern void PreloadEffectResources();
extern void ProcessSystemTick();
extern void RankingTable_Init();
extern void HSD_LObjLoadDesc();
extern void Scene3D_GetCameraPos();
extern void Scene3D_Init();
extern void Scene3D_SetupProjection();
extern void SetActiveCamera();
extern void SetCourseScene3D();
extern void SetPlayerCarObject();
extern void SetResourceLoadingFlag();
extern void SoundChannels_ClearAll();
extern void SoundDriver_GetOrCreate();
extern void TransitionEffect_GetOrCreate();
extern void Vec3_Normalize();
extern void Vec3_Subtract();
extern void WeatherSystem_Init();
extern void clNormal3D_Construct();
extern void clNormal3D_SetScale();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_characterId;
extern unsigned int g_raceCamera;
extern unsigned int g_weatherSystem;
extern unsigned int lbl_806D12BC;
extern unsigned int lbl_806D7348;
extern unsigned int lbl_806D7364;
extern unsigned int lbl_806D7368;
extern unsigned int lbl_806D736C;
extern unsigned int lbl_806D7370;
extern unsigned int lbl_806D7374;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8048E144[];
extern unsigned int lbl_8048E430[];
extern unsigned int lbl_8048E46C[];

/* --- function index (1 fns, .text 0x80134FF0..0x8013558C) ---
 * [  0] 0x80134FF0 size:0x59C   global BiribiriLand_Init
 */

/* --- forward decls --- */
asm void BiribiriLand_Init(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();
extern void dtor_80122FD8();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; unsigned int f29; unsigned int f30; unsigned int f31; unsigned int f32; unsigned int f33; unsigned int f34; unsigned int f35; unsigned int f36; unsigned int f37; unsigned int f38; unsigned int f39; unsigned int f40; unsigned int f41; unsigned int f42; unsigned int f43; unsigned int f44; unsigned int f45; unsigned int f46; unsigned int f47; unsigned int f48; void *f49; unsigned int f50; unsigned int f51; void *f52; unsigned int f53; void *f54; unsigned int f55; unsigned int f56; void *f57; unsigned int f58; void *f59; unsigned int f60; unsigned int f61; void *f62; unsigned int f63; void *f64; unsigned int f65; unsigned int f66; void *f67; unsigned int f68; void *f69; unsigned int f70; unsigned int f71; void *f72; unsigned int f73; void *f74; unsigned int f75; unsigned int f76; void *f77; unsigned int f78; void *f79; unsigned int f80; unsigned int f81; void *f82; unsigned int f83; void *f84; unsigned int f85; void *f86; unsigned int f87; unsigned int f88; void *f89; unsigned int f90; void *f91; unsigned int f92; unsigned int f93; void *f94; unsigned int f95; void *f96; unsigned int f97; unsigned int f98; void *f99; } extab_BiribiriLand_Init = { 0x30CA0000, 0x000000A8, 0x000900C8, 0x000000D8, 0x000000C0, 0x000000E0, 0x000400C8, 0x00000110, 0x000000D4, 0x00000120, 0x001100C8, 0x00000174, 0x001000E8, 0x000001C4, 0x000800C8, 0x00000208, 0x000000FC, 0x00000214, 0x000000C8, 0x00000228, 0x00040110, 0x00000244, 0x000000C8, 0x00000250, 0x00000124, 0x0000025C, 0x000D00C8, 0x000002A0, 0x00000138, 0x000002B4, 0x002300C8, 0x00000360, 0x00000154, 0x00000374, 0x0000014C, 0x00000394, 0x003D0154, 0x000004D0, 0x000000C8, 0x00000510, 0x00030168, 0x00000550, 0x000000C8, 0x00000560, 0x0000017C, 0x0000056C, 0x000000C8, 0x00000000, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001C, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x0A80001B, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80122FD8 };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_BiribiriLand_Init = {
    (void *)&BiribiriLand_Init, 0x0000059C, (void *)&extab_BiribiriLand_Init
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void BiribiriLand_Init(void) { /* 0x80134FF0 size:0x59C */
    nofralloc
    stwu r1, -0x80(r1)
    mflr r0
    stw r0, 0x84(r1)
    stfd f31, 0x70(r1)
    psq_st f31, 0x78(r1), 0, 0
    stfd f30, 0x60(r1)
    psq_st f30, 0x68(r1), 0, 0
    stfd f29, 0x50(r1)
    psq_st f29, 0x58(r1), 0, 0
    stmw r26, 0x38(r1)
    mr r31, r3
    mr r0, r31
    mr r28, r0
    bl GameMode_BaseInit
    lis r4, lbl_8048E144@ha
    lis r3, lbl_8048E46C@ha
    addi r0, r4, lbl_8048E144@l
    lfs f0, lbl_806D7330(r2)
    stw r0, 0x0(r28)
    addi r3, r3, lbl_8048E46C@l
    li r0, 0x0
    stfs f0, 0x4(r28)
    stw r3, 0x0(r31)
    stw r0, 0x8(r31)
    stw r0, 0xc(r31)
    stw r0, 0x10(r31)
    stw r0, 0x14(r31)
    stw r0, 0x18(r31)
    stw r0, 0x1c(r31)
    stw r0, 0x20(r31)
    stw r0, 0x24(r31)
    stb r0, 0x28(r31)
    stb r0, 0x29(r31)
    stb r0, 0x2a(r31)
    stb r0, 0x2b(r31)
    stw r0, 0x2c(r31)
    stw r0, 0x30(r31)
    stw r0, 0x34(r31)
    stfs f0, 0x38(r31)
    stfs f0, 0x3c(r31)
    stfs f0, 0x40(r31)
    bl DrawManager_GetOrCreate
    li r3, 0x0
    bl SetResourceLoadingFlag
    bl DMAChannelManager_Init
    bl TransitionEffect_GetOrCreate
    bl SoundChannels_ClearAll
    bl ItemObjectManager_Init
    bl CourseObjectManager_Init
    li r3, 0x37c
    bl Alloc
    mr. r28, r3
    beq BiribiriLand_Init_L_801350C8
    bl InputManager_Init
    BiribiriLand_Init_L_801350C8:
    stw r28, 0x10(r31)
    bl GetCourseDataPtr
    bl HSD_LObjLoadDesc
    stw r3, 0x20(r31)
    li r3, 0x2c
    bl Alloc
    mr. r28, r3
    beq BiribiriLand_Init_L_80135100
    lfs f1, lbl_806D7364(r2)
    li r4, 0x100
    lfs f2, lbl_806D732C(r2)
    li r5, 0x100
    lwz r6, 0x20(r31)
    bl Camera_Create
    BiribiriLand_Init_L_80135100:
    stw r28, 0x1c(r31)
    li r3, 0x0
    lwz r4, 0x1c(r31)
    bl SetActiveCamera
    lwz r0, 0x1c(r31)
    li r3, 0x0
    stw r0, g_raceCamera(r13)
    bl ProcessSystemTick
    bl GetRaceContextPtr
    bl RankingTable_Init
    li r0, 0x0
    li r3, 0x0
    stw r0, lbl_806D12BC(r13)
    bl SoundDriver_GetOrCreate
    addi r6, r1, 0x2c
    addi r4, r1, 0x24
    addi r5, r1, 0x28
    li r3, 0x0
    bl GetStartPosition
    li r3, 0x118
    bl Alloc
    mr. r28, r3
    beq BiribiriLand_Init_L_801351A4
    lwz r30, g_characterId(r13)
    bl GetCourseStartYaw
    fmr f29, f1
    bl GetDisplayBufferIndex
    li r0, 0x0
    mr r4, r3
    stw r0, 0x8(r1)
    fmr f3, f29
    mr r3, r28
    mr r5, r30
    lfs f1, 0x24(r1)
    li r6, 0x0
    lfs f2, 0x2c(r1)
    li r7, 0x0
    li r8, 0x1
    li r9, 0x3
    li r10, 0x0
    bl CarObject_Init
    BiribiriLand_Init_L_801351A4:
    stw r28, 0x8(r31)
    addi r4, r1, 0x24
    lwz r3, 0x8(r31)
    bl CarObject_SetPosition
    lwz r3, 0x8(r31)
    bl CarObject_GetRenderObj
    li r0, 0x1
    stw r0, 0x238(r3)
    lwz r3, 0x8(r31)
    bl SetPlayerCarObject
    li r3, 0x58
    bl Alloc
    mr. r28, r3
    beq BiribiriLand_Init_L_801351F8
    lfs f1, lbl_806D7330(r2)
    lis r4, lbl_803580E0@ha
    addi r4, r4, lbl_803580E0@l
    li r5, 0x0
    fmr f2, f1
    fmr f3, f1
    bl LakituStart_Init
    BiribiriLand_Init_L_801351F8:
    stw r28, 0xc(r31)
    li r3, 0x3084
    bl Alloc
    mr. r28, r3
    beq BiribiriLand_Init_L_80135228
    lwz r3, g_characterId(r13)
    li r4, -0x1
    bl GetKartModelNameEntry
    mr r4, r3
    mr r3, r28
    lwz r4, 0x0(r4)
    bl Scene3D_Init
    BiribiriLand_Init_L_80135228:
    stw r28, 0x14(r31)
    li r3, 0x8
    bl Alloc
    mr. r28, r3
    beq BiribiriLand_Init_L_80135240
    bl ChallengeGoalCamera_Init
    BiribiriLand_Init_L_80135240:
    stw r28, 0x18(r31)
    li r3, 0x0
    bl ProcessSystemTick
    lwz r3, 0x14(r31)
    addi r4, r1, 0x14
    addi r5, r1, 0x10
    bl Scene3D_GetCameraPos
    lfs f1, 0x14(r1)
    lfs f0, lbl_806D7338(r2)
    lfs f2, 0x10(r1)
    fadds f1, f1, f0
    stfs f1, 0x14(r1)
    lwz r3, 0x14(r31)
    bl Scene3D_SetupProjection
    li r3, 0x80
    bl Alloc
    mr. r28, r3
    beq BiribiriLand_Init_L_80135290
    li r4, 0x0
    bl HUD_Init
    BiribiriLand_Init_L_80135290:
    stw r28, 0x24(r31)
    li r4, 0x6
    li r5, 0x0
    lwz r3, 0x24(r31)
    bl HUD_RegisterOverlay
    lwz r3, 0x24(r31)
    li r4, 0x11
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x24(r31)
    li r4, 0x12
    li r5, 0x0
    bl HUD_RegisterOverlay
    lwz r3, 0x24(r31)
    li r4, 0xe
    li r5, 0x0
    bl HUD_RegisterOverlay
    li r0, 0x0
    stb r0, g_lakituStartAnimDone(r13)
    lwz r3, 0x14(r31)
    bl SetCourseScene3D
    li r0, 0x0
    stb r0, g_raceEnded(r13)
    bl MiniGame_GetTimerValue
    xoris r3, r3, 0x8000
    lis r0, 0x4330
    stw r3, 0x34(r1)
    li r3, 0x1
    lfd f1, lbl_806D7348(r2)
    stw r0, 0x30(r1)
    lfd f0, 0x30(r1)
    fsubs f0, f0, f1
    stfs f0, g_raceTimeRemaining(r13)
    bl PreloadEffectResources
    li r3, 0x9
    bl PreloadEffectResources
    li r3, 0xa
    bl PreloadEffectResources
    li r3, 0x214
    bl Alloc
    mr. r27, r3
    beq BiribiriLand_Init_L_801354B4
    lis r3, lbl_8048E430@ha
    mr r28, r27
    addi r29, r3, lbl_8048E430@l
    li r30, 0x0
    BiribiriLand_Init_L_80135348:
    li r3, 0x5c
    bl Alloc
    mr. r26, r3
    beq BiribiriLand_Init_L_80135364
    lwz r4, 0x0(r29)
    li r5, 0x0
    bl clNormal3D_Construct
    BiribiriLand_Init_L_80135364:
    cmpwi r30, 0x5
    stw r26, 0x0(r28)
    bgt BiribiriLand_Init_L_80135384
    lfs f1, lbl_806D7368(r2)
    lwz r3, 0x0(r28)
    fmr f2, f1
    fmr f3, f1
    bl Object_SetJObjScaleXYZ
    BiribiriLand_Init_L_80135384:
    addi r30, r30, 0x1
    addi r28, r28, 0x4
    cmpwi r30, 0x7
    addi r29, r29, 0x4
    blt BiribiriLand_Init_L_80135348
    lfs f1, lbl_806D7330(r2)
    li r4, 0x0
    lwz r3, 0x18(r27)
    fmr f3, f1
    lfs f2, lbl_806D7328(r2)
    fmr f4, f1
    bl clNormal3D_SetScale
    lis r3, lbl_80357F6C@ha
    lfs f30, lbl_806D7334(r2)
    lfs f31, lbl_806D7360(r2)
    addi r28, r3, lbl_80357F6C@l
    lfs f29, lbl_806D7330(r2)
    mr r29, r27
    li r30, 0x0
    BiribiriLand_Init_L_801353D0:
    lfs f1, 0x0(r28)
    addi r3, r1, 0x18
    lfs f0, 0x4(r28)
    mr r4, r3
    stfs f1, 0x1c(r29)
    lfs f1, 0x8(r28)
    stfs f0, 0x20(r29)
    lfs f0, 0xc(r28)
    stfs f1, 0x24(r29)
    lfs f1, 0x10(r28)
    stfs f0, 0x28(r29)
    lfs f0, 0x14(r28)
    stfs f1, 0x2c(r29)
    stfs f0, 0x30(r29)
    lfs f1, 0x1c(r29)
    lfs f0, 0x28(r29)
    fadds f0, f1, f0
    fmuls f0, f30, f0
    stfs f0, 0x34(r29)
    lfs f1, 0x20(r29)
    lfs f0, 0x2c(r29)
    fadds f0, f1, f0
    fmadds f0, f30, f0, f31
    stfs f0, 0x38(r29)
    lfs f1, 0x24(r29)
    lfs f0, 0x30(r29)
    fadds f0, f1, f0
    fmuls f0, f30, f0
    stfs f0, 0x3c(r29)
    lfs f1, 0x28(r29)
    lfs f0, 0x1c(r29)
    fsubs f0, f1, f0
    stfs f0, 0x18(r1)
    lfs f1, 0x2c(r29)
    lfs f0, 0x20(r29)
    fsubs f0, f1, f0
    stfs f0, 0x1c(r1)
    lfs f1, 0x30(r29)
    lfs f0, 0x24(r29)
    fsubs f0, f1, f0
    stfs f0, 0x20(r1)
    bl Vec3_Normalize
    lfs f0, 0x20(r1)
    addi r30, r30, 0x1
    cmplwi r30, 0x9
    li r0, 0x0
    fneg f0, f0
    addi r28, r28, 0x24
    stfs f0, 0x40(r29)
    lfs f0, 0x1c(r1)
    stfs f0, 0x44(r29)
    lfs f0, 0x18(r1)
    stfs f0, 0x48(r29)
    stfs f29, 0x4c(r29)
    stb r0, 0x50(r29)
    addi r29, r29, 0x38
    blt BiribiriLand_Init_L_801353D0
    BiribiriLand_Init_L_801354B4:
    stw r27, 0x30(r31)
    li r3, 0x30
    bl Alloc
    mr. r26, r3
    beq BiribiriLand_Init_L_80135528
    lfs f3, lbl_806D736C(r2)
    mr r4, r26
    lfs f2, lbl_806D7330(r2)
    addi r3, r26, 0xc
    stfs f3, 0x0(r26)
    addi r5, r26, 0x18
    lfs f1, lbl_806D7370(r2)
    stfs f2, 0x4(r26)
    lfs f0, lbl_806D7374(r2)
    stfs f1, 0x8(r26)
    stfs f3, 0xc(r26)
    stfs f2, 0x10(r26)
    stfs f0, 0x14(r26)
    bl Vec3_Subtract
    addi r3, r26, 0x18
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0x20(r26)
    fneg f0, f0
    stfs f0, 0x24(r26)
    lfs f0, 0x1c(r26)
    stfs f0, 0x28(r26)
    lfs f0, 0x18(r26)
    stfs f0, 0x2c(r26)
    BiribiriLand_Init_L_80135528:
    stw r26, 0x34(r31)
    lwz r0, g_weatherSystem(r13)
    cmplwi r0, 0x0
    bne BiribiriLand_Init_L_80135554
    li r3, 0x1b4
    bl Alloc
    mr. r26, r3
    beq BiribiriLand_Init_L_80135550
    li r4, 0x1
    bl WeatherSystem_Init
    BiribiriLand_Init_L_80135550:
    stw r26, g_weatherSystem(r13)
    BiribiriLand_Init_L_80135554:
    li r3, 0x1
    bl SetResourceLoadingFlag
    mr r3, r31
    psq_l f31, 0x78(r1), 0, 0
    lfd f31, 0x70(r1)
    psq_l f30, 0x68(r1), 0, 0
    lfd f30, 0x60(r1)
    psq_l f29, 0x58(r1), 0, 0
    lfd f29, 0x50(r1)
    lmw r26, 0x38(r1)
    lwz r0, 0x84(r1)
    mtlr r0
    addi r1, r1, 0x80
    blr
}


