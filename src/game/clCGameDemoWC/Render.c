#pragma cplusplus on
#include "game/DemoKartScene.h"
#include "game/singleton.h"

/* Render-only owner view; offsets agree with clCGameDemoWC_Tick's view. */
struct DemoWCRenderAux {
    virtual void v0();
    virtual void v1();
    virtual void Render();
};
struct DemoWCRender {
    void *vtable;
    unsigned char first, pad5[3];
    float frame;
    DemoScene *scene;
    int drawHandle;
    DemoNormal *normal;
    DemoDriver *driver;
    DemoTornado *tornado;
    Mtx matrix;
    HSD_JObj *joint;
    int event;
    DemoWCRenderAux *aux;
};

static inline float Clamp(float v, float lo, float hi)
{
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

#pragma exceptions on
extern "C" void clCGameDemoWC_Render(DemoWCRender *self)
{
    unsigned char alpha;
    float frame;
    if (self->scene->Ready() == 1) {
        clDrawMan_Buckets_Reset(SINGLETON_INSTANCE(lbl_806D10AC));
        TransparentDraw_SortAndDispatch();
        CObj_DebugVizPathFlush(self->scene);
        fn_8016B0C4();
        Object_RenderJObjTree(self->normal, 7);
        KartDriver_RenderTimed(self->driver, 0, 1);
        self->aux->Render();
        ItemObjectManager_Render();
        DrawEffect_TickAndCull();
        clDrawMan_EndFrame_NoOp(SINGLETON_INSTANCE(lbl_806D10AC));
        clDrawMan_Buckets_Dispatch(SINGLETON_INSTANCE(lbl_806D10AC));
        alpha = 0;
        frame = self->frame;
        if (frame < 30.0f)
            alpha = 255.0f - 255.0f * Clamp(frame / 30.0f, 0.0f, 1.0f);
        if (frame > 240.0f)
            alpha = 255.0f - 255.0f * Clamp((270.0f - frame) / 30.0f, 0.0f, 1.0f);
        if (alpha) fn_80181790(self->scene, 0, 1.0f, 0, 0, alpha, 0);
        self->scene->Render();
        HSD_StateInvalidate(0x7f);
    }
}
#pragma exceptions reset
#pragma cplusplus reset
