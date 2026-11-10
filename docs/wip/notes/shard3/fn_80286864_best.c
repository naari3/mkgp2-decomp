/* Triforce pseudo-random numbers (LCG). */
#include <dolphin.h>

u32 random_nm1_data_806D0C18 = 1;

static inline u32 Step(void) {
    { random_nm1_data_806D0C18 = random_nm1_data_806D0C18 * 0x41C64E6D + 12345; }
    return random_nm1_data_806D0C18;
}

static inline u32 Next(void) {
    u32 a = Step();
    u32 c = Step();
    u32 b = Step();
    return ((a << 1) & 0xFFFE0000) | ((b >> 14) & 0x1FFFC) | ((c >> 16) & 3);
}

static inline u32 RandRange(u32 min, u32 max) {
    u64 range = (u64)max - min + 1;
    u64 product = range * Next();
    product >>= 32;
    return (u32)product + min;
}

u32 fn_802867B8(u32 min, u32 max) {
    return RandRange(min, max);
}

BOOL fn_80286864(u32 num, u16 den) {
    BOOL ret = FALSE;
    if (RandRange(0, 0x10000) < (num << 16) / den) {
        ret = TRUE;
    }
    return ret;
}
