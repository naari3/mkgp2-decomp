#include "game/VoiceSystem_Init_private.h"

static inline void VoiceSystem_ClearPlayCounts(VoiceClip *clips) {
    int i;
    for (i = 0; i < 0x282; i++) clips[i].playCount = 0;
}

int VoiceSystem_Init(void) {
    VoiceInitBss *state = (VoiceInitBss *)g_voiceQueue;
    RaceVoiceData *data = &lbl_80496C38;
    OSTime now;
    int volume;
    int cup;
    float duration;
    int i;
    if (g_voiceSystemInitDone == 1) return 0;
    for (i = 0; i < 64; i++) {
        state->queue[i].id = 0;
        state->queue[i].priority = -1;
        state->queue[i].flag = 0;
    }
    g_voiceQueueHead = 0;
    g_voiceQueueTail = 0;
    g_voiceLastTime = OSGetTime();
    now = OSGetTime();
    volume = g_playerData.audible ? 255 : 0;
    cup = g_cupId;
    g_voiceStreamStartTime = 0;
    g_voiceStreamLastPollTime = 0;
    g_goalFanfareVariant = 0;
    lbl_806D1764 = 0;
    lbl_806D176C = 0;
    g_bgmStateId = 0;
    lbl_806D1774 = 0;
    lbl_806CFD34 = -1;
    lbl_806D1775 = 0;
    lbl_806D1776 = 0;
    lbl_806D1777 = 0;
    lbl_806D177C = 0;
    g_raceRankingPathObject = 0;
    lbl_806D178F = 0;
    lbl_806D1730 = 0;
    g_goalTriggerCheckpoint = 1;
    g_voiceLapTimerScalar = 2;
    g_voiceFinalLapCheckpoint = -1;
    g_voiceMidRaceCheckpoint = -1;
    g_lastPlayerCurrentCheckpoint = -1;
    g_lastPlayerIndexCrossingCheckpoint = -1;
    g_taMinLapPlayerIndex = -1;
    g_countdownVoiceId = -1;
    g_currentVoiceStreamHandle = -1;
    g_currentVoiceDispatchId = -1;
    g_currentVoiceSubId = -1;
    g_currentRaceEventPlayer = -1;
    g_currentTAVoiceId = -1;
    g_voiceStreamVolume = volume;
    lbl_806D1778 = 0;
    lbl_806D1788 = lbl_806D97F4;
    g_voiceTickTimeHi = now;
    lbl_806D1728 = now;
    lbl_806D17C8 = now;
    lbl_806D17D0 = now;
    Voice_bss_806D17D8 = now;
    g_voiceStreamTime = now;
    lbl_806D1798 = now;
    g_bgmStateTimeHi = now;
    g_voiceSystemInitDone = 1;
    g_voiceRaceStartLatched = 0;
    lbl_806CFD36 = 0;
    lbl_806D175E = 0;
    lbl_806D175F = 0;
    lbl_806D1760 = 0;
    lbl_806D1768 = 0;
    lbl_806D1770 = 0;
    g_goalFanfareSubState = 0;
    g_voiceQueueMuted = 0;
    g_goalFanfareTriggered = 0;
    lbl_806D178D = 0;
    VoiceSystem_Init_bss_806D178E = 0;
    lbl_806D17B4 = 0;
    lbl_806D1750 = (int)now;
    g_voiceTickCounter = (int)now;
    VoiceSystem_Init_bss_806D1790 = ((float)(lbl_80598A60.duration * 2));
    g_voiceCupLongRoundTable = 0;
    state->speaker[1] = 0;
    state->speaker[0] = -1;
    ((unsigned char *)state->speaker)[8] = 0;
    if (cup == 2 && g_longRoundFlag == 1)
        g_voiceCupLongRoundTable = (RaceVoiceCourseLine *)((char *)data + 0x334C);
    if (cup == 4 && g_longRoundFlag == 1)
        g_voiceCupLongRoundTable = (RaceVoiceCourseLine *)((char *)data + 0x3360);
    if (cup == 5 && g_longRoundFlag == 1)
        g_voiceCupLongRoundTable = (RaceVoiceCourseLine *)((char *)data + 0x33D8);
    if (cup == 6 && g_longRoundFlag == 1)
        g_voiceCupLongRoundTable = (RaceVoiceCourseLine *)((char *)data + 0x3400);
    for (i = 0; i < 8; i++) {
        RaceVoiceEntry *entry = (RaceVoiceEntry *)((unsigned int)state + 0x190) + i;
        entry->id = -1;
        entry->character = -1;
        entry->rank = 0;
        entry->state = 0;
        entry->f32 = 0;
        entry->item = 0;
        *(int *)entry->pad44 = 0;
        *(int *)(entry->pad14 + 0x14) = 0;
        entry->driver = 0;
        entry->rival = 0;
        entry->f34 = -76;
        entry->player = -1;
        entry->kind = -1;
        entry->hits = 0;
        entry->distance = 0;
        lbl_806D1734[i] = 0;
        entry->pad36[0] = entry->player;
        *(OSTime *)(entry->pad55 + 3) = now;
        entry->active = 0;
        entry->participant = 0;
        entry->overtaken = 0;
        entry->silent = 0;
        entry->present = 0;
        entry->pad02[1] = 0;
        entry->pad02[0] = 0;
        entry->f64 = 0;
    }
    VoiceSystem_ClearPlayCounts((VoiceClip *)((unsigned int)data + 0x1534));
    return 1;
}


