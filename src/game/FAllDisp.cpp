#include "game/types/text_word.h"
/*
 * 0x80231D50..0x802321D4: clFAllDisp, the pulsing "ALL" banner (resource
 * 0xC6F) that slides in above the face icons.
 * Owns .rodata 0x803DB630..0x803DB6E0: the leading block holds the RTTI names
 * of weak classes whose copies the linker dropped.
 */

#include "game/FlowScene.h"

extern "C" {
extern unsigned char g_finalLapCoinJumpEnabled;
void PreloadResource(int id);
void fn_80120A08(int id);
void fn_8011FAFC(ResCtrl *r, int prio);
}

#pragma force_active on
extern const unsigned int lbl_803DB630[40] = {TEXT_WORD('c', 'l', 'F', 'l'), TEXT_WORD('o', 'a', 't', 'C'), TEXT_WORD('o', 'u', 'n', 't'), TEXT_WORD('e', 'r', 0, 0), TEXT_WORD('c', 'l', 'C', 'o'), TEXT_WORD('u', 'n', 't', 'e'), TEXT_WORD('r', 'I', 'n', 't'), TEXT_WORD('e', 'r', 'f', 'a'), TEXT_WORD('c', 'e', 0, 0), TEXT_WORD('c', 'l', 'I', 'n'), TEXT_WORD('t', 'C', 'o', 'u'), TEXT_WORD('n', 't', 'e', 'r'), 0x00000000, TEXT_WORD('c', 'l', 'C', 'T'), TEXT_WORD('a', 's', 'k', 'I'), TEXT_WORD('n', 't', 'e', 'r'), TEXT_WORD('f', 'a', 'c', 'e'), 0x00000000, TEXT_WORD('c', 'l', 'Y', 'T'), TEXT_WORD('a', 's', 'k', 'I'), TEXT_WORD('n', 't', 'e', 'r'), TEXT_WORD('f', 'a', 'c', 'e'), 0x00000000, TEXT_WORD('c', 'l', 'F', 'a'), TEXT_WORD('c', 'e', 'N', 'R'), TEXT_WORD('i', 'g', 'h', 't'), TEXT_WORD('E', 'y', 'e', 0), TEXT_WORD('c', 'l', 'F', 'a'), TEXT_WORD('c', 'e', 'N', 'a'), TEXT_WORD('m', 'i', 'd', 'a'), TEXT_WORD('I', 'T', 'a', 's'), TEXT_WORD('k', 0, 0, 0), TEXT_WORD('c', 'l', 'F', 'a'), TEXT_WORD('c', 'e', 'N', 'L'), TEXT_WORD('e', 'f', 't', 'E'), TEXT_WORD('y', 'e', 0, 0), TEXT_WORD('c', 'l', 'F', 'a'), TEXT_WORD('c', 'e', 'N', 'T'), TEXT_WORD('e', 'a', 'r', 's'), 0x00000000};
#pragma force_active reset

class clFAllDisp {
public:
    virtual ~clFAllDisp();
    virtual void _pure() = 0;
    unsigned char visible;
    float x, y;
    VHolder<FlowFaderI> fade;
    VHolder<FlowFaderF> slide;
    VHolder<FlowFaderF> scale;

    clFAllDisp();
    void Draw();
};

void clFAllDisp::Draw() {
    if (g_finalLapCoinJumpEnabled == 1) {
        return;
    }
    if (visible) {
        ResCtrl r;
        float s = scale.p->Value();
        r.resId = 0xC6F;
        float px = x;
        float dy = -19.2f;
        r.Show(px, (y + dy) + slide.p->Value(), 1.0f);
        r.SetScale(s);
        fn_8011FAFC(&r, 3);
        r.mode = 3;
        r.SetColor(fade.p->Value() | 0xFFFFFF00);
        fn_8011FAFC(&r, 3);
    }
    fade.p->Step();
    slide.p->Step();
    scale.p->Step();
    if (slide.p->Done()) {
        if (32.0f == slide.p->Value()) {
            fade.p->Set(0xFF, 0, 15);
            slide.p->Set(32.0f, 0.0f, 15);
            scale.p->Set(1.08f, 0.6f, 15);
            return;
        }
        fade.p->Set(0, 0xFF, 15);
        slide.p->Set(0.0f, 32.0f, 15);
        scale.p->Set(0.6f, 1.08f, 15);
    }
}

clFAllDisp::~clFAllDisp() {
    fn_80120A08(0xC6F);
}

clFAllDisp::clFAllDisp() : visible(0), x(0.0f), y(0.0f), fade(new FlowFaderI), slide(new FlowFaderF(0.0f)), scale(new FlowFaderF(0.0f)) {
    PreloadResource(0xC6F);
    fade.p->Set(0, 0xFF, 15);
    slide.p->Set(0.0f, 32.0f, 15);
    scale.p->Set(0.6f, 1.08f, 15);
}
