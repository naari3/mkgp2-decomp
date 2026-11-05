#ifndef GAME_VOICE_EVENT_PUSH_RACE_PRIVATE_H
#define GAME_VOICE_EVENT_PUSH_RACE_PRIVATE_H
#include "game/RaceVoiceEventsPrivate.h"

typedef struct RaceEventVoiceClip {
    unsigned char playCount, pad1[3];
    float length;
    void *path;
} RaceEventVoiceClip;

extern short lbl_80496C38[14];
extern int g_currentRaceEventPlayer;
extern unsigned int g_voiceTickCounter;
extern const float lbl_806D9828, lbl_806D982C;
extern OSTime g_voiceStreamStartTime, g_voiceStreamLastPollTime;
extern unsigned int lbl_806D17C8, lbl_806D17CC;
extern unsigned int lbl_806D17D0, lbl_806D17D4;
extern unsigned int lbl_806D17D8, lbl_806D17DC;

static inline OSTime RaceEvent_Time(unsigned int lo, unsigned int hi) {
    return (OSTime)(((unsigned long long)hi << 32) | lo);
}
static inline float RaceEvent_QueueTime(short *tables) {
    RaceEventVoiceClip *clips = (RaceEventVoiceClip *)((char *)tables + 0x1534);
    float time = 0.0f;
    int i;
    if (g_voiceQueueHead != 0) {
        for (i = g_voiceQueueTail; i < g_voiceQueueHead; i++)
            time += clips[g_voiceQueue[i].id].length;
        time -= (float)OSTicksToMilliseconds(g_voiceStreamLastPollTime - g_voiceStreamStartTime) / 1000.0f;
        if (time < 0.0f) time = 0.0f;
    }
    return time;
}
static inline unsigned char RaceEvent_Queued(short id) {
    int i;
    for (i = g_voiceQueueTail; i < g_voiceQueueHead; i++) {
        if (g_voiceQueue[i].id == id) return 1;
    }
    return 0;
}
static inline short RaceEvent_Select(int character, int id, short *tables) {
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
#endif
