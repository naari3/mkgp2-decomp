/* Triforce system manager: brings up backup data, JVS, coin and the media
 * board, then runs the board link state machine once per frame. */
#include <dolphin.h>
#include <string.h>

typedef struct AmCoinSlot {
    /* 0x0 */ u32 credits;
    /* 0x4 */ u32 bonus;
    /* 0x8 */ u32 unk8;
    /* 0xC */ u16 total;
    /* 0xE */ u16 service;
} AmCoinSlot;

typedef struct AmNetCfg {
    /* 0x0 */ u8 type;
    /* 0x1 */ u8 a;
    /* 0x2 */ u8 b;
    /* 0x3 */ u8 c;
    /* 0x4 */ u8 d;
    /* 0x5 */ u8 e;
    /* 0x6 */ u8 pad[10];
} AmNetCfg;

typedef struct AmBackup {
    /* 0x000 */ u8 version;
    /* 0x001 */ u8 unk01[5];
    /* 0x006 */ u8 region[2];
    /* 0x008 */ u8 gameId[8];
    /* 0x010 */ u8 coinCfg[0x20];
    /* 0x030 */ AmCoinSlot slot[4];
    /* 0x070 */ u8 jvsCfg[0x40];
    /* 0x0B0 */ AmNetCfg netCfg;
    /* 0x0C0 */ u8 unkC0[0x134];
} AmBackup;

typedef struct AmInfo {
    /* 0x00 */ u8 region[2];
    /* 0x02 */ u8 jvsVer[2];
    /* 0x04 */ u8 jvsCmdVer[2];
    /* 0x06 */ u8 mbVer[2];
    /* 0x08 */ u8 gameId[8];
    /* 0x10 */ u8 commVer;
    /* 0x12 */ u16 boardId;
    /* 0x14 */ u8 netVer[2];
    /* 0x16 */ u8 unk16[2];
    /* 0x18 */ char serial[0x14];
    /* 0x2C */ char mbSerial[0x14];
    /* 0x40 */ u8 date[8];
    /* 0x48 */ char netSerial[0x14];
    /* 0x5C */ u8 unk5C[0x84];
} AmInfo;

typedef struct AmFirm {
    /* 0x0 */ u32 size;
    /* 0x4 */ void* buf;
} AmFirm;

typedef struct AmSys {
    /* 0x00 */ u32 ready;
    /* 0x04 */ s32 mode;
    /* 0x08 */ s32 dirty;
    /* 0x0C */ u32 state;
    /* 0x10 */ u8 mbId;
    /* 0x11 */ u8 netId;
    /* 0x12 */ u8 numCoin;
    /* 0x14 */ u32 ip;
    /* 0x18 */ s32 ownFirm;
    /* 0x1C */ AmFirm firm;
    /* 0x24 */ AmInfo info;
} AmSys;

typedef struct AmThread {
    /* 0x0000 */ OSThread thread;
    /* 0x0318 */ u8 stack[0x1000];
    /* 0x1318 */ OSMessageQueue queue;
    /* 0x1338 */ void* msgs[0x10];
} AmThread;

typedef struct AmOptions {
    /* 0x00 */ u8 coinA;
    /* 0x01 */ u8 coinB;
    /* 0x02 */ u8 numCoin;
    /* 0x04 */ u32 coinCfg;
    /* 0x08 */ s32 clearCoin;
    /* 0x0C */ u8 keep;
    /* 0x10 */ AmFirm firm;
} AmOptions;

typedef struct AmBackupDesc {
    char id[8];
    u32 size;
    u32 flags;
} AmBackupDesc;

extern s32 lbl_806CF010;

