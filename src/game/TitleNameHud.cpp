/*
 * Player title name HUD part: ctor, dtor and factory @ 0x80252D90..0x80253294.
 * Update/Draw/SetDelay live in TitleNameHudUpdate.cpp; the resource
 * preload/free helpers in between are fn_80252D48.c and fn_80252D6C.c.
 */

#include "game/TitleNameHud_unlock_private.h"

extern "C" TitleNameHud *fn_80252D90(int layer) {
    return new TitleNameHud(layer);
}

TitleNameHud::~TitleNameHud() {
    for (int i = 0; i < count; i++) {
        SpriteHandle_Destroy(sprites[i]);
    }
}
