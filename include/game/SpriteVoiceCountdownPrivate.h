#ifndef GAME_SPRITE_VOICE_COUNTDOWN_PRIVATE_H
#define GAME_SPRITE_VOICE_COUNTDOWN_PRIVATE_H
#include "game/SpriteVoicePrivate.h"

typedef struct VoiceSpeakerKart {
    unsigned char pad000[0x1F4];
    int id, character;
    unsigned char pad1FC[0x4C];
    int index;
} VoiceSpeakerKart;
typedef struct VoiceSpeaker {
    int countdown;
    VoiceSpeakerKart *kart;
    unsigned char disabled;
    unsigned char pad09[7];
} VoiceSpeaker;
static inline unsigned char VoiceQueue_CanPushAt(VoiceQueueEntry *queue, short priority, unsigned char flush) {
    VoiceQueueEntry *last;
    int i;

    if (priority > 0 && g_voiceQueueHead != 0) {
        last = &queue[g_voiceQueueHead - 1];
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
                    queue[i].id = 0;
                    queue[i].priority = -1;
                    queue[i].flag = 0;
                }
                g_voiceQueueHead = 0;
                g_voiceQueueTail = 0;
                g_voiceLastTime = OSGetTime();
            }
        }
    }
    return 1;
}

static inline int SpriteVoice_PushAt(VoiceQueueEntry *queue, short id, short priority, unsigned char flag, unsigned char flush) {
    if (id == -1) {
        return 0;
    }
    if (g_voiceQueueHead >= 0x40) {
        return 0;
    }
    if (g_voiceQueueMuted && priority != -2) {
        return 0;
    }
    if (!VoiceQueue_CanPushAt(queue, priority, flush)) {
        return 0;
    }
    if (flush && g_voiceQueueHead == 0 && g_countdownVoiceId >= 0x36 && g_countdownVoiceId <= 0xB7 &&
        id >= 0x36 && id <= 0xB7) {
        queue[g_voiceQueueHead].id = 0x1CD;
        queue[g_voiceQueueHead].priority = priority;
        queue[g_voiceQueueHead++].flag = flag;
    }
    queue[g_voiceQueueHead].id = id;
    queue[g_voiceQueueHead].priority = priority;
    queue[g_voiceQueueHead++].flag = flag;
    return 1;
}

#endif
