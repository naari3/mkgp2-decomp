#include "game/VoiceItemEventPrivate.h"

/* The scan cursor is independent of the indexed attack/response reads. */
static inline VoiceItemMap *ItemMaps(VoiceItemData *data) {
    return (VoiceItemMap *)((unsigned int)data + 0x118C);
}

static inline short EventItemVoice(VoiceItemData *data, int item, int response) {
    VoiceItemMap *map = ItemMaps(data);
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

static inline short RemapItemVoice(short item) {
    short voice;
    voice=item;
    switch (item) {
    case 0x7B: voice=0x3D; break;
    case 0x7C: voice=0x32; break;
    case 0x7D: voice=0x17; break;
    case 0x7E: voice=0x50; break;
    case 0x7F: voice=0x39; break;
    case 0x80: voice=0x40; break;
    case 0x81: voice=0x2B; break;
    case 0x82: voice=0x46; break;
    case 0x83: voice=0x5D; break;
    case 0x84: voice=0x2D; break;
    case 0x85: voice=0x55; break;
    case 0x86: voice=0x4E; break;
    case 0x87: voice=0x3E; break;
    }
    return voice;
}

#pragma use_lmw_stmw on
#pragma exceptions on
int fn_801B1D5C(RaceVoiceRival *kart, RaceVoiceRival *target, short item, unsigned char mode) {
    short voice;
    void *held;
    VoiceItemData *data = (VoiceItemData *)&lbl_80496C38;
    if (!g_voiceSystemInitDone) return 0;
    if (!kart) return 0;
    if (!target) return 0;
    held = g_raceEntryArray[target->playerIndex].item;
    if (held && KartItem_GetByte_f4(held)) { g_bgmStateId = 0; return 0; }
    voice=RemapItemVoice(item);
    g_raceEntryArray[target->playerIndex].state=3;
    g_raceEntryArray[kart->playerIndex].state=2;
    g_raceEntryArray[kart->playerIndex].driver=(RaceVoiceDriver *)target;
    if (g_gameMode==2 && !SyncSlot_GetHostSend()) return 1;
    if (g_goalFanfareTriggered) return 1;
    if ((int)g_bgmStateId==7 && lbl_806D1775==kart->playerIndex && lbl_806D1776==target->playerIndex) {
        PUSH(CHARACTER(lbl_806D1776),7);
        THIRD(0x1C6,0x1D7,0x1D8,7);
        g_bgmStateId=0;
    }
    if ((signed char)g_bgmStateId==0x6E) {
        if (lbl_806D1776==-1) {
            if (lbl_806D1775==kart->playerIndex && voice==lbl_806CFD34) {
                voice=EventItemVoice(data,voice,1);
                lbl_806D1776=target->playerIndex;
                if (voice!=-1 && data->clips[voice].playCount==0) {
                    PUSH(CHARACTER(lbl_806D1776),11);
                    PUSH(voice,11);
                    g_bgmStateId=0;
                } else {
                    THIRD(0x1C8,0x25A,0x25B,11);
                    lbl_806D1774=1;
                    if (data->clips[0x1E5].playCount==0 && g_raceEntryArray[lbl_806D1775].f32>g_raceEntryArray[lbl_806D1776].f32) {
                        PUSH(CHARACTER(lbl_806D1775),11);
                        PUSH(0x1E5,11);
                        g_bgmStateId=0;
                    } else lbl_806D177C=g_raceEntryArray[lbl_806D1776].player;
                }
            }
        } else if (lbl_806D1776==kart->playerIndex) {
            PUSH(0x1CD,11);
            PUSH(CHARACTER(lbl_806D1776),11);
            PAIR(0x1CE,0x1CF,11);
            g_bgmStateId=0;
        } else if (lbl_806D1776==target->playerIndex) {
            if ((g_voiceTickCounter&1)==0) PUSH(0x1EA,11);
            else { PUSH(0x1CD,11); PUSH(0x1EB,11); }
            g_bgmStateId=0;
        }
        return 1;
    } else if ((signed char)g_bgmStateId==0x6F) {
        if (lbl_806D1776==-1) {
            if (lbl_806D1775==kart->playerIndex && voice==lbl_806CFD34) {
                lbl_806D1776=target->playerIndex;
                if (g_voiceTickCounter%3==0) PUSH(0x1C8,11);
                else if (g_voiceTickCounter%3==1) { PUSH(CHARACTER(lbl_806D1776),11); PUSH(0x1C6,11); }
                else { PUSH(CHARACTER(lbl_806D1776),11); PUSH(0x1C7,11); }
                if (data->clips[0x1E5].playCount==0 && g_raceEntryArray[lbl_806D1775].f32>g_raceEntryArray[lbl_806D1776].f32) {
                    PUSH(CHARACTER(lbl_806D1775),11);
                    PUSH(0x1E5,11);
                    g_bgmStateId=0;
                } else lbl_806D177C=g_raceEntryArray[lbl_806D1776].player;
            }
        } else if (lbl_806D1776==kart->playerIndex) {
            PUSH(0x1CD,11);
            PUSH(CHARACTER(lbl_806D1776),11);
            PAIR(0x1CE,0x1CF,11);
            g_bgmStateId=0;
        } else if (lbl_806D1776==target->playerIndex) {
            if ((g_voiceTickCounter&1)==0) PUSH(0x1EA,11);
            else { PUSH(0x1CD,11); PUSH(0x1EB,11); }
            g_bgmStateId=0;
        }
        return 1;
    } else if ((signed char)g_bgmStateId==14) {
        if (lbl_806D1776==target->playerIndex) {
            if ((g_voiceTickCounter&1)==0) PUSH(0x1EA,14);
            else { PUSH(0x1CD,14); PUSH(0x1EB,14); }
            g_bgmStateId=0;
        }
        return 1;
    }
    if (!RaceVoice_CanQueue(9)) return 1;
    if (g_raceEntryArray[target->playerIndex].participant) {
        if (g_raceEntryArray[target->playerIndex].id>=0 && g_raceEntryArray[target->playerIndex].id!=0) {
            if (voice==0x30 || voice==0x31) {
                VoiceQueue_Push(CHARACTER(target->playerIndex),9,0,1);
                VoiceQueue_Push(EventItemVoice(data,voice,0),9,0,0);
                VoiceQueue_Push(0x1D4,9,0,0);
                VoiceQueue_Push(0x1DE,9,0,0);
                return 1;
            } else if (voice==0x2E || voice==0x2F) {
                VoiceQueue_Push(CHARACTER(target->playerIndex),9,0,1);
                VoiceQueue_Push(EventItemVoice(data,voice,0),9,0,0);
                VoiceQueue_Push(0x1D4,9,0,0);
                VoiceQueue_Push(0x1DF,9,0,0);
                return 1;
            }
        }
        if (!RaceVoice_CanQueue(13)) return 1;
    }
    if (g_raceEntryArray[target->playerIndex].participant && EventItemVoice(data,voice,1)!=-1) {
        PUSH(CHARACTER(target->playerIndex),13);
        PUSH(EventItemVoice(data,voice,1),13);
        return 1;
    }
    if (!mode) {
        lbl_806D1775=kart->playerIndex;
        lbl_806D1776=target->playerIndex;
        if ((g_raceEntryArray[lbl_806D1775].participant || g_raceEntryArray[lbl_806D1776].participant) && EventItemVoice(data,voice,0)!=-1) {
            if (PUSH(CHARACTER(lbl_806D1776),14)) {
                PUSH(EventItemVoice(data,voice,0),14);
                PAIR(0x1D4,0x1D5,14);
                g_bgmStateId=14;
                lbl_806D1777=g_raceEntryArray[lbl_806D1775].player;
                lbl_806D177C=g_raceEntryArray[lbl_806D1776].player;
            }
            return 1;
        }
    }
    if (mode) {
        lbl_806D1775=kart->playerIndex;
        lbl_806D1776=target->playerIndex;
        if ((g_raceEntryArray[lbl_806D1775].participant || g_raceEntryArray[lbl_806D1776].participant) && EventItemVoice(data,voice,0)!=-1) {
            if (PUSH(CHARACTER(lbl_806D1776),15)) {
                PUSH(EventItemVoice(data,voice,0),15);
                PAIR(0x1ED,0x1EE,15);
                g_bgmStateId=15;
                lbl_806D1777=g_raceEntryArray[lbl_806D1775].player;
                lbl_806D177C=g_raceEntryArray[lbl_806D1776].player;
            }
            return 1;
        }
    }
    return 1;
}

#pragma exceptions reset
#pragma use_lmw_stmw reset
