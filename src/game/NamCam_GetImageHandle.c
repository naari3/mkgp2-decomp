/* NamCam image fetch: HTTP GET over the AC socket layer into the capture
 * buffer, polled once per frame. Returns 1 when a complete JPEG arrived. */

typedef struct NamCamTimeout {
    int sec;
    int usec;
} NamCamTimeout;

typedef struct NamCamFdSet {
    unsigned int bits[8];
} NamCamFdSet;

typedef struct NamCamRequest {
    char text[0x1A];
} NamCamRequest;

/* Connection state behind the 0x80000-byte capture buffer. */
typedef struct NamCamConn {
    unsigned char addr[0x10]; /* sockaddr passed to acConnect */
    char state;
    char step;
    unsigned char pad12[2];
    int sock;
    unsigned char ready;
    unsigned char pad19[3];
    unsigned int sent;
    unsigned int received;
    int retry;
    int timeout;
} NamCamConn;

#define NAMCAM_BUFFER_SIZE 0x80000

typedef struct NamCamWork {
    char buffer[NAMCAM_BUFFER_SIZE];
    NamCamConn conn;
} NamCamWork;

#define NAMCAM_CONN (&g_namCam->conn)

/* fd_set words are kept in network (big/little swapped) order. */
#define NAMCAM_SWAP32(x) (((x) << 24) | (((x) << 8) & 0xFF0000) | (((x) >> 8) & 0xFF00) | (((x) >> 24) & 0xFF))
#define NAMCAM_FD_BIT(fd) NAMCAM_SWAP32((unsigned int)1 << ((fd) & 31))

extern void AcError_LogIfError(int sock, int err);
extern void DebugPrintf(const char *fmt, ...);
extern int acClosesocket(int sock);
extern int acConnect(int sock, void *addr, int len);
extern int acPollResponse(int sock);
extern int acReadResponse(int sock);
extern int acRecv(int sock, void *buf, int len, int flags);
extern int acSelect(int n, NamCamFdSet *rd, NamCamFdSet *wr, NamCamFdSet *ex, NamCamTimeout *tv);
extern int acSend(int sock, unsigned int a, unsigned int b, int flags);
extern int acSetTimeOuts(int sock, int a, int b, int c);
extern int acSocket(int domain, int type, int proto);
extern unsigned int fn_802929BC(NamCamRequest *req, unsigned int offset, unsigned int len);
extern void fn_80292BFC(int a, char *dst, int len);
extern void *memset(void *dst, int c, unsigned int n);

extern NamCamWork *g_namCam;
extern int NamCam_GetImageHandle_bss_806D1074;
extern char NamCam_GetImageHandle_bss_806D1078;
extern const char lbl_806D26C0[8]; /* "%d %d \n" */
extern const NamCamTimeout lbl_806DCF00;
extern const NamCamTimeout lbl_806DCF08;

/* Shared .rodata pool: the GET request template at +0, messages after it. */
typedef struct NamCamPool {
    NamCamRequest request;
} NamCamPool;
extern const NamCamPool lbl_802EB4E0;

