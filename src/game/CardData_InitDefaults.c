/*
 * CardData_InitDefaults, 0x80090C88..0x80090FF0: resets the in-memory
 * card save image to a fresh card.
 *
 * NonMatching: only the epilogue order differs (the target reloads LR
 * before r31/r30).
 */

typedef struct CardData {
    unsigned short header[6]; /* 0x000 */
    signed char field0C; /* 0x00C */
    unsigned char field0D; /* 0x00D */
    unsigned char field0E; /* 0x00E */
    unsigned char name[0x30]; /* 0x00F */
    unsigned char pad03F;
    int field40; /* 0x040 */
    int field44; /* 0x044 */
    unsigned char pad048[0xB4 - 0x48];
    unsigned char unlocks[0x3C]; /* 0x0B4 */
    unsigned char records[0x64]; /* 0x0F0 */
    unsigned char pad154[0x16C - 0x154];
    unsigned char field16C; /* 0x16C */
    unsigned char field16D; /* 0x16D */
    unsigned char pad16E[0x17B - 0x16E];
    unsigned char field17B; /* 0x17B */
    unsigned char field17C; /* 0x17C */
    unsigned char field17D; /* 0x17D */
    unsigned char volumeFlag; /* 0x17E */
    unsigned char field17F; /* 0x17F */
    int language; /* 0x180 */
    unsigned char field184; /* 0x184 */
    unsigned char pad185[3];
    int field188; /* 0x188 */
    int field18C; /* 0x18C */
    int field190; /* 0x190 */
    unsigned char pad194[4];
    unsigned char field198; /* 0x198 */
} CardData;

extern void *memset(void *dst, int c, unsigned long n);
int isJapanese(void);
void SetCardVolumeFlagByte(unsigned char v);

#pragma exceptions on

void CardData_InitDefaults(CardData *data, unsigned char applyVolume)
{
    int i;

    for (i = 0; i < 6; i++) {
        data->header[i] = 0;
    }
    for (i = 0; i < 0x3C; i++) {
        data->unlocks[i] = 0;
    }
    {
        int j;
        for (j = 0; j < 0x64; j++) {
            data->records[j] = 0;
        }
    }
    data->language = isJapanese();
    data->field0C = -1;
    data->field16C = 50;
    data->field16D = 0;
    data->field0D = 2;
    memset(data, 0, 0xC);
    data->field40 = 0;
    data->field17D = 1;
    data->unlocks[0] = 1;
    data->unlocks[1] = 1;
    data->unlocks[2] = 1;
    data->unlocks[3] = 1;
    data->unlocks[4] = 1;
    data->unlocks[5] = 1;
    data->unlocks[6] = 1;
    data->unlocks[7] = 1;
    data->unlocks[8] = 1;
    data->unlocks[9] = 1;
    data->unlocks[10] = 1;
    data->unlocks[11] = 1;
    data->unlocks[23] = 1;
    data->unlocks[22] = 1;
    data->field0E = 0xFF;
    data->field17B = 0;
    data->field17C = 0xFF;
    data->volumeFlag = 0;
    if (applyVolume == 1) {
        SetCardVolumeFlagByte(data->volumeFlag);
    }
    for (i = 0; i < 0x30; i++) {
        data->name[i] = 0;
    }
    data->field188 = 0;
    data->field18C = 0;
    data->field190 = 0;
    data->field184 = 0;
    data->field44 = data->field40;
    data->field198 = 0;
    data->field17F = 0;
}

#pragma exceptions reset
