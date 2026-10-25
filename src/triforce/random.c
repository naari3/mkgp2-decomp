/* Triforce pseudo-random numbers (LCG). */
#include <dolphin.h>

static u32 Seed = 1;

void fn_802867B0(u32 seed) {
    Seed = seed;
}

static inline u32 Step(void) {
    Seed = Seed * 0x41C64E6D + 12345;
    return Seed;
}

static inline u32 Next(void) {
    u32 a = Step();
    u32 b = Step();
    u32 c = Step();
    return ((a << 1) & 0xFFFE0000) | ((b >> 14) & 0x1FFFC) | ((c >> 16) & 3);
}

static inline u32 RandRange(u32 min, u32 max) {
    u64 range = (u64)max - min + 1;
    return min + (u32)((range * Next()) >> 32);
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
