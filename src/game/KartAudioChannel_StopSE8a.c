/* Stop SE 0x8A on the kart's channel; optionally forget its handle. */
#include "game/types/KartAudioChannel.h"

extern void fn_8016C394(unsigned int id);

void KartAudioChannel_StopSE8a(KartAudioChannel *self, unsigned char clear)
{
    if (self->skidState != -1) {
        fn_8016C394(((self->channel & 0xf) << 27) | 0x8a);
        if (clear == 1) {
            self->skidState = -1;
        }
    }
}
