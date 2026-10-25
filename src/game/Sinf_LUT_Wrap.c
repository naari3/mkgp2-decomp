/* Sinf_LUT_Wrap (0x8006584C, size 0x68): sine of an angle in degrees via
 * the 16-bit LUT at lbl_802EE580. Same as LUT_Sine with the degree scale
 * lbl_806D2C50 (65536 / 360). */

extern const float lbl_806D2C50;
extern const float lbl_806D2C54;
extern const float lbl_806D2C58;
extern const float lbl_806D2C5C;
extern unsigned short lbl_806CEF18;
extern const float lbl_802EE580[];

#pragma exceptions on
float Sinf_LUT_Wrap(float angle) {
    float scale = lbl_806D2C50;
    float bias = (angle > lbl_806D2C5C) ? lbl_806D2C54 : lbl_806D2C58;
    unsigned int idx = (int)(scale * angle + bias);
    idx &= lbl_806CEF18;
    if ((unsigned short)idx > 0x7FFF) {
        idx = (0x10000 - idx) & 0xFFFF;
    }
    return lbl_802EE580[(unsigned short)idx];
}
#pragma exceptions reset
