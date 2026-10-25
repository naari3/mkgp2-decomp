/* Triforce replacement for dvdlow.c: DI commands go to the AM baseboard. */
#include <dolphin.h>
#include <dolphin/dvd.h>

#include <dolphin/hw_regs.h>

typedef volatile u32 vu32;

typedef struct DVDBuffer {
    void* addr;
    u32 length;
    u32 offset;
} DVDBuffer;

typedef struct DVDCommand {
    s32 cmd;
    void* addr;
    u32 length;
    u32 offset;
    DVDLowCallback callback;
} DVDCommand;

typedef struct DIKey {
    u32 cmd;
    u32 offset;
    u32 length;
} DIKey;

DIKey* __DIKey;
static BOOL FirstRead = TRUE;
static volatile BOOL StopAtNextInt;
static u32 LastLength;
static DVDLowCallback Callback;
static DVDLowCallback ResetCoverCallback;
static volatile OSTime LastResetEnd;
static volatile u32 ResetOccurred;
static volatile BOOL WaitingCoverClose;
static BOOL Breaking;
static volatile u32 WorkAroundType;
static u32 WorkAroundSeekLocation;
static volatile OSTime LastReadFinished;
static OSTime LastReadIssued;
static volatile BOOL LastCommandWasRead;
static OSTime LastCommandIssued;
static vu32 NextCommandNumber;

static DVDCommand CommandList[3];
static OSAlarm AlarmForWA;
static OSAlarm AlarmForTimeout;
static OSAlarm AlarmForBreak;
static DVDBuffer Prev;
static DVDBuffer Curr;

void __DVDLowSetWAType(u32 type, u32 location);
extern void __DVDSetOptionalCommandChecker(void (*)(DVDCommandBlock*, DVDLowCallback));
extern void __DVDSetImmCommand(u32 cmd);
extern void __DVDSetDmaCommand(u32 cmd);
extern void fn_802867B0(void);
extern void fn_80286730(void);
extern u32 fn_802867B8(u32, u32);
extern void fn_80286314(u32, u32, u32);
extern BOOL fn_80286570(void);

static void CommandChecker(DVDCommandBlock* block, DVDLowCallback cb);
BOOL DI_DMA_Write_LowLevel(void* addr, u32 length, u32 offset, DVDLowCallback callback);
static BOOL fn_80285EAC(DVDLowCallback callback);
static BOOL fn_80285F48(u32 arg, DVDLowCallback callback);
static BOOL fn_8028607C(u32, u32, u32, DVDLowCallback callback);
static BOOL fn_80285FE8(void);
static void fn_8028625C(u32 cmd, u32 offset, u32 length);

void fn_802857E0(void) {
    fn_802867B0();
    __DVDSetOptionalCommandChecker(CommandChecker);
    __DVDSetImmCommand(0x65);
    __DVDSetImmCommand(0x67);
    __DVDSetImmCommand(0x68);
    __DVDSetDmaCommand(0x66);
    fn_80286730();
}

static void CommandChecker(DVDCommandBlock* block, DVDLowCallback cb) {
    u32 len;

    __DIRegs[1] = __DIRegs[1];
    switch (block->command) {
    case 0x66:
        len = block->length - block->transferredSize;
        block->currTransferSize = len > 0x80000 ? 0x80000 : len;
        DI_DMA_Write_LowLevel((u8*)block->addr + block->transferredSize, block->currTransferSize,
                              block->offset + block->transferredSize, cb);
        break;
    case 0x67:
        fn_80285F48(block->length, cb);
        break;
    case 0x65:
        fn_80285EAC(cb);
        break;
    case 0x68:
        fn_8028607C(block->offset, block->length, block->currTransferSize, cb);
        break;
    }
}

void __DVDInitWA(void) {
    NextCommandNumber = 0;
    CommandList[0].cmd = -1;
    __DVDLowSetWAType(0, 0);
    OSInitAlarm();
}

