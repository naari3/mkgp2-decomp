extern void MemoryManager_TimedFree(void *p);
extern void *lbl_806D18A0;

void fn_801DC5C0(void) {
    void *p = lbl_806D18A0;
    if (p != 0) {
        if (p != 0) {
            MemoryManager_TimedFree(p);
        }
    }
    lbl_806D18A0 = 0;
}
