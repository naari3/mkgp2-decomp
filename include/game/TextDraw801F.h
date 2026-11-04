#ifndef TEXT_DRAW_801F_H
#define TEXT_DRAW_801F_H
#include "game/FlowScene.h"
/* Full view of the otherwise opaque TextManager fields used by the renderer. */
struct TextDraw801F {
    float x,y,cursorX,scaleX,scaleY,angle;
    int font;
    int field1C;
    unsigned int color;
    unsigned short glyphs[256];
    float z;
    int mode;
    float advance;
};
struct GlyphDraw801F {
    unsigned short card,code;
    int normalResource,largeResource,advance;
};
extern "C" {
extern GlyphDraw801F lbl_804E5590[];
extern const float lbl_806DA738[2], lbl_806DA740[2], lbl_806DA748[2];
extern const float lbl_806DA750[2], lbl_806DA758[2], lbl_806DA760[2];
extern const float lbl_806DA768, lbl_806DA76C, lbl_806DA770;
void fn_8011FAFC(ResCtrl *, int);
double sin(double);
double cos(double);
}
#endif
