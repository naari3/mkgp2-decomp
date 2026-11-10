/* Backup_PublishShadowCopy_Inline @ 0x80075470 (size 0x220).
 * Publishes the backup working copy (lbl_80598A60) to g_backupShadowCopy when
 * backup is available and idle; returns 1 on publish, 0 otherwise. */
#pragma use_lmw_stmw on

#include "game/BackupShadowCopy.h"

int Backup_PublishShadowCopy_Inline(void) {
    if (lbl_806D1120 == 0) {
        return 0;
    }
    if (lbl_806D1128 != 0) {
        return 0;
    }
    fn_80288210(0, &lbl_80598A60);
    Backup_CopyToPublished();
    return 1;
}
