extern void KartItem_DispatchEffectRenderByState(void *item);
extern void KartDriver_RenderTimed(void *driver, int pass, int arg);
extern void KartItem_FlushPendingRender_v2(void *item);
extern void KartItem_FlushRenderIfReady(void *item);
extern void KartItem_FlushPendingRender(void *item);
extern void TornadoEffect_SubmitRender(void *item);

void fn_801E6E4C(char *self, int arg) {
    if (*(void **)(self + 0x78) != 0) {
        KartItem_DispatchEffectRenderByState(*(void **)(self + 0x14));
        KartDriver_RenderTimed(*(void **)(self + 0x10), 1, arg);
        KartItem_FlushPendingRender_v2(*(void **)(self + 0x14));
        KartItem_FlushRenderIfReady(*(void **)(self + 0x14));
        KartDriver_RenderTimed(*(void **)(self + 0x10), 2, arg);
        KartItem_FlushPendingRender(*(void **)(self + 0x14));
        TornadoEffect_SubmitRender(*(void **)(self + 0x14));
    }
}
