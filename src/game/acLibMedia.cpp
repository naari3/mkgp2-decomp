/*
 * acLib media update @ 0x80255000..0x80255620.
 *
 * fn_802554DC runs once per frame (acLibUpdateMedia): it polls the two JVS
 * input boards, services a pending media request and performs the reset
 * when one has been requested.
 */

struct ResetState {
    char pad00[0x18];
    unsigned short kind;
    char pad1A[2];
    unsigned int error;
};

struct MediaConfig {
    int busy;
    unsigned char port0;
    unsigned char port1;
    char pad06[2];
    int (*onReset)(unsigned int error);
};

struct MediaRequest {
    unsigned int state;
    unsigned int port;
    unsigned int arg;
    unsigned int len;
};

extern "C" {
extern MediaConfig lbl_80679E28;
extern unsigned int lbl_80679E34[8];
extern unsigned int lbl_80679E54[32];
extern MediaRequest lbl_80679ED4;
extern int lbl_806D1AD0;
extern int lbl_806D1AD4;
extern const char lbl_803F13E4[];
ResetState *fn_8028D6B0(void);
int sprintf(char *buf, const char *fmt, ...);
void OSReport(const char *fmt, ...);
void *memset(void *dst, int c, unsigned long n);
void fn_80286A74(void *info, int hot);
void fn_802947CC(void);
void fn_80286774(void);
void GXAbortFrame(void);
void VISetBlack(int black);
void VIFlush(void);
void VIWaitForRetrace(void);
void OSResetSystem(int reset, unsigned int code, int menu);
int fn_8028AA40(unsigned char board, int *a, unsigned char *b);
int fn_8028AD94(unsigned char board, unsigned char **data, unsigned char *players, unsigned char *bits);
void fn_802895E4(int id, unsigned char b, int a, unsigned int pressed);
int fn_80293BF4(void);
void fn_8028B9A4(void);
unsigned char fn_8028B0B4(void);
MediaRequest *fn_80288EAC(void);
int fn_8028A8B4(unsigned char port, unsigned char arg, unsigned short len);
void fn_8029425C(void);
int fn_80293BCC(void);
void fn_80293DD4(void);
}

extern "C" int fn_80255000(void) {
    ResetState *rs = fn_8028D6B0();
    int reset = 0;
    unsigned int error;
    switch (rs->kind) {
    case 2:
    case 3:
        reset = 1;
        error = 0;
        break;
    default:
        if (rs->error != 0) {
            reset = 1;
            error = rs->error;
        }
        break;
    }
    if (reset) {
        char info[0x30];
        char msg[0x50];
        if (lbl_80679E28.onReset != 0 && lbl_80679E28.onReset(error) == 0) {
            return 0;
        }
        sprintf(msg, lbl_803F13E4, rs->error);
        OSReport(msg);
        memset(info, 0, sizeof(info));
        if (rs->kind == 3) {
            fn_80286A74(info, 1);
        } else {
            fn_80286A74(info, 0);
        }
        fn_802947CC();
        fn_80286774();
        GXAbortFrame();
        VISetBlack(1);
        VIFlush();
        VIWaitForRetrace();
        if (rs->kind == 3) {
            OSResetSystem(0, 0, 0);
        } else {
            OSResetSystem(0, 0, 0);
        }
    }
    return 0;
}

extern "C" int fn_80255154(unsigned char board, int id) {
    unsigned int u;
    int a;
    unsigned char *data;
    unsigned char b;
    unsigned char players;
    unsigned char bits;
    unsigned int coin;
    unsigned int service;
    unsigned int pressed;
    unsigned int *cnt;
    int i;
    int prev;
    int cur;

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

    lbl_80679E34[lbl_806D1AD4] = coin;
    if (++lbl_806D1AD4 >= 8) {
        lbl_806D1AD4 = 0;
    }
    cur = lbl_806D1AD4;
    {
        int t = cur - 1;
        prev = 7;
        if (t >= 0) {
            prev = t;
        }
    }
    cnt = lbl_80679E54;
    cur -= 2;
    for (i = 0; i < 32; i++) {
        unsigned int mask = 1 << i;
        if (!(lbl_80679E34[prev] & mask)) {
            int k = cur;
            int n = 7;
            int j;
            if (cur < 0) {
                k = 7;
            }
            if (lbl_80679E34[k] & mask) {
                n--;
            }
            for (j = 0; j < 6; j++) {
                if (--k < 0) {
                    k = 7;
                }
                if (lbl_80679E34[k] & mask) {
                    n--;
                }
            }
            if (n <= 0) {
                cnt[i] = 8;
            }
        }
    }

    pressed = 0;
    if (lbl_806D1AD0 == 0) {
        for (i = 0; i < 32; i++) {
            unsigned int mask = 1 << i;
            if (service & mask) {
                cnt[i] = 0;
            } else if (cnt[i] != 0) {
                cnt[i]--;
                pressed |= mask;
            }
        }
    }
    fn_802895E4(id, b, a, pressed);
    return 0;
}

extern "C" int fn_802554DC(void) {
    if (fn_80293BF4()) {
        fn_8028B9A4();
        if (lbl_80679E28.busy == 0) {
            int boards = fn_8028B0B4();
            if (boards) {
                fn_80255154(boards, 1);
                int second = boards - 1;
                if (second > 0) {
                    fn_80255154(second, 2);
                }
            }
            if (lbl_80679ED4.state == 0) {
                MediaRequest *req = fn_80288EAC();
                if (req == 0) {
                    goto done;
                }
                lbl_80679ED4 = *req;
            }
            {
                MediaRequest *cur = &lbl_80679ED4;
                switch ((int)cur->state) {
                case 1: {
                    int port;
                    if (cur->port == 2) {
                        port = lbl_80679E28.port1;
                    } else {
                        port = lbl_80679E28.port0;
                    }
                    if (fn_8028A8B4(port, cur->arg, cur->len) == 0) {
                        cur->state = 0;
                    }
                    break;
                }
                case 2:
                    break;
                }
            }
        done:
            fn_8029425C();
        }
        if (fn_80293BCC()) {
            fn_80255000();
        }
        fn_80293DD4();
    }
    return 0;
}
