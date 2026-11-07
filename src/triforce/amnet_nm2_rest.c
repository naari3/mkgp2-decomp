#include <triforce/amnet_priv.h>

static inline void ProbeTraceAdd(u8 op, u8 dir, void* buf, u32 addr, u32 size) {
    u32 n = lbl_806D1E44++;
    u32 i = n & 7;
    lbl_806937C0[i].seq = n;
    lbl_806937C0[i].op = op;
    lbl_806937C0[i].dir = dir;
    lbl_806937C0[i].buf = buf;
    lbl_806937C0[i].addr = addr;
    lbl_806937C0[i].size = size;
    memcpy(lbl_806937C0[i].data, buf, 0x20);
}

static inline void ProbeDevClear(u32 addr, NetDev* dev) {
    u8 raw[0x40];
    u8 id;
    void* buf;
    buf = ALIGN32(raw);
    id = dev->id;
    memset(buf, 0, 0x20);
    if ((lbl_806937C0[0].flags & 2) && id == 0xA9) {
        ProbeTraceAdd('C', 'L', buf, addr, 0x20);
    }
    if ((lbl_806937C0[0].flags & 1) && id == 0xA9) {
        ProbeTraceAdd('W', 'R', buf, addr, 0x20);
    }
    DevWrite(buf, addr, 0x20);
    if ((lbl_806937C0[0].flags & 4) && id == 0xA9) {
        DCInvalidateRange(buf, 0x20);
        ProbeTraceAdd('W', '2', buf, -1, -1);
    }
}

/* Keep aligned transfer storage inside the transport helpers. */
static inline void ReadDeviceInfoImpl(u32 addr, void* info) {
    u8 raw[0x40];
    void* buf = ALIGN32(raw);
    DevRead(addr, buf, 0x20);
    memcpy(info, buf, 0x20);
}

static inline void WriteDeviceCommandImpl(u32 addr, void* cmd) {
    u8 raw[0x40];
    void* buf = ALIGN32(raw);
    memcpy(buf, cmd, 0x20);
    DevWrite(buf, addr, 0x20);
}

static inline u16 ReadDeviceHalfImpl(u32 addr) {
    u8 raw[0x40];
    void* buf = ALIGN32(raw);
    u32 v;
    DevRead(addr, buf, 0x20);
    v = *(u16*)buf;
    return BSWAP16(v);
}

static inline u32 ReadDeviceWordImpl(u32 addr) {
    u8 raw[0x40];
    void* buf = ALIGN32(raw);
    u32 v;
    DevRead(addr, buf, 0x20);
    v = *(u32*)buf;
    return BSWAP32(v);
}

static inline void ReadDeviceInfo(u32 addr, void* info) {
    ReadDeviceInfoImpl(addr, info);
}

static inline void WriteDeviceCommand(u32 addr, void* cmd) {
    WriteDeviceCommandImpl(addr, cmd);
}

static inline u16 ReadDeviceHalf(u32 addr) {
    return ReadDeviceHalfImpl(addr);
}

static inline u32 ReadDeviceWord(u32 addr) {
    return ReadDeviceWordImpl(addr);
}

static inline void WriteDeviceWord(u32 addr, u32 val) {
    DevPoke(addr, val);
}

static inline void InitializeDevSend(void* buf, u32 addr, u8 id) {
    if ((lbl_806937C0[0].flags & 1) && id == 0xA9) {
        ProbeTraceAdd('W', 'R', buf, addr, 0x20);
    }
    DevWrite(buf, addr, 0x20);
    if ((lbl_806937C0[0].flags & 4) && id == 0xA9) {
        DCInvalidateRange(buf, 0x20);
        ProbeTraceAdd('W', '2', buf, -1, -1);
    }
}

static inline void InitializeDevClear(u32 addr, NetDev* dev) {
    u8 raw[0x40];
    u8 id;
    void* buf;
    buf = ALIGN32(raw);
    id = dev->id;
    memset(buf, 0, 0x20);
    if ((lbl_806937C0[0].flags & 2) && id == 0xA9) {
        ProbeTraceAdd('C', 'L', buf, addr, 0x20);
    }
    InitializeDevSend(buf, addr, id);
}

