#ifndef GAME_FLOWKARTPOSITION_PRIVATE_H
#define GAME_FLOWKARTPOSITION_PRIVATE_H
struct TextManager;
#include "game/types/FKPosition.h"
static inline FKPosition operator+(const FKPosition &a, const FKPosition &b) {
    FKPosition r; r.x = a.x + b.x; r.y = a.y + b.y; return r;
}
struct FKPositioned { char pad[0xC]; float x, y;
    void SetPosition(float a,float b) { x=a; y=b; }
    void SetPosition(FKPosition p) { x=p.x; y=p.y; }
};
struct FKPositionIcon { char pad[0x10]; unsigned char active; char pad11[3]; float x,y,z;
    void SetPosition(FKPosition p) { active=1; x=p.x; y=p.y; z=1.0f; }
};
struct FKPositionPanel {
    char pad00[0x18]; int mode; int state;
    char pad20[0x28]; FKPositioned *labelB, *labelA;
    FKPositionIcon *icons[3]; TextManager *texts[3];
};
extern "C" {
extern const FKPosition lbl_8039FC60[];
void fn_801F93EC(TextManager *, float, float);
}
static inline void FKPlaceText(TextManager *t, FKPosition p) { fn_801F93EC(t,p.x,p.y); }
static inline FKPosition FKOffset(float x,float y,const FKPosition &b) { FKPosition r; r.x=x+b.x; r.y=y+b.y; return r; }
#endif
