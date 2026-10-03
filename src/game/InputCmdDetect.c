#include "game/InputCmd.h"

extern int WrapInRange(int value, int low, int high);
extern void DebugPrintf(const char *format, ...);
extern const char lbl_802EDD58[];
extern const char lbl_802EDD78[];
extern const char lbl_806D2968[8];
extern const float lbl_806D295C;
extern const float lbl_806D2960;
extern const float lbl_806D2964;
extern const float lbl_806D2970[2];

static inline int ScanMode0(InputCmdView *self)
{
    int phase = 0;
    int budget = 15;
    int index = WrapInRange(self->writeIndex - 1, 0, self->capacity - 1);
    while (index != self->readIndex) {
        InputCmdSampleView *sample = &self->samples[index];
        float y, z;
        if (!sample->live) return 0;
        y = sample->y;
        z = sample->z;
        switch (phase) {
        case 0:
            if (y > lbl_806D2964 && z > lbl_806D2960) {
                budget = 15;
                ++phase;
            }
            break;
        case 1:
            if (y < lbl_806D2970[0] && z < lbl_806D2964) return 1;
            break;
        default: return 0;
        }
        if (budget-- < 0) return 0;
        index = WrapInRange(index - 1, 0, self->capacity - 1);
    }
    return 0;
}

static inline int ScanMode1(InputCmdView *self)
{
    int phase = 0;
    int budget = 15;
    int index = WrapInRange(self->writeIndex - 1, 0, self->capacity - 1);
    while (index != self->readIndex) {
        InputCmdSampleView *sample = &self->samples[index];
        float y, z;
        if (!sample->live) return 0;
        y = sample->y;
        z = sample->z;
        switch (phase) {
        case 0:
            if (y > lbl_806D2964 && z > lbl_806D2960) {
                budget = 15;
                ++phase;
            }
            break;
        case 1:
            if (y > lbl_806D2964 && z < lbl_806D2964) return 1;
            break;
        default:
            DebugPrintf(lbl_802EDD58, lbl_806D2968, 0xF1);
            return 0;
        }
        if (budget-- < 0) return 0;
        index = WrapInRange(index - 1, 0, self->capacity - 1);
    }
    return 0;
}

static inline int ScanMode2(InputCmdView *self)
{
    int phase = 0;
    int budget = 15;
    int index = self->writeIndex;
    while (index != self->readIndex) {
        switch (phase) {
        case 3:
            if (self->samples[index].y < lbl_806D295C) return 1;
            break;
        case 2:
            if (self->samples[index].y > lbl_806D2960) {
                budget = 15;
                ++phase;
            }
            break;
        case 1:
            if (self->samples[index].y < lbl_806D295C) {
                budget = 15;
                ++phase;
            }
            break;
        case 0:
            if (self->samples[index].y > lbl_806D2960) {
                budget = 15;
                ++phase;
            }
            break;
        default: return 1;
        }
        if (budget-- < 0) return 0;
        index = WrapInRange(index - 1, 0, self->capacity - 1);
    }
    return 0;
}

int InputCmd_DetectGesturePattern(InputCmdView *self)
{
    int result;
    /* This call site treats the opaque +0x14 storage as a signed enum. */
    switch ((int)self->config) {
    case 0: result = ScanMode0(self); break;
    case 1: result = ScanMode1(self); break;
    case 2: result = ScanMode2(self); break;
    default:
        DebugPrintf(lbl_802EDD78, lbl_806D2968, 0x8E);
        result = ScanMode0(self);
        break;
    }
    return result;
}
