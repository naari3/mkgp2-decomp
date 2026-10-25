extern void *lbl_804E5538[];
extern void MemoryManager_TimedFree(void *p);

void **fn_801F7B2C(void **self, short flag) {
    if (self != 0) {
        *self = lbl_804E5538;
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
