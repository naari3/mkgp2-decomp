extern void *lbl_806D1878;
extern char lbl_8039FCF0[];
extern void MemoryManager_TimedFree(void *);
extern void *StrPcb_GetInstance(void);
extern void StrPcb_ClearStatusBits(void *pcb, int bits);
extern void DebugPrintf(const char *fmt, ...);

static inline void DeletePcbLink(void *p) {
    if (p != 0) {
        if (StrPcb_GetInstance() != 0) {
            StrPcb_ClearStatusBits(StrPcb_GetInstance(), 0xC);
        }
        DebugPrintf(lbl_8039FCF0);
        MemoryManager_TimedFree(p);
    }
}

void fn_801DAE54(void) {
    if (lbl_806D1878 != 0) {
        DeletePcbLink(lbl_806D1878);
        lbl_806D1878 = 0;
    }
}
