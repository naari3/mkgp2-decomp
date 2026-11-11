/* clRaceCountNum, 0x80215508..0x802159E8.
 * Definitions are in reverse target order for deferred code generation.
 * Vtable, base lists, RTTI records and type names are compiler-emitted. */
#include "game/FlowScene.h"
#include "game/types/clRaceCountNum.h"

extern "C" {
extern const int lbl_803C3E50[6] = {2846, 2846, 2847, 2848, 2849, 2850};
extern const float lbl_806DAE60;
extern const float lbl_806DAE64;
extern const float lbl_806DAE68;
extern const float lbl_806DAE6C;
extern const float lbl_806DAE70;
extern const float lbl_806DAE74;
extern const float lbl_806DAE78;
extern const float lbl_806DAE7C;
extern const float lbl_806DAE80;
extern const float lbl_806DAE88;
extern const float lbl_806DAE8C;
extern const float lbl_806DAE90;
extern const float lbl_806DAE94;
extern int g_countdownPhase;
extern int g_gameMode;
void PreloadResource(int res);
void fn_80120A08(int res);
void fn_8011FAFC(ResCtrl *ctrl, int layer);
int SpriteHandle_CreateDefault(ResCtrl *ctrl, int layer);
void SpriteHandle_Destroy(int sprite);
void SpriteHandle_SetActiveFlag(int sprite, int active);
void SpriteHandle_RecomputeCull(int sprite);
void SpriteLayer_SetResource(int sprite, int res);
void fn_8011F804(int sprite, float x, float y);
void fn_8011F744(int sprite, float sx, float sy);
int fn_8020A900(int value, int digit);
void Tachometer_SetDisplaySpeedRef(float v);
void Tachometer_SetMaxSpeedRef(float v);
}

struct clRaceCountNum : clCTaskInterface {
    int layer;
    int kind;
    VHolder<FlowFaderI> alpha;
    VHolder<FlowFaderF> scale;
    clRaceCountNum(int kind_, int layer_, int id_)
        : clCTaskInterface(id_), layer(layer_), kind(kind_), alpha(new FlowFaderI),
          scale(new FlowFaderF(lbl_806DAE7C)) {
        if (kind_ < 1 || kind_ > 5) {
            kind = 1;
        }
        alpha.p->Set(0, 0xFF, 15);
        scale.p->Set(lbl_806DAE80, lbl_806DAE6C, 15);
    }
    ~clRaceCountNum();
    void Finish();
    void Update();
    void Draw();
};

clRaceCountNum::~clRaceCountNum() {
}

extern "C" clRaceCountNum *fn_80215784(int kind, int layer, int id) {
    return new clRaceCountNum(kind, layer, id);
}

void clRaceCountNum::Finish() {
    delete this;
}

extern "C" void fn_80215708(void) {
    PreloadResource(0xB1E);
    PreloadResource(0xB1F);
    PreloadResource(0xB20);
    PreloadResource(0xB21);
    PreloadResource(0xB22);
}

extern "C" void fn_802156C4(void) {
    fn_80120A08(0xB1E);
    fn_80120A08(0xB1F);
    fn_80120A08(0xB20);
    fn_80120A08(0xB21);
    fn_80120A08(0xB22);
}

void clRaceCountNum::Update() {
    ResCtrl rc;
    unsigned int c = alpha.p->Value() | 0xFFFFFF00;
    float s = scale.p->Value();
    rc.resId = lbl_803C3E50[kind];
    rc.Show(lbl_806DAE60, lbl_806DAE64, lbl_806DAE68);
    rc.SetColor(c);
    rc.SetScale(s);
    fn_8011FAFC(&rc, layer);
    alpha.p->Step();
    scale.p->Step();
    if (scale.p->Done()) {
        float v = scale.p->Value();
        if (lbl_806DAE6C == v) {
            scale.p->Set(lbl_806DAE6C, lbl_806DAE68, 5);
        } else if (lbl_806DAE68 == v) {
            scale.p->Set(lbl_806DAE68, lbl_806DAE70, 20);
        } else if (lbl_806DAE70 == v) {
            scale.p->Set(lbl_806DAE70, lbl_806DAE74, 5);
        } else if (lbl_806DAE74 == v) {
            alpha.p->Set(0xFF, 0, 15);
            scale.p->Set(lbl_806DAE74, lbl_806DAE78, 15);
        } else {
            field0C = 1;
        }
    }
}

void clRaceCountNum::Draw() {}