s32 fn_8028D8CC(u8 id, NetBlob* blob) {
    NetDev* dev;
    const u32* configs = lbl_803F2798;
    u32 base;
    u32 off;
    u32 v;

    dev = FindDev(id);
    if (dev == NULL) {
        return 1;
    }
    switch (id) {
    case 0x21: {
        /* The device header workspace is a complete 32-byte packet. */
        u16 hdr[16];
        u8 info[0x20];
        u16 cmd[16];
        ReadDeviceInfo(0x80000040, info);
        memcpy(hdr, info, 8);
        if (memcmp(&hdr[2], lbl_806DC934, 4) != 0) {
            cmd[1] = 0;
            cmd[0] = 0x100;
            cmd[2] = 0;
            cmd[3] = 0;
            WriteDeviceCommand(0x80000040, cmd);
            return 5;
        }
        base = (BSWAP16(hdr[1]) << 16) | BSWAP16(hdr[0]);
        lbl_80699140.hwFlags = ReadDeviceHalf(0x80000000);
        if (lbl_80699140.hwFlags & 0x100) {
            lbl_80699140.prio = 0;
        } else {
            lbl_80699140.prio = 1;
        }
        lbl_80699140.base[0] = base;
        lbl_80699140.base[1] = 0;
        dev->kind = 1;
        if (base != 0) {
            off = base - 0x01000000;
            dev->flags |= 0xD;
            dev->cmdAddr = off + 0x900000;
            dev->statAddr = off + 0x900020;
            InitializeDevClear(dev->cmdAddr, dev);
            InitializeDevClear(dev->statAddr, dev);
            memcpy(lbl_80699140.cfgA, &configs[0], sizeof(lbl_80699140.cfgA));
            lbl_80699140.cfgA[0] += off;
            lbl_80699140.cfgA[6] += off;
            lbl_80699140.cfgA[8] += off;
            fn_80293070(lbl_80699140.cfgA);
            memcpy(lbl_80699140.cfgB, &configs[10], sizeof(lbl_80699140.cfgB));
            lbl_80699140.cfgB[0] += off;
            lbl_80699140.cfgB[4] += off;
            fn_80290F70(lbl_80699140.cfgB);
            memcpy(lbl_80699140.cfgC, &configs[16], sizeof(lbl_80699140.cfgC));
            lbl_80699140.cfgC[0] += off;
            fn_80291010(lbl_80699140.cfgC);
        }
        return 0;
    }
    case 0x29: {
        v = ReadDeviceWord(0x80000140);
        if (!(v & 1)) {
            if (blob != NULL && blob->len != 0 && blob->data != NULL) {
                DevWrite(blob->data, 0x84800000, blob->len);
                WriteDeviceWord(0x80000140, 0x01000000);
            }
            return 5;
        }
        lbl_80699140.prio = 1;
        lbl_80699140.hwFlags = ReadDeviceWord(0x80000120);
        dev->kind = 2;
        dev->flags |= 1;
        dev->cmdAddr = 0x84000000;
        dev->statAddr = 0x84000020;
        InitializeDevClear(dev->cmdAddr, dev);
        InitializeDevClear(dev->statAddr, dev);
        return 0;
    }
    case 0xA9: {
        v = ReadDeviceWord(0x80000160);
        if (v & 1) {
            return 5;
        }
        lbl_80699140.base[1] = 0x89000000;
        dev->kind = 3;
        dev->flags |= 9;
        dev->cmdAddr = 0x89000000;
        dev->statAddr = 0x89000200;
        InitializeDevClear(dev->cmdAddr, dev);
        InitializeDevClear(dev->statAddr, dev);
        memcpy(lbl_80699140.cfgA, &configs[20], sizeof(lbl_80699140.cfgA));
        lbl_80699140.cfgA[0] += 0x89000000;
        lbl_80699140.cfgA[6] += 0x89000000;
        lbl_80699140.cfgA[8] += 0x89000000;
        fn_80293070(lbl_80699140.cfgA);
        memcpy(lbl_80699140.cfgB, &configs[30], sizeof(lbl_80699140.cfgB));
        lbl_80699140.cfgB[0] += 0x89000000;
        lbl_80699140.cfgB[4] += 0x89000000;
        fn_80290F70(lbl_80699140.cfgB);
        return 0;
    }
    default:
        return 1;
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
    if ((lbl_806937C0[0].flags & 2) && id == 0xA9) {
        ProbeTraceAdd('C', 'L', buf, addr, 0x20);
    }
    if ((lbl_806937C0[0].flags & 1) && id == 0xA9) {
        ProbeTraceAdd('W', 'R', buf, addr, 0x20);
    }
    DevWrite(buf, addr, 0x20);
    if ((lbl_806937C0[0].flags & 4) && id == 0xA9) {
        DCInvalidateRange(buf, 0x20);
        ProbeTraceAdd('W', '2', buf, -1, -1);
    }
}

s32 fn_8028EAA8(u8 id) {
    NetDev* dev = FindDev(id);

    if (dev == NULL) {
        return 1;
    }
    ResetDevAddress(&dev->cmdAddr, dev);
    ProbeDevClear(dev->statAddr, dev);
    switch (dev->kind) {
    default:
        break;
    case 1:
        break;
    case 2:
        DevPoke(0x84000040, 0);
        break;
    }
    return 0;
}
