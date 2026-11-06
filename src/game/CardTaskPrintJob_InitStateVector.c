#include "game/CardTaskPrintJobState_private.h"

extern CardTaskPrintJobCallback lbl_803F1C68;

void CardTaskPrintJob_InitStateVector(CardTaskPrintJobState *self)
{
    self->step = lbl_803F1C68;
    self->result = 0;
    self->status = 0;
}
