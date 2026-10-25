extern const int lbl_806DA848;
extern int lbl_806D1A98;

void fn_80242DE0(void) {
    lbl_806D1A98 = lbl_806DA848;
}

__declspec(section ".ctors") static void (*const fn_80242DE0_ctor)(void) = fn_80242DE0;
