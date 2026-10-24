/*
 * StrPcb command / status setters, 0x80037E08..0x80038288.
 *
 * Absorbs the former single-function TUs StrPcb_SetTimer3c40.c,
 * StrPcb_SetTimer3034_38.c and StrPcb_BeginEffect.c.
 */

#include "game/StrPcb.h"

extern const float lbl_806D241C;
extern const float lbl_802E9848[3];
extern int lbl_802E9838[];
extern u8 lbl_80598A60[];
extern unsigned int lbl_806D1008;

extern int Clamp_Int(int value, int min, int max);
extern void fn_802554DC(void);
extern void fn_802E5380(void);
extern int fn_80293290(int chan, int *count);
extern void fn_8029321C(int chan);

#pragma exceptions on
int StrPcb_RunAndWaitIdle(StrPcbCmd *pcb)
{
    int timeout;

    if (pcb->intensityMode == 0) {
        return 1;
    }
    if (pcb->state20 == 4) {
        return 0;
    }
    StrPcb_ForceRun(pcb);
    timeout = 3600;
    while (pcb->state20 != 0) {
        Frame_PostDrawOverlay();
        Frame_UpdatePerFrameState();
        if (pcb->commError26 == 1 || StrPcb_HasErrorInline(pcb) == 1) {
            return 0;
        }
        if (timeout-- < 0) {
            pcb->stickyError5C = 1;
            pcb->state20 = 4;
            return 0;
        }
    }
    return 1;
}
#pragma exceptions reset

void StrPcb_ResetCommands_NeutralDefault(StrPcbCmd *pcb)
{
    StrPcb_ResetNeutralDefault(pcb);
}

#pragma exceptions on
void StrPcb_ForceRun_Neutral(StrPcbCmd *pcb)
{
    StrPcb_ForceRun(pcb);
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
