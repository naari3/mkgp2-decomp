#ifndef TRIFORCE_ACSOCKET_PRIVATE_H
#define TRIFORCE_ACSOCKET_PRIVATE_H

/* Triforce media board BSD-style socket API (ac*). Each socket slot tracks
 * one outstanding board request; buffers are staged through board memory. */
#include <dolphin.h>
#include <string.h>

extern char* strtok(char* str, const char* delim);
extern long strtol(const char* str, char** end, int base);

typedef struct AcSock {
    /* 0x00 */ s32 ready;
    /* 0x04 */ u8 id;
    /* 0x05 */ u8 cmd;
    /* 0x08 */ s32 result;
    /* 0x0C */ u32 bufAddr;
    /* 0x10 */ u32 addrOff;
    /* 0x14 */ void* addr;
    /* 0x18 */ u32 lenOff;
    /* 0x1C */ u32* len;
} AcSock;

typedef struct AcState {
    /* 0x00 */ u32 sockBase;
    /* 0x04 */ u32 sockStride;
    /* 0x08 */ u32 unk08;
    /* 0x0C */ u32 devBase;
    /* 0x10 */ u32 bufOff;
    /* 0x14 */ u32 bufSize;
    /* 0x18 */ u32 txOff;
    /* 0x1C */ u32 txSize;
    /* 0x20 */ u32 rxOff;
    /* 0x24 */ u32 rxSize;
    /* 0x28 */ s32 alignTx;
    /* 0x2C */ s32 alignRx;
    /* 0x30 */ OSSemaphore sem;
    /* 0x3C */ AcSock sock[64];
} AcState;

extern void fn_8028D530(void* buf, u32 addr, u32 len);
extern void fn_8028D5E8(u32 addr, void* buf, u32 len);
extern s32 fn_8028F590(s32 a0, s32 a1, s32 a2);
extern s32 fn_8028F69C(u8 id);
extern s32 fn_8028F7EC(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 fn_8028F9BC(s32 mask, s32 a0, u32 a1, s32 a2, s32 a3);
extern s32 fn_8028FA70(s32 a0, u32 a1, u32 a2, u32 a3, u32 a4);
extern u8 fn_8028FC3C(s32 mask, s32 a0, u32 a1, s32 a2, s32 a3);
extern s32 fn_8028FCF0(u32 a0, u32 a1, s32 a2);
extern s32 fn_8028FEB8(s32 a0, s32 a1);
extern s32 fn_80290060(u32 a0, u32 a1);
extern s32 fn_802901F8(u8 id);
extern s32 fn_8029027C(s32 a0);
extern u8 fn_80290400(s32 mask, s32 a0, u32 a1, u32 a2);
extern s32 fn_802904C0(s32 a0);
extern s32 fn_80290644(s32 a0, u32 a1, u32 a2);
extern u8 fn_80290810(s32 mask, s32 a0, u32 a1, u32 a2);

#define BSWAP32(v) (((v) << 24) | (((v) << 8) & 0xFF0000) | (((v) >> 8) & 0xFF00) | ((v) >> 24))

extern u8 acsocket_nm7_bss_806992A0[0x4000];
extern u8 acsocket_nm6_bss_8069D2A0[0x4000];
extern u8 acsocket_nm7_bss_806A12A0[0x200];
extern AcState acsocket_nm7_bss_806A14A0;
#define RxBounce acsocket_nm7_bss_806992A0
#define TxBounce acsocket_nm6_bss_8069D2A0
#define Buf acsocket_nm7_bss_806A12A0
#define State acsocket_nm7_bss_806A14A0

static inline u32 SockAddr(AcSock* k, u32 off) {
    return k->bufAddr + off;
}

static inline u32 BufDev(AcSock* k, s32 n) {
    return SockAddr(k, State.bufOff + n);
}

static inline u8* BufPtr(s32 n) {
    return Buf + n;
}

/* Out-of-range descriptors fall back to slot 0. */
#define SOCK(s) (&State.sock[(s) & -((u32)(s) <= 63)])

static inline s32 CheckRange(u32 off, u32 len, u32 size) {
    if (off >= size || off + len > size) {
        return -1;
    }
    return 0;
}

static inline void GetAlign(s32* tx, s32* rx) {
    if (tx != NULL) {
        *tx = State.alignTx;
    }
    if (rx != NULL) {
        *rx = State.alignRx;
    }
}

void fn_80291C7C(AcSock*, void*, u32*, void*, u32*, void*, u32*, void*, u32*);
s32 acClosesocket(s32);
s32 fn_80292AD8(u8*, u32, s32, s32, s32);
s32 fn_80292D18(u32, u8*, s32, s32, s32);

#endif
