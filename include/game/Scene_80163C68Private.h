#ifndef GAME_SCENE_80163C68_PRIVATE_H
#define GAME_SCENE_80163C68_PRIVATE_H

// This caller passes the full integer alpha, before the callee narrows it.
#define fn_80181790 fn_80181790_ByteAlphaDeclaration
#include "game/DemoKartScene.h"
#undef fn_80181790

struct LoaderDraw {
    char pad0[0x14];
    void *environment;
    char pad18[0x10];
    void *object;
    void *flag;
    void *reverseFlag;
    void *banner;
    void *system;
    void *ai;
    unsigned char done;
    unsigned char ready;
    char pad42[6];
    float fade;
    DemoSceneBase *scene;
};

extern "C" {
extern void *g_carObjects[4];
extern void *g_itemSelects[4];
extern void *lbl_806D10D0;
extern void *lbl_806D109C;
extern int g_totalLaps;
extern int g_currentLap;
extern const float lbl_806D88F0, lbl_806D88F4, lbl_806D88F8;
void Stub_NoOp_80030aec(DemoSceneBase *);
void Object_RenderJObjIfWithinRange(void *);
void Jyugemu_Flag_Render(void *);
void Jyugemu_ReverseFlag_Render(void *);
void LapBannerScene_RenderIfActive(void *);
void CourseEnvironment_RenderObjects_Timed(void *);
void Subsystem36c_DispatchPass2_Timed(void *);
void Subsystem36c_DispatchPass4_Timed(void *);
void fn_801EB91C(void *, int);
void fn_80208E2C(void *);
void NoopRenderHook_Pending_80064d28();
void *GetKartSlotKartVariant(int);
void KartItem_TriggerStateAction(void *);
void KartItem_IsAtStartSlot(void *);
void KartItem_RenderPipelinedWithEffects(void *, int);
void fn_80139810();
void clItemBoxManager_Draw(void *);
void TransitionEffect_RenderPass(void *, int);
void ItemSelect_DrawUIHelperIfActive(void *);
void HSD_LObjDeleteCurrentAll(int);
void fn_80181790(DemoSceneBase *, int, float, int, int, int, int);
}

static inline void *BoxManager() { return lbl_806D10D0 == 0 ? 0 : lbl_806D10D0; }
static inline void *Transition() { return lbl_806D109C == 0 ? 0 : lbl_806D109C; }

#endif
