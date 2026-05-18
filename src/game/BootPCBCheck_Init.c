/*
 * BootPCBCheck_Init @ 0x80084DF8 (size 0x90).
 *
 * Idempotent initializer for the 4-cabinet PCB-link "boot PCB check" task.
 * Lazily allocates a 0xD8-byte state buffer, runs DisplayContext_Init on it,
 * publishes the pointer to two .sbss slots, registers the polling callback
 * (PCBCheck_StateSet) against g_pcbListener, raises the sync target to 0x36
 * and arms the 0xE10 (3600-frame / 60 s) wait counter.
 *
 *   - if (g_BootPCBCheckArm != 0) return 0;            (lbl_806D11B8 -- gate)
 *   - if (g_BootPCBCheckBuf == 0) {                    (lbl_806D1880)
 *         buf = Alloc(0xD8);
 *         if (buf != 0) DisplayContext_Init();
 *         g_BootPCBCheckBuf = buf;
 *     }
 *   - g_BootPCBCheckArm = g_BootPCBCheckBuf;
 *   - if (g_BootPCBCheckBuf == 0) return 0;
 *   - SetSyncTarget(0x36);
 *   - PCBCheck_StateSet(g_pcbListener);
 *   - g_BootPCBCheckTimer = 0xE10;
 *   - return 1;
 *
 * The target carries a 24-byte extab with a DELETEPOINTER cleanup for r31
 * (the freshly Alloc'd buffer) calling MemoryManager_TimedFree (=
 * MemoryManager_TimedFree). The cleanup range covers PC=0..0x44 -- through the
 * `bl PCBCheck_StateSet` call, so if any of Alloc / DisplayContext_Init /
 * SetSyncTarget / PCBCheck_StateSet throws, the just-allocated buffer is
 * freed before re-raising. CW 1.3.2 has no concise way to express this
 * scoped-pointer C++ idiom in C; emit the extab/extabindex manually via
 * the project's `.extab_user` / `.extabindex_user` pipeline (mirrors
 * ServiceMenu.c / OpenFullServiceMenu).
 */

extern void *Alloc(int size);
extern void DisplayContext_Init(void);
extern void SetSyncTarget(int target);
extern void PCBCheck_StateSet(unsigned int listener);
extern void MemoryManager_TimedFree(void *);

extern unsigned int lbl_806D11B8;   // .sbss size 0x4: gate (init done flag, holds buf ptr)
extern unsigned int lbl_806D11BC;   // .sbss size 0x4: 60s wait counter
extern unsigned int lbl_806D1880;   // .sbss size 0x8: allocated state buffer ptr
extern unsigned int g_pcbListener;  // .sbss size 0x4: PCB listener handle

/* --- forward decl --- */
int BootPCBCheck_Init(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) ---
 * Mirror of target @etb_80008D5C: size 0x18 with a single DELETEPOINTER
 * action covering up to PC=0x44 (the bl PCBCheck_StateSet site).
 *
 * Layout (six 4-byte words):
 *   0x08080000   header (1 PC range, r31 saved-GPR range, large frame)
 *   0x00000044   PC end (offset from function start)
 *   0x00000010   action offset
 *   0x00000000   PC range terminator
 *   0x8A80001F   action: DELETEPOINTER r31 + end bit
 *   <dtor>       destructor function pointer
 */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct {
    unsigned int f0;
    unsigned int f1;
    unsigned int f2;
    unsigned int f3;
    unsigned int f4;
    void *f5;
} extab_BootPCBCheck_Init = {
    0x08080000, 0x00000044, 0x00000010, 0x00000000, 0x8A80001F, (void *)&MemoryManager_TimedFree
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_BootPCBCheck_Init = {
    (void *)&BootPCBCheck_Init, 0x00000090, (void *)&extab_BootPCBCheck_Init
};

int BootPCBCheck_Init(void) {
    void *buf;
    if (lbl_806D11B8 != 0) {
        return 0;
    }
    buf = (void *)lbl_806D1880;
    if (lbl_806D1880 == 0) {
        buf = Alloc(0xD8);
        if (buf != 0) {
            DisplayContext_Init();
        }
        lbl_806D1880 = (unsigned int)buf;
    }
    lbl_806D11B8 = lbl_806D1880;
    if (lbl_806D1880 == 0) {
        return 0;
    }
    SetSyncTarget(0x36);
    PCBCheck_StateSet(g_pcbListener);
    lbl_806D11BC = 0xE10;
    return 1;
}
