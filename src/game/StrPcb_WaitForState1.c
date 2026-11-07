/*
 * StrPcb_WaitForState1 @ 0x80037CC0 (0x148).
 *
 * Built with GC/1.3: under 1.3.2 the pcb/timeout callee-saved registers
 * come out swapped. The error check compares the code bytes as int
 * (target cmpwi), so the TU keeps its own copy of the header inline.
 */
#include "game/StrPcb.h"

static inline u8 HasErr(StrPcbCmd *pcb)
{
    if ((int)pcb->errorCode[0] == 'E') {
        if ((int)pcb->errorCode[1] != '0' || (int)pcb->errorCode[2] != '0') {
            return 1;
        }
    }
    return pcb->stickyError5C;
}
#pragma exceptions on
int StrPcb_WaitForState1(StrPcbCmd *pcb)
{
    int timeout;

    if (pcb->intensityMode == 0) {
        return 1;
    }
    if (pcb->state20 == 4) {
        return 0;
    }
    if (pcb->state20 == 1) {
        return 1;
    }
    StrPcb_ResetNeutralDefault(pcb);
    timeout = 3600;
    while (pcb->state20 != 1) {
        Frame_PostDrawOverlay();
        Frame_UpdatePerFrameState();
        if (pcb->commError26 == 1 || HasErr(pcb) == 1) {
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
