/* Cosine of an angle in degrees via the 16-bit sine LUT (quarter-turn
 * phase shift). */
extern const float lbl_806D2C54;
extern const float lbl_806D2C58;
extern const float lbl_806D2C5C;
extern const float lbl_806D2C50;
extern unsigned short g_sineLutIndexMask;
extern const float LUT_Sine_rodata_802EE580[];

#pragma exceptions on
float Cosf_LUT_Wrap(float angle)
{
    float scale = lbl_806D2C50;
    float bias = (angle > lbl_806D2C5C) ? lbl_806D2C54 : lbl_806D2C58;
    unsigned int idx = (int)(scale * angle + bias);
    unsigned int mask = g_sineLutIndexMask;
    idx &= mask;
    idx = (unsigned short)(idx - 0x4000);
    idx &= mask;
    if ((unsigned short)idx > 0x7FFF) {
        idx = (0x10000 - idx) & 0xFFFF;
    }
    return LUT_Sine_rodata_802EE580[(unsigned short)idx];
}

#pragma exceptions reset
