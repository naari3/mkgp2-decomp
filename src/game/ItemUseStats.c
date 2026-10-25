/* Per-kart item use counters by item category, 0x80045EE8..0x800461F0. */

typedef struct ItemDataEntry {
    unsigned char pad_00[5];
    signed char category;
} ItemDataEntry;

typedef struct ItemUseStats {
    unsigned char pad_00[4];
    int shell;
    int banana;
    int cat5_6_8;
    int cat7_9;
    unsigned char flag14;
    unsigned char flag15;
    unsigned char pad_16[2];
    int itemId;
} ItemUseStats;

extern ItemDataEntry *GetItemDataEntry(int id);

static inline ItemDataEntry *ItemUseStats_LookupItem(int id)
{
    if (id >= 0x115) {
        return 0;
    }
    return GetItemDataEntry(id);
}

static inline void ItemUseStats_DecrementCategory(ItemUseStats *stats, int category)
{
    switch (category) {
    case 1:
        stats->banana--;
        break;
    case 2:
    case 3:
    case 4:
    case 10:
    case 11:
        stats->shell--;
        break;
    case 5:
    case 6:
    case 8:
        stats->cat5_6_8--;
        break;
    case 7:
    case 9:
        stats->cat7_9--;
        break;
    }
    if (stats->shell < 0) {
        stats->shell = 0;
    }
    if (stats->banana < 0) {
        stats->banana = 0;
    }
    if (stats->cat5_6_8 < 0) {
        stats->cat5_6_8 = 0;
    }
    if (stats->cat7_9 < 0) {
        stats->cat7_9 = 0;
    }
}

static inline void ItemUseStats_IncrementCategory(ItemUseStats *stats, int category)
{
    switch (category) {
    case 1:
        stats->banana++;
        break;
    case 2:
    case 3:
    case 4:
    case 10:
    case 11:
        stats->shell++;
        break;
    case 5:
    case 6:
    case 8:
        stats->cat5_6_8++;
        break;
    case 7:
    case 9:
        stats->cat7_9++;
        break;
    }
}

void fn_80045EE8(ItemUseStats *stats, int category)
{
    ItemUseStats_DecrementCategory(stats, category);
}

void fn_80045F98(ItemUseStats *stats, int category)
{
    ItemUseStats_IncrementCategory(stats, category);
}

int ItemUseStats_GetItemIdIfFlag15(ItemUseStats *stats)
{
    if (stats->flag15 == 1) {
        return stats->itemId;
    }
    return -1;
}

int ItemUseStats_GetItemIdIfFlag14(ItemUseStats *stats)
{
    if (stats->flag14 == 1) {
        return stats->itemId;
    }
    return -1;
}

int ItemUseStats_GetCountBanana(ItemUseStats *stats)
{
    return stats->banana;
}

int ItemUseStats_GetCountCat7_9(ItemUseStats *stats)
{
    return stats->cat7_9;
}

int ItemUseStats_GetCountShell(ItemUseStats *stats)
{
    return stats->shell;
}

int ItemUseStats_GetCountCat5_6_8(ItemUseStats *stats)
{
    return stats->cat5_6_8;
}

#pragma exceptions on
void ItemCategoryBudget_Decrement(ItemUseStats *stats, int itemId)
{
    ItemUseStats_DecrementCategory(stats, ItemUseStats_LookupItem(itemId)->category);
}

void ItemUseStats_RegisterUse(ItemUseStats *stats)
{
    stats->flag14 = 1;
    ItemUseStats_IncrementCategory(stats, ItemUseStats_LookupItem(stats->itemId)->category);
}
#pragma exceptions reset
