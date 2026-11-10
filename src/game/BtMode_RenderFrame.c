/* BtMode_RenderFrame (0x800A28D4): battle-mode counterpart of
 * RaceScene_RenderFrame. Draws the scene while battle mode is active: the
 * player kart (and the rival kart once the race starts), course objects,
 * effects and the HUD layers, then flushes the HUD and GX state. */
#pragma cplusplus on

#include "game/types/SceneCamera.h"

struct ISESlotOwner {
    unsigned char pad00[0x18];
    unsigned char *iseState; /* 0x18 */
};

struct BtScene {
    void *vtable;
    void *object;          /* 0x04 */
    void *jyugemuFlag;     /* 0x08 */
    void *jyugemuReverse;  /* 0x0C */
    void *lapBanner;       /* 0x10 */
    void *environment;     /* 0x14 */
    void *pad18;
    SceneCamera *camera;   /* 0x1C */
    void *pad20[3];
    void *hud;             /* 0x2C */
};

extern "C" {
extern unsigned char lbl_806D13A1;
extern int g_cupId;
extern void *g_carObjects[];
extern void *g_taGhostCar;
extern void *g_taSound;
extern void *lbl_806D10AC;
extern void *lbl_806D10D0;
extern void *lbl_806D109C;
extern unsigned int lbl_806DC17C;
extern unsigned int lbl_806DC180;
extern unsigned int lbl_806DC184;
extern unsigned int lbl_806DC188;
extern unsigned int lbl_806DC18C;
extern unsigned int lbl_806DC190;
extern unsigned int lbl_806DC194;
extern unsigned int lbl_806DC198;
extern unsigned int lbl_806DC19C;
extern unsigned int lbl_806DC1A0;
extern unsigned int lbl_806DC1A4;
extern unsigned int lbl_806DC1AC;
extern unsigned int lbl_806DC1B0;
extern unsigned int lbl_806DC1B4;
extern unsigned int lbl_806DC1B8;

void clDrawMan_Buckets_Reset(void *mgr);
void TransparentDraw_SortAndDispatch(void);
void CObj_DebugVizPathFlush(SceneCamera *cam);
void fn_8016B0C4(void);
void IsTimerModeEnabled(void);
void KartItem_RenderPipelinedWithEffects(void *car, int flag);
unsigned char IsRaceStarted(void);
void *CarObject_GetRenderObj(void *car);
ISESlotOwner *KartItem_GetCurrentISESlot(void *obj);
void Stub_NoOp_80030aec(SceneCamera *cam);
void Object_RenderJObjIfWithinRange(void *obj);
void Jyugemu_Flag_Render(void *p);
void Jyugemu_ReverseFlag_Render(void *p);
void LapBannerScene_RenderIfActive(void *p);
void CourseEnvironment_RenderObjects_Timed(void *p);
void Subsystem36c_DispatchPass2_Timed(void *p);
void Subsystem36c_DispatchPass4_Timed(void *p);
void NoopRenderHook_Pending_80064d28(void);
void ItemObjectManager_Render(void);
void DrawEffect_TickAndCull(void);
void fn_80139810(void);
void clItemBoxManager_Draw(void *mgr);
void clDrawMan_EndFrame_NoOp(void *mgr);
void clDrawMan_Buckets_Dispatch(void *mgr);
void TransitionEffect_RenderPass(void *fx, int pass);
void fn_80253448(void *hud, unsigned int layers);
void fn_8023E2F8(void *p);
void *GetKartSlotKartVariant(int slot);
void KartItem_TriggerStateAction(void *kart);
void KartItem_IsAtStartSlot(void *kart);
void fn_802535D4(void *hud);
void HSD_StateInvalidate(int mask);
}

static inline void *DrawMan(void)
{
    if (lbl_806D10AC == 0) {
        return 0;
    }
    return lbl_806D10AC;
}

static inline void *ItemBoxMgr(void)
{
    if (lbl_806D10D0 == 0) {
        return 0;
    }
    return lbl_806D10D0;
}

static inline void *Transition(void)
{
    if (lbl_806D109C == 0) {
        return 0;
    }
    return lbl_806D109C;
}

extern "C" void BtMode_RenderFrame(BtScene *self)
{
    int i;

    if (lbl_806D13A1 == 1) {
        if (self->camera->Begin() == 1) {
            clDrawMan_Buckets_Reset(DrawMan());
            TransparentDraw_SortAndDispatch();
            CObj_DebugVizPathFlush(self->camera);
            fn_8016B0C4();
            if (g_cupId == 0) {
                IsTimerModeEnabled();
            }
            KartItem_RenderPipelinedWithEffects(g_carObjects[0], 0);
            if (g_taGhostCar != 0) {
                if (!IsRaceStarted()) {
                    unsigned char *ise = KartItem_GetCurrentISESlot(CarObject_GetRenderObj(g_taGhostCar))->iseState;
                    if (ise != 0) {
                        ise[0x28] = 0;
                    }
                }
                KartItem_RenderPipelinedWithEffects(g_taGhostCar, 0);
            }
            Stub_NoOp_80030aec(self->camera);
            Object_RenderJObjIfWithinRange(self->object);
            Jyugemu_Flag_Render(self->jyugemuFlag);
            Jyugemu_ReverseFlag_Render(self->jyugemuReverse);
            LapBannerScene_RenderIfActive(self->lapBanner);
            CourseEnvironment_RenderObjects_Timed(self->environment);
            Subsystem36c_DispatchPass2_Timed(self->environment);
            NoopRenderHook_Pending_80064d28();
            ItemObjectManager_Render();
            DrawEffect_TickAndCull();
            fn_80139810();
            clItemBoxManager_Draw(ItemBoxMgr());
            clDrawMan_EndFrame_NoOp(DrawMan());
            clDrawMan_Buckets_Dispatch(DrawMan());
            Subsystem36c_DispatchPass4_Timed(self->environment);
            TransitionEffect_RenderPass(Transition(), 5);
            fn_80253448(self->hud, lbl_806DC190 | lbl_806DC188 | lbl_806DC18C | lbl_806DC184 | lbl_806DC198 | lbl_806DC19C);
            if (g_taSound != 0) {
                fn_8023E2F8(g_taSound);
            }
            fn_80253448(self->hud, lbl_806DC180 | lbl_806DC17C | lbl_806DC1A0 | lbl_806DC1A4 | lbl_806DC1AC |
                                       lbl_806DC194 | lbl_806DC1B0 | lbl_806DC1B4 | lbl_806DC1B8);
            for (i = 0; i < 8; i++) {
                void *kart = GetKartSlotKartVariant(i);
                if (kart != 0) {
                    KartItem_TriggerStateAction(kart);
                    KartItem_IsAtStartSlot(kart);
                }
            }
            TransitionEffect_RenderPass(Transition(), 2);
            TransitionEffect_RenderPass(Transition(), 4);
            TransitionEffect_RenderPass(Transition(), 6);
            self->camera->End();
        }
        fn_802535D4(self->hud);
        HSD_StateInvalidate(0x7F);
    }
}
