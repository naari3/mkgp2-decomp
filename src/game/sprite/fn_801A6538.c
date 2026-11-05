#include "game/RaceVoiceRivalPrivate.h"

/* Rotating comment lists.  They are the initialisers of the voice module's
 * local arrays and live inside its .rodata block at 0x803810A8. */
typedef struct VoiceList6 { short v[6]; } VoiceList6;
typedef struct VoiceList5 { short v[5]; } VoiceList5;
typedef struct VoiceList10 { short v[10]; } VoiceList10;
typedef struct VoiceList3 { short v[3]; } VoiceList3;
typedef struct RaceVoiceRodata {
    unsigned char pad0[0x2C18];
    VoiceList6 leadFar;    /* 0x2C18 */
    VoiceList5 leadNear;   /* 0x2C24 */
    short pad2C2E;
    VoiceList5 leadClose;  /* 0x2C30 */
    short pad2C3A;
    VoiceList10 chasing;   /* 0x2C3C */
} RaceVoiceRodata;
extern const RaceVoiceRodata lbl_803810A8;
extern const VoiceList3 lbl_806D97E8;

extern OSTime g_voiceTickTimeHi;
extern OSTime lbl_806D1728;
extern signed char lbl_806D1730;
extern unsigned char lbl_806D1734[8];
extern unsigned char lbl_806D1750;
extern unsigned char lbl_806D1760;
extern unsigned char lbl_806CFD36;
extern signed char lbl_806D178F;
extern const float lbl_806D9818, lbl_806D981C, lbl_806D9820;


#define SINCE(t) ((float)OSTicksToMilliseconds(now - (t)) / 1000.0f)
#define CLIP_PLAYED(id) (clips[id].playCount)

/* Character voice of every kart that is spinning out. */
static inline unsigned char RaceVoice_PushSpinning(RaceVoiceData *data) {
    unsigned char pushed = 0;
    int i;

    for (i = 0; i < 8; i++) {
        if (g_raceEntryArray[i].state == 5) {
            if (VoiceQueue_Push(RaceVoice_Character(data, g_raceEntryArray[i].driver->character,
                                                    g_raceEntryArray[i].driver->id),
                                0x10, 0, 1)) {
                pushed = 1;
            }
        }
    }
    return pushed;
}

/* Announcer update: spin-outs, rival hits, goal line, course lines,
 * overtakes, item hits, boost and the rotating mid-race comments.
 * NonMatching (~97%): the original addressed its pooled .data/.rodata
 * (voice clip table at +0x1534, goal lines at +0xF8C) as hoisted address
 * constants; with an extern struct MWCC folds those offsets into the index,
 * with residual register allocation differences.  The time divisor is a
 * literal so each check reloads it without preserving f31 across calls. */
