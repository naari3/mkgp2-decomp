extern char g_metricsTable[0xC4];
extern char lbl_805985A8[0xC];
extern const float lbl_806D2478;

extern void *__construct_array(void *table, void *initCb, void *dtorCb,
                         int alignment, int count);
extern void __register_global_object(int key, void *cb, void *target);
extern void __destroy_arr(void *table, void *dtorCb, int alignment, int count);
extern void MemoryManager_TimedFree(void *p);

void *MetricsTable_DefaultDtor(void *self, short bDelete);
void MetricsTable_Shutdown(void);
void MetricsTable_DefaultSlotInit(float *slot);

#pragma exceptions on
void MetricsTable_Init(void) {
    __construct_array(g_metricsTable, (void *)&MetricsTable_DefaultSlotInit,
                (void *)&MetricsTable_DefaultDtor, 4, 0x30);
    __register_global_object(0, (void *)&MetricsTable_Shutdown, lbl_805985A8);
}

void MetricsTable_Shutdown(void) {
    __destroy_arr(g_metricsTable, (void *)&MetricsTable_DefaultDtor, 4, 0x30);
}

void *MetricsTable_DefaultDtor(void *self, short bDelete) {
    if ((self != 0) && (bDelete > 0)) {
        MemoryManager_TimedFree(self);
    }
    return self;
}
#pragma exceptions reset

void MetricsTable_DefaultSlotInit(float *slot) {
    *slot = lbl_806D2478;
}

__declspec(section ".ctors") static void (*const s_metricsTable_ctor)(void) = MetricsTable_Init;
