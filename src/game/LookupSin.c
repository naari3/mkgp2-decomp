/* LookupSin (0x80186928)
 *
 * 12-bit sin lookup into the shared LUT lbl_80491988. Built with GC/2.6,
 * which schedules the constant loads ahead of the `stwu`.
 */

extern const float lbl_806D9270;
extern const float lbl_806D9274;

extern float lbl_80491988[];

#pragma exceptions on
float LookupSin(float a) {
    return lbl_80491988[(int)(lbl_806D9270 * (lbl_806D9274 * a)) & 0xFFF];
}
#pragma exceptions reset
