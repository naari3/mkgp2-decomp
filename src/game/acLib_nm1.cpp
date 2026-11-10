/* acLib JVS coin and service input polling. */
#include "game/acLib_private.h"

static inline unsigned int UpdateCoinHistory(unsigned int coin, unsigned int service) {
    unsigned int pressed;
    unsigned int *cnt;
    int i;
    int prev;
    long cur;
    acLib_nm1_bss_80679E34[acLib_tail_bss_806D1AD4] = coin;
    if (++acLib_tail_bss_806D1AD4 >= 8) {
        acLib_tail_bss_806D1AD4 = 0;
    }
    cur = acLib_tail_bss_806D1AD4;
    {
        int t = cur - 1;
        prev = 7;
        if (t >= 0) {
            prev = t;
        }
    }
    cnt = acLib_nm1_bss_80679E54;
    cur -= 2;
    for (i = 0; i < 32; i++) {
        unsigned int mask = 1 << i;
        if (!(acLib_nm1_bss_80679E34[prev] & mask)) {
            int k = cur;
            int n = 7;
            int j;
            for (j = 0; j < 7; j++) {
                if (k < 0) {
                    k = 7;
                }
                if (acLib_nm1_bss_80679E34[k] & mask) {
                    n--;
                }
                k--;
            }
            if (n <= 0) {
                cnt[i] = 8;
            }
        }
    }

    pressed = 0;
    if (acLib_tail_bss_806D1AD0 == 0) {
        for (int pulse = 0; pulse < 32; pulse++) {
            unsigned int mask = 1 << pulse;
            if (!(service & mask)) {
                if (cnt[pulse] != 0) {
                    cnt[pulse]--;
                    pressed |= mask;
                }
            } else {
                cnt[pulse] = 0;
            }
        }
    }
    return pressed;
}

extern "C" int fn_80255154(int board, int id) {
    int a;
    unsigned char *data;
    unsigned char b;
    unsigned char players;
    unsigned char bits;
    unsigned int coin;
    unsigned int u;
    unsigned int service;
    unsigned int pressed;

    board = (unsigned char)board;
    if (fn_8028AA40(board, &a, &b)) {
        return 1;
    }
    if (fn_8028AD94(board, &data, &players, &bits)) {
        return 1;
    }
    bits = (bits + 7) / 8;
    coin = 0;
    service = 0;
    for (u = 0; u < players; u++) {
        unsigned char v = data[u * bits + 1];
        if (v & 0x40) {
            coin |= 1 << (u + 4);
        }
        if (v & 0x80) {
            service |= 1 << (u + 4);
        }
    }

    pressed = UpdateCoinHistory(coin, service);
    fn_802895E4(id, b, a, pressed);
    return 0;
}
