/*
 * Daily clock / operation clock helpers, 0x8008C930..0x8008CB3C.
 */

#include "game/types/OSCalendarTime.h"

long long OSGetTime(void);
void OSTicksToCalendarTime(long long ticks, OSCalendarTime *td);

#include "game/types/OperationClockState.h"

static inline unsigned int SecondsOfDay(void) {
    OSCalendarTime t;

    OSTicksToCalendarTime(OSGetTime(), &t);
    return t.hour * 3600 + t.min * 60 + t.sec;
}

#pragma exceptions on

int DailyClock_GetCurrentSeconds(void *clock) {
    return SecondsOfDay();
}

int OperationClockState_CommitDelta(OperationClockState *st) {
    OSCalendarTime t;

    if (st->state != 2) {
        return 0;
    }
    OSTicksToCalendarTime(OSGetTime(), &t);
    st->state = 3;
    st->deltaSeconds = t.hour * 3600 + t.min * 60 + t.sec;
    if (st->deltaSeconds < st->start) {
        st->deltaSeconds += 86400;
    }
    st->deltaSeconds -= st->start;
    return 1;
}

int OperationClockState_RefreshCurrent(OperationClockState *st) {
    if (st->state != 2) {
        return 0;
    }
    st->currentSeconds = SecondsOfDay();
    if (st->currentSeconds < st->start) {
        st->currentSeconds += 86400;
    }
    st->currentSeconds -= st->start;
    return 1;
}

int OperationClockState_StartTick(OperationClockState *st) {
    OSCalendarTime t;

    if (st->state != 1) {
        return 0;
    }
    OSTicksToCalendarTime(OSGetTime(), &t);
    st->state = 2;
    st->start = t.hour * 3600 + t.min * 60 + t.sec;
    return 1;
}

#pragma exceptions reset

void OperationClockState_Reset(OperationClockState *st) {
    st->state = 1;
    st->start = 0;
    st->currentSeconds = 0;
    st->deltaSeconds = 0;
}
