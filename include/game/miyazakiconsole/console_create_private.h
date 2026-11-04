#ifndef MIYAZAKI17E_CONSOLE_CREATE_PRIVATE_H
#define MIYAZAKI17E_CONSOLE_CREATE_PRIVATE_H
#include "game/DemoKartScene.h"
#include "game/FlowScene.h"
#include "game/miyazakiconsole/miyazakiconsole.h"
struct ConsoleDisplay {
    unsigned char active;
    void Enable() { active=1; }
};
extern "C" {
extern const char lbl_80376220[];
extern const char lbl_806D923C[4];
extern void *lbl_803FDF28[], *lbl_803FDF40[];
extern int lbl_806D15F8, lbl_806D1600, lbl_806D166C, lbl_806D1670;
extern void *lbl_806D15FC;
void fn_80180170();
Menu *fn_801816AC(const char *);
void fn_801805AC(Menu *, void *);
void fn_801804CC(Menu *, const char *);
void fn_8017F538();
ConsoleDisplay *fn_801DAEC0();
}
struct ConsoleInputData {
    void *vt;
    unsigned char enabled, flag5, flag6;
    int fields[8];
    ConsoleInputData() {
        vt=lbl_803FDF28;
        g_pInputState=(InputState *)this;
        vt=lbl_803FDF40;
        enabled=0;
        flag5=1;
        flag6=1;
        for (int i=0;i<8;i++) fields[i]=0;
    }
};
struct MiyazakiMode : DemoRoot {
    int unused;
    virtual void Key();
    MiyazakiMode(const char *s) {
        lbl_806D15F8=0;
        lbl_806D15FC=0;
        lbl_806D1600=0;
        fn_80180170();
        lbl_806D166C=0;
        lbl_806D1670=5;
        Menu *menu=fn_801816AC(s+0xb68);
        fn_801805AC(menu,(void *)fn_8017F538);
        fn_801804CC(menu,s+0xb74);
        fn_801804CC(menu,s+0xb84);
        fn_801804CC(menu,s+0xb94);
        fn_801804CC(menu,s+0x7d0);
        fn_801804CC(menu,s+0xba8);
        fn_801804CC(menu,lbl_806D923C);
        if (GetInput()==0) new ConsoleInputData;
        if (GetInput()!=0) {
            InputState *in=GetInput();
            in->enabled=1;
            in->held=0;
            in->edge=0;
        }
        fn_801DAEC0()->Enable();
    }
};

#endif