extern s32 fn_80286B80(s32 a0);
extern s32 fn_80286BD4(s32 a0, s32 a1);
extern s32 fn_802882BC(s32 a, AmBackup* bk);
extern u32 fn_80288668(s32 a, AmBackup* bk);
extern void fn_80288B80(void);
extern s32 fn_80288BCC(const AmBackupDesc* desc);
extern void fn_80289A90(void* p);
extern void fn_80289B04(void* p);
extern void fn_80289B7C(void* p);
extern s32 fn_80289BEC(s32 kind);
extern void fn_80289E20(void);
extern void fn_8028A16C(void* a, void* b, void* c);
extern void fn_8028A3EC(void* p, u32 cfg);
extern void fn_8028AFF4(void* p);
extern void fn_8028BFB0(void);
extern s32 fn_8028BFD4(void);
extern void fn_8028C158(u8 ch);
extern void fn_8028C5E4(u8 ch);
extern s32 fn_8028CB64(u8* ch);
extern s32 fn_8028D000(u8 id);
extern void fn_8028D6C0(u32 idx, void* cb);
extern void fn_8028D6EC(s32 (*cb)(u8));
extern void fn_8028D704(s32 (*cb)(u8));
extern void fn_8028D71C(u32 idx, u32 val);
extern u8 fn_8028D870(void);
extern s32 fn_8028D8CC(u8 id, void* arg);
extern void fn_8028EAA8(u8 id);
extern u8 fn_8028EF74(u8 id);
extern u8 fn_8028F008(void);
extern void fn_8028F0E8(void);
extern s32 fn_8028F160(s32 a);
extern s32 fn_802908D0(char* out);
extern s32 fn_802909FC(char* out);
extern s32 fn_80290B28(u16* a, u16* b);
extern s32 fn_80290C6C(u16* a, u16* b);
extern s32 fn_80290DB0(u8 id, u32* out);
extern u8 fn_80290E44(s32 mask, u32 a0);
extern u8* fn_802857A8(void);

static AmThread RxThread;
static AmThread TxThread;
static AmBackup Backup;
static AmSys Sys;

static u32 PollTries;
static u32 PollTicks;
static u8 PollId;
static s32 LockCount;

static const AmBackupDesc BackupDesc = {"ACBU0001", 0x1F4, 0x83};
static const AmNetCfg DefaultNetCfg = {0x20, 0x0E, 0x1A, 0xFF, 0xFF, 0xFF};
static const char FirmPath[] = "firmware.asic";

#define CLAMP(v, lo, hi) ((v) < (lo) ? (lo) : ((v) > (hi) ? (hi) : (v)))

static inline void InsertDash(char* s) {
    s32 i;

    if (s[4] != '-') {
        for (i = 16; i > 4; i--) {
            s[i] = s[i - 1];
        }
        s[i] = '-';
    }
}

AmInfo* fn_80293BBC(void) {
    return &Sys.info;
}

BOOL fn_80293BCC(void) {
    return Sys.state >= 4;
}

u32 fn_80293BF4(void) {
    return Sys.ready;
}

BOOL fn_80293C04(AmNetCfg* cfg) {
    BOOL ok = TRUE;
    u32 max;

    if (cfg == NULL) {
        return FALSE;
    }
    switch (cfg->type) {
    case 0x20:
        if (cfg->a < 10 || cfg->a > 60) {
            cfg->a = CLAMP(cfg->a, 10, 60);
            ok = FALSE;
        }
        if (cfg->b < 10 || cfg->b > 60) {
            cfg->b = CLAMP(cfg->b, 10, 60);
            ok = FALSE;
        }
        if (cfg->c < 155 || cfg->c > 255) {
            cfg->c = CLAMP(cfg->c, 155, 255);
            ok = FALSE;
        }
        if (cfg->d < 155 || cfg->d > 255) {
            cfg->d = CLAMP(cfg->d, 155, 255);
            ok = FALSE;
        }
        if (cfg->e < 155 || cfg->e > 255) {
            cfg->e = CLAMP(cfg->e, 155, 255);
            ok = FALSE;
        }
        max = cfg->c;
        if (max < cfg->d) {
            max = cfg->d;
        }
        if (max < cfg->e) {
            max = cfg->e;
        }
        if (max * cfg->b > 0x2BD4) {
            ok = FALSE;
            cfg->b = 0x2BD4 / max;
        }
        break;
    default:
        *cfg = DefaultNetCfg;
        return FALSE;
    }
    return ok;
}

