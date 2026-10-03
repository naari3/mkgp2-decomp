/* Localized asset rows contain three variant pointers (12-byte stride).
 * Alias lookup writes a byte flag; its returned word selects the index table.
 */
extern int ItemAlias_DestToSource(int destId, unsigned char *foundOut);
extern int isJapanese(void);
extern int g_itemIdToIndexTable[];
extern const char *g_itemAssetTable_EN[][3];
extern const char *g_itemAssetTable_JP[][3];

const char *Item_GetLocalizedAsset(int id, int variant) {
    int index;
    unsigned char aliasScratch[8];

    if (id < 0 || id >= 0x147) {
        index = 0x146;
    } else {
        index = g_itemIdToIndexTable[ItemAlias_DestToSource((unsigned char)id, aliasScratch)];
    }
    if (variant < 0 || variant > 2) {
        variant = 0;
    }
    if (isJapanese() == 0) {
        return g_itemAssetTable_EN[index][variant];
    } else {
        return g_itemAssetTable_JP[index][variant];
    }
}
