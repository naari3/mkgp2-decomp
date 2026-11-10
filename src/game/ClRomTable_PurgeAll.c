/*
 * ClRomTable_PurgeAll, 0x8003AC84..0x8003AD4C: force-destroys every rom in
 * the 40-entry ClRomTable (.bss 0x80598678) and returns how many slots were
 * in use.
 */

#include "game/types/ClRomEntry.h"

extern ClRomEntry lbl_80598678[40];

extern int strcmp(const char *a, const char *b);
extern void clRom_DtorForce(void *rom, int flag);

#pragma cplusplus on
#pragma exceptions on

static inline void ClRomTable_PurgeEntries(int &count, int &i)
{
    ClRomEntry *table;
    const char *path;
    ClRomEntry *e;
    ClRomEntry *entry;
    int j;
    ClRomEntry *found;

    table = lbl_80598678;
    count = 0;
    for (i = 0, e = table; i < 40; i++, e++) {
        path = e->path;
        if (path != 0) {
            entry = table;
            for (j = 0; j < 40; j++, entry++) {
                if (entry->path != 0 && strcmp(entry->path, path) == 0) {
                    found = &lbl_80598678[j];
                    goto found_entry;
                }
            }
            found = 0;
found_entry:
            if (found != 0) {
                clRom_DtorForce(found->rom, 1);
                found->rom = 0;
                found->path = 0;
            }
            count++;
        }
    }
}

extern "C" int ClRomTable_PurgeAll(void)
{
    int count;
    int i;
    ClRomTable_PurgeEntries(count, i);
    return count;
}
#pragma exceptions reset
#pragma cplusplus reset
