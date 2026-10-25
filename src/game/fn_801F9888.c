extern void *memset(void *dst, int c, unsigned long n);
extern void *lbl_806D1980;
extern char lbl_806D19A0[8];

static inline void DestroyInstance(void *inst) {
    if (inst != 0) {
        memset(lbl_806D19A0, 0, 1);
    }
}

void fn_801F9888(void) {
    if (lbl_806D1980 != 0) {
        DestroyInstance(lbl_806D1980);
        lbl_806D1980 = 0;
    }
}
