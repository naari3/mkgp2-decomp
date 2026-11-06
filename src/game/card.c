/* card_backup @ 0x800746A8: capture calendar time, then publish the backup. */
#pragma use_lmw_stmw on
#include "game/Backup_GetMinutesSinceBoot_private.h"

void card_backup(void)
{
    OSCalendarTime calendar;
    OSTicksToCalendarTime(OSGetTime(), &calendar);
    *(OSCalendarTime *)&lbl_80598A60.blk064.w[1] = calendar;
    if (lbl_806D1120 != 0 && lbl_806D1128 == 0) {
        fn_80288210(0, &lbl_80598A60);
        Backup_CopyToPublished();
    }
}
#pragma use_lmw_stmw reset
