#ifndef GAME_RACE_VOICE_EVENTS_PRIVATE_H
#define GAME_RACE_VOICE_EVENTS_PRIVATE_H

/* Voice queue helpers from SpriteVoicePrivate.h, with the item pointer and
 * unsigned participant byte needed by the race-event announcers. */
#include "game/os_time.h"

#include "game/types/VoiceQueueEntry.h"

extern int g_countdownVoiceId;
extern OSTime g_voiceLastTime;
extern VoiceQueueEntry g_voiceQueue[64];
extern int g_voiceQueueHead;
extern unsigned char g_voiceQueueMuted;
extern int g_voiceQueueTail;

static inline unsigned char VoiceQueue_CanPush(short priority, unsigned char flush) {
    VoiceQueueEntry *last;
    int i;

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
            if (last->priority > priority && flush) {
                for (i = 0; i < 64; i++) {
                    g_voiceQueue[i].id = 0;
                    g_voiceQueue[i].priority = -1;
                    g_voiceQueue[i].flag = 0;
                }
                g_voiceQueueHead = 0;
                g_voiceQueueTail = 0;
                g_voiceLastTime = OSGetTime();
            }
        }
    }
    return 1;
}

static inline int SpriteVoice_Push(short id, short priority, unsigned char flag, unsigned char flush) {
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
    if (flush && g_voiceQueueHead == 0 && g_countdownVoiceId >= 0x36 && g_countdownVoiceId <= 0xB7 &&
        id >= 0x36 && id <= 0xB7) {
        g_voiceQueue[g_voiceQueueHead].id = 0x1CD;
        g_voiceQueue[g_voiceQueueHead].priority = priority;
        g_voiceQueue[g_voiceQueueHead++].flag = flag;
    }
    g_voiceQueue[g_voiceQueueHead].id = id;
    g_voiceQueue[g_voiceQueueHead].priority = priority;
    g_voiceQueue[g_voiceQueueHead++].flag = flag;
    return 1;
}

typedef struct SpriteVoiceRaceEntry {
    unsigned char present, pad1[3];
    int kind, rank, state;
    unsigned char pad10[0x20];
    unsigned char active;
    unsigned char participant;
    signed char f32, player;
    signed char f34;
    unsigned char pad35[3];
    int id;
    int character;
    void *item;
    unsigned char pad44[0xC];
    int distance;
    unsigned char pad54[0xC];
    unsigned int f60;
    unsigned char f64, pad65[3];
} SpriteVoiceRaceEntry;
extern SpriteVoiceRaceEntry g_raceEntryArray[8];
extern int g_gameMode;
extern short lbl_80496C54[14];
extern short lbl_80496CF4[52];
static inline short SpriteVoice_Select(int character, int id) {
    short *normal = lbl_80496C54;
    short *special = lbl_80496CF4;
    short voice = 0x43;
    if (character > -1 && character < 13) {
        if (g_gameMode == 2) {
            if (id >= 0 && id <= 3) voice = special[character + id * 13];
            else voice = normal[character];
        } else voice = normal[character];
    }
    return voice;
}

#endif
