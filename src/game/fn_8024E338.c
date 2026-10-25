extern const int lbl_806DA85C;
extern int lbl_806D1AB8;

void fn_8024E338(void) {
    lbl_806D1AB8 = lbl_806DA85C;
}

__declspec(section ".ctors") static void (*const fn_8024E338_ctor)(void) = fn_8024E338;
