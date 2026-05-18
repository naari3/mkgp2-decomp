/*
 * IsCardValid @ 0x8023F65C (size 0xB8).
 *
 * Validates the local PCB's card slot state. Returns 1 if the card is OK to
 * proceed, 0 if validation fails. Reads a small status block at
 * lbl_80598A60 (offsets 0x20/0x21/0x23/0x24) and consults
 * PcbSlot_GetCharIdByte(0) / PcbSlot_GetByIndex(0) for further checks.
 *
 * Behaviour (per Ghidra / disasm):
 *   - state = (signed char)p[0x20];
 *   - if (state == 2) return 0;          // disabled
 *   - if (state == 1) {                   // normal card path
 *         if (p[0x24] == 0) return 0;
 *         if (p[0x23] == 0) return 0;
 *         if (p[0x21] != 1 &&
 *             PcbSlot_GetCharIdByte(0) > 0 &&
 *             PcbSlot_GetCharIdByte(0) < 0x35 &&
 *             ((PcbSlot_GetByIndex(0)[3] >> 4) & 1) == 0) {
 *             return 0;
 *         }
 *     }
 *   - return 1;
 *
 * Note: PcbSlot_GetCharIdByte(0) is called twice in the && chain — target asm
 * has two separate `bl` instructions in sequence, no value caching.
 *
 * extab/extabindex entries are present in the target (Large Frame, size 0xB8,
 * header word 0x00080000). Emitted via #pragma exceptions on/reset so CW
 * auto-generates them.
 */

extern unsigned char lbl_80598A60[];

extern unsigned int PcbSlot_GetCharIdByte(int pcbIdx);
extern unsigned char *PcbSlot_GetByIndex(int pcbIdx);

#pragma exceptions on
unsigned int IsCardValid(void) {
    unsigned char *p = lbl_80598A60;
    int state = (signed char)p[0x20];

    if (state == 2) {
        return 0;
    }
    if (state == 1) {
        if (p[0x24] == 0) {
            return 0;
        }
        if (p[0x23] == 0) {
            return 0;
        }
        if ((int)(signed char)p[0x21] != 1 &&
            (int)PcbSlot_GetCharIdByte(0) > 0 &&
            (int)PcbSlot_GetCharIdByte(0) < 0x35 &&
            ((PcbSlot_GetByIndex(0)[3] >> 4) & 1) == 0) {
            return 0;
        }
    }
    return 1;
}
#pragma exceptions reset
