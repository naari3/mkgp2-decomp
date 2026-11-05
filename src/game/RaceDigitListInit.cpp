#include "game/RaceDigitListPrivate.h"

extern "C" void fn_80247CE4(RaceDigitList *self) {
    self->count = 0;
    RaceDigitNode *end = (RaceDigitNode *)&self->last;
    end->next = end;
    end->prev = end;
}
