#include "game/StrPcbLifetimePrivate.h"

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

