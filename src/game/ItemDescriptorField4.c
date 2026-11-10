extern int ItemAlias_DestToSource(unsigned int itemDestId, void *aliasOut);
extern unsigned int g_itemIdToIndexTable[0x148];

typedef struct ItemDescriptor {
    unsigned int nameMsgId;
    unsigned int field_4;
    unsigned int field_8;
    unsigned int field_C;
} ItemDescriptor;

extern struct ItemDescriptor lbl_803DC530[];

#pragma exceptions on

unsigned int fn_8023DBEC(unsigned int itemDestId) {
    unsigned int descriptorIndex;
    int aliasedItemId;
    unsigned char aliasScratch[8];

    if (((int)itemDestId < 0) || ((int)itemDestId >= 0x147)) {
        descriptorIndex = 0x146;
    } else {
        aliasedItemId = ItemAlias_DestToSource(itemDestId & 0xff, aliasScratch);
        descriptorIndex = g_itemIdToIndexTable[aliasedItemId];
    }
    return lbl_803DC530[descriptorIndex].field_4;
}

