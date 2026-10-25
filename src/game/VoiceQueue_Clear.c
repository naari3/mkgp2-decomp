#include "game/os_time.h"

typedef struct VoiceQueueEntry {
    short id;
    short arg;
    unsigned char played;
} VoiceQueueEntry;

extern unsigned char g_voiceSystemInitDone;
extern VoiceQueueEntry g_voiceQueue[64];
extern int g_voiceQueueHead;
extern int g_voiceQueueTail;
extern OSTime g_voiceLastTime;
extern void VoiceIntro_PushRaceStart(void);

int VoiceQueue_Clear(void) {
    int i;

    if (!g_voiceSystemInitDone) {
        return 0;
    }
    for (i = 0; i < 64; i++) {
        g_voiceQueue[i].id = 0;
        g_voiceQueue[i].arg = -1;
        g_voiceQueue[i].played = 0;
    }
    g_voiceQueueHead = 0;
    g_voiceQueueTail = 0;
    g_voiceLastTime = OSGetTime();
    VoiceIntro_PushRaceStart();
    return 1;
}
