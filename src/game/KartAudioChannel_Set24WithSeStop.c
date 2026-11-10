/* Change the channel's engine state; leaving state 0 or 1 stops that
 * state's looping SE. */
#include "game/types/KartAudioChannel.h"

extern void fn_8016C394(unsigned int id);

void KartAudioChannel_Set24WithSeStop(KartAudioChannel *self, int state)
{
    if (self->mode != state) {
        switch (self->mode) {
        case 0:
            fn_8016C394(((self->channel & 0xf) << 27) | 0x51);
            break;
        case 1:
            fn_8016C394(((self->channel & 0xf) << 27) | 0x52);
            break;
        default:
            return;
        }
        self->playing = 0;
    }
    self->mode = state;
}
