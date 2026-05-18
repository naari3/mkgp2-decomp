/* LUT_Sin12Bit
 *
 * 0x80186998 (size 0x30). 12-bit indexed lookup into a 4096-entry float
 * sine LUT. The input angle is scaled, truncated to int (fctiwz + stfd /
 * lwz idiom for single-precision casts under CW 1.3.2), masked to 12 bits,
 * and used to index the table.
 *
 * Has extab/extabindex entry (large-frame flag from the stack-allocated
 * fctiwz scratch slot), so wrap with #pragma exceptions on / reset to let
 * CW auto-emit the singleton extab + extabindex entries (one each).
 */

extern const float lbl_806D9270;
extern const float lbl_80491988[];

#pragma exceptions on
float LUT_Sin12Bit(float angle) {
    return lbl_80491988[(int)(lbl_806D9270 * angle) & 0xFFF];
}
#pragma exceptions reset
