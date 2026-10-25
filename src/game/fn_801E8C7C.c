extern const float lbl_806DA3C0;
extern const float lbl_806DA3D0;
extern float lbl_806D1910;
extern float lbl_806D1914;

void fn_801E8C7C(void) {
    lbl_806D1910 = lbl_806DA3C0;
    lbl_806D1914 = lbl_806DA3D0;
}

__declspec(section ".ctors") static void (*const s_fn_801E8C7C_ctor)(void) = fn_801E8C7C;
