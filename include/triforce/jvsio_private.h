#ifndef TRIFORCE_JVSIO_PRIVATE_H
#define TRIFORCE_JVSIO_PRIVATE_H
/* Triforce JVS I/O over SI channel 0. */
#include <dolphin.h>

typedef struct JvsRing {
    /* 0x0 */ u16 size;
    /* 0x2 */ u16 rd;
    /* 0x4 */ u16 wr;
    /* 0x8 */ u8* buf;
    /* 0xC */ u8 state;
    /* 0xD */ u8 unkD;
    /* 0xE */ u8 unkE;
    /* 0xF */ u8 unkF;
} JvsRing;

typedef struct JvsReq {
    /* 0x00 */ u8 n;
    /* 0x01 */ u8 response[0x80];
    /* 0x81 */ u8 cmd[0x20];
    /* 0xA1 */ u8 rlen[0x20];
    /* 0xC1 */ u8 padC1[3];
    /* 0xC4 */ u8* reply[0x20];
} JvsReq;

typedef struct JvsNode {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1[0x65 - 0x1];
    /* 0x65 */ u8 unk65[0x41];
    /* 0xA6 */ u8 unkA6;
    /* 0xA7 */ u8 unkA7;
    /* 0xA8 */ u8 unkA8;
    /* 0xAC */ void* unkAC;
    /* 0xB0 */ void* unkB0;
    /* 0xB4 */ void* unkB4;
    /* 0xB8 */ void* unkB8;
    u8 unkBC;
    u8 padBD[3];
    void* unkC0;
    void* unkC4;
    u8 padC8[4];
    /* 0xCC */ u8 unkCC;
    /* 0xCD */ u8 unkCD;
    /* 0xCE */ u8 unkCE;
    /* 0xCF */ u8 unkCF;
    /* 0xD0 */ u8 unkD0;
    /* 0xD1 */ u8 unkD1;
    /* 0xD2 */ u8 unkD2;
    /* 0xD3 */ u8 unkD3;
    /* 0xD4 */ u8 unkD4;
    /* 0xD5 */ u8 unkD5;
    /* 0xD6 */ u16 unkD6;
    /* 0xD8 */ u8 unkD8;
    /* 0xD9 */ u8 unkD9;
    /* 0xDA */ u8 unkDA;
    /* 0xDB */ u8 unkDB;
    /* 0xDC */ u8 unkDC;
    /* 0xDD */ u8 unkDD;
    /* 0xDE */ u8 unkDE;
    /* 0xDF */ u8 unkDF;
} JvsNode;

typedef struct JvsEvent {
    u8 node;
    u8 cmd;
    u8 err;
    u8 pad;
} JvsEvent;

typedef struct JvsCmd {
    /* 0x0000 */ u8 buf[0x80];
    /* 0x0080 */ u16 len;
    /* 0x0084 */ s32 cur[16];
    /* 0x00C4 */ s32 next[16];
    /* 0x0104 */ u32 unk104;
    /* 0x0108 */ u8 unk108;
    /* 0x0109 */ u8 nodeCount;
    /* 0x010A */ u8 qrd;
    /* 0x010B */ u8 qwr;
    /* 0x010C */ JvsEvent queue[256];
    /* 0x050C */ JvsNode node[16];
    /* 0x130C */ JvsReq req[2][16];
    /* 0x3B8C */ u8 pad3B8C[0x4FCC - 0x3B8C];
    /* 0x4FCC */ JvsReq* curReq;
    /* 0x4FD0 */ u8 pad4FD0[0x10];
} JvsCmd;

typedef struct JvsTx {
    /* 0x000 */ u8 buf[0x80];
    /* 0x080 */ u8 rx[0x80];
    /* 0x100 */ u32 err[4];
    /* 0x110 */ u16 len;
    /* 0x112 */ u8 pad112[2];
    /* 0x114 */ u8 result;
    /* 0x115 */ u8 unk115;
    /* 0x116 */ u8 unk116;
    /* 0x117 */ u8 unk117[3];
    /* 0x11A */ u8 unk11A[0x10];
    /* 0x12A */ u8 unk12A;
    /* 0x12B */ u8 unk12B;
    /* 0x12C */ u16 analog[4];
    /* 0x134 */ u8 unk134;
    /* 0x135 */ u8 unk135;
    /* 0x136 */ u8 unk136;
    /* 0x137 */ u8 unk137;
    /* 0x138 */ u32 unk138;
    /* 0x13C */ u8 unk13C[0x10];
    /* 0x14C */ u16 packetCount;
    /* 0x150 */ u8* packet[64];
    /* 0x250 */ JvsRing ring[2];
} JvsTx;

extern JvsCmd jvsio_bss_8067E2A0;
extern JvsTx jvsio_bss_80683280;

#endif
