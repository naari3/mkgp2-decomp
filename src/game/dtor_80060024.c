typedef struct ItemBoxResponder {
    void *vtbl;
} ItemBoxResponder;

extern char lbl_803F9D00[];
extern void *lbl_806D10D0;
extern void clItemBoxManager_UnregisterResponder(void *mgr, ItemBoxResponder *responder);
extern void MemoryManager_TimedFree(void *);

static inline void *item_box_manager(void) {
    void *mgr = lbl_806D10D0;

    if (mgr == 0) {
        return 0;
    }
    return mgr;
}

ItemBoxResponder *dtor_80060024(ItemBoxResponder *self, short flags) {
    if (self != 0) {
        self->vtbl = lbl_803F9D00;
        if (item_box_manager() != 0) {
            clItemBoxManager_UnregisterResponder(item_box_manager(), self);
        }
        if (flags > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
