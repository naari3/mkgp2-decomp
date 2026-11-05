#ifndef GAME_SPRITE_VOICE_GOAL_PRIVATE_H
#define GAME_SPRITE_VOICE_GOAL_PRIVATE_H
#include "game/SpriteVoicePrivate.h"

/* Only the progress pointer is consumed here. */
typedef struct VoiceProgressKart {
    unsigned char pad000[0x2AC];
    void *progress;
} VoiceProgressKart;
static inline VoiceProgressKart *VoiceGoal_Kart(SpriteVoiceRaceEntry *entry) {
    return *(VoiceProgressKart **)((char *)entry + 0x44);
}
static inline SpriteVoiceRaceEntry *VoiceGoal_Find(int player) {
    int i;
    for (i = 0; i < 8; i++) {
        if (g_raceEntryArray[i].id != -1 && g_raceEntryArray[i].player == player)
            return &g_raceEntryArray[i];
    }
    return 0;
}
static inline short VoiceGoal_Select(int character, int id, short *normal, short *special) {
    short voice = 0x43;
    if (character > -1 && character < 13) {
        if (g_gameMode == 2) {
            if (id >= 0 && id <= 3) voice = special[character + id * 13];
            else voice = normal[character];
        } else voice = normal[character];
    }
    return voice;
}
extern unsigned char VoiceQueue_Push(short, short, unsigned char, unsigned char);
extern short lbl_80496C38[198];
extern int g_goalFanfareVariant, g_goalFanfarePlayerIndex;
extern int g_lastPlayerIndexCrossingCheckpoint, lbl_806D17BC;
extern unsigned int g_voiceTickCounter;
extern unsigned char g_goalFanfareSubState;
extern OSTime g_goalFanfareStartTimeHi;
extern const float lbl_806D9804, lbl_806D9810;
extern void *g_raceRankingPathObject;
extern int Race_CompareKartProgress(void *, void *, void *);
#endif
