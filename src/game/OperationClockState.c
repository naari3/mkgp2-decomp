/*
 * Daily clock / operation clock helpers, 0x8008C930..0x8008CB3C.
 */

typedef struct OSCalendarTime {
    int sec;
    int min;
    int hour;
    int mday;
    int mon;
    int year;
    int wday;
    int yday;
    int msec;
    int usec;
} OSCalendarTime;

long long OSGetTime(void);
void OSTicksToCalendarTime(long long ticks, OSCalendarTime *td);

typedef struct OperationClockState {
    int state; /* 0 idle, 1 ready, 2 ticking, 3 committed */
    unsigned int start; /* 0x04, seconds of day */
    unsigned int current; /* 0x08 */
    unsigned int delta; /* 0x0C */
} OperationClockState;

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
    st->delta = t.hour * 3600 + t.min * 60 + t.sec;
    if (st->delta < st->start) {
        st->delta += 86400;
    }
    st->delta -= st->start;
    return 1;
}

int OperationClockState_RefreshCurrent(OperationClockState *st) {
    if (st->state != 2) {
        return 0;
    }
    st->current = SecondsOfDay();
    if (st->current < st->start) {
        st->current += 86400;
    }
    st->current -= st->start;
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
    st->current = 0;
    st->delta = 0;
}
