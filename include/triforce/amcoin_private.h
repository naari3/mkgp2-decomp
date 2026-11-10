#ifndef TRIFORCE_AMCOIN_PRIVATE_H
#define TRIFORCE_AMCOIN_PRIVATE_H
#include <dolphin.h>

typedef struct CoinConfig {
    /* 0x00 */ u8 creditMax;
    /* 0x01 */ u8 serviceMax;
    /* 0x02 */ u8 numPlayers;
    /* 0x03 */ u8 separate;
    /* 0x04 */ u8 commonService;
    /* 0x05 */ u8 serviceSplit;
    /* 0x06 */ u8 coinSetting;
    /* 0x07 */ u8 freePlay;
    /* 0x08 */ u8 coinMul[2];
    /* 0x0A */ u8 bonusDiv;
    /* 0x0B */ u8 coinsPerCredit;
    /* 0x0C */ u8 startCost[8];
    /* 0x14 */ u8 pad[0xC];
} CoinConfig;

typedef struct CoinSlot {
    /* 0x00 */ u32 credit;
    /* 0x04 */ u32 coin;
    /* 0x08 */ u32 perCredit;
    /* 0x0C */ u16 bonus;
    /* 0x0E */ u16 service;
} CoinSlot;

typedef struct CoinStats {
    /* 0x00 */ u32 coins[4];
    /* 0x10 */ u32 totalCoins;
    /* 0x14 */ u32 paidCredits;
    /* 0x18 */ u32 serviceCredits;
    /* 0x1C */ u32 allCredits;
    /* 0x20 */ u32 pad[8];
} CoinStats;

typedef struct CoinChute {
    /* 0x00 */ u16 count[4];
    /* 0x08 */ u32 timer;
    /* 0x0C */ u32 prev;
    /* 0x10 */ u32 hold[4];
} CoinChute;

typedef struct CoinEvent {
    u32 type;
    u32 chute;
    u32 index;
    u32 value;
} CoinEvent;

typedef struct StatusQueue {
    u32 head;
    u32 tail;
    u32 buf[16];
} StatusQueue;

typedef struct EventQueue {
    u32 head;
    u32 tail;
    CoinEvent buf[16];
} EventQueue;

typedef struct CoinTableEntry {
    u32 freePlay;
    u32 mul0;
    u32 mul1;
    u32 bonusDiv;
    u32 perCredit;
} CoinTableEntry;

typedef struct CoinState {
    /* 0x000 */ CoinConfig cfg;
    /* 0x020 */ CoinSlot slot[4];
    /* 0x060 */ CoinStats stats;
    /* 0x0A0 */ u32 dirty[3];
    /* 0x0AC */ u32 numChutes;
    /* 0x0B0 */ u32 chuteMode[3];
    /* 0x0BC */ CoinChute chute[3];
    /* 0x11C */ StatusQueue status;
    /* 0x164 */ EventQueue event;
    /* 0x26C */ OSSemaphore sem;
} CoinState;


#define Coin amcoin_state_bss_80690E40
#define StrBuf amcoin_bss_80690E20
#define Event amcoin_bss_80690E30
#define CoinTable amcoin_tables_rodata_803F2688
#define DefaultConfig amcoin_tail_rodata_803F2668

extern char StrBuf[0x10];
extern CoinEvent Event;
extern CoinState Coin;
extern const CoinConfig DefaultConfig;
extern const CoinTableEntry CoinTable[11];
extern const char lbl_806DC920[6];
extern const char lbl_806DC928[8];

char* fn_80288CC8(u32 slot);
BOOL fn_80288DEC(u32 type, u32 chute, u32 index, u32 value);
CoinEvent* fn_80288EAC(void);
BOOL fn_80288F6C(u32 slot, u32 game);
u32 fn_80289040(u32 slot, u32 game);
u32 fn_8028911C(u32 slot, u32 n);
s32 fn_80289324(u32 slot, u32 coins);
u32 fn_802894EC(u32 chute, u32 index);
s32 fn_802895E4(u32 chute, s32 n, u16* counters, u32 buttons);
s32 fn_80289A90(CoinStats* stats);
s32 fn_80289B04(CoinSlot* slots);
s32 fn_80289B7C(CoinConfig* cfg);
u32 fn_80289BEC(u32 i);
s32 fn_80289C68(u32 mode1, u32 mode2);
s32 fn_80289D4C(u8 max);
s32 fn_80289E20(void);
BOOL fn_80289E54(CoinSlot* slots, CoinConfig* cfg);
BOOL fn_80289ED8(CoinConfig* cfg);
s32 fn_8028A16C(CoinConfig* cfg, CoinSlot* slots, CoinStats* stats);
s32 fn_8028A3EC(CoinConfig* dst, u8* src);

#endif
