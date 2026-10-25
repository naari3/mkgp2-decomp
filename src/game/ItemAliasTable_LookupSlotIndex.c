typedef struct ItemAliasEntry {
    int source;
    int dest;
    int flags;
} ItemAliasEntry;

typedef struct ItemClassEntry {
    unsigned char pad0[4];
    unsigned char flag0;
    unsigned char flag1;
    unsigned char pad6[0x14 - 6];
} ItemClassEntry;

extern ItemAliasEntry g_itemAliasTable[155];
extern ItemClassEntry lbl_8041CBA8[];

int ItemAliasTable_LookupSlotIndex(int id)
{
    int i;

    for (i = 0; i < 155; i++) {
        if (id == g_itemAliasTable[i].dest) {
            return i;
        }
    }
    return 0;
}

unsigned char ItemClass_GetFlagByte1(int id)
{
    return lbl_8041CBA8[id].flag1;
}

unsigned char ItemClass_GetFlagByte0(int id)
{
    return lbl_8041CBA8[id].flag0;
}

ItemClassEntry *GetItemDataEntry(int id)
{
    return &lbl_8041CBA8[id];
}
