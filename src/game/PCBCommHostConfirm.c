/* Only the observed sync bytes are viewed here; globals retain their ownership. */
extern unsigned char g_pcbSyncTable[0x1C];
extern int g_currentSceneState;
extern int g_myPcbId;
extern unsigned char g_pcbSyncReady;
extern unsigned char g_isCommHost;
extern void SetLocalPcbRole(int role);

#pragma exceptions on
int PCBComm_ConfirmHostBattle(void)
{
    int scene = g_currentSceneState;
    unsigned char *slot = g_pcbSyncTable + g_myPcbId;
    unsigned char role = slot[3];
    if (scene != 50) return 0;
    if (role == 5) return 0;
    if (g_pcbSyncReady == 0 && slot[-1] != 50) return 0;
    if (role == 0) {
        SetLocalPcbRole(0);
        g_isCommHost = 0;
    } else {
        SetLocalPcbRole(role);
        if (g_myPcbId == role - 1) g_isCommHost = 1;
        else g_isCommHost = 0;
    }
    return 1;
}

int PCBComm_ConfirmHostLobby(void)
{
    int scene = g_currentSceneState;
    unsigned char *slot = g_pcbSyncTable + g_myPcbId;
    unsigned char role = slot[3];
    if (scene != 8) return 0;
    if (role == 1) return 0;
    if (g_pcbSyncReady == 0 && slot[-1] != 8) return 0;
    if (role == 0) {
        SetLocalPcbRole(0);
        g_isCommHost = 0;
    } else {
        SetLocalPcbRole(role);
        if (g_myPcbId == role - 1) g_isCommHost = 1;
        else g_isCommHost = 0;
    }
    return 1;
}
#pragma exceptions reset
