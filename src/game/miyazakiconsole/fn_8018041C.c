extern void MemoryManager_TimedFree(void *p);

void *fn_8018041C(void *self, short flag) {
    if (self) {
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
