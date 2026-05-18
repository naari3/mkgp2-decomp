extern float Saturate_Double(float v, float lo, float hi);
extern const float lbl_806D2940;
extern const float lbl_806D2954;

#pragma exceptions on
void SoundCtrl_SetVolume(void *self, float volume) {
    *(float *)((char *)self + 0x1C) =
        Saturate_Double(volume, lbl_806D2940, lbl_806D2954);
}
#pragma exceptions reset
