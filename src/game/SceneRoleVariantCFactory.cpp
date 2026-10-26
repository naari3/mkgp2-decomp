#include "game/SceneRoleVariantCPrivate.h"
extern "C" {
void PreloadResource(int);
void card_force_backup_now();
void fn_8020F3F0();
extern unsigned char g_playerData[0x1DC];
void fn_801D6DF0(void *);
extern unsigned char lbl_806D17F2, lbl_806D17F0;
}
inline SceneRoleVariantCBase::SceneRoleVariantCBase()
    : child(0), route(5), list(new SceneListImpl), fader(new FlowFaderI)
{
    PreloadResource(0x1ECD);
    PreloadResource(0x72F);
    PreloadResource(0x734);
    PreloadResource(0x730);
    if ((lbl_806DBFC8 == lbl_806D1A60->value) == 1)
        fader.p->Set(255, 0, 15);
    card_force_backup_now();
    fn_8020F3F0();
}
inline SceneRoleVariantC::SceneRoleVariantC()
{
    fn_801D6DF0(g_playerData);
    if (lbl_806D17F2 && lbl_806D17F0)
        route = 4;
    else
        route = 5;
    Start(route);
}
extern "C" SceneRoleVariantC *fn_8024CA18()
{
    return new SceneRoleVariantC;
}
