extern const int lbl_806DA85C;
extern int lbl_806D1AC0;

void fn_8024F400(void) {
    lbl_806D1AC0 = lbl_806DA85C;
}

__declspec(section ".ctors") static void (*const fn_8024F400_ctor)(void) = fn_8024F400;
