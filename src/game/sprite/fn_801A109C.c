extern int lbl_80678A0C[];
extern int lbl_806D16E8;
extern void fn_8011F6C8(int h, void *arg);

void fn_801A109C(void *arg) {
    if (lbl_80678A0C[lbl_806D16E8] != -1) {
        fn_8011F6C8(lbl_80678A0C[lbl_806D16E8], arg);
    }
}
