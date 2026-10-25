/* LookupCos (0x801868EC)
 *
 * 12-bit cos lookup into the shared LUT lbl_80491988. Built with GC/2.6,
 * which schedules the constant loads ahead of the `stwu`.
 */

extern const float lbl_806D9270;
extern const float lbl_806D9274;
extern const float lbl_806D9290;
extern float lbl_80491988[];

#pragma exceptions on
float LookupCos(float a) {
    return lbl_80491988[(int)(lbl_806D9270 * (lbl_806D9274 * a + lbl_806D9290)) & 0xFFF];
}
#pragma exceptions reset
