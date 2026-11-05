#include "game/SpriteVoiceCountdownPrivate.h"

extern int g_currentVoiceSubId, g_goalFanfareVariant;
extern unsigned char g_bgmStateId;
extern unsigned int g_voiceTickCounter;
extern unsigned char IsRaceStarted(void);
extern unsigned char KartItem_GetByte_f4(void *);

void fn_801A7D0C(void) {
    VoiceQueueEntry *queue = g_voiceQueue;
    unsigned char available;
    if ((g_currentVoiceSubId == -1 || g_currentVoiceSubId == 2) && IsRaceStarted()) {
        if (VoiceQueue_CanPushAt(queue, 8, 0)) {
            if (((VoiceSpeaker *)(queue + 64))->countdown == -1 || ((VoiceSpeaker *)(queue + 64))->countdown > 300) {
                if ((int)g_bgmStateId == 8) g_bgmStateId = 0;
                g_currentVoiceSubId = -1;
            } else if (g_currentVoiceSubId != 2) {
                if (((VoiceSpeaker *)(queue + 64))->countdown >= 280 && ((VoiceSpeaker *)(queue + 64))->countdown <= 300) {
                    if (SpriteVoice_PushAt(queue, 0x1DB, 8, 1, 1)) {
                        g_bgmStateId = 8;
                        g_currentVoiceSubId = 2;
                        g_goalFanfareVariant = ((VoiceSpeaker *)(queue + 64))->countdown;
                    }
                }
            } else {
                g_goalFanfareVariant--;
                if (g_goalFanfareVariant == 180) SpriteVoice_PushAt(queue, 0x1DC, 8, 1, 1);
                if (g_goalFanfareVariant == 0) {
                    if (SpriteVoice_PushAt(queue, SpriteVoice_Select(((VoiceSpeaker *)(queue + 64))->kart->character,
                                         ((VoiceSpeaker *)(queue + 64))->kart->id), 8, 1, 1)) {
                        available = 1;
                        if (((VoiceSpeaker *)(queue + 64))->disabled) available = 0;
                        if (*(void **)((char *)&((SpriteVoiceRaceEntry *)((char *)(queue + 64) + 16))[((VoiceSpeaker *)(queue + 64))->kart->index] + 0x40) &&
                            KartItem_GetByte_f4(*(void **)((char *)&((SpriteVoiceRaceEntry *)((char *)(queue + 64) + 16))[((VoiceSpeaker *)(queue + 64))->kart->index] + 0x40)))
                            available = 0;
                        if (available) SpriteVoice_PushAt(queue, 0x1DD, 8, 1, 0);
                        else if (g_voiceTickCounter % 2 == 0) SpriteVoice_PushAt(queue, 0x1CB, 8, 1, 1);
                        else SpriteVoice_PushAt(queue, 0x1CC, 8, 1, 1);
                    }
                    g_bgmStateId = 0;
                    g_currentVoiceSubId = -1;
                }
            }
        }
    }
}
