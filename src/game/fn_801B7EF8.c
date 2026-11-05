/* Countdown digit and transition animation update. */
typedef struct CountdownSprites {
    void *digits[3];
    void *transitions[4];
    unsigned short *glyphs[5];
} CountdownSprites;
extern CountdownSprites lbl_80679280;
extern const float lbl_806D9898;
extern const double lbl_806D98A0;
extern signed char lbl_806D181C, lbl_806D181D, lbl_806D181E;
extern float lbl_806D1838, lbl_806D183C;
extern double modf(double, double *);
extern void Sprite_SetAnimTime(void *, float);

#pragma exceptions on
int fn_801B7EF8(void) {
    CountdownSprites *sprites = &lbl_80679280;
    double integral;
    double phase;
    int digit;
    if (lbl_806D183C < 0.0f) return 0;
    if (lbl_806D1838 != lbl_806D183C) {
        digit = (int)lbl_806D183C;
        if ((float)digit >= 10.0f) {
            lbl_806D181C = 0;
            *sprites->glyphs[1] = 0x1842 + digit / 10;
            *sprites->glyphs[0] = 0x1842 + digit % 10;
        } else if ((float)digit >= lbl_806D9898) {
            lbl_806D181C = 1;
            *sprites->glyphs[2] = 0x1842 + digit % 10;
        } else {
            lbl_806D181C = 2;
            *sprites->glyphs[4] = 0x184C + digit % 10;
        }
        phase = modf(lbl_806D183C, &integral);
        if ((signed char)integral != lbl_806D181E) {
            if ((signed char)integral >= 6) {
                if (lbl_806D181E < -1) lbl_806D181D = 0;
                else lbl_806D181D = 1;
            } else {
                if (lbl_806D181E >= 6) lbl_806D181D = 2;
                else lbl_806D181D = 3;
            }
            lbl_806D181E = (signed char)integral;
        }
        phase = lbl_806D98A0 - phase;
        Sprite_SetAnimTime(sprites->digits[lbl_806D181C], (float)phase);
        Sprite_SetAnimTime(sprites->transitions[lbl_806D181D], (float)phase);
        lbl_806D1838 = lbl_806D183C;
    }
    return 1;
}
#pragma exceptions reset
