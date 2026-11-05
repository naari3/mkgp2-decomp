#include "game/SelectionSlotsPrivate.h"

void fn_80242E04(SelectionSlots *self) {
    int i;
    for (i = 0; i < 8; ++i) {
        SelectionSlot *slot = self->slots[self->order[i]];
        if (slot) {
            void *display = slot->display;
            unsigned char enabled = slot->enabled;
            if (display) fn_80230ED4(display, enabled);
        }
    }
}
