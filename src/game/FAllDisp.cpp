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

const unsigned int lbl_803DB630[40] = {0x636C466C, 0x6F617443, 0x6F756E74, 0x65720000, 0x636C436F, 0x756E7465, 0x72496E74, 0x65726661, 0x63650000, 0x636C496E, 0x74436F75, 0x6E746572, 0x00000000, 0x636C4354, 0x61736B49, 0x6E746572, 0x66616365, 0x00000000, 0x636C5954, 0x61736B49, 0x6E746572, 0x66616365, 0x00000000, 0x636C4661, 0x63654E52, 0x69676874, 0x45796500, 0x636C4661, 0x63654E61, 0x6D696461, 0x49546173, 0x6B000000, 0x636C4661, 0x63654E4C, 0x65667445, 0x79650000, 0x636C4661, 0x63654E54, 0x65617273, 0x00000000};

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
        r.Show(px, (y + -19.2f) + slide.p->Value(), 1.0f);
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
