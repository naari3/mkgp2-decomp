#include "game/types/ItemAliasEntry.h"

#include "game/types/ItemClassEntry.h"

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
