/* Change the channel's engine state; leaving state 0 or 1 stops that
 * state's looping SE. */
typedef struct KartAudioChannel {
    unsigned char pad00[0x8];
    int channel;           /* 0x08 */
    unsigned char pad0c[0xc];
    unsigned char playing; /* 0x18 */
    unsigned char pad19[0xb];
    int state;             /* 0x24 */
} KartAudioChannel;

extern void fn_8016C394(unsigned int id);

void KartAudioChannel_Set24WithSeStop(KartAudioChannel *self, int state)
{
    if (self->state != state) {
        switch (self->state) {
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
    self->state = state;
}