#pragma exceptions on
int NamCam_GetImageHandle(char **outData, unsigned int *outSize)
{
    const char *strings = (const char *)&lbl_802EB4E0;
    NamCamRequest request = lbl_802EB4E0.request;
    int n;

    if (!NamCam_GetImageHandle_bss_806D1078) {
        NamCam_GetImageHandle_bss_806D1074 = 0;
        NamCam_GetImageHandle_bss_806D1078 = 1;
    }
    switch (NAMCAM_CONN->state) {
    case 0:
        NAMCAM_CONN->timeout = 60;
        NAMCAM_CONN->ready = 0;
        if (NAMCAM_CONN->sock >= 0) {
            acClosesocket(NAMCAM_CONN->sock);
        }
        NAMCAM_CONN->sock = -1;
        if (--NAMCAM_CONN->retry > 0) {
            return 0;
        }
        memset(g_namCam->buffer, 0, NAMCAM_BUFFER_SIZE);
        NAMCAM_CONN->state = 1;
        break;
    case 1:
        NAMCAM_CONN->sock = acSocket(2, 1, 0);
        if (NAMCAM_CONN->sock < 0) {
            NAMCAM_CONN->retry = 60;
            DebugPrintf(strings + 0x440, NAMCAM_CONN->sock);
            AcError_LogIfError(0, NAMCAM_CONN->sock);
            NAMCAM_CONN->state = 0;
            return 0;
        }
        acSetTimeOuts(NAMCAM_CONN->sock, 2000, 2000, 2000);
        NAMCAM_CONN->state = 2;
        if (acConnect(NAMCAM_CONN->sock, NAMCAM_CONN, 0x10) < 0) {
            DebugPrintf(strings + 0x494);
            for (;;) {
            }
        }
        break;
    case 2:
        if (acPollResponse(NAMCAM_CONN->sock) == 1) {
            n = acReadResponse(NAMCAM_CONN->sock);
            if (n < 0) {
                DebugPrintf(strings + 0x454, n);
                AcError_LogIfError(NAMCAM_CONN->sock, n);
                NAMCAM_CONN->state = 0;
                return 0;
            }
            NAMCAM_CONN->state = 3;
            NAMCAM_CONN->step = 0;
        }
        break;
    case 3:
        switch (NAMCAM_CONN->step) {
        case 0:
            NAMCAM_CONN->sent = 0;
            NAMCAM_CONN->step++;
        case 1: {
            NamCamTimeout tv = lbl_806DCF00;
            NamCamFdSet fds;
            unsigned int len;

            memset(&fds, 0, sizeof(fds));
            fds.bits[(unsigned int)NAMCAM_CONN->sock / 32] |= NAMCAM_FD_BIT(NAMCAM_CONN->sock);
            n = acSelect(0x100, 0, &fds, 0, &tv);
            if (n <= 0) {
                DebugPrintf(strings + 0x4a4, n);
                return 0;
            }
            if (!(fds.bits[(unsigned int)NAMCAM_CONN->sock / 32] & NAMCAM_FD_BIT(NAMCAM_CONN->sock))) {
                return 0;
            }
            len = fn_802929BC(&request, NAMCAM_CONN->sent, 0x1A - NAMCAM_CONN->sent);
            if (len != 0x1A - NAMCAM_CONN->sent) {
                DebugPrintf(lbl_806D26C0, NAMCAM_CONN->sent, len);
                for (;;) {
                }
            }
            if (acSend(NAMCAM_CONN->sock, NAMCAM_CONN->sent, 0x1A - NAMCAM_CONN->sent, 0) < 0) {
                DebugPrintf(strings + 0x4c0);
                for (;;) {
                }
            }
            NAMCAM_CONN->step++;
        }
        case 2:
            if (acPollResponse(NAMCAM_CONN->sock) != 1) {
                return 0;
            }
            n = acReadResponse(NAMCAM_CONN->sock);
            if (n < 0) {
                DebugPrintf(strings + 0x468, n);
                AcError_LogIfError(NAMCAM_CONN->sock, n);
                NAMCAM_CONN->state = 0;
                return 0;
            }
            NAMCAM_CONN->sent += n;
            if (NAMCAM_CONN->sent < 0x1A) {
                NAMCAM_CONN->step = 1;
                return 0;
            }
            NAMCAM_CONN->state = 4;
            NAMCAM_CONN->step = 0;
            break;
        }
        break;
    case 4:
        switch (NAMCAM_CONN->step) {
        case 0:
            NAMCAM_CONN->received = 0;
            NAMCAM_CONN->step++;
        case 1: {
            NamCamTimeout tv = lbl_806DCF08;
            NamCamFdSet fds;

            memset(&fds, 0, sizeof(fds));
            fds.bits[(unsigned int)NAMCAM_CONN->sock / 32] |= NAMCAM_FD_BIT(NAMCAM_CONN->sock);
            n = acSelect(0x100, &fds, 0, 0, &tv);
            if (n <= 0) {
                DebugPrintf(strings + 0x4d8, n);
                NAMCAM_CONN->timeout--;
                if (NAMCAM_CONN->timeout < 0) {
                    NAMCAM_CONN->sock = -1;
                    NAMCAM_CONN->state = 0;
                }
                return 0;
            }
            if (!(fds.bits[(unsigned int)NAMCAM_CONN->sock / 32] & NAMCAM_FD_BIT(NAMCAM_CONN->sock))) {
                return 0;
            }
            acRecv(NAMCAM_CONN->sock, 0, 0x10000, 0);
            while (acPollResponse(NAMCAM_CONN->sock) != 1) {
            }
            n = acReadResponse(NAMCAM_CONN->sock);
            if (n > 0) {
                fn_80292BFC(0, g_namCam->buffer + NAMCAM_CONN->received, n);
            }
            if (n < 0) {
                DebugPrintf(strings + 0x47c, n);
                AcError_LogIfError(NAMCAM_CONN->sock, n);
                NAMCAM_CONN->state = 0;
                return 0;
            }
            if (n > 0) {
                NAMCAM_CONN->received += n;
            }
            if (n != 0) {
                return 0;
            }
            {
                NamCamWork *work = g_namCam;
                char *end = work->buffer + work->conn.received;
                if (end[-2] == -1 && end[-1] == -0x27) {
                    for (*outData = work->buffer + 3;
                         (*outData)[0] != '\n' || (*outData)[-1] != '\r' || (*outData)[-2] != '\n' ||
                         (*outData)[-3] != '\r';
                         (*outData)++) {
                    }
                    (*outData)++;
                    NAMCAM_CONN->ready = 1;
                    NAMCAM_CONN->state = 0;
                    if (outSize != 0) {
                        *outSize = NAMCAM_CONN->received;
                        if (*outSize > NAMCAM_BUFFER_SIZE) {
                            DebugPrintf(strings + 0x4f4);
                            for (;;) {
                            }
                        }
                    }
                    return 1;
                }
                work->conn.state = 0;
                return 0;
            }
        }
        }
        break;
    }
    return 0;
}
#pragma exceptions reset
