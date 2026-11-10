#ifndef GAME_RACE_CONFIG_801F_PRIVATE_H
#define GAME_RACE_CONFIG_801F_PRIVATE_H
#include "game/TestMenuPage.h"
/* The older menu header discards this getter's return value. Keep its
 * layout declarations while supplying the getter signature used here. */
#define fn_801F98CC fn_801F98CC_legacy_declaration
#include "game/MenuModeLane_private.h"
#undef fn_801F98CC
typedef MenuScene RaceConfig801F;
struct RaceItem801F {
    char reserved0[5];
    signed char category;
    char reserved6[6];
    const char *name;
};
extern "C" {
void *fn_801F98CC();
void OverlayText(int, int, int, const char *, ...);
extern const char DebugOverlay_RaceConfig_rodata_803BE6C0[];

extern const char lbl_806DA68C[3];
extern const char *DebugOverlay_RaceConfig_data_806D0064[2], *DebugOverlay_RaceConfig_data_806D006C[2];
const char *DebugOverlay_GetCupLabel(int);
const char *DebugOverlay_GetLongRoundLabel(int);
const char *DebugOverlay_GetDaytimeLabel(int);
const char *GetCharacterName(int);
RaceItem801F *GetItemDataEntry_Bounded(int);
void fn_8023E2F8(void *);
}
#endif
