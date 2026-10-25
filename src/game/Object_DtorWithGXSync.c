typedef struct GXSyncObject {
    unsigned char pad_00[0x20];
    void *buffer;
    void *rom;
    unsigned char pad_28[4];
    void *jobj;
    void *jobjOverride;
    unsigned char pad_34[5];
    unsigned char ownsRom;
    unsigned char pad_3A[6];
    void *work;
} GXSyncObject;

extern void GXDrawDone(void);
extern void fn_802D041C(void *);
extern void clRom_Release(void *);
extern void MemoryManager_Free(void *);
extern void MemoryManager_TimedFree(void *);

GXSyncObject *Object_DtorWithGXSync(GXSyncObject *self, short flags) {
    if (self != 0) {
        GXDrawDone();
        if (self->rom != 0 || self->ownsRom == 1) {
            if (self->jobjOverride != 0) {
                fn_802D041C(self->jobjOverride);
            } else if (self->jobj != 0) {
                fn_802D041C(self->jobj);
            }
            if (self->rom != 0) {
                clRom_Release(self->rom);
            }
        }
        if (self->buffer != 0) {
            MemoryManager_Free(self->buffer);
        }
        MemoryManager_Free(self->work);
        if (flags > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
