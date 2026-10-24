#ifndef GAME_STRPCB_H
#define GAME_STRPCB_H

/* StrPcb: steering force-feedback PCB controller. */

typedef unsigned char u8;

typedef struct StrPcbCmd {
    u8 pad_00[4];
    float intensityScale;
    int intensityMode;
    int positionTarget;
    u8 pad_10[4];
    int counter14;
    u8 dirty18;
    u8 pad_19[7];
    int state20;
    u8 status24;
    u8 pad_25;
    u8 commError26;
    u8 pad_27[6];
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
    u8 pad_64[8];
    u8 effectId;
} StrPcbCmd;

extern const float lbl_806D2400;
extern const float lbl_806D2410;
extern const float lbl_806D23E0;
extern const float lbl_806D23DC;
extern unsigned int lbl_806D100C;

extern unsigned int OSGetTick(void);
extern void Frame_PostDrawOverlay(void);
extern void Frame_UpdatePerFrameState(void);

static inline void StrPcb_ClearTransient(StrPcbCmd *pcb)
{
    pcb->timer30 = 0;
    pcb->value34 = 0;
    pcb->value38 = 0;
    pcb->timer3C = 0;
    pcb->value40 = 0;
}

static inline void StrPcb_SetNeutralCommands(StrPcbCmd *pcb)
{
    pcb->dirty18 = 1; pcb->command2D = 0x2D;
    pcb->dirty18 = 1; pcb->command2E = 0x14;
    pcb->dirty18 = 1; pcb->command2F = 0;
    pcb->dirty18 = 1; pcb->counter14 = 0;
    StrPcb_ClearTransient(pcb);
}

static inline void StrPcb_ResetNeutralDefault(StrPcbCmd *pcb)
{
    pcb->value4C = lbl_806D2410;
    StrPcb_SetNeutralCommands(pcb);
}

static inline void StrPcb_ForceRun(StrPcbCmd *pcb)
{
    if (pcb->state20 != 0) {
        pcb->state20 = 3;
    }
    pcb->status24 |= 0x80;
    pcb->value4C = lbl_806D23DC;
    lbl_806D100C = OSGetTick();
    StrPcb_SetNeutralCommands(pcb);
}

static inline u8 StrPcb_HasErrorInline(StrPcbCmd *pcb)
{
    if ((char)pcb->errorCode[0] == 'E') {
        if ((char)pcb->errorCode[1] != '0' || (char)pcb->errorCode[2] != '0') {
            return 1;
        }
    }
    return pcb->stickyError5C;
}

#endif
