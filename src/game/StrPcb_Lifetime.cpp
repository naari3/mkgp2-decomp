#include "game/StrPcbLifetimePrivate.h"
/* The rx/tx/control buffers are owned here (.bss 0x80598100..0x80598530):
 * StrPcb_Init addresses them all from one base register, which MWCC only
 * does for data defined in the same TU. */
extern "C" {
u8 StrPcb_Init_bss_80598100[0x200];
u8 lbl_80598300[0x200];
u8 StrPcb_OutputTick_bss_80598500[0xC];
u8 StrPcb_InputTick_bss_8059850C[0x24];
}

static inline void StrPcb_SetPositionTargetInline(StrPcb *pcb, int target)
{
    pcb->dirty18 = 1;
    pcb->positionTarget = target & 0x3FF;
}

StrPcb::StrPcb(int target) : buffer(new int)
{
    int mode = Clamp_Int(1, 0, 2);

    intensityMode = mode;
    intensityScale = StrPcb_rodata_802E9848[mode];
    positionTarget = target;
    position10 = 0x1FF;
    position28 = 0x1FF;
    counter14 = 0;
    receivedPosData = 0x1FF;
    memset(&StrPcb_OutputTick_bss_80598500[0], 0, 4);
    memset(&StrPcb_InputTick_bss_8059850C[0], 0, 4);
    memset(lbl_80598300, 0, 4);
    memset(StrPcb_Init_bss_80598100, 0, 4);
    memset(StrPcb_bss_806D1000, 0, 3);
    memset(this, 0, 3);
    flags.bit40 = 0;
    flags.bit20 = 0;
    flags.bit10 = 0;
    flags.bit08 = 0;
    flags.low = 0;
    flags.id = 0x35;
    flags.bit01 = 0;
    StrPcb_bss_806D1004 = 0;
    StrPcb_OutputTick_bss_80598500[0] = 0xFF;
    StrPcb_OutputTick_bss_80598500[1] = 0xFF;
    StrPcb_OutputTick_bss_80598500[5] = 0;
    StrPcb_OutputTick_bss_80598500[7] = 0;
    StrPcb_OutputTick_bss_80598500[9] = 0;
    StrPcb_SetPositionTargetInline(this, positionTarget);
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
    fn_802939F0(lbl_80598300, 0x200, StrPcb_Init_bss_80598100, 0x200, this);
    {
        Stopwatch sw;
        sw.Start();
        while ((sw.ElapsedMs() >= lbl_806D2400) == 0) {
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
