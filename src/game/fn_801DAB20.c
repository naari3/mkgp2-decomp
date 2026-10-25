extern void MemoryManager_TimedFree(void *);
extern void fn_80121210(void);
extern char lbl_8049BC20[];

void *fn_801DAB20(void *self, short flag) {
    if (self != 0) {
        *(char **)self = lbl_8049BC20;
        fn_80121210();
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
