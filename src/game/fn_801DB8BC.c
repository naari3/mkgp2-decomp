extern void MemoryManager_TimedFree(void *p);
extern void *lbl_806D1888;

void fn_801DB8BC(void) {
    if (lbl_806D1888 != 0) {
        MemoryManager_TimedFree(lbl_806D1888);
    }
    lbl_806D1888 = 0;
}
