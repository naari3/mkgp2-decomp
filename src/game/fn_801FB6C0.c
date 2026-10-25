extern void *lbl_804EBECC[];
extern void dtor_801FD32C(void *self, int flag);
extern void MemoryManager_TimedFree(void *p);

void **fn_801FB6C0(void **self, short flag) {
    if (self != 0) {
        *self = lbl_804EBECC;
        dtor_801FD32C(self, 0);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
