#include "game/RaceVoiceEventsPrivate.h"

extern int g_cupId, g_longRoundFlag, g_courseVariantIdx;
extern unsigned int g_voiceTickCounter;
extern int g_humanPlayerCount;
extern short g_charRaceStartVoiceTable[14], lbl_80496D5C[52];

static inline short SelectStartVoice(int character, int id) {
    short *normal = g_charRaceStartVoiceTable;
    short *special = lbl_80496D5C;
    short voice = 0x43;
    if (character > -1 && character < 13) {
        if (g_gameMode == 2) {
            if (id >= 0 && id <= 3) voice = special[character + id * 13];
            else voice = normal[character];
        } else voice = normal[character];
    }
    return voice;
}

/* Commit the driver entry before advancing the queue index. */
static inline void PushDriverVoice(short voice) {
    if (voice == -1 || g_voiceQueueHead >= 64 || g_voiceQueueMuted) return;
    g_voiceQueue[g_voiceQueueHead].id = voice;
    g_voiceQueue[g_voiceQueueHead].priority = 0;
    g_voiceQueue[g_voiceQueueHead].flag = 0;
    g_voiceQueueHead++;
}

static inline int CourseVoiceId(int base, int round) {
    return base + round;
}

/* Queue the cup/course introduction, participating drivers, and start prompt. */
void fn_801AF850(void) {
    int cup = g_cupId;
    int longRound = g_longRoundFlag;
    int variant = g_courseVariantIdx;
    int participants;
    int i;
    if (cup == 1) SpriteVoice_Push(0x10 + longRound * 3 + variant % 3, -1, 0, 1);
    if (cup == 2) SpriteVoice_Push(0x16 + longRound * 3 + variant % 3, -1, 0, 1);
    if (cup == 3) SpriteVoice_Push(0x1C + longRound * 3 + variant % 3, -1, 0, 1);
    if (cup == 4) SpriteVoice_Push(0x22 + longRound * 2 + variant % 2, -1, 0, 1);
    if (cup == 5) SpriteVoice_Push(0x26 + longRound * 2 + variant % 2, -1, 0, 1);
    if (cup == 6) {
        int voice = CourseVoiceId(0x2B, longRound);
        SpriteVoice_Push(voice, -1, 0, 1);
    }
    if (cup == 7) {
        int voice = CourseVoiceId(0x2E, longRound);
        SpriteVoice_Push(voice, -1, 0, 1);
    }
    if (cup == 8) {
        int voice = CourseVoiceId(0x32, longRound);
        SpriteVoice_Push(voice, -1, 0, 1);
    }
    participants = 0;
    for (i = 0; i < 8; i++) {
        if (g_raceEntryArray[i].participant) participants++;
    }
    if (participants != 4) {
        if (g_voiceTickCounter % 2 == 0) SpriteVoice_Push(0x18A, 0, 0, 0);
        else SpriteVoice_Push(0x16F, 0, 0, 0);
    }
    for (i = 0; i < 8; i++) {
        if (g_raceEntryArray[i].participant) {
            PushDriverVoice(SelectStartVoice(g_raceEntryArray[i].character, g_raceEntryArray[i].id));
        }
    }
    if (participants == 4) {
        if (g_voiceTickCounter % 2 == 0) SpriteVoice_Push(0x18B, 0, 0, 0);
        else SpriteVoice_Push(0x170, 0, 0, 0);
    }
    if (g_humanPlayerCount <= 0) {
        if (g_voiceTickCounter % 2 == 0) SpriteVoice_Push(0x18F, 0, 0, 0);
        else SpriteVoice_Push(0x171, 0, 0, 0);
    } else {
        switch (g_voiceTickCounter % 5) {
        case 0: SpriteVoice_Push(0x172, 0, 0, 0); break;
        case 1: SpriteVoice_Push(0x173, 0, 0, 0); break;
        case 2: SpriteVoice_Push(0x174, 0, 0, 0); break;
        case 3: SpriteVoice_Push(0x171, 0, 0, 0); break;
        default: SpriteVoice_Push(0x18F, 0, 0, 0); break;
        }
    }
}
