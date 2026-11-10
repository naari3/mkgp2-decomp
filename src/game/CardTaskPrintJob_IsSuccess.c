typedef unsigned int u32;

#include "game/types/CardTaskPrintJob.h"

unsigned char CardTaskPrintJob_IsSuccess(CardTaskPrintJob *self)
{
    return self->status == 0;
}
