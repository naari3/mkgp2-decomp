#include "game/types/c_region.h"
C_REGION_BEGIN
/* === extracted from auto_ReverseChallenge_Ren_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls --- */
C_REGION_END
#pragma cplusplus on
struct RevScene {
    virtual void Slot8();
    virtual unsigned char IsRenderReady();
    virtual void RenderTail();
};
struct ReverseChallengeRenderView {
    char unknown0[8];
    void *environment;
    char unknownC[8];
    void *kart;
    void *objects;
    RevScene *scene;
    char unknown20[4];
    void *overlay;
    char unknown28[8];
    void *banana;
    char unknown34[0xc];
    unsigned char active;
};

extern "C" {
extern const unsigned int lbl_806DC1B0;
extern const unsigned int lbl_806DC190;
extern const unsigned int lbl_806DC1B8;
void clDrawMan_Buckets_Reset(void *);
void TransparentDraw_SortAndDispatch(void);
void CObj_DebugVizPathFlush(void *);
void fn_8016B0C4(void);
void KartItem_RenderPipelinedWithEffects(void *, int);
void Object_RenderJObjIfWithinRange(void *);
void CourseEnvironment_RenderObjects_Timed(void *);
void Subsystem36c_DispatchPass2_Timed(void *);
void ItemObjectManager_Render(void);
void BananaField_Render(void *);
void DrawEffect_TickAndCull(void);
void clDrawMan_EndFrame_NoOp(void *);
void clDrawMan_Buckets_Dispatch(void *);
void Subsystem36c_DispatchPass4_Timed(void *);
void TransitionEffect_RenderPass(void *, int);
void fn_80253448(void *, unsigned int);
void fn_802535D4(void *);
void HSD_StateInvalidate(int);
}

static inline void *RC_PRESENT(void *p)
{
    if (!p) p = 0;
    return p;
}

/* --- function index (1 fns, .text 0x800ACFC0..0x800AD134) ---
 * [  0] 0x800ACFC0 size:0x174   global ReverseChallenge_Render
 */

#pragma exceptions on
extern "C" void ReverseChallenge_Render(ReverseChallengeRenderView *self)
{
    if (self->active) {
        if (self->scene->IsRenderReady() == 1) {
            clDrawMan_Buckets_Reset(RC_PRESENT(*(void **)&lbl_806D10AC));
            TransparentDraw_SortAndDispatch();
            CObj_DebugVizPathFlush(self->scene);
            fn_8016B0C4();
            KartItem_RenderPipelinedWithEffects(self->kart, 0);
            Object_RenderJObjIfWithinRange(self->objects);
            CourseEnvironment_RenderObjects_Timed(self->environment);
            Subsystem36c_DispatchPass2_Timed(self->environment);
            ItemObjectManager_Render();
            BananaField_Render(self->banana);
            fn_80253448(self->overlay, lbl_806DC190);
            DrawEffect_TickAndCull();
            clDrawMan_EndFrame_NoOp(RC_PRESENT(*(void **)&lbl_806D10AC));
            clDrawMan_Buckets_Dispatch(RC_PRESENT(*(void **)&lbl_806D10AC));
            Subsystem36c_DispatchPass4_Timed(self->environment);
            TransitionEffect_RenderPass(RC_PRESENT(*(void **)&lbl_806D109C), 2);
            TransitionEffect_RenderPass(RC_PRESENT(*(void **)&lbl_806D109C), 4);
            fn_80253448(self->overlay, lbl_806DC1B0 | lbl_806DC190);
            self->scene->RenderTail();
        }
        fn_80253448(self->overlay, lbl_806DC1B8);
        fn_802535D4(self->overlay);
        TransitionEffect_RenderPass(RC_PRESENT(*(void **)&lbl_806D109C), 1);
        HSD_StateInvalidate(0x7f);
    }
}
#pragma exceptions reset
#pragma cplusplus reset
