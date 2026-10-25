#include <dolphin.h>
#include <dolphin/pad.h>

/* Only __PADDisableRecalibration (called from OSReset) survives in the
 * mkgp2 link; the arcade build reads its inputs over JVS instead of PAD. */

u32 __PADSpec;

BOOL __PADDisableRecalibration(BOOL disable) {
    BOOL enabled;
    BOOL prev;

    enabled = OSDisableInterrupts();
    prev = (__gUnknown800030E3 & 0x40) ? TRUE : FALSE;
    __gUnknown800030E3 &= ~0x40;
    if (disable) {
        __gUnknown800030E3 |= 0x40;
    }

    OSRestoreInterrupts(enabled);
    return prev;
}
