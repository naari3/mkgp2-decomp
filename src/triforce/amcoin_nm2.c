#include <triforce/amcoin_private.h>
#include <stdio.h>
#include <string.h>

s32 fn_8028A3EC(CoinConfig* dst, u8* src) {
    CoinConfig tmp;
    const CoinTableEntry* t;
    u8 flags;

    if (src == NULL || dst == NULL) {
        return 1;
    }
    memcpy(&tmp, dst, sizeof(CoinConfig));
    if (src[0] == 0) {
        return 0;
    }
    flags = src[1];
    if (flags & 2) {
        tmp.separate = flags & 1;
    }
    flags >>= 2;
    if (flags & 2) {
        tmp.commonService = flags & 1;
    }
    flags >>= 2;
    if (flags & 2) {
        tmp.serviceSplit = flags & 1;
    }
    tmp.coinSetting = src[3];
    if (tmp.coinSetting == 10) {
        tmp.freePlay = 1;
    } else {
        tmp.freePlay = 0;
    }
    tmp.coinMul[0] = src[4];
    tmp.coinMul[1] = src[5];
    tmp.bonusDiv = src[6];
    tmp.coinsPerCredit = src[7];
    if (tmp.coinSetting != 0) {
        /* fakematch (hand): natural code is `&CoinTable[tmp.coinSetting]`. Read
           through a cast, the second load is not a frontend CSE temp but a
           backend one numbered after the src[4..7] loads (regfix diag). */
        t = &CoinTable[*(u8 *)&tmp.coinSetting];
        tmp.coinMul[0] = t->mul0;
        if (tmp.separate == 0 && t->perCredit != 1) {
            tmp.coinMul[1] = t->mul1;
        }
        tmp.bonusDiv = t->bonusDiv;
        tmp.coinsPerCredit = t->perCredit;
    }
    tmp.startCost[0] = src[8];
    tmp.startCost[1] = src[9];
    tmp.startCost[2] = src[10];
    tmp.startCost[3] = src[11];
    tmp.startCost[4] = src[12];
    tmp.startCost[5] = src[13];
    tmp.startCost[6] = src[14];
    tmp.startCost[7] = src[15];
    if (!fn_80289ED8(&tmp)) {
        return 2;
    }
    memcpy(dst, &tmp, sizeof(CoinConfig));
    return 0;
}
