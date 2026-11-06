#include "game/Backup_GetMinutesSinceBoot_private.h"

static inline unsigned int CalendarSeconds(const OSCalendarTime *time)
{
    return (time->year - 2000) * 32140800
        + time->mon * 2678400 + (time->mday - 1) * 86400
        + time->hour * 3600 + time->min * 60 + time->sec;
}

#pragma use_lmw_stmw on
unsigned char Backup_GetMinutesSinceBoot(unsigned int threshold)
{
    OSCalendarTime boot;
    OSCalendarTime now;
    OSTicksToCalendarTime(lbl_80598A60.time, &boot);
    OSTicksToCalendarTime(OSGetTime(), &now);
    return (CalendarSeconds(&now) - CalendarSeconds(&boot)) / 3600 >= threshold;
}
#pragma use_lmw_stmw reset
