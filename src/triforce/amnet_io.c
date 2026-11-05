#include <triforce/amnet_priv.h>

s32 fn_8028D3E4(u8 ch) {
    s32 ret = 0;
    if (lbl_80699140.sendHook != NULL) {
        lbl_80699140.sendHook(ch);
    } else {
        ret = LockedSend(ch);
    }
    return ret;
}

s32 fn_8028D460(u8 id) {
    NetChan* c;
    s32 i;
    s32 n;

    if (id == 0) {
        return 1;
    }
    c = lbl_80697940;
    i = 0;
    for (n = 64; n != 0; n--) {
        if (!(c->tx.flags & 0x80) && c->tx.id == id) {
            return SendChan(i);
        }
        c++;
        i++;
    }
    return 1;
}

void fn_8028D530(void* buf, u32 addr, u32 len) {
    DevWrite(buf, addr, len);
}

void fn_8028D5E8(u32 addr, void* buf, u32 len) {
    DevRead(addr, buf, len);
}

u32 fn_8028D6A0(void) {
    return lbl_80699140.unkC8;
}

u32* fn_8028D6B0(void) {
    return &lbl_80699140.param;
}

s32 fn_8028D6C0(u32 idx, void* cb) {
    if (idx > 3) {
        return 1;
    }
    lbl_80699140.cb[idx] = cb;
    return 0;
}

NetSendHook fn_8028D6EC(NetSendHook hook) {
    NetSendHook old = lbl_80699140.sendHook;
    lbl_80699140.sendHook = hook;
    return old;
}

void* fn_8028D704(void* hook) {
    void* old = lbl_80699140.hookB0;
    lbl_80699140.hookB0 = hook;
    return old;
}

s32 fn_8028D71C(s32 idx, u32 base) {
    if (idx < 0 || idx > 1) {
        return 1;
    }
    lbl_80699140.base[idx] = base;
    return 0;
}
