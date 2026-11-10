/* Backup_PublishShadowCopy @ 0x80074370 (size 0x21C).
 * Stamps the backup working copy with OSGetTime() and, when backup is
 * available and idle, publishes it to g_backupShadowCopy. */
#pragma use_lmw_stmw on

#include "game/BackupShadowCopy.h"

void Backup_PublishShadowCopy(void) {
    lbl_80598A60.time = OSGetTime();
    if (lbl_806D1120 != 0 && lbl_806D1128 == 0) {
        fn_80288210(0, &lbl_80598A60);
        Backup_CopyToPublished();
    }
}