s32 fn_802946A4(u8 id);

s32 fn_80293DD4(void) {
    AmSys* s = &Sys;
    u32 ip;
    u16 ver;
    u16 unused;

    switch (s->state) {
    case 1:
        Sys.mbId = fn_8028F008();
        if (Sys.mbId == 0) {
            s->state = 0;
            break;
        }
        s->state = 2;
        fn_802946A4(Sys.mbId);
    case 2:
        if (fn_8028D8CC(Sys.mbId, &Sys.firm.size) != 0) {
            break;
        }
        Sys.numCoin = fn_8028D870();
        if (Sys.ownFirm != 0 && Sys.firm.size != 0 && Sys.firm.buf != NULL) {
            Sys.firm.size = 0;
            OSFreeToHeap(lbl_806CF010, Sys.firm.buf);
            Sys.firm.buf = NULL;
        }
        s->state = 3;
        PollTicks = 0;
        PollTries = 0;
        PollId = 0;
    case 3:
        if (PollTicks == 0) {
            PollId = fn_80290E44(0, 1);
            if (PollId == 0) {
                s->state = 0;
                break;
            }
        }
        ip = 0;
        if (fn_80290DB0(PollId, &ip) != 0) {
            if (++PollTicks < 60) {
                break;
            }
            if (++PollTries >= 10) {
                s->state = 0;
            }
            PollTicks = 0;
            fn_8028D000(PollId);
            PollId = 0;
            fn_8028EAA8(Sys.mbId);
            break;
        }
        PollId = 0;
        fn_8028D71C(0, ip);
        ver = 0;
        fn_80290C6C(&ver, NULL);
        Sys.info.mbVer[1] = ver;
        Sys.info.mbVer[0] = ver >> 8;
        fn_802909FC(Sys.info.mbSerial);
        InsertDash(Sys.info.mbSerial);
        Sys.ip = ip;
        Sys.netId = fn_8028EF74(Sys.mbId);
        if (Sys.netId == 0) {
            s->state = 4;
            break;
        }
        s->state = 5;
    case 5:
        if (fn_8028D8CC(Sys.netId, NULL) != 0) {
            break;
        }
        s->state = 6;
        PollTicks = 0;
        PollTries = 0;
        PollId = 0;
    case 6:
        if (PollTicks == 0) {
            PollId = fn_80290E44(0x80000000, 1);
            if (PollId == 0) {
                s->state = 0;
                break;
            }
        }
        ip = 0;
        if (fn_80290DB0(PollId, &ip) != 0) {
            if (++PollTicks < 60) {
                break;
            }
            if (++PollTries >= 10) {
                s->state = 4;
                Sys.netId = 0;
            }
            PollTicks = 0;
            fn_8028D000(PollId);
            PollId = 0;
            fn_8028EAA8(Sys.netId);
            break;
        }
        PollId = 0;
        unused = 0;
        fn_80290B28(&unused, NULL);
        Sys.info.netVer[1] = unused;
        Sys.info.netVer[0] = unused >> 8;
        fn_802908D0(Sys.info.netSerial);
        InsertDash(Sys.info.netSerial);
        s->state = 4;
        break;
    }
    return 0;
}

s32 fn_8029425C(void) {
    s32 ret = 0;
    AmBackup* bk = &Backup;
    s32 r;

    if (fn_80289BEC(1)) {
        fn_80289B04(bk->slot);
        Sys.dirty = 1;
    }
    if (fn_80289BEC(2)) {
        fn_80289A90(bk->jvsCfg);
        Sys.dirty = 1;
    }
    if (Sys.dirty != 0) {
        r = fn_802882BC(0, bk);
        if (r == 5) {
            ret = 6;
        } else if (r != 0) {
            ret = 1;
        }
        if (r != 5) {
            Sys.dirty = 0;
        }
    }
    return ret;
}

s32 fn_80294340(OSMessageQueue* queue) {
    void* msg;

    while (OSReceiveMessage(queue, &msg, 1)) {
        fn_8028C158((u8)(u32)msg);
    }
    return 0;
}

