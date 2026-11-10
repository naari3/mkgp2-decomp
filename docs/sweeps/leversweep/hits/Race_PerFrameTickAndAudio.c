#include "game/RacePerFramePrivate.h"

static inline signed char TickPlayerRank(const TickEntry *entry) {
    return entry->player;
}

static inline unsigned char TickFanfare(TickBlock *block) {
    TickEntry *entries = block->entries;
    TickEntry *entry;
    if (g_voiceQueueMuted) return 1;
    entry = &entries[g_goalFanfarePlayerIndex];
    if (!entry->kart->finished) {
        if (g_gameMode == 2 && TickPlayerRank(entry) != 0) {
            if (TickFindLeader(block)->kart->finished) {
                g_voiceQueueMuted = 1;
                g_goalFanfareStartTimeHi = OSGetTime();
                g_goalFanfareSubState = 0;
                g_currentVoiceSubId = -1;
                g_goalFanfareVariant = 1;
            }
        }
    } else {
        g_voiceQueueMuted = 1;
        g_goalFanfareStartTimeHi = OSGetTime();
        g_goalFanfareSubState = 0;
        g_currentVoiceSubId = -1;
        g_goalFanfareVariant = 0;
    }
    return 0;
}

int Race_PerFrameTickAndAudio(void) {
    TickEntry *entries;
    TickBlock *block = (TickBlock *)g_voiceQueue;
    TickEntry *entry;
    int scalar, minRank, minIndex;
    int i, j;
    unsigned char goal;

    if (!g_voiceRaceStartLatched) {
        if (IsRaceStarted()) g_voiceRaceStartLatched = 1;
        g_voiceTickTimeHi = OSGetTime();
    }
    if (!g_voiceSystemInitDone) return 0;
    g_voiceTickCounter++;
    g_lastPlayerCurrentCheckpoint = -1;
    g_lastPlayerIndexCrossingCheckpoint = -1;
    entries = block->entries;
    scalar = g_voiceLapTimerScalar;
    minRank = 10;
    minIndex = -1;
    entry = entries;
    for (i = 0; i < 8; i++, entry++) {
        if (entry->id != -1) {
            entry->checkpoint = scalar - entry->kart->lap;
            entry->player = entry->kart->rank;
            if (entry->checkpoint < -1) entry->checkpoint = -1;
            if (TickPlayerRank(entry) < minRank && entry->participant) {
                minRank = TickPlayerRank(entry);
                minIndex = i;
            }
            if (TickPlayerRank(entry) == 0) {
                g_lastPlayerCurrentCheckpoint = entry->checkpoint;
                g_lastPlayerIndexCrossingCheckpoint = i;
            }
        }
    }
    if (g_gameMode == 2 && g_currentVoiceSubId == -1) g_taMinLapPlayerIndex = minIndex;
    if (g_raceRankingPathObject) {
        for (i = 0, entry = entries; i < 8; entry++, i++) {
            if (entry->id != -1 && TickPlayerRank(entry) != 0) {
                TickEntry *other = entries;
                for (j = 0; j < 8; j++) {
                    if (other[j].id != -1 && TickPlayerRank(other) == TickPlayerRank(entry) - 1) {
                        entry->distance = Race_CompareKartProgress(g_raceRankingPathObject, block->entries[j].kart->participantIndex, entry->kart->participantIndex);
                        if (TickPlayerRank(entry) != entry->previousRank) {
                            entry->overtakeState = 0;
                            entry->previousRank = entry->player;
                        }
                        switch (entry->overtakeState) {
                        case 0:
                            if (entry->distance >= 6) entry->overtakeState++;
                            break;
                        case 1:
                            if (entry->distance <= 4) entry->overtakeState++;
                            break;
                        default:
                            if (++entry->overtakeState > 18) entry->overtakeState = 0;
                            break;
                        }
                        break;
                    }
                }
            } else {
                entry->distance = 0;
                entry->overtakeState = 0;
            }
        }
    }
    if (!RaceAnnouncer_TickAndEnqueue()) {
        if (!VoiceEvent_PushRace()) TickBgm();
    } else {
        if (g_goalFanfareTriggered) goal = 1;
        else if (g_lastPlayerCurrentCheckpoint != g_goalTriggerCheckpoint) goal = 0;
        else if (!fn_801A1BD0(&Race_PerFrameTickAndAudio_data_80496DC4[g_ccClass * 128 + ((g_cupId - 1) * 16 + g_longRoundFlag * 8 + g_reverseRoundFlag * 4)], (RaceVoiceEntry *)&entries[g_lastPlayerIndexCrossingCheckpoint])) goal = 0;
        else {
            g_goalFanfareTriggered = 1;
            g_currentVoiceSubId = -1;
            g_goalFanfareVariant = 0;
            g_bgmStateId = 0;
            goal = 1;
        }
        if (!goal) {
            if (!VoiceEvent_PushRace()) TickBgm();
        } else if (fn_801AECF4()) {
            goal = TickFanfare(block);
            if (!goal) fn_801A5DC0();
            else fn_801A4F38();
        }
    }
    block->pendingId = -1;
    block->pendingArg = 0;
    block->pendingFlag = 0;
    for (i = 0, entry = entries; i < 8; entry++, i++) {
        if (entry->id != -1) {
            float *matrix = KartDriver_GetKartRootMtx(entry->kart);
            entry->lastX = matrix[3];
            entry->lastZ = matrix[11];
            entry->present = 0;
            entry->kind = -1;
            entry->rank = 0;
            entry->state = 0;
            entry->event = 0;
            entry->driver = 0;
            entry->rival = 0;
            entry->f64 = 0;
        }
    }
    if (g_gameMode == 2) {
        unsigned char ready = 0;
        if (g_currentTAVoiceId != -1) {
            if (g_voicePlayCountTable[g_currentTAVoiceId].length < (float)OSTicksToMilliseconds(OSGetTime() - g_voiceStreamTime) / lbl_806D9804) ready = 1;
        } else ready = 1;
        if (ready) {
            if (TickPeek(block) != -1) {
                g_currentTAVoiceId = TickPeek(block);
                TickPop();
            } else g_currentTAVoiceId = -1;
            SyncSlot_GetHostSend()->voiceId = (short)g_currentTAVoiceId;
            g_voiceStreamTime = OSGetTime();
        } else SyncSlot_GetHostSend()->voiceId = -1;
    } else {
        if (g_currentVoiceStreamHandle != -1) {
            if (ClStream_IsActive(g_currentVoiceStreamHandle)) {
                g_voiceStreamLastPollTime = OSGetTime();
                if (g_voicePlayCountTable[g_countdownVoiceId].length >
                    (float)OSTicksToMilliseconds(g_voiceStreamLastPollTime - g_voiceStreamStartTime) / lbl_806D9804)
                    goto stream_polled;
            }
            if (g_currentVoiceStreamHandle != -1) ClStream_Stop(g_currentVoiceStreamHandle);
            g_countdownVoiceId = -1;
            g_currentVoiceStreamHandle = -1;
            g_voiceStreamStartTime = 0;
            g_voiceStreamLastPollTime = 0;
        }
stream_polled:
        if (g_currentVoiceStreamHandle == -1) {
            int id = TickPeek(block);
            if (id != -1) {
                TickPlay(id);
                g_currentVoiceDispatchId = id;
                TickPop();
            } else g_currentVoiceDispatchId = -1;
        }
    }
    return 1;
}
