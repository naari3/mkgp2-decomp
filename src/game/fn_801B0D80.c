#include "game/os_time.h"

typedef struct VoiceQueueEntry {
    short id;
    short arg;
    unsigned char played;
} VoiceQueueEntry;

typedef struct VoiceClip {
    unsigned char playCount;
    char pad1[3];
    float length;
    void *path;
} VoiceClip;

extern int g_voiceQueueHead;
extern int g_voiceQueueTail;
extern VoiceQueueEntry g_voiceQueue[];
extern VoiceClip g_voicePlayCountTable[];
extern OSTime g_voiceStreamStartTime;
extern OSTime g_voiceStreamLastPollTime;

float fn_801B0D80(void) {
    float total = 0.0f;
    int i;

    if (g_voiceQueueHead != 0) {
        for (i = g_voiceQueueTail; i < g_voiceQueueHead; i++) {
            total += g_voicePlayCountTable[g_voiceQueue[i].id].length;
        }
        total -= (float)OSTicksToMilliseconds(g_voiceStreamLastPollTime - g_voiceStreamStartTime) / 1000.0f;
        if (total < 0.0f) {
            total = 0.0f;
        }
    }
    return total;
}
