/*
 * StrPcb command / status setters, 0x80037F64..0x80038288.
 *
 * Formerly three single-function TUs (StrPcb_SetTimer3c40.c,
 * StrPcb_SetTimer3034_38.c, StrPcb_BeginEffect.c); merged now that the
 * surrounding functions are native C too.
 */

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
    u8 pad_25[8];
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
    u8 pad_50[0x10];
    int state60;
    u8 pad_64[8];
    u8 effectId;
} StrPcbCmd;

extern float lbl_806D2410;
extern const float lbl_806D23DC;
extern const float lbl_806D241C;
extern const float lbl_802E9848[3];
extern int lbl_802E9838[];
extern u8 lbl_80598A60[];
extern unsigned int lbl_806D100C;
extern unsigned int lbl_806D1008;

extern unsigned int OSGetTick(void);
extern int Clamp_Int(int value, int min, int max);
extern void fn_802554DC(void);
extern void fn_802E5380(void);
extern int fn_80293290(int chan, int *count);
extern void fn_8029321C(int chan);

void StrPcb_ResetCommands_NeutralDefault(StrPcbCmd *pcb)
{
    pcb->value4C = lbl_806D2410;
    pcb->dirty18 = 1; pcb->command2D = 0x2D;
    pcb->dirty18 = 1; pcb->command2E = 0x14;
    pcb->dirty18 = 1; pcb->command2F = 0;
    pcb->dirty18 = 1; pcb->counter14 = 0;
    pcb->timer30 = 0;
    pcb->value34 = 0;
    pcb->value38 = 0;
    pcb->timer3C = 0;
    pcb->value40 = 0;
}

#pragma exceptions on
void StrPcb_ForceRun_Neutral(StrPcbCmd *pcb)
{
    if (pcb->state20 != 0) {
        pcb->state20 = 3;
    }
    pcb->status24 |= 0x80;
    pcb->value4C = lbl_806D23DC;
    lbl_806D100C = OSGetTick();
    pcb->dirty18 = 1; pcb->command2D = 0x2D;
    pcb->dirty18 = 1; pcb->command2E = 0x14;
    pcb->dirty18 = 1; pcb->command2F = 0;
    pcb->dirty18 = 1; pcb->counter14 = 0;
    pcb->timer30 = 0;
    pcb->value34 = 0;
    pcb->value38 = 0;
    pcb->timer3C = 0;
    pcb->value40 = 0;
}
#pragma exceptions reset

void StrPcb_ClearStatusBits(StrPcbCmd *pcb, u8 bits)
{
    pcb->status24 &= ~bits;
}

void StrPcb_SetStatusBits(StrPcbCmd *pcb, u8 bits, u8 force)
{
    if (!force && (bits & 4) && lbl_80598A60[0x44] == 0) {
        bits &= ~4;
    }
    if (!force && (bits & 8) && lbl_80598A60[0x45] == 0) {
        bits &= ~8;
    }
    pcb->status24 |= bits;
}

#pragma exceptions on
void StrPcb_SetTimer3c40(StrPcbCmd *pcb, float time, int mode)
{
    float scale = lbl_806D241C;
    pcb->timer3C = scale * time;
    pcb->value40 = mode;
}

void StrPcb_SetTimer3034_38(StrPcbCmd *pcb, int value34,
                            int value38, float time)
{
    float scale = lbl_806D241C;
    pcb->timer30 = scale * time;
    pcb->value34 = value34;
    pcb->value38 = value38;
}
#pragma exceptions reset

void StrPcb_SetCmdByte2f(StrPcbCmd *pcb, u8 value)
{
    pcb->dirty18 = 1;
    pcb->command2F = value;
}

void StrPcb_SetCmdByte2e(StrPcbCmd *pcb, u8 value)
{
    pcb->dirty18 = 1;
    pcb->command2E = value;
}

void StrPcb_SetCmdByte2d(StrPcbCmd *pcb, u8 value)
{
    pcb->dirty18 = 1;
    pcb->command2D = value;
}

void StrPcb_SetCounterField14(StrPcbCmd *pcb, int value)
{
    pcb->dirty18 = 1;
    pcb->counter14 = value;
}

int StrPcb_GetReceivedPosData(StrPcbCmd *pcb)
{
    return pcb->receivedPosData;
}

void StrPcb_SetPositionTarget(StrPcbCmd *pcb, int target)
{
    pcb->dirty18 = 1;
    pcb->positionTarget = target & 0x3FF;
}

u8 StrPcb_IsInErrorState(StrPcbCmd *pcb)
{
    return pcb->state60 == 4;
}

float StrPcb_GetIntensityScale(StrPcbCmd *pcb)
{
    return pcb->intensityScale;
}

#pragma exceptions on
void StrPcb_SetIntensityMode(StrPcbCmd *pcb, int mode)
{
    int m = Clamp_Int(mode, 0, 2);
    pcb->intensityMode = m;
    pcb->intensityScale = lbl_802E9848[m];
}
#pragma exceptions reset

void StrPcb_BeginEffect(StrPcbCmd *pcb, int effect)
{
    pcb->effectId = lbl_802E9838[effect];
    pcb->state60 = 1;
}

#pragma exceptions on
void StrPcb_DrainInputBuffer(void)
{
    int i;
    int count;

    fn_802554DC();
    fn_802E5380();
    for (i = 0; i < 20; i++) {
        if (fn_80293290(0, &count) == 0 && count > 0) {
            while (count-- > 0) {
                fn_8029321C(0);
            }
        }
    }
    lbl_806D1008 = OSGetTick();
}
#pragma exceptions reset
