/*
 * StrPcb singleton lifetime, 0x80038288..0x80038778: constructor,
 * GetInstance, Shutdown, EnsureInstance and the receive-buffer holder dtor.
 * Field layout matches include/game/StrPcb.h (StrPcbCmd).
 *
 * NonMatching: StrPcb_Init keeps &lbl_80598100 in r31 from the prologue
 * (this code rematerialises it), and StrPcb_Shutdown has the pcb/timeout
 * registers (r30/r31) swapped. The other three functions match.
 */

typedef unsigned char u8;

extern "C" {
unsigned int OSGetTick(void);
void *memset(void *dst, int c, unsigned long n);
int Clamp_Int(int value, int min, int max);
void Frame_PostDrawOverlay(void);
void Frame_UpdatePerFrameState(void);
void fn_802939F0(u8 *tx, int txSize, u8 *rx, int rxSize, void *owner);
void fn_80293998(void);
int fn_80293290(int chan, int *count);
void fn_8029321C(int chan);

extern const float lbl_802E9848[3];
extern const float lbl_806D23E0;
extern const float lbl_806D23E4;
extern const float lbl_806D2400;
extern const float lbl_806D2410;
struct StrPcbBufs {
    u8 rx[0x200];
    u8 tx[0x200];
    u8 ctl[0x10];
};
extern StrPcbBufs lbl_80598100;
extern u8 lbl_806D1000[3];
extern int lbl_806D1004;
}

void *operator new(unsigned long size);
void operator delete(void *ptr);

class Stopwatch {
public:
    Stopwatch() { m_start = OSGetTick(); }
    ~Stopwatch() {}
    float ElapsedMs()
    {
        return (float)(((OSGetTick() - m_start) << 3) / ((*(volatile unsigned int *)0x800000F8 >> 2) / 125000)) / lbl_806D23E4;
    }

private:
    unsigned int m_start;
};

struct StrPcbBuffer {
    int *p;

    StrPcbBuffer(int *q) : p(q) {}
    ~StrPcbBuffer();
};

struct StrPcbFlags {
    u8 bit80 : 1;
    u8 bit40 : 1;
    u8 bit20 : 1;
    u8 bit10 : 1;
    u8 bit08 : 1;
    u8 bit04 : 1;
    u8 low : 2;
    u8 id;
    u8 pad2 : 7;
    u8 bit01 : 1;
};

class StrPcb {
public:
    StrPcbFlags flags;
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
    StrPcbBuffer buffer;
    u8 effectId;

    StrPcb(int target);
    ~StrPcb();

};

extern "C" StrPcb *lbl_806D1010;

static inline void StrPcb_ClearTransient(StrPcb *pcb)
{
    pcb->timer30 = 0;
    pcb->value34 = 0;
    pcb->value38 = 0;
    pcb->timer3C = 0;
    pcb->value40 = 0;
}

static inline void StrPcb_SetNeutralCommands(StrPcb *pcb)
{
    pcb->dirty18 = 1; pcb->command2D = 0x2D;
    pcb->dirty18 = 1; pcb->command2E = 0x14;
    pcb->dirty18 = 1; pcb->command2F = 0;
    pcb->dirty18 = 1; pcb->counter14 = 0;
    StrPcb_ClearTransient(pcb);
}

static inline void StrPcb_ResetNeutralDefault(StrPcb *pcb)
{
    pcb->value4C = lbl_806D2410;
    StrPcb_SetNeutralCommands(pcb);
}

static inline u8 StrPcb_HasErrorInline(StrPcb *pcb)
{
    if ((char)pcb->errorCode[0] == 'E') {
        if ((char)pcb->errorCode[1] != '0' || (char)pcb->errorCode[2] != '0') {
            return 1;
        }
    }
    return pcb->stickyError5C;
}

/*
 * Built with -inline deferred, which emits the functions in reverse source
 * order; the buffer destructor is defined first so it lands last.
 */

StrPcbBuffer::~StrPcbBuffer()
{
    if (p != 0) {
        delete p;
    }
}

extern "C" void StrPcb_EnsureInstance(void)
{
    if (lbl_806D1010 == 0) {
        lbl_806D1010 = new StrPcb(0x1FF);
    }
}


inline StrPcb::~StrPcb()
{
    int timeout;

    if (intensityMode != 0 && state20 != 4 && state20 != 1) {
        StrPcb_ResetNeutralDefault(this);
        timeout = 3600;
        while (state20 != 1) {
            Frame_PostDrawOverlay();
            Frame_UpdatePerFrameState();
            if (commError26 == 1 || StrPcb_HasErrorInline(this) == 1) {
                break;
            }
            if (timeout-- < 0) {
                stickyError5C = 1;
                state20 = 4;
                break;
            }
        }
    }
    fn_80293998();
}

extern "C" void StrPcb_Shutdown(void)
{
    delete lbl_806D1010;
    lbl_806D1010 = 0;
}

extern "C" StrPcb *StrPcb_GetInstance(void)
{
    return lbl_806D1010;
}

StrPcb::StrPcb(int target) : buffer(new int)
{
    int mode = Clamp_Int(1, 0, 2);

    intensityMode = mode;
    intensityScale = lbl_802E9848[mode];
    positionTarget = target;
    position10 = 0x1FF;
    position28 = 0x1FF;
    counter14 = 0;
    receivedPosData = 0x1FF;
    memset(&lbl_80598100.ctl[0], 0, 4);
    memset(&lbl_80598100.ctl[0xC], 0, 4);
    memset(lbl_80598100.tx, 0, 4);
    memset(lbl_80598100.rx, 0, 4);
    memset(lbl_806D1000, 0, 3);
    memset(this, 0, 3);
    flags.bit40 = 0;
    flags.bit20 = 0;
    flags.bit10 = 0;
    flags.bit08 = 0;
    flags.low = 0;
    flags.id = 0x35;
    flags.bit01 = 0;
    lbl_806D1004 = 0;
    lbl_80598100.ctl[0] = 0xFF;
    lbl_80598100.ctl[1] = 0xFF;
    lbl_80598100.ctl[5] = 0;
    lbl_80598100.ctl[7] = 0;
    lbl_80598100.ctl[9] = 0;
    dirty18 = 1;
    positionTarget &= 0x3FF;
    dirty18 = 1; command2D = 0;
    dirty18 = 1; command2E = 0;
    dirty18 = 1; command2F = 0;
    dirty18 = 0;
    status24 = 0;
    statusSent25 = 0;
    commError26 = 0;
    positionAck27 = 1;
    state20 = 1;
    command2D = 0;
    command2E = 0;
    value48 = lbl_806D23E0;
    value4C = lbl_806D23E0;
    StrPcb_ClearTransient(this);
    state60 = 0;
    effectTimer64 = lbl_806D23E0;
    effectId = 0;
    errorCode[0] = 0;
    errorCode[1] = 0;
    errorCode[2] = 0;
    stickyError5C = 0;
    fn_802939F0(lbl_80598100.tx, 0x200, lbl_80598100.rx, 0x200, this);
    {
        Stopwatch sw;
        while (!(sw.ElapsedMs() >= lbl_806D2400)) {
        }
    }
    for (int i = 0; i < 20; i++) {
        int count;
        if (fn_80293290(0, &count) == 0 && count > 0) {
            while (count-- > 0) {
                fn_8029321C(0);
            }
        }
    }
}
