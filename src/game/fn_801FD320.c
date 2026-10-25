extern const int lbl_806DA848;
extern int lbl_806D19C8;

void fn_801FD320(void) {
    lbl_806D19C8 = lbl_806DA848;
}

__declspec(section ".ctors") static void (*const fn_801FD320_ctor)(void) = fn_801FD320;
