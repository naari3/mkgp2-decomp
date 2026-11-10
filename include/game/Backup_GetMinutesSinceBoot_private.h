#ifndef GAME_BACKUP_MINUTES_PRIVATE_H
#define GAME_BACKUP_MINUTES_PRIVATE_H

#include "game/BackupShadowCopy.h"

/* OSCalendarTime layout from dolphin/os.h; that umbrella header also pulls
 * in libc headers unavailable under this game TU's compiler include flags. */
#include "game/types/OSCalendarTime.h"
extern void OSTicksToCalendarTime(OSTime ticks, OSCalendarTime *td);

#endif
