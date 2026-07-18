struct CardTaskPrintJob {
    int (CardTaskPrintJob::*is_running)();
};

#pragma exceptions on
extern "C" int CardTaskPrintJob_IsRunning_Thunk(CardTaskPrintJob *self) {
    return (self->*self->is_running)();
}
#pragma exceptions reset