void __DVDInterruptHandler(__OSInterrupt interrupt, OSContext* context) {
    DVDLowCallback cb;
    OSContext exceptionContext;
    u32 cause = 0;
    u32 reg;
    u32 intr;
    u32 mask;

    if (LastCommandWasRead) {
        LastReadFinished = __OSGetSystemTime();
        FirstRead = FALSE;
        Prev.addr = Curr.addr;
        Prev.length = Curr.length;
        Prev.offset = Curr.offset;
        if (StopAtNextInt == TRUE) {
            cause |= 8;
        }
    }

    LastCommandWasRead = FALSE;
    StopAtNextInt = FALSE;
    reg = __DIRegs[0];
    mask = reg & 0x2a;
    intr = (reg & 0x54) & (mask << 1);

    if (intr & 0x40) {
        cause |= 8;
    }

    if (intr & 0x10) {
        cause |= 1;
    }

    if (intr & 4) {
        cause |= 2;
    }

    if (cause) {
        ResetOccurred = FALSE;
        OSCancelAlarm(&AlarmForTimeout);
    }

    __DIRegs[0] = intr | mask;

    if (ResetOccurred && (__OSGetSystemTime() - LastResetEnd) < OSMillisecondsToTicks(200)) {
        reg = __DIRegs[1];
        mask = reg & 0x2;
        intr = (reg & 4) & (mask << 1);
        if (intr & 4) {
            if (ResetCoverCallback) {
                ResetCoverCallback(4);
            }
            ResetCoverCallback = NULL;
        }

        __DIRegs[1] = __DIRegs[1];
    } else if (WaitingCoverClose) {
        reg = __DIRegs[1];
        mask = reg & 2;
        intr = (reg & 4) & (mask << 1);

        if (intr & 4) {
            cause |= 4;
        }

        __DIRegs[1] = intr | mask;
        WaitingCoverClose = FALSE;
    } else {
        __DIRegs[1] = 0;
    }

    if ((cause & 8) && !Breaking) {
        cause &= ~8;
    }

    if ((cause & 1)) {
        if (fn_80285FE8()) {
            return;
        }
    }

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);

    if (cause) {
        cb = Callback;
        Callback = NULL;
        if (cb) {
            cb(cause);
        }

        Breaking = FALSE;
    }

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
}

static void AlarmHandlerForTimeout(OSAlarm* alarm, OSContext* context) {
    OSContext tmpContext;
    DVDLowCallback callback;

    OSReport("Timeout: command issued: %7llu, now: %7llu\n",
             OSTicksToMicroseconds(LastCommandIssued), OSTicksToMicroseconds(__OSGetSystemTime()));
    __OSMaskInterrupts(0x400);
    OSClearContext(&tmpContext);
    OSSetCurrentContext(&tmpContext);
    callback = Callback;
    Callback = NULL;
    if (callback != NULL) {
        callback(0x10);
    }
    OSClearContext(&tmpContext);
    OSSetCurrentContext(context);
}

static inline void SetTimeoutAlarm(OSTime timeout) {
    LastCommandIssued = __OSGetSystemTime();
    OSCreateAlarm(&AlarmForTimeout);
    OSSetAlarm(&AlarmForTimeout, timeout, AlarmHandlerForTimeout);
}

void DI_DMA_Read_LowLevel(void* addr, u32 length, u32 offset, DVDLowCallback callback) {
    StopAtNextInt = FALSE;
    Callback = callback;
    LastCommandWasRead = TRUE;
    LastReadIssued = __OSGetSystemTime();

    fn_8028625C(0xa8, offset / 4, length);
    __DIRegs[5] = (u32)addr;
    __DIRegs[6] = length;
    LastLength = length;
    __DIRegs[7] = 3;
    SetTimeoutAlarm(OSSecondsToTicks(30));
}

BOOL DVDLowRead(void* addr, u32 length, u32 offset, DVDLowCallback callback) {
    __DIRegs[6] = length;
    Curr.addr = addr;
    Curr.length = length;
    Curr.offset = offset;
    DI_DMA_Read_LowLevel(addr, length, offset, callback);
    return TRUE;
}

BOOL DVDLowSeek(u32 offset, DVDLowCallback callback) {
    return FALSE;
}

BOOL DVDLowWaitCoverClose(DVDLowCallback callback) {
    return FALSE;
}

BOOL DVDLowReadDiskID(DVDDiskID* diskID, DVDLowCallback callback) {
    return FALSE;
}

