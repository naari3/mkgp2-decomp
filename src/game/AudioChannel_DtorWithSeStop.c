typedef struct AudioChannel {
    unsigned char pad_00[8];
    int channel;
    unsigned char pad_0C[0x24];
    int loopSe;
    int extraSe;
} AudioChannel;

extern void fn_8016C394(int);
extern void MemoryManager_TimedFree(void *);

#define CHANNEL_SE(self, id) ((((self)->channel & 0xF) << 27) | (id))

AudioChannel *AudioChannel_DtorWithSeStop(AudioChannel *self, short flags) {
    if (self != 0) {
        fn_8016C394(CHANNEL_SE(self, 0x50));
        fn_8016C394(CHANNEL_SE(self, 0x51));
        fn_8016C394(CHANNEL_SE(self, 0x52));
        if (self->extraSe >= 0) {
            fn_8016C394(self->extraSe | ((self->channel & 0xF) << 27));
        }
        if (self->loopSe != -1) {
            fn_8016C394(CHANNEL_SE(self, 0x8A));
            self->loopSe = -1;
        }
        if (flags > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
