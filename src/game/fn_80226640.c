extern const int lbl_806DA85C;
extern int lbl_806D1A78;

void fn_80226640(void) {
    lbl_806D1A78 = lbl_806DA85C;
}

__declspec(section ".ctors") static void (*const fn_80226640_ctor)(void) = fn_80226640;
