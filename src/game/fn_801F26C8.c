extern void *lbl_804E5284[];
extern void *lbl_80419DC8[];
extern void MemoryManager_TimedFree(void *p);

static inline void BaseDtor(void **self) {
    if (self != 0) {
        *self = lbl_80419DC8;
    }
}

void **fn_801F26C8(void **self, short flag) {
    if (self != 0) {
        *self = lbl_804E5284;
        BaseDtor(self);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
