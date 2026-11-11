#include "game/types/clMrrFace.h"

extern "C" {
extern void PreloadResource(int);
extern void *GetEnemyParam(void);
extern int *AI_GetItemList(void *, int, int, int, int);
extern int fn_8023DBEC(int);
extern int g_gameMode, g_cupId, g_roundIndex;

}

#include "game/ItemListHudPrivate.h"

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

#include "game/FlowScene.h"
extern "C" void fn_8011FAFC(ResCtrl *, int);
#include "game/types/clMrrCaution.h"
struct PulseOwner {
    void *vt;
    int field04, layer;
    unsigned char visible, pad[0x23];
    clMrrCaution *pulse;
};
extern "C" const float lbl_806DBEBC;

clMrrCaution::~clMrrCaution() {}

clMrrFace::~clMrrFace() {
    if (field38) { delete (VObject *)field38; field38 = 0; }
    if (other) { delete (VObject *)other; other = 0; }
    if (field34) { delete (VObject *)field34; field34 = 0; }
    if (field30) { delete (VObject *)field30; field30 = 0; }
}

extern "C" void fn_80244128(ItemPanel *owner, float x, float y, float scale) {
    PulseOwner *self = (PulseOwner *)owner;
    unsigned char visible = self->visible;
    if (scale <= 1.0f && scale >= lbl_806DBEBC) {
        if (!self->pulse) self->pulse = new clMrrCaution(self->field04,self->layer);
    } else {
        if (self->pulse) { delete (VObject *)self->pulse; self->pulse = 0; }
    }
    if (self->pulse) {
        self->pulse->SetPosition(x,y);
        self->pulse->scale=scale;
        self->pulse->Draw(visible);
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

ItemListHud::~ItemListHud() {
    for (int i=7; i>=0; --i) {
        if (objects[i]) { delete objects[i]; objects[i]=0; }
        values[i]=0;
    }
}

extern "C" ItemListHud *fn_80243A24(int layer) { return new ItemListHud(layer); }

extern "C" void fn_80243958(void) {
    int round, cup, mode;
    int *items;
    int i;
    PreloadResource(0xC49);
    PreloadResource(0xC2E);
    PreloadResource(0xC2D);
    PreloadResource(0x1CD3);
    PreloadResource(0x1CD4);
    PreloadResource(0x1CD6);
    if (g_gameMode != 1) {
        for (i = 0; i < 5; ++i) {
            round = g_roundIndex;
            cup = g_cupId;
            mode = g_gameMode;
            items = AI_GetItemList(GetEnemyParam(), mode, cup, round, i);
            while (*items != -1) {
                PreloadResource(fn_8023DBEC(*items));
                ++items;
            }
        }
    }
}

extern "C" void fn_802437AC(clMrrFaceHud *self, RivalPath *path) {
    if (path) {
        self->path = path;
        RivalRender *kart;
        for (int i = 0; i < 8; ++i) {
            RivalPathEntry *entry = PathManager_GetEntrySubStruct(path, i);
            if (!entry || entry->id == -1) continue;
            kart = entry->kart;
            if (!kart) continue;
            int slot = kart->slot;
            if (slot == GetDisplayBufferIndex()) continue;
            self->karts[i] = kart;
            if (kart->character > -1 && kart->character < 13) {
                self->markers[i] = new clMrrFace(kart, self->layer);
            }
        }
    }
}
