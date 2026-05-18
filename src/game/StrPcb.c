/*
 * Trivial deleting destructor @ 0x80036E40 (size 0x3C, 15 instr).
 *
 * vtable-dispatched dtor with 13+ callers across KartMovement_Init,
 * WarpZone_*, WarpDashMgr_Init etc. Body is byte-identical to its
 * dead-code twin dtor_80036988 (see game/StrPcb_988.c) but the two
 * functions live in separate vtable slots so the binary keeps both.
 *
 * Lives in its own TU because of the QuadFrame_FromPackedCorners/QuadFrame_FromCornerPtrs wedge
 * (extabindex-carrying functions between 0x80036988 and 0x80036E40).
 */

extern void MemoryManager_TimedFree(void *);

#pragma exceptions on
void *dtor_80036E40(void *this, short flag) {
    if (this != 0) {
        if (flag > 0) {
            MemoryManager_TimedFree(this);
        }
    }
    return this;
}
#pragma exceptions reset
