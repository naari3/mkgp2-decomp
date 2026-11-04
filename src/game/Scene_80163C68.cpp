#include "game/Scene_80163C68Private.h"

extern "C" void fn_80163C68(LoaderDraw *s) {
    if (s->done != 1 && s->ready) {
        if (s->scene->Ready() == 1) {
            clDrawMan_Buckets_Reset(GetDrawMan());
            TransparentDraw_SortAndDispatch();
            CObj_DebugVizPathFlush(s->scene);
            fn_8016B0C4();
            Stub_NoOp_80030aec(s->scene);
            Object_RenderJObjIfWithinRange(s->object);
            Jyugemu_Flag_Render(s->flag);
            Jyugemu_ReverseFlag_Render(s->reverseFlag);
            LapBannerScene_RenderIfActive(s->banner);
            CourseEnvironment_RenderObjects_Timed(s->environment);
            Subsystem36c_DispatchPass2_Timed(s->environment);
            fn_801EB91C(s->ai, 1);
            fn_80208E2C(s->system);
            NoopRenderHook_Pending_80064d28();
            ItemObjectManager_Render();
            DrawEffect_TickAndCull();
            for (int i = 0; i < 8; i++) {
                void *kart = GetKartSlotKartVariant(i);
                if (kart) {
                    KartItem_TriggerStateAction(kart);
                    KartItem_IsAtStartSlot(kart);
                }
            }
            KartItem_RenderPipelinedWithEffects(g_carObjects[0], 0);
            fn_80139810();
            clItemBoxManager_Draw(BoxManager());
            clDrawMan_EndFrame_NoOp(GetDrawMan());
            clDrawMan_Buckets_Dispatch(GetDrawMan());
            Subsystem36c_DispatchPass4_Timed(s->environment);
            TransitionEffect_RenderPass(Transition(), 5);
            TransitionEffect_RenderPass(Transition(), 3);
            if (g_currentLap < g_totalLaps + 1) ItemSelect_DrawUIHelperIfActive(g_itemSelects[0]);
            TransitionEffect_RenderPass(Transition(), 2);
            TransitionEffect_RenderPass(Transition(), 4);
            TransitionEffect_RenderPass(Transition(), 6);
            s->scene->Render();
            HSD_LObjDeleteCurrentAll(0);
        }
        TransitionEffect_RenderPass(Transition(), 1);
        if (s->fade > lbl_806D88F0) {
            fn_80181790(s->scene, 0, lbl_806D88F8, 0, 0, (int)(lbl_806D88F4 * s->fade), 0);
        }
        HSD_StateInvalidate(0x7f);
    }
}
