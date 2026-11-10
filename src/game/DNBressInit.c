/* Derive squared spawn radii, accelerations and breath spawn extents. */
extern float DNBressInit_data_806D0540, DNBressInit_data_806D0544, DNBressInit_data_806D0550, DNBressInit_data_806D0554;
extern float DNBressInit_data_806D0560, DNBressInit_data_806D0564, DNBressInit_data_806D0570, DNBressInit_data_806D0574;
extern float lbl_806D0548[2], DNBressInit_data_806D0558[2], DNBressInit_data_806D0568[2], DNBressInit_data_806D0578[2];
/* The endpoints are offsets 0x18..0x2c from the first point. */
extern const float lbl_803D02A0[12], DNBressInit_rodata_803D02B8[12];
extern float DNBress_nm3_data_804EDF80[18];
void fn_80227FA4(void) {
    lbl_806D0548[0] = DNBressInit_data_806D0540 * DNBressInit_data_806D0540;
    lbl_806D0548[1] = DNBressInit_data_806D0544 * DNBressInit_data_806D0544;
    DNBressInit_data_806D0558[0] = DNBressInit_data_806D0550 * DNBressInit_data_806D0550;
    DNBressInit_data_806D0558[1] = DNBressInit_data_806D0554 * DNBressInit_data_806D0554;
    DNBressInit_data_806D0568[0] = -(0.017453288659453392f * DNBressInit_data_806D0560);
    DNBressInit_data_806D0568[1] = -(0.017453288659453392f * DNBressInit_data_806D0564);
    DNBressInit_data_806D0578[0] = -(0.017453288659453392f * DNBressInit_data_806D0570);
    DNBressInit_data_806D0578[1] = -(0.017453288659453392f * DNBressInit_data_806D0574);
    DNBress_nm3_data_804EDF80[0] = DNBressInit_rodata_803D02B8[6] - lbl_803D02A0[6];
    DNBress_nm3_data_804EDF80[1] = DNBressInit_rodata_803D02B8[7] - lbl_803D02A0[7];
    DNBress_nm3_data_804EDF80[2] = DNBressInit_rodata_803D02B8[8] - lbl_803D02A0[8];
    DNBress_nm3_data_804EDF80[3] = DNBressInit_rodata_803D02B8[9] - lbl_803D02A0[9];
    DNBress_nm3_data_804EDF80[4] = DNBressInit_rodata_803D02B8[10] - lbl_803D02A0[10];
    DNBress_nm3_data_804EDF80[5] = DNBressInit_rodata_803D02B8[11] - lbl_803D02A0[11];
}
__declspec(section ".ctors") static void (*const init)(void) = fn_80227FA4;