BOOL DVDLowStopMotor(DVDLowCallback callback) {
    return FALSE;
}

BOOL DVDLowRequestError(DVDLowCallback callback) {
    return FALSE;
}

BOOL DVDLowInquiry(DVDDriveInfo* info, DVDLowCallback callback) {
    return FALSE;
}

BOOL DI_DMA_Write_LowLevel(void* addr, u32 length, u32 offset, DVDLowCallback callback) {
    Callback = callback;
    StopAtNextInt = FALSE;
    fn_8028625C(0xaa, offset / 4, length);
    __DIRegs[5] = (u32)addr;
    __DIRegs[6] = length;
    LastLength = length;
    __DIRegs[7] = 7;
    SetTimeoutAlarm(OSSecondsToTicks(30));
    return TRUE;
}

static BOOL fn_80285EAC(DVDLowCallback callback) {
    Callback = callback;
    StopAtNextInt = FALSE;
    fn_8028625C(0x12, 0, 4);
    __DIRegs[7] = 1;
    SetTimeoutAlarm(OSSecondsToTicks(30));
    return TRUE;
}

static BOOL fn_80285F48(u32 arg, DVDLowCallback callback) {
    Callback = callback;
    StopAtNextInt = FALSE;
    fn_8028625C((arg << 8) | 0xab, 0, 4);
    __DIRegs[7] = 1;
    SetTimeoutAlarm(OSSecondsToTicks(30));
    return TRUE;
}

static BOOL fn_80285FE8(void) {
    if (!fn_80286570()) {
        return FALSE;
    }
    __DIRegs[7] = 1;
    SetTimeoutAlarm(OSSecondsToTicks(30));
    return TRUE;
}

static BOOL fn_8028607C(u32 a, u32 b, u32 c, DVDLowCallback callback) {
    Callback = callback;
    StopAtNextInt = FALSE;
    fn_80286314(a, b, c);
    if (fn_80286570()) {
        __DIRegs[7] = 1;
        SetTimeoutAlarm(OSSecondsToTicks(30));
    }
    return TRUE;
}

BOOL DVDLowAudioStream(u32 subcmd, u32 length, u32 offset, DVDLowCallback callback) {
    return FALSE;
}

BOOL DVDLowRequestAudioStatus(u32 subcmd, DVDLowCallback callback) {
    return FALSE;
}

BOOL DVDLowAudioBufferConfig(BOOL enable, u32 size, DVDLowCallback callback) {
    return FALSE;
}

void DVDLowReset(void) {
    u32 reg;
    OSTime resetStart;

    __DIRegs[1] = 2;
    reg = __PIRegs[9];
    __PIRegs[9] = (reg & ~4) | 1;

    resetStart = __OSGetSystemTime();
    while ((__OSGetSystemTime() - resetStart) < OSMicrosecondsToTicks(12))
        ;

    __PIRegs[9] = reg | 5;
    ResetOccurred = TRUE;
    LastResetEnd = __OSGetSystemTime();
}

BOOL DVDLowBreak(void) {
    StopAtNextInt = TRUE;
    Breaking = TRUE;
    return TRUE;
}

DVDLowCallback DVDLowClearCallback(void) {
    DVDLowCallback old;
    __DIRegs[1] = 0;
    old = Callback;
    Callback = NULL;
    return old;
}

void __DVDLowSetWAType(u32 type, u32 location) {
    BOOL enabled;
    enabled = OSDisableInterrupts();
    WorkAroundType = type;
    WorkAroundSeekLocation = location;
    OSRestoreInterrupts(enabled);
}

static void fn_8028625C(u32 cmd, u32 offset, u32 length) {
    u32 v[11];
    u16 key = ((fn_802867B8(0, 0x7FFF) << 1) & 0x1FFFE) + 1;

    v[0] = ((key << 16) | cmd) ^ __DIKey->cmd;
    v[1] = offset ^ __DIKey->offset;
    v[2] = length ^ __DIKey->length;
    __DIKey->cmd *= key;
    __DIKey->offset *= key;
    __DIKey->length *= key;
    __DIRegs[2] = v[0];
    __DIRegs[3] = v[1];
    __DIRegs[4] = v[2];
}
