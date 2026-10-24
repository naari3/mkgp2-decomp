extern void MemoryManager_TimedFree(void *p);
extern void *lbl_806D18C0;

void fn_801DE7DC(void) {
    if (lbl_806D18C0 != 0) {
        MemoryManager_TimedFree(lbl_806D18C0);
    }
    lbl_806D18C0 = 0;
}
