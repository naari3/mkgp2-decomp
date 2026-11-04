#include "game/anon_8021F088_private.h"

void clCSSceneCoinMilage::Destroy() {
    delete this;
}

extern "C" clCSSceneCoinMilage *fn_80223500(void) {
    return new clCSSceneCoinMilage;
}
