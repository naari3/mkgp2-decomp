/*
 * StrPcb construction and lifetime, 0x80038288..0x80038778:
 * StrPcb_Init (ctor), StrPcb_GetInstance, StrPcb_Shutdown,
 * StrPcb_EnsureInstance and the weak buffer-holder dtor (dtor_8003871C).
 */

typedef unsigned char u8;

void *operator new(unsigned long size);
void operator delete(void *p);

extern "C" {
extern const float StrPcb_rodata_802E9848[3];
extern const float lbl_806D23E4;
extern const float lbl_806D2400;
extern const float lbl_806D2410;
extern u8 StrPcb_bss_806D1000[3];
extern int StrPcb_bss_806D1004;

unsigned int OSGetTick(void);
int Clamp_Int(int value, int min, int max);
void *memset(void *dst, int c, unsigned long n);
void fn_802939F0(void *rxBuf, int rxSize, void *txBuf, int txSize, void *ctx);
void fn_80293998(void);
int fn_80293290(int chan, int *count);
u8 fn_8029321C(int chan);
void Frame_PostDrawOverlay(void);
void Frame_UpdatePerFrameState(void);
}

#define OS_BUS_CLOCK (*(unsigned int *)0x800000F8)
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)
#define OSTicksToMicroseconds(ticks) (((ticks) * 8) / (OS_TIMER_CLOCK / 125000))

struct StrPcbSerialBuffers {
    u8 tx[0x200];
    u8 rx[0x200];
    u8 packet[0xC];
    u8 log[0x24];
};

extern "C" StrPcbSerialBuffers StrPcb_Init_bss_80598100;

class StrPcbScratch {
public:
    StrPcbScratch(void *p) : ptr(p) {}
    ~StrPcbScratch()
    {
        if (ptr != 0) {
            operator delete(ptr);
        }
    }

    void *ptr;
};

class StrPcbStopwatch {
public:
    StrPcbStopwatch() { start = OSGetTick(); }
    ~StrPcbStopwatch() {}

    u8 HasElapsed(void)
    {
        return (float)OSTicksToMicroseconds(OSGetTick() - start) / lbl_806D23E4 >= lbl_806D2400;
    }

    unsigned int start;
};

class StrPcb {
public:
    StrPcb(int position);
    ~StrPcb() { fn_80293998(); }

    u8 HasError(void)
    {
        if ((char)errorCode[0] == 'E') {
            if ((char)errorCode[1] != '0' || (char)errorCode[2] != '0') {
                return 1;
            }
        }
        return stickyError5C;
    }

    void ParkAndWait(void)
    {
        if (intensityMode != 0 && state20 != 4 && state20 != 1) {
            int timeout;

            value4C = lbl_806D2410;
            SetCommand2D(0x2D);
            SetCommand2E(0x14);
            SetCommand2F(0);
            SetCounter(0);
            ClearTransient();
            timeout = 3600;
            while (state20 != 1) {
                Frame_PostDrawOverlay();
                Frame_UpdatePerFrameState();
                if (commError26 == 1) {
                    break;
                }
                if (HasError() == 1) {
                    break;
                }
                if (timeout-- < 0) {
                    stickyError5C = 1;
                    state20 = 4;
                    break;
                }
            }
        }
    }

    void SetCommand2D(u8 v) { dirty18 = 1; command2D = v; }
    void SetCommand2E(u8 v) { dirty18 = 1; command2E = v; }
    void SetCommand2F(u8 v) { dirty18 = 1; command2F = v; }
    void SetCounter(int v) { dirty18 = 1; counter14 = v; }
    void SetPositionTarget(int v) { dirty18 = 1; positionTarget = v & 0x3FF; }
    void ClearTransient(void)
    {
        timer30 = 0;
        value34 = 0;
        value38 = 0;
        timer3C = 0;
        value40 = 0;
    }

