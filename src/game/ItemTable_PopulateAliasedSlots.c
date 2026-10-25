/* ItemTable_PopulateAliasedSlots (0x800D76E8): copies the class entry of
 * each alias source into item ids 0x9F..0x114, then fills the fixed extra
 * slots 0x109..0x114 from their base items. */

typedef struct ItemAliasEntry {
    int source;
    int dest;
    int flags;
} ItemAliasEntry;

typedef struct ItemClassEntry {
    unsigned char pad0[4];
    unsigned char flag0;
    signed char flag1;
    unsigned char pad6[0x14 - 6];
} ItemClassEntry;

extern ItemAliasEntry g_itemAliasTable[155];
extern ItemClassEntry lbl_8041CBA8[];
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
            memcpy(&lbl_8041CBA8[id], &lbl_8041CBA8[src], sizeof(ItemClassEntry));
        }
    }
    memcpy(&lbl_8041CBA8[0x109], &lbl_8041CBA8[0x4F], sizeof(ItemClassEntry));
    memcpy(&lbl_8041CBA8[0x10A], &lbl_8041CBA8[0x53], sizeof(ItemClassEntry));
    memcpy(&lbl_8041CBA8[0x10B], &lbl_8041CBA8[0x65], sizeof(ItemClassEntry));
    memcpy(&lbl_8041CBA8[0x10C], &lbl_8041CBA8[0x4B], sizeof(ItemClassEntry));
    memcpy(&lbl_8041CBA8[0x10D], &lbl_8041CBA8[0x57], sizeof(ItemClassEntry));
    memcpy(&lbl_8041CBA8[0x10E], &lbl_8041CBA8[0x45], sizeof(ItemClassEntry));
    memcpy(&lbl_8041CBA8[0x10F], &lbl_8041CBA8[0x70], sizeof(ItemClassEntry));
    memcpy(&lbl_8041CBA8[0x110], &lbl_8041CBA8[0x67], sizeof(ItemClassEntry));
    memcpy(&lbl_8041CBA8[0x111], &lbl_8041CBA8[0x66], sizeof(ItemClassEntry));
    memcpy(&lbl_8041CBA8[0x112], &lbl_8041CBA8[0x62], sizeof(ItemClassEntry));
    memcpy(&lbl_8041CBA8[0x113], &lbl_8041CBA8[0x68], sizeof(ItemClassEntry));
    memcpy(&lbl_8041CBA8[0x114], &lbl_8041CBA8[0x63], sizeof(ItemClassEntry));
    lbl_8041CBA8[0x115].flag1 = -1;
}
