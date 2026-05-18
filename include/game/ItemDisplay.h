/*
 * ItemDisplay singleton (game/ItemDisplay_*).
 *
 * Struct layout from Ghidra bmp_output (size 0x14):
 *   +0x00  Sprite *sprite
 *   +0x04  int     state
 *   +0x08  (unknown, gap)
 *   +0x0C  (unknown, gap)
 *   +0x10  int     pendingItemId
 *
 * Only fields touched by ItemDisplay_Stop are named; the gap region
 * (+0x08..+0x10) is opaque. Padding stays as raw bytes so the struct
 * size matches Ghidra (0x14) without inventing field semantics.
 */

#ifndef GAME_ITEMDISPLAY_H
#define GAME_ITEMDISPLAY_H

typedef struct Sprite Sprite;

typedef struct ItemDisplay {
    /* +0x00 */ Sprite *sprite;
    /* +0x04 */ int state;
    /* +0x08 */ unsigned char _pad08[0x10 - 0x08];
    /* +0x10 */ int pendingItemId;
} ItemDisplay;

#endif /* GAME_ITEMDISPLAY_H */
