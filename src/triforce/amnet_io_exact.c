#include <triforce/amnet_priv.h>

/* ---- amnet_io.c ---- */

s32 fn_8028D3E4(u8 ch) {
    s32 ret = 0;
    if (amnet_nm3_bss_80699140.sendHook != NULL) {
        amnet_nm3_bss_80699140.sendHook(ch);
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
    c = amnet_nm3_bss_80697940;
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
    return amnet_nm3_bss_80699140.unkC8;
}

u32* fn_8028D6B0(void) {
    return &amnet_nm3_bss_80699140.param;
}

s32 fn_8028D6C0(u32 idx, void* cb) {
    if (idx > 3) {
        return 1;
    }
    amnet_nm3_bss_80699140.cb[idx] = cb;
    return 0;
}

NetSendHook fn_8028D6EC(NetSendHook hook) {
    NetSendHook old = amnet_nm3_bss_80699140.sendHook;
    amnet_nm3_bss_80699140.sendHook = hook;
    return old;
}

void* fn_8028D704(void* hook) {
    void* old = amnet_nm3_bss_80699140.hookB0;
    amnet_nm3_bss_80699140.hookB0 = hook;
    return old;
}

s32 fn_8028D71C(s32 idx, u32 base) {
    if (idx < 0 || idx > 1) {
        return 1;
    }
    amnet_nm3_bss_80699140.base[idx] = base;
    return 0;
}

/* ---- amnet_nm1.c ---- */

/* Wanted flag bits: bit 0 always, the sign bit selects reverse search. */
#define NET_WANT(m) (((m) | 1) & 0x7FFFFFFF)

s32 fn_8028D750(s32 mask, u8 kind, u8* out) {
    s32 rev = mask & 0x80000000;
    NetDev* dev;
    u32 i;

    for (i = 0; i < amnet_nm3_bss_80699140.numDev; i++) {
        if (rev) {
            dev = &amnet_nm3_bss_80699140.dev[amnet_nm3_bss_80699140.numDev - 1 - i];
        } else {
            dev = &amnet_nm3_bss_80699140.dev[i];
        }
        if (dev->kind == kind && NET_WANT(mask) == (NET_WANT(mask) & dev->flags)) {
            if (out != NULL) {
                *out = dev->id;
            }
            return 1;
        }
    }
    return 0;
}

/* ---- amnet_probe.c ---- */

s32 fn_8028D7E8(s32 mask, u8* out) {
    u32 want = (mask | 1) & 0x7FFFFFFF;
    s32 rev = mask & 0x80000000;
    NetDev* dev;
    u32 i;

    for (i = 0; i < amnet_nm3_bss_80699140.numDev; i++) {
        if (rev) {
            dev = &amnet_nm3_bss_80699140.dev[amnet_nm3_bss_80699140.numDev - 1 - i];
        } else {
            dev = &amnet_nm3_bss_80699140.dev[i];
        }
        if (want == (want & dev->flags)) {
            if (out != NULL) {
                *out = dev->id;
            }
            return 1;
        }
    }
    return 0;
}

/* ---- amnet_nm2.c ---- */

u32 fn_8028D870(void) {
    u32 ret = 8;
    if (amnet_nm3_bss_80699140.numDev != 0 && FindDev(0x29) != NULL) {
        ret = (u8)(amnet_nm3_bss_80699140.hwFlags & 7);
    }
    return ret;
}

