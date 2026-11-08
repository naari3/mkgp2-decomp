#include "game/MidRaceVoicePrivate.h"

extern unsigned char VoiceQueue_Push(short, short, unsigned char, unsigned char);
extern int g_goalFanfareVariant, g_goalFanfarePlayerIndex;
extern int g_lastPlayerIndexCrossingCheckpoint, lbl_806D17BC;
extern unsigned char g_goalFanfareSubState;
extern OSTime g_goalFanfareStartTimeHi;
extern const float lbl_806D9804, lbl_806D9810;
extern void *g_raceRankingPathObject;
extern int Race_CompareKartProgress(void *, int, int);

static inline short Goal_SelectFirst(short *tables, int character, int id) {
    short *normal = tables;
    short *special = tables + 42;
    short voice = 0x43;
    if (character > -1 && character < 13) {
        if (g_gameMode == 2) {
            if (id >= 0 && id <= 3) voice = special[character + id * 13];
            else voice = normal[character];
        } else voice = normal[character];
    }
    return voice;
}
static inline short Goal_SelectOther(short *tables, int character, int id) {
    short *normal = tables + 14;
    short *special = tables + 94;
    short voice = 0x43;
    if (character > -1 && character < 13) {
        if (g_gameMode == 2) {
            if (id >= 0 && id <= 3) voice = special[character + id * 13];
            else voice = normal[character];
        } else voice = normal[character];
    }
    return voice;
}


static inline int Goal_ParticipantOffset(int offset) {
    MidRaceKart **karts = (MidRaceKart **)((char *)g_raceEntryArray + 0x44);
    MidRaceKart *kart = *(MidRaceKart **)((char *)karts + offset);
    return kart->participantIndex;
}

static inline int Goal_Participant(int index) {
    MidRaceKart **karts = (MidRaceKart **)((char *)g_raceEntryArray + 0x44);
    MidRaceKart *kart = *(MidRaceKart **)((char *)karts + index * sizeof(SpriteVoiceRaceEntry));
    return kart->participantIndex;
}

