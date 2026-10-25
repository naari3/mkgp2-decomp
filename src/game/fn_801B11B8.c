#include "game/os_time.h"

extern int g_currentVoiceStreamHandle;
extern int g_countdownVoiceId;
extern OSTime g_voiceStreamStartTime;
extern OSTime g_voiceStreamLastPollTime;
typedef struct VoiceClip {
    unsigned char playCount;
    char pad1[3];
    float length;
    void *path;
} VoiceClip;

extern VoiceClip g_voicePlayCountTable[];
extern unsigned char ClStream_IsActive(int handle);
extern void ClStream_Stop(int handle);

int fn_801B11B8(void) {
    OSTime now;

    if (g_currentVoiceStreamHandle == -1) {
        return 0;
    }
    if (ClStream_IsActive(g_currentVoiceStreamHandle)) {
        now = OSGetTime();
        g_voiceStreamLastPollTime = now;
        if (g_voicePlayCountTable[g_countdownVoiceId].length >
            (float)OSTicksToMilliseconds(now - g_voiceStreamStartTime) / 1000.0f) {
            return 1;
        }
    }
    if (g_currentVoiceStreamHandle != -1) {
        ClStream_Stop(g_currentVoiceStreamHandle);
    }
    g_countdownVoiceId = -1;
    g_currentVoiceStreamHandle = -1;
    g_voiceStreamStartTime = 0;
    g_voiceStreamLastPollTime = 0;
    return 0;
}
