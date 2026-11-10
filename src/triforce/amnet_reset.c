#include <triforce/amnet_priv.h>

/* ---- amnet_nm2_rest.c ---- */

static inline void ProbeTraceAdd(u8 op, u8 dir, void* buf, u32 addr, u32 size) {
    u32 n = amnet_nm3_bss_806D1E44++;
    u32 i = n & 7;
    amnet_nm3_bss_806937C0[i].seq = n;
    amnet_nm3_bss_806937C0[i].op = op;
    amnet_nm3_bss_806937C0[i].dir = dir;
    amnet_nm3_bss_806937C0[i].buf = buf;
    amnet_nm3_bss_806937C0[i].addr = addr;
    amnet_nm3_bss_806937C0[i].size = size;
    memcpy(amnet_nm3_bss_806937C0[i].data, buf, 0x20);
}

static inline void ProbeDevClear(u32 addr, NetDev* dev) {
    u8 raw[0x40];
    u8 id;
    void* buf;
    buf = ALIGN32(raw);
    id = dev->id;
    memset(buf, 0, 0x20);
    if ((amnet_nm3_bss_806937C0[0].flags & 2) && id == 0xA9) {
        ProbeTraceAdd('C', 'L', buf, addr, 0x20);
    }
    if ((amnet_nm3_bss_806937C0[0].flags & 1) && id == 0xA9) {
        ProbeTraceAdd('W', 'R', buf, addr, 0x20);
    }
    DevWrite(buf, addr, 0x20);
    if ((amnet_nm3_bss_806937C0[0].flags & 4) && id == 0xA9) {
        DCInvalidateRange(buf, 0x20);
        ProbeTraceAdd('W', '2', buf, -1, -1);
    }
}

static inline void ResetDevAddress(u32* address, NetDev* dev) {
    u8 raw[0x40];
    void* buf;
    u32 addr;
    u8 id;
    buf = ALIGN32(raw);
    addr = *address;
    id = dev->id;
    memset(buf, 0, 0x20);
    if ((amnet_nm3_bss_806937C0[0].flags & 2) && id == 0xA9) {
        ProbeTraceAdd('C', 'L', buf, addr, 0x20);
    }
    if ((amnet_nm3_bss_806937C0[0].flags & 1) && id == 0xA9) {
        ProbeTraceAdd('W', 'R', buf, addr, 0x20);
    }
    DevWrite(buf, addr, 0x20);
    if ((amnet_nm3_bss_806937C0[0].flags & 4) && id == 0xA9) {
        DCInvalidateRange(buf, 0x20);
        ProbeTraceAdd('W', '2', buf, -1, -1);
    }
}

#pragma push
#pragma opt_dead_assignments off
s32 fn_8028EAA8(u8 id) {
    NetDev* dev = FindDev(id);

    if (dev == NULL) {
        return 1;
    }
    ResetDevAddress(&dev->cmdAddr, dev);
    ProbeDevClear(dev->statAddr, dev);
    switch (dev->kind) {
    case 1:
        break;
    case 2:
        DevPoke(0x84000040, 0);
        break;
    case 3:
        break;
    }
    return 0;
}
#pragma pop

