/*
 * OpenFullServiceMenu @ 0x80073E7C (size 0x50).
 *
 * Trivial wrapper that creates a ServiceMenu instance:
 *   - ServiceButtonExtra_Set(1)  (ServiceButtonExtra_Set, sets a global flag)
 *   - SetSyncTarget(0x35)        (raise sync target id)
 *   - p = Alloc(0x28C)           (allocate ServiceMenu state)
 *   - if (p) ServiceMenu_Init(p, -1)
 *   - return p
 *
 * The target has a DELETEPOINTER extab cleanup for r31 with dtor =
 * MemoryManager_TimedFree (= dtor_8003AFB8). The cleanup covers the
 * `bl ServiceMenu_Init` call, so if Init throws the just-allocated
 * buffer is freed before re-raising.
 *
 * The C++ idiom in the original code is a scoped raw-pointer object
 * (std::auto_ptr-style) whose destructor calls MemoryManager_TimedFree.
 * Emulating this in C requires manual extab emission via __declspec
 * section ".extab_user" + the postprocess_extab_user.py rename hook.
 */

extern void ServiceButtonExtra_Set(unsigned char value);
extern void SetSyncTarget(int target);
extern void *Alloc(int size);
extern void ServiceMenu_Init(void *self, int param);
extern void dtor_8003AFB8(void *);

/* --- forward decl --- */
void *OpenFullServiceMenu(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) ---
 * Mirror of target @etb_800082A8: size 0x18 with a single DELETEPOINTER
 * action covering up to PC=0x38 (the bl ServiceMenu_Init site).
 *
 * Layout (six 4-byte words):
 *   0x08080000   header (1 PC range, r31 saved-GPR range, large frame)
 *   0x00000038   PC end (offset from function start)
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
} extab_OpenFullServiceMenu = {
    0x08080000, 0x00000038, 0x00000010, 0x00000000, 0x8A80001F, (void *)&dtor_8003AFB8
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_OpenFullServiceMenu = {
    (void *)&OpenFullServiceMenu, 0x00000050, (void *)&extab_OpenFullServiceMenu
};

void *OpenFullServiceMenu(void) {
    void *p;
    ServiceButtonExtra_Set(1);
    SetSyncTarget(0x35);
    p = Alloc(0x28C);
    if (p != 0) {
        ServiceMenu_Init(p, -1);
    }
    return p;
}
