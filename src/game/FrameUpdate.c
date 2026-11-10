#include "game/FrameUpdate_private.h"

static inline void FrameBackup_Copy(void)
{
    {
        unsigned char byte00 = lbl_80598A60.byte00;
        unsigned int word04 = lbl_80598A60.word04;
        unsigned int word08 = lbl_80598A60.word08;
        unsigned int word0C = lbl_80598A60.word0C;
        unsigned int word10 = lbl_80598A60.word10;
        unsigned long long qw18 = lbl_80598A60.qw18;
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
        g_backupShadowCopy.byte00 = byte00;
        g_backupShadowCopy.word04 = word04;
        g_backupShadowCopy.word08 = word08;
        g_backupShadowCopy.word0C = word0C;
        g_backupShadowCopy.word10 = word10;
        g_backupShadowCopy.qw18 = qw18;
        g_backupShadowCopy.word20 = word20;
        g_backupShadowCopy.word24 = word24;
        g_backupShadowCopy.half28 = half28;
        g_backupShadowCopy.packed2A.byte2A = byte2A;
        g_backupShadowCopy.packed2A.word2B = word2B;
        g_backupShadowCopy.packed2A.half2F = half2F;
        g_backupShadowCopy.packed2A.byte31 = byte31;
        g_backupShadowCopy.word34 = word34;
        g_backupShadowCopy.word38 = word38;
        g_backupShadowCopy.word3C = word3C;
        g_backupShadowCopy.word40 = word40;
        g_backupShadowCopy.word44 = word44;
        g_backupShadowCopy.word48 = word48;
        g_backupShadowCopy.word4C = word4C;
        g_backupShadowCopy.half50 = half50;
        g_backupShadowCopy.packed52.byte52 = byte52;
        g_backupShadowCopy.packed52.word53 = word53;
        g_backupShadowCopy.packed52.word57 = word57;
        g_backupShadowCopy.packed52.word5B = word5B;
        g_backupShadowCopy.packed52.half5F = half5F;
    }
    g_backupShadowCopy.block64 = lbl_80598A60.block64;
    g_backupShadowCopy.block274 = lbl_80598A60.block274;
    g_backupShadowCopy.block4E0 = lbl_80598A60.block4E0;
    g_backupShadowCopy.block31E0 = lbl_80598A60.block31E0;
}

static inline void FrameBackup_CaptureCalibration(struct FrameBackup *backup,
                                                 const unsigned short *bits)
{
    backup->word40 = bits[5];
    backup->word3C = bits[6];
}

#pragma exceptions on
#pragma push
#pragma opt_common_subs off
void FrameUpdate(void)
{
    if (lbl_806D1124 != 0 && --lbl_806D1124 <= 0) {
        FrameBackup_CaptureCalibration(&lbl_80598A60, (const unsigned short *)g_jvsOperatorBits);
        if (lbl_806D1120 != 0 && lbl_806D1128 == 0) {
            fn_80288210(0, &lbl_80598A60);
            FrameBackup_Copy();
        }
    }
    if (lbl_806D1114 > 0) --lbl_806D1114;
    ++lbl_806D1110;
}
#pragma pop

#pragma exceptions reset
