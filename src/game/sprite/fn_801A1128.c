typedef struct SprCtx {
    float a, b;
    float c, d;
    float e, f;
} SprCtx;
extern int lbl_80678A0C[];
extern int lbl_806D16E8;
extern SprCtx lbl_8067897C;
extern void fn_8011F804(int h, SprCtx *ctx);

void fn_801A1128(float x, float y) {
    if (lbl_80678A0C[lbl_806D16E8] != -1) {
        lbl_8067897C.c = x;
        lbl_8067897C.d = y;
        fn_8011F804(lbl_80678A0C[lbl_806D16E8], &lbl_8067897C);
    }
}
