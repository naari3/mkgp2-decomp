#include "game/ItemUseVoice801B4548Private.h"

static inline float ItemVoiceLength801B(VoiceItemData *data, short voice) {
    return 2.0f + (data->clips[0x1C5].length + data->clips[voice].length);
}

#define ITEM_ENTRY_VOICE801B(e) RaceVoice_Character((RaceVoiceData *)data, (e)->character, (e)->id)

static inline int FindNearestVoiceKart801B(void) {
    int i;
    int nearest;
    float distance;
    float best;
    best = 10000.0f;
    nearest = -1;
    for (i = 0; i < 8; i++) {
        if (g_raceEntryArray[i].id != -1) {
            distance = fn_801A19FC(ItemVoice_Kart(&g_raceEntryArray[g_taMinLapPlayerIndex]),
                                  ItemVoice_Kart(&g_raceEntryArray[i]));
            if (0.0f <= distance && distance <= best) {
                nearest = i;
                best = distance;
            }
        }
    }
    return nearest;
}

#pragma use_lmw_stmw on

int fn_801B4548(int kart, int item) {
    VoiceItemData *data = (VoiceItemData *)&lbl_80496C38;
    RaceVoiceEntry *entry;
    int category;
    int i;
    int nearest;
    short voice;
    unsigned int variant;
    OSTime now;

    if (!g_voiceSystemInitDone) return 0;
    if (kart < 0 || kart >= 8) return 0;
    entry = &g_raceEntryArray[kart];
    entry->present = 1;
    entry->kind = item;
    category = GetItemDataEntry_Bounded(item)->category;
    if (category == 5) g_raceEntryArray[kart].rank = 1;
    else if (category == 6) g_raceEntryArray[kart].rank = 2;
    else if (category == 7) g_raceEntryArray[kart].rank = 2;
    else if (item == 8) g_raceEntryArray[kart].rank = 3;
    else if (item == 1) g_raceEntryArray[kart].rank = 3;
    else if (item == 2) g_raceEntryArray[kart].rank = 3;
    else if (item == 3) g_raceEntryArray[kart].rank = 3;
    else if (item == 4) g_raceEntryArray[kart].rank = 3;
    else if (item == 5) g_raceEntryArray[kart].rank = 3;
    else if (item == 6) g_raceEntryArray[kart].rank = 3;
    else if (item == 10) g_raceEntryArray[kart].rank = 3;
    else if (item == 9) g_raceEntryArray[kart].rank = 3;
    else if (item == 11) g_raceEntryArray[kart].rank = 3;
    else if (item == 7) g_raceEntryArray[kart].rank = 3;
    else if (item == 0x8F) g_raceEntryArray[kart].rank = 3;
    else if (item == 0x89) g_raceEntryArray[kart].rank = 3;
    else g_raceEntryArray[kart].rank = 5;

    if (item == 0x99) fn_801B3D40(kart);
    if (g_gameMode == 2 && SyncSlot_GetHostSend() == 0) return 1;
    if (g_goalFanfareTriggered) return 1;
    if ((signed char)g_bgmStateId != 0) return 1;
    if (!RaceVoice_CanQueue(11)) return 1;

    if (kart == g_taMinLapPlayerIndex && (signed char)ItemClass_GetFlagByte1(item) == 7) {
        nearest = FindNearestVoiceKart801B();
        if (nearest != -1 && ItemVoice(data, item, 0) != -1) {
            if (VoiceQueue_Push(ITEM_ENTRY_VOICE801B(&g_raceEntryArray[g_taMinLapPlayerIndex]), 7, 1, 1)) {
                VoiceQueue_Push(ItemVoice(data, item, 0), 7, 1, 1);
                VoiceQueue_Push(0x1D6, 7, 1, 1);
                g_bgmStateId = 7;
                now = OSGetTime();
                g_bgmStateTimeLo = (unsigned int)now;
                g_bgmStateTimeHi = (unsigned long long)now >> 32;
                lbl_806CFD34 = ItemVoice_BaseItem(item);
                lbl_806D1775 = g_taMinLapPlayerIndex;
                lbl_806D1776 = nearest;
                return 1;
            }
        }
    }

    if (kart == g_taMinLapPlayerIndex && (signed char)ItemClass_GetFlagByte1(item) == 5 &&
        item != 0x2E && item != 0x2F && item != 0x31 && item != 0x30) {
        for (i = 0; i < 8; i++) {
            if (g_raceEntryArray[i].id != -1 &&
                fn_801A1828(ItemVoice_Kart(&g_raceEntryArray[g_taMinLapPlayerIndex]),
                            ItemVoice_Kart(&g_raceEntryArray[i])) > 0.0f) {
                voice = ITEM_ENTRY_VOICE801B(entry);
                if (VoiceQueue_Push(voice, 11, 1, 1)) {
                    variant = g_voiceTickCounter % 3;
                    if (variant == 0) {
                        VoiceQueue_Push(ItemVoice(data, item, 0), 11, 1, 1);
                        VoiceQueue_Push(0x1C5, 11, 1, 1);
                    } else if (variant == 1) VoiceQueue_Push(0x17B, 11, 1, 1);
                    else VoiceQueue_Push(0x17C, 11, 1, 1);
                    g_bgmStateId = 0x6E;
                    lbl_806D1774 = 0;
                    now = OSGetTime();
                    g_bgmStateTimeLo = (unsigned int)now;
                    g_bgmStateTimeHi = (unsigned long long)now >> 32;
                    lbl_806D1788 = ItemVoiceLength801B(data, voice);
                    lbl_806CFD34 = ItemVoice_BaseItem(item);
                    lbl_806D1775 = kart;
                    lbl_806D1777 = g_raceEntryArray[(signed char)(unsigned char)kart].player;
                    lbl_806D1778 = g_raceEntryArray[(signed char)(unsigned char)kart].distance;
                    lbl_806D1776 = -1;
                    lbl_806D177C = -1;
                    return 1;
                }
            }
        }
    }

    if (kart == g_taMinLapPlayerIndex) {
        if (item == 0x24) {
            if (VoiceQueue_Push(ITEM_ENTRY_VOICE801B(&g_raceEntryArray[kart]), 11, 1, 1)) {
                variant = g_voiceTickCounter % 3;
                if (variant == 0) VoiceQueue_Push(0x201, 11, 1, 1);
                else if (variant == 1) VoiceQueue_Push(0x202, 11, 1, 1);
                else VoiceQueue_Push(0x203, 11, 1, 1);
                g_bgmStateId = 0x6F;
            }
        } else if (g_raceEntryArray[kart].rank == 3) {
            if (VoiceQueue_Push(ITEM_ENTRY_VOICE801B(&g_raceEntryArray[kart]), 11, 1, 1)) {
                variant = g_voiceTickCounter % 3;
                if (variant == 0) {
                    VoiceQueue_Push(ItemVoice(data, item, 0), 11, 1, 1);
                    VoiceQueue_Push(0x204, 11, 1, 1);
                } else if (variant == 1) VoiceQueue_Push(0x205, 11, 1, 1);
                else VoiceQueue_Push(0x206, 11, 1, 1);
                g_bgmStateId = 0x6F;
            }
        } else if (item == 0x12) {
            if (VoiceQueue_Push(ITEM_ENTRY_VOICE801B(&g_raceEntryArray[kart]), 11, 1, 1)) {
                VoiceQueue_Push(0x208, 11, 1, 1);
                g_bgmStateId = 0x6F;
            }
        } else if (item == 0xB) {
            if (VoiceQueue_Push(ITEM_ENTRY_VOICE801B(&g_raceEntryArray[kart]), 11, 1, 1)) {
                VoiceQueue_Push(0x209, 11, 1, 1);
                g_bgmStateId = 0x6F;
            }
        } else if (item == 0x1D) {
            if (VoiceQueue_Push(ITEM_ENTRY_VOICE801B(&g_raceEntryArray[kart]), 11, 1, 1)) {
                VoiceQueue_Push(0x20A, 11, 1, 1);
                g_bgmStateId = 0x6F;
            }
        }
        if ((signed char)g_bgmStateId != 0) {
            lbl_806CFD34 = ItemVoice_BaseItem(item);
            lbl_806D1775 = kart;
            lbl_806D1777 = g_raceEntryArray[(signed char)(unsigned char)kart].player;
            lbl_806D1778 = g_raceEntryArray[(signed char)(unsigned char)kart].distance;
            now = OSGetTime();
            g_bgmStateTimeLo = (unsigned int)now;
            g_bgmStateTimeHi = (unsigned long long)now >> 32;
            lbl_806D1776 = -1;
            lbl_806D177C = -1;
            return 1;
        }
    }

    if (!RaceVoice_CanQueue(21)) return 1;
    if (g_raceEntryArray[kart].id == 6 && item == 0x24) {
        VoiceQueue_Push(ITEM_ENTRY_VOICE801B(&g_raceEntryArray[kart]), 21, 0, 1);
        variant = g_voiceTickCounter % 3;
        if (variant == 0) VoiceQueue_Push(0x201, 21, 0, 0);
        else if (variant == 1) VoiceQueue_Push(0x202, 21, 0, 0);
        else VoiceQueue_Push(0x203, 21, 0, 0);
        return 1;
    }
    if (!RaceVoice_Queued(22) && g_raceEntryArray[kart].id == 6 && g_raceEntryArray[kart].rank == 3) {
        VoiceQueue_Push(ITEM_ENTRY_VOICE801B(&g_raceEntryArray[kart]), 22, 0, 1);
        variant = g_voiceTickCounter % 3;
        if (variant == 0) {
            VoiceQueue_Push(ItemVoice(data, item, 0), 22, 0, 0);
            VoiceQueue_Push(0x204, 22, 0, 0);
        } else if (variant == 1) VoiceQueue_Push(0x205, 22, 0, 0);
        else VoiceQueue_Push(0x206, 22, 0, 0);
        return 1;
    }
    if (item == 0x7A && g_voiceTickCounter % 10 < 3) {
        VoiceQueue_Push(0x1CD, 23, 0, 1);
        VoiceQueue_Push(ITEM_ENTRY_VOICE801B(&g_raceEntryArray[kart]), 23, 0, 0);
        VoiceQueue_Push(0x207, 23, 0, 0);
        return 1;
    }
    if (g_raceEntryArray[kart].id == 6 && item == 0x12) {
        VoiceQueue_Push(ITEM_ENTRY_VOICE801B(&g_raceEntryArray[kart]), 24, 0, 1);
        VoiceQueue_Push(0x208, 24, 0, 0);
        return 1;
    }
    if (g_raceEntryArray[kart].id == 6 && item == 0xB) {
        VoiceQueue_Push(ITEM_ENTRY_VOICE801B(&g_raceEntryArray[kart]), 25, 0, 1);
        VoiceQueue_Push(0x209, 25, 0, 0);
        return 1;
    }
    if (g_raceEntryArray[kart].id == 6 && item == 0x1D) {
        VoiceQueue_Push(ITEM_ENTRY_VOICE801B(&g_raceEntryArray[kart]), 26, 0, 1);
        VoiceQueue_Push(0x20A, 26, 0, 0);
        return 1;
    }
    if (item == 0x19 && g_voiceTickCounter % 10 < 3) {
        VoiceQueue_Push(0x1CD, 27, 0, 1);
        VoiceQueue_Push(ITEM_ENTRY_VOICE801B(&g_raceEntryArray[kart]), 27, 0, 0);
        VoiceQueue_Push(0x20B, 27, 0, 0);
        return 1;
    }
    if (item == 0x1C && g_voiceTickCounter % 10 < 3) {
        VoiceQueue_Push(0x1CD, 28, 0, 1);
        VoiceQueue_Push(ITEM_ENTRY_VOICE801B(&g_raceEntryArray[kart]), 28, 0, 0);
        VoiceQueue_Push(0x20C, 28, 0, 0);
        return 1;
    }
    return 1;
}
#pragma use_lmw_stmw reset
