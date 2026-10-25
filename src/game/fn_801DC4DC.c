extern int fn_801DE7D4(void);
extern int fn_801DE7CC(void);
extern int lbl_806D1898;
extern int lbl_806D189C;

void fn_801DC4DC(void) {
    lbl_806D1898 = fn_801DE7D4() * 60;
    lbl_806D189C = fn_801DE7CC() * 60;
}

__declspec(section ".ctors") static void (*const s_fn_801DC4DC_ctor)(void) = fn_801DC4DC;
