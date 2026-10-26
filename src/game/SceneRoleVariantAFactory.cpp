#include "game/SceneRoleVariantA.h"

struct VariantASettings {
    unsigned char pad[12];
    float value;
};
extern "C" {
extern VariantASettings *lbl_806D1A60;
extern const float lbl_806DBFC8;
extern unsigned char lbl_806D17F2;
void PreloadResource(int);
void card_force_backup_now();
void fn_8020F3F0();
}

inline VariantABase::VariantABase()
    : child(0), route(5), list(new SceneListImpl), fader(new FlowFaderI)
{
    PreloadResource(0x1ecd);
    PreloadResource(0x72f);
    PreloadResource(0x734);
    PreloadResource(0x730);
    if ((unsigned int)(lbl_806DBFC8 == lbl_806D1A60->value) == 1)
        fader.p->Set(255, 0, 15);
    card_force_backup_now();
    fn_8020F3F0();
}
inline VariantAOwner::VariantAOwner() {
    if (lbl_806D17F2) route = 4;
    else route = 5;
    Start(route);
}
extern "C" VariantAOwner *fn_8024C0F4() { return new VariantAOwner; }
