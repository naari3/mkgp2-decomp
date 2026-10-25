#include "game/os_time.h"

typedef struct VoiceClip {
    unsigned char playCount;
    char pad1[3];
    float length;
    void *path;
} VoiceClip;

extern int g_currentVoiceStreamHandle;
extern int g_countdownVoiceId;
extern int g_voiceStreamVolume;
extern OSTime g_voiceStreamStartTime;
extern OSTime g_voiceStreamLastPollTime;
extern VoiceClip g_voicePlayCountTable[];
extern void ClStream_Stop(int handle);
extern int ClStream_PlayMono(void *path, int volume, int channelFlag);
extern int fn_80194AE0(int handle, unsigned char volume);

static inline void StopCurrentVoice(void) {
    if (g_currentVoiceStreamHandle != -1) {
        ClStream_Stop(g_currentVoiceStreamHandle);
    }
    g_currentVoiceStreamHandle = -1;
    g_voiceStreamStartTime = 0;
    g_voiceStreamLastPollTime = 0;
}

int fn_801B3980(int id) {
    OSTime now;

    if (g_currentVoiceStreamHandle != -1) {
        StopCurrentVoice();
    }
    g_countdownVoiceId = id;
    g_currentVoiceStreamHandle = ClStream_PlayMono(g_voicePlayCountTable[id].path, 0, 1);
    if (g_currentVoiceStreamHandle != -1) {
        fn_80194AE0(g_currentVoiceStreamHandle, g_voiceStreamVolume);
    }
    now = OSGetTime();
    g_voiceStreamStartTime = now;
    g_voiceStreamLastPollTime = now;
    g_voicePlayCountTable[id].playCount++;
    return 1;
}
