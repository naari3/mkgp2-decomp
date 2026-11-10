/* ItemTable_PopulateAliasedSlots (0x800D76E8): copies the class entry of
 * each alias source into item ids 0x9F..0x114, then fills the fixed extra
 * slots 0x109..0x114 from their base items. */

#include "game/types/ItemAliasEntry.h"

typedef struct ItemClassEntry {
    unsigned char pad0[4];
    unsigned char flag0;
    signed char flag1;
    unsigned char pad6[0x14 - 6];
} ItemClassEntry;

extern ItemAliasEntry g_itemAliasTable[155];
extern ItemClassEntry g_itemClassTable[];
extern void *memcpy(void *dst, const void *src, unsigned long n);

static inline int ItemAlias_FindSource(int id, signed char *found)
{
    int i;

    for (i = 0; i < 155; i++) {
        if (id == g_itemAliasTable[i].flags) {
            if (found) {
                *found = 1;
            }
            return g_itemAliasTable[i].source;
        }
    }
    if (found) {
        *found = 0;
    }
    return id;
}

void ItemTable_PopulateAliasedSlots(void)
{
    int id;

    for (id = 0x9F; id < 0x115; id++) {
        signed char found;
        int src = ItemAlias_FindSource(id, &found);
        if (found) {
            memcpy(&g_itemClassTable[id], &g_itemClassTable[src], sizeof(ItemClassEntry));
        }
    }
    memcpy(&g_itemClassTable[0x109], &g_itemClassTable[0x4F], sizeof(ItemClassEntry));
    memcpy(&g_itemClassTable[0x10A], &g_itemClassTable[0x53], sizeof(ItemClassEntry));
    memcpy(&g_itemClassTable[0x10B], &g_itemClassTable[0x65], sizeof(ItemClassEntry));
    memcpy(&g_itemClassTable[0x10C], &g_itemClassTable[0x4B], sizeof(ItemClassEntry));
    memcpy(&g_itemClassTable[0x10D], &g_itemClassTable[0x57], sizeof(ItemClassEntry));
    memcpy(&g_itemClassTable[0x10E], &g_itemClassTable[0x45], sizeof(ItemClassEntry));
    memcpy(&g_itemClassTable[0x10F], &g_itemClassTable[0x70], sizeof(ItemClassEntry));
    memcpy(&g_itemClassTable[0x110], &g_itemClassTable[0x67], sizeof(ItemClassEntry));
    memcpy(&g_itemClassTable[0x111], &g_itemClassTable[0x66], sizeof(ItemClassEntry));
    memcpy(&g_itemClassTable[0x112], &g_itemClassTable[0x62], sizeof(ItemClassEntry));
    memcpy(&g_itemClassTable[0x113], &g_itemClassTable[0x68], sizeof(ItemClassEntry));
    memcpy(&g_itemClassTable[0x114], &g_itemClassTable[0x63], sizeof(ItemClassEntry));
    g_itemClassTable[0x115].flag1 = -1;
}
