/* Derive squared spawn radii, accelerations and breath spawn extents. */
extern float lbl_806D0540, lbl_806D0544, lbl_806D0550, lbl_806D0554;
extern float lbl_806D0560, lbl_806D0564, lbl_806D0570, lbl_806D0574;
extern float lbl_806D0548[2], lbl_806D0558[2], lbl_806D0568[2], lbl_806D0578[2];
/* The endpoints are offsets 0x18..0x2c from the first point. */
extern const float lbl_803D02A0[12], lbl_803D02B8[12];
extern float lbl_804EDF80[18];
void fn_80227FA4(void) {
    lbl_806D0548[0] = lbl_806D0540 * lbl_806D0540;
    lbl_806D0548[1] = lbl_806D0544 * lbl_806D0544;
    lbl_806D0558[0] = lbl_806D0550 * lbl_806D0550;
    lbl_806D0558[1] = lbl_806D0554 * lbl_806D0554;
    lbl_806D0568[0] = -(0.017453288659453392f * lbl_806D0560);
    lbl_806D0568[1] = -(0.017453288659453392f * lbl_806D0564);
    lbl_806D0578[0] = -(0.017453288659453392f * lbl_806D0570);
    lbl_806D0578[1] = -(0.017453288659453392f * lbl_806D0574);
    lbl_804EDF80[0] = lbl_803D02B8[6] - lbl_803D02A0[6];
    lbl_804EDF80[1] = lbl_803D02B8[7] - lbl_803D02A0[7];
    lbl_804EDF80[2] = lbl_803D02B8[8] - lbl_803D02A0[8];
    lbl_804EDF80[3] = lbl_803D02B8[9] - lbl_803D02A0[9];
    lbl_804EDF80[4] = lbl_803D02B8[10] - lbl_803D02A0[10];
    lbl_804EDF80[5] = lbl_803D02B8[11] - lbl_803D02A0[11];
}
__declspec(section ".ctors") static void (*const init)(void) = fn_80227FA4;
