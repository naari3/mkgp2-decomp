/*
 * ISESlot_Deactivate @ 0x80049D0C (size 0x6C, 27 instr).
 *
 * Slot teardown routine. Returns 0 immediately if the slot is already
 * inactive; otherwise, if the slot kind at +0x14 is not 0x51 and the
 * ItemObject pointer at +0x18 is non-NULL, call ItemObject_SetByte18c
 * (ItemObject_SetByte18c) on that ItemObject with value 2, then clear the slot
 * pointer at +0x18 and the active flag at +0x4, and return 1.
 *
 * Slot layout used here (partial):
 *   +0x04  u8   active flag (lbz / cmplwi unsigned compare)
 *   +0x14  int  kind/type (compared signed against 0x51)
 *   +0x18  void*  item pointer (ItemObject *)
 *
 * Built with CW 1.3.2 + `-Cpp_exceptions on` so the extab/extabindex pair
 * (0x800068B0 / 0x80020174) is auto-emitted with Saved GPR r31, Large
 * Frame flag (0x08080000 / 0x00000000).
 */

extern void ItemObject_SetByte18c(void *item, int val); /* ItemObject_SetByte18c */

#pragma exceptions on
int ISESlot_Deactivate(void *slot) {
    if (*((unsigned char *)slot + 4) == 0) {
        return 0;
    }
    if (*(int *)((char *)slot + 0x14) != 0x51 &&
        *(void **)((char *)slot + 0x18) != 0) {
        ItemObject_SetByte18c(*(void **)((char *)slot + 0x18), 2);
    }
    *(void **)((char *)slot + 0x18) = 0;
    *((unsigned char *)slot + 4) = 0;
    return 1;
}
#pragma exceptions reset
