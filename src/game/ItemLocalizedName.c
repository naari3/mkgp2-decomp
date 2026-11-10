extern int isJapanese(void);
extern int g_itemIdToIndexTable[];
extern const char *ItemLocalizedName_rodata_803DE9AC[];
extern const char *ItemLocalizedName_rodata_803E2914[];

const char *fn_8023DAA8(int id) {
    int index;
    if (id < 0 || id >= 0x147) index = 0x146;
    else index = g_itemIdToIndexTable[id];
    if (isJapanese() == 0) return ItemLocalizedName_rodata_803DE9AC[index];
    else return ItemLocalizedName_rodata_803E2914[index];
}
