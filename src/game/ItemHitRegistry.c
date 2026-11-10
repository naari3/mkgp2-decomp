/*
 * ItemHitRegistry: registry of items currently colliding/registered against
 * a kart, with per-kind counters.
 *
 * .text 0x800D8840..0x800D8E20 (dtk group auto_03_800D8840_text)
 *
 * Data:
 *   ItemHitRegistry_bss_80656F08 (.bss 0x300): 64-entry registry, stride 0xc
 *   ItemHitRegistry_AddEntry_rodata_8032DE00 (.rodata):    kind table, stride 0x18, first field = kind id
 *   ItemHitRegistry_bss_806D14D8 (.sbss):      total count
 *   ItemHitRegistry_bss_806D14DC/E0/E4 (.sbss): per-kind-family counters
 */

#include "game/types/HitItem.h"

typedef struct ItemHitEntry {
    HitItem *item;       /* 0x0 */
    unsigned char flag;  /* 0x4 */
    int kind;            /* 0x8 */
} ItemHitEntry;

typedef struct ItemKindDef {
    int kind;                /* 0x0 */
    unsigned char pad[0x14]; /* 0x4 */
} ItemKindDef;

extern ItemHitEntry ItemHitRegistry_bss_80656F08[64];
extern const ItemKindDef ItemHitRegistry_AddEntry_rodata_8032DE00[24];

extern int ItemHitRegistry_bss_806D14D8;
extern int ItemHitRegistry_bss_806D14DC;
extern int ItemHitRegistry_bss_806D14E0;
extern int ItemHitRegistry_bss_806D14E4;

int ItemHitRegistry_RemoveEntry(HitItem *item, int unused, int *outTotal) {
    int i;
    int j;

    if (outTotal != 0) {
        *outTotal = ItemHitRegistry_bss_806D14D8;
    }

    for (i = 0; i < 64; i++) {
        if (ItemHitRegistry_bss_80656F08[i].item == item) {
            if (ItemHitRegistry_bss_80656F08[i].flag == 0) {
                return 0;
            }
            for (j = i; j < 63; j++) {
                ItemHitRegistry_bss_80656F08[j].item = ItemHitRegistry_bss_80656F08[j + 1].item;
                ItemHitRegistry_bss_80656F08[j].flag = ItemHitRegistry_bss_80656F08[j + 1].flag;
                ItemHitRegistry_bss_80656F08[j].kind = ItemHitRegistry_bss_80656F08[j + 1].kind;
            }
            ItemHitRegistry_bss_80656F08[63].item = 0;
            ItemHitRegistry_bss_80656F08[63].flag = 0;
            ItemHitRegistry_bss_80656F08[63].kind = -1;
            return 1;
        }
    }
    return 1;
}

int ItemHitRegistry_AddEntry(HitItem *item) {
    int i;
    int found;

    found = -1;
    for (i = 0; i < 24; i++) {
        if (item->kind == ItemHitRegistry_AddEntry_rodata_8032DE00[i].kind) {
            found = i;
            break;
        }
    }
    if (found < 0) {
        return 0;
    }

    for (i = 0; i < 64; i++) {
        if (ItemHitRegistry_bss_80656F08[i].item == item) {
            return 1;
        }
        if (ItemHitRegistry_bss_80656F08[i].item == 0) {
            ItemHitRegistry_bss_80656F08[i].item = item;
            ItemHitRegistry_bss_80656F08[i].flag = 0;
            ItemHitRegistry_bss_80656F08[i].kind = item->kind;
            if (item->kind == 0x46 || item->kind == 0x82) {
                ItemHitRegistry_bss_806D14DC++;
                if (ItemHitRegistry_bss_806D14DC % 3 == 0) {
                    ItemHitRegistry_bss_806D14D8++;
                }
            } else if (item->kind == 0x62) {
                ItemHitRegistry_bss_806D14E0++;
                if (ItemHitRegistry_bss_806D14E0 % 3 == 0) {
                    ItemHitRegistry_bss_806D14D8++;
                }
            } else if (item->kind == 0x69) {
                ItemHitRegistry_bss_806D14E4++;
                if (ItemHitRegistry_bss_806D14E4 % 5 == 0) {
                    ItemHitRegistry_bss_806D14D8++;
                }
            } else {
                ItemHitRegistry_bss_806D14D8++;
            }
            return 1;
        }
    }
    return 0;
}

void ItemHitRegistry_PruneStale(void) {
    int i;

    for (i = 0; i < 64; i++) {
        HitItem *it = ItemHitRegistry_bss_80656F08[i].item;
        unsigned char stale;

        if (it == 0) {
            continue;
        }
        stale = 1;
        if (it->state != 0) {
            if (it->kind == ItemHitRegistry_bss_80656F08[i].kind) {
                stale = 0;
            }
        }
        if (ItemHitRegistry_bss_806D14D8 > 3 || stale == 1) {
            ItemHitRegistry_bss_80656F08[i].flag = 1;
            if (it->kind == 0x46 || it->kind == 0x82) {
                ItemHitRegistry_bss_806D14DC--;
                if (ItemHitRegistry_bss_806D14DC % 3 == 0) {
                    ItemHitRegistry_bss_806D14D8--;
                }
            } else if (it->kind == 0x62) {
                ItemHitRegistry_bss_806D14E0--;
                if (ItemHitRegistry_bss_806D14E0 % 3 == 0) {
                    ItemHitRegistry_bss_806D14D8--;
                }
            } else if (it->kind == 0x69) {
                ItemHitRegistry_bss_806D14E4--;
                if (ItemHitRegistry_bss_806D14E4 % 5 == 0) {
                    ItemHitRegistry_bss_806D14D8--;
                }
            } else {
                ItemHitRegistry_bss_806D14D8--;
            }
            if (stale == 1) {
                ItemHitRegistry_bss_80656F08[i].item = 0;
            }
        }
    }
}

void ItemHitRegistry_Reset(void) {
    int i;

    for (i = 0; i < 64; i++) {
        ItemHitRegistry_bss_80656F08[i].item = 0;
        ItemHitRegistry_bss_80656F08[i].flag = 0;
        ItemHitRegistry_bss_80656F08[i].kind = -1;
    }
    ItemHitRegistry_bss_806D14D8 = 0;
    ItemHitRegistry_bss_806D14DC = 0;
    ItemHitRegistry_bss_806D14E0 = 0;
    ItemHitRegistry_bss_806D14E4 = 0;
}
