/* Per-frame NAM camera shutdown: drain frames until the socket goes idle
 * (or the countdown runs out), then free the receiver. Returns 1 when it
 * is gone. */
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

int NamCam_TickShutdownCountdown(void)
{
    int handle;

    if (lbl_806D1070 == 0) {
        DebugPrintf(lbl_802EB9E4);
        return 1;
    }
    NamCam_GetImageHandle(&handle, 0);
    lbl_806D1070->sock.countdown--;
    if (lbl_806D1070->sock.countdown <= 0) {
        MemoryManager_TimedFree(lbl_806D1070);
        lbl_806D1070 = 0;
        return 1;
    }
    switch (lbl_806D1070->sock.state) {
    case 0:
        if (lbl_806D1070->sock.busy == 0) {
            lbl_806D1070->sock.state = 1;
            lbl_806D1070->sock.countdown = 0x78;
        }
        break;
    case 1:
        if (lbl_806D1070->sock.busy == 1) {
            MemoryManager_TimedFree(lbl_806D1070);
            lbl_806D1070 = 0;
            return 1;
        }
        break;
    }
    return 0;
}
