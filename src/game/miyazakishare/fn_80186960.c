extern float lbl_80491988[];
extern const float lbl_806D9290;
extern const float lbl_806D9270;

float fn_80186960(float x) {
    return lbl_80491988[(int)(lbl_806D9270 * (lbl_806D9290 + x)) & 0xfff];
}
