typedef struct SprCtx {
    float a, b;
    float c, d;
    float e, f;
    unsigned char pad[4];
    float r, g, b2, alpha;
} SprCtx;
extern int lbl_80678A0C[];
extern int lbl_806D16E8;
extern SprCtx lbl_8067897C;
extern const float lbl_806D97E0;
extern void fn_8011F610(int h, int r, int g, int b);
extern void SpriteHandle_SetCornerAlpha(int h, int a);

void fn_801A0FD4(float r, float g, float b, float a) {
    if (lbl_80678A0C[lbl_806D16E8] != -1) {
        lbl_8067897C.r = r;
        lbl_8067897C.g = g;
        lbl_8067897C.b2 = b;
        lbl_8067897C.alpha = a;
        fn_8011F610(lbl_80678A0C[lbl_806D16E8], (int)(lbl_806D97E0 * r), (int)(lbl_806D97E0 * g), (int)(lbl_806D97E0 * b));
        SpriteHandle_SetCornerAlpha(lbl_80678A0C[lbl_806D16E8], (int)(lbl_806D97E0 * a));
    }
}
