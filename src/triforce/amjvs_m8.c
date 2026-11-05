#include <triforce/amjvs_internal.h>

s32 fn_8028BFB0(void) {
    fn_80293AF0();
    return 0;
}

static inline void Delay(void) {
    volatile s32 n = 0x196E28;

    while (n-- != 0) {
    }
}

s32 fn_8028BFD4(void) {
    u8* res;

    memset(&Mgr, 0, 0x26EC);
    OSInitSemaphore(&Mgr.sem, 1);
    fn_8028250C();
    res = fn_802857A8();
    if (res[0] != 0) {
        return 2;
    }
    if (res[3] != 0x10) {
        return 3;
    }
    switch (res[4] >> 4) {
    case 2:
        return 3;
    default:
        return 3;
    case 1:
        do {
            fn_80282F3C();
            fn_80282E04();
            fn_80282BB0();
            fn_80282B54();
            fn_80282DA8();
            fn_80282CDC(0x3000);
            fn_80282EB8();
            fn_80282E60();
            Delay();
        } while (res[0] != 0);
        fn_80282F3C();
        fn_80283E9C();
        fn_80282C68(1);
        fn_80282EB8();
        fn_80282E60();
        Delay();
        do {
            fn_80282F3C();
            fn_80282E04();
            fn_80282EB8();
            fn_80282E60();
            Delay();
        } while (!(res[0x17] & 0x10));
        fn_80293B74();
        return 0;
    }
}
