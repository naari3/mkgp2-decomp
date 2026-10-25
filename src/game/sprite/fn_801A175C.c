extern void MemoryManager_TimedFree(void *p);

void *fn_801A175C(void *self, short flag) {
    if (self != 0 && flag > 0) {
        MemoryManager_TimedFree(self);
    }
    return self;
}
