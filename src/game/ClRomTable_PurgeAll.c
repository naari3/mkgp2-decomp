/*
 * ClRomTable_PurgeAll, 0x8003AC84..0x8003AD4C: force-destroys every rom in
 * the 40-entry ClRomTable (.bss 0x80598678) and returns how many slots were
 * in use.
 */

typedef struct ClRomEntry {
    void *rom;        /* +0x00 */
    const char *path; /* +0x04 */
} ClRomEntry;

extern ClRomEntry lbl_80598678[40];

extern int strcmp(const char *a, const char *b);
extern void clRom_DtorForce(void *rom, int flag);

static inline ClRomEntry *ClRomTable_FindByPath(ClRomEntry *table, const char *path)
{
    ClRomEntry *entry = table;
    int i;

    for (i = 0; i < 40; i++, entry++) {
        if (entry->path != 0 && strcmp(entry->path, path) == 0) {
            return &lbl_80598678[i];
        }
    }
    return 0;
}

#pragma exceptions on

#pragma opt_propagation off
/* fakematch (trace, regalloc_patterns 72): the natural code is
 *     ClRomEntry *table = lbl_80598678; int count = 0;
 *     for (i = 0; i < 40; i++) if (table[i].path != 0) { found = Find(table, table[i].path); ... }
 * The target colours walker, path, table in that order and gives `table`
 * the direct addi (`mr walker,table`), which needs all three to be split-off
 * lifetime ranges (declaration order = colour order). The chain of zero
 * dummies costs no instructions. */
int ClRomTable_PurgeAll(void)
{
    ClRomEntry *e;
    const char *path;
    ClRomEntry *table;
    ClRomEntry *found;
    int count;
    int i;

    e = 0;
    path = (const char *)e;
    table = (ClRomEntry *)path;
    count = (int)table;
    table = lbl_80598678;
    for (i = 0, e = table; i < 40; i++, e++) {
        path = e->path;
        if (path != 0) {
            found = ClRomTable_FindByPath(table, path);
            if (found != 0) {
                clRom_DtorForce(found->rom, 1);
                found->rom = 0;
                found->path = 0;
            }
            count++;
        }
    }
    return count;
}
#pragma opt_propagation reset
#pragma exceptions reset
