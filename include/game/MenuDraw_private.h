#ifndef GAME_MENU_DRAW_PRIVATE_H
#define GAME_MENU_DRAW_PRIVATE_H
#include "game/SpritePairOwner.h"
struct MenuChildView {
    virtual ~MenuChildView();
    virtual int Update();
    virtual void Draw();
};
struct MenuOwnerView {
    void *vtable;
    unsigned char finished;
    unsigned char padding[3];
    MenuChildView *child;
};
extern "C" {
extern Sprite *lbl_806D17F8, *lbl_806D17FC, *lbl_806D1800, *lbl_806D180C;
extern Sprite *lbl_806D1820, *lbl_806D1840, *lbl_806D1844;
extern Sprite *lbl_80679280[3], *lbl_8067928C[4];
extern unsigned char lbl_806D184F, lbl_806D1850;
extern signed char lbl_806D1858, lbl_806D181C, lbl_806D181D, lbl_806D184D;
extern float lbl_806D1854, lbl_806D1848;
void fn_801A1174(int, int, int, int, int);
void fn_801A10DC(float, float);
void fn_801A1128(float, float);
void fn_801A0FD4(float, float, float, float);
void fn_801A0DF0();
void fn_8011FA98();
}
#endif
