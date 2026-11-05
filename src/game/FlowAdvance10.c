#include "game/FlowAdvancePrivate.h"
void fn_80245E50(struct FlowAdvance10 *self, int value) {
    if (self->state < 4) self->next = value + 1;
}
void fn_80245E68(void) {}
