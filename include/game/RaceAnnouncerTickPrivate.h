#ifndef GAME_RACE_ANNOUNCER_TICK_PRIVATE_H
#define GAME_RACE_ANNOUNCER_TICK_PRIVATE_H
#include "game/RaceVoiceRivalPrivate.h"

extern unsigned char lbl_806D1770, g_voiceQueueMuted;
extern int g_currentVoiceSubId, g_lastPlayerIndexCrossingCheckpoint;
extern int g_lastPlayerCurrentCheckpoint, g_goalTriggerCheckpoint;
extern OSTime g_voiceStreamStartTime, g_voiceStreamLastPollTime;
extern unsigned char IsRaceStarted(void);
extern const float lbl_806D9818;

static inline int TickWriteQueue(int index, short id) {
    g_voiceQueue[index].id = id;
    g_voiceQueue[index].priority = 4;
    g_voiceQueue[index].flag = 0;
    return index + 1;
}

static inline void TickPush(short id) {
    if (g_voiceQueueHead < 64 && !g_voiceQueueMuted) {
        g_voiceQueueHead = TickWriteQueue(g_voiceQueueHead, id);
    }
}

static inline void TickPushFirst(short id) {
    if (g_voiceQueueHead < 64 && !g_voiceQueueMuted) {
        g_voiceQueue[g_voiceQueueHead].id = id;
        g_voiceQueue[g_voiceQueueHead].priority = 4;
        g_voiceQueue[g_voiceQueueHead].flag = 0;
        g_voiceQueueHead++;
    }
}

static inline float TickRemaining(VoiceClip *clips) {
    float remaining = 0.0f;
    int i;
    if (g_voiceQueueHead != 0) {
        for (i = g_voiceQueueTail; i < g_voiceQueueHead; i++) {
            /* Keep the clip base separate from the indexed byte offset. */
            remaining += *(float *)((unsigned int)clips + g_voiceQueue[i].id * sizeof(VoiceClip) + 4);
        }
        remaining -= (float)OSTicksToMilliseconds(g_voiceStreamLastPollTime - g_voiceStreamStartTime) / 1000.0f;
        if (remaining < 0.0f) remaining = 0.0f;
    }
    return remaining;
}
#endif
