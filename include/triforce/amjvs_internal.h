#ifndef TRIFORCE_AMJVS_INTERNAL_H
#define TRIFORCE_AMJVS_INTERNAL_H

/* Triforce JVS I/O manager: queues per-node output requests and polls inputs. */
#include <dolphin.h>
#include <string.h>

typedef struct JvsNode {
    /* 0x00 */ u8 pad0[0xAC];
    /* 0xAC */ u8* sw;
    /* 0xB0 */ u8* analog;
    /* 0xB4 */ u8* coin;
    /* 0xB8 */ u8 padB8[0xCC - 0xB8];
    /* 0xCC */ u8 players;
    /* 0xCD */ u8 swBits;
    /* 0xCE */ u8 analogCh;
    /* 0xCF */ u8 coinSlots;
    /* 0xD0 */ u8 analogBits;
    /* 0xD1 */ u8 rotary;
    /* 0xD2 */ u8 keycode;
    /* 0xD3 */ u8 unkD3;
    /* 0xD4 */ u8 unkD4;
    /* 0xD5 */ u8 screenPos;
    /* 0xD6 */ u16 miscSw;
    /* 0xD8 */ u8 extAnalog;
    /* 0xD9 */ u8 unkD9;
    /* 0xDA */ u8 gpOut;
    /* 0xDB */ u8 padDB[5];
} JvsNode;

typedef struct JvsFeatures {
    u8 players, swBits, analogCh, coinSlots, analogBits;
    u8 rotary, keycode, unkD3, unkD4, screenPos;
    u16 miscSw;
    u8 extAnalog, unkD9;
} JvsFeatures;

typedef struct JvsEvent {
    u8 node;
    u8 cmd;
    u8 err;
    u8 pad;
} JvsEvent;

typedef struct JvsReq {
    /* 0x00 */ u8 n;
    /* 0x01 */ u8 pad1[0x80];
    /* 0x81 */ u8 cmd[0x20];
    /* 0xA1 */ u8 rlen[0x20];
    /* 0xC4 */ u32 resp[0x20];
} JvsReq;

typedef struct JvsCmd {
    /* 0x0000 */ u8 pad0[0x84];
    /* 0x0084 */ s32 cur[16];
    /* 0x00C4 */ u8 padC4[0x130C - 0xC4];
    /* 0x130C */ JvsReq req[2][16];
} JvsCmd;

typedef s32 (*JvsHandler)(u8 node, u8 cmd, u32 resp);

typedef struct JvsHandlerEntry {
    JvsHandler fn;
    u8 rlen;
} JvsHandlerEntry;

typedef struct JvsStats {
    s32 total;
    s32 count;
    s32 runs;
    s32 streak;
} JvsStats;

typedef struct JvsOutCfg {
    u8 data[0x10];
} JvsOutCfg;

typedef struct JvsMgrNode {
    /* 0x000 */ u32 flags;
    /* 0x004 */ u32 rawMask;
    /* 0x008 */ JvsStats err;
    /* 0x018 */ u8 arg[0x40];
    /* 0x058 */ void* data[0x40];
    /* 0x158 */ u32 used;
    /* 0x15C */ u8 buf[0x100];
} JvsMgrNode;

typedef struct JvsMgr {
    /* 0x0000 */ BOOL ready;
    /* 0x0004 */ u32 state;
    /* 0x0008 */ JvsMgrNode node[16];
    /* 0x25C8 */ BOOL outPending;
    /* 0x25CC */ JvsOutCfg out;
    /* 0x25DC */ BOOL resetPending;
    /* 0x25E0 */ OSSemaphore sem;
    /* 0x25EC */ JvsHandlerEntry handler[0x20];
    /* 0x26EC */ u8 pad26EC[0x1C];
} JvsMgr;

