#include "game/SpriteColorContext_private.h"

extern SpriteColorContext lbl_8067897C;
extern int lbl_80678A0C[];
extern int lbl_806D16E8;
extern void fn_8011F610(int, unsigned char, unsigned char, unsigned char);
extern void SpriteHandle_SetCornerAlpha(int, int);

void fn_801A0E54(int r, int g, int b, int a) {
    short red, green, blue, alpha;
    if (lbl_80678A0C[lbl_806D16E8] != -1) {
        lbl_8067897C.redOffset = r;
        lbl_8067897C.greenOffset = g;
        lbl_8067897C.blueOffset = b;
        lbl_8067897C.alphaOffset = a;
        red = (int)(255.0f * lbl_8067897C.red) + r;
        if (red > 255) red -= 255;
        if (red < 0) red = 0;
        green = (int)(255.0f * lbl_8067897C.green) + g;
        if (green > 255) green -= 255;
        if (green < 0) green = 0;
        blue = (int)(255.0f * lbl_8067897C.blue) + b;
        if (blue > 255) blue -= 255;
        if (blue < 0) blue = 0;
        alpha = (int)(255.0f * lbl_8067897C.alpha) + a;
        if (alpha > 255) alpha -= 255;
        if (alpha < 0) alpha = 0;
        fn_8011F610(lbl_80678A0C[lbl_806D16E8], (unsigned char)red, (unsigned char)green, (unsigned char)blue);
        SpriteHandle_SetCornerAlpha(lbl_80678A0C[lbl_806D16E8], (unsigned char)alpha);
    }
}
