#ifndef CXC_BUY_CARD_H
#define CXC_BUY_CARD_H
#include "game/FlowScene.h"
struct CardStep { char pad[0xC]; int done; void *seq, *fader; int state, result; };
struct RefillSingleton { char opaque[0x5C]; RefillSingleton(); };
struct CardChoicePanel {
    char pad[0x10]; int state; int pad14; int result;
    float x, y, x2, y2;
    char pad2c[0x24]; char group50[0x10]; TextManager *center;
    char pad64[8]; float offset[8];
    CardChoicePanel(int, int, int);
};
struct BuyCardStep : CardStep {
    int timeout, selection, next;
    unsigned char creditOnly; char pad2d[3];
    int retries; void *text; int coins;
    unsigned char automatic; char pad3d[3];
    int flash; void *indicator; CardChoicePanel *panel; int *kart; void *choice;
};
extern "C" {
extern const int lbl_803BFF54[];
extern const float lbl_806DA81C, lbl_806DA800;
extern RefillSingleton *lbl_806D1A88;
extern unsigned char g_playerData[];
void fn_8020A7CC(void *, int, int, int);
}
static inline RefillSingleton *BuyRefill() {
    return lbl_806D1A88 ? lbl_806D1A88 : (lbl_806D1A88 = new RefillSingleton);
}
#endif
