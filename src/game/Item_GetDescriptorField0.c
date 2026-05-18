/*
 * Item descriptor field accessor (nameMsgId / field_0 variant).
 *
 *   Item_GetDescriptorField0 @ 0x8023DC50 (size 0x9C)
 *
 * Clamps itemDestId to [0..0x146] (sentinel index 0x146 on out-of-range).
 * In-range ids are routed through ItemAlias_DestToSource (with a 16-byte
 * alias scratch buffer on the stack -- larger than the sibling
 * Item_GetDescriptorFieldC/Field8's 8-byte buf), then indexed into
 * g_itemIdToIndexTable to obtain a slot index into the global
 * ItemDescriptor array at 0x803DC530 (stride 0x10).
 *
 * Unlike the FieldC/Field8 pair this fn also takes an `outAliasByte`
 * out-param: when non-NULL it is pre-cleared to 0, then (only if
 * itemDestId != 0) overwritten with aliasScratch[0] -- the per-alias
 * flag byte set by ItemAlias_DestToSource. The id==0 short-circuit
 * leaves *outAliasByte at the pre-cleared 0.
 *
 * Returns ItemDescriptor[descriptorIdx].nameMsgId (field_0).
 *
 * This TU is intentionally separate from Item_GetDescriptor.c (which
 * holds FieldC + Field8) because excluded fn_8023DBEC sits between
 * them in the original .text layout.  Lives in the `game` lib
 * (CW 1.3.2); `#pragma exceptions on` lets CW auto-emit the
 * extab/extabindex entries.
 */

extern int ItemAlias_DestToSource(unsigned int itemDestId, void *aliasOut);
extern unsigned int g_itemIdToIndexTable[0x148];

struct ItemDescriptor {
    unsigned int nameMsgId;
    unsigned int field_4;
    unsigned int field_8;
    unsigned int field_C;
};

extern struct ItemDescriptor lbl_803DC530[];

#pragma exceptions on

unsigned int Item_GetDescriptorField0(unsigned int itemDestId, unsigned char *outAliasByte) {
    unsigned int descriptorIndex;
    int aliasedItemId;
    unsigned char aliasScratch[16];

    if (outAliasByte != 0) {
        *outAliasByte = 0;
    }
    if (((int)itemDestId < 0) || ((int)itemDestId >= 0x147)) {
        descriptorIndex = 0x146;
    } else {
        aliasedItemId = ItemAlias_DestToSource(itemDestId & 0xff, aliasScratch);
        if ((outAliasByte != 0) && ((int)itemDestId != 0)) {
            *outAliasByte = aliasScratch[0];
        }
        descriptorIndex = g_itemIdToIndexTable[aliasedItemId];
    }
    return lbl_803DC530[descriptorIndex].nameMsgId;
}

#pragma exceptions reset
