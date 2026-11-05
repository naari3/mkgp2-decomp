#ifndef GAME_RANKING_MGR_PRIVATE_H
#define GAME_RANKING_MGR_PRIVATE_H
extern "C" {
#include "game/AISpeedPrivate.h"
}
class RankingThinkBox {
public:
    virtual void Update();
    virtual void UpdateKart(int);
    void *lastCar;
    void *firstCar;
};
struct RankingManager { RankingThinkBox *box; };
extern "C" {
extern int g_gameMode;
extern void *Read_U32[8];
extern void *lbl_806D1928;
unsigned char IsRaceStarted();
void *GetPlayerCarBySlot(int);

void fn_801DC774();
int fn_801E6DDC(void *);
void fn_80208FA0(void *, int, int);
}
#endif
