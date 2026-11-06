#include "game/StrPcbLifetimePrivate.h"

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
