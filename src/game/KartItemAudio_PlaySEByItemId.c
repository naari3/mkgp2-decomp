/*
 * KartItemAudio_PlaySEByItemId @ 0x8005982C (size 0x644)
 *
 * Plays the character voice line that goes with using an item. The voice
 * SE id is (per-character voice base + per-item offset); the base comes from
 * a 13-entry table indexed by self->charId. Six item ids are excluded up
 * front (no voice). Every played voice is followed by the same positional
 * update as the other KartItemAudio dispatchers, and voiceHandle (0x28) is
 * reset to -1.
 *
 * The target addresses the voice table, the exclusion list and the shared
 * zero Vec3 through one hoisted base (lbl_802EDC70, then +0x34 / +0xB4) and
 * keeps an `addi rX, base, 0` for the voice table. CW emits that shape for
 * objects defined in the same TU, so this TU owns .rodata 0x802EDC70..
 * 0x802EDD30 and defines the four objects there (lbl_802EDCBC and
 * lbl_802EDD24 stay global: other TUs reference them). An extern struct
 * overlay only reaches ~96-97% (offsets get folded into displacements).
 * The function is
 * its own reversed-extab singleton (extab 0x800076F0, extabindex 0x80020900);
 * KartItemAudio.c (0x8005A140..) cannot absorb it because the 0x80059E70..
 * 0x8005A140 gap belongs to other TUs.
 */

extern int ItemAlias_DestToSource(unsigned int itemDestId, void *aliasOut);
extern int SoundMgr_PlaySE(int soundId);
extern int isJapanese(void);
extern void fn_8016C288(); /* positional SE update (id, Vec3 *pos) */

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

/* .rodata 0x802EDC70..0x802EDD30 */
const int lbl_802EDC70[13] = {
    0xD7, 0xEC, 0x101, 0x116, 0x12B, 0x141, 0x156, 0x16B, 0x180, 0x195, 0x1AA, 0x1C0, 0x1D5,
};
const int lbl_802EDCA4[6] = { 0x52, 0x53, 0xA7, 0x10A, 0x2A, 0xFB };
const unsigned int lbl_802EDCBC[26] = {
    0x004, 0x7E, 0x800, 0x77, 0x008, 0x76, 0x040, 0x76, 0x080, 0x76, 0x010, 0x7C, 0x001,
    0x73,  0x002, 0x73, 0x020, 0x74, 0x200, 0x7A, 0x100, 0x79, 0x400, 0x7F, 0x000, 0xFFFFFFFF,
};
const Vec3 lbl_802EDD24 = { 0.0f, 0.0f, 0.0f };

typedef struct KartItemAudio {
    int charId;               /* 0x0 */
    unsigned char playerType; /* 0x4: 1 = local player */
    unsigned char pad_5;
    unsigned char voiceOn;    /* 0x6 */
    unsigned char pad_7;
    unsigned int channel;     /* 0x8: low 4 bits = SE channel (encoded << 27) */
    float *mtx;               /* 0xC: 3x4 matrix; translation column at [3],[7],[11] */
    unsigned char pad_10[0x18];
    int voiceHandle;          /* 0x28 */
} KartItemAudio;

static inline unsigned char KartItemAudio_IsVoicedItem(int itemId) {
    const int *p = lbl_802EDCA4;
    int i;
    for (i = 0; i < 6; i++, p++) {
        if (itemId == *p) {
            return 0;
        }
    }
    return 1;
}

#define KIA_PLAY_VOICE(self, ofs)                                       \
    if (self->voiceOn != 0) {                                           \
        int se = lbl_802EDC70[self->charId] + (ofs);                    \
        isJapanese();                                                   \
        SoundMgr_PlaySE(se | ((self->channel & 0xF) << 27));            \
        if (self->playerType == 0) {                                    \
            float *mtx = self->mtx;                                     \
            if (mtx != 0) {                                             \
                Vec3 pos = lbl_802EDD24;                                \
                pos.x = mtx[3];                                         \
                pos.y = mtx[7];                                         \
                pos.z = mtx[11];                                        \
                fn_8016C288(se | ((self->channel & 0xF) << 27), &pos);  \
            }                                                           \
        }                                                               \
        self->voiceHandle = -1;                                         \
    }

#pragma exceptions on

void KartItemAudio_PlaySEByItemId(KartItemAudio *self, int itemId) {
    unsigned char aliasScratch[4];
    int srcId;

    if (!KartItemAudio_IsVoicedItem(itemId)) {
        return;
    }
    if (itemId < 0x115) {
        srcId = ItemAlias_DestToSource(itemId & 0xFF, aliasScratch);
    } else {
        srcId = itemId;
    }
    switch (srcId) {
    case 0x8:
    case 0x2B:
    case 0x2D:
    case 0x37:
    case 0x38:
    case 0x42:
    case 0x46:
    case 0x47:
    case 0x48:
    case 0x4A:
    case 0x4B:
    case 0x4D:
    case 0x50:
    case 0x5B:
    case 0x5C:
    case 0x5D:
    case 0x65:
    case 0x69:
    case 0x137:
        KIA_PLAY_VOICE(self, 0xC);
        break;
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x121:
        KIA_PLAY_VOICE(self, 0x3);
        break;
    case 0x3D:
    case 0x3F:
        KIA_PLAY_VOICE(self, 0xD);
        break;
    case 0x64:
        KIA_PLAY_VOICE(self, 0xE);
        break;
    case 0x3E:
    case 0x4F:
    case 0x63:
        KIA_PLAY_VOICE(self, 0xF);
        break;
    case 0x39:
    case 0x3B:
        KIA_PLAY_VOICE(self, 0x10);
        break;
    case 0x53:
        break;
    case 0x3C:
    case 0x49:
    case 0x4C:
    default:
        KIA_PLAY_VOICE(self, 0xE);
        break;
    }
}

#pragma exceptions reset
