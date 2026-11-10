#include <triforce/amjvs_internal.h>

u32 amjvs_nm7_bss_806D1E3C;
u32 amjvs_nm7_bss_806D1E38;

#define NEXT_STATE()  \
    Mgr.state++;      \
    InitTimer = 0;    \
    InitNode = 0

static const char lbl_803F2768[] = "namco ltd.;GC-AM BASE PCB;Ver1.00;JPN,TRIFORCE";

s32 fn_8028BAD0(void) {
    u8* res = fn_802857A8();
    u8* count = fn_80285778();
    JvsNode* nodes = fn_802857B8();
    OSSemaphore* sem;
    JvsFeatures* n;
    u32 bits;

    if (Mgr.ready) {
        return 0;
    }
    sem = &Mgr.sem;
    OSWaitSemaphore(sem);
    switch (Mgr.state) {
    case 0:
        fn_802856A4(fn_8028B3D0);
        NEXT_STATE();
        break;
    case 1:
        InitTimer++;
        fn_80282F3C();
        fn_80282E04();
        fn_80285638(0);
        fn_80285418();
        fn_802854B0();
        fn_80282EB8();
        fn_80282E60();
        if (InitTimer >= 2) {
            NEXT_STATE();
        }
        break;
    case 2:
        InitTimer++;
        fn_80282F3C();
        fn_80282E04();
        fn_80282EB8();
        fn_80282E60();
        if (InitTimer >= 60) {
            NEXT_STATE();
        }
        break;
    case 3:
        InitTimer++;
        if (!(res[0x17] & 1)) {
            fn_80282F3C();
            fn_80282E04();
            fn_80282EB8();
            fn_80282E60();
            break;
        }
        Mgr.state++;
        InitTimer = 0;
        InitNode = 0;
    case 4:
        if (InitTimer++ == 0 && InitNode == 0) {
            InitNode = 1;
        }
        if (InitNode < 16 && (res[0x17] & 1) && *count == InitNode - 1) {
            fn_80282F3C();
            fn_80285638(0);
            fn_80285384(InitNode);
            fn_802854B0();
            fn_80282EB8();
            fn_80282E60();
            InitTimer = 0;
            Mgr.state++;
            break;
        }
        Mgr.state = 6;
        InitTimer = 0;
        InitNode = 0;
        break;
    case 5:
        InitTimer++;
        fn_80282F3C();
        fn_80282E04();
        fn_80282EB8();
        fn_80282E60();
        if (InitTimer >= 3) {
            Mgr.state = 4;
            InitTimer = 0;
            InitNode++;
        }
        break;
    case 6:
        if (InitTimer++ == 0 && InitNode == 0) {
            InitNode = 1;
        }
        if (InitNode <= *count && InitNode < 16) {
            fn_80282F3C();
            fn_80285638(InitNode);
            fn_80285308();
            fn_802854B0();
            fn_80282EB8();
            fn_80282E60();
            InitTimer = 0;
            Mgr.state++;
            break;
        }
        Mgr.state = 10;
        InitTimer = 0;
        InitNode = 0;
        break;
    case 7:
        fn_80282F3C();
        fn_80285638(InitNode);
        fn_8028528C();
        fn_80285210();
        fn_80285194();
        fn_80285118();
        fn_802854B0();
        fn_80282EB8();
        fn_80282E60();
        InitTimer = 0;
        Mgr.state++;
        break;
    case 8:
        fn_80282F3C();
        fn_80285638(InitNode);
        fn_80285048(lbl_803F2768);
        fn_802854B0();
        fn_80282EB8();
        fn_80282E60();
        InitTimer = 0;
        Mgr.state++;
        break;
    case 9:
        bits = 0;
        n = (JvsFeatures*)&nodes[InitNode].players;
        if (n->players != 0) {
            bits |= 1;
        }
        if (n->analogCh != 0) {
            bits |= 2;
        }
        if (n->coinSlots != 0) {
            bits |= 4;
        }
        if (n->rotary != 0) {
            bits |= 8;
        }
        if (n->keycode != 0) {
            bits |= 0x10;
        }
        if (n->screenPos != 0) {
            bits |= 0x20;
        }
        if (n->miscSw != 0) {
            bits |= 0x40;
        }
        if (n->unkD9 != 0) {
            bits |= 0x4000;
        }
        Mgr.node[InitNode].flags = bits;
        InitTimer = 0;
        Mgr.state = 6;
        InitNode++;
        break;
    case 10:
        InitTimer++;
        fn_80282F3C();
        fn_80282E04();
        fn_80282EB8();
        fn_80282E60();
        if (InitTimer >= 2) {
            NEXT_STATE();
            OSSignalSemaphore(sem);
            fn_8028B180(TRUE);
            OSWaitSemaphore(sem);
            Mgr.ready = TRUE;
        }
        break;
    }
    OSSignalSemaphore(sem);
    return Mgr.ready ? 0 : 5;
}
