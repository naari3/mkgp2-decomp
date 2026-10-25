/*
 * Statistics block copy, 0x8008DE60..0x8008E33C (GC/2.6).
 * The copy is three runs of pair copies; it is 99.7%: the scheduler
 * hoists the 0x1A4 load above the 0x1A0 store, the target does not.
 */

typedef struct PlayStatsPair {
    unsigned int a;
    unsigned int b;
} PlayStatsPair;

typedef struct PlayStatsBlock {
    PlayStatsPair p0[26];
    unsigned int w1;
    PlayStatsPair p2[25];
    unsigned int w3;
    unsigned int w4;
    PlayStatsPair p5[25];
} PlayStatsBlock;

typedef struct BackupStatsShadow {
    unsigned char pad000[0x274];
    PlayStatsBlock stats;
} BackupStatsShadow;

extern BackupStatsShadow lbl_80598A60;
extern PlayStatsBlock lbl_805AC2E0;

void Backup_PublishShadowCopy_Inline(void);
void PlayStats_CopyStatsBlock(PlayStatsBlock *dst, const PlayStatsBlock *src);

void PlayStats_CopyStatsBlock(PlayStatsBlock *dst, const PlayStatsBlock *src)
{
    dst->p0[0] = src->p0[0];
    dst->p0[1] = src->p0[1];
    dst->p0[2] = src->p0[2];
    dst->p0[3] = src->p0[3];
    dst->p0[4] = src->p0[4];
    dst->p0[5] = src->p0[5];
    dst->p0[6] = src->p0[6];
    dst->p0[7] = src->p0[7];
    dst->p0[8] = src->p0[8];
    dst->p0[9] = src->p0[9];
    dst->p0[10] = src->p0[10];
    dst->p0[11] = src->p0[11];
    dst->p0[12] = src->p0[12];
    dst->p0[13] = src->p0[13];
    dst->p0[14] = src->p0[14];
    dst->p0[15] = src->p0[15];
    dst->p0[16] = src->p0[16];
    dst->p0[17] = src->p0[17];
    dst->p0[18] = src->p0[18];
    dst->p0[19] = src->p0[19];
    dst->p0[20] = src->p0[20];
    dst->p0[21] = src->p0[21];
    dst->p0[22] = src->p0[22];
    dst->p0[23] = src->p0[23];
    dst->p0[24] = src->p0[24];
    dst->p0[25] = src->p0[25];
    dst->w1 = src->w1;
    dst->p2[0] = src->p2[0];
    dst->p2[1] = src->p2[1];
    dst->p2[2] = src->p2[2];
    dst->p2[3] = src->p2[3];
    dst->p2[4] = src->p2[4];
    dst->p2[5] = src->p2[5];
    dst->p2[6] = src->p2[6];
    dst->p2[7] = src->p2[7];
    dst->p2[8] = src->p2[8];
    dst->p2[9] = src->p2[9];
    dst->p2[10] = src->p2[10];
    dst->p2[11] = src->p2[11];
    dst->p2[12] = src->p2[12];
    dst->p2[13] = src->p2[13];
    dst->p2[14] = src->p2[14];
    dst->p2[15] = src->p2[15];
    dst->p2[16] = src->p2[16];
    dst->p2[17] = src->p2[17];
    dst->p2[18] = src->p2[18];
    dst->p2[19] = src->p2[19];
    dst->p2[20] = src->p2[20];
    dst->p2[21] = src->p2[21];
    dst->p2[22] = src->p2[22];
    dst->p2[23] = src->p2[23];
    dst->p2[24] = src->p2[24];
    dst->w3 = src->w3;
    dst->w4 = src->w4;
    dst->p5[0] = src->p5[0];
    dst->p5[1] = src->p5[1];
    dst->p5[2] = src->p5[2];
    dst->p5[3] = src->p5[3];
    dst->p5[4] = src->p5[4];
    dst->p5[5] = src->p5[5];
    dst->p5[6] = src->p5[6];
    dst->p5[7] = src->p5[7];
    dst->p5[8] = src->p5[8];
    dst->p5[9] = src->p5[9];
    dst->p5[10] = src->p5[10];
    dst->p5[11] = src->p5[11];
    dst->p5[12] = src->p5[12];
    dst->p5[13] = src->p5[13];
    dst->p5[14] = src->p5[14];
    dst->p5[15] = src->p5[15];
    dst->p5[16] = src->p5[16];
    dst->p5[17] = src->p5[17];
    dst->p5[18] = src->p5[18];
    dst->p5[19] = src->p5[19];
    dst->p5[20] = src->p5[20];
    dst->p5[21] = src->p5[21];
    dst->p5[22] = src->p5[22];
    dst->p5[23] = src->p5[23];
    dst->p5[24] = src->p5[24];
}