void fn_801A4F38(void) {
    short *tables = lbl_80496C38.f0;
    SpriteVoiceRaceEntry *entry;
    int player, comparison;
    int playerOffset;
    int i;
    OSTime now = OSGetTime();
    if (g_goalFanfareSubState != 0) return;
    if ((float)OSTicksToMilliseconds(now - g_goalFanfareStartTimeHi) / lbl_806D9804 < lbl_806D9810) return;
    g_goalFanfareSubState = 1;
    for (i = 0; i < 64; i++) {
        g_voiceQueue[i].id = 0;
        g_voiceQueue[i].priority = -1;
        g_voiceQueue[i].flag = 0;
    }
    g_voiceQueueHead = 0;
    g_voiceQueueTail = 0;
    g_voiceLastTime = OSGetTime();
    if (g_goalFanfareVariant == 1) {
        if (Race_CompareKartProgress(g_raceRankingPathObject,
            Goal_Participant(g_lastPlayerIndexCrossingCheckpoint),
            Goal_Participant(g_goalFanfarePlayerIndex)) <= 0) {
            VoiceQueue_Push(0x238, -2, 0, 1);
            VoiceQueue_Push(Goal_SelectFirst(tables, g_raceEntryArray[g_lastPlayerIndexCrossingCheckpoint].character,
                g_raceEntryArray[g_lastPlayerIndexCrossingCheckpoint].id), -2, 0, 1);
            VoiceQueue_Push(0x280, -2, 0, 1);
            VoiceQueue_Push(Goal_SelectOther(tables, g_raceEntryArray[g_goalFanfarePlayerIndex].character,
                g_raceEntryArray[g_goalFanfarePlayerIndex].id), -2, 0, 1);
            VoiceQueue_Push(0x23F, -2, 0, 1);
        } else {
            entry = RaceVoice_FindByRank(0);
            VoiceQueue_Push(Goal_SelectFirst(tables, entry->character, entry->id), -2, 0, 1);
            VoiceQueue_Push(0x240, -2, 0, 1);
            VoiceQueue_Push(0x280, -2, 0, 1);
            entry = RaceVoice_FindByRank(1);
            if (entry && entry->participant)
                VoiceQueue_Push(Goal_SelectOther(tables, entry->character, entry->id), -2, 0, 1);
            entry = RaceVoice_FindByRank(2);
            if (entry && entry->participant)
                VoiceQueue_Push(Goal_SelectOther(tables, entry->character, entry->id), -2, 0, 1);
            entry = RaceVoice_FindByRank(3);
            if (entry && entry->participant)
                VoiceQueue_Push(Goal_SelectOther(tables, entry->character, entry->id), -2, 0, 1);
            VoiceQueue_Push(0x241, -2, 0, 1);
        }
        return;
    }
    playerOffset = g_goalFanfarePlayerIndex * (int)sizeof(SpriteVoiceRaceEntry);
    player = ((SpriteVoiceRaceEntry *)((char *)g_raceEntryArray + playerOffset))->player;
    if (g_goalFanfarePlayerIndex == lbl_806D17BC && player != 0) {
        VoiceQueue_Push(0x238, -2, 0, 1);
        VoiceQueue_Push(Goal_SelectFirst(tables, g_raceEntryArray[g_lastPlayerIndexCrossingCheckpoint].character,
            g_raceEntryArray[g_lastPlayerIndexCrossingCheckpoint].id), -2, 0, 1);
        VoiceQueue_Push(Goal_SelectOther(tables, g_raceEntryArray[g_goalFanfarePlayerIndex].character,
            g_raceEntryArray[g_goalFanfarePlayerIndex].id), -2, 0, 1);
        VoiceQueue_Push(0x239, -2, 0, 1);
    } else if (g_goalFanfarePlayerIndex != lbl_806D17BC && player == 0) {
        VoiceQueue_Push(0x238, -2, 0, 1);
        VoiceQueue_Push(Goal_SelectFirst(tables, g_raceEntryArray[g_goalFanfarePlayerIndex].character,
            g_raceEntryArray[g_goalFanfarePlayerIndex].id), -2, 0, 1);
        VoiceQueue_Push(0x23A, -2, 0, 1);
    } else {
        if (player == 0) {
            entry = RaceVoice_FindByRank(1);
            if (entry && entry->distance <= 0) {
                VoiceQueue_Push(0x238, -2, 0, 1);
                VoiceQueue_Push(Goal_SelectFirst(tables, g_raceEntryArray[g_goalFanfarePlayerIndex].character,
                    g_raceEntryArray[g_goalFanfarePlayerIndex].id), -2, 0, 1);
                VoiceQueue_Push(0x23E, -2, 0, 1);
                return;
            }
        }
        if (player == 0) {
            VoiceQueue_Push(0x238, -2, 0, 1);
            VoiceQueue_Push(Goal_SelectFirst(tables, g_raceEntryArray[g_goalFanfarePlayerIndex].character,
                g_raceEntryArray[g_goalFanfarePlayerIndex].id), -2, 0, 1);
            if (g_voiceTickCounter % 3 == 0) VoiceQueue_Push(0x23B, -2, 0, 1);
            else if (g_voiceTickCounter % 3 == 1) VoiceQueue_Push(0x23C, -2, 0, 1);
            else VoiceQueue_Push(0x23D, -2, 0, 1);
        } else if (g_gameMode != 2) {
            comparison = Race_CompareKartProgress(g_raceRankingPathObject,
                Goal_Participant(g_lastPlayerIndexCrossingCheckpoint),
                Goal_ParticipantOffset(playerOffset));
            if (player != 0 && comparison <= 0) {
                VoiceQueue_Push(0x238, -2, 0, 1);
                VoiceQueue_Push(Goal_SelectFirst(tables, g_raceEntryArray[g_lastPlayerIndexCrossingCheckpoint].character,
                    g_raceEntryArray[g_lastPlayerIndexCrossingCheckpoint].id), -2, 0, 1);
                VoiceQueue_Push(0x280, -2, 0, 1);
                VoiceQueue_Push(Goal_SelectOther(tables, g_raceEntryArray[g_goalFanfarePlayerIndex].character,
                    g_raceEntryArray[g_goalFanfarePlayerIndex].id), -2, 0, 1);
                VoiceQueue_Push(0x23F, -2, 0, 1);
            } else if (player == 1 || player == 2) {
                RaceVoice_FindByRank(player + 1);
                VoiceQueue_Push(Goal_SelectFirst(tables, g_raceEntryArray[g_goalFanfarePlayerIndex].character,
                    g_raceEntryArray[g_goalFanfarePlayerIndex].id), -2, 0, 1);
                VoiceQueue_Push(0x240, -2, 0, 1);
                VoiceQueue_Push(0x242, -2, 0, 1);
            } else if (player >= 3) {
                VoiceQueue_Push(Goal_SelectFirst(tables, g_raceEntryArray[g_goalFanfarePlayerIndex].character,
                    g_raceEntryArray[g_goalFanfarePlayerIndex].id), -2, 0, 1);
                VoiceQueue_Push(0x240, -2, 0, 1);
                VoiceQueue_Push(0x243, -2, 0, 1);
            }
        }
    }
}