    u8 flag07 : 1;
    u8 flag06 : 1;
    u8 flag05 : 1;
    u8 flag04 : 1;
    u8 flag03 : 1;
    u8 flag02 : 1;
    u8 mode00 : 2;
    u8 header01;
    u8 flags02 : 7;
    u8 flag20 : 1;
    u8 pad_03;
    float intensityScale;
    int intensityMode;
    int positionTarget;
    int position10;
    int counter14;
    u8 dirty18;
    u8 pad_19[7];
    int state20;
    u8 status24;
    u8 statusSent25;
    u8 commError26;
    u8 positionAck27;
    int position28;
    u8 pad_2C;
    u8 command2D;
    u8 command2E;
    u8 command2F;
    u8 timer30;
    u8 pad_31[3];
    int value34;
    int value38;
    u8 timer3C;
    u8 pad_3D[3];
    int value40;
    int receivedPosData;
    float value48;
    float value4C;
    int value50;
    int value54;
    u8 errorCode[3];
    u8 pad_5B;
    u8 stickyError5C;
    u8 pad_5D[3];
    int state60;
    float effectTimer64;
    StrPcbScratch scratch;
    u8 effectId;
};

extern "C" {
extern StrPcb *StrPcb_bss_806D1010;

StrPcb *StrPcb_GetInstance(void);
void StrPcb_Shutdown(void);
void StrPcb_EnsureInstance(void);
}

StrPcb::StrPcb(int position) : scratch(operator new(4))
{
    StrPcbSerialBuffers *bufs = &StrPcb_Init_bss_80598100;
    int i;
    int count;
    int mode;

    mode = Clamp_Int(1, 0, 2);
    intensityMode = mode;
    intensityScale = StrPcb_rodata_802E9848[mode];
    positionTarget = position;
    position10 = 0x1FF;
    position28 = 0x1FF;
    counter14 = 0;
    receivedPosData = 0x1FF;
    memset(bufs->packet, 0, 4);
    memset(bufs->log, 0, 4);
    memset(bufs->rx, 0, 4);
    memset(bufs->tx, 0, 4);
    memset(StrPcb_bss_806D1000, 0, 3);
    memset(this, 0, 3);
    flag06 = 0;
    flag05 = 0;
    flag04 = 0;
    flag03 = 0;
    mode00 = 0;
    header01 = 0x35;
    flag20 = 0;
    StrPcb_bss_806D1004 = 0;
    {
        u8 *packet = bufs->packet;

        packet[0] = 0xFF;
        packet[1] = 0xFF;
        packet[5] = 0;
        packet[7] = 0;
        packet[9] = 0;
    }
    SetPositionTarget(positionTarget);
    SetCommand2D(0);
    SetCommand2E(0);
    SetCommand2F(0);
    dirty18 = 0;
    status24 = 0;
    statusSent25 = 0;
    commError26 = 0;
    positionAck27 = 1;
    state20 = 1;
    command2D = 0;
    command2E = 0;
    value48 = 0.0f;
    value4C = 0.0f;
    ClearTransient();
    state60 = 0;
    effectTimer64 = 0.0f;
    effectId = 0;
    errorCode[0] = 0;
    errorCode[1] = 0;
    errorCode[2] = 0;
    stickyError5C = 0;
    fn_802939F0(bufs->rx, 0x200, bufs->tx, 0x200, this);
    {
        StrPcbStopwatch stopwatch;

        while (!stopwatch.HasElapsed()) {
        }
    }
    for (i = 0; i < 20; i++) {
        if (fn_80293290(0, &count) == 0 && count > 0) {
            while (count-- > 0) {
                fn_8029321C(0);
            }
        }
    }
}

StrPcb *StrPcb_GetInstance(void)
{
    return StrPcb_bss_806D1010;
}

void StrPcb_Shutdown(void)
{
    StrPcb *pcb = StrPcb_bss_806D1010;

    if (pcb != 0) {
        pcb->ParkAndWait();
        delete pcb;
    }
    StrPcb_bss_806D1010 = 0;
}

void StrPcb_EnsureInstance(void)
{
    if (StrPcb_bss_806D1010 == 0) {
        StrPcb_bss_806D1010 = new StrPcb(0x1FF);
    }
}
