extern void *lbl_804E5558[];
extern void *lbl_804E5538[];
extern void MemoryManager_TimedFree(void *p);

static inline void BaseDtor(void **self) {
    if (self != 0) {
        *self = lbl_804E5538;
    }
}

void **dtor_801F7A74(void **self, short flag) {
    if (self != 0) {
        *self = lbl_804E5558;
        BaseDtor(self);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
