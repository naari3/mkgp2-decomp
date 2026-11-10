#include <triforce/amnet_priv.h>

u8 fn_8028EF74(u8 id) {
    switch (id) {
    default:
    case 0x21:
        return 0;
    case 0x29:
        if (FindDev(0xA9) == NULL && amnet_nm3_bss_80699140.numDev < 2) {
            amnet_nm3_bss_80699140.dev[amnet_nm3_bss_80699140.numDev++].id = 0xA9;
            return 0xA9;
        }
        return 0;
    }
}

u8 fn_8028F008(void) {
    DVDCommandBlock block;
    const u8* p;
    u32 v;
    u8 id;

    memset(&block, 0, sizeof(block));
    v = fn_802869A0(&block);
    id = BSWAP32(v);
    for (p = lbl_806DC930; *p != 0;) {
        if (*p++ == id) {
            if (FindDev(id) == NULL && amnet_nm3_bss_80699140.numDev < 2) {
                amnet_nm3_bss_80699140.dev[amnet_nm3_bss_80699140.numDev++].id = id;
                return id;
            }
            return 0;
        }
    }
    return 0;
}

s32 fn_8028F0E8(void) {
    u16 v;

    fn_80287B44(0, 2, &v);
    v |= 0x37F;
    fn_802879FC(0, 2, v);
    if (!fn_80294DF8(0)) {
        return 1;
    }
    memset(&amnet_nm3_bss_80699140, 0, sizeof(NetState));
    return 0;
}

s32 fn_8028F160(u32 param) {
    u16 v;

    memset(&amnet_nm3_bss_80699140, 0, sizeof(NetState));
    amnet_nm3_bss_80699140.param = param;
    amnet_nm3_bss_80699140.unkC8 = 0x01000000;
    OSInitSemaphore(&amnet_nm3_bss_80699140.sem, 1);
    memset(amnet_nm3_bss_80697940, 0, sizeof(amnet_nm3_bss_80697940));
    if (!fn_80294E30(0, 2)) {
        return 1;
    }
    OSInitSemaphore(&amnet_nm3_bss_80699140.irqSem, 0);
    if (amnet_nm3_data_804F5800[4] != NULL) {
        amnet_nm3_data_804F5800[4]();
    }
    fn_80287E14(2, (EXICallback)fn_8028CC80);
    fn_80287B44(0, 2, &v);
    v &= ~0x7E;
    fn_802879FC(0, 2, v);
    return 0;
}

void fn_8028F25C(void) {
    fn_80287CCC(0, 2, 0x201);
    fn_802878B4(0, 2, 0x14);
}

void fn_8028F298(void) {
    u8 info[0x20];
    u8 raw[0x40];
    void* buf = ALIGN32(raw);

    DevRead(0x88000000, buf, 0x20);
    memcpy(info, buf, 0x20);
}

void fn_8028F31C(void) {
    fn_802878B4(0, 2, 0x10);
}

void fn_8028F348(void) {
    DevPoke(0x84000040, 0x01000000);
}

void fn_8028F3D8(void) {
    fn_802878B4(0, 2, 4);
}

void fn_8028F404(void) {
    fn_80287CCC(0, 2, 0);
}

void fn_8028F430(void) {
    fn_80287CCC(0, 2, 0x201);
}
