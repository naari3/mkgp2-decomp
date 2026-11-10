#include <triforce/amjvs_internal.h>

s16 amjvs_nm3_bss_806D1E30[4];

static inline s32 ReadAnalog(s32 node, s16** out, u8* chans) {
    u8* count = fn_80285778();
    JvsNode* nodes = fn_802857B8();
    u8* p;
    u32 n;
    s16* dst;

    if (node < 1 || node > *count || out == NULL) {
        return 1;
    }
    if (chans != NULL) {
        *chans = nodes[node].analogCh;
    }
    n = 4;
    if (nodes[node].analogCh <= 4) {
        n = nodes[node].analogCh;
    }
    p = nodes[node].analog;
    if (p == (u8*)nodes) {
        return 5;
    }
    dst = AnalogBuf;
    {
        u32 i;
        for (i = 0; i < n; i++) {
            *dst++ = (p[0] << 8) | p[1];
            p += 2;
        }
    }
    *out = AnalogBuf;
    return 0;
}

/* The up-counting loop gives the target's cmplwi/ble guard; the smaller unroll
   budget makes MWCC unroll it 4x (srwi. 2 / andi. 3) instead of 8x. */
#pragma push
#pragma opt_unroll_instr_count 16
s32 fn_8028AAC0(s32 node, s16** out, u8* chans) {
    return ReadAnalog(node, out, chans);
}
#pragma pop
