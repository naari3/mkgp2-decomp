/* g_itemAliasTable: 0x9B entries, each 0xC bytes (3 ints).
 *   +0x0: src item id
 *   +0x4: remap (hit context) id
 *   +0x8: dest item id
 */
extern int g_itemAliasTable[0x9B][3];

int ItemAlias_SourceToDest(int srcId) {
    int *p;
    int i;
    p = &g_itemAliasTable[0][0];
    i = 0;
    for (;;) {
        int k;
        for (k = 0; k < 0x9b; k++) {
            if (srcId == *p) {
                return g_itemAliasTable[i][2];
            }
            p += 3;
            i += 1;
        }
        return 0;
    }
}

int ItemAlias_DestToSource(int destId, unsigned char *foundOut) {
    int *p;
    int i;
    p = &g_itemAliasTable[0][0];
    i = 0;
    {
        int k;
        for (k = 0; k < 0x9b; k++) {
            if (destId == p[2]) {
                if (foundOut != 0) {
                    *foundOut = 1;
                }
                return g_itemAliasTable[i][0];
            }
            p += 3;
            i += 1;
        }
    }
    if (foundOut == 0) {
        return destId;
    }
    *foundOut = 0;
    return destId;
}

/* The index lookup uses slot zero as its fallback, like
 * ItemAliasTable_LookupSlotIndex. Keep it separate from indexed access. */
static inline int ItemAlias_FindHitIndex(int srcId) {
    int i;
    for (i = 0; i < 0x9b; i++) {
        if (srcId == g_itemAliasTable[i][1]) {
            return i;
        }
    }
    return 0;
}

static inline int ItemAlias_SourceAtIndex(int i) {
    if (i >= 0x9b) {
        return 0;
    }
    return g_itemAliasTable[i][0];
}

int ItemAlias_HitRemapLookup(int srcId) {
    return ItemAlias_SourceAtIndex(ItemAlias_FindHitIndex(srcId));
}
