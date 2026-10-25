/*
 * ClRomTable_PurgeAll, 0x8003AC84..0x8003AD4C: force-destroys every rom in
 * the 40-entry ClRomTable (.bss 0x80598678) and returns how many slots were
 * in use.
 *
 * NonMatching: the table base and the outer slot pointer swap registers
 * (r27/r29) against the target.
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

int ClRomTable_PurgeAll(void)
{
    ClRomEntry *table = lbl_80598678;
    ClRomEntry *found;
    const char *path;
    int count = 0;
    int i;

    for (i = 0; i < 40; i++) {
        if (table[i].path != 0) {
            found = ClRomTable_FindByPath(table, table[i].path);
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
#pragma exceptions reset
