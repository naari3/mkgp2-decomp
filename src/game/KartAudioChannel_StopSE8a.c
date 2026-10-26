/* Stop SE 0x8A on the kart's channel; optionally forget its handle. */
typedef struct KartAudioChannel {
    unsigned char pad00[0x8];
    int channel;   /* 0x08 */
    unsigned char pad0C[0x24];
    int handle30;  /* 0x30 */
} KartAudioChannel;

extern void fn_8016C394(unsigned int id);

void KartAudioChannel_StopSE8a(KartAudioChannel *self, unsigned char clear)
{
    if (self->handle30 != -1) {
        fn_8016C394(((self->channel & 0xf) << 27) | 0x8a);
        if (clear == 1) {
            self->handle30 = -1;
        }
    }
}
