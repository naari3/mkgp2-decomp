extern int lbl_806D15D8;
extern void *lbl_806D15D0;
extern void *lbl_80491224[3];
extern void Object_DtorWithGXSync(void *p, int flag);
extern void MemoryManager_TimedFree(void *p);

static inline void Release(void) {
    int i;
    if (lbl_806D15D0 != 0) {
        Object_DtorWithGXSync(lbl_806D15D0, 1);
        lbl_806D15D0 = 0;
    }
    for (i = 0; i < 3; i++) {
        if (lbl_80491224[i] != 0) {
            Object_DtorWithGXSync(lbl_80491224[i], 1);
            lbl_80491224[i] = 0;
        }
    }
}

void *fn_8016F9A0(void *p, short flag) {
    if (p != 0) {
        if (lbl_806D15D8 > 0 && --lbl_806D15D8 == 0) {
            Release();
        }
        if (flag > 0) MemoryManager_TimedFree(p);
    }
    return p;
}
