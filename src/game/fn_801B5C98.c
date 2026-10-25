#include "game/os_time.h"

typedef struct VoiceClip {
    unsigned char playCount;
    char pad1[3];
    float length;
    void *path;
} VoiceClip;

typedef struct SyncSlot {
    char pad00[0x18];
    short voiceId;
} SyncSlot;

extern unsigned char g_voiceSystemInitDone;
extern int g_currentVoiceStreamHandle;
extern int g_countdownVoiceId;
extern int g_currentVoiceDispatchId;
extern int g_voiceStreamVolume;
extern OSTime g_voiceStreamStartTime;
extern OSTime g_voiceStreamLastPollTime;
extern VoiceClip g_voicePlayCountTable[];
extern SyncSlot *SyncSlot_GetRecv(void);
extern unsigned char ClStream_IsActive(int handle);
extern void ClStream_Stop(int handle);
extern int ClStream_PlayMono(void *path, int volume, int channelFlag);
extern unsigned char fn_80194AE0(unsigned int handle, unsigned char vol);

static inline void StopVoice(void)
{
    if (g_currentVoiceStreamHandle != -1) {
        ClStream_Stop(g_currentVoiceStreamHandle);
    }
    g_countdownVoiceId = -1;
    g_currentVoiceStreamHandle = -1;
    g_voiceStreamStartTime = 0;
    g_voiceStreamLastPollTime = 0;
}

static inline void StopStream(void)
{
    if (g_currentVoiceStreamHandle != -1) {
        ClStream_Stop(g_currentVoiceStreamHandle);
    }
    g_currentVoiceStreamHandle = -1;
    g_voiceStreamStartTime = 0;
    g_voiceStreamLastPollTime = 0;
}

static inline void PlayVoice(int id)
{
    OSTime now;

    if (g_currentVoiceStreamHandle != -1) {
        StopStream();
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
}

int fn_801B5C98(void)
{
    int id;

    if (!g_voiceSystemInitDone) {
        return 0;
    }
    id = SyncSlot_GetRecv()->voiceId;
    if (id != -1) {
        StopVoice();
    }
    if (g_currentVoiceStreamHandle != -1 && !ClStream_IsActive(g_currentVoiceStreamHandle)) {
        StopVoice();
    }
    if (g_currentVoiceStreamHandle == -1) {
        if (id == -1) {
            g_currentVoiceDispatchId = -1;
        } else {
            PlayVoice(id);
            g_currentVoiceDispatchId = id;
        }
    }
    return 1;
}