void fn_801A6538(void) {
    const RaceVoiceRodata *ro = &lbl_803810A8;
    RaceVoiceData *data = &lbl_80496C38;
    OSTime now = OSGetTime();
    unsigned char pushed;
    int i;
    int count;
    RaceVoiceEntry *entry;
    RaceVoiceEntry *first;
    unsigned char cond;
    float timer;
    short voice;
    VoiceClip *clips;
    VoiceList10 chaseCur;
    VoiceList10 chaseList;
    VoiceList6 farCur;
    VoiceList5 nearCur;
    VoiceList5 closeCur;
    VoiceList6 farList;
    VoiceList5 nearList;
    VoiceList5 closeList;
    VoiceList3 backCur;
    VoiceList3 backList;

    if (!RaceVoice_Queued(0x10) && RaceVoice_PushSpinning(data)) {
        if (g_voiceTickCounter % 2 == 0) VoiceQueue_Push(0x1CB, 0x10, 0, 0);
        else VoiceQueue_Push(0x1CC, 0x10, 0, 0);
        return;
    }

    if (!RaceVoice_CanQueue(0x11)) {
        return;
    }

    if (SINCE(g_voiceTickTimeHi) >= lbl_806D9818) {
        count = 0;
        for (i = 0; i < 8; i++) {
            if (g_raceEntryArray[i].rival != 0 &&
                (g_taMinLapPlayerIndex == i || g_taMinLapPlayerIndex == g_raceEntryArray[i].rival->playerIndex)) {
                lbl_806D1734[i] = 1;
                count = 1;
            }
        }
        if (SINCE(lbl_806D1728) <= lbl_806D9818) {
            if (count) {
                lbl_806D1730++;
            }
        } else {
            lbl_806D1728 = now;
            lbl_806D1730 = 0;
            for (i = 0; i < 8; i++) {
                lbl_806D1734[i] = 0;
            }
        }
        if (lbl_806D1730 >= 4) {
            count = 0;
            for (i = 0; i < 8; i++) {
                if (lbl_806D1734[i]) {
                    count++;
                }
            }
            if (count != 0 && !RaceVoice_Queued(0x11)) {
                if (g_voiceTickCounter % 5 == 0) VoiceQueue_Push(0x1EF, 0x11, 1, 1);
                else if (g_voiceTickCounter % 5 == 1) VoiceQueue_Push(0x1F0, 0x11, 1, 1);
                else if (g_voiceTickCounter % 5 == 2) VoiceQueue_Push(0x1F1, 0x11, 1, 1);
                else if (g_voiceTickCounter % 5 == 3) VoiceQueue_Push(0x1F2, 0x11, 1, 1);
                else VoiceQueue_Push(0x1F3, 0x11, 1, 1);
                switch (count) {
                case 3:
                    if (g_voiceTickCounter % 3 == 0) {
                        VoiceQueue_Push(0x1F7, 0x11, 1, 1);
                    } else if (g_voiceTickCounter % 3 == 1) {
                        VoiceQueue_Push(0x1F8, 0x11, 1, 1);
                        VoiceQueue_Push(0x1F5, 0x11, 1, 1);
                    } else {
                        VoiceQueue_Push(0x1F9, 0x11, 1, 1);
                        VoiceQueue_Push(0x1F6, 0x11, 1, 1);
                    }
                    break;
                case 4:
                case 5:
                case 6:
                    if (g_voiceTickCounter % 3 == 0) VoiceQueue_Push(0x1FA, 0x11, 1, 1);
                    else if (g_voiceTickCounter % 3 == 1) VoiceQueue_Push(0x1FB, 0x11, 1, 1);
                    else VoiceQueue_Push(0x1FC, 0x11, 1, 1);
                    break;
                default:
                    for (i = 0; i < 8; i++) {
                        if (lbl_806D1734[i]) {
                            VoiceQueue_Push(ENTRY_VOICE(&g_raceEntryArray[i]), 0x11, 1, 1);
                        }
                    }
                    if (g_voiceTickCounter % 4 == 0) VoiceQueue_Push(0x1F4, 0x11, 1, 1);
                    else if (g_voiceTickCounter % 4 == 1) VoiceQueue_Push(0x1F5, 0x11, 1, 1);
                    else if (g_voiceTickCounter % 4 == 2) VoiceQueue_Push(0x1F6, 0x11, 1, 1);
                    else VoiceQueue_Push(0x1A8, 0x11, 1, 1);
                    break;
                }
            }
            for (i = 0; i < 8; i++) {
                lbl_806D1734[i] = 0;
            }
            lbl_806D1728 = now;
            lbl_806D1730++;
        }
    }

    if (!RaceVoice_CanQueue(0x12)) {
        return;
    }

    if (!lbl_806D1760) {
        entry = RaceVoice_FindByRank(1);
        if (entry->participant &&
            fn_801A1BD0(data->goalLines + ((g_cupId - 1) * 16 + g_longRoundFlag * 8 + g_reverseRoundFlag * 4),
                        entry)) {
            lbl_806D1760 = 1;
            if (!entry->silent && VoiceQueue_Push(ENTRY_VOICE(entry), 0x12, 0, 1)) {
                VoiceQueue_Push(0x1FD, 0x12, 0, 0);
                return;
            }
        }
    }

    if (g_voiceCupLongRoundTable != 0 && !KartItem_GetByte_f4(g_raceEntryArray[g_taMinLapPlayerIndex].item)) {
        for (i = 0;; i++) {
            if (fn_801A1BD0(g_voiceCupLongRoundTable[i].line, &g_raceEntryArray[g_taMinLapPlayerIndex]) &&
                VoiceQueue_Push(ENTRY_VOICE(&g_raceEntryArray[g_taMinLapPlayerIndex]), 0x13, 0, 1)) {
                if (g_voiceTickCounter % 2 == 0) VoiceQueue_Push(0x1FE, 0x12, 0, 0);
                else VoiceQueue_Push(0x1FF, 0x12, 0, 0);
                break;
            }
            if (g_voiceCupLongRoundTable[i].last == 1) {
                break;
            }
        }
    }

    pushed = 0;
    for (i = 0; i < 8; i++) {
        entry = &g_raceEntryArray[i];
        if (entry->overtaken) {
            if (!pushed) {
                VoiceQueue_Push(0x1CD, 0x14, 0, 1);
            }
            VoiceQueue_Push(ENTRY_VOICE(entry), 0x14, 0, 0);
            pushed = 1;
            entry->overtaken = 0;
        }
    }
    if (pushed) {
        VoiceQueue_Push(0x200, 0x14, 0, 0);
        return;
    }

    for (i = 0; i < 8; i++) {
        entry = &g_raceEntryArray[i];
        pushed = 0;
        if (entry->participant) {
            cond = 0;
            if (g_gameMode == 2) {
                if (entry->player >= 2 && entry->hits >= 2) cond = 1;
            } else {
                if (entry->player >= 3 && entry->hits >= 2) cond = 1;
            }
            if (cond) {
                VoiceQueue_Push(ENTRY_VOICE(entry), 0x1D, 0, 1);
                entry->hits = 0;
                pushed = 1;
            }
        }
        if (pushed) {
            if (g_voiceTickCounter % 6 == 0) VoiceQueue_Push(0x254, 0x1D, 0, 0);
            else if (g_voiceTickCounter % 6 == 1) VoiceQueue_Push(0x255, 0x1D, 0, 0);
            else if (g_voiceTickCounter % 6 == 2) VoiceQueue_Push(0x256, 0x1D, 0, 0);
            else if (g_voiceTickCounter % 6 == 3) VoiceQueue_Push(0x257, 0x1D, 0, 0);
            else if (g_voiceTickCounter % 6 == 4) VoiceQueue_Push(0x258, 0x1D, 0, 0);
            else VoiceQueue_Push(0x259, 0x1D, 0, 0);
            return;
        }
    }

    if (g_gameMode == 0) {
        entry = &g_raceEntryArray[g_taMinLapPlayerIndex];
        if (entry->item != 0 && KartItem_GetBoostArmedAndTimer(entry->item, &timer)) {
            if (!lbl_806CFD36 && timer >= lbl_806D9818 &&
                VoiceQueue_Push(ENTRY_VOICE(&g_raceEntryArray[g_taMinLapPlayerIndex]), 0x1E, 0, 1)) {
                if (g_voiceTickCounter % 3 == 0) VoiceQueue_Push(0x25C, 0x1E, 0, 0);
                else if (g_voiceTickCounter % 3 == 1) VoiceQueue_Push(0x25D, 0x1E, 0, 0);
                else VoiceQueue_Push(0x25E, 0x1E, 0, 0);
                lbl_806CFD36 = 1;
                return;
            }
        } else {
            lbl_806CFD36 = 0;
        }
        if (lbl_806D178F >= 5 &&
            VoiceQueue_Push(ENTRY_VOICE(&g_raceEntryArray[g_taMinLapPlayerIndex]), 0x1E, 0, 1)) {
            VoiceQueue_Push(0x25F, 0x1E, 0, 0);
            lbl_806D178F = 0;
            return;
        }
    }

    if (SINCE(g_voiceTickTimeHi) >= lbl_806D981C) {
        if (!(SINCE(g_voiceLastTime) >= lbl_806D9820)) {
            return;
        }
        entry = &g_raceEntryArray[g_taMinLapPlayerIndex];
        pushed = 0;
        if (entry == 0) {
            return;
        }
        switch (entry->player) {
        case 0:
            first = RaceVoice_FindByRank(1);
            if (first == 0 || first->distance >= 7) {
                farList = ro->leadFar;
                for (i = 0; i < 6; i++) {
                    clips = data->clips;
                    farCur = farList;
                    voice = farCur.v[(lbl_806D1750 + i) % 6];
                    if (!CLIP_PLAYED(voice)) {
                        VoiceQueue_Push(ENTRY_VOICE(entry), 0x1F, 0, 1);
                        pushed = VoiceQueue_Push(voice, 0x1F, 0, 0);
                        break;
                    }
                }
            } else if (first->distance >= 2) {
                nearList = ro->leadNear;
                for (i = 0; i < 5; i++) {
                    clips = data->clips;
                    nearCur = nearList;
                    voice = nearCur.v[(lbl_806D1750 + i) % 5];
                    if (!CLIP_PLAYED(voice)) {
                        VoiceQueue_Push(ENTRY_VOICE(entry), 0x1F, 0, 1);
                        pushed = VoiceQueue_Push(voice, 0x1F, 0, 0);
                        break;
                    }
                }
            } else {
                closeList = ro->leadClose;
                for (i = 0; i < 5; i++) {
                    clips = data->clips;
                    closeCur = closeList;
                    voice = closeCur.v[(lbl_806D1750 + i) % 5];
                    if (!CLIP_PLAYED(voice)) {
                        if (voice == 0x267 || voice == 0x268) {
                            VoiceQueue_Push(ENTRY_VOICE(entry), 0x1F, 0, 1);
                            pushed = VoiceQueue_Push(voice, 0x1F, 0, 0);
                        } else {
                            pushed = VoiceQueue_Push(voice, 0x1F, 0, 1);
                        }
                        break;
                    }
                }
            }
            break;
        case 1:
        case 2:
        case 3:
        case 4:
            chaseList = ro->chasing;
            for (i = 0; i < 10; i++) {
                clips = data->clips;
                chaseCur = chaseList;
                voice = chaseCur.v[(lbl_806D1750 + i) % 10];
                if (voice == 0x113) {
                    if (!CLIP_PLAYED(voice + entry->player)) {
                        VoiceQueue_Push(ENTRY_VOICE(entry), 0x1F, 0, 1);
                        pushed = VoiceQueue_Push(voice + entry->player, 0x1F, 0, 0);
                        break;
                    }
                } else if (!CLIP_PLAYED(voice)) {
                    if ((unsigned short)(voice - 0x26A) <= 1 || voice == 0x186 || voice == 0x187) {
                        VoiceQueue_Push(ENTRY_VOICE(entry), 0x1F, 0, 1);
                        pushed = VoiceQueue_Push(voice, 0x1F, 0, 0);
                    } else {
                        pushed = VoiceQueue_Push(voice, 0x1F, 0, 1);
                    }
                    break;
                }
            }
            break;
        default:
            backList = lbl_806D97E8;
            for (i = 0; i < 3; i++) {
                clips = data->clips;
                backCur = backList;
                voice = backCur.v[(lbl_806D1750 + i) % 3];
                if (!CLIP_PLAYED(voice)) {
                    if (voice == 0x26E || voice == 0x26F) {
                        VoiceQueue_Push(ENTRY_VOICE(entry), 0x1F, 0, 1);
                        if (voice == 0x26F) {
                            VoiceQueue_Push(0x118, 0x1F, 0, 0);
                        }
                        pushed = VoiceQueue_Push(voice, 0x1F, 0, 0);
                    } else {
                        pushed = VoiceQueue_Push(voice, 0x1F, 0, 1);
                    }
                    break;
                }
            }
            break;
        }
        g_voiceLastTime = now;
        if (pushed) {
            lbl_806D1750++;
        }
    }
}
