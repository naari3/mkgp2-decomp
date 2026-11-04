#include "game/FlowYesNo.h"

extern "C" void fn_80204740(VObject *obj) {
    delete obj;
}

extern "C" YesNoTask *fn_80204778(int kind, unsigned char defYes, int layer, int id) {
    return new YesNoTask(kind, defYes, layer, id);
}
