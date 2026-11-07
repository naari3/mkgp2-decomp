#pragma inline_max_size(1000)
/* Memberwise player snapshot; the compiler preserves alignment holes. */
#pragma cplusplus on
extern "C" {
#include "game/CardLoadShadowPrivate.h"
extern void card_backup(void);

void card_force_backup_now(void)
{
    lbl_80598A60.captured = 1;
    lbl_80598A60.player = g_playerData;
    card_backup();
}
}
#pragma cplusplus reset

