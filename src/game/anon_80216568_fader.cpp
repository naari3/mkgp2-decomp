#include "game/FlowScene.h"

/* Construct the canonical inline type at the caller-provided address. */
inline void *operator new(unsigned long, void *p) { return p; }
extern "C" FlowFaderI *fn_80218B28(FlowFaderI *p) {
    return new (p) FlowFaderI;
}
