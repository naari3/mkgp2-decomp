#ifndef GAME_HUDSELECTIONPRIVATE_H
#define GAME_HUDSELECTIONPRIVATE_H
#include "game/FlowScene.h"
extern "C" {
extern char HudFlow24_vtable_804EE83C[], lbl_804EDB28[];
extern int g_countdownPhase;
extern const float lbl_806DBF18, lbl_806DBF1C, lbl_806DBF20, lbl_806DBF24;
#include "game/types/HudSelectionPosition.h"
extern HudSelectionPosition HudSelectionUpdate_rodata_803EF75C[];
void fn_801F8E54();
void MemoryManager_TimedFree(void *);
void fn_801F93D0(TextManager *,float,float);
void fn_801F8A34(void *,TextManager *,int);
}
struct HudSelectionBase {
 void *vptr; int countdown, field08, state;
 ~HudSelectionBase() { vptr=lbl_804EDB28; }
};
struct HudSelection : HudSelectionBase {
 int selection;
 VHolder<FlowFaderF> position;
 VHolder<FlowFaderF> alpha;
 TextManager *text;
 void *context;
 HudSelection(int);
};
#endif
