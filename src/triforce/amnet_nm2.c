#include <triforce/amnet_priv.h>

u32 fn_8028D870(void) {
    u32 ret = 8;
    if (lbl_80699140.numDev != 0 && FindDev(0x29) != NULL) {
        ret = lbl_80699140.hwFlags & 7;
    }
    return ret;
}

s32 fn_8028D8CC(u8 id, NetBlob* blob) {
    NetDev* dev;
    u32 base;
    u32 off;
    u32 v;
    void* buf;
    u8 raw0[0x40];
    u8 raw1[0x40];
    u8 raw2[0x40];
    u16 cmd[16];
    u8 info[0x20];
    u16 hdr[4];

    dev = FindDev(id);
    if (dev == NULL) {
        return 1;
    }
    switch (id) {
    case 0x21:
        buf = ALIGN32(raw0);
        DevRead(0x80000040, buf, 0x20);
        memcpy(info, buf, 0x20);
        memcpy(hdr, info, 8);
        if (memcmp(&hdr[2], lbl_806DC934, 4) != 0) {
            cmd[1] = 0;
            buf = ALIGN32(raw1);
            cmd[0] = 0x100;
            cmd[2] = 0;
            cmd[3] = 0;
            memcpy(buf, cmd, 0x20);
            DevWrite(buf, 0x80000040, 0x20);
            return 5;
        }
        buf = ALIGN32(raw2);
        base = (BSWAP16(hdr[1]) << 16) | BSWAP16(hdr[0]);
        DevRead(0x80000000, buf, 0x20);
        v = *(u16*)buf;
        lbl_80699140.hwFlags = BSWAP16(v);
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
            DevClear(dev->cmdAddr, dev);
            DevClear(dev->statAddr, dev);
            memcpy(lbl_80699140.cfgA, &lbl_803F2798[0], sizeof(lbl_80699140.cfgA));
            lbl_80699140.cfgA[0] += off;
            lbl_80699140.cfgA[6] += off;
            lbl_80699140.cfgA[8] += off;
            fn_80293070(lbl_80699140.cfgA);
            memcpy(lbl_80699140.cfgB, &lbl_803F2798[10], sizeof(lbl_80699140.cfgB));
            lbl_80699140.cfgB[0] += off;
            lbl_80699140.cfgB[4] += off;
            fn_80290F70(lbl_80699140.cfgB);
            memcpy(lbl_80699140.cfgC, &lbl_803F2798[16], sizeof(lbl_80699140.cfgC));
            lbl_80699140.cfgC[0] += off;
            fn_80291010(lbl_80699140.cfgC);
        }
        return 0;
    case 0x29:
        buf = ALIGN32(raw0);
        DevRead(0x80000140, buf, 0x20);
        v = *(u32*)buf;
        if (!(BSWAP32(v) & 1)) {
            if (blob != NULL && blob->len != 0 && blob->data != NULL) {
                DevWrite(blob->data, 0x84800000, blob->len);
                DevPoke(0x80000140, 0x01000000);
            }
            return 5;
        }
        buf = ALIGN32(raw1);
        lbl_80699140.prio = 1;
        DevRead(0x80000120, buf, 0x20);
        v = *(u32*)buf;
        lbl_80699140.hwFlags = BSWAP32(v);
        dev->kind = 2;
        dev->flags |= 1;
        dev->cmdAddr = 0x84000000;
        dev->statAddr = 0x84000020;
        DevClear(dev->cmdAddr, dev);
        DevClear(dev->statAddr, dev);
        return 0;
    case 0xA9:
        buf = ALIGN32(raw0);
        DevRead(0x80000160, buf, 0x20);
        v = *(u32*)buf;
        if (BSWAP32(v) & 1) {
            return 5;
        }
        lbl_80699140.base[1] = 0x89000000;
        dev->kind = 3;
        dev->flags |= 9;
        dev->cmdAddr = 0x89000000;
        dev->statAddr = 0x89000200;
        DevClear(dev->cmdAddr, dev);
        DevClear(dev->statAddr, dev);
        memcpy(lbl_80699140.cfgA, &lbl_803F2798[20], sizeof(lbl_80699140.cfgA));
        lbl_80699140.cfgA[0] += 0x89000000;
        lbl_80699140.cfgA[6] += 0x89000000;
        lbl_80699140.cfgA[8] += 0x89000000;
        fn_80293070(lbl_80699140.cfgA);
        memcpy(lbl_80699140.cfgB, &lbl_803F2798[30], sizeof(lbl_80699140.cfgB));
        lbl_80699140.cfgB[0] += 0x89000000;
        lbl_80699140.cfgB[4] += 0x89000000;
        fn_80290F70(lbl_80699140.cfgB);
        return 0;
    default:
        return 1;
    }
}

s32 fn_8028EAA8(u8 id) {
    NetDev* dev = FindDev(id);

    if (dev == NULL) {
        return 1;
    }
    DevClear(dev->cmdAddr, dev);
    DevClear(dev->statAddr, dev);
    switch (dev->kind) {
    case 1:
        break;
    case 2:
        DevPoke(0x84000040, 0);
        break;
    }
    return 0;
}
