#include "triforce/acsocket_private.h"

const char lbl_806DC940[] = " \t\n.";

s32 fn_802928DC(void) {
    s32 i;
    s32 n = 0;

    for (i = 0; i < 64; i++) {
        if (!(acClosesocket(i) & 0x80000000)) {
            n++;
        }
    }
    return n;
}

u32 fn_80292934(const char* str) {
    u8 ip[4];
    char buf[0x20];
    char* tok;
    u8* p;
    s32 i;

    strncpy(buf, str, 0x1F);
    tok = strtok(buf, lbl_806DC940);
    p = ip;
    for (i = 0; i < 4; i++, p++) {
        if (tok == NULL) {
            break;
        }
        *p = strtol(tok, NULL, 10);
        tok = strtok(NULL, lbl_806DC940);
    }
    return *(u32*)ip;
}

s32 fn_802929BC(u8* src, u32 off, s32 len) {
    s32 tx;
    s32 rx;
    s32 total = 0;
    s32 n;
    s32 r;

    GetAlign(&tx, &rx);
    while (len > 0) {
        n = len;
        if (tx) {
            if (((u32)src & 0x1F || off & 0x1F) && ((off + len + 0x1F) & ~0x1F) - (off & ~0x1F) > 0x4000) {
                n = 0x4000 - (off & 0x1F);
            }
        } else if (((u32)src & 0x1F || off & 0x1F) && ((off + len + 1) & ~1) - (off & ~1) > 0x4000) {
            n = 0x4000 - (off & 1);
        }
        r = fn_80292AD8(src, off, n, tx, rx);
        if (r == -1) {
            break;
        }
        total += r;
        off += r;
        src += r;
        len -= r;
    }
    return total;
}
