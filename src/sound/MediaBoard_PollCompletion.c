extern float fn_80038778(float v, float lo, float hi);
extern const float lbl_806D2940;
extern const float lbl_806D2954;

#pragma exceptions on
void MediaBoard_PollCompletion(void *self, float value) {
    *(float *)((char *)self + 0x10) =
        fn_80038778(value, lbl_806D2940, lbl_806D2954);
}
#pragma exceptions reset
