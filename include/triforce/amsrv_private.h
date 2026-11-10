#include "game/types/le.h"
#ifndef TRIFORCE_AMSRV_PRIVATE_H
#define TRIFORCE_AMSRV_PRIVATE_H
/* Triforce media board service: board-side requests that read and write
 * game memory, plus the two link status blocks. */
#include <dolphin.h>
#include <string.h>

typedef struct NetPacket {
    /* 0x00 */ u8 id;
    /* 0x01 */ u8 sub;
    /* 0x02 */ u16 flags;
    /* 0x04 */ u32 result;
    /* 0x08 */ u32 arg[6];
} NetPacket;

typedef struct NetLinkA {
    /* 0x00 */ u32 cfg[6];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ OSSemaphore sem;
    /* 0x2C */ s32 ready;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 busy;
    /* 0x34 */ s32 result;
    /* 0x38 */ u32 cfg0;
    /* 0x3C */ u8 pad3C[4];
} NetLinkA;

typedef struct NetLinkB {
    /* 0x00 */ u32 cfg0;
    /* 0x04 */ u32 cfg1;
    /* 0x08 */ u32 unk08;
    /* 0x0C */ u32 cfg2;
    /* 0x10 */ u32 cfg3;
    /* 0x14 */ OSSemaphore sem;
    /* 0x20 */ s32 ready;
    /* 0x24 */ u32 unk24[2];
    /* 0x2C */ u32 cfg0b;
    /* 0x30 */ u8 pad30[0x10];
} NetLinkB;

extern NetPacket* fn_8028CE34(u8 ch);
extern NetPacket* fn_8028CF1C(u8 ch);
extern s32 fn_8028D3E4(u8 ch);
extern u32* fn_8028D6B0(void);
extern s32 fn_8028F45C(void);

#define BSWAP16(v) LE_AS_WRITTEN(((((v) << 8) & 0xFF00) | (((v) >> 8) & 0xFF)), (v))
#define BSWAP32(v) LE_AS_WRITTEN((((v) << 24) | (((v) << 8) & 0xFF0000) | (((v) >> 8) & 0xFF00) | ((v) >> 24)), (v))


#define REPLY(rsp, req)                                     \
    do {                                                    \
        (rsp)->id = (req)->id;                              \
        (rsp)->sub = (req)->sub;                            \
        (rsp)->flags = BSWAP16(BSWAP16((req)->flags) | 0x8000); \
    } while (0)

#endif
