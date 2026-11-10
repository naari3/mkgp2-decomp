#ifndef GAME_ITEM_USE_VOICE_801B4548_PRIVATE_H
#define GAME_ITEM_USE_VOICE_801B4548_PRIVATE_H
#include "game/VoiceItemEventPrivate.h"

#include "game/types/ItemUseVoiceItem.h"

extern ItemUseVoiceItem *GetItemDataEntry_Bounded(int);
extern unsigned char ItemClass_GetFlagByte1(int);
extern int fn_801B3D40(int);
extern float fn_801A19FC(void *, void *);
extern float fn_801A1828(void *, void *);

extern int lbl_806D1778;
/* The announcer stores the timer as separate high/low words. */
extern unsigned int g_bgmStateTimeHi, g_bgmStateTimeLo;
extern float lbl_806D1788;

static inline void *ItemVoice_Kart(RaceVoiceEntry *entry) {
    return *(void **)entry->pad44;
}
static inline short ItemVoice_BaseItem(short item) {
    switch (item) {
    case 0x7B: item = 0x3D; break;
    case 0x7C: item = 0x32; break;
    case 0x7D: item = 0x17; break;
    case 0x7E: item = 0x50; break;
    case 0x7F: item = 0x39; break;
    case 0x80: item = 0x40; break;
    case 0x81: item = 0x2B; break;
    case 0x82: item = 0x46; break;
    case 0x83: item = 0x5D; break;
    case 0x84: item = 0x2D; break;
    case 0x85: item = 0x55; break;
    case 0x86: item = 0x4E; break;
    case 0x87: item = 0x3E; break;
    }
    return item;
}
#endif
