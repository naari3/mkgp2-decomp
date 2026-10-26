/* Cosine of an angle in radians via the 16-bit sine LUT (quarter-turn
 * phase shift). */
extern const float lbl_806D2C54;
extern const float lbl_806D2C58;
extern const float lbl_806D2C5C;
extern const float lbl_806D2C60;
extern unsigned short lbl_806CEF18;
extern const float lbl_802EE580[];

float LUT_Cosine(float angle)
{
    float scale = lbl_806D2C60;
    float bias = (angle > lbl_806D2C5C) ? lbl_806D2C54 : lbl_806D2C58;
    unsigned int idx = (int)(scale * angle + bias);
    unsigned int mask = lbl_806CEF18;
    idx &= mask;
    idx = (unsigned short)(idx - 0x4000);
    idx &= mask;
    if ((unsigned short)idx > 0x7FFF) {
        idx = (0x10000 - idx) & 0xFFFF;
    }
    return lbl_802EE580[(unsigned short)idx];
}
