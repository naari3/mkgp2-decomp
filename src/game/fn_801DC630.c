extern void MemoryManager_TimedFree(void *p);
extern void *lbl_806D18A8;

void fn_801DC630(void) {
    if (lbl_806D18A8 != 0) {
        MemoryManager_TimedFree(lbl_806D18A8);
    }
    lbl_806D18A8 = 0;
}
