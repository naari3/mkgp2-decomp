#include "game/types/pmf.h"
struct CardTaskPrintJob;
PMF_TYPE(CardTaskPrintJobIsRunning, CardTaskPrintJob, int, ());
struct CardTaskPrintJob {
    CardTaskPrintJobIsRunning is_running;
};

#pragma exceptions on
extern "C" int CardTaskPrintJob_IsRunning_Thunk(CardTaskPrintJob *self) {
    return PMF_CALL(self, self->is_running)();
}
#pragma exceptions reset
