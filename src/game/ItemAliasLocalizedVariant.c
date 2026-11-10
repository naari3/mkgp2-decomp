/* Localized asset rows contain three variant pointers (12-byte stride).
 * Alias lookup writes a byte flag; its returned word selects the index table.
 */
extern int ItemAlias_DestToSource(int destId, unsigned char *foundOut);
extern int isJapanese(void);
extern int g_itemIdToIndexTable[];
extern const char *ItemAliasLocalizedVariant_rodata_803DFF74[][3];
extern const char *ItemAliasLocalizedVariant_rodata_803E3868[][3];

const char *fn_8023D938(int id, int variant) {
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
        return ItemAliasLocalizedVariant_rodata_803DFF74[index][variant];
    } else {
        return ItemAliasLocalizedVariant_rodata_803E3868[index][variant];
    }
}
