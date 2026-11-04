#include "game/FlowCountdown.h"

extern "C" CountdownBanner *fn_8020007C(int type, int layer, int id) {
    return new CountdownBanner(type, layer, id);
}

CountdownBanner::~CountdownBanner() {
}
