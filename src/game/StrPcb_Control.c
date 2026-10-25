/*
 * StrPcb control / error queries, 0x80037AB0..0x80037CC0.
 * Absorbs the former StrPcb_Error.c (its raw asm float stores are now
 * plain C with const sdata2 externs).
 */
#include "game/StrPcb.h"

extern char lbl_806D2414;
extern char lbl_806D2418;

#pragma exceptions on
void StrPcb_BeginTimedNeutral(StrPcbCmd *pcb)
{
    if (pcb->intensityMode != 0) {
        pcb->value50 = 0;
        pcb->value54 = 3600;
        StrPcb_ForceRun(pcb);
    }
}
#pragma exceptions reset

int StrPcb_HasError(StrPcbCmd *pcb)
{
    if ((char)pcb->errorCode[0] == 'E') {
        if ((char)pcb->errorCode[1] != '0' || (char)pcb->errorCode[2] != '0') {
            return 1;
        }
    }
    return pcb->stickyError5C;
}

u8 StrPcb_GetCommErrorFlag(StrPcbCmd *pcb)
{
    return pcb->commError26;
}

char *StrPcb_GetErrorCodeString(StrPcbCmd *pcb)
{
    char *code = (char *)pcb->errorCode;
    if (pcb->stickyError5C == 0) {
        return &lbl_806D2414;
    }
    if (code[0] == 'E') {
        return code;
    }
    return &lbl_806D2418;
}

void StrPcb_ResetCommands_Zero(StrPcbCmd *pcb, u8 resetValues)
{
    pcb->dirty18 = 1; pcb->command2D = 0;
    pcb->dirty18 = 1; pcb->command2E = 0;
    pcb->dirty18 = 1; pcb->command2F = 0;
    pcb->dirty18 = 1; pcb->counter14 = 0;
    StrPcb_ClearTransient(pcb);
    if (resetValues == 1) {
        pcb->value48 = lbl_806D2400;
        pcb->value4C = lbl_806D2410;
    }
    StrPcb_ClearTransient(pcb);
}

void StrPcb_ResetCommands_Neutral(StrPcbCmd *pcb, u8 resetValues)
{
    StrPcb_SetNeutralCommands(pcb);
    if (resetValues == 1) {
        pcb->value48 = lbl_806D23E0;
        pcb->value4C = lbl_806D23DC;
    }
    StrPcb_ClearTransient(pcb);
}
