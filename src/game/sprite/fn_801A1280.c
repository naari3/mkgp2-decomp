extern int lbl_80678A0C[200];
extern int lbl_806D16E8;
extern void SpriteHandle_Destroy(int h);

void fn_801A1280(void) {
    int i;
    for (i = 0; i < 200; i++) {
        if (lbl_80678A0C[i] != -1) {
            SpriteHandle_Destroy(lbl_80678A0C[i]);
        }
        lbl_80678A0C[i] = -1;
    }
    lbl_806D16E8 = 0;
}
