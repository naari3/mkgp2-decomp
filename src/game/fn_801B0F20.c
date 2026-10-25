typedef struct VoiceQueueEntry { short id; short arg; unsigned char played; } VoiceQueueEntry;
extern int g_voiceQueueHead;
extern unsigned char g_voiceQueueMuted;
extern VoiceQueueEntry g_voiceQueue[];
int fn_801B0F20(short id, short arg) {
    if (g_voiceQueueHead >= 0x40) return 0;
    if (g_voiceQueueMuted && arg != -2) return 0;
    g_voiceQueue[g_voiceQueueHead].id = id;
    g_voiceQueue[g_voiceQueueHead].arg = arg;
    g_voiceQueue[g_voiceQueueHead].played = 0;
    g_voiceQueueHead++;
    return 1;
}
