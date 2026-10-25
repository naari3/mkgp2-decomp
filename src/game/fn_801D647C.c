extern void fn_801D5F74(void *self, int id, int on);
extern void SoundMgr_Play(int id);
extern void SetCardVolumeFlagByte(unsigned char flag);

typedef struct CardFlags {
    char pad[0x19B];
    unsigned char unk19B;
    char pad19C[3];
    unsigned char volumeFlag;
} CardFlags;

void fn_801D647C(CardFlags *self, unsigned char a, unsigned char b, unsigned char c, int d) {
    if (a == 1) {
        fn_801D5F74(self, 0x3A, 1);
    }
    if (b == 1) {
        fn_801D5F74(self, 0x3F, 1);
    }
    if (c == 1) {
        fn_801D5F74(self, 0x33, 1);
    }
    if (a == 1 || b == 1 || c == 1) {
        SoundMgr_Play(1);
        if (self->unk19B == 0) {
            self->unk19B = 0x72;
        }
    }
    self->volumeFlag = 1;
    SetCardVolumeFlagByte(self->volumeFlag);
    if (d == 0) {
        return;
    }
}
