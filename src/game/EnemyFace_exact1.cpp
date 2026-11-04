#include "game/EnemyFace_private.h"

void TireSprite_Release() {
    for (int i = 0; i < 2; i++) {
        if (lbl_806D05F8[i]) {
            TEXReleasePalette(&lbl_806D05F8[i]);
            lbl_806D05F8[i] = 0;
        }
        if (lbl_806D05F0[i]) {
            MemoryManager_Free(lbl_806D05F0[i]);
            lbl_806D05F0[i] = 0;
        }
        if (lbl_806D0600[i]) {
            MemoryManager_Free(lbl_806D0600[i]);
            lbl_806D0600[i] = 0;
        }
    }
}
