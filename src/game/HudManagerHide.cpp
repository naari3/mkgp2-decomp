/*
 * HUD manager: start the slide-out of the visible parts @ 0x802537E8..0x80253B14.
 */

#include "game/HudManager.h"

extern "C" int g_gameMode;

void HudManager::HideAll() {
    int gm = g_gameMode;
    Delay(5, 0);
    Delay(12, 0);
    Delay(8, 0);
    Delay(0, 0);
    Delay(9, 0);
    Delay(21, 0);
    Delay(22, 0);
    if (gm == 1) {
        Delay(10, 0);
        Delay(3, 0);
        Delay(6, 5);
        Delay(11, 0);
    } else if (gm == 2) {
        Delay(4, 0);
        Delay(10, 0);
        Delay(3, 0);
        Delay(11, 0);
        Delay(6, 0);
        Delay(22, 0);
    } else {
        Delay(4, 0);
        Delay(10, 0);
        Delay(7, 5);
        Delay(3, 5);
        Delay(6, 10);
        Delay(11, 0);
    }
}
