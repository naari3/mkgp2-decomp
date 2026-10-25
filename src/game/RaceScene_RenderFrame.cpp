/* RaceScene_RenderFrame (0x8009DD64): VS-mode counterpart of
 * RaceScene_RenderPass. Only draws once the scene is running, and draws
 * the other karts before the local one. */

struct SceneCamera {
    virtual void v0();
    virtual unsigned char Begin();
    virtual void End();
};

struct VsScene {
    void *vtable;
    void *object;          /* 0x04 */
    void *jyugemuFlag;     /* 0x08 */
    void *jyugemuReverse;  /* 0x0C */
    void *lapBanner;       /* 0x10 */
    void *environment;     /* 0x14 */
    SceneCamera *camera;   /* 0x18 */
    void *pad1C[2];
    void *hud;             /* 0x24 */
    void *pad28;
    void *hud2C;           /* 0x2C */
    void *hud30;           /* 0x30 */
    void *overlay;         /* 0x34 */
};

extern "C" {
extern int g_currentSceneState;
extern int lbl_806D1314;
extern unsigned char lbl_806D12E8;
extern int lbl_806CF140;
extern int g_cupId;
extern int g_totalLaps;
extern int g_currentLap;
extern void *g_carObjects[];
extern void *g_itemSelects[];
extern void *lbl_806D10AC;
extern void *lbl_806D10D0;
extern void *lbl_806D109C;
extern unsigned int lbl_806DC178;
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
extern unsigned int lbl_806DC1A8;
extern unsigned int lbl_806DC1AC;
extern unsigned int lbl_806DC1B0;
extern unsigned int lbl_806DC1B4;
extern unsigned int lbl_806DC1B8;

void clDrawMan_Buckets_Reset(void *mgr);
void TransparentDraw_SortAndDispatch(void);
void CObj_DebugVizPathFlush(SceneCamera *cam);
void fn_8016B0C4(void);
void IsTimerModeEnabled(void);
void Stub_NoOp_80030aec(SceneCamera *cam);
void Object_RenderJObjIfWithinRange(void *obj);
void Jyugemu_Flag_Render(void *p);
void Jyugemu_ReverseFlag_Render(void *p);
void LapBannerScene_RenderIfActive(void *p);
void CourseEnvironment_RenderObjects_Timed(void *p);
void Subsystem36c_DispatchPass2_Timed(void *p);
void Subsystem36c_DispatchPass4_Timed(void *p);
void fn_801EB91C(void *p, int flag);
void fn_80208E2C(void *p);
void NoopRenderHook_Pending_80064d28(void);
void ItemObjectManager_Render(void);
void DrawEffect_TickAndCull(void);
void *GetKartSlotKartVariant(int slot);
void KartItem_TriggerStateAction(void *kart);
void KartItem_IsAtStartSlot(void *kart);
void KartItem_RenderPipelinedWithEffects(void *car, int flag);
void fn_80139810(void);
void clItemBoxManager_Draw(void *mgr);
void clDrawMan_EndFrame_NoOp(void *mgr);
void clDrawMan_Buckets_Dispatch(void *mgr);
void TransitionEffect_RenderPass(void *fx, int pass);
unsigned char IsRaceStarted(void);
void fn_80253448(void *hud, unsigned int layers);
void ItemSelect_DrawUIHelperIfActive(void *sel);
void fn_8020AFD4(void *p);
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

extern "C" void RaceScene_RenderFrame(VsScene *self)
{
    int i;
    int j;

    if (g_currentSceneState >= 0x2C && lbl_806D1314 == 0 && lbl_806D12E8 == 1) {
        if (self->camera->Begin() == 1) {
            clDrawMan_Buckets_Reset(DrawMan());
            TransparentDraw_SortAndDispatch();
            CObj_DebugVizPathFlush(self->camera);
            fn_8016B0C4();
            if (g_cupId == 0) {
                IsTimerModeEnabled();
            }
            Stub_NoOp_80030aec(self->camera);
            if (self->object != 0) {
                Object_RenderJObjIfWithinRange(self->object);
            }
            Jyugemu_Flag_Render(self->jyugemuFlag);
            Jyugemu_ReverseFlag_Render(self->jyugemuReverse);
            LapBannerScene_RenderIfActive(self->lapBanner);
            CourseEnvironment_RenderObjects_Timed(self->environment);
            Subsystem36c_DispatchPass2_Timed(self->environment);
            ItemObjectManager_Render();
            fn_801EB91C(self->hud2C, 1);
            fn_80208E2C(self->hud30);
            NoopRenderHook_Pending_80064d28();
            DrawEffect_TickAndCull();
            for (i = 0; i < 4; i++) {
                if (i != lbl_806CF140 && g_carObjects[i] != 0) {
                    KartItem_RenderPipelinedWithEffects(g_carObjects[i], 0);
                }
            }
            for (j = 0; j < 8; j++) {
                void *kart = GetKartSlotKartVariant(j);
                if (kart != 0) {
                    KartItem_TriggerStateAction(kart);
                    KartItem_IsAtStartSlot(kart);
                }
            }
            KartItem_RenderPipelinedWithEffects(g_carObjects[lbl_806CF140], 0);
            fn_80139810();
            clItemBoxManager_Draw(ItemBoxMgr());
            clDrawMan_EndFrame_NoOp(DrawMan());
            clDrawMan_Buckets_Dispatch(DrawMan());
            Subsystem36c_DispatchPass4_Timed(self->environment);
            TransitionEffect_RenderPass(Transition(), 5);
            TransitionEffect_RenderPass(Transition(), 3);
            if (IsRaceStarted() == 1) {
                fn_80253448(self->hud, lbl_806DC178);
            }
            fn_80253448(self->hud, lbl_806DC190 | lbl_806DC188 | lbl_806DC18C | lbl_806DC184 | lbl_806DC198 | lbl_806DC19C);
            if (g_currentLap < g_totalLaps + 1) {
                ItemSelect_DrawUIHelperIfActive(g_itemSelects[lbl_806CF140]);
            }
            fn_80253448(self->hud, lbl_806DC180 | lbl_806DC17C | lbl_806DC1A0 | lbl_806DC1A4 | lbl_806DC1AC |
                                       lbl_806DC194 | lbl_806DC1B0 | lbl_806DC1B4);
            fn_80253448(self->hud, lbl_806DC1A8);
            TransitionEffect_RenderPass(Transition(), 2);
            TransitionEffect_RenderPass(Transition(), 4);
            TransitionEffect_RenderPass(Transition(), 6);
            self->camera->End();
        }
        fn_80253448(self->hud, lbl_806DC1B8);
        TransitionEffect_RenderPass(Transition(), 1);
        if (self->overlay != 0) {
            fn_8020AFD4(self->overlay);
        }
        HSD_StateInvalidate(0x7F);
    }
}
