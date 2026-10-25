/*
 * SoundVolumePan_Update @ 0x80058F5C..0x800594D4: per-frame update of a
 * kart audio channel (layout set up by KartAudioChannel_Init). Fades the
 * engine loop volume (0x10/0x14) and the second channel (0x1C/0x20) toward
 * their targets in steps of 0.1, starts/stops the loop SEs, pushes volume
 * and pitch, and drives the 0x8A skid SE. SE ids are
 * ((channel & 0xF) << 27) | base, as in KartItemAudio.c.
 */

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct KartAudioChannel {
    unsigned char pad_0[4];
    unsigned char playerType; /* 0x04 */
    unsigned char enabled;    /* 0x05 */
    unsigned char pad_6[2];
    unsigned int channel;     /* 0x08 */
    float *mtx;               /* 0x0C */
    float targetVol;          /* 0x10 */
    float vol;                /* 0x14 */
    unsigned char playing;    /* 0x18 */
    unsigned char pad_19[3];
    float targetPitch;        /* 0x1C */
    float pitch;              /* 0x20 */
    int mode;                 /* 0x24 */
    int pendingStopSE;        /* 0x28 */
    int stopTimer;            /* 0x2C */
    int skidState;            /* 0x30 */
} KartAudioChannel;

extern const Vec3 lbl_802EDD24;
extern const Vec3 lbl_802EDD30;
extern int SoundMgr_PlaySE(int soundId);
extern void fn_8016C288();
extern void fn_8016C394();
extern void fn_8016C0D8();
extern unsigned char fn_8016C360();
extern int Clamp_Int(int v, int lo, int hi);

#define KAC_SE_ID(self, base) (((self->channel & 0xF) << 27) | (base))

#define KAC_PLAY_POSITIONAL(self, base)                     \
    SoundMgr_PlaySE(KAC_SE_ID(self, base));                 \
    if (self->playerType == 0) {                            \
        float *mtx = self->mtx;                             \
        if (mtx != 0) {                                     \
            Vec3 pos = lbl_802EDD24;                        \
            pos.x = mtx[3];                                 \
            pos.y = mtx[7];                                 \
            pos.z = mtx[11];                                \
            fn_8016C288(KAC_SE_ID(self, base), &pos);       \
        }                                                   \
    }

/* Inline (not the macro) so its Vec3 gets the stack slot after the
 * skid position update's. */
static inline void KAC_PlaySkid(KartAudioChannel *self)
{
    KAC_PLAY_POSITIONAL(self, 0x8A);
}

#pragma exceptions on

void SoundVolumePan_Update(KartAudioChannel *self)
{
    int pitch;

    if (self->pendingStopSE >= 0) {
        if (--self->stopTimer <= 0) {
            fn_8016C394(self->pendingStopSE | ((self->channel & 0xF) << 27));
            self->pendingStopSE = -1;
        }
    }

    if (self->vol != self->targetVol) {
        if (self->vol > self->targetVol) {
            self->vol -= 0.1f;
            if (self->vol < self->targetVol) {
                self->vol = self->targetVol;
            }
        } else {
            self->vol += 0.1f;
            if (self->vol > self->targetVol) {
                self->vol = self->targetVol;
            }
        }
    }
    if (self->vol <= 0.0f) {
        self->targetVol = 0.0f;
        self->vol = 0.0f;
        if (self->playing == 1) {
            switch (self->mode) {
            case 0:
                fn_8016C394(KAC_SE_ID(self, 0x51));
                break;
            case 1:
                fn_8016C394(KAC_SE_ID(self, 0x52));
                break;
            }
            self->playing = 0;
        }
    } else if (self->playing == 0) {
        self->playing = 1;
        if (self->enabled == 1) {
            switch (self->mode) {
            case 0:
                KAC_PLAY_POSITIONAL(self, 0x51);
                break;
            case 1:
                KAC_PLAY_POSITIONAL(self, 0x52);
                break;
            }
        }
    }
    if (self->playing == 1) {
        switch (self->mode) {
        case 0:
            fn_8016C0D8(KAC_SE_ID(self, 0x51), (int)(16380.0f * self->vol));
            break;
        case 1:
            fn_8016C0D8(KAC_SE_ID(self, 0x52), (int)(16380.0f * self->vol));
            break;
        }
    }

    if (self->pitch != self->targetPitch) {
        if (self->pitch > self->targetPitch) {
            self->pitch -= 0.1f;
            if (self->pitch < self->targetPitch) {
                self->pitch = self->targetPitch;
            }
        } else {
            self->pitch += 0.1f;
            if (self->pitch > self->targetPitch) {
                self->pitch = self->targetPitch;
            }
        }
    }
    if (self->pitch <= 0.0f) {
        self->targetPitch = 0.0f;
        self->pitch = 0.0f;
    }
    if (!fn_8016C360(KAC_SE_ID(self, 0x50)) && self->enabled == 1) {
        KAC_PLAY_POSITIONAL(self, 0x50);
    }
    pitch = Clamp_Int((int)(8192.0f * self->pitch) + 0x2000, 0x2000, 0x3F80);
    if (fn_8016C360(KAC_SE_ID(self, 0x50)) == 1 && self->enabled == 1) {
        fn_8016C0D8(KAC_SE_ID(self, 0x50), (unsigned short)pitch);
    }

    if (self->skidState == 2) {
        if (self->pitch > 0.01f) {
            if (!fn_8016C360(KAC_SE_ID(self, 0x8A))) {
                self->skidState = 2;
                KAC_PlaySkid(self);
            }
            if (self->mtx != 0) {
                float *mtx = self->mtx;
                Vec3 pos = lbl_802EDD30;
                pos.x = mtx[3];
                pos.y = mtx[7];
                pos.z = mtx[11];
                fn_8016C288(KAC_SE_ID(self, 0x8A), &pos);
            }
        } else if (self->skidState != -1) {
            fn_8016C394(KAC_SE_ID(self, 0x8A));
        }
    }
}

#pragma exceptions reset
