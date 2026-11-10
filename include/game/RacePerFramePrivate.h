#ifndef GAME_RACE_PER_FRAME_PRIVATE_H
#define GAME_RACE_PER_FRAME_PRIVATE_H
#include "game/RaceVoiceRivalPrivate.h"

/* Additional views used by the per-frame announcer, at 0x801B5E18. */
typedef struct TickKart {
    unsigned char pad000[0x23C];
    int rank, lap;
    unsigned char pad244[0x68];
    int participantIndex;
    unsigned char pad2B0[8];
    unsigned char finished;
} TickKart;
typedef struct TickEntry {
    unsigned char present, pad01[3];
    int kind, rank, state;
    void *driver;
    unsigned char pad14[0x14];
    int event;
    unsigned char pad2C[4];
    unsigned char active, participant;
    signed char checkpoint;
    unsigned char player;
    signed char f34, overtakeState, previousRank;
    unsigned char pad37;
    int id, character;
    void *item;
    TickKart *kart;
    float lastX, lastZ;
    int distance;
    unsigned char pad54[0xC];
    void *rival;
    unsigned char f64, pad65[3];
} TickEntry;
typedef struct TickBlock {
    VoiceQueueEntry queue[64];
    int pendingId, pendingArg;
    unsigned char pendingFlag;
    unsigned char pad189[7];
    TickEntry entries[8];
} TickBlock;
typedef struct TickSyncSlot { unsigned char pad00[0x18]; short voiceId; } TickSyncSlot;
extern unsigned char g_voiceRaceStartLatched, g_voiceSystemInitDone;
extern unsigned char g_voiceQueueMuted, g_bgmStateId, g_goalFanfareTriggered, g_goalFanfareSubState;
extern int g_lastPlayerCurrentCheckpoint, g_lastPlayerIndexCrossingCheckpoint;
extern int g_voiceLapTimerScalar, g_currentVoiceSubId, g_goalTriggerCheckpoint;
extern int g_goalFanfareVariant, g_goalFanfarePlayerIndex, g_ccClass;
extern int g_currentTAVoiceId, g_currentVoiceStreamHandle, g_countdownVoiceId;
extern int g_currentVoiceDispatchId, g_voiceStreamVolume;
extern void *g_raceRankingPathObject;
extern OSTime g_voiceTickTimeHi, g_bgmStateTimeHi, g_goalFanfareStartTimeHi;
extern OSTime g_voiceStreamTime, g_voiceStreamStartTime, g_voiceStreamLastPollTime;
extern const float lbl_806D9804, lbl_806D9808;
extern float lbl_806D1788;
extern float Race_PerFrameTickAndAudio_data_80496DC4[];
extern VoiceClip g_voicePlayCountTable[];
extern unsigned char IsRaceStarted(void), RaceAnnouncer_TickAndEnqueue(void), VoiceEvent_PushRace(void), fn_801AECF4(void);
extern int Race_CompareKartProgress(void *, int, int);
extern float *KartDriver_GetKartRootMtx(TickKart *);
extern TickSyncSlot *SyncSlot_GetHostSend(void);
extern unsigned char ClStream_IsActive(int);
extern void ClStream_Stop(int);
extern int ClStream_PlayMono(void *, int, int);
extern unsigned char fn_80194AE0(unsigned int, unsigned char);
extern void fn_801A4A10(void), fn_801A7D0C(void), fn_801A32BC(void), fn_801A24B8(void), fn_801A1D98(void);
extern void fn_801ACC18(void), fn_801AC208(void), fn_801AAF64(void), fn_801A9D58(void), fn_801A6538(void);
extern void fn_801A5DC0(void), fn_801A4F38(void);

static inline void TickBgm(void) {
    if ((signed char)g_bgmStateId != 0) {
        if ((signed char)g_bgmStateId == 7) fn_801A4A10();
        if ((int)g_bgmStateId == 8) fn_801A7D0C();
        if ((int)g_bgmStateId == 110 && g_voiceQueueHead == 0 && g_currentVoiceDispatchId == -1) {
            if ((float)OSTicksToMilliseconds(OSGetTime() - g_bgmStateTimeHi) / lbl_806D9804 > lbl_806D9808)
                g_bgmStateId = 0;
            else if (!((float)OSTicksToMilliseconds(OSGetTime() - g_bgmStateTimeHi) / lbl_806D9804 <= lbl_806D1788))
                fn_801A32BC();
        }
        if ((int)g_bgmStateId == 111 && g_voiceQueueHead == 0 && g_currentVoiceDispatchId == -1) {
            if ((float)OSTicksToMilliseconds(OSGetTime() - g_bgmStateTimeHi) / lbl_806D9804 > lbl_806D9808)
                g_bgmStateId = 0;
            else fn_801A32BC();
        }
        if ((int)g_bgmStateId == 14) fn_801A24B8();
        if ((int)g_bgmStateId == 15) fn_801A1D98();
    } else {
        fn_801ACC18(); fn_801AC208(); fn_801AAF64(); fn_801A9D58(); fn_801A7D0C(); fn_801A6538();
    }
}
static inline TickEntry *TickFindLeader(TickBlock *block) {
    int i;
    for (i = 0; i < 8; i++) {
        if (block->entries[i].id != -1 && (signed char)block->entries[i].player == 0)
            return &block->entries[i];
    }
    return 0;
}
static inline short TickPeek(TickBlock *block) {
    if (g_voiceQueueTail >= g_voiceQueueHead) return -1;
    return block->queue[g_voiceQueueTail].id;
}
static inline void TickPop(void) {
    if (g_voiceQueueTail < g_voiceQueueHead) g_voiceQueueTail++;
    if (g_voiceQueueTail >= g_voiceQueueHead) {
        g_voiceQueueHead = 0; g_voiceQueueTail = 0;
        g_voiceLastTime = OSGetTime();
    }
}
static inline void TickStopStream(void) {
    if (g_currentVoiceStreamHandle != -1) ClStream_Stop(g_currentVoiceStreamHandle);
    g_currentVoiceStreamHandle = -1;
    g_voiceStreamStartTime = 0;
    g_voiceStreamLastPollTime = 0;
}
static inline void TickPlay(int id) {
    OSTime now;
    if (g_currentVoiceStreamHandle != -1) TickStopStream();
    g_countdownVoiceId = id;
    g_currentVoiceStreamHandle = ClStream_PlayMono(g_voicePlayCountTable[id].path, 0, 1);
    if (g_currentVoiceStreamHandle != -1) fn_80194AE0(g_currentVoiceStreamHandle, g_voiceStreamVolume);
    now = OSGetTime();
    g_voiceStreamStartTime = now;
    g_voiceStreamLastPollTime = now;
    g_voicePlayCountTable[id].playCount++;
}
#endif
