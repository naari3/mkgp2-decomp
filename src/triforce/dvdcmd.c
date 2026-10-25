/* Triforce extra DVD commands (0x65-0x67), issued through dvd.c's queue. */
#include <dolphin.h>
#include <dolphin/dvd.h>

typedef BOOL (*IssueCommand)(s32 prio, DVDCommandBlock* block);

extern void* __DVDGetIssueCommandAddr(void);
extern OSThreadQueue __DVDThreadQueue;

BOOL fn_80286934(DVDCommandBlock* block, void* addr, s32 length, s32 offset, DVDCBCallback callback,
                 s32 prio) {
    block->command = 0x66;
    block->addr = addr;
    block->length = length;
    block->offset = offset;
    block->transferredSize = 0;
    block->callback = callback;
    return ((IssueCommand)__DVDGetIssueCommandAddr())(prio, block);
}

static inline BOOL Cmd65Async(DVDCommandBlock* block, DVDCBCallback callback) {
    block->command = 0x65;
    block->callback = callback;
    return ((IssueCommand)__DVDGetIssueCommandAddr())(2, block);
}

static void cbForCmd65Sync(s32 result, DVDCommandBlock* block);

s32 fn_802869A0(DVDCommandBlock* block) {
    BOOL result;
    s32 state;
    BOOL enabled;
    s32 retVal;

    result = Cmd65Async(block, cbForCmd65Sync);

    if (result == FALSE) {
        return -1;
    }

    enabled = OSDisableInterrupts();

    while (TRUE) {
        state = ((volatile DVDCommandBlock*)block)->state;

        if (state == 0 || state == -1 || state == 10) {
            retVal = (s32)block->transferredSize;
            break;
        }

        OSSleepThread(&__DVDThreadQueue);
    }

    OSRestoreInterrupts(enabled);
    return retVal;
}

static void cbForCmd65Sync(s32 result, DVDCommandBlock* block) {
    block->transferredSize = (u32)result;
    OSWakeupThread(&__DVDThreadQueue);
}

static inline BOOL Cmd67Async(DVDCommandBlock* block, u32 arg, DVDCBCallback callback) {
    u32 len = arg;
    block->command = 0x67;
    block->length = len;
    block->callback = callback;
    return ((IssueCommand)__DVDGetIssueCommandAddr())(2, block);
}

static void cbForCmd67Sync(s32 result, DVDCommandBlock* block);

s32 fn_80286A74(DVDCommandBlock* block, u32 arg) {
    BOOL result;
    s32 state;
    BOOL enabled;
    s32 retVal;

    result = Cmd67Async(block, arg, cbForCmd67Sync);

    if (result == FALSE) {
        return -1;
    }

    enabled = OSDisableInterrupts();

    while (TRUE) {
        state = ((volatile DVDCommandBlock*)block)->state;

        if (state == 0 || state == -1 || state == 10) {
            retVal = (s32)block->transferredSize;
            break;
        }

        OSSleepThread(&__DVDThreadQueue);
    }

    OSRestoreInterrupts(enabled);
    return retVal;
}

static void cbForCmd67Sync(s32 result, DVDCommandBlock* block) {
    block->transferredSize = (u32)result;
    OSWakeupThread(&__DVDThreadQueue);
}
