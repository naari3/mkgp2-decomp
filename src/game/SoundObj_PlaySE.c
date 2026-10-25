/*
 * SoundObj_PlaySE, 0x80059E70..0x80059F70: plays a character voice line
 * (voice base + offset) and its positional update.
 */

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct SoundObj {
    int charId;               /* 0x0 */
    unsigned char playerType; /* 0x4 */
    unsigned char pad_5;
    unsigned char voiceOn;    /* 0x6 */
    unsigned char pad_7;
    unsigned int channel;     /* 0x8 */
    float *mtx;               /* 0xC */
    unsigned char pad_10[0x18];
    int voiceHandle;          /* 0x28 */
} SoundObj;

extern const int lbl_802EDC70[13]; /* per-character voice base */
extern const Vec3 lbl_802EDD24;

extern int SoundMgr_PlaySE(int soundId);
extern int isJapanese(void);
extern void fn_8016C288(); /* positional SE update (id, Vec3 *pos) */

#pragma exceptions on

void SoundObj_PlaySE(SoundObj *self, int ofs)
{
    int se;

    if (self->voiceOn != 0) {
        se = ofs + lbl_802EDC70[self->charId];
        if (isJapanese() == 1 && self->charId == 10 && ofs == 0) {
            se = 0x1BF;
        }
        SoundMgr_PlaySE(se | ((self->channel & 0xF) << 27));
        if (self->playerType == 0) {
            float *mtx = self->mtx;
            if (mtx != 0) {
                Vec3 pos = lbl_802EDD24;
                pos.x = mtx[3];
                pos.y = mtx[7];
                pos.z = mtx[11];
                fn_8016C288(se | ((self->channel & 0xF) << 27), &pos);
            }
        }
        self->voiceHandle = -1;
    }
}

#pragma exceptions reset