s32 fn_80294394(void) {
    u8 ch;

    while (fn_8028CB64(&ch)) {
        fn_8028C5E4(ch);
    }
    return 0;
}

s32 fn_802943D0(u8 ch) {
    OSSendMessage(&RxThread.queue, (void*)(u32)ch, 1);
    return 0;
}

s32 fn_8029440C(u8 ch) {
    OSSendMessage(&TxThread.queue, (void*)(u32)ch, 1);
    return 0;
}

static inline void FillStack(AmThread* t) {
    s32 i;

    for (i = 0; i < 0x1000; i += 4) {
        t->stack[i + 0] = 'S';
        t->stack[i + 1] = 'E';
        t->stack[i + 2] = 'G';
        t->stack[i + 3] = 'A';
    }
}

void fn_80294448(void) {
    OSMessageQueue* txq;
    OSMessageQueue* rxq;

    memset(&TxThread, 0, sizeof(AmThread));
    FillStack(&TxThread);
    memset(&RxThread, 0, sizeof(AmThread));
    FillStack(&RxThread);
    txq = &TxThread.queue;
    OSInitMessageQueue(txq, TxThread.msgs, 0x10);
    rxq = &RxThread.queue;
    OSInitMessageQueue(rxq, RxThread.msgs, 0x10);
    OSCreateThread(&TxThread.thread, (void* (*)(void*))fn_80294394, txq, txq, 0x1000, 8, 1);
    OSResumeThread(&TxThread.thread);
    OSCreateThread(&RxThread.thread, (void* (*)(void*))fn_80294340, rxq, rxq, 0x1000, 8, 1);
    OSResumeThread(&RxThread.thread);
    fn_8028D704(fn_8029440C);
    fn_8028D6EC(fn_802943D0);
}

s32 fn_802946A4(u8 id) {
    DVDFileInfo fi;
    AmFirm firm;
    s32 entry;

    if (Sys.firm.size != 0 && Sys.firm.buf != NULL) {
        return 0;
    }
    switch (id) {
    case 0x29:
        entry = DVDConvertPathToEntrynum(FirmPath);
        if (entry < 0) {
            return 1;
        }
        DVDFastOpen(entry, &fi);
        memset(&firm, 0, sizeof(firm));
        firm.size = fi.length;
        firm.buf = OSAllocFromHeap(lbl_806CF010, fi.length);
        if (firm.buf == NULL) {
            DVDClose(&fi);
            return 1;
        }
        if (DVDReadPrio(&fi, firm.buf, firm.size, 0, 2) < firm.size) {
            OSFreeToHeap(lbl_806CF010, firm.buf);
            DVDClose(&fi);
            return 1;
        }
        DVDClose(&fi);
        Sys.firm = firm;
        Sys.ownFirm = 1;
        break;
    }
    return 0;
}

s32 fn_802947CC(void) {
    fn_8028BFB0();
    fn_8028F0E8();
    fn_80289E20();
    fn_80288B80();
    memset(&Sys, 0, sizeof(AmSys));
    return 0;
}

static inline void GetDate(u8* out) {
    OSCalendarTime t;

    if (out != NULL) {
        OSTicksToCalendarTime(OSGetTime(), &t);
        out[0] = CLAMP(t.year, 2000, 2099) - 2000;
        out[1] = CLAMP(t.mon, 0, 11) + 1;
        out[2] = CLAMP(t.mday, 1, 31);
        out[3] = CLAMP(t.hour, 0, 23);
        out[4] = CLAMP(t.min, 0, 59);
        out[5] = CLAMP(t.sec, 0, 59);
        out[6] = CLAMP(t.wday, 0, 6);
        out[7] = 0;
    }
}

