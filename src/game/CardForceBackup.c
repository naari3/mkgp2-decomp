#pragma inline_max_size(1000)
/* Memberwise player snapshot; the compiler preserves alignment holes.
 * NonMatching (82.5%): copying through a player-pointer local before setting
 * `captured` gives the target's single spill block and r31 base. Remaining:
 * the target stores `captured` (li r29,1) before the first __copy and spills
 * 0x50/0x58..0xa4 instead of 0x44.. (one fewer register in the big block). */
#pragma cplusplus on
extern "C" {
#include "game/CardLoadShadowPrivate.h"
extern void card_backup(void);

void card_force_backup_now(void)
{
    struct CardPlayerSnapshot *d = &lbl_80598A60.player;
    *d = g_playerData;
    lbl_80598A60.captured = 1;
    card_backup();
}
}
#pragma cplusplus reset

