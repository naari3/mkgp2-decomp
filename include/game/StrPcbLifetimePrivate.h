#ifndef GAME_STRPCB_LIFETIME_PRIVATE_H
#define GAME_STRPCB_LIFETIME_PRIVATE_H

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

extern const float StrPcb_rodata_802E9848[3];
extern const float lbl_806D23E0;
extern const float lbl_806D23E4;
extern const float lbl_806D2400;
extern const float lbl_806D2410;
extern u8 StrPcb_bss_806D1000[3];
extern int StrPcb_bss_806D1004;
}

void *operator new(unsigned long size);
void operator delete(void *ptr);

class Stopwatch {
public:
    Stopwatch() {}
    void Start() { m_start = OSGetTick(); }
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

extern "C" StrPcb *StrPcb_bss_806D1010;

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


#endif