s32 fn_80294810(s32 mode, s32 netArg, AmOptions* optIn) {
    AmBackup* bk = &Backup;
    AmOptions opt;
    AmInfo* info;
    s32 i;
    u32 r;

    LockCount = 0;
    memset(&Sys, 0, sizeof(AmSys));
    Sys.ready = 0;
    Sys.mode = mode;
    Sys.dirty = 0;
    Sys.state = 1;
    Sys.mbId = 0;
    Sys.netId = 0;
    Sys.numCoin = 8;
    if (optIn != NULL) {
        memcpy(&opt, optIn, sizeof(AmOptions));
    } else {
        memset(&opt, 0, sizeof(AmOptions));
    }
    if (opt.firm.size != 0 && opt.firm.buf != NULL) {
        Sys.firm = opt.firm;
        Sys.ownFirm = 0;
    }
    if (fn_80288BCC(&BackupDesc) != 0) {
        return 2;
    }
    r = fn_80288668(0, bk);
    if (r == 1) {
        memset(bk, 0, sizeof(AmBackup));
        bk->version = 1;
        bk->netCfg = DefaultNetCfg;
        Sys.dirty = 1;
    } else if (r != 0) {
        Sys.dirty = 1;
    }
    if (bk->version < 1) {
        bk->version = 1;
        Sys.dirty = 1;
    }
    if (opt.coinA != 0) {
        bk->coinCfg[0] = opt.coinA;
    }
    if (opt.coinB != 0) {
        bk->coinCfg[1] = opt.coinB;
    }
    if (opt.numCoin != 0) {
        bk->coinCfg[2] = opt.numCoin;
    }
    if (opt.coinCfg != 0) {
        fn_8028A3EC(bk->coinCfg, opt.coinCfg);
    }
    if (opt.clearCoin != 0) {
        memset(bk->slot, 0, sizeof(bk->slot));
        Sys.dirty = 1;
    } else {
        for (i = 0; i < bk->coinCfg[2]; i++) {
            if (opt.keep & 1) {
                bk->slot[i].credits = 0;
                Sys.dirty = 1;
            }
            if (~opt.keep & 2) {
                bk->slot[i].bonus = 0;
                Sys.dirty = 1;
            }
            if (~opt.keep & 4) {
                bk->slot[i].total = 0;
                Sys.dirty = 1;
            }
            if (~opt.keep & 8) {
                bk->slot[i].service = 0;
                Sys.dirty = 1;
            }
        }
    }
    fn_8028A16C(bk->coinCfg, bk->slot, bk->jvsCfg);
    if (fn_80289BEC(0)) {
        fn_80289B7C(bk->coinCfg);
        Sys.dirty = 1;
    }
    if (fn_80289BEC(1)) {
        fn_80289B04(bk->slot);
        Sys.dirty = 1;
    }
    if (fn_80289BEC(2)) {
        fn_80289A90(bk->jvsCfg);
        Sys.dirty = 1;
    }
    if (!fn_80293C04(&bk->netCfg)) {
        Sys.dirty = 1;
    }
    if (Sys.dirty != 0) {
        fn_802882BC(0, bk);
        Sys.dirty = 0;
    }
    if (fn_8028F160(netArg) != 0) {
        return 3;
    }
    fn_8028D6C0(0, bk->jvsCfg);
    info = &Sys.info;
    fn_8028D6C0(1, info);
    fn_80294448();
    if (fn_8028BFD4() != 0) {
        return 4;
    }
    fn_8028AFF4(&bk->netCfg);
    Sys.ready = 1;
    memcpy(info->region, bk->region, 2);
    memcpy(info->jvsVer, fn_802857A8() + 0x20, 2);
    memcpy(info->jvsCmdVer, fn_802857A8() + 0x22, 2);
    memcpy(info->gameId, bk->gameId, 8);
    info->commVer = fn_802857A8()[0x28];
    info->boardId = *(u16*)(fn_802857A8() + 0x2A);
    memcpy(info->serial, fn_802857A8() + 6, 0x10);
    InsertDash(info->serial);
    GetDate(info->date);
    return 0;
}

s32 fn_80294DF8(s32 a0) {
    if (--LockCount == 0) {
        return fn_80286B80(a0);
    }
    return 1;
}

s32 fn_80294E30(s32 a0, s32 a1) {
    if (LockCount++ == 0) {
        return fn_80286BD4(a0, a1);
    }
    return 1;
}
