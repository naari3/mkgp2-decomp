/* Per-frame NAM camera shutdown: drain frames until the socket goes idle
 * (or the countdown runs out), then free the receiver. Returns 1 when it
 * is gone. */
#include "game/types/NamCamSocket.h"

#include "game/types/NamCam.h"

extern NamCam *g_namCam;
extern char lbl_802EB9E4[];
extern void DebugPrintf(const char *fmt, ...);
extern void MemoryManager_TimedFree(void *p);
extern void NamCam_GetImageHandle(int *out, int flag);

int NamCam_TickShutdownCountdown(void)
{
    int handle;

    if (g_namCam == 0) {
        DebugPrintf(lbl_802EB9E4);
        return 1;
    }
    NamCam_GetImageHandle(&handle, 0);
    g_namCam->sock.countdown--;
    if (g_namCam->sock.countdown <= 0) {
        MemoryManager_TimedFree(g_namCam);
        g_namCam = 0;
        return 1;
    }
    switch (g_namCam->sock.state) {
    case 0:
        if (g_namCam->sock.busy == 0) {
            g_namCam->sock.state = 1;
            g_namCam->sock.countdown = 0x78;
        }
        break;
    case 1:
        if (g_namCam->sock.busy == 1) {
            MemoryManager_TimedFree(g_namCam);
            g_namCam = 0;
            return 1;
        }
        break;
    }
    return 0;
}
