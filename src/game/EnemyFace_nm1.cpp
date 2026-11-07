#include "game/EnemyFace_private.h"

void TireSprite_Load() {
    void **textures;
    TPLPalette **palettes;
    const int *resources;
    void **tluts;
    int i;
    unsigned int n;
    unsigned int k;

    DebugPrintf(lbl_803DA6A0);
    i = 0;
    textures = lbl_806D05F0;
    palettes = lbl_806D05F8;
    resources = lbl_806DB590;
    tluts = lbl_806D0600;
    for (; i < 2; i++, textures++, palettes++, resources++, tluts++) {
        if (*textures != 0) {
            return;
        }
        if (*palettes != 0) {
            return;
        }
        const char *path = ResourceTable_GetFilePathPtr(*resources);
        if (path == 0) {
            return;
        }
        TEXLoadPalette_Retry(palettes, path);
        if (*palettes == 0) {
            return;
        }
        n = (*palettes)->count;
        *textures = FUN_8003b120(n << 5);
        *tluts = FUN_8003b120(n * 0xC);
        for (k = 0; k < n; k++) {
            if (TEXGetPaletteEntry(*palettes, k)->clut) {
                TEXBindPaletteEntry_CI(*palettes, *textures, *tluts, 0, k);
            } else {
                TEXBindPaletteEntry_RGB(*palettes, *textures, k);
            }
        }
    }
    DebugPrintf(lbl_803DA6C0);
}
