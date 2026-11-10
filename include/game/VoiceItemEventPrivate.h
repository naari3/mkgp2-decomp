#ifndef GAME_VOICE_ITEM_EVENT_PRIVATE_H
#define GAME_VOICE_ITEM_EVENT_PRIVATE_H
#include "game/RaceVoiceRivalPrivate.h"

#include "game/types/VoiceItemMap.h"
typedef struct VoiceItemData {
    short f0[14], normal[14], raceStart[14], f54[52], special[52];
    unsigned char unknown124[0x118C-0x124];
    VoiceItemMap maps[156];
    VoiceClip clips[660];
} VoiceItemData;
extern unsigned char g_voiceSystemInitDone, g_goalFanfareTriggered, g_bgmStateId;
extern signed char lbl_806D1774, lbl_806D1775, lbl_806D1776, lbl_806D1777, lbl_806D177C;
extern short lbl_806CFD34;
extern void *SyncSlot_GetHostSend(void);

static inline short ItemVoice(VoiceItemData *data, int item, int response) {
    VoiceItemMap *map = data->maps;
    int i = 0;
    while (map->item != -1) {
        if (item == map->item) {
            VoiceItemMap *base = data->maps;
            if (response) return base[i].response;
            return base[i].attack;
        }
        map++;
        i++;
    }
    return -1;
}
#define PUSH(v,p) VoiceQueue_Push((v),(p),1,1)
#define CHARACTER(i) RaceVoice_Character((RaceVoiceData *)data,g_raceEntryArray[i].character,g_raceEntryArray[i].id)
#define THIRD(a,b,c,p) do { if (g_voiceTickCounter % 3 == 0) PUSH(a,p); else if (g_voiceTickCounter % 3 == 1) PUSH(b,p); else PUSH(c,p); } while (0)
#define PAIR(a,b,p) do { if ((g_voiceTickCounter & 1) == 0) PUSH(a,p); else PUSH(b,p); } while (0)


#endif
