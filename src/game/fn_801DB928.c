extern void MemoryManager_TimedFree(void *p);
extern void *lbl_806D1890;

void fn_801DB928(void) {
    if (lbl_806D1890 != 0) {
        MemoryManager_TimedFree(lbl_806D1890);
    }
    lbl_806D1890 = 0;
}
