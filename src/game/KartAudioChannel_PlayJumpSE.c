/* Play the jump SE for a jump kind (0..2), and its positional copy at the
 * kart when the channel has a source and is not muted. */
#include "game/types/Vec.h"

#include "game/types/SoundSource.h"

typedef struct KartAudioChannel {
    unsigned char pad00[0x4];
    unsigned char muted;   /* 0x04 */
    unsigned char pad05[0x3];
    int channel;           /* 0x08 */
    SoundSource *source;   /* 0x0C */
    unsigned char pad10[0x20];
    int jumpKind;          /* 0x30 */
} KartAudioChannel;

extern const Vec KartItemAudio_PlaySEByItemId_rodata_802EDD24;
extern void SoundMgr_PlaySE(unsigned int id);
extern void fn_8016C288(unsigned int id, Vec *pos);

void KartAudioChannel_PlayJumpSE(KartAudioChannel *self, int kind)
{
    unsigned int id;
    SoundSource *src;

    switch (kind) {
    case 0:
        id = 0x8b;
        break;
    case 1:
        id = 0x8c;
        break;
    case 2:
        id = 0x8a;
        break;
    default:
        return;
    }
    self->jumpKind = kind;
    SoundMgr_PlaySE(id | ((self->channel & 0xf) << 27));
    if (self->muted == 0) {
        src = self->source;
        if (src != 0) {
            Vec pos = KartItemAudio_PlaySEByItemId_rodata_802EDD24;
            pos.x = src->x;
            pos.y = src->y;
            pos.z = src->z;
            fn_8016C288(id | ((self->channel & 0xf) << 27), &pos);
        }
    }
}
