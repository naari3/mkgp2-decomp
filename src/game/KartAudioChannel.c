/* KartAudioChannel: per-kart SE channel state. */

typedef struct KartAudioChannel {
    void *owner;          /* 0x00 */
    unsigned char flag4;  /* 0x04 */
    unsigned char flag5;  /* 0x05 */
    unsigned char flag6;  /* 0x06 */
    unsigned char pad07;
    int channel;          /* 0x08 */
    int param0C;          /* 0x0C */
    float volume;         /* 0x10 */
    float pitch;          /* 0x14 */
    unsigned char active; /* 0x18 */
    unsigned char pad19[3];
    float volume2;        /* 0x1C */
    float pitch2;         /* 0x20 */
    int count24;          /* 0x24 */
    int handle28;         /* 0x28 */
    int count2C;          /* 0x2C */
    int handle30;         /* 0x30 */
    int handle34;         /* 0x34 */
} KartAudioChannel;

extern const float lbl_806D2940;
extern void fn_8016C394(int id);

void KartAudioChannel_Init(KartAudioChannel *self, void *owner, unsigned char flag,
                           unsigned char flag6, int channel, int param0C)
{
    self->owner = owner;
    self->flag5 = flag;
    self->flag4 = flag;
    self->flag6 = flag6;
    self->channel = channel;
    self->param0C = param0C;
    self->volume = lbl_806D2940;
    self->pitch = lbl_806D2940;
    self->active = 0;
    self->volume2 = lbl_806D2940;
    self->pitch2 = lbl_806D2940;
    self->count24 = 0;
    self->handle28 = -1;
    self->count2C = 0;
    self->handle34 = -1;
    self->handle30 = -1;
}

#pragma exceptions on
void KartAudioChannel_ResetSEsAndSetFlag(KartAudioChannel *self, unsigned char flag)
{
    fn_8016C394(((self->channel & 0xf) << 27) | 0x52);
    fn_8016C394(((self->channel & 0xf) << 27) | 0x51);
    fn_8016C394(((self->channel & 0xf) << 27) | 0x50);
    self->flag4 = flag;
}
#pragma exceptions reset
