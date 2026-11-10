#include "game/types/c_region.h"
C_REGION_BEGIN
#include "game/types/size_t.h"
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

extern float BiribiriLand_Render_data_806CF5F0;
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
const float BiribiriLand_UpdateObstacles_rodata_80357B00[255] = {
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
const BiribiriObstacleDesc BiribiriLand_rodata_80357F6C[9] = {
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

C_REGION_END
#pragma cplusplus on
struct BiribiriScene {
    virtual ~BiribiriScene();
    virtual unsigned char IsReady();
    virtual void Draw();
};
#pragma cplusplus reset
C_REGION_BEGIN

static inline void BiribiriDrawObstacles(BiribiriObstacles *obs)
{
    unsigned int i;

    for (i = 0; i < 9; i++) {
        int model = BiribiriLand_rodata_80357F6C[i].model;
        float yaw = BiribiriLand_rodata_80357F6C[i].yaw;
        if (model != 0) {
            yaw += lbl_806D7320;
        }
        Object_SetJObjPositionVec(obs->model[model], &obs->obstacles[i].a);
        Object_SetJObjRotationY(obs->model[model], yaw);
        Object_RenderJObjTree(obs->model[model], 7);
        if (BiribiriLand_rodata_80357F6C[i].glow) {
            Object_SetJObjPositionX(obs->model[5], obs->obstacles[i].a.x);
            Object_SetJObjPositionY(obs->model[5], obs->obstacles[i].a.y + BiribiriLand_Render_data_806CF5F0);
            Object_SetJObjField40(obs->model[5], obs->obstacles[i].a.z);
            Object_SetJObjRotationY(obs->model[5], yaw);
            Object_RenderJObjTree(obs->model[5], 7);
        }
        Object_SetJObjPositionVec(obs->model[model], &obs->obstacles[i].b);
        Object_SetJObjRotationY(obs->model[model], yaw);
        Object_RenderJObjTree(obs->model[model], 7);
        if (BiribiriLand_rodata_80357F6C[i].glow) {
            Object_SetJObjPositionX(obs->model[5], obs->obstacles[i].b.x);
            Object_SetJObjPositionY(obs->model[5], obs->obstacles[i].b.y + BiribiriLand_Render_data_806CF5F0);
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
extern void BiribiriLand_UpdateObstacles(BiribiriObstacles *obs);
C_REGION_END
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
extern Vec BiribiriLand_Update_bss_80677C88;
extern Vec BiribiriLand_Update_bss_80677C94;
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
    CObj_LoadProjMatrix(self->scene, &BiribiriLand_Update_bss_80677C88);
    CObj_ApplyScissor(self->scene, &BiribiriLand_Update_bss_80677C94);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(BiribiriLand_Update_bss_80677C88, BiribiriLand_Update_bss_80677C94);
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
C_REGION_BEGIN


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
        if (BiribiriLand_rodata_80357F6C[i].glow) {
            lift = 5.0f * LUT_Sin12Bit(lbl_806D735C * obs->obstacles[i].phase) + 5.0f;
        }
        obs->obstacles[i].a.x = BiribiriLand_rodata_80357F6C[i].a.x;
        obs->obstacles[i].a.y = BiribiriLand_rodata_80357F6C[i].a.y;
        obs->obstacles[i].a.z = BiribiriLand_rodata_80357F6C[i].a.z;
        obs->obstacles[i].b.x = BiribiriLand_rodata_80357F6C[i].b.x;
        obs->obstacles[i].b.y = BiribiriLand_rodata_80357F6C[i].b.y;
        obs->obstacles[i].b.z = BiribiriLand_rodata_80357F6C[i].b.z;
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
extern void CourseEnvironment_Dtor(void *, int);
extern void GetRaceContextPtr();
extern void ItemObjectManager_Reset();
extern void LakituStart_Dtor(void *, int);
extern void MemoryManager_TimedFree(void *);
extern void Object_DtorWithGXSync(void *, int);
extern void RankingTable_Init();
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
extern unsigned int lbl_806D10D0;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int BiribiriLand_vtable_8048E46C[];

/* --- function index (1 fns, .text 0x80134D68..0x80134FF0) ---
 * [  0] 0x80134D68 size:0x288   global BiribiriLand_Destroy
 */

/* --- forward decls --- */
void *BiribiriLand_Destroy(BiribiriState *, short);

C_REGION_END
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
        self->vtable = BiribiriLand_vtable_8048E46C;
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
C_REGION_BEGIN


/* === BiribiriLand_Init: C++ ctor (same template as ReverseChallenge_Init / RivalRun_Init) === */
C_REGION_END
#pragma cplusplus on
void *operator new(size_t size);
void operator delete(void *p);

extern "C" {
void GameMode_BaseInit();
void DrawManager_GetOrCreate(void);
void DMAChannelManager_Init(void);
void TransitionEffect_GetOrCreate(void);
void SoundChannels_ClearAll(void);
void ItemObjectManager_Init(void);
void CourseObjectManager_Init(void);
void GetCourseDataPtr(void);
int HSD_LObjLoadDesc(void);
void ProcessSystemTick(int arg);
void SoundDriver_GetOrCreate(int arg);
int GetDisplayBufferIndex(void);
void GetStartPosition(int idx, float *x, float *y, float *z);
float GetCourseStartYaw(void);
void CarObject_SetPosition(void *car, Vec *pos);
int *GetKartModelNameEntry(int chara, int arg);
void Vec3_Normalize(Vec *src, Vec *dst);
void Scene3D_GetCameraPos(void *scene, float *a, float *b);
void Scene3D_SetupProjection(void *scene, float a, float b);
void HUD_RegisterOverlay(void *hud, int id, int arg);
void SetCourseScene3D(void *scene);
void PreloadEffectResources(int id);
void Object_SetJObjScaleXYZ(void *obj, float x, float y, float z);
void clNormal3D_SetScale(void *obj, int arg, float a, float b, float c, float d);
extern int g_characterId;
extern int lbl_806D12BC;
extern const char *BiribiriLand_Init_data_8048E430[7];
extern char lbl_8048E144[];
}

#pragma exceptions on
struct BLInputManager { char data[0x37C]; BLInputManager(); };
struct BLCamera { char data[0x2C]; BLCamera(float a, float b, int w, int h, int target); };
struct BLCarObject {
    char data[0x118];
    BLCarObject(int disp, int chara, int cc, int a, int b, int c, int d, int e, float x, float z, float yaw);
};
struct BLPlayerCar : BLCarObject {
    BLPlayerCar(Vec *pos, int chara)
        : BLCarObject(GetDisplayBufferIndex(), chara, 0, 0, 1, 3, 0, 0, pos->x, pos->z, GetCourseStartYaw()) {}
};
struct BLRenderObj { char pad0[0x238]; int x238; };
struct BLLakituStart { char data[0x58]; BLLakituStart(const void *data, int arg, float x, float y, float z); };
struct BLScene3D { char data[0x3084]; BLScene3D(int name); };
struct BLGoalCamera { char data[8]; BLGoalCamera(); };
struct BLHUD { char data[0x80]; BLHUD(int arg); };
struct BLWeatherSystem { char data[0x1B4]; BLWeatherSystem(int arg); };
struct BLNormal3D { char data[0x5C]; BLNormal3D(const char *name, int arg); };

struct BLObstacles {
    BLNormal3D *model[7];
    BiribiriObstacle obstacles[9];
    BLObstacles() {
        int i;
        unsigned int j;
        for (i = 0; i < 7; i++) {
            model[i] = new BLNormal3D(BiribiriLand_Init_data_8048E430[i], 0);
            if (i <= 5) {
                Object_SetJObjScaleXYZ(model[i], 12.5f, 12.5f, 12.5f);
            }
        }
        clNormal3D_SetScale(model[6], 0, 0.0f, 1.0f, 0.0f, 0.0f);
        for (j = 0; j < 9; j++) {
            Vec d;
            obstacles[j].a.x = BiribiriLand_rodata_80357F6C[j].a.x;
            obstacles[j].a.y = BiribiriLand_rodata_80357F6C[j].a.y;
            obstacles[j].a.z = BiribiriLand_rodata_80357F6C[j].a.z;
            obstacles[j].b.x = BiribiriLand_rodata_80357F6C[j].b.x;
            obstacles[j].b.y = BiribiriLand_rodata_80357F6C[j].b.y;
            obstacles[j].b.z = BiribiriLand_rodata_80357F6C[j].b.z;
            obstacles[j].center.x = 0.5f * (obstacles[j].a.x + obstacles[j].b.x);
            obstacles[j].center.y = 0.5f * (obstacles[j].a.y + obstacles[j].b.y) + 5.8f;
            obstacles[j].center.z = 0.5f * (obstacles[j].a.z + obstacles[j].b.z);
            d.x = obstacles[j].b.x - obstacles[j].a.x;
            d.y = obstacles[j].b.y - obstacles[j].a.y;
            d.z = obstacles[j].b.z - obstacles[j].a.z;
            Vec3_Normalize(&d, &d);
            obstacles[j].direction.x = -d.z;
            obstacles[j].direction.y = d.y;
            obstacles[j].direction.z = d.x;
            obstacles[j].phase = 0.0f;
            obstacles[j].hit = 0;
        }
    }
};

struct BLGoalLine {
    Vec a;
    Vec b;
    Vec dir;
    Vec normal;
    BLGoalLine() {
        a.x = 6249.4f;
        a.y = 0.0f;
        a.z = -8690.3f;
        b.x = 6249.4f;
        b.y = 0.0f;
        b.z = -8983.7f;
        Vec3_Subtract(&b, &a, &dir);
        Vec3_Normalize(&dir, &dir);
        normal.x = -dir.z;
        normal.y = dir.y;
        normal.z = dir.x;
    }
};

#include "game/types/GameModeBase.h"

#include "game/types/ModeBase.h"

struct BiribiriLand : ModeBase {
    virtual void _key3();
    BLCarObject *car;
    BLLakituStart *lakitu;
    BLInputManager *input;
    BLScene3D *scene;
    BLGoalCamera *goalCam;
    BLCamera *camera;
    int renderTarget;
    BLHUD *hud;
    unsigned char x28, x29, x2A, x2B;
    int x2C;
    BLObstacles *obstacles;
    BLGoalLine *goal;
    Vec unused;
    BiribiriLand();
};

#pragma use_lmw_stmw on
BiribiriLand::BiribiriLand() {
    Vec pos;
    float camA, camB;

    car = 0;
    lakitu = 0;
    input = 0;
    scene = 0;
    goalCam = 0;
    camera = 0;
    renderTarget = 0;
    hud = 0;
    x28 = 0;
    x29 = 0;
    x2A = 0;
    x2B = 0;
    x2C = 0;
    obstacles = 0;
    goal = 0;
    unused.x = 0.0f;
    unused.y = 0.0f;
    unused.z = 0.0f;
    DrawManager_GetOrCreate();
    SetResourceLoadingFlag(0);
    DMAChannelManager_Init();
    TransitionEffect_GetOrCreate();
    SoundChannels_ClearAll();
    ItemObjectManager_Init();
    CourseObjectManager_Init();
    input = new BLInputManager;
    GetCourseDataPtr();
    renderTarget = HSD_LObjLoadDesc();
    camera = new BLCamera(1000.0f, 0.1f, 0x100, 0x100, renderTarget);
    SetActiveCamera(0, camera);
    *(BLCamera **)&g_raceCamera = camera;
    ProcessSystemTick(0);
    GetRaceContextPtr();
    RankingTable_Init();
    lbl_806D12BC = 0;
    SoundDriver_GetOrCreate(0);
    GetStartPosition(0, &pos.x, &pos.y, &pos.z);
    car = new BLPlayerCar(&pos, g_characterId);
    CarObject_SetPosition(car, &pos);
    {
        BLRenderObj *r = (BLRenderObj *)CarObject_GetRenderObj(car);
        r->x238 = 1;
    }
    SetPlayerCarObject(car);
    lakitu = new BLLakituStart(lbl_803580E0, 0, 0.0f, 0.0f, 0.0f);
    scene = new BLScene3D(*GetKartModelNameEntry(g_characterId, -1));
    goalCam = new BLGoalCamera;
    ProcessSystemTick(0);
    Scene3D_GetCameraPos(scene, &camA, &camB);
    camA += 10.0f;
    Scene3D_SetupProjection(scene, camA, camB);
    hud = new BLHUD(0);
    HUD_RegisterOverlay(hud, 6, 0);
    HUD_RegisterOverlay(hud, 0x11, 0);
    HUD_RegisterOverlay(hud, 0x12, 0);
    HUD_RegisterOverlay(hud, 0xE, 0);
    g_lakituStartAnimDone = 0;
    SetCourseScene3D(scene);
    g_raceEnded = 0;
    g_raceTimeRemaining = MiniGame_GetTimerValue();
    PreloadEffectResources(1);
    PreloadEffectResources(9);
    PreloadEffectResources(0xA);
    obstacles = new BLObstacles;
    goal = new BLGoalLine;
    if ((void *)g_weatherSystem == 0) {
        *(void **)&g_weatherSystem = new BLWeatherSystem(1);
    }
    SetResourceLoadingFlag(1);
}
#pragma use_lmw_stmw reset
#pragma exceptions reset
#pragma cplusplus reset
