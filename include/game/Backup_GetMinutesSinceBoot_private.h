#ifndef GAME_BACKUP_MINUTES_PRIVATE_H
#define GAME_BACKUP_MINUTES_PRIVATE_H

#include "game/BackupShadowCopy.h"

/* OSCalendarTime layout from dolphin/os.h; that umbrella header also pulls
 * in libc headers unavailable under this game TU's compiler include flags. */
typedef struct OSCalendarTime {
    int sec, min, hour, mday, mon, year, wday, yday, msec, usec;
} OSCalendarTime;
extern void OSTicksToCalendarTime(OSTime ticks, OSCalendarTime *td);

#endif
