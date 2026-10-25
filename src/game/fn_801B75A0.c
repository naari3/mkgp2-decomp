extern void MemoryManager_TimedFree(void *);
extern void dtor_8002CDF4(void *self, short flag);
extern void fn_801DB68C(void *ctx, short flag);
extern int fn_801B6B94(void);
extern char lbl_8049A214[];
extern void *lbl_806D1880;

void *fn_801B75A0(void *self, short flag) {
    if (self != 0) {
        *(char **)self = lbl_8049A214;
        if (lbl_806D1880 == 0) {
            fn_801DB68C(lbl_806D1880, 1);
            lbl_806D1880 = 0;
        }
        fn_801B6B94();
        dtor_8002CDF4(self, 0);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
