#ifndef GAME_TYPES_CLRESULT_H
#define GAME_TYPES_CLRESULT_H
#include "game/types/clJobRunner.h"
#include "game/MenuModeLane_private.h"
#include "game/HudFlowPrivate.h"
struct HudModeDisplay { char opaque[0x1c]; HudModeDisplay(int); };
struct HudModeOther { char opaque[0x18]; HudModeOther(); };
struct HudModeLast { char opaque[0x18]; HudModeLast(); };
extern "C" {
extern unsigned char lbl_806D17F1, lbl_806D17F2;
void fn_801F98CC(); void fn_8020F220();
void fn_801D5DB4(void *,int); void SetKartVariantOnPlayer(void *,int);
}
struct clResult : clJobRunner {
    virtual int Update();
    virtual void Draw();
    virtual ~clResult();
    int mode;
    SceneBase *scene;
    HudModeDisplay *display;
    clResult() {
        mode=0; scene=0;
        display=new HudModeDisplay(0);
        fn_801F98CC(); fn_8020F220();
        fn_801D5DB4(g_playerData,g_characterId);
        SetKartVariantOnPlayer(g_playerData,g_kartVariant);
        fn_8024F43C(fn_8024F588());
        lbl_806D17F0=0; lbl_806D17F2=0; lbl_806D17F1=0;
        if(g_gameMode==0) mode=0; else if(g_gameMode==1) mode=1; else mode=2;
        int selected=mode;
        if(!scene) switch(selected) {
        case 0: scene=(SceneBase *)new HudFlow; break;
        case 1: scene=(SceneBase *)new HudModeOther; break;
        case 2: scene=(SceneBase *)new HudModeLast; break;
        }
    }
};
#endif
