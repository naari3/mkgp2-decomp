/* Triforce DI command key exchange. */
#include <dolphin.h>
#include <dolphin/hw_regs.h>

typedef struct DIKey {
    u32 cmd;
    u32 offset;
    u32 length;
} DIKey;

extern DIKey* __DIKey;
extern BOOL __OSInIPL;
extern u32 fn_802867B8(u32 min, u32 max);
extern BOOL fn_80286864(u32 num, u32 den);

static u32 KeyReady = TRUE;
static BOOL KeyDone0;
static BOOL KeyDone1;
static BOOL KeyDone2;
static u32 NewKey0;
static u32 NewKey1;
static u32 NewKey2;
static u32 KeyPhase;

static DIKey SavedKey;

void fn_80286314(u32 cmd, u32 offset, u32 length) {
    NewKey0 = cmd;
    KeyDone0 = FALSE;
    KeyDone1 = FALSE;
    KeyDone2 = FALSE;
    NewKey1 = offset;
    NewKey2 = length;
    KeyPhase = 1;
    KeyReady = FALSE;
}

static inline u16 SameParity(int shift) {
    u8 a;
    u8 b;
    a = fn_802867B8(0, 0x7F);
    a <<= shift;
    b = fn_802867B8(0, 0x7F);
    b <<= shift;
    if (fn_80286864(1, 2)) {
        a++;
        b++;
    }
    return (a << 8) + b;
}

static inline u16 DiffParity(int shift) {
    u8 a;
    u8 b;
    a = fn_802867B8(0, 0x7F);
    a <<= shift;
    b = fn_802867B8(0, 0x7F);
    b <<= shift;
    if (fn_80286864(1, 2)) {
        a++;
    } else {
        b++;
    }
    return (a << 8) + b;
}

static BOOL fn_80286340(BOOL done, u32 key, u16* check, u32* value) {
    BOOL ret;

    if (done) {
        *value = fn_802867B8(0, 0x7FFFFFFF);
        ret = FALSE;
        if (fn_80286864(50, 100)) {
            *check = SameParity(1);
        } else {
            *check = DiffParity(1);
        }
    } else if (fn_80286864(20, 100)) {
        *check = SameParity(1);
        ret = TRUE;
        *value = key;
    } else {
        *check = DiffParity(1);
        *value = fn_802867B8(0, 0x7FFFFFFF);
        ret = FALSE;
    }
    return ret;
}

BOOL fn_80286570(void) {
    u16 check0;
    u16 check1;
    u16 check2;
    u32 value0;
    u32 value1;
    u32 value2;
    BOOL ret;

    if (KeyReady) {
        return FALSE;
    }
    if (KeyPhase) {
        KeyPhase ^= 1;
        ret = fn_80286340(KeyDone0, NewKey0, &check0, &value0);
        KeyDone0 = KeyDone0 || ret;
        __DIRegs[2] = (check0 << 16) | (value0 >> 16);
        ret = fn_80286340(KeyDone1, NewKey1, &check1, &value1);
        KeyDone1 = KeyDone1 || ret;
        __DIRegs[3] = (value0 << 16) | check1;
        __DIRegs[4] = value1;
    } else {
        KeyPhase ^= 1;
        ret = fn_80286340(KeyDone2, NewKey2, &check2, &value2);
        KeyDone2 = KeyDone2 || ret;
        __DIRegs[2] = (check2 << 16) | (value2 >> 16);
        __DIRegs[3] = value2 << 16;
        if (KeyDone0 && KeyDone1 && KeyDone2) {
            __DIRegs[4] = 0xFFFF;
            __DIKey->cmd = NewKey0;
            __DIKey->offset = NewKey1;
            __DIKey->length = NewKey2;
            KeyReady = TRUE;
            return TRUE;
        }
        __DIRegs[4] = 0;
    }
    return TRUE;
}

void fn_80286730(void) {
    if (__OSInIPL) {
        __DIKey = (DIKey*)0x80000000;
        return;
    }
    SavedKey.cmd = ((DIKey*)0x80000000)->cmd;
    SavedKey.offset = ((DIKey*)0x80000000)->offset;
    SavedKey.length = ((DIKey*)0x80000000)->length;
    __DIKey = &SavedKey;
}

void fn_80286774(void) {
    if (!__OSInIPL) {
        ((DIKey*)0x80000000)->cmd = SavedKey.cmd;
        ((DIKey*)0x80000000)->offset = SavedKey.offset;
        ((DIKey*)0x80000000)->length = SavedKey.length;
    }
    __DIKey = (DIKey*)0x80000000;
}
