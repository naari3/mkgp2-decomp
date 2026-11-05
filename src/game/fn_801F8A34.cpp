#include "game/TextDraw801F.h"

extern "C" void fn_801F8A34(void *, TextManager *manager, int layer) {
    TextDraw801F *text = (TextDraw801F *)manager;
    float sine, cosine;
    float specialAdvance, normalAdvance, lineAdvance;
    float cursorX, cursorY;
    float extraAdvance;
    float px, py;
    TextDraw801F *walker;
    int i;
    if (!isJapanese()) {
        specialAdvance = lbl_806DA738[0];
        normalAdvance = lbl_806DA740[0];
        lineAdvance = lbl_806DA740[1];
        if (text->font == 1) {
            float width = lbl_806DA748[0];
            normalAdvance = width;
            lineAdvance = lbl_806DA748[1];
            specialAdvance = lbl_806DA768 * width;
        }
    } else {
        specialAdvance = lbl_806DA750[0];
        normalAdvance = lbl_806DA758[0];
        lineAdvance = lbl_806DA758[1];
        if (text->font == 1) {
            float width = lbl_806DA760[0];
            normalAdvance = width;
            lineAdvance = lbl_806DA760[1];
            specialAdvance = lbl_806DA768 * width;
        }
    }
    cursorX = text->cursorX;
    cursorY = lbl_806DA76C;
    i = 0;
    sine = (float)sin(text->angle);
    cosine = (float)cos(text->angle);
    extraAdvance = lbl_806DA76C;
    walker = text;
    while (walker->glyphs[0] != 0xFFFF && i<256) {
        float y = cursorY * text->scaleY;
        float x = cursorX * text->scaleX;
        extraAdvance += text->advance;
        px = extraAdvance + (text->x + (cosine * x - sine * y));
        py = text->y + (sine * x + cosine * y);
        if (walker->glyphs[0] == 0x28E) {
            cursorX += specialAdvance;
        } else if (walker->glyphs[0] == 0) {
            cursorX += normalAdvance;
        } else if (walker->glyphs[0] == 0xC000) {
            cursorY += lineAdvance;
            cursorX = text->cursorX;
        } else if (walker->glyphs[0] < 0x2E3) {
            ResCtrl ctrl;
            int resource = lbl_804E5590[walker->glyphs[0]].normalResource;
            if (text->font == 1) resource = lbl_804E5590[walker->glyphs[0]].largeResource;
            ctrl.resId = resource;
            ctrl.SetColor(text->color);
            ctrl.SetScaleXY(text->scaleX, text->scaleY);
            ctrl.field28 = text->angle;
            ctrl.fieldc = text->mode;
            if (!(text->mode > -1 && text->mode < 2)) ctrl.fieldc = 0;
            if (text->mode == 1) {
                ctrl.Show(px, py, text->z);
            } else {
                ctrl.Show(px, py, lbl_806DA770);
            }
            fn_8011FAFC(&ctrl,layer);
            if (walker->glyphs[0] < 0x28E) {
                cursorX += normalAdvance;
            } else if (text->font == 1) {
                cursorX += normalAdvance;
            } else {
                cursorX += specialAdvance;
            }
        } else {
            cursorX += normalAdvance;
        }
        walker = (TextDraw801F *)((char *)walker + 2);
        ++i;
    }
}
