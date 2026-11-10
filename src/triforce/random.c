/* Triforce pseudo-random seed setter. */
#include <dolphin.h>

extern u32 random_nm1_data_806D0C18;

void fn_802867B0(u32 seed) {
    random_nm1_data_806D0C18 = seed;
}
