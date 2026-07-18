typedef unsigned char u8;

extern void SoundObj_PlaySE(void *sound, int se_id);

void CoinEvent_PlaySE_0x13(u8 *self) {
    SoundObj_PlaySE(*(void **)(self + 0x24), 0x13);
}
