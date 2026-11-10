#ifndef GAME_TYPES_OSCALENDARTIME_H
#define GAME_TYPES_OSCALENDARTIME_H

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

#endif /* GAME_TYPES_OSCALENDARTIME_H */
