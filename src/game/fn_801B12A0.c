#include "game/os_time.h"

typedef struct VoiceQueueEntry {
    short id;
    short arg;
    unsigned char played;
} VoiceQueueEntry;

extern unsigned char g_voiceSystemInitDone;
extern unsigned char g_voiceQueueMuted;
extern unsigned char g_goalFanfareSubState;
extern VoiceQueueEntry g_voiceQueue[64];
extern int g_voiceQueueHead;
extern int g_voiceQueueTail;
extern OSTime g_voiceLastTime;

static inline int Push(short id, short arg)
{
    if (g_voiceQueueHead >= 0x40) {
        return 0;
    }
    if (g_voiceQueueMuted && arg != -2) {
        return 0;
    }
    g_voiceQueue[g_voiceQueueHead].id = id;
    g_voiceQueue[g_voiceQueueHead].arg = arg;
    g_voiceQueue[g_voiceQueueHead].played = 0;
    g_voiceQueueHead++;
    return 1;
}

void fn_801B12A0(void)
{
    int i;

    if (g_voiceSystemInitDone) {
        if (!g_voiceQueueMuted) {
            g_voiceQueueMuted = 1;
            g_goalFanfareSubState = 1;
            for (i = 0; i < 64; i++) {
                g_voiceQueue[i].id = 0;
                g_voiceQueue[i].arg = -1;
                g_voiceQueue[i].played = 0;
            }
            g_voiceQueueHead = 0;
            g_voiceQueueTail = 0;
            g_voiceLastTime = OSGetTime();
            Push(0x244, -2);
        }
    }
}
