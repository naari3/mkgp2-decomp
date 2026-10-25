/*
 * StrPcb_WaitForState1 @ 0x80037CC0 (0x148), NonMatching.
 *
 * Logic and instruction stream match; only the callee-saved register
 * assignment is swapped (target: pcb in r30, timeout in r31; CW gives
 * pcb r31, timeout r30). The sibling StrPcb_RunAndWaitIdle, with the same
 * loop, matches with pcb in r31. Tried: initialised declaration, for-loop,
 * moving the timeout init, routing the loop through a static inline
 * wait helper, and a local alias of the parameter. None move the swap.
 */
#include "game/StrPcb.h"

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
