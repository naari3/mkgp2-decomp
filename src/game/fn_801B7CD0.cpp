#include "game/SpritePairOwner.h"

extern "C" {
extern Sprite *lbl_806D1820;
extern int lbl_806D1824;
extern short *lbl_806D1828, *lbl_806D182C, *lbl_806D1830, *lbl_806D1834;
extern const float lbl_806D9888, lbl_806D988C;
int CreditMgr_GetCoinCount(int, int);
int CreditMgr_GetCoinsPerCredit(int);
short *fn_801A0310(Sprite *, int);
void Sprite_SetAnimParam(Sprite *, int, int);
void Sprite_Destroy(Sprite *, int);
}

static inline void SetPosition(Sprite *sprite, float x, float y) {
    sprite->x = x;
    sprite->y = y;
}

extern "C" void fn_801B7CD0(int player) {
    if (player != -1 && lbl_806D1820 != 0) return;
    if (player == -1 && lbl_806D1820 == 0) return;
    if (player != -1) {
        int coins = CreditMgr_GetCoinCount(0, player);
        int cost = CreditMgr_GetCoinsPerCredit(player);
        lbl_806D1824 = player;
        int coinsTens = coins / 10;
        int coinsUnits = coins % 10;
        int costTens = cost / 10;
        int costUnits = cost % 10;
        lbl_806D1820 = new Sprite(0x17E, 1, 0);
        lbl_806D1828 = fn_801A0310(lbl_806D1820, 0x1D63);
        lbl_806D182C = fn_801A0310(lbl_806D1820, 0x1D64);
        lbl_806D1830 = fn_801A0310(lbl_806D1820, 0x1D65);
        lbl_806D1834 = fn_801A0310(lbl_806D1820, 0x1D66);
        SetPosition(lbl_806D1820, lbl_806D9888, lbl_806D988C);
        fn_8019FF6C(lbl_806D1820, 1);
        lbl_806D1820->layer = 7;
        if (cost != -1) {
            if (coinsTens != 0) {
                *lbl_806D1828 = coinsTens + 0x1D63;
                *lbl_806D182C = coinsUnits + 0x1D63;
            } else {
                *lbl_806D1828 = -1;
                *lbl_806D182C = coinsUnits + 0x1D63;
            }
            if (costTens != 0) {
                *lbl_806D1830 = costTens + 0x1D63;
                *lbl_806D1834 = costUnits + 0x1D63;
            } else {
                *lbl_806D1830 = costUnits + 0x1D63;
                *lbl_806D1834 = -1;
            }
        } else {
            Sprite_SetAnimParam(lbl_806D1820, 0x1D62, 0x1D6D);
            *lbl_806D1828 = -1;
            *lbl_806D182C = -1;
            *lbl_806D1830 = -1;
            *lbl_806D1834 = -1;
        }
    } else {
        Sprite_Destroy(lbl_806D1820, 1);
        lbl_806D1820 = 0;
    }
}
