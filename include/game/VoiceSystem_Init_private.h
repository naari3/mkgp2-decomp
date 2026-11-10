#ifndef GAME_VOICE_INIT_PRIVATE_H
#define GAME_VOICE_INIT_PRIVATE_H
#include "game/RaceVoiceRivalPrivate.h"

/* One contiguous BSS allocation: queue, current speaker, then eight race entries. */
typedef struct VoiceInitBss {
    VoiceQueueEntry queue[64];
    int speaker[4];
    RaceVoiceEntry entries[8];
} VoiceInitBss;
typedef struct VoiceInitSettings { unsigned char prefix[0x30]; unsigned char duration; } VoiceInitSettings;
typedef struct VoiceInitPlayer { unsigned char prefix[0x19E]; unsigned char audible; } VoiceInitPlayer;
extern VoiceInitSettings lbl_80598A60;
extern VoiceInitPlayer g_playerData;
extern const float lbl_806D97F4;
extern unsigned char lbl_806D1734[8];
extern OSTime g_voiceStreamStartTime;
extern OSTime g_voiceStreamLastPollTime;
extern int g_goalFanfareVariant;
extern int lbl_806D1764;
extern int lbl_806D176C;
extern unsigned char g_bgmStateId;
extern unsigned char lbl_806D1774;
extern short lbl_806CFD34;
extern unsigned char lbl_806D1775;
extern unsigned char lbl_806D1776;
extern unsigned char lbl_806D1777;
extern unsigned char lbl_806D177C;
extern int g_raceRankingPathObject;
extern unsigned char lbl_806D178F;
extern unsigned char lbl_806D1730;
extern int g_goalTriggerCheckpoint;
extern int g_voiceLapTimerScalar;
extern int g_voiceFinalLapCheckpoint;
extern int g_voiceMidRaceCheckpoint;
extern int g_lastPlayerCurrentCheckpoint;
extern int g_lastPlayerIndexCrossingCheckpoint;
extern int g_countdownVoiceId;
extern int g_currentVoiceStreamHandle;
extern int g_currentVoiceDispatchId;
extern int g_currentVoiceSubId;
extern int g_currentRaceEventPlayer;
extern int g_currentTAVoiceId;
extern int g_voiceStreamVolume;
extern int lbl_806D1778;
extern float lbl_806D1788;
extern OSTime g_voiceTickTimeHi;
extern OSTime lbl_806D1728;
extern OSTime lbl_806D17C8;
extern OSTime lbl_806D17D0;
extern OSTime Voice_bss_806D17D8;
extern OSTime g_voiceStreamTime;
extern OSTime lbl_806D1798;
extern OSTime g_bgmStateTimeHi;
extern unsigned char g_voiceSystemInitDone;
extern unsigned char g_voiceRaceStartLatched;
extern unsigned char lbl_806CFD36;
extern unsigned char lbl_806D175E;
extern unsigned char lbl_806D175F;
extern unsigned char lbl_806D1760;
extern unsigned char lbl_806D1768;
extern unsigned char lbl_806D1770;
extern unsigned char g_goalFanfareSubState;
extern unsigned char g_voiceQueueMuted;
extern unsigned char g_goalFanfareTriggered;
extern unsigned char lbl_806D178D;
extern unsigned char VoiceSystem_Init_bss_806D178E;
extern unsigned char lbl_806D17B4;
extern unsigned char lbl_806D1750;
extern float VoiceSystem_Init_bss_806D1790;


#endif
