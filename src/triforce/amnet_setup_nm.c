#include <triforce/amnet_priv.h>

/* Five board-config tables; separate objects so fn_8028D8CC addresses them off
 * one pooled .rodata base (addi rX, base, 0x0/0x28/0x40/0x50/0x78). */
const u32 amnet_setup_nm_rodata_803F2798[10] = {0x00800000, 0x00001000, 0x00000020, 0x00000000, 0x00000200, 0x00000200, 0x00A00000, 0x00100000, 0x00B00000, 0x00100000};
const u32 lbl_803F27C0[6] = {0x00D00000, 0x00100000, 0x000FF000, 0x00000000, 0x00D00000, 0x00100000};
const u32 lbl_803F27D8[4] = {0x00C00000, 0x00001000, 0x00000020, 0x00000000};
const u32 lbl_803F27E8[10] = {0x00040000, 0x00001000, 0x00000020, 0x00000000, 0x00000200, 0x00000200, 0x00100000, 0x00080000, 0x00180000, 0x00080000};
const u32 lbl_803F2810[6] = {0x00080000, 0x00080000, 0x0007F000, 0x00000000, 0x00080000, 0x00080000};

const NetHandler amnet_setup_nm_rodata_803F2828[12] = {
    fn_80291738, fn_80291738, fn_802916E4, fn_80291690, fn_802915F4, fn_80291524,
    fn_8029145C, fn_802913CC, fn_80291314, fn_80291738, fn_8029121C, fn_80291134,
};

const NetHandler amnet_setup_nm_rodata_803F2858[4] = {fn_80291738, fn_80291738, fn_80291098, fn_80291738};

const NetDispatch amnet_nm3_rodata_803F2868[3] = {
    {0x0000, 12, amnet_setup_nm_rodata_803F2828},
    {0x0300, 4, amnet_setup_nm_rodata_803F2858},
    {0, 0, NULL},
};

const u8 lbl_806DC930[] = {0x21, 0x29, 0};
const char lbl_806DC934[] = "GCAM";

/* ---- amnet_nm2_rest.c ---- */

static inline void ProbeTraceAdd(u8 op, u8 dir, void* buf, u32 addr, u32 size) {
    u32 i = amnet_nm3_bss_806D1E44 & 7;
    amnet_nm3_bss_806937C0[i].seq = amnet_nm3_bss_806D1E44++;
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
    return BSWAP32(*(u32*)buf);
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
    if ((amnet_nm3_bss_806937C0[0].flags & 1) && id == 0xA9) {
        ProbeTraceAdd('W', 'R', buf, addr, 0x20);
    }
    DevWrite(buf, addr, 0x20);
    if ((amnet_nm3_bss_806937C0[0].flags & 4) && id == 0xA9) {
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
    if ((amnet_nm3_bss_806937C0[0].flags & 2) && id == 0xA9) {
        ProbeTraceAdd('C', 'L', buf, addr, 0x20);
    }
    InitializeDevSend(buf, addr, id);
}

static inline void InitializeDevCommand(NetDev* dev) {
    u8 raw[0x40];
    void* buf;
    u32 addr;
    u8 id;
    buf = ALIGN32(raw);
    addr = dev->cmdAddr;
    id = dev->id;
    memset(buf, 0, 0x20);
    if ((amnet_nm3_bss_806937C0[0].flags & 2) && id == 0xA9) {
        ProbeTraceAdd('C', 'L', buf, addr, 0x20);
    }
    InitializeDevSend(buf, addr, id);
}

static inline NetDev* FindSetupDevice(u8 id) {
    NetDev* dev = FindDev(id);
    return dev;
}

s32 fn_8028D8CC(u8 id, NetBlob* blob) {
    NetDev* dev;
    u32 base;
    u32 off;
    u32 v;

    dev = FindSetupDevice(id);
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
        base = BSWAP16(hdr[1]);
        base <<= 16;
        base |= BSWAP16(hdr[0]);
        amnet_nm3_bss_80699140.hwFlags = ReadDeviceHalf(0x80000000);
        if (amnet_nm3_bss_80699140.hwFlags & 0x100) {
            amnet_nm3_bss_80699140.prio = 0;
        } else {
            amnet_nm3_bss_80699140.prio = 1;
        }
        amnet_nm3_bss_80699140.base[0] = base;
        amnet_nm3_bss_80699140.base[1] = 0;
        dev->kind = 1;
        if (base != 0) {
            off = base - 0x01000000;
            dev->flags |= 0xD;
            dev->cmdAddr = off + 0x900000;
            dev->statAddr = off + 0x900020;
            InitializeDevCommand(dev);
            InitializeDevClear(dev->statAddr, dev);
            memcpy(amnet_nm3_bss_80699140.cfgA, amnet_setup_nm_rodata_803F2798, sizeof(amnet_nm3_bss_80699140.cfgA));
            amnet_nm3_bss_80699140.cfgA[0] += off;
            amnet_nm3_bss_80699140.cfgA[6] += off;
            amnet_nm3_bss_80699140.cfgA[8] += off;
            fn_80293070(amnet_nm3_bss_80699140.cfgA);
            memcpy(amnet_nm3_bss_80699140.cfgB, lbl_803F27C0, sizeof(amnet_nm3_bss_80699140.cfgB));
            amnet_nm3_bss_80699140.cfgB[0] += off;
            amnet_nm3_bss_80699140.cfgB[4] += off;
            fn_80290F70(amnet_nm3_bss_80699140.cfgB);
            memcpy(amnet_nm3_bss_80699140.cfgC, lbl_803F27D8, sizeof(amnet_nm3_bss_80699140.cfgC));
            amnet_nm3_bss_80699140.cfgC[0] += off;
            fn_80291010(amnet_nm3_bss_80699140.cfgC);
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
        amnet_nm3_bss_80699140.prio = 1;
        amnet_nm3_bss_80699140.hwFlags = ReadDeviceWord(0x80000120);
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
        amnet_nm3_bss_80699140.base[1] = 0x89000000;
        dev->kind = 3;
        dev->flags |= 9;
        dev->cmdAddr = 0x89000000;
        dev->statAddr = 0x89000200;
        InitializeDevClear(dev->cmdAddr, dev);
        InitializeDevClear(dev->statAddr, dev);
        memcpy(amnet_nm3_bss_80699140.cfgA, lbl_803F27E8, sizeof(amnet_nm3_bss_80699140.cfgA));
        amnet_nm3_bss_80699140.cfgA[0] += 0x89000000;
        amnet_nm3_bss_80699140.cfgA[6] += 0x89000000;
        amnet_nm3_bss_80699140.cfgA[8] += 0x89000000;
        fn_80293070(amnet_nm3_bss_80699140.cfgA);
        memcpy(amnet_nm3_bss_80699140.cfgB, lbl_803F2810, sizeof(amnet_nm3_bss_80699140.cfgB));
        amnet_nm3_bss_80699140.cfgB[0] += 0x89000000;
        amnet_nm3_bss_80699140.cfgB[4] += 0x89000000;
        fn_80290F70(amnet_nm3_bss_80699140.cfgB);
        return 0;
    }
    default:
        return 1;
    }
}


