/*
 * game/ItemSelect.c
 *
 * Item-slot manipulation helpers for the player-side item selection state.
 *
 * Both functions operate on an array of 8-byte entries. The asm shows
 * three accessed offsets but the entry stride is 8 bytes; field_0 is
 * unread here and the +4/+8 fields are the slot's stored values:
 *
 *   struct SlotEntry {   // 8 bytes
 *       int field_0;     // +0x0  (unread in these helpers)
 *       int itemId;      // +0x4  (compared / written)
 *       int slot8;       // +0x8  (written; lives in next entry's +0x0)
 *   };
 *
 * Note: SlotEntry is laid out without alignment for the +0x8 field
 * because each entry is 8 bytes; the +0x8 store actually writes the
 * next entry's +0x0. This matches the asm pattern in the AddSlotItem
 * helper.
 *
 * The number of usable slots depends on a global mode flag at
 * lbl_806CF110 (sdata): when == 1, the loop bound is 4 (maxSlot=3);
 * otherwise the loop bound is 6 (maxSlot=5).
 *
 * Field names below are tentative (no Ghidra struct established yet);
 * offsets are verified against target asm:
 *   ItemSelect_GetSlotItemId @ 0x80060D40 (size 0x40)
 *   ItemSelect_AddSlotItem   @ 0x80060D80 (size 0x64)
 */

typedef struct SlotEntry {
    int field_0;
    int itemId;
} SlotEntry;

extern int lbl_806CF110;

int ItemSelect_GetSlotItemId(SlotEntry *arr, int idx) {
    int maxSlot;
    if (idx <= -1) {
        maxSlot = (lbl_806CF110 == 1) ? 3 : 5;
        if (maxSlot + 1 <= idx) {
            return -1;
        }
    }
    return arr[idx].itemId;
}

int ItemSelect_AddSlotItem(SlotEntry *arr, int itemId, int slot8) {
    SlotEntry *cursor = arr;
    int mode = lbl_806CF110;
    int i = 0;
    while (i < ((mode == 1) ? 3 : 5) + 1) {
        if (cursor->itemId == 0) {
            arr[i].itemId = itemId;
            (&arr[i].itemId)[1] = slot8;
            return 1;
        }
        cursor++;
        i++;
    }
    return 0;
}
