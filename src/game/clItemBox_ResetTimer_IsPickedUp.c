/* clItemBox timer reset and picked-up state query. */

#include "game/types/clItemBox.h"

extern const float lbl_806D29A8;

void clItemBox_ResetTimer(clItemBox *self)
{
    self->timer = lbl_806D29A8;
}

int clItemBox_IsPickedUp(clItemBox *self)
{
    return self->state == 3;
}
