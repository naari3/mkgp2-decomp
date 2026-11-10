#ifndef GAME_HUDRESULTFLOWPRIVATE_H
#define GAME_HUDRESULTFLOWPRIVATE_H
#include "game/HudFlowPrivate.h"
struct HudResultFlow : HudRoot { HudResultFlow(); };
extern "C" {
extern void *HudResultFlow_data_804EEBA8[];
HudChild *fn_8021E0C0();
HudChild *fn_8024C564();
void CalcEarnedCoins();
}
#endif
