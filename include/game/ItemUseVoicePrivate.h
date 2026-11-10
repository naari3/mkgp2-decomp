#ifndef GAME_ITEM_USE_VOICE_PRIVATE_H
#define GAME_ITEM_USE_VOICE_PRIVATE_H
#include "game/RaceVoiceRivalPrivate.h"

#include "game/types/ItemUseVoiceItem.h"
typedef struct ItemUseVoiceMap { short item, voice, unused; } ItemUseVoiceMap;

extern ItemUseVoiceItem *GetItemDataEntry_Bounded(int);
extern unsigned char ItemClass_GetFlagByte1(int);
extern int fn_801B3D40(int);
extern void *SyncSlot_GetHostSend(void);
extern float fn_801A19FC(void *, void *);
extern float fn_801A1828(void *, void *);
extern unsigned char g_voiceSystemInitDone, g_goalFanfareTriggered, g_bgmStateId;
extern unsigned char lbl_806D1774, lbl_806D1775, lbl_806D1776, lbl_806D1777, lbl_806D177C;
extern short lbl_806CFD34;
extern int lbl_806D1778;
extern OSTime g_bgmStateTimeHi;
extern float lbl_806D1788;

static inline void *ItemVoice_Kart(RaceVoiceEntry *entry) {
    return *(void **)entry->pad44;
}
static inline short ItemVoice_Lookup(RaceVoiceData *data, int item) {
    ItemUseVoiceMap *map = (ItemUseVoiceMap *)data->pad118C;
    int i;
    for (i = 0; map[i].item != -1; i++) {
        if (item == map[i].item) return ((ItemUseVoiceMap *)data->pad118C)[i].voice;
    }
    return -1;
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
