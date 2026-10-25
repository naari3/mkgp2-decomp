/*
 * 0x80218B80..0x80218D90: credit counter HUD update.
 */

#include "game/CreditHud.h"

extern "C" {
extern int lbl_806D1A5C;
extern unsigned char lbl_80598A60[];
extern const float lbl_806DAF30;
unsigned int CreditMgr_PollAcceptor(void);
int CreditMgr_GetCoinCount(int slot, int mode);
int CreditMgr_GetCoinsPerCredit(int mode);
void Sprite_AdvanceAnim(AnimSprite *s, float step);
}

void CreditHud::Update() {
    unsigned int ok = CreditMgr_PollAcceptor();
    unsigned char free = 0;
    if (ok == 0) {
        *slash = 0x1D6D;
        *coin10 = 0x1ECD;
        *coin1 = 0x1ECD;
        *per10 = 0x1ECD;
        *per1 = 0x1ECD;
    } else {
        int mode = lbl_806D1A5C;
        if (mode == 2 && lbl_80598A60[0x50] == 1) {
            free = 1;
        }
        if (mode == 3 && lbl_80598A60[0x51] == 1) {
            free = 1;
        }
        if (mode == 4 && lbl_80598A60[0x52] == 1) {
            free = 1;
        }
        int coins = CreditMgr_GetCoinCount(0, -1);
        int per = CreditMgr_GetCoinsPerCredit(-1);
        if (free == 1) {
            per = 0;
        }
        *slash = 0x1D62;
        *coin10 = (coins / 10) % 10 + 0x1D63;
        *coin1 = coins % 10 + 0x1D63;
        *per10 = (per / 10) % 10 + 0x1D63;
        *per1 = per % 10 + 0x1D63;
        if (*coin10 == 0x1D63) {
            *coin10 = 0x1ECD;
        }
        if (*per10 == 0x1D63) {
            *per10 = *per1;
            *per1 = 0x1ECD;
        }
    }
    Sprite_AdvanceAnim(sprite.p, lbl_806DAF30);
}
