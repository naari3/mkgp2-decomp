/* Shut the NAM camera down synchronously: keep drawing frames until the
 * socket has gone busy and then idle again (each wait times out after
 * 120 frames), then free the receiver. */
typedef struct NamCamSocket {
    unsigned char pad00[0x10];
    signed char busy;       /* 0x10 */
    unsigned char pad11[0x1b];
    int countdown;          /* 0x2C */
    int state;              /* 0x30 */
} NamCamSocket;

typedef struct NamCam {
    unsigned char frame[0x80000];
    NamCamSocket sock; /* 0x80000 */
} NamCam;

extern NamCam *lbl_806D1070;
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
    if (lbl_806D1070 == 0) {
        DebugPrintf(lbl_802EB9E4);
        return 1;
    }
    lbl_806D1070->sock.countdown = 0x78;
    ok = 1;
    while (lbl_806D1070->sock.busy != 0) {
        Frame_PostDrawOverlay();
        NamCam_GetImageHandle(&handle1, 0);
        Frame_UpdatePerFrameState();
        lbl_806D1070->sock.countdown--;
        if (lbl_806D1070->sock.countdown <= 0) {
            ok = 0;
            break;
        }
    }
    if (ok == 1) {
        lbl_806D1070->sock.countdown = 0x78;
        while (lbl_806D1070->sock.busy == 0) {
            Frame_PostDrawOverlay();
            NamCam_GetImageHandle(&handle2, 0);
            Frame_UpdatePerFrameState();
            lbl_806D1070->sock.countdown--;
            if (lbl_806D1070->sock.countdown <= 0) {
                break;
            }
        }
    }
    MemoryManager_TimedFree(lbl_806D1070);
    lbl_806D1070 = 0;
    return 1;
}
