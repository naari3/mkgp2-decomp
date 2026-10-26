/* Lazily created race context singleton and its deleting destructor. */
#pragma cplusplus on

struct RaceContext {
    void *vtable;
    RaceContext();
};

extern "C" {
void MemoryManager_TimedFree(void *p);
extern RaceContext *lbl_806D12DC;
extern void *lbl_8040E4DC[];
}

extern "C" RaceContext *RaceContext_EnsureSingleton(void)
{
    RaceContext *instance = lbl_806D12DC == 0 ? (RaceContext *)0 : lbl_806D12DC;
    if (instance == 0) {
        new RaceContext;
    }
    return lbl_806D12DC == 0 ? (RaceContext *)0 : lbl_806D12DC;
}

extern "C" RaceContext *dtor_8009DCE0(RaceContext *self, short flag)
{
    if (self) {
        self->vtable = lbl_8040E4DC;
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
