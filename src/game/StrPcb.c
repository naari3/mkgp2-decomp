/*
 * Trivial deleting destructor @ 0x80036E40 (size 0x3C, 15 instr).
 *
 * vtable-dispatched dtor with 13+ callers across KartMovement_Init,
 * WarpZone_*, WarpDashMgr_Init etc. Body is byte-identical to its
 * dead-code twin dtor_80036988 (see game/StrPcb_988.c) but the two
 * functions live in separate vtable slots so the binary keeps both.
 *
 * Lives in its own TU because of the fn_800369C4/fn_800369F8 wedge
 * (extabindex-carrying functions between 0x80036988 and 0x80036E40).
 */

extern void dtor_8003AFB8(void *);

#pragma exceptions on
void *dtor_80036E40(void *this, short flag) {
    if (this != 0) {
        if (flag > 0) {
            dtor_8003AFB8(this);
        }
    }
    return this;
}
#pragma exceptions reset
