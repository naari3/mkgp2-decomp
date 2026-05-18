/*
 * GetEnemyParam @ 0x801DE73C (size 0x74).
 *
 * Lazy-init singleton getter for the global clEnemyParam slot table.
 * Allocates a 0x18-byte (6 ints) struct on first call, fills all 6 slots
 * with -1, and stores the pointer into g_clEnemyParam (.sbss). Returns
 * the address of the items[] array (i.e. &g_clEnemyParam->items[0]).
 *
 * The target has a DELETEPOINTER extab cleanup for r31 with dtor =
 * MemoryManager_TimedFree (= MemoryManager_TimedFree). The cleanup covers the
 * `bl Alloc` ... `bl DebugPrintf` window, so if DebugPrintf throws the
 * just-allocated buffer is freed before re-raising. Same scoped raw-pointer
 * idiom as OpenFullServiceMenu (game/ServiceMenu.c).
 *
 * Manual extab emission via __declspec(section ".extab_user") +
 * postprocess_extab_user.py rename hook (same mechanism as ServiceMenu).
 */

extern void *Alloc(int size);
extern void DebugPrintf(const char *fmt, ...);
extern void MemoryManager_TimedFree(void *);

struct clEnemyParamSlots {
    int items[6];
};
extern struct clEnemyParamSlots *g_clEnemyParam;
extern char lbl_803BD0D8[];

/* --- forward decl --- */
int *GetEnemyParam(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) ---
 * Mirror of target @etb_800159D0: size 0x18 with a single DELETEPOINTER
 * action covering up to PC=0x3c (just after bl DebugPrintf).
 *
 * Layout (six 4-byte words):
 *   0x08080000   header (1 PC range, r31 saved-GPR range, large frame)
 *   0x0000003C   PC end (offset from function start, just after bl DebugPrintf)
 *   0x00000010   action offset
 *   0x00000000   PC range terminator
 *   0x8A80001F   action: DELETEPOINTER r31 + end bit
 *   <dtor>       destructor function pointer (MemoryManager_TimedFree)
 */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct {
    unsigned int f0;
    unsigned int f1;
    unsigned int f2;
    unsigned int f3;
    unsigned int f4;
    void *f5;
} extab_GetEnemyParam = {
    0x08080000, 0x0000003C, 0x00000010, 0x00000000, 0x8A80001F, (void *)&MemoryManager_TimedFree
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_GetEnemyParam = {
    (void *)&GetEnemyParam, 0x00000074, (void *)&extab_GetEnemyParam
};

int *GetEnemyParam(void) {
    struct clEnemyParamSlots *p;
    if (g_clEnemyParam == 0) {
        p = (struct clEnemyParamSlots *)Alloc(0x18);
        if (p != 0) {
            DebugPrintf(lbl_803BD0D8);
            p->items[0] = -1;
            p->items[1] = -1;
            p->items[2] = -1;
            p->items[3] = -1;
            p->items[4] = -1;
            p->items[5] = -1;
        }
        g_clEnemyParam = p;
    }
    return g_clEnemyParam->items;
}
