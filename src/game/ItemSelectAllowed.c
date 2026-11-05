#include "game/ItemSelectAllowedPrivate.h"

unsigned char IsItemSelectAllowed(void) {
    const struct ItemSelectionTable *table = &lbl_803DC378;
    struct ItemSelectionDefaults selected = table->defaults;
    int cup, round;
    lbl_806D1264[0] = selected.values[0];
    lbl_806D1264[1] = selected.values[1];
    lbl_806D1264[2] = selected.values[2];
    DebugPrintf(table->roundFormat, IsSpecialItemRound() == 1);
    DebugPrintf(table->modeFormat, lbl_806D12AD == 1);
    if (IsSpecialItemRound() == 1 && lbl_806D12AD == 1) return 1;
    cup = g_cupId;
    round = g_roundIndex;
    selected.values[0] = SelectRoundItem(table, cup, round, 0);
    selected.values[1] = SelectRoundItem(table, cup, round, 1);
    selected.values[2] = SelectRoundItem(table, cup, round, 2);
    lbl_806D1264[0] = selected.values[0];
    lbl_806D1264[1] = selected.values[1];
    lbl_806D1264[2] = selected.values[2];
    return 0;
}
