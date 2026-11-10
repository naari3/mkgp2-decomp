#ifndef TRIFORCE_AMUART_PRIVATE_H
#define TRIFORCE_AMUART_PRIVATE_H
#include "game/types/bitfields.h"

#include <dolphin.h>

typedef struct UartCfg {
    /* 0x0 */ u8 mode;
    /* 0x1 */ BITFIELDS3(u8 enable:1, u8 parity:2, u8 unk1:5)
    BITFIELDS2(u8 unk2:1, u8 baud:7) /* 0x2 */
    /* 0x3 */ u8 stop;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 unk5;
} UartCfg;

typedef struct UartChan {
    /* 0x00 */ s32 active;
    /* 0x04 */ s32 cfgPending;
    /* 0x08 */ UartCfg cfg;
    /* 0x0E */ u8 pad0E[2];
    /* 0x10 */ u16 maxRead;
    /* 0x14 */ u8* buf;
    /* 0x18 */ u16 size;
    /* 0x1A */ u16 head;
    /* 0x1C */ u16 tail;
    /* 0x20 */ s32 newFirm;
} UartChan;

typedef struct JvsPort {
    /* 0x0 */ u8 unk0[0xF];
    /* 0xF */ u8 flags;
} JvsPort;

typedef struct UartState {
    /* 0x00 */ UartChan chan[2];
    /* 0x48 */ OSSemaphore sem;
} UartState;

extern u8 amuart_bss_806A1CE0[0x80];
extern UartState amuart_bss_806A1D60;

#endif
