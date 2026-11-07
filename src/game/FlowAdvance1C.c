#include "game/FlowAdvancePrivate.h"
void fn_80246460(struct FlowAdvance1C *self, int value) {
    if (self->state < 5) self->next = value + 1;
}
static inline int IsFinished(struct FlowAdvance1C *self) { return self->state == 6; }
void fn_80246478(struct FlowAdvance1C *self) {
    if (IsFinished(self)) return;
}
