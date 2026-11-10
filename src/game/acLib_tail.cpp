/* acLib media update, initialization and shared state. */
#include "game/acLib_private.h"

extern "C" {
MediaConfig acLib_tail_bss_80679E28;
unsigned int acLib_nm1_bss_80679E34[8];
unsigned int acLib_nm1_bss_80679E54[32];
MediaRequestSlot acLib_tail_bss_80679ED4;
int acLib_tail_bss_806D1AD0;
int acLib_tail_bss_806D1AD4;
}

#pragma cplusplus off
static inline void CopyMediaRequest(struct MediaRequest *dst, const struct MediaRequest *src) {
    dst->state = src->state;
    dst->params = src->params;
    dst->len = src->len;
}
#pragma cplusplus reset

extern "C" int fn_802554DC(void) {
    if (fn_80293BF4()) {
        fn_8028B9A4();
        if (acLib_tail_bss_80679E28.busy == 0) {
            int boards = fn_8028B0B4();
            if (boards) {
                fn_80255154(boards, 1);
                int second = boards - 1;
                if (second > 0) {
                    fn_80255154((unsigned char)second, 2);
                }
            }
            if (acLib_tail_bss_80679ED4.req.state == 0) {
                MediaRequest *req = fn_80288EAC();
                if (req == 0) {
                    goto done;
                }
                CopyMediaRequest(&acLib_tail_bss_80679ED4.req, req);
            }
            {
                MediaRequest *cur = &acLib_tail_bss_80679ED4.req;
                switch ((int)cur->state) {
                case 1: {
                    int port;
                    if (cur->params.port == 2) {
                        port = acLib_tail_bss_80679E28.port1;
                    } else {
                        port = acLib_tail_bss_80679E28.port0;
                    }
                    if (fn_8028A8B4(port, cur->params.arg, cur->len) == 0) {
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

extern "C" void fn_80255620(void) {
    fn_802947CC();
}

extern "C" int fn_80255640(int a, int b, int c) {
    int i;
    int boards;
    int ret;
    acLib_tail_bss_806D1AD0 = 0;
    for (i = 0; i < 8; i++) {
        acLib_nm1_bss_80679E34[i] = 0;
        acLib_nm1_bss_80679E54[i] = 0;
    }
    acLib_tail_bss_806D1AD4 = 0;
    if (acLib_tail_data_806D0A90 == 0) {
        return 1;
    }
    memset(&acLib_tail_bss_80679E28, 0, 0xC);
    acLib_tail_bss_80679E28.busy = a;
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
        acLib_tail_bss_80679E28.port0 = boards;
        break;
    case 0:
        break;
    case 2:
    default:
        fn_80289C68(0x10, 0x11);
        acLib_tail_bss_80679E28.port0 = boards;
        acLib_tail_bss_80679E28.port1 = boards - 1;
        break;
    }
    return 0;
}

extern "C" void fn_802557B4(void) {
    acLib_tail_bss_806D1AD0 = 1;
}
