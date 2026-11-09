#ifndef GAME_COMMON_REWARD_PICKER_PRIVATE_H
#define GAME_COMMON_REWARD_PICKER_PRIVATE_H
extern "C" {
#include "game/CardLoadShadowPrivate.h"
}
typedef CardPlayerSnapshot PlayerData;
extern "C" {
extern PlayerData g_playerData;
extern int lbl_806D02E4;
extern int lbl_804EC5E8[65];
unsigned char fn_801D6F30(PlayerData *, int, int);
int Rand15(void);
int WrapInRange(int, int, int);
int fn_80209338(int);
}
#endif
