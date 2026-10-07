// Local ABI views: only fields and virtual slots observed in target assembly.
struct CoinScene {
    virtual void Slot8();
    virtual unsigned char IsRenderReady();
    virtual void RenderTail();
};

struct CoinChallengeRenderView {
    char unknown0[8];
    void* kart;
    void* objects;
    void* environment;
    CoinScene* scene;
    char unknown18[0x10];
    void* overlay;
    char unknown2c[4];
    unsigned char active;
};

extern "C" {
extern void* lbl_806D10AC;
extern void* lbl_806D10D0;
extern void* lbl_806D109C;
extern const float lbl_806DAE20;
extern const unsigned int lbl_806DC1B0;
extern const unsigned int lbl_806DC190;
extern const unsigned int lbl_806DC1B8;
void clDrawMan_Buckets_Reset(void*);
void clDrawMan_SetMaxClipZ(void*, float);
void TransparentDraw_SortAndDispatch();
void CObj_DebugVizPathFlush(void*);
void fn_8016B0C4();
void KartItem_RenderPipelinedWithEffects(void*, int);
void Object_RenderJObjIfWithinRange(void*);
void CourseEnvironment_RenderObjects_Timed(void*);
void fn_80139810();
void clItemBoxManager_Draw(void*);
void Subsystem36c_DispatchPass2_Timed(void*);
void ItemObjectManager_Render();
void DrawEffect_TickAndCull();
void clDrawMan_EndFrame_NoOp(void*);
void clDrawMan_Buckets_Dispatch(void*);
void Subsystem36c_DispatchPass4_Timed(void*);
void TransitionEffect_RenderPass(void*, int);
void fn_80253448(void*, unsigned int);
void fn_8011F994(int);
void fn_802535D4(void*);
void fn_802C14B8(int);
}

static inline void* PresentOrNull(void* p) {
    if (!p) p = 0;
    return p;
}

#pragma exceptions on
extern "C" void MiniGame_CoinChallenge_Destroy(CoinChallengeRenderView* self) {
    if (self->active) {
        if (self->scene->IsRenderReady() == 1) {
            clDrawMan_Buckets_Reset(PresentOrNull(lbl_806D10AC));
            clDrawMan_SetMaxClipZ(PresentOrNull(lbl_806D10AC), lbl_806DAE20);
            TransparentDraw_SortAndDispatch();
            CObj_DebugVizPathFlush(self->scene);
            fn_8016B0C4();
            KartItem_RenderPipelinedWithEffects(self->kart, 0);
            Object_RenderJObjIfWithinRange(self->objects);
            CourseEnvironment_RenderObjects_Timed(self->environment);
            fn_80139810();
            clItemBoxManager_Draw(PresentOrNull(lbl_806D10D0));
            Subsystem36c_DispatchPass2_Timed(self->environment);
            ItemObjectManager_Render();
            DrawEffect_TickAndCull();
            clDrawMan_EndFrame_NoOp(PresentOrNull(lbl_806D10AC));
            clDrawMan_Buckets_Dispatch(PresentOrNull(lbl_806D10AC));
            Subsystem36c_DispatchPass4_Timed(self->environment);
            TransitionEffect_RenderPass(PresentOrNull(lbl_806D109C), 2);
            TransitionEffect_RenderPass(PresentOrNull(lbl_806D109C), 4);
            TransitionEffect_RenderPass(PresentOrNull(lbl_806D109C), 6);
            fn_80253448(self->overlay, lbl_806DC1B0 | lbl_806DC190);
            fn_8011F994(1);
            self->scene->RenderTail();
        }
        fn_80253448(self->overlay, lbl_806DC1B8);
        fn_802535D4(self->overlay);
        TransitionEffect_RenderPass(PresentOrNull(lbl_806D109C), 1);
        fn_802C14B8(0x7f);
    }
}
