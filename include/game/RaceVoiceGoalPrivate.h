#ifndef GAME_RACE_VOICE_GOAL_PRIVATE_H
#define GAME_RACE_VOICE_GOAL_PRIVATE_H

/* Shared declarations for the race announcer event handlers at
 * 0x801A9D58..0x801ACC18 (goal / final-lap / ranking voice events). */
#include "game/RaceVoiceEventsPrivate.h"

/* Voice tables and course trigger lines that start at 0x80496C38.  Some of
 * the handlers address them through one base pointer, so they are described
 * here as one block. */
typedef struct RaceVoiceTables {
    short f0[14];                  /* 0x000 lbl_80496C38 */
    short normal[14];              /* 0x01C lbl_80496C54 */
    short raceStart[14];           /* 0x038 g_charRaceStartVoiceTable */
    short f54[52];                 /* 0x054 lbl_80496C8C */
    short special[52];             /* 0x0BC lbl_80496CF4 */
    short f124[52];                /* 0x124 lbl_80496D5C */
    unsigned char pad18C[0xF8C - 0x18C];
    float goalLines[8 * 2 * 2 * 4]; /* 0xF8C: [cup][long round][reverse] x1,z1,x2,z2 */
} RaceVoiceTables;
extern RaceVoiceTables lbl_80496C38;

extern int g_cupId, g_longRoundFlag, g_reverseRoundFlag;
extern int g_taMinLapPlayerIndex;
extern unsigned int g_voiceTickCounter;
extern unsigned char IsRaceStarted(void);
extern unsigned char fn_801A1BD0(float *line, SpriteVoiceRaceEntry *entry);

/* SpriteVoice_Push variant used by these handlers: the entry is filled in
 * place and the head is advanced afterwards. */
static inline int RaceVoice_Push(short id, short priority, unsigned char flag, unsigned char flush) {
    if (id == -1) {
        return 0;
    }
    if (g_voiceQueueHead >= 0x40) {
        return 0;
    }
    if (g_voiceQueueMuted && priority != -2) {
        return 0;
    }
    if (!VoiceQueue_CanPush(priority, flush)) {
        return 0;
    }
    g_voiceQueue[g_voiceQueueHead].id = id;
    g_voiceQueue[g_voiceQueueHead].priority = priority;
    g_voiceQueue[g_voiceQueueHead].flag = flag;
    g_voiceQueueHead++;
    return 1;
}

/* Push without the priority-run check of VoiceQueue_CanPush. */
static inline int RaceVoice_PushDirect(short id, short priority, unsigned char flag) {
    if (g_voiceQueueHead >= 0x40) {
        return 0;
    }
    if (g_voiceQueueMuted && priority != -2) {
        return 0;
    }
    g_voiceQueue[g_voiceQueueHead].id = id;
    g_voiceQueue[g_voiceQueueHead].priority = priority;
    g_voiceQueue[g_voiceQueueHead++].flag = flag;
    return 1;
}

/* First race entry whose current rank equals rank, or 0. */
static inline SpriteVoiceRaceEntry *RaceVoice_FindByRank(int rank) {
    int i;
    for (i = 0; i < 8; i++) {
        if (g_raceEntryArray[i].id != -1 && g_raceEntryArray[i].player == rank) {
            return &g_raceEntryArray[i];
        }
    }
    return 0;
}

/* Progress handle of the kart object referenced by a race entry. */
typedef struct RaceVoiceKart {
    unsigned char pad000[0x2AC];
    void *progress;
} RaceVoiceKart;
static inline RaceVoiceKart *RaceVoice_Kart(SpriteVoiceRaceEntry *entry) {
    return *(RaceVoiceKart **)entry->pad44;
}
#define RACE_VOICE_PROGRESS(entry) (RaceVoice_Kart(entry)->progress)

#endif