extern void fn_8028250C(void);
extern BOOL fn_80282AC8(u8 a, u8 b);
extern BOOL fn_80282B54(void);
extern BOOL fn_80282BB0(void);
extern BOOL fn_80282C0C(void);
extern BOOL fn_80282C68(u8 v);
extern BOOL fn_80282CDC(u32 v);
extern BOOL fn_80282DA8(void);
extern BOOL fn_80282E04(void);
extern void fn_80282E60(void);
extern BOOL fn_80282EB8(void);
extern void fn_80282F3C(void);
extern u8 fn_80283E3C(void);
extern JvsEvent fn_80283E54(void);
extern BOOL fn_80283E9C(void);
extern BOOL fn_80284480(u8 len, void* data, u8 rlen);
extern BOOL fn_80284518(u8 a, u16 v);
extern BOOL fn_802845D4(u8 a, u16 v);
extern BOOL fn_80284690(u8 len, void* data);
extern BOOL fn_80284754(u8 len, void* data);
extern BOOL fn_80284834(u8 a, u8 b);
extern BOOL fn_802848D8(u8 a, u8 b);
extern BOOL fn_8028497C(u8 len, void* data);
extern BOOL fn_80284A40(u8 a, u16 v);
extern BOOL fn_80284AFC(u8 a, u16 v);
extern BOOL fn_80284BB8(u8 a);
extern BOOL fn_80284C48(u8 a);
extern BOOL fn_80284CD8(u8 a);
extern BOOL fn_80284D68(void);
extern BOOL fn_80284DE4(u8 a);
extern BOOL fn_80284E78(u8 a);
extern BOOL fn_80284F0C(u8 a);
extern BOOL fn_80284FA0(u8 a, u8 b);
extern BOOL fn_80285048(const char* str);
extern BOOL fn_80285118(void);
extern BOOL fn_80285194(void);
extern BOOL fn_80285210(void);
extern BOOL fn_8028528C(void);
extern BOOL fn_80285308(void);
extern BOOL fn_80285384(u8 a);
extern BOOL fn_80285418(void);
extern BOOL fn_802854B0(void);
extern void fn_80285638(u8 node);
extern void fn_802856A4(void* cb);
extern u8* fn_80285778(void);
extern u8* fn_80285788(void);
extern u8* fn_802857A8(void);
extern JvsNode* fn_802857B8(void);
extern JvsCmd* fn_802857C8(void);
extern void* fn_802857D4(void);
extern s32 fn_80293580(void);
extern void fn_80293AF0(void);
extern void fn_80293B74(void);

extern JvsMgr amjvs_bss_806910B8;
#define Mgr amjvs_bss_806910B8

extern s16 amjvs_nm3_bss_806D1E30[4];
extern u32 amjvs_nm7_bss_806D1E38;
extern u32 amjvs_nm7_bss_806D1E3C;
#define AnalogBuf amjvs_nm3_bss_806D1E30
#define InitNode amjvs_nm7_bss_806D1E38
#define InitTimer amjvs_nm7_bss_806D1E3C

s32 fn_8028A598(s32 node, u8 n, u8* data);
s32 fn_8028A618(s32 node, u8 n, u8* data);
s32 fn_8028A740(s32 node, u32 ch);
s32 fn_8028A808(s32 node, u8* slots, u8* bits);
s32 fn_8028A8B4(s32 node, u8 idx, s16 v);
s32 fn_8028A934(s32 node, u8 idx, s16 v);
s32 fn_8028AA40(s32 node, s16** out, u8* count);
s32 fn_8028AAC0(s32 node, s16** out, u8* chans);
s32 fn_8028AC1C(s32 node, u32 ch);
s32 fn_8028ACEC(s32 node, u8* chans);
s32 fn_8028AD94(s32 node, u8** sw, u8* players, u8* bits);
s32 fn_8028AE64(s32 node, u8 player, u8 byte);
s32 fn_8028AF48(s32 node, u8* players, u8* bits);
s32 fn_8028AFF4(JvsOutCfg* out);
u8 fn_8028B090(void);
u8 fn_8028B0B4(void);
s32 fn_8028B0D8(s32 node, JvsStats* out);
void fn_8028B180(BOOL filter);
s32 fn_8028B3D0(u8 node, u8 idx);
s32 fn_8028B48C(s32 node);
s32 fn_8028B9A4(void);
s32 fn_8028BAD0(void);
s32 fn_8028BFB0(void);
s32 fn_8028BFD4(void);

#endif
