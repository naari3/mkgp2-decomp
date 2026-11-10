/* Shut the NAM camera down synchronously: keep drawing frames until the
 * socket has gone busy and then idle again (each wait times out after
 * 120 frames), then free the receiver. */
#include "game/types/NamCamSocket.h"

#include "game/types/NamCam.h"

extern NamCam *g_namCam;
extern char lbl_802EB9E4[];
extern void DebugPrintf(const char *fmt, ...);
extern void MemoryManager_TimedFree(void *p);
extern void NamCam_GetImageHandle(int *out, int flag);
extern char lbl_802EB9F8[];
extern void Frame_PostDrawOverlay(void);
extern void Frame_UpdatePerFrameState(void);

int NamCam_End(void)
{
    int handle1;
    int handle2;
    unsigned char ok;

    DebugPrintf(lbl_802EB9F8);
    if (g_namCam == 0) {
        DebugPrintf(lbl_802EB9E4);
        return 1;
    }
    g_namCam->sock.countdown = 0x78;
    ok = 1;
    while (g_namCam->sock.busy != 0) {
        Frame_PostDrawOverlay();
        NamCam_GetImageHandle(&handle1, 0);
        Frame_UpdatePerFrameState();
        g_namCam->sock.countdown--;
        if (g_namCam->sock.countdown <= 0) {
            ok = 0;
            break;
        }
    }
    if (ok == 1) {
        g_namCam->sock.countdown = 0x78;
        while (g_namCam->sock.busy == 0) {
            Frame_PostDrawOverlay();
            NamCam_GetImageHandle(&handle2, 0);
            Frame_UpdatePerFrameState();
            g_namCam->sock.countdown--;
            if (g_namCam->sock.countdown <= 0) {
                break;
            }
        }
    }
    MemoryManager_TimedFree(g_namCam);
    g_namCam = 0;
    return 1;
}
