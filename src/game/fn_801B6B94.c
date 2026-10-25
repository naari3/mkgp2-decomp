#include "game/os_time.h"

typedef struct VoiceQueueEntry {
    short id;
    short arg;
    unsigned char played;
} VoiceQueueEntry;

extern unsigned char g_voiceSystemInitDone;
extern int g_currentVoiceStreamHandle;
extern int g_countdownVoiceId;
extern OSTime g_voiceStreamStartTime;
extern OSTime g_voiceStreamLastPollTime;
extern VoiceQueueEntry g_voiceQueue[64];
extern int g_voiceQueueHead;
extern int g_voiceQueueTail;
extern OSTime g_voiceLastTime;
extern void ClStream_Stop(int handle);

int fn_801B6B94(void) {
    int i;

    if (!g_voiceSystemInitDone) {
        return 0;
    }
    if (g_currentVoiceStreamHandle != -1) {
        ClStream_Stop(g_currentVoiceStreamHandle);
    }
    g_countdownVoiceId = -1;
    g_currentVoiceStreamHandle = -1;
    g_voiceStreamStartTime = 0;
    g_voiceStreamLastPollTime = 0;
    for (i = 0; i < 64; i++) {
        g_voiceQueue[i].id = 0;
        g_voiceQueue[i].arg = -1;
        g_voiceQueue[i].played = 0;
    }
    g_voiceQueueHead = 0;
    g_voiceQueueTail = 0;
    g_voiceLastTime = OSGetTime();
    g_voiceSystemInitDone = 0;
    return 0;
}
