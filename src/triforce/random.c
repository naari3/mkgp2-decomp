/* Triforce pseudo-random seed setter. */
#include <dolphin.h>

extern u32 lbl_806D0C18;

void fn_802867B0(u32 seed) {
    lbl_806D0C18 = seed;
}
