#ifndef GAME_TYPES_CLEZMENU_H
#define GAME_TYPES_CLEZMENU_H
#include "game/types/pmf.h"
#include "game/FlowScene.h"
#include "game/TestMenuPage.h"

struct MenuRect801F { float x, y, w, h; };
struct MenuSprite801F {
    char opaque[0x94];
    ~MenuSprite801F();
};
#include "game/types/clSceneInterface.h"
struct clEzMenu : clSceneInterface {
    virtual ~clEzMenu();
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    /* Three additional null vtable slots in the target; original names unknown. */
    virtual void Slot18() = 0;
    virtual void Slot1C() = 0;
    virtual void Slot20() = 0;
    void *context;
    MenuSprite801F *sprites;
    VHolder<FlowFaderI> fade;
    int field14;
    int selection;
    int option;
    int level;
    int state;
    void fn_801F2400();
    void fn_801F2370();
    void fn_801F21C8();
    void fn_801F20A0();
    void fn_801F1EE0();
    void fn_801F1C58();
    void fn_801F1AC8();
    void fn_801F19C8();
    void fn_801F1664();
    void fn_801F140C();
    void fn_801F1244();
    void fn_801F0ECC();
    void fn_801F0D04();
    void fn_801F0CC0();
    void fn_801F230C();
    void fn_801F1FE4();
    void fn_801F1BC8();
    void fn_801F190C();
    void fn_801F15D4();
    void fn_801F115C();
    void fn_801F0E3C();
    void fn_801F0CBC();
};
PMF_TYPE(clEzMenuMethod, clEzMenu, void, ());
typedef clEzMenuMethod MenuMethod801F;
extern "C" {
extern const float lbl_806DA550, lbl_806DA554, lbl_806DA558;
extern const float lbl_806DA55C, lbl_806DA560, lbl_806DA564;
extern const float lbl_806DA568, lbl_806DA56C;
extern char lbl_804E4C28[];
extern char lbl_804E4D30[];
extern clEzMenuMethod lbl_804E5050[], lbl_804E51A0[];
void clCGameDemoWC_StubBlr_800adda0(clEzMenu *);
void clCGameDemoWC_StubBlr_800adda4();
void clCGameDemoWC_StubBlr_800adda8(int);
int fn_8020A788(FlowFaderI *);
void fn_8020A7CC(FlowFaderI *, int, int, int);
void fn_801F6E98(MenuSprite801F *, unsigned int);
void fn_801F7B74(void *, MenuSprite801F *, float);
void fn_801F6D58(MenuSprite801F *, void *, int, int);
void fn_801F6C2C(MenuSprite801F *, void *, int, int);
void fn_801F7040(MenuSprite801F *, void *, float);
void fn_801F6F7C(MenuSprite801F *, void *, float);
void fn_801F6ED0(MenuSprite801F *, float, float);
void fn_801F7CD8(void *, int);
void *StrPcb_GetInstance();
void StrPcb_RunAndWaitIdle(void *);
void StrPcb_ResetCommands_Neutral(void *, int);
void GX_EndDraw(int);
void GX_BeginDraw();
}
#endif
