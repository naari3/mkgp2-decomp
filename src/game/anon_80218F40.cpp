#include "game/anon_80218F40_private.h"


void MinimapHud::Start(int n) {
    if (state < 4) {
        delay = n + 1;
    }
}

void MinimapHud::Draw() {
}
