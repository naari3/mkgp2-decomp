/*
 * acLib init @ 0x80255640..0x802557B4: resets the coin history kept for
 * fn_80255154 (acLibMedia.cpp), starts the JVS driver and records which
 * board ports carry the player inputs.
 */

typedef int (*AcLibResetHook)(unsigned int error);

struct AcLibState {
    int busy;
    unsigned char port0;
    unsigned char port1;
    char pad06[2];
    AcLibResetHook onReset;
    unsigned int coinHistory[8];
    unsigned int coinCount[32];
};

extern "C" {
extern AcLibState lbl_80679E28;
extern int lbl_806D1AD0;
extern int lbl_806D1AD4;
extern void *lbl_806D0A90;
void *memset(void *dst, int c, unsigned long n);
int fn_80294810(int a, int b, int c);
int fn_8028BAD0(void);
unsigned char fn_8028B0B4(void);
void fn_80289C68(int a, int b);
}

extern "C" int fn_80255640(int a, int b, int c) {
    AcLibState *st = &lbl_80679E28;
    unsigned int *hist = st->coinHistory;
    unsigned int *count = st->coinCount;
    int i;
    int boards;
    int ret;
    lbl_806D1AD0 = 0;
    for (i = 0; i < 8; i++) {
        hist[i] = 0;
        count[i] = 0;
    }
    lbl_806D1AD4 = 0;
    if (lbl_806D0A90 == 0) {
        return 1;
    }
    memset(st, 0, 0xC);
    st->busy = a;
    ret = fn_80294810(a, b, c);
    if (ret != 0) {
        return ret;
    }
    while (fn_8028BAD0() == 5) {
        volatile int wait = 0x196E28;
        while (wait-- != 0) {
        }
    }
    boards = fn_8028B0B4();
    switch (boards) {
    case 1:
        fn_80289C68(0x20, 0);
        lbl_80679E28.port0 = boards;
        break;
    case 0:
        break;
    default:
        fn_80289C68(0x10, 0x11);
        lbl_80679E28.port0 = boards;
        lbl_80679E28.port1 = boards - 1;
        break;
    }
    return 0;
}
