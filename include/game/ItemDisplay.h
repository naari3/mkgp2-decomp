/*
 * ItemDisplay singleton (game/ItemDisplay_*).
 *
 * Struct layout (size 0x14). Field offsets verified against
 * ItemDisplay_GetOrCreate @ 0x8020AE A8 store sequence:
 *   +0x00  Sprite *sprite          (stw r5=NULL, 0x0)
 *   +0x04  int     state           (stw r5=0,    0x4)
 *   +0x08  int     styleId         (stw r4=4,    0x8)
 *   +0x0C  int     currentItemId   (stw r5=0,    0xC)
 *   +0x10  int     pendingItemId   (stw r0=-1,   0x10)
 *
 * styleId / currentItemId semantics are inferred from the literal
 * constants written by GetOrCreate (style=4, currentItem=0) and the
 * pendingItemId reset to -1 already known from ItemDisplay_Stop.
 */

#ifndef GAME_ITEMDISPLAY_H
#define GAME_ITEMDISPLAY_H

typedef struct Sprite Sprite;

typedef struct ItemDisplay {
    /* +0x00 */ Sprite *sprite;
    /* +0x04 */ int state;
    /* +0x08 */ int styleId;
    /* +0x0C */ int currentItemId;
    /* +0x10 */ int pendingItemId;
} ItemDisplay;

#endif /* GAME_ITEMDISPLAY_H */
