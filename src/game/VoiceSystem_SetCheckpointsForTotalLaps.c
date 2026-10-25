typedef struct LapTable {
    int v[8];
} LapTable;

extern unsigned char g_voiceSystemInitDone;
extern int g_voiceLapTimerScalar;
extern int g_goalTriggerCheckpoint;
extern int g_voiceFinalLapCheckpoint;
extern int g_voiceMidRaceCheckpoint;
extern LapTable kVoiceMidRaceCheckpointByTotalLaps;
extern LapTable kVoiceFinalLapCheckpointByTotalLaps;

void VoiceSystem_SetCheckpointsForTotalLaps(int totalLaps) {
    LapTable fin = kVoiceFinalLapCheckpointByTotalLaps;
    LapTable mid = kVoiceMidRaceCheckpointByTotalLaps;

    if (g_voiceSystemInitDone) {
        g_voiceLapTimerScalar = totalLaps;
        if (totalLaps > 7) {
            totalLaps = 7;
        }
        g_goalTriggerCheckpoint = g_voiceLapTimerScalar - 1;
        g_voiceFinalLapCheckpoint = fin.v[totalLaps];
        g_voiceMidRaceCheckpoint = mid.v[totalLaps];
    }
}
