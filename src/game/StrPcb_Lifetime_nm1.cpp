/* Built with GC/1.3 (as StrPcb_WaitForState1): the error-code bytes are
 * compared as int (target cmpwi), so the TU keeps its own inline. */
#include "game/StrPcbLifetimePrivate.h"

StrPcbBuffer::~StrPcbBuffer()
{
    if (p != 0) {
        delete p;
    }
}

extern "C" void StrPcb_EnsureInstance(void)
{
    if (StrPcb_bss_806D1010 == 0) {
        StrPcb_bss_806D1010 = new StrPcb(0x1FF);
    }
}


static inline u8 StrPcb_HasErrorInt(StrPcb *pcb)
{
    if ((int)pcb->errorCode[0] == 'E') {
        if ((int)pcb->errorCode[1] != '0' || (int)pcb->errorCode[2] != '0') {
            return 1;
        }
    }
    return pcb->stickyError5C;
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
            if (commError26 == 1 || StrPcb_HasErrorInt(this) == 1) {
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
    delete StrPcb_bss_806D1010;
    StrPcb_bss_806D1010 = 0;
}

