extern void *lbl_804E4B44[];
extern void *lbl_804E4AF0[];
extern void MemoryManager_TimedFree(void *p);

static inline void BaseDtor(void **self) {
    if (self != 0) {
        *self = lbl_804E4AF0;
    }
}

void **fn_801E8F5C(void **self, short flag) {
    if (self != 0) {
        *self = lbl_804E4B44;
        BaseDtor(self);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
