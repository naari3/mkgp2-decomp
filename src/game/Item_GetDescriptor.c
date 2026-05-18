/*
 * Item descriptor field accessors (paired).
 *
 *   Item_GetDescriptorFieldC @ 0x8023DB24 (size 0x64)
 *   Item_GetDescriptorField8 @ 0x8023DB88 (size 0x64)
 *
 * Both clamp itemDestId to [0..0x146], else fall back to sentinel index
 * 0x146.  In-range ids are routed through ItemAlias_DestToSource (with an
 * 8-byte alias scratch buffer on the stack) and then indexed into
 * g_itemIdToIndexTable[0x804EB6B0] to obtain a slot index into the global
 * ItemDescriptor array at 0x803DC530 (stride 0x10).
 *
 * The two fns differ only by which struct field they fetch
 * (Item_GetDescriptorFieldC -> field_C, Item_GetDescriptorField8 ->
 * field_8). Both live in the `game` lib (CW 1.3.2) and each carries its
 * own extab/extabindex entry (Has Large Frame: Yes); `#pragma exceptions
 * on` lets CW auto-emit them so they match the original layout.
 */

extern int ItemAlias_DestToSource(unsigned int itemDestId, void *aliasOut);
extern unsigned int g_itemIdToIndexTable[0x148];

struct ItemDescriptor {
    unsigned int pad[2];
    unsigned int field_8;
    unsigned int field_C;
};

extern struct ItemDescriptor lbl_803DC530[];

#pragma exceptions on

unsigned int Item_GetDescriptorFieldC(unsigned int itemDestId) {
    unsigned int descriptorIndex;
    int aliasedItemId;
    unsigned char aliasScratch[8];

    if (((int)itemDestId < 0) || ((int)itemDestId >= 0x147)) {
        descriptorIndex = 0x146;
    } else {
        aliasedItemId = ItemAlias_DestToSource(itemDestId & 0xff, aliasScratch);
        descriptorIndex = g_itemIdToIndexTable[aliasedItemId];
    }
    return lbl_803DC530[descriptorIndex].field_C;
}

unsigned int Item_GetDescriptorField8(unsigned int itemDestId) {
    unsigned int descriptorIndex;
    int aliasedItemId;
    unsigned char aliasScratch[8];

    if (((int)itemDestId < 0) || ((int)itemDestId >= 0x147)) {
        descriptorIndex = 0x146;
    } else {
        aliasedItemId = ItemAlias_DestToSource(itemDestId & 0xff, aliasScratch);
        descriptorIndex = g_itemIdToIndexTable[aliasedItemId];
    }
    return lbl_803DC530[descriptorIndex].field_8;
}

#pragma exceptions reset
