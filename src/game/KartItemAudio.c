/*
 * KartItemAudio item-SE dispatchers.
 *
 *   KartItemAudio_StopSEByItemId     @ 0x8005A140 (size 0x1D4)
 *   KartItemAudio_PlayHitConfirmSE   @ 0x8005A314 (size 0x324)
 *   KartItemAudio_PlayThrowConfirmSE @ 0x8005A638 (size 0x3CC)
 *
 * All three take (KartItemAudio *self, int itemId). itemIds < 0x115 are
 * canonicalized through ItemAlias_DestToSource first. The SE id is built as
 * ((self->channel & 0xF) << 27) | <seBase> (clrlslwi + ori in the target).
 *
 * If self->playerType == 0 and self->mtx != NULL, every played SE is
 * followed by a positional update (fn_8016C288) using the translation
 * column of the 3x4 matrix at self->mtx ([3], [7], [11]). The Vec3 is
 * initialized from the shared zero vector lbl_802EDD24 and then overwritten
 * component-wise (the dead struct copy is emitted by CW and kept).
 *
 * Each function is its own dtk reversed-extab singleton group; the three
 * extab (0x80007710..0x80007728) and extabindex (0x80020930..0x80020954)
 * entries are contiguous, so one TU covers all three. CW auto-emits the
 * 8-byte extab entries via `#pragma exceptions on`.
 *
 * StopSE / PlayHit are sparse switches that CW lowers to a comparison tree;
 * PlayThrowConfirmSE is dense enough to get a jump table
 * (jumptable_803F9968 in .data).
 */

extern int ItemAlias_DestToSource(unsigned int itemDestId, void *aliasOut);
extern int SoundMgr_PlaySE(int soundId);
extern void KartItemAudio_PlaySEByItemId(); /* 0x8005982C: play the item's main SE */
extern void fn_8016C288();                  /* positional SE update (id, Vec3 *pos) */
extern void fn_8016C394();                  /* stop SE by id */
extern void fn_8016C488();                  /* global SE stop (mode) */
extern void fn_8016C4CC();                  /* global SE stop / reset (mode) */

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

/* Shared zero Vec3 in .rodata (0x802EDD24). */
extern const Vec3 lbl_802EDD24;

typedef struct KartItemAudio {
    unsigned char pad_0[4];
    unsigned char playerType; /* 0x4: 1 = local player */
    unsigned char pad_5[3];
    unsigned int channel;     /* 0x8: low 4 bits = SE channel (encoded << 27) */
    float *mtx;               /* 0xC: 3x4 matrix; translation column at [3],[7],[11] */
} KartItemAudio;

#define KIA_SE_ID(self, base) (((self->channel & 0xF) << 27) | (base))

/* Play SE `base`, then update its 3D position from the kart matrix when
 * this audio context belongs to a remote kart with a valid matrix. */
#define KIA_PLAY_POSITIONAL(self, base)                     \
    SoundMgr_PlaySE(KIA_SE_ID(self, base));                 \
    if (self->playerType == 0) {                            \
        float *mtx = self->mtx;                             \
        if (mtx != 0) {                                     \
            Vec3 pos = lbl_802EDD24;                        \
            pos.x = mtx[3];                                 \
            pos.y = mtx[7];                                 \
            pos.z = mtx[11];                                \
            fn_8016C288(KIA_SE_ID(self, base), &pos);       \
        }                                                   \
    }

#pragma exceptions on

void KartItemAudio_StopSEByItemId(KartItemAudio *self, int itemId) {
    unsigned char aliasScratch[4];
    int srcId;

    if (itemId < 0x115) {
        srcId = ItemAlias_DestToSource(itemId & 0xFF, aliasScratch);
    } else {
        srcId = itemId;
    }
    switch (srcId) {
    case 0xE:
    case 0x10:
    case 0x15:
    case 0x16:
    case 0x1E:
    case 0x1F:
    case 0x20:
    case 0x24:
    case 0x28:
        if (self->playerType == 1) {
            fn_8016C488(0);
        }
        break;
    case 0x21:
        if (self->playerType == 1) {
            fn_8016C394(KIA_SE_ID(self, 0xC5));
        }
        break;
    case 0x3C:
        if (self->playerType == 1) {
            fn_8016C4CC(0);
        }
        break;
    case 0x19:
        KIA_PLAY_POSITIONAL(self, 0xA2);
        break;
    case 0x2D:
    case 0x46:
    case 0x5D:
        fn_8016C394(KIA_SE_ID(self, 0x8A));
        break;
    case 0x98:
        fn_8016C394(KIA_SE_ID(self, 0xCF));
        break;
    }
}

void KartItemAudio_PlayHitConfirmSE(KartItemAudio *self, int itemId) {
    unsigned char aliasScratch[4];
    int srcId;

    if (itemId < 0x115) {
        srcId = ItemAlias_DestToSource(itemId & 0xFF, aliasScratch);
    } else {
        srcId = itemId;
    }
    KartItemAudio_PlaySEByItemId(self, srcId);
    switch (srcId) {
    case 0x2D:
    case 0x46:
    case 0x5D:
        KIA_PLAY_POSITIONAL(self, 0x63);
        KIA_PLAY_POSITIONAL(self, 0x8A);
        break;
    case 0x39:
    case 0x3A:
        KIA_PLAY_POSITIONAL(self, 0x85);
        break;
    case 0x50:
        KIA_PLAY_POSITIONAL(self, 0x84);
        break;
    case 0x3C:
        if (self->playerType == 1) {
            fn_8016C4CC(1);
        }
        break;
    case 0x98:
        KIA_PLAY_POSITIONAL(self, 0xCF);
        break;
    }
}

void KartItemAudio_PlayThrowConfirmSE(KartItemAudio *self, int itemId) {
    unsigned char aliasScratch[4];
    int srcId;

    if (itemId < 0x115) {
        srcId = ItemAlias_DestToSource(itemId & 0xFF, aliasScratch);
    } else {
        srcId = itemId;
    }
    switch (srcId) {
    case 0xE:
    case 0x10:
    case 0x15:
    case 0x16:
    case 0x1E:
    case 0x1F:
    case 0x20:
    case 0x24:
    case 0x28:
        if (self->playerType == 1) {
            fn_8016C488(1);
        }
        break;
    case 0x1D:
        KIA_PLAY_POSITIONAL(self, 0xC6);
        break;
    case 0x23:
        KIA_PLAY_POSITIONAL(self, 0xA4);
        break;
    case 0x1C:
        KIA_PLAY_POSITIONAL(self, 0xC7);
        break;
    case 0x21:
        KIA_PLAY_POSITIONAL(self, 0xC7);
        if (self->playerType == 1) {
            KIA_PLAY_POSITIONAL(self, 0xC5);
        }
        break;
    case 0x19:
        KIA_PLAY_POSITIONAL(self, 0xA1);
        break;
    case 0xC:
    case 0xD:
    case 0xF:
    case 0x11:
    case 0x13:
    case 0x14:
    case 0x18:
    case 0x25:
    case 0x26:
    case 0x27:
        KIA_PLAY_POSITIONAL(self, 0x64);
        break;
    }
}

#pragma exceptions reset
