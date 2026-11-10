#ifndef GAME_FIGURESLOTPRIVATE_H
#define GAME_FIGURESLOTPRIVATE_H
/* Observed Sprite and clFlowCup ABI; compatible with clFlowCup.c. */
void* operator new(unsigned long);
void operator delete(void*) throw();
struct FigureSprite {
    int field0, layer, field8;
    float x,y,sx,sy,rotation,alpha;
    char tail[12];
    void SetScale(float scale) { sx=scale; sy=scale; }
    void SetPos(float px,float py) { x=px; y=py; }
    FigureSprite(int,int,int);
    FigureSprite(int,int,float,float);
};
struct FigureSlot { int state,phase,ticks; FigureSprite* sprite; };
struct FigureSlotView {
    char pad00[0x20]; FigureSlot slots[9];
    char padb0[0x118-0xb0]; unsigned char second;
    char pad119[0x154-0x119]; unsigned char unlock0,unlock1;
};
struct FigurePosition { short label,sub; float x,y; };
extern "C" {
extern FigurePosition clFlowCup_data_8049AD58[];
extern const float lbl_806D9C7C,lbl_806D9C80,lbl_806D9C70,lbl_806D9C84,lbl_806D9C88;
extern const float lbl_806D9C74,lbl_806D9C8C,lbl_806D9C90,lbl_806D9C94;
unsigned char Sprite_AdvanceAnim(FigureSprite*,float);
void Sprite_SetupAnim(FigureSprite*,int,int,int);
void Sprite_SetAnimParam(FigureSprite*,int,short);
void fn_801A0550(FigureSprite*);
void fn_8019FF6C(FigureSprite*,int);
void Sprite_Destroy(FigureSprite*,int);
}
#endif
