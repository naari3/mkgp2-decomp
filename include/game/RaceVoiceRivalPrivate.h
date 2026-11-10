#ifndef GAME_RACE_VOICE_RIVAL_PRIVATE_H
#define GAME_RACE_VOICE_RIVAL_PRIVATE_H

/* Private declarations for the race announcer update at 0x801A6538
 * (hit / overtake / goal-line / mid-race commentary).  The voice module
 * addresses its tables through one base pointer, so the .data block at
 * 0x80496C38 and the initialiser block in .rodata are described as one
 * object each. */
#include "game/os_time.h"

#include "game/types/VoiceQueueEntry.h"

extern VoiceQueueEntry g_voiceQueue[64];
extern int g_voiceQueueHead;
extern int g_voiceQueueTail;
extern OSTime g_voiceLastTime;
extern unsigned char VoiceQueue_Push(short id, short priority, unsigned char flag, unsigned char flush);

/* Driver object referenced by a race entry. */
typedef struct RaceVoiceDriver {
    unsigned char pad000[0x1F4];
    int id;        /* 0x1F4 */
    int character; /* 0x1F8 */
} RaceVoiceDriver;

typedef struct RaceVoiceRival {
    unsigned char pad000[0x248];
    int playerIndex; /* 0x248 */
} RaceVoiceRival;

typedef struct RaceVoiceEntry {
    unsigned char present;   /* 0x00 */
    unsigned char silent;    /* 0x01 */
    unsigned char pad02[2];
    int kind;                /* 0x04 */
    int rank;                /* 0x08 */
    int state;               /* 0x0C */
    RaceVoiceDriver *driver; /* 0x10 */
    unsigned char pad14[0x1C];
    unsigned char active;      /* 0x30 */
    unsigned char participant; /* 0x31 */
    signed char f32;           /* 0x32 */
    signed char player;        /* 0x33 */
    signed char f34;           /* 0x34 */
    signed char hits;          /* 0x35 */
    unsigned char pad36[2];
    int id;         /* 0x38 */
    int character;  /* 0x3C */
    void *item;     /* 0x40 */
    unsigned char pad44[0xC];
    int distance;   /* 0x50 */
    unsigned char overtaken; /* 0x54 */
    unsigned char pad55[0xB];
    RaceVoiceRival *rival; /* 0x60 */
    unsigned char f64, pad65[3];
} RaceVoiceEntry;
extern RaceVoiceEntry g_raceEntryArray[8];
extern int g_gameMode;

#include "game/types/VoiceClip.h"

/* .data block starting at 0x80496C38. */
typedef struct RaceVoiceData {
    short f0[14];                   /* 0x000 */
    short normal[14];               /* 0x01C */
    short raceStart[14];            /* 0x038 */
    short f54[52];                  /* 0x054 */
    short special[52];              /* 0x0BC */
    short f124[52];                 /* 0x124 */
    unsigned char pad18C[0xF8C - 0x18C];
    float goalLines[8 * 2 * 2 * 4]; /* 0xF8C: [cup][long round][reverse] x1,z1,x2,z2 */
    unsigned char pad118C[0x1534 - 0x118C];
    VoiceClip clips[1];             /* 0x1534 g_voicePlayCountTable */
} RaceVoiceData;
extern RaceVoiceData lbl_80496C38;

/* Course trigger lines for the long-round course voice. */
typedef struct RaceVoiceCourseLine {
    unsigned char last;
    unsigned char pad1[3];
    float line[4];
} RaceVoiceCourseLine;
extern RaceVoiceCourseLine *g_voiceCupLongRoundTable;

extern int g_cupId, g_longRoundFlag, g_reverseRoundFlag;
extern int g_taMinLapPlayerIndex;
extern unsigned int g_voiceTickCounter;
extern unsigned char fn_801A1BD0(float *line, RaceVoiceEntry *entry);
extern unsigned char KartItem_GetByte_f4(void *item);
extern unsigned char KartItem_GetBoostArmedAndTimer(void *item, float *timer);

static inline short RaceVoice_Character(RaceVoiceData *data, int character, int id) {
    short *normal = data->normal;
    short *special = data->special;
    short voice = 0x43;
    if (character > -1 && character < 13) {
        if (g_gameMode == 2) {
            if (id >= 0 && id <= 3) voice = special[character + id * 13];
            else voice = normal[character];
        } else voice = normal[character];
    }
    return voice;
}
#define ENTRY_VOICE(e) RaceVoice_Character(data, (e)->character, (e)->id)

static inline unsigned char RaceVoice_Queued(short priority) {
    int i;
    for (i = g_voiceQueueTail; i < g_voiceQueueHead; i++) {
        if (g_voiceQueue[i].priority == priority) {
            return 1;
        }
    }
    return 0;
}

static inline unsigned char RaceVoice_CanQueue(short priority) {
    VoiceQueueEntry *last;

    if (priority > 0 && g_voiceQueueHead != 0) {
        last = &g_voiceQueue[g_voiceQueueHead - 1];
        if (last->flag) {
            if (last->priority != priority) {
                return 0;
            }
        } else {
            if (last->priority < priority) {
                return 0;
            }
        }
    }
    return 1;
}

static inline RaceVoiceEntry *RaceVoice_FindByRank(int rank) {
    int i;
    for (i = 0; i < 8; i++) {
        if (g_raceEntryArray[i].id != -1 && g_raceEntryArray[i].player == rank) {
            return &g_raceEntryArray[i];
        }
    }
    return 0;
}

#endif
