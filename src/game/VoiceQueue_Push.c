#include "game/os_time.h"

typedef struct VoiceQueueEntry {
    short id;
    short priority;
    unsigned char flag;
} VoiceQueueEntry;

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

int VoiceQueue_Push(short id, short priority, unsigned char flag, unsigned char flush) {
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
