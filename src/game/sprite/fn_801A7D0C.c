#include "game/SpriteVoiceCountdownTickPrivate.h"

/* These adjacent objects form the original compiler-managed BSS pool. */
VoiceQueueEntry g_voiceQueue[64];
VoiceSpeaker g_raceCurrentSpeakerId;
SpriteVoiceRaceEntry g_raceEntryArray[8];

extern int g_currentVoiceSubId, g_goalFanfareVariant;
extern unsigned char g_bgmStateId;
extern unsigned int g_voiceTickCounter;
extern unsigned char IsRaceStarted(void);
extern unsigned char KartItem_GetByte_f4(void *);

static inline unsigned char Countdown_Push(short id, short priority, unsigned char flag, unsigned char flush) {
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
        g_voiceQueue[g_voiceQueueHead].flag = flag;
        g_voiceQueueHead++;
    }
    g_voiceQueue[g_voiceQueueHead].id = id;
    g_voiceQueue[g_voiceQueueHead].priority = priority;
    g_voiceQueue[g_voiceQueueHead].flag = flag;
    g_voiceQueueHead++;
    return 1;
}

static inline void *Countdown_Item(int index) {
    return ((CountdownRaceItemEntry *)g_raceEntryArray)[index].item;
}

void fn_801A7D0C(void) {
    unsigned char available;
    if ((g_currentVoiceSubId == -1 || g_currentVoiceSubId == 2) && IsRaceStarted()) {
        if (VoiceQueue_CanPush(8, 0)) {
            if (g_raceCurrentSpeakerId.countdown == -1 || g_raceCurrentSpeakerId.countdown > 300) {
                if ((int)g_bgmStateId == 8) g_bgmStateId = 0;
                g_currentVoiceSubId = -1;
            } else if (g_currentVoiceSubId != 2) {
                if (g_raceCurrentSpeakerId.countdown >= 280 && g_raceCurrentSpeakerId.countdown <= 300) {
                    if (Countdown_Push(0x1DB, 8, 1, 1)) {
                        g_bgmStateId = 8;
                        g_currentVoiceSubId = 2;
                        g_goalFanfareVariant = g_raceCurrentSpeakerId.countdown;
                    }
                }
            } else {
                g_goalFanfareVariant--;
                if (g_goalFanfareVariant == 180) Countdown_Push(0x1DC, 8, 1, 1);
                if (g_goalFanfareVariant == 0) {
                    if (Countdown_Push(SpriteVoice_Select(g_raceCurrentSpeakerId.kart->character,
                                         g_raceCurrentSpeakerId.kart->id), 8, 1, 1)) {
                        available = 1;
                        if (g_raceCurrentSpeakerId.disabled) available = 0;
                        if (Countdown_Item(g_raceCurrentSpeakerId.kart->index) &&
                            KartItem_GetByte_f4(Countdown_Item(g_raceCurrentSpeakerId.kart->index)))
                            available = 0;
                        if (available) Countdown_Push(0x1DD, 8, 1, 0);
                        else if (g_voiceTickCounter % 2 == 0) Countdown_Push(0x1CB, 8, 1, 1);
                        else Countdown_Push(0x1CC, 8, 1, 1);
                    }
                    g_bgmStateId = 0;
                    g_currentVoiceSubId = -1;
                }
            }
        }
    }
}
