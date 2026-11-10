#include "game/ItemPanelDrawPrivate.h"
static inline void DrawPanelItem(ItemPanel *self,float x,float y,float scale) {
    unsigned char visible=self->enabled;
    int item=ItemUseStats_GetItemIdIfFlag15(self->kart->stats);
    if (item>-1) {
        if (self->item) delete self->item;
        self->item=new PanelItem(self->kart,item,self->layer);
    } else if (KartMovement_GetCurrentItemId(self->kart)==-1) {
        delete self->item; self->item=0;
    }
    if (self->item) {
        if (self->item->state==5) { delete self->item; self->item=0; }
        else {
            self->item->SetPos(x,y);
            self->item->scale=scale;
            fn_80244524(self->item,visible);
        }
    }
}
#pragma push
#pragma opt_lifetimes off
extern "C" void fn_80243C70(ItemPanel *self) {
    unsigned char saved=self->enabled;
    unsigned char visible=saved;
    float x=self->x, y=self->y, scale=self->scale;
    if (PanelSuppressed(self->kart)==1) { self->enabled=0; visible=0; }
    ResCtrl rc;
    int layer=self->layer;
    fn_80121E10(&rc);
    rc.resId=0xC2E;
    rc.Show(ItemPanelDraw_rodata_803EF5B0[0]*scale+x,ItemPanelDraw_rodata_803EF5B0[1]*scale+y,lbl_806DBE90);
    rc.SetScale(scale);
    if (visible) fn_8011FAFC(&rc,layer);
    if (self->overlay!=-1) {
        ResCtrl overlay;
        fn_80121E10(&overlay);
        overlay.resId=self->overlay;
        overlay.Show(ItemPanelDraw_rodata_803EF5B0[2]*scale+x,ItemPanelDraw_rodata_803EF5B0[3]*scale+y,lbl_806DBE90);
        overlay.SetScaleXY(scale*lbl_806D6DE4,scale*lbl_806D6DE8);
        if (visible) fn_8011FAFC(&overlay,layer);
    }
    if (self->extra!=-1) {
        ResCtrl extra;
        extra.resId=self->extra;
        extra.Show(ItemPanelDraw_rodata_803EF5B0[10]*scale+x,ItemPanelDraw_rodata_803EF5B0[11]*scale+y,lbl_806DBE90);
        extra.SetScaleXY(lbl_806DBEB0*scale,lbl_806DBEB4*scale);
        if (visible) fn_8011FAFC(&extra,self->layer);
    }
    float px=ItemPanelDraw_rodata_803EF5B0[4]*self->scale+x;
    float py=ItemPanelDraw_rodata_803EF5B0[5]*self->scale+y;
    float size;
    if (self->overlay<0) size=self->scale;
    else if (self->variant==0) {
        size=lbl_806DBEB0*self->scale;
        py-=lbl_806DBEB8*self->scale;
    } else size=lbl_806DBEB0*self->scale;
    fn_80121E10(&rc);
    rc.resId=self->icon;
    rc.Show(px,py,lbl_806DBE90);
    rc.SetScale(size);
    if (visible) fn_8011FAFC(&rc,self->layer);
    fn_80244128(self,ItemPanelDraw_rodata_803EF5B0[4]*scale+x,ItemPanelDraw_rodata_803EF5B0[5]*scale+y,scale);
    fn_80244128(self,ItemPanelDraw_rodata_803EF5B0[4]*scale+x,ItemPanelDraw_rodata_803EF5B0[5]*scale+y,scale);
    float mx=ItemPanelDraw_rodata_803EF5B0[6]*scale+x;
    float my=ItemPanelDraw_rodata_803EF5B0[7]*scale+y;
    if (self->mark) {
        DrawPanelMark(self,self->enabled,mx,my,scale);
    }
    x=ItemPanelDraw_rodata_803EF5B0[8]*scale+x;
    px=ItemPanelDraw_rodata_803EF5B0[9]*scale+y;
    DrawPanelItem(self,x,px,scale);
    if (PanelSuppressed(self->kart)==1) self->enabled=saved;
}
#pragma pop
