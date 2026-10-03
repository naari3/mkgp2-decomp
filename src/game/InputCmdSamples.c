#include "game/InputCmd.h"

extern const float lbl_806D2958;
extern int InputCmd_DetectGesturePattern(InputCmdView *);
extern int WrapInRange(int value, int lo, int hi);

static inline void InputCmd_ClearSamples(InputCmdView *self) {
    int i;
    for (i = self->capacity; i-- > 0;) {
        InputCmdSampleView *sample = &self->samples[i];
        sample->x = lbl_806D2958;
        sample->y = lbl_806D2958;
        sample->z = lbl_806D2958;
        sample->code = 0;
        sample->live = 0;
    }
}

void InputCmd_TickAndDetectAndClear(InputCmdView *self) {
    self->detected = 0;
    if (self->cooldown > 0) {
        self->cooldown--;
        InputCmd_ClearSamples(self);
    } else {
        self->detected = InputCmd_DetectGesturePattern(self);
        if (self->detected == 1) {
            InputCmd_ClearSamples(self);
        }
    }
}

void InputCmd_PushSample(InputCmdView *self, float x, float y, float z, int code) {
    InputCmdSampleView *sample = &self->samples[self->writeIndex];
    sample->x = x;
    sample->y = y;
    sample->z = z;
    sample->code = code;
    sample->live = 1;
    self->writeIndex = WrapInRange(self->writeIndex + 1, 0, self->capacity - 1);
    if (self->writeIndex == self->readIndex) {
        self->readIndex = WrapInRange(self->readIndex + 1, 0, self->capacity - 1);
    }
}
