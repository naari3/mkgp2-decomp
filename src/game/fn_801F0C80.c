typedef float f32;

extern f32 lbl_806D1930;
extern f32 lbl_806D1934;
extern f32 lbl_806D1938;
extern f32 lbl_806D193C;
extern f32 lbl_806D1940;
extern f32 lbl_806D1944;
extern f32 lbl_806D1948;
extern f32 lbl_806DA530;
extern f32 lbl_806DA534;
extern f32 lbl_806DA538;
extern f32 lbl_806DA53C;
extern f32 lbl_806DA540;
extern f32 lbl_806DA544;
extern f32 lbl_806DA548;

void fn_801F0C80(void) {
    lbl_806D1930 = lbl_806DA530;
    lbl_806D1934 = lbl_806DA534;
    lbl_806D1938 = lbl_806DA538;
    lbl_806D193C = lbl_806DA53C;
    lbl_806D1940 = lbl_806DA540;
    lbl_806D1944 = lbl_806DA544;
    lbl_806D1948 = lbl_806DA548;
}

__declspec(section ".ctors") static void (*const s_fn_801F0C80_ctor)(void) = fn_801F0C80;
