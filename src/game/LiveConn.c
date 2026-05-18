extern int g_currentVoiceStreamHandle;

unsigned int Live_IsConnectReady(void) {
    return (g_currentVoiceStreamHandle == -1) ? 1 : 0;
}
