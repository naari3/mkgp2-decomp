#ifndef GAME_ITEMPANELDRAWPRIVATE_H
#define GAME_ITEMPANELDRAWPRIVATE_H
#include "game/FlowScene.h"
struct ItemPanelFlags { char pad[0x10]; unsigned long long bits; };
struct ItemPanelKart {
    char pad[0x304]; ItemPanelFlags *flags;
    char pad308[0x344-0x308]; void *stats;
};
struct PanelItem {
    virtual ~PanelItem();
    int field4,field8,state;
    char pad10[0x28-0x10];
    float x,y,scale;
    char pad34[0x50-0x34];
    PanelItem(ItemPanelKart *, int, int);
    void SetPos(float px,float py) { x=px; y=py; }
};
struct PanelMark {
    char pad[0xC]; float x,y,scale;
    void SetPos(float px,float py) { x=px; y=py; }
};
struct ItemPanel {
    void *vptr;
    ItemPanelKart *kart;
    int layer;
    unsigned char enabled; char pad0D[3];
    float x,y,scale;
    unsigned char variant; char pad1D[3];
    int icon,overlay,field28,extra,field30,field34;
    PanelItem *item;
    PanelMark *mark;
};
extern "C" {
extern float ItemPanelDraw_rodata_803EF5B0[12];
extern const float lbl_806DBE90,lbl_806D6DE4,lbl_806D6DE8,lbl_806DBEB0,lbl_806DBEB4,lbl_806DBEB8;
void fn_80121E10(ResCtrl *);
void fn_8011FAFC(ResCtrl *, int);
void fn_80244128(ItemPanel *,float,float,float);
void fn_80230ED8(PanelMark *,unsigned char);
void fn_80244524(PanelItem *,unsigned char);
int ItemUseStats_GetItemIdIfFlag15(void *);
int KartMovement_GetCurrentItemId(ItemPanelKart *);
}
inline void DrawPanelMark(ItemPanel *self,unsigned char enabled,float x,float y,float scale) {
    self->mark->SetPos(x,y);
    self->mark->scale=scale;
    fn_80230ED8(self->mark,enabled);
}
inline unsigned char PanelSuppressed(ItemPanelKart *k) {
    if ((k->flags->bits & 0x8000000000ULL)==0) return 0;
    return 1;
}
#endif
