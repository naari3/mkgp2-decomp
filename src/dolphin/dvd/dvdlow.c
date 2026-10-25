#include <dolphin.h>
#include <dolphin/dvd.h>

/* The game replaces the rest of dvdlow.c with triforce/dvdlow.c; only this survives. */
static OSAlarm AlarmForTimeout;
static OSAlarm AlarmForBreak;

BOOL __DVDLowTestAlarm(OSAlarm* alarm) {
    if (alarm == &AlarmForBreak) {
        return TRUE;
    }
    if (alarm == &AlarmForTimeout) {
        return TRUE;
    }

    return FALSE;
}
