#include "game/FrameUpdate_private.h"

static inline void FrameBackup_Copy(void)
{
    {
        unsigned char byte00 = lbl_80598A60.byte00;
        unsigned int word04 = lbl_80598A60.word04;
        unsigned int word08 = lbl_80598A60.word08;
        unsigned int word0C = lbl_80598A60.word0C;
        unsigned int word10 = lbl_80598A60.word10;
        unsigned int word1C = lbl_80598A60.word1C;
        unsigned int word18 = lbl_80598A60.word18;
        unsigned int word20 = lbl_80598A60.word20;
        unsigned int word24 = lbl_80598A60.word24;
        unsigned short half28 = lbl_80598A60.half28;
        unsigned char byte2A = lbl_80598A60.packed2A.byte2A;
        unsigned int word2B = lbl_80598A60.packed2A.word2B;
        unsigned short half2F = lbl_80598A60.packed2A.half2F;
        unsigned char byte31 = lbl_80598A60.packed2A.byte31;
        unsigned int word34 = lbl_80598A60.word34;
        unsigned int word38 = lbl_80598A60.word38;
        unsigned int word3C = lbl_80598A60.word3C;
        unsigned int word40 = lbl_80598A60.word40;
        unsigned int word44 = lbl_80598A60.word44;
        unsigned int word48 = lbl_80598A60.word48;
        unsigned int word4C = lbl_80598A60.word4C;
        unsigned short half50 = lbl_80598A60.half50;
        unsigned char byte52 = lbl_80598A60.packed52.byte52;
        unsigned int word53 = lbl_80598A60.packed52.word53;
        unsigned int word57 = lbl_80598A60.packed52.word57;
        unsigned int word5B = lbl_80598A60.packed52.word5B;
        unsigned short half5F = lbl_80598A60.packed52.half5F;
        lbl_8059F480.byte00 = byte00;
        lbl_8059F480.word04 = word04;
        lbl_8059F480.word08 = word08;
        lbl_8059F480.word0C = word0C;
        lbl_8059F480.word10 = word10;
        lbl_8059F480.word1C = word1C;
        lbl_8059F480.word18 = word18;
        lbl_8059F480.word20 = word20;
        lbl_8059F480.word24 = word24;
        lbl_8059F480.half28 = half28;
        lbl_8059F480.packed2A.byte2A = byte2A;
        lbl_8059F480.packed2A.word2B = word2B;
        lbl_8059F480.packed2A.half2F = half2F;
        lbl_8059F480.packed2A.byte31 = byte31;
        lbl_8059F480.word34 = word34;
        lbl_8059F480.word38 = word38;
        lbl_8059F480.word3C = word3C;
        lbl_8059F480.word40 = word40;
        lbl_8059F480.word44 = word44;
        lbl_8059F480.word48 = word48;
        lbl_8059F480.word4C = word4C;
        lbl_8059F480.half50 = half50;
        lbl_8059F480.packed52.byte52 = byte52;
        lbl_8059F480.packed52.word53 = word53;
        lbl_8059F480.packed52.word57 = word57;
        lbl_8059F480.packed52.word5B = word5B;
        lbl_8059F480.packed52.half5F = half5F;
    }
    lbl_8059F480.block64 = lbl_80598A60.block64;
    lbl_8059F480.block274 = lbl_80598A60.block274;
    lbl_8059F480.block4E0 = lbl_80598A60.block4E0;
    lbl_8059F480.block31E0 = lbl_80598A60.block31E0;
}

#pragma exceptions on
void FrameUpdate(void)
{
    if (lbl_806D1124 != 0 && --lbl_806D1124 <= 0) {
        lbl_80598A60.word40 = *(unsigned short *)(g_jvsOperatorBits + 0xA);
        lbl_80598A60.word3C = *(unsigned short *)(g_jvsOperatorBits + 0xC);
        if (lbl_806D1120 && lbl_806D1128 == 0) {
            fn_80288210(0);
            FrameBackup_Copy();
        }
    }
    if (lbl_806D1114 > 0) --lbl_806D1114;
    ++lbl_806D1110;
}
#pragma exceptions reset
