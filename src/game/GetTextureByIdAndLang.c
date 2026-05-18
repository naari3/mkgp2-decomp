/*
 * GetTextureByIdAndLang @ 0x8013C2D4 (size 0x60).
 *
 * 2D table lookup keyed by (id, lang). When id is out of range (>= 0xA0)
 * a sdata fallback pointer is returned. When lang is negative the auto
 * language is resolved via isJapanese() (0 = JP, 1 = EN).
 *
 * Table layout: lbl_8048E548 = void *[0xA0][2] (size 0x500). The id*2+lang
 * computation is expressed as `id*8 + lang*4` byte offsets at the asm level
 * via slwi/add/lwzx.
 *
 * Has extab/extabindex entries (Large Frame flag set). CW auto-emits them
 * when wrapped in #pragma exceptions on/reset, same pattern as HUD_*.
 */

extern int isJapanese(void);
extern void *lbl_806CF640;
extern void *lbl_8048E548[0xA0][2];

#pragma exceptions on
void *GetTextureByIdAndLang(unsigned int id, int lang) {
    if (id >= 0xA0) {
        return lbl_806CF640;
    }
    if (lang < 0) {
        lang = isJapanese();
    }
    return lbl_8048E548[id][lang];
}
#pragma exceptions reset
