#include "game/anon_80218F40_private.h"

extern "C" MinimapHud *fn_80219900(int unused, int layer) {
    return new MinimapHud(unused, layer);
}
