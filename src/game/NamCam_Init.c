/* Allocate the NAM camera receiver: a 512 KiB frame buffer followed by
 * the socket state, set up for port 80 on PCB 0's address. */
typedef struct NamCamSocket {
    unsigned char pad00;
    unsigned char family;   /* 0x01 */
    unsigned short port;    /* 0x02 */
    unsigned int addr;      /* 0x04 */
    unsigned char pad08[0x8];
    unsigned char flag10;   /* 0x10 */
    unsigned char flag11;   /* 0x11 */
    unsigned char flag12;   /* 0x12 */
    unsigned char flag13;   /* 0x13 */
    int socket;             /* 0x14 */
    unsigned char connected; /* 0x18 */
    unsigned char pad19[0xb];
    int received;           /* 0x24 */
    unsigned char pad28[0x8];
    int frames;             /* 0x30 */
} NamCamSocket;

typedef struct NamCam {
    unsigned char frame[0x80000];
    NamCamSocket sock; /* 0x80000 */
} NamCam;

extern NamCam *g_namCam;
extern char lbl_802EBA04[];
extern void *Alloc(unsigned long size);
extern char *PcbIdToIpString(int pcb);
extern unsigned int acInetAddr(const char *str);
extern void DebugPrintf(const char *fmt, ...);

int NamCam_Init(void)
{
    g_namCam = Alloc(sizeof(NamCam));
    g_namCam->sock.family = 2;
    g_namCam->sock.port = 0x50;
    g_namCam->sock.addr = acInetAddr(PcbIdToIpString(0));
    g_namCam->sock.flag10 = 0;
    g_namCam->sock.flag11 = 0;
    g_namCam->sock.flag12 = 0;
    g_namCam->sock.flag13 = 0;
    g_namCam->sock.socket = -1;
    g_namCam->sock.connected = 0;
    g_namCam->sock.received = 0;
    g_namCam->sock.frames = 0;
    DebugPrintf(lbl_802EBA04);
    return 1;
}
