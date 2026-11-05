#ifndef GAME_FLOWKARTDRAW_PRIVATE_H
#define GAME_FLOWKARTDRAW_PRIVATE_H
#include "game/FlowScene.h"
inline TextManager::~TextManager() {}
struct FKDrawPart { const char *text; char pad04[0x44]; float x,y; };
struct FKDrawView { int index; void *sprite; int layer; float x,y; FKDrawPart primary; FKDrawPart secondary[3]; char pad154[8]; float alpha; };
struct FKDrawEntry { char pad00[10]; short primary; short secondary[3]; short pad12; };
extern "C" {
extern FKDrawEntry lbl_8039E9F8[];
extern const float lbl_806DA190,lbl_806DA194;
void fn_801A0004(void *);
void *fn_801F8E58();
void fn_801F8A34(void *,TextManager *,int);
}
#endif
