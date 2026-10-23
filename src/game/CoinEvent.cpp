typedef unsigned char u8;
struct CoinEventContext { u8 pad[0x1f8]; int mode; };
struct CoinEventView {
    u8 pad0[0x24]; void* sound; u8 pad28[4]; CoinEventContext* context;
    u8 pad30[0xcd]; u8 pending; u8 padfe[0xb]; u8 resultPlayed;
};
extern "C" {
extern void SoundObj_PlaySE(void*, int);
extern int WrapInRange(int, int, int);
extern signed char lbl_806D1094;
extern int lbl_806D1090;
extern int lbl_806CEDF8[2];
void CoinEvent_PlayResultSE(CoinEventView* self, int result) {
    int se;
    if (self->context->mode == 12) {
        if (result == 0) se = 0x13; else se = 4;
    } else {
        if (result == 0) se = 0x13; else se = 0xf;
    }
    SoundObj_PlaySE(self->sound, se);
    self->resultPlayed = 1;
    self->pending = 0;
}
void CoinEvent_PlayAlternatingSE(CoinEventView* self) {
    if (lbl_806D1094 == 0) {
        lbl_806D1090 = 0;
        lbl_806D1094 = 1;
    }
    lbl_806D1090 = WrapInRange(lbl_806D1090 + 1, 0, 1);
    SoundObj_PlaySE(self->sound, lbl_806CEDF8[lbl_806D1090]);
}
}
